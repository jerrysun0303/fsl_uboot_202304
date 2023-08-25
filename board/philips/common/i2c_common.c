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

#if CONFIG_IS_ENABLED(DM_I2C)

/* If DM is in use, retrieve the chip for the specified bus number */
int fsl_i2c_get_device(int address, int bus, DEVICE_HANDLE_T *dev)
{
	int ret = i2c_get_chip_for_busnum(bus, address, 1, dev);

	if (ret)
		printf("I2C: Bus %d has no device with address 0x%02X\n",
		       bus, address);
	return ret;
}

#else

/* Handle is passed directly */
int fsl_i2c_get_device(int address, int bus, DEVICE_HANDLE_T *dev)
{
	*dev = address;
	return 0;
}

#endif
