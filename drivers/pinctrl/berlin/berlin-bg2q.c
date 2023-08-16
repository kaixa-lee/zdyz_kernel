/*
 * Marvell Berlin BG2Q pinctrl driver
 *
 * Copyright (C) 2014 Marvell Technology Group Ltd.
 *
 * Antoine TÃ©nart <antoine.tenart@free-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>

#include "berlin.h"

static const struct berlin_desc_group berlin2q_soc_pinctrl_groups[] = {
    /* G */
    BERLIN_PINCTRL_GROUP("G0", 0x18, 0x3, 0x00,
                         BERLIN_PINCTRL_FUNCTION(0x0, "nand"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "mmc"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("G1", 0x18, 0x3, 0x03,
                         BERLIN_PINCTRL_FUNCTION(0x0, "nand"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("G2", 0x18, 0x3, 0x06,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "arc"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "lvds")),
    BERLIN_PINCTRL_GROUP("G3", 0x18, 0x3, 0x09,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "i2s2"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "lvds")),
    BERLIN_PINCTRL_GROUP("G4", 0x18, 0x3, 0x0c,
                         BERLIN_PINCTRL_FUNCTION(0x0, "pll"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "sd0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "rgmii"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "sata_dbg"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "usb0_dbg"),
                         BERLIN_PINCTRL_FUNCTION(0x7, "usb1_dbg")),
    BERLIN_PINCTRL_GROUP("G5", 0x18, 0x3, 0x0f,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "sd0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "rgmii"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "sata_dbg"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "usb0_dbg"),
                         BERLIN_PINCTRL_FUNCTION(0x7, "usb1_dbg")),
    BERLIN_PINCTRL_GROUP("G6", 0x18, 0x3, 0x12,
                         BERLIN_PINCTRL_FUNCTION(0x0, "jtag"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "twsi0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("G7", 0x18, 0x3, 0x15,
                         BERLIN_PINCTRL_FUNCTION(0x0, "jtag"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "twsi1"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "eddc")),
    BERLIN_PINCTRL_GROUP("G8", 0x18, 0x3, 0x18,
                         BERLIN_PINCTRL_FUNCTION(0x0, "spi1"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "gpio")),
    BERLIN_PINCTRL_GROUP("G9", 0x18, 0x3, 0x1b,
                         BERLIN_PINCTRL_FUNCTION(0x0, "spi1"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "sata")),
    BERLIN_PINCTRL_GROUP("G10", 0x1c, 0x3, 0x00,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "spi1"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "i2s0"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "pwm"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "sata")),
    BERLIN_PINCTRL_GROUP("G11", 0x1c, 0x3, 0x03,
                         BERLIN_PINCTRL_FUNCTION(0x0, "jtag"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "spi1"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "i2s1"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "pwm"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "sata")),
    BERLIN_PINCTRL_GROUP("G12", 0x1c, 0x3, 0x06,
                         BERLIN_PINCTRL_FUNCTION(0x0, "agc"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "gpio")),
    BERLIN_PINCTRL_GROUP("G13", 0x1c, 0x3, 0x09,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "sts1"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "rgmii"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "usb0_dbg"),
                         BERLIN_PINCTRL_FUNCTION(0x7, "usb1_dbg")),
    BERLIN_PINCTRL_GROUP("G14", 0x1c, 0x3, 0x0c,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "sts0"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "sts1"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "usb0_dbg"),
                         BERLIN_PINCTRL_FUNCTION(0x7, "usb1_dbg")),
    BERLIN_PINCTRL_GROUP("G15", 0x1c, 0x3, 0x0f,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "sts0"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "sts1"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "vdac"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "usb0_dbg"),
                         BERLIN_PINCTRL_FUNCTION(0x7, "usb1_dbg")),
    BERLIN_PINCTRL_GROUP("G16", 0x1c, 0x3, 0x12,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "sts0"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "sts1"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "osco"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "usb0_dbg"),
                         BERLIN_PINCTRL_FUNCTION(0x7, "usb1_dbg")),
    BERLIN_PINCTRL_GROUP("G17", 0x1c, 0x3, 0x15,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "rgmii"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "spdif"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "sts1"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "usb0_dbg"),
                         BERLIN_PINCTRL_FUNCTION(0x7, "usb1_dbg")),
    BERLIN_PINCTRL_GROUP("G18", 0x1c, 0x3, 0x18,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "rgmii"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "i2s2"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "sts1")),
    BERLIN_PINCTRL_GROUP("G19", 0x1c, 0x3, 0x1b,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "rgmii"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "i2s3"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "sts1"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "osco")),
    BERLIN_PINCTRL_GROUP("G20", 0x20, 0x3, 0x00,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "demod"),
                         /*
                          * Mode 0x4 mux usb2_dbg *and* usb3_dbg:
                          * add two functions so it can be used with other groups
                          * within the same subnode in the device tree
                          */
                         BERLIN_PINCTRL_FUNCTION(0x4, "usb2_dbg"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "usb3_dbg")),
    BERLIN_PINCTRL_GROUP("G21", 0x20, 0x3, 0x03,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "sts2"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "demod")),
    BERLIN_PINCTRL_GROUP("G22", 0x20, 0x3, 0x06,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("G23", 0x20, 0x3, 0x09,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "avif"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "usb2_dbg")),
    BERLIN_PINCTRL_GROUP("G24", 0x20, 0x3, 0x0c,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "demod"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "usb2_dbg")),
    BERLIN_PINCTRL_GROUP("G25", 0x20, 0x3, 0x0f,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "vga"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "avif"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "usb2_dbg")),
    BERLIN_PINCTRL_GROUP("G26", 0x20, 0x3, 0x12,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "lvds"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("G27", 0x20, 0x3, 0x15,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "agc"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("G28", 0x20, 0x3, 0x18,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "avif"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "usb2_dbg")),
    BERLIN_PINCTRL_GROUP("G29", 0x20, 0x3, 0x1b,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "scrd0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("G30", 0x24, 0x3, 0x00,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "scrd1"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("G31", 0x24, 0x3, 0x03,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "sd1"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("G32", 0x24, 0x3, 0x06,
                         BERLIN_PINCTRL_FUNCTION(0x0, "cam"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "sd1"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    /* GAV */
    BERLIN_PINCTRL_GROUP("GAV0", 0x24, 0x3, 0x09,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dvio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "lvds")),
    BERLIN_PINCTRL_GROUP("GAV1", 0x24, 0x3, 0x0c,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dvio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "vga")),
    BERLIN_PINCTRL_GROUP("GAV2", 0x24, 0x3, 0x0f,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dvio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "i2s3"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "pdm"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "adac")),
    BERLIN_PINCTRL_GROUP("GAV3", 0x24, 0x3, 0x12,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dvio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "i2s3"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "adac")),
    BERLIN_PINCTRL_GROUP("GAV4", 0x24, 0x3, 0x15,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dvio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "i2s1"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "adac")),
    BERLIN_PINCTRL_GROUP("GAV5", 0x24, 0x3, 0x18,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dvio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "spdif")),
    BERLIN_PINCTRL_GROUP("GAV6", 0x24, 0x3, 0x1b,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dvio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "i2s2")),
    BERLIN_PINCTRL_GROUP("GAV7", 0x28, 0x3, 0x00,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dvio"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "i2s3")),
    BERLIN_PINCTRL_GROUP("GAV8", 0x28, 0x3, 0x03,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dv0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "pwm")),
    BERLIN_PINCTRL_GROUP("GAV9", 0x28, 0x3, 0x06,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dv0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "pwm")),
    BERLIN_PINCTRL_GROUP("GAV10", 0x28, 0x3, 0x09,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dv0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "agc")),
    BERLIN_PINCTRL_GROUP("GAV11", 0x28, 0x3, 0x0c,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "dv0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "fp"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "i2s0"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "pwm"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "vclki")),
    BERLIN_PINCTRL_GROUP("GAV12", 0x28, 0x3, 0x0f,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "i2s2"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "i2s1")),
    BERLIN_PINCTRL_GROUP("GAV13", 0x28, 0x3, 0x12,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "i2s2")),
    BERLIN_PINCTRL_GROUP("GAV14", 0x28, 0x3, 0x15,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "i2s2"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "i2s1")),
    BERLIN_PINCTRL_GROUP("GAV15", 0x28, 0x3, 0x18,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "i2s1"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "dac_dbg")),
    BERLIN_PINCTRL_GROUP("GAV16", 0x28, 0x3, 0x1b,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "i2s0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "i2s1"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "i2s3"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "pdm"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "dac_dbg")),
    BERLIN_PINCTRL_GROUP("GAV17", 0x2c, 0x3, 0x00,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "i2s0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "i2s1"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "pwm"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "i2s3"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "pdm"),
                         BERLIN_PINCTRL_FUNCTION(0x6, "dac_dbg")),
    BERLIN_PINCTRL_GROUP("GAV18", 0x2c, 0x3, 0x03,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "spdif"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "arc")),
    BERLIN_PINCTRL_GROUP("GAV19", 0x2c, 0x3, 0x06,
                         BERLIN_PINCTRL_FUNCTION(0x0, "avio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "spdif"),
                         BERLIN_PINCTRL_FUNCTION(0x4, "i2s3"),
                         BERLIN_PINCTRL_FUNCTION(0x5, "pdm")),
};

static const struct berlin_desc_group berlin2q_sysmgr_pinctrl_groups[] = {
    /* GSM */
    BERLIN_PINCTRL_GROUP("GSM0", 0x40, 0x2, 0x00,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "spi2"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "eth1")),
    BERLIN_PINCTRL_GROUP("GSM1", 0x40, 0x2, 0x02,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "spi2"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "eth1")),
    BERLIN_PINCTRL_GROUP("GSM2", 0x40, 0x2, 0x04,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "spi2"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "eddc")),
    BERLIN_PINCTRL_GROUP("GSM3", 0x40, 0x2, 0x06,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "spi2"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "eddc")),
    BERLIN_PINCTRL_GROUP("GSM4", 0x40, 0x1, 0x08,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "hdmi")),
    BERLIN_PINCTRL_GROUP("GSM5", 0x40, 0x1, 0x09,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "hdmi")),
    BERLIN_PINCTRL_GROUP("GSM6", 0x40, 0x1, 0x0a,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "hdmi")),
    BERLIN_PINCTRL_GROUP("GSM7", 0x40, 0x1, 0x0b,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "hdmi")),
    BERLIN_PINCTRL_GROUP("GSM8", 0x40, 0x1, 0x0c,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "hdmi")),
    BERLIN_PINCTRL_GROUP("GSM9", 0x40, 0x1, 0x0d,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "hdmi")),
    BERLIN_PINCTRL_GROUP("GSM10", 0x40, 0x1, 0x0e,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "led")),
    BERLIN_PINCTRL_GROUP("GSM11", 0x40, 0x1, 0x0f,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "led")),
    BERLIN_PINCTRL_GROUP("GSM12", 0x40, 0x2, 0x10,
                         BERLIN_PINCTRL_FUNCTION(0x0, "uart0"), /* RX/TX */
                         BERLIN_PINCTRL_FUNCTION(0x1, "irda0"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("GSM13", 0x40, 0x2, 0x12,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "uart0"), /* CTS/RTS */
                         BERLIN_PINCTRL_FUNCTION(0x2, "uart1"), /* RX/TX */
                         BERLIN_PINCTRL_FUNCTION(0x3, "twsi2")),
    BERLIN_PINCTRL_GROUP("GSM14", 0x40, 0x2, 0x14,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "uart1"), /* RX/TX */
                         BERLIN_PINCTRL_FUNCTION(0x2, "irda1"),
                         BERLIN_PINCTRL_FUNCTION(0x3, "twsi3")),
    BERLIN_PINCTRL_GROUP("GSM15", 0x40, 0x2, 0x16,
                         BERLIN_PINCTRL_FUNCTION(0x0, "pwr"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "led"),
                         BERLIN_PINCTRL_FUNCTION(0x2, "gpio")),
    BERLIN_PINCTRL_GROUP("GSM16", 0x40, 0x1, 0x18,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "eddc")),
    BERLIN_PINCTRL_GROUP("GSM17", 0x40, 0x1, 0x19,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "eddc")),
    BERLIN_PINCTRL_GROUP("GSM18", 0x40, 0x1, 0x1a,
                         BERLIN_PINCTRL_FUNCTION(0x0, "gpio"),
                         BERLIN_PINCTRL_FUNCTION(0x1, "eddc")),
};

static const struct berlin_pinctrl_desc berlin2q_soc_pinctrl_data = {
    .groups = berlin2q_soc_pinctrl_groups,
    .ngroups = ARRAY_SIZE(berlin2q_soc_pinctrl_groups),
};

static const struct berlin_pinctrl_desc berlin2q_sysmgr_pinctrl_data = {
    .groups = berlin2q_sysmgr_pinctrl_groups,
    .ngroups = ARRAY_SIZE(berlin2q_sysmgr_pinctrl_groups),
};

static const struct of_device_id berlin2q_pinctrl_match[] = {
    {
        .compatible = "marvell,berlin2q-chip-ctrl",
        .data = &berlin2q_soc_pinctrl_data,
    },
    {
        .compatible = "marvell,berlin2q-system-ctrl",
        .data = &berlin2q_sysmgr_pinctrl_data,
    },
    {}
};
MODULE_DEVICE_TABLE(of, berlin2q_pinctrl_match);

static int berlin2q_pinctrl_probe(struct platform_device *pdev)
{
    const struct of_device_id *match =
        of_match_device(berlin2q_pinctrl_match, &pdev->dev);
    struct regmap_config *rmconfig;
    struct regmap *regmap;
    struct resource *res;
    void __iomem *base;

    rmconfig = devm_kzalloc(&pdev->dev, sizeof(*rmconfig), GFP_KERNEL);
    if (!rmconfig) {
        return -ENOMEM;
    }

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    base = devm_ioremap_resource(&pdev->dev, res);
    if (IS_ERR(base)) {
        return PTR_ERR(base);
    }

    rmconfig->reg_bits = 32,
              rmconfig->val_bits = 32,
                        rmconfig->reg_stride = 4,
                                  rmconfig->max_register = resource_size(res);

    regmap = devm_regmap_init_mmio(&pdev->dev, base, rmconfig);
    if (IS_ERR(regmap)) {
        return PTR_ERR(regmap);
    }

    return berlin_pinctrl_probe(pdev, match->data);
}

static struct platform_driver berlin2q_pinctrl_driver = {
    .probe	= berlin2q_pinctrl_probe,
    .driver	= {
        .name = "berlin-bg2q-pinctrl",
        .of_match_table = berlin2q_pinctrl_match,
    },
};
module_platform_driver(berlin2q_pinctrl_driver);

MODULE_AUTHOR("Antoine TÃ©nart <antoine.tenart@free-electrons.com>");
MODULE_DESCRIPTION("Marvell Berlin BG2Q pinctrl driver");
MODULE_LICENSE("GPL");
