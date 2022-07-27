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

#ifndef VC_XTIMER_H
#define VC_XTIMER_H

#include "vc_usticker.h"

#ifdef __cplusplus
extern "C" {
#endif

#define XTIMER_CONFIG_CLOCK_SECOND    VC_USTICKER_SECOND
#define XTIMER_CONFIG_NOW64           0
#define XTIMER_CONFIG_USEC_BASE_FREQ  (1000000UL)
#define XTIMER_CONFIG_USEC_MIN        (10UL)
#define XTIMER_CONFIG_USEC_WIDTH      VC_USTICKER_WIDTH
#define XTIMER_CONFIG_EXTEND          1

#define XTIMER_CLOCK_SECOND XTIMER_CONFIG_CLOCK_SECOND

typedef struct xtimer_base xtimer_base_t;
typedef struct xtimer_clock xtimer_clock_t;

struct xtimer_base {
    xtimer_base_t *next;
    uint32_t offset;
};

#if XTIMER_CONFIG_NOW64
typedef uint64_t xtimer_now_t;
#else
typedef uint32_t xtimer_now_t;
#endif

typedef struct {
    xtimer_base_t base;
    void (*callback)(void *arg);
    void *arg;
} xtimer_t;

typedef struct {
    void (*set)(xtimer_clock_t *clock, uint32_t value);
    uint32_t (*now)(xtimer_clock_t *clock);
    void (*cancel)(xtimer_clock_t *clock);
} xtimer_ops_t;

struct xtimer_clock {
    xtimer_base_t list;
    const xtimer_ops_t *ops;
    xtimer_base_t *last;
    uint32_t adjust;
#if XTIMER_CONFIG_EXTEND || XTIMER_CONFIG_NOW64
    uint32_t max_value;
    uint32_t lower_last;
    xtimer_now_t checkpoint;
#endif
};

void xtimer_handler(xtimer_clock_t *clock);
void xtimer_set(xtimer_clock_t *clock, xtimer_t *timer, uint32_t value);
void xtimer_remove(xtimer_clock_t *clock, xtimer_t *timer);
xtimer_now_t _xtimer_now_extend(xtimer_clock_t *clock);

static inline xtimer_now_t xtimer_now(xtimer_clock_t *clock)
{
#if XTIMER_CONFIG_NOW64
    if (1) {
#elif XTIMER_CONFIG_EXTEND
    if (clock->max_value < UINT32_MAX) {
#else
    if (0) {
#endif
        return _xtimer_now_extend(clock);
    } else {
        return clock->ops->now(clock);
    }
}

void xtimer_update_head_offset(xtimer_clock_t *clock);
void xtimer_init(xtimer_clock_t *clock);

#if XTIMER_CONFIG_EXTEND
static inline void xtimer_init_extend(xtimer_clock_t *clock)
{
    if (clock->max_value < UINT32_MAX) {
        clock->ops->set(clock, clock->max_value >> 1);
    }
}
#endif

extern xtimer_clock_t *const XTIMER_USEC;

#ifdef __cplusplus
}
#endif

#endif /* VC_XTIMER_H */
