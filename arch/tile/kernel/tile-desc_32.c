/* TILEPro opcode information.
 *
 * Copyright 2011 Tilera Corporation. All Rights Reserved.
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation, version 2.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 *   NON INFRINGEMENT.  See the GNU General Public License for
 *   more details.
 *
 *
 *
 *
 *
 */

/* This define is BFD_RELOC_##x for real bfd, or -1 for everyone else. */
#define BFD_RELOC(x) -1

/* Special registers. */
#define TREG_LR 55
#define TREG_SN 56
#define TREG_ZERO 63

#include <linux/stddef.h>
#include <asm/tile-desc.h>

const struct tilepro_opcode tilepro_opcodes[395] = {
    {
        "bpt", TILEPRO_OPC_BPT, 0x2, 0, TREG_ZERO, 0,
        { { 0, }, {  }, { 0, }, { 0, }, { 0, } },
    },
    {
        "info", TILEPRO_OPC_INFO, 0xf, 1, TREG_ZERO, 1,
        { { 0 }, { 1 }, { 2 }, { 3 }, { 0, } },
    },
    {
        "infol", TILEPRO_OPC_INFOL, 0x3, 1, TREG_ZERO, 1,
        { { 4 }, { 5 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "j", TILEPRO_OPC_J, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 6 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "jal", TILEPRO_OPC_JAL, 0x2, 1, TREG_LR, 1,
        { { 0, }, { 6 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "move", TILEPRO_OPC_MOVE, 0xf, 2, TREG_ZERO, 1,
        { { 7, 8 }, { 9, 10 }, { 11, 12 }, { 13, 14 }, { 0, } },
    },
    {
        "move.sn", TILEPRO_OPC_MOVE_SN, 0x3, 2, TREG_SN, 1,
        { { 7, 8 }, { 9, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "movei", TILEPRO_OPC_MOVEI, 0xf, 2, TREG_ZERO, 1,
        { { 7, 0 }, { 9, 1 }, { 11, 2 }, { 13, 3 }, { 0, } },
    },
    {
        "movei.sn", TILEPRO_OPC_MOVEI_SN, 0x3, 2, TREG_SN, 1,
        { { 7, 0 }, { 9, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "moveli", TILEPRO_OPC_MOVELI, 0x3, 2, TREG_ZERO, 1,
        { { 7, 4 }, { 9, 5 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "moveli.sn", TILEPRO_OPC_MOVELI_SN, 0x3, 2, TREG_SN, 1,
        { { 7, 4 }, { 9, 5 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "movelis", TILEPRO_OPC_MOVELIS, 0x3, 2, TREG_SN, 1,
        { { 7, 4 }, { 9, 5 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "prefetch", TILEPRO_OPC_PREFETCH, 0x12, 1, TREG_ZERO, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 15 } },
    },
    {
        "raise", TILEPRO_OPC_RAISE, 0x2, 0, TREG_ZERO, 1,
        { { 0, }, {  }, { 0, }, { 0, }, { 0, } },
    },
    {
        "add", TILEPRO_OPC_ADD, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "add.sn", TILEPRO_OPC_ADD_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addb", TILEPRO_OPC_ADDB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addb.sn", TILEPRO_OPC_ADDB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addbs_u", TILEPRO_OPC_ADDBS_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addbs_u.sn", TILEPRO_OPC_ADDBS_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addh", TILEPRO_OPC_ADDH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addh.sn", TILEPRO_OPC_ADDH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addhs", TILEPRO_OPC_ADDHS, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addhs.sn", TILEPRO_OPC_ADDHS_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addi", TILEPRO_OPC_ADDI, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 11, 12, 2 }, { 13, 14, 3 }, { 0, } },
    },
    {
        "addi.sn", TILEPRO_OPC_ADDI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addib", TILEPRO_OPC_ADDIB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addib.sn", TILEPRO_OPC_ADDIB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addih", TILEPRO_OPC_ADDIH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addih.sn", TILEPRO_OPC_ADDIH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addli", TILEPRO_OPC_ADDLI, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 4 }, { 9, 10, 5 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addli.sn", TILEPRO_OPC_ADDLI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 4 }, { 9, 10, 5 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "addlis", TILEPRO_OPC_ADDLIS, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 4 }, { 9, 10, 5 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "adds", TILEPRO_OPC_ADDS, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "adds.sn", TILEPRO_OPC_ADDS_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "adiffb_u", TILEPRO_OPC_ADIFFB_U, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "adiffb_u.sn", TILEPRO_OPC_ADIFFB_U_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "adiffh", TILEPRO_OPC_ADIFFH, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "adiffh.sn", TILEPRO_OPC_ADIFFH_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "and", TILEPRO_OPC_AND, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "and.sn", TILEPRO_OPC_AND_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "andi", TILEPRO_OPC_ANDI, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 11, 12, 2 }, { 13, 14, 3 }, { 0, } },
    },
    {
        "andi.sn", TILEPRO_OPC_ANDI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "auli", TILEPRO_OPC_AULI, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 4 }, { 9, 10, 5 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "avgb_u", TILEPRO_OPC_AVGB_U, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "avgb_u.sn", TILEPRO_OPC_AVGB_U_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "avgh", TILEPRO_OPC_AVGH, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "avgh.sn", TILEPRO_OPC_AVGH_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bbns", TILEPRO_OPC_BBNS, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bbns.sn", TILEPRO_OPC_BBNS_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bbnst", TILEPRO_OPC_BBNST, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bbnst.sn", TILEPRO_OPC_BBNST_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bbs", TILEPRO_OPC_BBS, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bbs.sn", TILEPRO_OPC_BBS_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bbst", TILEPRO_OPC_BBST, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bbst.sn", TILEPRO_OPC_BBST_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bgez", TILEPRO_OPC_BGEZ, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bgez.sn", TILEPRO_OPC_BGEZ_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bgezt", TILEPRO_OPC_BGEZT, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bgezt.sn", TILEPRO_OPC_BGEZT_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bgz", TILEPRO_OPC_BGZ, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bgz.sn", TILEPRO_OPC_BGZ_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bgzt", TILEPRO_OPC_BGZT, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bgzt.sn", TILEPRO_OPC_BGZT_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bitx", TILEPRO_OPC_BITX, 0x5, 2, TREG_ZERO, 1,
        { { 7, 8 }, { 0, }, { 11, 12 }, { 0, }, { 0, } },
    },
    {
        "bitx.sn", TILEPRO_OPC_BITX_SN, 0x1, 2, TREG_SN, 1,
        { { 7, 8 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "blez", TILEPRO_OPC_BLEZ, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "blez.sn", TILEPRO_OPC_BLEZ_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "blezt", TILEPRO_OPC_BLEZT, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "blezt.sn", TILEPRO_OPC_BLEZT_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "blz", TILEPRO_OPC_BLZ, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "blz.sn", TILEPRO_OPC_BLZ_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "blzt", TILEPRO_OPC_BLZT, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "blzt.sn", TILEPRO_OPC_BLZT_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bnz", TILEPRO_OPC_BNZ, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bnz.sn", TILEPRO_OPC_BNZ_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bnzt", TILEPRO_OPC_BNZT, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bnzt.sn", TILEPRO_OPC_BNZT_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bytex", TILEPRO_OPC_BYTEX, 0x5, 2, TREG_ZERO, 1,
        { { 7, 8 }, { 0, }, { 11, 12 }, { 0, }, { 0, } },
    },
    {
        "bytex.sn", TILEPRO_OPC_BYTEX_SN, 0x1, 2, TREG_SN, 1,
        { { 7, 8 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bz", TILEPRO_OPC_BZ, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bz.sn", TILEPRO_OPC_BZ_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bzt", TILEPRO_OPC_BZT, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "bzt.sn", TILEPRO_OPC_BZT_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 10, 20 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "clz", TILEPRO_OPC_CLZ, 0x5, 2, TREG_ZERO, 1,
        { { 7, 8 }, { 0, }, { 11, 12 }, { 0, }, { 0, } },
    },
    {
        "clz.sn", TILEPRO_OPC_CLZ_SN, 0x1, 2, TREG_SN, 1,
        { { 7, 8 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "crc32_32", TILEPRO_OPC_CRC32_32, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "crc32_32.sn", TILEPRO_OPC_CRC32_32_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "crc32_8", TILEPRO_OPC_CRC32_8, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "crc32_8.sn", TILEPRO_OPC_CRC32_8_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "ctz", TILEPRO_OPC_CTZ, 0x5, 2, TREG_ZERO, 1,
        { { 7, 8 }, { 0, }, { 11, 12 }, { 0, }, { 0, } },
    },
    {
        "ctz.sn", TILEPRO_OPC_CTZ_SN, 0x1, 2, TREG_SN, 1,
        { { 7, 8 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "drain", TILEPRO_OPC_DRAIN, 0x2, 0, TREG_ZERO, 0,
        { { 0, }, {  }, { 0, }, { 0, }, { 0, } },
    },
    {
        "dtlbpr", TILEPRO_OPC_DTLBPR, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "dword_align", TILEPRO_OPC_DWORD_ALIGN, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "dword_align.sn", TILEPRO_OPC_DWORD_ALIGN_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "finv", TILEPRO_OPC_FINV, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "flush", TILEPRO_OPC_FLUSH, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "fnop", TILEPRO_OPC_FNOP, 0xf, 0, TREG_ZERO, 1,
        { {  }, {  }, {  }, {  }, { 0, } },
    },
    {
        "icoh", TILEPRO_OPC_ICOH, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "ill", TILEPRO_OPC_ILL, 0xa, 0, TREG_ZERO, 1,
        { { 0, }, {  }, { 0, }, {  }, { 0, } },
    },
    {
        "inthb", TILEPRO_OPC_INTHB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "inthb.sn", TILEPRO_OPC_INTHB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "inthh", TILEPRO_OPC_INTHH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "inthh.sn", TILEPRO_OPC_INTHH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "intlb", TILEPRO_OPC_INTLB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "intlb.sn", TILEPRO_OPC_INTLB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "intlh", TILEPRO_OPC_INTLH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "intlh.sn", TILEPRO_OPC_INTLH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "inv", TILEPRO_OPC_INV, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "iret", TILEPRO_OPC_IRET, 0x2, 0, TREG_ZERO, 1,
        { { 0, }, {  }, { 0, }, { 0, }, { 0, } },
    },
    {
        "jalb", TILEPRO_OPC_JALB, 0x2, 1, TREG_LR, 1,
        { { 0, }, { 22 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "jalf", TILEPRO_OPC_JALF, 0x2, 1, TREG_LR, 1,
        { { 0, }, { 22 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "jalr", TILEPRO_OPC_JALR, 0x2, 1, TREG_LR, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "jalrp", TILEPRO_OPC_JALRP, 0x2, 1, TREG_LR, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "jb", TILEPRO_OPC_JB, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 22 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "jf", TILEPRO_OPC_JF, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 22 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "jr", TILEPRO_OPC_JR, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "jrp", TILEPRO_OPC_JRP, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lb", TILEPRO_OPC_LB, 0x12, 2, TREG_ZERO, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 23, 15 } },
    },
    {
        "lb.sn", TILEPRO_OPC_LB_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lb_u", TILEPRO_OPC_LB_U, 0x12, 2, TREG_ZERO, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 23, 15 } },
    },
    {
        "lb_u.sn", TILEPRO_OPC_LB_U_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lbadd", TILEPRO_OPC_LBADD, 0x2, 3, TREG_ZERO, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lbadd.sn", TILEPRO_OPC_LBADD_SN, 0x2, 3, TREG_SN, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lbadd_u", TILEPRO_OPC_LBADD_U, 0x2, 3, TREG_ZERO, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lbadd_u.sn", TILEPRO_OPC_LBADD_U_SN, 0x2, 3, TREG_SN, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lh", TILEPRO_OPC_LH, 0x12, 2, TREG_ZERO, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 23, 15 } },
    },
    {
        "lh.sn", TILEPRO_OPC_LH_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lh_u", TILEPRO_OPC_LH_U, 0x12, 2, TREG_ZERO, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 23, 15 } },
    },
    {
        "lh_u.sn", TILEPRO_OPC_LH_U_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lhadd", TILEPRO_OPC_LHADD, 0x2, 3, TREG_ZERO, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lhadd.sn", TILEPRO_OPC_LHADD_SN, 0x2, 3, TREG_SN, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lhadd_u", TILEPRO_OPC_LHADD_U, 0x2, 3, TREG_ZERO, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lhadd_u.sn", TILEPRO_OPC_LHADD_U_SN, 0x2, 3, TREG_SN, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lnk", TILEPRO_OPC_LNK, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 9 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lnk.sn", TILEPRO_OPC_LNK_SN, 0x2, 1, TREG_SN, 1,
        { { 0, }, { 9 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lw", TILEPRO_OPC_LW, 0x12, 2, TREG_ZERO, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 23, 15 } },
    },
    {
        "lw.sn", TILEPRO_OPC_LW_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lw_na", TILEPRO_OPC_LW_NA, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lw_na.sn", TILEPRO_OPC_LW_NA_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lwadd", TILEPRO_OPC_LWADD, 0x2, 3, TREG_ZERO, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lwadd.sn", TILEPRO_OPC_LWADD_SN, 0x2, 3, TREG_SN, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lwadd_na", TILEPRO_OPC_LWADD_NA, 0x2, 3, TREG_ZERO, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "lwadd_na.sn", TILEPRO_OPC_LWADD_NA_SN, 0x2, 3, TREG_SN, 1,
        { { 0, }, { 9, 24, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "maxb_u", TILEPRO_OPC_MAXB_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "maxb_u.sn", TILEPRO_OPC_MAXB_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "maxh", TILEPRO_OPC_MAXH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "maxh.sn", TILEPRO_OPC_MAXH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "maxib_u", TILEPRO_OPC_MAXIB_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "maxib_u.sn", TILEPRO_OPC_MAXIB_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "maxih", TILEPRO_OPC_MAXIH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "maxih.sn", TILEPRO_OPC_MAXIH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mf", TILEPRO_OPC_MF, 0x2, 0, TREG_ZERO, 1,
        { { 0, }, {  }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mfspr", TILEPRO_OPC_MFSPR, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 9, 25 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "minb_u", TILEPRO_OPC_MINB_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "minb_u.sn", TILEPRO_OPC_MINB_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "minh", TILEPRO_OPC_MINH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "minh.sn", TILEPRO_OPC_MINH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "minib_u", TILEPRO_OPC_MINIB_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "minib_u.sn", TILEPRO_OPC_MINIB_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "minih", TILEPRO_OPC_MINIH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "minih.sn", TILEPRO_OPC_MINIH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mm", TILEPRO_OPC_MM, 0x3, 5, TREG_ZERO, 1,
        { { 7, 8, 16, 26, 27 }, { 9, 10, 17, 28, 29 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mnz", TILEPRO_OPC_MNZ, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "mnz.sn", TILEPRO_OPC_MNZ_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mnzb", TILEPRO_OPC_MNZB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mnzb.sn", TILEPRO_OPC_MNZB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mnzh", TILEPRO_OPC_MNZH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mnzh.sn", TILEPRO_OPC_MNZH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mtspr", TILEPRO_OPC_MTSPR, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 30, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhh_ss", TILEPRO_OPC_MULHH_SS, 0x5, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 11, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mulhh_ss.sn", TILEPRO_OPC_MULHH_SS_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhh_su", TILEPRO_OPC_MULHH_SU, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhh_su.sn", TILEPRO_OPC_MULHH_SU_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhh_uu", TILEPRO_OPC_MULHH_UU, 0x5, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 11, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mulhh_uu.sn", TILEPRO_OPC_MULHH_UU_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhha_ss", TILEPRO_OPC_MULHHA_SS, 0x5, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 31, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mulhha_ss.sn", TILEPRO_OPC_MULHHA_SS_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhha_su", TILEPRO_OPC_MULHHA_SU, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhha_su.sn", TILEPRO_OPC_MULHHA_SU_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhha_uu", TILEPRO_OPC_MULHHA_UU, 0x5, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 31, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mulhha_uu.sn", TILEPRO_OPC_MULHHA_UU_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhhsa_uu", TILEPRO_OPC_MULHHSA_UU, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhhsa_uu.sn", TILEPRO_OPC_MULHHSA_UU_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhl_ss", TILEPRO_OPC_MULHL_SS, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhl_ss.sn", TILEPRO_OPC_MULHL_SS_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhl_su", TILEPRO_OPC_MULHL_SU, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhl_su.sn", TILEPRO_OPC_MULHL_SU_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhl_us", TILEPRO_OPC_MULHL_US, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhl_us.sn", TILEPRO_OPC_MULHL_US_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhl_uu", TILEPRO_OPC_MULHL_UU, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhl_uu.sn", TILEPRO_OPC_MULHL_UU_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhla_ss", TILEPRO_OPC_MULHLA_SS, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhla_ss.sn", TILEPRO_OPC_MULHLA_SS_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhla_su", TILEPRO_OPC_MULHLA_SU, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhla_su.sn", TILEPRO_OPC_MULHLA_SU_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhla_us", TILEPRO_OPC_MULHLA_US, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhla_us.sn", TILEPRO_OPC_MULHLA_US_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhla_uu", TILEPRO_OPC_MULHLA_UU, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhla_uu.sn", TILEPRO_OPC_MULHLA_UU_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulhlsa_uu", TILEPRO_OPC_MULHLSA_UU, 0x5, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 31, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mulhlsa_uu.sn", TILEPRO_OPC_MULHLSA_UU_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulll_ss", TILEPRO_OPC_MULLL_SS, 0x5, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 11, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mulll_ss.sn", TILEPRO_OPC_MULLL_SS_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulll_su", TILEPRO_OPC_MULLL_SU, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulll_su.sn", TILEPRO_OPC_MULLL_SU_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulll_uu", TILEPRO_OPC_MULLL_UU, 0x5, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 11, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mulll_uu.sn", TILEPRO_OPC_MULLL_UU_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mullla_ss", TILEPRO_OPC_MULLLA_SS, 0x5, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 31, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mullla_ss.sn", TILEPRO_OPC_MULLLA_SS_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mullla_su", TILEPRO_OPC_MULLLA_SU, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mullla_su.sn", TILEPRO_OPC_MULLLA_SU_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mullla_uu", TILEPRO_OPC_MULLLA_UU, 0x5, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 31, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mullla_uu.sn", TILEPRO_OPC_MULLLA_UU_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulllsa_uu", TILEPRO_OPC_MULLLSA_UU, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mulllsa_uu.sn", TILEPRO_OPC_MULLLSA_UU_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mvnz", TILEPRO_OPC_MVNZ, 0x5, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 31, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mvnz.sn", TILEPRO_OPC_MVNZ_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mvz", TILEPRO_OPC_MVZ, 0x5, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 31, 12, 18 }, { 0, }, { 0, } },
    },
    {
        "mvz.sn", TILEPRO_OPC_MVZ_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mz", TILEPRO_OPC_MZ, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "mz.sn", TILEPRO_OPC_MZ_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mzb", TILEPRO_OPC_MZB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mzb.sn", TILEPRO_OPC_MZB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mzh", TILEPRO_OPC_MZH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "mzh.sn", TILEPRO_OPC_MZH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "nap", TILEPRO_OPC_NAP, 0x2, 0, TREG_ZERO, 0,
        { { 0, }, {  }, { 0, }, { 0, }, { 0, } },
    },
    {
        "nop", TILEPRO_OPC_NOP, 0xf, 0, TREG_ZERO, 1,
        { {  }, {  }, {  }, {  }, { 0, } },
    },
    {
        "nor", TILEPRO_OPC_NOR, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "nor.sn", TILEPRO_OPC_NOR_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "or", TILEPRO_OPC_OR, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "or.sn", TILEPRO_OPC_OR_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "ori", TILEPRO_OPC_ORI, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 11, 12, 2 }, { 13, 14, 3 }, { 0, } },
    },
    {
        "ori.sn", TILEPRO_OPC_ORI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "packbs_u", TILEPRO_OPC_PACKBS_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "packbs_u.sn", TILEPRO_OPC_PACKBS_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "packhb", TILEPRO_OPC_PACKHB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "packhb.sn", TILEPRO_OPC_PACKHB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "packhs", TILEPRO_OPC_PACKHS, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "packhs.sn", TILEPRO_OPC_PACKHS_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "packlb", TILEPRO_OPC_PACKLB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "packlb.sn", TILEPRO_OPC_PACKLB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "pcnt", TILEPRO_OPC_PCNT, 0x5, 2, TREG_ZERO, 1,
        { { 7, 8 }, { 0, }, { 11, 12 }, { 0, }, { 0, } },
    },
    {
        "pcnt.sn", TILEPRO_OPC_PCNT_SN, 0x1, 2, TREG_SN, 1,
        { { 7, 8 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "rl", TILEPRO_OPC_RL, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "rl.sn", TILEPRO_OPC_RL_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "rli", TILEPRO_OPC_RLI, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 11, 12, 34 }, { 13, 14, 35 }, { 0, } },
    },
    {
        "rli.sn", TILEPRO_OPC_RLI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "s1a", TILEPRO_OPC_S1A, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "s1a.sn", TILEPRO_OPC_S1A_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "s2a", TILEPRO_OPC_S2A, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "s2a.sn", TILEPRO_OPC_S2A_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "s3a", TILEPRO_OPC_S3A, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "s3a.sn", TILEPRO_OPC_S3A_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadab_u", TILEPRO_OPC_SADAB_U, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadab_u.sn", TILEPRO_OPC_SADAB_U_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadah", TILEPRO_OPC_SADAH, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadah.sn", TILEPRO_OPC_SADAH_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadah_u", TILEPRO_OPC_SADAH_U, 0x1, 3, TREG_ZERO, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadah_u.sn", TILEPRO_OPC_SADAH_U_SN, 0x1, 3, TREG_SN, 1,
        { { 21, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadb_u", TILEPRO_OPC_SADB_U, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadb_u.sn", TILEPRO_OPC_SADB_U_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadh", TILEPRO_OPC_SADH, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadh.sn", TILEPRO_OPC_SADH_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadh_u", TILEPRO_OPC_SADH_U, 0x1, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sadh_u.sn", TILEPRO_OPC_SADH_U_SN, 0x1, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sb", TILEPRO_OPC_SB, 0x12, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 17 }, { 0, }, { 0, }, { 15, 36 } },
    },
    {
        "sbadd", TILEPRO_OPC_SBADD, 0x2, 3, TREG_ZERO, 1,
        { { 0, }, { 24, 17, 37 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "seq", TILEPRO_OPC_SEQ, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "seq.sn", TILEPRO_OPC_SEQ_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "seqb", TILEPRO_OPC_SEQB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "seqb.sn", TILEPRO_OPC_SEQB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "seqh", TILEPRO_OPC_SEQH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "seqh.sn", TILEPRO_OPC_SEQH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "seqi", TILEPRO_OPC_SEQI, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 11, 12, 2 }, { 13, 14, 3 }, { 0, } },
    },
    {
        "seqi.sn", TILEPRO_OPC_SEQI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "seqib", TILEPRO_OPC_SEQIB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "seqib.sn", TILEPRO_OPC_SEQIB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "seqih", TILEPRO_OPC_SEQIH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "seqih.sn", TILEPRO_OPC_SEQIH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sh", TILEPRO_OPC_SH, 0x12, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 17 }, { 0, }, { 0, }, { 15, 36 } },
    },
    {
        "shadd", TILEPRO_OPC_SHADD, 0x2, 3, TREG_ZERO, 1,
        { { 0, }, { 24, 17, 37 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shl", TILEPRO_OPC_SHL, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "shl.sn", TILEPRO_OPC_SHL_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shlb", TILEPRO_OPC_SHLB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shlb.sn", TILEPRO_OPC_SHLB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shlh", TILEPRO_OPC_SHLH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shlh.sn", TILEPRO_OPC_SHLH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shli", TILEPRO_OPC_SHLI, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 11, 12, 34 }, { 13, 14, 35 }, { 0, } },
    },
    {
        "shli.sn", TILEPRO_OPC_SHLI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shlib", TILEPRO_OPC_SHLIB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shlib.sn", TILEPRO_OPC_SHLIB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shlih", TILEPRO_OPC_SHLIH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shlih.sn", TILEPRO_OPC_SHLIH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shr", TILEPRO_OPC_SHR, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "shr.sn", TILEPRO_OPC_SHR_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shrb", TILEPRO_OPC_SHRB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shrb.sn", TILEPRO_OPC_SHRB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shrh", TILEPRO_OPC_SHRH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shrh.sn", TILEPRO_OPC_SHRH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shri", TILEPRO_OPC_SHRI, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 11, 12, 34 }, { 13, 14, 35 }, { 0, } },
    },
    {
        "shri.sn", TILEPRO_OPC_SHRI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shrib", TILEPRO_OPC_SHRIB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shrib.sn", TILEPRO_OPC_SHRIB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shrih", TILEPRO_OPC_SHRIH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "shrih.sn", TILEPRO_OPC_SHRIH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slt", TILEPRO_OPC_SLT, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "slt.sn", TILEPRO_OPC_SLT_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slt_u", TILEPRO_OPC_SLT_U, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "slt_u.sn", TILEPRO_OPC_SLT_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltb", TILEPRO_OPC_SLTB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltb.sn", TILEPRO_OPC_SLTB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltb_u", TILEPRO_OPC_SLTB_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltb_u.sn", TILEPRO_OPC_SLTB_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slte", TILEPRO_OPC_SLTE, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "slte.sn", TILEPRO_OPC_SLTE_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slte_u", TILEPRO_OPC_SLTE_U, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "slte_u.sn", TILEPRO_OPC_SLTE_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slteb", TILEPRO_OPC_SLTEB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slteb.sn", TILEPRO_OPC_SLTEB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slteb_u", TILEPRO_OPC_SLTEB_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slteb_u.sn", TILEPRO_OPC_SLTEB_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slteh", TILEPRO_OPC_SLTEH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slteh.sn", TILEPRO_OPC_SLTEH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slteh_u", TILEPRO_OPC_SLTEH_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slteh_u.sn", TILEPRO_OPC_SLTEH_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slth", TILEPRO_OPC_SLTH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slth.sn", TILEPRO_OPC_SLTH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slth_u", TILEPRO_OPC_SLTH_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slth_u.sn", TILEPRO_OPC_SLTH_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slti", TILEPRO_OPC_SLTI, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 11, 12, 2 }, { 13, 14, 3 }, { 0, } },
    },
    {
        "slti.sn", TILEPRO_OPC_SLTI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "slti_u", TILEPRO_OPC_SLTI_U, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 11, 12, 2 }, { 13, 14, 3 }, { 0, } },
    },
    {
        "slti_u.sn", TILEPRO_OPC_SLTI_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltib", TILEPRO_OPC_SLTIB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltib.sn", TILEPRO_OPC_SLTIB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltib_u", TILEPRO_OPC_SLTIB_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltib_u.sn", TILEPRO_OPC_SLTIB_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltih", TILEPRO_OPC_SLTIH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltih.sn", TILEPRO_OPC_SLTIH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltih_u", TILEPRO_OPC_SLTIH_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sltih_u.sn", TILEPRO_OPC_SLTIH_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sne", TILEPRO_OPC_SNE, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "sne.sn", TILEPRO_OPC_SNE_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sneb", TILEPRO_OPC_SNEB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sneb.sn", TILEPRO_OPC_SNEB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sneh", TILEPRO_OPC_SNEH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sneh.sn", TILEPRO_OPC_SNEH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sra", TILEPRO_OPC_SRA, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "sra.sn", TILEPRO_OPC_SRA_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "srab", TILEPRO_OPC_SRAB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "srab.sn", TILEPRO_OPC_SRAB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "srah", TILEPRO_OPC_SRAH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "srah.sn", TILEPRO_OPC_SRAH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "srai", TILEPRO_OPC_SRAI, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 11, 12, 34 }, { 13, 14, 35 }, { 0, } },
    },
    {
        "srai.sn", TILEPRO_OPC_SRAI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sraib", TILEPRO_OPC_SRAIB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sraib.sn", TILEPRO_OPC_SRAIB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sraih", TILEPRO_OPC_SRAIH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sraih.sn", TILEPRO_OPC_SRAIH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 32 }, { 9, 10, 33 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sub", TILEPRO_OPC_SUB, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "sub.sn", TILEPRO_OPC_SUB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "subb", TILEPRO_OPC_SUBB, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "subb.sn", TILEPRO_OPC_SUBB_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "subbs_u", TILEPRO_OPC_SUBBS_U, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "subbs_u.sn", TILEPRO_OPC_SUBBS_U_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "subh", TILEPRO_OPC_SUBH, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "subh.sn", TILEPRO_OPC_SUBH_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "subhs", TILEPRO_OPC_SUBHS, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "subhs.sn", TILEPRO_OPC_SUBHS_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "subs", TILEPRO_OPC_SUBS, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "subs.sn", TILEPRO_OPC_SUBS_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "sw", TILEPRO_OPC_SW, 0x12, 2, TREG_ZERO, 1,
        { { 0, }, { 10, 17 }, { 0, }, { 0, }, { 15, 36 } },
    },
    {
        "swadd", TILEPRO_OPC_SWADD, 0x2, 3, TREG_ZERO, 1,
        { { 0, }, { 24, 17, 37 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "swint0", TILEPRO_OPC_SWINT0, 0x2, 0, TREG_ZERO, 0,
        { { 0, }, {  }, { 0, }, { 0, }, { 0, } },
    },
    {
        "swint1", TILEPRO_OPC_SWINT1, 0x2, 0, TREG_ZERO, 0,
        { { 0, }, {  }, { 0, }, { 0, }, { 0, } },
    },
    {
        "swint2", TILEPRO_OPC_SWINT2, 0x2, 0, TREG_ZERO, 0,
        { { 0, }, {  }, { 0, }, { 0, }, { 0, } },
    },
    {
        "swint3", TILEPRO_OPC_SWINT3, 0x2, 0, TREG_ZERO, 0,
        { { 0, }, {  }, { 0, }, { 0, }, { 0, } },
    },
    {
        "tblidxb0", TILEPRO_OPC_TBLIDXB0, 0x5, 2, TREG_ZERO, 1,
        { { 21, 8 }, { 0, }, { 31, 12 }, { 0, }, { 0, } },
    },
    {
        "tblidxb0.sn", TILEPRO_OPC_TBLIDXB0_SN, 0x1, 2, TREG_SN, 1,
        { { 21, 8 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "tblidxb1", TILEPRO_OPC_TBLIDXB1, 0x5, 2, TREG_ZERO, 1,
        { { 21, 8 }, { 0, }, { 31, 12 }, { 0, }, { 0, } },
    },
    {
        "tblidxb1.sn", TILEPRO_OPC_TBLIDXB1_SN, 0x1, 2, TREG_SN, 1,
        { { 21, 8 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "tblidxb2", TILEPRO_OPC_TBLIDXB2, 0x5, 2, TREG_ZERO, 1,
        { { 21, 8 }, { 0, }, { 31, 12 }, { 0, }, { 0, } },
    },
    {
        "tblidxb2.sn", TILEPRO_OPC_TBLIDXB2_SN, 0x1, 2, TREG_SN, 1,
        { { 21, 8 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "tblidxb3", TILEPRO_OPC_TBLIDXB3, 0x5, 2, TREG_ZERO, 1,
        { { 21, 8 }, { 0, }, { 31, 12 }, { 0, }, { 0, } },
    },
    {
        "tblidxb3.sn", TILEPRO_OPC_TBLIDXB3_SN, 0x1, 2, TREG_SN, 1,
        { { 21, 8 }, { 0, }, { 0, }, { 0, }, { 0, } },
    },
    {
        "tns", TILEPRO_OPC_TNS, 0x2, 2, TREG_ZERO, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "tns.sn", TILEPRO_OPC_TNS_SN, 0x2, 2, TREG_SN, 1,
        { { 0, }, { 9, 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "wh64", TILEPRO_OPC_WH64, 0x2, 1, TREG_ZERO, 1,
        { { 0, }, { 10 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "xor", TILEPRO_OPC_XOR, 0xf, 3, TREG_ZERO, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 11, 12, 18 }, { 13, 14, 19 }, { 0, } },
    },
    {
        "xor.sn", TILEPRO_OPC_XOR_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 16 }, { 9, 10, 17 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "xori", TILEPRO_OPC_XORI, 0x3, 3, TREG_ZERO, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        "xori.sn", TILEPRO_OPC_XORI_SN, 0x3, 3, TREG_SN, 1,
        { { 7, 8, 0 }, { 9, 10, 1 }, { 0, }, { 0, }, { 0, } },
    },
    {
        NULL, TILEPRO_OPC_NONE, 0, 0, TREG_ZERO, 0, { { 0, } },
    }
};
#define BITFIELD(start, size) ((start) | (((1 << (size)) - 1) << 6))
#define CHILD(array_index) (TILEPRO_OPC_NONE + (array_index))

static const unsigned short decode_X0_fsm[1153] = {
    BITFIELD(22, 9) /* index 0 */,
    CHILD(513), CHILD(530), CHILD(547), CHILD(564), CHILD(596), CHILD(613),
    CHILD(630), TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, CHILD(663), CHILD(680), CHILD(697),
    CHILD(714), CHILD(746), CHILD(763), CHILD(780), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813),
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813),
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813),
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813),
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813),
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813),
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813),
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813),
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813),
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(813),
    CHILD(813), CHILD(813), CHILD(813), CHILD(813), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828), CHILD(828),
    CHILD(828), CHILD(828), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(873), CHILD(878), CHILD(883), CHILD(903), CHILD(908),
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, CHILD(913),
    CHILD(918), CHILD(923), CHILD(943), CHILD(948), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, CHILD(953), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, CHILD(988), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, CHILD(993), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, CHILD(1076), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(18, 4) /* index 513 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_ADDB, TILEPRO_OPC_ADDH, TILEPRO_OPC_ADD,
    TILEPRO_OPC_ADIFFB_U, TILEPRO_OPC_ADIFFH, TILEPRO_OPC_AND,
    TILEPRO_OPC_AVGB_U, TILEPRO_OPC_AVGH, TILEPRO_OPC_CRC32_32,
    TILEPRO_OPC_CRC32_8, TILEPRO_OPC_INTHB, TILEPRO_OPC_INTHH,
    TILEPRO_OPC_INTLB, TILEPRO_OPC_INTLH, TILEPRO_OPC_MAXB_U,
    BITFIELD(18, 4) /* index 530 */,
    TILEPRO_OPC_MAXH, TILEPRO_OPC_MINB_U, TILEPRO_OPC_MINH, TILEPRO_OPC_MNZB,
    TILEPRO_OPC_MNZH, TILEPRO_OPC_MNZ, TILEPRO_OPC_MULHHA_SS,
    TILEPRO_OPC_MULHHA_SU, TILEPRO_OPC_MULHHA_UU, TILEPRO_OPC_MULHHSA_UU,
    TILEPRO_OPC_MULHH_SS, TILEPRO_OPC_MULHH_SU, TILEPRO_OPC_MULHH_UU,
    TILEPRO_OPC_MULHLA_SS, TILEPRO_OPC_MULHLA_SU, TILEPRO_OPC_MULHLA_US,
    BITFIELD(18, 4) /* index 547 */,
    TILEPRO_OPC_MULHLA_UU, TILEPRO_OPC_MULHLSA_UU, TILEPRO_OPC_MULHL_SS,
    TILEPRO_OPC_MULHL_SU, TILEPRO_OPC_MULHL_US, TILEPRO_OPC_MULHL_UU,
    TILEPRO_OPC_MULLLA_SS, TILEPRO_OPC_MULLLA_SU, TILEPRO_OPC_MULLLA_UU,
    TILEPRO_OPC_MULLLSA_UU, TILEPRO_OPC_MULLL_SS, TILEPRO_OPC_MULLL_SU,
    TILEPRO_OPC_MULLL_UU, TILEPRO_OPC_MVNZ, TILEPRO_OPC_MVZ, TILEPRO_OPC_MZB,
    BITFIELD(18, 4) /* index 564 */,
    TILEPRO_OPC_MZH, TILEPRO_OPC_MZ, TILEPRO_OPC_NOR, CHILD(581),
    TILEPRO_OPC_PACKHB, TILEPRO_OPC_PACKLB, TILEPRO_OPC_RL, TILEPRO_OPC_S1A,
    TILEPRO_OPC_S2A, TILEPRO_OPC_S3A, TILEPRO_OPC_SADAB_U, TILEPRO_OPC_SADAH,
    TILEPRO_OPC_SADAH_U, TILEPRO_OPC_SADB_U, TILEPRO_OPC_SADH,
    TILEPRO_OPC_SADH_U,
    BITFIELD(12, 2) /* index 581 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, CHILD(586),
    BITFIELD(14, 2) /* index 586 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, CHILD(591),
    BITFIELD(16, 2) /* index 591 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_MOVE,
    BITFIELD(18, 4) /* index 596 */,
    TILEPRO_OPC_SEQB, TILEPRO_OPC_SEQH, TILEPRO_OPC_SEQ, TILEPRO_OPC_SHLB,
    TILEPRO_OPC_SHLH, TILEPRO_OPC_SHL, TILEPRO_OPC_SHRB, TILEPRO_OPC_SHRH,
    TILEPRO_OPC_SHR, TILEPRO_OPC_SLTB, TILEPRO_OPC_SLTB_U, TILEPRO_OPC_SLTEB,
    TILEPRO_OPC_SLTEB_U, TILEPRO_OPC_SLTEH, TILEPRO_OPC_SLTEH_U,
    TILEPRO_OPC_SLTE,
    BITFIELD(18, 4) /* index 613 */,
    TILEPRO_OPC_SLTE_U, TILEPRO_OPC_SLTH, TILEPRO_OPC_SLTH_U, TILEPRO_OPC_SLT,
    TILEPRO_OPC_SLT_U, TILEPRO_OPC_SNEB, TILEPRO_OPC_SNEH, TILEPRO_OPC_SNE,
    TILEPRO_OPC_SRAB, TILEPRO_OPC_SRAH, TILEPRO_OPC_SRA, TILEPRO_OPC_SUBB,
    TILEPRO_OPC_SUBH, TILEPRO_OPC_SUB, TILEPRO_OPC_XOR, TILEPRO_OPC_DWORD_ALIGN,
    BITFIELD(18, 3) /* index 630 */,
    CHILD(639), CHILD(642), CHILD(645), CHILD(648), CHILD(651), CHILD(654),
    CHILD(657), CHILD(660),
    BITFIELD(21, 1) /* index 639 */,
    TILEPRO_OPC_ADDS, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 642 */,
    TILEPRO_OPC_SUBS, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 645 */,
    TILEPRO_OPC_ADDBS_U, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 648 */,
    TILEPRO_OPC_ADDHS, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 651 */,
    TILEPRO_OPC_SUBBS_U, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 654 */,
    TILEPRO_OPC_SUBHS, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 657 */,
    TILEPRO_OPC_PACKHS, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 660 */,
    TILEPRO_OPC_PACKBS_U, TILEPRO_OPC_NONE,
    BITFIELD(18, 4) /* index 663 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_ADDB_SN, TILEPRO_OPC_ADDH_SN,
    TILEPRO_OPC_ADD_SN, TILEPRO_OPC_ADIFFB_U_SN, TILEPRO_OPC_ADIFFH_SN,
    TILEPRO_OPC_AND_SN, TILEPRO_OPC_AVGB_U_SN, TILEPRO_OPC_AVGH_SN,
    TILEPRO_OPC_CRC32_32_SN, TILEPRO_OPC_CRC32_8_SN, TILEPRO_OPC_INTHB_SN,
    TILEPRO_OPC_INTHH_SN, TILEPRO_OPC_INTLB_SN, TILEPRO_OPC_INTLH_SN,
    TILEPRO_OPC_MAXB_U_SN,
    BITFIELD(18, 4) /* index 680 */,
    TILEPRO_OPC_MAXH_SN, TILEPRO_OPC_MINB_U_SN, TILEPRO_OPC_MINH_SN,
    TILEPRO_OPC_MNZB_SN, TILEPRO_OPC_MNZH_SN, TILEPRO_OPC_MNZ_SN,
    TILEPRO_OPC_MULHHA_SS_SN, TILEPRO_OPC_MULHHA_SU_SN,
    TILEPRO_OPC_MULHHA_UU_SN, TILEPRO_OPC_MULHHSA_UU_SN,
    TILEPRO_OPC_MULHH_SS_SN, TILEPRO_OPC_MULHH_SU_SN, TILEPRO_OPC_MULHH_UU_SN,
    TILEPRO_OPC_MULHLA_SS_SN, TILEPRO_OPC_MULHLA_SU_SN,
    TILEPRO_OPC_MULHLA_US_SN,
    BITFIELD(18, 4) /* index 697 */,
    TILEPRO_OPC_MULHLA_UU_SN, TILEPRO_OPC_MULHLSA_UU_SN,
    TILEPRO_OPC_MULHL_SS_SN, TILEPRO_OPC_MULHL_SU_SN, TILEPRO_OPC_MULHL_US_SN,
    TILEPRO_OPC_MULHL_UU_SN, TILEPRO_OPC_MULLLA_SS_SN, TILEPRO_OPC_MULLLA_SU_SN,
    TILEPRO_OPC_MULLLA_UU_SN, TILEPRO_OPC_MULLLSA_UU_SN,
    TILEPRO_OPC_MULLL_SS_SN, TILEPRO_OPC_MULLL_SU_SN, TILEPRO_OPC_MULLL_UU_SN,
    TILEPRO_OPC_MVNZ_SN, TILEPRO_OPC_MVZ_SN, TILEPRO_OPC_MZB_SN,
    BITFIELD(18, 4) /* index 714 */,
    TILEPRO_OPC_MZH_SN, TILEPRO_OPC_MZ_SN, TILEPRO_OPC_NOR_SN, CHILD(731),
    TILEPRO_OPC_PACKHB_SN, TILEPRO_OPC_PACKLB_SN, TILEPRO_OPC_RL_SN,
    TILEPRO_OPC_S1A_SN, TILEPRO_OPC_S2A_SN, TILEPRO_OPC_S3A_SN,
    TILEPRO_OPC_SADAB_U_SN, TILEPRO_OPC_SADAH_SN, TILEPRO_OPC_SADAH_U_SN,
    TILEPRO_OPC_SADB_U_SN, TILEPRO_OPC_SADH_SN, TILEPRO_OPC_SADH_U_SN,
    BITFIELD(12, 2) /* index 731 */,
    TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN, CHILD(736),
    BITFIELD(14, 2) /* index 736 */,
    TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN, CHILD(741),
    BITFIELD(16, 2) /* index 741 */,
    TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN,
    TILEPRO_OPC_MOVE_SN,
    BITFIELD(18, 4) /* index 746 */,
    TILEPRO_OPC_SEQB_SN, TILEPRO_OPC_SEQH_SN, TILEPRO_OPC_SEQ_SN,
    TILEPRO_OPC_SHLB_SN, TILEPRO_OPC_SHLH_SN, TILEPRO_OPC_SHL_SN,
    TILEPRO_OPC_SHRB_SN, TILEPRO_OPC_SHRH_SN, TILEPRO_OPC_SHR_SN,
    TILEPRO_OPC_SLTB_SN, TILEPRO_OPC_SLTB_U_SN, TILEPRO_OPC_SLTEB_SN,
    TILEPRO_OPC_SLTEB_U_SN, TILEPRO_OPC_SLTEH_SN, TILEPRO_OPC_SLTEH_U_SN,
    TILEPRO_OPC_SLTE_SN,
    BITFIELD(18, 4) /* index 763 */,
    TILEPRO_OPC_SLTE_U_SN, TILEPRO_OPC_SLTH_SN, TILEPRO_OPC_SLTH_U_SN,
    TILEPRO_OPC_SLT_SN, TILEPRO_OPC_SLT_U_SN, TILEPRO_OPC_SNEB_SN,
    TILEPRO_OPC_SNEH_SN, TILEPRO_OPC_SNE_SN, TILEPRO_OPC_SRAB_SN,
    TILEPRO_OPC_SRAH_SN, TILEPRO_OPC_SRA_SN, TILEPRO_OPC_SUBB_SN,
    TILEPRO_OPC_SUBH_SN, TILEPRO_OPC_SUB_SN, TILEPRO_OPC_XOR_SN,
    TILEPRO_OPC_DWORD_ALIGN_SN,
    BITFIELD(18, 3) /* index 780 */,
    CHILD(789), CHILD(792), CHILD(795), CHILD(798), CHILD(801), CHILD(804),
    CHILD(807), CHILD(810),
    BITFIELD(21, 1) /* index 789 */,
    TILEPRO_OPC_ADDS_SN, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 792 */,
    TILEPRO_OPC_SUBS_SN, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 795 */,
    TILEPRO_OPC_ADDBS_U_SN, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 798 */,
    TILEPRO_OPC_ADDHS_SN, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 801 */,
    TILEPRO_OPC_SUBBS_U_SN, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 804 */,
    TILEPRO_OPC_SUBHS_SN, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 807 */,
    TILEPRO_OPC_PACKHS_SN, TILEPRO_OPC_NONE,
    BITFIELD(21, 1) /* index 810 */,
    TILEPRO_OPC_PACKBS_U_SN, TILEPRO_OPC_NONE,
    BITFIELD(6, 2) /* index 813 */,
    TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN,
    CHILD(818),
    BITFIELD(8, 2) /* index 818 */,
    TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN,
    CHILD(823),
    BITFIELD(10, 2) /* index 823 */,
    TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN,
    TILEPRO_OPC_MOVELI_SN,
    BITFIELD(6, 2) /* index 828 */,
    TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, CHILD(833),
    BITFIELD(8, 2) /* index 833 */,
    TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, CHILD(838),
    BITFIELD(10, 2) /* index 838 */,
    TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, TILEPRO_OPC_MOVELI,
    BITFIELD(0, 2) /* index 843 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, CHILD(848),
    BITFIELD(2, 2) /* index 848 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, CHILD(853),
    BITFIELD(4, 2) /* index 853 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, CHILD(858),
    BITFIELD(6, 2) /* index 858 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, CHILD(863),
    BITFIELD(8, 2) /* index 863 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, CHILD(868),
    BITFIELD(10, 2) /* index 868 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_INFOL,
    BITFIELD(20, 2) /* index 873 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_ADDIB, TILEPRO_OPC_ADDIH, TILEPRO_OPC_ADDI,
    BITFIELD(20, 2) /* index 878 */,
    TILEPRO_OPC_MAXIB_U, TILEPRO_OPC_MAXIH, TILEPRO_OPC_MINIB_U,
    TILEPRO_OPC_MINIH,
    BITFIELD(20, 2) /* index 883 */,
    CHILD(888), TILEPRO_OPC_SEQIB, TILEPRO_OPC_SEQIH, TILEPRO_OPC_SEQI,
    BITFIELD(6, 2) /* index 888 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, CHILD(893),
    BITFIELD(8, 2) /* index 893 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, CHILD(898),
    BITFIELD(10, 2) /* index 898 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_MOVEI,
    BITFIELD(20, 2) /* index 903 */,
    TILEPRO_OPC_SLTIB, TILEPRO_OPC_SLTIB_U, TILEPRO_OPC_SLTIH,
    TILEPRO_OPC_SLTIH_U,
    BITFIELD(20, 2) /* index 908 */,
    TILEPRO_OPC_SLTI, TILEPRO_OPC_SLTI_U, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(20, 2) /* index 913 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_ADDIB_SN, TILEPRO_OPC_ADDIH_SN,
    TILEPRO_OPC_ADDI_SN,
    BITFIELD(20, 2) /* index 918 */,
    TILEPRO_OPC_MAXIB_U_SN, TILEPRO_OPC_MAXIH_SN, TILEPRO_OPC_MINIB_U_SN,
    TILEPRO_OPC_MINIH_SN,
    BITFIELD(20, 2) /* index 923 */,
    CHILD(928), TILEPRO_OPC_SEQIB_SN, TILEPRO_OPC_SEQIH_SN, TILEPRO_OPC_SEQI_SN,
    BITFIELD(6, 2) /* index 928 */,
    TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN, CHILD(933),
    BITFIELD(8, 2) /* index 933 */,
    TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN, CHILD(938),
    BITFIELD(10, 2) /* index 938 */,
    TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN,
    TILEPRO_OPC_MOVEI_SN,
    BITFIELD(20, 2) /* index 943 */,
    TILEPRO_OPC_SLTIB_SN, TILEPRO_OPC_SLTIB_U_SN, TILEPRO_OPC_SLTIH_SN,
    TILEPRO_OPC_SLTIH_U_SN,
    BITFIELD(20, 2) /* index 948 */,
    TILEPRO_OPC_SLTI_SN, TILEPRO_OPC_SLTI_U_SN, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE,
    BITFIELD(20, 2) /* index 953 */,
    TILEPRO_OPC_NONE, CHILD(958), TILEPRO_OPC_XORI, TILEPRO_OPC_NONE,
    BITFIELD(0, 2) /* index 958 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(963),
    BITFIELD(2, 2) /* index 963 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(968),
    BITFIELD(4, 2) /* index 968 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(973),
    BITFIELD(6, 2) /* index 973 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(978),
    BITFIELD(8, 2) /* index 978 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(983),
    BITFIELD(10, 2) /* index 983 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_INFO,
    BITFIELD(20, 2) /* index 988 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_ANDI_SN, TILEPRO_OPC_XORI_SN,
    TILEPRO_OPC_NONE,
    BITFIELD(17, 5) /* index 993 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_RLI, TILEPRO_OPC_SHLIB, TILEPRO_OPC_SHLIH,
    TILEPRO_OPC_SHLI, TILEPRO_OPC_SHRIB, TILEPRO_OPC_SHRIH, TILEPRO_OPC_SHRI,
    TILEPRO_OPC_SRAIB, TILEPRO_OPC_SRAIH, TILEPRO_OPC_SRAI, CHILD(1026),
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(12, 4) /* index 1026 */,
    TILEPRO_OPC_NONE, CHILD(1043), CHILD(1046), CHILD(1049), CHILD(1052),
    CHILD(1055), CHILD(1058), CHILD(1061), CHILD(1064), CHILD(1067),
    CHILD(1070), CHILD(1073), TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1043 */,
    TILEPRO_OPC_BITX, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1046 */,
    TILEPRO_OPC_BYTEX, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1049 */,
    TILEPRO_OPC_CLZ, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1052 */,
    TILEPRO_OPC_CTZ, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1055 */,
    TILEPRO_OPC_FNOP, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1058 */,
    TILEPRO_OPC_NOP, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1061 */,
    TILEPRO_OPC_PCNT, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1064 */,
    TILEPRO_OPC_TBLIDXB0, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1067 */,
    TILEPRO_OPC_TBLIDXB1, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1070 */,
    TILEPRO_OPC_TBLIDXB2, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1073 */,
    TILEPRO_OPC_TBLIDXB3, TILEPRO_OPC_NONE,
    BITFIELD(17, 5) /* index 1076 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_RLI_SN, TILEPRO_OPC_SHLIB_SN,
    TILEPRO_OPC_SHLIH_SN, TILEPRO_OPC_SHLI_SN, TILEPRO_OPC_SHRIB_SN,
    TILEPRO_OPC_SHRIH_SN, TILEPRO_OPC_SHRI_SN, TILEPRO_OPC_SRAIB_SN,
    TILEPRO_OPC_SRAIH_SN, TILEPRO_OPC_SRAI_SN, CHILD(1109), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(12, 4) /* index 1109 */,
    TILEPRO_OPC_NONE, CHILD(1126), CHILD(1129), CHILD(1132), CHILD(1135),
    CHILD(1055), CHILD(1058), CHILD(1138), CHILD(1141), CHILD(1144),
    CHILD(1147), CHILD(1150), TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1126 */,
    TILEPRO_OPC_BITX_SN, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1129 */,
    TILEPRO_OPC_BYTEX_SN, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1132 */,
    TILEPRO_OPC_CLZ_SN, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1135 */,
    TILEPRO_OPC_CTZ_SN, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1138 */,
    TILEPRO_OPC_PCNT_SN, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1141 */,
    TILEPRO_OPC_TBLIDXB0_SN, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1144 */,
    TILEPRO_OPC_TBLIDXB1_SN, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1147 */,
    TILEPRO_OPC_TBLIDXB2_SN, TILEPRO_OPC_NONE,
    BITFIELD(16, 1) /* index 1150 */,
    TILEPRO_OPC_TBLIDXB3_SN, TILEPRO_OPC_NONE,
};

static const unsigned short decode_X1_fsm[1540] = {
    BITFIELD(54, 9) /* index 0 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    CHILD(513), CHILD(561), CHILD(594), TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, CHILD(641),
    CHILD(689), CHILD(722), TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, CHILD(766),
    CHILD(766), CHILD(766), CHILD(766), CHILD(766), CHILD(766), CHILD(766),
    CHILD(766), CHILD(766), CHILD(766), CHILD(766), CHILD(766), CHILD(766),
    CHILD(766), CHILD(766), CHILD(766), CHILD(766), CHILD(766), CHILD(766),
    CHILD(766), CHILD(766), CHILD(766), CHILD(766), CHILD(766), CHILD(766),
    CHILD(766), CHILD(766), CHILD(766), CHILD(766), CHILD(766), CHILD(766),
    CHILD(766), CHILD(781), CHILD(781), CHILD(781), CHILD(781), CHILD(781),
    CHILD(781), CHILD(781), CHILD(781), CHILD(781), CHILD(781), CHILD(781),
    CHILD(781), CHILD(781), CHILD(781), CHILD(781), CHILD(781), CHILD(781),
    CHILD(781), CHILD(781), CHILD(781), CHILD(781), CHILD(781), CHILD(781),
    CHILD(781), CHILD(781), CHILD(781), CHILD(781), CHILD(781), CHILD(781),
    CHILD(781), CHILD(781), CHILD(781), CHILD(796), CHILD(796), CHILD(796),
    CHILD(796), CHILD(796), CHILD(796), CHILD(796), CHILD(796), CHILD(796),
    CHILD(796), CHILD(796), CHILD(796), CHILD(796), CHILD(796), CHILD(796),
    CHILD(796), CHILD(796), CHILD(796), CHILD(796), CHILD(796), CHILD(796),
    CHILD(796), CHILD(796), CHILD(796), CHILD(796), CHILD(796), CHILD(796),
    CHILD(796), CHILD(796), CHILD(796), CHILD(796), CHILD(796), CHILD(826),
    CHILD(826), CHILD(826), CHILD(826), CHILD(826), CHILD(826), CHILD(826),
    CHILD(826), CHILD(826), CHILD(826), CHILD(826), CHILD(826), CHILD(826),
    CHILD(826), CHILD(826), CHILD(826), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843), CHILD(843),
    CHILD(843), CHILD(860), CHILD(899), CHILD(923), CHILD(932),
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    CHILD(941), CHILD(950), CHILD(974), CHILD(983), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM,
    TILEPRO_OPC_MM, TILEPRO_OPC_MM, TILEPRO_OPC_MM, CHILD(992),
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, CHILD(1334),
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J,
    TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_J, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL,
    TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_JAL, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(49, 5) /* index 513 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_ADDB, TILEPRO_OPC_ADDH, TILEPRO_OPC_ADD,
    TILEPRO_OPC_AND, TILEPRO_OPC_INTHB, TILEPRO_OPC_INTHH, TILEPRO_OPC_INTLB,
    TILEPRO_OPC_INTLH, TILEPRO_OPC_JALRP, TILEPRO_OPC_JALR, TILEPRO_OPC_JRP,
    TILEPRO_OPC_JR, TILEPRO_OPC_LNK, TILEPRO_OPC_MAXB_U, TILEPRO_OPC_MAXH,
    TILEPRO_OPC_MINB_U, TILEPRO_OPC_MINH, TILEPRO_OPC_MNZB, TILEPRO_OPC_MNZH,
    TILEPRO_OPC_MNZ, TILEPRO_OPC_MZB, TILEPRO_OPC_MZH, TILEPRO_OPC_MZ,
    TILEPRO_OPC_NOR, CHILD(546), TILEPRO_OPC_PACKHB, TILEPRO_OPC_PACKLB,
    TILEPRO_OPC_RL, TILEPRO_OPC_S1A, TILEPRO_OPC_S2A, TILEPRO_OPC_S3A,
    BITFIELD(43, 2) /* index 546 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, CHILD(551),
    BITFIELD(45, 2) /* index 551 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, CHILD(556),
    BITFIELD(47, 2) /* index 556 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_MOVE,
    BITFIELD(49, 5) /* index 561 */,
    TILEPRO_OPC_SB, TILEPRO_OPC_SEQB, TILEPRO_OPC_SEQH, TILEPRO_OPC_SEQ,
    TILEPRO_OPC_SHLB, TILEPRO_OPC_SHLH, TILEPRO_OPC_SHL, TILEPRO_OPC_SHRB,
    TILEPRO_OPC_SHRH, TILEPRO_OPC_SHR, TILEPRO_OPC_SH, TILEPRO_OPC_SLTB,
    TILEPRO_OPC_SLTB_U, TILEPRO_OPC_SLTEB, TILEPRO_OPC_SLTEB_U,
    TILEPRO_OPC_SLTEH, TILEPRO_OPC_SLTEH_U, TILEPRO_OPC_SLTE,
    TILEPRO_OPC_SLTE_U, TILEPRO_OPC_SLTH, TILEPRO_OPC_SLTH_U, TILEPRO_OPC_SLT,
    TILEPRO_OPC_SLT_U, TILEPRO_OPC_SNEB, TILEPRO_OPC_SNEH, TILEPRO_OPC_SNE,
    TILEPRO_OPC_SRAB, TILEPRO_OPC_SRAH, TILEPRO_OPC_SRA, TILEPRO_OPC_SUBB,
    TILEPRO_OPC_SUBH, TILEPRO_OPC_SUB,
    BITFIELD(49, 4) /* index 594 */,
    CHILD(611), CHILD(614), CHILD(617), CHILD(620), CHILD(623), CHILD(626),
    CHILD(629), CHILD(632), CHILD(635), CHILD(638), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 611 */,
    TILEPRO_OPC_SW, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 614 */,
    TILEPRO_OPC_XOR, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 617 */,
    TILEPRO_OPC_ADDS, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 620 */,
    TILEPRO_OPC_SUBS, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 623 */,
    TILEPRO_OPC_ADDBS_U, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 626 */,
    TILEPRO_OPC_ADDHS, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 629 */,
    TILEPRO_OPC_SUBBS_U, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 632 */,
    TILEPRO_OPC_SUBHS, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 635 */,
    TILEPRO_OPC_PACKHS, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 638 */,
    TILEPRO_OPC_PACKBS_U, TILEPRO_OPC_NONE,
    BITFIELD(49, 5) /* index 641 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_ADDB_SN, TILEPRO_OPC_ADDH_SN,
    TILEPRO_OPC_ADD_SN, TILEPRO_OPC_AND_SN, TILEPRO_OPC_INTHB_SN,
    TILEPRO_OPC_INTHH_SN, TILEPRO_OPC_INTLB_SN, TILEPRO_OPC_INTLH_SN,
    TILEPRO_OPC_JALRP, TILEPRO_OPC_JALR, TILEPRO_OPC_JRP, TILEPRO_OPC_JR,
    TILEPRO_OPC_LNK_SN, TILEPRO_OPC_MAXB_U_SN, TILEPRO_OPC_MAXH_SN,
    TILEPRO_OPC_MINB_U_SN, TILEPRO_OPC_MINH_SN, TILEPRO_OPC_MNZB_SN,
    TILEPRO_OPC_MNZH_SN, TILEPRO_OPC_MNZ_SN, TILEPRO_OPC_MZB_SN,
    TILEPRO_OPC_MZH_SN, TILEPRO_OPC_MZ_SN, TILEPRO_OPC_NOR_SN, CHILD(674),
    TILEPRO_OPC_PACKHB_SN, TILEPRO_OPC_PACKLB_SN, TILEPRO_OPC_RL_SN,
    TILEPRO_OPC_S1A_SN, TILEPRO_OPC_S2A_SN, TILEPRO_OPC_S3A_SN,
    BITFIELD(43, 2) /* index 674 */,
    TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN, CHILD(679),
    BITFIELD(45, 2) /* index 679 */,
    TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN, CHILD(684),
    BITFIELD(47, 2) /* index 684 */,
    TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN, TILEPRO_OPC_OR_SN,
    TILEPRO_OPC_MOVE_SN,
    BITFIELD(49, 5) /* index 689 */,
    TILEPRO_OPC_SB, TILEPRO_OPC_SEQB_SN, TILEPRO_OPC_SEQH_SN,
    TILEPRO_OPC_SEQ_SN, TILEPRO_OPC_SHLB_SN, TILEPRO_OPC_SHLH_SN,
    TILEPRO_OPC_SHL_SN, TILEPRO_OPC_SHRB_SN, TILEPRO_OPC_SHRH_SN,
    TILEPRO_OPC_SHR_SN, TILEPRO_OPC_SH, TILEPRO_OPC_SLTB_SN,
    TILEPRO_OPC_SLTB_U_SN, TILEPRO_OPC_SLTEB_SN, TILEPRO_OPC_SLTEB_U_SN,
    TILEPRO_OPC_SLTEH_SN, TILEPRO_OPC_SLTEH_U_SN, TILEPRO_OPC_SLTE_SN,
    TILEPRO_OPC_SLTE_U_SN, TILEPRO_OPC_SLTH_SN, TILEPRO_OPC_SLTH_U_SN,
    TILEPRO_OPC_SLT_SN, TILEPRO_OPC_SLT_U_SN, TILEPRO_OPC_SNEB_SN,
    TILEPRO_OPC_SNEH_SN, TILEPRO_OPC_SNE_SN, TILEPRO_OPC_SRAB_SN,
    TILEPRO_OPC_SRAH_SN, TILEPRO_OPC_SRA_SN, TILEPRO_OPC_SUBB_SN,
    TILEPRO_OPC_SUBH_SN, TILEPRO_OPC_SUB_SN,
    BITFIELD(49, 4) /* index 722 */,
    CHILD(611), CHILD(739), CHILD(742), CHILD(745), CHILD(748), CHILD(751),
    CHILD(754), CHILD(757), CHILD(760), CHILD(763), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 739 */,
    TILEPRO_OPC_XOR_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 742 */,
    TILEPRO_OPC_ADDS_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 745 */,
    TILEPRO_OPC_SUBS_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 748 */,
    TILEPRO_OPC_ADDBS_U_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 751 */,
    TILEPRO_OPC_ADDHS_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 754 */,
    TILEPRO_OPC_SUBBS_U_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 757 */,
    TILEPRO_OPC_SUBHS_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 760 */,
    TILEPRO_OPC_PACKHS_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 763 */,
    TILEPRO_OPC_PACKBS_U_SN, TILEPRO_OPC_NONE,
    BITFIELD(37, 2) /* index 766 */,
    TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN,
    CHILD(771),
    BITFIELD(39, 2) /* index 771 */,
    TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN,
    CHILD(776),
    BITFIELD(41, 2) /* index 776 */,
    TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN, TILEPRO_OPC_ADDLI_SN,
    TILEPRO_OPC_MOVELI_SN,
    BITFIELD(37, 2) /* index 781 */,
    TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, CHILD(786),
    BITFIELD(39, 2) /* index 786 */,
    TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, CHILD(791),
    BITFIELD(41, 2) /* index 791 */,
    TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, TILEPRO_OPC_ADDLI, TILEPRO_OPC_MOVELI,
    BITFIELD(31, 2) /* index 796 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, CHILD(801),
    BITFIELD(33, 2) /* index 801 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, CHILD(806),
    BITFIELD(35, 2) /* index 806 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, CHILD(811),
    BITFIELD(37, 2) /* index 811 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, CHILD(816),
    BITFIELD(39, 2) /* index 816 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, CHILD(821),
    BITFIELD(41, 2) /* index 821 */,
    TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_AULI, TILEPRO_OPC_INFOL,
    BITFIELD(31, 4) /* index 826 */,
    TILEPRO_OPC_BZ, TILEPRO_OPC_BZT, TILEPRO_OPC_BNZ, TILEPRO_OPC_BNZT,
    TILEPRO_OPC_BGZ, TILEPRO_OPC_BGZT, TILEPRO_OPC_BGEZ, TILEPRO_OPC_BGEZT,
    TILEPRO_OPC_BLZ, TILEPRO_OPC_BLZT, TILEPRO_OPC_BLEZ, TILEPRO_OPC_BLEZT,
    TILEPRO_OPC_BBS, TILEPRO_OPC_BBST, TILEPRO_OPC_BBNS, TILEPRO_OPC_BBNST,
    BITFIELD(31, 4) /* index 843 */,
    TILEPRO_OPC_BZ_SN, TILEPRO_OPC_BZT_SN, TILEPRO_OPC_BNZ_SN,
    TILEPRO_OPC_BNZT_SN, TILEPRO_OPC_BGZ_SN, TILEPRO_OPC_BGZT_SN,
    TILEPRO_OPC_BGEZ_SN, TILEPRO_OPC_BGEZT_SN, TILEPRO_OPC_BLZ_SN,
    TILEPRO_OPC_BLZT_SN, TILEPRO_OPC_BLEZ_SN, TILEPRO_OPC_BLEZT_SN,
    TILEPRO_OPC_BBS_SN, TILEPRO_OPC_BBST_SN, TILEPRO_OPC_BBNS_SN,
    TILEPRO_OPC_BBNST_SN,
    BITFIELD(51, 3) /* index 860 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_ADDIB, TILEPRO_OPC_ADDIH, TILEPRO_OPC_ADDI,
    CHILD(869), TILEPRO_OPC_MAXIB_U, TILEPRO_OPC_MAXIH, TILEPRO_OPC_MFSPR,
    BITFIELD(31, 2) /* index 869 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(874),
    BITFIELD(33, 2) /* index 874 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(879),
    BITFIELD(35, 2) /* index 879 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(884),
    BITFIELD(37, 2) /* index 884 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(889),
    BITFIELD(39, 2) /* index 889 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(894),
    BITFIELD(41, 2) /* index 894 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_INFO,
    BITFIELD(51, 3) /* index 899 */,
    TILEPRO_OPC_MINIB_U, TILEPRO_OPC_MINIH, TILEPRO_OPC_MTSPR, CHILD(908),
    TILEPRO_OPC_SEQIB, TILEPRO_OPC_SEQIH, TILEPRO_OPC_SEQI, TILEPRO_OPC_SLTIB,
    BITFIELD(37, 2) /* index 908 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, CHILD(913),
    BITFIELD(39, 2) /* index 913 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, CHILD(918),
    BITFIELD(41, 2) /* index 918 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_MOVEI,
    BITFIELD(51, 3) /* index 923 */,
    TILEPRO_OPC_SLTIB_U, TILEPRO_OPC_SLTIH, TILEPRO_OPC_SLTIH_U,
    TILEPRO_OPC_SLTI, TILEPRO_OPC_SLTI_U, TILEPRO_OPC_XORI, TILEPRO_OPC_LBADD,
    TILEPRO_OPC_LBADD_U,
    BITFIELD(51, 3) /* index 932 */,
    TILEPRO_OPC_LHADD, TILEPRO_OPC_LHADD_U, TILEPRO_OPC_LWADD,
    TILEPRO_OPC_LWADD_NA, TILEPRO_OPC_SBADD, TILEPRO_OPC_SHADD,
    TILEPRO_OPC_SWADD, TILEPRO_OPC_NONE,
    BITFIELD(51, 3) /* index 941 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_ADDIB_SN, TILEPRO_OPC_ADDIH_SN,
    TILEPRO_OPC_ADDI_SN, TILEPRO_OPC_ANDI_SN, TILEPRO_OPC_MAXIB_U_SN,
    TILEPRO_OPC_MAXIH_SN, TILEPRO_OPC_MFSPR,
    BITFIELD(51, 3) /* index 950 */,
    TILEPRO_OPC_MINIB_U_SN, TILEPRO_OPC_MINIH_SN, TILEPRO_OPC_MTSPR, CHILD(959),
    TILEPRO_OPC_SEQIB_SN, TILEPRO_OPC_SEQIH_SN, TILEPRO_OPC_SEQI_SN,
    TILEPRO_OPC_SLTIB_SN,
    BITFIELD(37, 2) /* index 959 */,
    TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN, CHILD(964),
    BITFIELD(39, 2) /* index 964 */,
    TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN, CHILD(969),
    BITFIELD(41, 2) /* index 969 */,
    TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN, TILEPRO_OPC_ORI_SN,
    TILEPRO_OPC_MOVEI_SN,
    BITFIELD(51, 3) /* index 974 */,
    TILEPRO_OPC_SLTIB_U_SN, TILEPRO_OPC_SLTIH_SN, TILEPRO_OPC_SLTIH_U_SN,
    TILEPRO_OPC_SLTI_SN, TILEPRO_OPC_SLTI_U_SN, TILEPRO_OPC_XORI_SN,
    TILEPRO_OPC_LBADD_SN, TILEPRO_OPC_LBADD_U_SN,
    BITFIELD(51, 3) /* index 983 */,
    TILEPRO_OPC_LHADD_SN, TILEPRO_OPC_LHADD_U_SN, TILEPRO_OPC_LWADD_SN,
    TILEPRO_OPC_LWADD_NA_SN, TILEPRO_OPC_SBADD, TILEPRO_OPC_SHADD,
    TILEPRO_OPC_SWADD, TILEPRO_OPC_NONE,
    BITFIELD(46, 7) /* index 992 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    CHILD(1121), CHILD(1121), CHILD(1121), CHILD(1121), CHILD(1124),
    CHILD(1124), CHILD(1124), CHILD(1124), CHILD(1127), CHILD(1127),
    CHILD(1127), CHILD(1127), CHILD(1130), CHILD(1130), CHILD(1130),
    CHILD(1130), CHILD(1133), CHILD(1133), CHILD(1133), CHILD(1133),
    CHILD(1136), CHILD(1136), CHILD(1136), CHILD(1136), CHILD(1139),
    CHILD(1139), CHILD(1139), CHILD(1139), CHILD(1142), CHILD(1142),
    CHILD(1142), CHILD(1142), CHILD(1145), CHILD(1145), CHILD(1145),
    CHILD(1145), CHILD(1148), CHILD(1148), CHILD(1148), CHILD(1148),
    CHILD(1151), CHILD(1242), CHILD(1290), CHILD(1323), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1121 */,
    TILEPRO_OPC_RLI, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1124 */,
    TILEPRO_OPC_SHLIB, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1127 */,
    TILEPRO_OPC_SHLIH, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1130 */,
    TILEPRO_OPC_SHLI, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1133 */,
    TILEPRO_OPC_SHRIB, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1136 */,
    TILEPRO_OPC_SHRIH, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1139 */,
    TILEPRO_OPC_SHRI, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1142 */,
    TILEPRO_OPC_SRAIB, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1145 */,
    TILEPRO_OPC_SRAIH, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1148 */,
    TILEPRO_OPC_SRAI, TILEPRO_OPC_NONE,
    BITFIELD(43, 3) /* index 1151 */,
    TILEPRO_OPC_NONE, CHILD(1160), CHILD(1163), CHILD(1166), CHILD(1169),
    CHILD(1172), CHILD(1175), CHILD(1178),
    BITFIELD(53, 1) /* index 1160 */,
    TILEPRO_OPC_DRAIN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1163 */,
    TILEPRO_OPC_DTLBPR, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1166 */,
    TILEPRO_OPC_FINV, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1169 */,
    TILEPRO_OPC_FLUSH, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1172 */,
    TILEPRO_OPC_FNOP, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1175 */,
    TILEPRO_OPC_ICOH, TILEPRO_OPC_NONE,
    BITFIELD(31, 2) /* index 1178 */,
    CHILD(1183), CHILD(1211), CHILD(1239), CHILD(1239),
    BITFIELD(53, 1) /* index 1183 */,
    CHILD(1186), TILEPRO_OPC_NONE,
    BITFIELD(33, 2) /* index 1186 */,
    TILEPRO_OPC_ILL, TILEPRO_OPC_ILL, TILEPRO_OPC_ILL, CHILD(1191),
    BITFIELD(35, 2) /* index 1191 */,
    TILEPRO_OPC_ILL, CHILD(1196), TILEPRO_OPC_ILL, TILEPRO_OPC_ILL,
    BITFIELD(37, 2) /* index 1196 */,
    TILEPRO_OPC_ILL, CHILD(1201), TILEPRO_OPC_ILL, TILEPRO_OPC_ILL,
    BITFIELD(39, 2) /* index 1201 */,
    TILEPRO_OPC_ILL, CHILD(1206), TILEPRO_OPC_ILL, TILEPRO_OPC_ILL,
    BITFIELD(41, 2) /* index 1206 */,
    TILEPRO_OPC_ILL, TILEPRO_OPC_ILL, TILEPRO_OPC_BPT, TILEPRO_OPC_ILL,
    BITFIELD(53, 1) /* index 1211 */,
    CHILD(1214), TILEPRO_OPC_NONE,
    BITFIELD(33, 2) /* index 1214 */,
    TILEPRO_OPC_ILL, TILEPRO_OPC_ILL, TILEPRO_OPC_ILL, CHILD(1219),
    BITFIELD(35, 2) /* index 1219 */,
    TILEPRO_OPC_ILL, CHILD(1224), TILEPRO_OPC_ILL, TILEPRO_OPC_ILL,
    BITFIELD(37, 2) /* index 1224 */,
    TILEPRO_OPC_ILL, CHILD(1229), TILEPRO_OPC_ILL, TILEPRO_OPC_ILL,
    BITFIELD(39, 2) /* index 1229 */,
    TILEPRO_OPC_ILL, CHILD(1234), TILEPRO_OPC_ILL, TILEPRO_OPC_ILL,
    BITFIELD(41, 2) /* index 1234 */,
    TILEPRO_OPC_ILL, TILEPRO_OPC_ILL, TILEPRO_OPC_RAISE, TILEPRO_OPC_ILL,
    BITFIELD(53, 1) /* index 1239 */,
    TILEPRO_OPC_ILL, TILEPRO_OPC_NONE,
    BITFIELD(43, 3) /* index 1242 */,
    CHILD(1251), CHILD(1254), CHILD(1257), CHILD(1275), CHILD(1278),
    CHILD(1281), CHILD(1284), CHILD(1287),
    BITFIELD(53, 1) /* index 1251 */,
    TILEPRO_OPC_INV, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1254 */,
    TILEPRO_OPC_IRET, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1257 */,
    CHILD(1260), TILEPRO_OPC_NONE,
    BITFIELD(31, 2) /* index 1260 */,
    TILEPRO_OPC_LB, TILEPRO_OPC_LB, TILEPRO_OPC_LB, CHILD(1265),
    BITFIELD(33, 2) /* index 1265 */,
    TILEPRO_OPC_LB, TILEPRO_OPC_LB, TILEPRO_OPC_LB, CHILD(1270),
    BITFIELD(35, 2) /* index 1270 */,
    TILEPRO_OPC_LB, TILEPRO_OPC_LB, TILEPRO_OPC_LB, TILEPRO_OPC_PREFETCH,
    BITFIELD(53, 1) /* index 1275 */,
    TILEPRO_OPC_LB_U, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1278 */,
    TILEPRO_OPC_LH, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1281 */,
    TILEPRO_OPC_LH_U, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1284 */,
    TILEPRO_OPC_LW, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1287 */,
    TILEPRO_OPC_MF, TILEPRO_OPC_NONE,
    BITFIELD(43, 3) /* index 1290 */,
    CHILD(1299), CHILD(1302), CHILD(1305), CHILD(1308), CHILD(1311),
    CHILD(1314), CHILD(1317), CHILD(1320),
    BITFIELD(53, 1) /* index 1299 */,
    TILEPRO_OPC_NAP, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1302 */,
    TILEPRO_OPC_NOP, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1305 */,
    TILEPRO_OPC_SWINT0, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1308 */,
    TILEPRO_OPC_SWINT1, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1311 */,
    TILEPRO_OPC_SWINT2, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1314 */,
    TILEPRO_OPC_SWINT3, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1317 */,
    TILEPRO_OPC_TNS, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1320 */,
    TILEPRO_OPC_WH64, TILEPRO_OPC_NONE,
    BITFIELD(43, 2) /* index 1323 */,
    CHILD(1328), TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(45, 1) /* index 1328 */,
    CHILD(1331), TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1331 */,
    TILEPRO_OPC_LW_NA, TILEPRO_OPC_NONE,
    BITFIELD(46, 7) /* index 1334 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    CHILD(1463), CHILD(1463), CHILD(1463), CHILD(1463), CHILD(1466),
    CHILD(1466), CHILD(1466), CHILD(1466), CHILD(1469), CHILD(1469),
    CHILD(1469), CHILD(1469), CHILD(1472), CHILD(1472), CHILD(1472),
    CHILD(1472), CHILD(1475), CHILD(1475), CHILD(1475), CHILD(1475),
    CHILD(1478), CHILD(1478), CHILD(1478), CHILD(1478), CHILD(1481),
    CHILD(1481), CHILD(1481), CHILD(1481), CHILD(1484), CHILD(1484),
    CHILD(1484), CHILD(1484), CHILD(1487), CHILD(1487), CHILD(1487),
    CHILD(1487), CHILD(1490), CHILD(1490), CHILD(1490), CHILD(1490),
    CHILD(1151), CHILD(1493), CHILD(1517), CHILD(1529), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1463 */,
    TILEPRO_OPC_RLI_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1466 */,
    TILEPRO_OPC_SHLIB_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1469 */,
    TILEPRO_OPC_SHLIH_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1472 */,
    TILEPRO_OPC_SHLI_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1475 */,
    TILEPRO_OPC_SHRIB_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1478 */,
    TILEPRO_OPC_SHRIH_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1481 */,
    TILEPRO_OPC_SHRI_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1484 */,
    TILEPRO_OPC_SRAIB_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1487 */,
    TILEPRO_OPC_SRAIH_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1490 */,
    TILEPRO_OPC_SRAI_SN, TILEPRO_OPC_NONE,
    BITFIELD(43, 3) /* index 1493 */,
    CHILD(1251), CHILD(1254), CHILD(1502), CHILD(1505), CHILD(1508),
    CHILD(1511), CHILD(1514), CHILD(1287),
    BITFIELD(53, 1) /* index 1502 */,
    TILEPRO_OPC_LB_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1505 */,
    TILEPRO_OPC_LB_U_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1508 */,
    TILEPRO_OPC_LH_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1511 */,
    TILEPRO_OPC_LH_U_SN, TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1514 */,
    TILEPRO_OPC_LW_SN, TILEPRO_OPC_NONE,
    BITFIELD(43, 3) /* index 1517 */,
    CHILD(1299), CHILD(1302), CHILD(1305), CHILD(1308), CHILD(1311),
    CHILD(1314), CHILD(1526), CHILD(1320),
    BITFIELD(53, 1) /* index 1526 */,
    TILEPRO_OPC_TNS_SN, TILEPRO_OPC_NONE,
    BITFIELD(43, 2) /* index 1529 */,
    CHILD(1534), TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(45, 1) /* index 1534 */,
    CHILD(1537), TILEPRO_OPC_NONE,
    BITFIELD(53, 1) /* index 1537 */,
    TILEPRO_OPC_LW_NA_SN, TILEPRO_OPC_NONE,
};

static const unsigned short decode_Y0_fsm[168] = {
    BITFIELD(27, 4) /* index 0 */,
    TILEPRO_OPC_NONE, CHILD(17), CHILD(22), CHILD(27), CHILD(47), CHILD(52),
    CHILD(57), CHILD(62), CHILD(67), TILEPRO_OPC_ADDI, CHILD(72), CHILD(102),
    TILEPRO_OPC_SEQI, CHILD(117), TILEPRO_OPC_SLTI, TILEPRO_OPC_SLTI_U,
    BITFIELD(18, 2) /* index 17 */,
    TILEPRO_OPC_ADD, TILEPRO_OPC_S1A, TILEPRO_OPC_S2A, TILEPRO_OPC_SUB,
    BITFIELD(18, 2) /* index 22 */,
    TILEPRO_OPC_MNZ, TILEPRO_OPC_MVNZ, TILEPRO_OPC_MVZ, TILEPRO_OPC_MZ,
    BITFIELD(18, 2) /* index 27 */,
    TILEPRO_OPC_AND, TILEPRO_OPC_NOR, CHILD(32), TILEPRO_OPC_XOR,
    BITFIELD(12, 2) /* index 32 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, CHILD(37),
    BITFIELD(14, 2) /* index 37 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, CHILD(42),
    BITFIELD(16, 2) /* index 42 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_MOVE,
    BITFIELD(18, 2) /* index 47 */,
    TILEPRO_OPC_RL, TILEPRO_OPC_SHL, TILEPRO_OPC_SHR, TILEPRO_OPC_SRA,
    BITFIELD(18, 2) /* index 52 */,
    TILEPRO_OPC_SLTE, TILEPRO_OPC_SLTE_U, TILEPRO_OPC_SLT, TILEPRO_OPC_SLT_U,
    BITFIELD(18, 2) /* index 57 */,
    TILEPRO_OPC_MULHLSA_UU, TILEPRO_OPC_S3A, TILEPRO_OPC_SEQ, TILEPRO_OPC_SNE,
    BITFIELD(18, 2) /* index 62 */,
    TILEPRO_OPC_MULHH_SS, TILEPRO_OPC_MULHH_UU, TILEPRO_OPC_MULLL_SS,
    TILEPRO_OPC_MULLL_UU,
    BITFIELD(18, 2) /* index 67 */,
    TILEPRO_OPC_MULHHA_SS, TILEPRO_OPC_MULHHA_UU, TILEPRO_OPC_MULLLA_SS,
    TILEPRO_OPC_MULLLA_UU,
    BITFIELD(0, 2) /* index 72 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(77),
    BITFIELD(2, 2) /* index 77 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(82),
    BITFIELD(4, 2) /* index 82 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(87),
    BITFIELD(6, 2) /* index 87 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(92),
    BITFIELD(8, 2) /* index 92 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(97),
    BITFIELD(10, 2) /* index 97 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_INFO,
    BITFIELD(6, 2) /* index 102 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, CHILD(107),
    BITFIELD(8, 2) /* index 107 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, CHILD(112),
    BITFIELD(10, 2) /* index 112 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_MOVEI,
    BITFIELD(15, 5) /* index 117 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_RLI, TILEPRO_OPC_RLI, TILEPRO_OPC_RLI, TILEPRO_OPC_RLI,
    TILEPRO_OPC_SHLI, TILEPRO_OPC_SHLI, TILEPRO_OPC_SHLI, TILEPRO_OPC_SHLI,
    TILEPRO_OPC_SHRI, TILEPRO_OPC_SHRI, TILEPRO_OPC_SHRI, TILEPRO_OPC_SHRI,
    TILEPRO_OPC_SRAI, TILEPRO_OPC_SRAI, TILEPRO_OPC_SRAI, TILEPRO_OPC_SRAI,
    CHILD(150), CHILD(159), TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(12, 3) /* index 150 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_BITX, TILEPRO_OPC_BYTEX, TILEPRO_OPC_CLZ,
    TILEPRO_OPC_CTZ, TILEPRO_OPC_FNOP, TILEPRO_OPC_NOP, TILEPRO_OPC_PCNT,
    BITFIELD(12, 3) /* index 159 */,
    TILEPRO_OPC_TBLIDXB0, TILEPRO_OPC_TBLIDXB1, TILEPRO_OPC_TBLIDXB2,
    TILEPRO_OPC_TBLIDXB3, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE,
};

static const unsigned short decode_Y1_fsm[140] = {
    BITFIELD(59, 4) /* index 0 */,
    TILEPRO_OPC_NONE, CHILD(17), CHILD(22), CHILD(27), CHILD(47), CHILD(52),
    CHILD(57), TILEPRO_OPC_ADDI, CHILD(62), CHILD(92), TILEPRO_OPC_SEQI,
    CHILD(107), TILEPRO_OPC_SLTI, TILEPRO_OPC_SLTI_U, TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE,
    BITFIELD(49, 2) /* index 17 */,
    TILEPRO_OPC_ADD, TILEPRO_OPC_S1A, TILEPRO_OPC_S2A, TILEPRO_OPC_SUB,
    BITFIELD(49, 2) /* index 22 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_MNZ, TILEPRO_OPC_MZ, TILEPRO_OPC_NONE,
    BITFIELD(49, 2) /* index 27 */,
    TILEPRO_OPC_AND, TILEPRO_OPC_NOR, CHILD(32), TILEPRO_OPC_XOR,
    BITFIELD(43, 2) /* index 32 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, CHILD(37),
    BITFIELD(45, 2) /* index 37 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, CHILD(42),
    BITFIELD(47, 2) /* index 42 */,
    TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_OR, TILEPRO_OPC_MOVE,
    BITFIELD(49, 2) /* index 47 */,
    TILEPRO_OPC_RL, TILEPRO_OPC_SHL, TILEPRO_OPC_SHR, TILEPRO_OPC_SRA,
    BITFIELD(49, 2) /* index 52 */,
    TILEPRO_OPC_SLTE, TILEPRO_OPC_SLTE_U, TILEPRO_OPC_SLT, TILEPRO_OPC_SLT_U,
    BITFIELD(49, 2) /* index 57 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_S3A, TILEPRO_OPC_SEQ, TILEPRO_OPC_SNE,
    BITFIELD(31, 2) /* index 62 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(67),
    BITFIELD(33, 2) /* index 67 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(72),
    BITFIELD(35, 2) /* index 72 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(77),
    BITFIELD(37, 2) /* index 77 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(82),
    BITFIELD(39, 2) /* index 82 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, CHILD(87),
    BITFIELD(41, 2) /* index 87 */,
    TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_ANDI, TILEPRO_OPC_INFO,
    BITFIELD(37, 2) /* index 92 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, CHILD(97),
    BITFIELD(39, 2) /* index 97 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, CHILD(102),
    BITFIELD(41, 2) /* index 102 */,
    TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_ORI, TILEPRO_OPC_MOVEI,
    BITFIELD(48, 3) /* index 107 */,
    TILEPRO_OPC_NONE, TILEPRO_OPC_RLI, TILEPRO_OPC_SHLI, TILEPRO_OPC_SHRI,
    TILEPRO_OPC_SRAI, CHILD(116), TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(43, 3) /* index 116 */,
    TILEPRO_OPC_NONE, CHILD(125), CHILD(130), CHILD(135), TILEPRO_OPC_NONE,
    TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(46, 2) /* index 125 */,
    TILEPRO_OPC_FNOP, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(46, 2) /* index 130 */,
    TILEPRO_OPC_ILL, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
    BITFIELD(46, 2) /* index 135 */,
    TILEPRO_OPC_NOP, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE, TILEPRO_OPC_NONE,
};

static const unsigned short decode_Y2_fsm[24] = {
    BITFIELD(56, 3) /* index 0 */,
    CHILD(9), TILEPRO_OPC_LB_U, TILEPRO_OPC_LH, TILEPRO_OPC_LH_U,
    TILEPRO_OPC_LW, TILEPRO_OPC_SB, TILEPRO_OPC_SH, TILEPRO_OPC_SW,
    BITFIELD(20, 2) /* index 9 */,
    TILEPRO_OPC_LB, TILEPRO_OPC_LB, TILEPRO_OPC_LB, CHILD(14),
    BITFIELD(22, 2) /* index 14 */,
    TILEPRO_OPC_LB, TILEPRO_OPC_LB, TILEPRO_OPC_LB, CHILD(19),
    BITFIELD(24, 2) /* index 19 */,
    TILEPRO_OPC_LB, TILEPRO_OPC_LB, TILEPRO_OPC_LB, TILEPRO_OPC_PREFETCH,
};

#undef BITFIELD
#undef CHILD
const unsigned short * const
tilepro_bundle_decoder_fsms[TILEPRO_NUM_PIPELINE_ENCODINGS] = {
    decode_X0_fsm,
    decode_X1_fsm,
    decode_Y0_fsm,
    decode_Y1_fsm,
    decode_Y2_fsm
};
const struct tilepro_operand tilepro_operands[43] = {
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_IMM8_X0),
        8, 1, 0, 0, 0, 0,
        create_Imm8_X0, get_Imm8_X0
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_IMM8_X1),
        8, 1, 0, 0, 0, 0,
        create_Imm8_X1, get_Imm8_X1
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_IMM8_Y0),
        8, 1, 0, 0, 0, 0,
        create_Imm8_Y0, get_Imm8_Y0
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_IMM8_Y1),
        8, 1, 0, 0, 0, 0,
        create_Imm8_Y1, get_Imm8_Y1
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_IMM16_X0),
        16, 1, 0, 0, 0, 0,
        create_Imm16_X0, get_Imm16_X0
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_IMM16_X1),
        16, 1, 0, 0, 0, 0,
        create_Imm16_X1, get_Imm16_X1
    },
    {
        TILEPRO_OP_TYPE_ADDRESS, BFD_RELOC(TILEPRO_JOFFLONG_X1),
        29, 1, 0, 0, 1, TILEPRO_LOG2_BUNDLE_ALIGNMENT_IN_BYTES,
        create_JOffLong_X1, get_JOffLong_X1
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 0, 1, 0, 0,
        create_Dest_X0, get_Dest_X0
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 0, 0, 0,
        create_SrcA_X0, get_SrcA_X0
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 0, 1, 0, 0,
        create_Dest_X1, get_Dest_X1
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 0, 0, 0,
        create_SrcA_X1, get_SrcA_X1
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 0, 1, 0, 0,
        create_Dest_Y0, get_Dest_Y0
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 0, 0, 0,
        create_SrcA_Y0, get_SrcA_Y0
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 0, 1, 0, 0,
        create_Dest_Y1, get_Dest_Y1
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 0, 0, 0,
        create_SrcA_Y1, get_SrcA_Y1
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 0, 0, 0,
        create_SrcA_Y2, get_SrcA_Y2
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 0, 0, 0,
        create_SrcB_X0, get_SrcB_X0
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 0, 0, 0,
        create_SrcB_X1, get_SrcB_X1
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 0, 0, 0,
        create_SrcB_Y0, get_SrcB_Y0
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 0, 0, 0,
        create_SrcB_Y1, get_SrcB_Y1
    },
    {
        TILEPRO_OP_TYPE_ADDRESS, BFD_RELOC(TILEPRO_BROFF_X1),
        17, 1, 0, 0, 1, TILEPRO_LOG2_BUNDLE_ALIGNMENT_IN_BYTES,
        create_BrOff_X1, get_BrOff_X1
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 1, 0, 0,
        create_Dest_X0, get_Dest_X0
    },
    {
        TILEPRO_OP_TYPE_ADDRESS, BFD_RELOC(NONE),
        28, 1, 0, 0, 1, TILEPRO_LOG2_BUNDLE_ALIGNMENT_IN_BYTES,
        create_JOff_X1, get_JOff_X1
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 0, 1, 0, 0,
        create_SrcBDest_Y2, get_SrcBDest_Y2
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 1, 0, 0,
        create_SrcA_X1, get_SrcA_X1
    },
    {
        TILEPRO_OP_TYPE_SPR, BFD_RELOC(TILEPRO_MF_IMM15_X1),
        15, 0, 0, 0, 0, 0,
        create_MF_Imm15_X1, get_MF_Imm15_X1
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_MMSTART_X0),
        5, 0, 0, 0, 0, 0,
        create_MMStart_X0, get_MMStart_X0
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_MMEND_X0),
        5, 0, 0, 0, 0, 0,
        create_MMEnd_X0, get_MMEnd_X0
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_MMSTART_X1),
        5, 0, 0, 0, 0, 0,
        create_MMStart_X1, get_MMStart_X1
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_MMEND_X1),
        5, 0, 0, 0, 0, 0,
        create_MMEnd_X1, get_MMEnd_X1
    },
    {
        TILEPRO_OP_TYPE_SPR, BFD_RELOC(TILEPRO_MT_IMM15_X1),
        15, 0, 0, 0, 0, 0,
        create_MT_Imm15_X1, get_MT_Imm15_X1
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 1, 0, 0,
        create_Dest_Y0, get_Dest_Y0
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_SHAMT_X0),
        5, 0, 0, 0, 0, 0,
        create_ShAmt_X0, get_ShAmt_X0
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_SHAMT_X1),
        5, 0, 0, 0, 0, 0,
        create_ShAmt_X1, get_ShAmt_X1
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_SHAMT_Y0),
        5, 0, 0, 0, 0, 0,
        create_ShAmt_Y0, get_ShAmt_Y0
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_SHAMT_Y1),
        5, 0, 0, 0, 0, 0,
        create_ShAmt_Y1, get_ShAmt_Y1
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        6, 0, 1, 0, 0, 0,
        create_SrcBDest_Y2, get_SrcBDest_Y2
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(TILEPRO_DEST_IMM8_X1),
        8, 1, 0, 0, 0, 0,
        create_Dest_Imm8_X1, get_Dest_Imm8_X1
    },
    {
        TILEPRO_OP_TYPE_ADDRESS, BFD_RELOC(NONE),
        10, 1, 0, 0, 1, TILEPRO_LOG2_SN_INSTRUCTION_SIZE_IN_BYTES,
        create_BrOff_SN, get_BrOff_SN
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(NONE),
        8, 0, 0, 0, 0, 0,
        create_Imm8_SN, get_Imm8_SN
    },
    {
        TILEPRO_OP_TYPE_IMMEDIATE, BFD_RELOC(NONE),
        8, 1, 0, 0, 0, 0,
        create_Imm8_SN, get_Imm8_SN
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        2, 0, 0, 1, 0, 0,
        create_Dest_SN, get_Dest_SN
    },
    {
        TILEPRO_OP_TYPE_REGISTER, BFD_RELOC(NONE),
        2, 0, 1, 0, 0, 0,
        create_Src_SN, get_Src_SN
    }
};




/* Given a set of bundle bits and a specific pipe, returns which
 * instruction the bundle contains in that pipe.
 */
const struct tilepro_opcode *
find_opcode(tilepro_bundle_bits bits, tilepro_pipeline pipe)
{
    const unsigned short *table = tilepro_bundle_decoder_fsms[pipe];
    int index = 0;

    while (1) {
        unsigned short bitspec = table[index];
        unsigned int bitfield =
            ((unsigned int)(bits >> (bitspec & 63))) & (bitspec >> 6);

        unsigned short next = table[index + 1 + bitfield];
        if (next <= TILEPRO_OPC_NONE) {
            return &tilepro_opcodes[next];
        }

        index = next - TILEPRO_OPC_NONE;
    }
}


int
parse_insn_tilepro(tilepro_bundle_bits bits,
                   unsigned int pc,
                   struct tilepro_decoded_instruction
                   decoded[TILEPRO_MAX_INSTRUCTIONS_PER_BUNDLE])
{
    int num_instructions = 0;
    int pipe;

    int min_pipe, max_pipe;
    if ((bits & TILEPRO_BUNDLE_Y_ENCODING_MASK) == 0) {
        min_pipe = TILEPRO_PIPELINE_X0;
        max_pipe = TILEPRO_PIPELINE_X1;
    } else {
        min_pipe = TILEPRO_PIPELINE_Y0;
        max_pipe = TILEPRO_PIPELINE_Y2;
    }

    /* For each pipe, find an instruction that fits. */
    for (pipe = min_pipe; pipe <= max_pipe; pipe++) {
        const struct tilepro_opcode *opc;
        struct tilepro_decoded_instruction *d;
        int i;

        d = &decoded[num_instructions++];
        opc = find_opcode (bits, (tilepro_pipeline)pipe);
        d->opcode = opc;

        /* Decode each operand, sign extending, etc. as appropriate. */
        for (i = 0; i < opc->num_operands; i++) {
            const struct tilepro_operand *op =
                    &tilepro_operands[opc->operands[pipe][i]];
            int opval = op->extract (bits);
            if (op->is_signed) {
                /* Sign-extend the operand. */
                int shift = (int)((sizeof(int) * 8) - op->num_bits);
                opval = (opval << shift) >> shift;
            }

            /* Adjust PC-relative scaled branch offsets. */
            if (op->type == TILEPRO_OP_TYPE_ADDRESS) {
                opval *= TILEPRO_BUNDLE_SIZE_IN_BYTES;
                opval += (int)pc;
            }

            /* Record the final value. */
            d->operands[i] = op;
            d->operand_values[i] = opval;
        }
    }

    return num_instructions;
}
