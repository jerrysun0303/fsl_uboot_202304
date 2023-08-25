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
#include <asm/fsl_law.h>
#include <asm/mmu.h>

struct law_entry law_table[] = {
	SET_LAW(CFG_SYS_FLASH_BASE_PHYS, LAW_SIZE_256M, LAW_TRGT_IF_LBC),
#ifdef CFG_SYS_BMAN_MEM_PHYS
	SET_LAW(CFG_SYS_BMAN_MEM_PHYS, LAW_SIZE_2M, LAW_TRGT_IF_BMAN),
#endif
#ifdef CFG_SYS_QMAN_MEM_PHYS
	SET_LAW(CFG_SYS_QMAN_MEM_PHYS, LAW_SIZE_2M, LAW_TRGT_IF_QMAN),
#endif
#ifdef PIXIS_BASE_PHYS
	SET_LAW(PIXIS_BASE_PHYS, LAW_SIZE_4K, LAW_TRGT_IF_LBC),
#endif
#ifdef CPLD_BASE_PHYS
	SET_LAW(CPLD_BASE_PHYS, LAW_SIZE_4K, LAW_TRGT_IF_LBC),
#endif
#ifdef CFG_SYS_DCSRBAR_PHYS
	/* Limit DCSR to 32M to access NPC Trace Buffer */
	SET_LAW(CFG_SYS_DCSRBAR_PHYS, LAW_SIZE_32M, LAW_TRGT_IF_DCSR),
#endif
#ifdef CFG_SYS_NAND_BASE_PHYS
	SET_LAW(CFG_SYS_NAND_BASE_PHYS, LAW_SIZE_1M, LAW_TRGT_IF_LBC),
#endif
};

int num_law_entries = ARRAY_SIZE(law_table);
