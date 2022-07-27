#ifndef HMAC_H
#define HMAC_H

#ifdef __cplusplus
extern "C" {
#endif


#include "hash.h"



#define HMAC_IPAD                 (0x36363636)
#define HMAC_OPAD                 (0x5c5c5c5c)
#define HMAC_IPAD_XOR_OPAD        (HMAC_IPAD ^ HMAC_OPAD)


//HMAC context
typedef struct
{
	uint32_t K0[HASH_BLOCK_MAX_WORD_LEN];
	HASH_ALG hash_alg;
	HASH_CTX hash_ctx[1];
} HMAC_CTX;


//HMAC DMA context
#ifdef HASH_DMA_FUNCTION
typedef struct
{
	HMAC_CTX hmac_ctx[1];
	HASH_DMA_CTX hash_dma_ctx[1];
} HMAC_DMA_CTX;
#endif




//APIs

uint32_t hmac_init(HMAC_CTX *ctx, HASH_ALG hash_alg, uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes);

uint32_t hmac_update(HMAC_CTX *ctx, const uint8_t *msg, uint32_t msg_bytes);

uint32_t hmac_final(HMAC_CTX *ctx, uint8_t *mac);

uint32_t hmac(HASH_ALG hash_alg, uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes, uint8_t *msg, uint32_t msg_bytes,
		uint8_t *mac);


#ifdef HASH_DMA_FUNCTION
uint32_t hmac_dma_init(HMAC_DMA_CTX *ctx, HASH_ALG hash_alg, const uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes,
		HASH_CALLBACK callback);

uint32_t hmac_dma_update_blocks(HMAC_DMA_CTX *ctx, uint32_t *msg, uint32_t msg_words);

uint32_t hmac_dma_final(HMAC_DMA_CTX *ctx, uint32_t *remainder_msg, uint32_t remainder_bytes, uint32_t *mac);

uint32_t hmac_dma(HASH_ALG hash_alg, uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes, uint32_t *msg, uint32_t msg_bytes,
		uint32_t *mac, HASH_CALLBACK callback);
#endif



#ifdef __cplusplus
}
#endif

#endif
