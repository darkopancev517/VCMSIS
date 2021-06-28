/**************************************************************************//**
 * @file     system_vc7300.c
 * @brief    CMSIS Device System Source File for
 *           VC7300 Device
 * @version  V1.0.0
 * @date     28. June 2021
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

#include "vc7300.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define  SYSTEM_CLOCK       (39321600UL) /* 39.3216 MHz */

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

void SystemInit(void)
{
#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
  SCB->VTOR = (uint32_t) &(__VECTOR_TABLE[0]);
#endif

  SystemCoreClock = SYSTEM_CLOCK; /* 39.3216 MHz */

  /* Initialize VC7300 using internal HFRC0 */
  uint32_t temp = VC_MISC2->CLKSEL;
  temp &= ~VC_MISC2_CLKSEL_CLKSEL_Msk;
  temp |= (0UL << VC_MISC2_CLKSEL_CLKSEL_Pos); /* 0: Internal HFRC0, 1: RTCLK */
  VC_MISC2->CLKSEL = temp;

  /* Set current selection to 200nA */
  temp = VC_ANA->CLKCTRL1;
  temp &= ~VC_ANA_CLKCTRL1_LFXO_CURSEL_Msk;
  temp |= (1UL << VC_ANA_CLKCTRL1_LFXO_CURSEL_Pos); /* 1: 200nA, 0: 400nA */
  VC_ANA->CLKCTRL1 = temp;

  /* Set HFRCO high frequency mode */
  temp = VC_ANA->CLKCTRL2;
  temp &= ~VC_ANA_CLKCTRL2_HFRCO_HF_Msk;
  temp |= (1UL << VC_ANA_CLKCTRL2_HFRCO_HF_Pos); /* 1: HF mode, 0: LF mode */
  VC_ANA->CLKCTRL2 = temp;

  /* Wait until clock is stable */
  while ((VC_PMU->STS & VC_PMU_STS_EXIST_32K_Msk) == 0);
  while ((VC_ANA->CLKCTRL4 & VC_ANA_CLKCTRL4_AC_LOCK_Msk) == 0);

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

  /* Config analog LFXO capacitor selection */
  temp = VC_ANA->CLKCTRL1;
  temp &= ~VC_ANA_CLKCTRL1_LFXO_CSEL_Msk;
  temp |= (4UL << VC_ANA_CLKCTRL1_LFXO_CSEL_Pos); /* 12pF */
  VC_ANA->CLKCTRL1 = temp;

  /* Config ANA_LDOCTRL */
  temp = VC_ANA->LDOCTRL;
  temp &= ~VC_ANA_LDOCTRL_VDD3_FON_Msk;
  temp &= ~VC_ANA_LDOCTRL_LPLDO15_VSEL_SLP_Msk;
  temp |= (1UL << VC_ANA_LDOCTRL_VDD3_FON_Pos); /* Enabled */
  temp |= (0x2UL << VC_ANA_LDOCTRL_LPLDO15_VSEL_SLP_Pos); /* 1.3V */
  VC_ANA->LDOCTRL = temp;

  /* Config powerup delay */
  temp = VC_MISC2->PWRUPDLY;
  temp &= ~VC_MISC2_PWRUPDLY_PWRUPDLY_Msk;
  temp |= VC_MISC2_PWRUPDLY_PWRUPDLY_DELAY(0x3F); /* 63 PCLKs delay */
  VC_MISC2->PWRUPDLY = temp;

  /* Disable watchdog timer */
  VC_PMU->WDTPASS = (0xAA5555AA << VC_PMU_WDTPASS_UNLOCK_Pos);
  VC_PMU->WDTEN = (0UL << VC_PMU_WDTEN_WDTEN_Pos); /* Disabled */

  /* Enable default AHB peripheral clock */
  temp = VC_MISC2->HCLKEN;
  temp &= ~VC_MISC2_HCLKEN_HCLKEN_Msk;
  temp |= (1UL << VC_MISC2_HCLKEN_GPIO_Pos); /* Enabled GPIO clock */
  temp |= (1UL << VC_MISC2_HCLKEN_MEM_Pos); /* Enabled MEM clock */
  VC_MISC2->CLKEN_UNLOCK = (0x55AAAA55 << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos);
  VC_MISC2->HCLKEN = temp;

  /* Enable default APB peripheral clock */
  temp = VC_MISC2->PCLKEN;
  temp &= ~VC_MISC2_PCLKEN_PCLKEN_Msk;
  temp |= (1UL << VC_MISC2_PCLKEN_MISC_Pos); /* Enabled MISC clock */
  temp |= (1UL << VC_MISC2_PCLKEN_MISC2_Pos); /* Enabled MISC2 clock */
  temp |= (1UL << VC_MISC2_PCLKEN_PMU_Pos); /* Enabled PMU clock */
  temp |= (1UL << VC_MISC2_PCLKEN_ANA_Pos); /* Enabled ANA clock */
  VC_MISC2->CLKEN_UNLOCK = (0x55AAAA55 << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos);
  VC_MISC2->PCLKEN = temp;

  /* Wait until clock is stable */
  while ((VC_PMU->STS & VC_PMU_STS_EXIST_32K_Msk) == 0);
  while ((VC_ANA->CLKCTRL4 & VC_ANA_CLKCTRL4_AC_LOCK_Msk) == 0);
}
