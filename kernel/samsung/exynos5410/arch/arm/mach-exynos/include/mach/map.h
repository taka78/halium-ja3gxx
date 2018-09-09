/* linux/arch/arm/mach-exynos/include/mach/map.h
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * EXYNOS4 - Memory map definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_MAP_H
#define __ASM_ARCH_MAP_H __FILE__

#include <plat/map-base.h>

/*
 * EXYNOS4 UART offset is 0x10000 but the older S5P SoCs are 0x400.
 * So need to define it, and here is to avoid redefinition warning.
 */
#define S3C_UART_OFFSET			(0x10000)

#include <plat/map-s5p.h>

#define EXYNOS4_PA_SYSRAM0		0x02025000
#define EXYNOS4_PA_SYSRAM1		0x02020000
#define EXYNOS4_PA_SYSRAM_NS		0x0203F000
#define EXYNOS4_PA_SYSRAM_NS_4X12	0x0204F000
#define EXYNOS5_PA_SYSRAM		0x02020000
#define EXYNOS5250_PA_SYSRAM_NS		0x0204F000
#define EXYNOS5410_PA_SYSRAM_NS		0x02073000

#define EXYNOS4_PA_FIMC0		0x11800000
#define EXYNOS4_PA_FIMC1		0x11810000
#define EXYNOS4_PA_FIMC2		0x11820000
#define EXYNOS4_PA_FIMC3		0x11830000
#define EXYNOS4_PA_JPEG			0x11840000
#define EXYNOS5_PA_JPEG			0x11E00000
#define EXYNOS5_PA_JPEG_HX		0x11F50000
#define EXYNOS4_PA_JPEG			0x11840000

#define EXYNOS4_PA_G2D			0x12800000

#define EXYNOS_PA_AUDSS_INTMEM		0x03000000
#define EXYNOS_PA_AUDSS_COMMBOX 	0x03820000
#define EXYNOS_PA_AUDSS 		0x03810000
#define EXYNOS4_PA_I2S0			0x03830000
#define EXYNOS4_PA_I2S1			0xE3100000
#define EXYNOS4_PA_I2S2			0xE2A00000
#define EXYNOS5_PA_I2S0			0x03830000
#define EXYNOS5_PA_I2S1			0x12D60000
#define EXYNOS5_PA_I2S2			0x12D70000

#define EXYNOS4_PA_PCM0			0x03840000
#define EXYNOS4_PA_PCM1			0x13980000
#define EXYNOS4_PA_PCM2			0x13990000
#define EXYNOS5_PA_PCM0			0x03840000
#define EXYNOS5_PA_PCM1			0x12D80000
#define EXYNOS5_PA_PCM2			0x12D90000

#define EXYNOS4_PA_SROM_BANK(x)		(0x04000000 + ((x) * 0x01000000))

#define EXYNOS4_PA_ONENAND		0x0C000000
#define EXYNOS4_PA_ONENAND_DMA		0x0C600000

#define EXYNOS_PA_CHIPID		0x10000000

#define EXYNOS4_PA_SYSCON		0x10010000
#define EXYNOS5_PA_SYSCON		0x10050100

#define EXYNOS5_PA_TMU			0x10060000
#define EXYNOS5_PA_ACE			0x10830000
#define EXYNOS4_PA_PMU			0x10020000
#define EXYNOS5_PA_PMU			0x10040000

#define EXYNOS4_PA_CMU			0x10030000
#define EXYNOS5_PA_CMU			0x10010000

#define EXYNOS4_PA_SYSTIMER		0x10050000
#define EXYNOS5_PA_SYSTIMER		0x101C0000

#define EXYNOS4_PA_WATCHDOG		0x10060000
#define EXYNOS5_PA_WATCHDOG		0x101D0000

#define EXYNOS5410_PA_TMU1		0x10064000
#define EXYNOS5410_PA_TMU2		0x10068000
#define EXYNOS5410_PA_TMU3		0x1006C000

#define EXYNOS4_PA_RTC			0x10070000
#define EXYNOS5_PA_RTC			0x101E0000

#define EXYNOS4_PA_KEYPAD		0x100A0000

#define EXYNOS4_PA_DMC0			0x10400000
#define EXYNOS4_PA_DMC1			0x10410000

#define EXYNOS4_PA_COMBINER		0x10440000
#define EXYNOS5_PA_COMBINER		0x10440000

#define EXYNOS4_PA_GIC_CPU		0x10480000
#define EXYNOS4_PA_GIC_DIST		0x10490000
#define EXYNOS5_PA_GIC_CPU		0x10482000
#define EXYNOS5_PA_GIC_DIST		0x10481000

#define EXYNOS4_PA_COREPERI		0x10500000
#define EXYNOS4_PA_TWD			0x10500600
#define EXYNOS4_PA_L2CC			0x10502000

#define EXYNOS4_PA_DMC0_4X12		0x10600000
#define EXYNOS4_PA_DMC1_4X12		0x10610000
#define EXYNOS5_PA_C2C			0x10E00000

#define EXYNOS5_PA_C2C_CP		0x10E40000
#define EXYNOS5_PA_C2C_EXT		0x10D00000

#define EXYNOS4_PA_S_MDMA0		0x10800000
#define EXYNOS4_PA_NS_MDMA0		0x10810000
#define EXYNOS4_PA_S_MDMA1		0x12840000
#define EXYNOS4_PA_NS_MDMA1		0x12850000
#define EXYNOS4_PA_PDMA0		0x12680000
#define EXYNOS4_PA_PDMA1		0x12690000
#define EXYNOS5_PA_MDMA0		0x10800000
#define EXYNOS5_PA_MDMA1		0x11C10000
#define EXYNOS5_PA_PDMA0		0x121A0000
#define EXYNOS5_PA_PDMA1		0x121B0000

#define EXYNOS4_PA_FIMC_IS		0x12000000
#define EXYNOS4_PA_MDMA0		EXYNOS4_PA_NS_MDMA0
#define EXYNOS4_PA_MDMA1		EXYNOS4_PA_NS_MDMA1

#define EXYNOS4_PA_GPS			0x12700000

#define EXYNOS4_PA_SYSMMU_G2D_ACP	0x10A40000
#define EXYNOS4_PA_SYSMMU_SSS		0x10A50000
#define EXYNOS4_PA_SYSMMU_FIMC0		0x11A20000
#define EXYNOS4_PA_SYSMMU_FIMC1		0x11A30000
#define EXYNOS4_PA_SYSMMU_FIMC2		0x11A40000
#define EXYNOS4_PA_SYSMMU_FIMC3		0x11A50000
#define EXYNOS4_PA_SYSMMU_JPEG		0x11A60000
#define EXYNOS4_PA_SYSMMU_FIMD0		0x11E20000
#define EXYNOS4_PA_SYSMMU_FIMD1		0x12220000
#define EXYNOS4_PA_SYSMMU_ISP		0x12260000
#define EXYNOS4_PA_SYSMMU_DRC		0x12270000
#define EXYNOS4_PA_SYSMMU_FD		0x122A0000
#define EXYNOS4_PA_SYSMMU_ISPCPU	0x122B0000
#define EXYNOS4_PA_SYSMMU_FIMC_LITE0	0x123B0000
#define EXYNOS4_PA_SYSMMU_FIMC_LITE1	0x123C0000
#define EXYNOS4_PA_SYSMMU_PCIe		0x12620000
#define EXYNOS4_PA_SYSMMU_G2D		0x12A20000
#define EXYNOS4_PA_SYSMMU_ROTATOR	0x12A30000
#define EXYNOS4_PA_SYSMMU_MDMA2		0x12A40000
#define EXYNOS4_PA_SYSMMU_TV		0x12E20000
#define EXYNOS4_PA_SYSMMU_MFC_L		0x13620000
#define EXYNOS4_PA_SYSMMU_MFC_R		0x13630000
#define EXYNOS4_PA_SPI0			0x13920000
#define EXYNOS4_PA_SPI1			0x13930000
#define EXYNOS4_PA_SPI2			0x13940000
#define EXYNOS5_PA_SPI0			0x12D20000
#define EXYNOS5_PA_SPI1			0x12D30000
#define EXYNOS5_PA_SPI2			0x12D40000
#define EXYNOS5_PA_SPI3			0x131A0000

#define EXYNOS5_PA_LPI			0x10040004
#define EXYNOS5_PA_CORE_MISC		0x10CE0000
#define EXYNOS5_PA_CCI			0x10D20000

#define EXYNOS5_PA_SYSMMU_MDMA1		0x10A40000
#define EXYNOS5_PA_SYSMMU_SSS		0x10A50000
#define EXYNOS5_PA_SYSMMU_2D		0x10A60000
#define EXYNOS5_PA_SYSMMU_MFC_R		0x11200000
#define EXYNOS5_PA_SYSMMU_MFC_L		0x11210000
#define EXYNOS5_PA_SYSMMU_ROTATOR	0x11D40000
#define EXYNOS5_PA_SYSMMU_MDMA2		0x11D50000
#define EXYNOS5_PA_SYSMMU_JPEG		0x11F20000
#define EXYNOS5_PA_SS_UDC		0x1200C100
#define EXYNOS5_PA_SS_DRD		0x12000000
#define EXYNOS5_PA_SS_PHY		0x12100000
#define EXYNOS5_PA_SYSMMU_IOP		0x12360000
#define EXYNOS5_PA_SYSMMU_RTIC		0x12370000
#define EXYNOS5_PA_SYSMMU_ISP		0x13260000
#define EXYNOS5_PA_SYSMMU_DRC		0x13270000
#define EXYNOS5_PA_SYSMMU_SCALERC	0x13280000
#define EXYNOS5_PA_SYSMMU_SCALERP	0x13290000
#define EXYNOS5_PA_SYSMMU_FD		0x132A0000
#define EXYNOS5_PA_SYSMMU_ISPCPU	0x132B0000
#define EXYNOS5_PA_SYSMMU_ODC		0x132C0000
#define EXYNOS5_PA_SYSMMU_DIS0		0x132D0000
#define EXYNOS5_PA_SYSMMU_DIS1		0x132E0000
#define EXYNOS5_PA_SYSMMU_3DNR		0x132F0000
#define EXYNOS5_PA_SYSMMU_LITE0		0x13C40000
#define EXYNOS5_PA_SYSMMU_LITE1		0x13C50000
#define EXYNOS5_PA_SYSMMU_LITE2		0x13CA0000
#define EXYNOS5_PA_SYSMMU_GSC0		0x13E80000
#define EXYNOS5_PA_SYSMMU_GSC1		0x13E90000
#define EXYNOS5_PA_SYSMMU_GSC2		0x13EA0000
#define EXYNOS5_PA_SYSMMU_GSC3		0x13EB0000
#define EXYNOS5_PA_SYSMMU_FIMD1		0x14640000
#define EXYNOS5_PA_SYSMMU_TV		0x14650000

/* Exynos5 variation */
#define EXYNOS5_PA_SYSMMU_MJPEG		0x11F10000
#define EXYNOS5_PA_SYSMMU_FIMD0		0x13A20000
#define EXYNOS5_PA_SYSMMU_S3D		0x13CB0000
#define EXYNOS5_PA_SYSMMU_3AA		0x13CC0000
#define EXYNOS5_PA_SYSMMU_LITE2A	0x13D20000
#define EXYNOS5_PA_SYSMMU_SCALER	0x13F10000
#define EXYNOS5_PA_SYSMMU_GSC1A		0x13F30000

#define EXYNOS4_PA_GPIO1		0x11400000
#define EXYNOS4_PA_GPIO2		0x11000000
#define EXYNOS4_PA_GPIO3		0x03860000
#define EXYNOS4_PA_GPIO4		0x106e0000
#define EXYNOS5_PA_GPIO1		0x11400000
#define EXYNOS5_PA_GPIO2		0x13400000
#define EXYNOS5_PA_GPIO3		0x10D10000
#define EXYNOS5_PA_GPIO4		0x03860000

#define EXYNOS4_PA_PPMU_DMC0		0x106A0000
#define EXYNOS4_PA_PPMU_DMC1		0x106B0000
#define EXYNOS4_PA_PPMU_CPU		0x106C0000
#define EXYNOS5_PA_PPMU_DDR_C		0x10C40000
#define EXYNOS5_PA_PPMU_DDR_R1		0x10C50000
#define EXYNOS5_PA_PPMU_CPU		0x10C60000
#define EXYNOS5_PA_PPMU_DDR_L		0x10CB0000
#define EXYNOS5_PA_PPMU_RIGHT		0x13660000

#define EXYNOS5_PA_DREXII		0x10DD0000

#define EXYNOS4_PA_G3D			0x13000000
#define EXYNOS5_PA_G3D			0x11800000

#define EXYNOS5410_PA_GPIO_LB		0x14000000
#define EXYNOS5410_PA_GPIO_RT		0x13400000
#define EXYNOS5410_PA_GPIO_C2C		0x10D10000
#define EXYNOS5410_PA_GPIO_AUDIO	0x03860000

#define EXYNOS4_PA_MIPI_CSIS0		0x11880000
#define EXYNOS4_PA_MIPI_CSIS1		0x11890000

#define EXYNOS4_PA_FIMD0		0x11C00000
#define EXYNOS5_PA_FIMD1		0x14400000
#ifdef CONFIG_SOC_EXYNOS5410
#define EXYNOS5_PA_DSIM0		0x13900000
#define EXYNOS5_PA_DSIM1		0x14500000
#else
#define EXYNOS5_PA_DSIM0		0x14500000
#endif
#define EXYNOS5_PA_DP			0x145B0000

#define EXYNOS5_PA_FIMG2D		0x10850000
#define EXYNOS5_PA_USB3_DRD0		0x12000000
#define EXYNOS5_PA_USB3_DRD0_PHY	0x12100000
#define EXYNOS5_PA_USB3_DRD1		0x12400000
#define EXYNOS5_PA_USB3_DRD1_PHY	0x12500000

#define EXYNOS4_PA_HSMMC(x)		(0x12510000 + ((x) * 0x10000))
#define EXYNOS5_PA_HSMMC(x)		(0x12200000 + ((x) * 0x10000))
#define EXYNOS4_PA_DWMCI		0x12550000

#define EXYNOS4_PA_SATA			0x12560000
#define EXYNOS4_PA_SATAPHY		0x125D0000
#define EXYNOS4_PA_SATAPHY_CTRL		0x126B0000

#define EXYNOS4_PA_SROMC		0x12570000
#define EXYNOS5_PA_SROMC		0x12250000

#define EXYNOS4_PA_EHCI			0x12580000
#define EXYNOS4_PA_OHCI			0x12590000
#define EXYNOS4_PA_HSPHY		0x125B0000
#define EXYNOS4_PA_USB_HSOTG		0x12480000
#define EXYNOS5_PA_EHCI			0x12110000
#define EXYNOS5_PA_OHCI			0x12120000
#define EXYNOS5_PA_HSPHY		0x12130000
#define EXYNOS5_PA_USB_HSOTG		0x12140000

#define EXYNOS4_PA_FIMC_LITE0		0x12390000
#define EXYNOS4_PA_FIMC_LITE1		0x123A0000
#define EXYNOS4_PA_MFC			0x13400000
#define EXYNOS5_PA_MFC			0x11000000

#define EXYNOS4_PA_UART			0x13800000
#define EXYNOS5_PA_UART			0x12C00000

#define EXYNOS4_PA_VP			0x12C00000
#define EXYNOS4_PA_MIXER		0x12C10000
#define EXYNOS4_PA_SDO			0x12C20000
#define EXYNOS4_PA_HDMI			0x12D00000
#define EXYNOS4_PA_HDMI_CEC		0x100B0000
#define EXYNOS4_PA_IIC_HDMIPHY		0x138E0000

#define EXYNOS5_PA_MIXER		0x14450000
#define EXYNOS5_PA_HDMI			0x14530000
#define EXYNOS5_PA_HDMIPHY		0x145D0000
#define EXYNOS5_PA_HDMI_CEC		0x101B0000
#define EXYNOS5_PA_IIC_HDMIPHY		0x12CE0000

#define EXYNOS5_PA_FIMC_IS		0x13000000

#define EXYNOS5_PA_FIMC_LITE0		0x13C00000
#define EXYNOS5_PA_FIMC_LITE1		0x13C10000
#ifdef CONFIG_SOC_EXYNOS5250
#define EXYNOS5_PA_FIMC_LITE2		0x13C90000
#else
#define EXYNOS5_PA_FIMC_LITE2		0x13D00000
#endif

#define EXYNOS5_PA_MIPI_CSIS0		0x13C20000
#define EXYNOS5_PA_MIPI_CSIS1		0x13C30000
#define EXYNOS5_PA_MIPI_CSIS2		0x13D10000

#define EXYNOS5_PA_GSC0 		0x13E00000
#define EXYNOS5_PA_GSC1 		0x13E10000
#define EXYNOS5_PA_GSC2 		0x13E20000
#define EXYNOS5_PA_GSC3 		0x13E30000
#define EXYNOS5_PA_SCALER		0x13F00000

#define EXYNOS5_PA_ROTATOR		0x11C00000

#define EXYNOS4_PA_IIC(x)		(0x13860000 + ((x) * 0x10000))
#define EXYNOS5_PA_IIC(x)		(0x12C60000 + ((x) * 0x10000))

#define EXYNOS5250_PA_HSIIC0		0x12C50000
#define EXYNOS5250_PA_HSIIC1		0x12D00000
#define EXYNOS5250_PA_HSIIC2		0x12D50000
#define EXYNOS5250_PA_HSIIC3		0x12DE0000

#define EXYNOS5410_PA_HSIIC(x)		(0x12CA0000 + ((x) * 0x10000))

#define EXYNOS4_PA_ADC			0x13910000
#define EXYNOS4_PA_ADC1			0x13911000
#define EXYNOS4X12_PA_ADC		0x126C0000
#define EXYNOS5_PA_ADC			0x12D10000

#define EXYNOS4_PA_AC97			0x139A0000

#define EXYNOS4_PA_SPDIF		0x139B0000
#define EXYNOS5_PA_SPDIF		0x12DB0000

#define EXYNOS4_PA_TIMER		0x139D0000
#define EXYNOS5_PA_TIMER		0x12DD0000

#define EXYNOS4_PA_SDRAM		0x40000000
#define EXYNOS5_PA_SDRAM		0x40000000

#define EXYNOS5_PA_BTS_FBM_DDR_R1	0x10C30000
#define EXYNOS5_PA_BTS_CPU		0x10C80000
#define EXYNOS5_PA_BTS_G3D_ACP		0x10EA0000
#define EXYNOS5_PA_BTS_MFC0		0x11220000
#define EXYNOS5_PA_BTS_MFC1		0x11230000
#define EXYNOS5_PA_BTS_ROTATOR		0x11D60000
#define EXYNOS5_PA_BTS_MDMA1		0x11D70000
#define EXYNOS5_PA_BTS_JPEG		0x11F40000
#define EXYNOS5_PA_BTS_GSCL0		0x13EC0000
#define EXYNOS5_PA_BTS_GSCL1		0x13ED0000
#define EXYNOS5_PA_BTS_GSCL2		0x13EE0000
#define EXYNOS5_PA_BTS_GSCL3		0x13EF0000
#define EXYNOS5_PA_BTS_GSCL4		0x13F20000
#define EXYNOS5_PA_BTS_DISP10		0x14660000
#define EXYNOS5_PA_BTS_DISP11		0x14670000
#define EXYNOS5_PA_BTS_MIXER0		0x14690000
#define EXYNOS5_PA_BTS_MIXER1		0x146A0000
#define EXYNOS5_PA_BTS_C2C		0x10c90000
#define EXYNOS5_PA_BTS_FIMC_ISP		0x13300000
#define EXYNOS5_PA_BTS_FIMC_DRC		0x13310000
#define EXYNOS5_PA_BTS_FIMC_SCALER_C	0x13320000
#define EXYNOS5_PA_BTS_FIMC_SCALER_P	0x13330000
#define EXYNOS5_PA_BTS_FIMC_FD		0x13340000
#define EXYNOS5_PA_BTS_FIMC_ODC		0x13370000
#define EXYNOS5_PA_BTS_FIMC_DIS0	0x13380000
#define EXYNOS5_PA_BTS_FIMC_DIS1	0x13390000
#define EXYNOS5_PA_BTS_FIMC_3DNR	0x133A0000

#define EXYNOS5_PA_BTS_EAGLE		0x10C80000
#define EXYNOS5_PA_BTS_KFC		0x10C90000
#define EXYNOS5_PA_BTS_G3D0		0x11A00000
#define EXYNOS5_PA_BTS_G3D1		0x11A20000
#define EXYNOS5_PA_BTS_FIMD1M0		0x14660000
#define EXYNOS5_PA_BTS_FIMD1M1		0x14670000
#define EXYNOS5_PA_BTS_FIMD1M2		0x14680000
#define EXYNOS5_PA_BTS_G2D		0x10AA0000
#define EXYNOS5_PA_BTS_FIMCLITE0	0x13C60000
#define EXYNOS5_PA_BTS_FIMCLITE1	0x13C70000
#define EXYNOS5_PA_BTS_FIMCLITE2	0x13D30000

/* DREX PA Defines */
#define EXYNOS5_PA_DREXI_1		0x10C30000
#define EXYNOS5_PA_DREXI_0		0x10C20000

/* NOCP BASE ADDRESS*/
#define EXYNOS5410_NOCP_MFC0_BASE	0x12AA1000
#define EXYNOS5410_NOCP_MFC1_BASE	0x12AA1400
#define EXYNOS5410_NOCP_GSC23_BASE	0x14261000
#define EXYNOS5410_NOCP_S3D0_BASE	0x14261400
#define EXYNOS5410_NOCP_S3D1_BASE	0x14261800
#define EXYNOS5410_NOCP_ISP0_BASE	0x13471000
#define EXYNOS5410_NOCP_ISP1_BASE	0x13471400
#define EXYNOS5410_NOCP_TRP_EAGLE_BASE	0x10CB0000
#define EXYNOS5410_NOCP_TRP_KFC_BASE	0x10CB0800
#define EXYNOS5410_NOCP_TRP_CCI_BASE	0x10CB1000
#define EXYNOS5410_NOCP_TRP_G2D_BASE	0x10CB1800
#define EXYNOS5410_NOCP_G3D0_BASE	0x116D1000
#define EXYNOS5410_NOCP_G3D1_BASE	0x116D1400
#define EXYNOS5410_NOCP_GEN_BASE	0x13671000
#define EXYNOS5410_NOCP_FSYS_BASE	0x13671400
#define EXYNOS5410_NOCP_MEM0_0_BASE	0x10CA1000
#define EXYNOS5410_NOCP_MEM0_1_BASE	0x10CA1400
#define EXYNOS5410_NOCP_MEM1_0_BASE	0x10CA1C00
#define EXYNOS5410_NOCP_MEM1_1_BASE	0x10CA2000
#define EXYNOS5410_NOCP_CCI_BASE	0x10CA2800
#define EXYNOS5410_NOCP_C2C_BASE	0x10CA3000
#define EXYNOS5410_NOCP_GSC0_BASE	0x14061000
#define EXYNOS5410_NOCP_GSC1_BASE	0x14061400
#define EXYNOS5410_NOCP_DISP0_BASE	0x114D1000
#define EXYNOS5410_NOCP_DISP1_BASE	0x114D1400

#define NOCP_BASE(_name)		EXYNOS5410_NOCP_##_name##_BASE

/* Compatibiltiy Defines */

#if defined(CONFIG_ARCH_EXYNOS4)
#define S3C_PA_HSMMC0			EXYNOS4_PA_HSMMC(0)
#define S3C_PA_HSMMC1			EXYNOS4_PA_HSMMC(1)
#define S3C_PA_HSMMC2			EXYNOS4_PA_HSMMC(2)
#define S3C_PA_HSMMC3			EXYNOS4_PA_HSMMC(3)
#elif defined(CONFIG_ARCH_EXYNOS5)
#define S3C_PA_HSMMC0			EXYNOS5_PA_HSMMC(0)
#define S3C_PA_HSMMC1			EXYNOS5_PA_HSMMC(1)
#define S3C_PA_HSMMC2			EXYNOS5_PA_HSMMC(2)
#define S3C_PA_HSMMC3			EXYNOS5_PA_HSMMC(3)
#endif

#if defined(CONFIG_ARCH_EXYNOS4)
#define S3C_PA_IIC			EXYNOS4_PA_IIC(0)
#define S3C_PA_IIC1			EXYNOS4_PA_IIC(1)
#define S3C_PA_IIC2			EXYNOS4_PA_IIC(2)
#define S3C_PA_IIC3			EXYNOS4_PA_IIC(3)
#define S3C_PA_IIC4			EXYNOS4_PA_IIC(4)
#define S3C_PA_IIC5			EXYNOS4_PA_IIC(5)
#define S3C_PA_IIC6			EXYNOS4_PA_IIC(6)
#define S3C_PA_IIC7			EXYNOS4_PA_IIC(7)
#endif

#if defined(CONFIG_ARCH_EXYNOS5)
#define S3C_PA_IIC			EXYNOS5_PA_IIC(0)
#define S3C_PA_IIC1			EXYNOS5_PA_IIC(1)
#define S3C_PA_IIC2			EXYNOS5_PA_IIC(2)
#define S3C_PA_IIC3			EXYNOS5_PA_IIC(3)
#define S3C_PA_IIC4			EXYNOS5_PA_IIC(4)
#define S3C_PA_IIC5			EXYNOS5_PA_IIC(5)
#define S3C_PA_IIC6			EXYNOS5_PA_IIC(6)
#define S3C_PA_IIC7			EXYNOS5_PA_IIC(7)
#endif

#if defined(CONFIG_ARCH_EXYNOS4)
#define S3C_PA_RTC			EXYNOS4_PA_RTC
#define S3C_PA_WDT			EXYNOS4_PA_WATCHDOG
#define S3C_PA_SPI0			EXYNOS4_PA_SPI0
#define S3C_PA_SPI1			EXYNOS4_PA_SPI1
#define S3C_PA_SPI2			EXYNOS4_PA_SPI2
#elif defined(CONFIG_ARCH_EXYNOS5)
#define S3C_PA_RTC			EXYNOS5_PA_RTC
#define S3C_PA_WDT			EXYNOS5_PA_WATCHDOG
#define S3C_PA_SPI0			EXYNOS5_PA_SPI0
#define S3C_PA_SPI1			EXYNOS5_PA_SPI1
#define S3C_PA_SPI2			EXYNOS5_PA_SPI2
#define S3C_PA_SPI3			EXYNOS5_PA_SPI3
#endif

#define S5P_PA_TIMER			EXYNOS5_PA_TIMER

#ifdef CONFIG_ARCH_EXYNOS4
#define S3C_PA_USB_HSOTG		EXYNOS4_PA_USB_HSOTG
#elif defined(CONFIG_ARCH_EXYNOS5)
#define S3C_PA_USB_HSOTG		EXYNOS5_PA_USB_HSOTG
#endif

#if defined(CONFIG_ARCH_EXYNOS4)
#define S5P_PA_EHCI			EXYNOS4_PA_EHCI
#elif defined(CONFIG_ARCH_EXYNOS5)
#define S5P_PA_EHCI			EXYNOS5_PA_EHCI
#endif
#define S5P_PA_FIMC0			EXYNOS4_PA_FIMC0
#define S5P_PA_FIMC1			EXYNOS4_PA_FIMC1
#define S5P_PA_FIMC2			EXYNOS4_PA_FIMC2
#define S5P_PA_FIMC3			EXYNOS4_PA_FIMC3
#ifdef CONFIG_ARCH_EXYNOS4
#define S5P_PA_JPEG			EXYNOS4_PA_JPEG
#else
#define S5P_PA_JPEG			EXYNOS5_PA_JPEG
#define S5P_PA_JPEG_HX			EXYNOS5_PA_JPEG_HX
#endif
#define S5P_PA_G2D			EXYNOS4_PA_G2D
#define S5P_PA_FIMD0			EXYNOS4_PA_FIMD0
#define S5P_PA_FIMD1			EXYNOS5_PA_FIMD1
#define S5P_PA_DSIM0			EXYNOS5_PA_DSIM0
#define S5P_PA_DSIM1			EXYNOS5_PA_DSIM1
#define S5P_PA_DP			EXYNOS5_PA_DP
#define S5P_PA_FIMG2D			EXYNOS5_PA_FIMG2D

#if defined(CONFIG_ARCH_EXYNOS4)
#define S5P_PA_MFC			EXYNOS4_PA_MFC
#define S5P_PA_MIPI_CSIS0		EXYNOS4_PA_MIPI_CSIS0
#define S5P_PA_MIPI_CSIS1		EXYNOS4_PA_MIPI_CSIS1
#define S5P_PA_FIMC_LITE0		EXYNOS4_PA_FIMC_LITE0
#define S5P_PA_FIMC_LITE1		EXYNOS4_PA_FIMC_LITE1
#define S5P_PA_SDO			EXYNOS4_PA_SDO
#define S5P_PA_MIXER			EXYNOS4_PA_MIXER
#define S5P_PA_VP			EXYNOS4_PA_VP
#define S5P_PA_HDMI			EXYNOS4_PA_HDMI
#define S5P_PA_IIC_HDMIPHY		EXYNOS4_PA_IIC_HDMIPHY
#elif defined(CONFIG_ARCH_EXYNOS5)
#define S5P_PA_MFC			EXYNOS5_PA_MFC
#define S5P_PA_MIPI_CSIS0		EXYNOS5_PA_MIPI_CSIS0
#define S5P_PA_MIPI_CSIS1		EXYNOS5_PA_MIPI_CSIS1
#define S5P_PA_MIPI_CSIS2		EXYNOS5_PA_MIPI_CSIS2
#define S5P_PA_HDMI_CEC			EXYNOS5_PA_HDMI_CEC
#define S5P_PA_MIXER			EXYNOS5_PA_MIXER
#define S5P_PA_HDMI			EXYNOS5_PA_HDMI
#define S5P_PA_HDMIPHY			EXYNOS5_PA_HDMIPHY
#define S5P_PA_IIC_HDMIPHY		EXYNOS5_PA_IIC_HDMIPHY
#endif
#define S5P_PA_ONENAND			EXYNOS4_PA_ONENAND
#define S5P_PA_ONENAND_DMA		EXYNOS4_PA_ONENAND_DMA
#define S5P_PA_SDRAM			EXYNOS4_PA_SDRAM

#if defined(CONFIG_SOC_EXYNOS4210)
#define SAMSUNG_PA_ADC			EXYNOS4_PA_ADC
#define SAMSUNG_PA_ADC1			EXYNOS4_PA_ADC1
#elif defined(CONFIG_SOC_EXYNOS4212) || defined(CONFIG_SOC_EXYNOS4412)
#define SAMSUNG_PA_ADC			EXYNOS4X12_PA_ADC
#elif defined(CONFIG_ARCH_EXYNOS5)
#define SAMSUNG_PA_ADC			EXYNOS5_PA_ADC
#endif
#define SAMSUNG_PA_KEYPAD		EXYNOS4_PA_KEYPAD

#define S5P_PA_ACE			EXYNOS5_PA_ACE
#define S5P_PA_TMU			EXYNOS5_PA_TMU

#if defined(CONFIG_ARCH_EXYNOS4)
#define EXYNOS_PA_OHCI			EXYNOS4_PA_OHCI
#elif defined(CONFIG_ARCH_EXYNOS5)
#define EXYNOS_PA_OHCI			EXYNOS5_PA_OHCI
#endif
/* Compatibility UART */

#define EXYNOS4_PA_UART0		0x13800000
#define EXYNOS4_PA_UART1		0x13810000
#define EXYNOS4_PA_UART2		0x13820000
#define EXYNOS4_PA_UART3		0x13830000
#define EXYNOS4_SZ_UART			SZ_256

#define EXYNOS5_PA_UART0		0x12C00000
#define EXYNOS5_PA_UART1		0x12C10000
#define EXYNOS5_PA_UART2		0x12C20000
#define EXYNOS5_PA_UART3		0x12C30000
#define EXYNOS5_SZ_UART			SZ_256

#define S3C_VA_UARTx(x)			(S3C_VA_UART + ((x) * S3C_UART_OFFSET))

/* Compatibility C2C */
#define EXYNOS_PA_C2C			EXYNOS5_PA_C2C
#define EXYNOS_PA_C2C_CP		EXYNOS5_PA_C2C_CP

#define EXYNOS_PA_C2C_EXT		EXYNOS5_PA_C2C_EXT
#endif /* __ASM_ARCH_MAP_H */
