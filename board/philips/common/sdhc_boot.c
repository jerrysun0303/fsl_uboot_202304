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
#include <mmc.h>
#include <malloc.h>

/*
 * The environment variables are written to just after the u-boot image
 * on SDCard, so we must read the MBR to get the start address and code
 * length of the u-boot image, then calculate the address of the env.
 */
#define ESDHC_BOOT_IMAGE_SIZE	0x48
#define ESDHC_BOOT_IMAGE_ADDR	0x50

#define ESDHC_DEFAULT_ENVADDR	0x400

int mmc_get_env_addr(struct mmc *mmc, int copy, u32 *env_addr)
{
	u8 *tmp_buf;
	u32 blklen, code_offset, code_len, n;

	blklen = mmc->read_bl_len;
	tmp_buf = malloc(blklen);
	if (!tmp_buf)
		return 1;

	/* read out the first block, get the config data information */
#ifdef CONFIG_BLK
	n = blk_dread(mmc_get_blk_desc(mmc), 0, 1, tmp_buf);
#else
	n = mmc->block_dev.block_read(&mmc->block_dev, 0, 1, tmp_buf);
#endif
	if (!n) {
		free(tmp_buf);
		return 1;
	}

	/* Get the Source Address, from offset 0x50 */
	code_offset = *(u32 *)(tmp_buf + ESDHC_BOOT_IMAGE_ADDR);

	/* Get the code size from offset 0x48 */
	code_len = *(u32 *)(tmp_buf + ESDHC_BOOT_IMAGE_SIZE);

#ifdef CONFIG_ESDHC_HC_BLK_ADDR
	/*
	 * On soc BSC9131, BSC9132:
	 * In High Capacity SD Cards (> 2 GBytes), the 32-bit source address and
	 * code length of these soc specify the memory address in block address
	 * format. Block length is fixed to 512 bytes as per the SD High
	 * Capacity specification.
	 */
	u64 tmp;

	if (mmc->high_capacity) {
		tmp = (u64)code_offset * blklen;
		tmp += code_len * blklen;
	} else
		tmp = code_offset + code_len;

	if ((tmp + CONFIG_ENV_SIZE > mmc->capacity) ||
			(tmp > 0xFFFFFFFFU))
		*env_addr = ESDHC_DEFAULT_ENVADDR;
	else
		*env_addr = tmp;

	free(tmp_buf);

	return 0;
#endif

	*env_addr = code_offset + code_len;

	free(tmp_buf);

	return 0;
}
