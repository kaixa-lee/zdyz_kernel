/*
 * DRA7xx Power domains framework
 *
 * Copyright (C) 2009-2013 Texas Instruments, Inc.
 * Copyright (C) 2009-2011 Nokia Corporation
 *
 * Generated by code originally written by:
 * Abhijit Pagare (abhijitpagare@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 * Paul Walmsley (paul@pwsan.com)
 *
 * This file is automatically generated from the OMAP hardware databases.
 * We respectfully ask that any modifications to this file be coordinated
 * with the public linux-omap@vger.kernel.org mailing list and the
 * authors above to ensure that the autogeneration scripts are kept
 * up-to-date with the file contents.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>

#include "powerdomain.h"

#include "prcm-common.h"
#include "prcm44xx.h"
#include "prm7xx.h"
#include "prcm_mpu7xx.h"

/* iva_7xx_pwrdm: IVA-HD power domain */
static struct powerdomain iva_7xx_pwrdm = {
    .name		  = "iva_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_IVA_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_RET_ON,
    .pwrsts_logic_ret = PWRSTS_OFF,
    .banks		  = 4,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* hwa_mem */
        [1] = PWRSTS_OFF_RET,	/* sl2_mem */
        [2] = PWRSTS_OFF_RET,	/* tcm1_mem */
        [3] = PWRSTS_OFF_RET,	/* tcm2_mem */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* hwa_mem */
        [1] = PWRSTS_OFF_RET,	/* sl2_mem */
        [2] = PWRSTS_OFF_RET,	/* tcm1_mem */
        [3] = PWRSTS_OFF_RET,	/* tcm2_mem */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* rtc_7xx_pwrdm:  */
static struct powerdomain rtc_7xx_pwrdm = {
    .name		  = "rtc_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_RTC_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_ON,
};

/* custefuse_7xx_pwrdm: Customer efuse controller power domain */
static struct powerdomain custefuse_7xx_pwrdm = {
    .name		  = "custefuse_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_CUSTEFUSE_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_ON,
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* ipu_7xx_pwrdm: Audio back end power domain */
static struct powerdomain ipu_7xx_pwrdm = {
    .name		  = "ipu_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_IPU_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_RET_ON,
    .pwrsts_logic_ret = PWRSTS_OFF,
    .banks		  = 2,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* aessmem */
        [1] = PWRSTS_OFF_RET,	/* periphmem */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* aessmem */
        [1] = PWRSTS_OFF_RET,	/* periphmem */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* dss_7xx_pwrdm: Display subsystem power domain */
static struct powerdomain dss_7xx_pwrdm = {
    .name		  = "dss_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_DSS_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_RET_ON,
    .pwrsts_logic_ret = PWRSTS_OFF,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* dss_mem */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* dss_mem */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* l4per_7xx_pwrdm: Target peripherals power domain */
static struct powerdomain l4per_7xx_pwrdm = {
    .name		  = "l4per_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_L4PER_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_RET_ON,
    .pwrsts_logic_ret = PWRSTS_OFF_RET,
    .banks		  = 2,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* nonretained_bank */
        [1] = PWRSTS_OFF_RET,	/* retained_bank */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* nonretained_bank */
        [1] = PWRSTS_OFF_RET,	/* retained_bank */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* gpu_7xx_pwrdm: 3D accelerator power domain */
static struct powerdomain gpu_7xx_pwrdm = {
    .name		  = "gpu_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_GPU_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_ON,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* gpu_mem */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* gpu_mem */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* wkupaon_7xx_pwrdm: Wake-up power domain */
static struct powerdomain wkupaon_7xx_pwrdm = {
    .name		  = "wkupaon_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_WKUPAON_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_ON,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_ON,	/* wkup_bank */
    },
};

/* core_7xx_pwrdm: CORE power domain */
static struct powerdomain core_7xx_pwrdm = {
    .name		  = "core_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_CORE_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_INA_ON,
    .pwrsts_logic_ret = PWRSTS_RET,
    .banks		  = 5,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* core_nret_bank */
        [1] = PWRSTS_OFF_RET,	/* core_ocmram */
        [2] = PWRSTS_OFF_RET,	/* core_other_bank */
        [3] = PWRSTS_OFF_RET,	/* ipu_l2ram */
        [4] = PWRSTS_OFF_RET,	/* ipu_unicache */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* core_nret_bank */
        [1] = PWRSTS_OFF_RET,	/* core_ocmram */
        [2] = PWRSTS_OFF_RET,	/* core_other_bank */
        [3] = PWRSTS_OFF_RET,	/* ipu_l2ram */
        [4] = PWRSTS_OFF_RET,	/* ipu_unicache */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* coreaon_7xx_pwrdm: Always ON logic that sits in VDD_CORE voltage domain */
static struct powerdomain coreaon_7xx_pwrdm = {
    .name		  = "coreaon_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_COREAON_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_ON,
};

/* cpu0_7xx_pwrdm: MPU0 processor and Neon coprocessor power domain */
static struct powerdomain cpu0_7xx_pwrdm = {
    .name		  = "cpu0_pwrdm",
    .prcm_offs	  = DRA7XX_MPU_PRCM_PRM_C0_INST,
    .prcm_partition	  = DRA7XX_MPU_PRCM_PARTITION,
    .pwrsts		  = PWRSTS_RET_ON,
    .pwrsts_logic_ret = PWRSTS_RET,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* cpu0_l1 */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_ON,	/* cpu0_l1 */
    },
};

/* cpu1_7xx_pwrdm: MPU1 processor and Neon coprocessor power domain */
static struct powerdomain cpu1_7xx_pwrdm = {
    .name		  = "cpu1_pwrdm",
    .prcm_offs	  = DRA7XX_MPU_PRCM_PRM_C1_INST,
    .prcm_partition	  = DRA7XX_MPU_PRCM_PARTITION,
    .pwrsts		  = PWRSTS_RET_ON,
    .pwrsts_logic_ret = PWRSTS_RET,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* cpu1_l1 */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_ON,	/* cpu1_l1 */
    },
};

/* vpe_7xx_pwrdm:  */
static struct powerdomain vpe_7xx_pwrdm = {
    .name		  = "vpe_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_VPE_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_RET_ON,
    .pwrsts_logic_ret = PWRSTS_OFF_RET,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* vpe_bank */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* vpe_bank */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* mpu_7xx_pwrdm: Modena processor and the Neon coprocessor power domain */
static struct powerdomain mpu_7xx_pwrdm = {
    .name		  = "mpu_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_MPU_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_RET_ON,
    .pwrsts_logic_ret = PWRSTS_RET,
    .banks		  = 2,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* mpu_l2 */
        [1] = PWRSTS_RET,	/* mpu_ram */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* mpu_l2 */
        [1] = PWRSTS_OFF_RET,	/* mpu_ram */
    },
};

/* l3init_7xx_pwrdm: L3 initators pheripherals power domain  */
static struct powerdomain l3init_7xx_pwrdm = {
    .name		  = "l3init_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_L3INIT_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_RET_ON,
    .pwrsts_logic_ret = PWRSTS_OFF_RET,
    .banks		  = 3,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* gmac_bank */
        [1] = PWRSTS_OFF_RET,	/* l3init_bank1 */
        [2] = PWRSTS_OFF_RET,	/* l3init_bank2 */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* gmac_bank */
        [1] = PWRSTS_OFF_RET,	/* l3init_bank1 */
        [2] = PWRSTS_OFF_RET,	/* l3init_bank2 */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* eve3_7xx_pwrdm:  */
static struct powerdomain eve3_7xx_pwrdm = {
    .name		  = "eve3_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_EVE3_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_ON,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* eve3_bank */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* eve3_bank */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* emu_7xx_pwrdm: Emulation power domain */
static struct powerdomain emu_7xx_pwrdm = {
    .name		  = "emu_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_EMU_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_ON,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* emu_bank */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* emu_bank */
    },
};

/* dsp2_7xx_pwrdm:  */
static struct powerdomain dsp2_7xx_pwrdm = {
    .name		  = "dsp2_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_DSP2_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_ON,
    .banks		  = 3,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* dsp2_edma */
        [1] = PWRSTS_OFF_RET,	/* dsp2_l1 */
        [2] = PWRSTS_OFF_RET,	/* dsp2_l2 */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* dsp2_edma */
        [1] = PWRSTS_OFF_RET,	/* dsp2_l1 */
        [2] = PWRSTS_OFF_RET,	/* dsp2_l2 */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* dsp1_7xx_pwrdm: Tesla processor power domain */
static struct powerdomain dsp1_7xx_pwrdm = {
    .name		  = "dsp1_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_DSP1_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_ON,
    .banks		  = 3,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* dsp1_edma */
        [1] = PWRSTS_OFF_RET,	/* dsp1_l1 */
        [2] = PWRSTS_OFF_RET,	/* dsp1_l2 */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* dsp1_edma */
        [1] = PWRSTS_OFF_RET,	/* dsp1_l1 */
        [2] = PWRSTS_OFF_RET,	/* dsp1_l2 */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* cam_7xx_pwrdm: Camera subsystem power domain */
static struct powerdomain cam_7xx_pwrdm = {
    .name		  = "cam_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_CAM_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_ON,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* vip_bank */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* vip_bank */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* eve4_7xx_pwrdm:  */
static struct powerdomain eve4_7xx_pwrdm = {
    .name		  = "eve4_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_EVE4_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_ON,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* eve4_bank */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* eve4_bank */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* eve2_7xx_pwrdm:  */
static struct powerdomain eve2_7xx_pwrdm = {
    .name		  = "eve2_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_EVE2_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_ON,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* eve2_bank */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* eve2_bank */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/* eve1_7xx_pwrdm:  */
static struct powerdomain eve1_7xx_pwrdm = {
    .name		  = "eve1_pwrdm",
    .prcm_offs	  = DRA7XX_PRM_EVE1_INST,
    .prcm_partition	  = DRA7XX_PRM_PARTITION,
    .pwrsts		  = PWRSTS_OFF_ON,
    .banks		  = 1,
    .pwrsts_mem_ret	= {
        [0] = PWRSTS_OFF_RET,	/* eve1_bank */
    },
    .pwrsts_mem_on	= {
        [0] = PWRSTS_OFF_RET,	/* eve1_bank */
    },
    .flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
};

/*
 * The following power domains are not under SW control
 *
 * mpuaon
 * mmaon
 */

/* As powerdomains are added or removed above, this list must also be changed */
static struct powerdomain *powerdomains_dra7xx[] __initdata = {
    &iva_7xx_pwrdm,
    &rtc_7xx_pwrdm,
    &custefuse_7xx_pwrdm,
    &ipu_7xx_pwrdm,
    &dss_7xx_pwrdm,
    &l4per_7xx_pwrdm,
    &gpu_7xx_pwrdm,
    &wkupaon_7xx_pwrdm,
    &core_7xx_pwrdm,
    &coreaon_7xx_pwrdm,
    &cpu0_7xx_pwrdm,
    &cpu1_7xx_pwrdm,
    &vpe_7xx_pwrdm,
    &mpu_7xx_pwrdm,
    &l3init_7xx_pwrdm,
    &eve3_7xx_pwrdm,
    &emu_7xx_pwrdm,
    &dsp2_7xx_pwrdm,
    &dsp1_7xx_pwrdm,
    &cam_7xx_pwrdm,
    &eve4_7xx_pwrdm,
    &eve2_7xx_pwrdm,
    &eve1_7xx_pwrdm,
    NULL
};

void __init dra7xx_powerdomains_init(void)
{
    pwrdm_register_platform_funcs(&omap4_pwrdm_operations);
    pwrdm_register_pwrdms(powerdomains_dra7xx);
    pwrdm_complete_init();
}
