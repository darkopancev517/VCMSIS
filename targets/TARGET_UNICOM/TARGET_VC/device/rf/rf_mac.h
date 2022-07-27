/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __CENT_MAC_H
#define __CENT_MAC_H

#include <stdint.h>
#include "rf_host.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WPMAC_RXP_FCS_RESULT__CSR_WPRXP_FCS_MATCH_MASK  0x00000001
#define WPMAC_RXP_FCS_RESULT__CSR_WPRXP_FCS_TYPE_MASK   0x00000030
#define PHY_INTERRUPT_CR0__RG_PHY_TX_END_IRQ_MASK       0x00000001
#define PHY_INTERRUPT_CR0__RG_PHY_RX_PKT_IRQ_MASK       0x00000008
#define PHY_INTERRUPT_CR0__RG_PHY_RX_PHR_IRQ_MASK       0x00000020
#define PHY_INTERRUPT_CR0__RG_PHY_RX_PMD_IRQ_MASK       0x00000040
#define ModeSwitch_Timeout                              0x00008000
/*EVENT_M0_IRQ_T*/
#define M0_INTERRUPT_SAVE_NVRAM                         0x00000001

#define MAC_RX_BUF_ADDR             0x20002800
#define MAC_TX_BUF_ADDR             0x20003000

#define MAC_RXBUF_LEN               2048
#define MAC_TXBUF_LEN               2048
#define MAC_BUF_SIZE                2048

// -----------------------------------------------------------------------------------------

static inline uint32_t cent_align_len(uint32_t len) { return ((len+3)&0xfffc); } //4-byte alignment
extern uint32_t cent_rxHi_receive(uint8_t *data, uint32_t len);
extern uint8_t is_fcs_match(void);
extern uint8_t fcs_type(void);
extern uint32_t get_fcs_pattern(uint32_t *data);
extern uint32_t get_pkt_sr(void);
extern uint32_t get_phr_len(void);
extern uint32_t get_pkt_len(void);
extern uint8_t is_ack(void);
extern uint8_t is_rtt_ack(void);
extern uint32_t cent_mac_tx_prefill(uint8_t *data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif




