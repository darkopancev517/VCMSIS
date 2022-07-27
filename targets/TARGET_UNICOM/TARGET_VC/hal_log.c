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

#include "hal/log.h"
#include "hal/serial_api.h"

extern int stdio_uart_inited;
extern serial_t stdio_uart;

int hal_log(const char *_format, ...)
{
    if (!stdio_uart_inited) {
        serial_init(&stdio_uart, STDIO_UART_TX, STDIO_UART_RX);
    }

    char log_string[256];
    int chars_written;
    va_list args;

    va_start(args, _format);
    chars_written = vsnprintf(&log_string[0], sizeof(log_string), _format, args);
    va_end(args);

    if ((chars_written == 0) || (chars_written > sizeof(log_string)))
        return -1;

    for (int i = 0; i < chars_written; i++) {
        serial_putc(&stdio_uart, log_string[i]);
    }

    return chars_written;
}
