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

#include "vc_xtimer.h"

void vc_usticker_init(void)
{
    uint32_t temp = VC_MISC2->PCLKEN;
    temp |= (1UL << VC_MISC2_PCLKEN_TIMER_Pos);
    VC_MISC2->CLKEN_UNLOCK = (0x55AAAA55UL << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos);
    VC_MISC2->PCLKEN = temp;

    temp = VC_PWM0->CTL;
    temp &= ~VC_PWM_CTL_TSEL_Msk;
    temp &= ~VC_PWM_CTL_ID_Msk;
    temp |= (1UL << VC_PWM_CTL_TSEL_Pos);

#ifdef DEVICE_MCU_VC7351
    /* SystemCoreClock / APBDIV / 64 = 120MHz / 2 / 64 = ~1MHz (0.9375MHz) */
    temp |= (6UL << VC_PWM_CTL_ID_Pos);
#endif

#ifdef DEVICE_MCU_VC6330
    /* SystemCoreClock / APBDIV / 8 = 25MHz / 4 / 8 = ~0.7MHz (0.78125MHz) */
    temp |= (3UL << VC_PWM_CTL_ID_Pos);
#endif

    VC_PWM0->CTL = temp;

    vc_usticker_start();
}

void vc_usticker_start(void)
{
    uint32_t temp = VC_PWM0->CTL;
    temp &= ~VC_PWM_CTL_MC_Msk;
    temp |= (2UL << VC_PWM_CTL_MC_Pos); /* Continous Mode */
    VC_PWM0->CTL = temp;
}

void vc_usticker_stop(void)
{
    uint32_t temp = VC_PWM0->CTL;
    temp &= ~VC_PWM_CTL_MC_Msk;
    VC_PWM0->CTL = temp;
}

void __usticker_set(uint32_t value)
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

void vc_usticker_set(uint32_t value)
{
    uint16_t now = vc_usticker_read();
    uint32_t target = now + value;
    if (target > 0xffff) {
        target = target - 0xffff;
    }
    __usticker_set(target);
}

void vc_usticker_clear(void)
{
    /* clear capture/compare register period to it's default value */
    VC_PWM0->CCR[0] = VC_PWM_CCR_CCR_Msk;

    /* clear PWM counter */
    uint32_t temp = VC_PWM0->CTL;
    temp &= ~VC_PWM_CTL_CLR_Msk;
    temp |= (1UL << VC_PWM_CTL_CLR_Pos);
    VC_PWM0->CTL = temp;
}

uint32_t vc_usticker_read(void)
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
