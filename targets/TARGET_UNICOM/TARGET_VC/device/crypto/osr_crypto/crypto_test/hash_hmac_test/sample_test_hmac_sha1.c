#include <stdio.h>
#include "../../crypto_include/hash_hmac/hmac_sha1.h"
#include "../../crypto_include/utility.h"



void hash_call_manage(void);




#ifdef SUPPORT_HASH_SHA1

uint32_t sample_test_hmac_sha1(void)
{
	uint8_t msg[80] = {
		0xCB,0xAC,0x28,0x1C,0xAC,0xD3,0x03,0x5F,0x81,0x5A,0x0E,0x82,0xF0,0xA5,0xEA,0x7A,
		0xC5,0x3C,0x4F,0xF7,0x0B,0xB7,0x9F,0xA6,0x1E,0x80,0xEA,0xF6,0xE6,0x03,0x0F,0x7F,
		0xF8,0x3E,0xF7,0x36,0x0F,0xC4,0x10,0xB0,0x1E,0xDC,0x20,0xD1,0xA1,0xB2,0xBD,0xAF,
		0xBE,0xC0,0x21,0xB4,0xF3,0x68,0xE3,0x06,0x91,0x34,0xE0,0x12,0xC2,0xB4,0x30,0x70,
		0x83,0xD3,0xA9,0xBD,0xD2,0x06,0xE2,0x4E,0x5F,0x0D,0x86,0xE1,0x3D,0x66,0x36,0x65,
	};
	uint8_t key[16] = {
		0x92,0x8C,0x8A,0xBE,0xCB,0xCB,0x38,0x5B,0x8E,0xEA,0xA0,0x05,0x9A,0xC8,0x05,0x84,
	};
	uint8_t std_mac[20] = {
		0x06,0x10,0x3A,0xED,0x2A,0x69,0x71,0xF6,0x8F,0x1A,0x83,0xAC,0x5F,0x0D,0x01,0xA0,
		0xCF,0xFE,0x16,0xCD
	};
	uint8_t mac[20];
	uint8_t msg_byte_len = 80;
	uint8_t key_byte_len = 16;
	uint8_t mac_byte_len = 20;  //digest_byte_len

	uint32_t ret;

	HMAC_SHA1_CTX hmac_sha1_ctx[1];
	HMAC_CTX *hmac_ctx = hmac_sha1_ctx;

#ifdef HASH_DMA_FUNCTION
	uint8_t block_byte_len = 64;
	uint32_t *msg_buf = (uint32_t *)(DMA_RAM_BASE);
	uint32_t *mac_buf = msg_buf+512;
	uint32_t msg_words = (msg_byte_len - (msg_byte_len%block_byte_len))/4;
	uint32_t remainder_bytes = msg_byte_len - msg_words*4;
	HMAC_SHA1_DMA_CTX hmac_sha1_dma_ctx[1];
	HMAC_DMA_CTX *hmac_dma_ctx = hmac_sha1_dma_ctx;

	uint32_copy(msg_buf, (uint32_t *)msg, (msg_byte_len+3)/4);
#endif

	printf("\r\n\r\n -------------- HMAC-SHA1 sample test -------------- ");

	//the following 4 calculations are equivalent

	/**************** test 1 ****************/
	memset_(mac, 0, mac_byte_len);
	ret = hmac_sha1_init(hmac_sha1_ctx, key, 0, key_byte_len);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_sha1_update(hmac_sha1_ctx, msg, 4);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_sha1_update(hmac_sha1_ctx, msg+4, 44);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_sha1_update(hmac_sha1_ctx, msg+48, 32);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_sha1_final(hmac_sha1_ctx, mac);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_mac, mac, mac_byte_len))
	{
		printf("\r\n HMAC-SHA1 sample test 1 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n HMAC-SHA1 sample test 1 success");fflush(stdout);
	}


	/**************** test 2 ****************/
	memset_(mac, 0, mac_byte_len);
	ret = hmac_sha1(key, 0, key_byte_len, msg, msg_byte_len, mac);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_mac, mac, mac_byte_len))
	{
		printf("\r\n HMAC-SHA1 sample test 2 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n HMAC-SHA1 sample test 2 success");fflush(stdout);
	}

	/**************** test 3 ****************/
	memset_(mac, 0, mac_byte_len);
	ret = hmac_init(hmac_ctx, HASH_SHA1, key, 0, key_byte_len);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_update(hmac_sha1_ctx, msg, 4);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_update(hmac_sha1_ctx, msg+4, 44);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_update(hmac_sha1_ctx, msg+48, 32);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_final(hmac_sha1_ctx, mac);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_mac, mac, mac_byte_len))
	{
		printf("\r\n HMAC-SHA1 sample test 3 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n HMAC-SHA1 sample test 3 success");fflush(stdout);
	}


	/**************** test 4 ****************/
	memset_(mac, 0, mac_byte_len);
	ret = hmac(HASH_SHA1, key, 0, key_byte_len, msg, msg_byte_len, mac);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_mac, mac, mac_byte_len))
	{
		printf("\r\n HMAC-SHA1 sample test 4 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n HMAC-SHA1 sample test 4 success");fflush(stdout);
	}


#ifdef HASH_DMA_FUNCTION
	//the following 4 DMA calculations are equivalent

	/**************** dma test 1 ****************/
	uint32_clear(mac_buf, mac_byte_len/4);
	ret = hmac_sha1_dma_init(hmac_sha1_dma_ctx, key, 0, key_byte_len, hash_call_manage);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_sha1_dma_update_blocks(hmac_sha1_dma_ctx, msg_buf, msg_words);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_sha1_dma_final(hmac_sha1_dma_ctx, msg_buf+msg_words, remainder_bytes, mac_buf);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_mac, mac_buf, mac_byte_len))
	{
		printf("\r\n HMAC-SHA1 dma sample test 1 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n HMAC-SHA1 dma sample test 1 success");fflush(stdout);
	}

	/**************** dma test 2 ****************/
	uint32_clear(mac_buf, mac_byte_len/4);
	ret = hmac_sha1_dma(key, 0, key_byte_len, msg_buf, msg_byte_len, mac_buf, hash_call_manage);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_mac, mac_buf, mac_byte_len))
	{
		printf("\r\n HMAC-SHA1 dma sample test 2 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n HMAC-SHA1 dma sample test 2 success");fflush(stdout);
	}

	/**************** dma test 3 ****************/
	uint32_clear(mac_buf, mac_byte_len/4);
	ret = hmac_dma_init(hmac_dma_ctx, HASH_SHA1, key, 0, key_byte_len, hash_call_manage);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_dma_update_blocks(hmac_dma_ctx, msg_buf, msg_words);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hmac_dma_final(hmac_dma_ctx, msg_buf+msg_words, remainder_bytes, mac_buf);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_mac, mac_buf, mac_byte_len))
	{
		printf("\r\n HMAC-SHA1 dma sample test 3 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n HMAC-SHA1 dma sample test 3 success");fflush(stdout);
	}

	/**************** dma test 4 ****************/
	uint32_clear(mac_buf, mac_byte_len/4);
	ret = hmac_dma(HASH_SHA1, key, 0, key_byte_len, msg_buf, msg_byte_len, mac_buf, hash_call_manage);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_mac, mac_buf, mac_byte_len))
	{
		printf("\r\n HMAC-SHA1 dma sample test 4 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n HMAC-SHA1 dma sample test 4 success");fflush(stdout);
	}
#endif

	return 0;
}


#endif

