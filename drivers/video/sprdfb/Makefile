
obj-$(CONFIG_FB_SC8825) := sprdfb_main.o sprdfb_panel.o sprdfb_dispc.o sprdfb_lcdc.o sprdfb_mcu.o sprdfb_rgb.o sprdfb_mipi.o sprdfb_i2c.o sprdfb_spi.o sprdfb_dsi.o sprdfb_chip_common.o sprdfb_chip_8825.o
obj-$(CONFIG_FB_SC8825) += dsi_1_10a/
obj-$(CONFIG_FB_SC8825) += spi/
obj-$(CONFIG_FB_SC8825) += lcd/

obj-$(CONFIG_FB_SCX35) := sprdfb_main.o sprdfb_panel.o sprdfb_dispc.o sprdfb_mcu.o sprdfb_rgb.o sprdfb_mipi.o sprdfb_i2c.o sprdfb_spi.o sprdfb_dsi.o  sprdfb_chip_common.o sprdfb_chip_8830.o
obj-$(CONFIG_FB_SCX35) += dsi_1_10a/
obj-$(CONFIG_FB_SCX35) += spi/
obj-$(CONFIG_FB_SCX35) += lcd/

obj-$(CONFIG_FB_SCX30G) := sprdfb_main.o sprdfb_panel.o sprdfb_dispc.o sprdfb_mcu.o sprdfb_rgb.o sprdfb_mipi.o sprdfb_i2c.o sprdfb_spi.o sprdfb_dsi.o  sprdfb_chip_common.o sprdfb_chip_8830.o
obj-$(CONFIG_FB_SCX30G) += dsi_1_21a/
obj-$(CONFIG_FB_SCX30G) += spi/
obj-$(CONFIG_FB_SCX30G) += lcd/
obj-$(CONFIG_FB_SCX15) := sprdfb_main.o sprdfb_panel.o sprdfb_dispc.o sprdfb_mcu.o sprdfb_rgb.o sprdfb_i2c.o sprdfb_spi.o sprdfb_chip_common.o sprdfb_chip_7715.o
obj-$(CONFIG_FB_SCX15) += spi/
obj-$(CONFIG_FB_SCX15) += lcd/

# ========== SharkL configuration begin ===========
ifeq ($(CONFIG_FB_SCX35L), y)
obj-y := sprdfb_main.o sprdfb_panel.o sprdfb_dispc.o
obj-y += sprdfb_dsi.o sprdfb_mipi.o
obj-y += sprdfb_mcu.o sprdfb_rgb.o sprdfb_spi.o sprdfb_i2c.o
obj-y += sprdfb_chip_common.o sprdfb_chip_9630.o
endif
ifeq ($(CONFIG_MACH_SPX35LFPGA), y)
obj-$(CONFIG_FB_SCX35L) += spi_gpio_drv.o
endif
ifeq ($(CONFIG_MACH_PIKELFPGA), y)
obj-$(CONFIG_FB_SCX35L) += spi_gpio_drv.o
endif
obj-$(CONFIG_FB_SCX35L) += dsi_1_21a/
obj-$(CONFIG_FB_SCX35L) += spi/
obj-$(CONFIG_FB_SCX35L) += lcd/
# ========== SharkL configuration end ============

# This file is used for creating file node
obj-y += sprdfb_attr.o
