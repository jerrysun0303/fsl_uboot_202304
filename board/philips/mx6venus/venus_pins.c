// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2023 Shenzhen Philips N.V. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include <asm/arch/imx-regs.h>
#include <asm/arch/mx6-pins.h>
#include <asm/mach-imx/iomux-v3.h>
#include "venus_pins.h"
#include <asm/io.h>
#include <asm/gpio.h>
//#include <linux/delay.h>

#define  GPIO1_DATA 0x2090000
#define  GPIO1_DIR  0x2090004
#define  GPIO2_DATA 0x20A0000
#define  GPIO2_DIR  0x20A0004
#define  GPIO3_DATA 0x20A4000
#define  GPIO3_DIR  0x20A4004
#define  GPIO4_DATA 0x20A8000
#define  GPIO4_DIR  0x20A8004
#define  GPIO5_DATA 0x20AC000
#define  GPIO5_DIR  0x20AC004
#define  GPIO6_DATA 0x20B0000
#define  GPIO6_DIR  0x20B0004


#define VDD5V_SW_CPU_GPIO	IMX_GPIO_NR(2, 1)
#define VMAIN_IN_SW_CPU		IMX_GPIO_NR(2, 2)

#define NURSE_CALL_OUTPUT	IMX_GPIO_NR(2, 22)

#define POWER_STATE		IMX_GPIO_NR(3, 3)

#define ALARM_BLUE_LED_GPIO	IMX_GPIO_NR(3, 6)
#define ALARM_RED_LED_GPIO	IMX_GPIO_NR(3, 7)
#define ALARM_YELLOW_LED_GPIO	IMX_GPIO_NR(3, 8)

#define BOOT_IBP		IMX_GPIO_NR(3, 10)
#define WDT_IBP			IMX_GPIO_NR(3, 11)
#define WDT_F0			IMX_GPIO_NR(3, 12)
#define BOOT_F0			IMX_GPIO_NR(3, 13)
#define WDT_F1			IMX_GPIO_NR(3, 14)
#define BOOT_F1			IMX_GPIO_NR(3, 15)

#define TPS61165_PWM_GPIO IMX_GPIO_NR(1, 17)
#define TPS61165_CCFL_SW_GPIO IMX_GPIO_NR(6, 2)
#define LED_BACLLIGHT_PWM_GPIO IMX_GPIO_NR(1, 18)
#define LED_BACKLIGHT_EN_GPIO IMX_GPIO_NR(3, 9)

#define  GPIO_DIR_IN 0
#define  GPIO_DIR_OUT 1

/* Note: udelay() is not accurate for i2c timing */
static void __udelay(int time)
{
	int i, j;
	for (i = 0; i < time; i++) {
		for (j = 0; j < 200; j++) {
			asm("nop");
			asm("nop");
		}
	}
}
#define mdelay(n) ({unsigned long msec = (n); while (msec--) __udelay(1000); })

int dm_gpio_config(struct gpio_desc *desc, const  char *gpio_pin, const char *request_name,  int pin_direct)
{
	int ret = dm_gpio_lookup_name(gpio_pin, desc);
	if (ret)
		return ret;

	ret = dm_gpio_request(desc, request_name);
	if (ret)
		return ret;

	if (pin_direct == 1)
		dm_gpio_set_dir_flags(desc, GPIOD_IS_OUT | GPIOD_IS_OUT_ACTIVE);
	else
		dm_gpio_set_dir_flags(desc, GPIOD_IS_IN);

	return 0;
}

void venus_poweron_setup(void)
{
	struct gpio_desc desc_Vmain_in_G2_2;
	struct gpio_desc desc_VDD_5V_G2_1;
	struct gpio_desc desc_Backlight_G3_9;

	struct gpio_desc desc_LED_BLUE_G3_6;
	struct gpio_desc desc_LED_RED_G3_7;
	struct gpio_desc desc_LED_YELLOW_G3_8;
	struct gpio_desc desc_NURSE_CALL_G2_22;
	struct gpio_desc desc_POWER_LED_G3_3;
	struct gpio_desc  desc_TPS61165_PWM_GPIO;
	struct gpio_desc  desc_TPS61165_CCFL_SW_GPIO;
	struct gpio_desc  desc_BOOT_IBP;
	struct gpio_desc  desc_WDT_IBP;
	struct gpio_desc  desc_WDT_F0;
	struct gpio_desc  desc_BOOT_F0;
	struct gpio_desc  desc_WDT_F1;
	struct gpio_desc  desc_BOOT_F1;

	imx_iomux_v3_setup_pad(MX6_PAD_SD1_DAT1__GPIO1_IO17  | MUX_PAD_CTRL(NO_PAD_CTRL));
	dm_gpio_config(&desc_TPS61165_PWM_GPIO, "GPIO1_17", "tps61165 pwm", GPIO_DIR_OUT);

	imx_iomux_v3_setup_pad(MX6_PAD_CSI0_DAT16__GPIO6_IO02 | MUX_PAD_CTRL(NO_PAD_CTRL));
	dm_gpio_config(&desc_TPS61165_CCFL_SW_GPIO, "GPIO6_2", "tps61165 CCFL", GPIO_DIR_OUT);
	/*backlight of LCD & M21 & GPIO3_9 pin*/
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA9__GPIO3_IO09 | MUX_PAD_CTRL(NO_PAD_CTRL));
	dm_gpio_config(&desc_Backlight_G3_9, "GPIO3_9", "back light", GPIO_DIR_OUT);

	/*leds G3_6 G3_7 G3_8 */
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA6__GPIO3_IO06 | MUX_PAD_CTRL(NO_PAD_CTRL));
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA7__GPIO3_IO07 | MUX_PAD_CTRL(NO_PAD_CTRL));
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA8__GPIO3_IO08| MUX_PAD_CTRL(NO_PAD_CTRL));
	dm_gpio_config(&desc_LED_BLUE_G3_6, "GPIO3_6", "led blue", GPIO_DIR_OUT);
	dm_gpio_config(&desc_LED_RED_G3_7, "GPIO3_7", "led red", GPIO_DIR_OUT);
	dm_gpio_config(&desc_LED_YELLOW_G3_8, "GPIO3_8", "led yellow", GPIO_DIR_OUT);

	/* NURSE CALL ouput & H25 && GPIO2_22*/
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_A16__GPIO2_IO22 | MUX_PAD_CTRL(NO_PAD_CTRL));
	dm_gpio_config(&desc_NURSE_CALL_G2_22, "GPIO2_22", "nurse call", GPIO_DIR_OUT);

	/* Power ON/OFF LED enable & K24 && GPIO3_3*/
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA3__GPIO3_IO03 | MUX_PAD_CTRL(NO_PAD_CTRL));
	dm_gpio_config(&desc_POWER_LED_G3_3, "GPIO3_3", "power on/off led", GPIO_DIR_OUT);

	 /* Vmain_in & F16 & GPIO2_2 pin */
	imx_iomux_v3_setup_pad(MX6_PAD_NANDF_D2__GPIO2_IO02 | MUX_PAD_CTRL(NO_PAD_CTRL));
	dm_gpio_config(&desc_Vmain_in_G2_2, "GPIO2_2", "Vmain in", GPIO_DIR_OUT);

	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA10__GPIO3_IO10 | MUX_PAD_CTRL(NO_PAD_CTRL));
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA11__GPIO3_IO11 | MUX_PAD_CTRL(NO_PAD_CTRL));
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA12__GPIO3_IO12 | MUX_PAD_CTRL(NO_PAD_CTRL));
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA13__GPIO3_IO13 | MUX_PAD_CTRL(NO_PAD_CTRL));
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA14__GPIO3_IO14 | MUX_PAD_CTRL(NO_PAD_CTRL));
	imx_iomux_v3_setup_pad(MX6_PAD_EIM_DA15__GPIO3_IO15 | MUX_PAD_CTRL(NO_PAD_CTRL));

	dm_gpio_config(&desc_BOOT_IBP, "GPIO3_10", "boot ibp", GPIO_DIR_OUT);
	dm_gpio_config(&desc_BOOT_F0, "GPIO3_11", "boot f0", GPIO_DIR_OUT);
	dm_gpio_config(&desc_BOOT_F1, "GPIO3_12", "boot f1", GPIO_DIR_OUT);
	dm_gpio_config(&desc_WDT_IBP, "GPIO3_13", "wdt ibp", GPIO_DIR_OUT);
	dm_gpio_config(&desc_WDT_F0, "GPIO3_14", "wdt f0", GPIO_DIR_OUT);
	dm_gpio_config(&desc_WDT_F1, "GPIO3_15", "wdt f1", GPIO_DIR_OUT);

	/* VDD5V_SW_CPU */
	imx_iomux_v3_setup_pad(MX6_PAD_NANDF_D1__GPIO2_IO01 | MUX_PAD_CTRL(NO_PAD_CTRL));
	dm_gpio_config(&desc_VDD_5V_G2_1, "GPIO2_1", "VDD 5V", GPIO_DIR_OUT);

	__udelay(1000*1000);
	__udelay(500*1000);

	/*enable Power ON LED  */
	dm_gpio_set_value(&desc_POWER_LED_G3_3, 1);
	/*enable VDD 5v*/
	dm_gpio_set_value(&desc_VDD_5V_G2_1, 1);
	/*enable Vmain in*/
	dm_gpio_set_value(&desc_Vmain_in_G2_2, 1);

	/*light leds*/
	dm_gpio_set_value(&desc_LED_BLUE_G3_6, 1);
	dm_gpio_set_value(&desc_LED_RED_G3_7, 1);
	dm_gpio_set_value(&desc_LED_YELLOW_G3_8, 1);


	__udelay(600*1000);

	dm_gpio_set_value(&desc_WDT_IBP, 1);
	dm_gpio_set_value(&desc_WDT_F0, 1);
	dm_gpio_set_value(&desc_WDT_F1, 1);

}

/*------------------------------------------------------*/
/* Debug UART 1*/
/*------------------------------------------------------*/
void venus_uart_debug_pins (void)
{
	/* UART1 TXD */
	imx_iomux_v3_setup_pad(MX6_PAD_SD3_DAT7__UART1_TX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL));
	/* UART1 RXD */
	imx_iomux_v3_setup_pad(MX6_PAD_SD3_DAT6__UART1_RX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL));
}

/*------------------------------------------------------*/
/* watch dog config,  need test*/
/*------------------------------------------------------*/
void venus_watchdog_config(void)
{
	imx_iomux_v3_setup_pad(MX6_PAD_SD1_DAT3__WDOG2_B);
	imx_iomux_v3_setup_pad(MX6_PAD_GPIO_9__WDOG1_B);
}