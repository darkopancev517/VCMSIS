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
#include <stddef.h>
#include <stdbool.h>
#include "us_ticker_api.h"
#include "pinmap.h"

#include "vc_usticker.h"
#include "vc_xtimer.h"

static unsigned int us_ticker_irqmask;
static bool us_ticker_inited = false;

static void _us_ticker_timer_callback(void *arg);
static xtimer_t _us_ticker_timer;

void us_ticker_init(void)
{
    if (us_ticker_inited) {
        return;
    }
    _us_ticker_timer.callback = _us_ticker_timer_callback;
    _us_ticker_timer.arg = NULL;
    xtimer_init(XTIMER_USEC);
    us_ticker_inited = true;
}

uint32_t us_ticker_read(void)
{
    if (!us_ticker_inited) {
        us_ticker_init();
    }
    return xtimer_now(XTIMER_USEC);
}

void us_ticker_set_interrupt(timestamp_t timestamp)
{
    if (!us_ticker_inited) {
        us_ticker_init();
    }
    xtimer_set(XTIMER_USEC, &_us_ticker_timer, timestamp);
}

void us_ticker_disable_interrupt(void)
{
    us_ticker_irqmask = __get_PRIMASK();
    __disable_irq();
}

void us_ticker_clear_interrupt(void)
{
    __set_PRIMASK(us_ticker_irqmask);
}

static void _us_ticker_timer_callback(void *arg)
{
    (void)arg;
    us_ticker_irq_handler();
}
