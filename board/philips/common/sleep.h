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


#ifndef __SLEEP_H
#define __SLEEP_H

#define DCFG_CCSR_CRSTSR_WDRFR	(1 << 3)
#define DDR_BUFF_LEN			128

/* determine if it is a wakeup from deep sleep */
bool is_warm_boot(void);

/* disable console output */
void fsl_dp_disable_console(void);

/* clean up everything and jump to kernel */
int fsl_dp_resume(void);
#endif
