/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#include "priv.h"

#include <subdev/bios.h>
#include <subdev/bus.h>
#include <subdev/gpio.h>
#include <subdev/i2c.h>
#include <subdev/clk.h>
#include <subdev/therm.h>
#include <subdev/devinit.h>
#include <subdev/mc.h>
#include <subdev/timer.h>
#include <subdev/fb.h>
#include <subdev/instmem.h>
#include <subdev/mmu.h>

#include <engine/dmaobj.h>
#include <engine/fifo.h>
#include <engine/sw.h>
#include <engine/gr.h>
#include <engine/disp.h>

int
nv20_identify(struct nvkm_device *device)
{
    switch (device->chipset) {
    case 0x20:
        device->cname = "NV20";
        device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nvkm_bios_oclass;
        device->oclass[NVDEV_SUBDEV_GPIO   ] =  nv10_gpio_oclass;
        device->oclass[NVDEV_SUBDEV_I2C    ] =  nv04_i2c_oclass;
        device->oclass[NVDEV_SUBDEV_CLK    ] = &nv04_clk_oclass;
        device->oclass[NVDEV_SUBDEV_DEVINIT] =  nv20_devinit_oclass;
        device->oclass[NVDEV_SUBDEV_MC     ] =  nv04_mc_oclass;
        device->oclass[NVDEV_SUBDEV_BUS    ] =  nv04_bus_oclass;
        device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
        device->oclass[NVDEV_SUBDEV_FB     ] =  nv20_fb_oclass;
        device->oclass[NVDEV_SUBDEV_INSTMEM] =  nv04_instmem_oclass;
        device->oclass[NVDEV_SUBDEV_MMU    ] = &nv04_mmu_oclass;
        device->oclass[NVDEV_ENGINE_DMAOBJ ] =  nv04_dmaeng_oclass;
        device->oclass[NVDEV_ENGINE_FIFO   ] =  nv17_fifo_oclass;
        device->oclass[NVDEV_ENGINE_SW     ] =  nv10_sw_oclass;
        device->oclass[NVDEV_ENGINE_GR     ] = &nv20_gr_oclass;
        device->oclass[NVDEV_ENGINE_DISP   ] =  nv04_disp_oclass;
        break;
    case 0x25:
        device->cname = "NV25";
        device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nvkm_bios_oclass;
        device->oclass[NVDEV_SUBDEV_GPIO   ] =  nv10_gpio_oclass;
        device->oclass[NVDEV_SUBDEV_I2C    ] =  nv04_i2c_oclass;
        device->oclass[NVDEV_SUBDEV_CLK    ] = &nv04_clk_oclass;
        device->oclass[NVDEV_SUBDEV_DEVINIT] =  nv20_devinit_oclass;
        device->oclass[NVDEV_SUBDEV_MC     ] =  nv04_mc_oclass;
        device->oclass[NVDEV_SUBDEV_BUS    ] =  nv04_bus_oclass;
        device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
        device->oclass[NVDEV_SUBDEV_FB     ] =  nv25_fb_oclass;
        device->oclass[NVDEV_SUBDEV_INSTMEM] =  nv04_instmem_oclass;
        device->oclass[NVDEV_SUBDEV_MMU    ] = &nv04_mmu_oclass;
        device->oclass[NVDEV_ENGINE_DMAOBJ ] =  nv04_dmaeng_oclass;
        device->oclass[NVDEV_ENGINE_FIFO   ] =  nv17_fifo_oclass;
        device->oclass[NVDEV_ENGINE_SW     ] =  nv10_sw_oclass;
        device->oclass[NVDEV_ENGINE_GR     ] = &nv25_gr_oclass;
        device->oclass[NVDEV_ENGINE_DISP   ] =  nv04_disp_oclass;
        break;
    case 0x28:
        device->cname = "NV28";
        device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nvkm_bios_oclass;
        device->oclass[NVDEV_SUBDEV_GPIO   ] =  nv10_gpio_oclass;
        device->oclass[NVDEV_SUBDEV_I2C    ] =  nv04_i2c_oclass;
        device->oclass[NVDEV_SUBDEV_CLK    ] = &nv04_clk_oclass;
        device->oclass[NVDEV_SUBDEV_DEVINIT] =  nv20_devinit_oclass;
        device->oclass[NVDEV_SUBDEV_MC     ] =  nv04_mc_oclass;
        device->oclass[NVDEV_SUBDEV_BUS    ] =  nv04_bus_oclass;
        device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
        device->oclass[NVDEV_SUBDEV_FB     ] =  nv25_fb_oclass;
        device->oclass[NVDEV_SUBDEV_INSTMEM] =  nv04_instmem_oclass;
        device->oclass[NVDEV_SUBDEV_MMU    ] = &nv04_mmu_oclass;
        device->oclass[NVDEV_ENGINE_DMAOBJ ] =  nv04_dmaeng_oclass;
        device->oclass[NVDEV_ENGINE_FIFO   ] =  nv17_fifo_oclass;
        device->oclass[NVDEV_ENGINE_SW     ] =  nv10_sw_oclass;
        device->oclass[NVDEV_ENGINE_GR     ] = &nv25_gr_oclass;
        device->oclass[NVDEV_ENGINE_DISP   ] =  nv04_disp_oclass;
        break;
    case 0x2a:
        device->cname = "NV2A";
        device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nvkm_bios_oclass;
        device->oclass[NVDEV_SUBDEV_GPIO   ] =  nv10_gpio_oclass;
        device->oclass[NVDEV_SUBDEV_I2C    ] =  nv04_i2c_oclass;
        device->oclass[NVDEV_SUBDEV_CLK    ] = &nv04_clk_oclass;
        device->oclass[NVDEV_SUBDEV_DEVINIT] =  nv20_devinit_oclass;
        device->oclass[NVDEV_SUBDEV_MC     ] =  nv04_mc_oclass;
        device->oclass[NVDEV_SUBDEV_BUS    ] =  nv04_bus_oclass;
        device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
        device->oclass[NVDEV_SUBDEV_FB     ] =  nv25_fb_oclass;
        device->oclass[NVDEV_SUBDEV_INSTMEM] =  nv04_instmem_oclass;
        device->oclass[NVDEV_SUBDEV_MMU    ] = &nv04_mmu_oclass;
        device->oclass[NVDEV_ENGINE_DMAOBJ ] =  nv04_dmaeng_oclass;
        device->oclass[NVDEV_ENGINE_FIFO   ] =  nv17_fifo_oclass;
        device->oclass[NVDEV_ENGINE_SW     ] =  nv10_sw_oclass;
        device->oclass[NVDEV_ENGINE_GR     ] = &nv2a_gr_oclass;
        device->oclass[NVDEV_ENGINE_DISP   ] =  nv04_disp_oclass;
        break;
    default:
        nv_fatal(device, "unknown Kelvin chipset\n");
        return -EINVAL;
    }

    return 0;
}
