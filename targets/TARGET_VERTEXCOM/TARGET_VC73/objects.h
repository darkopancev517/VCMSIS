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

#ifndef MBED_OBJECTS_H
#define MBED_OBJECTS_H

#include <stdbool.h>

#include "cmsis.h"
#include "PortNames.h"
#include "PeripheralNames.h"
#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    PinName pin;
} gpio_t;

struct gpio_irq_s {
    uint32_t ch;
};

struct port_s {
    PortName port;
    uint32_t mask;
    PinDirection direction;
};

struct serial_s {
    int instance;
    uint32_t baudrate;
    uint32_t databits;
    uint32_t stopbits;
    uint32_t parity;
    uint32_t handler;
    uint32_t context;
    uint32_t irq_mask;
    bool update;
    PinName pin_tx;
    PinName pin_rx;
};

#ifdef __cplusplus
}
#endif

#endif /* MBED_OBJECTS_H */
