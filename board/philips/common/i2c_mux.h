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

#ifndef __NXP_I2C_MUX_H__
#define __NXP_I2C_MUX_H__

#ifdef CONFIG_FSL_USE_PCA9547_MUX
int select_i2c_ch_pca9547(u8 ch, int bus);
int select_i2c_ch_pca9547_sec(u8 ch, int bus);
#endif

#endif
