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
#include <asm/io.h>
#include <asm/arch/ls102xa_stream_id.h>

void ls102xa_config_smmu_stream_id(struct smmu_stream_id *id, uint32_t num)
{
	void *scfg = (void *)CFG_SYS_FSL_SCFG_ADDR;
	int i;
	u32 icid;

	for (i = 0; i < num; i++) {
		icid = (id[i].stream_id & 0xff) << 24;
		out_be32((u32 *)(scfg + id[i].offset), icid);
	}
}

void ls1021x_config_caam_stream_id(struct liodn_id_table *tbl, int size)
{
	int i;
	u32 liodn;

	for (i = 0; i < size; i++) {
		if (tbl[i].num_ids == 2)
			liodn = (tbl[i].id[0] << 16) | tbl[i].id[1];
		else
			liodn = tbl[i].id[0];

		out_le32((u32 *)(tbl[i].reg_offset), liodn);
	}
}
