/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2023 Koninklijke Philips N.V. All Rights Reserved.
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

#ifndef __MX6DL_VENUS_CONFIG_H
#define __MX6DL_VENUS_CONFIG_H

#define CFG_MXC_UART_BASE	UART1_BASE
#define CONSOLE_DEV		"ttymxc0"

#if defined(CONFIG_MX6Q) || defined(CONFIG_MX6QP)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6DL)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6S)
#define PHYS_SDRAM_SIZE		(512u * 1024 * 1024)
#endif

#include "mx6dl_venus_common.h"
//#include "mx6sabre_common.h"

/* Falcon Mode */

/* Falcon Mode - MMC support: args@1MB kernel@2MB */

#define CFG_SYS_FSL_USDHC_NUM	3

/* PMIC */
#define CFG_POWER_PFUZE100_I2C_ADDR	0x08

/* USB Configs */
#ifdef CONFIG_CMD_USB
#define CFG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CFG_MXC_USB_FLAGS		0
#endif

#endif                         /* __MX6DL_VENUS_CONFIG_H */
