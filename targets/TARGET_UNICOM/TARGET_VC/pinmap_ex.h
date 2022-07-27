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

#ifndef PINMAP_EX_H
#define PINMAP_EX_H

#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    PinName tx;
    PinName rx;
    int instance;
    int irqn;
} PinMapUART;

typedef struct {
    PinName sck;
    PinName miso;
    PinName mosi;
    int instance;
    int irqn;
} PinMapSPI;

typedef struct {
    PinName scl;
    PinName sda;
    int instance;
    int irqn;
} PinMapI2C;

typedef struct {
    PinName adc_pin;
    int instance;
} PinMapADC;

extern const PinMapUART PinMap_UART[];
extern const PinMapSPI PinMap_SPI[];
extern const PinMapI2C PinMap_I2C[];
extern const PinMapADC PinMap_ADC[];

int pin_instance_uart(PinName tx, PinName rx);
int pin_instance_spi(PinName sck, PinName miso, PinName mosi);
int pin_instance_i2c(PinName scl, PinName sda);
int pin_instance_adc(PinName pin);

#ifdef __cplusplus
}
#endif

#endif /* PINMAP_EX_H */
