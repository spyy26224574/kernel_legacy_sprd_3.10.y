/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _MACH_WATCHDOG_H_
#define _MACH_WATCHDOG_H_

void sprd_set_reboot_mode(const char *cmd);
void sprd_turnon_watchdog(unsigned int ms);
void sprd_turnoff_watchdog(void);
#endif