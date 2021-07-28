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

#include "xtimer.h"

void vc73xx_usticker_init(void)
{
    uint32_t temp = VC_MISC2->PCLKEN;
    temp |= (1UL << VC_MISC2_PCLKEN_TIMER_Pos);
    VC_MISC2->CLKEN_UNLOCK = (0x55AAAA55UL << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos);
    VC_MISC2->PCLKEN = temp;

    temp = VC_PWM0->CTL;
    temp &= ~VC_PWM_CTL_TSEL_Msk;
    temp &= ~VC_PWM_CTL_ID_Msk;
    temp |= (1UL << VC_PWM_CTL_TSEL_Pos);
    temp |= (6UL << VC_PWM_CTL_ID_Pos); /* SystemCoreClock / APBDIV / 64 = 120MHz / 2 / 64 = ~1MHz (0.9375MHz) */
    VC_PWM0->CTL = temp;

    vc73xx_usticker_start();
}

void vc73xx_usticker_start(void)
{
    uint32_t temp = VC_PWM0->CTL;
    temp &= ~VC_PWM_CTL_MC_Msk;
    temp |= (2UL << VC_PWM_CTL_MC_Pos); /* Continous Mode */
    VC_PWM0->CTL = temp;
}

void vc73xx_usticker_stop(void)
{
    uint32_t temp = VC_PWM0->CTL;
    temp &= ~VC_PWM_CTL_MC_Msk;
    VC_PWM0->CTL = temp;
}

void vc73xx_usticker_set(uint32_t value)
{
    /* config capture/compare register CCR period */
    VC_PWM0->CCR[0] = value;

    /* enable capture/compare interrupt */
    uint32_t temp = VC_PWM0->CCTL[0];
    temp &= ~VC_PWM_CCTL_CCIE_Msk;
    temp |= (1UL << VC_PWM_CCTL_CCIE_Pos);
    VC_PWM0->CCTL[0] = temp;

    NVIC_EnableIRQ(PWM0_IRQn);
}

void vc73xx_usticker_clear(void)
{
    /* clear capture/compare register period to it's default value */
    VC_PWM0->CCR[0] = VC_PWM_CCR_CCR_Msk;

    /* clear PWM counter */
    uint32_t temp = VC_PWM0->CTL;
    temp &= ~VC_PWM_CTL_CLR_Msk;
    temp |= (1UL << VC_PWM_CTL_CLR_Pos);
    VC_PWM0->CTL = temp;
}

uint32_t vc73xx_usticker_read(void)
{
    return VC_PWM0->TAR;
}

void PWM0_Handler(void)
{
    if ((VC_PWM0->CCTL[0] & VC_PWM_CCTL_CCIFG_Msk) != 0) {
        /* clear CCIFG interrupt status & disable CC interrupt */
        uint32_t temp = VC_PWM0->CCTL[0];
        temp &= ~VC_PWM_CCTL_CCIE_Msk;
        temp |= (1UL << VC_PWM_CCTL_CCIFG_Pos);
        VC_PWM0->CCTL[0] = temp;
        NVIC_DisableIRQ(PWM0_IRQn);
        xtimer_handler(XTIMER_USEC);
    }
}
