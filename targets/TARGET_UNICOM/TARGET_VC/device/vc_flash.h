/*
 * Copyright (c) 2022 Vertexcom Technologies, Inc. All rights reserved.
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

#ifndef VC_FLASH_H
#define VC_FLASH_H

#include <stdint.h>
#include <stddef.h>
#include "device.h"
#include "pinmap.h"

#ifdef __cplusplus
extern "C" {
#endif

void     vcflash_disable_cache(void);
void     vcflash_enable_cache(void);
void     vcflash_write_enable(void);
uint32_t vcflash_get_manuid(void);
void     vcflash_quad_enable(void);
int32_t  vcflash_erase_sector(uint32_t address);
int32_t  vcflash_program_page(uint32_t address, const uint8_t *data, uint32_t size);
uint32_t vcflash_get_size(void);
uint32_t vcflash_get_sector_size(uint32_t address);
uint32_t vcflash_get_page_size(void);

#ifdef __cplusplus
}
#endif

#endif /* VC_FLASH_H */
