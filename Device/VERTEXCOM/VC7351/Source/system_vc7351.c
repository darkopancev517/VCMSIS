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

void SystemInit(void)
{
#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
  SCB->VTOR = (uint32_t) &(__VECTOR_TABLE[0]);
#endif

  SystemCoreClock = SYSTEM_CLOCK;

  /* Set AHB clock divider */
  uint32_t temp = VC_MISC2->CLKDIVH;
  temp &= ~VC_MISC2_CLKDIVH_CLKDIVH_Msk;
  temp |= VC_MISC2_CLKDIVH_CLKDIVH_DIV(1);
  VC_MISC2->CLKDIVH = temp;

  /* Set APB clock divider */
  temp = VC_MISC2->CLKDIVP;
  temp &= ~VC_MISC2_CLKDIVP_CLKDIVP_Msk;
  temp |= VC_MISC2_CLKDIVP_CLKDIVP_DIV(2);
  VC_MISC2->CLKDIVP = temp;

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

  /* Disable watchdog timer */
  VC_PMU->WDTPASS = (0xAA5555AA << VC_PMU_WDTPASS_UNLOCK_Pos);
  VC_PMU->WDTEN = (0UL << VC_PMU_WDTEN_WDTEN_Pos); /* Disabled */
}
