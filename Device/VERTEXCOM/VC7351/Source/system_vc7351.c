/**************************************************************************//**
 * @file     system_vc7351.c
 * @brief    CMSIS Device System Source File for
 *           VC7351 Device
 * @version  V1.0.0
 * @date     30. June 2021
 ******************************************************************************/
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

#include "vc7351.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define  SYSTEM_CLOCK       (120000000) /* 120 MHz */

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
extern const VECTOR_TABLE_Type __VECTOR_TABLE[64];

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYSTEM_CLOCK;  /* System Core Clock Frequency */

/*----------------------------------------------------------------------------
  System Core Clock update function
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate(void)
{
    SystemCoreClock = SYSTEM_CLOCK;
}

static void vcAnaInit(void);
static void vcAnaSetGPPLL_120MHz(void);
static void vcAnaSetBBPLL_192MHz(void);

static void vcFlashDisableCache(void);
static void vcFlashEnableCache(void);
static void vcFlashWriteEnable(void);
static uint32_t vcFlashGetManuID(void);
static void vcFlashQuadEnable(void);

void SystemInit(void)
{
#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
  SCB->VTOR = (uint32_t) &(__VECTOR_TABLE[0]);
#endif

  uint32_t temp = 0;

  /* ----------- System Clock setting */

  vcAnaInit();
  vcAnaSetGPPLL_120MHz();
  SystemCoreClock = SYSTEM_CLOCK; /* 120 MHz */
  vcAnaSetBBPLL_192MHz();

  /* ----------- FLASH setting */

  vcFlashDisableCache();
  vcFlashQuadEnable();

  temp = VC_MEM->FLASH_CFG;
  temp &= ~VC_MEM_FLASH_CFG_CMDCLK_Msk;
  temp &= ~VC_MEM_FLASH_CFG_MEMCLK_Msk;
  temp &= ~VC_MEM_FLASH_CFG_SIZE_Msk;
  temp &= ~VC_MEM_FLASH_CFG_MEMMODE_Msk;
  temp &= ~VC_MEM_FLASH_CFG_CMDLAT_Msk;
  temp &= ~VC_MEM_FLASH_CFG_MEMLAT_Msk;
  temp |= (1UL << VC_MEM_FLASH_CFG_CMDCLK_Pos);   /* CMDCLK : HCLK/2 */
  temp |= (0UL << VC_MEM_FLASH_CFG_MEMCLK_Pos);   /* MEMCLK : HCLK/1 */
  temp |= (5UL << VC_MEM_FLASH_CFG_SIZE_Pos);     /* SIZE   : 16Mbits */
  temp |= (5UL << VC_MEM_FLASH_CFG_MEMMODE_Pos);  /* MEMMODE: 4IO Mode */
  temp |= (1UL << VC_MEM_FLASH_CFG_CMDLAT_Pos);   /* CMDLAT : 0.5 Cycle after falling edge of internal SPICLK */
  temp |= (1UL << VC_MEM_FLASH_CFG_MEMLAT_Pos);   /* MEMLAT : 0.5 Cycle after falling edge of internal SPICLK */
  VC_MEM->FLASH_CFG = temp;

  vcFlashEnableCache();

  /* ----------- MISC setting */

  /* Set AHB clock divider */
  temp = VC_MISC2->CLKDIVH;
  temp &= ~VC_MISC2_CLKDIVH_CLKDIVH_Msk;
  temp |= VC_MISC2_CLKDIVH_CLKDIVH_DIV(1);
  VC_MISC2->CLKDIVH = temp;

  /* Set APB clock divider */
  temp = VC_MISC2->CLKDIVP;
  temp &= ~VC_MISC2_CLKDIVP_CLKDIVP_Msk;
  temp |= VC_MISC2_CLKDIVP_CLKDIVP_DIV(2);
  VC_MISC2->CLKDIVP = temp;

  /* ----------- RTC setting */

  /* Disable RTC write protection */
  VC_RTC->PWD = (0x5AA55AA5 << VC_RTC_PWD_PWDEN_Pos);
  VC_RTC->CE = (0xA55AA55B << VC_RTC_CE_CE_Pos);
  while ((VC_RTC->CE & VC_RTC_CE_BSY_Msk) != 0);

  /* Always calibrate RTC  */
  temp = VC_RTC->CAL;
  temp &= ~VC_RTC_CAL_CAL_Msk;
  temp |= (1 << VC_RTC_CAL_CAL_Pos);
  VC_RTC->CAL = temp;

  /* Enable RTC write protection */
  VC_RTC->PWD = (0x5AA55AA5 << VC_RTC_PWD_PWDEN_Pos);
  VC_RTC->CE = (0xA55AA55A << VC_RTC_CE_CE_Pos);
  while ((VC_RTC->CE & VC_RTC_CE_BSY_Msk) != 0);

  /* ----------- Watchdog setting */

  /* Disable watchdog timer */
  VC_PMU->WDTPASS = (0xAA5555AA << VC_PMU_WDTPASS_UNLOCK_Pos);
  VC_PMU->WDTEN = (0UL << VC_PMU_WDTEN_WDTEN_Pos); /* Disabled */

  /* ----------- Peripheral Clock setting */

  /* Note: by default all peripheral clock was enabled */

  /* VC_MISC2->HCLKEN : default (0xFFFF) */
  /* VC_MISC2->PLCKEN : default (0xFFFFFFFF) */

  /* TODO: Turn off some of the unused peripheral clock to reduce
   *       power consumption */
}

void vcAnaInit(void)
{
  uint32_t temp = VC_ANA->RG_LFXO_CTRL;
  temp &= ~VC_ANA_RG_LFXO_CURSEL_Msk;
  temp &= ~VC_ANA_RG_LFXO_IBBG_EN_Msk;
  temp |= (0x3UL << VC_ANA_RG_LFXO_CURSEL_Pos);       /* CURSEL: 500nA */
  temp |= (0UL << VC_ANA_RG_LFXO_IBBG_EN_Pos);        /* CURSOURCE: ANABG */
  VC_ANA->RG_LFXO_CTRL = temp;

  temp = VC_ANA->RG_LFRCO_CTRL;
  temp &= ~VC_ANA_RG_LFRCO_RSEL_Msk;
  temp &= ~VC_ANA_RG_LFRCO_CSEL_Msk;
  temp |= (0xEUL << VC_ANA_RG_LFRCO_RSEL_Pos);        /* LFRCO resistor selection */
  temp |= (0x65UL << VC_ANA_RG_LFRCO_CSEL_Pos);       /* LFRCO capacitor selection */
  VC_ANA->RG_LFRCO_CTRL = temp;

  temp = VC_ANA->RG_HFXO_CTRL;
  temp &= ~VC_ANA_RG_HFXO_EN_Msk;
  temp |= (1UL << VC_ANA_RG_HFXO_EN_Pos);
  VC_ANA->RG_HFXO_CTRL = temp;

  temp = VC_ANA->RG_HFRCO_CTRL0;
  temp &= ~VC_ANA_RG_HFRCO_CTRL0_AC_PERIOD_Msk;
  temp |= (1UL << VC_ANA_RG_HFRCO_CTRL0_AC_PERIOD_Pos);
  VC_ANA->RG_HFRCO_CTRL0 = temp;

  temp = VC_ANA->RG_HFRCO_CTRL1;
  temp &= ~VC_ANA_RG_HFRCO_CTRL1_AC_TGT_Msk;
  temp |= (0x5B9UL << VC_ANA_RG_HFRCO_CTRL1_AC_TGT_Pos);
  VC_ANA->RG_HFRCO_CTRL1 = temp;

  VC_ANA->RG_LDO_CTRL = 0; /* setl RF LDO CTRL register to 0 */
}

void vcAnaSetGPPLL_120MHz(void)
{
  uint32_t temp = VC_ANA->RG_GPPLL_CTRL1;
  temp &= ~VC_ANA_RG_GPPLL_PREDIV_Msk;
  temp &= ~VC_ANA_RG_GPPLL_DDSM_IN_Msk;
  temp &= ~VC_ANA_RG_GPPLL_DDSM_EN_Msk;
  temp |= (1UL << VC_ANA_RG_GPPLL_PREDIV_Pos);
  temp |= (20UL << VC_ANA_RG_GPPLL_DDSM_IN_Integer_Pos);
  temp |= (0UL << VC_ANA_RG_GPPLL_DDSM_IN_Fraction_Pos);
  temp |= (0UL << VC_ANA_RG_GPPLL_DDSM_EN_Pos);
  VC_ANA->RG_GPPLL_CTRL1 = temp;

  temp = VC_ANA->RG_GPPLL_CTRL0;
  temp &= ~VC_ANA_RG_GPPLL_POSDIV_Msk;
  temp &= ~VC_ANA_RG_GPPLL_EN_Msk;
  temp |= (2UL << VC_ANA_RG_GPPLL_POSDIV_Pos);
  temp |= (1UL << VC_ANA_RG_GPPLL_EN_Pos);
  VC_ANA->RG_GPPLL_CTRL0 = temp;

  for (int i = 0; i < 0x1000; i++);

  temp = VC_MISC2->CLKSEL;
  temp &= ~VC_MISC2_CLKSEL_CLKSEL_Msk;
  temp |= (2UL << VC_MISC2_CLKSEL_CLKSEL_Pos); /* AHB clock source: GPLL */
  VC_MISC2->CLKSEL = temp;
}

void vcAnaSetBBPLL_192MHz(void)
{
  uint32_t timeout = 5000;

  /* Enable DDSM_TEST */
  uint32_t temp = VC_ANA->RG_SOC_BBPLL_CTRL;
  temp &= ~VC_ANA_RG_SOC_BBPLL_DDSM_TEST_Msk;
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_DDSM_TEST_Pos);
  VC_ANA->RG_SOC_BBPLL_CTRL = temp;

  /* Set DDSM_TESTIN */
  temp = VC_ANA->RG_SOC_BBPLL_TESTIN;
  temp &= ~VC_ANA_RG_SOC_BBPLL_TESTIN_Msk;
  temp |= (16UL << VC_ANA_RG_SOC_BBPLL_TESTIN_Integer_Pos);
  temp |= (0UL << VC_ANA_RG_SOC_BBPLL_TESTIN_Fraction_Pos);
  VC_ANA->RG_SOC_BBPLL_TESTIN = temp;

  /* Filled BBPLL parameter needed */
  temp = VC_ANA->RG_SOC_BBPLL_METER_CTRL;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FM_BINMODE_Msk;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_PLL_WAIT_TIME_Msk;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FNPLL_IBAND_RST_Msk;
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_METER_FM_BINMODE_Pos);
  temp |= (63UL << VC_ANA_RG_SOC_BBPLL_METER_PLL_WAIT_TIME_Pos);
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_METER_FNPLL_IBAND_RST_Pos);
  VC_ANA->RG_SOC_BBPLL_METER_CTRL = temp;

  temp = VC_ANA->RG_BBPLL_CTRL;
  temp &= ~VC_ANA_RG_BBPLL_PDADCCLK_EN_Msk;
  temp &= ~VC_ANA_RG_BBPLL_IR_Msk;
  temp &= ~VC_ANA_RG_BBPLL_IC_Msk;
  temp &= ~VC_ANA_RG_BBPLL_TXDACCLK_EN_Msk;
  temp &= ~VC_ANA_RG_BBPLL_IQADCCLK_EN_Msk;
  temp |= (1UL << VC_ANA_RG_BBPLL_PDADCCLK_EN_Pos);
  temp |= (3UL << VC_ANA_RG_BBPLL_IR_Pos);
  temp |= (1UL << VC_ANA_RG_BBPLL_IC_Pos);
  temp |= (1UL << VC_ANA_RG_BBPLL_TXDACCLK_EN_Pos);
  temp |= (1UL << VC_ANA_RG_BBPLL_IQADCCLK_EN_Pos);
  VC_ANA->RG_BBPLL_CTRL = temp;

  /* Enable BBPPLL */
  temp = VC_ANA->RG_BBPLL_CTRL;
  temp &= ~VC_ANA_RG_BBPLL_EN_Msk;
  temp |= (1UL << VC_ANA_RG_BBPLL_EN_Pos);
  VC_ANA->RG_BBPLL_CTRL;

  temp = VC_ANA->RG_SOC_BBPLL_METER_CTRL;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_MANU_IBAND_Msk;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FM_EN_Msk;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FNPLL_IBAND_RST_Msk;
  temp |= (8UL << VC_ANA_RG_SOC_BBPLL_METER_MANU_IBAND_Pos);
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_METER_FM_EN_Pos);
  temp |= (0UL << VC_ANA_RG_SOC_BBPLL_METER_FNPLL_IBAND_RST_Pos);
  VC_ANA->RG_SOC_BBPLL_METER_CTRL = temp;

  while (((VC_ANA->RG_SOC_BBPLL_METER_CTRL & VC_ANA_RG_SOC_BBPLL_METER_FM_DONE_Msk) == 0) && (--timeout))
  {
    for(int i = 0; i < 100000; i++);
  }

  /* Set DDSMIN */
  temp = VC_ANA->RG_SOC_BBPLL_DDSMIN;
  temp &= ~VC_ANA_RG_SOC_BBPLL_DDSMIN_Msk;
  temp |= (16UL << VC_ANA_RG_SOC_BBPLL_DDSMIN_Integer_Pos);
  temp |= (0UL << VC_ANA_RG_SOC_BBPLL_DDSMIN_Fraction_Pos);
  VC_ANA->RG_SOC_BBPLL_DDSMIN = temp;

  temp = VC_ANA->RG_BBPLL_CTRL;
  temp &= ~VC_ANA_RG_BBPLL_SOCCLK_DIV3_Msk;
  temp |= (0UL << VC_ANA_RG_BBPLL_SOCCLK_DIV3_Pos);
  VC_ANA->RG_BBPLL_CTRL = temp;

  /* Set OFFSET */
  temp = VC_ANA->RG_SOC_BBPLL_OFFSETIN;
  temp &= ~VC_ANA_RG_SOC_BBPLL_OFFSETIN_Msk;
  temp |= (0UL << VC_ANA_RG_SOC_BBPLL_OFFSETIN_Pos);
  VC_ANA->RG_SOC_BBPLL_OFFSETIN = temp;

  /* Enable DDSM */
  temp = VC_ANA->RG_SOC_BBPLL_CTRL;
  temp &= ~VC_ANA_RG_SOC_BBPLL_DDSM_TEST_Msk;
  temp &= ~VC_ANA_RG_SOC_BBPLL_DDSM_EN_Msk;
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_DDSM_TEST_Pos);
  temp |= (0UL << VC_ANA_RG_SOC_BBPLL_DDSM_EN_Pos);
  VC_ANA->RG_SOC_BBPLL_CTRL = temp;

  temp = VC_ANA->RG_SOC_BBPLL_METER_CTRL;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FM_MANUALSEL_Msk;
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_METER_FM_MANUALSEL_Pos);
  VC_ANA->RG_SOC_BBPLL_METER_CTRL = temp;
}

void vcFlashDisableCache(void)
{
  /* FLASH Disable Cache */
  uint32_t temp = VC_MEM->FLASH_CACHE;
  temp &= ~VC_MEM_FLASH_CACHE_EN_Msk;
  temp |= (0UL << VC_MEM_FLASH_CACHE_EN_Pos);
  VC_MEM->FLASH_CACHE = temp;
}

void vcFlashEnableCache(void)
{
  /* FLASH Enable Cache */
  uint32_t temp = VC_MEM->FLASH_CACHE;
  temp &= ~VC_MEM_FLASH_CACHE_EN_Msk;
  temp |= (1UL << VC_MEM_FLASH_CACHE_EN_Pos);
  VC_MEM->FLASH_CACHE = temp;
}

void vcFlashWriteEnable(void)
{
  /* FLASH Write Enable */
  uint32_t temp = 0;
  temp |= (1UL << VC_MEM_FLASH_CMD_ACT_Pos);
  temp |= (1UL << VC_MEM_FLASH_CMD_POLL_Pos);
  temp |= (0x6UL << VC_MEM_FLASH_CMD_CMDID_Pos); /* WINBOND_CMDID_WRITE_ENABLE: 0x6 */
  VC_MEM->FLASH_CMD = temp;
  while ((VC_MEM->FLASH_SR & VC_MEM_FLASH_SR_WEL_Msk) == 0);
}

uint32_t vcFlashGetManuID(void)
{
  uint32_t temp = VC_MEM->FLASH_ID;
  return (temp >> VC_MEM_FLASH_ID_MANU_ID_Pos);
}

void vcFlashQuadEnable(void)
{
  /* SPIFLASH QUAD ENABLE */
  while ((VC_MEM->FLASH_SR & VC_MEM_FLASH_SR_WIP_Msk) != 0);
  vcFlashWriteEnable();
  uint32_t temp = 0;
  temp |= (1UL << VC_MEM_FLASH_CMD_ACT_Pos);
  temp |= (1UL << VC_MEM_FLASH_CMD_CMDWR_Pos);
  temp |= (1UL << VC_MEM_FLASH_CMD_CMDDATA_Pos);
  temp |= (1UL << VC_MEM_FLASH_CMD_POLL_Pos);
  if (vcFlashGetManuID() == 0xEFUL)
  {
    /* WINBOND_CMDID_WSR2: 0x31 */
    temp |= (0x31UL << VC_MEM_FLASH_CMD_CMDID_Pos);
    temp |= (0UL << VC_MEM_FLASH_CMD_LENGTH_Pos);
    ((uint8_t *)(VC_MEM->FLASH_BUFx))[0] = 0x2U; /* Set QE: 1 */
  }
  else
  {
    /* GigaDevice GD_CMDID_WRSR: 0x1 */
    temp |= (0x1UL << VC_MEM_FLASH_CMD_CMDID_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_LENGTH_Pos);
    ((uint8_t *)(VC_MEM->FLASH_BUFx))[0] = 0x0U;
    ((uint8_t *)(VC_MEM->FLASH_BUFx))[1] = 0x2U; /* Set QE: 1 */
  }
  VC_MEM->FLASH_CMD = temp;
  while ((VC_MEM->FLASH_CMD & VC_MEM_FLASH_CMD_ACT_Msk) != 0);
}
