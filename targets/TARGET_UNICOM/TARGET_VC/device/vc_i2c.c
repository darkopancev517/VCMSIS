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

#include "vc_i2c.h"

static uint8_t _i2c_get_clock_cr(uint32_t *hz);
static void _i2c_sfio_enable(int i2c_id);
static void _i2c_reset(int i2c_id);

void vci2c_init(int i2c_id, uint32_t *freq)
{
    if ((i2c_id == 0 || i2c_id > 2) || (freq == NULL))
        return;

    uint32_t temp = 0;

    vci2c_power_on(i2c_id);

    _i2c_reset(i2c_id);

    uint32_t corrected_freq = *freq;
    uint8_t cr = _i2c_get_clock_cr(&corrected_freq);
    *freq = corrected_freq;

    temp = VC_I2C(i2c_id)->CTRL;
    temp &= ~VC_I2C_CTRL_CR0_Msk;
    temp &= ~VC_I2C_CTRL_CR1_Msk;
    temp &= ~VC_I2C_CTRL_CR2_Msk;
    temp |= ((cr & 0x1UL) << VC_I2C_CTRL_CR0_Pos);
    temp |= (((cr >> 1) & 0x1UL) << VC_I2C_CTRL_CR1_Pos);
    temp |= (((cr >> 2) & 0x1UL) << VC_I2C_CTRL_CR2_Pos);
    VC_I2C(i2c_id)->CTRL = temp;

    _i2c_sfio_enable(i2c_id);
}

void vci2c_power_on(int i2c_id)
{
    uint32_t temp = VC_MISC2->PCLKEN;
    temp |= (1UL << VC_MISC2_PCLKEN_I2C_Pos);
    VC_MISC2->CLKEN_UNLOCK = (0x55AAAA55 << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos);
    VC_MISC2->PCLKEN = temp;
}

void vci2c_power_off(int i2c_id)
{
    uint32_t temp = VC_MISC2->PCLKEN;
    temp &= ~VC_MISC2_PCLKEN_I2C_Msk;
    VC_MISC2->CLKEN_UNLOCK = (0x55AAAA55 << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos);
    VC_MISC2->PCLKEN = temp;
}

void vci2c_enable(int i2c_id)
{
    uint32_t temp = VC_I2C(i2c_id)->CTRL;
    temp |= (1UL << VC_I2C_CTRL_EN_Pos);
    VC_I2C(i2c_id)->CTRL = temp;
}

void vci2c_disable(int i2c_id)
{
    uint32_t temp = VC_I2C(i2c_id)->CTRL;
    temp &= ~VC_I2C_CTRL_EN_Msk;
    VC_I2C(i2c_id)->CTRL = temp;
}

void vci2c_ack_enable(int i2c_id)
{
    uint32_t temp = VC_I2C(i2c_id)->CTRL;
    temp |= (1UL << VC_I2C_CTRL_AA_Pos);
    VC_I2C(i2c_id)->CTRL = temp;
}

void vci2c_ack_disable(int i2c_id)
{
    uint32_t temp = VC_I2C(i2c_id)->CTRL;
    temp &= ~VC_I2C_CTRL_AA_Msk;
    VC_I2C(i2c_id)->CTRL = temp;
}

int vci2c_send_start(int i2c_id)
{
    /* clear SI flag & enable start flag */
    uint32_t temp = VC_I2C(i2c_id)->CTRL;
    temp &= ~VC_I2C_CTRL_SI_Msk;
    temp |= (1UL << VC_I2C_CTRL_STA_Pos);
    VC_I2C(i2c_id)->CTRL = temp;

    /* TODO: do timeout mechansim */
    while ((VC_I2C(i2c_id)->CTRL & VC_I2C_CTRL_SI_Msk) == 0);

    /* disable start flag */
    temp = VC_I2C(i2c_id)->CTRL;
    temp &= ~VC_I2C_CTRL_STA_Msk;
    VC_I2C(i2c_id)->CTRL = temp;

    return 0;
}

int vci2c_send_stop(int i2c_id)
{
    /* clear SI flag & enable stop flag */
    uint32_t temp = VC_I2C(i2c_id)->CTRL;
    temp &= ~VC_I2C_CTRL_SI_Msk;
    temp |= (1UL << VC_I2C_CTRL_STO_Pos);
    VC_I2C(i2c_id)->CTRL = temp;

    /* TODO: do timeout mechansim */
    while ((VC_I2C(i2c_id)->CTRL & VC_I2C_CTRL_SI_Msk) == 0);

    /* disable stop flag */
    temp = VC_I2C(i2c_id)->CTRL;
    temp &= ~VC_I2C_CTRL_STO_Msk;
    VC_I2C(i2c_id)->CTRL = temp;

    return 0;
}

uint8_t vci2c_get_status(int i2c_id)
{
    return (VC_I2C(i2c_id)->STS & 0xff);
}

int vci2c_send_byte(int i2c_id, uint8_t data)
{
    /* clear SI flag */
    uint32_t temp = VC_I2C(i2c_id)->CTRL;
    temp &= ~VC_I2C_CTRL_SI_Msk;
    VC_I2C(i2c_id)->CTRL = temp;

    /* send data */
    VC_I2C(i2c_id)->DATA = data;

    /* TODO: do timeout mechansim */
    while ((VC_I2C(i2c_id)->CTRL & VC_I2C_CTRL_SI_Msk) == 0);

    return 0;
}

uint8_t vci2c_read_byte(int i2c_id)
{
    /* clear SI flag */
    uint32_t temp = VC_I2C(i2c_id)->CTRL;
    temp &= ~VC_I2C_CTRL_SI_Msk;
    VC_I2C(i2c_id)->CTRL = temp;

    /* TODO: do timeout mechansim */
    while ((VC_I2C(i2c_id)->CTRL & VC_I2C_CTRL_SI_Msk) == 0);

    return (VC_I2C(i2c_id)->DATA & 0xFF);
}

static uint8_t _i2c_get_clock_cr(uint32_t *hz)
{
    uint8_t cr = 0;
    uint32_t old_hz = *hz;
    uint32_t new_hz = 0;

    /* Supported Frequency:
     * Frequench  : CR2 CR1 CR0 : APBCLK divider (APBCLK: 60MHz)
     * - 1M       : 110         : 60
     * - 500K     : 101         : 120
     * - 375K     : 011         : 160
     * - 312.5K   : 010         : 192
     * - 267.8K   : 001         : 224
     * - 234.375K : 000         : 256
     * - 62.5K    : 100         : 960
     */

    if (old_hz < 100000) {
        new_hz = 62500;
        cr = 0x4; /* 100 */
    } else if (old_hz < 250000) {
        new_hz = 234375;
        cr = 0;   /* 000 */
    } else if (old_hz < 350000) {
        new_hz = 312500;
        cr = 0x2; /* 010 */
    } else if (old_hz < 500000) {
        new_hz = 375000;
        cr = 0x3; /* 011 */
    } else if (old_hz < 1000000) {
        new_hz = 500000;
        cr = 0x5; /* 101 */
    } else {
        new_hz = 1000000;
        cr = 0x6; /* 110 */
    }

    *hz = new_hz;

    return cr;
}

static void _i2c_sfio_enable(int i2c_id)
{
    uint32_t temp = 0;

    switch (i2c_id) {
    case 1:
        /* I2C1 SCL SDA - IOB13 IOB14 */
        temp = VC_GPIOB->SEL1;
        temp &= ~VC_GPIO_IOB_SEL1_IOBx_SEL_Msk(13);
        temp &= ~VC_GPIO_IOB_SEL1_IOBx_SEL_Msk(14);
        temp |= VC_GPIO_SEL1_IOB13_I2C1_SCL;
        temp |= VC_GPIO_SEL1_IOB14_I2C1_SDA;
        VC_GPIOB->SEL1 = temp;
        break;

    case 2:
        /* I2C2 SCL SDA - IOC4 IOC5 */
        temp = VC_GPIOC->SEL0;
        temp &= ~VC_GPIO_IOC_SEL0_IOCx_SEL_Msk(4);
        temp &= ~VC_GPIO_IOC_SEL0_IOCx_SEL_Msk(5);
        temp |= VC_GPIO_SEL0_IOC4_I2C2_SCL;
        temp |= VC_GPIO_SEL0_IOC5_I2C2_SDA;
        VC_GPIOC->SEL0 = temp;
        break;

    default:
        break;
    }
}

static void _i2c_reset(int i2c_id)
{
    VC_I2C(i2c_id)->DATA = 0;
    VC_I2C(i2c_id)->ADDR = 0;
    VC_I2C(i2c_id)->CTRL = 0;
    VC_I2C(i2c_id)->CTRL2 = 0;
}
