/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __CENT_CMD_H
#define __CENT_CMD_H

#include <stdbool.h>
#include <stdint.h>
#include "rf_host.h"

#ifdef __cplusplus
extern "C" {
#endif

bool cent_cmd_res_check(uint32_t rc);
uint32_t cent_send_cmd(RF_HCMD_CMD_T cmd, uint16_t param, uint32_t param_ext, uint32_t *pval);
uint32_t cent_write_cmd_ext(RF_HCMD_CMD_T cmd, uint16_t param, uint32_t paramExt);

uint32_t cent_cmd_read_channel(void);//TODO: unified interface 

uint32_t cent_cmd_status(void);
uint32_t cent_cmd_idle(void);
uint32_t cent_cmd_sleep(uint32_t period);
uint32_t cent_cmd_shutdown(void);
uint32_t cent_cmd_cal_32k(void);
uint32_t cent_cmd_cal_4m(void);
uint32_t cent_cmd_cal_vco(void);
uint32_t cent_cmd_cal_iq(void);
uint32_t cent_cmd_cal_rxadc(void);
uint32_t cent_cmd_period_config(uint32_t period, uint32_t tolerance);


uint32_t cent_cmd_init(void);
uint32_t cent_cmd_tx(uint32_t fcs, uint32_t packet_len);
uint32_t cent_cmd_tx_refilled(uint32_t write_len);
uint32_t cent_cmd_rx(uint32_t next_state);
uint32_t cent_cmd_rx_read(uint32_t read_len);

uint32_t cent_cmd_txpwr(int16_t txpwr);

uint32_t cent_cmd_ofdm_txpwr(int16_t txpwr);
int32_t cent_cmd_ModeSwitch_CCA(void);
int32_t cent_cmd_tx_settling_time(void);
uint32_t cent_cmd_dsp_value(void);

uint32_t cent_cmd_rssi(int *prssi);//modified

uint32_t cent_cmd_mac_loopback(uint32_t fcs, uint32_t packet_len);
uint32_t cent_cmd_state_change(uint32_t state);


uint32_t cent_wakeup(void);
uint32_t cent_cmd_set_channel(uint32_t chn_band);
uint32_t cent_cmd_set_modi(uint32_t modi);
uint32_t cent_cmd_get_modi(void);
uint32_t cent_cmd_set_rate(uint32_t rate);
uint32_t cent_cmd_data_whitening(uint16_t dw);
uint32_t cent_cmd_rtt(uint16_t bEn);
uint32_t cent_cmd_mrfsk(uint32_t parm,uint32_t rf_channel);
uint32_t cent_cmd_txpower(uint32_t txpwrmode);
uint32_t cent_cmd_basemode(uint32_t basemode);
uint32_t cent_cmd_newmode(uint8_t CH_ID, uint8_t CH_NO, uint8_t PHY_TYPE, uint8_t PHY_MODE, uint8_t TXPWR);
uint32_t cent_cmd_optmcs(uint32_t parmFSK);
uint32_t SetRFMode(uint32_t rfmode);
uint32_t SetDSPRead(uint8_t cmd, uint32_t param);
uint32_t SetDSPWrite(uint8_t cmd, uint32_t param, uint32_t IsEXTCMD);
uint32_t SetMSAlgo(uint32_t param);
uint32_t GetRFMode(void);
uint32_t cent_cmd_txdelay(uint32_t delay);
uint32_t TransceiverFecCtrlSwMode(uint32_t fec_en, uint32_t fec_type);
uint32_t cent_cmd_pmb_length(uint16_t length);
uint32_t cent_cmd_rx16mhz(uint16_t rx16m);

uint32_t cent_cmd_txcw(uint16_t enable);
uint32_t cent_cmd_txcm(uint16_t enable);

uint32_t cent_cmd_statistic_clear(void);

uint32_t cent_cmd_pa_select(uint16_t pa);
uint32_t cent_cmd_dctune(uint16_t dctune);
uint16_t cent_cmd_read_dctune(void);//TODO: unified interface 
uint32_t cent_cmd_rssi_offset(int16_t offset);
uint32_t cent_cmd_elna_enable(uint16_t sw);
uint16_t cent_cmd_saradc(uint16_t vin_sel);//TODO: unified interface 
uint32_t rf_cmd_get_ofdm_version();
uint32_t rf_cmd_get_m0_version();
uint32_t GetM0HWSET_IDX(void);
uint32_t GetM0HWSET_VAL(void);
void SetM0HWSET_Clean(void);
int cent_is_powerup();

#ifdef __cplusplus
}
#endif

#endif /* __CENT_CMD_H */
