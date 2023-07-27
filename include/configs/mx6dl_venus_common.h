/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * Copyright 2018 NXP
 *
 * Configuration settings for the Freescale i.MX6Q SabreSD board.
 */

#ifndef __MX6DL_VENUS_COMMON_CONFIG_H
#define __MX6DL_VENUS_COMMON_CONFIG_H

#include <linux/stringify.h>
#include "mx6_common.h"
#include "imx_env.h"

/* MMC Configs */
#define CFG_SYS_FSL_ESDHC_ADDR      0

#ifdef CONFIG_MX6S
#define SYS_NOSMP "nosmp"
#else
#define SYS_NOSMP
#endif

#ifdef CONFIG_NAND_BOOT
#define MFG_NAND_PARTITION "mtdparts=8000000.nor:1m(boot),-(rootfs)\\;gpmi-nand:64m(nandboot),16m(nandkernel),16m(nanddtb),16m(nandtee),-(nandrootfs)"
#else
#define MFG_NAND_PARTITION ""
#endif

#define CONFIG_FEC_CLOCK_FROM_ANATOP
#undef is_boot_from_usb


#define MACH_NAME		"mx6dl-olive-1.0"
					
#define CFG_EXTRA_ENV_SETTINGS \
		"ipaddr=192.168.1.99\0"						\
		"serverip=192.168.1.200\0"						\
		"gatewayip=192.168.1.1\0"    \
		"netmask=255.255.255.0\0"    \
		"ethaddr=00:0c:29:e7:39:85\0"    \
		"fdt_addr=0x18000000\0"						\
		"emmc_dev=3\0"	\
		"netdev=eth0\0"						\
		"ethprime=FEC0\0"					\
		"lvds_num=0\0"						\
		"splashimage=0x30000000\0"				\
		"splashpos=m,m\0"					\
		"verify=no\0"						\
		"uboot=mx6/u-boot.bin\0"				\
		"kernel=mx6/uImage\0"					\
		"nfsroot=/opt/eldk/arm\0"				\
		"mach="MACH_NAME"\0"					\
		"mmcdev=3\0"						\
		"console=null\0"					\
		"bootargs_base=setenv bootargs console=${console} " 	\
			"machine=${mach} "				\
			"u_boot_version=${u_boot_version} "		\
			"user_debug=0x1f panic=1\0"			\
		"bootargs_nfs=setenv bootargs ${bootargs} root=/dev/nfs "\
			"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0"\
		"bootcmd_net=run bootargs_base bootargs_nfs; "		\
			"tftpboot ${loadaddr} ${kernel}; bootm\0"	\
		"bootargs_mmc=setenv bootargs ${bootargs} "     	\
			"root=/dev/mmcblk0p1 rootwait\0"                \
		"bootcmd_mmc=run bootargs_base bootargs_mmc; "   	\
			"mmc dev ${mmcdev}; "				\
			"mmc read ${loadaddr} 0x800 0x2000; bootm\0"	\
		"bootcmd=run bootcmd_mmc\0"				\


/* Physical Memory Map */
#define PHYS_SDRAM                     MMDC0_ARB_BASE_ADDR

#define CFG_SYS_SDRAM_BASE          PHYS_SDRAM
#define CFG_SYS_INIT_RAM_ADDR       IRAM_BASE_ADDR
#define CFG_SYS_INIT_RAM_SIZE       IRAM_SIZE

#endif                         /* __MX6QSABRE_COMMON_CONFIG_H */
