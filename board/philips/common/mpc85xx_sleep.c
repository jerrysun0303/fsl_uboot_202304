// SPDX-License-Identifier: GPL-2.0+
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

#include <common.h>
#include <log.h>
#include <asm/global_data.h>
#include <asm/immap_85xx.h>
#include "sleep.h"
#ifdef CONFIG_U_QE
#include <fsl_qe.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

void __weak board_mem_sleep_setup(void)
{
}

void __weak board_sleep_prepare(void)
{
}

bool is_warm_boot(void)
{
	struct ccsr_gur __iomem *gur = (void *)CFG_SYS_MPC85xx_GUTS_ADDR;

	if (in_be32(&gur->scrtsr[0]) & DCFG_CCSR_CRSTSR_WDRFR)
		return 1;

	return 0;
}

void fsl_dp_disable_console(void)
{
	gd->flags |= GD_FLG_SILENT | GD_FLG_DISABLE_CONSOLE;
}

/*
 * When wakeup from deep sleep, the first 128 bytes space
 * will be used to do DDR training which corrupts the data
 * in there. This function will restore them.
 */
static void dp_ddr_restore(void)
{
	u64 *src, *dst;
	int i;
	struct ccsr_scfg __iomem *scfg = (void *)CFG_SYS_MPC85xx_SCFG;

	/* get the address of ddr date from SPARECR3 */
	src = (u64 *)(in_be32(&scfg->sparecr[2]) + DDR_BUFF_LEN - 8);
	dst = (u64 *)(CFG_SYS_SDRAM_BASE + DDR_BUFF_LEN - 8);

	for (i = 0; i < DDR_BUFF_LEN / 8; i++)
		*dst-- = *src--;

	flush_dcache();
}

static void dp_resume_prepare(void)
{
	dp_ddr_restore();

	board_sleep_prepare();

	l2cache_init();
#if defined(CONFIG_RAMBOOT_PBL)
	disable_cpc_sram();
#endif
	enable_cpc();

#ifdef CONFIG_U_QE
	u_qe_resume();
#endif

}

int fsl_dp_resume(void)
{
	u32 start_addr;
	void (*kernel_resume)(void);
	struct ccsr_scfg __iomem *scfg = (void *)CFG_SYS_MPC85xx_SCFG;

	if (!is_warm_boot())
		return 0;

	dp_resume_prepare();

	/* Get the entry address and jump to kernel */
	start_addr = in_be32(&scfg->sparecr[1]);
	debug("Entry address is 0x%08x\n", start_addr);
	kernel_resume = (void (*)(void))start_addr;
	kernel_resume();

	return 0;
}
