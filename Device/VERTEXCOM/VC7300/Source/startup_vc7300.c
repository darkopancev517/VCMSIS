/******************************************************************************
 * @file     startup_vc7300.c
 * @brief    CMSIS-Core(M) Device Startup File for
 *           VC7300 Device
 * @version  V1.0.0
 * @date     28. June 2021
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

#include "vc7300.h"

/*---------------------------------------------------------------------------
  External References
 *---------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;

extern __NO_RETURN void __PROGRAM_START(void);

/*---------------------------------------------------------------------------
  Internal References
 *---------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler  (void);
__NO_RETURN void Default_Handler(void);

/*---------------------------------------------------------------------------
  Exception / Interrupt Handler
 *---------------------------------------------------------------------------*/
/* Exceptions Handler */
void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak));
void MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

/* Interrupts Handler */
void PMU_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void UART32K0_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UART32K1_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void UART0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART2_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART3_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void ISO78160_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void ISO78161_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM0_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM0_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM2_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM3_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void ANA_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void KEYSCAN_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void UART6_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void CRYPTO_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIO_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const VECTOR_TABLE_Type __VECTOR_TABLE[64];
       const VECTOR_TABLE_Type __VECTOR_TABLE[64] __VECTOR_TABLE_ATTRIBUTE = {
  (VECTOR_TABLE_Type)(&__INITIAL_SP),   /*     Initial Stack Pointer */
  Reset_Handler,                        /*     Reset Handler */
  NMI_Handler,                          /* -14 NMI Handler */
  HardFault_Handler,                    /* -13 Hard Fault Handler */
  MemManage_Handler,                    /* -12 MPU Fault Handler */
  BusFault_Handler,                     /* -11 Bus Fault Handler */
  UsageFault_Handler,                   /* -10 Usage Fault Handler */
  0,                                    /*     Reserved */
  0,                                    /*     Reserved */
  0,                                    /*     Reserved */
  0,                                    /*     Reserved */
  SVC_Handler,                          /*  -5 SVCall Handler */
  DebugMon_Handler,                     /*  -4 Debug Monitor Handler */
  0,                                    /*     Reserved */
  PendSV_Handler,                       /*  -2 PendSV Handler */
  SysTick_Handler,                      /*  -1 SysTick Handler */

  /* Interrupts */
  PMU_Handler,                          /*   0 PMU Handler */
  RTC_Handler,                          /*   1 RTC Handler */
  UART32K0_Handler,                     /*   2 UART32K0 Handler */
  UART32K1_Handler,                     /*   3 UART32K1 Handler */
  I2C1_Handler,                         /*   4 I2C1 Handler */
  SPI1_Handler,                         /*   5 SPI1 Handler */
  UART0_Handler,                        /*   6 UART0 Handler */
  UART1_Handler,                        /*   7 UART1 Handler */
  UART2_Handler,                        /*   8 UART2 Handler */
  UART3_Handler,                        /*   9 UART3 Handler */
  UART4_Handler,                        /*  10 UART4 Handler */
  UART5_Handler,                        /*  11 UART5 Handler */
  ISO78160_Handler,                     /*  12 ISO78160 Handler */
  ISO78161_Handler,                     /*  13 ISO78161 Handler */
  TIM0_Handler,                         /*  14 TIM0 Handler */
  TIM1_Handler,                         /*  15 TIM1 Handler */
  TIM2_Handler,                         /*  16 TIM2 Handler */
  TIM3_Handler,                         /*  17 TIM3 Handler */
  PWM0_Handler,                         /*  18 PWM0 Handler */
  PWM1_Handler,                         /*  19 PWM1 Handler */
  PWM2_Handler,                         /*  20 PWM2 Handler */
  PWM3_Handler,                         /*  21 PWM3 Handler */
  DMA_Handler,                          /*  22 DMA Handler */
  FLASH_Handler,                        /*  23 FLASH Handler */
  ANA_Handler,                          /*  24 ANA Handler */
  0,                                    /*     Reserved */
  0,                                    /*     Reserved */
  SPI2_Handler,                         /*  27 SPI2 Handler */
  SPI3_Handler,                         /*  28 SPI3 Handler */
  KEYSCAN_Handler,                      /*  29 KEYSCAN Handler */
  UART6_Handler,                        /*  30 UART6 Handler */
  CRYPTO_Handler,                       /*  31 CRYPTO Handler */
  0,                                    /*     Reserved */
  0,                                    /*     Reserved */
  0,                                    /*     Reserved */
  0,                                    /*     Reserved */
  I2C2_Handler,                         /*  36 I2C2 Handler */
  GPIO_Handler,                         /*  37 GPIO Handler */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*---------------------------------------------------------------------------
  Reset Handler called on controller reset
 *---------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
  SystemInit();                    /* CMSIS System Initialization */
  __PROGRAM_START();               /* Enter PreMain (C library entry point) */
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/*---------------------------------------------------------------------------
  Hard Fault Handler
 *---------------------------------------------------------------------------*/
void HardFault_Handler(void)
{
  while(1);
}

/*---------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *---------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#endif
