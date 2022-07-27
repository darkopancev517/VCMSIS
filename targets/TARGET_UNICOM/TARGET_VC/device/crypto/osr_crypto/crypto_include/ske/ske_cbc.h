#ifndef SKE_CBC_H
#define SKE_CBC_H


#include "ske.h"



#ifdef __cplusplus
extern "C" {
#endif






//APIs

uint32_t ske_lp_cbc_init(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv);

uint32_t ske_lp_cbc_update_blocks(uint8_t *in, uint8_t *out, uint32_t bytes);

uint32_t ske_lp_cbc_final(void);

uint32_t ske_lp_cbc_crypto(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint8_t *in, uint8_t *out, uint32_t bytes);


#ifdef SKE_LP_DMA_FUNCTION
uint32_t ske_lp_dma_cbc_init(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv);

uint32_t ske_lp_dma_cbc_update_blocks(uint32_t *in, uint32_t *out, uint32_t words, SKE_CALLBACK callback);

uint32_t ske_lp_dma_cbc_final(void);

uint32_t ske_lp_dma_cbc_crypto(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint32_t *in, uint32_t *out, uint32_t words, SKE_CALLBACK callback);
#endif







#ifdef __cplusplus
}
#endif

#endif
