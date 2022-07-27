#include <stdio.h>

#include "ske_basic.h"
#include "../crypto_common/utility.h"
#include "../crypto_include/trng.h"



//ske_lp register pointer
volatile static ske_lp_reg_t * const g_ske_lp_reg = (ske_lp_reg_t *)(SKE_LP_BASE_ADDR);



/* function: get ske IP version
 * parameters: none
 * return: ske IP version
 * caution:
 */
uint32_t ske_lp_get_version(void)
{
	return g_ske_lp_reg->ske_version;
}


/* function: set ske_lp to be CPU mode
 * parameters: none
 * return: none
 * caution:
 *     1. for ske_lp, make up_cfg high, to input key(for dma too)
 */
void ske_lp_set_cpu_mode(void)
{
	volatile uint32_t flag = (((uint32_t)1)<<SKE_LP_UP_CFG_OFFSET);
	volatile uint32_t mask = ~(((uint32_t)1)<<SKE_LP_DMA_OFFSET);

	g_ske_lp_reg->cfg &= mask;
	g_ske_lp_reg->cfg |= flag;
}


/* function: set ske_lp to be DMA mode
 * parameters: none
 * return: none
 * caution:
 *    1. after calling this function, please make up_cfg low
 */
void ske_lp_set_dma_mode(void)
{
	volatile uint32_t flag = (((uint32_t)1)<<SKE_LP_DMA_OFFSET);
//	volatile uint32_t mask = ~(((uint32_t)1)<<SKE_LP_UP_CFG_OFFSET);

	g_ske_lp_reg->cfg |= flag;
//	g_ske_lp_reg->cfg &= mask;
}


/* function: set the ske_lp endian
 * parameters: none
 * return: none
 * caution:
 *     1. actually, this config works for only CPU mode now
 */
void ske_lp_set_endian_uint32(void)
{
	volatile uint32_t mask = ~(((uint32_t)3)<<SKE_LP_REVERSE_BYTE_ORDER_IN_WORD_OFFSET);
#ifndef SKE_LP_CPU_BIG_ENDIAN
	volatile uint32_t flag = (((uint32_t)2)<<SKE_LP_REVERSE_BYTE_ORDER_IN_WORD_OFFSET);
#endif

	g_ske_lp_reg->cfg &= mask;    //clear bit[25:24], and now requires CPU is big-endian
#ifndef SKE_LP_CPU_BIG_ENDIAN
	g_ske_lp_reg->cfg |= flag;    //requires CPU is little-endian, input and output reversed by hardware----ske IP
#endif
}


/* function: set ske_lp encrypting or decrypting
 * parameters:
 *     crypto --------------------- input, SKE_CRYPTO_ENCRYPT or SKE_CRYPTO_DECRYPT
 * return: none
 * caution:
 *     1. please make sure crypto is valid
 */
void ske_lp_set_crypto(SKE_CRYPTO crypto)
{
	volatile uint32_t mask = ~(((uint32_t)1)<<SKE_LP_CRYPTO_OFFSET);

	g_ske_lp_reg->cfg &= mask;
	g_ske_lp_reg->cfg |= (((uint32_t)crypto) << SKE_LP_CRYPTO_OFFSET);
}


/* function: set ske_lp alg
 * parameters:
 *     ske_alg -------------------- input, ske_lp algorithm
 * return: none
 * caution:
 *     1. please make sure ske_alg is valid
 */
void ske_lp_set_alg(SKE_ALG ske_alg)
{
	volatile uint32_t mask = ~(0x0000000F);
	uint32_t cfg;

	switch(ske_alg)
	{
#ifdef SUPPORT_SKE_DES
	case SKE_ALG_DES:
		cfg = 3;
		break;
#endif

#ifdef SUPPORT_SKE_AES_128
	case SKE_ALG_AES_128:
		cfg = 1;
		break;
#endif

#ifdef SUPPORT_SKE_AES_192
	case SKE_ALG_AES_192:
		cfg = 4;
		break;
#endif

#ifdef SUPPORT_SKE_AES_256
	case SKE_ALG_AES_256:
		cfg = 5;
		break;
#endif

#ifdef SUPPORT_SKE_SM4
	case SKE_ALG_SM4:
		cfg = 2;
		break;
#endif

	default:
		cfg = 2;  //default alg SM4
	}

	g_ske_lp_reg->cfg &= mask;		// clear bit[3:0]
	g_ske_lp_reg->cfg |= cfg;		// set ske_lp alg cfg
}


/* function: set ske_lp alg operation mode
 * parameters:
 *     mode ----------------------- input, operation mode
 * return: none
 * caution:
 *     1. please make sure mode is valid
 */
void ske_lp_set_mode(SKE_MODE mode)
{
	volatile uint32_t mask = ~(0x0000000F << SKE_LP_MODE_OFFSET);

	g_ske_lp_reg->cfg &= mask;        							//clear bit [31:28]
	g_ske_lp_reg->cfg |= (((uint32_t)mode) << SKE_LP_MODE_OFFSET);         	//set mode
}


/* function: set whether ske_lp current input data is the last data or not
 * parameters:
 *     is_last_block -------------- input, 0:no, other:yes
 * return: none
 * caution:
 *     1. just for CMAC/CCM/GCM/XTS mode
 */
void ske_lp_set_last_block(uint32_t is_last_block)
{
	volatile uint32_t flag = (((uint32_t)1)<<SKE_LP_LAST_DATA_OFFSET);
	volatile uint32_t mask = ~(((uint32_t)1)<<SKE_LP_LAST_DATA_OFFSET);

	if(is_last_block)
	{
		g_ske_lp_reg->m_din_cr |= flag;
	}
	else
	{
		g_ske_lp_reg->m_din_cr &= mask;
	}
}


/* function: set ske_lp current input data bit length
 * parameters:
 *     bytes ---------------------- input, byte length of current input data
 * return: none
 * caution:
 *     1. just for CMAC

void ske_lp_set_last_block_len(uint32_t bytes)
{
	volatile uint32_t mask = ~0x000000FF;

	g_ske_lp_reg->m_din_cr &= mask;
	g_ske_lp_reg->m_din_cr |= (bytes<<3);
} */


/* function: ske_lp start to expand key or calc
 * parameters:none
 * return: none
 * caution:
 */
void ske_lp_start(void)
{
	volatile uint32_t start_flag = 1;

	g_ske_lp_reg->ctrl |= start_flag;
}


/* function: wait till ske_lp calculating is done
 * parameters:
 * return: none
 * caution:
 */
uint32_t ske_lp_wait_till_done(void)
{
	volatile uint32_t finish_flag = 1;
	volatile uint32_t clear_flag = 0;

	while(!(g_ske_lp_reg->sr2 & finish_flag))
	{;}

	g_ske_lp_reg->sr2 = clear_flag;  //write 0 to clear

	return SKE_SUCCESS;
}


/* function: set ske_lp key
 * parameters:
 *     key ------------------------ input, key in word buffer
 *     idx ------------------------ input, key index, only 1 and 2 are valid
 *     key_words ------------------ input, word length of key
 * return: none
 * caution:
 *     1. if idx is 1, set key1 register, else if idx is 2, set key2 register, please
 *        make sure idx is valid
 */
void ske_lp_set_key_uint32(uint32_t *key, uint32_t idx, uint32_t key_words)
{
	volatile uint32_t *key_reg = g_ske_lp_reg->key1;
	int32_t i;

#if 0
	for(i = 0; i < key_words; i++)
	{
		key_reg[i] = key[i];//printf("\r\nkey %08x", key_reg[i]);
	}
#else
	if(2 == key_words)      //for DES
	{
		key_reg[2] = key[0];
		key_reg[3] = key[1];
	}
	else                    //for AES/SM4
	{
		for(i = 0; i < key_words; i++)
		{
			key_reg[i] = key[i];
		}
	}
#endif
}


/* function: set ske_lp iv
 * parameters:
 *     iv ------------------------- input, iv in word buffer
 *     block_words ---------------- input, word length of ske_lp block
 * return: none
 * caution:
 *     1. please make sure the three parameters are valid
 */
void ske_lp_set_iv_uint32(uint32_t *iv, uint32_t block_words)
{
#if 0
	int32_t i;

	for(i = 0; i < block_words; i++)
	{
		g_ske_lp_reg->iv[i] = iv[i];
	}
#else
	if(4 == block_words)      //for AES/SM4
	{
		g_ske_lp_reg->iv[0] = iv[0];
		g_ske_lp_reg->iv[1] = iv[1];
		g_ske_lp_reg->iv[2] = iv[2];
		g_ske_lp_reg->iv[3] = iv[3];
	}
	else                      //for DES
	{
		g_ske_lp_reg->iv[2] = iv[0];
		g_ske_lp_reg->iv[3] = iv[1];
	}
#endif
}


#if (defined(SUPPORT_SKE_MODE_GCM) || defined(SUPPORT_SKE_MODE_CCM))
/* function: set aad bits(just for ske_lp ccm/gcm mode)
 * parameters:
 *     aad_bytes ------------------ input, byte length of aad
 * return: none
 * caution:
 *     1. this function is just for CCM/GCM mode
 */
void ske_lp_set_aad_len_uint32(uint32_t aad_bytes)
{
	g_ske_lp_reg->ske_a_len_l = ((aad_bytes)<<3)&0xFFFFFFFF;
	g_ske_lp_reg->ske_a_len_h = aad_bytes>>(32-3);
}
#endif


#if (defined(SUPPORT_SKE_MODE_GCM) || defined(SUPPORT_SKE_MODE_CCM) || defined(SUPPORT_SKE_MODE_XTS))
/* function: set plaintext/ciphertext bits(just for ske_lp ccm/gcm/xts mode)
 * parameters:
 *     c_bytes -------------------- input, byte length of plaintext/ciphertext
 * return: none
 * caution:
 *     1. this function is just for CCM/GCM/XTS mode
 */
void ske_lp_set_c_len_uint32(uint32_t c_bytes)
{
	g_ske_lp_reg->ske_c_len_l = ((c_bytes)<<3)&0xFFFFFFFF;
	g_ske_lp_reg->ske_c_len_h = c_bytes>>(32-3);
}
#endif


/* function: input one block
 * parameters:
 *     in ------------------------- input, plaintext or ciphertext in word buffer
 *     block_words ---------------- input, word length of ske_lp block
 * return: none
 * caution:
 *     1. in is a word buffer of only one block.
 */
void ske_lp_simple_set_input_block(uint32_t *in, uint32_t block_words)
{
#if 0
	uint32_t i;

	for(i = 0; i < block_words; i++)
	{
		g_ske_lp_reg->m_din[i] = in[i];
	}
#else
	if(4 == block_words)      //for AES/SM4
	{
		g_ske_lp_reg->m_din[0] = in[0];
		g_ske_lp_reg->m_din[1] = in[1];
		g_ske_lp_reg->m_din[2] = in[2];
		g_ske_lp_reg->m_din[3] = in[3];
	}
	else                      //for DES
	{
		g_ske_lp_reg->m_din[2] = in[0];
		g_ske_lp_reg->m_din[3] = in[1];
	}
#endif
}


/* function: output one block
 * parameters:
 *     out ------------------------ output, one block output of ske_lp in word buffer
 *     block_words ---------------- input, word length of ske_lp block
 * return: none
 * caution:
 */
void ske_lp_simple_get_output_block(uint32_t *out, uint32_t block_words)
{
#if 0
	uint32_t i;

	for(i = 0; i < block_words; i++)
	{
		out[i] = g_ske_lp_reg->m_dout[i];
	}
#else
	if(4 == block_words)      //for AES/SM4
	{
		out[0] = g_ske_lp_reg->m_dout[0];
		out[1] = g_ske_lp_reg->m_dout[1];
		out[2] = g_ske_lp_reg->m_dout[2];
		out[3] = g_ske_lp_reg->m_dout[3];
	}
	else                      //for DES
	{
		out[0] = g_ske_lp_reg->m_dout[2];
		out[1] = g_ske_lp_reg->m_dout[3];
	}
#endif
}


/* function: ske_lp expand key
 * parameters:
 *     dma_en --------------------- input, for DMA mode(not 0) or not(0)
 * return: SKE_SUCCESS(success), other(error)
 * caution:  1. must be called after ske_lp_set_crypto() and ske_lp_set_alg(), and the key is set already.
 */
uint32_t ske_lp_expand_key(uint32_t dma_en)
{
	volatile uint32_t mask = ~(((uint32_t)1)<<SKE_LP_UP_CFG_OFFSET);
	volatile uint32_t flag = (((uint32_t)1)<<SKE_LP_UP_CFG_OFFSET);
	uint32_t ret;

	//update cfg
	g_ske_lp_reg->cfg |= flag;

	//expand key
	ske_lp_start();

	ret = ske_lp_wait_till_done();
	if(SKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//not update cfg
	if (SKE_LP_DMA_ENABLE == dma_en)
	{
		ske_lp_set_dma_mode();
	}
	else
	{;}

	g_ske_lp_reg->cfg &= mask;

	return SKE_SUCCESS;
}


/************************* DMA *************************/

#ifdef SKE_LP_DMA_FUNCTION
/* function: wait till ske_lp dma calculating is done
 * parameters:
 *     callback ------------------- callback function pointer, this could be NULL, means doing nothing
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 */
uint32_t ske_lp_dma_calc_wait_till_done(SKE_CALLBACK callback)
{
	volatile uint32_t finish_flag = 1;
	volatile uint32_t clear_flag = 0;

#ifdef SUPPORT_SKE_IRQ
	volatile uint32_t flag_irq = (((uint32_t)1) << SKE_LP_IRQ_OFFSET);

	if(ske_lp_reg->cfg & flag_irq)
	{
		return SKE_SUCCESS;
	}
	else
	{;}
#endif

	while(!(g_ske_lp_reg->sr2 & finish_flag))
	{
		if(callback)
		{
	    	callback();
	    }
		else
		{;}
	}

	g_ske_lp_reg->sr2 = clear_flag;

	return SKE_SUCCESS;
}


/* function: basic ske_lp DMA operation
 * parameters:
 *     ctx ------------------------ input, SKE_CTX context pointer
 *     in ------------------------- input, plaintext or ciphertext
 *     out ------------------------ output, ciphertext or plaintext
 *     in_words ------------------- input, word length of in, must be multiples of block word length
 *     out_words ------------------ input, word length of out, must be multiples of block word length
 *     callback ------------------- callback function pointer, this could be NULL, means doing nothing
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. in_words & out_words must be multiples of block words.
 *     2. it could be without output, namely, out can be NULL, out_words can be 0(for input AAD, or CBC_MAC/CMAC mode)
 */
uint32_t ske_lp_dma_operate(SKE_CTX *ctx, uint32_t *in, uint32_t *out, uint32_t in_words, uint32_t out_words,
		SKE_CALLBACK callback)
{
	if(NULL == in)
	{
		return SKE_BUFFER_NULL;
	}
	else if (0 == in_words)
	{
		return SKE_SUCCESS;
	}
	else
	{;}

	//src & dst addr
	g_ske_lp_reg->dma_sa_l = (uint32_t)in;
	g_ske_lp_reg->dma_da_l = (uint32_t)out;

	//data word length
	g_ske_lp_reg->dma_rlen = in_words<<2;
	g_ske_lp_reg->dma_wlen = out_words<<2;

	ske_lp_start();

	return ske_lp_dma_calc_wait_till_done(callback);
}


/* function: clear the last (16-bytes) of the block in(16 bytes)
 * parameters:
 *     in ------------------------- input, one block buffer(128bits, for AES/SM4 GCM, CCM mode)
 *     bytes ---------------------- input, real bytes of in, must be in[1,16]
 * return: none
 * caution:
 *     1. this function is for GCM,CCM mode of DMA.
 */
void clear_block_tail(uint32_t in[4], uint32_t bytes)
{
	uint32_t i;

	i = bytes/4;
	bytes &= 3;

	if(bytes)
	{
#ifdef SKE_LP_CPU_BIG_ENDIAN
		in[i] &= 0xFFFFFFFF<<(32-bytes*8);
#else
		in[i] &= (1<<(bytes*8)) - 1;
#endif
		i++;
	}

	while(i < 4)
	{
		in[i++]=0;
	}
}
#endif


/* function: update ske_lp some blocks without output
 * parameters:
 *     ctx ------------------------ input, SKE_CTX context pointer
 *     in ------------------------- input, some blocks
 *     bytes ---------------------- input, byte length of in
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the bytes is a multiple of block byte length ctx->block_bytes
 *     2. this function is called by CCM(input aad)/GCM(input aad)/CMAC/CBC-MAC mode
 */
uint32_t ske_lp_update_blocks_no_output(SKE_CTX *ctx, uint8_t *in, uint32_t bytes)
{
	uint32_t in_word_align;
	uint32_t tmp_in[4];
	uint32_t i;
	uint32_t ret;

	if(((uint32_t)in) & 3)
	{
		in_word_align = 0;
	}
	else
	{
		in_word_align = 1;
	}

	//input one block ---> calculating ---> output one block
	for (i = 0; i < bytes; i += ctx->block_bytes)
	{
		if(in_word_align)
		{
			ske_lp_simple_set_input_block((uint32_t *)in, ctx->block_words);
		}
		else
		{
			memcpy_(tmp_in, in, ctx->block_bytes);
			ske_lp_simple_set_input_block((uint32_t *)tmp_in, ctx->block_words);
		}

		ske_lp_start();

		ret = ske_lp_wait_till_done();
		if(SKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{;}

		in += ctx->block_bytes;
	}

	return SKE_SUCCESS;
}


/* function: update ske_lp some blocks and get the same number of blocks
 * parameters:
 *     ctx ------------------------ input, SKE_CTX context pointer
 *     in ------------------------- input, some blocks
 *     out ------------------------ output, the same number of blocks;
 *     bytes ---------------------- input, byte length of in
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the bytes is a multiple of block byte length ctx->block_bytes
 */
uint32_t ske_lp_update_blocks_internal(SKE_CTX *ctx, uint8_t *in, uint8_t *out, uint32_t bytes)
{
	uint32_t in_word_align, out_word_align;
	uint32_t tmp_in[4];
	uint32_t i, round = bytes/ctx->block_bytes;
	uint32_t block_bytes = ctx->block_bytes;
	uint32_t ret;

	if(((uint32_t)in) & 3)
	{
		in_word_align = 0;
	}
	else
	{
		in_word_align = 1;
	}

	if(((uint32_t)out) & 3)
	{
		out_word_align = 0;
	}
	else
	{
		out_word_align = 1;
	}

	if(in_word_align && out_word_align)
	{
#if 1
		if(block_bytes == 16)       //for AES/SM4
		{
			for (i = 0 ; i < round; i++)
			{
				//ske_lp_simple_set_input_block((uint32_t *)in, ctx->block_words);
				g_ske_lp_reg->m_din[0] = ((uint32_t *)in)[0];
				g_ske_lp_reg->m_din[1] = ((uint32_t *)in)[1];
				g_ske_lp_reg->m_din[2] = ((uint32_t *)in)[2];
				g_ske_lp_reg->m_din[3] = ((uint32_t *)in)[3];

				ske_lp_start();

				ret = ske_lp_wait_till_done();
				if(SKE_SUCCESS != ret)
				{
					return ret;
				}
				else
				{;}

				//ske_lp_simple_get_output_block((uint32_t *)out, ctx->block_words);
				((uint32_t *)out)[0] = g_ske_lp_reg->m_dout[0];
				((uint32_t *)out)[1] = g_ske_lp_reg->m_dout[1];
				((uint32_t *)out)[2] = g_ske_lp_reg->m_dout[2];
				((uint32_t *)out)[3] = g_ske_lp_reg->m_dout[3];

				in += block_bytes;
				out += block_bytes;
			}
		}
		else                        //for DES/3DES
		{
			for (i = 0; i < round; i++)
			{
				//ske_lp_simple_set_input_block((uint32_t *)in, ctx->block_words);
				g_ske_lp_reg->m_din[2] = ((uint32_t *)in)[0];
				g_ske_lp_reg->m_din[3] = ((uint32_t *)in)[1];

				ske_lp_start();

				ret = ske_lp_wait_till_done();
				if(SKE_SUCCESS != ret)
				{
					return ret;
				}
				else
				{;}

				//ske_lp_simple_get_output_block((uint32_t *)out, ctx->block_words);
				((uint32_t *)out)[0] = g_ske_lp_reg->m_dout[2];
				((uint32_t *)out)[1] = g_ske_lp_reg->m_dout[3];

				in += block_bytes;
				out += block_bytes;
			}
		}
#else
		for (i = 0 ; i < round; i++)
		{
			ske_lp_simple_set_input_block((uint32_t *)in, ctx->block_words);//print_buf_U32((uint32_t *)in_tmp, ctx->block_words, "in");

			ske_lp_start();

			ret = ske_lp_wait_till_done();
			if(SKE_SUCCESS != ret)
			{
				return ret;
			}
			else
			{;}

			ske_lp_simple_get_output_block((uint32_t *)out, ctx->block_words);//print_buf_U32((uint32_t *)out_tmp, ctx->block_words, "out");

			in += block_bytes;
			out += block_bytes;
		}
#endif
	}
	else
	{
		for (i = 0; i < round; i++)
		{
			if(in_word_align)
			{
				ske_lp_simple_set_input_block((uint32_t *)in, ctx->block_words);
			}
			else
			{
				memcpy_(tmp_in, in, block_bytes);
				ske_lp_simple_set_input_block((uint32_t *)tmp_in, ctx->block_words);
			}

			ske_lp_start();

			ret = ske_lp_wait_till_done();
			if(SKE_SUCCESS != ret)
			{
				return ret;
			}
			else
			{;}

			if(out_word_align)
			{
				ske_lp_simple_get_output_block((uint32_t *)out, ctx->block_words);
			}
			else
			{
				ske_lp_simple_get_output_block((uint32_t *)tmp_in, ctx->block_words);
				memcpy_(out, tmp_in, block_bytes);
			}

			in += block_bytes;
			out += block_bytes;
		}
	}

	return SKE_SUCCESS;
}


#ifdef SUPPORT_SKE_MODE_GMAC
/* function: for GMAC mode to input message blocks(just for AES/SM4, block size is 16 bytes)
 * parameters:
 *     in ------------------------- input, some blocks
 *     bytes ---------------------- input, byte length of in
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the bytes is a multiple of block byte length 16
 *     2. this function is like ske_lp_update_blocks_internal(), but discard output
 */
uint32_t ske_lp_gmac_update_blocks_internal(uint8_t *in, uint32_t bytes)
{
	uint32_t tmp[4];
	uint32_t i, round = bytes/16;
	uint32_t ret;

	if(0 ==(((uint32_t)in)&3))
	{
		for (i = 0; i < round; i++)
		{
			//ske_lp_simple_set_input_block((uint32_t *)in, ctx->block_words);
			g_ske_lp_reg->m_din[0] = ((uint32_t *)in)[0];
			g_ske_lp_reg->m_din[1] = ((uint32_t *)in)[1];
			g_ske_lp_reg->m_din[2] = ((uint32_t *)in)[2];
			g_ske_lp_reg->m_din[3] = ((uint32_t *)in)[3];

			ske_lp_start();

			ret = ske_lp_wait_till_done();
			if(SKE_SUCCESS != ret)
			{
				return ret;
			}
			else
			{;}

//			*tmp = g_ske_lp_reg->m_dout[0];
//			*tmp = g_ske_lp_reg->m_dout[1];
//			*tmp = g_ske_lp_reg->m_dout[2];
//			*tmp = g_ske_lp_reg->m_dout[3];

			in += 16;
		}
	}
	else
	{
		//input one block ---> calculating ---> output one block
		for (i = 0; i < round; i++)
		{
			memcpy_(tmp, in, 16);
			ske_lp_simple_set_input_block((uint32_t *)tmp, 4);

			ske_lp_start();

			ret = ske_lp_wait_till_done();
			if(SKE_SUCCESS != ret)
			{
				return ret;
			}
			else
			{;}

//			ske_lp_simple_get_output_block((uint32_t *)tmp, 4);

			in += 16;
		}
	}

	return SKE_SUCCESS;
}
#endif


#if (defined(SUPPORT_SKE_TDES_128))
/* function: TDES input one block and output one block
 * parameters:
 *     is_EEE --------------------- input, is tdes SKE_ALG_TDES_EEE_128/SKE_ALG_TDES_EEE_192 or not
 *     key ------------------------ input, TDES key, 24 bytes
 *     crypto --------------------- input, SKE_CRYPTO_ENCRYPT or SKE_CRYPTO_DECRYPT
 *     in ------------------------- input, one block
 *     out ------------------------ output, one block
 * return: SKE_SUCCESS(success), other(error)
 * caution:
 *     1. hw DES must be set already
 *     2. hw ECB must be set already
 */
uint32_t tdes_ecb_update_one_block(uint32_t is_EEE, uint32_t key[6], SKE_CRYPTO crypto, uint32_t in[2], uint32_t out[2])
{
	uint32_t ret;

	/***************** round 1 *****************/
	ske_lp_set_cpu_mode();//to update cfg
	ske_lp_set_crypto(crypto);

	ske_lp_set_key_uint32((SKE_CRYPTO_ENCRYPT == crypto)?key:key+4, 1, 2);
	ske_lp_expand_key(SKE_LP_DMA_DISABLE);

	g_ske_lp_reg->m_din[2] = in[0];
	g_ske_lp_reg->m_din[3] = in[1];

	ske_lp_start();
	ret = ske_lp_wait_till_done();
	if(SKE_SUCCESS != ret)
	{
		goto END;
	}
	else
	{;}

	/***************** round 2 *****************/
	ske_lp_set_cpu_mode();//to update cfg
	if(!is_EEE)
	{
		ske_lp_set_crypto((SKE_CRYPTO_ENCRYPT == crypto)?SKE_CRYPTO_DECRYPT:SKE_CRYPTO_ENCRYPT);
	}
	else
	{;}

	ske_lp_set_key_uint32(key+2, 1, 2);
	ske_lp_expand_key(SKE_LP_DMA_DISABLE);

	g_ske_lp_reg->m_din[2] = g_ske_lp_reg->m_dout[2];
	g_ske_lp_reg->m_din[3] = g_ske_lp_reg->m_dout[3];

	ske_lp_start();
	ret = ske_lp_wait_till_done();
	if(SKE_SUCCESS != ret)
	{
		goto END;
	}
	else
	{;}

	/***************** round 3 *****************/
	ske_lp_set_cpu_mode();//to update cfg
	if(!is_EEE)
	{
		ske_lp_set_crypto(crypto);
	}
	else
	{;}

	ske_lp_set_key_uint32((SKE_CRYPTO_ENCRYPT == crypto)?key+4:key, 1, 2);
	ske_lp_expand_key(SKE_LP_DMA_DISABLE);

	g_ske_lp_reg->m_din[2] = g_ske_lp_reg->m_dout[2];
	g_ske_lp_reg->m_din[3] = g_ske_lp_reg->m_dout[3];

	ske_lp_start();
	ret = ske_lp_wait_till_done();
	if(SKE_SUCCESS != ret)
	{
		goto END;
	}
	else
	{;}

	out[0] = g_ske_lp_reg->m_dout[2];
	out[1] = g_ske_lp_reg->m_dout[3];

	ret = SKE_SUCCESS;

END:

	return ret;
}
#endif

