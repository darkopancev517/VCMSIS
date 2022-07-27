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

#include "pinmap_ex.h"

const PinMapUART PinMap_UART[] = {
    {PB_2, PA_12, 0, (int)UART0_IRQn},
    {PB_3, PA_13, 1, (int)UART1_IRQn},
    {PB_4, PA_14, 2, (int)UART2_IRQn},
    {PB_5, PA_15, 3, (int)UART3_IRQn},
    {PB_6, PB_0,  4, (int)UART4_IRQn},
    {PB_7, PB_1,  5, (int)UART5_IRQn},
    {PB_8, PB_15, 6, (int)UART6_IRQn},
    {NC, NC, 0, 0}
};

const PinMapSPI PinMap_SPI[] = {
    {DUMMY, DUMMY, DUMMY, 0, 0}, /* SPI_0 not supported */
    {PB_10, PB_11, PB_12, 1, (int)SPI1_IRQn},
    {PC_1,  PC_2,  PC_3,  2, (int)SPI2_IRQn},
    {PC_9,  PC_10, PC_11, 3, (int)SPI3_IRQn},
    {NC, NC, NC, 0, 0}
};

const PinMapI2C PinMap_I2C[] = {
    {DUMMY, DUMMY, 0, 0}, /* I2C_0 not supported */
    {PB_13, PB_14, 1, (int)I2C1_IRQn},
    {PC_4,  PC_5,  2, (int)I2C2_IRQn},
    {NC, NC, 0, 0}
};

const PinMapADC PinMap_ADC[] = {
    {PA_0,  0},
    {PA_1,  1},
    {PA_2,  2},
    {PA_3,  3},
    {PA_4,  4},
    {PA_8,  5},
    {PC_6,  6},
    {PC_12, 7},
    {NC, 0}
};

int pin_instance_uart(PinName tx, PinName rx)
{
    int instance = NC;
    for (int i = 0; ((PinMap_UART[i].tx != NC) && (PinMap_UART[i].rx != NC)); i++) {
        if ((PinMap_UART[i].tx == tx) && (PinMap_UART[i].rx == rx)) {
            instance = PinMap_UART[i].instance;
            break;
        }
    }
    return instance;
}

int pin_instance_spi(PinName sck, PinName miso, PinName mosi)
{
    int instance = NC;
    for (int i = 0;
         ((PinMap_SPI[i].sck != NC) &&
         (PinMap_SPI[i].miso != NC) &&
         (PinMap_SPI[i].mosi != NC));
         i++)
    {
        if ((PinMap_SPI[i].sck == sck) &&
            (PinMap_SPI[i].miso == miso) &&
            (PinMap_SPI[i].mosi == mosi)) {
            instance = PinMap_SPI[i].instance;
            break;
        }
    }
    return instance;
}

int pin_instance_i2c(PinName scl, PinName sda)
{
    int instance = NC;
    for (int i = 0; ((PinMap_I2C[i].scl != NC) && (PinMap_I2C[i].sda != NC)); i++) {
        if ((PinMap_I2C[i].scl == scl) && (PinMap_I2C[i].sda == sda)) {
            instance = PinMap_I2C[i].instance;
            break;
        }
    }
    return instance;
}

int pin_instance_adc(PinName pin)
{
    int instance = NC;
    for (int i = 0; (PinMap_ADC[i].adc_pin != NC); i++) {
        if (PinMap_ADC[i].adc_pin == pin) {
            instance = PinMap_ADC[i].instance;
            break;
        }
    }
    return instance;
}
