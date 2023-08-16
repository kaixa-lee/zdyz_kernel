/*
 * linux/arch/arm/mach-pxa/pxa930.c
 *
 * Code specific to PXA930
 *
 * Copyright (C) 2007-2008 Marvell Internation Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/dma-mapping.h>
#include <linux/irq.h>
#include <linux/gpio-pxa.h>
#include <linux/platform_device.h>

#include <mach/pxa930.h>

#include "devices.h"

static struct mfp_addr_map pxa930_mfp_addr_map[] __initdata = {

    MFP_ADDR(GPIO0, 0x02e0),
    MFP_ADDR(GPIO1, 0x02dc),
    MFP_ADDR(GPIO2, 0x02e8),
    MFP_ADDR(GPIO3, 0x02d8),
    MFP_ADDR(GPIO4, 0x02e4),
    MFP_ADDR(GPIO5, 0x02ec),
    MFP_ADDR(GPIO6, 0x02f8),
    MFP_ADDR(GPIO7, 0x02fc),
    MFP_ADDR(GPIO8, 0x0300),
    MFP_ADDR(GPIO9, 0x02d4),
    MFP_ADDR(GPIO10, 0x02f4),
    MFP_ADDR(GPIO11, 0x02f0),
    MFP_ADDR(GPIO12, 0x0304),
    MFP_ADDR(GPIO13, 0x0310),
    MFP_ADDR(GPIO14, 0x0308),
    MFP_ADDR(GPIO15, 0x030c),
    MFP_ADDR(GPIO16, 0x04e8),
    MFP_ADDR(GPIO17, 0x04f4),
    MFP_ADDR(GPIO18, 0x04f8),
    MFP_ADDR(GPIO19, 0x04fc),
    MFP_ADDR(GPIO20, 0x0518),
    MFP_ADDR(GPIO21, 0x051c),
    MFP_ADDR(GPIO22, 0x04ec),
    MFP_ADDR(GPIO23, 0x0500),
    MFP_ADDR(GPIO24, 0x04f0),
    MFP_ADDR(GPIO25, 0x0504),
    MFP_ADDR(GPIO26, 0x0510),
    MFP_ADDR(GPIO27, 0x0514),
    MFP_ADDR(GPIO28, 0x0520),
    MFP_ADDR(GPIO29, 0x0600),
    MFP_ADDR(GPIO30, 0x0618),
    MFP_ADDR(GPIO31, 0x0610),
    MFP_ADDR(GPIO32, 0x060c),
    MFP_ADDR(GPIO33, 0x061c),
    MFP_ADDR(GPIO34, 0x0620),
    MFP_ADDR(GPIO35, 0x0628),
    MFP_ADDR(GPIO36, 0x062c),
    MFP_ADDR(GPIO37, 0x0630),
    MFP_ADDR(GPIO38, 0x0634),
    MFP_ADDR(GPIO39, 0x0638),
    MFP_ADDR(GPIO40, 0x063c),
    MFP_ADDR(GPIO41, 0x0614),
    MFP_ADDR(GPIO42, 0x0624),
    MFP_ADDR(GPIO43, 0x0608),
    MFP_ADDR(GPIO44, 0x0604),
    MFP_ADDR(GPIO45, 0x050c),
    MFP_ADDR(GPIO46, 0x0508),
    MFP_ADDR(GPIO47, 0x02bc),
    MFP_ADDR(GPIO48, 0x02b4),
    MFP_ADDR(GPIO49, 0x02b8),
    MFP_ADDR(GPIO50, 0x02c8),
    MFP_ADDR(GPIO51, 0x02c0),
    MFP_ADDR(GPIO52, 0x02c4),
    MFP_ADDR(GPIO53, 0x02d0),
    MFP_ADDR(GPIO54, 0x02cc),
    MFP_ADDR(GPIO55, 0x029c),
    MFP_ADDR(GPIO56, 0x02a0),
    MFP_ADDR(GPIO57, 0x0294),
    MFP_ADDR(GPIO58, 0x0298),
    MFP_ADDR(GPIO59, 0x02a4),
    MFP_ADDR(GPIO60, 0x02a8),
    MFP_ADDR(GPIO61, 0x02b0),
    MFP_ADDR(GPIO62, 0x02ac),
    MFP_ADDR(GPIO63, 0x0640),
    MFP_ADDR(GPIO64, 0x065c),
    MFP_ADDR(GPIO65, 0x0648),
    MFP_ADDR(GPIO66, 0x0644),
    MFP_ADDR(GPIO67, 0x0674),
    MFP_ADDR(GPIO68, 0x0658),
    MFP_ADDR(GPIO69, 0x0654),
    MFP_ADDR(GPIO70, 0x0660),
    MFP_ADDR(GPIO71, 0x0668),
    MFP_ADDR(GPIO72, 0x0664),
    MFP_ADDR(GPIO73, 0x0650),
    MFP_ADDR(GPIO74, 0x066c),
    MFP_ADDR(GPIO75, 0x064c),
    MFP_ADDR(GPIO76, 0x0670),
    MFP_ADDR(GPIO77, 0x0678),
    MFP_ADDR(GPIO78, 0x067c),
    MFP_ADDR(GPIO79, 0x0694),
    MFP_ADDR(GPIO80, 0x069c),
    MFP_ADDR(GPIO81, 0x06a0),
    MFP_ADDR(GPIO82, 0x06a4),
    MFP_ADDR(GPIO83, 0x0698),
    MFP_ADDR(GPIO84, 0x06bc),
    MFP_ADDR(GPIO85, 0x06b4),
    MFP_ADDR(GPIO86, 0x06b0),
    MFP_ADDR(GPIO87, 0x06c0),
    MFP_ADDR(GPIO88, 0x06c4),
    MFP_ADDR(GPIO89, 0x06ac),
    MFP_ADDR(GPIO90, 0x0680),
    MFP_ADDR(GPIO91, 0x0684),
    MFP_ADDR(GPIO92, 0x0688),
    MFP_ADDR(GPIO93, 0x0690),
    MFP_ADDR(GPIO94, 0x068c),
    MFP_ADDR(GPIO95, 0x06a8),
    MFP_ADDR(GPIO96, 0x06b8),
    MFP_ADDR(GPIO97, 0x0410),
    MFP_ADDR(GPIO98, 0x0418),
    MFP_ADDR(GPIO99, 0x041c),
    MFP_ADDR(GPIO100, 0x0414),
    MFP_ADDR(GPIO101, 0x0408),
    MFP_ADDR(GPIO102, 0x0324),
    MFP_ADDR(GPIO103, 0x040c),
    MFP_ADDR(GPIO104, 0x0400),
    MFP_ADDR(GPIO105, 0x0328),
    MFP_ADDR(GPIO106, 0x0404),

    MFP_ADDR(nXCVREN, 0x0204),
    MFP_ADDR(DF_CLE_nOE, 0x020c),
    MFP_ADDR(DF_nADV1_ALE, 0x0218),
    MFP_ADDR(DF_SCLK_E, 0x0214),
    MFP_ADDR(DF_SCLK_S, 0x0210),
    MFP_ADDR(nBE0, 0x021c),
    MFP_ADDR(nBE1, 0x0220),
    MFP_ADDR(DF_nADV2_ALE, 0x0224),
    MFP_ADDR(DF_INT_RnB, 0x0228),
    MFP_ADDR(DF_nCS0, 0x022c),
    MFP_ADDR(DF_nCS1, 0x0230),
    MFP_ADDR(nLUA, 0x0254),
    MFP_ADDR(nLLA, 0x0258),
    MFP_ADDR(DF_nWE, 0x0234),
    MFP_ADDR(DF_nRE_nOE, 0x0238),
    MFP_ADDR(DF_ADDR0, 0x024c),
    MFP_ADDR(DF_ADDR1, 0x0250),
    MFP_ADDR(DF_ADDR2, 0x025c),
    MFP_ADDR(DF_ADDR3, 0x0260),
    MFP_ADDR(DF_IO0, 0x023c),
    MFP_ADDR(DF_IO1, 0x0240),
    MFP_ADDR(DF_IO2, 0x0244),
    MFP_ADDR(DF_IO3, 0x0248),
    MFP_ADDR(DF_IO4, 0x0264),
    MFP_ADDR(DF_IO5, 0x0268),
    MFP_ADDR(DF_IO6, 0x026c),
    MFP_ADDR(DF_IO7, 0x0270),
    MFP_ADDR(DF_IO8, 0x0274),
    MFP_ADDR(DF_IO9, 0x0278),
    MFP_ADDR(DF_IO10, 0x027c),
    MFP_ADDR(DF_IO11, 0x0280),
    MFP_ADDR(DF_IO12, 0x0284),
    MFP_ADDR(DF_IO13, 0x0288),
    MFP_ADDR(DF_IO14, 0x028c),
    MFP_ADDR(DF_IO15, 0x0290),

    MFP_ADDR(GSIM_UIO, 0x0314),
    MFP_ADDR(GSIM_UCLK, 0x0318),
    MFP_ADDR(GSIM_UDET, 0x031c),
    MFP_ADDR(GSIM_nURST, 0x0320),

    MFP_ADDR(PMIC_INT, 0x06c8),

    MFP_ADDR(RDY, 0x0200),

    MFP_ADDR_END,
};

static struct mfp_addr_map pxa935_mfp_addr_map[] __initdata = {
    MFP_ADDR(GPIO159, 0x0524),
    MFP_ADDR(GPIO163, 0x0534),
    MFP_ADDR(GPIO167, 0x0544),
    MFP_ADDR(GPIO168, 0x0548),
    MFP_ADDR(GPIO169, 0x054c),
    MFP_ADDR(GPIO170, 0x0550),
    MFP_ADDR(GPIO171, 0x0554),
    MFP_ADDR(GPIO172, 0x0558),
    MFP_ADDR(GPIO173, 0x055c),

    MFP_ADDR_END,
};

static struct pxa_gpio_platform_data pxa93x_gpio_pdata = {
    .irq_base	= PXA_GPIO_TO_IRQ(0),
};

static int __init pxa930_init(void)
{
    int ret = 0;

    if (cpu_is_pxa93x()) {
        mfp_init_base(io_p2v(MFPR_BASE));
        mfp_init_addr(pxa930_mfp_addr_map);
        platform_device_add_data(&pxa93x_device_gpio,
                                 &pxa93x_gpio_pdata,
                                 sizeof(pxa93x_gpio_pdata));
        ret = platform_device_register(&pxa93x_device_gpio);
    }

    if (cpu_is_pxa935()) {
        mfp_init_addr(pxa935_mfp_addr_map);
    }

    return 0;
}

core_initcall(pxa930_init);