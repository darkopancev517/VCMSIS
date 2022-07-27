#ifndef SHA1_H
#define SHA1_H



#include "hash.h"



#ifdef __cplusplus
extern "C" {
#endif


#ifdef SUPPORT_HASH_SHA1


typedef HASH_CTX SHA1_CTX;

#ifdef HASH_DMA_FUNCTION
typedef HASH_DMA_CTX SHA1_DMA_CTX;
#endif


//APIs

uint32_t sha1_init(SHA1_CTX *ctx);

uint32_t sha1_update(SHA1_CTX *ctx, const uint8_t *msg, uint32_t msg_bytes);

uint32_t sha1_final(SHA1_CTX *ctx, uint8_t *digest);

uint32_t sha1(uint8_t *msg, uint32_t msg_bytes, uint8_t *digest);


#ifdef HASH_DMA_FUNCTION
uint32_t sha1_dma_init(SHA1_DMA_CTX *ctx, HASH_CALLBACK callback);

uint32_t sha1_dma_update_blocks(SHA1_DMA_CTX *ctx, uint32_t *msg, uint32_t msg_words);

uint32_t sha1_dma_final(SHA1_DMA_CTX *ctx, uint32_t *remainder_msg, uint32_t remainder_bytes, uint32_t *digest);

uint32_t sha1_dma(uint32_t *msg, uint32_t msg_bytes, uint32_t *digest, HASH_CALLBACK callback);
#endif


#endif


#ifdef __cplusplus
}
#endif


#endif
