

#include "../../crypto_include/ske/ske_cbc.h"




#ifdef SUPPORT_SKE_MODE_CBC


uint32_t ske_lp_cbc_init(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv)
{
	return ske_lp_init(alg, SKE_MODE_CBC, crypto, key, sp_key_idx, iv);
}

uint32_t ske_lp_cbc_update_blocks(uint8_t *in, uint8_t *out, uint32_t bytes)
{
	return ske_lp_update_blocks(in, out, bytes);
}

uint32_t ske_lp_cbc_final(void)
{
	return ske_lp_final();
}

uint32_t ske_lp_cbc_crypto(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint8_t *in, uint8_t *out, uint32_t bytes)
{
	return ske_lp_crypto(alg, SKE_MODE_CBC, crypto, key, sp_key_idx, iv, in, out, bytes);
}


#ifdef SKE_LP_DMA_FUNCTION
uint32_t ske_lp_dma_cbc_init(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv)
{
	return ske_lp_dma_init(alg, SKE_MODE_CBC, crypto, key, sp_key_idx, iv);
}

uint32_t ske_lp_dma_cbc_update_blocks(uint32_t *in, uint32_t *out, uint32_t words, SKE_CALLBACK callback)
{
	return ske_lp_dma_update_blocks(in, out, words, callback);
}

uint32_t ske_lp_dma_cbc_final(void)
{
	return ske_lp_dma_final();
}

uint32_t ske_lp_dma_cbc_crypto(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint32_t *in, uint32_t *out, uint32_t words, SKE_CALLBACK callback)
{
	return ske_lp_dma_crypto(alg, SKE_MODE_CBC, crypto, key, sp_key_idx, iv, in, out, words, callback);
}
#endif


#endif

