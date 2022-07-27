#ifndef SHA256_H
#define SHA256_H



#include "hash.h"



#ifdef __cplusplus
extern "C" {
#endif


#ifdef SUPPORT_HASH_SHA256


typedef HASH_CTX SHA256_CTX;

#ifdef HASH_DMA_FUNCTION
typedef HASH_DMA_CTX SHA256_DMA_CTX;
#endif


//APIs

uint32_t sha256_init(SHA256_CTX *ctx);

uint32_t sha256_update(SHA256_CTX *ctx, const uint8_t *msg, uint32_t msg_bytes);

uint32_t sha256_final(SHA256_CTX *ctx, uint8_t *digest);

uint32_t sha256(uint8_t *msg, uint32_t msg_bytes, uint8_t *digest);


#ifdef HASH_DMA_FUNCTION
uint32_t sha256_dma_init(SHA256_DMA_CTX *ctx, HASH_CALLBACK callback);

uint32_t sha256_dma_update_blocks(SHA256_DMA_CTX *ctx, uint32_t *msg, uint32_t msg_words);

uint32_t sha256_dma_final(SHA256_DMA_CTX *ctx, uint32_t *remainder_msg, uint32_t remainder_bytes, uint32_t *digest);

uint32_t sha256_dma(uint32_t *msg, uint32_t msg_bytes, uint32_t *digest, HASH_CALLBACK callback);
#endif


#endif


#ifdef __cplusplus
}
#endif


#endif
