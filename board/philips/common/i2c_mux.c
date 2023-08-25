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
#include <i2c.h>
#include "i2c_common.h"
#include "i2c_mux.h"

/*
 * A new Kconfig option for something that used to always be built should be
 * “default y”.
 */
#ifdef CONFIG_FSL_USE_PCA9547_MUX

int select_i2c_ch_pca9547(u8 ch, int bus)
{
	int ret;
	DEVICE_HANDLE_T dev;

	/* Open device handle */
	ret = fsl_i2c_get_device(I2C_MUX_PCA_ADDR_PRI, bus, &dev);
	if (ret) {
		printf("PCA: No PCA9547 device found\n");
		return ret;
	}

	ret = I2C_WRITE(dev, 0, &ch, sizeof(ch));
	if (ret) {
		printf("PCA: Unable to select channel %d (%d)\n", (int)ch, ret);
		return ret;
	}

	return 0;
}

#ifdef I2C_MUX_PCA_ADDR_SEC
int select_i2c_ch_pca9547_sec(u8 ch, int bus)
{
	int ret;
	DEVICE_HANDLE_T dev;

	/* Open device handle */
	ret = fsl_i2c_get_device(I2C_MUX_PCA_ADDR_SEC, bus, &dev);
	if (ret) {
		printf("PCA: No PCA9547 device found\n");
		return ret;
	}

	ret = I2C_WRITE(dev, 0, &ch, sizeof(ch));
	if (ret) {
		printf("PCA: Unable to select channel %d (%d)\n", (int)ch, ret);
		return ret;
	}

	return 0;
}
#endif
#endif
