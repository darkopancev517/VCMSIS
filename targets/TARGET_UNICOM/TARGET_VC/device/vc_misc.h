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

#ifndef VC_MISC_H
#define VC_MISC_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "device.h"
#include "pinmap.h"
#include "pinmap_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEVICE_MCU_VC7351
void vcmisc_set_m0_addrh(uint8_t base);
void vcmisc_ahb_async_bridge_unlock();
void vcmisc_ahb_async_bridge_lock();
void vcmisc_m0_start(bool ben);
void vcmisc_m0_clksel(uint8_t sel);
#endif

#ifdef __cplusplus
}
#endif

#endif /* VC_MISC_H */
