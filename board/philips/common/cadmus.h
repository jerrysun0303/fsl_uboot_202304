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

#ifndef __CADMUS_H_
#define __CADMUS_H_


/*
 * CADMUS Board System Register interface.
 */

/*
 * Returns board version register.
 */
extern unsigned int get_board_version(void);

/*
 * Returns either 33000000 or 66000000 as the SYS_CLK_FREQ.
 */
extern unsigned long get_board_sys_clk(void);


/*
 * Returns 1 - 4, as found in the USER CSR[6:7] bits.
 */
extern unsigned int get_pci_slot(void);


/*
 * Returns PCI DUAL as found in CM_PCI[3].
 */
extern unsigned int get_pci_dual(void);


#endif	/* __CADMUS_H_ */
