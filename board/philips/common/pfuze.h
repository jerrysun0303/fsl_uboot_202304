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


#ifndef __PFUZE_BOARD_HELPER__
#define __PFUZE_BOARD_HELPER__

#ifdef CONFIG_DM_PMIC_PFUZE100
struct udevice *pfuze_common_init(void);
int pfuze_mode_init(struct udevice *dev, u32 mode);
#else
struct pmic *pfuze_common_init(unsigned char i2cbus);
int pfuze_mode_init(struct pmic *p, u32 mode);
#endif

#endif
