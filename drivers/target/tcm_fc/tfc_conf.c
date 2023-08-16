/*******************************************************************************
 * Filename:  tcm_fc.c
 *
 * This file contains the configfs implementation for TCM_fc fabric node.
 * Based on tcm_loop_configfs.c
 *
 * Copyright (c) 2010 Cisco Systems, Inc.
 * Copyright (c) 2009,2010 Rising Tide, Inc.
 * Copyright (c) 2009,2010 Linux-iSCSI.org
 *
 * Copyright (c) 2009,2010 Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 ****************************************************************************/

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <generated/utsrelease.h>
#include <linux/utsname.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/configfs.h>
#include <linux/kernel.h>
#include <linux/ctype.h>
#include <asm/unaligned.h>
#include <scsi/scsi.h>
#include <scsi/scsi_host.h>
#include <scsi/scsi_device.h>
#include <scsi/scsi_cmnd.h>
#include <scsi/libfc.h>

#include <target/target_core_base.h>
#include <target/target_core_fabric.h>
#include <target/target_core_fabric_configfs.h>
#include <target/target_core_configfs.h>
#include <target/configfs_macros.h>

#include "tcm_fc.h"

static const struct target_core_fabric_ops ft_fabric_ops;

static LIST_HEAD(ft_wwn_list);
DEFINE_MUTEX(ft_lport_lock);

unsigned int ft_debug_logging;
module_param_named(debug_logging, ft_debug_logging, int, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(debug_logging, "a bit mask of logging levels");

/*
 * Parse WWN.
 * If strict, we require lower-case hex and colon separators to be sure
 * the name is the same as what would be generated by ft_format_wwn()
 * so the name and wwn are mapped one-to-one.
 */
static ssize_t ft_parse_wwn(const char *name, u64 *wwn, int strict)
{
    const char *cp;
    char c;
    u32 byte = 0;
    u32 pos = 0;
    u32 err;
    int val;

    *wwn = 0;
    for (cp = name; cp < &name[FT_NAMELEN - 1]; cp++) {
        c = *cp;
        if (c == '\n' && cp[1] == '\0') {
            continue;
        }
        if (strict && pos++ == 2 && byte++ < 7) {
            pos = 0;
            if (c == ':') {
                continue;
            }
            err = 1;
            goto fail;
        }
        if (c == '\0') {
            err = 2;
            if (strict && byte != 8) {
                goto fail;
            }
            return cp - name;
        }
        err = 3;
        val = hex_to_bin(c);
        if (val < 0 || (strict && isupper(c))) {
            goto fail;
        }
        *wwn = (*wwn << 4) | val;
    }
    err = 4;
fail:
    pr_debug("err %u len %zu pos %u byte %u\n",
             err, cp - name, pos, byte);
    return -1;
}

ssize_t ft_format_wwn(char *buf, size_t len, u64 wwn)
{
    u8 b[8];

    put_unaligned_be64(wwn, b);
    return snprintf(buf, len,
                    "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x",
                    b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
}

static ssize_t ft_wwn_show(void *arg, char *buf)
{
    u64 *wwn = arg;
    ssize_t len;

    len = ft_format_wwn(buf, PAGE_SIZE - 2, *wwn);
    buf[len++] = '\n';
    return len;
}

static ssize_t ft_wwn_store(void *arg, const char *buf, size_t len)
{
    ssize_t ret;
    u64 wwn;

    ret = ft_parse_wwn(buf, &wwn, 0);
    if (ret > 0) {
        *(u64 *)arg = wwn;
    }
    return ret;
}

/*
 * ACL auth ops.
 */

static ssize_t ft_nacl_show_port_name(
    struct se_node_acl *se_nacl,
    char *page)
{
    struct ft_node_acl *acl = container_of(se_nacl,
                                           struct ft_node_acl, se_node_acl);

    return ft_wwn_show(&acl->node_auth.port_name, page);
}

static ssize_t ft_nacl_store_port_name(
    struct se_node_acl *se_nacl,
    const char *page,
    size_t count)
{
    struct ft_node_acl *acl = container_of(se_nacl,
                                           struct ft_node_acl, se_node_acl);

    return ft_wwn_store(&acl->node_auth.port_name, page, count);
}

TF_NACL_BASE_ATTR(ft, port_name, S_IRUGO | S_IWUSR);

static ssize_t ft_nacl_show_node_name(
    struct se_node_acl *se_nacl,
    char *page)
{
    struct ft_node_acl *acl = container_of(se_nacl,
                                           struct ft_node_acl, se_node_acl);

    return ft_wwn_show(&acl->node_auth.node_name, page);
}

static ssize_t ft_nacl_store_node_name(
    struct se_node_acl *se_nacl,
    const char *page,
    size_t count)
{
    struct ft_node_acl *acl = container_of(se_nacl,
                                           struct ft_node_acl, se_node_acl);

    return ft_wwn_store(&acl->node_auth.node_name, page, count);
}

TF_NACL_BASE_ATTR(ft, node_name, S_IRUGO | S_IWUSR);

static struct configfs_attribute *ft_nacl_base_attrs[] = {
    &ft_nacl_port_name.attr,
    &ft_nacl_node_name.attr,
    NULL,
};

/*
 * ACL ops.
 */

/*
 * Add ACL for an initiator.  The ACL is named arbitrarily.
 * The port_name and/or node_name are attributes.
 */
static struct se_node_acl *ft_add_acl(
    struct se_portal_group *se_tpg,
    struct config_group *group,
    const char *name)
{
    struct ft_node_acl *acl;
    struct ft_tpg *tpg;
    u64 wwpn;
    u32 q_depth;

    pr_debug("add acl %s\n", name);
    tpg = container_of(se_tpg, struct ft_tpg, se_tpg);

    if (ft_parse_wwn(name, &wwpn, 1) < 0) {
        return ERR_PTR(-EINVAL);
    }

    acl = kzalloc(sizeof(struct ft_node_acl), GFP_KERNEL);
    if (!acl) {
        return ERR_PTR(-ENOMEM);
    }
    acl->node_auth.port_name = wwpn;

    q_depth = 32;		/* XXX bogus default - get from tpg? */
    return core_tpg_add_initiator_node_acl(&tpg->se_tpg,
                                           &acl->se_node_acl, name, q_depth);
}

static void ft_del_acl(struct se_node_acl *se_acl)
{
    struct se_portal_group *se_tpg = se_acl->se_tpg;
    struct ft_tpg *tpg;
    struct ft_node_acl *acl = container_of(se_acl,
                                           struct ft_node_acl, se_node_acl);

    pr_debug("del acl %s\n",
             config_item_name(&se_acl->acl_group.cg_item));

    tpg = container_of(se_tpg, struct ft_tpg, se_tpg);
    pr_debug("del acl %p se_acl %p tpg %p se_tpg %p\n",
             acl, se_acl, tpg, &tpg->se_tpg);

    core_tpg_del_initiator_node_acl(&tpg->se_tpg, se_acl, 1);
    kfree(acl);
}

struct ft_node_acl *ft_acl_get(struct ft_tpg *tpg, struct fc_rport_priv *rdata)
{
    struct ft_node_acl *found = NULL;
    struct ft_node_acl *acl;
    struct se_portal_group *se_tpg = &tpg->se_tpg;
    struct se_node_acl *se_acl;

    spin_lock_irq(&se_tpg->acl_node_lock);
    list_for_each_entry(se_acl, &se_tpg->acl_node_list, acl_list) {
        acl = container_of(se_acl, struct ft_node_acl, se_node_acl);
        pr_debug("acl %p port_name %llx\n",
                 acl, (unsigned long long)acl->node_auth.port_name);
        if (acl->node_auth.port_name == rdata->ids.port_name ||
            acl->node_auth.node_name == rdata->ids.node_name) {
            pr_debug("acl %p port_name %llx matched\n", acl,
                     (unsigned long long)rdata->ids.port_name);
            found = acl;
            /* XXX need to hold onto ACL */
            break;
        }
    }
    spin_unlock_irq(&se_tpg->acl_node_lock);
    return found;
}

static struct se_node_acl *ft_tpg_alloc_fabric_acl(struct se_portal_group *se_tpg)
{
    struct ft_node_acl *acl;

    acl = kzalloc(sizeof(*acl), GFP_KERNEL);
    if (!acl) {
        pr_err("Unable to allocate struct ft_node_acl\n");
        return NULL;
    }
    pr_debug("acl %p\n", acl);
    return &acl->se_node_acl;
}

static void ft_tpg_release_fabric_acl(struct se_portal_group *se_tpg,
                                      struct se_node_acl *se_acl)
{
    struct ft_node_acl *acl = container_of(se_acl,
                                           struct ft_node_acl, se_node_acl);

    pr_debug("acl %p\n", acl);
    kfree(acl);
}

/*
 * local_port port_group (tpg) ops.
 */
static struct se_portal_group *ft_add_tpg(
    struct se_wwn *wwn,
    struct config_group *group,
    const char *name)
{
    struct ft_lport_wwn *ft_wwn;
    struct ft_tpg *tpg;
    struct workqueue_struct *wq;
    unsigned long index;
    int ret;

    pr_debug("tcm_fc: add tpg %s\n", name);

    /*
     * Name must be "tpgt_" followed by the index.
     */
    if (strstr(name, "tpgt_") != name) {
        return NULL;
    }

    ret = kstrtoul(name + 5, 10, &index);
    if (ret) {
        return NULL;
    }
    if (index > UINT_MAX) {
        return NULL;
    }

    if ((index != 1)) {
        pr_err("Error, a single TPG=1 is used for HW port mappings\n");
        return ERR_PTR(-ENOSYS);
    }

    ft_wwn = container_of(wwn, struct ft_lport_wwn, se_wwn);
    tpg = kzalloc(sizeof(*tpg), GFP_KERNEL);
    if (!tpg) {
        return NULL;
    }
    tpg->index = index;
    tpg->lport_wwn = ft_wwn;
    INIT_LIST_HEAD(&tpg->lun_list);

    wq = alloc_workqueue("tcm_fc", 0, 1);
    if (!wq) {
        kfree(tpg);
        return NULL;
    }

    ret = core_tpg_register(&ft_fabric_ops, wwn, &tpg->se_tpg,
                            tpg, TRANSPORT_TPG_TYPE_NORMAL);
    if (ret < 0) {
        destroy_workqueue(wq);
        kfree(tpg);
        return NULL;
    }
    tpg->workqueue = wq;

    mutex_lock(&ft_lport_lock);
    ft_wwn->tpg = tpg;
    mutex_unlock(&ft_lport_lock);

    return &tpg->se_tpg;
}

static void ft_del_tpg(struct se_portal_group *se_tpg)
{
    struct ft_tpg *tpg = container_of(se_tpg, struct ft_tpg, se_tpg);
    struct ft_lport_wwn *ft_wwn = tpg->lport_wwn;

    pr_debug("del tpg %s\n",
             config_item_name(&tpg->se_tpg.tpg_group.cg_item));

    destroy_workqueue(tpg->workqueue);

    /* Wait for sessions to be freed thru RCU, for BUG_ON below */
    synchronize_rcu();

    mutex_lock(&ft_lport_lock);
    ft_wwn->tpg = NULL;
    if (tpg->tport) {
        tpg->tport->tpg = NULL;
        tpg->tport = NULL;
    }
    mutex_unlock(&ft_lport_lock);

    core_tpg_deregister(se_tpg);
    kfree(tpg);
}

/*
 * Verify that an lport is configured to use the tcm_fc module, and return
 * the target port group that should be used.
 *
 * The caller holds ft_lport_lock.
 */
struct ft_tpg *ft_lport_find_tpg(struct fc_lport *lport)
{
    struct ft_lport_wwn *ft_wwn;

    list_for_each_entry(ft_wwn, &ft_wwn_list, ft_wwn_node) {
        if (ft_wwn->wwpn == lport->wwpn) {
            return ft_wwn->tpg;
        }
    }
    return NULL;
}

/*
 * target config instance ops.
 */

/*
 * Add lport to allowed config.
 * The name is the WWPN in lower-case ASCII, colon-separated bytes.
 */
static struct se_wwn *ft_add_wwn(
    struct target_fabric_configfs *tf,
    struct config_group *group,
    const char *name)
{
    struct ft_lport_wwn *ft_wwn;
    struct ft_lport_wwn *old_ft_wwn;
    u64 wwpn;

    pr_debug("add wwn %s\n", name);
    if (ft_parse_wwn(name, &wwpn, 1) < 0) {
        return NULL;
    }
    ft_wwn = kzalloc(sizeof(*ft_wwn), GFP_KERNEL);
    if (!ft_wwn) {
        return NULL;
    }
    ft_wwn->wwpn = wwpn;

    mutex_lock(&ft_lport_lock);
    list_for_each_entry(old_ft_wwn, &ft_wwn_list, ft_wwn_node) {
        if (old_ft_wwn->wwpn == wwpn) {
            mutex_unlock(&ft_lport_lock);
            kfree(ft_wwn);
            return NULL;
        }
    }
    list_add_tail(&ft_wwn->ft_wwn_node, &ft_wwn_list);
    ft_format_wwn(ft_wwn->name, sizeof(ft_wwn->name), wwpn);
    mutex_unlock(&ft_lport_lock);

    return &ft_wwn->se_wwn;
}

static void ft_del_wwn(struct se_wwn *wwn)
{
    struct ft_lport_wwn *ft_wwn = container_of(wwn,
                                  struct ft_lport_wwn, se_wwn);

    pr_debug("del wwn %s\n", ft_wwn->name);
    mutex_lock(&ft_lport_lock);
    list_del(&ft_wwn->ft_wwn_node);
    mutex_unlock(&ft_lport_lock);

    kfree(ft_wwn);
}

static ssize_t ft_wwn_show_attr_version(
    struct target_fabric_configfs *tf,
    char *page)
{
    return sprintf(page, "TCM FC " FT_VERSION " on %s/%s on "
                   ""UTS_RELEASE"\n",  utsname()->sysname, utsname()->machine);
}

TF_WWN_ATTR_RO(ft, version);

static struct configfs_attribute *ft_wwn_attrs[] = {
    &ft_wwn_version.attr,
    NULL,
};

static char *ft_get_fabric_name(void)
{
    return "fc";
}

static char *ft_get_fabric_wwn(struct se_portal_group *se_tpg)
{
    struct ft_tpg *tpg = se_tpg->se_tpg_fabric_ptr;

    return tpg->lport_wwn->name;
}

static u16 ft_get_tag(struct se_portal_group *se_tpg)
{
    struct ft_tpg *tpg = se_tpg->se_tpg_fabric_ptr;

    /*
     * This tag is used when forming SCSI Name identifier in EVPD=1 0x83
     * to represent the SCSI Target Port.
     */
    return tpg->index;
}

static u32 ft_get_default_depth(struct se_portal_group *se_tpg)
{
    return 1;
}

static int ft_check_false(struct se_portal_group *se_tpg)
{
    return 0;
}

static void ft_set_default_node_attr(struct se_node_acl *se_nacl)
{
}

static u32 ft_tpg_get_inst_index(struct se_portal_group *se_tpg)
{
    struct ft_tpg *tpg = se_tpg->se_tpg_fabric_ptr;

    return tpg->index;
}

static const struct target_core_fabric_ops ft_fabric_ops = {
    .module =			THIS_MODULE,
    .name =				"fc",
    .get_fabric_name =		ft_get_fabric_name,
    .get_fabric_proto_ident =	fc_get_fabric_proto_ident,
    .tpg_get_wwn =			ft_get_fabric_wwn,
    .tpg_get_tag =			ft_get_tag,
    .tpg_get_default_depth =	ft_get_default_depth,
    .tpg_get_pr_transport_id =	fc_get_pr_transport_id,
    .tpg_get_pr_transport_id_len =	fc_get_pr_transport_id_len,
    .tpg_parse_pr_out_transport_id = fc_parse_pr_out_transport_id,
    .tpg_check_demo_mode =		ft_check_false,
    .tpg_check_demo_mode_cache =	ft_check_false,
    .tpg_check_demo_mode_write_protect = ft_check_false,
    .tpg_check_prod_mode_write_protect = ft_check_false,
    .tpg_alloc_fabric_acl =		ft_tpg_alloc_fabric_acl,
    .tpg_release_fabric_acl =	ft_tpg_release_fabric_acl,
    .tpg_get_inst_index =		ft_tpg_get_inst_index,
    .check_stop_free =		ft_check_stop_free,
    .release_cmd =			ft_release_cmd,
    .shutdown_session =		ft_sess_shutdown,
    .close_session =		ft_sess_close,
    .sess_get_index =		ft_sess_get_index,
    .sess_get_initiator_sid =	NULL,
    .write_pending =		ft_write_pending,
    .write_pending_status =		ft_write_pending_status,
    .set_default_node_attributes =	ft_set_default_node_attr,
    .get_task_tag =			ft_get_task_tag,
    .get_cmd_state =		ft_get_cmd_state,
    .queue_data_in =		ft_queue_data_in,
    .queue_status =			ft_queue_status,
    .queue_tm_rsp =			ft_queue_tm_resp,
    .aborted_task =			ft_aborted_task,
    /*
     * Setup function pointers for generic logic in
     * target_core_fabric_configfs.c
     */
    .fabric_make_wwn =		&ft_add_wwn,
    .fabric_drop_wwn =		&ft_del_wwn,
    .fabric_make_tpg =		&ft_add_tpg,
    .fabric_drop_tpg =		&ft_del_tpg,
    .fabric_post_link =		NULL,
    .fabric_pre_unlink =		NULL,
    .fabric_make_np =		NULL,
    .fabric_drop_np =		NULL,
    .fabric_make_nodeacl =		&ft_add_acl,
    .fabric_drop_nodeacl =		&ft_del_acl,

    .tfc_wwn_attrs			= ft_wwn_attrs,
    .tfc_tpg_nacl_base_attrs	= ft_nacl_base_attrs,
};

static struct notifier_block ft_notifier = {
    .notifier_call = ft_lport_notify
};

static int __init ft_init(void)
{
    int ret;

    ret = target_register_template(&ft_fabric_ops);
    if (ret) {
        goto out;
    }

    ret = fc_fc4_register_provider(FC_TYPE_FCP, &ft_prov);
    if (ret) {
        goto out_unregister_template;
    }

    blocking_notifier_chain_register(&fc_lport_notifier_head, &ft_notifier);
    fc_lport_iterate(ft_lport_add, NULL);
    return 0;

out_unregister_template:
    target_unregister_template(&ft_fabric_ops);
out:
    return ret;
}

static void __exit ft_exit(void)
{
    blocking_notifier_chain_unregister(&fc_lport_notifier_head,
                                       &ft_notifier);
    fc_fc4_deregister_provider(FC_TYPE_FCP, &ft_prov);
    fc_lport_iterate(ft_lport_del, NULL);
    target_unregister_template(&ft_fabric_ops);
    synchronize_rcu();
}

MODULE_DESCRIPTION("FC TCM fabric driver " FT_VERSION);
MODULE_LICENSE("GPL");
module_init(ft_init);
module_exit(ft_exit);
