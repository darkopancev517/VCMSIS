#include <stdio.h>
#include "../../crypto_include/utility.h"
#include "../../crypto_include/hash_hmac/hash.h"
#include "../../crypto_include/hash_hmac/hmac.h"



extern uint32_t check_hash_alg(HASH_ALG hash_alg);
extern uint32_t hash_get_block_word_len(HASH_ALG hash_alg);
extern uint32_t hash_get_digest_word_len(HASH_ALG hash_alg);



/* function: init HMAC
 * parameters:
 *     ctx ------------------------ input, HMAC_CTX context pointer
 *     hash_alg ------------------- input, specific hash algorithm
 *     key ------------------------ input, key
 *     sp_key_idx ----------------- input, index of secure port key
 *     key_bytes ------------------ input, byte length of key, it could be 0
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure hash_alg is valid
 */
uint32_t hmac_init(HMAC_CTX *ctx, HASH_ALG hash_alg, uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes)
{
	uint32_t block_byte_len, digest_byte_len;
	uint32_t i, ret;

	if(NULL == ctx)
	{
		return HASH_BUFFER_NULL;
	}
	else if(HASH_SUCCESS != check_hash_alg(hash_alg))
	{
		return HASH_INPUT_INVALID;
	}
	else if(NULL == key)
	{
#ifdef HMAC_SECURE_PORT_FUNCTION
		//TODO
#else
		key_bytes = 0;
#endif
	}
	else
	{;}

	if(key)   //key is from user input
	{
		//hash_hmac_disable_secure_port();
	}
	else      //key is from secure port
	{
#ifdef HMAC_SECURE_PORT_FUNCTION
		//hash_hmac_enable_secure_port(sp_key_idx);
		//hash_hmac_enable_secure_port(sp_key_idx+1);
#endif
	}

	block_byte_len = hash_get_block_word_len(hash_alg)<<2;
	digest_byte_len = hash_get_digest_word_len(hash_alg)<<2;

	ctx->hash_alg = hash_alg;

	//get K0
	if(key_bytes <= block_byte_len)
	{
		memcpy_(ctx->K0, key, key_bytes);
		memset_(((uint8_t *)(ctx->K0)) + key_bytes, 0, block_byte_len - key_bytes);
	}
	else
	{
		//K0 = hash(key)||000..00
		ret = hash_init(ctx->hash_ctx, hash_alg);
		if(HASH_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		ret = hash_update(ctx->hash_ctx, (uint8_t *)key, key_bytes);
		if(HASH_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		ret = hash_final(ctx->hash_ctx, (uint8_t *)(ctx->K0));
		if(HASH_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		memset_(((uint8_t *)(ctx->K0)) + digest_byte_len, 0, block_byte_len - digest_byte_len);
	}

	//get K0 ^ ipad
	digest_byte_len = block_byte_len/4;
	for(i=0; i<digest_byte_len; i++)
	{
		ctx->K0[i] ^= HMAC_IPAD;
	}

	ret = hash_init(ctx->hash_ctx, hash_alg);
	if(HASH_SUCCESS != ret)
	{
		goto END;
	}
	else
	{
		ret = hash_update(ctx->hash_ctx, (uint8_t *)(ctx->K0), block_byte_len);
	}

END:
	if(HASH_SUCCESS != ret)
	{
		memset_(ctx, 0, sizeof(HMAC_CTX));
	}
	else
	{;}

	return ret;
}


/* function: hmac update message
 * parameters:
 *     ctx ------------------------ input, HMAC_CTX context pointer
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the input message
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the three parameters are valid, and ctx is initialized
 */
uint32_t hmac_update(HMAC_CTX *ctx, const uint8_t *msg, uint32_t msg_bytes)
{
	if(NULL == ctx)
	{
		return HASH_BUFFER_NULL;
	}
	else
	{
		return hash_update(ctx->hash_ctx, msg, msg_bytes);
	}
}


/* function: message update done, get the hmac
 * parameters:
 *     ctx ------------------------ input, HMAC_CTX context pointer
 *     mac ------------------------ output, hmac
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the ctx is valid and initialized
 *     2. please make sure the mac buffer is sufficient
 */
uint32_t hmac_final(HMAC_CTX *ctx, uint8_t *mac)
{
	uint32_t block_word_len;
	uint32_t i, ret;

	if(NULL == ctx || NULL == mac)
	{
		return HASH_BUFFER_NULL;
	}
	else
	{;}

	//set mac as hash((K0^ipad)||message)
	ret = hash_final(ctx->hash_ctx, mac);
	if(HASH_SUCCESS != ret)
	{
		goto END;
	}
	else
	{;}

	//get K0 ^ opad
	block_word_len = hash_get_block_word_len(ctx->hash_alg);
	for(i=0; i<block_word_len; i++)
	{
		ctx->K0[i] ^= HMAC_IPAD_XOR_OPAD;
	}

	ret = hash_init(ctx->hash_ctx, ctx->hash_alg);
	if(HASH_SUCCESS != ret)
	{
		goto END;
	}
	else
	{;}

	ret = hash_update(ctx->hash_ctx, (uint8_t *)(ctx->K0), ctx->hash_ctx->block_byte_len);
	if(HASH_SUCCESS != ret)
	{
		goto END;
	}
	else
	{;}

	ret = hash_update(ctx->hash_ctx, mac, ctx->hash_ctx->digest_byte_len);
	if(HASH_SUCCESS != ret)
	{
		goto END;
	}
	else
	{;}

	ret = hash_final(ctx->hash_ctx, mac);

END:
	if(HASH_SUCCESS != ret)
	{
		memset_(mac, 0, hash_get_digest_word_len(ctx->hash_alg)<<2);
	}
	else
	{;}

	memset_(ctx, 0, sizeof(HMAC_CTX));

	return ret;
}


/* function: input key and whole message, get the hmac
 * parameters:
 *     hash_alg ------------------- input, specific hash algorithm
 *     key ------------------------ input, key
 *     sp_key_idx ----------------- input, index of secure port key
 *     key_bytes ------------------ input, byte length of the key
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the input message
 *     mac ------------------------ output, hmac
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the mac buffer is sufficient
 */
uint32_t hmac(HASH_ALG hash_alg, uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes, uint8_t *msg, uint32_t msg_bytes,
		uint8_t *mac)
{
	HMAC_CTX ctx[1];
	uint32_t ret;

	if(NULL == mac)
	{
		return HASH_BUFFER_NULL;
	}
	else
	{;}

	ret = hmac_init(ctx, hash_alg, key, sp_key_idx, key_bytes);
	if(HASH_SUCCESS != ret)
	{
		goto END;
	}
	else
	{;}

	ret = hash_update(ctx->hash_ctx, (uint8_t *)msg, msg_bytes);
	if(HASH_SUCCESS != ret)
	{
		goto END;
	}
	else
	{;}

	ret = hmac_final(ctx, mac);

END:
	memset_(ctx, 0, sizeof(HMAC_CTX));

	return ret;
}


#ifdef HASH_DMA_FUNCTION
/* function: init dma hmac
 * parameters:
 *     ctx ------------------------ input, HMAC_DMA_CTX context pointer
 *     hash_alg ------------------- input, specific hash algorithm
 *     key ------------------------ input, key
 *     sp_key_idx ----------------- input, index of secure port key
 *     key_bytes ------------------ input, key byte length
 *     callback ------------------- callback function pointer
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure hash_alg is valid
 *     2. here hmac is not for SHA3.
 */
uint32_t hmac_dma_init(HMAC_DMA_CTX *ctx, HASH_ALG hash_alg, const uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes,
		HASH_CALLBACK callback)
{
	uint32_t ret;

	if(NULL == ctx || NULL == callback)
	{
		return HASH_BUFFER_NULL;
	}
	else if(HASH_SUCCESS != check_hash_alg(hash_alg))
	{
		return HASH_INPUT_INVALID;
	}
	else if(NULL == key)
	{
		key_bytes = 0;
	}
	else
	{;}

	ret = hmac_init(ctx->hmac_ctx, hash_alg, (uint8_t *)key, sp_key_idx, key_bytes);
	if(HASH_SUCCESS == ret)
	{
		ctx->hash_dma_ctx->hash_alg = hash_alg;
		ctx->hash_dma_ctx->block_word_len = (ctx->hmac_ctx->hash_ctx->block_byte_len)/4;
		uint32_copy(ctx->hash_dma_ctx->total, ctx->hmac_ctx->hash_ctx->total, (ctx->hash_dma_ctx->block_word_len)/8);
		ctx->hash_dma_ctx->callback = callback;

		hash_set_dma_mode();
		hash_set_dma_output_len(0);
	}
	else
	{;}

	return ret;
}


/* function: dma hmac update message
 * parameters:
 *     ctx ------------------------ input, HMAC_DMA_CTX context pointer
 *     msg ------------------------ input, message
 *     msg_words ------------------ input, word length of the input message, must be a multiple of block word length of HASH
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the four parameters are valid, and ctx is initialized
 */
uint32_t hmac_dma_update_blocks(HMAC_DMA_CTX *ctx, uint32_t *msg, uint32_t msg_words)
{
	if(NULL == ctx)
	{
		return HASH_BUFFER_NULL;
	}
	else
	{
		return hash_dma_update_blocks(ctx->hash_dma_ctx, msg, msg_words);
	}
}


/* function: dma hmac message update done, get the hmac
 * parameters:
 *     ctx ------------------------ input, HMAC_DMA_CTX context pointer
 *     remainder_msg -------------- input, message
 *     remainder_bytes ------------ input, byte length of the last message, must be in [0, BLOCK_BYTE_LEN-1],
 *                                  here BLOCK_BYTE_LEN is block byte length of HASH
 *     mac ------------------------ output, hmac
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the three parameters are valid, and ctx is initialized
 */
uint32_t hmac_dma_final(HMAC_DMA_CTX *ctx, uint32_t *remainder_msg, uint32_t remainder_bytes, uint32_t *mac)
{
	uint32_t i;
	uint32_t ret;

	if((NULL == ctx) || (NULL == mac))
	{
		return HASH_BUFFER_NULL;
	}
	else
	{;}

	ret = hash_dma_final(ctx->hash_dma_ctx, remainder_msg, remainder_bytes, mac);//print_buf_U8(mac, 32, "mac---------");
	if(HASH_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//get K0 ^ opad
	for(i=0; i<ctx->hash_dma_ctx->block_word_len; i++)
	{
		ctx->hmac_ctx->K0[i] ^= HMAC_IPAD_XOR_OPAD;
	}

	ret = hash_init(ctx->hmac_ctx->hash_ctx, ctx->hmac_ctx->hash_alg);
	if(HASH_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = hash_update(ctx->hmac_ctx->hash_ctx, (uint8_t *)(ctx->hmac_ctx->K0), ctx->hmac_ctx->hash_ctx->block_byte_len);
	if(HASH_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//tmp_iterator may not be accessed by bytes
	uint32_copy(ctx->hmac_ctx->K0, mac, ctx->hmac_ctx->hash_ctx->digest_byte_len/4);
	ret = hash_update(ctx->hmac_ctx->hash_ctx, (uint8_t *)(ctx->hmac_ctx->K0), ctx->hmac_ctx->hash_ctx->digest_byte_len);
	if(HASH_SUCCESS != ret)
	{
		return ret;
	}
	else
	{
		return hash_final(ctx->hmac_ctx->hash_ctx, (uint8_t *)mac);
	}
}


/* function: dma hmac input key and message, get the hmac
 * parameters:
 *     hash_alg ------------------- input, specific hash algorithm
 *     key ------------------------ input, key
 *     sp_key_idx ----------------- input, index of secure port key
 *     key_bytes ------------------ input, key byte length
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the input message
 *     mac ------------------------ output, hmac
 *     callback ------------------- callback function pointer
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure hash_alg is valid
 */
uint32_t hmac_dma(HASH_ALG hash_alg, uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes, uint32_t *msg, uint32_t msg_bytes,
		uint32_t *mac, HASH_CALLBACK callback)
{
	uint32_t blocks_words, remainder_bytes;
	uint32_t ret;
	HMAC_DMA_CTX ctx[1];

	if(NULL == mac)
	{
		return HASH_BUFFER_NULL;
	}
	else
	{;}

	if(NULL == key)
	{
		key_bytes = 0;
	}
	else
	{;}

	if(NULL == msg)
	{
		msg_bytes = 0;
	}
	else
	{;}

	ret = hmac_dma_init(ctx, hash_alg, key, sp_key_idx, key_bytes, callback);
	if(HASH_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	remainder_bytes = msg_bytes % ctx->hmac_ctx->hash_ctx->block_byte_len;
	blocks_words = (msg_bytes - remainder_bytes)/4;
	ret = hash_dma_update_blocks(ctx->hash_dma_ctx, msg, blocks_words);
	if(HASH_SUCCESS != ret)
	{
		return ret;
	}
	else
	{
		return hmac_dma_final(ctx, (uint32_t *)(msg+blocks_words), remainder_bytes, mac);
	}
}
#endif

