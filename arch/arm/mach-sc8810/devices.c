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

#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <mach/hardware.h>
#include <mach/irqs.h>
#include "devices.h"

/* example platform device & its resource */
static struct resource resources_example[] = {
	[0] = {
		.start	= IRQ_SOFT_TRIG_INT,
		.end	= IRQ_SOFT_TRIG_INT,
		.flags	= IORESOURCE_IRQ,
	},
	[1] = {
		.start	= SPRD_BUSM1_BASE,
		.end	= SPRD_BUSM1_BASE + SPRD_BUSM1_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
};

struct platform_device sprd_device_example = {
	.name		= "sprd_example",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(resources_example),
	.resource	= resources_example,
};

static struct resource sprd_serial_resources1[] = {
	[0] = {
		.start = SPRD_SERIAL0_BASE,
		.end = SPRD_SERIAL0_BASE + SPRD_SERIAL0_SIZE-1,
		.name = "serial_res",
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_SER0_INT,
		.end = IRQ_SER0_INT,
		.flags = IORESOURCE_IRQ,
	},
};
struct platform_device sprd_serial_device1 = {
	.name           = "serial_sprd",
	.id             =  0,
	.num_resources  = ARRAY_SIZE(sprd_serial_resources1),
	.resource       = sprd_serial_resources1,
};

static struct resource sprd_serial_resources2[] = {
	[0] = {
		.start = SPRD_SERIAL1_BASE,
		.end = SPRD_SERIAL1_BASE + SPRD_SERIAL1_SIZE-1,
		.name = "serial_res",
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_SER1_INT,
		.end = IRQ_SER1_INT,
		.flags = IORESOURCE_IRQ,
	},
};
struct platform_device sprd_serial_device2 = {
	.name           = "serial_sprd",
	.id             =  1,
	.num_resources  = ARRAY_SIZE(sprd_serial_resources2),
	.resource       = sprd_serial_resources2,
};

static struct resource sprd_serial_resources3[] = {
	[0] = {
		.start = SPRD_SERIAL2_BASE,
		.end = SPRD_SERIAL2_BASE + SPRD_SERIAL2_SIZE-1,
		.name = "serial_res",
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_SER2_INT,
		.end = IRQ_SER2_INT,
		.flags = IORESOURCE_IRQ,
	}
};
struct platform_device sprd_serial_device3 = {
	.name           = "serial_sprd",
	.id             =  2,
	.num_resources  = ARRAY_SIZE(sprd_serial_resources3),
	.resource       = sprd_serial_resources3,
};