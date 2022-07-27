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

#ifndef VC_MBOX_H
#define VC_MBOX_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "device.h"
#include "pinmap.h"
#include "pinmap_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

void vcmbx_put_msg0(uint32_t mw);
void vcmbx_put_msg1(uint32_t mw);
uint32_t vcmbx_get_m0msg0();
uint32_t vcmbx_get_m0msg1();
void vcmbx_clear_int(uint32_t msg0, uint32_t msg1);
void vcmbx_enable_int(bool ben);


#ifdef __cplusplus
}
#endif

#endif /* VC7_MBOX_H */
