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

#ifndef VC73XX_UART_H
#define VC73XX_UART_H

#include <stdint.h>
#include <stddef.h>
#include "device.h"
#include "pinmap.h"
#include "pinmap_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VCUART_PARITY_NONE    0
#define VCUART_PARITY_ODD     1
#define VCUART_PARITY_EVEN    2
#define VCUART_PARITY_FORCED1 3
#define VCUART_PARITY_FORCED0 4

enum {
    VCUART_TX_IRQ = (1 << 0),
    VCUART_RX_IRQ = (1 << 1)
};

int  vcuart_init(int uart_id, uint32_t baudrate, uint8_t parity, uint8_t databits, uint8_t stopbits);
void vcuart_power_on(int uart_id);
void vcuart_power_off(int uart_id);
void vcuart_set_mode(int uart_id, uint8_t parity, uint8_t databits, uint8_t stopbits);
void vcuart_set_baudrate(int uart_id, int baudrate);
void vcuart_set_irq(int uart_id, uint32_t irq_mask);
void vcuart_putchar(int uart_id, char c);

#ifdef __cplusplus
}
#endif

#endif /* VC73XX_UART_H */
