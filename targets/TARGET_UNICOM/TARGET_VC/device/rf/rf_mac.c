/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "rf_mac.h"
#include "rf_prober.h"
#include "hal/rf.h"

uint32_t get_fcs_pattern(uint32_t *data)
{

    if (fcs_type())
        return (*data & 0xFFFF);
    else
        return (*data & 0xFFFFFFFF);
}

uint8_t is_ack(void)
{
    uint32_t mhr;

    cent_spi_readW(MAC_RX_BUF_ADDR, &mhr);

    if ((mhr & 0x7) == 0x2)
        return 1;
    else
        return 0;
}
uint8_t is_rtt_ack(void)
{
    uint32_t mhr;

    cent_spi_readW(MAC_RX_BUF_ADDR, &mhr);
    
    if ((mhr ^ 0xaa55aa55) == 0)
        return 1; //pass
    else
        return 0; //fail
}
uint32_t cent_mac_tx_prefill(uint8_t *data, uint32_t length)
{
    if (length > MAC_TXBUF_LEN)
        length = MAC_TXBUF_LEN;

    hal_rf_write(MAC_TX_BUF_ADDR, data, length);

    return length;
}

extern uint32_t g_rx_complete;

uint32_t cent_rxHi_receive(uint8_t *data, uint32_t len)//len must be 4-byte aligned
{
    uint32_t read_len;

    read_len=len;
    hal_rf_read(data, MAC_RX_BUF_ADDR, read_len);

    if (g_rx_complete == 0) {
    } else {
		g_rx_complete = 0;
    }

    return read_len;
}


uint8_t is_fcs_match(void)
{
    uint32_t packet_status;

    packet_status = get_pkt_sr();

    if (packet_status & WPMAC_RXP_FCS_RESULT__CSR_WPRXP_FCS_MATCH_MASK)
        return 1;// 1: match
    else
        return 0;// 0:mismatch
}

uint8_t fcs_type(void)
{
    uint32_t packet_status;

    packet_status = get_pkt_sr();

    if (packet_status & WPMAC_RXP_FCS_RESULT__CSR_WPRXP_FCS_TYPE_MASK)//The Type of FCS. (0: FCS-32, 1: FCS-16)
        return FCS_16;
    else    
        return FCS_32;
}


