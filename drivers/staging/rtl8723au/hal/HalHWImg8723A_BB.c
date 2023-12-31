/******************************************************************************
*
* Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of version 2 of the GNU General Public License as
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
******************************************************************************/

#include "odm_precomp.h"

static bool CheckCondition(const u32  Condition, const u32  Hex)
{
    u32 _board     = (Hex & 0x000000FF);
    u32 _interface = (Hex & 0x0000FF00) >> 8;
    u32 _platform  = (Hex & 0x00FF0000) >> 16;
    u32 cond = Condition;

    if (Condition == 0xCDCDCDCD) {
        return true;
    }

    cond = Condition & 0x000000FF;
    if ((_board == cond) && cond != 0x00) {
        return false;
    }

    cond = Condition & 0x0000FF00;
    cond >>= 8;
    if ((_interface & cond) == 0 && cond != 0x07) {
        return false;
    }

    cond = Condition & 0x00FF0000;
    cond >>= 16;
    if ((_platform & cond) == 0 && cond != 0x0F) {
        return false;
    }
    return true;
}

/******************************************************************************
*                           AGC_TAB_1T.TXT
******************************************************************************/

static u32 Array_AGC_TAB_1T_8723A[] = {
    0xC78, 0x7B000001,
    0xC78, 0x7B010001,
    0xC78, 0x7B020001,
    0xC78, 0x7B030001,
    0xC78, 0x7B040001,
    0xC78, 0x7B050001,
    0xC78, 0x7A060001,
    0xC78, 0x79070001,
    0xC78, 0x78080001,
    0xC78, 0x77090001,
    0xC78, 0x760A0001,
    0xC78, 0x750B0001,
    0xC78, 0x740C0001,
    0xC78, 0x730D0001,
    0xC78, 0x720E0001,
    0xC78, 0x710F0001,
    0xC78, 0x70100001,
    0xC78, 0x6F110001,
    0xC78, 0x6E120001,
    0xC78, 0x6D130001,
    0xC78, 0x6C140001,
    0xC78, 0x6B150001,
    0xC78, 0x6A160001,
    0xC78, 0x69170001,
    0xC78, 0x68180001,
    0xC78, 0x67190001,
    0xC78, 0x661A0001,
    0xC78, 0x651B0001,
    0xC78, 0x641C0001,
    0xC78, 0x631D0001,
    0xC78, 0x621E0001,
    0xC78, 0x611F0001,
    0xC78, 0x60200001,
    0xC78, 0x49210001,
    0xC78, 0x48220001,
    0xC78, 0x47230001,
    0xC78, 0x46240001,
    0xC78, 0x45250001,
    0xC78, 0x44260001,
    0xC78, 0x43270001,
    0xC78, 0x42280001,
    0xC78, 0x41290001,
    0xC78, 0x402A0001,
    0xC78, 0x262B0001,
    0xC78, 0x252C0001,
    0xC78, 0x242D0001,
    0xC78, 0x232E0001,
    0xC78, 0x222F0001,
    0xC78, 0x21300001,
    0xC78, 0x20310001,
    0xC78, 0x06320001,
    0xC78, 0x05330001,
    0xC78, 0x04340001,
    0xC78, 0x03350001,
    0xC78, 0x02360001,
    0xC78, 0x01370001,
    0xC78, 0x00380001,
    0xC78, 0x00390001,
    0xC78, 0x003A0001,
    0xC78, 0x003B0001,
    0xC78, 0x003C0001,
    0xC78, 0x003D0001,
    0xC78, 0x003E0001,
    0xC78, 0x003F0001,
    0xC78, 0x7B400001,
    0xC78, 0x7B410001,
    0xC78, 0x7B420001,
    0xC78, 0x7B430001,
    0xC78, 0x7B440001,
    0xC78, 0x7B450001,
    0xC78, 0x7A460001,
    0xC78, 0x79470001,
    0xC78, 0x78480001,
    0xC78, 0x77490001,
    0xC78, 0x764A0001,
    0xC78, 0x754B0001,
    0xC78, 0x744C0001,
    0xC78, 0x734D0001,
    0xC78, 0x724E0001,
    0xC78, 0x714F0001,
    0xC78, 0x70500001,
    0xC78, 0x6F510001,
    0xC78, 0x6E520001,
    0xC78, 0x6D530001,
    0xC78, 0x6C540001,
    0xC78, 0x6B550001,
    0xC78, 0x6A560001,
    0xC78, 0x69570001,
    0xC78, 0x68580001,
    0xC78, 0x67590001,
    0xC78, 0x665A0001,
    0xC78, 0x655B0001,
    0xC78, 0x645C0001,
    0xC78, 0x635D0001,
    0xC78, 0x625E0001,
    0xC78, 0x615F0001,
    0xC78, 0x60600001,
    0xC78, 0x49610001,
    0xC78, 0x48620001,
    0xC78, 0x47630001,
    0xC78, 0x46640001,
    0xC78, 0x45650001,
    0xC78, 0x44660001,
    0xC78, 0x43670001,
    0xC78, 0x42680001,
    0xC78, 0x41690001,
    0xC78, 0x406A0001,
    0xC78, 0x266B0001,
    0xC78, 0x256C0001,
    0xC78, 0x246D0001,
    0xC78, 0x236E0001,
    0xC78, 0x226F0001,
    0xC78, 0x21700001,
    0xC78, 0x20710001,
    0xC78, 0x06720001,
    0xC78, 0x05730001,
    0xC78, 0x04740001,
    0xC78, 0x03750001,
    0xC78, 0x02760001,
    0xC78, 0x01770001,
    0xC78, 0x00780001,
    0xC78, 0x00790001,
    0xC78, 0x007A0001,
    0xC78, 0x007B0001,
    0xC78, 0x007C0001,
    0xC78, 0x007D0001,
    0xC78, 0x007E0001,
    0xC78, 0x007F0001,
    0xC78, 0x3800001E,
    0xC78, 0x3801001E,
    0xC78, 0x3802001E,
    0xC78, 0x3803001E,
    0xC78, 0x3804001E,
    0xC78, 0x3805001E,
    0xC78, 0x3806001E,
    0xC78, 0x3807001E,
    0xC78, 0x3808001E,
    0xC78, 0x3C09001E,
    0xC78, 0x3E0A001E,
    0xC78, 0x400B001E,
    0xC78, 0x440C001E,
    0xC78, 0x480D001E,
    0xC78, 0x4C0E001E,
    0xC78, 0x500F001E,
    0xC78, 0x5210001E,
    0xC78, 0x5611001E,
    0xC78, 0x5A12001E,
    0xC78, 0x5E13001E,
    0xC78, 0x6014001E,
    0xC78, 0x6015001E,
    0xC78, 0x6016001E,
    0xC78, 0x6217001E,
    0xC78, 0x6218001E,
    0xC78, 0x6219001E,
    0xC78, 0x621A001E,
    0xC78, 0x621B001E,
    0xC78, 0x621C001E,
    0xC78, 0x621D001E,
    0xC78, 0x621E001E,
    0xC78, 0x621F001E,
};

#define READ_NEXT_PAIR(v1, v2, i)			\
	do {						\
		i += 2; v1 = Array[i]; v2 = Array[i+1];	\
	} while (0)

void ODM_ReadAndConfig_AGC_TAB_1T_8723A(struct dm_odm_t *pDM_Odm)
{
    u32 hex;
    u32 i;
    u8 platform = 0x04;
    u8 board = pDM_Odm->BoardType;
    u32 ArrayLen = sizeof(Array_AGC_TAB_1T_8723A)/sizeof(u32);
    u32 *Array = Array_AGC_TAB_1T_8723A;

    hex = board;
    hex += ODM_ITRF_USB << 8;
    hex += platform << 16;
    hex += 0xFF000000;
    for (i = 0; i < ArrayLen; i += 2) {
        u32 v1 = Array[i];
        u32 v2 = Array[i+1];

        /*  This (offset, data) pair meets the condition. */
        if (v1 < 0xCDCDCDCD) {
            odm_ConfigBB_AGC_8723A(pDM_Odm, v1, v2);
            continue;
        } else {
            if (!CheckCondition(Array[i], hex)) {
                /* Discard the following (offset, data) pairs */
                READ_NEXT_PAIR(v1, v2, i);
                while (v2 != 0xDEAD &&
                       v2 != 0xCDEF &&
                       v2 != 0xCDCD && i < ArrayLen - 2) {
                    READ_NEXT_PAIR(v1, v2, i);
                }
                i -= 2; /*  prevent from for-loop += 2 */
            } else {
                /*  Configure matched pairs and skip to
                    end of if-else. */
                READ_NEXT_PAIR(v1, v2, i);
                while (v2 != 0xDEAD &&
                       v2 != 0xCDEF &&
                       v2 != 0xCDCD && i < ArrayLen - 2) {
                    odm_ConfigBB_AGC_8723A(pDM_Odm, v1, v2);
                    READ_NEXT_PAIR(v1, v2, i);
                }
                while (v2 != 0xDEAD && i < ArrayLen - 2) {
                    READ_NEXT_PAIR(v1, v2, i);
                }
            }
        }
    }
}

/******************************************************************************
*                           PHY_REG_1T.TXT
******************************************************************************/

static u32 Array_PHY_REG_1T_8723A[] = {
    0x800, 0x80040000,
    0x804, 0x00000003,
    0x808, 0x0000FC00,
    0x80C, 0x0000000A,
    0x810, 0x10001331,
    0x814, 0x020C3D10,
    0x818, 0x02200385,
    0x81C, 0x00000000,
    0x820, 0x01000100,
    0x824, 0x00390004,
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
    0x858, 0x569A569A,
    0x85C, 0x001B25A4,
    0x860, 0x66F60110,
    0x864, 0x061F0130,
    0x868, 0x00000000,
    0x86C, 0x32323200,
    0x870, 0x07000760,
    0x874, 0x22004000,
    0x878, 0x00000808,
    0x87C, 0x00000000,
    0x880, 0xC0083070,
    0x884, 0x000004D5,
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
    0xA00, 0x00D047C8,
    0xA04, 0x80FF000C,
    0xA08, 0x8C838300,
    0xA0C, 0x2E68120F,
    0xA10, 0x9500BB78,
    0xA14, 0x11144028,
    0xA18, 0x00881117,
    0xA1C, 0x89140F00,
    0xA20, 0x1A1B0000,
    0xA24, 0x090E1317,
    0xA28, 0x00000204,
    0xA2C, 0x00D30000,
    0xA70, 0x101FBF00,
    0xA74, 0x00000007,
    0xA78, 0x00000900,
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
    0xC30, 0x69E9AC44,
    0xFF0F011F, 0xABCD,
    0xC34, 0x469652CF,
    0xCDCDCDCD, 0xCDCD,
    0xC34, 0x469652AF,
    0xFF0F011F, 0xDEAD,
    0xC38, 0x49795994,
    0xC3C, 0x0A97971C,
    0xC40, 0x1F7C403F,
    0xC44, 0x000100B7,
    0xC48, 0xEC020107,
    0xC4C, 0x007F037F,
    0xC50, 0x69543420,
    0xC54, 0x43BC0094,
    0xC58, 0x69543420,
    0xC5C, 0x433C0094,
    0xC60, 0x00000000,
    0xFF0F011F, 0xABCD,
    0xC64, 0x7116848B,
    0xCDCDCDCD, 0xCDCD,
    0xC64, 0x7112848B,
    0xFF0F011F, 0xDEAD,
    0xC68, 0x47C00BFF,
    0xC6C, 0x00000036,
    0xC70, 0x2C7F000D,
    0xC74, 0x018610DB,
    0xC78, 0x0000001F,
    0xC7C, 0x00B91612,
    0xC80, 0x40000100,
    0xC84, 0x20F60000,
    0xC88, 0x40000100,
    0xC8C, 0x20200000,
    0xC90, 0x00121820,
    0xC94, 0x00000000,
    0xC98, 0x00121820,
    0xC9C, 0x00007F7F,
    0xCA0, 0x00000000,
    0xCA4, 0x00000080,
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
    0xD00, 0x00080740,
    0xD04, 0x00020401,
    0xD08, 0x0000907F,
    0xD0C, 0x20010201,
    0xD10, 0xA0633333,
    0xD14, 0x3333BC43,
    0xD18, 0x7A8F5B6B,
    0xD2C, 0xCC979975,
    0xD30, 0x00000000,
    0xD34, 0x80608000,
    0xD38, 0x00000000,
    0xD3C, 0x00027293,
    0xD40, 0x00000000,
    0xD44, 0x00000000,
    0xD48, 0x00000000,
    0xD4C, 0x00000000,
    0xD50, 0x6437140A,
    0xD54, 0x00000000,
    0xD58, 0x00000000,
    0xD5C, 0x30032064,
    0xD60, 0x4653DE68,
    0xD64, 0x04518A3C,
    0xD68, 0x00002101,
    0xD6C, 0x2A201C16,
    0xD70, 0x1812362E,
    0xD74, 0x322C2220,
    0xD78, 0x000E3C24,
    0xE00, 0x2A2A2A2A,
    0xE04, 0x2A2A2A2A,
    0xE08, 0x03902A2A,
    0xE10, 0x2A2A2A2A,
    0xE14, 0x2A2A2A2A,
    0xE18, 0x2A2A2A2A,
    0xE1C, 0x2A2A2A2A,
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
    0xE6C, 0x631B25A0,
    0xE70, 0x631B25A0,
    0xE74, 0x081B25A0,
    0xE78, 0x081B25A0,
    0xE7C, 0x081B25A0,
    0xE80, 0x081B25A0,
    0xE84, 0x631B25A0,
    0xE88, 0x081B25A0,
    0xE8C, 0x631B25A0,
    0xED0, 0x631B25A0,
    0xED4, 0x631B25A0,
    0xED8, 0x631B25A0,
    0xEDC, 0x001B25A0,
    0xEE0, 0x001B25A0,
    0xEEC, 0x6B1B25A0,
    0xF14, 0x00000003,
    0xF4C, 0x00000000,
    0xF00, 0x00000300,
};

void ODM_ReadAndConfig_PHY_REG_1T_8723A(struct dm_odm_t *pDM_Odm)
{
    u32 hex = 0;
    u32 i = 0;
    u8  platform = 0x04;
    u8  board = pDM_Odm->BoardType;
    u32 ArrayLen = sizeof(Array_PHY_REG_1T_8723A)/sizeof(u32);
    u32 *Array = Array_PHY_REG_1T_8723A;

    hex += board;
    hex += ODM_ITRF_USB << 8;
    hex += platform << 16;
    hex += 0xFF000000;
    for (i = 0; i < ArrayLen; i += 2) {
        u32 v1 = Array[i];
        u32 v2 = Array[i+1];

        /*  This (offset, data) pair meets the condition. */
        if (v1 < 0xCDCDCDCD) {
            odm_ConfigBB_PHY_8723A(pDM_Odm, v1, v2);
            continue;
        } else {
            if (!CheckCondition(Array[i], hex)) {
                /* Discard the following (offset, data) pairs */
                READ_NEXT_PAIR(v1, v2, i);
                while (v2 != 0xDEAD &&
                       v2 != 0xCDEF &&
                       v2 != 0xCDCD && i < ArrayLen - 2) {
                    READ_NEXT_PAIR(v1, v2, i);
                }
                i -= 2; /*  prevent from for-loop += 2 */
            } else {
                /*  Configure matched pairs and skip to
                    end of if-else. */
                READ_NEXT_PAIR(v1, v2, i);
                while (v2 != 0xDEAD &&
                       v2 != 0xCDEF &&
                       v2 != 0xCDCD && i < ArrayLen - 2) {
                    odm_ConfigBB_PHY_8723A(pDM_Odm, v1, v2);
                    READ_NEXT_PAIR(v1, v2, i);
                }
                while (v2 != 0xDEAD && i < ArrayLen - 2) {
                    READ_NEXT_PAIR(v1, v2, i);
                }
            }
        }
    }
}

/******************************************************************************
*                           PHY_REG_MP.TXT
******************************************************************************/

static u32 Array_PHY_REG_MP_8723A[] = {
    0xC30, 0x69E9AC4A,
    0xC3C, 0x0A979718,
};

void ODM_ReadAndConfig_PHY_REG_MP_8723A(struct dm_odm_t *pDM_Odm)
{
    u32 hex = 0;
    u32 i;
    u8 platform = 0x04;
    u8 board = pDM_Odm->BoardType;
    u32 ArrayLen = sizeof(Array_PHY_REG_MP_8723A)/sizeof(u32);
    u32 *Array = Array_PHY_REG_MP_8723A;

    hex += board;
    hex += ODM_ITRF_USB << 8;
    hex += platform << 16;
    hex += 0xFF000000;
    for (i = 0; i < ArrayLen; i += 2) {
        u32 v1 = Array[i];
        u32 v2 = Array[i+1];

        /*  This (offset, data) pair meets the condition. */
        if (v1 < 0xCDCDCDCD) {
            odm_ConfigBB_PHY_8723A(pDM_Odm, v1, v2);
            continue;
        } else {
            if (!CheckCondition(Array[i], hex)) {
                /* Discard the following (offset, data) pairs */
                READ_NEXT_PAIR(v1, v2, i);
                while (v2 != 0xDEAD &&
                       v2 != 0xCDEF &&
                       v2 != 0xCDCD && i < ArrayLen - 2) {
                    READ_NEXT_PAIR(v1, v2, i);
                }
                i -= 2; /*  prevent from for-loop += 2 */
            } else {
                /* Configure matched pairs and skip to
                   end of if-else. */
                READ_NEXT_PAIR(v1, v2, i);
                while (v2 != 0xDEAD &&
                       v2 != 0xCDEF &&
                       v2 != 0xCDCD && i < ArrayLen - 2) {
                    odm_ConfigBB_PHY_8723A(pDM_Odm, v1, v2);
                    READ_NEXT_PAIR(v1, v2, i);
                }
                while (v2 != 0xDEAD && i < ArrayLen - 2) {
                    READ_NEXT_PAIR(v1, v2, i);
                }
            }
        }
    }
}
