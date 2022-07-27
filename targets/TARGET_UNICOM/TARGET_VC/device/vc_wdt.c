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

#include "vc_wdt.h"

void vcwdt_clear(void)
{
    VC_PMU->WDTCLR = 0x55AAAA55;
}

void vcwdt_enable(void)
{
    VC_PMU->WDTPASS = 0xAA5555AA;
    VC_PMU->WDTEN |= (1UL << VC_PMU_WDTEN_WDTEN_Pos);
}

void vcwdt_disable(void)
{
    VC_PMU->WDTPASS = 0xAA5555AA;
    uint32_t temp = VC_PMU->WDTEN;
    temp &= ~(VC_PMU_WDTEN_WDTEN_Msk);
    VC_PMU->WDTEN = temp;
}

void vcwdt_set_period(vcwdt_period_t period)
{
    VC_PMU->WDTPASS = 0xAA5555AA;
    uint32_t temp = VC_PMU->WDTEN;
    temp &= ~(VC_PMU_WDTEN_WDTSEL_Msk);
    switch (period) {
    case VCWDT_PERIOD_2_SECS:
        temp |= (0UL << VC_PMU_WDTEN_WDTSEL_Pos);
        break;
    case VCWDT_PERIOD_1_SECS:
        temp |= (1UL << VC_PMU_WDTEN_WDTSEL_Pos);
        break;
    case VCWDT_PERIOD_0_5_SECS:
        temp |= (2UL << VC_PMU_WDTEN_WDTSEL_Pos);
        break;
    case VCWDT_PERIOD_0_25_SECS:
        temp |= (3UL << VC_PMU_WDTEN_WDTSEL_Pos);
        break;
    default:
        (void) temp;
        break;
    }
    VC_PMU->WDTEN = temp;
}

uint16_t vcwdt_get_counter(void)
{
    return (VC_PMU->WDTCLR & VC_PMU_WDTCLR_WDTCNT_Msk);
}

int vcwdt_get_status(void)
{
    return ((VC_PMU->WDTSTS & VC_PMU_WDTSTS_WDTSTS_Msk) != 0) ? 1 : 0;
}

void vcwdt_clear_status(void)
{
    VC_PMU->WDTSTS |= (1UL << VC_PMU_WDTSTS_WDTSTS_Pos);
}


