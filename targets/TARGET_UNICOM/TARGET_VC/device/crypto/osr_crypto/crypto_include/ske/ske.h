#ifndef SKE_H
#define SKE_H


#include "../../crypto_hal/ske_basic.h"


#ifdef __cplusplus
extern "C" {
#endif




//APIs

void ske_lp_big_endian_add_uint8(uint8_t *a, uint32_t a_bytes, uint8_t b);

void ske_lp_little_endian_add_uint32(uint32_t *a, uint32_t a_words, uint32_t b);

uint8_t ske_lp_get_key_byte_len(SKE_ALG ske_alg);

uint8_t ske_lp_get_block_byte_len(SKE_ALG ske_alg);

void ske_lp_set_iv(uint8_t *iv, uint32_t block_bytes);

void ske_lp_set_key(SKE_ALG alg, uint8_t *key, uint16_t key_bytes, uint16_t key_idx);

uint32_t ske_lp_init_internal(SKE_CTX *ctx, SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, uint8_t *key,
		uint16_t sp_key_idx, uint8_t *iv , uint32_t dma_en);


uint32_t ske_lp_init(SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv);

uint32_t ske_lp_update_blocks(uint8_t *in, uint8_t *out, uint32_t bytes);

uint32_t ske_lp_final(void);

uint32_t ske_lp_crypto(SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint8_t *in, uint8_t *out, uint32_t bytes);


#ifdef SKE_LP_DMA_FUNCTION
uint32_t ske_lp_dma_init(SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv);

uint32_t ske_lp_dma_update_blocks(uint32_t *in, uint32_t *out, uint32_t words, SKE_CALLBACK callback);

uint32_t ske_lp_dma_final(void);

uint32_t ske_lp_dma_crypto(SKE_ALG alg, SKE_MODE mode, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint32_t *in, uint32_t *out, uint32_t words, SKE_CALLBACK callback);
#endif




#ifdef __cplusplus
}
#endif

#endif
