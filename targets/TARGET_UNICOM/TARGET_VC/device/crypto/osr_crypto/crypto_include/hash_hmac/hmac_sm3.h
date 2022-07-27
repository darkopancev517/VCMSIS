#ifndef HMAC_SM3_H
#define HMAC_SM3_H



#include "hmac.h"



#ifdef __cplusplus
extern "C" {
#endif


#ifdef SUPPORT_HASH_SM3


typedef HMAC_CTX HMAC_SM3_CTX;

#ifdef HASH_DMA_FUNCTION
typedef HMAC_DMA_CTX HMAC_SM3_DMA_CTX;
#endif


//APIs

uint32_t hmac_sm3_init(HMAC_SM3_CTX *ctx, uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes);

uint32_t hmac_sm3_update(HMAC_SM3_CTX *ctx, const uint8_t *msg, uint32_t msg_bytes);

uint32_t hmac_sm3_final(HMAC_SM3_CTX *ctx, uint8_t *mac);

uint32_t hmac_sm3(uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes, uint8_t *msg, uint32_t msg_bytes, uint8_t *mac);


#ifdef HASH_DMA_FUNCTION
uint32_t hmac_sm3_dma_init(HMAC_SM3_DMA_CTX *ctx, const uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes,
		HASH_CALLBACK callback);

uint32_t hmac_sm3_dma_update_blocks(HMAC_SM3_DMA_CTX *ctx, uint32_t *msg, uint32_t msg_words);

uint32_t hmac_sm3_dma_final(HMAC_SM3_DMA_CTX *ctx, uint32_t *remainder_msg, uint32_t remainder_bytes,
		uint32_t *mac);

uint32_t hmac_sm3_dma(uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes, uint32_t *msg, uint32_t msg_bytes,
		uint32_t *mac, HASH_CALLBACK callback);
#endif


#endif


#ifdef __cplusplus
}
#endif


#endif
