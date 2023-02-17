#ifndef HPLC_RX_H
#define HPLC_RX_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void vc_cn_mac_disable_ire();
extern void vc_cn_mac_enable_ire();
extern void vc_plc_dma_disable_ire();
extern void vc_plc_dma_enable_ire();
extern void vc_lmac_cfg_phy_rx_disable();
extern void vc_lmac_cfg_phy_rx_enable();

#ifdef __cplusplus
}
#endif

#endif // HPLC_RX_H
