/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 *
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/pinctrl/pinctrl.h>
#include "pinctrl-mxs.h"

enum imx28_pin_enum {
    GPMI_D00	= PINID(0, 0),
    GPMI_D01	= PINID(0, 1),
    GPMI_D02	= PINID(0, 2),
    GPMI_D03	= PINID(0, 3),
    GPMI_D04	= PINID(0, 4),
    GPMI_D05	= PINID(0, 5),
    GPMI_D06	= PINID(0, 6),
    GPMI_D07	= PINID(0, 7),
    GPMI_CE0N	= PINID(0, 16),
    GPMI_CE1N	= PINID(0, 17),
    GPMI_CE2N	= PINID(0, 18),
    GPMI_CE3N	= PINID(0, 19),
    GPMI_RDY0	= PINID(0, 20),
    GPMI_RDY1	= PINID(0, 21),
    GPMI_RDY2	= PINID(0, 22),
    GPMI_RDY3	= PINID(0, 23),
    GPMI_RDN	= PINID(0, 24),
    GPMI_WRN	= PINID(0, 25),
    GPMI_ALE	= PINID(0, 26),
    GPMI_CLE	= PINID(0, 27),
    GPMI_RESETN	= PINID(0, 28),
    LCD_D00		= PINID(1, 0),
    LCD_D01		= PINID(1, 1),
    LCD_D02		= PINID(1, 2),
    LCD_D03		= PINID(1, 3),
    LCD_D04		= PINID(1, 4),
    LCD_D05		= PINID(1, 5),
    LCD_D06		= PINID(1, 6),
    LCD_D07		= PINID(1, 7),
    LCD_D08		= PINID(1, 8),
    LCD_D09		= PINID(1, 9),
    LCD_D10		= PINID(1, 10),
    LCD_D11		= PINID(1, 11),
    LCD_D12		= PINID(1, 12),
    LCD_D13		= PINID(1, 13),
    LCD_D14		= PINID(1, 14),
    LCD_D15		= PINID(1, 15),
    LCD_D16		= PINID(1, 16),
    LCD_D17		= PINID(1, 17),
    LCD_D18		= PINID(1, 18),
    LCD_D19		= PINID(1, 19),
    LCD_D20		= PINID(1, 20),
    LCD_D21		= PINID(1, 21),
    LCD_D22		= PINID(1, 22),
    LCD_D23		= PINID(1, 23),
    LCD_RD_E	= PINID(1, 24),
    LCD_WR_RWN	= PINID(1, 25),
    LCD_RS		= PINID(1, 26),
    LCD_CS		= PINID(1, 27),
    LCD_VSYNC	= PINID(1, 28),
    LCD_HSYNC	= PINID(1, 29),
    LCD_DOTCLK	= PINID(1, 30),
    LCD_ENABLE	= PINID(1, 31),
    SSP0_DATA0	= PINID(2, 0),
    SSP0_DATA1	= PINID(2, 1),
    SSP0_DATA2	= PINID(2, 2),
    SSP0_DATA3	= PINID(2, 3),
    SSP0_DATA4	= PINID(2, 4),
    SSP0_DATA5	= PINID(2, 5),
    SSP0_DATA6	= PINID(2, 6),
    SSP0_DATA7	= PINID(2, 7),
    SSP0_CMD	= PINID(2, 8),
    SSP0_DETECT	= PINID(2, 9),
    SSP0_SCK	= PINID(2, 10),
    SSP1_SCK	= PINID(2, 12),
    SSP1_CMD	= PINID(2, 13),
    SSP1_DATA0	= PINID(2, 14),
    SSP1_DATA3	= PINID(2, 15),
    SSP2_SCK	= PINID(2, 16),
    SSP2_MOSI	= PINID(2, 17),
    SSP2_MISO	= PINID(2, 18),
    SSP2_SS0	= PINID(2, 19),
    SSP2_SS1	= PINID(2, 20),
    SSP2_SS2	= PINID(2, 21),
    SSP3_SCK	= PINID(2, 24),
    SSP3_MOSI	= PINID(2, 25),
    SSP3_MISO	= PINID(2, 26),
    SSP3_SS0	= PINID(2, 27),
    AUART0_RX	= PINID(3, 0),
    AUART0_TX	= PINID(3, 1),
    AUART0_CTS	= PINID(3, 2),
    AUART0_RTS	= PINID(3, 3),
    AUART1_RX	= PINID(3, 4),
    AUART1_TX	= PINID(3, 5),
    AUART1_CTS	= PINID(3, 6),
    AUART1_RTS	= PINID(3, 7),
    AUART2_RX	= PINID(3, 8),
    AUART2_TX	= PINID(3, 9),
    AUART2_CTS	= PINID(3, 10),
    AUART2_RTS	= PINID(3, 11),
    AUART3_RX	= PINID(3, 12),
    AUART3_TX	= PINID(3, 13),
    AUART3_CTS	= PINID(3, 14),
    AUART3_RTS	= PINID(3, 15),
    PWM0		= PINID(3, 16),
    PWM1		= PINID(3, 17),
    PWM2		= PINID(3, 18),
    SAIF0_MCLK	= PINID(3, 20),
    SAIF0_LRCLK	= PINID(3, 21),
    SAIF0_BITCLK	= PINID(3, 22),
    SAIF0_SDATA0	= PINID(3, 23),
    I2C0_SCL	= PINID(3, 24),
    I2C0_SDA	= PINID(3, 25),
    SAIF1_SDATA0	= PINID(3, 26),
    SPDIF		= PINID(3, 27),
    PWM3		= PINID(3, 28),
    PWM4		= PINID(3, 29),
    LCD_RESET	= PINID(3, 30),
    ENET0_MDC	= PINID(4, 0),
    ENET0_MDIO	= PINID(4, 1),
    ENET0_RX_EN	= PINID(4, 2),
    ENET0_RXD0	= PINID(4, 3),
    ENET0_RXD1	= PINID(4, 4),
    ENET0_TX_CLK	= PINID(4, 5),
    ENET0_TX_EN	= PINID(4, 6),
    ENET0_TXD0	= PINID(4, 7),
    ENET0_TXD1	= PINID(4, 8),
    ENET0_RXD2	= PINID(4, 9),
    ENET0_RXD3	= PINID(4, 10),
    ENET0_TXD2	= PINID(4, 11),
    ENET0_TXD3	= PINID(4, 12),
    ENET0_RX_CLK	= PINID(4, 13),
    ENET0_COL	= PINID(4, 14),
    ENET0_CRS	= PINID(4, 15),
    ENET_CLK	= PINID(4, 16),
    JTAG_RTCK	= PINID(4, 20),
    EMI_D00		= PINID(5, 0),
    EMI_D01		= PINID(5, 1),
    EMI_D02		= PINID(5, 2),
    EMI_D03		= PINID(5, 3),
    EMI_D04		= PINID(5, 4),
    EMI_D05		= PINID(5, 5),
    EMI_D06		= PINID(5, 6),
    EMI_D07		= PINID(5, 7),
    EMI_D08		= PINID(5, 8),
    EMI_D09		= PINID(5, 9),
    EMI_D10		= PINID(5, 10),
    EMI_D11		= PINID(5, 11),
    EMI_D12		= PINID(5, 12),
    EMI_D13		= PINID(5, 13),
    EMI_D14		= PINID(5, 14),
    EMI_D15		= PINID(5, 15),
    EMI_ODT0	= PINID(5, 16),
    EMI_DQM0	= PINID(5, 17),
    EMI_ODT1	= PINID(5, 18),
    EMI_DQM1	= PINID(5, 19),
    EMI_DDR_OPEN_FB	= PINID(5, 20),
    EMI_CLK		= PINID(5, 21),
    EMI_DQS0	= PINID(5, 22),
    EMI_DQS1	= PINID(5, 23),
    EMI_DDR_OPEN	= PINID(5, 26),
    EMI_A00		= PINID(6, 0),
    EMI_A01		= PINID(6, 1),
    EMI_A02		= PINID(6, 2),
    EMI_A03		= PINID(6, 3),
    EMI_A04		= PINID(6, 4),
    EMI_A05		= PINID(6, 5),
    EMI_A06		= PINID(6, 6),
    EMI_A07		= PINID(6, 7),
    EMI_A08		= PINID(6, 8),
    EMI_A09		= PINID(6, 9),
    EMI_A10		= PINID(6, 10),
    EMI_A11		= PINID(6, 11),
    EMI_A12		= PINID(6, 12),
    EMI_A13		= PINID(6, 13),
    EMI_A14		= PINID(6, 14),
    EMI_BA0		= PINID(6, 16),
    EMI_BA1		= PINID(6, 17),
    EMI_BA2		= PINID(6, 18),
    EMI_CASN	= PINID(6, 19),
    EMI_RASN	= PINID(6, 20),
    EMI_WEN		= PINID(6, 21),
    EMI_CE0N	= PINID(6, 22),
    EMI_CE1N	= PINID(6, 23),
    EMI_CKE		= PINID(6, 24),
};

static const struct pinctrl_pin_desc imx28_pins[] = {
    MXS_PINCTRL_PIN(GPMI_D00),
    MXS_PINCTRL_PIN(GPMI_D01),
    MXS_PINCTRL_PIN(GPMI_D02),
    MXS_PINCTRL_PIN(GPMI_D03),
    MXS_PINCTRL_PIN(GPMI_D04),
    MXS_PINCTRL_PIN(GPMI_D05),
    MXS_PINCTRL_PIN(GPMI_D06),
    MXS_PINCTRL_PIN(GPMI_D07),
    MXS_PINCTRL_PIN(GPMI_CE0N),
    MXS_PINCTRL_PIN(GPMI_CE1N),
    MXS_PINCTRL_PIN(GPMI_CE2N),
    MXS_PINCTRL_PIN(GPMI_CE3N),
    MXS_PINCTRL_PIN(GPMI_RDY0),
    MXS_PINCTRL_PIN(GPMI_RDY1),
    MXS_PINCTRL_PIN(GPMI_RDY2),
    MXS_PINCTRL_PIN(GPMI_RDY3),
    MXS_PINCTRL_PIN(GPMI_RDN),
    MXS_PINCTRL_PIN(GPMI_WRN),
    MXS_PINCTRL_PIN(GPMI_ALE),
    MXS_PINCTRL_PIN(GPMI_CLE),
    MXS_PINCTRL_PIN(GPMI_RESETN),
    MXS_PINCTRL_PIN(LCD_D00),
    MXS_PINCTRL_PIN(LCD_D01),
    MXS_PINCTRL_PIN(LCD_D02),
    MXS_PINCTRL_PIN(LCD_D03),
    MXS_PINCTRL_PIN(LCD_D04),
    MXS_PINCTRL_PIN(LCD_D05),
    MXS_PINCTRL_PIN(LCD_D06),
    MXS_PINCTRL_PIN(LCD_D07),
    MXS_PINCTRL_PIN(LCD_D08),
    MXS_PINCTRL_PIN(LCD_D09),
    MXS_PINCTRL_PIN(LCD_D10),
    MXS_PINCTRL_PIN(LCD_D11),
    MXS_PINCTRL_PIN(LCD_D12),
    MXS_PINCTRL_PIN(LCD_D13),
    MXS_PINCTRL_PIN(LCD_D14),
    MXS_PINCTRL_PIN(LCD_D15),
    MXS_PINCTRL_PIN(LCD_D16),
    MXS_PINCTRL_PIN(LCD_D17),
    MXS_PINCTRL_PIN(LCD_D18),
    MXS_PINCTRL_PIN(LCD_D19),
    MXS_PINCTRL_PIN(LCD_D20),
    MXS_PINCTRL_PIN(LCD_D21),
    MXS_PINCTRL_PIN(LCD_D22),
    MXS_PINCTRL_PIN(LCD_D23),
    MXS_PINCTRL_PIN(LCD_RD_E),
    MXS_PINCTRL_PIN(LCD_WR_RWN),
    MXS_PINCTRL_PIN(LCD_RS),
    MXS_PINCTRL_PIN(LCD_CS),
    MXS_PINCTRL_PIN(LCD_VSYNC),
    MXS_PINCTRL_PIN(LCD_HSYNC),
    MXS_PINCTRL_PIN(LCD_DOTCLK),
    MXS_PINCTRL_PIN(LCD_ENABLE),
    MXS_PINCTRL_PIN(SSP0_DATA0),
    MXS_PINCTRL_PIN(SSP0_DATA1),
    MXS_PINCTRL_PIN(SSP0_DATA2),
    MXS_PINCTRL_PIN(SSP0_DATA3),
    MXS_PINCTRL_PIN(SSP0_DATA4),
    MXS_PINCTRL_PIN(SSP0_DATA5),
    MXS_PINCTRL_PIN(SSP0_DATA6),
    MXS_PINCTRL_PIN(SSP0_DATA7),
    MXS_PINCTRL_PIN(SSP0_CMD),
    MXS_PINCTRL_PIN(SSP0_DETECT),
    MXS_PINCTRL_PIN(SSP0_SCK),
    MXS_PINCTRL_PIN(SSP1_SCK),
    MXS_PINCTRL_PIN(SSP1_CMD),
    MXS_PINCTRL_PIN(SSP1_DATA0),
    MXS_PINCTRL_PIN(SSP1_DATA3),
    MXS_PINCTRL_PIN(SSP2_SCK),
    MXS_PINCTRL_PIN(SSP2_MOSI),
    MXS_PINCTRL_PIN(SSP2_MISO),
    MXS_PINCTRL_PIN(SSP2_SS0),
    MXS_PINCTRL_PIN(SSP2_SS1),
    MXS_PINCTRL_PIN(SSP2_SS2),
    MXS_PINCTRL_PIN(SSP3_SCK),
    MXS_PINCTRL_PIN(SSP3_MOSI),
    MXS_PINCTRL_PIN(SSP3_MISO),
    MXS_PINCTRL_PIN(SSP3_SS0),
    MXS_PINCTRL_PIN(AUART0_RX),
    MXS_PINCTRL_PIN(AUART0_TX),
    MXS_PINCTRL_PIN(AUART0_CTS),
    MXS_PINCTRL_PIN(AUART0_RTS),
    MXS_PINCTRL_PIN(AUART1_RX),
    MXS_PINCTRL_PIN(AUART1_TX),
    MXS_PINCTRL_PIN(AUART1_CTS),
    MXS_PINCTRL_PIN(AUART1_RTS),
    MXS_PINCTRL_PIN(AUART2_RX),
    MXS_PINCTRL_PIN(AUART2_TX),
    MXS_PINCTRL_PIN(AUART2_CTS),
    MXS_PINCTRL_PIN(AUART2_RTS),
    MXS_PINCTRL_PIN(AUART3_RX),
    MXS_PINCTRL_PIN(AUART3_TX),
    MXS_PINCTRL_PIN(AUART3_CTS),
    MXS_PINCTRL_PIN(AUART3_RTS),
    MXS_PINCTRL_PIN(PWM0),
    MXS_PINCTRL_PIN(PWM1),
    MXS_PINCTRL_PIN(PWM2),
    MXS_PINCTRL_PIN(SAIF0_MCLK),
    MXS_PINCTRL_PIN(SAIF0_LRCLK),
    MXS_PINCTRL_PIN(SAIF0_BITCLK),
    MXS_PINCTRL_PIN(SAIF0_SDATA0),
    MXS_PINCTRL_PIN(I2C0_SCL),
    MXS_PINCTRL_PIN(I2C0_SDA),
    MXS_PINCTRL_PIN(SAIF1_SDATA0),
    MXS_PINCTRL_PIN(SPDIF),
    MXS_PINCTRL_PIN(PWM3),
    MXS_PINCTRL_PIN(PWM4),
    MXS_PINCTRL_PIN(LCD_RESET),
    MXS_PINCTRL_PIN(ENET0_MDC),
    MXS_PINCTRL_PIN(ENET0_MDIO),
    MXS_PINCTRL_PIN(ENET0_RX_EN),
    MXS_PINCTRL_PIN(ENET0_RXD0),
    MXS_PINCTRL_PIN(ENET0_RXD1),
    MXS_PINCTRL_PIN(ENET0_TX_CLK),
    MXS_PINCTRL_PIN(ENET0_TX_EN),
    MXS_PINCTRL_PIN(ENET0_TXD0),
    MXS_PINCTRL_PIN(ENET0_TXD1),
    MXS_PINCTRL_PIN(ENET0_RXD2),
    MXS_PINCTRL_PIN(ENET0_RXD3),
    MXS_PINCTRL_PIN(ENET0_TXD2),
    MXS_PINCTRL_PIN(ENET0_TXD3),
    MXS_PINCTRL_PIN(ENET0_RX_CLK),
    MXS_PINCTRL_PIN(ENET0_COL),
    MXS_PINCTRL_PIN(ENET0_CRS),
    MXS_PINCTRL_PIN(ENET_CLK),
    MXS_PINCTRL_PIN(JTAG_RTCK),
    MXS_PINCTRL_PIN(EMI_D00),
    MXS_PINCTRL_PIN(EMI_D01),
    MXS_PINCTRL_PIN(EMI_D02),
    MXS_PINCTRL_PIN(EMI_D03),
    MXS_PINCTRL_PIN(EMI_D04),
    MXS_PINCTRL_PIN(EMI_D05),
    MXS_PINCTRL_PIN(EMI_D06),
    MXS_PINCTRL_PIN(EMI_D07),
    MXS_PINCTRL_PIN(EMI_D08),
    MXS_PINCTRL_PIN(EMI_D09),
    MXS_PINCTRL_PIN(EMI_D10),
    MXS_PINCTRL_PIN(EMI_D11),
    MXS_PINCTRL_PIN(EMI_D12),
    MXS_PINCTRL_PIN(EMI_D13),
    MXS_PINCTRL_PIN(EMI_D14),
    MXS_PINCTRL_PIN(EMI_D15),
    MXS_PINCTRL_PIN(EMI_ODT0),
    MXS_PINCTRL_PIN(EMI_DQM0),
    MXS_PINCTRL_PIN(EMI_ODT1),
    MXS_PINCTRL_PIN(EMI_DQM1),
    MXS_PINCTRL_PIN(EMI_DDR_OPEN_FB),
    MXS_PINCTRL_PIN(EMI_CLK),
    MXS_PINCTRL_PIN(EMI_DQS0),
    MXS_PINCTRL_PIN(EMI_DQS1),
    MXS_PINCTRL_PIN(EMI_DDR_OPEN),
    MXS_PINCTRL_PIN(EMI_A00),
    MXS_PINCTRL_PIN(EMI_A01),
    MXS_PINCTRL_PIN(EMI_A02),
    MXS_PINCTRL_PIN(EMI_A03),
    MXS_PINCTRL_PIN(EMI_A04),
    MXS_PINCTRL_PIN(EMI_A05),
    MXS_PINCTRL_PIN(EMI_A06),
    MXS_PINCTRL_PIN(EMI_A07),
    MXS_PINCTRL_PIN(EMI_A08),
    MXS_PINCTRL_PIN(EMI_A09),
    MXS_PINCTRL_PIN(EMI_A10),
    MXS_PINCTRL_PIN(EMI_A11),
    MXS_PINCTRL_PIN(EMI_A12),
    MXS_PINCTRL_PIN(EMI_A13),
    MXS_PINCTRL_PIN(EMI_A14),
    MXS_PINCTRL_PIN(EMI_BA0),
    MXS_PINCTRL_PIN(EMI_BA1),
    MXS_PINCTRL_PIN(EMI_BA2),
    MXS_PINCTRL_PIN(EMI_CASN),
    MXS_PINCTRL_PIN(EMI_RASN),
    MXS_PINCTRL_PIN(EMI_WEN),
    MXS_PINCTRL_PIN(EMI_CE0N),
    MXS_PINCTRL_PIN(EMI_CE1N),
    MXS_PINCTRL_PIN(EMI_CKE),
};

static struct mxs_regs imx28_regs = {
    .muxsel = 0x100,
    .drive = 0x300,
    .pull = 0x600,
};

static struct mxs_pinctrl_soc_data imx28_pinctrl_data = {
    .regs = &imx28_regs,
    .pins = imx28_pins,
    .npins = ARRAY_SIZE(imx28_pins),
};

static int imx28_pinctrl_probe(struct platform_device *pdev)
{
    return mxs_pinctrl_probe(pdev, &imx28_pinctrl_data);
}

static const struct of_device_id imx28_pinctrl_of_match[] = {
    { .compatible = "fsl,imx28-pinctrl", },
    { /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, imx28_pinctrl_of_match);

static struct platform_driver imx28_pinctrl_driver = {
    .driver = {
        .name = "imx28-pinctrl",
        .of_match_table = imx28_pinctrl_of_match,
    },
    .probe = imx28_pinctrl_probe,
    .remove = mxs_pinctrl_remove,
};

static int __init imx28_pinctrl_init(void)
{
    return platform_driver_register(&imx28_pinctrl_driver);
}
postcore_initcall(imx28_pinctrl_init);

static void __exit imx28_pinctrl_exit(void)
{
    platform_driver_unregister(&imx28_pinctrl_driver);
}
module_exit(imx28_pinctrl_exit);

MODULE_AUTHOR("Shawn Guo <shawn.guo@linaro.org>");
MODULE_DESCRIPTION("Freescale i.MX28 pinctrl driver");
MODULE_LICENSE("GPL v2");
