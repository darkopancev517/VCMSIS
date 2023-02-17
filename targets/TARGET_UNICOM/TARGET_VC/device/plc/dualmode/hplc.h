#ifndef HPLC_H
#define HPLC_H

#include <stdint.h>

#include "vc_lmac_dma.h"
#include "vc_lmac_dma_if.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CHIP_IS_MP_VERSION 0

enum {
  PLC_TX_OK,
  PLC_TX_ERR,
  PLC_TX_BUSY,
  PLC_TX_COLLISION,
};

#define LMAC_AUTO_CFG_CSMA 0

#define VC_SWAP_16(n) (uint16_t)((((uint16_t) (n)) << 8) | (((uint16_t) (n)) >> 8))

extern void vc_lmac_cfg_arq_MyTEI(uint16_t pMyTEI);

void vcplc_init(void);
int vcplc_transmit(const uint8_t *data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // HPLC_H
