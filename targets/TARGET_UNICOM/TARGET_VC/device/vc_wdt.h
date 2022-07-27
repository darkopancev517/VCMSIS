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

#ifndef VC_WDT_H
#define VC_WDT_H

#include <stdint.h>
#include <stddef.h>
#include "device.h"
#include "pinmap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    VCWDT_PERIOD_2_SECS = 0,    /* 2 seconds period */
    VCWDT_PERIOD_1_SECS,        /* 1 seconds period */
    VCWDT_PERIOD_0_5_SECS,      /* 0.5 seconds period */
    VCWDT_PERIOD_0_25_SECS,     /* 0.25 seconds period */
} vcwdt_period_t;

void     vcwdt_clear(void);
void     vcwdt_enable(void);
void     vcwdt_disable(void);
void     vcwdt_set_period(vcwdt_period_t period);
uint16_t vcwdt_get_counter(void);
int      vcwdt_get_status(void);
void     vcwdt_clear_status(void);

#ifdef __cplusplus
}
#endif

#endif /* VC_WDT_H */
