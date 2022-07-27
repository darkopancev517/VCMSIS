#include <stdio.h>
#include "../../crypto_include/hash_hmac/sha256.h"
#include "../../crypto_include/utility.h"



void hash_call_manage(void);




#ifdef SUPPORT_HASH_SHA256

uint32_t sample_test_sha256(void)
{
	uint8_t msg[80] = {
		0xCB,0xAC,0x28,0x1C,0xAC,0xD3,0x03,0x5F,0x81,0x5A,0x0E,0x82,0xF0,0xA5,0xEA,0x7A,
		0xC5,0x3C,0x4F,0xF7,0x0B,0xB7,0x9F,0xA6,0x1E,0x80,0xEA,0xF6,0xE6,0x03,0x0F,0x7F,
		0xF8,0x3E,0xF7,0x36,0x0F,0xC4,0x10,0xB0,0x1E,0xDC,0x20,0xD1,0xA1,0xB2,0xBD,0xAF,
		0xBE,0xC0,0x21,0xB4,0xF3,0x68,0xE3,0x06,0x91,0x34,0xE0,0x12,0xC2,0xB4,0x30,0x70,
		0x83,0xD3,0xA9,0xBD,0xD2,0x06,0xE2,0x4E,0x5F,0x0D,0x86,0xE1,0x3D,0x66,0x36,0x65,
	};
	uint8_t std_digest[32] = {
		0x9A,0xFB,0x65,0x73,0x35,0xA9,0x7C,0x53,0x6A,0x5F,0xD6,0xCC,0x15,0xBD,0xCC,0xC4,
		0xDD,0x97,0x5A,0x26,0x1E,0x3B,0x65,0x31,0xCA,0x04,0x14,0x9A,0x90,0x8C,0x46,0xFA
	};
	uint8_t digest[32];
	uint8_t msg_byte_len = 80;
	uint8_t digest_byte_len = 32;

	uint32_t ret;

	SHA256_CTX sha256_ctx[1];
	HASH_CTX *hash_ctx = sha256_ctx;

#ifdef HASH_DMA_FUNCTION
	uint8_t block_byte_len = 64;
	uint32_t *msg_buf = (uint32_t *)(DMA_RAM_BASE);
	uint32_t *digest_buf = msg_buf+512;
	uint32_t msg_words = (msg_byte_len - (msg_byte_len%block_byte_len))/4;
	uint32_t remainder_bytes = msg_byte_len - msg_words*4;
	SHA256_DMA_CTX sha256_dma_ctx[1];
	HASH_DMA_CTX *hash_dma_ctx = sha256_dma_ctx;

	uint32_copy(msg_buf, (uint32_t *)msg, (msg_byte_len+3)/4);
#endif

	printf("\r\n\r\n -------------- SHA256 sample test -------------- ");

	//the following 4 calculations are equivalent

	/**************** test 1 ****************/
	memset_(digest, 0, digest_byte_len);
	ret = sha256_init(sha256_ctx);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = sha256_update(sha256_ctx, msg, 4);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = sha256_update(sha256_ctx, msg+4, 44);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = sha256_update(sha256_ctx, msg+48, 32);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = sha256_final(sha256_ctx, digest);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_digest, digest, digest_byte_len))
	{
		printf("\r\n SHA256 sample test 1 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n SHA256 sample test 1 success");fflush(stdout);
	}

	/**************** test 2 ****************/
	memset_(digest, 0, digest_byte_len);
	ret = sha256(msg, msg_byte_len, digest);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_digest, digest, digest_byte_len))
	{
		printf("\r\n SHA256 sample test 2 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n SHA256 sample test 2 success");fflush(stdout);
	}

	/**************** test 3 ****************/
	memset_(digest, 0, digest_byte_len);
	ret = hash_init(hash_ctx, HASH_SHA256);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hash_update(hash_ctx, msg, 4);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hash_update(hash_ctx, msg+4, 44);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hash_update(hash_ctx, msg+48, 32);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hash_final(hash_ctx, digest);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_digest, digest, digest_byte_len))
	{
		printf("\r\n SHA256 sample test 3 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n SHA256 sample test 3 success");fflush(stdout);
	}

	/**************** test 4 ****************/
	memset_(digest, 0, digest_byte_len);
	ret = hash(HASH_SHA256, msg, msg_byte_len, digest);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(memcmp_(std_digest, digest, digest_byte_len))
	{
		printf("\r\n SHA256 sample test 4 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n SHA256 sample test 4 success");fflush(stdout);
	}


#ifdef HASH_DMA_FUNCTION
	//the following 4 DMA calculations are equivalent

	/**************** dma test 1 ****************/
	uint32_clear(digest_buf, digest_byte_len/4);
	ret = sha256_dma_init(sha256_dma_ctx, hash_call_manage);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = sha256_dma_update_blocks(sha256_dma_ctx, msg_buf, msg_words);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = sha256_dma_final(sha256_dma_ctx, msg_buf+msg_words, remainder_bytes, digest_buf);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(uint32_BigNumCmp((uint32_t *)std_digest, digest_byte_len/4, digest_buf, digest_byte_len/4))
	{
		printf("\r\n SHA256 dma sample test 1 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n SHA256 dma sample test 1 success");fflush(stdout);
	}

	/**************** dma test 2 ****************/
	uint32_clear(digest_buf, digest_byte_len/4);
	ret = sha256_dma(msg_buf, msg_byte_len, digest_buf, hash_call_manage);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(uint32_BigNumCmp((uint32_t *)std_digest, digest_byte_len/4, digest_buf, digest_byte_len/4))
	{
		printf("\r\n SHA256 dma sample test 2 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n SHA256 dma sample test 2 success");fflush(stdout);
	}

	/**************** dma test 3 ****************/
	uint32_clear(digest_buf, digest_byte_len/4);
	ret = hash_dma_init(hash_dma_ctx, HASH_SHA256, hash_call_manage);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hash_dma_update_blocks(hash_dma_ctx, msg_buf, msg_words);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	ret = hash_dma_final(hash_dma_ctx, msg_buf+msg_words, remainder_bytes, digest_buf);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(uint32_BigNumCmp((uint32_t *)std_digest, digest_byte_len/4, digest_buf, digest_byte_len/4))
	{
		printf("\r\n SHA256 dma sample test 3 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n SHA256 dma sample test 3 success");fflush(stdout);
	}

	/**************** dma test 4 ****************/
	uint32_clear(digest_buf, digest_byte_len/4);
	ret = hash_dma(HASH_SHA256, msg_buf, msg_byte_len, digest_buf, hash_call_manage);
	if(HASH_SUCCESS != ret)
	{
		return 1;
	}

	if(uint32_BigNumCmp((uint32_t *)std_digest, digest_byte_len/4, digest_buf, digest_byte_len/4))
	{
		printf("\r\n SHA256 dma sample test 4 error");fflush(stdout);
		return 1;
	}
	else
	{
		printf("\r\n SHA256 dma sample test 4 success");fflush(stdout);
	}

#endif

	return 0;
}


#endif

