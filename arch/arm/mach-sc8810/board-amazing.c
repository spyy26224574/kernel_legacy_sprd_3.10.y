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
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/delay.h>

#include <asm/io.h>
#include <asm/setup.h>
#include <asm/mach/time.h>
#include <asm/mach/arch.h>
#include <asm/mach-types.h>

#include <mach/hardware.h>
#include <linux/i2c.h>
#include <linux/i2c-gpio.h>
#include <linux/spi/spi.h>
#include <mach/globalregs.h>
#include <mach/board.h>
#include <mach/gpio-amazing.h>
#include "devices.h"
#include <linux/ktd253b_bl.h>
#include <mach/gpio.h>
#include <linux/spi/mxd_cmmb_026x.h>

extern void __init sc8810_reserve(void);
extern void __init sc8810_map_io(void);
extern void __init sc8810_init_irq(void);
extern void __init sc8810_timer_init(void);
extern void __init regulator_add_devices(void);
extern void __init sc8810_clock_init(void);
static struct platform_device rfkill_device;
static struct platform_device brcm_bluesleep_device;

static unsigned int sd_detect_gpio = GPIO_SDIO_DETECT;

/* Control ldo for maxscend cmmb chip according to HW design */
static struct regulator *cmmb_regulator_1v8 = NULL;

static struct platform_device  gpsctl_dev = {
	.name               = "gpsctl",
	/*.dev.platform_data  = &pdata_gpsctl,*/
};

static struct platform_device *devices[] __initdata = {
	&sprd_serial_device0,
	&sprd_serial_device1,
	&sprd_serial_device2,
	&sprd_device_rtc,
	&sprd_nand_device,
	&sprd_lcd_device0,
	&sprd_backlight_device,
	&sprd_i2c_device0,
	&sprd_i2c_device1,
	&sprd_i2c_device2,
	&sprd_spi0_device,
	&sprd_spi1_device,
	&sprd_keypad_device,
	&sprd_audio_soc_device,
	&sprd_audio_soc_vbc_device,
	&sprd_audio_vbc_device,
	&sprd_battery_device,
	&sprd_pmem_device,
	&sprd_pmem_adsp_device,
	&sprd_sdio1_device,
	&sprd_sdio0_device,
	&sprd_vsp_device,
	&sprd_dcam_device,
	&sprd_scale_device,
	&sprd_rotation_device,
	&rfkill_device,
	&brcm_bluesleep_device,
	&gpsctl_dev,
};

static struct resource bluesleep_resources[] = {
	{
		.name	= "gpio_host_wake",
		.start	= GPIO_BT2AP_WAKE,
		.end	= GPIO_BT2AP_WAKE,
		.flags	= IORESOURCE_IO,
	},
	{
		.name	= "gpio_ext_wake",
		.start	= GPIO_AP2BT_WAKE,
		.end	= GPIO_AP2BT_WAKE,
		.flags	= IORESOURCE_IO,
	},
};

static struct platform_device brcm_bluesleep_device = {
	.name = "bluesleep",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(bluesleep_resources),
	.resource	= bluesleep_resources,
};

static struct resource rfkill_resources[] = {
	{
		.name   = "bt_power",
		.start  = GPIO_BT_POWER,
		.end    = GPIO_BT_POWER,
		.flags  = IORESOURCE_IO,
	},
	{
		.name   = "bt_reset",
		.start  = GPIO_BT_RESET,
		.end    = GPIO_BT_RESET,
		.flags  = IORESOURCE_IO,
	},
};

static struct platform_device rfkill_device = {
	.name = "rfkill",
	.id = -1,
	.num_resources	= ARRAY_SIZE(rfkill_resources),
	.resource	= rfkill_resources,
};

static struct platform_ktd253b_backlight_data ktd253b_data = {
	.max_brightness = 255,
	.dft_brightness = 50,
	.ctrl_pin       = GPIO_BK,
};

static struct sys_timer sc8810_timer = {
	.init = sc8810_timer_init,
};

static int calibration_mode = false;
static int __init calibration_start(char *str)
{
	if(str)
		pr_info("modem calibartion:%s\n", str);
	calibration_mode = true;
	return 1;
}
__setup("calibration=", calibration_start);

int in_calibration(void)
{
	return (calibration_mode == true);
}

EXPORT_SYMBOL(in_calibration);

static void __init sprd_add_otg_device(void)
{
	/*
	 * if in calibrtaion mode, we do nothing, modem will handle everything
	 */
	if (calibration_mode)
		return;
	platform_device_register(&sprd_otg_device);
}

static struct i2c_gpio_platform_data pdata_gpio_i2c_p4 = {
	.sda_pin                = GPIO_I2C_SDA,             /*  SIMCLK3 */
	.sda_is_open_drain      = 0,
	.scl_pin                = GPIO_I2C_SCL,             /*  SIMCLK2*/
	.scl_is_open_drain      = 0,
	.udelay                 = 2,            /* ~100 kHz */
};

static struct platform_device  device_data_gpio_i2c_p4 = {
	.name               = "i2c-gpio",
	.id                 = 4,
	.dev.platform_data  = &pdata_gpio_i2c_p4,
};

static struct i2c_board_info i2c1_boardinfo[] = {
	{I2C_BOARD_INFO("sensor_main",0x3C),},
	{I2C_BOARD_INFO("sensor_sub",0x21),},
};

static struct i2c_board_info __initdata i2c_boardinfo_p4[] = {
	{I2C_BOARD_INFO("zinitix_isp", 0x50),},
	{I2C_BOARD_INFO("Zinitix_tsp", 0x20),},
};

static int sc8810_add_i2c_devices(void)
{
	platform_device_register(&device_data_gpio_i2c_p4);
	i2c_register_board_info(4, i2c_boardinfo_p4,ARRAY_SIZE(i2c_boardinfo_p4));
	i2c_register_board_info(1, i2c1_boardinfo, ARRAY_SIZE(i2c1_boardinfo));
	return 0;
}

struct platform_device audio_pa_amplifier_device = {
	.name = "speaker-pa",
	.id = -1,
};

static int audio_pa_amplifier_l(u32 cmd, void *data)
{
	int ret = 0;
	if (cmd < 0) {
		/* get speaker amplifier status : enabled or disabled */
		ret = 0;
	} else {
		/* set speaker amplifier */
	}
	return ret;
}

static void mxd_cmmb_poweron()
{
       gpio_direction_output(GPIO_CMMB_EN, 0);
       msleep(3);
       gpio_direction_output(GPIO_CMMB_EN, 1);
}
static void mxd_cmmb_poweroff()
{
       gpio_direction_output(GPIO_CMMB_EN, 0);
}
static int mxd_cmmb_init()
{
	int ret=0;
	ret = gpio_request(GPIO_CMMB_EN,   "MXD_CMMB_EN");
	if (ret)
	{
		pr_debug("mxd spi req gpio en err!\n");
		goto err_gpio_init;
	}
        gpio_direction_output(GPIO_CMMB_EN, 0);
	gpio_set_value(GPIO_CMMB_EN, 0);
	return 0;
err_gpio_init:
        gpio_free(GPIO_CMMB_EN);
	return ret;
}



static struct mxd_cmmb_026x_platform_data mxd_plat_data = {
	.poweron  = mxd_cmmb_poweron,
	.poweroff = mxd_cmmb_poweroff,
	.init     = mxd_cmmb_init,
};

static int spi_cs_gpio_map[][2] = {
    {SPI0_WIFI_CS_GPIO,  0},
    {SPI1_CMMB_CS_GPIO,  0},
} ;


static struct spi_board_info spi_boardinfo[] = {
	{
		.modalias = "wlan_spi",
		.bus_num = 0,
		.chip_select = 0,
		.max_speed_hz = 48 * 1000 * 1000,
		.mode = SPI_CPOL | SPI_CPHA,
	},
	{
		.modalias = "cmmb-dev",
		.bus_num = 1,
		.chip_select = 0,
		.max_speed_hz = 10 * 1000 * 1000,
		.mode = SPI_CPOL | SPI_CPHA,
		.platform_data = &mxd_plat_data,
	},
};


static void sprd_spi_init(void)
{
	int busnum, cs, gpio;
	int i;

	struct spi_board_info *info = spi_boardinfo;

	for (i = 0; i < ARRAY_SIZE(spi_boardinfo); i++) {
		busnum = info[i].bus_num;
		cs = info[i].chip_select;
		gpio   = spi_cs_gpio_map[busnum][cs];

		info[i].controller_data = (void *)gpio;
	}

        spi_register_board_info(info, ARRAY_SIZE(spi_boardinfo));
}

static int sc8810_add_misc_devices(void)
{
	if (0) {
		platform_set_drvdata(&audio_pa_amplifier_device, audio_pa_amplifier_l);
		if (platform_device_register(&audio_pa_amplifier_device))
			pr_err("faile to install audio_pa_amplifier_device\n");
	}
	return 0;
}

static void __init sc8810_init_machine(void)
{
	int clk;
	regulator_add_devices();
	sprd_add_otg_device();
	platform_device_add_data(&sprd_sdio0_device, &sd_detect_gpio, sizeof(sd_detect_gpio));
	platform_device_add_data(&sprd_backlight_device,&ktd253b_data,sizeof(ktd253b_data));
	clk=48000000;
	platform_device_add_data(&sprd_serial_device0,(const void*)&clk,sizeof(int));
	clk=26000000;
	platform_device_add_data(&sprd_serial_device1,(const void*)&clk,sizeof(int));
	platform_device_add_data(&sprd_serial_device2,(const void*)&clk,sizeof(int));
	platform_add_devices(devices, ARRAY_SIZE(devices));
	sc8810_add_i2c_devices();
	sc8810_add_misc_devices();
	sprd_spi_init();
}

static void __init sc8810_fixup(struct machine_desc *desc, struct tag *tag,
		char **cmdline, struct meminfo *mi)
{
}

static void __init sc8810_init_early(void)
{
	/* earlier init request than irq and timer */
	sc8810_clock_init();

}

MACHINE_START(SC8810OPENPHONE, "SP8810")
	.reserve	= sc8810_reserve,
	.map_io		= sc8810_map_io,
	.init_irq	= sc8810_init_irq,
	.timer		= &sc8810_timer,
	.init_machine	= sc8810_init_machine,
	.fixup		= sc8810_fixup,
	.init_early	= sc8810_init_early,
MACHINE_END