/*
 * bcmevent read-only data shared by kernel or app layers
 *
 * Copyright (C) 1999-2016, Broadcom Corporation
 *
 *      Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2 (the "GPL"),
 * available at http://www.broadcom.com/licenses/GPLv2.php, with the
 * following added to such license:
 *
 *      As a special exception, the copyright holders of this software give you
 * permission to link this software with independent modules, and to copy and
 * distribute the resulting executable under terms of your choice, provided that
 * you also meet, for each linked independent module, the terms and conditions of
 * the license of that module.  An independent module is a module which is not
 * derived from this software.  The special exception does not apply to any
 * modifications of the software.
 *
 *      Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Broadcom software provided under a license
 * other than the GPL, without Broadcom's express prior written consent.
 * $Id: bcmevent.c 487870 2014-06-27 07:37:35Z $
 */

#include <typedefs.h>
#include <bcmutils.h>
#include <proto/ethernet.h>
#include <proto/bcmeth.h>
#include <proto/bcmevent.h>

/* Use the actual name for event tracing */
#define BCMEVENT_NAME(_event) {(_event), #_event}

const bcmevent_name_t bcmevent_names[] = {
    BCMEVENT_NAME(WLC_E_SET_SSID),
    BCMEVENT_NAME(WLC_E_JOIN),
    BCMEVENT_NAME(WLC_E_START),
    BCMEVENT_NAME(WLC_E_AUTH),
    BCMEVENT_NAME(WLC_E_AUTH_IND),
    BCMEVENT_NAME(WLC_E_DEAUTH),
    BCMEVENT_NAME(WLC_E_DEAUTH_IND),
    BCMEVENT_NAME(WLC_E_ASSOC),
    BCMEVENT_NAME(WLC_E_ASSOC_IND),
    BCMEVENT_NAME(WLC_E_REASSOC),
    BCMEVENT_NAME(WLC_E_REASSOC_IND),
    BCMEVENT_NAME(WLC_E_DISASSOC),
    BCMEVENT_NAME(WLC_E_DISASSOC_IND),
    BCMEVENT_NAME(WLC_E_QUIET_START),
    BCMEVENT_NAME(WLC_E_QUIET_END),
    BCMEVENT_NAME(WLC_E_BEACON_RX),
    BCMEVENT_NAME(WLC_E_LINK),
    BCMEVENT_NAME(WLC_E_MIC_ERROR),
    BCMEVENT_NAME(WLC_E_NDIS_LINK),
    BCMEVENT_NAME(WLC_E_ROAM),
    BCMEVENT_NAME(WLC_E_TXFAIL),
    BCMEVENT_NAME(WLC_E_PMKID_CACHE),
    BCMEVENT_NAME(WLC_E_RETROGRADE_TSF),
    BCMEVENT_NAME(WLC_E_PRUNE),
    BCMEVENT_NAME(WLC_E_AUTOAUTH),
    BCMEVENT_NAME(WLC_E_EAPOL_MSG),
    BCMEVENT_NAME(WLC_E_SCAN_COMPLETE),
    BCMEVENT_NAME(WLC_E_ADDTS_IND),
    BCMEVENT_NAME(WLC_E_DELTS_IND),
    BCMEVENT_NAME(WLC_E_BCNSENT_IND),
    BCMEVENT_NAME(WLC_E_BCNRX_MSG),
    BCMEVENT_NAME(WLC_E_BCNLOST_MSG),
    BCMEVENT_NAME(WLC_E_ROAM_PREP),
    BCMEVENT_NAME(WLC_E_PFN_NET_FOUND),
    BCMEVENT_NAME(WLC_E_PFN_NET_LOST),
#if defined(IBSS_PEER_DISCOVERY_EVENT)
    BCMEVENT_NAME(WLC_E_IBSS_ASSOC),
#endif /* defined(IBSS_PEER_DISCOVERY_EVENT) */
    BCMEVENT_NAME(WLC_E_RADIO),
    BCMEVENT_NAME(WLC_E_PSM_WATCHDOG),
    BCMEVENT_NAME(WLC_E_PROBREQ_MSG),
    BCMEVENT_NAME(WLC_E_SCAN_CONFIRM_IND),
    BCMEVENT_NAME(WLC_E_PSK_SUP),
    BCMEVENT_NAME(WLC_E_COUNTRY_CODE_CHANGED),
    BCMEVENT_NAME(WLC_E_EXCEEDED_MEDIUM_TIME),
    BCMEVENT_NAME(WLC_E_ICV_ERROR),
    BCMEVENT_NAME(WLC_E_UNICAST_DECODE_ERROR),
    BCMEVENT_NAME(WLC_E_MULTICAST_DECODE_ERROR),
    BCMEVENT_NAME(WLC_E_TRACE),
    BCMEVENT_NAME(WLC_E_IF),
#ifdef WLP2P
    BCMEVENT_NAME(WLC_E_P2P_DISC_LISTEN_COMPLETE),
#endif
    BCMEVENT_NAME(WLC_E_RSSI),
    BCMEVENT_NAME(WLC_E_PFN_SCAN_COMPLETE),
    BCMEVENT_NAME(WLC_E_EXTLOG_MSG),
#ifdef WIFI_ACT_FRAME
    BCMEVENT_NAME(WLC_E_ACTION_FRAME),
    BCMEVENT_NAME(WLC_E_ACTION_FRAME_RX),
    BCMEVENT_NAME(WLC_E_ACTION_FRAME_COMPLETE),
#endif
    BCMEVENT_NAME(WLC_E_ESCAN_RESULT),
    BCMEVENT_NAME(WLC_E_ACTION_FRAME_OFF_CHAN_COMPLETE),
#ifdef WLP2P
    BCMEVENT_NAME(WLC_E_PROBRESP_MSG),
    BCMEVENT_NAME(WLC_E_P2P_PROBREQ_MSG),
#endif
#ifdef PROP_TXSTATUS
    BCMEVENT_NAME(WLC_E_FIFO_CREDIT_MAP),
#endif
    BCMEVENT_NAME(WLC_E_WAKE_EVENT),
    BCMEVENT_NAME(WLC_E_DCS_REQUEST),
    BCMEVENT_NAME(WLC_E_RM_COMPLETE),
#ifdef WLMEDIA_HTSF
    BCMEVENT_NAME(WLC_E_HTSFSYNC),
#endif
    BCMEVENT_NAME(WLC_E_OVERLAY_REQ),
    BCMEVENT_NAME(WLC_E_CSA_COMPLETE_IND),
    BCMEVENT_NAME(WLC_E_EXCESS_PM_WAKE_EVENT),
    BCMEVENT_NAME(WLC_E_PFN_SCAN_NONE),
    BCMEVENT_NAME(WLC_E_PFN_SCAN_ALLGONE),
#ifdef SOFTAP
    BCMEVENT_NAME(WLC_E_GTK_PLUMBED),
#endif
    BCMEVENT_NAME(WLC_E_ASSOC_REQ_IE),
    BCMEVENT_NAME(WLC_E_ASSOC_RESP_IE),
    BCMEVENT_NAME(WLC_E_ACTION_FRAME_RX_NDIS),
    BCMEVENT_NAME(WLC_E_BEACON_FRAME_RX),
#ifdef WLTDLS
    BCMEVENT_NAME(WLC_E_TDLS_PEER_EVENT),
#endif /* WLTDLS */
    BCMEVENT_NAME(WLC_E_NATIVE),
#ifdef WLPKTDLYSTAT
    BCMEVENT_NAME(WLC_E_PKTDELAY_IND),
#endif /* WLPKTDLYSTAT */
    BCMEVENT_NAME(WLC_E_SERVICE_FOUND),
    BCMEVENT_NAME(WLC_E_GAS_FRAGMENT_RX),
    BCMEVENT_NAME(WLC_E_GAS_COMPLETE),
    BCMEVENT_NAME(WLC_E_P2PO_ADD_DEVICE),
    BCMEVENT_NAME(WLC_E_P2PO_DEL_DEVICE),
#ifdef WLWNM
    BCMEVENT_NAME(WLC_E_WNM_STA_SLEEP),
#endif /* WLWNM */
#if defined(WL_PROXDETECT)
    BCMEVENT_NAME(WLC_E_PROXD),
#endif
    BCMEVENT_NAME(WLC_E_CCA_CHAN_QUAL),
    BCMEVENT_NAME(WLC_E_BSSID),
#ifdef PROP_TXSTATUS
    BCMEVENT_NAME(WLC_E_BCMC_CREDIT_SUPPORT),
#endif
    BCMEVENT_NAME(WLC_E_TXFAIL_THRESH),
    BCMEVENT_NAME(WLC_E_RMC_EVENT),
};

const int bcmevent_names_size = ARRAYSIZE(bcmevent_names);
