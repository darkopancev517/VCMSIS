#include <stdio.h>

#include "../../crypto_include/utility.h"
#include "../../crypto_include/ske/ske_gcm_gmac.h"



#ifdef SUPPORT_SKE_MODE_GCM



/* function: ske_lp gcm mode init config(CPU style)
 * parameters:
 *     ctx ------------------------ input, SKE_GCM_CTX context pointer
 *     alg ------------------------ input, ske_lp algorithm
 *     crypto --------------------- input, encrypting or decrypting
 *     key ------------------------ input, key in bytes, key of AES(128/192/256) or SM4
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes
 *     iv_bytes ------------------- input, byte length of iv, now only 12 bytes is supported
 *     aad_bytes ------------------ input, byte length of aad, it could be any value, including 0
 *     c_bytes -------------------- input, byte length of plaintext/ciphertext, it could be any value, including 0
 *     mac_bytes ------------------ input, byte length of mac, must be in [0,16]
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is for CPU style
 *     2. only AES(128/192/256) and SM4 are supported for GCM mode
 *     3. if key is from user input, please make sure key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 *     4. iv must be 12 bytes here
 *     5. aad_bytes and c_bytes could not be zero at the same time
 */
uint32_t ske_lp_gcm_init(SKE_GCM_CTX *ctx, SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx,
		uint8_t *iv, uint32_t iv_bytes, uint32_t aad_bytes, uint32_t c_bytes, uint32_t mac_bytes)
{
	uint32_t tmp[4];

	if(NULL == ctx || NULL == iv)
	{
		return SKE_BUFFER_NULL;
	}
	else if(12 != iv_bytes)
	{
		return SKE_INPUT_INVALID;
	}
	else if((0 == aad_bytes) && (0 == c_bytes))
	{
		return SKE_INPUT_INVALID;
	}
	else if (mac_bytes > SKE_LP_GCM_MAX_BYTES)
	{
		return SKE_INPUT_INVALID;
	}
	else
	{;}

	memcpy_(tmp, iv, iv_bytes);
	memset_(((uint8_t *)(tmp))+iv_bytes, 0, sizeof(tmp)-iv_bytes);

	ctx->aad_bytes     = aad_bytes;
	ctx->c_bytes       = c_bytes;
	ctx->mac_bytes     = mac_bytes;
	ctx->current_bytes = 0;
	ctx->crypto        = crypto;

	ske_lp_set_cpu_mode();
	ske_lp_set_aad_len_uint32(aad_bytes);
	ske_lp_set_c_len_uint32(c_bytes);

	return ske_lp_init_internal(ctx->ske_gcm_ctx, alg, SKE_MODE_GCM, crypto, key, sp_key_idx, (uint8_t *)tmp, SKE_LP_DMA_DISABLE);
}


#ifdef SKE_LP_GCM_CPU_UPDATE_AAD_BY_STEP
/* function: ske_lp gcm mode input aad
 * parameters:
 *     ctx ------------------------ input, SKE_GCM_CTX context pointer
 *     aad ------------------------ input, aad
 *     bytes ---------------------- input, real byte length of aad
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function must be called after calling ske_lp_gcm_init()
 *     2. if there is no aad, this function could be omitted
 *     3. if the whole aad is too long, you could divide it into some sections by byte, then call
 *        this function to input the sections respectively. for example, if the whole aad byte
 *        length is 65, it could be divided into 3 sections with byte length 10,47,8 respectively.
 */
uint32_t ske_lp_gcm_update_aad(SKE_GCM_CTX *ctx, uint8_t *aad, uint32_t bytes)
{
	uint32_t blocks_bytes, remainder_bytes;
	uint32_t total_bytes, idx, capacity_bytes;
	uint32_t ret = SKE_ERROR;

	if(NULL == ctx)
	{
		return SKE_BUFFER_NULL;
	}
	else if((0 == ctx->aad_bytes) || (NULL == aad) || (0 == bytes))
	{
		return SKE_SUCCESS;
	}
	else
	{;}

	idx = ctx->current_bytes & 0x0F;
	capacity_bytes = 16 - idx;

	total_bytes = ctx->current_bytes + bytes;
	if(total_bytes < bytes || total_bytes > ctx->aad_bytes)
	{
		return SKE_INPUT_INVALID;
	}
	else if(total_bytes == ctx->aad_bytes)
	{
		if(idx)
		{
			if(bytes > capacity_bytes)
			{
				memcpy_(ctx->buf + idx, aad, capacity_bytes);
				ret = ske_lp_update_blocks_no_output(ctx->ske_gcm_ctx, ctx->buf, 16);
				if(SKE_SUCCESS != ret)
				{
					goto END;
				}
				else
				{;}

				aad += capacity_bytes;
				bytes -= capacity_bytes;
			}
			else
			{
				//the last block
				memcpy_(ctx->buf + idx, aad, bytes);
				memset_(ctx->buf + idx + bytes, 0, sizeof(ctx->buf) - (idx + bytes));
				goto LAST_BLOCK;
			}
		}

		blocks_bytes = (bytes)&(~0x0F);
		remainder_bytes = (bytes)&0x0F;
		if(0 == remainder_bytes)
		{
			blocks_bytes -= 16;
			remainder_bytes = 16;
		}
		else
		{;}

		ret = ske_lp_update_blocks_no_output(ctx->ske_gcm_ctx, aad, blocks_bytes);
		if(SKE_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		//the last block
		memcpy_(ctx->buf, aad+blocks_bytes, remainder_bytes);
		memset_(ctx->buf + remainder_bytes, 0, sizeof(ctx->buf) - remainder_bytes);

LAST_BLOCK:

		ske_lp_set_last_block(1);
		ret = ske_lp_update_blocks_no_output(ctx->ske_gcm_ctx, ctx->buf, 16);
		ske_lp_set_last_block(0);

		if(SKE_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		ctx->current_bytes = 0;
	}
	else
	{
		ctx->current_bytes = total_bytes;

		if(idx)
		{
			if(bytes >= capacity_bytes)
			{
				memcpy_(ctx->buf + idx, aad, capacity_bytes);
				ret = ske_lp_update_blocks_no_output(ctx->ske_gcm_ctx, ctx->buf, 16);
				if(SKE_SUCCESS != ret)
				{
					goto END;
				}
				else
				{;}

				aad += capacity_bytes;
				bytes -= capacity_bytes;
			}
			else
			{
				memcpy_(ctx->buf + idx, aad, bytes);
				ret = SKE_SUCCESS;
				goto END;
			}
		}

		blocks_bytes = (bytes)&(~0x0F);
		remainder_bytes = (bytes)&0x0F;

		ret = ske_lp_update_blocks_no_output(ctx->ske_gcm_ctx, aad, blocks_bytes);
		if(SKE_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		if(remainder_bytes)
		{
			memcpy_(ctx->buf, aad+blocks_bytes, remainder_bytes);
		}
		else
		{;}
	}

	ret = SKE_SUCCESS;

END:

	return ret;
}
#endif


/* function: ske_lp gcm mode input aad(one-off style)
 * parameters:
 *     ctx ------------------------ input, SKE_GCM_CTX context pointer
 *     aad ------------------------ input, aad, its length is ctx->aad_bytes, please make sure
 *                                         aad here is integral
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function must be called after calling ske_lp_gcm_init()
 *     2. if there is no aad, this function could be omitted
 *     3. please make sure aad is integral
 */
uint32_t ske_lp_gcm_aad(SKE_GCM_CTX *ctx, uint8_t *aad)
{
#ifndef SKE_LP_GCM_CPU_UPDATE_AAD_BY_STEP
	uint32_t blocks_bytes, remainder_bytes;
	uint32_t ret = SKE_ERROR;

	if(NULL == ctx || (NULL == aad && ctx->aad_bytes != 0))
	{
		return SKE_BUFFER_NULL;
	}
	else if(0 == ctx->aad_bytes)
	{
		return SKE_SUCCESS;
	}
	else
	{;}

	blocks_bytes = (ctx->aad_bytes)&(~0x0F);
	remainder_bytes = (ctx->aad_bytes)&0x0F;

	if(0 == remainder_bytes)
	{
		blocks_bytes -= 16;
		remainder_bytes = 16;
	}
	else
	{;}

	ret = ske_lp_update_blocks_no_output(ctx->ske_gcm_ctx, aad, blocks_bytes);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//the last block
	memcpy_(ctx->buf, aad+blocks_bytes, remainder_bytes);
	memset_(ctx->buf + remainder_bytes, 0, sizeof(ctx->buf) - remainder_bytes);

	ske_lp_set_last_block(1);
	ret = ske_lp_update_blocks_no_output(ctx->ske_gcm_ctx, ctx->buf, 16);
	ske_lp_set_last_block(0);

	return ret;
#else
	if(NULL == ctx)
	{
		return SKE_BUFFER_NULL;
	}
	else
	{
		return ske_lp_gcm_update_aad(ctx, aad, ctx->aad_bytes);
	}
#endif
}


/* function: ske_lp gcm mode input plaintext/ciphertext
 * parameters:
 *     ctx ------------------------ input, SKE_GCM_CTX context pointer
 *     in ------------------------- input, plaintext or ciphertext
 *     out ------------------------ output, ciphertext or plaintext
 *     bytes ---------------------- input, byte length of input or output
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function must be called after calling ske_lp_gcm_aad()
 *     2. if there is no plaintext/ciphertext, this function could be omitted
 *     3. to save memory, in and out could be the same buffer, in this case, the output will
 *        cover the input.
 *     4. if the whole plaintext/ciphertext is too long, you could divide it by block(16 bytes),
 *        and if the whole plaintext/ciphertext byte length is not a multiple of 16, please make
 *        sure the last section contains the tail, then call this function to input the sections
 *        respectively. for example, if the whole plaintext/ciphertext byte length is 65, it 
 *        could be divided into 3 sections with byte length 48,16,1 respectively.
 */
uint32_t ske_lp_gcm_update_blocks(SKE_GCM_CTX *ctx, uint8_t *in, uint8_t *out, uint32_t bytes)
{
	uint32_t blocks_bytes, remainder_bytes;
	uint32_t total_bytes;
	uint32_t ret = SKE_ERROR;

	if(NULL == ctx || NULL == in || NULL == out)
	{
		return SKE_BUFFER_NULL;
	}
	else if(0 == bytes)    //input is empty
	{
		return SKE_SUCCESS;
	}
	else
	{;}

	total_bytes = ctx->current_bytes + bytes;
	if (total_bytes < bytes || total_bytes > ctx->c_bytes)  // overflow
	{
		return SKE_INPUT_INVALID;
	}
	else if (total_bytes == ctx->c_bytes)
	{
		blocks_bytes = (bytes)&(~0x0F);
		remainder_bytes = (bytes)&0x0F;
		if(0 == remainder_bytes)
		{
			blocks_bytes -= 16;
			remainder_bytes = 16;
		}
		else
		{;}

		ret = ske_lp_update_blocks_internal(ctx->ske_gcm_ctx, in, out, blocks_bytes);
		if(SKE_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		//the last block
		memcpy_(ctx->buf, in+blocks_bytes, remainder_bytes);
		memset_(ctx->buf + remainder_bytes, 0, sizeof(ctx->buf) - remainder_bytes);

		ske_lp_set_last_block(1);
		ret = ske_lp_update_blocks_internal(ctx->ske_gcm_ctx, ctx->buf, ctx->buf, 16);
		ske_lp_set_last_block(0);

		if(SKE_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		memcpy_(out+blocks_bytes, ctx->buf, remainder_bytes);
	} 
	else
	{
		if(bytes & (16-1))
		{
			ret = SKE_INPUT_INVALID;
			goto END;
		}
		else
		{
			ret = ske_lp_update_blocks_internal(ctx->ske_gcm_ctx, in, out, bytes);
			if(SKE_SUCCESS != ret)
			{
				goto END;
			}
			else
			{;}
		}
	}

	ret = SKE_SUCCESS;
	ctx->current_bytes = total_bytes;

END:

	return ret;
}


/* function: ske_lp gcm mode finish
 * parameters:
 *     ctx ------------------------ input, SKE_GCM_CTX context pointer
 *     mac ------------------------ input(for decryption), output(for encryption)
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function must be called after calling ske_lp_gcm_update()
 *     2. mac_bytes could be 0, but not bigger than SKE_LP_GCM_MAX_BYTES
 *     3. for encryption, mac is output; and for decryption, mac is input, if returns SKE_SUCCESS
 *        that means certification passed, otherwise not.
 */
uint32_t ske_lp_gcm_final(SKE_GCM_CTX *ctx, uint8_t *mac)
{
	uint32_t ret;

	if(NULL == ctx || NULL == mac)
	{
		return SKE_BUFFER_NULL;
	}
	else
	{;}

	ske_lp_start();

	//get mac
	ret = ske_lp_wait_till_done();
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ske_lp_simple_get_output_block((uint32_t *)ctx->buf, ctx->ske_gcm_ctx->block_words);

	if(SKE_CRYPTO_ENCRYPT == ctx->crypto)
	{
		memcpy_(mac, ctx->buf, ctx->mac_bytes);
		ret = SKE_SUCCESS;
	}
	else
	{
		ret = memcmp_(mac, ctx->buf, ctx->mac_bytes);
	}

	//memset_(ctx, 0, sizeof(SKE_GCM_CTX));

	return ret;
}


/* function: ske_lp gcm mode encrypt/decrypt(one-off style)
 * parameters:
 *     alg ------------------------ input, ske_lp algorithm
 *     crypto --------------------- input, encrypting or decrypting
 *     key ------------------------ input, key in bytes, key of AES(128/192/256) or SM4
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes
 *     iv_bytes ------------------- input, byte length of iv, now only 12 bytes supported
 *     aad ------------------------ input, aad, please make sure aad here is integral
 *     aad_bytes ------------------ input, byte length of aad, it could be any value, including 0
 *     in ------------------------- input, plaintext or ciphertext
 *     out ------------------------ output, ciphertext or plaintext
 *     c_bytes -------------------- input, byte length of plaintext/ciphertext, it could be any value,
 *                                  including 0
 *     mac ------------------------ input(for decryption), output(for encryption)
 *     mac_bytes ------------------ input, byte length of mac.
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is for CPU style
 *     2. only AES(128/192/256) and SM4 are supported for GCM mode
 *     3. if key is from user input, please make sure key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 *     4. iv must be 12 bytes here
 *     5. aad_bytes and c_bytes could not be zero at the same time
 *     6. to save memory, in and out could be the same buffer, in this case, the output will
 *        cover the input.
 *     7. mac_bytes could be 0, but not bigger than SKE_LP_GCM_MAX_BYTES
 *     8. for encryption, mac is output; and for decryption, mac is input, if returns SKE_SUCCESS
 *        that means certification passed, otherwise not.
 */
uint32_t ske_lp_gcm_crypto(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint32_t iv_bytes, uint8_t *aad, uint32_t aad_bytes, uint8_t *in, uint8_t *out, uint32_t c_bytes,
		uint8_t *mac, uint32_t mac_bytes)
{
	SKE_GCM_CTX ctx[1];
	uint32_t ret;

	ret = ske_lp_gcm_init(ctx, alg, crypto, key, sp_key_idx, iv, iv_bytes, aad_bytes, c_bytes, mac_bytes);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = ske_lp_gcm_aad(ctx, aad);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = ske_lp_gcm_update_blocks(ctx, in, out, c_bytes);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	return ske_lp_gcm_final(ctx, mac);
}




#ifdef SUPPORT_SKE_MODE_GMAC
/* function: ske_lp gmac mode init config(CPU style)
 * parameters:
 *     ctx ------------------------ input, SKE_GMAC_CTX context pointer
 *     alg ------------------------ input, ske_lp algorithm
 *     mac_action ----------------- input, must be SKE_GENERATE_MAC or SKE_VERIFY_MAC
 *     key ------------------------ input, key in bytes, key of AES(128/192/256) or SM4
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes
 *     iv_bytes ------------------- input, byte length of iv, now only 12 bytes supported
 *     aad_bytes ------------------ input, byte length of aad, it could be any value, including 0
 *     c_bytes -------------------- input, byte length of message, it could be any value, including 0
 *     mac_bytes ------------------ input, byte length of mac, must be in [1,16]
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is for CPU style
 *     2. only AES(128/192/256) and SM4 are supported for GMAC mode
 *     3. if key is from user input, please make sure key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 *     4. iv must be 12 bytes here
 *     5. aad_bytes and c_bytes could not be zero at the same time
 */
uint32_t ske_lp_gmac_init(SKE_GMAC_CTX *ctx, SKE_ALG alg, SKE_MAC mac_action, uint8_t *key, uint16_t sp_key_idx,
		uint8_t *iv, uint32_t iv_bytes, uint32_t aad_bytes, uint32_t c_bytes, uint32_t mac_bytes)
{
	if(NULL == ctx)
	{
		return SKE_BUFFER_NULL;
	}
	else
	{;}

	ctx->mac_action = mac_action;

	return ske_lp_gcm_init(ctx->gcm_ctx, alg, SKE_CRYPTO_ENCRYPT, key, sp_key_idx, iv, iv_bytes, aad_bytes, c_bytes, mac_bytes);
}


#ifdef SKE_LP_GCM_CPU_UPDATE_AAD_BY_STEP
/* function: ske_lp gmac mode input aad
 * parameters:
 *     ctx ------------------------ input, SKE_GMAC_CTX context pointer
 *     aad ------------------------ input, aad
 *     bytes ---------------------- input, real byte length of aad
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function must be called after calling ske_lp_gmac_init()
 *     2. if there is no aad, this function could be omitted
 *     3. if the whole aad is too long, you could divide it into some sections by byte, then call
 *        this function to input the sections respectively. for example, if the whole aad byte
 *        length is 65, it could be divided into 3 sections with byte length 10,47,8 respectively.
 */
uint32_t ske_lp_gmac_update_aad(SKE_GMAC_CTX *ctx, uint8_t *aad, uint32_t bytes)
{
	return ske_lp_gcm_update_aad(ctx->gcm_ctx, aad, bytes);
}
#endif


/* function: ske_lp gmac mode input aad(one-off style)
 * parameters:
 *     ctx ------------------------ input, SKE_GMAC_CTX context pointer
 *     aad ------------------------ input, aad, its length is ctx->gcm_ctx->aad_bytes, please make sure
 *                                         aad here is integral
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function must be called after calling ske_lp_gmac_init()
 *     2. if there is no aad, this function could be omitted
 */
uint32_t ske_lp_gmac_aad(SKE_GMAC_CTX *ctx, uint8_t *aad)
{
	if(NULL == ctx)
	{
		return SKE_BUFFER_NULL;
	}
	else
	{;}

	return ske_lp_gcm_aad(ctx->gcm_ctx, aad);
}


/* function: ske_lp gmac mode input message
 * parameters:
 *     ctx ------------------------ input, SKE_GMAC_CTX context pointer
 *     in ------------------------- input, message
 *     bytes ---------------------- input, byte length of message
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function must be called after calling ske_lp_gmac_aad()
 *     2. if there is no message, this function could be omitted
 *     3. if the whole message is too long, you could divide it into some sections by byte, then call
 *        this function to input the sections respectively. for example, if the whole message byte
 *        length is 65, it could be divided into 3 sections with byte length 15,49,1 respectively.
 */
uint32_t ske_lp_gmac_update(SKE_GMAC_CTX *ctx, uint8_t *in, uint32_t bytes)
{
	uint32_t blocks_bytes, remainder_bytes;
	uint32_t total_bytes, idx, capacity_bytes;
	uint32_t ret = SKE_ERROR;

	if(NULL == ctx || ((NULL == in) && bytes != 0))
	{
		return SKE_BUFFER_NULL;
	}
	else if((0 == ctx->gcm_ctx->c_bytes) || (NULL == in) || (0 == bytes))    //input is empty
	{
		return SKE_SUCCESS;
	}
	else
	{;}

	idx = ctx->gcm_ctx->current_bytes & 0x0F;
	capacity_bytes = 16 - idx;

	total_bytes = ctx->gcm_ctx->current_bytes + bytes;
	if(total_bytes < bytes  || total_bytes > ctx->gcm_ctx->c_bytes)
	{
		return SKE_INPUT_INVALID;
	}
	else if(total_bytes == ctx->gcm_ctx->c_bytes)
	{
		if(idx)
		{
			if(bytes > capacity_bytes)
			{
				memcpy_(ctx->gcm_ctx->buf + idx, in, capacity_bytes);
				ret = ske_lp_gmac_update_blocks_internal(ctx->gcm_ctx->buf, 16);
				if(SKE_SUCCESS != ret)
				{
					goto END;
				}
				else
				{;}

				in += capacity_bytes;
				bytes -= capacity_bytes;
			}
			else
			{
				//the last block
				memcpy_(ctx->gcm_ctx->buf + idx, in, bytes);
				memset_(ctx->gcm_ctx->buf + idx + bytes, 0, sizeof(ctx->gcm_ctx->buf) - (idx + bytes));
				goto LAST_BLOCK;
			}
		}

		blocks_bytes = bytes & (~0x0F);
		remainder_bytes = bytes & 0x0F;
		if(0 == remainder_bytes)
		{
			blocks_bytes -= 16;
			remainder_bytes = 16;
		}
		else
		{;}

		ret = ske_lp_gmac_update_blocks_internal(in, blocks_bytes);
		if(SKE_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		//the last block
		memcpy_(ctx->gcm_ctx->buf, in + blocks_bytes, remainder_bytes);
		memset_(ctx->gcm_ctx->buf + remainder_bytes, 0, sizeof(ctx->gcm_ctx->buf) - remainder_bytes);

LAST_BLOCK:

		ske_lp_set_last_block(1);
		ret = ske_lp_gmac_update_blocks_internal(ctx->gcm_ctx->buf, 16);
		ske_lp_set_last_block(0);
		if(SKE_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		ctx->gcm_ctx->current_bytes = total_bytes;
	}
	else
	{
		ctx->gcm_ctx->current_bytes = total_bytes;

		if(idx)
		{
			if(bytes >= capacity_bytes)
			{
				memcpy_(ctx->gcm_ctx->buf + idx, in, capacity_bytes);
				ret = ske_lp_gmac_update_blocks_internal(ctx->gcm_ctx->buf, 16);
				if(SKE_SUCCESS != ret)
				{
					goto END;
				}
				else
				{;}

				in += capacity_bytes;
				bytes -= capacity_bytes;
			}
			else
			{
				memcpy_(ctx->gcm_ctx->buf + idx, in, bytes);
				ret = SKE_SUCCESS;
				goto END;
			}
		}

		blocks_bytes = (bytes)&(~0x0F);
		remainder_bytes = (bytes)&0x0F;

		ret = ske_lp_gmac_update_blocks_internal(in, blocks_bytes);
		if(SKE_SUCCESS != ret)
		{
			goto END;
		}
		else
		{;}

		if(remainder_bytes)
		{
			memcpy_(ctx->gcm_ctx->buf, in+blocks_bytes, remainder_bytes);
		}
		else
		{;}
	}

	ret = SKE_SUCCESS;

END:

	return ret;
}


/* function: ske_lp gmac mode finish
 * parameters:
 *     ctx ------------------------ input, SKE_GMAC_CTX context pointer
 *     mac ------------------------ input(for generating mac), output(for verifying mac)
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function must be called after calling ske_lp_gmac_update_blocks()
 *     2. mac_bytes must be in [1, SKE_LP_GCM_MAX_BYTES]
 *     3. if ctx->mac_action is SKE_GENERATE_MAC, mac is output. and if ctx->mac_action is SKE_VERIFY_MAC,
 *        mac is input, return value SKE_SUCCESS means the mac is valid, otherwise mac is invalid.
 */
uint32_t ske_lp_gmac_final(SKE_GMAC_CTX *ctx, uint8_t *mac)
{
	uint32_t ret;

	if(NULL == ctx || NULL == mac)
	{
		return SKE_BUFFER_NULL;
	}
	else
	{;}

	//get mac
	ret = ske_lp_gcm_final(ctx->gcm_ctx, ctx->gcm_ctx->buf);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	if(SKE_GENERATE_MAC == ctx->mac_action)
	{
		memcpy_(mac, ctx->gcm_ctx->buf, ctx->gcm_ctx->mac_bytes);
		ret = SKE_SUCCESS;
	}
	else
	{
		ret = memcmp_(mac, ctx->gcm_ctx->buf, ctx->gcm_ctx->mac_bytes);
	}

	return ret;
}


/* function: ske_lp gmac mode(one-off style)
 * parameters:
 *     alg ------------------------ input, ske_lp algorithm
 *     mac_action ----------------- input, must be SKE_GENERATE_MAC or SKE_VERIFY_MAC
 *     key ------------------------ input, key in bytes, key of AES(128/192/256) or SM4
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes
 *     iv_bytes ------------------- input, byte length of iv, now only 12 bytes supported
 *     aad ------------------------ input, aad, please make sure aad here is integral
 *     aad_bytes ------------------ input, byte length of aad, it could be any value, including 0
 *     in ------------------------- input, message
 *     c_bytes -------------------- input, byte length of message, it could be any value,
 *                                  including 0
 *     mac ------------------------ input(for generating mac), output(for verifying mac)
 *     mac_bytes ------------------ input, byte length of mac.
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is for CPU style
 *     2. only AES(128/192/256) and SM4 are supported for GCM mode
 *     3. if key is from user input, please make sure key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 *     4. iv must be 12 bytes here
 *     5. aad_bytes and c_bytes could not be zero at the same time
 *     6. mac_bytes must be in [1, SKE_LP_GCM_MAX_BYTES]
 *     7. if mac_action is SKE_GENERATE_MAC, mac is output. and if mac_action is SKE_VERIFY_MAC,
 *        mac is input, return value SKE_SUCCESS means the mac is valid, otherwise mac is invalid.
 */
uint32_t ske_lp_gmac_crypto(SKE_ALG alg, SKE_MAC mac_action, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint32_t iv_bytes, uint8_t *aad, uint32_t aad_bytes, uint8_t *in, uint32_t c_bytes, uint8_t *mac,
		uint32_t mac_bytes)
{
	SKE_GMAC_CTX ctx[1];
	uint32_t ret;

	ret = ske_lp_gmac_init(ctx, alg, mac_action, key, sp_key_idx, iv, iv_bytes, aad_bytes, c_bytes, mac_bytes);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = ske_lp_gcm_aad(ctx->gcm_ctx, aad);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = ske_lp_gmac_update(ctx, in, c_bytes);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	return ske_lp_gmac_final(ctx, mac);
}
#endif



#ifdef SKE_LP_DMA_FUNCTION
/* function: ske_lp dma gcm mode init config
 * parameters:
 *     ctx ------------------------ input, SKE_GCM_CTX context pointer
 *     alg ------------------------ input, ske_lp algorithm
 *     crypto --------------------- input, encrypting or decrypting
 *     key ------------------------ input, key in bytes, key of AES(128/192/256) or SM4
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes
 *     iv_bytes ------------------- input, byte length of iv, now only 12 bytes is supported
 *     aad_bytes ------------------ input, byte length of aad, it could be any value, including 0
 *     c_bytes -------------------- input, byte length of plaintext/ciphertext, it could be any value, including 0
 *     mac_bytes ------------------ input, byte length of mac, must be in [0,16]
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is for DMA style
 *     2. only AES(128/192/256) and SM4 are supported for GCM mode
 *     3. if key is from user input, please make sure key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 *     4. iv must be 12 bytes here
 *     5. aad_bytes and c_bytes could not be zero at the same time
 */
uint32_t ske_lp_dma_gcm_init(SKE_GCM_CTX *ctx, SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx,
		uint8_t *iv, uint32_t iv_bytes, uint32_t aad_bytes, uint32_t c_bytes, uint32_t mac_bytes)
{
	uint32_t tmp[4];

	if(NULL == ctx || NULL == iv)
	{
		return SKE_BUFFER_NULL;
	}
	else if(12 != iv_bytes)
	{
		return SKE_INPUT_INVALID;
	}
	else if((0 == aad_bytes) && (0 == c_bytes))
	{
		return SKE_INPUT_INVALID;
	}
	else if ((aad_bytes > 0x1fffffff) || (c_bytes > 0x1fffffff))
	{
		return SKE_INPUT_INVALID;
	}
	else if (mac_bytes > SKE_LP_GCM_MAX_BYTES)
	{
		return SKE_INPUT_INVALID;
	}
	else
	{;}

	memcpy_(tmp, iv, iv_bytes);
	memset_(((uint8_t *)(tmp))+iv_bytes, 0, sizeof(tmp)-iv_bytes);

	ctx->aad_bytes     = aad_bytes;
	ctx->c_bytes       = c_bytes;
	ctx->mac_bytes     = mac_bytes;
	ctx->current_bytes = 0;
	ctx->crypto        = crypto;

	ske_lp_set_cpu_mode();
	ske_lp_set_aad_len_uint32(aad_bytes);
	ske_lp_set_c_len_uint32(c_bytes);

	return ske_lp_init_internal(ctx->ske_gcm_ctx, alg, SKE_MODE_GCM, crypto, key, sp_key_idx, (uint8_t *)tmp , SKE_LP_DMA_ENABLE);
}


/* function: ske_lp dma gcm mode input aad
 * parameters:
 *     ctx ------------------------ input, SKE_GCM_CTX context pointer
 *     aad ------------------------ input, aad
 *     bytes ---------------------- input, real byte length of aad
 *     callback ------------------- callback function pointer, this could be NULL, means doing nothing
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function must be called after calling ske_lp_dma_gcm_init()
 *     2. the whole aad must be some blocks, if not, please pad it with 0
 *     3. if the whole aad is too long, you could divide it by block(16 bytes), and if the whole aad byte
 *        length is not a multiple of 16, please make sure the last section contains the tail, then call
 *        this function to input the sections respectively. for example, if the whole aad byte length is 65,
 *        it could be divided into 3 sections with byte length 48,16,1 respectively.
 */
uint32_t ske_lp_dma_gcm_update_aad_blocks(SKE_GCM_CTX *ctx, uint32_t *aad, uint32_t bytes, SKE_CALLBACK callback)
{
	uint32_t aad_blocks_words = ((bytes+15)&(~0x0F))/4;
	uint32_t total_bytes;
	uint32_t ret;

	if(NULL == ctx)
	{
		return SKE_BUFFER_NULL;
	}
	else if((NULL == aad) || (0 == bytes))
	{
		return SKE_SUCCESS;
	}
	else
	{;}

	total_bytes = ctx->current_bytes + bytes;

	if (total_bytes < bytes || total_bytes > ctx->aad_bytes)  // overflow
	{
		return SKE_INPUT_INVALID;
	}
	else if(total_bytes == ctx->aad_bytes)
	{
		ret = ske_lp_dma_operate(ctx->ske_gcm_ctx, aad, NULL, aad_blocks_words, 0, callback);
		if(SKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{;}

		ctx->current_bytes = 0;
	}
	else
	{
		if(bytes & (16-1))
		{
			return SKE_INPUT_INVALID;
		}
		else
		{;}

		ret = ske_lp_dma_operate(ctx->ske_gcm_ctx, aad, NULL, aad_blocks_words, 0, callback);
		if(SKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{;}

		ctx->current_bytes = total_bytes;
	}

	return SKE_SUCCESS;
}


/* function: ske_lp dma gcm mode input plaintext/ciphertext, get ciphertext/plaintext+mac
 * parameters:
 *     ctx ------------------------ input, SKE_GCM_CTX context pointer
 *     in ------------------------- input, plaintext/ciphertext
 *     out ------------------------ output, ciphertext/plaintext or ciphertext/plaintext+mac
 *     in_bytes ------------------- input, byte length of in
 *     callback ------------------- callback function pointer, this could be NULL, means doing nothing
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function must be called after calling ske_lp_dma_gcm_update_aad_blocks()
 *     2. the whole plaintext/ciphertext must be some blocks, if not, please pad it with 0
 *     3. if the whole plaintext/ciphertext is too long, you could divide it by block(16 bytes), and if
 *        the whole plaintext/ciphertext byte length is not a multiple of 16, please make sure the last
 *        section contains the tail, then call this function to input the sections respectively. for
 *        example, if the whole plaintext/ciphertext byte length is 65, it could be divided into 3 sections
 *        with byte length 48,16,1 respectively.
 *     4. the output will be some blocks too, it has the same length as the input, and with padding 0 if
 *        necessary
 *     5. if input contains the tail, then output will be ciphertext/plaintext+mac
 *     6. to save memory, in and out could be the same buffer, in this case, the output will
 *        cover the input.
 */
uint32_t ske_lp_dma_gcm_update_blocks(SKE_GCM_CTX *ctx, uint32_t *in, uint32_t *out, uint32_t in_bytes,
		SKE_CALLBACK callback)
{
	uint32_t in_blocks_words = ((in_bytes+15)&(~0x0F))/4;
	uint32_t total_bytes;
	uint32_t ret;

	if((NULL == ctx) || (NULL == in) || (NULL == out))
	{
		return SKE_BUFFER_NULL;
	}
	else if(0 == in_bytes)
	{
		return SKE_SUCCESS;
	}
	else
	{;}

	if(0 == ctx->c_bytes)
	{
		if (0 == ctx->aad_bytes)
		{
			//hardware does not support
			return SKE_INPUT_INVALID;
		}
		else
		{
			//just for the case that aad is not NULL, and c is NULL, here input aad block including tail.
			ret = ske_lp_dma_operate(ctx->ske_gcm_ctx, in, out, in_blocks_words, 4, callback);
			if(SKE_SUCCESS != ret)
			{
				return ret;
			}
			else
			{;}

			clear_block_tail(out, ctx->mac_bytes);

			return SKE_SUCCESS;
		}
	}
	else
	{;}

	total_bytes = ctx->current_bytes + in_bytes;
	if (total_bytes < in_bytes || total_bytes > ctx->c_bytes)  // overflow
	{
		return SKE_INPUT_INVALID;
	}
	else if(total_bytes == ctx->c_bytes)
	{
		ret = ske_lp_dma_operate(ctx->ske_gcm_ctx, in, out, in_blocks_words, in_blocks_words + 4, callback);
		if(SKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{;}

		clear_block_tail(out + in_blocks_words, ctx->mac_bytes);
	}
	else
	{
		if(in_bytes & (16-1))
		{
			return SKE_INPUT_INVALID;
		}
		else
		{;}

		ret = ske_lp_dma_operate(ctx->ske_gcm_ctx, in, out, in_blocks_words, in_blocks_words, callback);
		if(SKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{;}
	}

	ctx->current_bytes = total_bytes;

	return SKE_SUCCESS;
}


/* function: ske_lp dma gcm mode finish
 * parameters:
 *     ctx ------------------------ input, SKE_GCM_CTX context pointer
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is optional
 */
uint32_t ske_lp_dma_gcm_final(SKE_GCM_CTX *ctx)
{
	if(NULL == ctx)
	{
		return SKE_BUFFER_NULL;
	}
	else
	{;}

	memset_(ctx, 0, sizeof(SKE_GCM_CTX));

	return SKE_SUCCESS;
}


/* function: ske_lp dma gcm mode encrypt/decrypt(one-off style)
 * parameters:
 *     alg ------------------------ input, ske_lp algorithm
 *     crypto --------------------- input, encrypting or decrypting
 *     key ------------------------ input, key in bytes, key of AES(128/192/256) or SM4
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes
 *     iv_bytes ------------------- input, byte length of iv, now only 12 bytes supported
 *     aad ------------------------ input, aad, please make sure aad here is integral
 *     aad_bytes ------------------ input, byte length of aad, it could be any value, including 0
 *     in ------------------------- input, plaintext/ciphertext
 *     out ------------------------ output, ciphertext/plaintext+mac
 *     c_bytes -------------------- input, byte length of plaintext/ciphertext, it could be any value, including 0
 *     mac_bytes ------------------ input, byte length of mac, must be in [0,16]
 *     callback ------------------- callback function pointer, this could be NULL, means doing nothing
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is for DMA style
 *     2. only AES(128/192/256) and SM4 are supported for GCM mode
 *     3. if key is from user input, please make sure key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 *     4. iv must be 12 bytes here
 *     5. aad_bytes and c_bytes could not be zero at the same time
 *     6. if aad exists, it must be some blocks, if not, please pad it with 0
 *     7. plaintext/ciphertext must be some blocks, if not, please pad it with 0
 *     8. the output ciphertext/plaintext has the same number of blocks as the input plaintext/ciphertext,  
 *        and followed by one block, it is mac with padding 0 if necessary, so is the second last blcok if 
 *        necessary(ciphertext/plaintext)
 *     9. please make sure aad and in(plaintext/ciphertext) both are integral
 *     10. to save memory, in and out could be the same buffer, in this case, the output will
 *        cover the input.
 */
uint32_t ske_lp_dma_gcm_crypto(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint32_t iv_bytes, uint32_t *aad, uint32_t aad_bytes, uint32_t *in, uint32_t *out, uint32_t c_bytes,
		uint32_t mac_bytes, SKE_CALLBACK callback)
{
	SKE_GCM_CTX ctx[1];
	uint32_t ret;

	ret = ske_lp_dma_gcm_init(ctx, alg, crypto, key, sp_key_idx, iv, iv_bytes, aad_bytes, c_bytes, mac_bytes);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	if(aad_bytes && (0 == c_bytes))
	{
		ret = ske_lp_dma_operate(ctx->ske_gcm_ctx, aad, out, ((aad_bytes+15)/16)<<2, 4, callback);
		if(SKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{;}

		clear_block_tail(out, mac_bytes);
	}
	else
	{
		ret = ske_lp_dma_gcm_update_aad_blocks(ctx, aad, aad_bytes, callback);
		if(SKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{;}

		ret = ske_lp_dma_gcm_update_blocks(ctx, in, out, c_bytes, callback);
		if(SKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{;}
	}

	return ske_lp_dma_gcm_final(ctx);
}

#endif


#endif
