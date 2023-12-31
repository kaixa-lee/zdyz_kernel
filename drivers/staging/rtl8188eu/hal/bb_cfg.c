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
* You should have received a copy of the GNU General Public License along with
* this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
*
*
******************************************************************************/

#include "odm_precomp.h"

#include <phy.h>

#define read_next_pair(array, v1, v2, i)		\
	 do {						\
		 i += 2;				\
		 v1 = array[i];				\
		 v2 = array[i+1];			\
	 } while (0)


/* AGC_TAB_1T.TXT */

static u32 array_agc_tab_1t_8188e[] = {
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

static bool set_baseband_agc_config(struct adapter *adapt)
{
    u32 i;
    u32 arraylen = sizeof(array_agc_tab_1t_8188e)/sizeof(u32);
    u32 *array = array_agc_tab_1t_8188e;

    for (i = 0; i < arraylen; i += 2) {
        u32 v1 = array[i];
        u32 v2 = array[i+1];

        if (v1 < 0xCDCDCDCD) {
            phy_set_bb_reg(adapt, v1, bMaskDWord, v2);
            udelay(1);
        }
    }
    return true;
}

/*  PHY_REG_1T.TXT  */

static u32 array_phy_reg_1t_8188e[] = {
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

static void rtl_bb_delay(struct adapter *adapt, u32 addr, u32 data)
{
    if (addr == 0xfe) {
        msleep(50);
    } else if (addr == 0xfd) {
        mdelay(5);
    } else if (addr == 0xfc) {
        mdelay(1);
    } else if (addr == 0xfb) {
        udelay(50);
    } else if (addr == 0xfa) {
        udelay(5);
    } else if (addr == 0xf9) {
        udelay(1);
    } else {
        phy_set_bb_reg(adapt, addr, bMaskDWord, data);
        /*  Add 1us delay between BB/RF register setting. */
        udelay(1);
    }
}

static bool set_baseband_phy_config(struct adapter *adapt)
{
    u32 i;
    u32 arraylen = sizeof(array_phy_reg_1t_8188e)/sizeof(u32);
    u32 *array = array_phy_reg_1t_8188e;

    for (i = 0; i < arraylen; i += 2) {
        u32 v1 = array[i];
        u32 v2 = array[i+1];

        if (v1 < 0xCDCDCDCD) {
            rtl_bb_delay(adapt, v1, v2);
        }
    }
    return true;
}

/*  PHY_REG_PG.TXT  */

static u32 array_phy_reg_pg_8188e[] = {
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

static void store_pwrindex_offset(struct adapter *Adapter, u32 regaddr, u32 bitmask, u32 data)
{
    struct hal_data_8188e *hal_data = GET_HAL_DATA(Adapter);
    u8 pwrGrpCnt = hal_data->pwrGroupCnt;

    if (regaddr == rTxAGC_A_Rate18_06) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][0] = data;
    }
    if (regaddr == rTxAGC_A_Rate54_24) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][1] = data;
    }
    if (regaddr == rTxAGC_A_CCK1_Mcs32) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][6] = data;
    }
    if (regaddr == rTxAGC_B_CCK11_A_CCK2_11 && bitmask == 0xffffff00) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][7] = data;
    }
    if (regaddr == rTxAGC_A_Mcs03_Mcs00) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][2] = data;
    }
    if (regaddr == rTxAGC_A_Mcs07_Mcs04) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][3] = data;
    }
    if (regaddr == rTxAGC_A_Mcs11_Mcs08) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][4] = data;
    }
    if (regaddr == rTxAGC_A_Mcs15_Mcs12) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][5] = data;
        if (hal_data->rf_type == RF_1T1R) {
            hal_data->pwrGroupCnt++;
        }
    }
    if (regaddr == rTxAGC_B_Rate18_06) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][8] = data;
    }
    if (regaddr == rTxAGC_B_Rate54_24) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][9] = data;
    }
    if (regaddr == rTxAGC_B_CCK1_55_Mcs32) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][14] = data;
    }
    if (regaddr == rTxAGC_B_CCK11_A_CCK2_11 && bitmask == 0x000000ff) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][15] = data;
    }
    if (regaddr == rTxAGC_B_Mcs03_Mcs00) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][10] = data;
    }
    if (regaddr == rTxAGC_B_Mcs07_Mcs04) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][11] = data;
    }
    if (regaddr == rTxAGC_B_Mcs11_Mcs08) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][12] = data;
    }
    if (regaddr == rTxAGC_B_Mcs15_Mcs12) {
        hal_data->MCSTxPowerLevelOriginalOffset[pwrGrpCnt][13] = data;
        if (hal_data->rf_type != RF_1T1R) {
            hal_data->pwrGroupCnt++;
        }
    }
}

static void rtl_addr_delay(struct adapter *adapt,
                           u32 addr, u32 bit_mask, u32 data)
{
    switch (addr) {
    case 0xfe:
        msleep(50);
        break;
    case 0xfd:
        mdelay(5);
        break;
    case 0xfc:
        mdelay(1);
        break;
    case 0xfb:
        udelay(50);
        break;
    case 0xfa:
        udelay(5);
        break;
    case 0xf9:
        udelay(1);
        break;
    default:
        store_pwrindex_offset(adapt, addr, bit_mask, data);
    }
}

static bool config_bb_with_pgheader(struct adapter *adapt)
{
    u32 i = 0;
    u32 arraylen = sizeof(array_phy_reg_pg_8188e) / sizeof(u32);
    u32 *array = array_phy_reg_pg_8188e;

    for (i = 0; i < arraylen; i += 3) {
        u32 v1 = array[i];
        u32 v2 = array[i+1];
        u32 v3 = array[i+2];

        if (v1 < 0xCDCDCDCD) {
            rtl_addr_delay(adapt, v1, v2, v3);
        }
    }
    return true;
}

static void rtl88e_phy_init_bb_rf_register_definition(struct adapter *Adapter)
{
    struct hal_data_8188e		*hal_data = GET_HAL_DATA(Adapter);
    struct bb_reg_def               *reg[4];

    reg[RF_PATH_A] = &(hal_data->PHYRegDef[RF_PATH_A]);
    reg[RF_PATH_B] = &(hal_data->PHYRegDef[RF_PATH_B]);
    reg[RF_PATH_C] = &(hal_data->PHYRegDef[RF_PATH_C]);
    reg[RF_PATH_D] = &(hal_data->PHYRegDef[RF_PATH_D]);

    reg[RF_PATH_A]->rfintfs = rFPGA0_XAB_RFInterfaceSW;
    reg[RF_PATH_B]->rfintfs = rFPGA0_XAB_RFInterfaceSW;
    reg[RF_PATH_C]->rfintfs = rFPGA0_XCD_RFInterfaceSW;
    reg[RF_PATH_D]->rfintfs = rFPGA0_XCD_RFInterfaceSW;

    reg[RF_PATH_A]->rfintfi = rFPGA0_XAB_RFInterfaceRB;
    reg[RF_PATH_B]->rfintfi = rFPGA0_XAB_RFInterfaceRB;
    reg[RF_PATH_C]->rfintfi = rFPGA0_XCD_RFInterfaceRB;
    reg[RF_PATH_D]->rfintfi = rFPGA0_XCD_RFInterfaceRB;

    reg[RF_PATH_A]->rfintfo = rFPGA0_XA_RFInterfaceOE;
    reg[RF_PATH_B]->rfintfo = rFPGA0_XB_RFInterfaceOE;

    reg[RF_PATH_A]->rfintfe = rFPGA0_XA_RFInterfaceOE;
    reg[RF_PATH_B]->rfintfe = rFPGA0_XB_RFInterfaceOE;

    reg[RF_PATH_A]->rf3wireOffset = rFPGA0_XA_LSSIParameter;
    reg[RF_PATH_B]->rf3wireOffset = rFPGA0_XB_LSSIParameter;

    reg[RF_PATH_A]->rfLSSI_Select = rFPGA0_XAB_RFParameter;
    reg[RF_PATH_B]->rfLSSI_Select = rFPGA0_XAB_RFParameter;
    reg[RF_PATH_C]->rfLSSI_Select = rFPGA0_XCD_RFParameter;
    reg[RF_PATH_D]->rfLSSI_Select = rFPGA0_XCD_RFParameter;

    reg[RF_PATH_A]->rfTxGainStage = rFPGA0_TxGainStage;
    reg[RF_PATH_B]->rfTxGainStage = rFPGA0_TxGainStage;
    reg[RF_PATH_C]->rfTxGainStage = rFPGA0_TxGainStage;
    reg[RF_PATH_D]->rfTxGainStage = rFPGA0_TxGainStage;

    reg[RF_PATH_A]->rfHSSIPara1 = rFPGA0_XA_HSSIParameter1;
    reg[RF_PATH_B]->rfHSSIPara1 = rFPGA0_XB_HSSIParameter1;

    reg[RF_PATH_A]->rfHSSIPara2 = rFPGA0_XA_HSSIParameter2;
    reg[RF_PATH_B]->rfHSSIPara2 = rFPGA0_XB_HSSIParameter2;

    reg[RF_PATH_A]->rfSwitchControl = rFPGA0_XAB_SwitchControl;
    reg[RF_PATH_B]->rfSwitchControl = rFPGA0_XAB_SwitchControl;
    reg[RF_PATH_C]->rfSwitchControl = rFPGA0_XCD_SwitchControl;
    reg[RF_PATH_D]->rfSwitchControl = rFPGA0_XCD_SwitchControl;

    reg[RF_PATH_A]->rfAGCControl1 = rOFDM0_XAAGCCore1;
    reg[RF_PATH_B]->rfAGCControl1 = rOFDM0_XBAGCCore1;
    reg[RF_PATH_C]->rfAGCControl1 = rOFDM0_XCAGCCore1;
    reg[RF_PATH_D]->rfAGCControl1 = rOFDM0_XDAGCCore1;

    reg[RF_PATH_A]->rfAGCControl2 = rOFDM0_XAAGCCore2;
    reg[RF_PATH_B]->rfAGCControl2 = rOFDM0_XBAGCCore2;
    reg[RF_PATH_C]->rfAGCControl2 = rOFDM0_XCAGCCore2;
    reg[RF_PATH_D]->rfAGCControl2 = rOFDM0_XDAGCCore2;

    reg[RF_PATH_A]->rfRxIQImbalance = rOFDM0_XARxIQImbalance;
    reg[RF_PATH_B]->rfRxIQImbalance = rOFDM0_XBRxIQImbalance;
    reg[RF_PATH_C]->rfRxIQImbalance = rOFDM0_XCRxIQImbalance;
    reg[RF_PATH_D]->rfRxIQImbalance = rOFDM0_XDRxIQImbalance;

    reg[RF_PATH_A]->rfRxAFE = rOFDM0_XARxAFE;
    reg[RF_PATH_B]->rfRxAFE = rOFDM0_XBRxAFE;
    reg[RF_PATH_C]->rfRxAFE = rOFDM0_XCRxAFE;
    reg[RF_PATH_D]->rfRxAFE = rOFDM0_XDRxAFE;

    reg[RF_PATH_A]->rfTxIQImbalance = rOFDM0_XATxIQImbalance;
    reg[RF_PATH_B]->rfTxIQImbalance = rOFDM0_XBTxIQImbalance;
    reg[RF_PATH_C]->rfTxIQImbalance = rOFDM0_XCTxIQImbalance;
    reg[RF_PATH_D]->rfTxIQImbalance = rOFDM0_XDTxIQImbalance;

    reg[RF_PATH_A]->rfTxAFE = rOFDM0_XATxAFE;
    reg[RF_PATH_B]->rfTxAFE = rOFDM0_XBTxAFE;
    reg[RF_PATH_C]->rfTxAFE = rOFDM0_XCTxAFE;
    reg[RF_PATH_D]->rfTxAFE = rOFDM0_XDTxAFE;

    reg[RF_PATH_A]->rfLSSIReadBack = rFPGA0_XA_LSSIReadBack;
    reg[RF_PATH_B]->rfLSSIReadBack = rFPGA0_XB_LSSIReadBack;
    reg[RF_PATH_C]->rfLSSIReadBack = rFPGA0_XC_LSSIReadBack;
    reg[RF_PATH_D]->rfLSSIReadBack = rFPGA0_XD_LSSIReadBack;

    reg[RF_PATH_A]->rfLSSIReadBackPi = TransceiverA_HSPI_Readback;
    reg[RF_PATH_B]->rfLSSIReadBackPi = TransceiverB_HSPI_Readback;
}

static bool config_parafile(struct adapter *adapt)
{
    struct eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(adapt);
    struct hal_data_8188e *hal_data = GET_HAL_DATA(adapt);

    set_baseband_phy_config(adapt);

    /* If EEPROM or EFUSE autoload OK, We must config by PHY_REG_PG.txt */
    if (!pEEPROM->bautoload_fail_flag) {
        hal_data->pwrGroupCnt = 0;
        config_bb_with_pgheader(adapt);
    }
    set_baseband_agc_config(adapt);
    return true;
}

bool rtl88eu_phy_bb_config(struct adapter *adapt)
{
    int rtstatus = true;
    struct hal_data_8188e	*hal_data = GET_HAL_DATA(adapt);
    u32 regval;
    u8 crystal_cap;

    rtl88e_phy_init_bb_rf_register_definition(adapt);

    /*  Enable BB and RF */
    regval = usb_read16(adapt, REG_SYS_FUNC_EN);
    usb_write16(adapt, REG_SYS_FUNC_EN, (u16)(regval|BIT13|BIT0|BIT1));

    usb_write8(adapt, REG_RF_CTRL, RF_EN|RF_RSTB|RF_SDMRSTB);

    usb_write8(adapt, REG_SYS_FUNC_EN, FEN_USBA | FEN_USBD | FEN_BB_GLB_RSTn | FEN_BBRSTB);

    /*  Config BB and AGC */
    rtstatus = config_parafile(adapt);

    /*  write 0x24[16:11] = 0x24[22:17] = crystal_cap */
    crystal_cap = hal_data->CrystalCap & 0x3F;
    phy_set_bb_reg(adapt, REG_AFE_XTAL_CTRL, 0x7ff800, (crystal_cap | (crystal_cap << 6)));

    return rtstatus;
}
