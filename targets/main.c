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

#include "crypto_hal/pke.h"
#include "crypto_hal/pke.h"
#include "crypto_hal/trng.h"
#include "crypto_test/test.h"

extern int stdio_uart_inited;
extern serial_t stdio_uart;

static volatile uint32_t systick_milis = 0;

#if 0
void print_test(void)
{
	uint32_t *p;
	uint64_t a,b;

	p = (uint32_t *)&a;
	a=0x1122334455667788;
	b=0x1111111111111111;

	printf("\r\n %llx", a+b);   // 2233445566778899
	printf("\r\n %llx", a-b);   // 11223344556677
	printf("\r\n %08lx %08lx", *p, *(p+1));  // 55667788 11223344
	printf("\r\n %llx ", ((uint64_t)0x22334455)*0x11223344);  //249F93204851594
    printf("\r\n");
}
#endif

uint32_t crypto_test(void)
{
    printf("\r\n ------------ CRYPTO TEST ------------- \r\n");

	//printf("PKE Version: %08lx\n\r", PKE_VERSION);fflush(stdout);

#if 1
    extern uint32_t ske_lp_get_version(void);
    printf("SKE Version: %08lx\r\n", ske_lp_get_version());

    //-----------------------------------------------------------------
    //NOTE: NON-DMA - all test passed
    //      DMA     - TODO
    //      TRNG    - SOFTWARE OK
    //      TRNG    - HARDWARE TODO
    //-----------------------------------------------------------------
	if(SKE_all_test())
		return 1;
#endif

#if 0
    //-----------------------------------------------------------------
    //NOTE: NON-DMA - all test passed
    //      DMA     - TODO
    //      TRNG    - SOFTWARE OK
    //      TRNG    - HARDWARE TODO
    //-----------------------------------------------------------------
	if(HASH_all_test())
		return 1;
#endif

#if 0
    //-----------------------------------------------------------------
    //NOTE: NON-DMA - all test passed
    //      DMA     - TODO
    //      TRNG    - SOFTWARE OK
    //      TRNG    - HARDWARE TODO
    //-----------------------------------------------------------------
	if(HMAC_all_test())
		return 1;
#endif

#if 0
    //-----------------------------------------------------------------
    //NOTE: NON-DMA - all test passed
    //      DMA     - TODO
    //      TRNG    - SOFTWARE OK
    //      TRNG    - HARDWARE TODO
    //-----------------------------------------------------------------
	if(HASH_HMAC_sample_test())
		return 1;
#endif

#if 0
    //-----------------------------------------------------------------
    //NOTE: all test passed with ignored TRNG_HT_ERROR in FPGA,
    //      but sometimes lead to encyrpt operation to failed
    //-----------------------------------------------------------------
	if(SM2_all_test())
		return 1;
#endif

#if 0
    //-----------------------------------------------------------------
    //NOTE: all test passed
    //-----------------------------------------------------------------
	if(ECCp_get_curve_paras_test())
		return 1;
#endif

#if 0
    //-----------------------------------------------------------------
    //NOTE: all test passed
    //-----------------------------------------------------------------
	if(ECCp_get_key_all_test())
		return 1;
#endif

#if 0
    //-----------------------------------------------------------------
    //NOTE: all test passed
    //-----------------------------------------------------------------
	if(ECDH_all_test())
		return 1;
#endif

#if 0
    //-----------------------------------------------------------------
    //NOTE: all test passed with ignored TRNG_HT_ERROR in FPGA,
    //      but sometimes lead to encyrpt operation to failed
    //-----------------------------------------------------------------
	if(ECDSA_all_test())
		return 1;
#endif

    printf("\r\n TEST OVER \r\n");//fflush(stdout);
    return 0;
}

uint32_t get_systick_micros(void)
{
    return systick_milis*1000 +1000-SysTick->VAL/(SystemCoreClock/1000000UL);
}

static void trng_debug(void)
{
    //Enable FPGA debug probe
    *((uint32_t *)0x40000204) = 0x443298;

    printf("\r\n\r\n0x40000204: 0x%08lx\r\n", *((uint32_t *)0x40000204));

    printf("TRNG DEBUG ---------------------------\r\n");

    uint32_t rand_number = 0;

    for (int i = 0; i < 128; i++) {
        if (i != 0 && i % 4 == 0) {
            printf("\r\n");
        }

        uint32_t res = get_rand((uint8_t *)&rand_number, 4);

        if (res != TRNG_SUCCESS && res == TRNG_HT_ERROR) {
            while(1);
        }

        printf("%08lx ", rand_number);
    }
}

#if 0
static void HPLC_test(void)
{

}
#endif

int main(void)
{
    NVIC_SetPriority(SysTick_IRQn, 0);
    SysTick_Config(SystemCoreClock / 1000); /* 1ms systick interrupt */

    //us_ticker_init();

    if (!stdio_uart_inited) {
        serial_init(&stdio_uart, STDIO_UART_TX, STDIO_UART_RX);
    }

    //pke_enable_interrupt();
    //NVIC_EnableIRQ(PKE_IRQn);

    //NVIC_EnableIRQ(HASH_IRQn);
    //NVIC_EnableIRQ(SKE_IRQn);

    //print_test();
    //crypto_test();

    trng_debug();

    //HPLC_test();

    while (1);

    return 0;
}

void SysTick_Handler(void)
{
    systick_milis++;
}

void HardFault_Handler(void)
{
    printf("HARDFAULT!!!\r\n");
    while (1);
}

void PKE_Handler(void)
{
    return;
}

void HASH_Handler(void)
{
    return;
}

void SKE_Handler(void)
{
    return;
}

void TRNG_Handler(void)
{
    return;
}
