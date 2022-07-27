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

#include "rtc_api.h"

#if DEVICE_RTC

#include "vc_rtc.h"

static time_t m_time_base;
static int m_rtc_enabled = 0;

void rtc_init(void)
{
    vcrtc_init();
    m_rtc_enabled = 1;
}

void rtc_free(void)
{
}

int rtc_isenabled(void)
{
    return m_rtc_enabled;
}

static uint32_t rtc_seconds_get(void)
{
    return vcrtc_get_seconds();
}

time_t rtc_read(void)
{
    return m_time_base + rtc_seconds_get();
}

void rtc_write(time_t t)
{
    uint32_t seconds;
    do {
        seconds = rtc_seconds_get();
        m_time_base = t - seconds;
    } while (seconds != rtc_seconds_get());
}

#endif /* #if DEVICE_RTC */
