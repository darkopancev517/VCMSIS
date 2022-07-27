/**************************************************************************//**
 * @file     system_vc6330.c
 * @brief    CMSIS Device System Source File for
 *           VC6330 Device
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

#include "vc6330.h"

#include "vc_ana.h"
#include "vc_flash.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define SYSTEM_CLOCK        (25000000) /* 25 MHz */

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
extern const void *_isr_vectors;

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
    SCB->VTOR = (uint32_t)&_isr_vectors;
#endif

    uint32_t temp = 0;

    /* ----------- System Clock setting */

    SystemCoreClock = SYSTEM_CLOCK;

    /* ----------- Watchdog setting */

    /* Disable watchdog timer */
    VC_PMU->WDTPASS = (0xAA5555AA << VC_PMU_WDTPASS_UNLOCK_Pos);
    VC_PMU->WDTEN = (0UL << VC_PMU_WDTEN_WDTEN_Pos); /* Disabled */

    /* ----------- MISC setting */

    /* Set clock using xtal 25MHz */
    temp = VC_MISC2->CLKSEL;
    temp &= ~VC_MISC2_CLKSEL_CLKSEL_Msk;
    temp |= VC_MISC2_CLKSEL_CLKSEL_XTAL25M;
    VC_MISC2->CLKSEL = temp;

    /* Set AHB clock divider to 1: AHB clock 25 MHz */
    temp = VC_MISC2->CLKDIVH;
    temp &= ~VC_MISC2_CLKDIVH_CLKDIVH_Msk;
    temp |= VC_MISC2_CLKDIVH_CLKDIVH_DIV(1);
    VC_MISC2->CLKDIVH = temp;

    /* Set APB clock divider to 4: APB clock 6.25 MHz*/
    temp = VC_MISC2->CLKDIVP;
    temp &= ~VC_MISC2_CLKDIVP_CLKDIVP_Msk;
    temp |= VC_MISC2_CLKDIVP_CLKDIVP_DIV_4;
    VC_MISC2->CLKDIVP = temp;

    /* Set APB clock divider */

    /* ----------- FLASH setting */

    vcflash_disable_cache();
    vcflash_quad_enable();

    temp = VC_MEM->FLASH_CFG;
    temp &= ~VC_MEM_FLASH_CFG_SIZE_Msk;
    temp &= ~VC_MEM_FLASH_CFG_MEMMODE_Msk;
    temp |= (5UL << VC_MEM_FLASH_CFG_SIZE_Pos);     /* SIZE   : 16Mbits */
    temp |= (5UL << VC_MEM_FLASH_CFG_MEMMODE_Pos);  /* MEMMODE: 4IO Mode */

    VC_MEM->FLASH_CFG = temp;

    vcflash_enable_cache();

    /* ----------- Peripheral Clock setting */

    /* Note: by default all peripheral clock was enabled */

    /* VC_MISC2->HCLKEN : default (0xFFFF) */
    /* VC_MISC2->PLCKEN : default (0xFFFFFFFF) */

    /* TODO: Turn off some of the unused peripheral clock to reduce
    *       power consumption */
}
