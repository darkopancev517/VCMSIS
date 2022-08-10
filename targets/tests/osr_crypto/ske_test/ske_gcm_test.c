#include <stdio.h>

#include "../../crypto_include/ske/ske_gcm_gmac.h"
#include "../../crypto_include/utility.h"

extern uint32_t get_systick_micros(void);
extern uint32_t get_systick_milis(void);

extern uint32_t ske_get_rand_number(uint32_t max_number);

//GCM mode is only available for AES and SM4(block length is 128bits)

#ifdef SUPPORT_SKE_MODE_GCM

extern void ske_call_manage(void);

uint32_t ske_gcm_test(SKE_ALG alg, uint8_t wordAlign, uint8_t *std_plain, uint32_t byteLen, uint8_t *key,
		uint16_t sp_key_idx, uint8_t *iv, uint8_t ivByteLen, uint8_t *aad, uint8_t aadByteLen, uint8_t *std_cipher,
		uint8_t *std_mac, uint32_t macByteLen)
{
	uint8_t key_buf[32+4];
	uint8_t iv_buf[64+4];
	uint8_t aad_buf[64+4];
	uint8_t std_plain_buf[256+4];
	uint8_t std_cipher_buf[256+4];
	uint8_t std_mac_buf[16+4];
	uint8_t cipher_buf[256+4];
	uint8_t replain_buf[256+4];
	uint8_t mac_buf[16+4];
	uint8_t *cipher_, *replain_, *mac_, *std_plain_, *std_cipher_, *std_mac_, *key_, *iv_, *aad_;
	uint32_t i,j;
	uint32_t block_byteLen, key_byteLen;
	uint32_t ret;

	char *name[]={"","","","","","AES_128","AES_192","AES_256","SM4"};

	SKE_GCM_CTX ctx[1];

	key_byteLen = ske_lp_get_key_byte_len(alg);
	block_byteLen = ske_lp_get_block_byte_len(alg); //16;

	printf("\r\n %s GCM test(iv=%d bytes,AAD=%d bytes,P/C=%lu bytes, mac=%lu bytes)",
			name[alg],ivByteLen,aadByteLen,byteLen,macByteLen);

	if(wordAlign)
	{
		cipher_     = cipher_buf;
		replain_    = replain_buf;
		mac_        = mac_buf;
		std_plain_  = std_plain_buf;
		std_cipher_ = std_cipher_buf;
		std_mac_    = std_mac_buf;
		if(key)
			key_    = key_buf;
		else
			key_    = NULL;
		iv_         = iv_buf;
		aad_        = aad_buf;
	}
	else
	{
		cipher_     = cipher_buf + 1;
		replain_    = replain_buf + 1;
		mac_        = mac_buf + 1;
		std_plain_  = std_plain_buf + 1;
		std_cipher_ = std_cipher_buf + 1;
		std_mac_    = std_mac_buf + 1;
		if(key)
			key_    = key_buf + 1;
		else
			key_    = NULL;
		iv_         = iv_buf + 1;
		aad_        = aad_buf + 1;
	}
	memcpy_(std_plain_, std_plain, byteLen);
	memcpy_(std_cipher_, std_cipher, byteLen);
	memcpy_(std_mac_, std_mac, macByteLen);
	if(key)
		memcpy_(key_, key, key_byteLen);
	memcpy_(iv_, iv, ivByteLen);
	memcpy_(aad_, aad, aadByteLen);

    uint32_t start = 0;
    uint32_t duration = 0;

	/**************** test 1: one-time style ******************/
#if 1
	//ENCRYPT
    start = get_systick_micros();

	ret = ske_lp_gcm_init(ctx, alg, SKE_CRYPTO_ENCRYPT, key_, sp_key_idx, iv_, ivByteLen, aadByteLen, byteLen, macByteLen);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm init 0 error, ret=%lu", ret);
		return 1;
	}

	ret = ske_lp_gcm_aad(ctx, aad_);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm aad 0 error");
		return 1;
	}

	ret = ske_lp_gcm_update_blocks(ctx, std_plain_, cipher_, byteLen);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm encrypt 0 error, ret=%lu", ret);
		print_buf_U8(std_plain_, byteLen, "std_plain");
		print_buf_U8(cipher_, byteLen, "cipher");
		return 1;
	}

	ret = ske_lp_gcm_final(ctx, mac_);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm final 0 error");
		return 1;
	}

	//DECRYPT
	ret = ske_lp_gcm_init(ctx, alg, SKE_CRYPTO_DECRYPT, key_, sp_key_idx, iv_, ivByteLen, aadByteLen, byteLen, macByteLen);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm init 1 error, ret=%lu", ret);
		return 1;
	}

	ret = ske_lp_gcm_aad(ctx, aad_);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm aad 1 error");
		return 1;
	}

	ret = ske_lp_gcm_update_blocks(ctx, cipher_, replain_, byteLen);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm decrypt 1 error, ret=%lu", ret);
		print_buf_U8(std_plain_, byteLen, "std_plain");
		print_buf_U8(cipher_, byteLen, "cipher");
		print_buf_U8(replain_, byteLen, "replain");
		return 1;
	}

	ret = ske_lp_gcm_final(ctx, mac_);

    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske final 1 error");
		return 1;
	}

#else

	//ENCRYPT
	ret = ske_lp_gcm_crypto(alg, SKE_CRYPTO_ENCRYPT, key_, sp_key_idx, iv_, ivByteLen, aad_, aadByteLen,
			std_plain_, cipher_, byteLen, mac_, macByteLen);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n encrypt 1 error, ret=%lu", ret);
		return 1;
	}

	//DECRYPT
	ret = ske_lp_gcm_crypto(alg, SKE_CRYPTO_DECRYPT, key_, sp_key_idx, iv_, ivByteLen, aad_, aadByteLen,
			cipher_, replain_, byteLen, mac_, macByteLen);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n decrypt 1 error, ret=%lu", ret);
		return 1;
	}
#endif

	if(memcmp_(mac_, std_mac_, macByteLen) || memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen))
	{
		printf("\r\n one time input test failure!!");
		print_buf_U8(std_plain_, byteLen, "std_plain");
		print_buf_U8(std_mac_, macByteLen, "std_mac");
		print_buf_U8(std_cipher_, byteLen, "std_cipher");
		print_buf_U8(key_, key_byteLen, "key");
		print_buf_U8(iv_, ivByteLen, "iv");
		print_buf_U8(aad_, aadByteLen, "aad");
		print_buf_U8(cipher_, byteLen, "cipher");
		print_buf_U8(mac_, macByteLen, "mac");
		print_buf_U8(replain_, byteLen, "replain");
		return 1;
	}
	else
	{
		printf("\r\n one time input test success!!, duration: %lu us", duration);
	}//fflush(stdout);


	/**************** test 2: multiple style(one block every time) ******************/
	memset_(cipher_, 0, byteLen);
	memset_(replain_, 0, byteLen);
	memset_(mac_, 0, 16);

	//ENCRYPT
    start = get_systick_micros();
	ret = ske_lp_gcm_init(ctx, alg, SKE_CRYPTO_ENCRYPT, key_, sp_key_idx, iv_, ivByteLen, aadByteLen, byteLen, macByteLen);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm init 2 error");
		return 1;
	}

	ret = ske_lp_gcm_aad(ctx, aad_);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm aad 2 error");
		return 1;
	}

	for(i=0; i<byteLen; i+=block_byteLen)
	{
		ret = ske_lp_gcm_update_blocks(ctx, std_plain_+i, cipher_+i, GET_MIN_LEN(block_byteLen, byteLen-i));
		if(SKE_SUCCESS != ret)
		{
			printf("\r\n ske gcm encrypt 2 error");
			return 1;
		}
	}

	ret = ske_lp_gcm_final(ctx, mac_);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm final 2 error");
		return 1;
	}

	//DECRYPT
	ret = ske_lp_gcm_init(ctx, alg, SKE_CRYPTO_DECRYPT, key_, sp_key_idx, iv_, ivByteLen, aadByteLen, byteLen, macByteLen);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm init 3 error, ret=%lu", ret);
		return 1;
	}

	ret = ske_lp_gcm_aad(ctx, aad_);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm aad 3 error");
		return 1;
	}

	for(i=0;i<byteLen;i+=block_byteLen)
	{
		ret = ske_lp_gcm_update_blocks(ctx, std_cipher_+i, replain_+i, GET_MIN_LEN(block_byteLen, byteLen-i));
		if(SKE_SUCCESS != ret)
		{
			printf("\r\n ske gcm decrypt 3 error");
			return 1;
		}
	}

	ret = ske_lp_gcm_final(ctx, mac_);

    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske final 3 error");
		return 1;
	}

	if(memcmp_(mac_, std_mac_, macByteLen) || memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen))
	{
		printf("\r\n multiple input test failure(one block every time)!!");
		print_buf_U8(std_plain_, byteLen, "std_plain");
		print_buf_U8(std_mac_, macByteLen, "std_mac");
		print_buf_U8(std_cipher_, byteLen, "std_cipher");
		print_buf_U8(cipher_, byteLen, "cipher");
		print_buf_U8(mac_, macByteLen, "mac");
		print_buf_U8(replain_, byteLen, "replain");
		return 1;
	}
	else
	{
		printf("\r\n multiple input test success(one block every time)!!, duration: %lu us", duration);
	}


	/**************** test 3: multiple style(random blocks every time) ******************/
	memset_(cipher_, 0, byteLen);
	memset_(replain_, 0, byteLen);
	memset_(mac_, 0, 16);

	//ENCRYPT
    start = get_systick_micros();

	ret = ske_lp_gcm_init(ctx, alg, SKE_CRYPTO_ENCRYPT, key_, sp_key_idx, iv_, ivByteLen, aadByteLen, byteLen, macByteLen);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm init 5 error");
		return 1;
	}

#ifdef SKE_LP_GCM_CPU_UPDATE_AAD_BY_STEP
	i=0;
	while(i < aadByteLen)
	{
		j = ske_get_rand_number(aadByteLen);
		j = GET_MIN_LEN(j, aadByteLen - i);

		ret = ske_lp_gcm_update_aad(ctx, aad_+i, j);//printf("\r\n %lu", j);
		if(SKE_SUCCESS != ret)
		{
			printf("\r\n ske gcm aad 5 error");
			return 1;
		}
		i+=j;
	}
#else
	ret = ske_lp_gcm_aad(ctx, aad_);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm aad 5 error");
		return 1;
	}
#endif

	i=0;
	while(i < byteLen)
	{
		j = ske_get_rand_number(byteLen/block_byteLen);
		j = j*block_byteLen;
		j = GET_MIN_LEN(j, byteLen-i);

		ret = ske_lp_gcm_update_blocks(ctx, std_plain_+i, cipher_+i, j);
		if(SKE_SUCCESS != ret)
		{
			printf("\r\n ske gcm encrypt 5 error");
			return 1;
		}
		i+=j;
	}

	ret = ske_lp_gcm_final(ctx, mac_);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm final 5 error");
		return 1;
	}

	//DECRYPT
	ret = ske_lp_gcm_init(ctx, alg, SKE_CRYPTO_DECRYPT, key_, sp_key_idx, iv_, ivByteLen, aadByteLen, byteLen, macByteLen);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm init 6 error");
		return 1;
	}

#ifdef SKE_LP_GCM_CPU_UPDATE_AAD_BY_STEP
	i=0;
	while(i < aadByteLen)
	{
		j = ske_get_rand_number(aadByteLen);
		j = GET_MIN_LEN(j, aadByteLen - i);

		ret = ske_lp_gcm_update_aad(ctx, aad_+i, j);//printf("\r\n %lu", j);
		if(SKE_SUCCESS != ret)
		{
			printf("\r\n ske gcm aad 6 error");
			return 1;
		}
		i+=j;
	}
#else
	ret = ske_lp_gcm_aad(ctx, aad_);
	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm aad 6 error");
		return 1;
	}
#endif

	i=0;
	while(i < byteLen)
	{
		j = ske_get_rand_number(byteLen/block_byteLen);
		j = j*block_byteLen;
		j = GET_MIN_LEN(j, byteLen-i);

		ret = ske_lp_gcm_update_blocks(ctx, cipher_+i, replain_+i, j);
		if(SKE_SUCCESS != ret)
		{
			printf("\r\n ske gcm encrypt 6 error");
			return 1;
		}
		i+=j;
	}

	ret = ske_lp_gcm_final(ctx, mac_);

    duration = get_systick_micros() - start;

	if(SKE_SUCCESS != ret)
	{
		printf("\r\n ske gcm final 6 error");
		return 1;
	}

	if(memcmp_(mac_, std_mac_, macByteLen) || memcmp_(cipher_, std_cipher_, byteLen) || memcmp_(replain_, std_plain_, byteLen))
	{
		printf("\r\n multiple input test failure(random blocks every time)!!");
		print_buf_U8(std_plain_, byteLen, "std_plain");
		print_buf_U8(std_mac_, macByteLen, "std_mac");
		print_buf_U8(std_cipher_, byteLen, "std_cipher");
		print_buf_U8(cipher_, byteLen, "cipher");
		print_buf_U8(mac_, macByteLen, "mac");
		print_buf_U8(replain_, byteLen, "replain");
		return 1;
	}
	else
	{
		printf("\r\n multiple input test success(random blocks every time)!!, duration: %lu us", duration);
	}
//*/
    printf("\r\n");

	fflush(stdout);

	return 0;
}


#ifdef SKE_LP_DMA_FUNCTION
uint32_t ske_dma_gcm_test(SKE_ALG alg, uint8_t *std_plain, uint32_t byteLen, uint8_t *key,
		uint16_t sp_key_idx, uint8_t *iv, uint8_t ivByteLen, uint8_t *aad, uint8_t aadByteLen, uint8_t *std_cipher,
		uint8_t *std_mac, uint32_t macByteLen)
{
	uint8_t tmp_buf[16];

	uint32_t *std_aad_buf     = (uint32_t *)(DMA_RAM_BASE);
	uint32_t *std_plain_buf   = std_aad_buf+0x200;
	uint32_t *std_cipher_buf  = std_plain_buf+0x200;
	uint32_t *std_mac_buf     = std_cipher_buf+0x200;

	uint32_t *in  = std_mac_buf+0x200;
	uint32_t *out = in+0x200;

	uint32_t i,j;
	uint32_t ret;

    uint32_t start = 0;
    uint32_t duration = 0;

	char *name[]={"","","","","","AES_128","AES_192","AES_256","SM4"};

	uint32_t block_byteLen;//, block_wordLen;//, dma_block_wordLen=4;
	SKE_GCM_CTX ctx[1];

	printf("\r\n %s GCM DMA test(iv=%d bytes,AAD=%d bytes,P/C=%lu bytes, mac=%lu bytes)",
			name[alg],ivByteLen,aadByteLen,byteLen,macByteLen);fflush(stdout);

	block_byteLen = ske_lp_get_block_byte_len(alg);
//	block_wordLen = block_byteLen/4;

	//set aad
	uint32_copy(std_aad_buf, (uint32_t *)aad, (aadByteLen&(~0x0F)/4));
	if(aadByteLen & 0x0F)
	{
		memcpy_(tmp_buf, aad+(aadByteLen&(~0x0F)), aadByteLen & 0x0F);
		memset_(tmp_buf+(aadByteLen & 0x0F), 0, 16-(aadByteLen & 0x0F));
		uint32_copy(std_aad_buf+(aadByteLen&(~0x0F))/4, (uint32_t *)tmp_buf, 4);
	}

	//set plain
	uint32_copy(std_plain_buf, (uint32_t *)std_plain, (byteLen&(~0x0F))/4);
	if(byteLen & 0x0F)
	{
		memcpy_(tmp_buf, std_plain+(byteLen&(~0x0F)), byteLen & 0x0F);
		memset_(tmp_buf+(byteLen & 0x0F), 0, 16-(byteLen & 0x0F));
		uint32_copy(std_plain_buf+(byteLen&(~0x0F))/4, (uint32_t *)tmp_buf, 4);
	}

	//set cipher
	uint32_copy(std_cipher_buf, (uint32_t *)std_cipher, (byteLen&(~0x0F))/4);
	if(byteLen & 0x0F)
	{
		memcpy_(tmp_buf, std_cipher+(byteLen&(~0x0F)), byteLen & 0x0F);
		memset_(tmp_buf+(byteLen & 0x0F), 0, 16-(byteLen & 0x0F));
		uint32_copy(std_cipher_buf+(byteLen&(~0x0F))/4, (uint32_t *)tmp_buf, 4);
	}

	//set mac
	memcpy_(tmp_buf, std_mac, macByteLen);
	memset_(tmp_buf+macByteLen, 0, 16-macByteLen);
	uint32_copy(std_mac_buf, (uint32_t *)tmp_buf, 4);

	//set input(plaintext)
	uint32_copy(in, (uint32_t *)std_plain_buf, ((byteLen+15)/16)*4);

	//ENCRYPT
    start = get_systick_micros();
#if 1
	if(aadByteLen && (0 == byteLen))
	{
		ret = ske_lp_dma_gcm_crypto(alg, SKE_CRYPTO_ENCRYPT, key, sp_key_idx, iv, ivByteLen, std_aad_buf, aadByteLen,
					in, out, byteLen, macByteLen, ske_call_manage);
	}
	else
	{
		ret = ske_lp_dma_gcm_init(ctx, alg, SKE_CRYPTO_ENCRYPT, key, sp_key_idx, iv, ivByteLen, aadByteLen, byteLen, macByteLen);
		if(SKE_SUCCESS != ret)
		{
			printf("\r\n ske gcm encrypt 1 error, ret=%lu", ret);fflush(stdout);
			return 1;
		}
#if 0      //multiple style(one block every time)
		//input aad
		i=0;
		while(i < aadByteLen)
		{
			j = GET_MIN_LEN(block_byteLen, aadByteLen-i);
			ret = ske_lp_dma_gcm_update_aad_blocks(ctx, std_aad_buf+i/4, j, ske_call_manage);
			if(SKE_SUCCESS != ret)
			{
				printf("\r\n ske gcm encrypt 2 error, ret=%lu", ret);fflush(stdout);
				return 1;
			}
			i+=j;
		}

		//input plaintext/ciphertext
		i=0;
		while(i < byteLen)
		{
			j = GET_MIN_LEN(block_byteLen, byteLen-i);
			ret = ske_lp_dma_gcm_update_blocks(ctx, in+i/4, out+i/4, j, ske_call_manage);
			if(SKE_SUCCESS != ret)
			{
				printf("\r\n ske gcm encrypt 3 error, ret=%lu", ret);fflush(stdout);
				return 1;
			}
			i+=j;
		}
#else                          //multiple style(random blocks every time)
		//input aad
		i=0;
		while(i < aadByteLen)
		{
			j = ske_get_rand_number(aadByteLen/block_byteLen);
			j = j*block_byteLen;
			j = GET_MIN_LEN(j, aadByteLen-i);

			ret = ske_lp_dma_gcm_update_aad_blocks(ctx, std_aad_buf+i/4, j, ske_call_manage);
			if(SKE_SUCCESS != ret)
			{
				printf("\r\n ske gcm encrypt 2 error, ret=%lu", ret);fflush(stdout);
				return 1;
			}
			i+=j;
		}

		//input plaintext/ciphertext
		i=0;
		while(i < byteLen)
		{
			j = ske_get_rand_number(byteLen/block_byteLen);
			j = j*block_byteLen;
			j = GET_MIN_LEN(j, byteLen-i);

			ret = ske_lp_dma_gcm_update_blocks(ctx, in+i/4, out+i/4, j, ske_call_manage);
			if(SKE_SUCCESS != ret)
			{
				printf("\r\n ske gcm encrypt 3 error, ret=%lu", ret);fflush(stdout);
				return 1;
			}
			i+=j;
		}
#endif

		ret = ske_lp_dma_gcm_final(ctx);
	}
#else
	ret = ske_lp_dma_gcm_crypto(alg, SKE_CRYPTO_ENCRYPT, key, sp_key_idx, iv, ivByteLen, std_aad_buf, aadByteLen,
			in, out, byteLen, macByteLen, ske_call_manage);
#endif
	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out, ((byteLen+15)/16)*4, std_cipher_buf, ((byteLen+15)/16)*4) ||
			uint32_BigNumCmp(out+((byteLen+15)/16)*4, 4, std_mac_buf, 4))
	{
		printf("\r\n ske gcm encrypt error, ret=%lu", ret);fflush(stdout);
		print_buf_U8((uint8_t *)in, ((aadByteLen+15)/16)*16+((byteLen+15)/16)*16, "in");
		print_buf_U8((uint8_t *)out, 16+((byteLen+15)/16)*16, "out");
		return 1;
	}


	//DECRYPT
	//set input(ciphertext)
	uint32_copy(in, (uint32_t *)out, ((byteLen+15)/16)*4);

#if 1
	if(aadByteLen && (0 == byteLen))
	{
		ret = ske_lp_dma_gcm_crypto(alg, SKE_CRYPTO_DECRYPT, key, sp_key_idx, iv, ivByteLen, std_aad_buf, aadByteLen,
					in, out, byteLen, macByteLen, ske_call_manage);
	}
	else
	{
		ret = ske_lp_dma_gcm_init(ctx, alg, SKE_CRYPTO_DECRYPT, key, sp_key_idx, iv, ivByteLen, aadByteLen, byteLen, macByteLen);
		if(SKE_SUCCESS != ret)
		{
			printf("\r\n ske gcm decrypt 1 error, ret=%lu", ret);fflush(stdout);
			return 1;
		}

#if 0                          //multiple style(one block every time)
		//input aad
		i=0;
		while(i < aadByteLen)
		{
			j = GET_MIN_LEN(block_byteLen, aadByteLen-i);
			ret = ske_lp_dma_gcm_update_aad_blocks(ctx, std_aad_buf+i/4, j, ske_call_manage);
			if(SKE_SUCCESS != ret)
			{
				printf("\r\n ske gcm decrypt 2 error, ret=%lu", ret);fflush(stdout);
				return 1;
			}
			i+=j;
		}

		//input plaintext/ciphertext
		i=0;
		while(i < byteLen)
		{
			j = GET_MIN_LEN(block_byteLen, byteLen-i);
			ret = ske_lp_dma_gcm_update_blocks(ctx, in+i/4, out+i/4, j, ske_call_manage);
			if(SKE_SUCCESS != ret)
			{
				printf("\r\n ske gcm decrypt 3 error, ret=%lu", ret);fflush(stdout);
				return 1;
			}
			i+=j;
		}
#else                          //multiple style(random blocks every time)
		//input aad
		i=0;
		while(i < aadByteLen)
		{
			j = ske_get_rand_number(aadByteLen/block_byteLen);
			j = j*block_byteLen;
			j = GET_MIN_LEN(j, aadByteLen-i);

			ret = ske_lp_dma_gcm_update_aad_blocks(ctx, std_aad_buf+i/4, j, ske_call_manage);
			if(SKE_SUCCESS != ret)
			{
				printf("\r\n ske gcm decrypt 2 error, ret=%lu", ret);fflush(stdout);
				return 1;
			}
			i+=j;
		}

		//input plaintext/ciphertext
		i=0;
		while(i < byteLen)
		{
			j = ske_get_rand_number(byteLen/block_byteLen);
			j = j*block_byteLen;
			j = GET_MIN_LEN(j, byteLen-i);

			ret = ske_lp_dma_gcm_update_blocks(ctx, in+i/4, out+i/4, j, ske_call_manage);
			if(SKE_SUCCESS != ret)
			{
				printf("\r\n ske gcm decrypt 3 error, ret=%lu", ret);fflush(stdout);
				return 1;
			}
			i+=j;
		}
#endif

		ret = ske_lp_dma_gcm_final(ctx);
	}
#else
	ret = ske_lp_dma_gcm_crypto(alg, SKE_CRYPTO_DECRYPT, key, sp_key_idx, iv, ivByteLen, std_aad_buf, aadByteLen,
			in, out, byteLen, macByteLen, ske_call_manage);
#endif

	if(SKE_SUCCESS != ret || uint32_BigNumCmp(out, ((byteLen+15)/16)*4, std_plain_buf, ((byteLen+15)/16)*4) ||
			uint32_BigNumCmp(out+((byteLen+15)/16)*4, 4, std_mac_buf, 4))
	{
		printf("\r\n ske gcm decrypt error, ret=%lu", ret);fflush(stdout);
		print_buf_U8((uint8_t *)in, ((aadByteLen+15)/16)*16+((byteLen+15)/16)*16, "in");
		print_buf_U8((uint8_t *)out, 16+((byteLen+15)/16)*16, "out");
		return 1;
	}
	/**/

    duration = get_systick_micros() - start;

	printf("\r\n GCM DMA test success, duration: %lu us", duration);

    printf("\r\n");

	return 0;
}
#endif







typedef struct {
	SKE_ALG alg;
	const uint8_t *std_plain;
	uint32_t c_bytes;    //byte length of plaintext or ciphertext
	const uint8_t *key;
	uint16_t keyid;
	const uint8_t *iv;
	uint32_t iv_bytes;
	const uint8_t *aad;
	uint32_t aad_bytes;
	const uint8_t *std_cipher;
	const uint8_t *std_mac;
	uint32_t mac_bytes;
}SKE_GCM_TEST_VECTOR;

uint32_t ske_gcm_test_internal(SKE_GCM_TEST_VECTOR *vector, uint32_t num)
{
	char *name[]={"","","","","","AES_128","AES_192","AES_256","SM4"};
	uint32_t i, ret;
	printf("\r\n\r\n  =================== %s GCM test ==================== ", name[vector[0].alg]);

	for(i=0; i<num; i++)
	{
		ret = ske_gcm_test(vector[i].alg, 1, (uint8_t *)vector[i].std_plain, vector[i].c_bytes, (uint8_t *)vector[i].key, vector[i].keyid,
				(uint8_t *)vector[i].iv, vector[i].iv_bytes, (uint8_t *)vector[i].aad, vector[i].aad_bytes, (uint8_t *)vector[i].std_cipher,
				(uint8_t *)vector[i].std_mac, 16);
		if(ret)
			return 1;

		ret = ske_gcm_test(vector[i].alg, 0, (uint8_t *)vector[i].std_plain, vector[i].c_bytes, (uint8_t *)vector[i].key, vector[i].keyid,
				(uint8_t *)vector[i].iv, vector[i].iv_bytes, (uint8_t *)vector[i].aad, vector[i].aad_bytes, (uint8_t *)vector[i].std_cipher,
				(uint8_t *)vector[i].std_mac, vector[i].mac_bytes);
		if(ret)
			return 1;

#ifdef SKE_LP_DMA_FUNCTION
		ret = ske_dma_gcm_test(vector[i].alg, (uint8_t *)vector[i].std_plain, vector[i].c_bytes, (uint8_t *)vector[i].key, vector[i].keyid, 
				(uint8_t *)vector[i].iv, vector[i].iv_bytes, (uint8_t *)vector[i].aad, vector[i].aad_bytes, (uint8_t *)vector[i].std_cipher, 
				(uint8_t *)vector[i].std_mac, 16);
		if(ret)
			return 1;

		ret = ske_dma_gcm_test(vector[i].alg, (uint8_t *)vector[i].std_plain, vector[i].c_bytes, (uint8_t *)vector[i].key, vector[i].keyid, 
				(uint8_t *)vector[i].iv, vector[i].iv_bytes, (uint8_t *)vector[i].aad, vector[i].aad_bytes, (uint8_t *)vector[i].std_cipher, 
				(uint8_t *)vector[i].std_mac, vector[i].mac_bytes);
		if(ret)
			return 1;
#endif
	}

	return 0;
}


#if  (defined(SUPPORT_SKE_AES_128) || defined(SUPPORT_SKE_AES_192) || defined(SUPPORT_SKE_AES_256) || defined(SUPPORT_SKE_SM4))
const uint8_t std_gcm_plain[256]  =  {
								0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,
								0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,
								0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,
								0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39,0x1a,0xaf,0xd2,0x55,
								0xB4,0xD1,0x4B,0x82,0xE0,0x03,0xCA,0x48,0x4C,0x28,0x1B,0x5D,0x4D,0x9B,0xBC,0x29,
								0xF3,0x61,0xD1,0x61,0x79,0x36,0xF5,0x3E,0x37,0xEF,0x97,0x73,0xB3,0x31,0x8C,0x8C,
								0x4E,0xCB,0x31,0x9E,0x26,0x4D,0xF6,0x29,0xBE,0x8C,0x41,0x1B,0xF5,0xC4,0xBE,0x45,
								0x03,0x62,0x56,0xE4,0xD8,0x2F,0x64,0x5A,0x4D,0x0A,0xDF,0x44,0x55,0xB1,0x31,0xA1,
								0x7B,0xC6,0x74,0x21,0x86,0xC4,0x2E,0x28,0x3A,0xA5,0xBA,0xD5,0x4A,0x18,0xEC,0x14,
								0x3B,0xAF,0x1E,0x6C,0x85,0x7F,0x32,0xEC,0x5D,0x92,0xB1,0x96,0xCF,0x7E,0x31,0x13,
								0x71,0xBD,0xA2,0xEA,0xE8,0xDF,0xD0,0x82,0xCF,0xEB,0x58,0x3A,0x41,0xCF,0xCE,0xAA,
								0x78,0x0F,0xD1,0x7F,0xBA,0xE9,0x31,0xDE,0xF7,0x17,0xB4,0x5B,0xB8,0x6F,0x15,0xD6,
								0x01,0xF5,0x44,0xFB,0xCC,0xB2,0x43,0x5F,0x80,0xE8,0x9D,0x6F,0x21,0x87,0x06,0x37,
								0x86,0x01,0xEA,0x99,0x15,0x6E,0x8A,0x88,0xAA,0xED,0x8C,0xE6,0x14,0x2F,0xB6,0x65,
								0xB6,0xEE,0xEB,0x6F,0x06,0xEA,0x9D,0x45,0xB0,0x14,0x04,0x00,0x59,0xB4,0x26,0x77,
								0x32,0xD7,0x33,0xB2,0xF0,0x92,0xE8,0x5E,0x40,0xF2,0x21,0x04,0xC4,0xF0,0x9C,0x80,};
const uint8_t std_gcm_key[32]= {
								0xfe,0xff,0xe9,0x92,0x86,0x65,0x73,0x1c,0x6d,0x6a,0x8f,0x94,0x67,0x30,0x83,0x08,
								0xfe,0xff,0xe9,0x92,0x86,0x65,0x73,0x1c,0x6d,0x6a,0x8f,0x94,0x67,0x30,0x83,0x08};
const uint8_t std_gcm_iv[12] = {
								0xca,0xfe,0xba,0xbe,0xfa,0xce,0xdb,0xad,0xde,0xca,0xf8,0x88};
const uint8_t std_aad[65]    = {
								0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,
								0xab,0xad,0xda,0xd2,0x7C,0xA4,0x8E,0x82,0x99,0xFC,0x5A,0xD3,0xE9,0x08,0xB7,0x65,
								0x1B,0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,
								0xef,0xab,0xad,0xda,0xd2,0x7C,0xA4,0x8E,0x82,0x99,0xFC,0x5A,0xD3,0xE9,0x08,0xB7,
								0x65,};
#endif

#ifdef SUPPORT_SKE_AES_128
const uint8_t std_aes128_gcm_cipher[256] =  {
								0x42,0x83,0x1E,0xC2,0x21,0x77,0x74,0x24,0x4B,0x72,0x21,0xB7,0x84,0xD0,0xD4,0x9C,
								0xE3,0xAA,0x21,0x2F,0x2C,0x02,0xA4,0xE0,0x35,0xC1,0x7E,0x23,0x29,0xAC,0xA1,0x2E,
								0x21,0xD5,0x14,0xB2,0x54,0x66,0x93,0x1C,0x7D,0x8F,0x6A,0x5A,0xAC,0x84,0xAA,0x05,
								0x1B,0xA3,0x0B,0x39,0x6A,0x0A,0xAC,0x97,0x3D,0x58,0xE0,0x91,0x47,0x3F,0x59,0x85,
								0x69,0x79,0x2C,0x46,0x2E,0xF1,0x7B,0xB9,0xF4,0x81,0xE4,0x14,0x87,0xBB,0x37,0x48,
								0xE5,0xB9,0x25,0x90,0xBA,0xFF,0xD2,0x01,0x14,0x38,0xCF,0x6F,0x70,0x42,0x68,0xED,
								0xBE,0xD5,0x6D,0x21,0x83,0x62,0xB6,0xDB,0xEE,0x80,0x46,0xDF,0xEA,0xF3,0xCF,0x34,
								0xC2,0xDF,0xA2,0x51,0xB8,0x49,0xE7,0x2A,0xC9,0x80,0x75,0x72,0x53,0xAB,0xA6,0xF9,
								0x85,0x10,0x89,0x90,0x6E,0xFF,0x8A,0x37,0x19,0xDC,0x8C,0x7E,0x0C,0x78,0xC9,0xD4,
								0xFB,0x19,0xC2,0xEA,0xA7,0x3A,0xBA,0xD6,0xCF,0x41,0x49,0x42,0xF4,0x47,0x97,0x38,
								0x03,0xD0,0xE4,0xFC,0x45,0x76,0x34,0x33,0xCE,0xAC,0xC6,0xBB,0x75,0xCD,0xE8,0x15,
								0xF9,0xB3,0xAA,0xBE,0x1F,0x20,0x06,0xF7,0x84,0xFB,0x0A,0xD9,0x22,0x90,0x42,0xF6,
								0xA5,0x46,0x40,0x05,0x56,0x23,0xEA,0xF1,0x2F,0x2C,0x59,0xCE,0x8E,0xD9,0xA8,0x85,
								0xA8,0x93,0x54,0xBA,0x6F,0x1D,0x39,0x9F,0xE1,0x0F,0x69,0xDE,0x94,0xB6,0x13,0x5F,
								0x06,0x73,0x95,0x9E,0x8F,0xFC,0x47,0xE3,0x47,0x95,0x79,0x33,0x1C,0xF7,0x0C,0xE4,
								0x83,0x47,0x09,0x6B,0x67,0xF5,0x1E,0x4E,0x86,0x63,0x31,0x2E,0xCE,0xD5,0x38,0xEC,};
#endif

#ifdef SUPPORT_SKE_AES_192
const uint8_t std_aes192_gcm_cipher[256] =  {
								0x39,0x80,0xCA,0x0B,0x3C,0x00,0xE8,0x41,0xEB,0x06,0xFA,0xC4,0x87,0x2A,0x27,0x57,
								0x85,0x9E,0x1C,0xEA,0xA6,0xEF,0xD9,0x84,0x62,0x85,0x93,0xB4,0x0C,0xA1,0xE1,0x9C,
								0x7D,0x77,0x3D,0x00,0xC1,0x44,0xC5,0x25,0xAC,0x61,0x9D,0x18,0xC8,0x4A,0x3F,0x47,
								0x18,0xE2,0x44,0x8B,0x2F,0xE3,0x24,0xD9,0xCC,0xDA,0x27,0x10,0xAC,0xAD,0xE2,0x56,
								0x4E,0xEF,0x84,0xD7,0x8C,0x6B,0x94,0xD0,0x0A,0x1B,0xD2,0xA1,0xDB,0xB0,0xF1,0x5F,
								0x79,0xCF,0xE8,0x1D,0xD4,0x84,0x4E,0x34,0x5B,0x09,0xA5,0x34,0x1D,0x5C,0x2B,0xB1,
								0xF1,0xC2,0xF6,0xD9,0xBF,0x11,0x12,0xDF,0xCA,0x93,0xC3,0x2D,0x28,0x90,0xCB,0x8A,
								0xF5,0x93,0x61,0xE5,0x36,0x9A,0xB9,0xDA,0x39,0xC8,0xBC,0xA3,0x9A,0x71,0x30,0x37,
								0xAF,0xA3,0x30,0x5C,0x5B,0x0A,0x9D,0x80,0xAF,0x0D,0x99,0x1F,0x0F,0xB8,0x6A,0x21,
								0x85,0x4A,0x8E,0x78,0x08,0x04,0x32,0x2B,0xA3,0xEA,0xB9,0x22,0x8C,0xFE,0x70,0x21,
								0x9C,0x2E,0x08,0x48,0x6A,0xB5,0x9F,0x9D,0xE4,0xC8,0x87,0x55,0xD7,0xFD,0x85,0x23,
								0xDF,0x11,0xDA,0xCB,0x80,0xD4,0xE7,0x88,0x74,0x07,0x17,0x15,0x86,0x09,0x28,0xF2,
								0x14,0x17,0xFD,0x60,0xF3,0x03,0x88,0xE3,0x31,0x75,0xC7,0x9D,0x73,0xD9,0xEE,0x56,
								0x09,0x6F,0xE1,0xF8,0x13,0x14,0x51,0x6F,0x20,0xA4,0x6F,0x7D,0x19,0x3D,0xF9,0x24,
								0xF8,0x5C,0x97,0xE9,0xC5,0x1F,0x50,0xD5,0x6B,0x8B,0x82,0x0F,0x96,0xE1,0x2C,0x7E,
								0x78,0x14,0xA3,0x84,0x8D,0x81,0xDA,0x1C,0x1C,0xB5,0x55,0x29,0x15,0x6E,0x3E,0x8E};
#endif

#ifdef SUPPORT_SKE_AES_256
const uint8_t std_aes256_gcm_cipher[256] =  {
								0x52,0x2D,0xC1,0xF0,0x99,0x56,0x7D,0x07,0xF4,0x7F,0x37,0xA3,0x2A,0x84,0x42,0x7D,
								0x64,0x3A,0x8C,0xDC,0xBF,0xE5,0xC0,0xC9,0x75,0x98,0xA2,0xBD,0x25,0x55,0xD1,0xAA,
								0x8C,0xB0,0x8E,0x48,0x59,0x0D,0xBB,0x3D,0xA7,0xB0,0x8B,0x10,0x56,0x82,0x88,0x38,
								0xC5,0xF6,0x1E,0x63,0x93,0xBA,0x7A,0x0A,0xBC,0xC9,0xF6,0x62,0x89,0x80,0x15,0xAD,
								0xD0,0x7E,0x30,0xD4,0x00,0xEE,0xB7,0x02,0x04,0xBD,0x95,0x40,0xBB,0x63,0x5C,0xC6,
								0x2F,0xFF,0x3F,0xD5,0x92,0x20,0x5C,0x37,0x6C,0x98,0x8A,0xA5,0xEB,0xF5,0x95,0x79,
								0x29,0x30,0xA5,0x16,0x3C,0x39,0x65,0x5A,0xEB,0xD3,0x9C,0x66,0x85,0xF3,0x73,0xE8,
								0x83,0xEC,0x3F,0x5B,0xB6,0xE4,0x60,0x95,0xE3,0x39,0xF4,0xEB,0x40,0x38,0xD5,0xF2,
								0xC7,0x5F,0x45,0xC0,0x62,0x20,0x03,0x0B,0xB0,0x4B,0x75,0x6B,0x45,0x30,0xA0,0x4B,
								0x71,0xFE,0xD7,0x0E,0x6A,0xAB,0xC8,0xD9,0x0A,0x84,0xC1,0x37,0xF6,0x86,0xBF,0x6A,
								0x8D,0x4C,0xD9,0x7E,0x70,0xD9,0x4B,0xB5,0x9E,0xFE,0xFB,0x4A,0x87,0x33,0xB3,0x21,
								0x35,0x50,0xC8,0x2D,0x14,0xB3,0x4C,0xCF,0x07,0xFB,0xA9,0xFE,0xC4,0x92,0xD2,0x04,
								0xD9,0xE9,0x61,0xEF,0x6A,0xB5,0x4F,0xFD,0x2D,0x9A,0x16,0xDF,0xC7,0x06,0xEC,0x72,
								0x11,0xCF,0x32,0x74,0x4D,0x6D,0xAC,0x7F,0xE0,0x43,0x31,0x50,0xDA,0x5C,0xCC,0xFF,
								0x03,0x10,0xFE,0x8B,0xA5,0x2C,0xD4,0xBC,0x85,0xF9,0x78,0xC9,0xA7,0x58,0x7C,0x26,
								0xD5,0x3B,0x08,0xCC,0xEE,0x10,0x75,0xD0,0xC0,0x9E,0xF4,0xFB,0x80,0x45,0xA8,0xCD};
#endif

#ifdef SUPPORT_SKE_SM4
const uint8_t std_sm4_gcm_cipher[256] =  {
								0xE4,0x11,0x0F,0xF1,0xC1,0x41,0x97,0xE6,0x76,0x21,0x6A,0x33,0x83,0x10,0x41,0xEB,
								0x09,0x58,0x00,0x11,0x7B,0xDC,0x3F,0x75,0x1A,0x49,0x6E,0xFC,0xF2,0xBB,0xDF,0xDB,
								0x3A,0x2E,0x13,0xFD,0xC5,0xC1,0x9D,0x07,0x1A,0xE5,0x48,0x3F,0xED,0xDE,0x98,0x5D,
								0x3F,0x2D,0x5B,0x4E,0xEE,0x0B,0xB6,0xDF,0xE3,0x63,0x36,0x83,0x23,0xF7,0x5B,0x80,
								0xFF,0xCB,0x6C,0x23,0xB1,0x4A,0x95,0xE2,0xA8,0xDA,0xD6,0xF6,0x9F,0xFA,0x2B,0xEF,
								0x2C,0x0A,0xB9,0x51,0xE5,0x47,0x65,0xC1,0x0D,0xD0,0xC1,0xD2,0xFD,0xD6,0x0C,0xFB,
								0xAF,0x2C,0xB9,0xA9,0x34,0x4F,0x80,0xE8,0xB6,0xCB,0x4D,0x56,0x1F,0x0B,0x3A,0x9B,
								0x68,0xF9,0x20,0x0E,0xB6,0xE3,0x83,0x46,0x34,0xD9,0xC8,0x96,0x91,0x80,0xD8,0x61,
								0x14,0xAB,0x39,0xDF,0x52,0x49,0x4B,0xF6,0x41,0x13,0xAD,0x78,0x42,0x7E,0x67,0x72,
								0x6D,0x41,0xD6,0xA4,0x75,0xA5,0x54,0xED,0x40,0x74,0x47,0x8A,0x53,0xCB,0xA7,0x6D,
								0xF7,0xCA,0x07,0x49,0x20,0x39,0x54,0xF9,0x3F,0xBF,0xDB,0x87,0x4A,0x01,0xA1,0xA1,
								0x0E,0xF3,0xAA,0xEC,0x3E,0x9E,0x95,0x24,0xC8,0x08,0x89,0xB5,0x8A,0xA1,0x0D,0x81,
								0xA2,0x3A,0xC6,0x5A,0xBE,0x70,0x5A,0x17,0xF7,0xCA,0x28,0xAE,0x8C,0xEA,0xA3,0x51,
								0x49,0x35,0x4A,0xBA,0x70,0x48,0xA7,0x5C,0x5C,0xDE,0x86,0x6E,0x28,0x94,0x9C,0x1A,
								0xDD,0xBE,0x1B,0x42,0x39,0x7A,0x2A,0x6A,0x95,0xCA,0x89,0xC4,0x12,0xB0,0x71,0xEF,
								0xB3,0x0B,0x41,0x64,0x43,0xEC,0xF2,0xDD,0x85,0x87,0x13,0x45,0xB1,0x54,0x18,0x84};
#endif



#ifdef SUPPORT_SKE_AES_128
const uint8_t std_aes128_gcm_mac_aad0_p256[]  = {0x97,0x5A,0x7B,0x3E,0x2E,0x76,0x19,0x59,0x4E,0xFB,0x4A,0x12,0xB3,0x88,0xB3,0xD0};
const uint8_t std_aes128_gcm_mac_aad3_p201[]  = {0xF0,0x0A,0x05,0xCF,0xD8,0x11,0x2B,0x6C,0x08,0x4B,0xAA,0xAC,0x06,0xEB,0xDB,0xAF};
const uint8_t std_aes128_gcm_mac_aad16_p120[] = {0x97,0x79,0x9F,0xA3,0xFC,0x35,0x41,0x33,0x41,0xA6,0x09,0xBC,0xCF,0x42,0x89,0xAF};
const uint8_t std_aes128_gcm_mac_aad17_p65[]  = {0xD9,0x89,0xF7,0xFF,0xD8,0xED,0xD4,0x99,0x4B,0x1D,0x1D,0x54,0x00,0x7F,0x3F,0x7B};
const uint8_t std_aes128_gcm_mac_aad20_p32[]  = {0xE1,0x3E,0x14,0x34,0x28,0x5A,0x94,0x26,0xAD,0xDF,0xBF,0xC2,0x70,0xD2,0x7F,0x16};
const uint8_t std_aes128_gcm_mac_aad32_p15[]  = {0x09,0x24,0xCA,0x52,0xC7,0x81,0x92,0x2E,0xC5,0x3B,0x9F,0x55,0x8F,0xDB,0x6C,0x80};
const uint8_t std_aes128_gcm_mac_aad33_p0[]   = {0x3C,0xBA,0x19,0x87,0x0D,0xFD,0x4D,0xDD,0x35,0x0F,0x6D,0xFB,0xF1,0x90,0xD7,0x4E};
const uint8_t std_aes128_gcm_mac_aad65_p256[] = {0x91,0x3E,0x19,0x46,0x86,0x50,0x00,0x5E,0xD8,0x8B,0xA9,0xC8,0xF5,0xA1,0xC8,0xF4};

uint32_t aes_128_gcm_test()
{
	SKE_GCM_TEST_VECTOR vector[8] = {
		{SKE_ALG_AES_128, std_gcm_plain, 256, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 0,  std_aes128_gcm_cipher, std_aes128_gcm_mac_aad0_p256,  16},
		{SKE_ALG_AES_128, std_gcm_plain, 201, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 3,  std_aes128_gcm_cipher, std_aes128_gcm_mac_aad3_p201,  13},
		{SKE_ALG_AES_128, std_gcm_plain, 120, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 16, std_aes128_gcm_cipher, std_aes128_gcm_mac_aad16_p120, 10},
		{SKE_ALG_AES_128, std_gcm_plain, 65,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 17, std_aes128_gcm_cipher, std_aes128_gcm_mac_aad17_p65,  9},
		{SKE_ALG_AES_128, std_gcm_plain, 32,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 20, std_aes128_gcm_cipher, std_aes128_gcm_mac_aad20_p32,  7},
		{SKE_ALG_AES_128, std_gcm_plain, 15,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 32, std_aes128_gcm_cipher, std_aes128_gcm_mac_aad32_p15,  4},
		{SKE_ALG_AES_128, std_gcm_plain, 0,   std_gcm_key, 0, std_gcm_iv, 12, std_aad, 33, std_aes128_gcm_cipher, std_aes128_gcm_mac_aad33_p0,   1},
		{SKE_ALG_AES_128, std_gcm_plain, 256, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 65, std_aes128_gcm_cipher, std_aes128_gcm_mac_aad65_p256, 16},
	};

	return ske_gcm_test_internal(vector, 8);
}
#endif

#ifdef SUPPORT_SKE_AES_192
const uint8_t std_aes192_gcm_mac_aad0_p256[]  = {0x36,0x21,0x7A,0xB6,0x75,0x39,0x55,0x13,0x44,0x16,0x28,0xB8,0xCB,0x94,0x45,0x16};
const uint8_t std_aes192_gcm_mac_aad3_p201[]  = {0x16,0x19,0x79,0x41,0xF7,0x31,0x5D,0x4E,0x42,0x64,0xA5,0xEE,0x45,0x52,0x60,0xB2};
const uint8_t std_aes192_gcm_mac_aad16_p120[] = {0x7F,0x6C,0x15,0xD0,0x46,0x5E,0xF5,0xC4,0x75,0x06,0xE6,0x7F,0x68,0xEC,0xA6,0xA8};
const uint8_t std_aes192_gcm_mac_aad17_p65[]  = {0x3F,0x55,0x20,0xDA,0x76,0x8B,0x45,0x99,0xF9,0x45,0xED,0xF8,0xC4,0x2D,0x37,0x75};
const uint8_t std_aes192_gcm_mac_aad20_p32[]  = {0x9C,0x95,0x3E,0x3F,0xDE,0xB9,0xDF,0x33,0xE4,0x8E,0xA6,0xC9,0xCC,0x3C,0x0C,0x8E};
const uint8_t std_aes192_gcm_mac_aad32_p15[]  = {0xAD,0xDC,0xEC,0xF8,0x05,0x6C,0x1B,0xEE,0xB3,0x87,0x2F,0xFE,0xBD,0x74,0x22,0x23};
const uint8_t std_aes192_gcm_mac_aad33_p0[]   = {0xCD,0x15,0xAB,0xBC,0xBC,0x4A,0xDA,0x30,0xB7,0x36,0x03,0xAC,0xD7,0x0F,0x65,0xB2};
const uint8_t std_aes192_gcm_mac_aad65_p256[] = {0x8B,0x6A,0x44,0xC6,0x88,0x64,0x8C,0xFE,0xF7,0xB2,0x53,0x69,0xB8,0x0C,0x66,0x97};

uint32_t aes_192_gcm_test()
{
	SKE_GCM_TEST_VECTOR vector[8] = {
		{SKE_ALG_AES_192, std_gcm_plain, 256, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 0,  std_aes192_gcm_cipher, std_aes192_gcm_mac_aad0_p256,  16},
		{SKE_ALG_AES_192, std_gcm_plain, 201, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 3,  std_aes192_gcm_cipher, std_aes192_gcm_mac_aad3_p201,  13},
		{SKE_ALG_AES_192, std_gcm_plain, 120, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 16, std_aes192_gcm_cipher, std_aes192_gcm_mac_aad16_p120, 10},
		{SKE_ALG_AES_192, std_gcm_plain, 65,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 17, std_aes192_gcm_cipher, std_aes192_gcm_mac_aad17_p65,  9},
		{SKE_ALG_AES_192, std_gcm_plain, 32,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 20, std_aes192_gcm_cipher, std_aes192_gcm_mac_aad20_p32,  7},
		{SKE_ALG_AES_192, std_gcm_plain, 15,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 32, std_aes192_gcm_cipher, std_aes192_gcm_mac_aad32_p15,  4},
		{SKE_ALG_AES_192, std_gcm_plain, 0,   std_gcm_key, 0, std_gcm_iv, 12, std_aad, 33, std_aes192_gcm_cipher, std_aes192_gcm_mac_aad33_p0,   1},
		{SKE_ALG_AES_192, std_gcm_plain, 256, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 65, std_aes192_gcm_cipher, std_aes192_gcm_mac_aad65_p256, 16},
	};

	return ske_gcm_test_internal(vector, 8);
}
#endif


#ifdef SUPPORT_SKE_AES_256
const uint8_t std_aes256_gcm_mac_aad0_p256[]  = {0xA0,0x6D,0x50,0x80,0xEA,0xA8,0x51,0x7B,0x5F,0x4C,0xBC,0x2B,0x6A,0x2A,0x19,0x25};
const uint8_t std_aes256_gcm_mac_aad3_p201[]  = {0x19,0xE1,0x84,0x49,0xF5,0x71,0x9F,0xB4,0x90,0x28,0x86,0x17,0x20,0xD9,0x0F,0xAD};
const uint8_t std_aes256_gcm_mac_aad16_p120[] = {0xAC,0x9B,0x6E,0x77,0x01,0xBE,0xBA,0x2D,0x5D,0x9B,0xC2,0x91,0xF0,0x83,0x49,0xAF};
const uint8_t std_aes256_gcm_mac_aad17_p65[]  = {0xBC,0x52,0x87,0x18,0x08,0x72,0xCF,0x53,0x08,0x9E,0xB3,0x48,0x66,0x41,0xB9,0xFA};
const uint8_t std_aes256_gcm_mac_aad20_p32[]  = {0xCF,0x9B,0xFF,0xA9,0xBD,0x33,0x4D,0x82,0x40,0xC8,0x68,0x34,0x2B,0x36,0xB5,0x06};
const uint8_t std_aes256_gcm_mac_aad32_p15[]  = {0x8A,0x86,0xAA,0x09,0xB5,0x10,0x91,0x76,0xEC,0x4B,0x6D,0xE7,0x69,0x6D,0x5B,0x89};
const uint8_t std_aes256_gcm_mac_aad33_p0[]   = {0x53,0x1B,0x3B,0x5F,0xC4,0xED,0x0F,0x01,0xDD,0x67,0x8C,0x38,0x4F,0x32,0xCE,0x87};
const uint8_t std_aes256_gcm_mac_aad65_p256[] = {0xFC,0xB0,0x91,0xC1,0xC8,0x68,0xC2,0x49,0xFE,0x54,0x35,0x90,0x8F,0xFB,0xBB,0xA3};

uint32_t aes_256_gcm_test()
{
	SKE_GCM_TEST_VECTOR vector[8] = {
		{SKE_ALG_AES_256, std_gcm_plain, 256, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 0,  std_aes256_gcm_cipher, std_aes256_gcm_mac_aad0_p256,  16},
		{SKE_ALG_AES_256, std_gcm_plain, 201, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 3,  std_aes256_gcm_cipher, std_aes256_gcm_mac_aad3_p201,  13},
		{SKE_ALG_AES_256, std_gcm_plain, 120, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 16, std_aes256_gcm_cipher, std_aes256_gcm_mac_aad16_p120, 10},
		{SKE_ALG_AES_256, std_gcm_plain, 65,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 17, std_aes256_gcm_cipher, std_aes256_gcm_mac_aad17_p65,  9},
		{SKE_ALG_AES_256, std_gcm_plain, 32,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 20, std_aes256_gcm_cipher, std_aes256_gcm_mac_aad20_p32,  7},
		{SKE_ALG_AES_256, std_gcm_plain, 15,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 32, std_aes256_gcm_cipher, std_aes256_gcm_mac_aad32_p15,  4},
		{SKE_ALG_AES_256, std_gcm_plain, 0,   std_gcm_key, 0, std_gcm_iv, 12, std_aad, 33, std_aes256_gcm_cipher, std_aes256_gcm_mac_aad33_p0,   1},
		{SKE_ALG_AES_256, std_gcm_plain, 256, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 65, std_aes256_gcm_cipher, std_aes256_gcm_mac_aad65_p256, 16},
	};

	return ske_gcm_test_internal(vector, 8);
}
#endif


#ifdef SUPPORT_SKE_SM4
const uint8_t std_sm4_gcm_mac_aad0_p256[]  = {0x87,0x60,0x91,0xAC,0x80,0x6C,0x53,0x62,0x04,0x64,0x16,0x62,0xDD,0xC2,0x17,0xDE};
const uint8_t std_sm4_gcm_mac_aad3_p201[]  = {0x0B,0xA4,0xC7,0xA8,0x89,0xB4,0xF9,0xCC,0x9B,0x54,0x76,0x35,0x22,0x78,0xCE,0x4F};
const uint8_t std_sm4_gcm_mac_aad16_p120[] = {0xFC,0xA6,0xC2,0x34,0xF7,0xFE,0x8A,0x73,0xF1,0x96,0x93,0xB2,0x42,0x3A,0x44,0x56};
const uint8_t std_sm4_gcm_mac_aad17_p65[]  = {0xC1,0xC7,0xC5,0x2B,0xB7,0x1A,0x2A,0xF9,0x68,0x24,0x3C,0x3C,0xDB,0x10,0x6B,0x21};
const uint8_t std_sm4_gcm_mac_aad20_p32[]  = {0x3E,0x1F,0x43,0xCD,0xE8,0x00,0xA9,0xBE,0x5A,0xA5,0xA1,0x08,0x2C,0xF7,0x74,0x46};
const uint8_t std_sm4_gcm_mac_aad32_p15[]  = {0x3E,0xCE,0x23,0x5C,0x9F,0xE4,0x3F,0x6C,0x46,0xC2,0xC9,0xFF,0x8F,0x94,0x7E,0xBA};
const uint8_t std_sm4_gcm_mac_aad33_p0[]   = {0xC8,0xEB,0x62,0xC2,0xAE,0x2C,0x9F,0x9C,0x9D,0x87,0x0C,0x4C,0x14,0x89,0xF7,0xE9};
const uint8_t std_sm4_gcm_mac_aad65_p256[] = {0x85,0x9E,0x62,0xC7,0x9B,0x6D,0x8A,0xF4,0xED,0x5E,0x11,0xF5,0x1A,0x52,0xAE,0xDC};

uint32_t sm4_gcm_test()
{
	SKE_GCM_TEST_VECTOR vector[8] = {
		{SKE_ALG_SM4, std_gcm_plain, 256, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 0,  std_sm4_gcm_cipher, std_sm4_gcm_mac_aad0_p256,  16},
		{SKE_ALG_SM4, std_gcm_plain, 201, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 3,  std_sm4_gcm_cipher, std_sm4_gcm_mac_aad3_p201,  13},
		{SKE_ALG_SM4, std_gcm_plain, 120, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 16, std_sm4_gcm_cipher, std_sm4_gcm_mac_aad16_p120, 10},
		{SKE_ALG_SM4, std_gcm_plain, 65,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 17, std_sm4_gcm_cipher, std_sm4_gcm_mac_aad17_p65,  9},
		{SKE_ALG_SM4, std_gcm_plain, 32,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 20, std_sm4_gcm_cipher, std_sm4_gcm_mac_aad20_p32,  7},
		{SKE_ALG_SM4, std_gcm_plain, 15,  std_gcm_key, 0, std_gcm_iv, 12, std_aad, 32, std_sm4_gcm_cipher, std_sm4_gcm_mac_aad32_p15,  4},
		{SKE_ALG_SM4, std_gcm_plain, 0,   std_gcm_key, 0, std_gcm_iv, 12, std_aad, 33, std_sm4_gcm_cipher, std_sm4_gcm_mac_aad33_p0,   1},
		{SKE_ALG_SM4, std_gcm_plain, 256, std_gcm_key, 0, std_gcm_iv, 12, std_aad, 65, std_sm4_gcm_cipher, std_sm4_gcm_mac_aad65_p256, 16},
	};

	return ske_gcm_test_internal(vector, 8);
}
#endif


//*
uint32_t ske_gcm_speed_test()
{
	uint8_t in[4096];
	uint8_t key[32];
	uint8_t aad[100];
	uint8_t iv[16];
	uint8_t mac[16];
	uint32_t iv_bytes = 12;
	uint32_t aad_bytes = 100;
	uint32_t c_bytes = 4096;
	uint32_t mac_bytes = 15;
	uint32_t i;
	uint32_t ret;

	printf("\r\n SKE GCM SPEED TEST: 10000 * 4KB blocks - begin ...");//fflush(stdout);

  uint32_t start = get_systick_milis();

	for(i=0;i<10000;i++)
	{
		ret = ske_lp_gcm_crypto(SKE_ALG_AES_128, SKE_CRYPTO_ENCRYPT, key, 0, iv,
				iv_bytes, aad, aad_bytes, in, in, c_bytes, mac, mac_bytes);
		if(SKE_SUCCESS != ret)
		{
			printf("\r\n gcm crypto error ret=%lu", ret); fflush(stdout);
			return 1;
		}
	}

  uint32_t duration = get_systick_milis() - start;

	printf("\r\n finished - duration: %lu ms", duration);//fflush(stdout);

	return 0;
}

#ifdef SKE_LP_DMA_FUNCTION
uint32_t ske_dma_gcm_speed_test()
{
	uint32_t *aad = (uint32_t *)DMA_RAM_BASE;
	uint32_t *in = (uint32_t *)(DMA_RAM_BASE+128);

	uint8_t key[32];
//	uint8_t aad[100];
	uint8_t iv[16];
//	uint8_t mac[16];
//	uint8_t M = 8;
	uint32_t iv_bytes = 12;
	uint32_t aad_bytes = 100;
	uint32_t c_bytes = 4096;
	uint32_t mac_bytes = 15;
	uint32_t i;
	uint32_t ret;

	printf("\r\n SKE GCM DMA SPEED TEST: 10000 * 4KB blocks - begin ...");//fflush(stdout);

  uint32_t start = get_systick_milis();

	for(i=0;i<10000;i++)
	{
		ret = ske_lp_dma_gcm_crypto(SKE_ALG_SM4, SKE_CRYPTO_ENCRYPT, key, 0, iv,
				iv_bytes, aad, aad_bytes, in, in, c_bytes, mac_bytes, ske_call_manage);
		if(SKE_SUCCESS != ret)
		{
			printf("\r\n dma gcm crypto error ret=%lu", ret); fflush(stdout);
			return 1;
		}
	}

  uint32_t duration = get_systick_milis() - start;

	printf("\r\n finished - duration: %lu ms", duration);fflush(stdout);

	return 0;
}
#endif
//*/


uint32_t SKE_LP_GCM_all_test()
{
	uint32_t ret;

#if 0
	if(SKE_SUCCESS != ske_gcm_speed_test())
		return 1;
#endif

#ifdef SKE_LP_DMA_FUNCTION
#if 0
	if(SKE_SUCCESS != ske_dma_gcm_speed_test())
		return 1;
#endif
#endif

/**/
#ifdef SUPPORT_SKE_AES_128
	ret = aes_128_gcm_test();
	if(ret)
		return 1;
#endif

#ifdef SUPPORT_SKE_AES_192
	ret = aes_192_gcm_test();
	if(ret)
		return 1;
#endif

#ifdef SUPPORT_SKE_AES_256
	ret = aes_256_gcm_test();
	if(ret)
		return 1;
#endif

#ifdef SUPPORT_SKE_SM4
	ret = sm4_gcm_test();
	if(ret)
		return 1;
#endif
//*/

	return 0;
}


#endif

