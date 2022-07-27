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

#include "lp_ticker_api.h"
#include "vc_rtc.h"

#if DEVICE_LPTICKER

extern bool g_rtc_ticker_fire_interrupt;

/* LP ticker is driven by 32kHz clock and counter length is 24 bits. */
const ticker_info_t *lp_ticker_get_info()
{
    static const ticker_info_t info = {
        32768, /* RTC Frequency (Hz) */
        24
    };
    return &info;
}

void lp_ticker_init(void)
{
    vcrtc_init();
    vcrtc_ticker_enable();
}

void lp_ticker_free(void)
{
}

uint32_t lp_ticker_read()
{
    return vcrtc_get_us_ticker();
}

void lp_ticker_set_interrupt(timestamp_t timestamp)
{
    vcrtc_ticker_set_interrupt(timestamp);
}

void lp_ticker_fire_interrupt(void)
{
    g_rtc_ticker_fire_interrupt = true;
    NVIC_SetPendingIRQ(RTC_IRQn);
}

void lp_ticker_disable_interrupt(void)
{
    /* Note: RTC ticker always run */
}

void lp_ticker_clear_interrupt(void)
{
    /* Note: already handled in RTC driver */
}

void vcrtc_ticker_callback(void)
{
    lp_ticker_irq_handler();
}

#endif /* #if DEVICE_LPTICKER */
