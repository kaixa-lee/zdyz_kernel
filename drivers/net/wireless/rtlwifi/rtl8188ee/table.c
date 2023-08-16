/******************************************************************************
 *
 * Copyright(c) 2009-2013  Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Created on  2010/ 5/18,  1:41
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/

#include "table.h"
u32 RTL8188EEPHY_REG_1TARRAY[] = {
    0x800, 0x80040000,
    0x804, 0x00000003,
    0x808, 0x0000FC00,
    0x80C, 0x0000000A,
    0x810, 0x10001331,
    0x814, 0x020C3D10,
    0x818, 0x02200385,
    0x81C, 0x00000000,
    0x820, 0x01000100,
    0x824, 0x00390204,
    0x828, 0x00000000,
    0x82C, 0x00000000,
    0x830, 0x00000000,
    0x834, 0x00000000,
    0x838, 0x00000000,
    0x83C, 0x00000000,
    0x840, 0x00010000,
    0x844, 0x00000000,
    0x848, 0x00000000,
    0x84C, 0x00000000,
    0x850, 0x00000000,
    0x854, 0x00000000,
    0x858, 0x569A11A9,
    0x85C, 0x01000014,
    0x860, 0x66F60110,
    0x864, 0x061F0649,
    0x868, 0x00000000,
    0x86C, 0x27272700,
    0x870, 0x07000760,
    0x874, 0x25004000,
    0x878, 0x00000808,
    0x87C, 0x00000000,
    0x880, 0xB0000C1C,
    0x884, 0x00000001,
    0x888, 0x00000000,
    0x88C, 0xCCC000C0,
    0x890, 0x00000800,
    0x894, 0xFFFFFFFE,
    0x898, 0x40302010,
    0x89C, 0x00706050,
    0x900, 0x00000000,
    0x904, 0x00000023,
    0x908, 0x00000000,
    0x90C, 0x81121111,
    0x910, 0x00000002,
    0x914, 0x00000201,
    0xA00, 0x00D047C8,
    0xA04, 0x80FF000C,
    0xA08, 0x8C838300,
    0xA0C, 0x2E7F120F,
    0xA10, 0x9500BB78,
    0xA14, 0x1114D028,
    0xA18, 0x00881117,
    0xA1C, 0x89140F00,
    0xA20, 0x1A1B0000,
    0xA24, 0x090E1317,
    0xA28, 0x00000204,
    0xA2C, 0x00D30000,
    0xA70, 0x101FBF00,
    0xA74, 0x00000007,
    0xA78, 0x00000900,
    0xA7C, 0x225B0606,
    0xA80, 0x218075B1,
    0xB2C, 0x80000000,
    0xC00, 0x48071D40,
    0xC04, 0x03A05611,
    0xC08, 0x000000E4,
    0xC0C, 0x6C6C6C6C,
    0xC10, 0x08800000,
    0xC14, 0x40000100,
    0xC18, 0x08800000,
    0xC1C, 0x40000100,
    0xC20, 0x00000000,
    0xC24, 0x00000000,
    0xC28, 0x00000000,
    0xC2C, 0x00000000,
    0xC30, 0x69E9AC47,
    0xC34, 0x469652AF,
    0xC38, 0x49795994,
    0xC3C, 0x0A97971C,
    0xC40, 0x1F7C403F,
    0xC44, 0x000100B7,
    0xC48, 0xEC020107,
    0xC4C, 0x007F037F,
    0xC50, 0x69553420,
    0xC54, 0x43BC0094,
    0xC58, 0x00013169,
    0xC5C, 0x00250492,
    0xC60, 0x00000000,
    0xC64, 0x7112848B,
    0xC68, 0x47C00BFF,
    0xC6C, 0x00000036,
    0xC70, 0x2C7F000D,
    0xC74, 0x020610DB,
    0xC78, 0x0000001F,
    0xC7C, 0x00B91612,
    0xC80, 0x390000E4,
    0xC84, 0x20F60000,
    0xC88, 0x40000100,
    0xC8C, 0x20200000,
    0xC90, 0x00091521,
    0xC94, 0x00000000,
    0xC98, 0x00121820,
    0xC9C, 0x00007F7F,
    0xCA0, 0x00000000,
    0xCA4, 0x000300A0,
    0xCA8, 0x00000000,
    0xCAC, 0x00000000,
    0xCB0, 0x00000000,
    0xCB4, 0x00000000,
    0xCB8, 0x00000000,
    0xCBC, 0x28000000,
    0xCC0, 0x00000000,
    0xCC4, 0x00000000,
    0xCC8, 0x00000000,
    0xCCC, 0x00000000,
    0xCD0, 0x00000000,
    0xCD4, 0x00000000,
    0xCD8, 0x64B22427,
    0xCDC, 0x00766932,
    0xCE0, 0x00222222,
    0xCE4, 0x00000000,
    0xCE8, 0x37644302,
    0xCEC, 0x2F97D40C,
    0xD00, 0x00000740,
    0xD04, 0x00020401,
    0xD08, 0x0000907F,
    0xD0C, 0x20010201,
    0xD10, 0xA0633333,
    0xD14, 0x3333BC43,
    0xD18, 0x7A8F5B6F,
    0xD2C, 0xCC979975,
    0xD30, 0x00000000,
    0xD34, 0x80608000,
    0xD38, 0x00000000,
    0xD3C, 0x00127353,
    0xD40, 0x00000000,
    0xD44, 0x00000000,
    0xD48, 0x00000000,
    0xD4C, 0x00000000,
    0xD50, 0x6437140A,
    0xD54, 0x00000000,
    0xD58, 0x00000282,
    0xD5C, 0x30032064,
    0xD60, 0x4653DE68,
    0xD64, 0x04518A3C,
    0xD68, 0x00002101,
    0xD6C, 0x2A201C16,
    0xD70, 0x1812362E,
    0xD74, 0x322C2220,
    0xD78, 0x000E3C24,
    0xE00, 0x2D2D2D2D,
    0xE04, 0x2D2D2D2D,
    0xE08, 0x0390272D,
    0xE10, 0x2D2D2D2D,
    0xE14, 0x2D2D2D2D,
    0xE18, 0x2D2D2D2D,
    0xE1C, 0x2D2D2D2D,
    0xE28, 0x00000000,
    0xE30, 0x1000DC1F,
    0xE34, 0x10008C1F,
    0xE38, 0x02140102,
    0xE3C, 0x681604C2,
    0xE40, 0x01007C00,
    0xE44, 0x01004800,
    0xE48, 0xFB000000,
    0xE4C, 0x000028D1,
    0xE50, 0x1000DC1F,
    0xE54, 0x10008C1F,
    0xE58, 0x02140102,
    0xE5C, 0x28160D05,
    0xE60, 0x00000008,
    0xE68, 0x001B25A4,
    0xE6C, 0x00C00014,
    0xE70, 0x00C00014,
    0xE74, 0x01000014,
    0xE78, 0x01000014,
    0xE7C, 0x01000014,
    0xE80, 0x01000014,
    0xE84, 0x00C00014,
    0xE88, 0x01000014,
    0xE8C, 0x00C00014,
    0xED0, 0x00C00014,
    0xED4, 0x00C00014,
    0xED8, 0x00C00014,
    0xEDC, 0x00000014,
    0xEE0, 0x00000014,
    0xEEC, 0x01C00014,
    0xF14, 0x00000003,
    0xF4C, 0x00000000,
    0xF00, 0x00000300,

};

u32 RTL8188EEPHY_REG_ARRAY_PG[] = {
    0xE00, 0xFFFFFFFF, 0x06070809,
    0xE04, 0xFFFFFFFF, 0x02020405,
    0xE08, 0x0000FF00, 0x00000006,
    0x86C, 0xFFFFFF00, 0x00020400,
    0xE10, 0xFFFFFFFF, 0x08090A0B,
    0xE14, 0xFFFFFFFF, 0x01030607,
    0xE18, 0xFFFFFFFF, 0x08090A0B,
    0xE1C, 0xFFFFFFFF, 0x01030607,
    0xE00, 0xFFFFFFFF, 0x00000000,
    0xE04, 0xFFFFFFFF, 0x00000000,
    0xE08, 0x0000FF00, 0x00000000,
    0x86C, 0xFFFFFF00, 0x00000000,
    0xE10, 0xFFFFFFFF, 0x00000000,
    0xE14, 0xFFFFFFFF, 0x00000000,
    0xE18, 0xFFFFFFFF, 0x00000000,
    0xE1C, 0xFFFFFFFF, 0x00000000,
    0xE00, 0xFFFFFFFF, 0x02020202,
    0xE04, 0xFFFFFFFF, 0x00020202,
    0xE08, 0x0000FF00, 0x00000000,
    0x86C, 0xFFFFFF00, 0x00000000,
    0xE10, 0xFFFFFFFF, 0x04040404,
    0xE14, 0xFFFFFFFF, 0x00020404,
    0xE18, 0xFFFFFFFF, 0x00000000,
    0xE1C, 0xFFFFFFFF, 0x00000000,
    0xE00, 0xFFFFFFFF, 0x02020202,
    0xE04, 0xFFFFFFFF, 0x00020202,
    0xE08, 0x0000FF00, 0x00000000,
    0x86C, 0xFFFFFF00, 0x00000000,
    0xE10, 0xFFFFFFFF, 0x04040404,
    0xE14, 0xFFFFFFFF, 0x00020404,
    0xE18, 0xFFFFFFFF, 0x00000000,
    0xE1C, 0xFFFFFFFF, 0x00000000,
    0xE00, 0xFFFFFFFF, 0x00000000,
    0xE04, 0xFFFFFFFF, 0x00000000,
    0xE08, 0x0000FF00, 0x00000000,
    0x86C, 0xFFFFFF00, 0x00000000,
    0xE10, 0xFFFFFFFF, 0x00000000,
    0xE14, 0xFFFFFFFF, 0x00000000,
    0xE18, 0xFFFFFFFF, 0x00000000,
    0xE1C, 0xFFFFFFFF, 0x00000000,
    0xE00, 0xFFFFFFFF, 0x02020202,
    0xE04, 0xFFFFFFFF, 0x00020202,
    0xE08, 0x0000FF00, 0x00000000,
    0x86C, 0xFFFFFF00, 0x00000000,
    0xE10, 0xFFFFFFFF, 0x04040404,
    0xE14, 0xFFFFFFFF, 0x00020404,
    0xE18, 0xFFFFFFFF, 0x00000000,
    0xE1C, 0xFFFFFFFF, 0x00000000,
    0xE00, 0xFFFFFFFF, 0x00000000,
    0xE04, 0xFFFFFFFF, 0x00000000,
    0xE08, 0x0000FF00, 0x00000000,
    0x86C, 0xFFFFFF00, 0x00000000,
    0xE10, 0xFFFFFFFF, 0x00000000,
    0xE14, 0xFFFFFFFF, 0x00000000,
    0xE18, 0xFFFFFFFF, 0x00000000,
    0xE1C, 0xFFFFFFFF, 0x00000000,
    0xE00, 0xFFFFFFFF, 0x00000000,
    0xE04, 0xFFFFFFFF, 0x00000000,
    0xE08, 0x0000FF00, 0x00000000,
    0x86C, 0xFFFFFF00, 0x00000000,
    0xE10, 0xFFFFFFFF, 0x00000000,
    0xE14, 0xFFFFFFFF, 0x00000000,
    0xE18, 0xFFFFFFFF, 0x00000000,
    0xE1C, 0xFFFFFFFF, 0x00000000,
    0xE00, 0xFFFFFFFF, 0x00000000,
    0xE04, 0xFFFFFFFF, 0x00000000,
    0xE08, 0x0000FF00, 0x00000000,
    0x86C, 0xFFFFFF00, 0x00000000,
    0xE10, 0xFFFFFFFF, 0x00000000,
    0xE14, 0xFFFFFFFF, 0x00000000,
    0xE18, 0xFFFFFFFF, 0x00000000,
    0xE1C, 0xFFFFFFFF, 0x00000000,
    0xE00, 0xFFFFFFFF, 0x00000000,
    0xE04, 0xFFFFFFFF, 0x00000000,
    0xE08, 0x0000FF00, 0x00000000,
    0x86C, 0xFFFFFF00, 0x00000000,
    0xE10, 0xFFFFFFFF, 0x00000000,
    0xE14, 0xFFFFFFFF, 0x00000000,
    0xE18, 0xFFFFFFFF, 0x00000000,
    0xE1C, 0xFFFFFFFF, 0x00000000,
    0xE00, 0xFFFFFFFF, 0x00000000,
    0xE04, 0xFFFFFFFF, 0x00000000,
    0xE08, 0x0000FF00, 0x00000000,
    0x86C, 0xFFFFFF00, 0x00000000,
    0xE10, 0xFFFFFFFF, 0x00000000,
    0xE14, 0xFFFFFFFF, 0x00000000,
    0xE18, 0xFFFFFFFF, 0x00000000,
    0xE1C, 0xFFFFFFFF, 0x00000000,

};

u32 RTL8188EE_RADIOA_1TARRAY[] = {
    0x000, 0x00030000,
    0x008, 0x00084000,
    0x018, 0x00000407,
    0x019, 0x00000012,
    0x01E, 0x00080009,
    0x01F, 0x00000880,
    0x02F, 0x0001A060,
    0x03F, 0x00000000,
    0x042, 0x000060C0,
    0x057, 0x000D0000,
    0x058, 0x000BE180,
    0x067, 0x00001552,
    0x083, 0x00000000,
    0x0B0, 0x000FF8FC,
    0x0B1, 0x00054400,
    0x0B2, 0x000CCC19,
    0x0B4, 0x00043003,
    0x0B6, 0x0004953E,
    0x0B7, 0x0001C718,
    0x0B8, 0x000060FF,
    0x0B9, 0x00080001,
    0x0BA, 0x00040000,
    0x0BB, 0x00000400,
    0x0BF, 0x000C0000,
    0x0C2, 0x00002400,
    0x0C3, 0x00000009,
    0x0C4, 0x00040C91,
    0x0C5, 0x00099999,
    0x0C6, 0x000000A3,
    0x0C7, 0x00088820,
    0x0C8, 0x00076C06,
    0x0C9, 0x00000000,
    0x0CA, 0x00080000,
    0x0DF, 0x00000180,
    0x0EF, 0x000001A0,
    0x051, 0x0006B27D,
    0x052, 0x0007E49D,
    0x053, 0x00000073,
    0x056, 0x00051FF3,
    0x035, 0x00000086,
    0x035, 0x00000186,
    0x035, 0x00000286,
    0x036, 0x00001C25,
    0x036, 0x00009C25,
    0x036, 0x00011C25,
    0x036, 0x00019C25,
    0x0B6, 0x00048538,
    0x018, 0x00000C07,
    0x05A, 0x0004BD00,
    0x019, 0x000739D0,
    0x034, 0x0000ADF3,
    0x034, 0x00009DF0,
    0x034, 0x00008DED,
    0x034, 0x00007DEA,
    0x034, 0x00006DE7,
    0x034, 0x000054EE,
    0x034, 0x000044EB,
    0x034, 0x000034E8,
    0x034, 0x0000246B,
    0x034, 0x00001468,
    0x034, 0x0000006D,
    0x000, 0x00030159,
    0x084, 0x00068200,
    0x086, 0x000000CE,
    0x087, 0x00048A00,
    0x08E, 0x00065540,
    0x08F, 0x00088000,
    0x0EF, 0x000020A0,
    0x03B, 0x000F02B0,
    0x03B, 0x000EF7B0,
    0x03B, 0x000D4FB0,
    0x03B, 0x000CF060,
    0x03B, 0x000B0090,
    0x03B, 0x000A0080,
    0x03B, 0x00090080,
    0x03B, 0x0008F780,
    0x03B, 0x000722B0,
    0x03B, 0x0006F7B0,
    0x03B, 0x00054FB0,
    0x03B, 0x0004F060,
    0x03B, 0x00030090,
    0x03B, 0x00020080,
    0x03B, 0x00010080,
    0x03B, 0x0000F780,
    0x0EF, 0x000000A0,
    0x000, 0x00010159,
    0x018, 0x0000F407,
    0xFFE, 0x00000000,
    0xFFE, 0x00000000,
    0x01F, 0x00080003,
    0xFFE, 0x00000000,
    0xFFE, 0x00000000,
    0x01E, 0x00000001,
    0x01F, 0x00080000,
    0x000, 0x00033E60,

};

u32 RTL8188EEMAC_1T_ARRAY[] = {
    0x026, 0x00000041,
    0x027, 0x00000035,
    0x428, 0x0000000A,
    0x429, 0x00000010,
    0x430, 0x00000000,
    0x431, 0x00000001,
    0x432, 0x00000002,
    0x433, 0x00000004,
    0x434, 0x00000005,
    0x435, 0x00000006,
    0x436, 0x00000007,
    0x437, 0x00000008,
    0x438, 0x00000000,
    0x439, 0x00000000,
    0x43A, 0x00000001,
    0x43B, 0x00000002,
    0x43C, 0x00000004,
    0x43D, 0x00000005,
    0x43E, 0x00000006,
    0x43F, 0x00000007,
    0x440, 0x0000005D,
    0x441, 0x00000001,
    0x442, 0x00000000,
    0x444, 0x00000015,
    0x445, 0x000000F0,
    0x446, 0x0000000F,
    0x447, 0x00000000,
    0x458, 0x00000041,
    0x459, 0x000000A8,
    0x45A, 0x00000072,
    0x45B, 0x000000B9,
    0x460, 0x00000066,
    0x461, 0x00000066,
    0x480, 0x00000008,
    0x4C8, 0x000000FF,
    0x4C9, 0x00000008,
    0x4CC, 0x000000FF,
    0x4CD, 0x000000FF,
    0x4CE, 0x00000001,
    0x4D3, 0x00000001,
    0x500, 0x00000026,
    0x501, 0x000000A2,
    0x502, 0x0000002F,
    0x503, 0x00000000,
    0x504, 0x00000028,
    0x505, 0x000000A3,
    0x506, 0x0000005E,
    0x507, 0x00000000,
    0x508, 0x0000002B,
    0x509, 0x000000A4,
    0x50A, 0x0000005E,
    0x50B, 0x00000000,
    0x50C, 0x0000004F,
    0x50D, 0x000000A4,
    0x50E, 0x00000000,
    0x50F, 0x00000000,
    0x512, 0x0000001C,
    0x514, 0x0000000A,
    0x516, 0x0000000A,
    0x525, 0x0000004F,
    0x550, 0x00000010,
    0x551, 0x00000010,
    0x559, 0x00000002,
    0x55D, 0x000000FF,
    0x605, 0x00000030,
    0x608, 0x0000000E,
    0x609, 0x0000002A,
    0x620, 0x000000FF,
    0x621, 0x000000FF,
    0x622, 0x000000FF,
    0x623, 0x000000FF,
    0x624, 0x000000FF,
    0x625, 0x000000FF,
    0x626, 0x000000FF,
    0x627, 0x000000FF,
    0x652, 0x00000020,
    0x63C, 0x0000000A,
    0x63D, 0x0000000A,
    0x63E, 0x0000000E,
    0x63F, 0x0000000E,
    0x640, 0x00000040,
    0x66E, 0x00000005,
    0x700, 0x00000021,
    0x701, 0x00000043,
    0x702, 0x00000065,
    0x703, 0x00000087,
    0x708, 0x00000021,
    0x709, 0x00000043,
    0x70A, 0x00000065,
    0x70B, 0x00000087,

};

u32 RTL8188EEAGCTAB_1TARRAY[] = {
    0xC78, 0xFB000001,
    0xC78, 0xFB010001,
    0xC78, 0xFB020001,
    0xC78, 0xFB030001,
    0xC78, 0xFB040001,
    0xC78, 0xFB050001,
    0xC78, 0xFA060001,
    0xC78, 0xF9070001,
    0xC78, 0xF8080001,
    0xC78, 0xF7090001,
    0xC78, 0xF60A0001,
    0xC78, 0xF50B0001,
    0xC78, 0xF40C0001,
    0xC78, 0xF30D0001,
    0xC78, 0xF20E0001,
    0xC78, 0xF10F0001,
    0xC78, 0xF0100001,
    0xC78, 0xEF110001,
    0xC78, 0xEE120001,
    0xC78, 0xED130001,
    0xC78, 0xEC140001,
    0xC78, 0xEB150001,
    0xC78, 0xEA160001,
    0xC78, 0xE9170001,
    0xC78, 0xE8180001,
    0xC78, 0xE7190001,
    0xC78, 0xE61A0001,
    0xC78, 0xE51B0001,
    0xC78, 0xE41C0001,
    0xC78, 0xE31D0001,
    0xC78, 0xE21E0001,
    0xC78, 0xE11F0001,
    0xC78, 0x8A200001,
    0xC78, 0x89210001,
    0xC78, 0x88220001,
    0xC78, 0x87230001,
    0xC78, 0x86240001,
    0xC78, 0x85250001,
    0xC78, 0x84260001,
    0xC78, 0x83270001,
    0xC78, 0x82280001,
    0xC78, 0x6B290001,
    0xC78, 0x6A2A0001,
    0xC78, 0x692B0001,
    0xC78, 0x682C0001,
    0xC78, 0x672D0001,
    0xC78, 0x662E0001,
    0xC78, 0x652F0001,
    0xC78, 0x64300001,
    0xC78, 0x63310001,
    0xC78, 0x62320001,
    0xC78, 0x61330001,
    0xC78, 0x46340001,
    0xC78, 0x45350001,
    0xC78, 0x44360001,
    0xC78, 0x43370001,
    0xC78, 0x42380001,
    0xC78, 0x41390001,
    0xC78, 0x403A0001,
    0xC78, 0x403B0001,
    0xC78, 0x403C0001,
    0xC78, 0x403D0001,
    0xC78, 0x403E0001,
    0xC78, 0x403F0001,
    0xC78, 0xFB400001,
    0xC78, 0xFB410001,
    0xC78, 0xFB420001,
    0xC78, 0xFB430001,
    0xC78, 0xFB440001,
    0xC78, 0xFB450001,
    0xC78, 0xFB460001,
    0xC78, 0xFB470001,
    0xC78, 0xFB480001,
    0xC78, 0xFA490001,
    0xC78, 0xF94A0001,
    0xC78, 0xF84B0001,
    0xC78, 0xF74C0001,
    0xC78, 0xF64D0001,
    0xC78, 0xF54E0001,
    0xC78, 0xF44F0001,
    0xC78, 0xF3500001,
    0xC78, 0xF2510001,
    0xC78, 0xF1520001,
    0xC78, 0xF0530001,
    0xC78, 0xEF540001,
    0xC78, 0xEE550001,
    0xC78, 0xED560001,
    0xC78, 0xEC570001,
    0xC78, 0xEB580001,
    0xC78, 0xEA590001,
    0xC78, 0xE95A0001,
    0xC78, 0xE85B0001,
    0xC78, 0xE75C0001,
    0xC78, 0xE65D0001,
    0xC78, 0xE55E0001,
    0xC78, 0xE45F0001,
    0xC78, 0xE3600001,
    0xC78, 0xE2610001,
    0xC78, 0xC3620001,
    0xC78, 0xC2630001,
    0xC78, 0xC1640001,
    0xC78, 0x8B650001,
    0xC78, 0x8A660001,
    0xC78, 0x89670001,
    0xC78, 0x88680001,
    0xC78, 0x87690001,
    0xC78, 0x866A0001,
    0xC78, 0x856B0001,
    0xC78, 0x846C0001,
    0xC78, 0x676D0001,
    0xC78, 0x666E0001,
    0xC78, 0x656F0001,
    0xC78, 0x64700001,
    0xC78, 0x63710001,
    0xC78, 0x62720001,
    0xC78, 0x61730001,
    0xC78, 0x60740001,
    0xC78, 0x46750001,
    0xC78, 0x45760001,
    0xC78, 0x44770001,
    0xC78, 0x43780001,
    0xC78, 0x42790001,
    0xC78, 0x417A0001,
    0xC78, 0x407B0001,
    0xC78, 0x407C0001,
    0xC78, 0x407D0001,
    0xC78, 0x407E0001,
    0xC78, 0x407F0001,

};