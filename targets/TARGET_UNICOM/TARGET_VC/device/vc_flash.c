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

#include "vc_flash.h"

void vcflash_disable_cache(void)
{
    uint32_t temp = VC_MEM->FLASH_CACHE;
    temp &= ~VC_MEM_FLASH_CACHE_EN_Msk;
    temp |= (0UL << VC_MEM_FLASH_CACHE_EN_Pos);
    VC_MEM->FLASH_CACHE = temp;
}

void vcflash_enable_cache(void)
{
    uint32_t temp = VC_MEM->FLASH_CACHE;
    temp &= ~VC_MEM_FLASH_CACHE_EN_Msk;
    temp |= (1UL << VC_MEM_FLASH_CACHE_EN_Pos);
    VC_MEM->FLASH_CACHE = temp;
}

void vcflash_write_enable(void)
{
    uint32_t temp = 0;
    temp |= (1UL << VC_MEM_FLASH_CMD_ACT_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_POLL_Pos);
    temp |= (0x6UL << VC_MEM_FLASH_CMD_CMDID_Pos); /* WINBOND_CMDID_WRITE_ENABLE: 0x6 */
    VC_MEM->FLASH_CMD = temp;

    while ((VC_MEM->FLASH_CMD & VC_MEM_FLASH_CMD_ACT_Msk) != 0);
}

uint32_t vcflash_get_manuid(void)
{
    uint32_t temp = VC_MEM->FLASH_ID;
    return (temp >> VC_MEM_FLASH_ID_MANU_ID_Pos);
}

void vcflash_quad_enable(void)
{
    /* SPIFLASH QUAD ENABLE */

    vcflash_write_enable();

    uint32_t temp = 0;

    temp |= (1UL << VC_MEM_FLASH_CMD_ACT_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_CMDWR_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_CMDDATA_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_POLL_Pos);

    if (vcflash_get_manuid() == 0xEFUL) {
        /* WINBOND_CMDID_WSR2: 0x31 */
        temp |= (0x31UL << VC_MEM_FLASH_CMD_CMDID_Pos);
        temp |= (0UL << VC_MEM_FLASH_CMD_LENGTH_Pos);
        ((uint8_t *)(VC_MEM->FLASH_BUFx))[0] = 0x2U; /* Set QE: 1 */
    } else {
        /* GigaDevice GD_CMDID_WRSR: 0x1 */
        temp |= (0x1UL << VC_MEM_FLASH_CMD_CMDID_Pos);
        temp |= (1UL << VC_MEM_FLASH_CMD_LENGTH_Pos);
        ((uint8_t *)(VC_MEM->FLASH_BUFx))[0] = 0x0U;
        ((uint8_t *)(VC_MEM->FLASH_BUFx))[1] = 0x2U; /* Set QE: 1 */
    }

    VC_MEM->FLASH_CMD = temp;

    while ((VC_MEM->FLASH_CMD & VC_MEM_FLASH_CMD_ACT_Msk) != 0);
}

int32_t vcflash_erase_sector(uint32_t address)
{
    uint32_t temp = 0;

    vcflash_write_enable();

    temp |= (1UL << VC_MEM_FLASH_CMD_ACT_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_CMDWR_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_POLL_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_CMDADDR_Pos);
    temp |= (0x20UL << VC_MEM_FLASH_CMD_CMDID_Pos); /* WINBOND_CMDID_SECTOR_ERASE: 0x20 */

    VC_MEM->FLASH_ADDR = address;
    VC_MEM->FLASH_CMD = temp;

    while ((VC_MEM->FLASH_CMD & VC_MEM_FLASH_CMD_ACT_Msk) != 0);

    return 0;
}

int32_t vcflash_program_page(uint32_t address, const uint8_t *data, uint32_t size)
{
    if (size == 0) {
        return -1;
    }

    uint32_t temp = 0;

    for (uint32_t i = 0; i < size; i++) {
        ((uint8_t *)(VC_MEM->FLASH_BUFx))[i] = data[i];
    }

    vcflash_write_enable();

    temp |= (1UL << VC_MEM_FLASH_CMD_ACT_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_CMDWR_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_POLL_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_CMDADDR_Pos);
    temp |= (1UL << VC_MEM_FLASH_CMD_CMDDATA_Pos);
    temp |= ((size - 1) << VC_MEM_FLASH_CMD_LENGTH_Pos);
    temp |= (0x2UL << VC_MEM_FLASH_CMD_CMDID_Pos); /* WINBOND_CMDID_PAGE_PROG: 0x2 */

    VC_MEM->FLASH_ADDR = address;
    VC_MEM->FLASH_CMD = temp;

    while ((VC_MEM->FLASH_CMD & VC_MEM_FLASH_CMD_ACT_Msk) != 0);

    return 0;
}

uint32_t vcflash_get_size(void)
{
    return 0x200000; // 2MB
}

uint32_t vcflash_get_sector_size(uint32_t address)
{
    (void)address;
    return 0x1000; // 4KB
}

uint32_t vcflash_get_page_size(void)
{
    return 0x10000; // 64KB
}
