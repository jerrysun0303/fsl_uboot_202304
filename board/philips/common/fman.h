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

#ifndef __FMAN_BOARD_HELPER__
#define __FMAN_BOARD_HELPER__

int fdt_set_phy_handle(void *fdt, char *compat, phys_addr_t addr,
			const char *alias);

enum srds_prtcl serdes_device_from_fm_port(enum fm_port port);

#endif
