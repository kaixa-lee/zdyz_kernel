/*
 * Copyright (c) 2006 Luc Verhaegen (quirks list)
 * Copyright (c) 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@intel.com>
 * Copyright 2010 Red Hat, Inc.
 *
 * DDC probing routines (drm_ddc_read & drm_do_probe_ddc_edid) originally from
 * FB layer.
 *   Copyright (C) 2006 Dennis Munsie <dmunsie@cecropia.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/hdmi.h>
#include <linux/i2c.h>
#include <linux/module.h>
#include <drm/drmP.h>
#include <drm/drm_edid.h>
#include <drm/drm_displayid.h>

#define version_greater(edid, maj, min) \
	(((edid)->version > (maj)) || \
	 ((edid)->version == (maj) && (edid)->revision > (min)))

#define EDID_EST_TIMINGS 16
#define EDID_STD_TIMINGS 8
#define EDID_DETAILED_TIMINGS 4

/*
 * EDID blocks out in the wild have a variety of bugs, try to collect
 * them here (note that userspace may work around broken monitors first,
 * but fixes should make their way here so that the kernel "just works"
 * on as many displays as possible).
 */

/* First detailed mode wrong, use largest 60Hz mode */
#define EDID_QUIRK_PREFER_LARGE_60		(1 << 0)
/* Reported 135MHz pixel clock is too high, needs adjustment */
#define EDID_QUIRK_135_CLOCK_TOO_HIGH		(1 << 1)
/* Prefer the largest mode at 75 Hz */
#define EDID_QUIRK_PREFER_LARGE_75		(1 << 2)
/* Detail timing is in cm not mm */
#define EDID_QUIRK_DETAILED_IN_CM		(1 << 3)
/* Detailed timing descriptors have bogus size values, so just take the
 * maximum size and use that.
 */
#define EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE	(1 << 4)
/* Monitor forgot to set the first detailed is preferred bit. */
#define EDID_QUIRK_FIRST_DETAILED_PREFERRED	(1 << 5)
/* use +hsync +vsync for detailed mode */
#define EDID_QUIRK_DETAILED_SYNC_PP		(1 << 6)
/* Force reduced-blanking timings for detailed modes */
#define EDID_QUIRK_FORCE_REDUCED_BLANKING	(1 << 7)
/* Force 8bpc */
#define EDID_QUIRK_FORCE_8BPC			(1 << 8)
/* Force 12bpc */
#define EDID_QUIRK_FORCE_12BPC			(1 << 9)

struct detailed_mode_closure {
    struct drm_connector *connector;
    struct edid *edid;
    bool preferred;
    u32 quirks;
    int modes;
};

#define LEVEL_DMT	0
#define LEVEL_GTF	1
#define LEVEL_GTF2	2
#define LEVEL_CVT	3

static struct edid_quirk {
    char vendor[4];
    int product_id;
    u32 quirks;
} edid_quirk_list[] = {
    /* Acer AL1706 */
    { "ACR", 44358, EDID_QUIRK_PREFER_LARGE_60 },
    /* Acer F51 */
    { "API", 0x7602, EDID_QUIRK_PREFER_LARGE_60 },
    /* Unknown Acer */
    { "ACR", 2423, EDID_QUIRK_FIRST_DETAILED_PREFERRED },

    /* Belinea 10 15 55 */
    { "MAX", 1516, EDID_QUIRK_PREFER_LARGE_60 },
    { "MAX", 0x77e, EDID_QUIRK_PREFER_LARGE_60 },

    /* Envision Peripherals, Inc. EN-7100e */
    { "EPI", 59264, EDID_QUIRK_135_CLOCK_TOO_HIGH },
    /* Envision EN2028 */
    { "EPI", 8232, EDID_QUIRK_PREFER_LARGE_60 },

    /* Funai Electronics PM36B */
    {
        "FCM", 13600, EDID_QUIRK_PREFER_LARGE_75 |
        EDID_QUIRK_DETAILED_IN_CM
    },

    /* LG Philips LCD LP154W01-A5 */
    { "LPL", 0, EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE },
    { "LPL", 0x2a00, EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE },

    /* Philips 107p5 CRT */
    { "PHL", 57364, EDID_QUIRK_FIRST_DETAILED_PREFERRED },

    /* Proview AY765C */
    { "PTS", 765, EDID_QUIRK_FIRST_DETAILED_PREFERRED },

    /* Samsung SyncMaster 205BW.  Note: irony */
    { "SAM", 541, EDID_QUIRK_DETAILED_SYNC_PP },
    /* Samsung SyncMaster 22[5-6]BW */
    { "SAM", 596, EDID_QUIRK_PREFER_LARGE_60 },
    { "SAM", 638, EDID_QUIRK_PREFER_LARGE_60 },

    /* Sony PVM-2541A does up to 12 bpc, but only reports max 8 bpc */
    { "SNY", 0x2541, EDID_QUIRK_FORCE_12BPC },

    /* ViewSonic VA2026w */
    { "VSC", 5020, EDID_QUIRK_FORCE_REDUCED_BLANKING },

    /* Medion MD 30217 PG */
    { "MED", 0x7b8, EDID_QUIRK_PREFER_LARGE_75 },

    /* Panel in Samsung NP700G7A-S01PL notebook reports 6bpc */
    { "SEC", 0xd033, EDID_QUIRK_FORCE_8BPC },
};

/*
 * Autogenerated from the DMT spec.
 * This table is copied from xfree86/modes/xf86EdidModes.c.
 */
static const struct drm_display_mode drm_dmt_modes[] = {
    /* 640x350@85Hz */
    {
        DRM_MODE("640x350", DRM_MODE_TYPE_DRIVER, 31500, 640, 672,
                 736, 832, 0, 350, 382, 385, 445, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 640x400@85Hz */
    {
        DRM_MODE("640x400", DRM_MODE_TYPE_DRIVER, 31500, 640, 672,
                 736, 832, 0, 400, 401, 404, 445, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 720x400@85Hz */
    {
        DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 35500, 720, 756,
                 828, 936, 0, 400, 401, 404, 446, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 640x480@60Hz */
    {
        DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25175, 640, 656,
                 752, 800, 0, 480, 489, 492, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 640x480@72Hz */
    {
        DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 664,
                 704, 832, 0, 480, 489, 492, 520, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 640x480@75Hz */
    {
        DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 656,
                 720, 840, 0, 480, 481, 484, 500, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 640x480@85Hz */
    {
        DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 36000, 640, 696,
                 752, 832, 0, 480, 481, 484, 509, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 800x600@56Hz */
    {
        DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 36000, 800, 824,
                 896, 1024, 0, 600, 601, 603, 625, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 800x600@60Hz */
    {
        DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 40000, 800, 840,
                 968, 1056, 0, 600, 601, 605, 628, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 800x600@72Hz */
    {
        DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 50000, 800, 856,
                 976, 1040, 0, 600, 637, 643, 666, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 800x600@75Hz */
    {
        DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 49500, 800, 816,
                 896, 1056, 0, 600, 601, 604, 625, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 800x600@85Hz */
    {
        DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 56250, 800, 832,
                 896, 1048, 0, 600, 601, 604, 631, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 800x600@120Hz RB */
    {
        DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 73250, 800, 848,
                 880, 960, 0, 600, 603, 607, 636, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 848x480@60Hz */
    {
        DRM_MODE("848x480", DRM_MODE_TYPE_DRIVER, 33750, 848, 864,
                 976, 1088, 0, 480, 486, 494, 517, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1024x768@43Hz, interlace */
    {
        DRM_MODE("1024x768i", DRM_MODE_TYPE_DRIVER, 44900, 1024, 1032,
                 1208, 1264, 0, 768, 768, 772, 817, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
                 DRM_MODE_FLAG_INTERLACE)
    },
    /* 1024x768@60Hz */
    {
        DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 65000, 1024, 1048,
                 1184, 1344, 0, 768, 771, 777, 806, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1024x768@70Hz */
    {
        DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 75000, 1024, 1048,
                 1184, 1328, 0, 768, 771, 777, 806, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1024x768@75Hz */
    {
        DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 78750, 1024, 1040,
                 1136, 1312, 0, 768, 769, 772, 800, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1024x768@85Hz */
    {
        DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 94500, 1024, 1072,
                 1168, 1376, 0, 768, 769, 772, 808, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1024x768@120Hz RB */
    {
        DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 115500, 1024, 1072,
                 1104, 1184, 0, 768, 771, 775, 813, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1152x864@75Hz */
    {
        DRM_MODE("1152x864", DRM_MODE_TYPE_DRIVER, 108000, 1152, 1216,
                 1344, 1600, 0, 864, 865, 868, 900, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1280x768@60Hz RB */
    {
        DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 68250, 1280, 1328,
                 1360, 1440, 0, 768, 771, 778, 790, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1280x768@60Hz */
    {
        DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 79500, 1280, 1344,
                 1472, 1664, 0, 768, 771, 778, 798, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1280x768@75Hz */
    {
        DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 102250, 1280, 1360,
                 1488, 1696, 0, 768, 771, 778, 805, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1280x768@85Hz */
    {
        DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 117500, 1280, 1360,
                 1496, 1712, 0, 768, 771, 778, 809, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1280x768@120Hz RB */
    {
        DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 140250, 1280, 1328,
                 1360, 1440, 0, 768, 771, 778, 813, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1280x800@60Hz RB */
    {
        DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 71000, 1280, 1328,
                 1360, 1440, 0, 800, 803, 809, 823, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1280x800@60Hz */
    {
        DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 83500, 1280, 1352,
                 1480, 1680, 0, 800, 803, 809, 831, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1280x800@75Hz */
    {
        DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 106500, 1280, 1360,
                 1488, 1696, 0, 800, 803, 809, 838, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1280x800@85Hz */
    {
        DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 122500, 1280, 1360,
                 1496, 1712, 0, 800, 803, 809, 843, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1280x800@120Hz RB */
    {
        DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 146250, 1280, 1328,
                 1360, 1440, 0, 800, 803, 809, 847, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1280x960@60Hz */
    {
        DRM_MODE("1280x960", DRM_MODE_TYPE_DRIVER, 108000, 1280, 1376,
                 1488, 1800, 0, 960, 961, 964, 1000, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1280x960@85Hz */
    {
        DRM_MODE("1280x960", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1344,
                 1504, 1728, 0, 960, 961, 964, 1011, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1280x960@120Hz RB */
    {
        DRM_MODE("1280x960", DRM_MODE_TYPE_DRIVER, 175500, 1280, 1328,
                 1360, 1440, 0, 960, 963, 967, 1017, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1280x1024@60Hz */
    {
        DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 108000, 1280, 1328,
                 1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1280x1024@75Hz */
    {
        DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 135000, 1280, 1296,
                 1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1280x1024@85Hz */
    {
        DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 157500, 1280, 1344,
                 1504, 1728, 0, 1024, 1025, 1028, 1072, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1280x1024@120Hz RB */
    {
        DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 187250, 1280, 1328,
                 1360, 1440, 0, 1024, 1027, 1034, 1084, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1360x768@60Hz */
    {
        DRM_MODE("1360x768", DRM_MODE_TYPE_DRIVER, 85500, 1360, 1424,
                 1536, 1792, 0, 768, 771, 777, 795, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1360x768@120Hz RB */
    {
        DRM_MODE("1360x768", DRM_MODE_TYPE_DRIVER, 148250, 1360, 1408,
                 1440, 1520, 0, 768, 771, 776, 813, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1400x1050@60Hz RB */
    {
        DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 101000, 1400, 1448,
                 1480, 1560, 0, 1050, 1053, 1057, 1080, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1400x1050@60Hz */
    {
        DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 121750, 1400, 1488,
                 1632, 1864, 0, 1050, 1053, 1057, 1089, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1400x1050@75Hz */
    {
        DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 156000, 1400, 1504,
                 1648, 1896, 0, 1050, 1053, 1057, 1099, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1400x1050@85Hz */
    {
        DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 179500, 1400, 1504,
                 1656, 1912, 0, 1050, 1053, 1057, 1105, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1400x1050@120Hz RB */
    {
        DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 208000, 1400, 1448,
                 1480, 1560, 0, 1050, 1053, 1057, 1112, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1440x900@60Hz RB */
    {
        DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 88750, 1440, 1488,
                 1520, 1600, 0, 900, 903, 909, 926, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1440x900@60Hz */
    {
        DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 106500, 1440, 1520,
                 1672, 1904, 0, 900, 903, 909, 934, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1440x900@75Hz */
    {
        DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 136750, 1440, 1536,
                 1688, 1936, 0, 900, 903, 909, 942, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1440x900@85Hz */
    {
        DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 157000, 1440, 1544,
                 1696, 1952, 0, 900, 903, 909, 948, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1440x900@120Hz RB */
    {
        DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 182750, 1440, 1488,
                 1520, 1600, 0, 900, 903, 909, 953, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1600x1200@60Hz */
    {
        DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 162000, 1600, 1664,
                 1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1600x1200@65Hz */
    {
        DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 175500, 1600, 1664,
                 1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1600x1200@70Hz */
    {
        DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 189000, 1600, 1664,
                 1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1600x1200@75Hz */
    {
        DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 202500, 1600, 1664,
                 1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1600x1200@85Hz */
    {
        DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 229500, 1600, 1664,
                 1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1600x1200@120Hz RB */
    {
        DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 268250, 1600, 1648,
                 1680, 1760, 0, 1200, 1203, 1207, 1271, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1680x1050@60Hz RB */
    {
        DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 119000, 1680, 1728,
                 1760, 1840, 0, 1050, 1053, 1059, 1080, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1680x1050@60Hz */
    {
        DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 146250, 1680, 1784,
                 1960, 2240, 0, 1050, 1053, 1059, 1089, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1680x1050@75Hz */
    {
        DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 187000, 1680, 1800,
                 1976, 2272, 0, 1050, 1053, 1059, 1099, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1680x1050@85Hz */
    {
        DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 214750, 1680, 1808,
                 1984, 2288, 0, 1050, 1053, 1059, 1105, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1680x1050@120Hz RB */
    {
        DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 245500, 1680, 1728,
                 1760, 1840, 0, 1050, 1053, 1059, 1112, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1792x1344@60Hz */
    {
        DRM_MODE("1792x1344", DRM_MODE_TYPE_DRIVER, 204750, 1792, 1920,
                 2120, 2448, 0, 1344, 1345, 1348, 1394, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1792x1344@75Hz */
    {
        DRM_MODE("1792x1344", DRM_MODE_TYPE_DRIVER, 261000, 1792, 1888,
                 2104, 2456, 0, 1344, 1345, 1348, 1417, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1792x1344@120Hz RB */
    {
        DRM_MODE("1792x1344", DRM_MODE_TYPE_DRIVER, 333250, 1792, 1840,
                 1872, 1952, 0, 1344, 1347, 1351, 1423, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1856x1392@60Hz */
    {
        DRM_MODE("1856x1392", DRM_MODE_TYPE_DRIVER, 218250, 1856, 1952,
                 2176, 2528, 0, 1392, 1393, 1396, 1439, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1856x1392@75Hz */
    {
        DRM_MODE("1856x1392", DRM_MODE_TYPE_DRIVER, 288000, 1856, 1984,
                 2208, 2560, 0, 1392, 1395, 1399, 1500, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1856x1392@120Hz RB */
    {
        DRM_MODE("1856x1392", DRM_MODE_TYPE_DRIVER, 356500, 1856, 1904,
                 1936, 2016, 0, 1392, 1395, 1399, 1474, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1920x1200@60Hz RB */
    {
        DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 154000, 1920, 1968,
                 2000, 2080, 0, 1200, 1203, 1209, 1235, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1920x1200@60Hz */
    {
        DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 193250, 1920, 2056,
                 2256, 2592, 0, 1200, 1203, 1209, 1245, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1920x1200@75Hz */
    {
        DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 245250, 1920, 2056,
                 2264, 2608, 0, 1200, 1203, 1209, 1255, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1920x1200@85Hz */
    {
        DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 281250, 1920, 2064,
                 2272, 2624, 0, 1200, 1203, 1209, 1262, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1920x1200@120Hz RB */
    {
        DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 317000, 1920, 1968,
                 2000, 2080, 0, 1200, 1203, 1209, 1271, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 1920x1440@60Hz */
    {
        DRM_MODE("1920x1440", DRM_MODE_TYPE_DRIVER, 234000, 1920, 2048,
                 2256, 2600, 0, 1440, 1441, 1444, 1500, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1920x1440@75Hz */
    {
        DRM_MODE("1920x1440", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2064,
                 2288, 2640, 0, 1440, 1441, 1444, 1500, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 1920x1440@120Hz RB */
    {
        DRM_MODE("1920x1440", DRM_MODE_TYPE_DRIVER, 380500, 1920, 1968,
                 2000, 2080, 0, 1440, 1443, 1447, 1525, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 2560x1600@60Hz RB */
    {
        DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 268500, 2560, 2608,
                 2640, 2720, 0, 1600, 1603, 1609, 1646, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
    /* 2560x1600@60Hz */
    {
        DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 348500, 2560, 2752,
                 3032, 3504, 0, 1600, 1603, 1609, 1658, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 2560x1600@75HZ */
    {
        DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 443250, 2560, 2768,
                 3048, 3536, 0, 1600, 1603, 1609, 1672, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 2560x1600@85HZ */
    {
        DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 505250, 2560, 2768,
                 3048, 3536, 0, 1600, 1603, 1609, 1682, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    },
    /* 2560x1600@120Hz RB */
    {
        DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 552750, 2560, 2608,
                 2640, 2720, 0, 1600, 1603, 1609, 1694, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC)
    },
};

/*
 * These more or less come from the DMT spec.  The 720x400 modes are
 * inferred from historical 80x25 practice.  The 640x480@67 and 832x624@75
 * modes are old-school Mac modes.  The EDID spec says the 1152x864@75 mode
 * should be 1152x870, again for the Mac, but instead we use the x864 DMT
 * mode.
 *
 * The DMT modes have been fact-checked; the rest are mild guesses.
 */
static const struct drm_display_mode edid_est_modes[] = {
    {
        DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 40000, 800, 840,
                 968, 1056, 0, 600, 601, 605, 628, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    }, /* 800x600@60Hz */
    {
        DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 36000, 800, 824,
                 896, 1024, 0, 600, 601, 603,  625, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    }, /* 800x600@56Hz */
    {
        DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 656,
                 720, 840, 0, 480, 481, 484, 500, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    }, /* 640x480@75Hz */
    {
        DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 664,
                 704,  832, 0, 480, 489, 491, 520, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    }, /* 640x480@72Hz */
    {
        DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 30240, 640, 704,
                 768,  864, 0, 480, 483, 486, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    }, /* 640x480@67Hz */
    {
        DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25200, 640, 656,
                 752, 800, 0, 480, 490, 492, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    }, /* 640x480@60Hz */
    {
        DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 35500, 720, 738,
                 846, 900, 0, 400, 421, 423,  449, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    }, /* 720x400@88Hz */
    {
        DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 28320, 720, 738,
                 846,  900, 0, 400, 412, 414, 449, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
    }, /* 720x400@70Hz */
    {
        DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 135000, 1280, 1296,
                 1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    }, /* 1280x1024@75Hz */
    {
        DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 78800, 1024, 1040,
                 1136, 1312, 0,  768, 769, 772, 800, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    }, /* 1024x768@75Hz */
    {
        DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 75000, 1024, 1048,
                 1184, 1328, 0,  768, 771, 777, 806, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    }, /* 1024x768@70Hz */
    {
        DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 65000, 1024, 1048,
                 1184, 1344, 0,  768, 771, 777, 806, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    }, /* 1024x768@60Hz */
    {
        DRM_MODE("1024x768i", DRM_MODE_TYPE_DRIVER,44900, 1024, 1032,
                 1208, 1264, 0, 768, 768, 776, 817, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC | DRM_MODE_FLAG_INTERLACE)
    }, /* 1024x768@43Hz */
    {
        DRM_MODE("832x624", DRM_MODE_TYPE_DRIVER, 57284, 832, 864,
                 928, 1152, 0, 624, 625, 628, 667, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
    }, /* 832x624@75Hz */
    {
        DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 49500, 800, 816,
                 896, 1056, 0, 600, 601, 604,  625, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    }, /* 800x600@75Hz */
    {
        DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 50000, 800, 856,
                 976, 1040, 0, 600, 637, 643, 666, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    }, /* 800x600@72Hz */
    {
        DRM_MODE("1152x864", DRM_MODE_TYPE_DRIVER, 108000, 1152, 1216,
                 1344, 1600, 0,  864, 865, 868, 900, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)
    }, /* 1152x864@75Hz */
};

struct minimode {
    short w;
    short h;
    short r;
    short rb;
};

static const struct minimode est3_modes[] = {
    /* byte 6 */
    { 640, 350, 85, 0 },
    { 640, 400, 85, 0 },
    { 720, 400, 85, 0 },
    { 640, 480, 85, 0 },
    { 848, 480, 60, 0 },
    { 800, 600, 85, 0 },
    { 1024, 768, 85, 0 },
    { 1152, 864, 75, 0 },
    /* byte 7 */
    { 1280, 768, 60, 1 },
    { 1280, 768, 60, 0 },
    { 1280, 768, 75, 0 },
    { 1280, 768, 85, 0 },
    { 1280, 960, 60, 0 },
    { 1280, 960, 85, 0 },
    { 1280, 1024, 60, 0 },
    { 1280, 1024, 85, 0 },
    /* byte 8 */
    { 1360, 768, 60, 0 },
    { 1440, 900, 60, 1 },
    { 1440, 900, 60, 0 },
    { 1440, 900, 75, 0 },
    { 1440, 900, 85, 0 },
    { 1400, 1050, 60, 1 },
    { 1400, 1050, 60, 0 },
    { 1400, 1050, 75, 0 },
    /* byte 9 */
    { 1400, 1050, 85, 0 },
    { 1680, 1050, 60, 1 },
    { 1680, 1050, 60, 0 },
    { 1680, 1050, 75, 0 },
    { 1680, 1050, 85, 0 },
    { 1600, 1200, 60, 0 },
    { 1600, 1200, 65, 0 },
    { 1600, 1200, 70, 0 },
    /* byte 10 */
    { 1600, 1200, 75, 0 },
    { 1600, 1200, 85, 0 },
    { 1792, 1344, 60, 0 },
    { 1792, 1344, 75, 0 },
    { 1856, 1392, 60, 0 },
    { 1856, 1392, 75, 0 },
    { 1920, 1200, 60, 1 },
    { 1920, 1200, 60, 0 },
    /* byte 11 */
    { 1920, 1200, 75, 0 },
    { 1920, 1200, 85, 0 },
    { 1920, 1440, 60, 0 },
    { 1920, 1440, 75, 0 },
};

static const struct minimode extra_modes[] = {
    { 1024, 576,  60, 0 },
    { 1366, 768,  60, 0 },
    { 1600, 900,  60, 0 },
    { 1680, 945,  60, 0 },
    { 1920, 1080, 60, 0 },
    { 2048, 1152, 60, 0 },
    { 2048, 1536, 60, 0 },
};

/*
 * Probably taken from CEA-861 spec.
 * This table is converted from xorg's hw/xfree86/modes/xf86EdidModes.c.
 */
static const struct drm_display_mode edid_cea_modes[] = {
    /* 1 - 640x480@60Hz */
    {
        DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25175, 640, 656,
                 752, 800, 0, 480, 490, 492, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 2 - 720x480@60Hz */
    {
        DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27000, 720, 736,
                 798, 858, 0, 480, 489, 495, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 3 - 720x480@60Hz */
    {
        DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27000, 720, 736,
                 798, 858, 0, 480, 489, 495, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 4 - 1280x720@60Hz */
    {
        DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1390,
                 1430, 1650, 0, 720, 725, 730, 750, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 5 - 1920x1080i@60Hz */
    {
        DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
                 2052, 2200, 0, 1080, 1084, 1094, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
                 DRM_MODE_FLAG_INTERLACE),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 6 - 720(1440)x480i@60Hz */
    {
        DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
                 801, 858, 0, 480, 488, 494, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 7 - 720(1440)x480i@60Hz */
    {
        DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
                 801, 858, 0, 480, 488, 494, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 8 - 720(1440)x240@60Hz */
    {
        DRM_MODE("720x240", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
                 801, 858, 0, 240, 244, 247, 262, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 9 - 720(1440)x240@60Hz */
    {
        DRM_MODE("720x240", DRM_MODE_TYPE_DRIVER, 13500, 720, 739,
                 801, 858, 0, 240, 244, 247, 262, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 10 - 2880x480i@60Hz */
    {
        DRM_MODE("2880x480i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
                 3204, 3432, 0, 480, 488, 494, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 11 - 2880x480i@60Hz */
    {
        DRM_MODE("2880x480i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
                 3204, 3432, 0, 480, 488, 494, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 12 - 2880x240@60Hz */
    {
        DRM_MODE("2880x240", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
                 3204, 3432, 0, 240, 244, 247, 262, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 13 - 2880x240@60Hz */
    {
        DRM_MODE("2880x240", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
                 3204, 3432, 0, 240, 244, 247, 262, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 14 - 1440x480@60Hz */
    {
        DRM_MODE("1440x480", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1472,
                 1596, 1716, 0, 480, 489, 495, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 15 - 1440x480@60Hz */
    {
        DRM_MODE("1440x480", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1472,
                 1596, 1716, 0, 480, 489, 495, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 16 - 1920x1080@60Hz */
    {
        DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
                 2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 17 - 720x576@50Hz */
    {
        DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
                 796, 864, 0, 576, 581, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 18 - 720x576@50Hz */
    {
        DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
                 796, 864, 0, 576, 581, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 19 - 1280x720@50Hz */
    {
        DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1720,
                 1760, 1980, 0, 720, 725, 730, 750, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 20 - 1920x1080i@50Hz */
    {
        DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
                 2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
                 DRM_MODE_FLAG_INTERLACE),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 21 - 720(1440)x576i@50Hz */
    {
        DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
                 795, 864, 0, 576, 580, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 22 - 720(1440)x576i@50Hz */
    {
        DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
                 795, 864, 0, 576, 580, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 23 - 720(1440)x288@50Hz */
    {
        DRM_MODE("720x288", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
                 795, 864, 0, 288, 290, 293, 312, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 24 - 720(1440)x288@50Hz */
    {
        DRM_MODE("720x288", DRM_MODE_TYPE_DRIVER, 13500, 720, 732,
                 795, 864, 0, 288, 290, 293, 312, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 25 - 2880x576i@50Hz */
    {
        DRM_MODE("2880x576i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
                 3180, 3456, 0, 576, 580, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 26 - 2880x576i@50Hz */
    {
        DRM_MODE("2880x576i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
                 3180, 3456, 0, 576, 580, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 27 - 2880x288@50Hz */
    {
        DRM_MODE("2880x288", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
                 3180, 3456, 0, 288, 290, 293, 312, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 28 - 2880x288@50Hz */
    {
        DRM_MODE("2880x288", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
                 3180, 3456, 0, 288, 290, 293, 312, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 29 - 1440x576@50Hz */
    {
        DRM_MODE("1440x576", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1464,
                 1592, 1728, 0, 576, 581, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 30 - 1440x576@50Hz */
    {
        DRM_MODE("1440x576", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1464,
                 1592, 1728, 0, 576, 581, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 31 - 1920x1080@50Hz */
    {
        DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
                 2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 32 - 1920x1080@24Hz */
    {
        DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2558,
                 2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 33 - 1920x1080@25Hz */
    {
        DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
                 2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 34 - 1920x1080@30Hz */
    {
        DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
                 2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 35 - 2880x480@60Hz */
    {
        DRM_MODE("2880x480", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2944,
                 3192, 3432, 0, 480, 489, 495, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 36 - 2880x480@60Hz */
    {
        DRM_MODE("2880x480", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2944,
                 3192, 3432, 0, 480, 489, 495, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 60, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 37 - 2880x576@50Hz */
    {
        DRM_MODE("2880x576", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2928,
                 3184, 3456, 0, 576, 581, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 38 - 2880x576@50Hz */
    {
        DRM_MODE("2880x576", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2928,
                 3184, 3456, 0, 576, 581, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 39 - 1920x1080i@50Hz */
    {
        DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 72000, 1920, 1952,
                 2120, 2304, 0, 1080, 1126, 1136, 1250, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE),
        .vrefresh = 50, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 40 - 1920x1080i@100Hz */
    {
        DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
                 2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
                 DRM_MODE_FLAG_INTERLACE),
        .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 41 - 1280x720@100Hz */
    {
        DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1720,
                 1760, 1980, 0, 720, 725, 730, 750, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 42 - 720x576@100Hz */
    {
        DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
                 796, 864, 0, 576, 581, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 43 - 720x576@100Hz */
    {
        DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
                 796, 864, 0, 576, 581, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 44 - 720(1440)x576i@100Hz */
    {
        DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
                 795, 864, 0, 576, 580, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 45 - 720(1440)x576i@100Hz */
    {
        DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
                 795, 864, 0, 576, 580, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 46 - 1920x1080i@120Hz */
    {
        DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
                 2052, 2200, 0, 1080, 1084, 1094, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
                 DRM_MODE_FLAG_INTERLACE),
        .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 47 - 1280x720@120Hz */
    {
        DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1390,
                 1430, 1650, 0, 720, 725, 730, 750, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 48 - 720x480@120Hz */
    {
        DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 54000, 720, 736,
                 798, 858, 0, 480, 489, 495, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 49 - 720x480@120Hz */
    {
        DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 54000, 720, 736,
                 798, 858, 0, 480, 489, 495, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 50 - 720(1440)x480i@120Hz */
    {
        DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 27000, 720, 739,
                 801, 858, 0, 480, 488, 494, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 51 - 720(1440)x480i@120Hz */
    {
        DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 27000, 720, 739,
                 801, 858, 0, 480, 488, 494, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 52 - 720x576@200Hz */
    {
        DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 108000, 720, 732,
                 796, 864, 0, 576, 581, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 200, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 53 - 720x576@200Hz */
    {
        DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 108000, 720, 732,
                 796, 864, 0, 576, 581, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 200, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 54 - 720(1440)x576i@200Hz */
    {
        DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
                 795, 864, 0, 576, 580, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 200, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 55 - 720(1440)x576i@200Hz */
    {
        DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
                 795, 864, 0, 576, 580, 586, 625, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 200, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 56 - 720x480@240Hz */
    {
        DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 108000, 720, 736,
                 798, 858, 0, 480, 489, 495, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 240, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 57 - 720x480@240Hz */
    {
        DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 108000, 720, 736,
                 798, 858, 0, 480, 489, 495, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
        .vrefresh = 240, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 58 - 720(1440)x480i@240 */
    {
        DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 54000, 720, 739,
                 801, 858, 0, 480, 488, 494, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 240, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
    },
    /* 59 - 720(1440)x480i@240 */
    {
        DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 54000, 720, 739,
                 801, 858, 0, 480, 488, 494, 525, 0,
                 DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
                 DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
        .vrefresh = 240, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 60 - 1280x720@24Hz */
    {
        DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 59400, 1280, 3040,
                 3080, 3300, 0, 720, 725, 730, 750, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 24, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 61 - 1280x720@25Hz */
    {
        DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3700,
                 3740, 3960, 0, 720, 725, 730, 750, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 25, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 62 - 1280x720@30Hz */
    {
        DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3040,
                 3080, 3300, 0, 720, 725, 730, 750, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 30, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 63 - 1920x1080@120Hz */
    {
        DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2008,
                 2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 120, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
    /* 64 - 1920x1080@100Hz */
    {
        DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2448,
                 2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 100, .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9,
    },
};

/*
 * HDMI 1.4 4k modes.
 */
static const struct drm_display_mode edid_4k_modes[] = {
    /* 1 - 3840x2160@30Hz */
    {
        DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
                 3840, 4016, 4104, 4400, 0,
                 2160, 2168, 2178, 2250, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 30,
    },
    /* 2 - 3840x2160@25Hz */
    {
        DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
                 3840, 4896, 4984, 5280, 0,
                 2160, 2168, 2178, 2250, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 25,
    },
    /* 3 - 3840x2160@24Hz */
    {
        DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
                 3840, 5116, 5204, 5500, 0,
                 2160, 2168, 2178, 2250, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 24,
    },
    /* 4 - 4096x2160@24Hz (SMPTE) */
    {
        DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000,
                 4096, 5116, 5204, 5500, 0,
                 2160, 2168, 2178, 2250, 0,
                 DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
        .vrefresh = 24,
    },
};

/*** DDC fetch and block validation ***/

static const u8 edid_header[] = {
    0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
};

/**
 * drm_edid_header_is_valid - sanity check the header of the base EDID block
 * @raw_edid: pointer to raw base EDID block
 *
 * Sanity check the header of the base EDID block.
 *
 * Return: 8 if the header is perfect, down to 0 if it's totally wrong.
 */
int drm_edid_header_is_valid(const u8 *raw_edid)
{
    int i, score = 0;

    for (i = 0; i < sizeof(edid_header); i++)
        if (raw_edid[i] == edid_header[i]) {
            score++;
        }

    return score;
}
EXPORT_SYMBOL(drm_edid_header_is_valid);

static int edid_fixup __read_mostly = 6;
module_param_named(edid_fixup, edid_fixup, int, 0400);
MODULE_PARM_DESC(edid_fixup,
                 "Minimum number of valid EDID header bytes (0-8, default 6)");

static void drm_get_displayid(struct drm_connector *connector,
                              struct edid *edid);

static int drm_edid_block_checksum(const u8 *raw_edid)
{
    int i;
    u8 csum = 0;
    for (i = 0; i < EDID_LENGTH; i++) {
        csum += raw_edid[i];
    }

    return csum;
}

static bool drm_edid_is_zero(const u8 *in_edid, int length)
{
    if (memchr_inv(in_edid, 0, length)) {
        return false;
    }

    return true;
}

/**
 * drm_edid_block_valid - Sanity check the EDID block (base or extension)
 * @raw_edid: pointer to raw EDID block
 * @block: type of block to validate (0 for base, extension otherwise)
 * @print_bad_edid: if true, dump bad EDID blocks to the console
 *
 * Validate a base or extension EDID block and optionally dump bad blocks to
 * the console.
 *
 * Return: True if the block is valid, false otherwise.
 */
bool drm_edid_block_valid(u8 *raw_edid, int block, bool print_bad_edid)
{
    u8 csum;
    struct edid *edid = (struct edid *)raw_edid;

    if (WARN_ON(!raw_edid)) {
        return false;
    }

    if (edid_fixup > 8 || edid_fixup < 0) {
        edid_fixup = 6;
    }

    if (block == 0) {
        int score = drm_edid_header_is_valid(raw_edid);
        if (score == 8) ;
        else if (score >= edid_fixup) {
            DRM_DEBUG("Fixing EDID header, your hardware may be failing\n");
            memcpy(raw_edid, edid_header, sizeof(edid_header));
        } else {
            goto bad;
        }
    }

    csum = drm_edid_block_checksum(raw_edid);
    if (csum) {
        if (print_bad_edid) {
            DRM_ERROR("EDID checksum is invalid, remainder is %d\n", csum);
        }

        /* allow CEA to slide through, switches mangle this */
        if (raw_edid[0] != 0x02) {
            goto bad;
        }
    }

    /* per-block-type checks */
    switch (raw_edid[0]) {
    case 0: /* base */
        if (edid->version != 1) {
            DRM_ERROR("EDID has major version %d, instead of 1\n", edid->version);
            goto bad;
        }

        if (edid->revision > 4) {
            DRM_DEBUG("EDID minor > 4, assuming backward compatibility\n");
        }
        break;

    default:
        break;
    }

    return true;

bad:
    if (print_bad_edid) {
        if (drm_edid_is_zero(raw_edid, EDID_LENGTH)) {
            printk(KERN_ERR "EDID block is all zeroes\n");
        } else {
            printk(KERN_ERR "Raw EDID:\n");
            print_hex_dump(KERN_ERR, " \t", DUMP_PREFIX_NONE, 16, 1,
                           raw_edid, EDID_LENGTH, false);
        }
    }
    return false;
}
EXPORT_SYMBOL(drm_edid_block_valid);

/**
 * drm_edid_is_valid - sanity check EDID data
 * @edid: EDID data
 *
 * Sanity-check an entire EDID record (including extensions)
 *
 * Return: True if the EDID data is valid, false otherwise.
 */
bool drm_edid_is_valid(struct edid *edid)
{
    int i;
    u8 *raw = (u8 *)edid;

    if (!edid) {
        return false;
    }

    for (i = 0; i <= edid->extensions; i++)
        if (!drm_edid_block_valid(raw + i * EDID_LENGTH, i, true)) {
            return false;
        }

    return true;
}
EXPORT_SYMBOL(drm_edid_is_valid);

#define DDC_SEGMENT_ADDR 0x30
/**
 * drm_do_probe_ddc_edid() - get EDID information via I2C
 * @data: I2C device adapter
 * @buf: EDID data buffer to be filled
 * @block: 128 byte EDID block to start fetching from
 * @len: EDID data buffer length to fetch
 *
 * Try to fetch EDID information by calling I2C driver functions.
 *
 * Return: 0 on success or -1 on failure.
 */
static int
drm_do_probe_ddc_edid(void *data, u8 *buf, unsigned int block, size_t len)
{
    struct i2c_adapter *adapter = data;
    unsigned char start = block * EDID_LENGTH;
    unsigned char segment = block >> 1;
    unsigned char xfers = segment ? 3 : 2;
    int ret, retries = 5;

    /*
     * The core I2C driver will automatically retry the transfer if the
     * adapter reports EAGAIN. However, we find that bit-banging transfers
     * are susceptible to errors under a heavily loaded machine and
     * generate spurious NAKs and timeouts. Retrying the transfer
     * of the individual block a few times seems to overcome this.
     */
    do {
        struct i2c_msg msgs[] = {
            {
                .addr	= DDC_SEGMENT_ADDR,
                .flags	= 0,
                .len	= 1,
                .buf	= &segment,
            }, {
                .addr	= DDC_ADDR,
                .flags	= 0,
                .len	= 1,
                .buf	= &start,
            }, {
                .addr	= DDC_ADDR,
                .flags	= I2C_M_RD,
                .len	= len,
                .buf	= buf,
            }
        };

        /*
         * Avoid sending the segment addr to not upset non-compliant
         * DDC monitors.
         */
        ret = i2c_transfer(adapter, &msgs[3 - xfers], xfers);

        if (ret == -ENXIO) {
            DRM_DEBUG_KMS("drm: skipping non-existent adapter %s\n",
                          adapter->name);
            break;
        }
    } while (ret != xfers && --retries);

    return ret == xfers ? 0 : -1;
}

/**
 * drm_do_get_edid - get EDID data using a custom EDID block read function
 * @connector: connector we're probing
 * @get_edid_block: EDID block read function
 * @data: private data passed to the block read function
 *
 * When the I2C adapter connected to the DDC bus is hidden behind a device that
 * exposes a different interface to read EDID blocks this function can be used
 * to get EDID data using a custom block read function.
 *
 * As in the general case the DDC bus is accessible by the kernel at the I2C
 * level, drivers must make all reasonable efforts to expose it as an I2C
 * adapter and use drm_get_edid() instead of abusing this function.
 *
 * Return: Pointer to valid EDID or NULL if we couldn't find any.
 */
struct edid *drm_do_get_edid(struct drm_connector *connector,
                             int (*get_edid_block)(void *data, u8 *buf, unsigned int block,
                                     size_t len),
                             void *data)
{
    int i, j = 0, valid_extensions = 0;
    u8 *block, *new;
    bool print_bad_edid = !connector->bad_edid_counter || (drm_debug & DRM_UT_KMS);

    if ((block = kmalloc(EDID_LENGTH, GFP_KERNEL)) == NULL) {
        return NULL;
    }

    /* base block fetch */
    for (i = 0; i < 4; i++) {
        if (get_edid_block(data, block, 0, EDID_LENGTH)) {
            goto out;
        }
        if (drm_edid_block_valid(block, 0, print_bad_edid)) {
            break;
        }
        if (i == 0 && drm_edid_is_zero(block, EDID_LENGTH)) {
            connector->null_edid_counter++;
            goto carp;
        }
    }
    if (i == 4) {
        goto carp;
    }

    /* if there's no extensions, we're done */
    if (block[0x7e] == 0) {
        return (struct edid *)block;
    }

    new = krealloc(block, (block[0x7e] + 1) * EDID_LENGTH, GFP_KERNEL);
    if (!new) {
        goto out;
    }
    block = new;

    for (j = 1; j <= block[0x7e]; j++) {
        for (i = 0; i < 4; i++) {
            if (get_edid_block(data,
                               block + (valid_extensions + 1) * EDID_LENGTH,
                               j, EDID_LENGTH)) {
                goto out;
            }
            if (drm_edid_block_valid(block + (valid_extensions + 1) * EDID_LENGTH, j, print_bad_edid)) {
                valid_extensions++;
                break;
            }
        }

        if (i == 4 && print_bad_edid) {
            dev_warn(connector->dev->dev,
                     "%s: Ignoring invalid EDID block %d.\n",
                     connector->name, j);

            connector->bad_edid_counter++;
        }
    }

    if (valid_extensions != block[0x7e]) {
        block[EDID_LENGTH-1] += block[0x7e] - valid_extensions;
        block[0x7e] = valid_extensions;
        new = krealloc(block, (valid_extensions + 1) * EDID_LENGTH, GFP_KERNEL);
        if (!new) {
            goto out;
        }
        block = new;
    }

    return (struct edid *)block;

carp:
    if (print_bad_edid) {
        dev_warn(connector->dev->dev, "%s: EDID block %d invalid.\n",
                 connector->name, j);
    }
    connector->bad_edid_counter++;

out:
    kfree(block);
    return NULL;
}
EXPORT_SYMBOL_GPL(drm_do_get_edid);

/**
 * drm_probe_ddc() - probe DDC presence
 * @adapter: I2C adapter to probe
 *
 * Return: True on success, false on failure.
 */
bool
drm_probe_ddc(struct i2c_adapter *adapter)
{
    unsigned char out;

    return (drm_do_probe_ddc_edid(adapter, &out, 0, 1) == 0);
}
EXPORT_SYMBOL(drm_probe_ddc);

/**
 * drm_get_edid - get EDID data, if available
 * @connector: connector we're probing
 * @adapter: I2C adapter to use for DDC
 *
 * Poke the given I2C channel to grab EDID data if possible.  If found,
 * attach it to the connector.
 *
 * Return: Pointer to valid EDID or NULL if we couldn't find any.
 */
struct edid *drm_get_edid(struct drm_connector *connector,
                          struct i2c_adapter *adapter)
{
    struct edid *edid;

    if (!drm_probe_ddc(adapter)) {
        return NULL;
    }

    edid = drm_do_get_edid(connector, drm_do_probe_ddc_edid, adapter);
    if (edid) {
        drm_get_displayid(connector, edid);
    }
    return edid;
}
EXPORT_SYMBOL(drm_get_edid);

/**
 * drm_edid_duplicate - duplicate an EDID and the extensions
 * @edid: EDID to duplicate
 *
 * Return: Pointer to duplicated EDID or NULL on allocation failure.
 */
struct edid *drm_edid_duplicate(const struct edid *edid)
{
    return kmemdup(edid, (edid->extensions + 1) * EDID_LENGTH, GFP_KERNEL);
}
EXPORT_SYMBOL(drm_edid_duplicate);

/*** EDID parsing ***/

/**
 * edid_vendor - match a string against EDID's obfuscated vendor field
 * @edid: EDID to match
 * @vendor: vendor string
 *
 * Returns true if @vendor is in @edid, false otherwise
 */
static bool edid_vendor(struct edid *edid, char *vendor)
{
    char edid_vendor[3];

    edid_vendor[0] = ((edid->mfg_id[0] & 0x7c) >> 2) + '@';
    edid_vendor[1] = (((edid->mfg_id[0] & 0x3) << 3) |
                      ((edid->mfg_id[1] & 0xe0) >> 5)) + '@';
    edid_vendor[2] = (edid->mfg_id[1] & 0x1f) + '@';

    return !strncmp(edid_vendor, vendor, 3);
}

/**
 * edid_get_quirks - return quirk flags for a given EDID
 * @edid: EDID to process
 *
 * This tells subsequent routines what fixes they need to apply.
 */
static u32 edid_get_quirks(struct edid *edid)
{
    struct edid_quirk *quirk;
    int i;

    for (i = 0; i < ARRAY_SIZE(edid_quirk_list); i++) {
        quirk = &edid_quirk_list[i];

        if (edid_vendor(edid, quirk->vendor) &&
            (EDID_PRODUCT_ID(edid) == quirk->product_id)) {
            return quirk->quirks;
        }
    }

    return 0;
}

#define MODE_SIZE(m) ((m)->hdisplay * (m)->vdisplay)
#define MODE_REFRESH_DIFF(c,t) (abs((c) - (t)))

/**
 * edid_fixup_preferred - set preferred modes based on quirk list
 * @connector: has mode list to fix up
 * @quirks: quirks list
 *
 * Walk the mode list for @connector, clearing the preferred status
 * on existing modes and setting it anew for the right mode ala @quirks.
 */
static void edid_fixup_preferred(struct drm_connector *connector,
                                 u32 quirks)
{
    struct drm_display_mode *t, *cur_mode, *preferred_mode;
    int target_refresh = 0;
    int cur_vrefresh, preferred_vrefresh;

    if (list_empty(&connector->probed_modes)) {
        return;
    }

    if (quirks & EDID_QUIRK_PREFER_LARGE_60) {
        target_refresh = 60;
    }
    if (quirks & EDID_QUIRK_PREFER_LARGE_75) {
        target_refresh = 75;
    }

    preferred_mode = list_first_entry(&connector->probed_modes,
                                      struct drm_display_mode, head);

    list_for_each_entry_safe(cur_mode, t, &connector->probed_modes, head) {
        cur_mode->type &= ~DRM_MODE_TYPE_PREFERRED;

        if (cur_mode == preferred_mode) {
            continue;
        }

        /* Largest mode is preferred */
        if (MODE_SIZE(cur_mode) > MODE_SIZE(preferred_mode)) {
            preferred_mode = cur_mode;
        }

        cur_vrefresh = cur_mode->vrefresh ?
                       cur_mode->vrefresh : drm_mode_vrefresh(cur_mode);
        preferred_vrefresh = preferred_mode->vrefresh ?
                             preferred_mode->vrefresh : drm_mode_vrefresh(preferred_mode);
        /* At a given size, try to get closest to target refresh */
        if ((MODE_SIZE(cur_mode) == MODE_SIZE(preferred_mode)) &&
            MODE_REFRESH_DIFF(cur_vrefresh, target_refresh) <
            MODE_REFRESH_DIFF(preferred_vrefresh, target_refresh)) {
            preferred_mode = cur_mode;
        }
    }

    preferred_mode->type |= DRM_MODE_TYPE_PREFERRED;
}

static bool
mode_is_rb(const struct drm_display_mode *mode)
{
    return (mode->htotal - mode->hdisplay == 160) &&
           (mode->hsync_end - mode->hdisplay == 80) &&
           (mode->hsync_end - mode->hsync_start == 32) &&
           (mode->vsync_start - mode->vdisplay == 3);
}

/*
 * drm_mode_find_dmt - Create a copy of a mode if present in DMT
 * @dev: Device to duplicate against
 * @hsize: Mode width
 * @vsize: Mode height
 * @fresh: Mode refresh rate
 * @rb: Mode reduced-blanking-ness
 *
 * Walk the DMT mode list looking for a match for the given parameters.
 *
 * Return: A newly allocated copy of the mode, or NULL if not found.
 */
struct drm_display_mode *drm_mode_find_dmt(struct drm_device *dev,
        int hsize, int vsize, int fresh,
        bool rb)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(drm_dmt_modes); i++) {
        const struct drm_display_mode *ptr = &drm_dmt_modes[i];
        if (hsize != ptr->hdisplay) {
            continue;
        }
        if (vsize != ptr->vdisplay) {
            continue;
        }
        if (fresh != drm_mode_vrefresh(ptr)) {
            continue;
        }
        if (rb != mode_is_rb(ptr)) {
            continue;
        }

        return drm_mode_duplicate(dev, ptr);
    }

    return NULL;
}
EXPORT_SYMBOL(drm_mode_find_dmt);

typedef void detailed_cb(struct detailed_timing *timing, void *closure);

static void
cea_for_each_detailed_block(u8 *ext, detailed_cb *cb, void *closure)
{
    int i, n = 0;
    u8 d = ext[0x02];
    u8 *det_base = ext + d;

    n = (127 - d) / 18;
    for (i = 0; i < n; i++) {
        cb((struct detailed_timing *)(det_base + 18 * i), closure);
    }
}

static void
vtb_for_each_detailed_block(u8 *ext, detailed_cb *cb, void *closure)
{
    unsigned int i, n = min((int)ext[0x02], 6);
    u8 *det_base = ext + 5;

    if (ext[0x01] != 1) {
        return;    /* unknown version */
    }

    for (i = 0; i < n; i++) {
        cb((struct detailed_timing *)(det_base + 18 * i), closure);
    }
}

static void
drm_for_each_detailed_block(u8 *raw_edid, detailed_cb *cb, void *closure)
{
    int i;
    struct edid *edid = (struct edid *)raw_edid;

    if (edid == NULL) {
        return;
    }

    for (i = 0; i < EDID_DETAILED_TIMINGS; i++) {
        cb(&(edid->detailed_timings[i]), closure);
    }

    for (i = 1; i <= raw_edid[0x7e]; i++) {
        u8 *ext = raw_edid + (i * EDID_LENGTH);
        switch (*ext) {
        case CEA_EXT:
            cea_for_each_detailed_block(ext, cb, closure);
            break;
        case VTB_EXT:
            vtb_for_each_detailed_block(ext, cb, closure);
            break;
        default:
            break;
        }
    }
}

static void
is_rb(struct detailed_timing *t, void *data)
{
    u8 *r = (u8 *)t;
    if (r[3] == EDID_DETAIL_MONITOR_RANGE)
        if (r[15] & 0x10) {
            *(bool *)data = true;
        }
}

/* EDID 1.4 defines this explicitly.  For EDID 1.3, we guess, badly. */
static bool
drm_monitor_supports_rb(struct edid *edid)
{
    if (edid->revision >= 4) {
        bool ret = false;
        drm_for_each_detailed_block((u8 *)edid, is_rb, &ret);
        return ret;
    }

    return ((edid->input & DRM_EDID_INPUT_DIGITAL) != 0);
}

static void
find_gtf2(struct detailed_timing *t, void *data)
{
    u8 *r = (u8 *)t;
    if (r[3] == EDID_DETAIL_MONITOR_RANGE && r[10] == 0x02) {
        *(u8 **)data = r;
    }
}

/* Secondary GTF curve kicks in above some break frequency */
static int
drm_gtf2_hbreak(struct edid *edid)
{
    u8 *r = NULL;
    drm_for_each_detailed_block((u8 *)edid, find_gtf2, &r);
    return r ? (r[12] * 2) : 0;
}

static int
drm_gtf2_2c(struct edid *edid)
{
    u8 *r = NULL;
    drm_for_each_detailed_block((u8 *)edid, find_gtf2, &r);
    return r ? r[13] : 0;
}

static int
drm_gtf2_m(struct edid *edid)
{
    u8 *r = NULL;
    drm_for_each_detailed_block((u8 *)edid, find_gtf2, &r);
    return r ? (r[15] << 8) + r[14] : 0;
}

static int
drm_gtf2_k(struct edid *edid)
{
    u8 *r = NULL;
    drm_for_each_detailed_block((u8 *)edid, find_gtf2, &r);
    return r ? r[16] : 0;
}

static int
drm_gtf2_2j(struct edid *edid)
{
    u8 *r = NULL;
    drm_for_each_detailed_block((u8 *)edid, find_gtf2, &r);
    return r ? r[17] : 0;
}

/**
 * standard_timing_level - get std. timing level(CVT/GTF/DMT)
 * @edid: EDID block to scan
 */
static int standard_timing_level(struct edid *edid)
{
    if (edid->revision >= 2) {
        if (edid->revision >= 4 && (edid->features & DRM_EDID_FEATURE_DEFAULT_GTF)) {
            return LEVEL_CVT;
        }
        if (drm_gtf2_hbreak(edid)) {
            return LEVEL_GTF2;
        }
        return LEVEL_GTF;
    }
    return LEVEL_DMT;
}

/*
 * 0 is reserved.  The spec says 0x01 fill for unused timings.  Some old
 * monitors fill with ascii space (0x20) instead.
 */
static int
bad_std_timing(u8 a, u8 b)
{
    return (a == 0x00 && b == 0x00) ||
           (a == 0x01 && b == 0x01) ||
           (a == 0x20 && b == 0x20);
}

/**
 * drm_mode_std - convert standard mode info (width, height, refresh) into mode
 * @connector: connector of for the EDID block
 * @edid: EDID block to scan
 * @t: standard timing params
 *
 * Take the standard timing params (in this case width, aspect, and refresh)
 * and convert them into a real mode using CVT/GTF/DMT.
 */
static struct drm_display_mode *
drm_mode_std(struct drm_connector *connector, struct edid *edid,
             struct std_timing *t)
{
    struct drm_device *dev = connector->dev;
    struct drm_display_mode *m, *mode = NULL;
    int hsize, vsize;
    int vrefresh_rate;
    unsigned aspect_ratio = (t->vfreq_aspect & EDID_TIMING_ASPECT_MASK)
                            >> EDID_TIMING_ASPECT_SHIFT;
    unsigned vfreq = (t->vfreq_aspect & EDID_TIMING_VFREQ_MASK)
                     >> EDID_TIMING_VFREQ_SHIFT;
    int timing_level = standard_timing_level(edid);

    if (bad_std_timing(t->hsize, t->vfreq_aspect)) {
        return NULL;
    }

    /* According to the EDID spec, the hdisplay = hsize * 8 + 248 */
    hsize = t->hsize * 8 + 248;
    /* vrefresh_rate = vfreq + 60 */
    vrefresh_rate = vfreq + 60;
    /* the vdisplay is calculated based on the aspect ratio */
    if (aspect_ratio == 0) {
        if (edid->revision < 3) {
            vsize = hsize;
        } else {
            vsize = (hsize * 10) / 16;
        }
    } else if (aspect_ratio == 1) {
        vsize = (hsize * 3) / 4;
    } else if (aspect_ratio == 2) {
        vsize = (hsize * 4) / 5;
    } else {
        vsize = (hsize * 9) / 16;
    }

    /* HDTV hack, part 1 */
    if (vrefresh_rate == 60 &&
        ((hsize == 1360 && vsize == 765) ||
         (hsize == 1368 && vsize == 769))) {
        hsize = 1366;
        vsize = 768;
    }

    /*
     * If this connector already has a mode for this size and refresh
     * rate (because it came from detailed or CVT info), use that
     * instead.  This way we don't have to guess at interlace or
     * reduced blanking.
     */
    list_for_each_entry(m, &connector->probed_modes, head)
    if (m->hdisplay == hsize && m->vdisplay == vsize &&
        drm_mode_vrefresh(m) == vrefresh_rate) {
        return NULL;
    }

    /* HDTV hack, part 2 */
    if (hsize == 1366 && vsize == 768 && vrefresh_rate == 60) {
        mode = drm_cvt_mode(dev, 1366, 768, vrefresh_rate, 0, 0,
                            false);
        mode->hdisplay = 1366;
        mode->hsync_start = mode->hsync_start - 1;
        mode->hsync_end = mode->hsync_end - 1;
        return mode;
    }

    /* check whether it can be found in default mode table */
    if (drm_monitor_supports_rb(edid)) {
        mode = drm_mode_find_dmt(dev, hsize, vsize, vrefresh_rate,
                                 true);
        if (mode) {
            return mode;
        }
    }
    mode = drm_mode_find_dmt(dev, hsize, vsize, vrefresh_rate, false);
    if (mode) {
        return mode;
    }

    /* okay, generate it */
    switch (timing_level) {
    case LEVEL_DMT:
        break;
    case LEVEL_GTF:
        mode = drm_gtf_mode(dev, hsize, vsize, vrefresh_rate, 0, 0);
        break;
    case LEVEL_GTF2:
        /*
         * This is potentially wrong if there's ever a monitor with
         * more than one ranges section, each claiming a different
         * secondary GTF curve.  Please don't do that.
         */
        mode = drm_gtf_mode(dev, hsize, vsize, vrefresh_rate, 0, 0);
        if (!mode) {
            return NULL;
        }
        if (drm_mode_hsync(mode) > drm_gtf2_hbreak(edid)) {
            drm_mode_destroy(dev, mode);
            mode = drm_gtf_mode_complex(dev, hsize, vsize,
                                        vrefresh_rate, 0, 0,
                                        drm_gtf2_m(edid),
                                        drm_gtf2_2c(edid),
                                        drm_gtf2_k(edid),
                                        drm_gtf2_2j(edid));
        }
        break;
    case LEVEL_CVT:
        mode = drm_cvt_mode(dev, hsize, vsize, vrefresh_rate, 0, 0,
                            false);
        break;
    }
    return mode;
}

/*
 * EDID is delightfully ambiguous about how interlaced modes are to be
 * encoded.  Our internal representation is of frame height, but some
 * HDTV detailed timings are encoded as field height.
 *
 * The format list here is from CEA, in frame size.  Technically we
 * should be checking refresh rate too.  Whatever.
 */
static void
drm_mode_do_interlace_quirk(struct drm_display_mode *mode,
                            struct detailed_pixel_timing *pt)
{
    int i;
    static const struct {
        int w, h;
    } cea_interlaced[] = {
        { 1920, 1080 },
        {  720,  480 },
        { 1440,  480 },
        { 2880,  480 },
        {  720,  576 },
        { 1440,  576 },
        { 2880,  576 },
    };

    if (!(pt->misc & DRM_EDID_PT_INTERLACED)) {
        return;
    }

    for (i = 0; i < ARRAY_SIZE(cea_interlaced); i++) {
        if ((mode->hdisplay == cea_interlaced[i].w) &&
            (mode->vdisplay == cea_interlaced[i].h / 2)) {
            mode->vdisplay *= 2;
            mode->vsync_start *= 2;
            mode->vsync_end *= 2;
            mode->vtotal *= 2;
            mode->vtotal |= 1;
        }
    }

    mode->flags |= DRM_MODE_FLAG_INTERLACE;
}

/**
 * drm_mode_detailed - create a new mode from an EDID detailed timing section
 * @dev: DRM device (needed to create new mode)
 * @edid: EDID block
 * @timing: EDID detailed timing info
 * @quirks: quirks to apply
 *
 * An EDID detailed timing block contains enough info for us to create and
 * return a new struct drm_display_mode.
 */
static struct drm_display_mode *drm_mode_detailed(struct drm_device *dev,
        struct edid *edid,
        struct detailed_timing *timing,
        u32 quirks)
{
    struct drm_display_mode *mode;
    struct detailed_pixel_timing *pt = &timing->data.pixel_data;
    unsigned hactive = (pt->hactive_hblank_hi & 0xf0) << 4 | pt->hactive_lo;
    unsigned vactive = (pt->vactive_vblank_hi & 0xf0) << 4 | pt->vactive_lo;
    unsigned hblank = (pt->hactive_hblank_hi & 0xf) << 8 | pt->hblank_lo;
    unsigned vblank = (pt->vactive_vblank_hi & 0xf) << 8 | pt->vblank_lo;
    unsigned hsync_offset = (pt->hsync_vsync_offset_pulse_width_hi & 0xc0) << 2 | pt->hsync_offset_lo;
    unsigned hsync_pulse_width = (pt->hsync_vsync_offset_pulse_width_hi & 0x30) << 4 | pt->hsync_pulse_width_lo;
    unsigned vsync_offset = (pt->hsync_vsync_offset_pulse_width_hi & 0xc) << 2 | pt->vsync_offset_pulse_width_lo >> 4;
    unsigned vsync_pulse_width = (pt->hsync_vsync_offset_pulse_width_hi & 0x3) << 4 | (pt->vsync_offset_pulse_width_lo & 0xf);

    /* ignore tiny modes */
    if (hactive < 64 || vactive < 64) {
        return NULL;
    }

    if (pt->misc & DRM_EDID_PT_STEREO) {
        DRM_DEBUG_KMS("stereo mode not supported\n");
        return NULL;
    }
    if (!(pt->misc & DRM_EDID_PT_SEPARATE_SYNC)) {
        DRM_DEBUG_KMS("composite sync not supported\n");
    }

    /* it is incorrect if hsync/vsync width is zero */
    if (!hsync_pulse_width || !vsync_pulse_width) {
        DRM_DEBUG_KMS("Incorrect Detailed timing. "
                      "Wrong Hsync/Vsync pulse width\n");
        return NULL;
    }

    if (quirks & EDID_QUIRK_FORCE_REDUCED_BLANKING) {
        mode = drm_cvt_mode(dev, hactive, vactive, 60, true, false, false);
        if (!mode) {
            return NULL;
        }

        goto set_size;
    }

    mode = drm_mode_create(dev);
    if (!mode) {
        return NULL;
    }

    if (quirks & EDID_QUIRK_135_CLOCK_TOO_HIGH) {
        timing->pixel_clock = cpu_to_le16(1088);
    }

    mode->clock = le16_to_cpu(timing->pixel_clock) * 10;

    mode->hdisplay = hactive;
    mode->hsync_start = mode->hdisplay + hsync_offset;
    mode->hsync_end = mode->hsync_start + hsync_pulse_width;
    mode->htotal = mode->hdisplay + hblank;

    mode->vdisplay = vactive;
    mode->vsync_start = mode->vdisplay + vsync_offset;
    mode->vsync_end = mode->vsync_start + vsync_pulse_width;
    mode->vtotal = mode->vdisplay + vblank;

    /* Some EDIDs have bogus h/vtotal values */
    if (mode->hsync_end > mode->htotal) {
        mode->htotal = mode->hsync_end + 1;
    }
    if (mode->vsync_end > mode->vtotal) {
        mode->vtotal = mode->vsync_end + 1;
    }

    drm_mode_do_interlace_quirk(mode, pt);

    if (quirks & EDID_QUIRK_DETAILED_SYNC_PP) {
        pt->misc |= DRM_EDID_PT_HSYNC_POSITIVE | DRM_EDID_PT_VSYNC_POSITIVE;
    }

    mode->flags |= (pt->misc & DRM_EDID_PT_HSYNC_POSITIVE) ?
                   DRM_MODE_FLAG_PHSYNC : DRM_MODE_FLAG_NHSYNC;
    mode->flags |= (pt->misc & DRM_EDID_PT_VSYNC_POSITIVE) ?
                   DRM_MODE_FLAG_PVSYNC : DRM_MODE_FLAG_NVSYNC;

set_size:
    mode->width_mm = pt->width_mm_lo | (pt->width_height_mm_hi & 0xf0) << 4;
    mode->height_mm = pt->height_mm_lo | (pt->width_height_mm_hi & 0xf) << 8;

    if (quirks & EDID_QUIRK_DETAILED_IN_CM) {
        mode->width_mm *= 10;
        mode->height_mm *= 10;
    }

    if (quirks & EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE) {
        mode->width_mm = edid->width_cm * 10;
        mode->height_mm = edid->height_cm * 10;
    }

    mode->type = DRM_MODE_TYPE_DRIVER;
    mode->vrefresh = drm_mode_vrefresh(mode);
    drm_mode_set_name(mode);

    return mode;
}

static bool
mode_in_hsync_range(const struct drm_display_mode *mode,
                    struct edid *edid, u8 *t)
{
    int hsync, hmin, hmax;

    hmin = t[7];
    if (edid->revision >= 4) {
        hmin += ((t[4] & 0x04) ? 255 : 0);
    }
    hmax = t[8];
    if (edid->revision >= 4) {
        hmax += ((t[4] & 0x08) ? 255 : 0);
    }
    hsync = drm_mode_hsync(mode);

    return (hsync <= hmax && hsync >= hmin);
}

static bool
mode_in_vsync_range(const struct drm_display_mode *mode,
                    struct edid *edid, u8 *t)
{
    int vsync, vmin, vmax;

    vmin = t[5];
    if (edid->revision >= 4) {
        vmin += ((t[4] & 0x01) ? 255 : 0);
    }
    vmax = t[6];
    if (edid->revision >= 4) {
        vmax += ((t[4] & 0x02) ? 255 : 0);
    }
    vsync = drm_mode_vrefresh(mode);

    return (vsync <= vmax && vsync >= vmin);
}

static u32
range_pixel_clock(struct edid *edid, u8 *t)
{
    /* unspecified */
    if (t[9] == 0 || t[9] == 255) {
        return 0;
    }

    /* 1.4 with CVT support gives us real precision, yay */
    if (edid->revision >= 4 && t[10] == 0x04) {
        return (t[9] * 10000) - ((t[12] >> 2) * 250);
    }

    /* 1.3 is pathetic, so fuzz up a bit */
    return t[9] * 10000 + 5001;
}

static bool
mode_in_range(const struct drm_display_mode *mode, struct edid *edid,
              struct detailed_timing *timing)
{
    u32 max_clock;
    u8 *t = (u8 *)timing;

    if (!mode_in_hsync_range(mode, edid, t)) {
        return false;
    }

    if (!mode_in_vsync_range(mode, edid, t)) {
        return false;
    }

    if ((max_clock = range_pixel_clock(edid, t)))
        if (mode->clock > max_clock) {
            return false;
        }

    /* 1.4 max horizontal check */
    if (edid->revision >= 4 && t[10] == 0x04)
        if (t[13] && mode->hdisplay > 8 * (t[13] + (256 * (t[12]&0x3)))) {
            return false;
        }

    if (mode_is_rb(mode) && !drm_monitor_supports_rb(edid)) {
        return false;
    }

    return true;
}

static bool valid_inferred_mode(const struct drm_connector *connector,
                                const struct drm_display_mode *mode)
{
    struct drm_display_mode *m;
    bool ok = false;

    list_for_each_entry(m, &connector->probed_modes, head) {
        if (mode->hdisplay == m->hdisplay &&
            mode->vdisplay == m->vdisplay &&
            drm_mode_vrefresh(mode) == drm_mode_vrefresh(m)) {
            return false;    /* duplicated */
        }
        if (mode->hdisplay <= m->hdisplay &&
            mode->vdisplay <= m->vdisplay) {
            ok = true;
        }
    }
    return ok;
}

static int
drm_dmt_modes_for_range(struct drm_connector *connector, struct edid *edid,
                        struct detailed_timing *timing)
{
    int i, modes = 0;
    struct drm_display_mode *newmode;
    struct drm_device *dev = connector->dev;

    for (i = 0; i < ARRAY_SIZE(drm_dmt_modes); i++) {
        if (mode_in_range(drm_dmt_modes + i, edid, timing) &&
            valid_inferred_mode(connector, drm_dmt_modes + i)) {
            newmode = drm_mode_duplicate(dev, &drm_dmt_modes[i]);
            if (newmode) {
                drm_mode_probed_add(connector, newmode);
                modes++;
            }
        }
    }

    return modes;
}

/* fix up 1366x768 mode from 1368x768;
 * GFT/CVT can't express 1366 width which isn't dividable by 8
 */
static void fixup_mode_1366x768(struct drm_display_mode *mode)
{
    if (mode->hdisplay == 1368 && mode->vdisplay == 768) {
        mode->hdisplay = 1366;
        mode->hsync_start--;
        mode->hsync_end--;
        drm_mode_set_name(mode);
    }
}

static int
drm_gtf_modes_for_range(struct drm_connector *connector, struct edid *edid,
                        struct detailed_timing *timing)
{
    int i, modes = 0;
    struct drm_display_mode *newmode;
    struct drm_device *dev = connector->dev;

    for (i = 0; i < ARRAY_SIZE(extra_modes); i++) {
        const struct minimode *m = &extra_modes[i];
        newmode = drm_gtf_mode(dev, m->w, m->h, m->r, 0, 0);
        if (!newmode) {
            return modes;
        }

        fixup_mode_1366x768(newmode);
        if (!mode_in_range(newmode, edid, timing) ||
            !valid_inferred_mode(connector, newmode)) {
            drm_mode_destroy(dev, newmode);
            continue;
        }

        drm_mode_probed_add(connector, newmode);
        modes++;
    }

    return modes;
}

static int
drm_cvt_modes_for_range(struct drm_connector *connector, struct edid *edid,
                        struct detailed_timing *timing)
{
    int i, modes = 0;
    struct drm_display_mode *newmode;
    struct drm_device *dev = connector->dev;
    bool rb = drm_monitor_supports_rb(edid);

    for (i = 0; i < ARRAY_SIZE(extra_modes); i++) {
        const struct minimode *m = &extra_modes[i];
        newmode = drm_cvt_mode(dev, m->w, m->h, m->r, rb, 0, 0);
        if (!newmode) {
            return modes;
        }

        fixup_mode_1366x768(newmode);
        if (!mode_in_range(newmode, edid, timing) ||
            !valid_inferred_mode(connector, newmode)) {
            drm_mode_destroy(dev, newmode);
            continue;
        }

        drm_mode_probed_add(connector, newmode);
        modes++;
    }

    return modes;
}

static void
do_inferred_modes(struct detailed_timing *timing, void *c)
{
    struct detailed_mode_closure *closure = c;
    struct detailed_non_pixel *data = &timing->data.other_data;
    struct detailed_data_monitor_range *range = &data->data.range;

    if (data->type != EDID_DETAIL_MONITOR_RANGE) {
        return;
    }

    closure->modes += drm_dmt_modes_for_range(closure->connector,
                      closure->edid,
                      timing);

    if (!version_greater(closure->edid, 1, 1)) {
        return;    /* GTF not defined yet */
    }

    switch (range->flags) {
    case 0x02: /* secondary gtf, XXX could do more */
    case 0x00: /* default gtf */
        closure->modes += drm_gtf_modes_for_range(closure->connector,
                          closure->edid,
                          timing);
        break;
    case 0x04: /* cvt, only in 1.4+ */
        if (!version_greater(closure->edid, 1, 3)) {
            break;
        }

        closure->modes += drm_cvt_modes_for_range(closure->connector,
                          closure->edid,
                          timing);
        break;
    case 0x01: /* just the ranges, no formula */
    default:
        break;
    }
}

static int
add_inferred_modes(struct drm_connector *connector, struct edid *edid)
{
    struct detailed_mode_closure closure = {
        .connector = connector,
        .edid = edid,
    };

    if (version_greater(edid, 1, 0))
        drm_for_each_detailed_block((u8 *)edid, do_inferred_modes,
                                    &closure);

    return closure.modes;
}

static int
drm_est3_modes(struct drm_connector *connector, struct detailed_timing *timing)
{
    int i, j, m, modes = 0;
    struct drm_display_mode *mode;
    u8 *est = ((u8 *)timing) + 5;

    for (i = 0; i < 6; i++) {
        for (j = 7; j >= 0; j--) {
            m = (i * 8) + (7 - j);
            if (m >= ARRAY_SIZE(est3_modes)) {
                break;
            }
            if (est[i] & (1 << j)) {
                mode = drm_mode_find_dmt(connector->dev,
                                         est3_modes[m].w,
                                         est3_modes[m].h,
                                         est3_modes[m].r,
                                         est3_modes[m].rb);
                if (mode) {
                    drm_mode_probed_add(connector, mode);
                    modes++;
                }
            }
        }
    }

    return modes;
}

static void
do_established_modes(struct detailed_timing *timing, void *c)
{
    struct detailed_mode_closure *closure = c;
    struct detailed_non_pixel *data = &timing->data.other_data;

    if (data->type == EDID_DETAIL_EST_TIMINGS) {
        closure->modes += drm_est3_modes(closure->connector, timing);
    }
}

/**
 * add_established_modes - get est. modes from EDID and add them
 * @connector: connector to add mode(s) to
 * @edid: EDID block to scan
 *
 * Each EDID block contains a bitmap of the supported "established modes" list
 * (defined above).  Tease them out and add them to the global modes list.
 */
static int
add_established_modes(struct drm_connector *connector, struct edid *edid)
{
    struct drm_device *dev = connector->dev;
    unsigned long est_bits = edid->established_timings.t1 |
                             (edid->established_timings.t2 << 8) |
                             ((edid->established_timings.mfg_rsvd & 0x80) << 9);
    int i, modes = 0;
    struct detailed_mode_closure closure = {
        .connector = connector,
        .edid = edid,
    };

    for (i = 0; i <= EDID_EST_TIMINGS; i++) {
        if (est_bits & (1<<i)) {
            struct drm_display_mode *newmode;
            newmode = drm_mode_duplicate(dev, &edid_est_modes[i]);
            if (newmode) {
                drm_mode_probed_add(connector, newmode);
                modes++;
            }
        }
    }

    if (version_greater(edid, 1, 0))
        drm_for_each_detailed_block((u8 *)edid,
                                    do_established_modes, &closure);

    return modes + closure.modes;
}

static void
do_standard_modes(struct detailed_timing *timing, void *c)
{
    struct detailed_mode_closure *closure = c;
    struct detailed_non_pixel *data = &timing->data.other_data;
    struct drm_connector *connector = closure->connector;
    struct edid *edid = closure->edid;

    if (data->type == EDID_DETAIL_STD_MODES) {
        int i;
        for (i = 0; i < 6; i++) {
            struct std_timing *std;
            struct drm_display_mode *newmode;

            std = &data->data.timings[i];
            newmode = drm_mode_std(connector, edid, std);
            if (newmode) {
                drm_mode_probed_add(connector, newmode);
                closure->modes++;
            }
        }
    }
}

/**
 * add_standard_modes - get std. modes from EDID and add them
 * @connector: connector to add mode(s) to
 * @edid: EDID block to scan
 *
 * Standard modes can be calculated using the appropriate standard (DMT,
 * GTF or CVT. Grab them from @edid and add them to the list.
 */
static int
add_standard_modes(struct drm_connector *connector, struct edid *edid)
{
    int i, modes = 0;
    struct detailed_mode_closure closure = {
        .connector = connector,
        .edid = edid,
    };

    for (i = 0; i < EDID_STD_TIMINGS; i++) {
        struct drm_display_mode *newmode;

        newmode = drm_mode_std(connector, edid,
                               &edid->standard_timings[i]);
        if (newmode) {
            drm_mode_probed_add(connector, newmode);
            modes++;
        }
    }

    if (version_greater(edid, 1, 0))
        drm_for_each_detailed_block((u8 *)edid, do_standard_modes,
                                    &closure);

    /* XXX should also look for standard codes in VTB blocks */

    return modes + closure.modes;
}

static int drm_cvt_modes(struct drm_connector *connector,
                         struct detailed_timing *timing)
{
    int i, j, modes = 0;
    struct drm_display_mode *newmode;
    struct drm_device *dev = connector->dev;
    struct cvt_timing *cvt;
    const int rates[] = { 60, 85, 75, 60, 50 };
    const u8 empty[3] = { 0, 0, 0 };

    for (i = 0; i < 4; i++) {
        int uninitialized_var(width), height;
        cvt = &(timing->data.other_data.data.cvt[i]);

        if (!memcmp(cvt->code, empty, 3)) {
            continue;
        }

        height = (cvt->code[0] + ((cvt->code[1] & 0xf0) << 4) + 1) * 2;
        switch (cvt->code[1] & 0x0c) {
        case 0x00:
            width = height * 4 / 3;
            break;
        case 0x04:
            width = height * 16 / 9;
            break;
        case 0x08:
            width = height * 16 / 10;
            break;
        case 0x0c:
            width = height * 15 / 9;
            break;
        }

        for (j = 1; j < 5; j++) {
            if (cvt->code[2] & (1 << j)) {
                newmode = drm_cvt_mode(dev, width, height,
                                       rates[j], j == 0,
                                       false, false);
                if (newmode) {
                    drm_mode_probed_add(connector, newmode);
                    modes++;
                }
            }
        }
    }

    return modes;
}

static void
do_cvt_mode(struct detailed_timing *timing, void *c)
{
    struct detailed_mode_closure *closure = c;
    struct detailed_non_pixel *data = &timing->data.other_data;

    if (data->type == EDID_DETAIL_CVT_3BYTE) {
        closure->modes += drm_cvt_modes(closure->connector, timing);
    }
}

static int
add_cvt_modes(struct drm_connector *connector, struct edid *edid)
{
    struct detailed_mode_closure closure = {
        .connector = connector,
        .edid = edid,
    };

    if (version_greater(edid, 1, 2)) {
        drm_for_each_detailed_block((u8 *)edid, do_cvt_mode, &closure);
    }

    /* XXX should also look for CVT codes in VTB blocks */

    return closure.modes;
}

static void
do_detailed_mode(struct detailed_timing *timing, void *c)
{
    struct detailed_mode_closure *closure = c;
    struct drm_display_mode *newmode;

    if (timing->pixel_clock) {
        newmode = drm_mode_detailed(closure->connector->dev,
                                    closure->edid, timing,
                                    closure->quirks);
        if (!newmode) {
            return;
        }

        if (closure->preferred) {
            newmode->type |= DRM_MODE_TYPE_PREFERRED;
        }

        drm_mode_probed_add(closure->connector, newmode);
        closure->modes++;
        closure->preferred = 0;
    }
}

/*
 * add_detailed_modes - Add modes from detailed timings
 * @connector: attached connector
 * @edid: EDID block to scan
 * @quirks: quirks to apply
 */
static int
add_detailed_modes(struct drm_connector *connector, struct edid *edid,
                   u32 quirks)
{
    struct detailed_mode_closure closure = {
        .connector = connector,
        .edid = edid,
        .preferred = 1,
        .quirks = quirks,
    };

    if (closure.preferred && !version_greater(edid, 1, 3))
        closure.preferred =
            (edid->features & DRM_EDID_FEATURE_PREFERRED_TIMING);

    drm_for_each_detailed_block((u8 *)edid, do_detailed_mode, &closure);

    return closure.modes;
}

#define AUDIO_BLOCK	0x01
#define VIDEO_BLOCK     0x02
#define VENDOR_BLOCK    0x03
#define SPEAKER_BLOCK	0x04
#define VIDEO_CAPABILITY_BLOCK	0x07
#define EDID_BASIC_AUDIO	(1 << 6)
#define EDID_CEA_YCRCB444	(1 << 5)
#define EDID_CEA_YCRCB422	(1 << 4)
#define EDID_CEA_VCDB_QS	(1 << 6)

/*
 * Search EDID for CEA extension block.
 */
static u8 *drm_find_edid_extension(struct edid *edid, int ext_id)
{
    u8 *edid_ext = NULL;
    int i;

    /* No EDID or EDID extensions */
    if (edid == NULL || edid->extensions == 0) {
        return NULL;
    }

    /* Find CEA extension */
    for (i = 0; i < edid->extensions; i++) {
        edid_ext = (u8 *)edid + EDID_LENGTH * (i + 1);
        if (edid_ext[0] == ext_id) {
            break;
        }
    }

    if (i == edid->extensions) {
        return NULL;
    }

    return edid_ext;
}

static u8 *drm_find_cea_extension(struct edid *edid)
{
    return drm_find_edid_extension(edid, CEA_EXT);
}

static u8 *drm_find_displayid_extension(struct edid *edid)
{
    return drm_find_edid_extension(edid, DISPLAYID_EXT);
}

/*
 * Calculate the alternate clock for the CEA mode
 * (60Hz vs. 59.94Hz etc.)
 */
static unsigned int
cea_mode_alternate_clock(const struct drm_display_mode *cea_mode)
{
    unsigned int clock = cea_mode->clock;

    if (cea_mode->vrefresh % 6 != 0) {
        return clock;
    }

    /*
     * edid_cea_modes contains the 59.94Hz
     * variant for 240 and 480 line modes,
     * and the 60Hz variant otherwise.
     */
    if (cea_mode->vdisplay == 240 || cea_mode->vdisplay == 480) {
        clock = clock * 1001 / 1000;
    } else {
        clock = DIV_ROUND_UP(clock * 1000, 1001);
    }

    return clock;
}

/**
 * drm_match_cea_mode - look for a CEA mode matching given mode
 * @to_match: display mode
 *
 * Return: The CEA Video ID (VIC) of the mode or 0 if it isn't a CEA-861
 * mode.
 */
u8 drm_match_cea_mode(const struct drm_display_mode *to_match)
{
    u8 mode;

    if (!to_match->clock) {
        return 0;
    }

    for (mode = 0; mode < ARRAY_SIZE(edid_cea_modes); mode++) {
        const struct drm_display_mode *cea_mode = &edid_cea_modes[mode];
        unsigned int clock1, clock2;

        /* Check both 60Hz and 59.94Hz */
        clock1 = cea_mode->clock;
        clock2 = cea_mode_alternate_clock(cea_mode);

        if ((KHZ2PICOS(to_match->clock) == KHZ2PICOS(clock1) ||
             KHZ2PICOS(to_match->clock) == KHZ2PICOS(clock2)) &&
            drm_mode_equal_no_clocks_no_stereo(to_match, cea_mode)) {
            return mode + 1;
        }
    }
    return 0;
}
EXPORT_SYMBOL(drm_match_cea_mode);

/**
 * drm_get_cea_aspect_ratio - get the picture aspect ratio corresponding to
 * the input VIC from the CEA mode list
 * @video_code: ID given to each of the CEA modes
 *
 * Returns picture aspect ratio
 */
enum hdmi_picture_aspect drm_get_cea_aspect_ratio(const u8 video_code)
{
    /* return picture aspect ratio for video_code - 1 to access the
     * right array element
    */
    return edid_cea_modes[video_code-1].picture_aspect_ratio;
}
EXPORT_SYMBOL(drm_get_cea_aspect_ratio);

/*
 * Calculate the alternate clock for HDMI modes (those from the HDMI vendor
 * specific block).
 *
 * It's almost like cea_mode_alternate_clock(), we just need to add an
 * exception for the VIC 4 mode (4096x2160@24Hz): no alternate clock for this
 * one.
 */
static unsigned int
hdmi_mode_alternate_clock(const struct drm_display_mode *hdmi_mode)
{
    if (hdmi_mode->vdisplay == 4096 && hdmi_mode->hdisplay == 2160) {
        return hdmi_mode->clock;
    }

    return cea_mode_alternate_clock(hdmi_mode);
}

/*
 * drm_match_hdmi_mode - look for a HDMI mode matching given mode
 * @to_match: display mode
 *
 * An HDMI mode is one defined in the HDMI vendor specific block.
 *
 * Returns the HDMI Video ID (VIC) of the mode or 0 if it isn't one.
 */
static u8 drm_match_hdmi_mode(const struct drm_display_mode *to_match)
{
    u8 mode;

    if (!to_match->clock) {
        return 0;
    }

    for (mode = 0; mode < ARRAY_SIZE(edid_4k_modes); mode++) {
        const struct drm_display_mode *hdmi_mode = &edid_4k_modes[mode];
        unsigned int clock1, clock2;

        /* Make sure to also match alternate clocks */
        clock1 = hdmi_mode->clock;
        clock2 = hdmi_mode_alternate_clock(hdmi_mode);

        if ((KHZ2PICOS(to_match->clock) == KHZ2PICOS(clock1) ||
             KHZ2PICOS(to_match->clock) == KHZ2PICOS(clock2)) &&
            drm_mode_equal_no_clocks_no_stereo(to_match, hdmi_mode)) {
            return mode + 1;
        }
    }
    return 0;
}

static int
add_alternate_cea_modes(struct drm_connector *connector, struct edid *edid)
{
    struct drm_device *dev = connector->dev;
    struct drm_display_mode *mode, *tmp;
    LIST_HEAD(list);
    int modes = 0;

    /* Don't add CEA modes if the CEA extension block is missing */
    if (!drm_find_cea_extension(edid)) {
        return 0;
    }

    /*
     * Go through all probed modes and create a new mode
     * with the alternate clock for certain CEA modes.
     */
    list_for_each_entry(mode, &connector->probed_modes, head) {
        const struct drm_display_mode *cea_mode = NULL;
        struct drm_display_mode *newmode;
        u8 mode_idx = drm_match_cea_mode(mode) - 1;
        unsigned int clock1, clock2;

        if (mode_idx < ARRAY_SIZE(edid_cea_modes)) {
            cea_mode = &edid_cea_modes[mode_idx];
            clock2 = cea_mode_alternate_clock(cea_mode);
        } else {
            mode_idx = drm_match_hdmi_mode(mode) - 1;
            if (mode_idx < ARRAY_SIZE(edid_4k_modes)) {
                cea_mode = &edid_4k_modes[mode_idx];
                clock2 = hdmi_mode_alternate_clock(cea_mode);
            }
        }

        if (!cea_mode) {
            continue;
        }

        clock1 = cea_mode->clock;

        if (clock1 == clock2) {
            continue;
        }

        if (mode->clock != clock1 && mode->clock != clock2) {
            continue;
        }

        newmode = drm_mode_duplicate(dev, cea_mode);
        if (!newmode) {
            continue;
        }

        /* Carry over the stereo flags */
        newmode->flags |= mode->flags & DRM_MODE_FLAG_3D_MASK;

        /*
         * The current mode could be either variant. Make
         * sure to pick the "other" clock for the new mode.
         */
        if (mode->clock != clock1) {
            newmode->clock = clock1;
        } else {
            newmode->clock = clock2;
        }

        list_add_tail(&newmode->head, &list);
    }

    list_for_each_entry_safe(mode, tmp, &list, head) {
        list_del(&mode->head);
        drm_mode_probed_add(connector, mode);
        modes++;
    }

    return modes;
}

static struct drm_display_mode *
drm_display_mode_from_vic_index(struct drm_connector *connector,
                                const u8 *video_db, u8 video_len,
                                u8 video_index)
{
    struct drm_device *dev = connector->dev;
    struct drm_display_mode *newmode;
    u8 cea_mode;

    if (video_db == NULL || video_index >= video_len) {
        return NULL;
    }

    /* CEA modes are numbered 1..127 */
    cea_mode = (video_db[video_index] & 127) - 1;
    if (cea_mode >= ARRAY_SIZE(edid_cea_modes)) {
        return NULL;
    }

    newmode = drm_mode_duplicate(dev, &edid_cea_modes[cea_mode]);
    if (!newmode) {
        return NULL;
    }

    newmode->vrefresh = 0;

    return newmode;
}

static int
do_cea_modes(struct drm_connector *connector, const u8 *db, u8 len)
{
    int i, modes = 0;

    for (i = 0; i < len; i++) {
        struct drm_display_mode *mode;
        mode = drm_display_mode_from_vic_index(connector, db, len, i);
        if (mode) {
            drm_mode_probed_add(connector, mode);
            modes++;
        }
    }

    return modes;
}

struct stereo_mandatory_mode {
    int width, height, vrefresh;
    unsigned int flags;
};

static const struct stereo_mandatory_mode stereo_mandatory_modes[] = {
    { 1920, 1080, 24, DRM_MODE_FLAG_3D_TOP_AND_BOTTOM },
    { 1920, 1080, 24, DRM_MODE_FLAG_3D_FRAME_PACKING },
    {
        1920, 1080, 50,
        DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF
    },
    {
        1920, 1080, 60,
        DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF
    },
    { 1280, 720,  50, DRM_MODE_FLAG_3D_TOP_AND_BOTTOM },
    { 1280, 720,  50, DRM_MODE_FLAG_3D_FRAME_PACKING },
    { 1280, 720,  60, DRM_MODE_FLAG_3D_TOP_AND_BOTTOM },
    { 1280, 720,  60, DRM_MODE_FLAG_3D_FRAME_PACKING }
};

static bool
stereo_match_mandatory(const struct drm_display_mode *mode,
                       const struct stereo_mandatory_mode *stereo_mode)
{
    unsigned int interlaced = mode->flags & DRM_MODE_FLAG_INTERLACE;

    return mode->hdisplay == stereo_mode->width &&
           mode->vdisplay == stereo_mode->height &&
           interlaced == (stereo_mode->flags & DRM_MODE_FLAG_INTERLACE) &&
           drm_mode_vrefresh(mode) == stereo_mode->vrefresh;
}

static int add_hdmi_mandatory_stereo_modes(struct drm_connector *connector)
{
    struct drm_device *dev = connector->dev;
    const struct drm_display_mode *mode;
    struct list_head stereo_modes;
    int modes = 0, i;

    INIT_LIST_HEAD(&stereo_modes);

    list_for_each_entry(mode, &connector->probed_modes, head) {
        for (i = 0; i < ARRAY_SIZE(stereo_mandatory_modes); i++) {
            const struct stereo_mandatory_mode *mandatory;
            struct drm_display_mode *new_mode;

            if (!stereo_match_mandatory(mode,
                                        &stereo_mandatory_modes[i])) {
                continue;
            }

            mandatory = &stereo_mandatory_modes[i];
            new_mode = drm_mode_duplicate(dev, mode);
            if (!new_mode) {
                continue;
            }

            new_mode->flags |= mandatory->flags;
            list_add_tail(&new_mode->head, &stereo_modes);
            modes++;
        }
    }

    list_splice_tail(&stereo_modes, &connector->probed_modes);

    return modes;
}

static int add_hdmi_mode(struct drm_connector *connector, u8 vic)
{
    struct drm_device *dev = connector->dev;
    struct drm_display_mode *newmode;

    vic--; /* VICs start at 1 */
    if (vic >= ARRAY_SIZE(edid_4k_modes)) {
        DRM_ERROR("Unknown HDMI VIC: %d\n", vic);
        return 0;
    }

    newmode = drm_mode_duplicate(dev, &edid_4k_modes[vic]);
    if (!newmode) {
        return 0;
    }

    drm_mode_probed_add(connector, newmode);

    return 1;
}

static int add_3d_struct_modes(struct drm_connector *connector, u16 structure,
                               const u8 *video_db, u8 video_len, u8 video_index)
{
    struct drm_display_mode *newmode;
    int modes = 0;

    if (structure & (1 << 0)) {
        newmode = drm_display_mode_from_vic_index(connector, video_db,
                  video_len,
                  video_index);
        if (newmode) {
            newmode->flags |= DRM_MODE_FLAG_3D_FRAME_PACKING;
            drm_mode_probed_add(connector, newmode);
            modes++;
        }
    }
    if (structure & (1 << 6)) {
        newmode = drm_display_mode_from_vic_index(connector, video_db,
                  video_len,
                  video_index);
        if (newmode) {
            newmode->flags |= DRM_MODE_FLAG_3D_TOP_AND_BOTTOM;
            drm_mode_probed_add(connector, newmode);
            modes++;
        }
    }
    if (structure & (1 << 8)) {
        newmode = drm_display_mode_from_vic_index(connector, video_db,
                  video_len,
                  video_index);
        if (newmode) {
            newmode->flags |= DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF;
            drm_mode_probed_add(connector, newmode);
            modes++;
        }
    }

    return modes;
}

/*
 * do_hdmi_vsdb_modes - Parse the HDMI Vendor Specific data block
 * @connector: connector corresponding to the HDMI sink
 * @db: start of the CEA vendor specific block
 * @len: length of the CEA block payload, ie. one can access up to db[len]
 *
 * Parses the HDMI VSDB looking for modes to add to @connector. This function
 * also adds the stereo 3d modes when applicable.
 */
static int
do_hdmi_vsdb_modes(struct drm_connector *connector, const u8 *db, u8 len,
                   const u8 *video_db, u8 video_len)
{
    int modes = 0, offset = 0, i, multi_present = 0, multi_len;
    u8 vic_len, hdmi_3d_len = 0;
    u16 mask;
    u16 structure_all;

    if (len < 8) {
        goto out;
    }

    /* no HDMI_Video_Present */
    if (!(db[8] & (1 << 5))) {
        goto out;
    }

    /* Latency_Fields_Present */
    if (db[8] & (1 << 7)) {
        offset += 2;
    }

    /* I_Latency_Fields_Present */
    if (db[8] & (1 << 6)) {
        offset += 2;
    }

    /* the declared length is not long enough for the 2 first bytes
     * of additional video format capabilities */
    if (len < (8 + offset + 2)) {
        goto out;
    }

    /* 3D_Present */
    offset++;
    if (db[8 + offset] & (1 << 7)) {
        modes += add_hdmi_mandatory_stereo_modes(connector);

        /* 3D_Multi_present */
        multi_present = (db[8 + offset] & 0x60) >> 5;
    }

    offset++;
    vic_len = db[8 + offset] >> 5;
    hdmi_3d_len = db[8 + offset] & 0x1f;

    for (i = 0; i < vic_len && len >= (9 + offset + i); i++) {
        u8 vic;

        vic = db[9 + offset + i];
        modes += add_hdmi_mode(connector, vic);
    }
    offset += 1 + vic_len;

    if (multi_present == 1) {
        multi_len = 2;
    } else if (multi_present == 2) {
        multi_len = 4;
    } else {
        multi_len = 0;
    }

    if (len < (8 + offset + hdmi_3d_len - 1)) {
        goto out;
    }

    if (hdmi_3d_len < multi_len) {
        goto out;
    }

    if (multi_present == 1 || multi_present == 2) {
        /* 3D_Structure_ALL */
        structure_all = (db[8 + offset] << 8) | db[9 + offset];

        /* check if 3D_MASK is present */
        if (multi_present == 2) {
            mask = (db[10 + offset] << 8) | db[11 + offset];
        } else {
            mask = 0xffff;
        }

        for (i = 0; i < 16; i++) {
            if (mask & (1 << i))
                modes += add_3d_struct_modes(connector,
                                             structure_all,
                                             video_db,
                                             video_len, i);
        }
    }

    offset += multi_len;

    for (i = 0; i < (hdmi_3d_len - multi_len); i++) {
        int vic_index;
        struct drm_display_mode *newmode = NULL;
        unsigned int newflag = 0;
        bool detail_present;

        detail_present = ((db[8 + offset + i] & 0x0f) > 7);

        if (detail_present && (i + 1 == hdmi_3d_len - multi_len)) {
            break;
        }

        /* 2D_VIC_order_X */
        vic_index = db[8 + offset + i] >> 4;

        /* 3D_Structure_X */
        switch (db[8 + offset + i] & 0x0f) {
        case 0:
            newflag = DRM_MODE_FLAG_3D_FRAME_PACKING;
            break;
        case 6:
            newflag = DRM_MODE_FLAG_3D_TOP_AND_BOTTOM;
            break;
        case 8:
            /* 3D_Detail_X */
            if ((db[9 + offset + i] >> 4) == 1) {
                newflag = DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF;
            }
            break;
        }

        if (newflag != 0) {
            newmode = drm_display_mode_from_vic_index(connector,
                      video_db,
                      video_len,
                      vic_index);

            if (newmode) {
                newmode->flags |= newflag;
                drm_mode_probed_add(connector, newmode);
                modes++;
            }
        }

        if (detail_present) {
            i++;
        }
    }

out:
    return modes;
}

static int
cea_db_payload_len(const u8 *db)
{
    return db[0] & 0x1f;
}

static int
cea_db_tag(const u8 *db)
{
    return db[0] >> 5;
}

static int
cea_revision(const u8 *cea)
{
    return cea[1];
}

static int
cea_db_offsets(const u8 *cea, int *start, int *end)
{
    /* Data block offset in CEA extension block */
    *start = 4;
    *end = cea[2];
    if (*end == 0) {
        *end = 127;
    }
    if (*end < 4 || *end > 127) {
        return -ERANGE;
    }
    return 0;
}

static bool cea_db_is_hdmi_vsdb(const u8 *db)
{
    int hdmi_id;

    if (cea_db_tag(db) != VENDOR_BLOCK) {
        return false;
    }

    if (cea_db_payload_len(db) < 5) {
        return false;
    }

    hdmi_id = db[1] | (db[2] << 8) | (db[3] << 16);

    return hdmi_id == HDMI_IEEE_OUI;
}

#define for_each_cea_db(cea, i, start, end) \
	for ((i) = (start); (i) < (end) && (i) + cea_db_payload_len(&(cea)[(i)]) < (end); (i) += cea_db_payload_len(&(cea)[(i)]) + 1)

static int
add_cea_modes(struct drm_connector *connector, struct edid *edid)
{
    const u8 *cea = drm_find_cea_extension(edid);
    const u8 *db, *hdmi = NULL, *video = NULL;
    u8 dbl, hdmi_len, video_len = 0;
    int modes = 0;

    if (cea && cea_revision(cea) >= 3) {
        int i, start, end;

        if (cea_db_offsets(cea, &start, &end)) {
            return 0;
        }

        for_each_cea_db(cea, i, start, end) {
            db = &cea[i];
            dbl = cea_db_payload_len(db);

            if (cea_db_tag(db) == VIDEO_BLOCK) {
                video = db + 1;
                video_len = dbl;
                modes += do_cea_modes(connector, video, dbl);
            } else if (cea_db_is_hdmi_vsdb(db)) {
                hdmi = db;
                hdmi_len = dbl;
            }
        }
    }

    /*
     * We parse the HDMI VSDB after having added the cea modes as we will
     * be patching their flags when the sink supports stereo 3D.
     */
    if (hdmi)
        modes += do_hdmi_vsdb_modes(connector, hdmi, hdmi_len, video,
                                    video_len);

    return modes;
}

static void
parse_hdmi_vsdb(struct drm_connector *connector, const u8 *db)
{
    u8 len = cea_db_payload_len(db);

    if (len >= 6) {
        connector->eld[5] |= (db[6] >> 7) << 1;  /* Supports_AI */
        connector->dvi_dual = db[6] & 1;
    }
    if (len >= 7) {
        connector->max_tmds_clock = db[7] * 5;
    }
    if (len >= 8) {
        connector->latency_present[0] = db[8] >> 7;
        connector->latency_present[1] = (db[8] >> 6) & 1;
    }
    if (len >= 9) {
        connector->video_latency[0] = db[9];
    }
    if (len >= 10) {
        connector->audio_latency[0] = db[10];
    }
    if (len >= 11) {
        connector->video_latency[1] = db[11];
    }
    if (len >= 12) {
        connector->audio_latency[1] = db[12];
    }

    DRM_DEBUG_KMS("HDMI: DVI dual %d, "
                  "max TMDS clock %d, "
                  "latency present %d %d, "
                  "video latency %d %d, "
                  "audio latency %d %d\n",
                  connector->dvi_dual,
                  connector->max_tmds_clock,
                  (int) connector->latency_present[0],
                  (int) connector->latency_present[1],
                  connector->video_latency[0],
                  connector->video_latency[1],
                  connector->audio_latency[0],
                  connector->audio_latency[1]);
}

static void
monitor_name(struct detailed_timing *t, void *data)
{
    if (t->data.other_data.type == EDID_DETAIL_MONITOR_NAME) {
        *(u8 **)data = t->data.other_data.data.str.str;
    }
}

/**
 * drm_edid_to_eld - build ELD from EDID
 * @connector: connector corresponding to the HDMI/DP sink
 * @edid: EDID to parse
 *
 * Fill the ELD (EDID-Like Data) buffer for passing to the audio driver. The
 * Conn_Type, HDCP and Port_ID ELD fields are left for the graphics driver to
 * fill in.
 */
void drm_edid_to_eld(struct drm_connector *connector, struct edid *edid)
{
    uint8_t *eld = connector->eld;
    u8 *cea;
    u8 *name;
    u8 *db;
    int sad_count = 0;
    int mnl;
    int dbl;

    memset(eld, 0, sizeof(connector->eld));

    cea = drm_find_cea_extension(edid);
    if (!cea) {
        DRM_DEBUG_KMS("ELD: no CEA Extension found\n");
        return;
    }

    name = NULL;
    drm_for_each_detailed_block((u8 *)edid, monitor_name, &name);
    for (mnl = 0; name && mnl < 13; mnl++) {
        if (name[mnl] == 0x0a) {
            break;
        }
        eld[20 + mnl] = name[mnl];
    }
    eld[4] = (cea[1] << 5) | mnl;
    DRM_DEBUG_KMS("ELD monitor %s\n", eld + 20);

    eld[0] = 2 << 3;		/* ELD version: 2 */

    eld[16] = edid->mfg_id[0];
    eld[17] = edid->mfg_id[1];
    eld[18] = edid->prod_code[0];
    eld[19] = edid->prod_code[1];

    if (cea_revision(cea) >= 3) {
        int i, start, end;

        if (cea_db_offsets(cea, &start, &end)) {
            start = 0;
            end = 0;
        }

        for_each_cea_db(cea, i, start, end) {
            db = &cea[i];
            dbl = cea_db_payload_len(db);

            switch (cea_db_tag(db)) {
            case AUDIO_BLOCK:
                /* Audio Data Block, contains SADs */
                sad_count = dbl / 3;
                if (dbl >= 1) {
                    memcpy(eld + 20 + mnl, &db[1], dbl);
                }
                break;
            case SPEAKER_BLOCK:
                /* Speaker Allocation Data Block */
                if (dbl >= 1) {
                    eld[7] = db[1];
                }
                break;
            case VENDOR_BLOCK:
                /* HDMI Vendor-Specific Data Block */
                if (cea_db_is_hdmi_vsdb(db)) {
                    parse_hdmi_vsdb(connector, db);
                }
                break;
            default:
                break;
            }
        }
    }
    eld[5] |= sad_count << 4;

    eld[DRM_ELD_BASELINE_ELD_LEN] =
        DIV_ROUND_UP(drm_eld_calc_baseline_block_size(eld), 4);

    DRM_DEBUG_KMS("ELD size %d, SAD count %d\n",
                  drm_eld_size(eld), sad_count);
}
EXPORT_SYMBOL(drm_edid_to_eld);

/**
 * drm_edid_to_sad - extracts SADs from EDID
 * @edid: EDID to parse
 * @sads: pointer that will be set to the extracted SADs
 *
 * Looks for CEA EDID block and extracts SADs (Short Audio Descriptors) from it.
 *
 * Note: The returned pointer needs to be freed using kfree().
 *
 * Return: The number of found SADs or negative number on error.
 */
int drm_edid_to_sad(struct edid *edid, struct cea_sad **sads)
{
    int count = 0;
    int i, start, end, dbl;
    u8 *cea;

    cea = drm_find_cea_extension(edid);
    if (!cea) {
        DRM_DEBUG_KMS("SAD: no CEA Extension found\n");
        return -ENOENT;
    }

    if (cea_revision(cea) < 3) {
        DRM_DEBUG_KMS("SAD: wrong CEA revision\n");
        return -ENOTSUPP;
    }

    if (cea_db_offsets(cea, &start, &end)) {
        DRM_DEBUG_KMS("SAD: invalid data block offsets\n");
        return -EPROTO;
    }

    for_each_cea_db(cea, i, start, end) {
        u8 *db = &cea[i];

        if (cea_db_tag(db) == AUDIO_BLOCK) {
            int j;
            dbl = cea_db_payload_len(db);

            count = dbl / 3; /* SAD is 3B */
            *sads = kcalloc(count, sizeof(**sads), GFP_KERNEL);
            if (!*sads) {
                return -ENOMEM;
            }
            for (j = 0; j < count; j++) {
                u8 *sad = &db[1 + j * 3];

                (*sads)[j].format = (sad[0] & 0x78) >> 3;
                (*sads)[j].channels = sad[0] & 0x7;
                (*sads)[j].freq = sad[1] & 0x7F;
                (*sads)[j].byte2 = sad[2];
            }
            break;
        }
    }

    return count;
}
EXPORT_SYMBOL(drm_edid_to_sad);

/**
 * drm_edid_to_speaker_allocation - extracts Speaker Allocation Data Blocks from EDID
 * @edid: EDID to parse
 * @sadb: pointer to the speaker block
 *
 * Looks for CEA EDID block and extracts the Speaker Allocation Data Block from it.
 *
 * Note: The returned pointer needs to be freed using kfree().
 *
 * Return: The number of found Speaker Allocation Blocks or negative number on
 * error.
 */
int drm_edid_to_speaker_allocation(struct edid *edid, u8 **sadb)
{
    int count = 0;
    int i, start, end, dbl;
    const u8 *cea;

    cea = drm_find_cea_extension(edid);
    if (!cea) {
        DRM_DEBUG_KMS("SAD: no CEA Extension found\n");
        return -ENOENT;
    }

    if (cea_revision(cea) < 3) {
        DRM_DEBUG_KMS("SAD: wrong CEA revision\n");
        return -ENOTSUPP;
    }

    if (cea_db_offsets(cea, &start, &end)) {
        DRM_DEBUG_KMS("SAD: invalid data block offsets\n");
        return -EPROTO;
    }

    for_each_cea_db(cea, i, start, end) {
        const u8 *db = &cea[i];

        if (cea_db_tag(db) == SPEAKER_BLOCK) {
            dbl = cea_db_payload_len(db);

            /* Speaker Allocation Data Block */
            if (dbl == 3) {
                *sadb = kmemdup(&db[1], dbl, GFP_KERNEL);
                if (!*sadb) {
                    return -ENOMEM;
                }
                count = dbl;
                break;
            }
        }
    }

    return count;
}
EXPORT_SYMBOL(drm_edid_to_speaker_allocation);

/**
 * drm_av_sync_delay - compute the HDMI/DP sink audio-video sync delay
 * @connector: connector associated with the HDMI/DP sink
 * @mode: the display mode
 *
 * Return: The HDMI/DP sink's audio-video sync delay in milliseconds or 0 if
 * the sink doesn't support audio or video.
 */
int drm_av_sync_delay(struct drm_connector *connector,
                      struct drm_display_mode *mode)
{
    int i = !!(mode->flags & DRM_MODE_FLAG_INTERLACE);
    int a, v;

    if (!connector->latency_present[0]) {
        return 0;
    }
    if (!connector->latency_present[1]) {
        i = 0;
    }

    a = connector->audio_latency[i];
    v = connector->video_latency[i];

    /*
     * HDMI/DP sink doesn't support audio or video?
     */
    if (a == 255 || v == 255) {
        return 0;
    }

    /*
     * Convert raw EDID values to millisecond.
     * Treat unknown latency as 0ms.
     */
    if (a) {
        a = min(2 * (a - 1), 500);
    }
    if (v) {
        v = min(2 * (v - 1), 500);
    }

    return max(v - a, 0);
}
EXPORT_SYMBOL(drm_av_sync_delay);

/**
 * drm_select_eld - select one ELD from multiple HDMI/DP sinks
 * @encoder: the encoder just changed display mode
 * @mode: the adjusted display mode
 *
 * It's possible for one encoder to be associated with multiple HDMI/DP sinks.
 * The policy is now hard coded to simply use the first HDMI/DP sink's ELD.
 *
 * Return: The connector associated with the first HDMI/DP sink that has ELD
 * attached to it.
 */
struct drm_connector *drm_select_eld(struct drm_encoder *encoder,
                                     struct drm_display_mode *mode)
{
    struct drm_connector *connector;
    struct drm_device *dev = encoder->dev;

    WARN_ON(!mutex_is_locked(&dev->mode_config.mutex));
    WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));

    list_for_each_entry(connector, &dev->mode_config.connector_list, head)
    if (connector->encoder == encoder && connector->eld[0]) {
        return connector;
    }

    return NULL;
}
EXPORT_SYMBOL(drm_select_eld);

/**
 * drm_detect_hdmi_monitor - detect whether monitor is HDMI
 * @edid: monitor EDID information
 *
 * Parse the CEA extension according to CEA-861-B.
 *
 * Return: True if the monitor is HDMI, false if not or unknown.
 */
bool drm_detect_hdmi_monitor(struct edid *edid)
{
    u8 *edid_ext;
    int i;
    int start_offset, end_offset;

    edid_ext = drm_find_cea_extension(edid);
    if (!edid_ext) {
        return false;
    }

    if (cea_db_offsets(edid_ext, &start_offset, &end_offset)) {
        return false;
    }

    /*
     * Because HDMI identifier is in Vendor Specific Block,
     * search it from all data blocks of CEA extension.
     */
    for_each_cea_db(edid_ext, i, start_offset, end_offset) {
        if (cea_db_is_hdmi_vsdb(&edid_ext[i])) {
            return true;
        }
    }

    return false;
}
EXPORT_SYMBOL(drm_detect_hdmi_monitor);

/**
 * drm_detect_monitor_audio - check monitor audio capability
 * @edid: EDID block to scan
 *
 * Monitor should have CEA extension block.
 * If monitor has 'basic audio', but no CEA audio blocks, it's 'basic
 * audio' only. If there is any audio extension block and supported
 * audio format, assume at least 'basic audio' support, even if 'basic
 * audio' is not defined in EDID.
 *
 * Return: True if the monitor supports audio, false otherwise.
 */
bool drm_detect_monitor_audio(struct edid *edid)
{
    u8 *edid_ext;
    int i, j;
    bool has_audio = false;
    int start_offset, end_offset;

    edid_ext = drm_find_cea_extension(edid);
    if (!edid_ext) {
        goto end;
    }

    has_audio = ((edid_ext[3] & EDID_BASIC_AUDIO) != 0);

    if (has_audio) {
        DRM_DEBUG_KMS("Monitor has basic audio support\n");
        goto end;
    }

    if (cea_db_offsets(edid_ext, &start_offset, &end_offset)) {
        goto end;
    }

    for_each_cea_db(edid_ext, i, start_offset, end_offset) {
        if (cea_db_tag(&edid_ext[i]) == AUDIO_BLOCK) {
            has_audio = true;
            for (j = 1; j < cea_db_payload_len(&edid_ext[i]) + 1; j += 3)
                DRM_DEBUG_KMS("CEA audio format %d\n",
                              (edid_ext[i + j] >> 3) & 0xf);
            goto end;
        }
    }
end:
    return has_audio;
}
EXPORT_SYMBOL(drm_detect_monitor_audio);

/**
 * drm_rgb_quant_range_selectable - is RGB quantization range selectable?
 * @edid: EDID block to scan
 *
 * Check whether the monitor reports the RGB quantization range selection
 * as supported. The AVI infoframe can then be used to inform the monitor
 * which quantization range (full or limited) is used.
 *
 * Return: True if the RGB quantization range is selectable, false otherwise.
 */
bool drm_rgb_quant_range_selectable(struct edid *edid)
{
    u8 *edid_ext;
    int i, start, end;

    edid_ext = drm_find_cea_extension(edid);
    if (!edid_ext) {
        return false;
    }

    if (cea_db_offsets(edid_ext, &start, &end)) {
        return false;
    }

    for_each_cea_db(edid_ext, i, start, end) {
        if (cea_db_tag(&edid_ext[i]) == VIDEO_CAPABILITY_BLOCK &&
            cea_db_payload_len(&edid_ext[i]) == 2) {
            DRM_DEBUG_KMS("CEA VCDB 0x%02x\n", edid_ext[i + 2]);
            return edid_ext[i + 2] & EDID_CEA_VCDB_QS;
        }
    }

    return false;
}
EXPORT_SYMBOL(drm_rgb_quant_range_selectable);

/**
 * drm_assign_hdmi_deep_color_info - detect whether monitor supports
 * hdmi deep color modes and update drm_display_info if so.
 * @edid: monitor EDID information
 * @info: Updated with maximum supported deep color bpc and color format
 *        if deep color supported.
 * @connector: DRM connector, used only for debug output
 *
 * Parse the CEA extension according to CEA-861-B.
 * Return true if HDMI deep color supported, false if not or unknown.
 */
static bool drm_assign_hdmi_deep_color_info(struct edid *edid,
        struct drm_display_info *info,
        struct drm_connector *connector)
{
    u8 *edid_ext, *hdmi;
    int i;
    int start_offset, end_offset;
    unsigned int dc_bpc = 0;

    edid_ext = drm_find_cea_extension(edid);
    if (!edid_ext) {
        return false;
    }

    if (cea_db_offsets(edid_ext, &start_offset, &end_offset)) {
        return false;
    }

    /*
     * Because HDMI identifier is in Vendor Specific Block,
     * search it from all data blocks of CEA extension.
     */
    for_each_cea_db(edid_ext, i, start_offset, end_offset) {
        if (cea_db_is_hdmi_vsdb(&edid_ext[i])) {
            /* HDMI supports at least 8 bpc */
            info->bpc = 8;

            hdmi = &edid_ext[i];
            if (cea_db_payload_len(hdmi) < 6) {
                return false;
            }

            if (hdmi[6] & DRM_EDID_HDMI_DC_30) {
                dc_bpc = 10;
                info->edid_hdmi_dc_modes |= DRM_EDID_HDMI_DC_30;
                DRM_DEBUG("%s: HDMI sink does deep color 30.\n",
                          connector->name);
            }

            if (hdmi[6] & DRM_EDID_HDMI_DC_36) {
                dc_bpc = 12;
                info->edid_hdmi_dc_modes |= DRM_EDID_HDMI_DC_36;
                DRM_DEBUG("%s: HDMI sink does deep color 36.\n",
                          connector->name);
            }

            if (hdmi[6] & DRM_EDID_HDMI_DC_48) {
                dc_bpc = 16;
                info->edid_hdmi_dc_modes |= DRM_EDID_HDMI_DC_48;
                DRM_DEBUG("%s: HDMI sink does deep color 48.\n",
                          connector->name);
            }

            if (dc_bpc > 0) {
                DRM_DEBUG("%s: Assigning HDMI sink color depth as %d bpc.\n",
                          connector->name, dc_bpc);
                info->bpc = dc_bpc;

                /*
                 * Deep color support mandates RGB444 support for all video
                 * modes and forbids YCRCB422 support for all video modes per
                 * HDMI 1.3 spec.
                 */
                info->color_formats = DRM_COLOR_FORMAT_RGB444;

                /* YCRCB444 is optional according to spec. */
                if (hdmi[6] & DRM_EDID_HDMI_DC_Y444) {
                    info->color_formats |= DRM_COLOR_FORMAT_YCRCB444;
                    DRM_DEBUG("%s: HDMI sink does YCRCB444 in deep color.\n",
                              connector->name);
                }

                /*
                 * Spec says that if any deep color mode is supported at all,
                 * then deep color 36 bit must be supported.
                 */
                if (!(hdmi[6] & DRM_EDID_HDMI_DC_36)) {
                    DRM_DEBUG("%s: HDMI sink should do DC_36, but does not!\n",
                              connector->name);
                }

                return true;
            } else {
                DRM_DEBUG("%s: No deep color support on this HDMI sink.\n",
                          connector->name);
            }
        }
    }

    return false;
}

/**
 * drm_add_display_info - pull display info out if present
 * @edid: EDID data
 * @info: display info (attached to connector)
 * @connector: connector whose edid is used to build display info
 *
 * Grab any available display info and stuff it into the drm_display_info
 * structure that's part of the connector.  Useful for tracking bpp and
 * color spaces.
 */
static void drm_add_display_info(struct edid *edid,
                                 struct drm_display_info *info,
                                 struct drm_connector *connector)
{
    u8 *edid_ext;

    info->width_mm = edid->width_cm * 10;
    info->height_mm = edid->height_cm * 10;

    /* driver figures it out in this case */
    info->bpc = 0;
    info->color_formats = 0;

    if (edid->revision < 3) {
        return;
    }

    if (!(edid->input & DRM_EDID_INPUT_DIGITAL)) {
        return;
    }

    /* Get data from CEA blocks if present */
    edid_ext = drm_find_cea_extension(edid);
    if (edid_ext) {
        info->cea_rev = edid_ext[1];

        /* The existence of a CEA block should imply RGB support */
        info->color_formats = DRM_COLOR_FORMAT_RGB444;
        if (edid_ext[3] & EDID_CEA_YCRCB444) {
            info->color_formats |= DRM_COLOR_FORMAT_YCRCB444;
        }
        if (edid_ext[3] & EDID_CEA_YCRCB422) {
            info->color_formats |= DRM_COLOR_FORMAT_YCRCB422;
        }
    }

    /* HDMI deep color modes supported? Assign to info, if so */
    drm_assign_hdmi_deep_color_info(edid, info, connector);

    /* Only defined for 1.4 with digital displays */
    if (edid->revision < 4) {
        return;
    }

    switch (edid->input & DRM_EDID_DIGITAL_DEPTH_MASK) {
    case DRM_EDID_DIGITAL_DEPTH_6:
        info->bpc = 6;
        break;
    case DRM_EDID_DIGITAL_DEPTH_8:
        info->bpc = 8;
        break;
    case DRM_EDID_DIGITAL_DEPTH_10:
        info->bpc = 10;
        break;
    case DRM_EDID_DIGITAL_DEPTH_12:
        info->bpc = 12;
        break;
    case DRM_EDID_DIGITAL_DEPTH_14:
        info->bpc = 14;
        break;
    case DRM_EDID_DIGITAL_DEPTH_16:
        info->bpc = 16;
        break;
    case DRM_EDID_DIGITAL_DEPTH_UNDEF:
    default:
        info->bpc = 0;
        break;
    }

    DRM_DEBUG("%s: Assigning EDID-1.4 digital sink color depth as %d bpc.\n",
              connector->name, info->bpc);

    info->color_formats |= DRM_COLOR_FORMAT_RGB444;
    if (edid->features & DRM_EDID_FEATURE_RGB_YCRCB444) {
        info->color_formats |= DRM_COLOR_FORMAT_YCRCB444;
    }
    if (edid->features & DRM_EDID_FEATURE_RGB_YCRCB422) {
        info->color_formats |= DRM_COLOR_FORMAT_YCRCB422;
    }
}

/**
 * drm_add_edid_modes - add modes from EDID data, if available
 * @connector: connector we're probing
 * @edid: EDID data
 *
 * Add the specified modes to the connector's mode list.
 *
 * Return: The number of modes added or 0 if we couldn't find any.
 */
int drm_add_edid_modes(struct drm_connector *connector, struct edid *edid)
{
    int num_modes = 0;
    u32 quirks;

    if (edid == NULL) {
        return 0;
    }
    if (!drm_edid_is_valid(edid)) {
        dev_warn(connector->dev->dev, "%s: EDID invalid.\n",
                 connector->name);
        return 0;
    }

    quirks = edid_get_quirks(edid);

    /*
     * EDID spec says modes should be preferred in this order:
     * - preferred detailed mode
     * - other detailed modes from base block
     * - detailed modes from extension blocks
     * - CVT 3-byte code modes
     * - standard timing codes
     * - established timing codes
     * - modes inferred from GTF or CVT range information
     *
     * We get this pretty much right.
     *
     * XXX order for additional mode types in extension blocks?
     */
    num_modes += add_detailed_modes(connector, edid, quirks);
    num_modes += add_cvt_modes(connector, edid);
    num_modes += add_standard_modes(connector, edid);
    num_modes += add_established_modes(connector, edid);
    if (edid->features & DRM_EDID_FEATURE_DEFAULT_GTF) {
        num_modes += add_inferred_modes(connector, edid);
    }
    num_modes += add_cea_modes(connector, edid);
    num_modes += add_alternate_cea_modes(connector, edid);

    if (quirks & (EDID_QUIRK_PREFER_LARGE_60 | EDID_QUIRK_PREFER_LARGE_75)) {
        edid_fixup_preferred(connector, quirks);
    }

    drm_add_display_info(edid, &connector->display_info, connector);

    if (quirks & EDID_QUIRK_FORCE_8BPC) {
        connector->display_info.bpc = 8;
    }

    if (quirks & EDID_QUIRK_FORCE_12BPC) {
        connector->display_info.bpc = 12;
    }

    return num_modes;
}
EXPORT_SYMBOL(drm_add_edid_modes);

/**
 * drm_add_modes_noedid - add modes for the connectors without EDID
 * @connector: connector we're probing
 * @hdisplay: the horizontal display limit
 * @vdisplay: the vertical display limit
 *
 * Add the specified modes to the connector's mode list. Only when the
 * hdisplay/vdisplay is not beyond the given limit, it will be added.
 *
 * Return: The number of modes added or 0 if we couldn't find any.
 */
int drm_add_modes_noedid(struct drm_connector *connector,
                         int hdisplay, int vdisplay)
{
    int i, count, num_modes = 0;
    struct drm_display_mode *mode;
    struct drm_device *dev = connector->dev;

    count = sizeof(drm_dmt_modes) / sizeof(struct drm_display_mode);
    if (hdisplay < 0) {
        hdisplay = 0;
    }
    if (vdisplay < 0) {
        vdisplay = 0;
    }

    for (i = 0; i < count; i++) {
        const struct drm_display_mode *ptr = &drm_dmt_modes[i];
        if (hdisplay && vdisplay) {
            /*
             * Only when two are valid, they will be used to check
             * whether the mode should be added to the mode list of
             * the connector.
             */
            if (ptr->hdisplay > hdisplay ||
                ptr->vdisplay > vdisplay) {
                continue;
            }
        }
        if (drm_mode_vrefresh(ptr) > 61) {
            continue;
        }
        mode = drm_mode_duplicate(dev, ptr);
        if (mode) {
            drm_mode_probed_add(connector, mode);
            num_modes++;
        }
    }
    return num_modes;
}
EXPORT_SYMBOL(drm_add_modes_noedid);

/**
 * drm_set_preferred_mode - Sets the preferred mode of a connector
 * @connector: connector whose mode list should be processed
 * @hpref: horizontal resolution of preferred mode
 * @vpref: vertical resolution of preferred mode
 *
 * Marks a mode as preferred if it matches the resolution specified by @hpref
 * and @vpref.
 */
void drm_set_preferred_mode(struct drm_connector *connector,
                            int hpref, int vpref)
{
    struct drm_display_mode *mode;

    list_for_each_entry(mode, &connector->probed_modes, head) {
        if (mode->hdisplay == hpref &&
            mode->vdisplay == vpref) {
            mode->type |= DRM_MODE_TYPE_PREFERRED;
        }
    }
}
EXPORT_SYMBOL(drm_set_preferred_mode);

/**
 * drm_hdmi_avi_infoframe_from_display_mode() - fill an HDMI AVI infoframe with
 *                                              data from a DRM display mode
 * @frame: HDMI AVI infoframe
 * @mode: DRM display mode
 *
 * Return: 0 on success or a negative error code on failure.
 */
int
drm_hdmi_avi_infoframe_from_display_mode(struct hdmi_avi_infoframe *frame,
        const struct drm_display_mode *mode)
{
    int err;

    if (!frame || !mode) {
        return -EINVAL;
    }

    err = hdmi_avi_infoframe_init(frame);
    if (err < 0) {
        return err;
    }

    if (mode->flags & DRM_MODE_FLAG_DBLCLK) {
        frame->pixel_repeat = 1;
    }

    frame->video_code = drm_match_cea_mode(mode);

    frame->picture_aspect = HDMI_PICTURE_ASPECT_NONE;

    /*
     * Populate picture aspect ratio from either
     * user input (if specified) or from the CEA mode list.
     */
    if (mode->picture_aspect_ratio == HDMI_PICTURE_ASPECT_4_3 ||
        mode->picture_aspect_ratio == HDMI_PICTURE_ASPECT_16_9) {
        frame->picture_aspect = mode->picture_aspect_ratio;
    } else if (frame->video_code > 0)
        frame->picture_aspect = drm_get_cea_aspect_ratio(
                                    frame->video_code);

    frame->active_aspect = HDMI_ACTIVE_ASPECT_PICTURE;
    frame->scan_mode = HDMI_SCAN_MODE_UNDERSCAN;

    return 0;
}
EXPORT_SYMBOL(drm_hdmi_avi_infoframe_from_display_mode);

static enum hdmi_3d_structure
s3d_structure_from_display_mode(const struct drm_display_mode *mode) {
    u32 layout = mode->flags & DRM_MODE_FLAG_3D_MASK;

    switch (layout)
    {
    case DRM_MODE_FLAG_3D_FRAME_PACKING:
        return HDMI_3D_STRUCTURE_FRAME_PACKING;
    case DRM_MODE_FLAG_3D_FIELD_ALTERNATIVE:
        return HDMI_3D_STRUCTURE_FIELD_ALTERNATIVE;
    case DRM_MODE_FLAG_3D_LINE_ALTERNATIVE:
        return HDMI_3D_STRUCTURE_LINE_ALTERNATIVE;
    case DRM_MODE_FLAG_3D_SIDE_BY_SIDE_FULL:
        return HDMI_3D_STRUCTURE_SIDE_BY_SIDE_FULL;
    case DRM_MODE_FLAG_3D_L_DEPTH:
        return HDMI_3D_STRUCTURE_L_DEPTH;
    case DRM_MODE_FLAG_3D_L_DEPTH_GFX_GFX_DEPTH:
        return HDMI_3D_STRUCTURE_L_DEPTH_GFX_GFX_DEPTH;
    case DRM_MODE_FLAG_3D_TOP_AND_BOTTOM:
        return HDMI_3D_STRUCTURE_TOP_AND_BOTTOM;
    case DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF:
        return HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF;
    default:
        return HDMI_3D_STRUCTURE_INVALID;
    }
}

/**
 * drm_hdmi_vendor_infoframe_from_display_mode() - fill an HDMI infoframe with
 * data from a DRM display mode
 * @frame: HDMI vendor infoframe
 * @mode: DRM display mode
 *
 * Note that there's is a need to send HDMI vendor infoframes only when using a
 * 4k or stereoscopic 3D mode. So when giving any other mode as input this
 * function will return -EINVAL, error that can be safely ignored.
 *
 * Return: 0 on success or a negative error code on failure.
 */
int
drm_hdmi_vendor_infoframe_from_display_mode(struct hdmi_vendor_infoframe *frame,
        const struct drm_display_mode *mode)
{
    int err;
    u32 s3d_flags;
    u8 vic;

    if (!frame || !mode) {
        return -EINVAL;
    }

    vic = drm_match_hdmi_mode(mode);
    s3d_flags = mode->flags & DRM_MODE_FLAG_3D_MASK;

    if (!vic && !s3d_flags) {
        return -EINVAL;
    }

    if (vic && s3d_flags) {
        return -EINVAL;
    }

    err = hdmi_vendor_infoframe_init(frame);
    if (err < 0) {
        return err;
    }

    if (vic) {
        frame->vic = vic;
    } else {
        frame->s3d_struct = s3d_structure_from_display_mode(mode);
    }

    return 0;
}
EXPORT_SYMBOL(drm_hdmi_vendor_infoframe_from_display_mode);

static int drm_parse_display_id(struct drm_connector *connector,
                                u8 *displayid, int length,
                                bool is_edid_extension)
{
    /* if this is an EDID extension the first byte will be 0x70 */
    int idx = 0;
    struct displayid_hdr *base;
    struct displayid_block *block;
    u8 csum = 0;
    int i;

    if (is_edid_extension) {
        idx = 1;
    }

    base = (struct displayid_hdr *)&displayid[idx];

    DRM_DEBUG_KMS("base revision 0x%x, length %d, %d %d\n",
                  base->rev, base->bytes, base->prod_id, base->ext_count);

    if (base->bytes + 5 > length - idx) {
        return -EINVAL;
    }

    for (i = idx; i <= base->bytes + 5; i++) {
        csum += displayid[i];
    }
    if (csum) {
        DRM_ERROR("DisplayID checksum invalid, remainder is %d\n", csum);
        return -EINVAL;
    }

    block = (struct displayid_block *)&displayid[idx + 4];
    DRM_DEBUG_KMS("block id %d, rev %d, len %d\n",
                  block->tag, block->rev, block->num_bytes);

    switch (block->tag) {
    case DATA_BLOCK_TILED_DISPLAY: {
        struct displayid_tiled_block *tile = (struct displayid_tiled_block *)block;

        u16 w, h;
        u8 tile_v_loc, tile_h_loc;
        u8 num_v_tile, num_h_tile;
        struct drm_tile_group *tg;

        w = tile->tile_size[0] | tile->tile_size[1] << 8;
        h = tile->tile_size[2] | tile->tile_size[3] << 8;

        num_v_tile = (tile->topo[0] & 0xf) | (tile->topo[2] & 0x30);
        num_h_tile = (tile->topo[0] >> 4) | ((tile->topo[2] >> 2) & 0x30);
        tile_v_loc = (tile->topo[1] & 0xf) | ((tile->topo[2] & 0x3) << 4);
        tile_h_loc = (tile->topo[1] >> 4) | (((tile->topo[2] >> 2) & 0x3) << 4);

        connector->has_tile = true;
        if (tile->tile_cap & 0x80) {
            connector->tile_is_single_monitor = true;
        }

        connector->num_h_tile = num_h_tile + 1;
        connector->num_v_tile = num_v_tile + 1;
        connector->tile_h_loc = tile_h_loc;
        connector->tile_v_loc = tile_v_loc;
        connector->tile_h_size = w + 1;
        connector->tile_v_size = h + 1;

        DRM_DEBUG_KMS("tile cap 0x%x\n", tile->tile_cap);
        DRM_DEBUG_KMS("tile_size %d x %d\n", w + 1, h + 1);
        DRM_DEBUG_KMS("topo num tiles %dx%d, location %dx%d\n",
                      num_h_tile + 1, num_v_tile + 1, tile_h_loc, tile_v_loc);
        DRM_DEBUG_KMS("vend %c%c%c\n", tile->topology_id[0], tile->topology_id[1], tile->topology_id[2]);

        tg = drm_mode_get_tile_group(connector->dev, tile->topology_id);
        if (!tg) {
            tg = drm_mode_create_tile_group(connector->dev, tile->topology_id);
        }
        if (!tg) {
            return -ENOMEM;
        }

        if (connector->tile_group != tg) {
            /* if we haven't got a pointer,
               take the reference, drop ref to old tile group */
            if (connector->tile_group) {
                drm_mode_put_tile_group(connector->dev, connector->tile_group);
            }
            connector->tile_group = tg;
        } else
            /* if same tile group, then release the ref we just took. */
        {
            drm_mode_put_tile_group(connector->dev, tg);
        }
    }
    break;
    default:
        printk("unknown displayid tag %d\n", block->tag);
        break;
    }
    return 0;
}

static void drm_get_displayid(struct drm_connector *connector,
                              struct edid *edid)
{
    void *displayid = NULL;
    int ret;
    connector->has_tile = false;
    displayid = drm_find_displayid_extension(edid);
    if (!displayid) {
        /* drop reference to any tile group we had */
        goto out_drop_ref;
    }

    ret = drm_parse_display_id(connector, displayid, EDID_LENGTH, true);
    if (ret < 0) {
        goto out_drop_ref;
    }
    if (!connector->has_tile) {
        goto out_drop_ref;
    }
    return;
out_drop_ref:
    if (connector->tile_group) {
        drm_mode_put_tile_group(connector->dev, connector->tile_group);
        connector->tile_group = NULL;
    }
    return;
}
