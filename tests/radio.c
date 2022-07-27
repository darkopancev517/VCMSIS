/*
 * Copyright (c) 2022, Hangzhou Lianxintong Semiconductor Co.,Ltd.
 * All rights reserved.
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

#include "hal/gpio_api.h"
#include "hal/us_ticker_api.h"
#include "hal/serial_api.h"
#include "hal/log.h"
#include "hal/rtc_api.h"
#include "hal/lp_ticker_api.h"

#include "vc73xx_xtimer.h"
#include "vc73xx_radio.h"
#include "vc73xx_rtc.h"

uint8_t rf_buf[256];
uint8_t tx_dummy[16] = { 0 };

void radio_receive_handler(int rx_length)
{
    hal_log("RECEIVE length: %d\r\n", rx_length);
    hal_log("[");
    for (int i = 0; i < rx_length; i++) {
        hal_log("%d ", rf_buf[i]);
    }
    hal_log("]\r\n");
}

int main(void)
{
    SysTick_Config(SystemCoreClock / 1000); /* 1ms systick interrupt */
    us_ticker_init();

    vcradio_init(rf_buf, sizeof(rf_buf), radio_receive_handler);
    hal_log("\r\nradio: vcradio_init done\r\n");

    if (!stdio_uart_inited) {
        serial_init(&stdio_uart, STDIO_UART_TX, STDIO_UART_RX);
    }
    serial_irq_set(&stdio_uart, RxIrq, 1);

    for (int i = 0; i < sizeof(tx_dummy); i++) {
        tx_dummy[i] = i;
    }

    rtc_init();
    lp_ticker_init();

    while(1) {
        hal_log("press any key to start rf transmit\r\n");
        serial_getc(&stdio_uart);
        vcradio_transmit(tx_dummy, sizeof(tx_dummy));
        hal_log("TRANSMIT length: %d done\r\n", sizeof(tx_dummy));
        hal_log("RTC SECONDS: %lu\r\n", rtc_read());
        hal_log("LP TICKER: %lu\r\n", lp_ticker_read());
    }

    return 0;
}

void SysTick_Handler(void)
{
    systick_counter++;
}
