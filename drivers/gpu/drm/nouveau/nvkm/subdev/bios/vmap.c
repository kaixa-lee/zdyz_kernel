/*
 * Copyright 2012 Nouveau Community
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
 * Authors: Martin Peres
 */
#include <subdev/bios.h>
#include <subdev/bios/bit.h>
#include <subdev/bios/vmap.h>

u16
nvbios_vmap_table(struct nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
    struct bit_entry bit_P;
    u16 vmap = 0x0000;

    if (!bit_entry(bios, 'P', &bit_P)) {
        if (bit_P.version == 2) {
            vmap = nv_ro16(bios, bit_P.offset + 0x20);
            if (vmap) {
                *ver = nv_ro08(bios, vmap + 0);
                switch (*ver) {
                case 0x10:
                case 0x20:
                    *hdr = nv_ro08(bios, vmap + 1);
                    *cnt = nv_ro08(bios, vmap + 3);
                    *len = nv_ro08(bios, vmap + 2);
                    return vmap;
                default:
                    break;
                }
            }
        }
    }

    return 0x0000;
}

u16
nvbios_vmap_parse(struct nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
                  struct nvbios_vmap *info)
{
    u16 vmap = nvbios_vmap_table(bios, ver, hdr, cnt, len);
    memset(info, 0x00, sizeof(*info));
    switch (!!vmap * *ver) {
    case 0x10:
    case 0x20:
        break;
    }
    return vmap;
}

u16
nvbios_vmap_entry(struct nvkm_bios *bios, int idx, u8 *ver, u8 *len)
{
    u8  hdr, cnt;
    u16 vmap = nvbios_vmap_table(bios, ver, &hdr, &cnt, len);
    if (vmap && idx < cnt) {
        vmap = vmap + hdr + (idx * *len);
        return vmap;
    }
    return 0x0000;
}

u16
nvbios_vmap_entry_parse(struct nvkm_bios *bios, int idx, u8 *ver, u8 *len,
                        struct nvbios_vmap_entry *info)
{
    u16 vmap = nvbios_vmap_entry(bios, idx, ver, len);
    memset(info, 0x00, sizeof(*info));
    switch (!!vmap * *ver) {
    case 0x10:
        info->link   = 0xff;
        info->min    = nv_ro32(bios, vmap + 0x00);
        info->max    = nv_ro32(bios, vmap + 0x04);
        info->arg[0] = nv_ro32(bios, vmap + 0x08);
        info->arg[1] = nv_ro32(bios, vmap + 0x0c);
        info->arg[2] = nv_ro32(bios, vmap + 0x10);
        break;
    case 0x20:
        info->unk0   = nv_ro08(bios, vmap + 0x00);
        info->link   = nv_ro08(bios, vmap + 0x01);
        info->min    = nv_ro32(bios, vmap + 0x02);
        info->max    = nv_ro32(bios, vmap + 0x06);
        info->arg[0] = nv_ro32(bios, vmap + 0x0a);
        info->arg[1] = nv_ro32(bios, vmap + 0x0e);
        info->arg[2] = nv_ro32(bios, vmap + 0x12);
        info->arg[3] = nv_ro32(bios, vmap + 0x16);
        info->arg[4] = nv_ro32(bios, vmap + 0x1a);
        info->arg[5] = nv_ro32(bios, vmap + 0x1e);
        break;
    }
    return vmap;
}
