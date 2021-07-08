/**************************************************************************//**
 * @file     startup_vc7351.s
 * @brief    CMSIS-Core(M) Device Startup File for VC7351 Cortex-M3 Device
 * @version  V1.0.0
 * @date     30. June 2021
 ******************************************************************************/
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

                .syntax  unified
                .arch    armv7-m

                .section .vectors
                .align   2
                .globl   __Vectors
                .globl   __Vectors_End
                .globl   __Vectors_Size
__Vectors:
                .long    __StackTop                         /*     Top of Stack */
                .long    Reset_Handler                      /*     Reset Handler */
                .long    NMI_Handler                        /* -14 NMI Handler */
                .long    HardFault_Handler                  /* -13 Hard Fault Handler */
                .long    MemManage_Handler                  /* -12 MPU Fault Handler */
                .long    BusFault_Handler                   /* -11 Bus Fault Handler */
                .long    UsageFault_Handler                 /* -10 Usage Fault Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    SVC_Handler                        /*  -5 SVC Handler */
                .long    DebugMon_Handler                   /*  -4 Debug Monitor Handler */
                .long    0                                  /*     Reserved */
                .long    PendSV_Handler                     /*  -2 PendSV Handler */
                .long    SysTick_Handler                    /*  -1 SysTick Handler */

                /* Interrupts */
                .long    PMU_Handler                        /*   0 PMU Handler */
                .long    RTC_Handler                        /*   1 RTC Handler */
                .long    UART32K0_Handler                   /*   2 UART32K0 Handler */
                .long    UART32K1_Handler                   /*   3 UART32K1 Handler */
                .long    I2C1_Handler                       /*   4 I2C1 Handler */
                .long    SPI1_Handler                       /*   5 SPI1 Handler */
                .long    UART0_Handler                      /*   6 UART0 Handler */
                .long    UART1_Handler                      /*   7 UART1 Handler */
                .long    UART2_Handler                      /*   8 UART2 Handler */
                .long    UART3_Handler                      /*   9 UART3 Handler */
                .long    UART4_Handler                      /*  10 UART4 Handler */
                .long    UART5_Handler                      /*  11 UART5 Handler */
                .long    ISO78160_Handler                   /*  12 ISO78160 Handler */
                .long    ISO78161_Handler                   /*  13 ISO78161 Handler */
                .long    TIM0_Handler                       /*  14 TIM0 Handler */
                .long    TIM1_Handler                       /*  15 TIM1 Handler */
                .long    TIM2_Handler                       /*  16 TIM2 Handler */
                .long    TIM3_Handler                       /*  17 TIM3 Handler */
                .long    PWM0_Handler                       /*  18 PWM0 Handler */
                .long    PWM1_Handler                       /*  19 PWM1 Handler */
                .long    PWM2_Handler                       /*  20 PWM2 Handler */
                .long    PWM3_Handler                       /*  21 PWM3 Handler */
                .long    DMA_Handler                        /*  22 DMA Handler */
                .long    FLASH_Handler                      /*  23 FLASH Handler */
                .long    ANA_Handler                        /*  24 ANA Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    SPI2_Handler                       /*  27 SPI2 Handler */
                .long    SPI3_Handler                       /*  28 SPI3 Handler */
                .long    KEYSCAN_Handler                    /*  29 KEYSCAN Handler */
                .long    UART6_Handler                      /*  30 UART6 Handler */
                .long    CRYPTO_Handler                     /*  31 CRYPTO Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    I2C2_Handler                       /*  36 I2C2 Handler */
                .long    GPIO_Handler                       /*  37 GPIO Handler */
                .long    MSGBOX_Handler                     /*  38 MSGBOX Handler */
                .long    0                                  /*     Reserved */
                .long    BPDET_Handler                      /*  40 BPDET Handler */
                .long    SDIO_Handler                       /*  41 SDIO Handler */

                .space   (6 * 4)                           /* Interrupts 42 .. 48 are left out */
__Vectors_End:
                .equ     __Vectors_Size, __Vectors_End - __Vectors
                .size    __Vectors, . - __Vectors


                .thumb
                .section .text
                .align   2

                .thumb_func
                .type    Reset_Handler, %function
                .globl   Reset_Handler
                .fnstart
Reset_Handler:
                bl       SystemInit

                ldr      r4, =__copy_table_start__
                ldr      r5, =__copy_table_end__

.L_loop0:
                cmp      r4, r5
                bge      .L_loop0_done
                ldr      r1, [r4]                /* source address */
                ldr      r2, [r4, #4]            /* destination address */
                ldr      r3, [r4, #8]            /* word count */
                lsls     r3, r3, #2              /* byte count */

.L_loop0_0:
                subs     r3, #4                  /* decrement byte count */
                ittt     ge
                ldrge    r0, [r1, r3]
                strge    r0, [r2, r3]
                bge      .L_loop0_0

                adds     r4, #12
                b        .L_loop0
.L_loop0_done:

                ldr      r3, =__zero_table_start__
                ldr      r4, =__zero_table_end__

.L_loop2:
                cmp      r3, r4
                bge      .L_loop2_done
                ldr      r1, [r3]                /* destination address */
                ldr      r2, [r3, #4]            /* word count */
                lsls     r2, r2, #2              /* byte count */
                movs     r0, 0

.L_loop2_0:
                subs     r2, #4                  /* decrement byte count */
                itt      ge
                strge    r0, [r1, r2]
                bge      .L_loop2_0

                adds     r3, #8
                b        .L_loop2
.L_loop2_done:

                bl       _start

                .fnend
                .size    Reset_Handler, . - Reset_Handler

/* The default macro is not used for HardFault_Handler
 * because this results in a poor debug illusion.
 */
                .thumb_func
                .type    HardFault_Handler, %function
                .weak    HardFault_Handler
                .fnstart
HardFault_Handler:
                b        .
                .fnend
                .size    HardFault_Handler, . - HardFault_Handler

                .thumb_func
                .type    Default_Handler, %function
                .weak    Default_Handler
                .fnstart
Default_Handler:
                b        .
                .fnend
                .size    Default_Handler, . - Default_Handler

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro   Set_Default_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm


/* Default exception/interrupt handler */

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  MemManage_Handler
                Set_Default_Handler  BusFault_Handler
                Set_Default_Handler  UsageFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  DebugMon_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  PMU_Handler
                Set_Default_Handler  RTC_Handler
                Set_Default_Handler  UART32K0_Handler
                Set_Default_Handler  UART32K1_Handler
                Set_Default_Handler  I2C1_Handler
                Set_Default_Handler  SPI1_Handler
                Set_Default_Handler  UART0_Handler
                Set_Default_Handler  UART1_Handler
                Set_Default_Handler  UART2_Handler
                Set_Default_Handler  UART3_Handler
                Set_Default_Handler  UART4_Handler
                Set_Default_Handler  UART5_Handler
                Set_Default_Handler  ISO78160_Handler
                Set_Default_Handler  ISO78161_Handler
                Set_Default_Handler  TIM0_Handler
                Set_Default_Handler  TIM1_Handler
                Set_Default_Handler  TIM2_Handler
                Set_Default_Handler  TIM3_Handler
                Set_Default_Handler  PWM0_Handler
                Set_Default_Handler  PWM1_Handler
                Set_Default_Handler  PWM2_Handler
                Set_Default_Handler  PWM3_Handler
                Set_Default_Handler  DMA_Handler
                Set_Default_Handler  FLASH_Handler
                Set_Default_Handler  ANA_Handler
                Set_Default_Handler  SPI2_Handler
                Set_Default_Handler  SPI3_Handler
                Set_Default_Handler  KEYSCAN_Handler
                Set_Default_Handler  UART6_Handler
                Set_Default_Handler  CRYPTO_Handler
                Set_Default_Handler  I2C2_Handler
                Set_Default_Handler  GPIO_Handler
                Set_Default_Handler  MSGBOX_Handler
                Set_Default_Handler  BPDET_Handler
                Set_Default_Handler  SDIO_Handler


                .end
