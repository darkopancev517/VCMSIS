#include <stdio.h>

#include "../../crypto_include/utility.h"
#include "../../crypto_include/ske/ske.h"



static SKE_CTX g_ske_ctx[1];


//since hardware does not suppot 3DES
#if (defined(SUPPORT_SKE_TDES_128))
static SKE_ALG g_ske_alg;              //hold current ske algorithm(for 3DES)
static SKE_MODE g_ske_mode;            //hold input mode for 3DES
static SKE_CRYPTO g_ske_crypto_action; //hold current block cipher crypto for 3DES
static uint32_t g_ske_key_buf[6];      //hold key for 3DES
static uint32_t g_ske_iv_buf[4];       //hold current IV for 3DES
#endif


#if (defined(SUPPORT_SKE_TDES_128))
/* function: a=a+1
 * parameters:
 *     a -------------------------- input, big integer a in bytes, big-endian
 *     bytes ---------------------- input, byte length of a
 * return: none
 * caution:
 *     1. for CTR/CCM counter addition(big-endian)
 */
void ske_big_endian_add_uint8(uint8_t *a, uint32_t a_bytes, uint8_t b)
{
	int32_t i;

	for(i=a_bytes; i>0; )
	{
		a[--i] += b;
		if(a[i] < b)
		{
			b = 1;
		}
		else
		{
#if 1
			b = 0;   //for security
#else
			break;
#endif
		}
	}
}
#endif


/* function: check whether the ske algorithm is valid or not
 * parameters:
 *     ske_alg -------------------- input, specific ske algorithm
 * return: SKE_SUCCESS(valid), other(invalid)
 * caution:
 *     1.
 */
uint8_t ske_lp_check_alg(SKE_ALG ske_alg)
{
	uint8_t ret;

	switch(ske_alg)
	{
#ifdef SUPPORT_SKE_DES
	case SKE_ALG_DES:
#endif

#ifdef SUPPORT_SKE_TDES_128
	case SKE_ALG_TDES_128:
#endif

#ifdef SUPPORT_SKE_TDES_192
	case SKE_ALG_TDES_192:
#endif

#ifdef SUPPORT_SKE_TDES_EEE_128
	case SKE_ALG_TDES_EEE_128:
#endif

#ifdef SUPPORT_SKE_TDES_EEE_192
	case SKE_ALG_TDES_EEE_192:
#endif

#ifdef SUPPORT_SKE_AES_128
	case SKE_ALG_AES_128:
#endif

#ifdef SUPPORT_SKE_AES_192
	case SKE_ALG_AES_192:
#endif

#ifdef SUPPORT_SKE_AES_256
	case SKE_ALG_AES_256:
#endif

#ifdef SUPPORT_SKE_SM4
	case SKE_ALG_SM4:
#endif
		ret = SKE_SUCCESS;
		break;

	default:
		ret = SKE_INPUT_INVALID;
		break;
	}

	return ret;
}


/* function: check whether the ske algorithm mode is valid or not
 * parameters:
 *     ske_alg -------------------- input, specific ske algorithm
 *     ske_mode ------------------- input, specific ske algorithm mode
 * return: SKE_SUCCESS(valid), other(invalid)
 * caution:
 *     1.
 */
uint8_t ske_lp_check_mode(SKE_ALG ske_alg, SKE_MODE ske_mode)
{
	uint8_t ret;

	switch(ske_mode)
	{
#ifdef SUPPORT_SKE_MODE_ECB
	case SKE_MODE_ECB:
#endif

#ifdef SUPPORT_SKE_MODE_CBC
	case SKE_MODE_CBC:
#endif

#ifdef SUPPORT_SKE_MODE_CFB
	case SKE_MODE_CFB:
#endif

#ifdef SUPPORT_SKE_MODE_OFB
	case SKE_MODE_OFB:
#endif

#ifdef SUPPORT_SKE_MODE_CTR
	case SKE_MODE_CTR:
#endif

#ifdef SUPPORT_SKE_MODE_CBC_MAC
	case SKE_MODE_CBC_MAC:
#endif
		ret = SKE_SUCCESS;
		break;

	//for DES/3DES, CAMC is not supported at present
#ifdef SUPPORT_SKE_MODE_CMAC
	case SKE_MODE_CMAC:
		switch(ske_alg)
		{
#ifdef SUPPORT_SKE_AES_128
		case SKE_ALG_AES_128 :
#endif

#ifdef SUPPORT_SKE_AES_192
		case SKE_ALG_AES_192 :
#endif

#ifdef SUPPORT_SKE_AES_256
		case SKE_ALG_AES_256 :
#endif

#ifdef SUPPORT_SKE_SM4
		case SKE_ALG_SM4 :
#endif

#if (defined(SUPPORT_SKE_AES_128) || defined(SUPPORT_SKE_AES_192) || defined(SUPPORT_SKE_AES_256) || defined(SUPPORT_SKE_SM4))
			ret = SKE_SUCCESS;
			break;
#endif

		default:
			ret = SKE_INPUT_INVALID;
		}
		break;
#endif

	//for DES/3DES, XTS, CCM and GCM mode are not supported due to the definition or standard
#ifdef SUPPORT_SKE_MODE_XTS
	case SKE_MODE_XTS:
#endif

#ifdef SUPPORT_SKE_MODE_CCM
	case SKE_MODE_CCM:
#endif

#ifdef SUPPORT_SKE_MODE_GCM
	case SKE_MODE_GCM:
#endif

#if (defined(SUPPORT_SKE_MODE_XTS) || defined(SUPPORT_SKE_MODE_CCM) || defined(SUPPORT_SKE_MODE_GCM))
		switch(ske_alg)
		{
#ifdef SUPPORT_SKE_AES_128
		case SKE_ALG_AES_128 :
#endif

#ifdef SUPPORT_SKE_AES_192
		case SKE_ALG_AES_192 :
#endif

#ifdef SUPPORT_SKE_AES_256
		case SKE_ALG_AES_256 :
#endif

#ifdef SUPPORT_SKE_SM4
		case SKE_ALG_SM4 :
#endif

#if (defined(SUPPORT_SKE_AES_128) || defined(SUPPORT_SKE_AES_192) || defined(SUPPORT_SKE_AES_256) || defined(SUPPORT_SKE_SM4))
			ret = SKE_SUCCESS;
			break;
#endif

		default:
			ret = SKE_INPUT_INVALID;
			break;
		}

		break;
#endif

	default:
		ret = SKE_INPUT_INVALID;
		break;
	}

	return ret;
}


/* function: get block byte length for spcific ske_lp alg
 * parameters:
 *     ske_alg -------------------- input, ske_lp algorithm
 * return: block byte length for ske_lp alg
 * caution:
 *     1. please make sure ske_alg is valid
 */
uint8_t ske_lp_get_block_byte_len(SKE_ALG ske_alg)
{
	uint8_t byteLen;

	switch(ske_alg)
	{
#ifdef SUPPORT_SKE_DES
	case SKE_ALG_DES :
#endif

#ifdef SUPPORT_SKE_TDES_128
	case SKE_ALG_TDES_128 :
#endif

#ifdef SUPPORT_SKE_TDES_192
	case SKE_ALG_TDES_192 :
#endif

#ifdef SUPPORT_SKE_TDES_EEE_128
	case SKE_ALG_TDES_EEE_128 :
#endif

#ifdef SUPPORT_SKE_TDES_EEE_192
	case SKE_ALG_TDES_EEE_192 :
#endif

#if (defined(SUPPORT_SKE_DES) ||defined(SUPPORT_SKE_TDES_128) ||defined(SUPPORT_SKE_TDES_192)   \
	||defined(SUPPORT_SKE_TDES_EEE_128) ||defined(SUPPORT_SKE_TDES_EEE_192))
		byteLen = 8;
		break;
#endif

#ifdef SUPPORT_SKE_AES_128
	case SKE_ALG_AES_128 :
#endif

#ifdef SUPPORT_SKE_AES_192
	case SKE_ALG_AES_192 :
#endif

#ifdef SUPPORT_SKE_AES_256
	case SKE_ALG_AES_256 :
#endif

#ifdef SUPPORT_SKE_SM4
	case SKE_ALG_SM4 :
#endif

#if (defined(SUPPORT_SKE_AES_128) ||defined(SUPPORT_SKE_AES_192) ||defined(SUPPORT_SKE_AES_256) ||defined(SUPPORT_SKE_SM4))
		byteLen = 16;
		break;
#endif

	default:
		byteLen = 16;   //default alg SM4
	}

	return byteLen;
}


/* function: get key byte length for spcific ske_lp alg
 * parameters:
 *     ske_alg -------------------- input, ske_lp algorithm
 * return: key byte length for ske_lp alg
 * caution:
 *     1. please make sure ske_alg is valid
 */
uint8_t ske_lp_get_key_byte_len(SKE_ALG ske_alg)
{
	uint8_t byte_len;

	switch(ske_alg)
	{
#ifdef SUPPORT_SKE_DES
	case SKE_ALG_DES :
		byte_len = 8;
		break;
#endif

#ifdef SUPPORT_SKE_TDES_128
	case SKE_ALG_TDES_128 :
#endif

#ifdef SUPPORT_SKE_TDES_EEE_128
	case SKE_ALG_TDES_EEE_128 :
#endif

#ifdef SUPPORT_SKE_AES_128
	case SKE_ALG_AES_128 :
#endif

#ifdef SUPPORT_SKE_SM4
	case SKE_ALG_SM4 :
#endif

#if (defined(SUPPORT_SKE_TDES_128) || defined(SUPPORT_SKE_TDES_EEE_128) || defined(SUPPORT_SKE_AES_128) \
	||defined(SUPPORT_SKE_SM4))
		byte_len = 16;
		break;
#endif

#ifdef SUPPORT_SKE_TDES_192
	case SKE_ALG_TDES_192 :
#endif

#ifdef SUPPORT_SKE_TDES_EEE_192
	case SKE_ALG_TDES_EEE_192 :
#endif

#ifdef SUPPORT_SKE_AES_192
	case SKE_ALG_AES_192 :
#endif

#if (defined(SUPPORT_SKE_TDES_192) || defined(SUPPORT_SKE_TDES_EEE_192) || defined(SUPPORT_SKE_AES_192))
		byte_len = 24;
		break;
#endif

#ifdef SUPPORT_SKE_AES_256
	case SKE_ALG_AES_256 :
		byte_len = 32;
		break;
#endif

	default:
		byte_len = 16;   //default alg SM4
	}

	return byte_len;
}


/* function: set ske_lp iv
 * parameters:
 *     iv ------------------------- input, initial vector
 *     block_bytes ---------------- input, byte length of current ske_lp block
 * return: none
 * caution:
 *     1. please make sure the inputs are valid
 */
void ske_lp_set_iv(uint8_t *iv, uint32_t block_bytes)
{
	uint32_t tmp[4];

	if(((uint32_t)iv) & 3)
	{
		memcpy_(tmp, iv, block_bytes);
		ske_lp_set_iv_uint32(tmp, block_bytes/4);
	}
	else
	{
		ske_lp_set_iv_uint32((uint32_t *)iv, block_bytes/4);
	}
}


/* function: set ske_lp key
 * parameters:
 *     alg ------------------------ input, ske_lp algorithm
 *     key ------------------------ input, key
 *     key_bytes ------------------ input, byte length of key
 *     key_idx -------------------- input, key index, only 1 and 2 are valid
 * return: none
 * caution:
 *     1. please make sure the inputs are valid
 */
void ske_lp_set_key(SKE_ALG alg, uint8_t *key, uint16_t key_bytes, uint16_t key_idx)
{
	uint32_t tmp[8];

	memcpy_(tmp, key, key_bytes);

	//for 3DES-2key, set key3=key1
	switch(alg)
	{
#ifdef SUPPORT_SKE_TDES_128
	case SKE_ALG_TDES_128 :
#endif

#ifdef SUPPORT_SKE_TDES_EEE_128
	case SKE_ALG_TDES_EEE_128 :
#endif

#if (defined(SUPPORT_SKE_TDES_128) || defined(SUPPORT_SKE_TDES_EEE_128))
		memcpy_(tmp+4, key, 8);
		key_bytes += 8;
		break;
#endif

	default:
		break;
	}

	ske_lp_set_key_uint32(tmp, key_idx, key_bytes/4);
}


/* function: ske_lp init config
 * parameters:
 *     ctx ------------------------ input, SKE_CTX context pointer
 *     alg ------------------------ input, ske_lp algorithm
 *     mode ----------------------- input, ske_lp algorithm operation mode, like ECB,CBC,OFB,etc.
 *     crypto --------------------- input, encrypting or decrypting
 *     key ------------------------ input, key in bytes
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes, must be a block
 *     dma_en --------------------- input, for DMA mode(not 0) or not(0)
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is common for CPU/DMA/DMA-LL
 *     2. if mode is ECB, then there is no iv, in this case iv could be NULL
 *     3. if mode is CMAC/CBC-MAC, the iv must be a block of all zero
 *     4. if key is from user input, please make sure the argument key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 */
uint32_t ske_lp_init_internal(SKE_CTX *ctx, SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, uint8_t *key,
		uint16_t sp_key_idx, uint8_t *iv, uint32_t dma_en)
{
	uint32_t key_bytes;

	if(NULL == ctx)
	{
		return SKE_BUFFER_NULL;
	}
	else if(SKE_SUCCESS != ske_lp_check_alg(alg))
	{
		return SKE_INPUT_INVALID;
	}
	else if(SKE_SUCCESS != ske_lp_check_mode(alg, mode))
	{
		return SKE_INPUT_INVALID;
	}
	else if(crypto > SKE_CRYPTO_DECRYPT)
	{
		return SKE_INPUT_INVALID;
	}
	else if(NULL == key)   //secure port
	{
		return SKE_INPUT_INVALID;
	}
	else
	{;}

	if(SKE_MODE_ECB == mode)
	{
		iv = NULL;
	}
	else if(NULL == iv)
	{
		return SKE_BUFFER_NULL;//SKE_ERROR;//
	}
	else
	{;}

#if (defined(SUPPORT_SKE_TDES_128))
	/******************* because hw does not support TDES ******************/

	g_ske_alg = alg;   //very important!!! to distinguish 3DES and other algorithm, if the MACRO is available

	if((SKE_ALG_TDES_128 == alg) || (SKE_ALG_TDES_192 == alg) || (SKE_ALG_TDES_EEE_128 == alg) ||
			(SKE_ALG_TDES_EEE_192 == alg))
	{
		if((SKE_ALG_TDES_128 == alg) || (SKE_ALG_TDES_EEE_128 == alg))
		{
			memcpy_(g_ske_key_buf, key, 16);
			memcpy_(g_ske_key_buf+16/4, key, 8);
		}
		else
		{
			memcpy_(g_ske_key_buf, key, 24);
		}

		g_ske_ctx->block_bytes = ske_lp_get_block_byte_len(alg);
		g_ske_ctx->block_words = g_ske_ctx->block_bytes>>2;

		g_ske_mode = mode;
		g_ske_crypto_action = crypto;
		alg = SKE_ALG_DES;

		if(SKE_MODE_ECB != mode)
		{
			memcpy_(g_ske_iv_buf, iv, 8);
			mode = SKE_MODE_ECB;
		}
		else
		{;}
	}
	else
	{;}
	/***********************************************************************/
#endif

	ctx->block_bytes = ske_lp_get_block_byte_len(alg);
	ctx->block_words = ctx->block_bytes>>2;

	ske_lp_set_endian_uint32();
	ske_lp_set_alg(alg);
	ske_lp_set_mode(mode);
	ske_lp_set_crypto(crypto);
	ske_lp_set_last_block(0);

	//set iv or nonce
	if(NULL != iv)
	{
		ske_lp_set_iv(iv, ctx->block_bytes);
	}
	else
	{;}

	// key1
	key_bytes = ske_lp_get_key_byte_len(alg);
	ske_lp_set_key(alg, key, key_bytes, sp_key_idx);
	return ske_lp_expand_key(dma_en);
}


/* function: ske_lp init config(CPU style)
 * parameters:
 *     alg ------------------------ input, ske_lp algorithm
 *     mode ----------------------- input, ske_lp algorithm operation mode, like ECB,CBC,OFB,etc.
 *     crypto --------------------- input, encrypting or decrypting
 *     key ------------------------ input, key in bytes
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes, must be a block
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. if mode is ECB, then there is no iv, in this case iv could be NULL
 *     2. this function is designed for ECB/CBC/CFB/OFB/CTR/XTS modes, and input/output unit must be a block
 *     3. if key is from user input, please make sure key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 */
uint32_t ske_lp_init(SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv)
{
	ske_lp_set_cpu_mode();
#if defined(SUPPORT_SKE_MODE_XTS)
	ske_lp_set_c_len_uint32(0);  //just for XTS mode
#endif

	return ske_lp_init_internal(g_ske_ctx, alg, mode, crypto, key, sp_key_idx, iv, SKE_LP_DMA_DISABLE);
}


#if (defined(SUPPORT_SKE_TDES_128))
/* function: ske 3des encryption or decryption(CPU style)
 * parameters:
 *     in ------------------------- input, plaintext or ciphertext
 *     out ------------------------ output, ciphertext or plaintext
 *     bytes ---------------------- input, byte length of input or output.
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is designed for ECB/CBC/CFB/OFB/CTR modes, and input/output unit must be a block
 *     2. to save memory, in and out could be the same buffer, in this case, the output will
 *        cover the input.
 *     3. bytes must be a multiple of block byte length.
 */
uint32_t ske_tdes_update_blocks(uint8_t *in, uint8_t *out, uint32_t bytes)
{
	uint32_t tmp_in[2], tmp_out[2];
	uint32_t tmp_iv[2];
	uint8_t *p_out = out;
	uint32_t is_EEE;
	uint32_t i;
	uint32_t ret;

	if(NULL == in)
	{
		return SKE_BUFFER_NULL;
	}
	else if(bytes & (g_ske_ctx->block_bytes-1))
	{
		return SKE_INPUT_INVALID;
	}
	else if (0 == bytes)
	{
		return SKE_SUCCESS;
	}
	else
	{;}

	if((SKE_ALG_TDES_128 == g_ske_alg) || (SKE_ALG_TDES_192 == g_ske_alg))
	{
		is_EEE = 0;
	}
	else
	{
		is_EEE = 1;
	}

	//input one block ---> calculating ---> output one block
	for (i = 0; i < bytes; i += g_ske_ctx->block_bytes)
	{
		/************* first **************/
		memcpy_(tmp_in, in, g_ske_ctx->block_bytes);

		if((SKE_MODE_CFB == g_ske_mode) || (SKE_MODE_OFB == g_ske_mode) || (SKE_MODE_CTR == g_ske_mode))
		{
			ret = tdes_ecb_update_one_block(is_EEE, g_ske_key_buf, SKE_CRYPTO_ENCRYPT, g_ske_iv_buf, tmp_iv);
			if(SKE_SUCCESS != ret)
			{
				ret = SKE_ERROR;
				goto END;
			}
			else
			{;}

			tmp_out[0] = tmp_iv[0] ^ tmp_in[0];
			tmp_out[1] = tmp_iv[1] ^ tmp_in[1];
		}
		else    //ECB or CBC
		{
			if((SKE_MODE_CBC == g_ske_mode) && (SKE_CRYPTO_ENCRYPT == g_ske_crypto_action)) //CBC encrypt
			{
				tmp_in[0] ^= g_ske_iv_buf[0];
				tmp_in[1] ^= g_ske_iv_buf[1];
			}
			else
			{;}

			ret = tdes_ecb_update_one_block(is_EEE, g_ske_key_buf, g_ske_crypto_action, tmp_in, tmp_out);
			if(SKE_SUCCESS != ret)
			{
				ret = SKE_ERROR;
				goto END;
			}
			else
			{;}

			if((SKE_MODE_CBC == g_ske_mode) && (SKE_CRYPTO_DECRYPT == g_ske_crypto_action)) //CBC decrypt
			{
				tmp_out[0] ^= g_ske_iv_buf[0];
				tmp_out[1] ^= g_ske_iv_buf[1];
			}
			else
			{;}
		}

		//update iv
		if(SKE_MODE_CTR == g_ske_mode)
		{
			ske_big_endian_add_uint8((uint8_t *)g_ske_iv_buf, g_ske_ctx->block_bytes, 1);
		}
		else if(SKE_MODE_OFB == g_ske_mode)
		{
			uint32_copy(g_ske_iv_buf, tmp_iv, g_ske_ctx->block_words);
		}
		else if((SKE_MODE_CBC == g_ske_mode) || (SKE_MODE_CFB == g_ske_mode))
		{
			if(SKE_CRYPTO_ENCRYPT == g_ske_crypto_action)
			{
				uint32_copy(g_ske_iv_buf, tmp_out, g_ske_ctx->block_words);
			}
			else
			{
				uint32_copy(g_ske_iv_buf, tmp_in, g_ske_ctx->block_words);
			}
		}
		else
		{;}

		//output
		if(out)
		{
			memcpy_(out, tmp_out, g_ske_ctx->block_bytes);
			out += g_ske_ctx->block_bytes;
		}
		else
		{;}

		in += g_ske_ctx->block_bytes;
	}

END:

	if(SKE_ERROR == ret)
	{
		uint32_clear(g_ske_key_buf, sizeof(g_ske_key_buf)/4);
		uint32_clear(g_ske_iv_buf, sizeof(g_ske_iv_buf)/4);
		if(p_out)
		{
			memset_(p_out, 0, bytes);
		}
		else
		{;}
	}
	else
	{;}

	return ret;
}
#endif


/* function: ske_lp encryption or decryption(CPU style)
 * parameters:
 *     in ------------------------- input, plaintext or ciphertext
 *     out ------------------------ output, ciphertext or plaintext
 *     bytes ---------------------- input, byte length of input or output.
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is designed for ECB/CBC/CFB/OFB/CTR/XTS modes, and input/output unit must be a block
 *     2. to save memory, in and out could be the same buffer, in this case, the output will
 *        cover the input.
 *     3. bytes must be a multiple of block byte length.
 */
uint32_t ske_lp_update_blocks(uint8_t *in, uint8_t *out, uint32_t bytes)
{
	if((NULL == in) || (NULL == out))
	{
		return SKE_BUFFER_NULL;
	}
	else if(bytes & (g_ske_ctx->block_bytes - 1))
	{
		return SKE_INPUT_INVALID;
	}
	else if (0 == bytes)
	{
		return SKE_SUCCESS;
	}
	else
	{;}

#if (defined(SUPPORT_SKE_TDES_128))
	if((SKE_ALG_TDES_128 == g_ske_alg) || (SKE_ALG_TDES_192 == g_ske_alg) ||
			(SKE_ALG_TDES_EEE_128 == g_ske_alg) || (SKE_ALG_TDES_EEE_192 == g_ske_alg))
	{
		return ske_tdes_update_blocks(in, out, bytes);
	}
	else
	{;}
#endif

	return ske_lp_update_blocks_internal(g_ske_ctx, in, out, bytes);
}


/* function: ske_lp finish
 * parameters: none
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. if encryption or decryption is done, please call this(optional)
 */
uint32_t ske_lp_final(void)
{
	memset_(g_ske_ctx, 0, sizeof(SKE_CTX));

#if (defined(SUPPORT_SKE_TDES_128))
	g_ske_alg = SKE_ALG_DES;
	g_ske_crypto_action = SKE_CRYPTO_ENCRYPT;
	g_ske_mode = SKE_MODE_ECB;
	uint32_clear(g_ske_key_buf, sizeof(g_ske_key_buf)/4);
	uint32_clear(g_ske_iv_buf, sizeof(g_ske_iv_buf)/4);
#endif

	return SKE_SUCCESS;
}


/* function: ske_lp encrypting or decrypting(CPU style, one-off style)
 * parameters:
 *     alg ------------------------ input, ske_lp algorithm
 *     mode ----------------------- input, ske_lp algorithm operation mode, like ECB,CBC,OFB,etc.
 *     crypto --------------------- input, encrypting or decrypting
 *     key ------------------------ input, key in bytes
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes, must be a block
 *     in ------------------------- input, plaintext or ciphertext
 *     out ------------------------ output, ciphertext or plaintext
 *     bytes ---------------------- input, byte length of input or output.
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. if mode is ECB, then there is no iv, in this case iv could be NULL
 *     2. this function is designed for ECB/CBC/CFB/OFB/CTR/XTS modes, and input/output unit is a block
 *     3. if key is from user input, please make sure key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 *     4. to save memory, in and out could be the same buffer, in this case, the output will
 *        cover the input.
 *     5. bytes must be a multiple of block byte length.
 */
uint32_t ske_lp_crypto(SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint8_t *in, uint8_t *out, uint32_t bytes)
{
	uint32_t ret;

	ske_lp_set_cpu_mode();
#if defined(SUPPORT_SKE_MODE_XTS)
	ske_lp_set_c_len_uint32(0);  //just for XTS mode
#endif

	ret = ske_lp_init_internal(g_ske_ctx, alg, mode, crypto, key, sp_key_idx, iv, SKE_LP_DMA_DISABLE);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{
		return ske_lp_update_blocks(in, out, bytes);
	}
}


uint32_t ske_lp_update_blocks_no_output_(SKE_CTX *ctx, uint8_t *in, uint32_t bytes)
{
#if (defined(SUPPORT_SKE_TDES_128))
	if((SKE_ALG_TDES_128 == g_ske_alg) || (SKE_ALG_TDES_192 == g_ske_alg) ||
			(SKE_ALG_TDES_EEE_128 == g_ske_alg) || (SKE_ALG_TDES_EEE_192 == g_ske_alg))
	{
		return ske_tdes_update_blocks(in, NULL, bytes);
	}
	else
	{;}
#endif

	return ske_lp_update_blocks_no_output(ctx, in, bytes);
}


uint32_t ske_lp_update_blocks_internal_(SKE_CTX *ctx, uint8_t *in, uint8_t *out, uint32_t bytes)
{
#if (defined(SUPPORT_SKE_TDES_128))
	if((SKE_ALG_TDES_128 == g_ske_alg) || (SKE_ALG_TDES_192 == g_ske_alg) ||
			(SKE_ALG_TDES_EEE_128 == g_ske_alg) || (SKE_ALG_TDES_EEE_192 == g_ske_alg))
	{
		return ske_tdes_update_blocks(in, out, bytes);
	}
	else
	{;}
#endif

	return ske_lp_update_blocks_internal(ctx, in, out, bytes);
}


#ifdef SKE_LP_DMA_FUNCTION
/* function: ske_lp init config(DMA style)
 * parameters:
 *     alg ------------------------ input, ske_lp algorithm
 *     mode ----------------------- input, ske_lp algorithm operation mode, like ECB,CBC,OFB,etc.
 *     crypto --------------------- input, encrypting or decrypting
 *     key ------------------------ input, key in bytes, must be a block
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. if mode is ECB, then there is no iv, in this case iv could be NULL
 *     2. this function is designed for ECB/CBC/CFB/OFB/CTR/XTS modes, and input/output unit is a block
 *     3. if key is from user input, please make sure key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 */
uint32_t ske_lp_dma_init(SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv)
{
	ske_lp_set_cpu_mode();
#if defined(SUPPORT_SKE_MODE_XTS)
	ske_lp_set_c_len_uint32(0);  //just for XTS mode
#endif

	return ske_lp_init_internal(g_ske_ctx, alg, mode, crypto, key, sp_key_idx, iv, SKE_LP_DMA_ENABLE);
}


/* function: ske_lp encryption or decryption(DMA style)
 * parameters:
 *     in ------------------------- input, plaintext or ciphertext
 *     out ------------------------ output, ciphertext or plaintext
 *     words ---------------------- input, word length of input or output, must be multiples of block length
 *     callback ------------------- callback function pointer, this could be NULL, means doing nothing
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. this function is designed for ECB/CBC/CFB/OFB/CTR/XTS modes, and input/output unit is a block
 *     2. to save memory, in and out could be the same buffer, in this case, the output will
 *        cover the input.
 *     3. words must be a multiple of block word length.
 */
uint32_t ske_lp_dma_update_blocks(uint32_t *in, uint32_t *out, uint32_t words, SKE_CALLBACK callback)
{
	if(0 == words)
	{
		return SKE_SUCCESS;
	}
	else if(words & (g_ske_ctx->block_words - 1))
	{
		return SKE_INPUT_INVALID;
	}
	else
	{
		return ske_lp_dma_operate(g_ske_ctx, in, out, words, words, callback);
	}
}


/* function: ske_lp finish(DMA style)
 * parameters: none
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. if encryption or decryption is done, please call this(optional)
 */
uint32_t ske_lp_dma_final(void)
{
	memset_(g_ske_ctx, 0, sizeof(SKE_CTX));

	return SKE_SUCCESS;
}


/* function: ske_lp encrypting or decrypting(DMA style, one-off style)
 * parameters:
 *     alg ------------------------ input, ske_lp algorithm
 *     mode ----------------------- input, ske_lp algorithm operation mode, like ECB,CBC,OFB,etc.
 *     crypto --------------------- input, encrypting or decrypting
 *     key ------------------------ input, key in bytes
 *     sp_key_idx ----------------- input, index of secure port key, (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX],
 *                                  if the MSB(sp_key_idx) is 1, that means using low 128bit of the 256bit key
 *     iv ------------------------- input, iv in bytes, must be a block
 *     in ------------------------- input, plaintext or ciphertext
 *     out ------------------------ output, ciphertext or plaintext
 *     words ---------------------- input, word length of input or output.
 *     callback ------------------- callback function pointer, this could be NULL, means do nothing
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. if mode is ECB, then there is no iv, in this case iv could be NULL
 *     2. this function is designed for ECB/CBC/CFB/OFB/CTR/XTS modes, and input/output unit is a block
 *     3. if key is from user input, please make sure key is not NULL(now sp_key_idx is useless),
 *        otherwise, key is from secure port, and (sp_key_idx & 0x7FFF) must be in [1,SKE_MAX_KEY_IDX]
 *     4. to save memory, in and out could be the same buffer, in this case, the output will
 *        cover the input.
 *     5. words must be a multiple of block word length.
 */
uint32_t ske_lp_dma_crypto(SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint32_t *in, uint32_t *out, uint32_t words, SKE_CALLBACK callback)
{
	uint32_t ret;

	ret = ske_lp_dma_init(alg, mode, crypto, key, sp_key_idx, iv);
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	return ske_lp_dma_update_blocks(in, out, words, callback);
}
#endif
