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

#include "hal/rf.h"
#include "hal/misc.h"

void hal_rf_init(void)
{
    extern void cent_init_pre_powerup();
    cent_init_pre_powerup();
}

uint64_t hal_rf_int_get_sts()
{
    return ((uint64_t)vcmbx_get_m0msg1()) << 32 | (uint64_t)vcmbx_get_m0msg0();
}

void hal_rf_int_clear_sts(uint64_t sts)
{
    vcmbx_clear_int((uint32_t)(sts>>32), (uint32_t)(sts&0xffffffffL));
}

void hal_rf_reset_assert(void)
{
    uint32_t value = 0;
    hal_misc_m0mem_write(0x400110c0, &value, 1);
    hal_misc_m0_start(0);
}

void hal_rf_load_code(void)
{
    //m0 code/data
    hal_misc_m0mem_write(0x00000000, (uint32_t *)0x84000, 0x00018000/4);//96KB
    //dsp iram
    hal_misc_m0mem_write(0x20090000, (uint32_t *)0x9C000, 0x00020000/4);//128KB
    //dsp data0
    hal_misc_m0mem_write(0x200c0000, (uint32_t *)0xBC000, 0x00028000/4);//160KB
}

int _hal_rf_read(const char *msg, uint8_t *dst, uint32_t srcm0, uint32_t blen)
{
    uint32_t rem = blen%4;
    uint32_t xw = 0;
    
    /* if received byte less than 4 bytes */
    if (blen < 4) 
    {
        if (rem>0){

            _hal_misc_m0mem_read(msg, &xw, srcm0, 1);
            
            ((uint8_t *)(dst))[0]=((uint8_t *)&xw)[0]; // mod 1
            
            if (rem>1){
                ((uint8_t *)(dst))[1]=((uint8_t *)&xw)[1]; // mod 2
            }
            if (rem>2){
                ((uint8_t *)(dst))[2]=((uint8_t *)&xw)[2]; // mod 3
            }
        }   
    }
    /* if received byte more than 4 bytes */
    else{

        //get byte to align 4 byte
        _hal_misc_m0mem_read(msg, (uint32_t *)dst, srcm0, blen/4);

        //Handle the rest byte
        if (rem>0){

            _hal_misc_m0mem_read(msg, &xw, srcm0+(blen/4)*4, 1);

            ((uint8_t *)(dst+(blen/4)*4))[0]=((uint8_t *)&xw)[0]; // mod 1

            if (rem>1){
                ((uint8_t *)(dst+(blen/4)*4))[1]=((uint8_t *)&xw)[1]; // mod 2
            }
            if (rem>2){
                ((uint8_t *)(dst+(blen/4)*4))[2]=((uint8_t *)&xw)[2]; // mod 3
            }
        }
    }
    return 0;
}

int _hal_rf_write(const char *msg, uint32_t dstm0, uint8_t *src, uint32_t blen)
{
    uint32_t rem = blen%4;
    uint32_t xw = 0;

    /* if transfer byte less than 4 bytes */
    if (blen < 4) 
    {
        _hal_misc_m0mem_read(msg, &xw, dstm0, 1);

        for (int b=0; b<rem; b++){
            int msk=0xff<<(b*8);
            xw = ((xw&~msk) | (((uint32_t)((uint8_t *)(src))[b])<<(b*8)));
        }
            
        _hal_misc_m0mem_write(msg, dstm0, &xw, 1);        
    }
    /* if transfer byte more than 4 bytes */
    else
    {
        //get byte to align 4 byte
        _hal_misc_m0mem_write(msg, dstm0, (uint32_t *)src, blen/4);

        //Handle the rest byte
        if (rem>0){

            _hal_misc_m0mem_read(msg, &xw, dstm0+(blen/4)*4, 1);

            for (int b=0; b<rem; b++){
                int msk=0xff<<(b*8);
                xw = (xw&~msk) | ((uint32_t)((uint8_t *)(src+(blen/4)*4))[b])<<(b*8);
            }

            _hal_misc_m0mem_write(msg, dstm0+(blen/4)*4, &xw, 1);
        }        
    }
    return 0;
}

int _hal_rf_get(const char *msg, uint32_t srcm0, uint32_t *pxw)
{
    return _hal_rf_read(msg, (uint8_t *)pxw, srcm0, 4);
}

int _hal_rf_put(const char *msg, uint32_t dstm0, uint32_t xw)
{
    return _hal_rf_write(msg, dstm0, (uint8_t *)&xw, 4);
}
