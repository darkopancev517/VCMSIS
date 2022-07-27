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

#include "vc_mbox.h"

void vcmbx_put_msg0(uint32_t mw)
{
    VC_MSG_BOX_M3->M3MSG_0 = 0;
    VC_MSG_BOX_M3->M3MSG_0 = mw;
}

void vcmbx_put_msg1(uint32_t mw)
{
    VC_MSG_BOX_M3->M3MSG_1 = 0;
    VC_MSG_BOX_M3->M3MSG_1 = mw;
}

uint32_t vcmbx_get_m0msg0()
{
    return (uint32_t)(VC_MSG_BOX_M3->M0M3MSG_INT0);
}

uint32_t vcmbx_get_m0msg1()
{
    return (uint32_t)(VC_MSG_BOX_M3->M0M3MSG_INT1.fields.M0_message);
}

static void _vcmbx_clear_m0msg0_int(uint32_t msg)
{
    VC_MSG_BOX_M3->M0M3MSG_INT0 = msg;
}

static void _vcmbx_clear_m0msg1_int(uint32_t msg)
{
    VC_MSG_BOX_M3->M0M3MSG_INT1.fields.M0_message = msg;
}

void vcmbx_clear_int(uint32_t msg0, uint32_t msg1)
{
    _vcmbx_clear_m0msg0_int(msg0);
    _vcmbx_clear_m0msg1_int(msg1);
}

void vcmbx_enable_int(bool ben)
{
    VC_MSG_BOX_M3->M3MSGIE_0 = ben ? 1 : 0;
    if (ben) {
        NVIC_EnableIRQ(MSGBOX_IRQn);
    } else {
        NVIC_DisableIRQ(MSGBOX_IRQn);
    }
}

static volatile unsigned int m_cntx = 0;
static volatile unsigned int m_chksum = 0;
static volatile unsigned int m_error = 0;

void MSGBOX_Handler(void)
{
    uint32_t msg0 = vcmbx_get_m0msg0();
    uint32_t msg1 = vcmbx_get_m0msg1();

    vcmbx_clear_int(msg0, msg1);
    m_chksum+=msg0;
    m_cntx++;
    if (msg1&0x80000000) {
        m_error++;
    }

    extern void vcradio_isr(void);
    vcradio_isr();
}
