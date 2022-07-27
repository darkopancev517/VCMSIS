#ifndef SM3_H
#define SM3_H



#include "hash.h"



#ifdef __cplusplus
extern "C" {
#endif


#ifdef SUPPORT_HASH_SM3


typedef HASH_CTX SM3_CTX;

#ifdef HASH_DMA_FUNCTION
typedef HASH_DMA_CTX SM3_DMA_CTX;
#endif


//APIs

uint32_t sm3_init(SM3_CTX *ctx);

uint32_t sm3_update(SM3_CTX *ctx, const uint8_t *msg, uint32_t msg_bytes);

uint32_t sm3_final(SM3_CTX *ctx, uint8_t *digest);

uint32_t sm3(uint8_t *msg, uint32_t msg_bytes, uint8_t *digest);


#ifdef HASH_DMA_FUNCTION
uint32_t sm3_dma_init(SM3_DMA_CTX *ctx, HASH_CALLBACK callback);

uint32_t sm3_dma_update_blocks(SM3_DMA_CTX *ctx, uint32_t *msg, uint32_t msg_words);

uint32_t sm3_dma_final(SM3_DMA_CTX *ctx, uint32_t *remainder_msg, uint32_t remainder_bytes, uint32_t *digest);

uint32_t sm3_dma(uint32_t *msg, uint32_t msg_bytes, uint32_t *digest, HASH_CALLBACK callback);
#endif


#endif


#ifdef __cplusplus
}
#endif


#endif
