#ifndef SKE_GCM_H
#define SKE_GCM_H


#include "ske.h"


#ifdef __cplusplus
extern "C" {
#endif




#define SKE_LP_GCM_CPU_UPDATE_AAD_BY_STEP


#define SKE_LP_GCM_MAX_BYTES    (16)




typedef struct{
	uint8_t buf[16];
	SKE_CTX ske_gcm_ctx[1];
	SKE_CRYPTO crypto;
	uint32_t aad_bytes;
	uint32_t c_bytes;
	uint32_t mac_bytes;
	uint32_t current_bytes;
} SKE_GCM_CTX;



typedef struct{
	SKE_GCM_CTX gcm_ctx[1];
	SKE_MAC mac_action;
} SKE_GMAC_CTX;



//APIs

uint32_t ske_lp_gcm_init(SKE_GCM_CTX *ctx, SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx,
		uint8_t *iv, uint32_t iv_bytes, uint32_t aad_bytes, uint32_t c_bytes, uint32_t mac_bytes);

uint32_t ske_lp_gcm_update_aad(SKE_GCM_CTX *ctx, uint8_t *aad, uint32_t bytes);

uint32_t ske_lp_gcm_aad(SKE_GCM_CTX *ctx, uint8_t *aad);

uint32_t ske_lp_gcm_update_blocks(SKE_GCM_CTX *ctx, uint8_t *in, uint8_t *out, uint32_t bytes);

uint32_t ske_lp_gcm_final(SKE_GCM_CTX *ctx, uint8_t *mac);

uint32_t ske_lp_gcm_crypto(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint32_t iv_bytes, uint8_t *aad, uint32_t aad_bytes, uint8_t *in, uint8_t *out, uint32_t c_bytes,
		uint8_t *mac, uint32_t mac_bytes);


#ifdef SKE_LP_DMA_FUNCTION
uint32_t ske_lp_dma_gcm_init(SKE_GCM_CTX *ctx, SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx,
		uint8_t *iv, uint32_t iv_bytes, uint32_t aad_bytes, uint32_t c_bytes, uint32_t mac_bytes);

uint32_t ske_lp_dma_gcm_update_aad_blocks(SKE_GCM_CTX *ctx, uint32_t *aad, uint32_t bytes, SKE_CALLBACK callback);

uint32_t ske_lp_dma_gcm_update_blocks(SKE_GCM_CTX *ctx, uint32_t *in, uint32_t *out, uint32_t in_bytes,
		SKE_CALLBACK callback);

uint32_t ske_lp_dma_gcm_final(SKE_GCM_CTX *ctx);

uint32_t ske_lp_dma_gcm_crypto(SKE_ALG alg, SKE_CRYPTO crypto, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint32_t iv_bytes, uint32_t *aad, uint32_t aad_bytes, uint32_t *in, uint32_t *out, uint32_t c_bytes, 
		uint32_t mac_bytes, SKE_CALLBACK callback);
#endif



#ifdef SUPPORT_SKE_MODE_GMAC
uint32_t ske_lp_gmac_init(SKE_GMAC_CTX *ctx, SKE_ALG alg, SKE_MAC mac_action, uint8_t *key, uint16_t sp_key_idx,
		uint8_t *iv, uint32_t iv_bytes, uint32_t aad_bytes, uint32_t c_bytes, uint32_t mac_bytes);

uint32_t ske_lp_gmac_update_aad(SKE_GMAC_CTX *ctx, uint8_t *aad, uint32_t bytes);

uint32_t ske_lp_gmac_aad(SKE_GMAC_CTX *ctx, uint8_t *aad);

uint32_t ske_lp_gmac_update(SKE_GMAC_CTX *ctx, uint8_t *in, uint32_t bytes);

uint32_t ske_lp_gmac_final(SKE_GMAC_CTX *ctx, uint8_t *mac);

uint32_t ske_lp_gmac_crypto(SKE_ALG alg, SKE_MAC mac_action, uint8_t *key, uint16_t sp_key_idx, uint8_t *iv,
		uint32_t iv_bytes, uint8_t *aad, uint32_t aad_bytes, uint8_t *in, uint32_t c_bytes, uint8_t *mac,
		uint32_t mac_bytes);
#endif




#ifdef __cplusplus
}
#endif

#endif
