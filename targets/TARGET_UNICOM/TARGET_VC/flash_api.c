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

#if DEVICE_FLASH

#include "flash_api.h"

#include "vc_flash.h"

int32_t flash_init(flash_t *obj)
{
    (void) obj; // Note: flash already initialized in SystemInit
    return 0;
}

int32_t flash_free(flash_t *obj)
{
    (void)obj;
    return 0;
}

int32_t flash_erase_sector(flash_t *obj, uint32_t address)
{
    (void)obj;
    return vcflash_erase_sector(address);
}

int32_t flash_program_page(flash_t *obj, uint32_t address, const uint8_t *data, uint32_t size)
{
    (void)obj;
    return vcflash_program_page(address, data, size);
}

uint32_t flash_get_size(const flash_t *obj)
{
    (void)obj;
    return vcflash_get_size();
}

uint32_t flash_get_sector_size(const flash_t *obj, uint32_t address)
{
    (void)obj;
    return vcflash_get_sector_size(address);
}

uint32_t flash_get_page_size(const flash_t *obj)
{
    (void)obj;
    return vcflash_get_page_size();
}

uint32_t flash_get_start_address(const flash_t *obj)
{
    (void)obj;
    return 0;
}

uint8_t flash_get_erase_value(const flash_t *obj)
{
    (void)obj;
    return 0xFF;
}

#endif
