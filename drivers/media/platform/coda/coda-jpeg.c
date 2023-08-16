/*
 * Coda multi-standard codec IP - JPEG support functions
 *
 * Copyright (C) 2014 Philipp Zabel, Pengutronix
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/swab.h>

#include "coda.h"
#include "trace.h"

#define SOI_MARKER	0xffd8
#define EOI_MARKER	0xffd9

/*
 * Typical Huffman tables for 8-bit precision luminance and
 * chrominance from JPEG ITU-T.81 (ISO/IEC 10918-1) Annex K.3
 */

static const unsigned char luma_dc_bits[16] = {
    0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const unsigned char luma_dc_value[12] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
};

static const unsigned char chroma_dc_bits[16] = {
    0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const unsigned char chroma_dc_value[12] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
};

static const unsigned char luma_ac_bits[16] = {
    0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03,
    0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7d,
};

static const unsigned char luma_ac_value[162 + 2] = {
    0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
    0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
    0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
    0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
    0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
    0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
    0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
    0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
    0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
    0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
    0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
    0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
    0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
    0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
    0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa, /* padded to 32-bit */
};

static const unsigned char chroma_ac_bits[16] = {
    0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04,
    0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x77,
};

static const unsigned char chroma_ac_value[162 + 2] = {
    0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
    0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
    0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
    0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
    0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
    0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
    0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
    0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
    0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
    0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
    0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
    0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
    0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
    0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
    0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa, /* padded to 32-bit */
};

/*
 * Quantization tables for luminance and chrominance components in
 * zig-zag scan order from the Freescale i.MX VPU libaries
 */

static unsigned char luma_q[64] = {
    0x06, 0x04, 0x04, 0x04, 0x05, 0x04, 0x06, 0x05,
    0x05, 0x06, 0x09, 0x06, 0x05, 0x06, 0x09, 0x0b,
    0x08, 0x06, 0x06, 0x08, 0x0b, 0x0c, 0x0a, 0x0a,
    0x0b, 0x0a, 0x0a, 0x0c, 0x10, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x10, 0x0c, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
};

static unsigned char chroma_q[64] = {
    0x07, 0x07, 0x07, 0x0d, 0x0c, 0x0d, 0x18, 0x10,
    0x10, 0x18, 0x14, 0x0e, 0x0e, 0x0e, 0x14, 0x14,
    0x0e, 0x0e, 0x0e, 0x0e, 0x14, 0x11, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x11, 0x11, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x11, 0x0c, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
};

struct coda_memcpy_desc {
    int offset;
    const void *src;
    size_t len;
};

static void coda_memcpy_parabuf(void *parabuf,
                                const struct coda_memcpy_desc *desc)
{
    u32 *dst = parabuf + desc->offset;
    const u32 *src = desc->src;
    int len = desc->len / 4;
    int i;

    for (i = 0; i < len; i += 2) {
        dst[i + 1] = swab32(src[i]);
        dst[i] = swab32(src[i + 1]);
    }
}

int coda_jpeg_write_tables(struct coda_ctx *ctx)
{
    int i;
    static const struct coda_memcpy_desc huff[8] = {
        { 0,   luma_dc_bits,    sizeof(luma_dc_bits)    },
        { 16,  luma_dc_value,   sizeof(luma_dc_value)   },
        { 32,  luma_ac_bits,    sizeof(luma_ac_bits)    },
        { 48,  luma_ac_value,   sizeof(luma_ac_value)   },
        { 216, chroma_dc_bits,  sizeof(chroma_dc_bits)  },
        { 232, chroma_dc_value, sizeof(chroma_dc_value) },
        { 248, chroma_ac_bits,  sizeof(chroma_ac_bits)  },
        { 264, chroma_ac_value, sizeof(chroma_ac_value) },
    };
    struct coda_memcpy_desc qmat[3] = {
        { 512, ctx->params.jpeg_qmat_tab[0], 64 },
        { 576, ctx->params.jpeg_qmat_tab[1], 64 },
        { 640, ctx->params.jpeg_qmat_tab[1], 64 },
    };

    /* Write huffman tables to parameter memory */
    for (i = 0; i < ARRAY_SIZE(huff); i++) {
        coda_memcpy_parabuf(ctx->parabuf.vaddr, huff + i);
    }

    /* Write Q-matrix to parameter memory */
    for (i = 0; i < ARRAY_SIZE(qmat); i++) {
        coda_memcpy_parabuf(ctx->parabuf.vaddr, qmat + i);
    }

    return 0;
}

bool coda_jpeg_check_buffer(struct coda_ctx *ctx, struct vb2_buffer *vb)
{
    void *vaddr = vb2_plane_vaddr(vb, 0);
    u16 soi = be16_to_cpup((__be16 *)vaddr);
    u16 eoi = be16_to_cpup((__be16 *)(vaddr +
                                      vb2_get_plane_payload(vb, 0) - 2));

    return soi == SOI_MARKER && eoi == EOI_MARKER;
}

/*
 * Scale quantization table using nonlinear scaling factor
 * u8 qtab[64], scale [50,190]
 */
static void coda_scale_quant_table(u8 *q_tab, int scale)
{
    unsigned int temp;
    int i;

    for (i = 0; i < 64; i++) {
        temp = DIV_ROUND_CLOSEST((unsigned int)q_tab[i] * scale, 100);
        if (temp <= 0) {
            temp = 1;
        }
        if (temp > 255) {
            temp = 255;
        }
        q_tab[i] = (unsigned char)temp;
    }
}

void coda_set_jpeg_compression_quality(struct coda_ctx *ctx, int quality)
{
    unsigned int scale;

    ctx->params.jpeg_quality = quality;

    /* Clip quality setting to [5,100] interval */
    if (quality > 100) {
        quality = 100;
    }
    if (quality < 5) {
        quality = 5;
    }

    /*
     * Non-linear scaling factor:
     * [5,50] -> [1000..100], [51,100] -> [98..0]
     */
    if (quality < 50) {
        scale = 5000 / quality;
    } else {
        scale = 200 - 2 * quality;
    }

    if (ctx->params.jpeg_qmat_tab[0]) {
        memcpy(ctx->params.jpeg_qmat_tab[0], luma_q, 64);
        coda_scale_quant_table(ctx->params.jpeg_qmat_tab[0], scale);
    }
    if (ctx->params.jpeg_qmat_tab[1]) {
        memcpy(ctx->params.jpeg_qmat_tab[1], chroma_q, 64);
        coda_scale_quant_table(ctx->params.jpeg_qmat_tab[1], scale);
    }
}
