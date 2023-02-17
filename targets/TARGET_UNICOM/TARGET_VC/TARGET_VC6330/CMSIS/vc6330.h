/*************************************************************************//**
 * @file     vc6330.h
 * @brief    CMSIS-Core(M) Device Peripheral Access Layer Header File for
 *           VC6330 Device
 * @version  V1.0.0
 * @date     29. June 2022
 *****************************************************************************/
/*
 * Copyright (c) 2022 Unicom Semiconductor, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef VC6330_H
#define VC6330_H

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================= */
/* ============        Interrupt Number Definition            ============ */
/* ======================================================================= */

typedef enum IRQn
{
/* ================     Cortex-M Core Exception Numbers     ================ */

  Reset_IRQn             = -15,  /*  1 Reset Vector
                                       invoked on Power up and warm reset */
  NonMaskableInt_IRQn    = -14,  /*  2 Non maskable Interrupt
                                       cannot be stopped or preempted */
  HardFault_IRQn         = -13,  /*  3 Hard Fault
                                       all classes of Fault */
  MemoryManagement_IRQn  = -12,  /*  4 Memory Management
                                       MPU mismatch, including Access Violation and No Match */
  BusFault_IRQn          = -11,  /*  5 Bus Fault
                                       Pre-Fetch-, Memory Access, other address/memory Fault */
  UsageFault_IRQn        = -10,  /*  6 Usage Fault
                                       i.e. Undef Instruction, Illegal State Transition */
  SVCall_IRQn            =  -5,  /* 11 System Service Call via SVC instruction */
  DebugMonitor_IRQn      =  -4,  /* 12 Debug Monitor */
  PendSV_IRQn            =  -2,  /* 14 Pendable request for system service */
  SysTick_IRQn           =  -1,  /* 15 System Tick TIMer */

/* ================        VC6330   Interrupt Numbers       ================ */

  PMU_IRQn               = 0,
  RTC_IRQn               = 1,

  I2C1_IRQn              = 4,
  SPI1_IRQn              = 5,
  UART0_IRQn             = 6,
  UART1_IRQn             = 7,
  UART2_IRQn             = 8,
  UART3_IRQn             = 9,
  UART4_IRQn             = 10,
  UART5_IRQn             = 11,
  ISO78160_IRQn          = 12,
  ISO78161_IRQn          = 13,
  TIM0_IRQn              = 14,
  TIM1_IRQn              = 15,
  TIM2_IRQn              = 16,
  TIM3_IRQn              = 17,
  PWM0_IRQn              = 18,
  PWM1_IRQn              = 19,
  PWM2_IRQn              = 20,
  PWM3_IRQn              = 21,
  DMA_IRQn               = 22,

  ANA_IRQn               = 24,

  SPI2_IRQn              = 27,
  SPI3_IRQn              = 28,
  KEYSCAN_IRQn           = 29,
  UART6_IRQn             = 30,
  HASH_IRQn              = 31,
  PLC_DMA_IRQn           = 32,
  PLC_MAC_IRQn           = 33,
  PHY_IRQn               = 34,
  ETHERNET_MAC_IRQn      = 35,
  I2C2_IRQn              = 36,
  ETHERNET_IRQn          = 37,
  GPIO_IRQn              = 38,
  PKE_IRQn               = 39,
  SKE_IRQn               = 40,
  SD_IRQn                = 41,
  TRNG_IRQn              = 42,
} IRQn_Type;

/* ========================================================================= */
/* ============      Processor and Core Peripheral Section      ============ */
/* ========================================================================= */

/* ================ Start of section using anonymous unions ================ */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/* ================    Configuration of Core Peripherals    ================ */
#define __CM3_REV               0x0001U  /* Core Revision r2p1 */

#define __Vendor_SysTickConfig  0U       /* Set to 1 if different SysTick Config is used */
#define __NVIC_PRIO_BITS        6U       /* Number of Bits used for Priority Levels */
#define __VTOR_PRESENT          1U       /* Set to 1 if VTOR is present */
#define __MPU_PRESENT           0U       /* Set to 1 if MPU is present */
#define __FPU_PRESENT           0U       /* Set to 1 if FPU is present */
#define __FPU_DP                0U       /* Set to 1 if FPU is double precision FPU (default is single precision FPU) */
#define __DSP_PRESENT           0U       /* Set to 1 if DSP extension are present */
#define __SAUREGION_PRESENT     0U       /* Set to 1 if SAU regions are present */

#define __PMU_PRESENT           0U       /* Set to 1 if PMU is present */
#define __PMU_NUM_EVENTCNT      0U       /* Set number of PMU Event Counters */

#define __ICACHE_PRESENT        0U       /* Set to 1 if I-Cache is present */
#define __DCACHE_PRESENT        0U       /* Set to 1 if D-Cache is present */
#define __DTCM_PRESENT          0U       /* Set to 1 if DTCM is present */

#include <core_cm3.h>                    /* Processor and core peripherals */
#include "system_vc6330.h"               /* System Header */

/* ========================================================================= */
/* ============       Device Specific Peripheral Section        ============ */
/* ========================================================================= */

/* ========================================================================= */
/* ============          PMU (Power Management Unit)            ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t DSLEEPEN;              /* (0x0000) PMU deep sleep enable register */
  __IOM uint32_t DSLEEPPASS;            /* (0x0004) PMU deep sleep password register */
  __IOM uint32_t CTRL;                  /* (0x0008) PMU control register */
  __IOM uint32_t STS;                   /* (0x000C) PMU status register */
  __IOM uint32_t IOAOEN;                /* (0x0010) IOA output enable register */
  __IOM uint32_t IOAIE;                 /* (0x0014) IOA input enable register */
  __IOM uint32_t IOADAT;                /* (0x0018) IOA data register */
  __IOM uint32_t IOAATT;                /* (0x001C) IOA attribute register */
  __IOM uint32_t IOAWKUEN;              /* (0x0020) IOA wake-up enable register */
  __IM uint32_t  IOASTS;                /* (0x0024) IOA status register */
  __IOM uint32_t IOAINT;                /* (0x0028) IOA interrupt status register */
  __IM uint32_t  RESERVED[2];
  __IOM uint32_t IOADR;                 /* (0x0034) IOA driving strength register */
  __IM uint32_t  RESERVED1[1];
  __IM uint32_t  VERCODE;               /* (0x003C) DATE code */

  __IOM uint32_t WDTPASS;               /* (0x0040) Watchdog timer unlock register */
  __IOM uint32_t WDTEN;                 /* (0x0044) Watchdog timer enable register */
  __OM uint32_t  WDTCLR;                /* (0x0048) Watchdog timer clear register */
  __IOM uint32_t WDTSTS;                /* (0x004C) Watchdog timer status register */
  __IOM uint32_t IOANODEG;              /* (0x0050) IOA no-deglitch control register */
  __IOM uint32_t IOASEL0;               /* (0x0054) IOA special function select register 0 */
  __IOM uint32_t IOASEL1;               /* (0x0058) IOA special function select register 1 */
  __IM uint32_t  RESERVED2[3];

  __IOM uint32_t REMAP;                 /* (0x0068) Re-map control register */
  __IOM uint32_t REMAPPASS;             /* (0x006C) Re-map password register */
  __IM uint32_t  STRAP;                 /* (0x0070) Boot strap status register */
  __IM uint32_t  VERSIONID;             /* (0x0074) Version ID of vc6330 */
  __IM uint32_t  RESERVED3[34];
  __IOM uint32_t RCO100KCTRL0;          /* (0x0100) PMU LDO control register */
  __IOM uint32_t RG_LDO_CTRL;           /* (0x0104) LDO 1.2V control register */
  __IOM uint32_t RG_BUCK_CTRL;          /* (0x0108) BUCK 1.2V control register */
  __IM uint32_t  RESERVED4[61];
  __IOM uint32_t RCO100KCTRL1;          /* (0x0200) PMU RC100K control register */
  __IM uint32_t  RESERVED5[3];
  __IOM uint32_t RCO1MCTRL;             /* (0x0210) BUCK 1M control register */
} VC_PMU_TypeDef;

/* PMU_DSLEEPEN register */
#define VC_PMU_DSLEEPEN_DSLEEP_Pos              0
#define VC_PMU_DSLEEPEN_DSLEEP_Msk              (1UL << VC_PMU_DSLEEPEN_DSLEEP_Pos)

#define VC_PMU_DSLEEPEN_WKU_Pos                 31
#define VC_PMU_DSLEEPEN_WKU_Msk                 (1UL << VC_PMU_DSLEEPEN_WKU_Pos)

/* PMU_DSLEEPPASS register */
#define VC_PMU_DSLEEPPASS_UNLOCK_Pos            0
#define VC_PMU_DSLEEPPASS_UNLOCK_Msk            (1UL << VC_PMU_DSLEEPPASS_UNLOCK_Pos)

/* PMU_CTRL register */
#define VC_PMU_CTRL_INTEN_Pos                   0
#define VC_PMU_CTRL_INTEN_Msk                   (1UL << VC_PMU_CTRL_INTEN_Pos)

#define VC_PMU_CTRL_PWUPCYC_Pos                 8
#define VC_PMU_CTRL_PWUPCYC_Msk                 (0xFFUL << VC_PMU_CTRL_PWUPCYC_Pos)

/* PMU_STS register */
#define VC_PMU_STS_EXTRST_Pos                   4
#define VC_PMU_STS_EXTRST_Msk                   (1UL << VC_PMU_STS_EXTRST_Pos)

#define VC_PMU_STS_PORST_Pos                    5
#define VC_PMU_STS_PORST_Msk                    (1UL << VC_PMU_STS_PORST_Pos)

#define VC_PMU_STS_DPORST_Pos                   6
#define VC_PMU_STS_DPORST_Msk                   (1UL << VC_PMU_STS_DPORST_Pos)

#define VC_PMU_STS_WDTSTS_Pos                   7
#define VC_PMU_STS_WDTSTS_Msk                   (1UL << VC_PMU_STS_WDTSTS_Pos)

#define VC_PMU_STS_SFTRST_Pos                   8
#define VC_PMU_STS_SFTRST_Msk                   (1UL << VC_PMU_STS_SFTRST_Pos)

#define VC_PMU_STS_BUCK_DROP_STS_Pos            10
#define VC_PMU_STS_BUCK_DROP_STS_Msk            (1UL << VC_PMU_STS_BUCK_DROP_STS_Pos)

#define VC_PMU_STS_WKUIOA_Pos                   16
#define VC_PMU_STS_WKUIOA_Msk                   (1UL << VC_PMU_STS_WKUIOA_Pos)

#define VC_PMU_STS_WKURTC_Pos                   17
#define VC_PMU_STS_WKURTC_Msk                   (1UL << VC_PMU_STS_WKURTC_Pos)

#define VC_PMU_STS_WKUANA_Pos                   18
#define VC_PMU_STS_WKUANA_Msk                   (1UL << VC_PMU_STS_WKUANA_Pos)

#define VC_PMU_STS_MODE_Pos                     24
#define VC_PMU_STS_MODE_Msk                     (1UL << VC_PMU_STS_MODE_Pos)

/* PMU_WDTPASS register */
#define VC_PMU_WDTPASS_UNLOCK_Pos               0
#define VC_PMU_WDTPASS_UNLOCK_Msk               (1UL << VC_PMU_WDTPASS_UNLOCK_Pos)

/* PMU_WDTEN register */
#define VC_PMU_WDTEN_WDTEN_Pos                  0
#define VC_PMU_WDTEN_WDTEN_Msk                  (1UL << VC_PMU_WDTEN_WDTEN_Pos)

#define VC_PMU_WDTEN_WDTSEL_Pos                 2
#define VC_PMU_WDTEN_WDTSEL_Msk                 (0x3UL << VC_PMU_WDTEN_WDTSEL_Pos)

/* PMU_WDTCLR register */
#define VC_PMU_WDTCLR_WDTCNT_Pos                0
#define VC_PMU_WDTCLR_WDTCNT_Msk                (0xFFFFUL << VC_PMU_WDTCLR_WDTCNT_Pos)

/* PMU_WDTSTS register */
#define VC_PMU_WDTSTS_WDTSTS_Pos                0
#define VC_PMU_WDTSTS_WDTSTS_Msk                (1UL << VC_PMU_WDTSTS_WDTSTS_Pos)

/* PMU_REMAP register */
#define VC_PMU_REMAP_REMAP_Pos                  0
#define VC_PMU_REMAP_REMAP_Msk                  (0x3UL << VC_PMU_REMAP_REMAP_Pos)

/* PMU_REMAPPASS register */
#define VC_PMU_REMAPPASS_REMAPUNLOCK_Pos        0
#define VC_PMU_REMAPPASS_REMAPUNLOCK_Msk        (1UL << VC_PMU_REMAPPASS_REMAPUNLOCK_Pos)

/* PMU_STRAP register */
#define VC_PMU_STRAP_STRAP_Pos                  0
#define VC_PMU_STRAP_STRAP_Msk                  (0xFFUL << VC_PMU_STRAP_STRAP_Pos)

/* PMU_RCO100KCTRL0 register */
#define VC_PMU_RG_RCO100KCTRL0_PWD_Pos          0
#define VC_PMU_RG_RCO100KCTRL0_PWD_Msk          (1UL << VC_PMU_RCO100KCTRL0_RG_RCO100K_PWD_Pos)

#define VC_PMU_RG_RCO100KCTRL0_CKMON_EN_Pos     1
#define VC_PMU_RG_RCO100KCTRL0_CMKON_EN_Msk     (1UL << VC_PMU_RG_RCO100K_CKMON_EN_Pos)

#define VC_PMU_RG_RCO100KCTRL0_RCODE_Pos        2
#define VC_PMU_RG_RCO100KCTRL0_RCODE_Msk        (0x1FUL << VC_PMU_RG_RCO100K_RCODE_Pos)

/* RG_LDO_CTRL register */
#define VC_PMU_RG_LDO_VOUT_SEL_Pos              0
#define VC_PMU_RG_LDO_VOUT_SEL_Msk              (0x7UL << VC_PMU_RG_LDO_VOUT_SEL_Pos)

/* RG_BUCK_CTRL register */
#define VC_PMU_RG_BUCK_VOUT_SEL_Pos             0
#define VC_PMU_RG_BUCK_VOUT_SEL_Msk             (0x7UL << VC_PMU_RG_BUCK_VOUT_SEL_Pos)

#define VC_PMU_RG_BUCK_TRIMVOL_Pos              3
#define VC_PMU_RG_BUCK_TRIMVOL_Msk              (0x7UL << VC_PMU_RG_BUCK_TRIMVOL_Pos)

#define VC_PMU_RG_BUCK_TRIMV0P6V_EN_Pos         6
#define VC_PMU_RG_BUCK_TRIMV0P6V_EN_Msk         (1UL << VC_PMU_RG_BUCK_TRIMV0P6V_EN_Pos)

#define VC_PMU_RG_BUCK_TRIMCUR_EN_Pos           7
#define VC_PMU_RG_BUCK_TRIMCUR_EN_Msk           (1UL << VC_PMU_RG_BUCK_TRIMCUR_EN_Pos)

#define VC_PMU_RG_BUCK_TRIMCUR_Pos              8
#define VC_PMU_RG_BUCK_TRIMCUR_Msk              (0x7UL << VC_PMU_RG_BUCK_TRIMCUR_Pos)

#define VC_PMU_RG_BUCK_SLOPECOM_EN_Pos          11
#define VC_PMU_RG_BUCK_SLOPECOM_EN_Msk          (1UL << VC_PMU_RG_BUCK_SLOPECOM_EN_Pos)

#define VC_PMU_RG_BUCK_SLOPECOM_DUB_Pos         12
#define VC_PMU_RG_BUCK_SLOPECOM_DUB_Msk         (1UL << VC_PMU_RG_BUCK_SLOPECOM_DUB_Pos)

#define VC_PMU_RG_BUCK_RCOMP_Pos                13
#define VC_PMU_RG_BUCK_RCOMP_Msk                (0x7UL << VC_PMU_RG_BUCK_RCOMP_Pos)

#define VC_PMU_RG_BUCK_LSDOC_Pos                16
#define VC_PMU_RG_BUCK_LSDOC_Msk                (0x3UL << VC_PMU_RG_BUCK_LSDOC_Pos)

#define VC_PMU_RG_BUCK_EN_Pos                   18
#define VC_PMU_RG_BUCK_EN_Msk                   (1UL << VC_PMU_RG_BUCK_EN_Pos)

#define VC_PMU_RG_BUCK_EA_SOFTST_Pos            19
#define VC_PMU_RG_BUCK_EA_SOFTST_Msk            (0x3UL << VC_PMU_RG_BUCK_EA_SOFTST_Pos)

#define VC_PMU_RG_BUCK_RCO1M_RCODE_Pos          21
#define VC_PMU_RG_BUCK_RCO1M_RCODE_Msk          (0x1FUL << VC_PMU_RG_BUCK_RCO1M_RCODE_Pos)

/* PMU_RCO100KCTRL1 register */
#define VC_PMU_RG_RCO100KCTRL1_FM_EN_Pos        0
#define VC_PMU_RG_RCO100KCTRL1_FM_EN_Msk        (1UL << VC_PMU_RG_RCO100KCTRL1_FM_EN_Pos)

#define VC_PMU_RG_RCO100KCTRL1_WIN_Pos          1
#define VC_PMU_RG_RCO100KCTRL1_WIN_Msk          (0x3UL << VC_PMU_RG_RCO100KCTRL1_WIN_Pos)

#define VC_PMU_RG_RCO100KCTRL1_FSEL_Pos         3
#define VC_PMU_RG_RCO100KCTRL1_FSEL_Msk         (0x3UL << VC_PMU_RG_RCO100KCTRL1_FSEL_Pos)

#define VC_PMU_RG_RCO100KCTRL1_BIN_MODE_Pos     5
#define VC_PMU_RG_RCO100KCTRL1_BIN_MODE_Msk     (1UL << VC_PMU_RG_RCO100KCTRL1_BIN_MODE_Pos)

#define VC_PMU_RG_RCO100KCTRL1_RCODE_MAN_Pos    6
#define VC_PMU_RG_RCO100KCTRL1_RCODE_MAN_Msk    (1UL << VC_PMU_RG_RCO100KCTRL1_RCODE_MAN_Pos)

#define VC_PMU_RG_RCO100KCTRL1_FREF_SEL_Pos     7
#define VC_PMU_RG_RCO100KCTRL1_FREF_SEL_Msk     (1UL << VC_PMU_RG_RCO100KCTRL1_FREF_SEL_Pos)

#define VC_PMU_RG_RCO100KCTRL1_FM_DONE_Pos      8
#define VC_PMU_RG_RCO100KCTRL1_FM_DONE_Msk      (1UL << VC_PMU_RG_RCO100KCTRL1_FM_DONE_Pos)

#define VC_PMU_RG_RCO100KCTRL1_FM_FAIL_Pos      9
#define VC_PMU_RG_RCO100KCTRL1_FM_FAIL_Msk      (1UL << VC_PMU_RG_RCO100KCTRL1_FM_FAIL_Pos)

#define VC_PMU_RG_RCO100KCTRL1_RTC_EN_Pos       10
#define VC_PMU_RG_RCO100KCTRL1_RTC_EN_Msk       (1UL << VC_PMU_RG_RCO100KCTRL1_RTC_EN_Pos)

#define VC_PMU_RG_RCO100KCTRL1_FREF_SRC_SEL_Pos 11
#define VC_PMU_RG_RCO100KCTRL1_FREF_SRC_SEL_Msk (1UL << VC_PMU_RG_RCO100KCTRL1_FREF_SRC_SEL_Pos)

/* PMU_RCO1MCTRL register */
#define VC_PMU_RG_BUCK_RCO1M_RCODE_MAN_Pos      6
#define VC_PMU_RG_BUCK_RCO1M_RCODE_MAN_Msk      (1UL << VC_PMU_RG_BUCK_RCO1M_RCODE_MAN_Pos)

/* ========================================================================= */
/* ============                Analog Controller                ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t RG_XTAL_CTRL;              /* (0x0000) XTAL control register */
  __IOM uint32_t RG_GPPLL_CTRL0;            /* (0x0004) General purpose PLL control 0 register */
  __IOM uint32_t RG_GPPLL_CTRL1;            /* (0x0008) General purpose PLL control 1 register */
  __IOM uint32_t RG_BBPLL_CTRL0;            /* (0x000C) Base band PLL control 0 register */
  __IOM uint32_t RG_BBPLL_CTRL1;            /* (0x0010) Base band PLL control 1 register */
  __IM uint32_t RESERVED[7];
  __IOM uint32_t ANA_TRNGCTRL; 	            /* (0x0030) True random number generator control register */
  __IOM uint32_t ANA_TRNGDATA;              /* (0x0034) True random number generator data register */
  __IOM uint32_t ANA_PRNGDATA;              /* (0x0038) Pseudo random number generator data register */
  __IM uint32_t RESERVED1;
  __IOM uint32_t ANA_RSV1;     	            /* (0x0040) Analog reserved register 1 */
  __IOM uint32_t ANA_RSV2;                  /* (0x0044) Analog reserved register 2 */
  __IOM uint32_t RG_ATEST_CTRL;             /* (0x0048) ATEST control register */
  __IM uint32_t RESERVED2;
  __IOM uint32_t ANA_CTRL;                  /* (0x0050) Analog control register */
  __IM uint32_t  RESERVED3[3];
  __IOM uint32_t ANA_INTSTS;                /* (0x0060) Analog interrupt status register */
  __IOM uint32_t ANA_INTEN;                 /* (0x0064) Analog interrupt enable register */
  __IM uint32_t  RESERVED4[42];
  __IOM uint32_t RG_SOC_FNPLL_CTRL;         /* (0x0110) SOC FNPLL control register */
  __IOM uint32_t RG_SOC_FNPLL_DDSMIN;       /* (0x0114) SOC FNPLL DDSMIN register */
  __IOM uint32_t RG_SOC_FNPLL_OFFSETIN;     /* (0x0118) SOC FNPLL OFFSETIN register */
  __IOM uint32_t RG_SOC_FNPLL_TESTIN;       /* (0x011C) SOC FNPLL TESTIN register */
  __IM uint32_t  RG_SOC_FNPLL_PROBE;        /* (0x0120) SOC FNPLL PROBE register */
  __IOM uint32_t RG_SOC_FNPLL_METER_CTRL;   /* (0x0124) SOC FNPLL METER control register */
  __IM uint32_t  RESERVED5[2];
  __IOM uint32_t RG_AUXSAR_CTRL;            /* (0x0130) AUXSAR control register */
  __IM uint32_t  RESERVED6[3];
  __IOM uint32_t ADCCTRL;                   /* (0x0140) ADC control */
  __IOM uint32_t ADCCHEN;                   /* (0x0144) ADC channel enable */
  __IOM uint32_t ADCDATA;                   /* (0x0148) ADC data */
  __IM uint32_t  RESERVED7;
  __IOM uint32_t ADCDATAx[16];              /* (0x0150) ADC CHx (0 - 15) data */
  __IOM uint32_t DYING_GASP_THRESHOLD;      /* (0x0190) Dying gasp threshold register */
  __IOM uint32_t RG_DTUNE_CTRL;             /* (0x0194) DTUNE register control */
  __IOM uint32_t RG_LVD_CTRL;               /* (0x0198) LVD control register */
  __IOM uint32_t RG_ABBBG_CTRL;             /* (0x019C) Bandgap reference register */
  __IOM uint32_t RESERVED8[24];
  __IOM uint32_t RG_SOC_GPPLL_CTRL;         /* (0x0200) SOC GPPLL control register */
  __IOM uint32_t RG_SOC_GPPLL_DDSMIN;       /* (0x0204) SOC GPPLL DDSMIN register */
  __IOM uint32_t RG_SOC_GPPLL_OFFSETIN;     /* (0x0208) SOC GPPLL OFFSETIN register */
  __IOM uint32_t RG_SOC_GPPLL_TESTIN;       /* (0x020C) SOC GPPLL TESTIN register */
  __IOM uint32_t RG_SOC_GPPLL_PROBE;        /* (0x0210) SOC GPPLL PROBE register */
  __IOM uint32_t RG_SOC_GPPLL_METER_CTRL;   /* (0x0214) SOC GPPLL METER control register */
  __IOM uint32_t RG_SOC_GPPLL_DDSM;         /* (0x0218) SOC GPPLL DDSM value */
  __IOM uint32_t RG_SOC_GPPLL_DDSM_OFFSET;  /* (0x021C) SOC GPPLL DDSM offset value */
} VC_ANA_TypeDef;

/* RG_XTAL_CTRL register */
#define VC_ANA_RG_XTAL_CTRL_HFXO_SOC_EN_Pos     1
#define VC_ANA_RG_XTAL_CTRL_HFXO_SOC_EN_Msk     (1UL << VC_ANA_RG_XTAL_CTRL_HFXO_SOC_EN_Pos)

#define VC_ANA_RG_XTAL_CTRL_HFXO_GPPLL_EN_Pos   2
#define VC_ANA_RG_XTAL_CTRL_HFXO_GPPLL_EN_Msk   (1UL << VC_ANA_RG_XTAL_CTRL_HFXO_GPPLL_EN_Pos)

#define VC_ANA_RG_XTAL_CTRL_HFXO_BBPLL_EN_Pos   3
#define VC_ANA_RG_XTAL_CTRL_HFXO_BBPLL_EN_Msk   (1UL << VC_ANA_RG_XTAL_CTRL_HFXO_BBPLL_EN_Pos)

#define VC_ANA_RG_XTAL_CTRL_HFXO_CURSEL_Pos     6
#define VC_ANA_RG_XTAL_CTRL_HFXO_CURSEL_Msk     (0x3UL << VC_ANA_RG_XTAL_CTRL_HFXO_CURSEL_Pos)

#define VC_ANA_RG_XTAL_CTRL_HFXO_CSEL_Pos       8
#define VC_ANA_RG_XTAL_CTRL_HFXO_CSEL_Msk       (0xFFUL << VC_ANA_RG_XTAL_CTRL_HFXO_CSEL_Pos)

#define VC_ANA_RG_XTAL_CTRL_HFXO_CKMON_EN_Pos   16
#define VC_ANA_RG_XTAL_CTRL_HFXO_CKMON_EN_Msk   (1UL << VC_ANA_RG_XTAL_CTRL_HFXO_CKMON_EN_Pos)

#define VC_ANA_RG_XTAL_CTRL_HFXO_AMPSEL_Pos     17
#define VC_ANA_RG_XTAL_CTRL_HFXO_AMPSEL_Msk     (0x3UL << VC_ANA_RG_XTAL_CTRL_HFXO_AMPSEL_Pos)

#define VC_ANA_RG_XTAL_CTRL_HFXO_NRB_EN_Pos     19
#define VC_ANA_RG_XTAL_CTRL_HFXO_NRB_EN_Msk     (1UL << VC_ANA_RG_XTAL_CTRL_HFXO_NRB_EN_Pos)

#define VC_ANA_RG_XTAL_CTRL_HFXO_LDO_EN_Pos     20
#define VC_ANA_RG_XTAL_CTRL_HFXO_LDO_EN_Msk     (1UL << VC_ANA_RG_XTAL_CTRL_HFXO_LDO_EN_Pos)

#define VC_ANA_RG_XTAL_CTRL_HFXO_DTUNE_EN_Pos   21
#define VC_ANA_RG_XTAL_CTRL_HFXO_DTUNE_EN_Msk   (1UL << VC_ANA_RG_XTAL_CTRL_HFXO_DTUNE_EN_Pos)

#define VC_ANA_RG_XTAL_CTRL_HFXO_DYSEL_Pos      22
#define VC_ANA_RG_XTAL_CTRL_HFXO_DYSEL_Msk      (0x3UL << VC_ANA_RG_XTAL_CTRL_HFXO_DYSEL_Pos)

#define VC_ANA_RG_XTAL_CTRL_XTALIO_DS_Pos       25
#define VC_ANA_RG_XTAL_CTRL_XTALIO_DS_Msk       (0x7UL << VC_ANA_RG_XTAL_CTRL_XTALIO_DS_Pos)

/* RG_GPPLL_CTRL0 register */
#define VC_ANA_RG_GPPLL_CTRL0_ZC_Pos            0
#define VC_ANA_RG_GPPLL_CTRL0_ZC_Msk            (0x1FUL << VC_ANA_RG_GPPLL_CTRL0_ZC_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_VS_SEL_Pos        5
#define VC_ANA_RG_GPPLL_CTRL0_VS_SEL_Msk        (0xFUL << VC_ANA_RG_GPPLL_CTRL0_VS_SEL_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_VS_REFSEL_Pos     9
#define VC_ANA_RG_GPPLL_CTRL0_VS_REFSEL_Msk     (1UL << VC_ANA_RG_GPPLL_CTRL0_VS_REFSEL_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_VCMON_EN_Pos      10
#define VC_ANA_RG_GPPLL_CTRL0_VCMON_EN_Msk      (1UL << VC_ANA_RG_GPPLL_CTRL0_VCMON_EN_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_SS_SEL_Pos        11
#define VC_ANA_RG_GPPLL_CTRL0_SS_SEL_Msk        (1UL << VC_ANA_RG_GPPLL_CTRL0_SS_SEL_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_V08SEL_Pos        12
#define VC_ANA_RG_GPPLL_CTRL0_V08SEL_Msk        (0xFUL << VC_ANA_RG_GPPLL_CTRL0_V08SEL_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_SR_Pos            16
#define VC_ANA_RG_GPPLL_CTRL0_SR_Msk            (0x3UL << VC_ANA_RG_GPPLL_CTRL0_SR_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_RSTDLY_Pos        18
#define VC_ANA_RG_GPPLL_CTRL0_RSTDLY_Msk        (0x3UL << VC_ANA_RG_GPPLL_CTRL0_RSTDLY_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_SC_Pos            20
#define VC_ANA_RG_GPPLL_CTRL0_SC_Msk            (1UL << VC_ANA_RG_GPPLL_CTRL0_SC_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_PULSEDLY_Pos      21
#define VC_ANA_RG_GPPLL_CTRL0_PULSEDLY_Msk      (0x7UL << VC_ANA_RG_GPPLL_CTRL0_PULSEDLY_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_PR_Pos            24
#define VC_ANA_RG_GPPLL_CTRL0_PR_Msk            (0x1FUL << VC_ANA_RG_GPPLL_CTRL0_PR_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_POSDIV_EN_Pos     29
#define VC_ANA_RG_GPPLL_CTRL0_POSDIV_EN_Msk     (1UL << VC_ANA_RG_GPPLL_CTRL0_POSDIV_EN_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_LDOV12_RST_Pos    30
#define VC_ANA_RG_GPPLL_CTRL0_LDOV12_RST_Msk    (1UL << VC_ANA_RG_GPPLL_CTRL0_LDOV12_RST_Pos)

#define VC_ANA_RG_GPPLL_CTRL0_LDOBIAS_RSTB_Pos  31
#define VC_ANA_RG_GPPLL_CTRL0_LDOBIAS_RSTB_Msk  (1UL << VC_ANA_RG_GPPLL_CTRL0_LDOBIAS_RSTB_Pos)

/* RG_GPPLL_CTRL1 register */
#define VC_ANA_RG_GPPLL_CTRL1_PC_Pos            0
#define VC_ANA_RG_GPPLL_CTRL1_PC_Msk            (0x1FUL << VC_ANA_RG_GPPLL_CTRL1_PC_Pos)

#define VC_ANA_RG_GPPLL_CTRL1_IR_Pos            5
#define VC_ANA_RG_GPPLL_CTRL1_IR_Msk            (0x7UL << VC_ANA_RG_GPPLL_CTRL1_IR_Pos)

#define VC_ANA_RG_GPPLL_CTRL1_EN_Pos            8
#define VC_ANA_RG_GPPLL_CTRL1_EN_Msk            (1UL << VC_ANA_RG_GPPLL_CTRL1_EN_Pos)

#define VC_ANA_RG_GPPLL_CTRL1_IC_Pos            9
#define VC_ANA_RG_GPPLL_CTRL1_IC_Msk            (0x3UL << VC_ANA_RG_GPPLL_CTRL1_IC_Pos)

#define VC_ANA_RG_GPPLL_CTRL1_DDSM_ACC5B_EN_Pos 11
#define VC_ANA_RG_GPPLL_CTRL1_DDSM_ACC5B_EN_Msk (1UL << VC_ANA_RG_GPPLL_CTRL1_DDSM_ACC5B_EN_Pos)

#define VC_ANA_RG_GPPLL_CTRL1_PI_RSTB_Pos       12
#define VC_ANA_RG_GPPLL_CTRL1_PI_RSTB_Msk       (1UL << VC_ANA_RG_GPPLL_CTRL1_PI_RSTB_Pos)

#define VC_ANA_RG_GPPLL_CTRL1_CP_RSTB_Pos       13
#define VC_ANA_RG_GPPLL_CTRL1_CP_RSTB_Msk       (1UL << VC_ANA_RG_GPPLL_CTRL1_CP_RSTB_Pos)

#define VC_ANA_RG_GPPLL_CTRL1_CKMON_EN_Pos      14
#define VC_ANA_RG_GPPLL_CTRL1_CKMON_EN_Msk      (1UL << VC_ANA_RG_GPPLL_CTRL1_CKMON_EN_Pos)

#define VC_ANA_RG_GPPLL_CTRL1_33T25_RST_Pos     16
#define VC_ANA_RG_GPPLL_CTRL1_33T25_RST_Msk     (1UL << VC_ANA_RG_GPPLL_CTRL1_33T25_RST_Pos)

#define VC_ANA_RG_GPPLL_CTRL1_POSDIVSEL_Pos     17
#define VC_ANA_RG_GPPLL_CTRL1_POSDIVSEL_Msk     (0x3UL << VC_ANA_RG_GPPLL_CTRL1_POSDIVSEL_Pos)

/* RG_BBPLL_CTRL0 register */
#define VC_ANA_RG_BBPLL_CTRL0_ZC_Pos            0
#define VC_ANA_RG_BBPLL_CTRL0_ZC_Msk            (0x1FUL << VC_ANA_RG_BBPLL_CTRL0_ZC_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_VS_SEL_Pos        5
#define VC_ANA_RG_BBPLL_CTRL0_VS_SEL_Msk        (0xFUL << VC_ANA_RG_BBPLL_CTRL0_VS_SEL_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_VS_REFSEL_Pos     9
#define VC_ANA_RG_BBPLL_CTRL0_VS_REFSEL_Msk     (1UL << VC_ANA_RG_BBPLL_CTRL0_VS_REFSEL_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_VCMON_EN_Pos      10
#define VC_ANA_RG_BBPLL_CTRL0_VCMON_EN_Msk      (1UL << VC_ANA_RG_BBPLL_CTRL0_VCMON_EN_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_SS_SEL_Pos        11
#define VC_ANA_RG_BBPLL_CTRL0_SS_SEL_Msk        (1UL << VC_ANA_RG_BBPLL_CTRL0_SS_SEL_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_V08SEL_Pos        12
#define VC_ANA_RG_BBPLL_CTRL0_V08SEL_Msk        (0xFUL << VC_ANA_RG_BBPLL_CTRL0_V08SEL_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_SR_Pos            16
#define VC_ANA_RG_BBPLL_CTRL0_SR_Msk            (0x3UL << VC_ANA_RG_BBPLL_CTRL0_SR_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_RSTDLY_Pos        18
#define VC_ANA_RG_BBPLL_CTRL0_RSTDLY_Msk        (0x3UL << VC_ANA_RG_BBPLL_CTRL0_RSTDLY_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_SC_Pos            20
#define VC_ANA_RG_BBPLL_CTRL0_SC_Msk            (1UL << VC_ANA_RG_BBPLL_CTRL0_SC_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_PULSEDLY_Pos      21
#define VC_ANA_RG_BBPLL_CTRL0_PULSEDLY_Msk      (0x7UL << VC_ANA_RG_BBPLL_CTRL0_PULSEDLY_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_PR_Pos            24
#define VC_ANA_RG_BBPLL_CTRL0_PR_Msk            (0x1FUL << VC_ANA_RG_BBPLL_CTRL0_PR_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_POSDIV_EN_Pos     29
#define VC_ANA_RG_BBPLL_CTRL0_POSDIV_EN_Msk     (1UL << VC_ANA_RG_BBPLL_CTRL0_POSDIV_EN_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_LDOV12_RST_Pos    30
#define VC_ANA_RG_BBPLL_CTRL0_LDOV12_RST_Msk    (1UL << VC_ANA_RG_BBPLL_CTRL0_LDOV12_RST_Pos)

#define VC_ANA_RG_BBPLL_CTRL0_LDOBIAS_RSTB_Pos  31
#define VC_ANA_RG_BBPLL_CTRL0_LDOBIAS_RSTB_Msk  (1UL << VC_ANA_RG_BBPLL_CTRL0_LDOBIAS_RSTB_Pos)

/* RG_BBPLL_CTRL1 register */
#define VC_ANA_RG_BBPLL_CTRL1_PC_Pos            0
#define VC_ANA_RG_BBPLL_CTRL1_PC_Msk            (0x1FUL << VC_ANA_RG_BBPLL_CTRL1_PC_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_IR_Pos            5
#define VC_ANA_RG_BBPLL_CTRL1_IR_Msk            (0x7UL << VC_ANA_RG_BBPLL_CTRL1_IR_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_EN_Pos            8
#define VC_ANA_RG_BBPLL_CTRL1_EN_Msk            (1UL << VC_ANA_RG_BBPLL_CTRL1_EN_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_IC_Pos            9
#define VC_ANA_RG_BBPLL_CTRL1_IC_Msk            (0x3UL << VC_ANA_RG_BBPLL_CTRL1_IC_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_DDSM_ACC5B_EN_Pos 11
#define VC_ANA_RG_BBPLL_CTRL1_DDSM_ACC5B_EN_Msk (1UL << VC_ANA_RG_BBPLL_CTRL1_DDSM_ACC5B_EN_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_PI_RSTB_Pos       12
#define VC_ANA_RG_BBPLL_CTRL1_PI_RSTB_Msk       (1UL << VC_ANA_RG_BBPLL_CTRL1_PI_RSTB_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_CP_RSTB_Pos       13
#define VC_ANA_RG_BBPLL_CTRL1_CP_RSTB_Msk       (1UL << VC_ANA_RG_BBPLL_CTRL1_CP_RSTB_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_CKMON_EN_Pos      14
#define VC_ANA_RG_BBPLL_CTRL1_CKMON_EN_Msk      (1UL << VC_ANA_RG_BBPLL_CTRL1_CKMON_EN_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_WBADC_EN_Pos      15
#define VC_ANA_RG_BBPLL_CTRL1_WBADC_EN_Msk      (1UL << VC_ANA_RG_BBPLL_CTRL1_WBADC_EN_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_33T25_RST_Pos     16
#define VC_ANA_RG_BBPLL_CTRL1_33T25_RST_Msk     (1UL << VC_ANA_RG_BBPLL_CTRL1_33T25_RST_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_DSPCK_EN_Pos      17
#define VC_ANA_RG_BBPLL_CTRL1_DSPCK_EN_Msk      (1UL << VC_ANA_RG_BBPLL_CTRL1_DSPCK_EN_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_DACCK_EN_Pos      18
#define VC_ANA_RG_BBPLL_CTRL1_DACCK_EN_Msk      (1UL << VC_ANA_RG_BBPLL_CTRL1_DACCK_EN_Pos)

#define VC_ANA_RG_BBPLL_CTRL1_ADCCK_EN_Pos      19
#define VC_ANA_RG_BBPLL_CTRL1_ADCCK_EN_Msk      (1UL << VC_ANA_RG_BBPLL_CTRL1_ADCCK_EN_Pos)

/* ANA_TRNGCTRL register */
#define VC_ANA_TRNGCTRL_TRNGEN_Pos              0
#define VC_ANA_TRNGCTRL_TRNGEN_Msk              (1UL << VC_ANA_TRNGCTRL_TRNGEN_Pos)

#define VC_ANA_TRNGCTRL_PRNG_Pos                1
#define VC_ANA_TRNGCTRL_PRNG_Msk                (1UL << VC_ANA_TRNGCTRL_PRNG_Pos)

#define VC_ANA_TRNGCTRL_RG_CLK_MODE_Pos         2
#define VC_ANA_TRNGCTRL_RG_CLK_MODE_Msk         (1UL << VC_ANA_TRNGCTRL_RG_CLK_MODE_Pos)

#define VC_ANA_TRNGCTRL_RG_PRNG_MODE_Pos        3
#define VC_ANA_TRNGCTRL_RG_PRNG_MODE_Msk        (1UL << VC_ANA_TRNGCTRL_RG_PRNG_MODE_Pos)

#define VC_ANA_TRNGCTRL_AON_Pos                 4
#define VC_ANA_TRNGCTRL_AON_Msk                 (1UL << VC_ANA_TRNGCTRL_AON_Pos)

#define VC_ANA_TRNGCTRL_RG_TRNG_CKSEL_Pos       5
#define VC_ANA_TRNGCTRL_RG_TRNG_CKSEL_Msk       (1UL << VC_ANA_TRNGCTRL_RG_TRNG_CKSEL_Pos)

#define VC_ANA_TRNGCTRL_BITSEL_Pos              6
#define VC_ANA_TRNGCTRL_BITSEL_Msk              (0x3UL << VC_ANA_TRNGCTRL_BITSEL_Pos)

#define VC_ANA_TRNGCTRL_CLKDIV_Pos              8
#define VC_ANA_TRNGCTRL_CLKDIV_Msk              (0xFFUL << VC_ANA_TRNGCTRL_CLKDIV_Pos)

#define VC_ANA_TRNGCTRL_DELAY_Pos               16
#define VC_ANA_TRNGCTRL_DELAY_Msk               (0xFFUL << VC_ANA_TRNGCTRL_DELAY_Pos)

#define VC_ANA_TRNGCTRL_SHIFT_BIT_SEL_Pos       24
#define VC_ANA_TRNGCTRL_SHIFT_BIT_SEL_Msk       (0x7UL << VC_ANA_TRNGCTRL_SHIFT_BIT_SEL_Pos)

#define VC_ANA_TRNGCTRL_CLKDIV_BASE_Pos         29
#define VC_ANA_TRNGCTRL_CLKDIV_BASE_Msk         (0x3UL << VC_ANA_TRNGCTRL_CLKDIV_BASE_Pos)

#define VC_ANA_TRNGCTRL_BSY_Pos                 30
#define VC_ANA_TRNGCTRL_BSY_Msk                 (1UL << VC_ANA_TRNGCTRL_BSY_Pos)

/* ANA_RSV1 register */
#define VC_ANA_RSV1_ANATOP_RSVL_Pos             0
#define VC_ANA_RSV1_ANATOP_RSVL_Msk             (0xFFUL << VC_ANA_RSV1_ANATOP_RSVL_Pos)

#define VC_ANA_RSV1_ANATOP_RSVH_Pos             8
#define VC_ANA_RSV1_ANATOP_RSVH_Msk             (0xFFUL << VC_ANA_RSV1_ANATOP_RSVH_Pos)

/* ANA_RSV2 register */
#define VC_ANA_RSV2_ABBTOP_RSVL_Pos             0
#define VC_ANA_RSV2_ABBTOP_RSVL_Msk             (0xFFUL << VC_ANA_RSV2_ABBTOP_RSVL_Pos)

#define VC_ANA_RSV2_ABBTOP_RSVH_Pos             8
#define VC_ANA_RSV2_ABBTOP_RSVH_Msk             (0xFFUL << VC_ANA_RSV2_ABBTOP_RSVH_Pos)

/* RG_ATEST_CTRL register */
#define VC_ANA_RG_ATEST_EN_Pos                  0
#define VC_ANA_RG_ATEST_EN_Msk                  (1UL << VC_ANA_RG_ATEST_EN_Pos)

#define VC_ANA_RG_ATEST_VTST_EN_Pos             1
#define VC_ANA_RG_ATEST_VTST_EN_Msk             (1UL << VC_ANA_RG_ATEST_VTST_EN_Pos)

#define VC_ANA_RG_ATEST_CKTST_R50_EN_Pos        2
#define VC_ANA_RG_ATEST_CKTST_R50_EN_Msk        (1UL << VC_ANA_RG_ATEST_CKTST_R50_EN_Pos)

#define VC_ANA_RG_ATEST_CKTST_EN_Pos            3
#define VC_ANA_RG_ATEST_CKTST_EN_Msk            (1UL << VC_ANA_RG_ATEST_CKTST_EN_Pos)

#define VC_ANA_RG_ATEST_CKTST_CUR_Pos           4
#define VC_ANA_RG_ATEST_CKTST_CUR_Msk           (0x3UL << VC_ANA_RG_ATEST_CKTST_CUR_Pos)

#define VC_ANA_RG_ATEST_CKTST_CKMUX_Pos         6
#define VC_ANA_RG_ATEST_CKTST_CKMUX_Msk         (0x7UL << VC_ANA_RG_ATEST_CKTST_CKMUX_Pos)

#define VC_ANA_RG_ATEST_VTST_VMUX_Pos           9
#define VC_ANA_RG_ATEST_VTST_VMUX_Msk           (0x7UL << VC_ANA_RG_ATEST_VTST_VMUX_Pos)

#define VC_ANA_RG_ATEST_RSTB_Pos                12
#define VC_ANA_RG_ATEST_RSTB_Msk                (1UL << VC_ANA_RG_ATEST_RSTB_Pos)

/* ANA_CTRL register */
#define VC_ANA_CTRL_ADC_SMP_EGE_Pos             0
#define VC_ANA_CTRL_ADC_SMP_EGE_Msk             (1UL << VC_ANA_CTRL_ADC_SMP_EGE_Pos)

#define VC_ANA_CTRL_ALWAYS_ON_Pos               1
#define VC_ANA_CTRL_ALWAYS_ON_Msk               (1UL << VC_ANA_CTRL_ALWAYS_ON_Pos)

#define VC_ANA_CTRL_AUXSAR_ONCE_DET_Pos         2
#define VC_ANA_CTRL_AUXSAR_ONCE_DET_Msk         (1UL << VC_ANA_CTRL_AUXSAR_ONCE_DET_Pos)

/* ANA_INTSTS register */
#define VC_ANA_INTSTS_INTSTS0_Pos               0
#define VC_ANA_INTSTS_INTSTS0_Msk               (1UL << VC_ANA_INTSTS_INTSTS0_Pos)

#define VC_ANA_INTSTS_INTSTS1_Pos               1
#define VC_ANA_INTSTS_INTSTS1_Msk               (1UL << VC_ANA_INTSTS_INTSTS1_Pos)

#define VC_ANA_INTSTS_INTSTS2_Pos               2
#define VC_ANA_INTSTS_INTSTS2_Msk               (1UL << VC_ANA_INTSTS_INTSTS2_Pos)

#define VC_ANA_INTSTS_INTSTS3_Pos               3
#define VC_ANA_INTSTS_INTSTS3_Msk               (1UL << VC_ANA_INTSTS_INTSTS3_Pos)

#define VC_ANA_INTSTS_INTSTS4_19_Pos            4
#define VC_ANA_INTSTS_INTSTS4_19_Msk            (0xFFFFUL << VC_ANA_INTSTS_INTSTS4_19_Pos)

#define VC_ANA_INTSTS_DYING_GASP_DET_Pos        20
#define VC_ANA_INTSTS_DYING_GASP_DET_Msk        (1UL << VC_ANA_INTSTS_DYING_GASP_DET_Pos)

#define VC_ANA_INTSTS_TRNG_ERROR_Pos            21
#define VC_ANA_INTSTS_TRNG_ERROR_Msk            (1UL << VC_ANA_INTSTS_TRNG_ERROR_Pos)

#define VC_ANA_INTSTS_LVD_SLOW_Pos              22
#define VC_ANA_INTSTS_LVD_SLOW_Msk              (1UL << VC_ANA_INTSTS_LVD_SLOW_Pos)

/* ANA_INTEN register */
#define VC_ANA_INTEN_INTEN0_Pos                 0
#define VC_ANA_INTEN_INTEN0_Msk                 (1UL << VC_ANA_INTEN_INTEN0_Pos)

#define VC_ANA_INTEN_INTEN1_Pos                 1
#define VC_ANA_INTEN_INTEN1_Msk                 (1UL << VC_ANA_INTEN_INTEN1_Pos)

#define VC_ANA_INTEN_INTEN2_Pos                 2
#define VC_ANA_INTEN_INTEN2_Msk                 (1UL << VC_ANA_INTEN_INTEN2_Pos)

#define VC_ANA_INTEN_INTEN3_Pos                 3
#define VC_ANA_INTEN_INTEN3_Msk                 (1UL << VC_ANA_INTEN_INTEN3_Pos)

#define VC_ANA_INTEN_INTEN4_19_Pos              4
#define VC_ANA_INTEN_INTEN4_19_Msk              (0xFFFFUL << VC_ANA_INTEN_INTEN4_19_Pos)

#define VC_ANA_INTEN_INTEN20_Pos                20
#define VC_ANA_INTEN_INTEN20_Msk                (1UL << VC_ANA_INTEN_INTEN20_Pos)

#define VC_ANA_INTEN_INTEN21_Pos                21
#define VC_ANA_INTEN_INTEN21_Msk                (1UL << VC_ANA_INTEN_INTEN21_Pos)

#define VC_ANA_INTEN_INTEN22_Pos                22
#define VC_ANA_INTEN_INTEN22_Msk                (1UL << VC_ANA_INTEN_INTEN22_Pos)

/* RG_SOC_FNPLL_CTRL register */
#define VC_ANA_RG_SOC_FNPLL_DDSM_EN_Pos            0
#define VC_ANA_RG_SOC_FNPLL_DDSM_EN_Msk            (1UL << VC_ANA_RG_SOC_FNPLL_DDSM_EN_Pos)

#define VC_ANA_RG_SOC_FNPLL_DDSM_LFSR_EN_Pos       1
#define VC_ANA_RG_SOC_FNPLL_DDSM_LFSR_EN_Msk       (1UL << VC_ANA_RG_SOC_FNPLL_DDSM_LFSR_EN_Pos)

#define VC_ANA_RG_SOC_FNPLL_DDSM_TEST_Pos          4
#define VC_ANA_RG_SOC_FNPLL_DDSM_TEST_Msk          (1UL << VC_ANA_RG_SOC_FNPLL_DDSM_TEST_Pos)

#define VC_ANA_RG_SOC_FNPLL_DDSM_ACC5B_EN_Pos      5
#define VC_ANA_RG_SOC_FNPLL_DDSM_ACC5B_EN_Msk      (1UL << VC_ANA_RG_SOC_FNPLL_DDSM_ACC5B_EN_Pos)

/* RG_SOC_FNPLL_DDSMIN register */
#define VC_ANA_RG_SOC_FNPLL_DDSMIN_Pos             0
#define VC_ANA_RG_SOC_FNPLL_DDSMIN_Msk             (0x7FFFFFFUL << VC_ANA_RG_SOC_FNPLL_DDSMIN_Pos)

/* RG_SOC_FNPLL_OFFSETIN register */
#define VC_ANA_RG_SOC_FNPLL_OFFSETIN_Pos           0
#define VC_ANA_RG_SOC_FNPLL_OFFSETIN_Msk           (0x7FUL << VC_ANA_RG_SOC_FNPLL_OFFSETIN_Pos)

/* RG_SOC_FNPLL_TESTIN register */
#define VC_ANA_RG_SOC_FNPLL_TESTIN_Pos             0
#define VC_ANA_RG_SOC_FNPLL_TESTIN_Msk             (0x7FFFFFFUL << VC_ANA_RG_SOC_FNPLL_TESTIN_Pos)

/* RG_SOC_FNPLL_PROBE register */
#define VC_ANA_RG_SOC_FNPLL_PROBE_Pos              0
#define VC_ANA_RG_SOC_FNPLL_PROBE_Msk              (0xFFFFFFUL << VC_ANA_RG_SOC_FNPLL_PROBE_Pos)

/* RG_SOC_FNPLL_METER_CTRL register */
#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_EN_Pos   0
#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_EN_Msk   (1UL << VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_EN_Pos)

#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_WIN_Pos     1
#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_WIN_Msk     (0x3UL << VC_ANA_RG_SOC_FNPLL_METER_CTRL_WIN_Pos)

#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_BINARYMODE_Pos   3
#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_BINARYMODE_Msk   (1UL << VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_BINARYMODE_Pos)

#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_MANUALSEL_Pos    4
#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_MANUALSEL_Msk    (1UL << VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_MANUALSEL_Pos)

#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_MANU_IBAND_Pos      5
#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_MANU_IBAND_Msk      (0xFUL << VC_ANA_RG_SOC_FNPLL_METER_CTRL_MANU_IBAND_Pos)

#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_PLL_WAIT_TIME_Pos   11
#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_PLL_WAIT_TIME_Msk   (0x7FUL << VC_ANA_RG_SOC_FNPLL_METER_CTRL_PLL_WAIT_TIME_Pos)

#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_FNPLL_IBAND_RST_Pos 18
#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_FNPLL_IBAND_RST_Msk (1UL << VC_ANA_RG_SOC_FNPLL_METER_CTRL_FNPLL_IBAND_RST_Pos)

#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_DONE_Pos         19
#define VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_DONE_Msk         (1UL << VC_ANA_RG_SOC_FNPLL_METER_CTRL_FM_DONE_Pos)

/* RG_AUXSAR_CTRL register */
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_RST_Pos     0
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_RST_Msk     (1UL << VC_ANA_RG_AUXSAR_CTRL_AUXADC_RST_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_VINTEN_Pos  1
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_VINTEN_Msk  (1UL << VC_ANA_RG_AUXSAR_CTRL_AUXADC_VINTEN_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_ASMODE_Pos  2
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_ASMODE_Msk  (1UL << VC_ANA_RG_AUXSAR_CTRL_AUXADC_ASMODE_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_ASDEL_Pos   3
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_ASDEL_Msk   (1UL << VC_ANA_RG_AUXSAR_CTRL_AUXADC_ASDEL_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_CKPHOUT_Pos 4
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_CKPHOUT_Msk (1UL << VC_ANA_RG_AUXSAR_CTRL_AUXADC_CKPHOUT_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_VREF_Pos    5
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_VREF_Msk    (0x3UL << VC_ANA_RG_AUXSAR_CTRL_AUXADC_VREF_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_VCAL_Pos    7
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_VCAL_Msk    (0x3UL << VC_ANA_RG_AUXSAR_CTRL_AUXADC_VCAL_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_TRIG_HIGH_Pos      9
#define VC_ANA_RG_AUXSAR_CTRL_TRIG_HIGH_Msk      (0x3FUL << VC_ANA_RG_AUXSAR_CTRL_TRIG_HIGH_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_TRIG_LOW_Pos       16
#define VC_ANA_RG_AUXSAR_CTRL_TRIG_LOW_Msk       (0x1FFUL << VC_ANA_RG_AUXSAR_CTRL_TRIG_LOW_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_VREF_FINE_Pos 25
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_VREF_FINE_Msk (0xFUL << VC_ANA_RG_AUXSAR_CTRL_AUXADC_VREF_FINE_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_SINGLE_Pos  29
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_SINGLE_Msk  (1UL << VC_ANA_RG_AUXSAR_CTRL_AUXADC_SINGLE_Pos)

#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_CKDIV_Pos   30
#define VC_ANA_RG_AUXSAR_CTRL_AUXADC_CKDIV_Msk   (0x3UL << VC_ANA_RG_AUXSAR_CTRL_AUXADC_CKDIV_Pos)

/* ANA_ADCCTRL register */
#define VC_ANA_ADCCTRL_ADC_EN_Pos               0
#define VC_ANA_ADCCTRL_ADC_EN_Msk               (1UL << VC_ANA_ADCCTRL_ADC_EN_Pos)

#define VC_ANA_ADCCTRL_ADC_START_Pos            1
#define VC_ANA_ADCCTRL_ADC_START_Msk            (1UL << VC_ANA_ADCCTRL_ADC_START_Pos)

#define VC_ANA_ADCCTRL_ADC_STOP_Pos             2
#define VC_ANA_ADCCTRL_ADC_STOP_Msk             (1UL << VC_ANA_ADCCTRL_ADC_STOP_Pos)

#define VC_ANA_ADCCTRL_ADC_CONTI_Pos            3
#define VC_ANA_ADCCTRL_ADC_CONTI_Msk            (1UL << VC_ANA_ADCCTRL_ADC_CONTI_Pos)

#define VC_ANA_ADCCTRL_ADC_TRG_SEL_Pos          4
#define VC_ANA_ADCCTRL_ADC_TRG_SEL_Msk          (0x7UL << VC_ANA_ADCCTRL_ADC_TRG_SEL_Pos)

#define VC_ANA_ADCCTRL_ADC_ALIEN_Pos            7
#define VC_ANA_ADCCTRL_ADC_ALIEN_Msk            (1UL << VC_ANA_ADCCTRL_ADC_ALIEN_Pos)

#define VC_ANA_ADCCTRL_ADC_DELAY_Pos            8
#define VC_ANA_ADCCTRL_ADC_DELAY_Msk            (0xFFUL << VC_ANA_ADCCTRL_ADC_DELAY_Pos)

#define VC_ANA_ADCCTRL_ADC_CLKSEL_Pos           16
#define VC_ANA_ADCCTRL_ADC_CLKSEL_Msk           (1UL << VC_ANA_ADCCTRL_ADC_CLKSEL_Pos)

#define VC_ANA_ADCCTRL_ADC_FEN_Pos              17
#define VC_ANA_ADCCTRL_ADC_FEN_Msk              (1UL << VC_ANA_ADCCTRL_ADC_FEN_Pos)

#define VC_ANA_ADCCTRL_ADC_CLKDIV_Pos           20
#define VC_ANA_ADCCTRL_ADC_CLKDIV_Msk           (0xFFUL << VC_ANA_ADCCTRL_ADC_CLKDIV_Pos)

/* ANA_ADCCHEN register */
#define VC_ANA_ADCCHEN_ADC_CHEN0_15_Pos         0
#define VC_ANA_ADCCHEN_ADC_CHEN0_15_Msk         (0xFFFFUL << VC_ANA_ADCCHEN_ADC_CHEN0_15_Pos)

/* ANA_ADCDATA register */
#define VC_ANA_ADCDATA_ADCDATA_Pos              0
#define VC_ANA_ADCDATA_ADCDATA_Msk              (0xFFFFUL << VC_ANA_ADCDATA_ADCDATA_Pos)

/* ANA_ADCDATAx register */
#define VC_ANA_ADCDATAx_ADCDATA0_15_Pos         0
#define VC_ANA_ADCDATAx_ADCDATA0_15_Msk         (0xFFFFUL << VC_ANA_ADCDATAx_ADCDATA0_15_Pos)

/* DYING GASP THRESHOLD register */
#define VC_ANA_DYING_THRES_Pos                  0
#define VC_ANA_DYING_THRES_Msk                  (0x3FFUL << VC_ANA_DYING_THRES_Pos)

/* RG_DTUNE_CTRL register */
#define VC_ANA_RG_DTUNE_CTRL_RSEL_Pos           0
#define VC_ANA_RG_DTUNE_CTRL_RSEL_Msk           (0x1FUL << VC_ANA_RG_DTUNE_CTRL_RSEL_Pos)

#define VC_ANA_RG_DTUNE_CTRL_MAN_Pos            5
#define VC_ANA_RG_DTUNE_CTRL_MAN_Msk            (1UL << VC_ANA_RG_DTUNE_CTRL_MAN_Pos)

/* RG_LVD_CTRL register */
#define VC_ANA_RG_LVD_CTRL_PWD_Pos              0
#define VC_ANA_RG_LVD_CTRL_PWD_Msk              (1UL << VC_ANA_RG_LVD_CTRL_PWD_Pos)

#define VC_ANA_RG_LVD_CTRL_VTHSEL_Pos           2
#define VC_ANA_RG_LVD_CTRL_VTHSEL_Msk           (0x3UL << VC_ANA_RG_LVD_CTRL_VTHSEL_Pos)

#define VC_ANA_RG_LVD_CTRL_PDNS_Pos             4
#define VC_ANA_RG_LVD_CTRL_PDNS_Msk             (1UL << VC_ANA_RG_LVD_CTRL_PDNS_Pos)

#define VC_ANA_RG_LVD_CTRL_LVD_DEBSEL_Pos       6
#define VC_ANA_RG_LVD_CTRL_LVD_DEBSEL_Msk       (0x3UL << VC_ANA_RG_LVD_CTRL_LVD_DEBSEL_Pos)

#define VC_ANA_RG_LVD_CTRL_LVD_SMPSEL_Pos       8
#define VC_ANA_RG_LVD_CTRL_LVD_SMPSEL_Msk       (0x3UL << VC_ANA_RG_LVD_CTRL_LVD_SMPSEL_Pos)

/* RG_ABBBG_CTRL register */
#define VC_ANA_RG_ABBBG_CTRL_TRIMVOL_Pos        0
#define VC_ANA_RG_ABBBG_CTRL_TRIMVOL_Msk        (0x7UL << VC_ANA_RG_ABBBG_CTRL_TRIMVOL_Pos)

#define VC_ANA_RG_ABBBG_CTRL_EN_Pos             3
#define VC_ANA_RG_ABBBG_CTRL_EN_Msk             (1UL << VC_ANA_RG_ABBBG_CTRL_EN_Pos)

/* RG_SOC_GPPLL_CTRL register */
#define VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_EN_Pos         0
#define VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_EN_Msk         (1UL << VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_EN_Pos)

#define VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_LFSR_EN_Pos    1
#define VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_LFSR_EN_Msk    (1UL << VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_LFSR_EN_Pos)

#define VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_TEST_Pos       4
#define VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_TEST_Msk       (1UL << VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_TEST_Pos)

#define VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_ACC5B_EN_Pos   5
#define VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_ACC5B_EN_Msk   (1UL << VC_ANA_RG_SOC_GPPLL_CTRL_DDSM_ACC5B_EN_Pos)

/* RG_SOC_GPPLL_DDSMIN register */
#define VC_ANA_RG_SOC_GPPLL_DDSMIN_Pos          0
#define VC_ANA_RG_SOC_GPPLL_DDSMIN_Msk          (0x3FFFFFFUL << VC_ANA_RG_SOC_GPPLL_DDSMIN_Pos)

/* RG_SOC_GPPLL_OFFSETIN register */
#define VC_ANA_RG_SOC_GPPLL_OFFSETIN_Pos        0
#define VC_ANA_RG_SOC_GPPLL_OFFSETIN_Msk        (0x7FUL << VC_ANA_RG_SOC_GPPLL_OFFSETIN_Pos)

/* RG_SOC_GPPLL_TESTIN register */
#define VC_ANA_RG_SOC_GPPLL_TESTIN_Pos          0
#define VC_ANA_RG_SOC_GPPLL_TESTIN_Msk          (0x3FFFFFFUL << VC_ANA_RG_SOC_GPPLL_TESTIN_Pos)

/* RG_SOC_GPPLL_PROBE register */
#define VC_ANA_RG_SOC_GPPLL_PROBE_Pos           0
#define VC_ANA_RG_SOC_GPPLL_PROBE_Msk           (0xFFFFFFUL << VC_ANA_RG_SOC_GPPLL_PROBE_Pos)

/* RG_SOC_GPPLL_METER_CTRL register */
#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_EN_Pos           0
#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_EN_Msk           (1UL << VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_EN_Pos)

#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_WIN_Pos             1
#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_WIN_Msk             (0x3UL << VC_ANA_RG_SOC_GPPLL_METER_CTRL_WIN_Pos)

#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_BINARYMODE_Pos   3
#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_BINARYMODE_Msk   (1UL << VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_BINARYMODE_Pos)

#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_MANUALSEL_Pos    4
#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_MANUALSEL_Msk    (1UL << VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_MANUALSEL_Pos)

#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_MANU_IBAND_Pos      5
#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_MANU_IBAND_Msk      (0xFUL << VC_ANA_RG_SOC_GPPLL_METER_CTRL_MANU_IBAND_Pos)

#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_PLL_WAIT_TIME_Pos   11
#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_PLL_WAIT_TIME_Msk   (0x7FUL << VC_ANA_RG_SOC_GPPLL_METER_CTRL_PLL_WAIT_TIME_Pos)

#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_FNPLL_IBAND_RST_Pos 18
#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_FNPLL_IBAND_RST_Msk (1UL << VC_ANA_RG_SOC_GPPLL_METER_CTRL_FNPLL_IBAND_RST_Pos)

#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_DONE_Pos         19
#define VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_DONE_Msk         (1UL << VC_ANA_RG_SOC_GPPLL_METER_CTRL_FM_DONE_Pos)

/* ========================================================================= */
/* ============                       RTC                       ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t SEC;                 /* (0x0000) RTC second register */
  __IOM uint32_t MIN;                 /* (0x0004) RTC minute register */
  __IOM uint32_t HOUR;                /* (0x0008) RTC hour register */
  __IOM uint32_t DAY;                 /* (0x000C) RTC day register */
  __IOM uint32_t WEEK;                /* (0x0010) RTC week register */
  __IOM uint32_t MON;                 /* (0x0014) RTC month register */
  __IOM uint32_t YEAR;                /* (0x0018) RTC year register */
  __IM uint32_t  RESERVED;
  __IOM uint32_t WKUSEC;              /* (0x0020) RTC wake-up second register */
  __IOM uint32_t WKUMIN;              /* (0x0024) RTC wake-up minute register */
  __IOM uint32_t WKUHOUR;             /* (0x0028) RTC wake-up hour register */
  __IOM uint32_t WKUCNT;              /* (0x002C) RTC wake-up counter register */
  __IOM uint32_t CAL;                 /* (0x0030) RTC calibration register */
  __IM uint32_t  RESERVED1[2];
  __IOM uint32_t ITV;                 /* (0x003C) RTC wake-up interval control */
  __IOM uint32_t SITV;                /* (0x0040) RTC wake-up second interval control */
  __IOM uint32_t PWD;                 /* (0x0044) RTC password control register */
  __IOM uint32_t CE;                  /* (0x0048) RTC write enable control register */
  __IOM uint32_t LOAD;                /* (0x004C) RTC read enable control register */
  __IOM uint32_t INTSTS;              /* (0x0050) RTC interrupt status control register */
  __IOM uint32_t INTEN;               /* (0x0054) RTC interrupt enable control register */
  __IOM uint32_t PSCA;                /* (0x0058) RTC clock pre-scaler control register */
} VC_RTC_TypeDef;

/* RTC_WKUSEC register */
#define VC_RTC_WKUSEC_WKUSEC_Pos                0
#define VC_RTC_WKUSEC_WKUSEC_Msk                (0x3FUL << VC_RTC_WKUSEC_WKUSEC_Pos)

/* RTC_WKUMIN register */
#define VC_RTC_WKUMIN_WKUMIN_Pos                0
#define VC_RTC_WKUMIN_WKUMIN_Msk                (0x3FUL << VC_RTC_WKUMIN_WKUMIN_Pos)

/* RTC_WKUHOUR register */
#define VC_RTC_WKUHOUR_WKUHOUR_Pos              0
#define VC_RTC_WKUHOUR_WKUHOUR_Msk              (0x1FUL << VC_RTC_WKUHOUR_WKUHOUR_Pos)

/* RTC_WKUCNT register */
#define VC_RTC_WKUCNT_WKUCNT_Pos                0
#define VC_RTC_WKUCNT_WKUCNT_Msk                (0xFFFFFFUL << VC_RTC_WKUCNT_WKUCNT_Pos)

#define VC_RTC_WKUCNT_CNTSEL_Pos                24
#define VC_RTC_WKUCNT_CNTSEL_Msk                (0x3UL << VC_RTC_WKUCNT_CNTSEL_Pos)

/* RTC_CAL register */
#define VC_RTC_CAL_CAL_Pos                      0
#define VC_RTC_CAL_CAL_Msk                      (0x3FFFUL << VC_RTC_CAL_CAL_Pos)

/* RTC_DIV register */
#define VC_RTC_DIV_RTCDIV_Pos                   0
#define VC_RTC_DIV_RTCDIV_Msk                   (0x3FFFFFFUL << VC_RTC_DIV_RTCDIV_Pos)

/* RTC_CTL register */
#define VC_RTC_CTL_MODE_Pos                     0
#define VC_RTC_CTL_MODE_Msk                     (0x3UL << VC_RTC_CTL_MODE_Pos)

/* RTC_ITV register */
#define VC_RTC_ITV_ITV_Pos                      0
#define VC_RTC_ITV_ITV_Msk                      (0x7UL << VC_RTC_ITV_ITV_Pos)

/* RTC_SITV register */
#define VC_RTC_SITV_SITV_Pos                    0
#define VC_RTC_SITV_SITV_Msk                    (0x3FUL << VC_RTC_SITV_SITV_Pos)

#define VC_RTC_SITV_SITVEN_Pos                  6
#define VC_RTC_SITV_SITVEN_Msk                  (1UL << VC_RTC_SITV_SITVEN_Pos)

/* RTC_PWD register */
#define VC_RTC_PWD_PWDEN_Pos                    0
#define VC_RTC_PWD_PWDEN_Msk                    (1UL << VC_RTC_PWD_PWDEN_Pos)

/* RTC_CE register */
#define VC_RTC_CE_CE_Pos                        0
#define VC_RTC_CE_CE_Msk                        (1UL << VC_RTC_CE_CE_Pos)

#define VC_RTC_CE_BSY_Pos                       1
#define VC_RTC_CE_BSY_Msk                       (1UL << VC_RTC_CE_BSY_Pos)

/* RTC_LOAD register */
#define VC_RTC_LOAD_LOAD_Pos                    0
#define VC_RTC_LOAD_LOAD_Msk                    (0xFFFFFFFFUL << VC_RTC_LOAD_LOAD_Pos)

/* RTC_INTSTS register */
#define VC_RTC_INTSTS_INTSTS0_Pos               0
#define VC_RTC_INTSTS_INTSTS0_Msk               (1UL << VC_RTC_INTSTS_INTSTS0_Pos)

#define VC_RTC_INTSTS_INTSTS1_Pos               1
#define VC_RTC_INTSTS_INTSTS1_Msk               (1UL << VC_RTC_INTSTS_INTSTS1_Pos)

#define VC_RTC_INTSTS_INTSTS2_Pos               2
#define VC_RTC_INTSTS_INTSTS2_Msk               (1UL << VC_RTC_INTSTS_INTSTS2_Pos)

#define VC_RTC_INTSTS_INTSTS3_Pos               3
#define VC_RTC_INTSTS_INTSTS3_Msk               (1UL << VC_RTC_INTSTS_INTSTS3_Pos)

#define VC_RTC_INTSTS_INTSTS4_Pos               4
#define VC_RTC_INTSTS_INTSTS4_Msk               (1UL << VC_RTC_INTSTS_INTSTS4_Pos)

#define VC_RTC_INTSTS_INTSTS5_Pos               5
#define VC_RTC_INTSTS_INTSTS5_Msk               (1UL << VC_RTC_INTSTS_INTSTS5_Pos)

#define VC_RTC_INTSTS_INTSTS6_Pos               6
#define VC_RTC_INTSTS_INTSTS6_Msk               (1UL << VC_RTC_INTSTS_INTSTS6_Pos)

#define VC_RTC_INTSTS_INTSTS7_Pos               7
#define VC_RTC_INTSTS_INTSTS7_Msk               (1UL << VC_RTC_INTSTS_INTSTS7_Pos)

#define VC_RTC_INTSTS_INTSTS8_Pos               8
#define VC_RTC_INTSTS_INTSTS8_Msk               (1UL << VC_RTC_INTSTS_INTSTS8_Pos)

#define VC_RTC_INTSTS_ACBSY_Pos                 9
#define VC_RTC_INTSTS_ACBSY_Msk                 (1UL << VC_RTC_INTSTS_ACBSY_Pos)

#define VC_RTC_INTSTS_INTSTS10_Pos              10
#define VC_RTC_INTSTS_INTSTS10_Msk              (1UL << VC_RTC_INTSTS_INTSTS10_Pos)

/* RTC_INTEN register */
#define VC_RTC_INTEN_INTEN0_Pos                 0
#define VC_RTC_INTEN_INTEN0_Msk                 (1UL << VC_RTC_INTEN_INTEN0_Pos)

#define VC_RTC_INTEN_INTEN1_Pos                 1
#define VC_RTC_INTEN_INTEN1_Msk                 (1UL << VC_RTC_INTEN_INTEN1_Pos)

#define VC_RTC_INTEN_INTEN2_Pos                 2
#define VC_RTC_INTEN_INTEN2_Msk                 (1UL << VC_RTC_INTEN_INTEN2_Pos)

#define VC_RTC_INTEN_INTEN3_Pos                 3
#define VC_RTC_INTEN_INTEN3_Msk                 (1UL << VC_RTC_INTEN_INTEN3_Pos)

#define VC_RTC_INTEN_INTEN4_Pos                 4
#define VC_RTC_INTEN_INTEN4_Msk                 (1UL << VC_RTC_INTEN_INTEN4_Pos)

#define VC_RTC_INTEN_INTEN5_Pos                 5
#define VC_RTC_INTEN_INTEN5_Msk                 (1UL << VC_RTC_INTEN_INTEN5_Pos)

#define VC_RTC_INTEN_INTEN6_Pos                 6
#define VC_RTC_INTEN_INTEN6_Msk                 (1UL << VC_RTC_INTEN_INTEN6_Pos)

#define VC_RTC_INTEN_INTEN7_Pos                 7
#define VC_RTC_INTEN_INTEN7_Msk                 (1UL << VC_RTC_INTEN_INTEN7_Pos)

#define VC_RTC_INTEN_INTEN8_Pos                 8
#define VC_RTC_INTEN_INTEN8_Msk                 (1UL << VC_RTC_INTEN_INTEN8_Pos)

#define VC_RTC_INTEN_INTEN10_Pos                10
#define VC_RTC_INTEN_INTEN10_Msk                (1UL << VC_RTC_INTEN_INTEN10_Pos)

/* RTC_PSCA register */
#define VC_RTC_PSCA_PSCA_Pos                    0
#define VC_RTC_PSCA_PSCA_Msk                    (0x3UL << VC_RTC_PSCA_PSCA_Pos)

/* ========================================================================= */
/* ============                     Memory                      ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t FLASH_CMD;           /* (0x0000) Flash controller command register */
  __IOM uint32_t FLASH_ADDR;          /* (0x0004) Flash  controller address register */
  __IOM uint32_t FLASH_CFG;           /* (0x0008) Flash controller configuration register */
  __IOM uint32_t FLASH_CACHE;         /* (0x000C) Flash controller cache configuration register */
  __IM uint32_t  FLASH_SR;            /* (0x0010) Flash controller SPI flash status register */
  __IM uint32_t  FLASH_ID;            /* (0x0014) Flash controller SPI flash ID register */
  __IM uint32_t  FLASH_CACHEHIT;      /* (0x0018) Flash cache hit rate counting register */
  __IOM uint32_t SPISRAM_CFG;         /* (0x001C) SPI SRAM controller configuration register */
  __IOM uint32_t INVADDR_S;           /* (0x0020) Invalid/flush cache start address */
  __IOM uint32_t INVADDR_E;           /* (0x0024) Invalid/flush cache end address */
  __IOM uint32_t CACHE_INV;           /* (0x0028) Invalid cache control register */
  __IOM uint32_t CACHE_FLUSH;         /* (0x002C) Flush cache control register */
  __IM uint32_t  RESERVED[52];
  __IOM uint32_t FLASH_BUFx[64];      /* (0x0100) - (0x01FC) Flash controller read/write buffer 0 - 63 */
} VC_MEM_TypeDef;

/* FLASH_CMD Register */
#define VC_MEM_FLASH_CMD_CMDID_Pos              0
#define VC_MEM_FLASH_CMD_CMDID_Msk              (0xFFUL << VC_MEM_FLASH_CMD_CMDID_Pos)

#define VC_MEM_FLASH_CMD_CMDDATA_Pos            8
#define VC_MEM_FLASH_CMD_CMDDATA_Msk            (1UL << VC_MEM_FLASH_CMD_CMDDATA_Pos)

#define VC_MEM_FLASH_CMD_CMDWR_Pos              9
#define VC_MEM_FLASH_CMD_CMDWR_Msk              (1UL << VC_MEM_FLASH_CMD_CMDWR_Pos)

#define VC_MEM_FLASH_CMD_CMDADDR_Pos            10
#define VC_MEM_FLASH_CMD_CMDADDR_Msk            (1UL << VC_MEM_FLASH_CMD_CMDADDR_Pos)

#define VC_MEM_FLASH_CMD_CMDADDR4_Pos           11
#define VC_MEM_FLASH_CMD_CMDADDR4_Msk           (1UL << VC_MEM_FLASH_CMD_CMDADDR4_Pos)

#define VC_MEM_FLASH_CMD_CMDMODE_Pos            12
#define VC_MEM_FLASH_CMD_CMDMODE_Msk            (0x7UL << VC_MEM_FLASH_CMD_CMDMODE_Pos)

#define VC_MEM_FLASH_CMD_LENGTH_Pos             16
#define VC_MEM_FLASH_CMD_LENGTH_Msk             (0xFFUL << VC_MEM_FLASH_CMD_LENGTH_Pos)

#define VC_MEM_FLASH_CMD_POLL_Pos               24
#define VC_MEM_FLASH_CMD_POLL_Msk               (1UL << VC_MEM_FLASH_CMD_POLL_Pos)

#define VC_MEM_FLASH_CMD_ACT_Pos                31
#define VC_MEM_FLASH_CMD_ACT_Msk                (1UL << VC_MEM_FLASH_CMD_ACT_Pos)

/* FLASH_ADDR register */
#define VC_MEM_FLASH_ADDR_Pos                   0
#define VC_MEM_FLASH_ADDR_Msk                   (0xFFFFFFFFUL << VC_MEM_FLASH_ADDR_Pos)

/* FLASH_CFG register */
#define VC_MEM_FLASH_CFG_CMDCLK_Pos             0
#define VC_MEM_FLASH_CFG_CMDCLK_Msk             (0xFUL << VC_MEM_FLASH_CFG_CMDCLK_Pos)

#define VC_MEM_FLASH_CFG_MEMCLK_Pos             4
#define VC_MEM_FLASH_CFG_MEMCLK_Msk             (0xFUL << VC_MEM_FLASH_CFG_MEMCLK_Pos)

#define VC_MEM_FLASH_CFG_SIZE_Pos               8
#define VC_MEM_FLASH_CFG_SIZE_Msk               (0x7UL << VC_MEM_FLASH_CFG_SIZE_Pos)

#define VC_MEM_FLASH_CFG_MEMMODE_Pos            12
#define VC_MEM_FLASH_CFG_MEMMODE_Msk            (0x7UL << VC_MEM_FLASH_CFG_MEMMODE_Pos)

#define VC_MEM_FLASH_CFG_CMDLAT_Pos             16
#define VC_MEM_FLASH_CFG_CMDLAT_Msk             (0x3UL << VC_MEM_FLASH_CFG_CMDLAT_Pos)

#define VC_MEM_FLASH_CFG_MEMLAT_Pos             18
#define VC_MEM_FLASH_CFG_MEMLAT_Msk             (0x3UL << VC_MEM_FLASH_CFG_MEMLAT_Pos)

#define VC_MEM_FLASH_CFG_TYPE_Pos               20
#define VC_MEM_FLASH_CFG_TYPE_Msk               (1UL << VC_MEM_FLASH_CFG_TYPE_Pos)

#define VC_MEM_FLASH_CFG_PERFENHC_Pos           21
#define VC_MEM_FLASH_CFG_PERFENHC_Msk           (1UL << VC_MEM_FLASH_CFG_PERFENHC_Pos)

#define VC_MEM_FLASH_CFG_MEMADDR4_Pos           23
#define VC_MEM_FLASH_CFG_MEMADDR4_Msk           (1UL << VC_MEM_FLASH_CFG_MEMADDR4_Pos)

/* FLASH_CACHE register */
#define VC_MEM_FLASH_CACHE_EN_Pos               0
#define VC_MEM_FLASH_CACHE_EN_Msk               (1UL << VC_MEM_FLASH_CACHE_EN_Pos)

#define VC_MEM_FLASH_CACHE_SIZE_Pos             1
#define VC_MEM_FLASH_CACHE_SIZE_Msk             (1UL << VC_MEM_FLASH_CACHE_SIZE_Pos)

#define VC_MEM_FLASH_CACHE_HITEN_Pos            2
#define VC_MEM_FLASH_CACHE_HITEN_Msk            (1UL << VC_MEM_FLASH_CACHE_HITEN_Pos)

#define VC_MEM_FLASH_CACHE_WB_Pos               3
#define VC_MEM_FLASH_CACHE_WB_Msk               (1UL << VC_MEM_FLASH_CACHE_WB_Pos)

/* FLASH_SR register */
#define VC_MEM_FLASH_SR_Pos                     0
#define VC_MEM_FLASH_SR_Msk                     (0xFFUL << VC_MEM_FLASH_SR_Pos)

#define VC_MEM_FLASH_SR_WIP_Pos                 0
#define VC_MEM_FLASH_SR_WIP_Msk                 (1UL << VC_MEM_FLASH_SR_WIP_Pos)

#define VC_MEM_FLASH_SR_WEL_Pos                 1
#define VC_MEM_FLASH_SR_WEL_Msk                 (1UL << VC_MEM_FLASH_SR_WEL_Pos)

#define VC_MEM_FLASH_SR_BP0_Pos                 2
#define VC_MEM_FLASH_SR_BP0_Msk                 (1UL << VC_MEM_FLASH_SR_BP0_Pos)

#define VC_MEM_FLASH_SR_BP1_Pos                 3
#define VC_MEM_FLASH_SR_BP1_Msk                 (1UL << VC_MEM_FLASH_SR_BP1_Pos)

#define VC_MEM_FLASH_SR_BP2_Pos                 4
#define VC_MEM_FLASH_SR_BP2_Msk                 (1UL << VC_MEM_FLASH_SR_BP2_Pos)

#define VC_MEM_FLASH_SR_BP3_Pos                 5
#define VC_MEM_FLASH_SR_BP3_Msk                 (1UL << VC_MEM_FLASH_SR_BP3_Pos)

#define VC_MEM_FLASH_SR_BP4_Pos                 6
#define VC_MEM_FLASH_SR_BP4_Msk                 (1UL << VC_MEM_FLASH_SR_BP4_Pos)

#define VC_MEM_FLASH_SR_SRP0_Pos                7
#define VC_MEM_FLASH_SR_SRP0_Msk                (1UL << VC_MEM_FLASH_SR_SRP0_Pos)

/* FLASH_CACHEHIT register */
#define VC_MEM_FLASH_CACHEHIT_HITRATE_Pos       0
#define VC_MEM_FLASH_CACHEHIT_HITRATE_Msk       (0xFFFFUL << VC_MEM_FLASH_CACHEHIT_HITRATE_Pos)

/* FLASH_ID register */
#define VC_MEM_FLASH_ID_DEV_ID_Pos              0
#define VC_MEM_FLASH_ID_DEV_ID_Msk              (0xFFFFUL << VC_MEM_FLASH_ID_DEV_ID_Pos)

#define VC_MEM_FLASH_ID_MANU_ID_Pos             16
#define VC_MEM_FLASH_ID_MANU_ID_Msk             (0xFFUL << VC_MEM_FLASH_ID_MANU_ID_Pos)

/* SPISRAM_CFG register */
#define VC_MEM_SPISRAM_CFG_SRAMEN_Pos           0
#define VC_MEM_SPISRAM_CFG_SRAMEN_Msk           (1UL << VC_MEM_SPISRAM_CFG_SRAMEN_Pos)

#define VC_MEM_SPISRAM_CFG_PSRAMEN_Pos          2
#define VC_MEM_SPISRAM_CFG_PSRAMEN_Msk          (1UL << VC_MEM_SPISRAM_CFG_PSRAMEN_Pos)

#define VC_MEM_SPISRAM_CFG_SRAMCLK_Pos          4
#define VC_MEM_SPISRAM_CFG_SRAMCLK_Msk          (0xFUL << VC_MEM_SPISRAM_CFG_SRAMCLK_Pos)

#define VC_MEM_SPISRAM_CFG_SRAMSIZE_Pos         8
#define VC_MEM_SPISRAM_CFG_SRAMSIZE_Msk         (0x7UL << VC_MEM_SPISRAM_CFG_SRAMSIZE_Pos)

#define VC_MEM_SPISRAM_CFG_SRAMMODE_Pos         12
#define VC_MEM_SPISRAM_CFG_SRAMMODE_Msk         (0x7UL << VC_MEM_SPISRAM_CFG_SRAMMODE_Pos)

#define VC_MEM_SPISRAM_CFG_SRAMLAT_Pos          18
#define VC_MEM_SPISRAM_CFG_SRAMLAT_Msk          (0x3UL << VC_MEM_SPISRAM_CFG_SRAMLAT_Pos)

#define VC_MEM_SPISRAM_CFG_SRAMADDR4_Pos        23
#define VC_MEM_SPISRAM_CFG_SRAMADDR4_Msk        (1UL << VC_MEM_SPISRAM_CFG_SRAMADDR4_Pos)

/* INVADDR_S register */
#define VC_MEM_INVADDR_S_Pos                    0
#define VC_MEM_INVADDR_S_Msk                    (0x1FFFFFFUL << VC_MEM_INVADDR_S_Pos)

#define VC_MEM_INVADDR_E_Pos                    0
#define VC_MEM_INVADDR_E_Msk                    (0x1FFFFFFUL << VC_MEM_INVADDR_E_Pos)

/* CACHE_INV register */
#define VC_MEM_CACHE_INV_Pos                    0
#define VC_MEM_CACHE_INV_Msk                    (0xFFFFFFFFUL << VC_MEM_CACHE_INV_Pos)

/* CACHE_FLUSH register */
#define VC_MEM_CACHE_FLUSH_Pos                  0
#define VC_MEM_CACHE_FLUSH_Msk                  (0xFFFFFFFFUL << VC_MEM_CACHE_FLUSH_Pos)

/* ========================================================================= */
/* ============                      GPIO                       ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t OEN;
  __IOM uint32_t IE;
  __IOM uint32_t DAT;
  __IOM uint32_t ATT;
} VC_GPIO_TypeDef;

typedef struct
{
  __IOM uint32_t OEN;                 /* (0x0010) IOA output enable register */
  __IOM uint32_t IE;                  /* (0x0014) IOA input enable register */
  __IOM uint32_t DAT;                 /* (0x0018) IOA data register */
  __IOM uint32_t ATT;                 /* (0x001C) IOA attribute register */
  __IOM uint32_t WKUEN;               /* (0x0020) IOA wake-up enable register */
  __IM uint32_t  STS;                 /* (0x0024) IOA status register */
  __IOM uint32_t INT;                 /* (0x0028) IOA interrupt status register */
  __IM uint32_t  RESERVED[9];
  __IOM uint32_t NODEG;               /* (0x0050) IOA no-deglitch control register */
  __IOM uint32_t SEL0;                /* (0x0054) IOA special function select register 0 */
  __IOM uint32_t SEL1;                /* (0x0058) IOA special function select register 1 */
} VC_GPIOA_TypeDef;

typedef struct
{
  __IOM uint32_t OEN;                 /* (0x0040) IOB output enable register */
  __IOM uint32_t IE;                  /* (0x0044) IOB input enable register */
  __IOM uint32_t DAT;                 /* (0x0048) IOB data register */
  __IOM uint32_t ATT;                 /* (0x004C) IOB attribute register */
  __IM uint32_t  STS;                 /* (0x0050) IOB input status register */
  __IOM uint32_t SEL0;                /* (0x0054) IOB special function select register 0 */
  __IOM uint32_t SEL1;                /* (0x0058) IOB special function select register 1 */
  __IM uint32_t  RESERVED[3];
  __IOM uint32_t DR;                  /* (0x0068) IOB driving strength register */
} VC_GPIOB_TypeDef;

typedef struct
{
  __IOM uint32_t OEN;                 /* (0x0080) IOC output enable register */
  __IOM uint32_t IE;                  /* (0x0084) IOC input enable register */
  __IOM uint32_t DAT;                 /* (0x0088) IOC data register */
  __IOM uint32_t ATT;                 /* (0x008C) IOC attribute register */
  __IM uint32_t  STS;                 /* (0x0090) IOC input status register */
  __IOM uint32_t SEL;                 /* (0x0094) IOC special function select register */
  __IM uint32_t  RESERVED[4];
  __IOM uint32_t DR;                  /* (0x00A8) IOC driving strength register */
  __IOM uint32_t WKUEN;               /* (0x00AC) IOC wake-up enable register */
  __IOM uint32_t INT;                 /* (0x00B0) IOC interrupt status register */
} VC_GPIOC_TypeDef;

typedef struct
{
  __IOM uint32_t OEN;                 /* (0x00C0) IOD output enable register */
  __IOM uint32_t IE;                  /* (0x00C4) IOD input enable register */
  __IOM uint32_t DAT;                 /* (0x00C8) IOD data register */
  __IOM uint32_t ATT;                 /* (0x00CC) IOD attribute register */
  __IM uint32_t  STS;                 /* (0x00D0) IOD input status register */
  __IOM uint32_t SEL;                 /* (0x00D4) IOD special function select register */
  __IM uint32_t  RESERVED[4];
  __IOM uint32_t DR;                  /* (0x00E8) IOD driving strength register */
} VC_GPIOD_TypeDef;

typedef struct
{
  __IOM uint32_t OEN;                 /* (0x0100) IOE output enable register */
  __IOM uint32_t IE;                  /* (0x0104) IOE input enable register */
  __IOM uint32_t DAT;                 /* (0x0108) IOE data register */
  __IOM uint32_t ATT;                 /* (0x010C) IOE attribute register */
  __IM uint32_t  STS;                 /* (0x0110) IOE input status register */
  __IOM uint32_t SEL;                 /* (0x0114) IOE special function select register */
  __IM uint32_t  RESERVED[5];
  __IOM uint32_t DR;                  /* (0x012C) IOE driving strength register */
} VC_GPIOE_TypeDef;

typedef struct
{
  __IOM uint32_t MISC;                /* (0x0200) IO misc. control register */
  __IOM uint32_t MISC2;               /* (0x0204) IO misc2. control register */
} VC_GPIOMISC_TypeDef;

/* GPIO_IOX_OEN register */
#define VC_GPIO_IOX_OEN_IOXOEN_Msk(pin)         (1UL << pin)
#define VC_GPIO_IOX_OEN_IOXOEN_Disabled(pin)    (1UL << pin) /* Disable IO's output function */
#define VC_GPIO_IOX_OEN_IOXOEN_Enabled(pin)     (0UL << pin) /* Enable IO's output function */

/* GPIO_IOX_IE register */
#define VC_GPIO_IOX_IE_IOXIE_Msk(pin)           (1UL << pin)
#define VC_GPIO_IOX_IE_IOXIE_Disabled(pin)      (0UL << pin) /* Disable IO's input function */
#define VC_GPIO_IOX_IE_IOXIE_Enabled(pin)       (1UL << pin) /* Enable IO's input function */

/* GPIO_IOX_DAT register */
#define VC_GPIO_IOX_DAT_IOXDAT_Msk(pin)         (1UL << pin)
#define VC_GPIO_IOX_DAT_IOXDAT_Disabled(pin)    (0UL << pin)
#define VC_GPIO_IOX_DAT_IOXDAT_Enabled(pin)     (1UL << pin)

/* GPIO_IOX_ATT register */
#define VC_GPIO_IOX_ATT_IOXATT_Msk(pin)         (1UL << pin)
#define VC_GPIO_IOX_ATT_IOXATT_CMOS(pin)        (0UL << pin)
#define VC_GPIO_IOX_ATT_IOXATT_OPEN_DRAIN(pin)  (1UL << pin)

/* GPIO_IOX_STS register */
#define VC_GPIO_IOX_STS_IOXSTS_Msk(pin)         (1UL << pin)

/* GPIO_IOX_DR register */
#define VC_GPIO_IOX_STS_IOXSTS_Msk(pin)         (1UL << pin)
#define VC_GPIO_IOX_STS_IOXSTS_MIN_4mA(pin)     (0UL << pin)
#define VC_GPIO_IOX_STS_IOXSTS_MIN_8mA(pin)     (1UL << pin)

/* GPIO_IOX_INT register */
#define VC_GPIO_IOX_INT_IOXINT_Msk(pin)         (1UL << pin)

/* GPIO_IOA_SEL0 register */
#define VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(pin)      (4UL * pin)
#define VC_GPIO_IOA_SEL0_IOAx_SEL_Msk(pin)      (0x7UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(pin))

/* GPIO_IOA_SEL1 register */
#define VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(pin)      (4UL * (pin - 8))
#define VC_GPIO_IOA_SEL1_IOAx_SEL_Msk(pin)      (0x7UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(pin))

/* GPIO_IOB_SEL0 register */
#define VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(pin)      (4UL * pin)
#define VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(pin)      (0x7UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(pin))

/* GPIO_IOB_SEL1 register */
#define VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(pin)      (4UL * (pin - 8))
#define VC_GPIO_IOB_SEL1_IOBx_SEL_Msk(pin)      (0x7UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(pin))

/* GPIO_IOC_SEL register */
#define VC_GPIO_IOC_SEL_IOCx_SEL_Pos(pin)       (2UL * pin)
#define VC_GPIO_IOC_SEL_IOCx_SEL_Msk(pin)       (0x3UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(pin))

/* GPIO_IOD_SEL register */
#define VC_GPIO_IOD_SEL_IODx_SEL_Pos(pin)       (2UL * pin)
#define VC_GPIO_IOD_SEL_IODx_SEL_Msk(pin)       (0x3UL << VC_GPIO_IOD_SEL_IODx_SEL_Pos(pin))

/* GPIO_IOE_SEL register */
#define VC_GPIO_IOE_SEL_IOEx_SEL_Pos(pin)       (2UL * pin)
#define VC_GPIO_IOE_SEL_IOEx_SEL_Msk(pin)       (0x3UL << VC_GPIO_IOE_SEL_IOEx_SEL_Pos(pin))

/* GPIO_IO_MISC register */
#define VC_GPIO_IO_MISC_I2CIOC_Pos              5
#define VC_GPIO_IO_MISC_I2CIOC_Msk              (1UL << VC_GPIO_IO_MISC_I2CIOC_Pos)

#define VC_GPIO_IO_MISC_FSPI_MUX_Pos            6
#define VC_GPIO_IO_MISC_FSPI_MUX_Msk            (0x3UL << VC_GPIO_IO_MISC_FSPI_MUX_Pos)

#define VC_GPIO_IO_MISC_I2CIOB1_Pos             12
#define VC_GPIO_IO_MISC_I2CIOB1_Msk             (1UL << VC_GPIO_IO_MISC_I2C1OB1_Pos)

#define VC_GPIO_IO_MISC_I2CIOC1_Pos             13
#define VC_GPIO_IO_MISC_I2CIOC1_Msk             (1UL << VC_GPIO_IO_MISC_I2CIOC1_Pos)

#define VC_GPIO_IO_MISC_ANATEST_Pos             14
#define VC_GPIO_IO_MISC_ANATEST_Msk             (0x3UL << VC_GPIO_IO_MISC_ANATEST_Pos)

/* GPIO_IO_MISC2 register */
#define VC_GPIO_IO_MISC2_PROBE0_SEL_Pos         0
#define VC_GPIO_IO_MISC2_PROBE0_SEL_Msk         (0x7UL << VC_GPIO_IO_MISC2_PROBE0_SEL_Pos)

#define VC_GPIO_IO_MISC2_PROBE0_EN_Pos          3
#define VC_GPIO_IO_MISC2_PROBE0_EN_Msk          (1UL << VC_GPIO_IO_MISC2_PROBE0_EN_Pos)

#define VC_GPIO_IO_MISC2_PROBE1_SEL_Pos         4
#define VC_GPIO_IO_MISC2_PROBE1_SEL_Msk         (0x7UL << VC_GPIO_IO_MISC2_PROBE1_SEL_Pos)

#define VC_GPIO_IO_MISC2_PROBE1_EN_Pos          7
#define VC_GPIO_IO_MISC2_PROBE1_EN_Msk          (1UL << VC_GPIO_IO_MISC2_PROBE1_EN_Pos)

#define VC_GPIO_IO_MISC2_PROBE2_SEL_Pos         8
#define VC_GPIO_IO_MISC2_PROBE2_SEL_Msk         (0x7UL << VC_GPIO_IO_MISC2_PROBE2_SEL_Pos)

#define VC_GPIO_IO_MISC2_PROBE2_EN_Pos          11
#define VC_GPIO_IO_MISC2_PROBE2_EN_Msk          (1UL << VC_GPIO_IO_MISC2_PROBE2_EN_Pos)

#define VC_GPIO_IO_MISC2_PROBE3_SEL_Pos         12
#define VC_GPIO_IO_MISC2_PROBE3_SEL_Msk         (0x7UL << VC_GPIO_IO_MISC2_PROBE3_SEL_Pos)

#define VC_GPIO_IO_MISC2_PROBE3_EN_Pos          15
#define VC_GPIO_IO_MISC2_PROBE3_EN_Msk          (1UL << VC_GPIO_IO_MISC2_PROBE3_EN_Pos)

#define VC_GPIO_IO_MISC2_PROBE4_SEL_Pos         16
#define VC_GPIO_IO_MISC2_PROBE4_SEL_Msk         (0x7UL << VC_GPIO_IO_MISC2_PROBE4_SEL_Pos)

#define VC_GPIO_IO_MISC2_PROBE4_EN_Pos          19
#define VC_GPIO_IO_MISC2_PROBE4_EN_Msk          (1UL << VC_GPIO_IO_MISC2_PROBE4_EN_Pos)

#define VC_GPIO_IO_MISC2_PROBE_GRP_Pos          20
#define VC_GPIO_IO_MISC2_PROBE_GRP_Msk          (0x7UL << VC_GPIO_IO_MISC2_PROBE_GRP_Pos)

/* GPIO EINTx wakeup signal */
#define VC_GPIO_IOx_WKUEN_Pos(pin)              (2UL * pin)
#define VC_GPIO_IOx_WKUEN_Msk(pin)              (0x3UL << VC_GPIO_IOx_WKUEN_Pos(pin))

/* Special Function IOA */
#define VC_GPIO_SEL0_IOAx_GPIO(pin)             (0UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(pin))
#define VC_GPIO_SEL0_IOAx_EINTx(pin)            (2UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(pin))

#define VC_GPIO_SEL1_IOAx_GPIO(pin)             (0UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(pin))
#define VC_GPIO_SEL1_IOAx_EINTx(pin)            (2UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(pin))

#define VC_GPIO_SEL0_IOA0_SPI3_CLK              (5UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(0))
#define VC_GPIO_SEL0_IOA0_FSPI_WPN              (6UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(0))

#define VC_GPIO_SEL0_IOA1_FSPI_HOLDN            (6UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(1))

#define VC_GPIO_SEL0_IOA2_SPI3_MOSI_SWAP0       (5UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(2))
#define VC_GPIO_SEL0_IOA2_SPI3_MISO_SWAP1       (5UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(2))
#define VC_GPIO_SEL0_IOA2_FSPI_MOSI             (6UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(2))

#define VC_GPIO_SEL0_IOA3_SPI3_MISO_SWAP0       (5UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(3))
#define VC_GPIO_SEL0_IOA3_SPI3_MOSI_SWAP1       (5UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(3))
#define VC_GPIO_SEL0_IOA3_FSPI_MISO             (6UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(3))

#define VC_GPIO_SEL0_IOA4_SCANIN0               (4UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(4))
#define VC_GPIO_SEL0_IOA4_SPI3_CSN              (5UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(4))
#define VC_GPIO_SEL0_IOA4_FSPI_RAMCSN           (6UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(4))

#define VC_GPIO_SEL0_IOA5_SCANIN1               (4UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(5))

#define VC_GPIO_SEL0_IOA6_SCANIN2               (4UL << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(6))

#define VC_GPIO_SEL1_IOA12_UART0_RX             (3UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(12))
#define VC_GPIO_SEL1_IOA12_SCANIN3              (4UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(12))

#define VC_GPIO_SEL1_IOA13_UART1_RX             (3UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(13))
#define VC_GPIO_SEL1_IOA13_ISO7816_RX0          (4UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(13))

#define VC_GPIO_SEL1_IOA14_UART2_RX             (3UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(14))

#define VC_GPIO_SEL1_IOA15_UART3_RX             (3UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(15))
#define VC_GPIO_SEL1_IOA15_ISO7816_RX1          (4UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(15))
#define VC_GPIO_SEL1_IOA15_RMII_MDIO            (5UL << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(15))

/* Special Function IOB */
#define VC_GPIO_SEL0_IOBx_GPIO(pin)             (0UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(pin))
#define VC_GPIO_SEL1_IOBx_GPIO(pin)             (0UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(pin))

#define VC_GPIO_SEL0_IOB0_PWM0                  (2UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(0))
#define VC_GPIO_SEL0_IOB0_UART4_RX              (3UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(0))
#define VC_GPIO_SEL0_IOB0_XTALO                 (5UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(0))

#define VC_GPIO_SEL0_IOB1_UART5_RX              (3UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(1))
#define VC_GPIO_SEL0_IOB1_FSPI_WPN              (5UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(1))
#define VC_GPIO_SEL0_IOB1_SD_DAT1               (6UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(1))

#define VC_GPIO_SEL0_IOB2_UART0_TX              (3UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(2))

#define VC_GPIO_SEL0_IOB3_UART1_TX              (3UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(3))
#define VC_GPIO_SEL0_IOB3_ISO7816_CLK0          (4UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(3))

#define VC_GPIO_SEL0_IOB4_UART2_TX              (3UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(4))

#define VC_GPIO_SEL0_IOB5_RMII_MDC              (2UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(5))
#define VC_GPIO_SEL0_IOB5_UART3_TX              (3UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(5))
#define VC_GPIO_SEL0_IOB5_ISO7816_CLK1          (4UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(5))

#define VC_GPIO_SEL0_IOB6_PWM1                  (2UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(6))
#define VC_GPIO_SEL0_IOB6_UART4_TX              (3UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(6))
#define VC_GPIO_SEL0_IOB6_RTCLK                 (4UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(6))
#define VC_GPIO_SEL0_IOB6_XTALO                 (5UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(6))
#define VC_GPIO_SEL0_IOB6_SDCMD                 (6UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(6))

#define VC_GPIO_SEL0_IOB7_UART5_TX              (3UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(7))
#define VC_GPIO_SEL0_IOB7_FSPI_HOLDN            (5UL << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(7))

#define VC_GPIO_SEL1_IOB8_RMII_REFCLK           (2UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(8))
#define VC_GPIO_SEL1_IOB8_UART6_TX              (3UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(8))
#define VC_GPIO_SEL1_IOB8_SCANOUT0              (4UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(8))
#define VC_GPIO_SEL1_IOB8_FSPI_RAMCSN           (5UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(8))

#define VC_GPIO_SEL1_IOB9_SPI1_CSN              (2UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(9))
#define VC_GPIO_SEL1_IOB9_FSPI_CSN              (5UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(9))

#define VC_GPIO_SEL1_IOB10_SPI1_CLK             (2UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(10))
#define VC_GPIO_SEL1_IOB10_FSPI_CLK             (5UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(10))
#define VC_GPIO_SEL1_IOB10_SD_CLK               (6UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(10))

#define VC_GPIO_SEL1_IOB11_SPI1_MISO_SWAP0      (2UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(11))
#define VC_GPIO_SEL1_IOB11_SPI1_MOSI_SWAP1      (2UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(11))
#define VC_GPIO_SEL1_IOB11_FSPI_MISO            (5UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(11))
#define VC_GPIO_SEL1_IOB11_SD_DAT0              (6UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(11))

#define VC_GPIO_SEL1_IOB12_SPI1_MOSI_SWAP0      (2UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(12))
#define VC_GPIO_SEL1_IOB12_SPI1_MISO_SWAP1      (2UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(12))
#define VC_GPIO_SEL1_IOB12_FSPI_MOSI            (5UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(12))
#define VC_GPIO_SEL1_IOB12_SD_CMD               (6UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(12))

#define VC_GPIO_SEL1_IOB13_PWM2                 (2UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(13))
#define VC_GPIO_SEL1_IOB13_I2C1_SCL_I2CIOC0     (3UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(13))
#define VC_GPIO_SEL1_IOB13_SCANOUT1             (4UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(13))
#define VC_GPIO_SEL1_IOB13_XTALO                (5UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(13))
#define VC_GPIO_SEL1_IOB13_SD_DAT2              (6UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(13))

#define VC_GPIO_SEL1_IOB14_PWM3                 (2UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(14))
#define VC_GPIO_SEL1_IOB14_I2C1_SDA_I2CIOC0     (3UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(14))
#define VC_GPIO_SEL1_IOB14_SCANOUT2             (4UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(14))
#define VC_GPIO_SEL1_IOB14_XTALO                (5UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(14))

#define VC_GPIO_SEL1_IOB15_TIM_EXT_CLK          (2UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(15))
#define VC_GPIO_SEL1_IOB15_UART6_RX             (3UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(15))
#define VC_GPIO_SEL1_IOB15_SCANOUT3             (4UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(15))
#define VC_GPIO_SEL1_IOB15_FSPI_CSN             (5UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(15))
#define VC_GPIO_SEL1_IOB15_SD_DAT3              (6UL << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(15))

/* Special Function IOC */
#define VC_GPIO_SEL_IOCx_GPIO(pin)              (0UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(pin))

#define VC_GPIO_SEL_IOC0_SPI2_CSN               (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(0))

#define VC_GPIO_SEL_IOC1_SPI2_CLK               (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(1))

#define VC_GPIO_SEL_IOC2_SPI2_MISO_SWAP0        (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(2))
#define VC_GPIO_SEL_IOC2_SPI2_MOSI_SWAP1        (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(2))

#define VC_GPIO_SEL_IOC3_SPI2_MOSI_SWAP0        (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(3))
#define VC_GPIO_SEL_IOC3_SPI2_MISO_SWAP1        (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(3))

#define VC_GPIO_SEL_IOC4_I2C2_SCL               (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(4))
#define VC_GPIO_SEL_IOC4_I2C1_SCL_I2CIOC1       (3UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(4))

#define VC_GPIO_SEL_IOC5_I2C2_SDA               (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(5))
#define VC_GPIO_SEL_IOC5_I2C1_SDA_I2CIOC1       (3UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(5))

#define VC_GPIO_SEL_IOC6_RMII_CRSDV             (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(6))

#define VC_GPIO_SEL_IOC7_RMII_RX0               (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(7))

#define VC_GPIO_SEL_IOC9_SPI1_CSN_1             (3UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(9))

#define VC_GPIO_SEL_IOC10_SPI1_CSN_3            (3UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(10))

#define VC_GPIO_SEL_IOC11_SPI1_CSN_2            (3UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(11))

#define VC_GPIO_SEL_IOC12_RMII_RX1              (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(12))

#define VC_GPIO_SEL_IOC13_RMII_TX0              (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(13))

#define VC_GPIO_SEL_IOC14_RMII_TX1              (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(14))

#define VC_GPIO_SEL_IOC15_RMII_TXEN             (2UL << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(15))

/* Special Function IOD */
#define VC_GPIO_SEL_IODx_GPIO(pin)              (0UL << VC_GPIO_IOD_SEL_IODx_SEL_Pos(pin))

/* Special Function IOE */
#define VC_GPIO_SEL_IOEx_GPIO(pin)              (0UL << VC_GPIO_IOE_SEL_IOEx_SEL_Pos(pin))

#define VC_GPIO_SEL_IOE2_FSPI_CLK               (3UL << VC_GPIO_IOE_SEL_IOEx_SEL_Pos(2))

#define VC_GPIO_SEL_IOE4_FSPI_CLK               (3UL << VC_GPIO_IOE_SEL_IOEx_SEL_Pos(4))

/* ========================================================================= */
/* ============                       DMA                       ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t IE;                  /* (0x0000) DMA interrupt enable register */
  __IOM uint32_t STS;                 /* (0x0004) DMA status register */
  __IM uint32_t  RESERVED[2];
  __IOM uint32_t C0CTL;               /* (0x0010) DMA channel 0 control register */
  __IOM uint32_t C0SRC;               /* (0x0014) DMA channel 0 source register */
  __IOM uint32_t C0DST;               /* (0x0018) DMA channel 0 destination register */
  __IM uint32_t  C0LEN;               /* (0x001C) DMA channel 0 transfer length register */
  __IOM uint32_t C1CTL;               /* (0x0020) DMA channel 1 control register */
  __IOM uint32_t C1SRC;               /* (0x0024) DMA channel 1 source register */
  __IOM uint32_t C1DST;               /* (0x0028) DMA channel 1 destination register */
  __IM uint32_t  C1LEN;               /* (0x002C) DMA channel 1 transfer length register */
  __IOM uint32_t C2CTL;               /* (0x0030) DMA channel 2 control register */
  __IOM uint32_t C2SRC;               /* (0x0034) DMA channel 2 source register */
  __IOM uint32_t C2DST;               /* (0x0038) DMA channel 2 destination register */
  __IM uint32_t  C2LEN;               /* (0x003C) DMA channel 2 transfer length register */
  __IOM uint32_t C3CTL;               /* (0x0040) DMA channel 3 control register */
  __IOM uint32_t C3SRC;               /* (0x0044) DMA channel 3 source register */
  __IOM uint32_t C3DST;               /* (0x0048) DMA channel 3 destination register */
  __IM uint32_t  C3LEN;               /* (0x004C) DMA channel 3 transfer length register */
  __IOM uint32_t C4CTL;               /* (0x0050) DMA channel 4 control register */
  __IOM uint32_t C4SRC;               /* (0x0054) DMA channel 4 source register */
  __IOM uint32_t C4DST;               /* (0x0058) DMA channel 4 destination register */
  __IM uint32_t  C4LEN;               /* (0x005C) DMA channel 4 transfer length register */
  __IOM uint32_t C5CTL;               /* (0x0060) DMA channel 5 control register */
  __IOM uint32_t C5SRC;               /* (0x0064) DMA channel 5 source register */
  __IOM uint32_t C5DST;               /* (0x0068) DMA channel 5 destination register */
  __IM uint32_t  C5LEN;               /* (0x006C) DMA channel 5 transfer length register */
  __IOM uint32_t C6CTL;               /* (0x0070) DMA channel 6 control register */
  __IOM uint32_t C6SRC;               /* (0x0074) DMA channel 6 source register */
  __IOM uint32_t C6DST;               /* (0x0078) DMA channel 6 destination register */
  __IM uint32_t  C6LEN;               /* (0x007C) DMA channel 6 transfer length register */
  __IOM uint32_t C7CTL;               /* (0x0080) DMA channel 7 control register */
  __IOM uint32_t C7SRC;               /* (0x0084) DMA channel 7 source register */
  __IOM uint32_t C7DST;               /* (0x0088) DMA channel 7 destination register */
  __IM uint32_t  C7LEN;               /* (0x008C) DMA channel 7 transfer length register */
} VC_DMA_TypeDef;

/* DMA_IE register */
#define VC_DMA_IE_C0PEIE_Pos                    0
#define VC_DMA_IE_C0PEIE_Msk                    (1UL << VC_DMA_IE_C0PEIE_Pos)

#define VC_DMA_IE_C1PEIE_Pos                    1
#define VC_DMA_IE_C1PEIE_Msk                    (1UL << VC_DMA_IE_C1PEIE_Pos)

#define VC_DMA_IE_C2PEIE_Pos                    2
#define VC_DMA_IE_C2PEIE_Msk                    (1UL << VC_DMA_IE_C2PEIE_Pos)

#define VC_DMA_IE_C3PEIE_Pos                    3
#define VC_DMA_IE_C3PEIE_Msk                    (1UL << VC_DMA_IE_C3PEIE_Pos)

#define VC_DMA_IE_C0FEIE_Pos                    4
#define VC_DMA_IE_C0FEIE_Msk                    (1UL << VC_DMA_IE_C0FEIE_Pos)

#define VC_DMA_IE_C1FEIE_Pos                    5
#define VC_DMA_IE_C1FEIE_Msk                    (1UL << VC_DMA_IE_C1FEIE_Pos)

#define VC_DMA_IE_C2FEIE_Pos                    6
#define VC_DMA_IE_C2FEIE_Msk                    (1UL << VC_DMA_IE_C2FEIE_Pos)

#define VC_DMA_IE_C3FEIE_Pos                    7
#define VC_DMA_IE_C3FEIE_Msk                    (1UL << VC_DMA_IE_C3FEIE_Pos)

#define VC_DMA_IE_C0DAIE_Pos                    8
#define VC_DMA_IE_C0DAIE_Msk                    (1UL << VC_DMA_IE_C0DAIE_Pos)

#define VC_DMA_IE_C1DAIE_Pos                    9
#define VC_DMA_IE_C1DAIE_Msk                    (1UL << VC_DMA_IE_C1DAIE_Pos)

#define VC_DMA_IE_C2DAIE_Pos                    10
#define VC_DMA_IE_C2DAIE_Msk                    (1UL << VC_DMA_IE_C2DAIE_Pos)

#define VC_DMA_IE_C3DAIE_Pos                    11
#define VC_DMA_IE_C3DAIE_Msk                    (1UL << VC_DMA_IE_C3DAIE_Pos)

#define VC_DMA_IE_C4PEIE_Pos                    16
#define VC_DMA_IE_C4PEIE_Msk                    (1UL << VC_DMA_IE_C4PEIE_Pos)

#define VC_DMA_IE_C5PEIE_Pos                    17
#define VC_DMA_IE_C5PEIE_Msk                    (1UL << VC_DMA_IE_C5PEIE_Pos)

#define VC_DMA_IE_C6PEIE_Pos                    18
#define VC_DMA_IE_C6PEIE_Msk                    (1UL << VC_DMA_IE_C6PEIE_Pos)

#define VC_DMA_IE_C7PEIE_Pos                    19
#define VC_DMA_IE_C7PEIE_Msk                    (1UL << VC_DMA_IE_C7PEIE_Pos)

#define VC_DMA_IE_C4FEIE_Pos                    20
#define VC_DMA_IE_C4FEIE_Msk                    (1UL << VC_DMA_IE_C4FEIE_Pos)

#define VC_DMA_IE_C5FEIE_Pos                    21
#define VC_DMA_IE_C5FEIE_Msk                    (1UL << VC_DMA_IE_C5FEIE_Pos)

#define VC_DMA_IE_C6FEIE_Pos                    22
#define VC_DMA_IE_C6FEIE_Msk                    (1UL << VC_DMA_IE_C6FEIE_Pos)

#define VC_DMA_IE_C7FEIE_Pos                    23
#define VC_DMA_IE_C7FEIE_Msk                    (1UL << VC_DMA_IE_C7FEIE_Pos)

#define VC_DMA_IE_D4DAIE_Pos                    24
#define VC_DMA_IE_D4DAIE_Msk                    (1UL << VC_DMA_IE_D4DAIE_Pos)

#define VC_DMA_IE_D5DAIE_Pos                    25
#define VC_DMA_IE_D5DAIE_Msk                    (1UL << VC_DMA_IE_D5DAIE_Pos)

#define VC_DMA_IE_D6DAIE_Pos                    26
#define VC_DMA_IE_D6DAIE_Msk                    (1UL << VC_DMA_IE_D6DAIE_Pos)

#define VC_DMA_IE_D7DAIE_Pos                    27
#define VC_DMA_IE_D7DAIE_Msk                    (1UL << VC_DMA_IE_D7DAIE_Pos)

/* DMA_STS register */
#define VC_DMA_STS_C0BUSY_Pos                   0
#define VC_DMA_STS_C0BUSY_Msk                   (1UL << VC_DMA_STS_C0BUSY_Pos)

#define VC_DMA_STS_C1BUSY_Pos                   1
#define VC_DMA_STS_C1BUSY_Msk                   (1UL << VC_DMA_STS_C1BUSY_Pos)

#define VC_DMA_STS_C2BUSY_Pos                   2
#define VC_DMA_STS_C2BUSY_Msk                   (1UL << VC_DMA_STS_C2BUSY_Pos)

#define VC_DMA_STS_C3BUSY_Pos                   3
#define VC_DMA_STS_C3BUSY_Msk                   (1UL << VC_DMA_STS_C3BUSY_Pos)

#define VC_DMA_STS_C0PE_Pos                     4
#define VC_DMA_STS_C0PE_Msk                     (1UL << VC_DMA_STS_C0PE_Pos)

#define VC_DMA_STS_C1PE_Pos                     5
#define VC_DMA_STS_C1PE_Msk                     (1UL << VC_DMA_STS_C1PE_Pos)

#define VC_DMA_STS_C2PE_Pos                     6
#define VC_DMA_STS_C2PE_Msk                     (1UL << VC_DMA_STS_C2PE_Pos)

#define VC_DMA_STS_C3PE_Pos                     7
#define VC_DMA_STS_C3PE_Msk                     (1UL << VC_DMA_STS_C3PE_Pos)

#define VC_DMA_STS_C0FE_Pos                     8
#define VC_DMA_STS_C0FE_Msk                     (1UL << VC_DMA_STS_C0FE_Pos)

#define VC_DMA_STS_C1FE_Pos                     9
#define VC_DMA_STS_C1FE_Msk                     (1UL << VC_DMA_STS_C1FE_Pos)

#define VC_DMA_STS_C2FE_Pos                     10
#define VC_DMA_STS_C2FE_Msk                     (1UL << VC_DMA_STS_C2FE_Pos)

#define VC_DMA_STS_C3FE_Pos                     11
#define VC_DMA_STS_C3FE_Msk                     (1UL << VC_DMA_STS_C3FE_Pos)

#define VC_DMA_STS_C0DA_Pos                     12
#define VC_DMA_STS_C0DA_Msk                     (1UL << VC_DMA_STS_C0DA_Pos)

#define VC_DMA_STS_C1DA_Pos                     13
#define VC_DMA_STS_C1DA_Msk                     (1UL << VC_DMA_STS_C1DA_Pos)

#define VC_DMA_STS_C2DA_Pos                     14
#define VC_DMA_STS_C2DA_Msk                     (1UL << VC_DMA_STS_C2DA_Pos)

#define VC_DMA_STS_C3DA_Pos                     15
#define VC_DMA_STS_C3DA_Msk                     (1UL << VC_DMA_STS_C3DA_Pos)

#define VC_DMA_STS_C4BUSY_Pos                   16
#define VC_DMA_STS_C4BUSY_Msk                   (1UL << VC_DMA_STS_C4BUSY_Pos)

#define VC_DMA_STS_C5BUSY_Pos                   17
#define VC_DMA_STS_C5BUSY_Msk                   (1UL << VC_DMA_STS_C5BUSY_Pos)

#define VC_DMA_STS_C6BUSY_Pos                   18
#define VC_DMA_STS_C6BUSY_Msk                   (1UL << VC_DMA_STS_C6BUSY_Pos)

#define VC_DMA_STS_C7BUSY_Pos                   19
#define VC_DMA_STS_C7BUSY_Msk                   (1UL << VC_DMA_STS_C7BUSY_Pos)

#define VC_DMA_STS_C4PE_Pos                     20
#define VC_DMA_STS_C4PE_Msk                     (1UL << VC_DMA_STS_C4PE_Pos)

#define VC_DMA_STS_C5PE_Pos                     21
#define VC_DMA_STS_C5PE_Msk                     (1UL << VC_DMA_STS_C5PE_Pos)

#define VC_DMA_STS_C6PE_Pos                     22
#define VC_DMA_STS_C6PE_Msk                     (1UL << VC_DMA_STS_C6PE_Pos)

#define VC_DMA_STS_C7PE_Pos                     23
#define VC_DMA_STS_C7PE_Msk                     (1UL << VC_DMA_STS_C7PE_Pos)

#define VC_DMA_STS_C4FE_Pos                     24
#define VC_DMA_STS_C4FE_Msk                     (1UL << VC_DMA_STS_C4FE_Pos)

#define VC_DMA_STS_C5FE_Pos                     25
#define VC_DMA_STS_C5FE_Msk                     (1UL << VC_DMA_STS_C5FE_Pos)

#define VC_DMA_STS_C6FE_Pos                     26
#define VC_DMA_STS_C6FE_Msk                     (1UL << VC_DMA_STS_C6FE_Pos)

#define VC_DMA_STS_C7FE_Pos                     27
#define VC_DMA_STS_C7FE_Msk                     (1UL << VC_DMA_STS_C7FE_Pos)

#define VC_DMA_STS_C4DA_Pos                     28
#define VC_DMA_STS_C4DA_Msk                     (1UL << VC_DMA_STS_C4DA_Pos)

#define VC_DMA_STS_C5DA_Pos                     29
#define VC_DMA_STS_C5DA_Msk                     (1UL << VC_DMA_STS_C5DA_Pos)

#define VC_DMA_STS_C6DA_Pos                     30
#define VC_DMA_STS_C6DA_Msk                     (1UL << VC_DMA_STS_C6DA_Pos)

#define VC_DMA_STS_C7DA_Pos                     31
#define VC_DMA_STS_C7DA_Msk                     (1UL << VC_DMA_STS_C7DA_Pos)

/* DMA_CxCTL register */
#define VC_DMA_CxCTL_EN_Pos                     0
#define VC_DMA_CxCTL_EN_Msk                     (1UL << VC_DMA_CxCTL_EN_Pos)

#define VC_DMA_CxCTL_SIZE_Pos                   1
#define VC_DMA_CxCTL_SIZE_Msk                   (0x3UL << VC_DMA_CxCTL_SIZE_Pos)

#define VC_DMA_CxCTL_SMODE_Pos                  3
#define VC_DMA_CxCTL_SMODE_Msk                  (0x3UL << VC_DMA_CxCTL_SMODE_Pos)

#define VC_DMA_CxCTL_DMODE_Pos                  5
#define VC_DMA_CxCTL_DMODE_Msk                  (0x3UL << VC_DMA_CxCTL_DMODE_Pos)

#define VC_DMA_CxCTL_SEQ_MODE_Pos               7
#define VC_DMA_CxCTL_SEQ_MODE_Msk               (1UL << VC_DMA_CxCTL_SEQ_MODE_Pos)

#define VC_DMA_CxCTL_TMODE_Pos                  12
#define VC_DMA_CxCTL_TMODE_Msk                  (1UL << VC_DMA_CxCTL_TMODE_Pos)

#define VC_DMA_CxCTL_CONT_Pos                   13
#define VC_DMA_CxCTL_CONT_Msk                   (1UL << VC_DMA_CxCTL_CONT_Pos)

#define VC_DMA_CxCTL_STOP_Pos                   15
#define VC_DMA_CxCTL_STOP_Msk                   (1UL << VC_DMA_CxCTL_STOP_Pos)

#define VC_DMA_CxCTL_DMASEL_Pos                 16
#define VC_DMA_CxCTL_DMASEL_Msk                 (0x3FUL << VC_DMA_CxCTL_DMASEL_Pos)

#define VC_DMA_CxCTL_DMASEL_SOFT1               (0UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART0_TX            (2UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART0_RX            (3UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART1_TX            (4UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART1_RX            (5UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART2_TX            (6UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART2_RX            (7UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART3_TX            (8UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART3_RX            (9UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART4_TX            (10UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART4_RX            (11UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART5_TX            (12UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART5_RX            (13UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART6_TX            (14UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART6_RX            (15UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART32K0            (16UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_UART32K1            (17UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ISO78160_TX         (18UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ISO78160_RX         (19UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ISO78161_TX         (20UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ISO78161_RX         (21UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_TIMER0              (22UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_TIMER1              (23UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_TIMER2              (24UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_TIMER3              (25UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_SPI1_TX             (26UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_SPI1_RX             (27UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_SPI2_TX             (28UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_SPI2_RX             (29UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_SPI3_TX             (30UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_SPI3_RX             (31UL << VC_DMA_CxCTL_DMASEL_Pos)

#define VC_DMA_CxCTL_DMASEL_SOFT2               (32UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA            (40UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA0           (41UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA1           (42UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA2           (43UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA3           (44UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA4           (45UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA5           (46UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA6           (47UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA7           (48UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA8           (49UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA9           (50UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA10          (51UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA11          (52UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA12          (53UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA13          (54UL << VC_DMA_CxCTL_DMASEL_Pos)
#define VC_DMA_CxCTL_DMASEL_ADC_DATA14          (55UL << VC_DMA_CxCTL_DMASEL_Pos)

/* DMA_CxSRC register */
#define VC_DMA_CxSRC_SRC_Pos                    0
#define VC_DMA_CxSRC_SRC_Msk                    (0xFFFFFFFFUL << VC_DMA_CxSRC_SRC_Pos)

/* DMA_CxDST register */
#define VC_DMA_CxDST_DST_Pos                    0
#define VC_DMA_CxDST_DST_Msk                    (0xFFFFFFFFUL << VC_DMA_CxDST_DST_Pos)

/* DMA_CxLEN register */
#define VC_DMA_CxLEN_PLEN_Pos                   0
#define VC_DMA_CxLEN_PLEN_Msk                   (0xFFUL << VC_DMA_CxLEN_PLEN_Pos)

#define VC_DMA_CxLEN_FLEN_Pos                   8
#define VC_DMA_CxLEN_FLEN_Msk                   (0xFFUL << VC_DMA_CxLEN_FLEN_Pos)

#define VC_DMA_CxLEN_CPLEN_Pos                  16
#define VC_DMA_CxLEN_CPLEN_Msk                  (0xFFUL << VC_DMA_CxLEN_CPLEN_Pos)

#define VC_DMA_CxLEN_CFLEN_Pos                  24
#define VC_DMA_CxLEN_CFLEN_Msk                  (0xFFUL << VC_DMA_CxLEN_CFLEN_Pos)


/* ========================================================================= */
/* ============                      UART                       ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t DATA;                /* (0x0000) UART data register */
  __IOM uint32_t STATE;               /* (0x0004) UART status register */
  __IOM uint32_t CTRL;                /* (0x0008) UART control register */
  __IOM uint32_t INTSTS;              /* (0x000C) UART interrupt status register */
  __IOM uint32_t BAUDDIV;             /* (0x0010) UART baudrate divide register */
  __IOM uint32_t CTRL2;               /* (0x0014) UART control regiser 2 */
  __IOM uint32_t DUTY;                /* (0x0018) UART IR carrier duty control register */
  __IOM uint32_t FIFOCTRL;            /* (0x001C) UART FIFO control register */
  __IM uint32_t  FIFOSTS;             /* (0x0020) UART FIFO status register */
  __IM uint32_t  TFIFOSTS;            /* (0x0024) UART transmit FIFO status */
} VC_UART_TypeDef;

typedef struct
{
  __IOM uint32_t GFIFOCTRL;           /* (0x0000) UART global FIFO control */
} VC_UART_GFIFO_TypeDef;

/* UART_DATA register */
#define VC_UART_DATA_DATA_Pos                   0
#define VC_UART_DATA_DATA_Msk                   (0xFFUL << VC_UART_DATA_DATA_Pos)

#define VC_UART_DATA_PE_Pos                     8
#define VC_UART_DATA_PE_Msk                     (1UL << VC_UART_DATA_PE_Pos)

/* UART_STATE register */
#define VC_UART_STATE_TXFULL_Pos                0
#define VC_UART_STATE_TXFULL_Msk                (1UL << VC_UART_STATE_TXFULL_Pos)

#define VC_UART_STATE_RXHFULL_Pos               1
#define VC_UART_STATE_RXHFULL_Msk               (1UL << VC_UART_STATE_RXHFULL_Pos)

#define VC_UART_STATE_TXOV_Pos                  2
#define VC_UART_STATE_TXOV_Msk                  (1UL << VC_UART_STATE_TXOV_Pos)

#define VC_UART_STATE_RXOV_Pos                  3
#define VC_UART_STATE_RXOV_Msk                  (1UL << VC_UART_STATE_RXOV_Pos)

#define VC_UART_STATE_RXPE_Pos                  4
#define VC_UART_STATE_RXPE_Msk                  (1UL << VC_UART_STATE_RXPE_Pos)

#define VC_UART_STATE_TXDONE_Pos                5
#define VC_UART_STATE_TXDONE_Msk                (1UL << VC_UART_STATE_TXDONE_Pos)

#define VC_UART_STATE_RXPSTS_Pos                6
#define VC_UART_STATE_RXPSTS_Msk                (1UL << VC_UART_STATE_RXPSTS_Pos)

/* UART_CTRL register */
#define VC_UART_CTRL_TXEN_Pos                   0
#define VC_UART_CTRL_TXEN_Msk                   (1UL << VC_UART_CTRL_TXEN_Pos)

#define VC_UART_CTRL_RXEN_Pos                   1
#define VC_UART_CTRL_RXEN_Msk                   (1UL << VC_UART_CTRL_RXEN_Pos)

#define VC_UART_CTRL_TXIE_Pos                   2
#define VC_UART_CTRL_TXIE_Msk                   (1UL << VC_UART_CTRL_TXIE_Pos)

#define VC_UART_CTRL_RXIE_Pos                   3
#define VC_UART_CTRL_RXIE_Msk                   (1UL << VC_UART_CTRL_RXIE_Pos)

#define VC_UART_CTRL_TXOVIE_Pos                 4
#define VC_UART_CTRL_TXOVIE_Msk                 (1UL << VC_UART_CTRL_TXOVIE_Pos)

#define VC_UART_CTRL_RXOVIE_Pos                 5
#define VC_UART_CTRL_RXOVIE_Msk                 (1UL << VC_UART_CTRL_RXOVIE_Pos)

#define VC_UART_CTRL_TEST_Pos                   6
#define VC_UART_CTRL_TEST_Msk                   (1UL << VC_UART_CTRL_TEST_Pos)

#define VC_UART_CTRL_RXPEIE_Pos                 7
#define VC_UART_CTRL_RXPEIE_Msk                 (1UL << VC_UART_CTRL_RXPEIE_Pos)

#define VC_UART_CTRL_TXDONEIE_Pos               8
#define VC_UART_CTRL_TXDONEIE_Msk               (1UL << VC_UART_CTRL_TXDONEIE_Pos)

/* UART_INTSTS register */
#define VC_UART_INTSTS_TXIF_Pos                 0
#define VC_UART_INTSTS_TXIF_Msk                 (1UL << VC_UART_INTSTS_TXIF_Pos)

#define VC_UART_INTSTS_RXIF_Pos                 1
#define VC_UART_INTSTS_RXIF_Msk                 (1UL << VC_UART_INTSTS_RXIF_Pos)

#define VC_UART_INTSTS_TXOVIF_Pos               2
#define VC_UART_INTSTS_TXOVIF_Msk               (1UL << VC_UART_INTSTS_TXOVIF_Pos)

#define VC_UART_INTSTS_RXOVIF_Pos               3
#define VC_UART_INTSTS_RXOVIF_Msk               (1UL << VC_UART_INTSTS_RXOVIF_Pos)

#define VC_UART_INTSTS_RXPEIF_Pos               4
#define VC_UART_INTSTS_RXPEIF_Msk               (1UL << VC_UART_INTSTS_RXPEIF_Pos)

#define VC_UART_INTSTS_TXDONEIF_Pos             5
#define VC_UART_INTSTS_TXDONEIF_Msk             (1UL << VC_UART_INTSTS_TXDONEIF_Pos)

/* UART_BAUDDIV register */
#define VC_UART_BAUDDIV_BAUDDIV_Pos             0
#define VC_UART_BAUDDIV_BAUDDIV_Msk             (0xFFFFFUL << VC_UART_BAUDDIV_BAUDDIV_Pos)

/* UART_CTRL2 register */
#define VC_UART_CTRL2_MSB_Pos                   0
#define VC_UART_CTRL2_MSB_Msk                   (1UL << VC_UART_CTRL2_MSB_Pos)

#define VC_UART_CTRL2_PEN_Pos                   1
#define VC_UART_CTRL2_PEN_Msk                   (1UL << VC_UART_CTRL2_PEN_Pos)

#define VC_UART_CTRL2_PMODE_Pos                 2
#define VC_UART_CTRL2_PMODE_Msk                 (0x3UL << VC_UART_CTRL2_PMODE_Pos)

#define VC_UART_CTRL2_LENGTH_Pos                4
#define VC_UART_CTRL2_LENGTH_Msk                (1UL << VC_UART_CTRL2_LENGTH_Pos)

#define VC_UART_CTRL2_STOPLEN_Pos               5
#define VC_UART_CTRL2_STOPLEN_Msk               (1UL << VC_UART_CTRL2_STOPLEN_Pos)

#define VC_UART_CTRL2_IREN_Pos                  6
#define VC_UART_CTRL2_IREN_Msk                  (1UL << VC_UART_CTRL2_IREN_Pos)

/* UART_DUTY register */
#define VC_UART_DUTY_DUTYL_Pos                  0
#define VC_UART_DUTY_DUTYL_Msk                  (0xFFFFUL << VC_UART_DUTY_DUTYL_Pos)

#define VC_UART_DUTY_DUTYH_Pos                  16
#define VC_UART_DUTY_DUTYH_Msk                  (0xFFFFUL << VC_UART_DUTY_DUTYH_Pos)

/* UART_FIFOCTRL register */
#define VC_UART_FIFOCTRL_RXFIFOLVL_Pos          0
#define VC_UART_FIFOCTRL_RXFIFOLVL_Msk          (0x7UL << VC_UART_FIFOCTRL_RXFIFOLVL_Pos)

#define VC_UART_FIFOCTRL_TXFIFOLVL_Pos          4
#define VC_UART_FIFOCTRL_TXFIFOLVL_Msk          (0x7UL << VC_UART_FIFOCTRL_TXFIFOLVL_Pos)

#define VC_UART_FIFOCTRL_OVMODE_Pos             14
#define VC_UART_FIFOCTRL_OVMODE_Msk             (1UL << VC_UART_FIFOCTRL_OVMODE_Pos)

#define VC_UART_FIFOCTRL_SFTRST_Pos             15
#define VC_UART_FIFOCTRL_SFTRST_Msk             (1UL << VC_UART_FIFOCTRL_SFTRST_Pos)

/* UART_FIFOSTS register - when doesn't use global fifo */
#define VC_UART_GFIFO0_FIFOSTS_RXFIFOLAST_Pos          0
#define VC_UART_GFIFO0_FIFOSTS_RXFIFOLAST_Msk          (0xFUL << VC_UART_GFIFO0_FIFOSTS_RXFIFOLAST_Pos)

#define VC_UART_GFIFO0_FIFOSTS_RXFIFOHEMPTY_Pos        4
#define VC_UART_GFIFO0_FIFOSTS_RXFIFOHEMPTY_Msk        (1UL << VC_UART_GFIFO0_FIFOSTS_RXFIFOHEMPTY_Pos)

#define VC_UART_GFIFO0_FIFOSTS_RXFIFOEMPTY_Pos         5
#define VC_UART_GFIFO0_FIFOSTS_RXFIFOEMPTY_Msk         (1UL << VC_UART_GFIFO0_FIFOSTS_RXFIFOEMPTY_Pos)

#define VC_UART_GFIFO0_FIFOSTS_RXFIFOHFULL_Pos         6
#define VC_UART_GFIFO0_FIFOSTS_RXFIFOHFULL_Msk         (1UL << VC_UART_GFIFO0_FIFOSTS_RXFIFOHFULL_Pos)

#define VC_UART_GFIFO0_FIFOSTS_RXFIFOFULL_Pos          7
#define VC_UART_GFIFO0_FIFOSTS_RXFIFOFULL_Msk          (1UL << VC_UART_GFIFO0_FIFOSTS_RXFIFOFULL_Pos)

#define VC_UART_GFIFO0_FIFOSTS_TXFIFOLAST_Pos          8
#define VC_UART_GFIFO0_FIFOSTS_TXFIFOLAST_Msk          (0xFUL << VC_UART_GFIFO0_FIFOSTS_TXFIFOLAST_Pos)

#define VC_UART_GFIFO0_FIFOSTS_TXFIFOHEMPTY_Pos        12
#define VC_UART_GFIFO0_FIFOSTS_TXFIFOHEMPTY_Msk        (1UL << VC_UART_GFIFO0_FIFOSTS_TXFIFOHEMPTY_Pos)

#define VC_UART_GFIFO0_FIFOSTS_TXFIFOEMPTY_Pos         13
#define VC_UART_GFIFO0_FIFOSTS_TXFIFOEMPTY_Msk         (1UL << VC_UART_GFIFO0_FIFOSTS_TXFIFOEMPTY_Pos)

#define VC_UART_GFIFO0_FIFOSTS_TXFIFOHFULL_Pos         14
#define VC_UART_GFIFO0_FIFOSTS_TXFIFOHFULL_Msk         (1UL << VC_UART_GFIFO0_FIFOSTS_TXFIFOHFULL_Pos)

#define VC_UART_GFIFO0_FIFOSTS_TXFIFOFULL_Pos          15
#define VC_UART_GFIFO0_FIFOSTS_TXFIFOFULL_Msk          (1UL << VC_UART_GFIFO0_FIFOSTS_TXFIFOFULL_Pos)

/* UART_FIFOSTS register - when does use global fifo */
#define VC_UART_GFIFO1_FIFOSTS_RXFIFOLAST_Pos          0
#define VC_UART_GFIFO1_FIFOSTS_RXFIFOLAST_Msk          (0x7FUL << VC_UART_GFIFO1_FIFOSTS_RXFIFOLAST_Pos)

#define VC_UART_GFIFO1_FIFOSTS_RXFIFOHEMPTY_Pos        12
#define VC_UART_GFIFO1_FIFOSTS_RXFIFOHEMPTY_Msk        (1UL << VC_UART_GFIFO1_FIFOSTS_RXFIFOHEMPTY_Pos)

#define VC_UART_GFIFO1_FIFOSTS_RXFIFOEMPTY_Pos         13
#define VC_UART_GFIFO1_FIFOSTS_RXFIFOEMPTY_Msk         (1UL << VC_UART_GFIFO1_FIFOSTS_RXFIFOEMPTY_Pos)

#define VC_UART_GFIFO1_FIFOSTS_RXFIFOHFULL_Pos         14
#define VC_UART_GFIFO1_FIFOSTS_RXFIFOHFULL_Msk         (1UL << VC_UART_GFIFO1_FIFOSTS_RXFIFOHFULL_Pos)

#define VC_UART_GFIFO1_FIFOSTS_RXFIFOFULL_Pos          15
#define VC_UART_GFIFO1_FIFOSTS_RXFIFOFULL_Msk          (1UL << VC_UART_GFIFO1_FIFOSTS_RXFIFOFULL_Pos)

/* UART_TFIOSTS register */
#define VC_UART_TFIFOSTS_TXFIFOLAST_Pos         0
#define VC_UART_TFIFOSTS_TXFIFOLAST_Msk         (0xFUL << VC_UART_TFIFOSTS_TXFIFOLAST_Pos)

#define VC_UART_TFIFOSTS_TXFIFOHEMPTY_Pos       12
#define VC_UART_TFIFOSTS_TXFIFOHEMPTY_Msk       (1UL << VC_UART_TFIFOSTS_TXFIFOHEMPTY_Pos)

#define VC_UART_TFIFOSTS_TXFIFOEMPTY_Pos        13
#define VC_UART_TFIFOSTS_TXFIFOEMPTY_Msk        (1UL << VC_UART_TFIFOSTS_TXFIFOEMPTY_Pos)

#define VC_UART_TFIFOSTS_TXFIFOHFULL_Pos        14
#define VC_UART_TFIFOSTS_TXFIFOHFULL_Msk        (1UL << VC_UART_TFIFOSTS_TXFIFOHFULL_Pos)

#define VC_UART_TFIFOSTS_TXFIFOFULL_Pos         15
#define VC_UART_TFIFOSTS_TXFIFOFULL_Msk         (1UL << VC_UART_TFIFOSTS_TXFIFOFULL_Pos)

/* UART_GFIFOCTRL register */
#define VC_UART_GFIFOCTRL_GFIFOEN_Pos           0
#define VC_UART_GFIFOCTRL_GFIFOEN_Msk           (1UL << VC_UART_GFIFOCTRL_GFIFOEN_Pos)

#define VC_UART_GFIFOCTRL_GFIFORST_Pos          1
#define VC_UART_GFIFOCTRL_GFIFORST_Msk          (1UL << VC_UART_GFIFOCTRL_GFIFORST_Pos)

#define VC_UART_GFIFOCTRL_OVMODE_Pos            2
#define VC_UART_GFIFOCTRL_OVMODE_Msk            (1UL << VC_UART_GFIFOCTRL_OVMODE_Pos)

#define VC_UART_GFIFOCTRL_GFIFOSEL_Pos          4
#define VC_UART_GFIFOCTRL_GFIFOSEL_Msk          (0x7UL << VC_UART_GFIFOCTRL_GFIFOSEL_Pos)

#define VC_UART_GFIFOCTRL_GRXFIFOLVL_Pos        8
#define VC_UART_GFIFOCTRL_GRXFIFOLVL_Msk        (0x3FUL << VC_UART_GFIFOCTRL_GRXFIFOLVL_Pos)

/* ========================================================================= */
/* ============                     ISO7816                     ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t BAUDDIVL;            /* (0x0004) ISO7816 baudrate low byte register */
  __IOM uint32_t BAUDDIVH;            /* (0x0008) ISO7816 baudrate high byte register */
  __IOM uint32_t DATA;                /* (0x000C) ISO7816 data register */
  __IOM uint32_t INFO;                /* (0x0010) ISO7816 information register */
  __IOM uint32_t CFG;                 /* (0x0014) ISO7816 control register */
  __IOM uint32_t CLK;                 /* (0x0018) ISO7816 clock divider control register */
} VC_ISO7816_TypeDef;

/* ISO7816_BAUDDIVL register */
#define VC_ISO7816_BAUDDIVL_BAUDDIVL_Pos        0
#define VC_ISO7816_BAUDDIVL_BAUDDIVL_Msk        (0xFFUL << VC_ISO7816_BAUDDIVL_BAUDDIVL_Pos)

/* ISO7816_BAUDDIVH register */
#define VC_ISO7816_BAUDDIVH_BAUDDIVH_Pos        0
#define VC_ISO7816_BAUDDIVH_BAUDDIVH_Msk        (0xFFUL << VC_ISO7816_BAUDDIVH_BAUDDIVH_Pos)

/* ISO7816_DATA register */
#define VC_ISO7816_DATA_DATA_Pos                0
#define VC_ISO7816_DATA_DATA_Msk                (0xFFUL << VC_ISO7816_DATA_DATA_Pos)

/* ISO7816_INFO register */
#define VC_ISO7816_INFO_RXACK_Pos                0
#define VC_ISO7816_INFO_RXACK_Msk                (1UL << VC_ISO7816_INFO_RXACK_Pos)

#define VC_ISO7816_INFO_CHKSUM_Pos              1
#define VC_ISO7816_INFO_CHKSUM_Msk              (1UL << VC_ISO7816_INFO_CHKSUM_Pos)

#define VC_ISO7816_INFO_RXERRIF_Pos             2
#define VC_ISO7816_INFO_RXERRIF_Msk             (1UL << VC_ISO7816_INFO_RXERRIF_Pos)

#define VC_ISO7816_INFO_TXERRIF_Pos             3
#define VC_ISO7816_INFO_TXERRIF_Msk             (1UL << VC_ISO7816_INFO_TXERRIF_Pos)

#define VC_ISO7816_INFO_RXIF_Pos                5
#define VC_ISO7816_INFO_RXIF_Msk                (1UL << VC_ISO7816_INFO_RXIF_Pos)

#define VC_ISO7816_INFO_TXIF_Pos                6
#define VC_ISO7816_INFO_TXIF_Msk                (1UL << VC_ISO7816_INFO_TXIF_Pos)

#define VC_ISO7816_INFO_RXOVIF_Pos              7
#define VC_ISO7816_INFO_RXOVIF_Msk              (1UL << VC_ISO7816_INFO_RXOVIF_Pos)

#define VC_ISO7816_INFO_TXRTYERRIF_Pos          8
#define VC_ISO7816_INFO_TXRTYERRIF_Msk          (1UL << VC_ISO7816_INFO_TXRTYERRIF_Pos)

/* ISO7816_CFG register */
#define VC_ISO7816_CFG_EN_Pos                   0
#define VC_ISO7816_CFG_EN_Msk                   (1UL << VC_ISO7816_CFG_EN_Pos)

#define VC_ISO7816_CFG_CHKP_Pos                 1
#define VC_ISO7816_CFG_CHKP_Msk                 (1UL << VC_ISO7816_CFG_CHKP_Pos)

#define VC_ISO7816_CFG_RXERRIE_Pos              2
#define VC_ISO7816_CFG_RXERRIE_Msk              (1UL << VC_ISO7816_CFG_RXERRIE_Pos)

#define VC_ISO7816_CFG_TXERRIE_Pos              3
#define VC_ISO7816_CFG_TXERRIE_Msk              (1UL << VC_ISO7816_CFG_TXERRIE_Pos)

#define VC_ISO7816_CFG_ACKLEN_Pos               4
#define VC_ISO7816_CFG_ACKLEN_Msk               (1UL << VC_ISO7816_CFG_ACKLEN_Pos)

#define VC_ISO7816_CFG_RXIE_Pos                 5
#define VC_ISO7816_CFG_RXIE_Msk                 (1UL << VC_ISO7816_CFG_RXIE_Pos)

#define VC_ISO7816_CFG_TXIE_Pos                 6
#define VC_ISO7816_CFG_TXIE_Msk                 (1UL << VC_ISO7816_CFG_TXIE_Pos)

#define VC_ISO7816_CFG_RXOVIE_Pos               7
#define VC_ISO7816_CFG_RXOVIE_Msk               (1UL << VC_ISO7816_CFG_RXOVIE_Pos)

#define VC_ISO7816_CFG_TXRTYERRIE_Pos           8
#define VC_ISO7816_CFG_TXRTYERRIE_Msk           (1UL << VC_ISO7816_CFG_TXRTYERRIE_Pos)

#define VC_ISO7816_CFG_AUTORXACK_Pos            9
#define VC_ISO7816_CFG_AUTORXACK_Msk            (1UL << VC_ISO7816_CFG_AUTORXACK_Pos)

#define VC_ISO7816_CFG_AUTOTXRTY_Pos            10
#define VC_ISO7816_CFG_AUTOTXRTY_Msk            (1UL << VC_ISO7816_CFG_AUTOTXRTY_Pos)

#define VC_ISO7816_CFG_LSB_Pos                  11
#define VC_ISO7816_CFG_LSB_Msk                  (1UL << VC_ISO7816_CFG_LSB_Pos)

#define VC_ISO7816_CFG_TXRTYCNT_Pos             12
#define VC_ISO7816_CFG_TXRTYCNT_Msk             (0xFUL << VC_ISO7816_CFG_TXRTYCNT_Pos)

/* ISO7816_CLK register */
#define VC_ISO7816_CLK_CLKDIV_Pos               0
#define VC_ISO7816_CLK_CLKDIV_Msk               (0x7FUL << VC_ISO7816_CLK_CLKDIV_Pos)

/* ========================================================================= */
/* ============                   TIM (Timer)                   ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t CTRL;                /* (0x0000) Timer control register */
  __IOM uint32_t VALUE;               /* (0x0004) Timer current count register */
  __IOM uint32_t RELOAD;              /* (0x0008) Timer reload register */
  __IOM uint32_t INT;                 /* (0x000C) Timer interrupt status register */
} VC_TIM_TypeDef;

/* TMR_CTRL register */
#define VC_TIM_CTRL_EN_Pos                      0
#define VC_TIM_CTRL_EN_Msk                      (1UL << VC_TIM_CTRL_EN_Pos)

#define VC_TIM_CTRL_EXTEN_Pos                   1
#define VC_TIM_CTRL_EXTEN_Msk                   (1UL << VC_TIM_CTRL_EXTEN_Pos)

#define VC_TIM_CTRL_EXTCLK_Pos                  2
#define VC_TIM_CTRL_EXTCLK_Msk                  (1UL << VC_TIM_CTRL_EXTCLK_Pos)

#define VC_TIM_CTRL_INTEN_Pos                   3
#define VC_TIM_CTRL_INTEN_Msk                   (1UL << VC_TIM_CTRL_INTEN_Pos)

/* TMR_VALUE register */
#define VC_TIM_VALUE_VALUE_Pos                  0
#define VC_TIM_VALUE_VALUE_Msk                  (0xFFFFFFFFUL << VC_TIM_VALUE_VALUE_Pos)

/* TMR_RELOAD register */
#define VC_TIM_RELOAD_RELOAD_Pos                0
#define VC_TIM_RELOAD_RELOAD_Msk                (0xFFFFFFFFUL << VC_TIM_RELOAD_RELOAD_Pos)

/* TMR_INT register */
#define VC_TIM_INT_INT_Pos                      0
#define VC_TIM_INT_INT_Msk                      (1UL << VC_TIM_INT_INT_Pos)

/* ========================================================================= */
/* ============                       PWM                       ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t CTL;                 /* (0x0000) PWM timer control register */
  __IM uint32_t  TAR;                 /* (0x0004) PWM timer current count register */
  __IOM uint32_t CCTL[3];             /* (0x0008 - 0x0010) PWM timer compare/capture control reg 0 - 3 */
  __IOM uint32_t CCR[3];              /* (0x0014 - 0x001C) PWM timer compare/capture data reg 0 - 3 */
} VC_PWM_TypeDef;

typedef struct
{
  __IOM uint32_t O_SEL;               /* (0x0000) PWM output selection register */
  __IOM uint32_t I_SEL01;             /* (0x0004) PWM0 and PWM1's input selection register */
  __IOM uint32_t I_SEL23;             /* (0x0008) PWM2 and PWM3's input selection register */
} VC_PWMSEL_TypeDef;

/* PWM_CTL register */
#define VC_PWM_CTL_IFG_Pos                      0
#define VC_PWM_CTL_IFG_Msk                      (1UL << VC_PWM_CTL_IFG_Pos)

#define VC_PWM_CTL_IE_Pos                       1
#define VC_PWM_CTL_IE_Msk                       (1UL << VC_PWM_CTL_IE_Pos)

#define VC_PWM_CTL_CLR_Pos                      2
#define VC_PWM_CTL_CLR_Msk                      (1UL << VC_PWM_CTL_CLR_Pos)

#define VC_PWM_CTL_TSEL_Pos                     3
#define VC_PWM_CTL_TSEL_Msk                     (1UL << VC_PWM_CTL_TSEL_Pos)

#define VC_PWM_CTL_MC_Pos                       4
#define VC_PWM_CTL_MC_Msk                       (0x3UL << VC_PWM_CTL_MC_Pos)

#define VC_PWM_CTL_ID_Pos                       6
#define VC_PWM_CTL_ID_Msk                       (0x7UL << VC_PWM_CTL_ID_Pos)

/* PWM_CCTL register */
#define VC_PWM_CCTL_CCIFG_Pos                   0
#define VC_PWM_CCTL_CCIFG_Msk                   (1UL << VC_PWM_CCTL_CCIFG_Pos)

#define VC_PWM_CCTL_COV_Pos                     1
#define VC_PWM_CCTL_COV_Msk                     (1UL << VC_PWM_CCTL_COV_Pos)

#define VC_PWM_CCTL_OUT_Pos                     2
#define VC_PWM_CCTL_OUT_Msk                     (1UL << VC_PWM_CCTL_OUT_Pos)

#define VC_PWM_CCTL_CCI_Pos                     3
#define VC_PWM_CCTL_CCI_Msk                     (1UL << VC_PWM_CCTL_CCI_Pos)

#define VC_PWM_CCTL_CCIE_Pos                    4
#define VC_PWM_CCTL_CCIE_Msk                    (1UL << VC_PWM_CCTL_CCIE_Pos)

#define VC_PWM_CCTL_OUTMOD_Pos                  5
#define VC_PWM_CCTL_OUTMOD_Msk                  (0x7UL << VC_PWM_CCTL_OUTMOD_Pos)

#define VC_PWM_CCTL_CAP_Pos                     8
#define VC_PWM_CCTL_CAP_Msk                     (1UL << VC_PWM_CCTL_CAP_Pos)

#define VC_PWM_CCTL_OUTEN_Pos                   9
#define VC_PWM_CCTL_OUTEN_Msk                   (1UL << VC_PWM_CCTL_OUTEN_Pos)

#define VC_PWM_CCTL_SCCI_Pos                    10
#define VC_PWM_CCTL_SCCI_Msk                    (1UL << VC_PWM_CCTL_SCCI_Pos)

#define VC_PWM_CCTL_OUT_HRES_Pos                11
#define VC_PWM_CCTL_OUT_HRES_Msk                (1UL << VC_PWM_CCTL_OUT_HRES_Pos)

#define VC_PWM_CCTL_CM_Pos                      14
#define VC_PWM_CCTL_CM_Msk                      (0x3UL << VC_PWM_CCTL_CM_Pos)

/* PWM_CCR register */
#define VC_PWM_CCR_CCR_Pos                      0
#define VC_PWM_CCR_CCR_Msk                      (0xFFFFUL << VC_PWM_CCR_CCR_Pos)

/* PWM_O_SEL register */
#define VC_PWM_O_SEL_SEL0_Pos                   0
#define VC_PWM_O_SEL_SEL0_Msk                   (0xFUL << VC_PWM_O_SEL_SEL0_Pos)

#define VC_PWM_O_SEL_SEL1_Pos                   4
#define VC_PWM_O_SEL_SEL1_Msk                   (0xFUL << VC_PWM_O_SEL_SEL1_Pos)

#define VC_PWM_O_SEL_SEL2_Pos                   8
#define VC_PWM_O_SEL_SEL2_Msk                   (0xFUL << VC_PWM_O_SEL_SEL2_Pos)

#define VC_PWM_O_SEL_SEL3_Pos                   12
#define VC_PWM_O_SEL_SEL3_Msk                   (0xFUL << VC_PWM_O_SEL_SEL3_Pos)

/* PWM_I_SELO1 register */
#define VC_PWM_I_SELO1_SEL00_Pos                0
#define VC_PWM_I_SELO1_SEL00_Msk                (0x3UL << VC_PWM_I_SELO1_SEL00_Pos)

#define VC_PWM_I_SELO1_SEL01_Pos                2
#define VC_PWM_I_SELO1_SEL01_Msk                (0x3UL << VC_PWM_I_SELO1_SEL01_Pos)

#define VC_PWM_I_SELO1_SEL02_Pos                4
#define VC_PWM_I_SELO1_SEL02_Msk                (0x3UL << VC_PWM_I_SELO1_SEL02_Pos)

#define VC_PWM_I_SELO1_SEL10_Pos                16
#define VC_PWM_I_SELO1_SEL10_Msk                (0x3UL << VC_PWM_I_SELO1_SEL10_Pos)

#define VC_PWM_I_SELO1_SEL11_Pos                18
#define VC_PWM_I_SELO1_SEL11_Msk                (0x3UL << VC_PWM_I_SELO1_SEL11_Pos)

#define VC_PWM_I_SELO1_SEL12_Pos                20
#define VC_PWM_I_SELO1_SEL12_Msk                (0x3UL << VC_PWM_I_SELO1_SEL12_Pos)

/* PWM_I_SEL23 register */
#define VC_PWM_I_SEL23_SEL20_Pos                0
#define VC_PWM_I_SEL23_SEL20_Msk                (0x3UL << VC_PWM_I_SEL23_SEL20_Pos)

#define VC_PWM_I_SEL23_SEL21_Pos                2
#define VC_PWM_I_SEL23_SEL21_Msk                (0x3UL << VC_PWM_I_SEL23_SEL21_Pos)

#define VC_PWM_I_SEL23_SEL22_Pos                4
#define VC_PWM_I_SEL23_SEL22_Msk                (0x3UL << VC_PWM_I_SEL23_SEL22_Pos)

#define VC_PWM_I_SEL23_SEL30_Pos                16
#define VC_PWM_I_SEL23_SEL30_Msk                (0x3UL << VC_PWM_I_SEL23_SEL30_Pos)

#define VC_PWM_I_SEL23_SEL31_Pos                18
#define VC_PWM_I_SEL23_SEL31_Msk                (0x3UL << VC_PWM_I_SEL23_SEL31_Pos)

#define VC_PWM_I_SEL23_SEL32_Pos                20
#define VC_PWM_I_SEL23_SEL32_Msk                (0x3UL << VC_PWM_I_SEL23_SEL32_Pos)

/* ========================================================================= */
/* ============                       SPI                       ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t CTRL;                /* (0x0000) SPI control register */
  __IOM uint32_t TXSTS;               /* (0x0004) SPI transmit status register */
  __IOM uint32_t TXDAT;               /* (0x0008) SPI transmit FIFO register */
  __IOM uint32_t RXSTS;               /* (0x000C) SPI receive status register */
  __IOM uint32_t RXDAT;               /* (0x0010) SPI receive FIFO register */
  __IOM uint32_t MISC;                /* (0x0014) SPI misc control register */
} VC_SPI_TypeDef;

/* SPI_CTRL register */
#define VC_SPI_CTRL_CLKDIVL_Pos                 0
#define VC_SPI_CTRL_CLKDIVL_Msk                 (0xFUL << VC_SPI_CTRL_CLKDIVL_Pos)

#define VC_SPI_CTRL_SCKPOL_Pos                  4
#define VC_SPI_CTRL_SCKPOL_Msk                  (1UL << VC_SPI_CTRL_SCKPOL_Pos)

#define VC_SPI_CTRL_SCKPHA_Pos                  5
#define VC_SPI_CTRL_SCKPHA_Msk                  (1UL << VC_SPI_CTRL_SCKPHA_Pos)

#define VC_SPI_CTRL_WIDTH_Pos                   6
#define VC_SPI_CTRL_WIDTH_Msk                   (0x3UL << VC_SPI_CTRL_WIDTH_Pos)

#define VC_SPI_CTRL_MOD_Pos                     8
#define VC_SPI_CTRL_MOD_Msk                     (1UL << VC_SPI_CTRL_MOD_Pos)

#define VC_SPI_CTRL_SWAP_Pos                    9
#define VC_SPI_CTRL_SWAP_Msk                    (1UL << VC_SPI_CTRL_SWAP_Pos)

#define VC_SPI_CTRL_CSGPIO_Pos                  10
#define VC_SPI_CTRL_CSGPIO_Msk                  (1UL << VC_SPI_CTRL_CSGPIO_Pos)

#define VC_SPI_CTRL_SPIRST_Pos                  11
#define VC_SPI_CTRL_SPIRST_Msk                  (1UL << VC_SPI_CTRL_SPIRST_Pos)

#define VC_SPI_CTRL_LSBF_Pos                    12
#define VC_SPI_CTRL_LSBF_Msk                    (1UL << VC_SPI_CTRL_LSBF_Pos)

#define VC_SPI_CTRL_BYTEORDER_Pos               13
#define VC_SPI_CTRL_BYTEORDER_Msk               (1UL << VC_SPI_CTRL_BYTEORDER_Pos)

#define VC_SPI_CTRL_SPIEN_Pos                   15
#define VC_SPI_CTRL_SPIEN_Msk                   (1UL << VC_SPI_CTRL_SPIEN_Pos)

#define VC_SPI_CTRL_CLKDIVH_Pos                 16
#define VC_SPI_CTRL_CLKDIVH_Msk                 (0xFUL << VC_SPI_CTRL_CLKDIVH_Pos)

/* SPI_TXSTS register */
#define VC_SPI_TXSTS_TXFFLAG_Pos                0
#define VC_SPI_TXSTS_TXFFLAG_Msk                (0xFUL << VC_SPI_TXSTS_TXFFLAG_Pos)

#define VC_SPI_TXSTS_TXFLEV_Pos                 4
#define VC_SPI_TXSTS_TXFLEV_Msk                 (0x7UL << VC_SPI_TXSTS_TXFLEV_Pos)

#define VC_SPI_TXSTS_TXFUR_Pos                  8
#define VC_SPI_TXSTS_TXFUR_Msk                  (1UL << VC_SPI_TXSTS_TXFUR_Pos)

#define VC_SPI_TXSTS_TXEMPTY_Pos                9
#define VC_SPI_TXSTS_TXEMPTY_Msk                (1UL << VC_SPI_TXSTS_TXEMPTY_Pos)

#define VC_SPI_TXSTS_SPITXIEN_Pos               14
#define VC_SPI_TXSTS_SPITXIEN_Msk               (1UL << VC_SPI_TXSTS_SPITXIEN_Pos)

#define VC_SPI_TXSTS_SPITXIF_Pos                15
#define VC_SPI_TXSTS_SPITXIF_Msk                (1UL << VC_SPI_TXSTS_SPITXIF_Pos)

/* SPI_TXDAT register */
#define VC_SPI_TXDAT_SPITXD_Pos                 0
#define VC_SPI_TXDAT_SPITXD_Msk                 (0xFFUL << VC_SPI_TXDAT_SPITXD_Pos)

/* SPI_RXSTS register */
#define VC_SPI_RXSTS_RXFFLAG_Pos                0
#define VC_SPI_RXSTS_RXFFLAG_Msk                (0xFUL << VC_SPI_RXSTS_RXFFLAG_Pos)

#define VC_SPI_RXSTS_RXFLEV_Pos                 4
#define VC_SPI_RXSTS_RXFLEV_Msk                 (0x7UL << VC_SPI_RXSTS_RXFLEV_Pos)

#define VC_SPI_RXSTS_RXFOV_Pos                  8
#define VC_SPI_RXSTS_RXFOV_Msk                  (1UL << VC_SPI_RXSTS_RXFOV_Pos)

#define VC_SPI_RXSTS_RXFULL_Pos                 9
#define VC_SPI_RXSTS_RXFULL_Msk                 (1UL << VC_SPI_RXSTS_RXFULL_Pos)

#define VC_SPI_RXSTS_SPIRXIEN_Pos               14
#define VC_SPI_RXSTS_SPIRXIEN_Msk               (1UL << VC_SPI_RXSTS_SPIRXIEN_Pos)

#define VC_SPI_RXSTS_SPIRXIF_Pos                15
#define VC_SPI_RXSTS_SPIRXIF_Msk                (1UL << VC_SPI_RXSTS_SPIRXIF_Pos)

/* SPI_RXDAT register */
#define VC_SPI_RXDAT_SPIRXD_Pos                 0
#define VC_SPI_RXDAT_SPIRXD_Msk                 (0xFFUL << VC_SPI_RXDAT_SPIRXD_Pos)

/* SPI_MISC register */
#define VC_SPI_MISC_TFE_Pos                     0
#define VC_SPI_MISC_TFE_Msk                     (1UL << VC_SPI_MISC_TFE_Pos)

#define VC_SPI_MISC_TNF_Pos                     1
#define VC_SPI_MISC_TNF_Msk                     (1UL << VC_SPI_MISC_TNF_Pos)

#define VC_SPI_MISC_RNE_Pos                     2
#define VC_SPI_MISC_RNE_Msk                     (1UL << VC_SPI_MISC_RNE_Pos)

#define VC_SPI_MISC_RFF_Pos                     3
#define VC_SPI_MISC_RFF_Msk                     (1UL << VC_SPI_MISC_RFF_Pos)

#define VC_SPI_MISC_BSY_Pos                     4
#define VC_SPI_MISC_BSY_Msk                     (1UL << VC_SPI_MISC_BSY_Pos)

#define VC_SPI_MISC_SMART_Pos                   8
#define VC_SPI_MISC_SMART_Msk                   (1UL << VC_SPI_MISC_SMART_Pos)

#define VC_SPI_MISC_OVER_Pos                    9
#define VC_SPI_MISC_OVER_Msk                    (1UL << VC_SPI_MISC_OVER_Pos)

#define VC_SPI_MISC_LATTIME_Pos                 10
#define VC_SPI_MISC_LATTIME_Msk                 (1UL << VC_SPI_MISC_LATTIME_Pos)

#define VC_SPI_MISC_LOOPBACK_Pos                11
#define VC_SPI_MISC_LOOPBACK_Msk                (1UL << VC_SPI_MISC_LOOPBACK_Pos)

/* ========================================================================= */
/* ============                       I2C                       ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t DATA;                /* (0x0000) I2C data register */
  __IOM uint32_t ADDR;                /* (0x0004) I2C address register */
  __IOM uint32_t CTRL;                /* (0x0008) I2C control register */
  __IOM uint32_t STS;                 /* (0x000C) I2C status register */
  __IM uint32_t  RESERVED[2];
  __IOM uint32_t CTRL2;               /* (0x0018) I2C interrupt enable register */
} VC_I2C_TypeDef;

/* I2C_DATA register */
#define VC_I2C_DATA_DATA_Pos                    0
#define VC_I2C_DATA_DATA_Msk                    (0xFFUL << VC_I2C_DATA_DATA_Pos)

/* I2C_ADDR register */
#define VC_I2C_ADDR_GC_Pos                      0
#define VC_I2C_ADDR_GC_Msk                      (1UL << VC_I2C_ADDR_GC_Pos)

#define VC_I2C_ADDR_SLA_Pos                     1
#define VC_I2C_ADDR_SLA_Msk                     (0x7F << VC_I2C_ADDR_SLA_Pos)

/* I2C_CTRL register */
#define VC_I2C_CTRL_CR0_Pos                     0
#define VC_I2C_CTRL_CR0_Msk                     (1UL << VC_I2C_CTRL_CR0_Pos)

#define VC_I2C_CTRL_CR1_Pos                     1
#define VC_I2C_CTRL_CR1_Msk                     (1UL << VC_I2C_CTRL_CR1_Pos)

#define VC_I2C_CTRL_AA_Pos                      2
#define VC_I2C_CTRL_AA_Msk                      (1UL << VC_I2C_CTRL_AA_Pos)

#define VC_I2C_CTRL_SI_Pos                      3
#define VC_I2C_CTRL_SI_Msk                      (1UL << VC_I2C_CTRL_SI_Pos)

#define VC_I2C_CTRL_STO_Pos                     4
#define VC_I2C_CTRL_STO_Msk                     (1UL << VC_I2C_CTRL_STO_Pos)

#define VC_I2C_CTRL_STA_Pos                     5
#define VC_I2C_CTRL_STA_Msk                     (1UL << VC_I2C_CTRL_STA_Pos)

#define VC_I2C_CTRL_EN_Pos                      6
#define VC_I2C_CTRL_EN_Msk                      (1UL << VC_I2C_CTRL_EN_Pos)

#define VC_I2C_CTRL_CR2_Pos                     7
#define VC_I2C_CTRL_CR2_Msk                     (1UL << VC_I2C_CTRL_CR2_Pos)

/* I2C_STS register */
#define VC_I2C_STS_STS_Pos                      5
#define VC_I2C_STS_STS_Msk                      (0x7UL << VC_I2C_STS_STS_Pos)

/* I2C_CTRL2 register */
#define VC_I2C_CTRL2_INTEN_Pos                  0
#define VC_I2C_CTRL2_INTEN_Msk                  (1UL << VC_I2C_CTRL2_INTEN_Pos)

/* ========================================================================= */
/* ============                      MISC                       ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t SRAMINT;             /* (0x0000) SRAM parity error interrupt */
  __IOM uint32_t SRAMINIT;            /* (0x0004) SRAM initialize register */
  __IM uint32_t  RESERVED[6];
  __IM uint32_t  HIADDR;              /* (0x0020) AHB invalid access address */
  __IM uint32_t  PIADDR;              /* (0x0024) APB invalid access address */
} VC_MISC_TypeDef;

/* MISC_SRAMINT register */
#define VC_MISC_SRAMINT_PERR_Pos                0
#define VC_MISC_SRAMINT_PERR_Msk                (1UL << VC_MISC_SRAMINT_PERR_Pos)

#define VC_MISC_SRAMINT_HIAL_Pos                1
#define VC_MISC_SRAMINT_HIAL_Msk                (1UL << VC_MISC_SRAMINT_HIAL_Pos)

#define VC_MISC_SRAMINT_HIAC_Pos                2
#define VC_MISC_SRAMINT_HIAC_Msk                (1UL << VC_MISC_SRAMINT_HIAC_Pos)

#define VC_MISC_SRAMINT_PIAC_Pos                3
#define VC_MISC_SRAMINT_PIAC_Msk                (1UL << VC_MISC_SRAMINT_PIAC_Pos)

#define VC_MISC_SRAMINT_LOCKUP_Pos              4
#define VC_MISC_SRAMINT_LOCKUP_Msk              (1UL << VC_MISC_SRAMINT_LOCKUP_Pos)

/* MISC_SRAMINIT register */
#define VC_MISC_SRAMINIT_INIT_Pos               2
#define VC_MISC_SRAMINIT_INIT_Msk               (1UL << VC_MISC_SRAMINIT_INIT_Pos)

#define VC_MISC_SRAMINIT_HIALIE_Pos             4
#define VC_MISC_SRAMINIT_HIALIE_Msk             (1UL << VC_MISC_SRAMINIT_HIALIE_Pos)

#define VC_MISC_SRAMINIT_HIACIE_Pos             5
#define VC_MISC_SRAMINIT_HIACIE_Msk             (1UL << VC_MISC_SRAMINIT_HIACIE_Pos)

#define VC_MISC_SRAMINIT_PIACIE_Pos             6
#define VC_MISC_SRAMINIT_PIACIE_Msk             (1UL << VC_MISC_SRAMINIT_PIACIE_Pos)

#define VC_MISC_SRAMINIT_LOCKIE_Pos             7
#define VC_MISC_SRAMINIT_LOCKIE_Msk             (1UL << VC_MISC_SRAMINIT_LOCKIE_Pos)

/* MISC_IRQLAT register */
#define VC_MISC_IRQLAT_IRQLAT_Pos               0
#define VC_MISC_IRQLAT_IRQLAT_Msk               (0xFFUL << VC_MISC_IRQLAT_IRQLAT_Pos)

#define VC_MISC_IRQLAT_LOCKRESET_Pos            8
#define VC_MISC_IRQLAT_LOCKRESET_Msk            (1UL << VC_MISC_IRQLAT_LOCKRESET_Pos)

#define VC_MISC_IRQLAT_NOHARDFAULT_Pos          9
#define VC_MISC_IRQLAT_NOHARDFAULT_Msk          (1UL << VC_MISC_IRQLAT_NOHARDFAULT_Pos)

/* ========================================================================= */
/* ============                     MISC2                       ============ */
/* ========================================================================= */

typedef struct
{
  __IM uint32_t  RESERVED;
  __IOM uint32_t CLKSEL;              /* (0x0004) Clock selection register */
  __IOM uint32_t CLKDIVH;             /* (0x0008) AHB clock divider control register */
  __IOM uint32_t CLKDIVP;             /* (0x000C) APB clock divider control register */
  __IOM uint32_t HCLKEN;              /* (0x0010) AHB clock enable control register */
  __IOM uint32_t PCLKEN;              /* (0x0014) APB clock enable control register */
  __IM uint32_t  RESERVED1[4];
  __IOM uint32_t CLKEN_UNLOCK;        /* (0x0028) HCLK, PCLK pass register */
} VC_MISC2_TypeDef;

typedef struct
{
  __IOM uint32_t FPGAWD0;             /* (0x0100) For FPGA mode control register 0 */
  __IOM uint32_t FPGAWD1;             /* (0x0104) For FPGA mode control register 1 */
  __IOM uint32_t FPGAWD2;             /* (0x0108) For FPGA mode control register 2 */
} VC_MISC2_FPGA_TypeDef;

/* MISC2_CLKSEL register */
#define VC_MISC2_CLKSEL_CLKSEL_Pos              0
#define VC_MISC2_CLKSEL_CLKSEL_Msk              (0x7UL << VC_MISC2_CLKSEL_CLKSEL_Pos)

#define VC_MISC2_CLKSEL_CLKSEL_R100K_0          (0UL << VC_MISC2_CLKSEL_CLKSEL_Pos)
#define VC_MISC2_CLKSEL_CLKSEL_XTAL25M          (1UL << VC_MISC2_CLKSEL_CLKSEL_Pos)
#define VC_MISC2_CLKSEL_CLKSEL_GPLL             (2UL << VC_MISC2_CLKSEL_CLKSEL_Pos)
#define VC_MISC2_CLKSEL_CLKSEL_32K              (3UL << VC_MISC2_CLKSEL_CLKSEL_Pos)
#define VC_MISC2_CLKSEL_CLKSEL_R100K_4          (4UL << VC_MISC2_CLKSEL_CLKSEL_Pos)

/* MISC2_CLKDIVH register */
#define VC_MISC2_CLKDIVH_CLKDIVH_Pos            0
#define VC_MISC2_CLKDIVH_CLKDIVH_Msk            (0xFFUL << VC_MISC2_CLKDIVH_CLKDIVH_Pos)
#define VC_MISC2_CLKDIVH_CLKDIVH_DIV(x)         ((x - 1) << VC_MISC2_CLKDIVH_CLKDIVH_Pos)

/* MISC2_CLKDIVP register */
#define VC_MISC2_CLKDIVP_CLKDIVP_Pos            0
#define VC_MISC2_CLKDIVP_CLKDIVP_Msk            (1UL << VC_MISC2_CLKDIVP_CLKDIVP_Pos)

#define VC_MISC2_CLKDIVP_CLKDIVP_DIV_2          (0UL << VC_MISC2_CLKDIVP_CLKDIVP_Pos)
#define VC_MISC2_CLKDIVP_CLKDIVP_DIV_4          (1UL << VC_MISC2_CLKDIVP_CLKDIVP_Pos)

/* MISC2_HCLKEN register */
#define VC_MISC2_HCLKEN_HCLKEN_Pos              0
#define VC_MISC2_HCLKEN_HCLKEN_Msk              (0xFFFFUL << VC_MISC2_HCLKEN_HCLKEN_Pos)

#define VC_MISC2_HCLKEN_DMA_Pos                 0
#define VC_MISC2_HCLKEN_DMA_Msk                 (1UL << VC_MISC2_HCLKEN_DMA_Pos)

#define VC_MISC2_HCLKEN_GPIO_Pos                1
#define VC_MISC2_HCLKEN_GPIO_Msk                (1UL << VC_MISC2_HCLKEN_GPIO_Pos)

#define VC_MISC2_HCLKEN_PLC_SEC_Pos             11
#define VC_MISC2_HCLKEN_PLC_SEC_Msk             (1UL << VC_MISC2_HCLKEN_PLC_SEC_Pos)

#define VC_MISC2_HCLKEN_BASEBAND_MAC_Pos        12
#define VC_MISC2_HCLKEN_BASEBAND_MAC_Msk        (1UL << VC_MISC2_HCLKEN_BASEBAND_MAC_Pos)

#define VC_MISC2_HCLKEN_ETH_MAC_Pos             13
#define VC_MISC2_HCLKEN_ETH_MAC_Msk             (1UL << VC_MISC2_HCLKEN_ETH_MAC_Pos)

/* MISC2_PCLKEN register */
#define VC_MISC2_PCLKEN_PCLKEN_Pos              0
#define VC_MISC2_PCLKEN_PCLKEN_Msk              (0xFFFFFFFFUL << VC_MISC2_PCLKEN_PCLKEN_Pos)

#define VC_MISC2_PCLKEN_DMA_Pos                 1
#define VC_MISC2_PCLKEN_DMA_Msk                 (1UL << VC_MISC2_PCLKEN_DMA_Pos)

#define VC_MISC2_PCLKEN_I2C_Pos                 2
#define VC_MISC2_PCLKEN_I2C_Msk                 (1UL << VC_MISC2_PCLKEN_I2C_Pos)

#define VC_MISC2_PCLKEN_SPI_Pos(x)              ((x - 1) + 3UL) /* SPI1 - SPI3 */
#define VC_MISC2_PCLKEN_SPI_Msk(x)              (1UL << VC_MISC2_PCLKEN_SPI_Pos(x))

#define VC_MISC2_PCLKEN_SPI1_Pos                3
#define VC_MISC2_PCLKEN_SPI1_Msk                (1UL << VC_MISC2_PCLKEN_SPI1_Pos)

#define VC_MISC2_PCLKEN_SPI2_Pos                4
#define VC_MISC2_PCLKEN_SPI2_Msk                (1UL << VC_MISC2_PCLKEN_SPI2_Pos)

#define VC_MISC2_PCLKEN_SPI3_Pos                5
#define VC_MISC2_PCLKEN_SPI3_Msk                (1UL << VC_MISC2_PCLKEN_SPI3_Pos)

#define VC_MISC2_PCLKEN_UART_Pos(x)             (x + 6UL) /* UART0 - UART6 */
#define VC_MISC2_PCLKEN_UART_Msk(x)             (1UL << VC_MISC2_PCLKEN_UART_Pos(x))

#define VC_MISC2_PCLKEN_UART0_Pos               6
#define VC_MISC2_PCLKEN_UART0_Msk               (1UL << VC_MISC2_PCLKEN_UART0_Pos)

#define VC_MISC2_PCLKEN_UART1_Pos               7
#define VC_MISC2_PCLKEN_UART1_Msk               (1UL << VC_MISC2_PCLKEN_UART1_Pos)

#define VC_MISC2_PCLKEN_UART2_Pos               8
#define VC_MISC2_PCLKEN_UART2_Msk               (1UL << VC_MISC2_PCLKEN_UART2_Pos)

#define VC_MISC2_PCLKEN_UART3_Pos               9
#define VC_MISC2_PCLKEN_UART3_Msk               (1UL << VC_MISC2_PCLKEN_UART3_Pos)

#define VC_MISC2_PCLKEN_UART4_Pos               10
#define VC_MISC2_PCLKEN_UART4_Msk               (1UL << VC_MISC2_PCLKEN_UART4_Pos)

#define VC_MISC2_PCLKEN_UART5_Pos               11
#define VC_MISC2_PCLKEN_UART5_Msk               (1UL << VC_MISC2_PCLKEN_UART5_Pos)

#define VC_MISC2_PCLKEN_UART6_Pos               12
#define VC_MISC2_PCLKEN_UART6_Msk               (1UL << VC_MISC2_PCLKEN_UART6_Pos)

#define VC_MISC2_PCLKEN_ISO7816_Pos(x)          (x + 13UL) /* ISO78160 - ISO78161 */
#define VC_MISC2_PCLKEN_ISO7816_Msk(x)          (1UL << VC_MISC2_PCLKEN_ISO7816_Pos(x))

#define VC_MISC2_PCLKEN_ISO78160_Pos            13
#define VC_MISC2_PCLKEN_ISO78160_Msk            (1UL << VC_MISC2_PCLKEN_ISO78160_Pos)

#define VC_MISC2_PCLKEN_ISO78161_Pos            14
#define VC_MISC2_PCLKEN_ISO78161_Msk            (1UL << VC_MISC2_PCLKEN_ISO78161_Pos)

#define VC_MISC2_PCLKEN_TIMER_Pos               15
#define VC_MISC2_PCLKEN_TIMER_Msk               (1UL << VC_MISC2_PCLKEN_TIMER_Pos)

#define VC_MISC2_PCLKEN_MISC_Pos                16
#define VC_MISC2_PCLKEN_MISC_Msk                (1UL << VC_MISC2_PCLKEN_MISC_Pos)

#define VC_MISC2_PCLKEN_MISC2_Pos               17
#define VC_MISC2_PCLKEN_MISC2_Msk               (1UL << VC_MISC2_PCLKEN_MISC2_Pos)

#define VC_MISC2_PCLKEN_PMU_Pos                 18
#define VC_MISC2_PCLKEN_PMU_Msk                 (1UL << VC_MISC2_PCLKEN_PMU_Pos)

#define VC_MISC2_PCLKEN_RTC_Pos                 19
#define VC_MISC2_PCLKEN_RTC_Msk                 (1UL << VC_MISC2_PCLKEN_RTC_Pos)

#define VC_MISC2_PCLKEN_ANA_Pos                 20
#define VC_MISC2_PCLKEN_ANA_Msk                 (1UL << VC_MISC2_PCLKEN_ANA_Pos)

#define VC_MISC2_PCLKEN_KEYSCAN_Pos             24
#define VC_MISC2_PCLKEN_KEYSCAN_Msk             (1UL << VC_MISC2_PCLKEN_KEYSCAN_Pos)

#define VC_MISC2_PCLKEN_EFUSE_Pos               25
#define VC_MISC2_PCLKEN_EFUSE_Msk               (1UL << VC_MISC2_PCLKEN_EFUSE_Pos)

/* MISC2_CLKEN_UNLOCK register */
#define VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos        0
#define VC_MISC2_CLKEN_UNLOCK_UNLOCK_Msk        (1UL << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos)

/* ========================================================================= */
/* ============                     MISC2                       ============ */
/* ========================================================================= */

typedef struct
{
    __IOM uint32_t ENDIAN;            /* (0x0000) Data endian select register */
    __IOM uint32_t TRNGCTRL;          /* (0x0004) TRNG control register */
    __IOM uint32_t TRNGSTS;           /* (0x0008) TRNG status register */
    __IM uint32_t  RESERVED;
    __IOM uint32_t AESKEY0;           /* (0x0010) AES CSR key 0 register */
    __IOM uint32_t AESKEY1;           /* (0x0014) AES CSR key 1 register */
    __IOM uint32_t AESKEY2;           /* (0x0018) AES CSR key 0 register */
    __IOM uint32_t AESKEY3;           /* (0x001C) AES CSR key 1 register */
    __IOM uint32_t AESKEY4;           /* (0x0020) AES CSR key 0 register */
    __IOM uint32_t AESKEY5;           /* (0x0024) AES CSR key 1 register */
    __IOM uint32_t AESKEY6;           /* (0x0028) AES CSR key 0 register */
    __IOM uint32_t AESKEY7;           /* (0x002C) AES CSR key 1 register */
    __IOM uint32_t AESCTRL;           /* (0x0030) AES pulse valid control register */
} VC_AHBMISC_TypeDef;

/* AHBMISC_ENDIAN register */
#define VC_AHBMISC_AHB_ENDIAN_HASH_Pos          0
#define VC_AHBMISC_AHB_ENDIAN_HASH_Msk          (1UL << VC_AHBMISC_AHB_ENDIAN_HASH_Pos)

#define VC_AHBMISC_M_AHB_ENDIAN_HASH_Pos        1
#define VC_AHBMISC_M_AHB_ENDIAN_HASH_Msk        (1UL << VC_AHBMISC_M_AHB_ENDIAN_HASH_Pos)

#define VC_AHBMISC_AHB_ENDIAN_PKE_Pos           2
#define VC_AHBMISC_AHB_ENDIAN_PKE_Msk           (1UL << VC_AHBMISC_AHB_ENDIAN_PKE_Pos)

#define VC_AHBMISC_AHB_ENDIAN_SKE_Pos           3
#define VC_AHBMISC_AHB_ENDIAN_SKE_Msk           (1UL << VC_AHBMISC_AHB_ENDIAN_SKE_Pos)

#define VC_AHBMISC_M_AHB_ENDIAN_SKE_Pos         4
#define VC_AHBMISC_M_AHB_ENDIAN_SKE_Msk         (1UL << VC_AHBMISC_M_AHB_ENDIAN_SKE_Pos)

#define VC_AHBMISC_AHB_ENDIAN_TRNG_Pos          5
#define VC_AHBMISC_AHB_ENDIAN_TRNG_Msk          (1UL << VC_AHBMISC_AHB_ENDIAN_TRNG_Pos)

/* AHBMISC_TRNGCTRL register */
#define VC_AHBMISC_TRNGCTRL_SKIP_STARTUP_Pos    0
#define VC_AHBMISC_TRNGCTRL_SKIP_STARTUP_Msk    (1UL << VC_AHBMISC_TRNGCTRL_SKIP_STARTUP_Pos)

#define VC_AHBMISC_TRNGCTRL_SCLK_SEL_Pos        1
#define VC_AHBMISC_TRNGCTRL_SCLK_SEL_Msk        (1UL << VC_AHBMISC_TRNGCTRL_SCLK_SEL_Pos)

/* AHBMISC_TRNGSTS register */
#define VC_AHBMISC_TRNGSTS_TRNG_RDY_Pos         0
#define VC_AHBMISC_TRNGSTS_TRNG_RDY_Msk         (1UL << VC_AHBMISC_TRNGSTS_TRNG_RDY_Pos)

#define VC_AHBMISC_TRNGSTS_ALARM_Pos            1
#define VC_AHBMISC_TRNGSTS_ALARM_Msk            (1UL << VC_AHBMISC_TRNGSTS_ALARM_Pos)

/* AHBMISC_AESKEYx register */
#define VC_AHBMISC_AESKEYx_AES_KEY_Pos          0
#define VC_AHBMISC_AESKEYx_AES_KEY_Msk          (0xFFFFFFFFUL << VC_AHBMISC_AESKEYx_AES_KEY_Pos)

/* AHBMISC_AESCTRL register */
#define VC_AHBMISC_AESCTRL_AES_KEY_VALID_Pos    0
#define VC_AHBMISC_AESCTRL_AES_KEY_VALID_Msk    (1UL << VC_AHBMISC_AESCTRL_AES_KEY_VALID_Pos)

/* ========================================================================= */
/* ============                      KEYSCAN                    ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t CTRL;                /* (0x0000) Key scan control register */
  __IM uint32_t  KEYSTS;              /* (0x0004) Key scan key status register */
  __IOM uint32_t SCANEN;              /* (0x0008) Key scan enable register */
  __IOM uint32_t INTEN;               /* (0x000C) Key scan interrupt enable register */
  __IOM uint32_t INTSTS;              /* (0x0010) Key scan interrupt status register */
} VC_KEYSCAN_TypeDef;

/* KEYSCAN_CTRL register */
#define VC_KEYSCAN_CTRL_EN_Pos                  0
#define VC_KEYSCAN_CTRL_EN_Msk                  (1UL << VC_KEYSCAN_CTRL_EN_Pos)

#define VC_KEYSCAN_CTRL_SPEED_Pos               2
#define VC_KEYSCAN_CTRL_SPEED_Msk               (0x3UL << VC_KEYSCAN_CTRL_SPEED_Pos)

#define VC_KEYSCAN_CTRL_PULSE_Pos               4
#define VC_KEYSCAN_CTRL_PULSE_Msk               (0x7UL << VC_KEYSCAN_CTRL_PULSE_Pos)

/* KEYSCAN_KEYSTS register */
#define VC_KEYSCAN_KEY_KEY_Pos                  0
#define VC_KEYSCAN_KEY_KEY_Msk                  (0xFFFFUL << VC_KEYSCAN_KEY_KEY_Pos)

/* KEYSCAN_SCANEN register */
#define VC_KEYSCAN_SCANEN_SCANEN_Pos            0
#define VC_KEYSCAN_SCANEN_SCANEN_Msk            (0xFFFFUL << VC_KEYSCAN_SCANEN_SCANEN_Pos)

/* KEYSCAN_INTEN register */
#define VC_KEYSCAN_INTEN_INTEN_Pos              0
#define VC_KEYSCAN_INTEN_INTEN_Msk              (0xFFFFUL << VC_KEYSCAN_INTEN_INTEN_Pos)

/* KEYSCAN_INTSTS register */
#define VC_KEYSCAN_INTSTS_INTSTS_Pos            0
#define VC_KEYSCAN_INTSTS_INTSTS_Msk            (0xFFFFUL << VC_KEYSCAN_INTSTS_INTSTS_Pos)

/* ========================================================================= */
/* ============                         PLC                     ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t CR1;                   /* (0x0000) PHY control register 1 */
  __IOM uint32_t CR2;                   /* (0x0004) PHY control register 2 */
  __IOM uint32_t CR3;                   /* (0x0008) PHY control register 3 */
  __IOM uint32_t CR4;                   /* (0x000C) PHY control register 4 */
  __IOM uint32_t IR1;                   /* (0x0010) PHY information register 1 */
  __IOM uint32_t IR2;                   /* (0x0014) PHY information register 2 */
  __IOM uint32_t IR3;                   /* (0x0018) PHY information register 3 */
  __IOM uint32_t IR4;                   /* (0x001C) PHY information register 4 */
} VC_PLC_PHY_TypeDef;

/* ================  End of section using anonymous unions  ================ */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/* ========================================================================= */
/* ============     Device Specific Peripheral Address Map      ============ */
/* ========================================================================= */

#define VC_PMU_BASE                     (0x40048000UL)
#define VC_PMU_RETENTION_RAM_BASE       (0x4004E000UL)
#define VC_ANA_BASE                     (0x4004B000UL)
#define VC_RTC_BASE                     (0x40049000UL)
#define VC_MEM_BASE                     (0x40020000UL)
#define VC_GPIOA_BASE                   (0x40048010UL)
#define VC_GPIOB_BASE                   (0x40000040UL)
#define VC_GPIOC_BASE                   (0x40000080UL)
#define VC_GPIOD_BASE                   (0x400000C0UL)
#define VC_GPIOE_BASE                   (0x40000100UL)
#define VC_GPIOMISC_BASE                (0x40000200UL)
#define VC_DMA_BASE                     (0x40040000UL)
#define VC_UART0_BASE                   (0x40043000UL)
#define VC_UART1_BASE                   (0x40043040UL)
#define VC_UART2_BASE                   (0x40043080UL)
#define VC_UART3_BASE                   (0x400430C0UL)
#define VC_UART4_BASE                   (0x40043100UL)
#define VC_UART5_BASE                   (0x40043140UL)
#define VC_UART6_BASE                   (0x40043180UL)
#define VC_UART_GFIFO_BASE              (0x40043400UL)
#define VC_ISO78160_BASE                (0x40044004UL)
#define VC_ISO78161_BASE                (0x40044044UL)
#define VC_TIM0_BASE                    (0x40045000UL)
#define VC_TIM1_BASE                    (0x40045020UL)
#define VC_TIM2_BASE                    (0x40045040UL)
#define VC_TIM3_BASE                    (0x40045060UL)
#define VC_PWM0_BASE                    (0x40045100UL)
#define VC_PWM1_BASE                    (0x40045140UL)
#define VC_PWM2_BASE                    (0x40045180UL)
#define VC_PWM3_BASE                    (0x400451C0UL)
#define VC_PWMSEL_BASE                  (0x400452F0UL)
#define VC_SPI1_BASE                    (0x40042000UL)
#define VC_SPI2_BASE                    (0x40042080UL)
#define VC_SPI3_BASE                    (0x40042100UL)
#define VC_I2C1_BASE                    (0x40041000UL)
#define VC_I2C2_BASE                    (0x40041020UL)
#define VC_MISC_BASE                    (0x40046000UL)
#define VC_MISC2_BASE                   (0x40047000UL)
#define VC_MISC2_FPGA_BASE              (0x40047100UL)
#define VC_AHBMISC_BASE                 (0x40004000UL)
#define VC_KEYSCAN_BASE                 (0x4004D000UL)

#define VC_PLC_DMA_BASE                 (0x40010000UL)
#define VC_PLC_BASE                     (0x40011000UL)
#define VC_PLC_PHY_BASE                 (0x400111C0UL)

#define VC_SKE_BASE                     (0x40008000UL)
#define VC_PKE_BASE                     (0x4000C000UL)
#define VC_TRNG_BASE                    (0x40014000UL)
#define VC_HASH_BASE                    (0x40018000UL)

/* ========================================================================= */
/* ============             Peripheral declaration              ============ */
/* ========================================================================= */

#define VC_PMU                          ((VC_PMU_TypeDef *) VC_PMU_BASE)
#define VC_ANA                          ((VC_ANA_TypeDef *) VC_ANA_BASE)
#define VC_RTC                          ((VC_RTC_TypeDef *) VC_RTC_BASE)
#define VC_MEM                          ((VC_MEM_TypeDef *) VC_MEM_BASE)
#define VC_GPIOA                        ((VC_GPIOA_TypeDef *) VC_GPIOA_BASE)
#define VC_GPIO(x)                      ((VC_GPIO_TypeDef *)(((x - 1) * 0x40UL) + VC_GPIOB_BASE))
#define VC_GPIOB                        ((VC_GPIOB_TypeDef *) VC_GPIOB_BASE)
#define VC_GPIOC                        ((VC_GPIOC_TypeDef *) VC_GPIOC_BASE)
#define VC_GPIOD                        ((VC_GPIOD_TypeDef *) VC_GPIOD_BASE)
#define VC_GPIOE                        ((VC_GPIOE_TypeDef *) VC_GPIOE_BASE)
#define VC_GPIOMISC                     ((VC_GPIOMISC_TypeDef *) VC_GPIOMISC_BASE)
#define VC_DMA                          ((VC_DMA_TypeDef *) VC_DMA_BASE)
#define VC_UART0                        ((VC_UART_TypeDef *) VC_UART0_BASE)
#define VC_UART1                        ((VC_UART_TypeDef *) VC_UART1_BASE)
#define VC_UART2                        ((VC_UART_TypeDef *) VC_UART2_BASE)
#define VC_UART3                        ((VC_UART_TypeDef *) VC_UART3_BASE)
#define VC_UART4                        ((VC_UART_TypeDef *) VC_UART4_BASE)
#define VC_UART5                        ((VC_UART_TypeDef *) VC_UART5_BASE)
#define VC_UART6                        ((VC_UART_TypeDef *) VC_UART6_BASE)
#define VC_UART(x)                      ((VC_UART_TypeDef *)((x * 0x40UL) + VC_UART0_BASE))
#define VC_GFIFO                        ((VC_UART_GFIFO_TypeDef *) VC_UART_GFIFO_BASE)
#define VC_ISO78160                     ((VC_ISO7816_TypeDef *) VC_ISO78160_BASE)
#define VC_ISO78161                     ((VC_ISO7816_TypeDef *) VC_ISO78161_BASE)
#define VC_TIM0                         ((VC_TIM_TypeDef *) VC_TIM0_BASE)
#define VC_TIM1                         ((VC_TIM_TypeDef *) VC_TIM1_BASE)
#define VC_TIM2                         ((VC_TIM_TypeDef *) VC_TIM2_BASE)
#define VC_TIM3                         ((VC_TIM_TypeDef *) VC_TIM3_BASE)
#define VC_PWM0                         ((VC_PWM_TypeDef *) VC_PWM0_BASE)
#define VC_PWM1                         ((VC_PWM_TypeDef *) VC_PWM1_BASE)
#define VC_PWM2                         ((VC_PWM_TypeDef *) VC_PWM2_BASE)
#define VC_PWM3                         ((VC_PWM_TypeDef *) VC_PWM3_BASE)
#define VC_PWMSEL                       ((VC_PWMSEL_Typedef *) VC_PWMSEL_BASE)
#define VC_SPI1                         ((VC_SPI_TypeDef *) VC_SPI1_BASE)
#define VC_SPI2                         ((VC_SPI_TypeDef *) VC_SPI2_BASE)
#define VC_SPI3                         ((VC_SPI_TypeDef *) VC_SPI3_BASE)
#define VC_SPI(x)                       ((VC_SPI_TypeDef *) ((x * 0x80UL) + VC_SPI1_BASE))
#define VC_I2C1                         ((VC_I2C_TypeDef *) VC_I2C1_BASE)
#define VC_I2C2                         ((VC_I2C_TypeDef *) VC_I2C2_BASE)
#define VC_I2C(x)                       ((VC_I2C_TypeDef *) ((x * 0x20UL) + VC_I2C1_BASE))
#define VC_MISC                         ((VC_MISC_TypeDef *) VC_MISC_BASE)
#define VC_MISC2                        ((VC_MISC2_TypeDef *) VC_MISC2_BASE)
#define VC_AHBMISC                      ((VC_AHBMISC_TypeDef *) VC_AHBMISC_BASE)
#define VC_MISC2_FPGA                   ((VC_MISC2_FPGA_TypeDef *) VC_MISC2_FPGA_BASE)
#define VC_KEYSCAN                      ((VC_KEYSCAN_TypeDef *) VC_KEYSCAN_BASE)
#define VC_PLC_PHY                      ((VC_PLC_PHY_TypeDef *) VC_PLC_PHY_BASE)

#ifdef __cplusplus
}
#endif

#endif // VC6330_H
