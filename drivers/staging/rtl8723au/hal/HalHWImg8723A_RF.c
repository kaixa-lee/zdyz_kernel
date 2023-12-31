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
*                           RadioA_1T.TXT
******************************************************************************/

static u32 Array_RadioA_1T_8723A[] = {
    0x000, 0x00030159,
    0x001, 0x00031284,
    0x002, 0x00098000,
    0xFF0F011F, 0xABCD,
    0x003, 0x00018C63,
    0xCDCDCDCD, 0xCDCD,
    0x003, 0x00039C63,
    0xFF0F011F, 0xDEAD,
    0x004, 0x000210E7,
    0x009, 0x0002044F,
    0x00A, 0x0001A3F1,
    0x00B, 0x00014787,
    0x00C, 0x000896FE,
    0x00D, 0x0000E02C,
    0x00E, 0x00039CE7,
    0x00F, 0x00000451,
    0x019, 0x00000000,
    0x01A, 0x00030355,
    0x01B, 0x00060A00,
    0x01C, 0x000FC378,
    0x01D, 0x000A1250,
    0x01E, 0x0000024F,
    0x01F, 0x00000000,
    0x020, 0x0000B614,
    0x021, 0x0006C000,
    0x022, 0x00000000,
    0x023, 0x00001558,
    0x024, 0x00000060,
    0x025, 0x00000483,
    0x026, 0x0004F000,
    0x027, 0x000EC7D9,
    0x028, 0x00057730,
    0x029, 0x00004783,
    0x02A, 0x00000001,
    0x02B, 0x00021334,
    0x02A, 0x00000000,
    0x02B, 0x00000054,
    0x02A, 0x00000001,
    0x02B, 0x00000808,
    0x02B, 0x00053333,
    0x02C, 0x0000000C,
    0x02A, 0x00000002,
    0x02B, 0x00000808,
    0x02B, 0x0005B333,
    0x02C, 0x0000000D,
    0x02A, 0x00000003,
    0x02B, 0x00000808,
    0x02B, 0x00063333,
    0x02C, 0x0000000D,
    0x02A, 0x00000004,
    0x02B, 0x00000808,
    0x02B, 0x0006B333,
    0x02C, 0x0000000D,
    0x02A, 0x00000005,
    0x02B, 0x00000808,
    0x02B, 0x00073333,
    0x02C, 0x0000000D,
    0x02A, 0x00000006,
    0x02B, 0x00000709,
    0x02B, 0x0005B333,
    0x02C, 0x0000000D,
    0x02A, 0x00000007,
    0x02B, 0x00000709,
    0x02B, 0x00063333,
    0x02C, 0x0000000D,
    0x02A, 0x00000008,
    0x02B, 0x0000060A,
    0x02B, 0x0004B333,
    0x02C, 0x0000000D,
    0x02A, 0x00000009,
    0x02B, 0x0000060A,
    0x02B, 0x00053333,
    0x02C, 0x0000000D,
    0x02A, 0x0000000A,
    0x02B, 0x0000060A,
    0x02B, 0x0005B333,
    0x02C, 0x0000000D,
    0x02A, 0x0000000B,
    0x02B, 0x0000060A,
    0x02B, 0x00063333,
    0x02C, 0x0000000D,
    0x02A, 0x0000000C,
    0x02B, 0x0000060A,
    0x02B, 0x0006B333,
    0x02C, 0x0000000D,
    0x02A, 0x0000000D,
    0x02B, 0x0000060A,
    0x02B, 0x00073333,
    0x02C, 0x0000000D,
    0x02A, 0x0000000E,
    0x02B, 0x0000050B,
    0x02B, 0x00066666,
    0x02C, 0x0000001A,
    0x02A, 0x000E0000,
    0x010, 0x0004000F,
    0x011, 0x000E31FC,
    0x010, 0x0006000F,
    0x011, 0x000FF9F8,
    0x010, 0x0002000F,
    0x011, 0x000203F9,
    0x010, 0x0003000F,
    0x011, 0x000FF500,
    0x010, 0x00000000,
    0x011, 0x00000000,
    0x010, 0x0008000F,
    0x011, 0x0003F100,
    0x010, 0x0009000F,
    0x011, 0x00023100,
    0x012, 0x00032000,
    0x012, 0x00071000,
    0x012, 0x000B0000,
    0x012, 0x000FC000,
    0x013, 0x000287B3,
    0x013, 0x000244B7,
    0x013, 0x000204AB,
    0x013, 0x0001C49F,
    0x013, 0x00018493,
    0x013, 0x0001429B,
    0x013, 0x00010299,
    0x013, 0x0000C29C,
    0x013, 0x000081A0,
    0x013, 0x000040AC,
    0x013, 0x00000020,
    0x014, 0x0001944C,
    0x014, 0x00059444,
    0x014, 0x0009944C,
    0x014, 0x000D9444,
    0xFF0F011F, 0xABCD,
    0x015, 0x0000F424,
    0x015, 0x0004F424,
    0x015, 0x0008F424,
    0x015, 0x000CF424,
    0xCDCDCDCD, 0xCDCD,
    0x015, 0x0000F474,
    0x015, 0x0004F477,
    0x015, 0x0008F455,
    0x015, 0x000CF455,
    0xFF0F011F, 0xDEAD,
    0x016, 0x00000339,
    0x016, 0x00040339,
    0x016, 0x00080339,
    0xFF0F011F, 0xABCD,
    0x016, 0x000C0356,
    0xCDCDCDCD, 0xCDCD,
    0x016, 0x000C0366,
    0xFF0F011F, 0xDEAD,
    0x000, 0x00010159,
    0x018, 0x0000F401,
    0x0FE, 0x00000000,
    0x0FE, 0x00000000,
    0x01F, 0x00000003,
    0x0FE, 0x00000000,
    0x0FE, 0x00000000,
    0x01E, 0x00000247,
    0x01F, 0x00000000,
    0x000, 0x00030159,
};

void ODM_ReadAndConfig_RadioA_1T_8723A(struct dm_odm_t *pDM_Odm)
{
#define READ_NEXT_PAIR(v1, v2, i)			\
		 do {						\
			 i += 2; v1 = Array[i]; v2 = Array[i+1];\
		 } while (0)

    u32     hex         = 0;
    u32     i           = 0;
    u8     platform    = 0x04;
    u8     board       = pDM_Odm->BoardType;
    u32     ArrayLen    = sizeof(Array_RadioA_1T_8723A)/sizeof(u32);
    u32 *Array = Array_RadioA_1T_8723A;

    hex += board;
    hex += ODM_ITRF_USB << 8;
    hex += platform << 16;
    hex += 0xFF000000;

    for (i = 0; i < ArrayLen; i += 2) {
        u32 v1 = Array[i];
        u32 v2 = Array[i+1];

        /*  This (offset, data) pair meets the condition. */
        if (v1 < 0xCDCDCDCD) {
            odm_ConfigRFReg_8723A(pDM_Odm, v1, v2, RF_PATH_A, v1);
            continue;
        } else {
            if (!CheckCondition(Array[i], hex)) {
                /*  Discard the following (offset, data) pairs. */
                READ_NEXT_PAIR(v1, v2, i);
                while (v2 != 0xDEAD &&
                       v2 != 0xCDEF &&
                       v2 != 0xCDCD && i < ArrayLen - 2) {
                    READ_NEXT_PAIR(v1, v2, i);
                }
                i -= 2; /*  prevent from for-loop += 2 */
            } else {
                /*  Configure matched pairs and skip to end of if-else. */
                READ_NEXT_PAIR(v1, v2, i);
                while (v2 != 0xDEAD &&
                       v2 != 0xCDEF &&
                       v2 != 0xCDCD && i < ArrayLen - 2) {
                    odm_ConfigRFReg_8723A(pDM_Odm, v1, v2,
                                          RF_PATH_A, v1);
                    READ_NEXT_PAIR(v1, v2, i);
                }

                while (v2 != 0xDEAD && i < ArrayLen - 2) {
                    READ_NEXT_PAIR(v1, v2, i);
                }
            }
        }
    }
}
