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


#ifndef _MPC85xx_VIA_H
void mpc85xx_config_via(struct pci_controller *hose, pci_dev_t dev, struct pci_config_table *tab);

/* Function 1, IDE */
void mpc85xx_config_via_usbide(struct pci_controller *hose, pci_dev_t dev, struct pci_config_table *tab);

/* Function 2, USB ports 0-1 */
void mpc85xx_config_via_usb(struct pci_controller *hose, pci_dev_t dev, struct pci_config_table *tab);

/* Function 3, USB ports 2-3 */
void mpc85xx_config_via_usb2(struct pci_controller *hose, pci_dev_t dev, struct pci_config_table *tab);

/* Function 5, Power Management */
void mpc85xx_config_via_power(struct pci_controller *hose, pci_dev_t dev, struct pci_config_table *tab);

/* Function 6, AC97 Interface */
void mpc85xx_config_via_ac97(struct pci_controller *hose, pci_dev_t dev, struct pci_config_table *tab);
#endif /* _MPC85xx_VIA_H */
