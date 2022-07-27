#include <stdio.h>
#include "hash_basic.h"
#include "../crypto_common/utility.h"




//hash register pointer
volatile static HASH_REG * const g_hash_reg = (HASH_REG *)HASH_BASE_ADDR;


/* function: get HFE IP version
 * parameters: none
 * return: HFE IP version
 * caution:
 */
uint32_t hash_get_version(void)
{
	return g_hash_reg->HASH_VERSION;
}


/* function: set hash to be CPU mode
 * parameters: none
 * return: none
 * caution:
 */
void hash_set_cpu_mode(void)
{
	volatile uint32_t mask = ~(((uint32_t)1)<<HASH_DMA_OFFSET);

	g_hash_reg->HASH_CFG &= mask;
}


/* function: set hash to be DMA mode
 * parameters: none
 * return: none
 * caution:
 */
void hash_set_dma_mode(void)
{
	volatile uint32_t flag = (((uint32_t)1)<<HASH_DMA_OFFSET);

	g_hash_reg->HASH_CFG |= flag;
}


/* function: set the specific hash algorithm
 * parameters:
 *     hash_alg ------------------- input, specific hash algorithm
 * return: none
 * caution: 
 *     1. please make sure hash_alg is valid
 */
void hash_set_alg(HASH_ALG hash_alg)
{
	volatile uint32_t mask = (~0x0000000F);

	g_hash_reg->HASH_CFG &= mask;
	g_hash_reg->HASH_CFG |= hash_alg;
}


/* function: enable hash interruption in CPU mode or DMA mode
 * parameters: none
 * return: none
 * caution: none
 */
void hash_enable_interruption(void)
{
	volatile uint32_t flag = (((uint32_t)1)<<HASH_INTERRUPTION_OFFSET);

	g_hash_reg->HASH_CFG |= flag;
}


/* function: disable hash interruption in CPU mode or DMA mode
 * parameters: none
 * return: none
 * caution: none
 */
void hash_disable_interruption(void)
{
	volatile uint32_t mask = ~(((uint32_t)1)<<HASH_INTERRUPTION_OFFSET);

	g_hash_reg->HASH_CFG &= mask;
}


/* function: set the tag whether current block is the last message block or not
 * parameters:
 *     tag ------------------------ input, 0(no), other(yes) 
 * return: none
 * caution: 
 *     1. if it is the last block, please config hash_reg->HASH_MSG_LEN,
 *        then the hardware will do the padding and post-processing.
 */
void hash_set_last_block(uint32_t tag)
{
	volatile uint32_t flag = (((uint32_t)1) << HASH_LAST_OFFSET);
	volatile uint32_t mask = (~(((uint32_t)1) << HASH_LAST_OFFSET));

	if(tag)     //current block is the last one of the message
	{
		g_hash_reg->HASH_CFG |= flag;
	}
	else 	    //current block is not the last one of the message
	{
		g_hash_reg->HASH_CFG &= mask;
	}
}


/* function: get current HASH iterator value
 * parameters:
 *     iterator ------------------- output, current hash iterator
 *     hash_iterator_words -------- input, iterator word length
 * return: none
 * caution:
 *     1.
 */
void hash_get_iterator(uint8_t *iterator, uint32_t hash_iterator_words)
{
	uint32_t temp;
	uint32_t i;

	if(((uint32_t)iterator) & 3) //for the case that iterator is not aligned by word
	{
		for (i = 0; i < hash_iterator_words; i++)
		{
			temp = g_hash_reg->HASH_OUT[i];
			memcpy_(iterator+(i<<2), &temp, 4);
		}
	}
	else
	{
		for (i = 0; i < hash_iterator_words; i++)
		{
			((uint32_t *)iterator)[i] = g_hash_reg->HASH_OUT[i];
		}
	}
}


/* function: input current iterator value
 * parameters:
 *     iterator ------------------- input, hash iterator value
 *     hash_iterator_words -------- input, iterator word length
 * return: none
 * caution:
 *     1. iterator must be word aligned
 */
void hash_set_iterator(uint32_t *iterator, uint32_t hash_iterator_words)
{
	uint32_t i;

	for (i = 0; i < hash_iterator_words; i++)
	{
		g_hash_reg->HASH_IN[i] = iterator[i];
	}
}


/* function: clear HASH_PCR_LEN
 * parameters:none
 * return: none
 * caution:none
 */
void hash_clear_msg_len(void)
{
	volatile uint32_t flag = 0;

	g_hash_reg->HASH_PCR_LEN[0] = flag;
	g_hash_reg->HASH_PCR_LEN[1] = flag;
	g_hash_reg->HASH_PCR_LEN[2] = flag;
	g_hash_reg->HASH_PCR_LEN[3] = flag;
}



/* function: set the total byte length of the whole message
 * parameters:
 *     msg_total_bytes ------------ input, total byte length of the whole message
 *     words ---------------------- input, word length of array msg_total_bytes
 * return: none
 * caution:
 *     1.
 */
void hash_set_msg_total_byte_len(uint32_t *msg_total_bytes, uint32_t words)
{
	while(words--)
	{
		g_hash_reg->HASH_PCR_LEN[words] = msg_total_bytes[words];
	}
}


/* function: set dma output bytes length
 * parameters:
 *     bytes ---------------------- input,  byte length of the written data for hash hardware
 * return: none
 * caution:
 *     1.
 */
void hash_set_dma_output_len(uint32_t bytes)
{
	g_hash_reg->DMA_WLEN = bytes;
}


/* function: start HASH iteration calc
 * parameters: none
 * return: none
 * caution:
 */
void hash_start(void)
{
	volatile uint32_t flag = 1;

	//while((g_hash_reg->HASH_SR1 & flag) == 1)
	//{;}

	g_hash_reg->HASH_SR2 |= flag;
	g_hash_reg->HASH_CTRL |= flag;

}


/* function: wait till done
 * parameters: none
 * return: none
 * caution:
 */
void hash_wait_till_done(void)
{
	volatile uint32_t flag = 1;

	while((g_hash_reg->HASH_SR2 & flag) == 0)
	{;}

	g_hash_reg->HASH_SR2 = flag;
}


/* function: DMA wait till done
 * parameters:
 *     callback ------------------- callback function pointer
 * return: none
 * caution:
 */
void hash_dma_wait_till_done(HASH_CALLBACK callback)
{
	volatile uint32_t flag = 1;

	while((g_hash_reg->HASH_SR2 & flag) == 0)
	{
		if(callback)
		{
			callback();
		}
		else
		{;}
	}

	g_hash_reg->HASH_SR2 = flag;
}


/* function: input message
 * parameters:
 *     msg ------------------------ input, message
 *     msg_words ------------------ input, word length of msg
 * return: none
 * caution:
 *     1. if msg does not contain the last block, please make sure msg_words is a multiple of the
 *        hash block word length.
 */
void hash_input_msg(uint8_t *msg, uint32_t msg_words)
{
	uint32_t tmp;
	uint32_t i;

	if(((uint32_t)msg) & 3)
	{
		for(i = 0; i < msg_words; i++)
		{
			memcpy_(&tmp, msg, 4);
			g_hash_reg->HASH_M_DIN[i] = tmp;
			msg += 4;
		}
	}
	else
	{
		for(i = 0; i < msg_words; i++)
		{
			g_hash_reg->HASH_M_DIN[i] = *((uint32_t *)msg);
			msg += 4;
		}
	}
}


#ifdef HASH_DMA_FUNCTION

/* function: basic HASH DMA operation
 * parameters:
 *     in ------------------------- input, message of some blocks, or message including the last byte(last block)
 *     out ------------------------ output, hash digest or hmac.
 *     inByteLen ------------------ input, actual byte length of input msg
 *     callback ------------------- callback function pointer
 * return: none
 * caution:
 *     1. for DMA operation, the unit of input and output is 4 words, so, please make sure the buffer
 *        out is sufficient.
 *     2. if just to input message, not to get digest or hmac, please set para out to be NULL and WLEN to be 0.
 *        if to get the digest or hmac, para out can not be NULL, and please set WLEN to be digest length.
 */
void hash_dma_operate(uint32_t *in, uint32_t *out, uint32_t inByteLen, HASH_CALLBACK callback)
{
	//src addr
	g_hash_reg->DMA_SA = ((uint32_t)in)&0xFFFFFFFF;

	//dst addr
	if(out)
	{
		g_hash_reg->DMA_DA = ((uint32_t)out)&0xFFFFFFFF;
	}
	else
	{;}

	//data byte length
	g_hash_reg->DMA_RLEN = inByteLen;

	hash_start();

	hash_dma_wait_till_done(callback);
}

#endif

