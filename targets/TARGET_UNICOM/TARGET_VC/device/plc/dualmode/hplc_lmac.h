#ifndef HPLC_LMAC_H
#define HPLC_LMAC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum vc_lmac_band_plan{
	BPLC_BAND_0,
	BPLC_BAND_1,
	BPLC_BAND_2,
	BPLC_BAND_3
} vc_lmac_band_plan;

typedef struct lmac_dma_struct{
	uint32_t gDMA_ISR;
	uint32_t gCNMAC_ISR;
} lmac_dma_struct;

typedef struct lmac_csma_struct{
	uint8_t fromQ;/*0:TxQ, 1:FxQ, 2:OxQ*/
	uint8_t minBE;
	uint8_t maxBE;
	uint8_t sackNeed;
	uint8_t pktType;
	uint8_t retry;
	uint32_t period;
} lmac_csma_struct;

typedef struct lmac_config_struct{
	uint8_t hv_flag;
} lmac_config_struct;

typedef struct lmac_context_struct {
	uint16_t LMAC_DTEI;
	uint16_t LMAC_STEI;
	vc_lmac_band_plan lmacBand;
	uint8_t	lmacToneMask;
	lmac_csma_struct lmacCsma;
	lmac_config_struct lmacConfig;
} lmac_context_struct;

#define LMAC_PTR lmac_ptr_g
typedef struct lmac_context_struct *LMAC_CONTEXT_PTR;
extern LMAC_CONTEXT_PTR lmac_ptr_g;

#ifdef __cplusplus
}
#endif

#endif // HPLC_LMAC_H
