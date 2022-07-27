#ifndef HASH_H
#define HASH_H

#ifdef __cplusplus
extern "C" {
#endif


#include "../../crypto_hal/hash_basic.h"


//#define CONFIG_HASH_SUPPORT_MUL_THREAD


//HASH status
typedef struct {
    uint32_t busy             : 1;        // calculate busy flag
} hash_status_t;


//HASH context
typedef struct
{
	HASH_ALG hash_alg;                                //current hash algorithm
	uint8_t block_byte_len;
	uint8_t iterator_word_len;
	uint8_t digest_byte_len;
	hash_status_t status;                             //hash update status, .busy=1 means doing锛�=0 means idle
	uint8_t first_update_flag;                        //whether first time to update message(1:yes, 0:no)
	uint8_t finish_flag;                              //whether the whole message has been inputted(1:yes, 0:no)
	uint8_t hash_buffer[HASH_BLOCK_MAX_BYTE_LEN];     //block buffer
	uint32_t total[HASH_TOTAL_LEN_MAX_WORD_LEN];      //total byte length of the whole message

#ifdef CONFIG_HASH_SUPPORT_MUL_THREAD
	uint32_t iterator[HASH_ITERATOR_MAX_WORD_LEN];    //keep current hash iterator value for multiple thread
#endif
} HASH_CTX;



#ifdef HASH_DMA_FUNCTION
//HASH DMA context
typedef struct
{
	HASH_ALG hash_alg;                                //current hash algorithm
	uint32_t total[HASH_TOTAL_LEN_MAX_WORD_LEN];      //total byte length of the whole message
	uint8_t block_word_len;
	HASH_CALLBACK callback;
} HASH_DMA_CTX;
#endif




//APIs
uint32_t hash_get_block_word_len(HASH_ALG hash_alg);

uint32_t hash_get_digest_word_len(HASH_ALG hash_alg);

uint32_t hash_get_iterator_word_len(HASH_ALG hash_alg);

uint32_t hash_init(HASH_CTX *ctx, HASH_ALG hash_alg);

uint32_t hash_update(HASH_CTX *ctx, const uint8_t *msg, uint32_t msg_bytes);

uint32_t hash_final(HASH_CTX *ctx, uint8_t *digest);

uint32_t hash(HASH_ALG hash_alg, uint8_t *msg, uint32_t msg_bytes, uint8_t *digest);


#ifdef HASH_DMA_FUNCTION
uint32_t hash_dma_init(HASH_DMA_CTX *ctx, HASH_ALG hash_alg, HASH_CALLBACK callback);

uint32_t hash_dma_update_blocks(HASH_DMA_CTX *ctx, uint32_t *msg, uint32_t msg_words);

uint32_t hash_dma_final(HASH_DMA_CTX *ctx, uint32_t *remainder_msg, uint32_t remainder_bytes, uint32_t *digest);

uint32_t hash_dma(HASH_ALG hash_alg, uint32_t *msg, uint32_t msg_bytes, uint32_t *digest,
		HASH_CALLBACK callback);
#endif




#ifdef __cplusplus
}
#endif

#endif
