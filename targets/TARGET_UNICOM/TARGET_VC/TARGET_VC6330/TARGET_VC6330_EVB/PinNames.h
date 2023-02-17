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

#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#ifndef DEVICE_BOARD_VC6330_EVB
#define DEVICE_BOARD_VC6330_EVB 1
#endif

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  PA_0  = 0x00,
  PA_1  = 0x01,
  PA_2  = 0x02,
  PA_3  = 0x03,
  PA_4  = 0x04,
  PA_5  = 0x05,
  PA_6  = 0x06,
  PA_7  = 0x07,
  PA_8  = 0x08,
  PA_9  = 0x09,
  PA_10 = 0x0A,
  PA_11 = 0x0B,
  PA_12 = 0x0C,
  PA_13 = 0x0D,
  PA_14 = 0x0E,
  PA_15 = 0x0F,

  PB_0  = 0x10,
  PB_1  = 0x11,
  PB_2  = 0x12,
  PB_3  = 0x13,
  PB_4  = 0x14,
  PB_5  = 0x15,
  PB_6  = 0x16,
  PB_7  = 0x17,
  PB_8  = 0x18,
  PB_9  = 0x19,
  PB_10 = 0x1A,
  PB_11 = 0x1B,
  PB_12 = 0x1C,
  PB_13 = 0x1D,
  PB_14 = 0x1E,
  PB_15 = 0x1F,

  PC_0  = 0x20,
  PC_1  = 0x21,
  PC_2  = 0x22,
  PC_3  = 0x23,
  PC_4  = 0x24,
  PC_5  = 0x25,
  PC_6  = 0x26,
  PC_7  = 0x27,
  PC_8  = 0x28,
  PC_9  = 0x29,
  PC_10 = 0x2A,
  PC_11 = 0x2B,
  PC_12 = 0x2C,
  PC_13 = 0x2D,
  PC_14 = 0x2E,
  PC_15 = 0x2F,

  PD_0  = 0x30,
  PD_1  = 0x31,
  PD_2  = 0x32,
  PD_3  = 0x33,
  PD_4  = 0x34,
  PD_5  = 0x35,
  PD_6  = 0x36,
  PD_7  = 0x37,
  PD_8  = 0x38,
  PD_9  = 0x39,
  PD_10 = 0x3A,
  PD_11 = 0x3B,
  PD_12 = 0x3C,
  PD_13 = 0x3D,
  PD_14 = 0x3E,
  PD_15 = 0x3F,

  STDIO_UART_TX = PB_2,
  STDIO_UART_RX = PA_12,

  // Generic signals namings
  SERIAL_TX = STDIO_UART_TX,
  SERIAL_RX = STDIO_UART_RX,

  // Dummy Pin definition
  DUMMY = 0xdeadbeef,

  // Not connected
  NC = (int)0xFFFFFFFF
} PinName;

typedef enum {
  PIN_INPUT,
  PIN_OUTPUT
} PinDirection;

typedef enum {
  PullNone    = 0,
  PullUp      = 1,
  PullDown    = 2,
  PullDefault = PullNone
} PinMode;

#ifdef __cplusplus
}
#endif

#endif /* MBED_PINNAMES_H */
