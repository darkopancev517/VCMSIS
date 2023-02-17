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

#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  UART_0 = (int)VC_UART0_BASE,
  UART_1 = (int)VC_UART1_BASE,
  UART_2 = (int)VC_UART2_BASE,
  UART_3 = (int)VC_UART3_BASE,
  UART_4 = (int)VC_UART4_BASE,
  UART_5 = (int)VC_UART5_BASE,
  UART_6 = (int)VC_UART6_BASE
} UARTName;

#define DEVICE_SPI_COUNT 3
typedef enum {
  SPI_1 = (int)VC_SPI1_BASE,
  SPI_2 = (int)VC_SPI2_BASE,
  SPI_3 = (int)VC_SPI3_BASE
} SPIName;

#ifdef __cplusplus
}
#endif

#endif /* MBED_PERIPHERALNAMES_H */
