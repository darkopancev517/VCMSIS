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

#ifndef VC_USTICKER_H
#define VC_USTICKER_H

#include <stdint.h>
#include <stddef.h>
#include "device.h"
#include "pinmap.h"
#include "pinmap_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEVICE_MCU_VC7351
#define VC_USTICKER_SECOND (937500UL) /* 120MHz SystemCoreClock */
#endif

#ifdef DEVICE_MCU_VC6330
#define VC_USTICKER_SECOND (781250UL) /* 25MHz SystemCoreClock */
#endif

#define VC_USTICKER_WIDTH  (16UL)

void vc_usticker_init(void);
void vc_usticker_start(void);
void vc_usticker_stop(void);
void vc_usticker_set(uint32_t value);
void vc_usticker_clear(void);
uint32_t vc_usticker_read(void);

#ifdef __cplusplus
}
#endif

#endif /* VC_USTICKER_H */
