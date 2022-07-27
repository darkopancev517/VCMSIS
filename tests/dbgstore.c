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

#include "dbgstore.h"
#include "dbgstore_util.h"

#include "heap.h"

extern int stdio_uart_inited;
extern serial_t stdio_uart;

static volatile uint32_t systick_counter = 0;

int main(void)
{
    SysTick_Config(SystemCoreClock / 1000); /* 1ms systick interrupt */
    us_ticker_init();

    if (!stdio_uart_inited) {
        serial_init(&stdio_uart, STDIO_UART_TX, STDIO_UART_RX);
    }

    dbg_store_init();

    hal_log("\r\n");
    hal_log("---------------------------------------------\r\n");
    hal_log("============ DBGSTORE TOOLS TEST ============\r\n");
    hal_log("---------------------------------------------\r\n");

    dbg_store_dump_previous();

#if 0
    int i = 0;

    for (i = 0; i < 10; i++) {
        dbg_store_add(__LINE__ + i, "%s: this is debug message test for DBGSTORE", __func__);
    }

    for (i = 0; i < 13; i++) {
        dbg_store_add(__LINE__ + i, "%s: DBGSTORE version 0.2", __func__);
    }

    for (i = 0; i < 18; i++) {
        dbg_store_add(__LINE__ + i, "%s: maybe it's the last version", __func__);
    }

    for (i = 0; i < 8; i++) {
        dbg_store_add(__LINE__ + i, "%s: done", __func__);
    }

    for (i = 0; i < 4; i++) {
        dbg_store_add(__LINE__ + i, "%s: something failed?", __func__);
    }

    for (i = 0; i < 2; i++) {
        dbg_store_add(__LINE__ + i, "%s: don't think so dude!!!", __func__);
    }

    for (i = 0; i < 20; i++) {
        dbg_store_add(__LINE__ + i, "%s: hope this would be last release!", __func__);
    }
#endif











    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "============= DBGSTORE TOOLS TEST =============");
    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "%s: DBGSTORE version 0.2 - 9/29/2021", __func__);
    dbg_store_add(__LINE__, "FREERTOS : Real-Time operating system for");
    dbg_store_add(__LINE__, "microcontrollers.");
    dbg_store_add(__LINE__, "Developed in partnership with the world's");
    dbg_store_add(__LINE__, "leading chip companies over a %d-year period,", 15);
    dbg_store_add(__LINE__, "and now downloaded every %d seconds,", 170);
    dbg_store_add(__LINE__, "FreeRTOS is a market-leading real-time");
    dbg_store_add(__LINE__, "operating system (RTOS) for microcontrollers");
    dbg_store_add(__LINE__, "and small microprocessors.");
    dbg_store_add(__LINE__, "Distributed freely under the MIT open source");
    dbg_store_add(__LINE__, "license, FreeRTOS includes a kernel and a");
    dbg_store_add(__LINE__, "growing set of IoT libraries suitable for use");
    dbg_store_add(__LINE__, "accross all industry sectors.");
    dbg_store_add(__LINE__, "FreeRTOS is built with an emphasis on");
    dbg_store_add(__LINE__, "reliability and ease of use.");
    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "%d", 123456789);
    dbg_store_add(__LINE__, "%d", 12345678);
    dbg_store_add(__LINE__, "%d", 1234567);
    dbg_store_add(__LINE__, "%d", 123456);
    dbg_store_add(__LINE__, "%d", 12345);
    dbg_store_add(__LINE__, "%d", 1234);
    dbg_store_add(__LINE__, "%d", 123);
    dbg_store_add(__LINE__, "%d", 12);
    dbg_store_add(__LINE__, "%d", 1);
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$=^&*()-");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$=^&*()");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$=^&*(");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$=^&");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$=^");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$=");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ12345678");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ12345");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ12");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWXY");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVWX");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUVW");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTUV");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRSTU");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRST");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQRS");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQR");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOPQ");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNOP");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMNO");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMN");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLM");
    dbg_store_add(__LINE__, "ABCDEFGHIJKL");
    dbg_store_add(__LINE__, "ABCDEFGHIJK");
    dbg_store_add(__LINE__, "ABCDEFGHIJ");
    dbg_store_add(__LINE__, "ABCDEFGHI");
    dbg_store_add(__LINE__, "ABCDEFGH");
    dbg_store_add(__LINE__, "ABCDEFG");
    dbg_store_add(__LINE__, "ABCDEF");
    dbg_store_add(__LINE__, "ABCDF");
    dbg_store_add(__LINE__, "ABCD");
    dbg_store_add(__LINE__, "ABC");
    dbg_store_add(__LINE__, "AB");
    dbg_store_add(__LINE__, "A");
    dbg_store_add(__LINE__, " ");
    dbg_store_add(__LINE__, "A");
    dbg_store_add(__LINE__, "AB");
    dbg_store_add(__LINE__, "ABC");
    dbg_store_add(__LINE__, "ABCD");
    dbg_store_add(__LINE__, "ABCDE");
    dbg_store_add(__LINE__, "ABCDEF");
    dbg_store_add(__LINE__, "ABCDEFG");
    dbg_store_add(__LINE__, "ABCDEFGH");
    dbg_store_add(__LINE__, "ABCDEFGHI");
    dbg_store_add(__LINE__, "ABCDEFGHIJ");
    dbg_store_add(__LINE__, "ABCDEFGHIJK");
    dbg_store_add(__LINE__, "ABCDEFGHIJKL");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLM");
    dbg_store_add(__LINE__, "ABCDEFGHIJKLMN");

    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "           THE LION AND THE MOUSE              ");
    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "Once upon a time, a mouse got too close to a");
    dbg_store_add(__LINE__, "lion. The lion started to eat the mouse.");
    dbg_store_add(__LINE__, "'Spare me!' cried the mouse,");
    dbg_store_add(__LINE__, "'And someday I will repay your kindness.'");
    dbg_store_add(__LINE__, "The lion let the mouse go, although he");
    dbg_store_add(__LINE__, "couldn't imagine how such a tiny creature");
    dbg_store_add(__LINE__, "could ever help him. One day, the lion was");
    dbg_store_add(__LINE__, "caught in a hunter's net. He roared in misery.");
    dbg_store_add(__LINE__, "The little mouse came to his rescue and gnawed");
    dbg_store_add(__LINE__, "through the ropes holding the lion.");
    dbg_store_add(__LINE__, " ");
    dbg_store_add(__LINE__, "*** THE-END ***");
    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "                LORA AND TOM                   ");
    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "Lora lives in Texas.");
    dbg_store_add(__LINE__, "She comes from Mexico.");
    dbg_store_add(__LINE__, "She speaks Spanish but she learns English in");
    dbg_store_add(__LINE__, "school.");
    dbg_store_add(__LINE__, "She walks to school with Tom every morning.");
    dbg_store_add(__LINE__, "He speaks English but he learns Spanish");
    dbg_store_add(__LINE__, "in school.");
    dbg_store_add(__LINE__, "Tom and Lora like to walk together.");
    dbg_store_add(__LINE__, "Lora helps Tom with Spanish and Tom helps");
    dbg_store_add(__LINE__, "Lora with English.");
    dbg_store_add(__LINE__, "On Mondays and Wednesdays Lora and Tom speak");
    dbg_store_add(__LINE__, "only English.");
    dbg_store_add(__LINE__, "On Tuesdays and Thursdays they speak only");
    dbg_store_add(__LINE__, "Spanish.");
    dbg_store_add(__LINE__, "On Fridays Lora speaks English and Tom");
    dbg_store_add(__LINE__, "speaks Spanish.");
    dbg_store_add(__LINE__, "Lora learns English in school but she also");
    dbg_store_add(__LINE__, "English from Tom.");
    dbg_store_add(__LINE__, "Many people in Texas speak Spanish.");
    dbg_store_add(__LINE__, "Lora likes Texas very much.");
    dbg_store_add(__LINE__, "She says that the people are very nice");
    dbg_store_add(__LINE__, "and the food is delicious.");
    dbg_store_add(__LINE__, "She has many friends.");
    dbg_store_add(__LINE__, "They always go out together on Fridays");
    dbg_store_add(__LINE__, "nights.");
    dbg_store_add(__LINE__, " ");
    dbg_store_add(__LINE__, "*** THE-END ***");
    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "                     MY DOG                    ");
    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "The name of my dog is Jack. He is black");
    dbg_store_add(__LINE__, "in colour. He is four years old. He keeps cat");
    dbg_store_add(__LINE__, "away from my house. If he sees a cat, he runs");
    dbg_store_add(__LINE__, "after it.");
    dbg_store_add(__LINE__, "He barks when he sees a stranger in my house.");
    dbg_store_add(__LINE__, "He never bites. He eats everything my mother");
    dbg_store_add(__LINE__, "gives him. But he likes to eat meat. Whenever");
    dbg_store_add(__LINE__, "I come back from school, he wags his tail.");
    dbg_store_add(__LINE__, "After I finish my homework, Jack and I play");
    dbg_store_add(__LINE__, "together. Sometimes, he also jumps and runs");
    dbg_store_add(__LINE__, "after me. I love my dog. My dog also loves");
    dbg_store_add(__LINE__, "me very much.");
    dbg_store_add(__LINE__, " ");
    dbg_store_add(__LINE__, "*** THE-END ***");
    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "                    Lorem ipsum                ");
    dbg_store_add(__LINE__, "-----------------------------------------------");
    dbg_store_add(__LINE__, "lorem ipsum dolor sit amet, consectetur");
    dbg_store_add(__LINE__, "elit, sed do eiusmod tempor incididunt ut");
    dbg_store_add(__LINE__, "labore et");
    dbg_store_add(__LINE__, "dolore magna aliqua.");
    dbg_store_add(__LINE__, "Ut enim ad minim veniam, quis nostrud");
    dbg_store_add(__LINE__, "exercitation ullamco laboris nisi ut aliquip ex");
    dbg_store_add(__LINE__, "ea commodo consequat.");


    for (int i = 0; i < 65; i++) {
        dbg_store_add(__LINE__ + i, "-----------------------------------------------"); 
    }


    dbg_store_dump_current();
    dbg_store_stats();

    heap_dump();

    //dbg_store_mem_dump((void *)0x18b000, DBGSTORE_PARTITION_SIZE);
    //dbg_store_mem_dump((void *)0x18c000, DBGSTORE_PARTITION_SIZE);
    //dbg_store_mem_dump((void *)0x18d000, DBGSTORE_PARTITION_SIZE);
    //dbg_store_mem_dump((void *)0x18e000, DBGSTORE_PARTITION_SIZE);

    while (1);

    return 0;
}

void SysTick_Handler(void)
{
    systick_counter++;
}
