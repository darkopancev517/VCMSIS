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

#ifndef VC73XX_GPIO_H
#define VC73XX_GPIO_H

#include <stdint.h>
#include <stddef.h>
#include "device.h"
#include "pinmap.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VC_PORT(x) (((uint8_t)(x) >> 4) & 0xF)
#define VC_PIN(x)  (((uint8_t)(x) & 0xF))

#ifndef GPIO_PIN_COUNT
#define GPIO_PIN_COUNT 64
#endif

typedef struct {
    bool         used_as_gpio : 1;
    PinDirection direction    : 1;
    PinMode      pull         : 2;
    bool         used_as_irq  : 1;
    bool         irq_fall     : 1;
    bool         irq_rise     : 1;
    bool         irq_both     : 1;
} vcgpio_cfg_t;

typedef uint64_t vcgpio_mask_t;

void vcgpio_init(PinName pin, vcgpio_cfg_t *cfg);
void vcgpio_free(PinName pin);
int  vcgpio_pin_out_read(PinName pin);
int  vcgpio_pin_read(PinName pin);
void vcgpio_pin_set(PinName pin);
void vcgpio_pin_clear(PinName pin);
void vcgpio_out_uninit(PinName pin);
void vcgpio_in_uninit(PinName pin);
void vcgpio_irq_enable(PinName port);
void vcgpio_irq_disable(PinName port);

#ifdef __cplusplus
}
#endif

#endif /* VC73XX_GPIO_H */
