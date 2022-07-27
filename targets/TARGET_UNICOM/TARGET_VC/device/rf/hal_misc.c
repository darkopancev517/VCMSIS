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

#include "hal/misc.h"
#include "vc_misc.h"

bool hal_misc_assert_m0_addr_range(uint32_t addrm0)
{
    switch ( addrm0 )
    {
        case 0x00000000 ... 0x0000FFFF : //INST RAM
        case 0x20000000 ... 0x20003FFF : //DATA RAM
        case 0x20080000 ... 0x20100000 : //DSP RAM
        case 0x30000000 ... 0x31000000 : //AHB2AHB Bridge
        case 0x40000000 ... 0x40024000 : //AHB2AHB Slave
        case 0x4004F000 ... 0x40060000 : //APB Slave
        case 0x40047000 ... 0x40047058:  //M0 MISC2 Controller
        case 0x42000000 ... 0x42240000 : //AHB Slave BitBand
        case 0x42800000 ... 0x42C00000 : //APB Slave BitBand
            return 1;
            break;
        default : 
            return 0; //not in range return false
            break;
    } 
}

void _hal_misc_m0mem_read(const char *msg, uint32_t *dst, uint32_t srcm0, uint32_t len)
{
    volatile uint32_t *pm0=(volatile uint32_t *)((long)((srcm0&0x00ffffff)+0x30000000));
    vcmisc_ahb_async_bridge_unlock(); //TODO: note about re-entrant issue
    vcmisc_set_m0_addrh((uint8_t)(srcm0>>24));
    for (int i=0; i<len; i++){
        dst[i]=pm0[i];
    }
    vcmisc_ahb_async_bridge_lock();
}

void _hal_misc_m0mem_write(const char *msg, uint32_t dstm0, uint32_t *src, uint32_t len)
{
    volatile uint32_t *pm0=(volatile uint32_t *)((long)((dstm0&0x00ffffff)+0x30000000));
    vcmisc_ahb_async_bridge_unlock(); //TODO: note about re-entrant issue
    vcmisc_set_m0_addrh((uint8_t)(dstm0>>24));
    for (int i=0; i<len; i++){
        pm0[i]=src[i];
    }
    vcmisc_ahb_async_bridge_lock();
}

uint32_t _hal_misc_m0mem_get(const char *msg, uint32_t srcm0)
{
    uint32_t xw;
    hal_misc_m0mem_read(&xw, srcm0, 1);
    return xw;
}

void _hal_misc_m0mem_put(const char *msg, uint32_t dstm0, uint32_t xw)
{
    hal_misc_m0mem_write(dstm0, &xw, 1);
}

void hal_misc_m0_start(bool bEn)
{
    vcmisc_m0_clksel(2);
    vcmisc_m0_start(bEn);
}
