/*************************************************************************//**
 * @file     <vc7351>.h
 * @brief    CMSIS-Core(M) Device Peripheral Access Layer Header File for
 *           VC7351 Device
 * @version  V1.0.0
 * @date     29. June 2021
 *****************************************************************************/
/*
 * Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved.
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

#ifndef VC7351_H
#define VC7351_H

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================= */
/* ============           Interrupt Number Definition           ============ */
/* ========================================================================= */

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

/* ================        VC7351   Interrupt Numbers       ================ */
  PMU_IRQn               = 0,
  RTC_IRQn               = 1,
  UART32K0_IRQn          = 2,
  UART32K1_IRQn          = 3,
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
  FLASH_IRQn             = 23,
  ANA_IRQn               = 24,

  SPI2_IRQn              = 27,
  SPI3_IRQn              = 28,
  KEYSCAN_IRQn           = 29,
  UART6_IRQn             = 30,
  CRYPTO_IRQn            = 31,

  I2C2_IRQn              = 36,
  GPIO_IRQn              = 37,
  MSGBOX_IRQn            = 38,

  BPDET_IRQn             = 40,
  SDIO_IRQn              = 41
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

/* TODO: Update PMU information */
#define __PMU_PRESENT           0U       /* Set to 1 if PMU is present */
#define __PMU_NUM_EVENTCNT      0U       /* Set number of PMU Event Counters */

#define __ICACHE_PRESENT        0U       /* Set to 1 if I-Cache is present */
#define __DCACHE_PRESENT        0U       /* Set to 1 if D-Cache is present */
#define __DTCM_PRESENT          0U       /* Set to 1 if DTCM is present */

#include <core_cm3.h>                    /* Processor and core peripherals */
#include "system_vc7351.h"               /* System Header */

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
  __IM uint32_t  RESERVED[4];
  __IM uint32_t  VERSIONID;             /* (0x003C) Version id of sirius register */
  __IOM uint32_t WDTPASS;               /* (0x0040) Watchdog timer unlock register */
  __IOM uint32_t WDTEN;                 /* (0x0044) Watchdog timer enable register */
  __OM uint32_t  WDTCLR;                /* (0x0048) Watchdog timer clear register */
  __IOM uint32_t WDTSTS;                /* (0x004C) Watchdog timer status register */
  __IOM uint32_t IOANODEG;              /* (0x0050) IOA no-deglitch control register */
  __IOM uint32_t IOASEL0;               /* (0x0054) IOA special function select register 0 */
  __IOM uint32_t IOASEL1;               /* (0x0058) IOA special function select register 1 */
  __IM uint32_t  RESERVED1[3];

  __IOM uint32_t REMAP;                 /* (0x0068) Re-map control register */
  __IOM uint32_t REMAPPASS;             /* (0x006C) Re-map password register */
  __IM uint32_t  STRAP;                 /* (0x0070) Boot strap status register */
  __IM uint32_t  RESERVED2[3];
  __IOM uint32_t PDOWNEN;               /* (0x0080) PMU power down enable register */
  __IOM uint32_t SPIPEN;                /* (0x0084) SPI probe pin enable register */
  __IM uint32_t  RESERVED3[31];
  __IOM uint32_t RG_LDO_CTRL;           /* (0x0104) LDO 1.2V control register */
  __IOM uint32_t RG_BUCK_CTRL;          /* (0x0108) BUCK 1.2V control register */
  __IOM uint32_t RG_LDODX_CTRL;         /* (0x010C) LDODX 1.2V control register */
  __IM uint32_t  RESERVED4[64];
  __IOM uint32_t PMURCO1MCTRL;          /* (0x0210) BUCK 1M control register */
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

#define VC_PMU_CTRL_RTCLK_SEL_Pos               1
#define VC_PMU_CTRL_RTCLK_SEL_Msk               (1UL << VC_PMU_CTRL_RTCLK_SEL_Pos)

#define VC_PMU_CTRL_INT_32K_EN_Pos              2
#define VC_PMU_CTRL_INT_32K_EN_Msk              (1UL << VC_PMU_CTRL_INT_32K_EN_Pos)

#define VC_PMU_CTRL_INT_48M_EN_Pos              3
#define VC_PMU_CTRL_INT_48M_EN_Msk              (1UL << VC_PMU_CTRL_INT_48M_EN_Pos)

#define VC_PMU_CTRL_PD_WKUEN_Pos                6
#define VC_PMU_CTRL_PD_WKUEN_Msk                (1UL << VC_PMU_CTRL_PD_WKUEN_Pos)

#define VC_PMU_CTRL_PWUPCYC_Pos                 8
#define VC_PMU_CTRL_PWUPCYC_Msk                 (0xFFUL << VC_PMU_CTRL_PWUPCYC_Pos)

#define VC_PMU_CTRL_NOWAITLOCK_Pos              17
#define VC_PMU_CTRL_NOWAITLOCK_Msk              (1UL << VC_PMU_CTRL_NOWAITLOCK_Pos)

#define VC_PMU_CTRL_INTWKUEN_Pos                18
#define VC_PMU_CTRL_INTWKUEN_Msk                (1UL << VC_PMU_CTRL_INTWKUEN_Pos)

#define VC_PMU_CTRL_FSEL32KXTAL_Pos             19
#define VC_PMU_CTRL_FSEL32KXTAL_Msk             (1UL << VC_PMU_CTRL_FSEL32KXTAL_Pos)

#define VC_PMU_CTRL_FCLKSELRCH_Pos              20
#define VC_PMU_CTRL_FCLKSELRCH_Msk              (1UL << VC_PMU_CTRL_FCLKSELRCH_Pos)

/* PMU_STS register */
#define VC_PMU_STS_INT_32K_Pos                  0
#define VC_PMU_STS_INT_32K_Msk                  (1UL << VC_PMU_STS_INT_32K_Pos)

#define VC_PMU_STS_INT_48M_Pos                  1
#define VC_PMU_STS_INT_48M_Msk                  (1UL << VC_PMU_STS_INT_48M_Pos)

#define VC_PMU_STS_EXIST_32K_Pos                2
#define VC_PMU_STS_EXIST_32K_Msk                (1UL << VC_PMU_STS_EXIST_32K_Pos)

#define VC_PMU_STS_EXIST_48M_Pos                3
#define VC_PMU_STS_EXIST_48M_Msk                (1UL << VC_PMU_STS_EXIST_48M_Pos)

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

#define VC_PMU_STS_MODERST_Pos                  11
#define VC_PMU_STS_MODERST_Msk                  (1UL << VC_PMU_STS_MODERST_Pos)

#define VC_PMU_STS_WKUIOA_Pos                   16
#define VC_PMU_STS_WKUIOA_Msk                   (1UL << VC_PMU_STS_WKUIOA_Pos)

#define VC_PMU_STS_WKURTC_Pos                   17
#define VC_PMU_STS_WKURTC_Msk                   (1UL << VC_PMU_STS_WKURTC_Pos)

#define VC_PMU_STS_WKUANA_Pos                   18
#define VC_PMU_STS_WKUANA_Msk                   (1UL << VC_PMU_STS_WKUANA_Pos)

#define VC_PMU_STS_WKUUART32K_Pos               19
#define VC_PMU_STS_WKUUART32K_Msk               (1UL << VC_PMU_STS_WKUUART32K_Pos)

#define VC_PMU_STS_WKUXTAL_Pos                  20
#define VC_PMU_STS_WKUXTAL_Msk                  (1UL << VC_PMU_STS_WKUXTAL_Pos)

#define VC_PMU_STS_WKUPU_Pos                    21
#define VC_PMU_STS_WKUPU_Msk                    (1UL << VC_PMU_STS_WKUPU_Pos)

#define VC_PMU_STS_WKUMODE_Pos                  22
#define VC_PMU_STS_WKUMODE_Msk                  (1UL << VC_PMU_STS_WKUMODE_Pos)

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

/* PMU_PDOWNEN register */
#define VC_PMU_PDOWNEN_PDOWN_Pos                0
#define VC_PMU_PDOWNEN_PDOWN_Msk                (1UL << VC_PMU_PDOWNEN_PDOWN_Pos)

#define VC_PMU_PDOWNEN_WKU_Pos                  31
#define VC_PMU_PDOWNEN_WKU_Msk                  (1UL << VC_PMU_PDOWNEN_WKU_Pos)

/* PMU_SPIPEN register */
#define VC_PMU_SPIPEN_SPIPEN_Pos                0
#define VC_PMU_SPIPEN_SPIPEN_Msk                (1UL << VC_PMU_SPIPEN_SPIPEN_Pos)

/* RG_LDO_CTRL register */
#define VC_PMU_RG_LDO_VOUT_SEL_Pos              0
#define VC_PMU_RG_LDO_VOUT_SEL_Msk              (0x7UL << VC_PMU_RG_LDO_VOUT_SEL_Pos)

/* RG_BUCK_CTRL register */
#define VC_PMU_RG_BUCK_VOUT_SEL_Pos             0
#define VC_PMU_RG_BUCK_VOUT_SEL_Msk             (0x7UL << VC_PMU_RG_BUCK_VOUT_SEL_Pos)

#define VC_PMU_RG_BUCK_TRIMVOL_Pos              3
#define VC_PMU_RG_BUCK_TRIMVOL_Msk              (0x7UL << VC_PMU_RG_BUCK_TRIMVOL_Pos)

#define VC_PMU_RG_BUCK_TRIMVOL_EN_Pos           6
#define VC_PMU_RG_BUCK_TRIMVOL_EN_Msk           (1UL << VC_PMU_RG_BUCK_TRIMVOL_EN_Pos)

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

/* RG_LDODX_CTRL register */
#define VC_PMU_RG_LDODX_EN_Pos                  0
#define VC_PMU_RG_LDODX_EN_Msk                  (1UL << VC_PMU_RG_LDODX_EN_Pos)

#define VC_PMU_RG_LDODX_VOUTSEL_Pos             1
#define VC_PMU_RG_LDODX_VOUTSEL_Msk             (0x7UL << VC_PMU_RG_LDODX_VOUTSEL_Pos)

/* PMU_RCO1MCTRL register */
#define VC_PMU_FM_EN_Pos                        0
#define VC_PMU_FM_EN_Msk                        (1UL << VC_PMU_FM_EN_Pos)

#define VC_PMU_WIN_Pos                          1
#define VC_PMU_WIN_Msk                          (0x3UL << VC_PMU_WIN_Pos)

#define VC_PMU_FSEL_Pos                         3
#define VC_PMU_FSEL_Msk                         (0x3UL << VC_PMU_FSEL_Pos)

#define VC_PMU_BIN_MODE_Pos                     5
#define VC_PMU_BIN_MODE_Msk                     (1UL << VC_PMU_BIN_MODE_Pos)

#define VC_PMU_RCO100K_RCODE_MAN_Pos            6
#define VC_PMU_RCO100K_RCODE_MAN_Msk            (1UL << VC_PMU_RCO100K_RCODE_MAN_Pos)

#define VC_PMU_FM_DONE_Pos                      8
#define VC_PMU_FM_DONE_Msk                      (1UL << VC_PMU_FM_DONE_Pos)

#define VC_PMU_FM_FAIL_Pos                      9
#define VC_PMU_FM_FAIL_Msk                      (1UL << VC_PMU_FM_FAIL_Pos)

/* ========================================================================= */
/* ============                Analog Controller                ============ */
/* ========================================================================= */

typedef struct
{
  __IOM uint32_t RG_HFXO_CTRL;              /* (0x0000) HFXO control register */
  __IOM uint32_t RG_GPPLL_CTRL0;            /* (0x0004) General purpose PLL control0 register */
  __IOM uint32_t RG_GPPLL_CTRL1;            /* (0x0008) General purpose PLL control1 register */
  __IOM uint32_t RG_BBPLL_CTRL;             /* (0x000C) BBPLL control register */
  __IOM uint32_t RG_LFXO_CTRL;              /* (0x0010) LFXO control register */
  __IOM uint32_t RG_LFRCO_CTRL;             /* (0x0014) LFRCO control register */
  __IM uint32_t  RESERVED[2];
  __IOM uint32_t CMP1CTRL;                  /* (0x0020) Comparator 1 control register */
  __IOM uint32_t CMP2CTRL;                  /* (0x0024) Comparator 2 control register */
  __IOM uint32_t CMP1CNT;                   /* (0x0028) Comparator 1 counter */
  __IOM uint32_t CMP2CNT;                   /* (0x002C) Comparator 2 counter */
  __IOM uint32_t TRNGCTRL;                  /* (0x0030) True random number generator control register */
  __IM uint32_t  TNRGDATA;                  /* (0x0034) True random number generator data register */
  __IOM uint32_t PRNGDATA;                  /* (0x0038) Pseudo random number generator data register */
  __IM uint32_t  RESERVED1[2];
  __IOM uint32_t RSV2;                      /* (0x0044) Analog reserved register 2 */
  __IM uint32_t  RESERVED2[2];
  __IM uint32_t  CTRL;                      /* (0x0050) Analog control register */
  __IM uint32_t  RESERVED3[3];
  __IOM uint32_t INTSTS;                    /* (0x0060) Analog interrupt status register */
  __IOM uint32_t INTEN;                     /* (0x0064) Analog interrupt enable register */
  __IM uint32_t  RESERVED4[42];
  __IOM uint32_t RG_SOC_BBPLL_CTRL;         /* (0x0110) SOC BBPLL control register */
  __IOM uint32_t RG_SOC_BBPLL_DDSMIN;       /* (0x0114) SOC BBPLL DDSMIN register */
  __IOM uint32_t RG_SOC_BBPLL_OFFSETIN;     /* (0x0118) SOC BBPLL OFFSETIN register */
  __IOM uint32_t RG_SOC_BBPLL_TESTIN;       /* (0x011C) SOC BBPLL TESTIN register */
  __IM uint32_t  RG_SOC_BBPLL_PROBE;        /* (0x0120) SOC BBPLL PROBE register */
  __IOM uint32_t RG_SOC_BBPLL_METER_CTRL;   /* (0x0124) SOC BBPLL METER control register */
  __IM uint32_t  RESERVED5[2];
  __IOM uint32_t RG_AUXSAR_CTRL;            /* (0x0130) AUXSAR control register */
  __IM uint32_t  RESERVED6[3];
  __IOM uint32_t ADCCTRL;                   /* (0x0140) ADC control register */
  __IOM uint32_t ADCMCHEN;                  /* (0x0144) ADC channel enable on manual mode register */
  __IOM uint32_t ADCDATA;                   /* (0x0148) ADC Data register */
  __IOM uint32_t ADCACHEN;                  /* (0x014C) ADC channel enable auto trigger mode */
  __IOM uint32_t ADCDATA4_15[12];           /* (0x0150 - 0x017C) ADC CH4 - CH15 Data register */
  __IOM uint32_t ADCDATA0_3[4];             /* (0x0180 - 0x018C) ADC CH0 - CH3 Data register */
  __IM uint32_t  RESERVED7;
  __IOM uint32_t RG_RFLDO_CTRL;             /* (0x0194) RF LDO control register */
  __IOM uint32_t RG_LVD_CTRL;               /* (0x0198) LVD control register */
  __IOM uint32_t RG_ANABG_CTRL;             /* (0x019C) Bandgap control register */
  __IM uint32_t  RESERVED8[24];
  __IOM uint32_t RG_HFRCO_CTRL0;            /* (0x0200) HFRCO control0 register */
  __IOM uint32_t RG_HFRCO_CTRL1;            /* (0x0204) HFRCO control1 register */
  __IOM uint32_t RG_HFRCO_CTRL2;            /* (0x0208) HFRCO control2 register */
  __IM uint32_t  RESERVED9;
  __IOM uint32_t RG_BISTPLL_CTRL0;          /* (0x0210) BIST PLL control0 register */
  __IOM uint32_t RG_BISTPLL_CTRL1;          /* (0x0214) BIST PLL control1 register */
  __IOM uint32_t RG_BISTPLL_METER_CTRL;     /* (0x0218) BIST PLL METER control register */
  __IM uint32_t  RESERVED10;
  __IOM uint32_t RG_CKO_CTRL;               /* (0x0220) CKO control register */
} VC_ANA_TypeDef;


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
#define VC_ANA_BASE                     (0x4004B000UL)
#define VC_RTC_BASE                     (0x40049000UL)
#define VC_MEM_BASE                     (0x40020000UL)
#define VC_GPIOA_BASE                   (0x40048010UL)
#define VC_GPIOB_BASE                   (0x40000040UL)
#define VC_GPIOC_BASE                   (0x40000080UL)
#define VC_GPIOD_BASE                   (0x400000C0UL)
#define VC_GPIOE_BASE                   (0x40000100UL)
#define VC_GPIOF_BASE                   (0x40000140UL)
#define VC_GPIOG_BASE                   (0x40000180UL)
#define VC_GPIOMISC_BASE                (0x40000200UL)
#define VC_DMA_BASE                     (0x40040000UL)
#define VC_UART0_BASE                   (0x40043000UL)
#define VC_UART1_BASE                   (0x40043040UL)
#define VC_UART2_BASE                   (0x40043080UL)
#define VC_UART3_BASE                   (0x400430C0UL)
#define VC_UART4_BASE                   (0x40043100UL)
#define VC_UART5_BASE                   (0x40043140UL)
#define VC_UART6_BASE                   (0x40043180UL)
#define VC_UART32K0_BASE                (0x4004C000UL)
#define VC_UART32K1_BASE                (0x4004C040UL)
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
#define VC_KEYSCAN_BASE                 (0x4004D000UL)

/* ========================================================================= */
/* ============             Peripheral declaration              ============ */
/* ========================================================================= */

#define VC_PMU                          ((VC_PMU_TypeDef *) VC_PMU_BASE)
#define VC_ANA                          ((VC_ANA_TypeDef *) VC_ANA_BASE)
#define VC_RTC                          ((VC_RTC_TypeDef *) VC_RTC_BASE)
#define VC_MEM                          ((VC_MEM_TypeDef *) VC_MEM_BASE)
#define VC_GPIOA                        ((VC_GPIOA_TypeDef *) VC_GPIOA_BASE)
#define VC_GPIOB                        ((VC_GPIOB_TypeDef *) VC_GPIOB_BASE)
#define VC_GPIOC                        ((VC_GPIOC_TypeDef *) VC_GPIOC_BASE)
#define VC_GPIOD                        ((VC_GPIOD_TypeDef *) VC_GPIOD_BASE)
#define VC_GPIOE                        ((VC_GPIOE_TypeDef *) VC_GPIOE_BASE)
#define VC_GPIOF                        ((VC_GPIOF_TypeDef *) VC_GPIOF_BASE)
#define VC_GPIOG                        ((VC_GPIOG_TypeDef *) VC_GPIOG_BASE)
#define VC_GPIOMISC                     ((VC_GPIOMISC_TypeDef *) VC_GPIOMISC_BASE)
#define VC_DMA                          ((VC_DMA_TypeDef *) VC_DMA_BASE)
#define VC_UART0                        ((VC_UART_TypeDef *) VC_UART0_BASE)
#define VC_UART1                        ((VC_UART_TypeDef *) VC_UART1_BASE)
#define VC_UART2                        ((VC_UART_TypeDef *) VC_UART2_BASE)
#define VC_UART3                        ((VC_UART_TypeDef *) VC_UART3_BASE)
#define VC_UART4                        ((VC_UART_TypeDef *) VC_UART4_BASE)
#define VC_UART5                        ((VC_UART_TypeDef *) VC_UART5_BASE)
#define VC_UART6                        ((VC_UART_TypeDef *) VC_UART6_BASE)
#define VC_UART32K0                     ((VC_UART32K_TypeDef *) VC_UART32K0_BASE)
#define VC_UART32K1                     ((VC_UART32K_TypeDef *) VC_UART32K1_BASE)
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
#define VC_I2C1                         ((VC_I2C_TypeDef *) VC_I2C1_BASE)
#define VC_I2C2                         ((VC_I2C_TypeDef *) VC_I2C2_BASE)
#define VC_MISC                         ((VC_MISC_TypeDef *) VC_MISC_BASE)
#define VC_MISC2                        ((VC_MISC2_TypeDef *) VC_MISC2_BASE)
#define VC_KEYSCAN                      ((VC_KEYSCAN_TypeDef *) VC_KEYSCAN_BASE)

#ifdef __cplusplus
}
#endif

#endif /* VC7351_H */
