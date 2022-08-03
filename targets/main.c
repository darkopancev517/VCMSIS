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

#define RUN_PRINT_TEST        0
#define RUN_OSR_CRYPTO_TEST   0
#define RUN_HPLC_CRYPTO_TEST  0
#define RUN_HPLC_SPEED_TEST   1
#define RUN_TRNG_TEST         0

extern int stdio_uart_inited;
extern serial_t stdio_uart;

static volatile uint32_t systick_milis = 0;
extern uint32_t ske_lp_get_version(void);

#if RUN_PRINT_TEST
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


#if RUN_OSR_CRYPTO_TEST
extern uint32_t ECCp_get_curve_paras_test(void);
extern uint32_t ECCp_get_key_all_test(void);
extern uint32_t ECDH_all_test(void);
extern uint32_t ECDSA_all_test(void);
extern uint32_t SM2_all_test(void);
extern uint32_t SKE_all_test(void);
extern uint32_t HASH_all_test(void);
extern uint32_t HMAC_all_test(void);
extern uint32_t HASH_HMAC_sample_test(void);

uint32_t osr_crypto_test(void)
{
  printf("\r\n ------------ CRYPTO TEST ------------- \r\n");
  printf("PKE Version: %08lx\n\r", PKE_VERSION);fflush(stdout);
  printf("SKE Version: %08lx\r\n", ske_lp_get_version());

  if(SKE_all_test())
    return 1;

  if(HASH_all_test())
    return 1;

  if(HMAC_all_test())
    return 1;

  if(HASH_HMAC_sample_test())
    return 1;

  if(SM2_all_test())
    return 1;

  if(ECCp_get_curve_paras_test())
    return 1;

  if(ECCp_get_key_all_test())
    return 1;

  if(ECDH_all_test())
    return 1;

  if(ECDSA_all_test())
    return 1;

  printf("\r\n TEST OVER \r\n");//fflush(stdout);
  return 0;
}
#endif

uint32_t get_systick_micros(void)
{
  return systick_milis*1000 +1000-SysTick->VAL/(SystemCoreClock/1000000UL);
}

#if RUN_TRNG_TEST
static void trng_test(void)
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
#endif

#if RUN_HPLC_CRYPTO_TEST
extern int HPLC_aes_cbc_test(void);
extern int HPLC_sha256_test(void);
extern int HPLC_sm2_test(void);
extern int HPLC_ecc_test(void);
extern int HPLC_aes_gcm_test(void);
extern int HPLC_sm3_test(void);
extern int HPLC_sm4_test(void);

static void HPLC_all_test(void)
{
  printf("\r\n ------------------ HPLC CRYPTO TEST ------------------");

  /* 1. SHA256 */
  if (HPLC_sha256_test() != 0) {
    printf("HPLC sha256 test failed\n");
  }

  /* 2. SM2 */
  if (HPLC_sm2_test() != 0) {
    printf("HPLC sm2 test failed\n");
  }

  /* 3. ECC */
  if (HPLC_ecc_test() != 0) {
    printf("HPLC ecc test failed\n");
  }

  /* 4. AES-CBC */
  if (HPLC_aes_cbc_test() != 0) {
    printf("HPLC aes cbc test failed\n");
  }

  /* 5. AES-GCM */
  if (HPLC_aes_gcm_test() != 0) {
    printf("HPLC aes gcm test failed\n");
  }

  /* 6. SM3 */
  if (HPLC_sm3_test() != 0) {
    printf("HPLC sm3 test failed\n");
  }

  /* 7. SM4 */
  if (HPLC_sm4_test() != 0) {
    printf("HPLC sm4 test failed\n");
  }

  printf("\r\n\r\n TEST OVER\n");
}
#endif

#if RUN_HPLC_SPEED_TEST
extern uint32_t ske_speed_test();
#ifdef SKE_LP_DMA_FUNCTION
extern uint32_t ske_dma_speed_test();
#endif
extern uint32_t ske_gcm_speed_test();
#ifdef SKE_LP_DMA_FUNCTION
extern uint32_t ske_dma_gcm_speed_test();
#endif

extern void SM2_keyget_speed_test();
extern void SM2_sign_speed_test();
extern void SM2_verify_speed_test();
extern void SM2_encrypt_speed_test();
extern void SM2_decrypt_speed_test();
extern void SM2_exchange_speed_test();

extern uint32_t ecdsa_speed_test(eccp_curve_t *curve);
extern uint32_t ecdh_speed_test(const eccp_curve_t *curve);

extern void hash_speed_test(void);
#ifdef HASH_DMA_FUNCTION
extern void hash_dma_speed_test(void);
#endif

extern void hmac_speed_test(void);
#ifdef HASH_DMA_FUNCTION
extern void hmac_dma_speed_test(void);
#endif

static void HPLC_speed_test(void)
{
  // ----- SKE IP speed test
  if (ske_speed_test()) {
    printf("SKE speed test failed\n");
    return;
  }

#if 0

#ifdef SKE_LP_DMA_FUNCTION
  if (ske_dma_speed_test()) {
    printf("SKE DMA speed test failed\n");
    return;
  }
#endif

  if (ske_gmc_speed_test()) {
    printf("SKE GCM speed test failed\n");
    return;
  }

#ifdef SKE_LP_DMA_FUNCTION
  if (ske_dma_gcm_speed_test()) {
    printf("SKE DMA GCM speed test failed\n");
    return;
  }
#endif

  // ----- PKE SM2 speed test
  SM2_keyget_speed_test();

  SM2_sign_speed_test();

  SM2_verify_speed_test();

  SM2_encrypt_speed_test();

  SM2_decrypt_speed_test();

  SM2_exchange_speed_test();

  // ----- PKE ecdsa speed test
	printf("\r\n---brainpoolp160r1 \r\n");
	if(ecdsa_speed_test((eccp_curve_t *)brainpoolp160r1))  //brainpoolp160r1 //secp521r1
		return ;

  /*
	printf("\r\n---secp192r1 \r\n");
	if(ecdsa_speed_test((eccp_curve_t *)secp192r1))
		return; 

	printf("\r\n---secp224r1 \r\n");
	if(ecdsa_speed_test((eccp_curve_t *)secp224r1))
		return;

	printf("\r\n---secp256r1 \r\n");
	if(ecdsa_speed_test((eccp_curve_t *)secp256r1))
		return;

	printf("\r\n---secp384r1 \r\n");
	if(ecdsa_speed_test((eccp_curve_t *)secp384r1))
		return;

	printf("\r\n---brainpoolp512r1 \r\n");
	if(ecdsa_speed_test((eccp_curve_t *)brainpoolp512r1))
		return;

	printf("\r\n---secp521r1 \r\n");
	if(ecdsa_speed_test((eccp_curve_t *)secp521r1))
		return;
  */

  // ----- PKE ecdh speed test
	if(ecdh_speed_test(secp521r1))  //brainpoolp512r1 //secp521r1 //secp224r1
		return 1;

  // ----- HASH speed test
  hash_speed_test();

#if HASH_DMA_FUNCTION
  hash_dma_speed_test();
#endif

  // ----- HMAC speed test
  hmac_speed_test();

#if HASH_DMA_FUNCTION
  hmac_dma_speed_test();
#endif

#endif // #if 0

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

#if RUN_PRINT_TEST
  print_test();
#endif

#if RUN_OSR_CRYPTO_TEST
  osr_crypto_test();
#endif

#if RUN_TRNG_TEST
  trng_test();
#endif

#if RUN_HPLC_CRYPTO_TEST
  HPLC_all_test();
#endif

#if RUN_HPLC_SPEED_TEST
  HPLC_speed_test();
#endif

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
