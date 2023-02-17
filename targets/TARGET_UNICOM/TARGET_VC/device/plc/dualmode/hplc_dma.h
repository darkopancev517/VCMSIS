#ifndef HPLC_DMA_H
#define HPLC_DMA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void LMAC_KICK_TX_DMA();
extern void LMAC_KICK_RX_DMA();

extern void vc_lmac_cfg_dma();
extern void lmac_dump_tx_desc();
extern void lmac_dump_rx_desc();

#ifdef __cplusplus
}
#endif

#endif // HPLC_DMA_H
