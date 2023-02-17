#include <stdio.h>

#include "../../crypto_include/utility.h"
#include "../../crypto_include/ske/ske.h"

#if defined(SUPPORT_SKE_MODE_CBC)
#include "../../crypto_include/ske/ske_cbc.h"
#endif

#if defined(SUPPORT_SKE_MODE_GCM)
#include "../../crypto_include/ske/ske_gcm_gmac.h"
#endif

extern uint32_t get_systick_micros(void);


#ifdef SUPPORT_SKE_AES_128

extern void ske_call_manage(void);



#if defined(SUPPORT_SKE_MODE_ECB)
uint32_t ske_lp_aes128_ecb_sample()
{
	uint8_t std_in[48]       = {0x81,0x70,0x99,0x44,0xE0,0xCB,0x2E,0x1D,0xB5,0xB0,0xA4,0x77,0xD1,0xA8,0x53,0x9B,
								0x0A,0x87,0x86,0xE3,0x4E,0xAA,0xED,0x99,0x30,0x3E,0xA6,0x97,0x55,0x95,0xB2,0x45,
								0x4D,0x5D,0x7F,0x91,0xEB,0xBD,0x4A,0xCD,0x72,0x6C,0x0E,0x0E,0x5E,0x3E,0xB5,0x5E,};
	uint8_t std_key[16]      = {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,};
	uint8_t std_cipher[48]   = {0x0B,0x54,0xE5,0x9F,0x47,0x14,0x4F,0xD8,0xEE,0x43,0x56,0xCA,0x0B,0x2D,0x7A,0x4B,
								0x84,0xD8,0x17,0x26,0xE2,0x8F,0x59,0xAD,0x95,0x56,0x8C,0x52,0xDA,0x98,0x3F,0x8D,
								0x65,0xED,0xDD,0x87,0x58,0x90,0xEC,0xE7,0xD8,0x03,0x66,0x9D,0xE2,0xF3,0x57,0x95,};
	uint8_t cipher[48], replain[48];

	uint32_t ret;

#ifdef SKE_LP_DMA_FUNCTION
	uint32_t *std_in_, *std_out_, *out, *out2;
#endif

	printf("\r\n  =================== AES128 ECB sample test ==================== \r\n");

    uint32_t start = 0;
    uint32_t duration = 0;

	/************** CPU style ***************/
	//encrypt
    start = get_systick_micros();
	ret = ske_lp_crypto(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, std_key, 0, NULL, std_in, cipher, 48);
    duration = get_systick_micros() - start;
	if(SKE_SUCCESS != ret ||memcmp_(std_cipher, cipher, 48))
	{
		printf("%s line-%d AES128 ecb encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 ecb encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//decrypt
    start = get_systick_micros();
	ret = ske_lp_crypto(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_DECRYPT, std_key, 0, NULL, cipher, replain, 48);
    duration = get_systick_micros() - start;
	if(SKE_SUCCESS != ret ||memcmp_(std_in, replain, 48))
	{
		printf("%s line-%d AES128 ecb decryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 ecb decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//the following encrypt & decrypt are equivalent to the above
	//encrypt
	memset_(cipher, 0, sizeof(cipher));
    start = get_systick_micros();
	ret  = ske_lp_init(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, std_key, 0, NULL);
	ret |= ske_lp_update_blocks(std_in, cipher, 16);
	ret |= ske_lp_update_blocks(std_in+16, cipher+16, 32);
    duration = get_systick_micros() - start;
	if(SKE_SUCCESS != ret ||memcmp_(std_cipher, cipher, 48))
	{
		printf("%s line-%d AES128 ecb encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 ecb encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//decrypt
	memset_(replain, 0, sizeof(replain));
    start = get_systick_micros();
	ret  = ske_lp_init(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_DECRYPT, std_key, 0, NULL);
	ret |= ske_lp_update_blocks(std_cipher, replain, 16);
	ret |= ske_lp_update_blocks(std_cipher+16, replain+16, 32);
    duration = get_systick_micros() - start;
	if(SKE_SUCCESS != ret ||memcmp_(std_in, replain, 48))
	{
		printf("%s line-%d AES128 ecb decryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 ecb decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}


#ifdef SKE_LP_DMA_FUNCTION
	/************** DMA style ***************/
	std_in_ = (uint32_t *)DMA_RAM_BASE;
	std_out_ = std_in_+64;

	out = std_out_+64;
	out2 = out+64;

	uint32_copy(std_in_, (uint32_t *)&std_in[0], 48/4);
	uint32_copy(std_out_, (uint32_t *)&std_cipher[0], 48/4);

	//ENCRYPT
    start = get_systick_micros();
	ret = ske_lp_dma_crypto(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, std_key, 0, NULL, std_in_, out, 48/4, ske_call_manage);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out, 48/4, std_out_, 48/4))
	{
		printf("%s line-%d AES128 ecb dma encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		print_buf_U32(out, 48/4, "out");
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 ecb dma encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//DECRYPT
    start = get_systick_micros();
	ret = ske_lp_dma_crypto(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_DECRYPT, std_key, 0, NULL, out, out2, 48/4, ske_call_manage);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out2, 48/4, std_in_, 48/4))
	{
		printf("%s line-%d AES128 ecb dma decryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		print_buf_U32(out2, 48/4, "out2");
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 ecb dma decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//the following encrypt & decrypt are equivalent to the above
	//encrypt
	uint32_clear(out, 48/4);
    start = get_systick_micros();
	ret  = ske_lp_dma_init(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, std_key, 0, NULL);
	ret |= ske_lp_dma_update_blocks(std_in_, out, 4, ske_call_manage);
	ret |= ske_lp_dma_update_blocks(std_in_+4, out+4, 8, ske_call_manage);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out, 48/4, std_out_, 48/4))
	{
		printf("%s line-%d AES128 ecb dma encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 ecb dma encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//decrypt
	uint32_clear(out2, 48/4);

    start = get_systick_micros();
	ret  = ske_lp_dma_init(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_DECRYPT, std_key, 0, NULL);
	ret |= ske_lp_dma_update_blocks(out, out2, 8, ske_call_manage);
	ret |= ske_lp_dma_update_blocks(out+8, out2+8, 4, ske_call_manage);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out2, 48/4, std_in_, 48/4))
	{
		printf("%s line-%d AES128 ecb dma encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 ecb dma decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	fflush(stdout);

#endif

	return 0;
}
#endif

#if defined(SUPPORT_SKE_MODE_CBC)
uint32_t ske_lp_aes128_cbc_sample()
{
	uint8_t std_in[48]       = {0x81,0x70,0x99,0x44,0xE0,0xCB,0x2E,0x1D,0xB5,0xB0,0xA4,0x77,0xD1,0xA8,0x53,0x9B,
								0x0A,0x87,0x86,0xE3,0x4E,0xAA,0xED,0x99,0x30,0x3E,0xA6,0x97,0x55,0x95,0xB2,0x45,
								0x4D,0x5D,0x7F,0x91,0xEB,0xBD,0x4A,0xCD,0x72,0x6C,0x0E,0x0E,0x5E,0x3E,0xB5,0x5E,};
	uint8_t std_key[16]      = {0xE0,0x70,0x99,0xF1,0xBF,0xAF,0xFD,0x7F,0x24,0x0C,0xD7,0x90,0xCA,0x4F,0xE1,0x34,};
	uint8_t std_iv[16]       = {0xC7,0x2B,0x65,0x91,0xA0,0xD7,0xDE,0x8F,0x6B,0x40,0x72,0x33,0xAD,0x35,0x81,0xD6};
	uint8_t std_cipher[48]   = {0x2C,0x1E,0xD4,0x56,0x36,0x2E,0x00,0x85,0xA8,0x1D,0x8E,0x61,0x69,0xAD,0x38,0xB7,
								0xB4,0x42,0x60,0xE1,0x56,0x8D,0x9E,0x85,0x0A,0x0C,0x95,0x37,0x44,0x02,0xDE,0x28,
								0x24,0xD5,0x05,0x61,0x30,0x42,0x42,0x86,0x0A,0xE7,0x17,0x3D,0xDD,0x19,0xEC,0x5B,};

	uint8_t cipher[48], replain[48];
	uint32_t ret;
#ifdef SKE_LP_DMA_FUNCTION
	uint32_t *std_in_, *std_out_, *out, *out2;
#endif

	printf("\r\n  =================== AES128 CBC sample test ==================== \r\n");

    uint32_t start = 0;
    uint32_t duration = 0;

	/************** CPU style ***************/
	//encrypt
    start = get_systick_micros();
	ret = ske_lp_cbc_crypto(SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, std_key, 0, std_iv, std_in, cipher, 48);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret ||memcmp_(cipher, std_cipher, 48))
	{
		printf("%s line-%d AES128 cbc encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 cbc encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//decrypt
    start = get_systick_micros();
	ret = ske_lp_cbc_crypto(SKE_ALG_AES_128, SKE_CRYPTO_DECRYPT, std_key, 0, std_iv, std_cipher, replain, 48);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret ||memcmp_(replain, std_in, 48))
	{
		printf("%s line-%d AES128 cbc decryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 cbc decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//the following encrypt & decrypt are equivalent to the above
	//encrypt
	memset_(cipher, 0, sizeof(cipher));
    start = get_systick_micros();
	ret  = ske_lp_cbc_init(SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, std_key, 0, std_iv);
	ret |= ske_lp_cbc_update_blocks(std_in, cipher, 16);
	ret |= ske_lp_cbc_update_blocks(std_in+16, cipher+16, 32);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret ||memcmp_(cipher, std_cipher, 48))
	{
		printf("%s line-%d AES128 cbc encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 cbc encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//decrypt
	memset_(replain, 0, sizeof(replain));
    start = get_systick_micros();
	ret = ske_lp_cbc_init(SKE_ALG_AES_128, SKE_CRYPTO_DECRYPT, std_key, 0, std_iv);
	ret |= ske_lp_cbc_update_blocks(std_cipher, replain, 16);
	ret |= ske_lp_cbc_update_blocks(std_cipher+16, replain+16, 32);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret ||memcmp_(std_in, replain, 48))
	{
		printf("%s line-%d AES128 cbc decryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 cbc decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}


#ifdef SKE_LP_DMA_FUNCTION
	/************** DMA style ***************/
	std_in_ = (uint32_t *)DMA_RAM_BASE;
	std_out_ = std_in_+64;

	out = std_out_+64;
	out2 = out+64;

	uint32_copy(std_in_, (uint32_t *)&std_in[0], 48/4);
	uint32_copy(std_out_, (uint32_t *)&std_cipher[0], 48/4);

	//encrypt
    start = get_systick_micros();
	ret = ske_lp_dma_cbc_crypto(SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, std_key, 0, std_iv, std_in_, out, 48/4, ske_call_manage);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out, 48/4, std_out_, 48/4))
	{
		printf("%s line-%d AES128 cbc dma encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 cbc dma encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//decrypt
    start = get_systick_micros();
	ret = ske_lp_dma_cbc_crypto(SKE_ALG_AES_128, SKE_CRYPTO_DECRYPT, std_key, 0, std_iv, out, out2, 48/4, ske_call_manage);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out2, 48/4, std_in_, 48/4))
	{
		printf("%s line-%d dma AES128 cbc dma decryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		print_buf_U32(out, 48/4, "out");
		print_buf_U32(out2, 48/4, "out2");
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 cbc dma decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//the following encrypt & decrypt are equivalent to the above
	//encrypt
	uint32_clear(out, 48/4);

    start = get_systick_micros();
	ret  = ske_lp_dma_cbc_init(SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, std_key, 0, std_iv);
	ret |= ske_lp_dma_cbc_update_blocks(std_in_, out, 4, ske_call_manage);
	ret |= ske_lp_dma_cbc_update_blocks(std_in_+4, out+4, 8, ske_call_manage);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out, 48/4, std_out_, 48/4))
	{
		printf("%s line-%d AES128 cbc dma encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 cbc dma encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//decrypt
	uint32_clear(out2, 48/4);
    start = get_systick_micros();
	ret  = ske_lp_dma_cbc_init(SKE_ALG_AES_128, SKE_CRYPTO_DECRYPT, std_key, 0, std_iv);
	ret |= ske_lp_dma_cbc_update_blocks(out, out2, 8, ske_call_manage);
	ret |= ske_lp_dma_cbc_update_blocks(out+8, out2+8, 4, ske_call_manage);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out2, 48/4, std_in_, 48/4))
	{
		printf("%s line-%d AES128 cbc dma encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 cbc dma decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	fflush(stdout);

#endif

	return 0;
}
#endif




#if defined(SUPPORT_SKE_MODE_GCM)
uint32_t ske_lp_aes128_gcm_sample()
{
	uint8_t std_plain[64]= {0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
							0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
							0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
							0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55,};
	uint8_t std_key[16]  = {0xfe,0xff,0xe9,0x92,0x86,0x65,0x73,0x1c,0x6d,0x6a,0x8f,0x94,0x67,0x30,0x83,0x08};
	uint8_t std_iv[12]   = {0xca,0xfe,0xba,0xbe,0xfa,0xce,0xdb,0xad,0xde,0xca,0xf8,0x88};
	uint8_t std_aad[20]  = {0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,
							0xab,0xad,0xda,0xd2};
	uint8_t std_cipher[] = {0x42,0x83,0x1e,0xc2,0x21,0x77,0x74,0x24,0x4b,0x72,0x21,0xb7,0x84,0xd0,0xd4,0x9c,
							0xe3,0xaa,0x21,0x2f,0x2c,0x02,0xa4,0xe0,0x35,0xc1,0x7e,0x23,0x29,0xac,0xa1,0x2e,
							0x21,0xd5,0x14,0xb2,0x54,0x66,0x93,0x1c,0x7d,0x8f,0x6a,0x5a,0xac,0x84,0xaa,0x05,
							0x1b,0xa3,0x0b,0x39,0x6a,0x0a,0xac,0x97,0x3d,0x58,0xe0,0x91,0x47,0x3f,0x59,0x85};
	uint8_t std_mac[]	 = {0xDA,0x80,0xCE,0x83,0x0C,0xFD,0xA0,0x2D,0xA2,0xA2,0x18,0xA1,0x74,0x4F,0x4C,0x76};

	uint8_t cipher[64], replain[64];
	uint8_t mac[16];
	uint32_t ret;
#ifdef SKE_LP_DMA_FUNCTION
	uint32_t *aad, *in, *out, *out2;
#endif

	SKE_GCM_CTX ctx[1];

	printf("\r\n  =================== AES128 GCM sample test ==================== \r\n");

    uint32_t start = 0;
    uint32_t duration = 0;

	/************** CPU style ***************/
	//encrypt
    start = get_systick_micros();
	ret = ske_lp_gcm_crypto(SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, std_key, 0, std_iv, 12, std_aad, 20, std_plain, cipher, 64, mac, 16);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || memcmp_(cipher, std_cipher, 64) || memcmp_(mac, std_mac, 16))
	{
		printf("%s line-%d AES128 gcm encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 gcm encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//decrypt
    start = get_systick_micros();
	ret = ske_lp_gcm_crypto(SKE_ALG_AES_128, SKE_CRYPTO_DECRYPT, std_key, 0, std_iv, 12, std_aad, 20, cipher, replain, 64, mac, 16);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || memcmp_(replain, std_plain, 64))
	{
		printf("%s line-%d AES128 gcm decryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 gcm decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//the following encrypt & decrypt are equivalent to the above
	//encrypt
	memset_(cipher, 0, sizeof(cipher));
    start = get_systick_micros();
	ret  = ske_lp_gcm_init(ctx, SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, std_key, 0, std_iv, 12, 20, 64, 16);
#ifdef SKE_LP_GCM_CPU_UPDATE_AAD_BY_STEP
	ret |= ske_lp_gcm_update_aad(ctx, std_aad, 1);
	ret |= ske_lp_gcm_update_aad(ctx, std_aad+1, 13);
	ret |= ske_lp_gcm_update_aad(ctx, std_aad+14, 6);
#else
	ret |= ske_lp_gcm_aad(ctx, std_aad);
#endif
	ret |= ske_lp_gcm_update_blocks(ctx, std_plain, cipher, 32);
	ret |= ske_lp_gcm_update_blocks(ctx, std_plain+32, cipher+32, 32);
	ret |= ske_lp_gcm_final(ctx, mac);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || memcmp_(cipher, std_cipher, 64) || memcmp_(mac, std_mac, 16))
	{
		printf("%s line-%d AES128 gcm encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 gcm encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}


	//decrypt
	memset_(replain, 0, sizeof(replain));
    start = get_systick_micros();
	ret  = ske_lp_gcm_init(ctx, SKE_ALG_AES_128, SKE_CRYPTO_DECRYPT, std_key, 0, std_iv, 12, 20, 64, 16);
#ifdef SKE_LP_GCM_CPU_UPDATE_AAD_BY_STEP
	ret |= ske_lp_gcm_update_aad(ctx, std_aad, 7);
	ret |= ske_lp_gcm_update_aad(ctx, std_aad+7, 10);
	ret |= ske_lp_gcm_update_aad(ctx, std_aad+17, 3);
#else
	ret |= ske_lp_gcm_aad(ctx, std_aad);
#endif
	ret |= ske_lp_gcm_update_blocks(ctx, cipher, replain, 16);
	ret |= ske_lp_gcm_update_blocks(ctx, cipher+16, replain+16, 32);
	ret |= ske_lp_gcm_update_blocks(ctx, cipher+48, replain+48, 16);
	ret |= ske_lp_gcm_final(ctx, mac);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || memcmp_(replain, std_plain, 64))
	{
		printf("%s line-%d AES128 gcm decryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 gcm decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}


#ifdef SKE_LP_DMA_FUNCTION
	/************** DMA style ***************/
	aad = (uint32_t *)DMA_RAM_BASE;
	in  = aad + 0x100;
	out = in + 0x100;
	out2 = out + 0x200;

	//copy aad
	uint32_copy(aad, (uint32_t *)std_aad, 20/4);
	uint32_clear(aad+5, 3);

	//copy plain
	uint32_copy(in, (uint32_t *)std_plain, 64/4);

	//encrypt
	uint32_clear(out, (64+16)/4);

    start = get_systick_micros();
	ret = ske_lp_dma_gcm_crypto(SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, std_key, 0, std_iv, 12, aad, 20,
			in, out, 64, 16, ske_call_manage);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out, 64/4, (uint32_t *)std_cipher, 64/4) ||
			uint32_BigNumCmp(out+64/4, 4, (uint32_t *)std_mac, 4))
	{
		printf("%s line-%d AES128 gcm dma encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		print_buf_U32(out, 48/4, "out");
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 gcm dma encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//copy cipher
	uint32_copy(in, (uint32_t *)out, 64/4);

	//decrypt
	uint32_clear(out2, (64+16)/4);

    start = get_systick_micros();
	ret = ske_lp_dma_gcm_crypto(SKE_ALG_AES_128, SKE_CRYPTO_DECRYPT, std_key, 0, std_iv, 12, aad, 20,
			in, out2, 64, 16, ske_call_manage);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out2, 64/4, (uint32_t *)std_plain, 64/4) ||
			uint32_BigNumCmp(out2+64/4, 4, (uint32_t *)std_mac, 4))
	{
		printf("%s line-%d AES128 gcm dma decryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		print_buf_U32(out2, 48/4, "out2");
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 gcm dma decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}


	//the following encrypt & decrypt are equivalent to the above

	//copy plain
	uint32_copy(in, (uint32_t *)std_plain, 64/4);

	//encrypt
	uint32_clear(out, (64+16)/4);

    start = get_systick_micros();
	ret  = ske_lp_dma_gcm_init(ctx, SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, std_key, 0, std_iv, 12, 20, 64, 16);
	ret |= ske_lp_dma_gcm_update_aad_blocks(ctx, aad, 16, ske_call_manage);
	ret |= ske_lp_dma_gcm_update_aad_blocks(ctx, aad+16/4, 4, ske_call_manage);
	ret |= ske_lp_dma_gcm_update_blocks(ctx, in, out, 16, ske_call_manage);
	ret |= ske_lp_dma_gcm_update_blocks(ctx, in+16/4, out+16/4, 32, ske_call_manage);
	ret |= ske_lp_dma_gcm_update_blocks(ctx, in+48/4, out+48/4, 16, ske_call_manage);
	ret |= ske_lp_dma_gcm_final(ctx);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out, 64/4, (uint32_t *)std_cipher, 64/4) ||
			uint32_BigNumCmp(out2+64/4, 4, (uint32_t *)std_mac, 4))
	{
		printf("%s line-%d AES128 gcm dma encryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		print_buf_U32(out, (64+16)/4, "out");
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 gcm dma encryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}

	//copy cipher
	uint32_copy(in, (uint32_t *)out, 64/4);

	//decrypt
	uint32_clear(out2, (64+16)/4);

    start = get_systick_micros();
	ret  = ske_lp_dma_gcm_init(ctx, SKE_ALG_AES_128, SKE_CRYPTO_DECRYPT, std_key, 0, std_iv, 12, 20, 64, 16);
	ret |= ske_lp_dma_gcm_update_aad_blocks(ctx, aad, 16, ske_call_manage);
	ret |= ske_lp_dma_gcm_update_aad_blocks(ctx, aad+16/4, 4, ske_call_manage);
	ret |= ske_lp_dma_gcm_update_blocks(ctx, in, out2, 32, ske_call_manage);
	ret |= ske_lp_dma_gcm_update_blocks(ctx, in+32/4, out2+32/4, 16, ske_call_manage);
	ret |= ske_lp_dma_gcm_update_blocks(ctx, in+48/4, out2+48/4, 16, ske_call_manage);
	ret |= ske_lp_dma_gcm_final(ctx);
    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out2, 64/4, (uint32_t *)std_plain, 64/4) ||
			uint32_BigNumCmp(out2+64/4, 4, (uint32_t *)std_mac, 4))
	{
		printf("%s line-%d AES128 gcm dma decryption failure, ret=%lu\r\n", __func__, __LINE__, ret);fflush(stdout);
		print_buf_U32(out2, (64+16)/4, "out2");
		return 1;
	}
	else
	{
		printf("%s line-%d AES128 gcm dma decryption success, duration: %lu us\r\n", __func__, __LINE__, duration);fflush(stdout);
	}/**/
#endif

	return 0;
}
#endif


#endif

