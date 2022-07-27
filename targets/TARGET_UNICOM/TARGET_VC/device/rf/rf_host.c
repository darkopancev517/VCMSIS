/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "rf_host.h"
#include "rf_prober.h"
#include "rf_queue.h"
#include "rf_pmu_csr.h"
#include "rf_cmd.h"
#include "rf_cfg.h"
#include "rf_hwset.h"

uint32_t cent_nv_get_front_end(void)
{
    if (rf_hwset.mFrontEndStateBits == 0xffffffff) {
        rf_hwset.mFrontEndStateBits = 0;
    }
    return rf_hwset.mFrontEndStateBits;
}

int32_t cent_nv_get_elna_rssi_offset(void)
{
    return rf_hwset.mELNARssiOffset;
}

void cent_nv_set_front_end(uint32_t febs)
{
    rf_hwset.mFrontEndStateBits = febs & (FRONT_END_STATE_ELNA_EN
                                       | FRONT_END_STATE_EPA_EN
                                       | FRONT_END_STATE_ANT_DIVERSITY_EN);
    if (febs & FRONT_END_STATE_EPA_EN) {
        rf_hwset.mPaSel = 0;
        cent_cmd_pa_select(rf_hwset.mPaSel);
    }
}

void cent_nv_set_pa_select(int bOn)
{
    if (cent_nv_get_front_end() & FRONT_END_STATE_EPA_EN) {
        rf_hwset.mPaSel = 0;
    } else {
        rf_hwset.mPaSel = bOn ? 1 : 0;
    }
    cent_cmd_pa_select(rf_hwset.mPaSel);
}

void cent_cal_load(void)
{
    if(rf_hwset.mFrequency != 0)
        cent_cmd_set_channel((uint32_t)rf_hwset.mFrequency);

    if(rf_hwset.mXtalOffset != 0)
        cent_cmd_dctune((uint16_t)rf_hwset.mXtalOffset);
    
    if (cent_nv_get_front_end() & FRONT_END_STATE_EPA_EN) {
        rf_hwset.mPaSel = 0; //ensure it is set to MPA to protect ePA
    }
    
    cent_cmd_pa_select(rf_hwset.mPaSel);
    cent_cmd_txpwr((int16_t)rf_hwset.mTxPower);

    if (cent_nv_get_front_end() & FRONT_END_STATE_ELNA_EN) {
        cent_elna_enable(2);
    }else{
        cent_elna_enable(0);
    }
   
}

void cent_get_statistic(struct STAT_INFO_T *pStatInfo)
{
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, pmb), (uint32_t*)&pStatInfo->pmb);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, sfd), (uint32_t*)&pStatInfo->sfd);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, phr), (uint32_t*)&pStatInfo->phr);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, antenna), (uint32_t*)&pStatInfo->antenna);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rx_pkt), (uint32_t*)&pStatInfo->rx_pkt);
    cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, sfd_timeout), (uint32_t *)&pStatInfo->sfd_timeout);
    cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rssi_less), (uint32_t*)&pStatInfo->rssi_less);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rssi_over), (uint32_t*)&pStatInfo->rssi_over);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rx_drop_by_len), (uint32_t*)&pStatInfo->rx_drop_by_len);
    cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, tx_en), (uint32_t *)&pStatInfo->tx_en);
    cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, txcmp), (uint32_t*)&pStatInfo->txcmp);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rxcmp), (uint32_t*)&pStatInfo->rxcmp);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, fcs_err), (uint32_t*)&pStatInfo->fcs_err);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rx_drop_by_addr), (uint32_t*)&pStatInfo->rx_drop_by_addr);
}

uint32_t get_cmd_status(void)
{
	uint32_t cmd_status;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, cmd_status), (uint32_t*)&cmd_status);
	return cmd_status;
}


uint32_t get_state(void)
{
	uint32_t state;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, state), (uint32_t*)&state);
	return state;
}

uint32_t get_pkt_len(void)
{
	uint32_t packet_len;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, packet_len), (uint32_t*)&packet_len);
	return packet_len;
}

uint32_t get_pkt_sr(void)
{
	uint32_t packet_sr;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, pkt_sr), (uint32_t*)&packet_sr);
	return packet_sr;
}

uint32_t get_phr_len(void)
{
	uint32_t phr_len;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, phr_len), (uint32_t*)&phr_len);
	return phr_len;
}

uint32_t get_pkt_lqi(void)
{
	uint32_t lqi;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, lqi), (uint32_t*)&lqi);
	return lqi;
}

uint32_t get_pkt_snr(void)
{
	uint32_t snr;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, snr), (uint32_t*)&snr);
	return snr;
}

int32_t get_pkt_rssi(void)
{
    uint32_t pkt_rssi,elna;
   
    cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, pkt_rssi), (uint32_t*)&pkt_rssi);

    elna = (pkt_rssi >> 15) & 0x1;

    if(pkt_rssi & 0x800) //if bit[12] is 1 , negative number
    {
        //do the 2's complement
        pkt_rssi = ~pkt_rssi;
        pkt_rssi &= 0xFFF;
        pkt_rssi += 1;

        //shift the Decimal places
        pkt_rssi = (pkt_rssi >> 3) * -1 ; 
    }
    else
    {
        pkt_rssi = (pkt_rssi >> 3) ;
    }
    
    if (cent_nv_get_front_end() & FRONT_END_STATE_ELNA_EN) {
        if(elna)
            pkt_rssi -= rf_hwset.mELNARssiOffset;
        else
            pkt_rssi -= rf_hwset.mRssiOffset;
    }else{
        pkt_rssi -= rf_hwset.mRssiOffset;
    }
    
    return pkt_rssi;
}

int get_receiving_status(void)
{
    uint32_t packet_receiving = 0;
    cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, packet_receiving), (uint32_t*)&packet_receiving);
    return (packet_receiving == 1) ? 1 : 0;
}


int32_t get_rssi(void)
{
	uint32_t rssi, elna;

	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, cca_rssi), (uint32_t*)&rssi);

    elna = (rssi >> 15) & 0x1;
    rssi &= ~0x8000;
    
    if(rssi & 0x800)//if bit[12] is 1 , negative number
    {
        //do the 2's complement
        rssi = ~rssi;
        rssi &= 0xFFF;
        rssi += 1;

         //shift the Decimal places
        rssi = (rssi >> 3) * -1 ;
    }
    else
    {
        rssi &= 0xFFF;
        rssi = (rssi >> 3) ;
    }

    if (cent_nv_get_front_end() & FRONT_END_STATE_ELNA_EN) {
        if(elna)
            rssi -= rf_hwset.mELNARssiOffset;
        else
            rssi -= rf_hwset.mRssiOffset;
    }else{
        rssi -= rf_hwset.mRssiOffset;
    }
    
    return rssi;
}

uint32_t get_cca(void)
{
	uint32_t cca;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, cca), (uint32_t*)&cca);

	return cca;
}

void cent_reset(void)
{
    //TODO: vcradio_host_reset_trig();
}

uint32_t rfmode_is_ofdm(void)
{
    uint32_t rfmode;
    cent_spi_readW(CENT_RFMODE, (uint32_t *)&rfmode);
    return (rfmode & 0x01);
}

int32_t GetModeSwitchCCA(void)
{
    uint32_t rssi, elna;
    cent_spi_readW(CENT_MODESWITCH_CCA, (uint32_t *)&rssi);

    elna = (rssi >> 15) & 0x1;

    if (rssi & 0x800) //if bit[12] is 1 , negative number
    {
        //do the 2's complement
        rssi = ~rssi;
        rssi &= 0xFFF;
        rssi += 1;

        //shift the Decimal places
        rssi = (rssi >> 3) * -1;
    }
    else
    {
        rssi = (rssi >> 3);
    }

    if (cent_nv_get_front_end() & FRONT_END_STATE_ELNA_EN)
    {
        if (elna)
            rssi -= rf_hwset.mELNARssiOffset;
        else
            rssi -= rf_hwset.mRssiOffset;
    }
    else
    {
        rssi -= rf_hwset.mRssiOffset;
    }

    return rssi;
}
int32_t GetTxSettlingTime(void)
{
    uint32_t time;
    cent_spi_readW(CENT_MODESWITCH_TX_SettlingTime, (uint32_t *)&time);

    return time;
}
uint32_t GetDspValue(void)
{
    uint32_t value;
    cent_spi_readW(CENT_DSP_ADDR3, (uint32_t *)&value);
    return value;
}
