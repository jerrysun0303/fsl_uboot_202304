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

#ifndef __NXP_I2C_COMMON_H__
#define __NXP_I2C_COMMON_H__

/* Common functionality shared by the I2C drivers for VID and the mux. */
#if CONFIG_IS_ENABLED(DM_I2C)
#define DEVICE_HANDLE_T struct udevice *

#define I2C_READ(dev, register, data, length) \
	dm_i2c_read(dev, register, data, length)
#define I2C_WRITE(dev, register, data, length) \
	dm_i2c_write(dev, register, data, length)
#else
#define DEVICE_HANDLE_T int

#define I2C_READ(dev, register, data, length) \
	i2c_read(dev, register, 1, data, length)
#define I2C_WRITE(dev, register, data, length) \
	i2c_write(dev, register, 1, data, length)
#endif

int fsl_i2c_get_device(int address, int bus, DEVICE_HANDLE_T *dev);

#endif
