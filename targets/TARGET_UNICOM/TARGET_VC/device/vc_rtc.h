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

#ifndef VC_RTC_H
#define VC_RTC_H

#include <stdint.h>
#include <stddef.h>
#include "device.h"
#include "pinmap.h"

#ifdef __cplusplus
extern "C" {
#endif

void     vcrtc_init(void);
void     vcrtc_ticker_enable(void);
void     vcrtc_ticker_disable(void);
void     vcrtc_ticker_set_interrupt(uint32_t timestamp);
void     vcrtc_ticker_callback(void);
uint32_t vcrtc_get_seconds(void);
uint32_t vcrtc_get_us_ticker(void);

#ifdef __cplusplus
}
#endif

#endif /* VC_RTC_H */
