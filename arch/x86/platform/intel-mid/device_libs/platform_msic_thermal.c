/*
 * platform_msic_thermal.c: msic_thermal platform data initilization file
 *
 * (C) Copyright 2013 Intel Corporation
 * Author: Sathyanarayanan Kuppuswamy <sathyanarayanan.kuppuswamy@intel.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 */

#include <linux/input.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <linux/mfd/intel_msic.h>
#include <asm/intel-mid.h>

#include "platform_msic.h"
#include "platform_ipc.h"

static void __init *msic_thermal_platform_data(void *info)
{
    return msic_generic_platform_data(info, INTEL_MSIC_BLOCK_THERMAL);
}

static const struct devs_id msic_thermal_dev_id __initconst = {
    .name = "msic_thermal",
    .type = SFI_DEV_TYPE_IPC,
    .delay = 1,
    .get_platform_data = &msic_thermal_platform_data,
    .device_handler = &ipc_device_handler,
};

sfi_device(msic_thermal_dev_id);
