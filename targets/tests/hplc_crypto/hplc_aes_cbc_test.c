
#include <stdio.h>
#include "../../crypto_include/utility.h"
#include "../../crypto_include/ske/ske.h"
#include "../../crypto_include/trng.h"

extern uint32_t get_systick_micros(void);

#define USE_TRNG_GET_RAND 0

#if USE_TRNG_GET_RAND
static void get_rand_(uint8_t *rand, uint32_t bytes)
{
	get_rand(rand, bytes);
}
#endif

//get random value in [1,max_number-1]
static uint32_t ske_get_rand_number(uint32_t max_number)
{
	uint32_t i=34;

#if USE_TRNG_GET_RAND
	get_rand_((uint8_t *)&i, 4);
#else
	//simple random number generator
	i *= i<<1;
	i -= i*3;
	i ^= 0x78345bc;
	i += 89 | i>>1;
#endif

	i = i%max_number;
	if(0 == i) {
		i=1;
	}

	return i;
}

//callback function
static void ske_call_manage(void)
{
}

static uint32_t SKE_test(SKE_ALG ske_alg, SKE_MODE mode, uint8_t wordAlign, const uint8_t *std_plain,
				uint32_t byteLen, const uint8_t *key, uint16_t key_id, const uint8_t *iv, const uint8_t *std_cipher)
{
	uint32_t i,j;
	uint8_t key_buf[64+4];
	uint8_t iv_buf[16+4];
	uint8_t std_plain_buf[128+4];
	uint8_t std_cipher_buf[128+4];
	uint8_t cipher_buf[128+4];
	uint8_t replain_buf[128+4];
	uint8_t *cipher_, *replain_, *std_plain_, *std_cipher_, *key_, *iv_;
	int8_t ret;

	char *name[]={"DES","TDES_128","TDES_192","TDES_EEE_128", "TDES_EEE_192","AES_128","AES_192","AES_256","SM4"};
	char *oper_mode[]={"BYPASS", "ECB", "XTS", "CBC", "CFB", "OFB", "CTR"};
	uint32_t block_byteLen, key_byteLen;

	key_byteLen = ske_lp_get_key_byte_len(ske_alg);
	block_byteLen = ske_lp_get_block_byte_len(ske_alg);

	if(wordAlign) {
		memcpy_(std_plain_buf, (void *)std_plain, byteLen);
		memcpy_(std_cipher_buf, (void *)std_cipher, byteLen);
		if(key != NULL)
			memcpy_(key_buf, (void *)key, key_byteLen);
		if(SKE_MODE_ECB != mode)
			memcpy_(iv_buf, (void *)iv, block_byteLen);

		cipher_     = cipher_buf;
		replain_    = replain_buf;
		std_plain_  = std_plain_buf;
		std_cipher_ = std_cipher_buf;
		if(key != NULL)
			key_        = key_buf;
		else
			key_        = NULL;
		iv_         = iv_buf;
	} else  {
		memcpy_(std_plain_buf + 1, (void *)std_plain, byteLen);
		memcpy_(std_cipher_buf + 1, (void *)std_cipher, byteLen);
		if(key != NULL)
			memcpy_(key_buf + 1, (void *)key, key_byteLen);
		if(SKE_MODE_ECB != mode)
			memcpy_(iv_buf + 1, (void *)iv, block_byteLen);

		cipher_     = cipher_buf + 1;
		replain_    = replain_buf + 1;
		std_plain_  = std_plain_buf + 1;
		std_cipher_ = std_cipher_buf + 1;
		if(key != NULL)
			key_        = key_buf + 1;
		else
			key_        = NULL;
		iv_         = iv_buf + 1;
	}

  uint32_t start = 0;
  uint32_t duration = 0;


	/**************** test 1: one-time style ******************/
    start = get_systick_micros();

	//ENCRYPT
	ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, iv_);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske init 1 error");
		return 1;
	}

	ret = ske_lp_update_blocks(std_plain_, cipher_, byteLen);

	if(SKE_SUCCESS != ret) {
		//printf("\r\n ske encrypt 1 error");
		print_buf_U8(std_plain_, byteLen, "std_plain");
		print_buf_U8(cipher_, byteLen, "cipher");
		return 1;
	}

	//DECRYPT
	ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, iv_);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske init 2 error");
		return 1;
	}

	ret = ske_lp_update_blocks(cipher_, replain_, byteLen);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske decrypt 2 error");
		print_buf_U8(std_plain_, byteLen, "std_plain");
		print_buf_U8(cipher_, byteLen, "cipher");
		return 1;
	}

  duration = get_systick_micros() - start;

	if(memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen)) {
		printf("\r\n %s %s one time input test failure!!", name[ske_alg], oper_mode[mode]);
		print_buf_U8(std_plain_, byteLen, "std_plain");
		print_buf_U8(std_cipher_, byteLen, "std_cipher");
		print_buf_U8(cipher_, byteLen, "cipher");
		print_buf_U8(replain_, byteLen, "replain");
		return 1;
	} else {
		printf("\r\n %s %s one time input test success!!, duration: %lu us", name[ske_alg], oper_mode[mode], duration);
	}

	/**************** test 2: multiple style(one block every time) ******************/
	memset_(cipher_, 0, byteLen);
	memset_(replain_, 0, byteLen);

	//ENCRYPT
  start = get_systick_micros();

	ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, iv_);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske init 3 error");
		return 1;
	}

	for(i=0; i<(byteLen/block_byteLen)*block_byteLen; i+=block_byteLen)
	{
		ret = ske_lp_update_blocks(std_plain_+i, cipher_+i, block_byteLen);
		if(SKE_SUCCESS != ret) {
			printf("\r\n ske encrypt 3 error");
			return 1;
		}
	}

	//DECRYPT
	ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, iv_);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske init 4 error");
		return 1;
	}

	for(i=0;i<byteLen;i+=block_byteLen)
	{
		ret = ske_lp_update_blocks(cipher_+i, replain_+i, block_byteLen);

		if(SKE_SUCCESS != ret) {
			printf("\r\n ske decrypt 4 error");
			return 1;
		}
	}

  duration = get_systick_micros() - start;
	
	if(memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen)) {
		printf("\r\n %s %s multiple input test failure(one block every time)!!", name[ske_alg], oper_mode[mode]);
		print_buf_U8(cipher_, byteLen, "cipher");
		print_buf_U8(replain_, byteLen, "replain");
		return 1;
	} else {
		printf("\r\n %s %s multiple input test success(one block every time)!!, duration: %lu us", name[ske_alg], oper_mode[mode], duration);
	}


	/**************** test 3: multiple style(random blocks every time) ******************/
	memset_(cipher_, 0, byteLen);
	memset_(replain_, 0, byteLen);

	//ENCRYPT
  start = get_systick_micros();

	ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, key_, key_id, iv_);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske init 5 error");
		return 1;
	}

	i=0;
	while(i*block_byteLen < byteLen)
	{
		j = ske_get_rand_number(byteLen/block_byteLen);
		if(j > byteLen/block_byteLen - i) {
			j = byteLen/block_byteLen - i;
		}

		ret = ske_lp_update_blocks(std_plain_+i*block_byteLen, cipher_+i*block_byteLen, j*block_byteLen);

		if(SKE_SUCCESS != ret) {
			printf("\r\n ske encrypt 5 error");
			return 1;
		}
		i+=j;
	}

	//DECRYPT
	ret = ske_lp_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, key_, key_id, iv_);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske init 6 error");
		return 1;
	}

	i=0;
	while(i*block_byteLen < byteLen)
	{
		j = ske_get_rand_number(byteLen/block_byteLen);
		if(j > byteLen/block_byteLen - i)
		{
			j = byteLen/block_byteLen - i;
		}

		ret = ske_lp_update_blocks(cipher_+i*block_byteLen, replain_+i*block_byteLen, j*block_byteLen);

		if(SKE_SUCCESS != ret) {
			//printf("\r\n ske decrypt 6 error");
			return 1;
		}
		i+=j;
	}

  duration = get_systick_micros() - start;

	if(memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen)) {
		printf("\r\n %s %s multiple input test failure(random blocks every time)!!", name[ske_alg], oper_mode[mode]);
		print_buf_U8(cipher_, byteLen, "cipher");
		print_buf_U8(replain_, byteLen, "replain");
		return 1;
	} else {
		printf("\r\n %s %s multiple input test success(random blocks every time)!!, duration: %lu us", name[ske_alg], oper_mode[mode], duration);
	}

  printf("\r\n");

	fflush(stdout);

	return 0;
}

#ifdef SKE_LP_DMA_FUNCTION
static uint32_t SKE_DMA_test(SKE_ALG ske_alg, SKE_MODE mode, const uint8_t *std_plain,
				uint32_t wordLen, const uint8_t *key, uint16_t key_id, const uint8_t *iv, const uint8_t *std_cipher)
{
	uint32_t i,j;
	uint32_t *std_plain_buf=(uint32_t *)(DMA_RAM_BASE+0x100);     //std_plain_buf[132];
	uint32_t *std_cipher_buf=std_plain_buf+0x100;                 //std_cipher_buf[132];
	uint32_t *cipher_buf=std_cipher_buf+0x100;                    //cipher_buf[132];
	uint32_t *replain_buf=cipher_buf+0x100;                       //replain_buf[132];
	uint32_t *cipher_, *replain_, *std_plain_, *std_cipher_;
	uint32_t ret;

  uint32_t start = 0;
  uint32_t duration = 0;

	char *name[]={"DES","TDES_128","TDES_192","TDES_EEE_128","TDES_EEE_192","AES_128","AES_192","AES_256","SM4"};
	//char *oper_mode[]={"ECB", "CBC", "CFB", "OFB", "CTR"};
	char *oper_mode[]={"BYPASS", "ECB", "XTS", "CBC", "CFB", "OFB", "CTR"};
	uint32_t block_wordLen, dma_block_wordLen;
	//mode = 1;

	block_wordLen     = ske_lp_get_block_byte_len(ske_alg)/4;
	dma_block_wordLen = block_wordLen;

	uint32_copy(std_plain_buf, (uint32_t *)std_plain, wordLen);//memcpy_(std_plain_buf, std_plain, byteLen);
	uint32_copy(std_cipher_buf, (uint32_t *)std_cipher, wordLen);//memcpy_(std_cipher_buf, std_cipher, byteLen);

	cipher_     = cipher_buf;
	replain_    = replain_buf;
	std_plain_  = std_plain_buf;
	std_cipher_ = std_cipher_buf;

	/**************** test 1: one-time style ******************/
  start = get_systick_micros();

	//ENCRYPT
	ret = ske_lp_dma_crypto(ske_alg, mode, SKE_CRYPTO_ENCRYPT, (uint8_t *)key, key_id, (uint8_t *)iv, std_plain_, cipher_, wordLen, ske_call_manage);
	if(SKE_SUCCESS != ret) {
		printf("\r\n ske dma encrypt 1 error");
		return 1;
	}

	//DECRYPT
	ret = ske_lp_dma_crypto(ske_alg, mode, SKE_CRYPTO_DECRYPT, (uint8_t *)key, key_id, (uint8_t *)iv, cipher_, replain_, wordLen, ske_call_manage);
	if(SKE_SUCCESS != ret) {
		printf("\r\n ske dma decrypt 1 error");
		return 1;
	}

  duration = get_systick_micros() - start;

	if(uint32_BigNumCmp(cipher_, wordLen, std_cipher_, wordLen) || uint32_BigNumCmp(replain_, wordLen, std_plain_, wordLen)) {
		printf("\r\n %s %s one time input test failure!!", name[ske_alg], oper_mode[mode]);
		print_buf_U32(std_plain_, wordLen, "std_plain");
		print_buf_U32(std_cipher_, wordLen, "std_cipher");
		print_buf_U32(cipher_, wordLen, "cipher");
		print_buf_U32(replain_, wordLen, "replain");
		return 1;
	} else {
		printf("\r\n %s %s DMA one time input test success!!, duration: %lu us", name[ske_alg], oper_mode[mode], duration);
	}

	/**************** test 2: multiple style(one block every time) ******************/
	uint32_clear(cipher_, wordLen);
	uint32_clear(replain_, wordLen);

  start = get_systick_micros();

	//ENCRYPT
	ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, (uint8_t *)key, key_id, (uint8_t *)iv);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske dma int 3 error");
		return 1;
	}

	for(i=0; i<wordLen; i+=dma_block_wordLen) {
		ret = ske_lp_dma_update_blocks(std_plain_+(i), cipher_+(i), GET_MIN_LEN(dma_block_wordLen,wordLen-i), ske_call_manage);

		if(SKE_SUCCESS != ret) {
			printf("\r\n ske dma encrypt 3 error");
			return 1;
		}
	}

	//DECRYPT
	ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, (uint8_t *)key, key_id, (uint8_t *)iv);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske dma int 4 error");
		return 1;
	}

	for(i=0; i<wordLen; i+=dma_block_wordLen) {
		ret = ske_lp_dma_update_blocks(cipher_+(i), replain_+(i), GET_MIN_LEN(dma_block_wordLen,wordLen-i), ske_call_manage);
		if(SKE_SUCCESS != ret) {
			printf("\r\n ske dma decrypt 4 error");
			return 1;
		}
	}

  duration = get_systick_micros() - start;

	if(uint32_BigNumCmp(cipher_, wordLen, std_cipher_, wordLen) || uint32_BigNumCmp(replain_, wordLen, std_plain_, wordLen)) {
		printf("\r\n %s %s multiple input test failure(one block every time)!!", name[ske_alg], oper_mode[mode]);
		print_buf_U32(std_plain_, wordLen, "std_plain");
		print_buf_U32(cipher_, wordLen, "cipher");
		print_buf_U32(replain_, wordLen, "replain");
		return 1;
	} else {
		printf("\r\n %s %s DMA multiple input test success(one block every time)!!, duration: %lu us", name[ske_alg], oper_mode[mode], duration);
	}


	/**************** test 3: multiple style(random block every time) ******************/
	uint32_clear(cipher_, wordLen);
	uint32_clear(replain_, wordLen);

  start = get_systick_micros() - start;

	//ENCRYPT
	ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_ENCRYPT, (uint8_t *)key, key_id, (uint8_t *)iv);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske dma int 5 error");
		return 1;
	}

	i=0;
	while(i < wordLen) {
		j = ske_get_rand_number(wordLen/dma_block_wordLen)*dma_block_wordLen;
		j = GET_MIN_LEN(j,wordLen-i);

		ret = ske_lp_dma_update_blocks(std_plain_+(i), cipher_+(i), j, ske_call_manage);

		if(SKE_SUCCESS != ret) {
			printf("\r\n ske dma encrypt 5 error");
			return 1;
		}

		i+=j;
	}

	//DECRYPT
	ret = ske_lp_dma_init(ske_alg, mode, SKE_CRYPTO_DECRYPT, (uint8_t *)key, key_id, (uint8_t *)iv);

	if(SKE_SUCCESS != ret) {
		printf("\r\n ske dma int 6 error");
		return 1;
	}

	i=0;
	while(i < wordLen)
	{
		j = ske_get_rand_number(wordLen/dma_block_wordLen)*dma_block_wordLen;
		j = GET_MIN_LEN(j,wordLen-i);

		ret = ske_lp_dma_update_blocks(cipher_+(i), replain_+(i), j, ske_call_manage);

		if(SKE_SUCCESS != ret) {
			printf("\r\n ske dma decrypt 6 error");
			return 1;
		}

		i+=j;
	}

  duration = get_systick_micros() - start;

	if(uint32_BigNumCmp(cipher_, wordLen, std_cipher_, wordLen) || uint32_BigNumCmp(replain_, wordLen, std_plain_, wordLen)) {
		printf("\r\n %s %s multiple input test failure(random blocks every time)!!", name[ske_alg], oper_mode[mode]);
		print_buf_U32(cipher_, wordLen, "cipher");
		print_buf_U32(replain_, wordLen, "replain");
		return 1;
	} else {
		printf("\r\n %s %s DMA multiple input test success(random blocks every time)!!, duration: %lu us", name[ske_alg], oper_mode[mode], duration);
	}

	fflush(stdout);

  // TODO: SUPPORT_SKE_IRQ

	return 0;
}
#endif

static const uint8_t std_in[128] =      {
								0x81,0x70,0x99,0x44,0xE0,0xCB,0x2E,0x1D,0xB5,0xB0,0xA4,0x77,0xD1,0xA8,0x53,0x9B,
								0x0A,0x87,0x86,0xE3,0x4E,0xAA,0xED,0x99,0x30,0x3E,0xA6,0x97,0x55,0x95,0xB2,0x45,
								0x4D,0x5D,0x7F,0x91,0xEB,0xBD,0x4A,0xCD,0x72,0x6C,0x0E,0x0E,0x5E,0x3E,0xB5,0x5E,
								0xF6,0xB1,0x5A,0x13,0x8E,0x22,0x6E,0xCD,0x1B,0x23,0x5A,0xB5,0xBB,0x52,0x51,0xC1,
								0x33,0x76,0xB2,0x64,0x48,0xA9,0xAC,0x1D,0xE8,0xBD,0x52,0x64,0x8C,0x0B,0x5F,0xFA,
								0x94,0x44,0x86,0x82,0xE3,0xCB,0x4D,0xE9,0xCB,0x8A,0xE7,0xF4,0xBD,0x41,0x0E,0xD5,
								0x02,0xB1,0x25,0x3A,0xD0,0x8B,0xB2,0x79,0x69,0xB5,0xF0,0x2B,0x10,0x02,0x9D,0x67,
								0xD0,0x7E,0x18,0x64,0xD9,0x4D,0x4F,0xCA,0x20,0x81,0x51,0xE2,0x6F,0x5F,0xEE,0x26,};
static const uint8_t std_key[64] =      {
								0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,
								0xB4,0x42,0x60,0xE1,0x56,0x8D,0x9E,0x85,0x0A,0x0C,0x95,0x37,0x44,0x02,0xDE,0x28,
								0xF0,0x79,0xA5,0x85,0xEC,0x84,0x36,0x90,0xC8,0x15,0x0A,0x31,0x47,0x24,0xE4,0x88,
								0x5F,0xD0,0x3B,0x37,0x9D,0xF7,0x0C,0x8E,0x4C,0x4F,0x77,0x26,0x17,0x4F,0x75,0xF7,};
static const uint8_t std_iv[16] =       {
								0xC7,0x2B,0x65,0x91,0xA0,0xD7,0xDE,0x8F,0x6B,0x40,0x72,0x33,0xAD,0x35,0x81,0xD6};

#ifdef SUPPORT_SKE_AES_128
static const uint8_t std_aes_128_cbc_out[128] = {
								0x2C,0x1E,0xD4,0x56,0x36,0x2E,0x00,0x85,0xA8,0x1D,0x8E,0x61,0x69,0xAD,0x38,0xB7,
								0xB4,0x42,0x60,0xE1,0x56,0x8D,0x9E,0x85,0x0A,0x0C,0x95,0x37,0x44,0x02,0xDE,0x28,
								0x24,0xD5,0x05,0x61,0x30,0x42,0x42,0x86,0x0A,0xE7,0x17,0x3D,0xDD,0x19,0xEC,0x5B,
								0x93,0xD2,0x67,0x84,0xE3,0xED,0xA0,0x21,0x22,0x78,0x8D,0xD6,0x28,0x64,0x60,0xAA,
								0xDD,0x9D,0x7E,0xA8,0xE2,0x79,0x68,0xBE,0x82,0xA6,0xBC,0x9F,0x5D,0xE8,0x4E,0xA0,
								0xB7,0xAA,0xDA,0xC7,0x91,0xA5,0x15,0xD7,0x80,0xBC,0x24,0x6A,0x90,0xB6,0x17,0xDF,
								0x10,0xD8,0x7B,0x2D,0xA2,0x35,0xCA,0xF7,0x56,0x1D,0xD8,0x03,0x97,0x3C,0xDE,0xAF,
								0x90,0xF7,0x1B,0x4A,0x34,0x55,0xC9,0x16,0xEA,0xA5,0xCE,0xF8,0x4B,0x0B,0x10,0x8A,};

static int HPLC_aes_128_cbc_test()
{
	int ret = 0;

#if defined (SUPPORT_SKE_MODE_CBC) 
	printf("\r\n\r\n =================== HPLC AES-128 CBC test ==================== ");
	ret |= SKE_test(SKE_ALG_AES_128, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_aes_128_cbc_out);
#endif

	if(ret) return 1;

#ifdef SKE_LP_DMA_FUNCTION
#if defined (SUPPORT_SKE_MODE_CBC)
	printf("\r\n\r\n =================== HPLC AES-128 DMA CBC test ==================== ");fflush(stdout);
	ret |= SKE_DMA_test(SKE_ALG_AES_128, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_aes_128_cbc_out);
#endif

	if(ret) return 1;
#endif

	return 0;
}
#endif

#ifdef SUPPORT_SKE_AES_192
static const uint8_t std_aes_192_cbc_out[128] = {
								0xB3,0x95,0x80,0xF4,0xD8,0x83,0x49,0xB8,0x0E,0x28,0xE6,0x78,0x98,0x46,0xD5,0x1D,
								0x52,0x0B,0xEA,0xA4,0xC2,0x5D,0xE4,0x9E,0xC0,0xFB,0xB1,0x48,0x59,0x91,0x17,0x73,
								0x4D,0x1F,0xE6,0x30,0x8C,0x6B,0x0A,0x29,0x95,0x3B,0x81,0x7B,0xBD,0x99,0xB5,0x85,
								0xCB,0x2D,0x26,0x90,0xB0,0xC8,0xE3,0x13,0xCD,0x1D,0xAC,0x02,0x14,0xD6,0xBC,0xCB,
								0xD7,0xE0,0xE3,0x62,0x4A,0x10,0x1B,0xDE,0x26,0x8B,0xB7,0x5A,0x34,0xB5,0x40,0xB5,
								0x6B,0xBA,0x91,0x7D,0x9F,0x39,0xF1,0x0E,0x89,0x7E,0x19,0xE9,0x39,0x6F,0x55,0x21,
								0x1F,0x93,0xCA,0x77,0x0F,0x9C,0x57,0xA9,0xC3,0x92,0x32,0xF6,0x54,0x1E,0xBA,0xDD,
								0xF3,0xE6,0x40,0x28,0x6A,0x59,0xB0,0xFC,0xA8,0x0C,0xC2,0x49,0x22,0x72,0xC8,0x9C,};

int HPLC_aes_192_cbc_test()
{
	int ret = 0;

#if defined (SUPPORT_SKE_MODE_CBC) 
	printf("\r\n\r\n =================== HPLC AES-192 CBC test ==================== ");
	ret |= SKE_test(SKE_ALG_AES_192, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_aes_192_cbc_out);
#endif

	if(ret) return 1;

#ifdef SKE_LP_DMA_FUNCTION
#if defined (SUPPORT_SKE_MODE_CBC)
	printf("\r\n\r\n =================== HPLC AES-192 CBC DMA test ==================== ");fflush(stdout);
	ret |= SKE_DMA_test(SKE_ALG_AES_192, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_aes_192_cbc_out);
#endif

	if(ret) return 1;
#endif

	return 0;
}
#endif

#ifdef SUPPORT_SKE_AES_256
static const uint8_t std_aes_256_cbc_out[128] = {
								0x7C,0xA4,0x8E,0x82,0x99,0xFC,0x5A,0xD3,0xE9,0x08,0xB7,0x65,0xE3,0x0D,0x7A,0x3B,
								0x63,0xE3,0x82,0xF6,0x46,0x23,0xAC,0xE0,0x41,0xC4,0x0B,0x29,0xF5,0x92,0x59,0x2F,
								0x96,0xAD,0xBB,0xA5,0x58,0x52,0x49,0x32,0x59,0x25,0x20,0xBA,0x17,0xDB,0x52,0xE9,
								0x42,0x32,0x64,0x38,0x86,0xF2,0x02,0xA9,0x6B,0xA2,0x58,0x76,0xC6,0x30,0x2D,0xFC,
								0xE9,0x93,0x46,0x7F,0xB1,0x38,0xE2,0x93,0x98,0xA7,0x30,0x61,0xEC,0xCF,0xBE,0x5A,
								0xA1,0xAE,0x0E,0xDC,0x93,0x7C,0xCA,0x4E,0x0C,0x7A,0x60,0x87,0x14,0x82,0x9D,0x4E,
								0x7E,0x47,0x16,0x77,0x06,0xA1,0x8F,0xA7,0x45,0x59,0x16,0x1A,0x00,0xB4,0x41,0x29,
								0xA9,0x5C,0x3E,0x41,0x65,0xB8,0xC9,0x24,0xAB,0xE0,0x4A,0x4A,0x2D,0xC2,0xB3,0x2D,};

static int HPLC_aes_256_cbc_test()
{
	int ret = 0;

#if defined (SUPPORT_SKE_MODE_CBC)
	printf("\r\n\r\n =================== HPLC AES-256 CBC test ==================== ");
	ret |= SKE_test(SKE_ALG_AES_256, SKE_MODE_CBC, 1, std_in, 128, std_key, 0, std_iv, std_aes_256_cbc_out);
#endif

if(ret) return 1;

#ifdef SKE_LP_DMA_FUNCTION
#if defined (SUPPORT_SKE_MODE_CBC)
	printf("\r\n\r\n =================== HPLC AES-256 CBC DMA test ==================== ");fflush(stdout);
	ret |= SKE_DMA_test(SKE_ALG_AES_256, SKE_MODE_CBC, std_in, 32, std_key, 0, std_iv, std_aes_256_cbc_out);
#endif

	if(ret) return 1;
#endif

	return 0;
}
#endif

int HPLC_aes_cbc_test(void)
{
#ifdef SUPPORT_SKE_AES_128
  if (HPLC_aes_128_cbc_test() != 0) {
    printf("HPLC aes 128 cbc test failed\n");
    return 1;
  }
#endif

#ifdef SUPPORT_SKE_AES_192
  if (HPLC_aes_192_cbc_test() != 0) {
    printf("HPLC aes 192 cbc test failed\n");
    return 1;
  }
#endif

#ifdef SUPPORT_SKE_AES_256
  if (HPLC_aes_256_cbc_test() != 0) {
    printf("HPLC aes 256 cbc test failed\n");
    return 1;
  }
#endif

  return 0;
}
