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

#ifndef __EMC2305_H_
#define __EMC2305_H_

#define I2C_EMC2305_CONF		0x20
#define I2C_EMC2305_FAN1		0x30
#define I2C_EMC2305_FAN2		0x40
#define I2C_EMC2305_FAN3		0x50
#define I2C_EMC2305_FAN4		0x60
#define I2C_EMC2305_FAN5		0x70

#define NUM_OF_FANS			5

void emc2305_init(int chip_addr);
void set_fan_speed(u8 data, int chip_addr);

#endif  /* __EMC2305_H_ */
