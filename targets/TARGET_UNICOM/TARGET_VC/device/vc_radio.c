/*
 * Copyright (c) 2022 Unicom Semiconductor, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "vc_radio.h"
#include "vc_gpio.h"
#include "vc_mbox.h"
#include "hal/rf.h"
#include "hal/misc.h"
#include "hal/gpio.h"
#include "hal/log.h"
#include "rf_cmd.h"
#include "rf_cfg.h"
#include "rf_mac.h"
#include "rf_hwset.h"
#include "rfmbx.h"

#include "us_ticker_api.h"
#include "gpio_api.h"

static uint8_t *m_rx_buffer = NULL;
static int m_max_buffer_sz;
static uint32_t m_rx_buf_index = 0;
static bool m_rx_buf_overflow = false;
static int16_t m_tx_power = 0;
static bool m_radio_initialized = false;
static uint32_t m_timestamp = 0;
static uint32_t m_phr_len;
static uint32_t m_tx_fcs = FCS_MODE;
static uint16_t m_pmb_len = 0;
static uint32_t m_systick_offset = 0;

uint32_t last_dwen = 0;
uint32_t last_rfmode = 0;
uint32_t last_opt = 0;
uint32_t last_mcs = 0;
uint32_t last_channel = 920000000;
uint32_t last_rate = 0;
uint32_t g_rx_complete = 0; // parameter used in rf_mac.c
uint32_t g_bit_duration = 20;
uint32_t g_fec_en = 0;

gpio_t TXLED_PIN;
gpio_t RXLED_PIN;

receive_handler m_receive_handler = NULL;

void vcradio_reinit(void)
{
}

void vcradio_load_dsp(void)
{
  hal_rf_reset_assert();
  hal_rf_load_code();
  hal_gpio_select_m0_gpio();
  hal_misc_m0_start(1);
}

void vcradio_init(uint8_t *buffer, int size, receive_handler handler)
{
  if (m_radio_initialized) {
    return;
  }

  m_systick_offset = ((SystemCoreClock / 1000) - 1) / (SystemCoreClock / 1000000);
  m_max_buffer_sz = size;
  m_rx_buffer = buffer;
  if (handler != NULL) {
    m_receive_handler = handler;
  }

  vcradio_load_dsp();
  vcradio_host_init();
  rfmbx_init();
  vcradio_host_event_int_enable();
  while (!cent_is_powerup());
  cent_misc_config(size);
  cent_cal_load();

  if (1 == rf_hwset.mCal[10]) {
    /* load TX LOFT & TX IQC calibration value */
    hal_misc_m0mem_put(0x40013edc, rf_hwset.mCal[0]);
    hal_misc_m0mem_put(0x40013ee0, rf_hwset.mCal[0]);
    hal_misc_m0mem_put(0x40013ee4, rf_hwset.mCal[0]);
    hal_misc_m0mem_put(0x40013ee8, rf_hwset.mCal[0]);
    hal_misc_m0mem_put(0x40013eec, rf_hwset.mCal[0]);
  }

  m_tx_power = rf_hwset.mTxPower;
  vcradio_receive_on();
  vcradio_host_rxled_off();
  vcradio_host_txled_off();

  // IOA9 & IOB15 define to M0 IO to control Multiplexer-TC2-EVB
  vcgpio_select_function(PA_9, 7);
  vcgpio_select_function(PB_15, 7);
  vcradio_set_data_whitening(1);

  // for OFDM Mode Reboot
  if (rf_hwset.mCal[15] == OFDM_MODE) {
    vcradio_set_RFMode(rf_hwset.mCal[15]);
    vcradio_set_opt_mcs(rf_hwset.mCal[13], rf_hwset.mCal[14]);
  }

  m_radio_initialized = true;
}

static uint32_t cent_tx_prefill(uint8_t *data, uint32_t length)
{
  return cent_mac_tx_prefill(data, length);
}

int vcradio_transmit(uint8_t *txdata, uint32_t txlen)
{
  int res = 1;
  int rs = vcradio_lock_irq();
  //cent_cmd_idle();
  cent_tx_prefill(txdata, txlen);
  vcradio_host_txled_on();
  rfmbx_clear();
  cent_cmd_tx(m_tx_fcs, txlen);
  bool btxcmplt = false;
  uint32_t t0 = vcradio_host_get_usec_now();
  uint32_t tmax = ((m_pmb_len + 2 + 2 + txlen + 4) * 8UL * g_bit_duration) * (g_fec_en + 1) + 5000UL;
  while (!btxcmplt) {
    RF_EVENT_T vnt;
    while ((rfmbx_get(&vnt)) == 0) {
      if (vnt.cmd == RF_EVENT_PHY_IRQn) {
        if (vnt.param & PHY_INTERRUPT_CR0__RG_PHY_TX_END_IRQ_MASK) {
          btxcmplt = 1;
          break;
        }
      }
    }
    if ((vcradio_host_get_usec_now() + (0xffffffffUL - t0) + m_systick_offset + 1UL) > tmax) {
      res = 0; // TX TIMEOUT
      break;
    }
  }
  m_rx_buf_index = 0;
  if (!rfmode_is_ofdm()) {
    cent_cmd_rx(SYS_RX);
  }
  vcradio_host_txled_off();
  vcradio_unlock_irq(rs);
  return res;
}

void vcradio_set_preamble_len(uint16_t pmblen)
{
  m_pmb_len = pmblen / 8;
  cent_cmd_pmb_length(pmblen);
}

uint16_t vcradio_get_preamble_len(void)
{
  return m_pmb_len;
}

void vcradio_set_data_rate(uint32_t rate)
{
  last_rate = rate;
  g_bit_duration = (1000000 / rate) + 1;
  cent_cmd_set_rate(rate);
}

static int _set_frequency(uint32_t freq)
{
  if (cent_cmd_set_channel(freq) == 0)
    return 0;

  rfmbx_clear();
  m_rx_buf_index = 0;
  cent_cmd_rx(SYS_RX);
  return 1;
}

int vcradio_set_frequency(uint32_t freq)
{
  last_channel = freq;
  return _set_frequency(freq);
}

uint32_t vcradio_get_frequency(void)
{
  return cent_cmd_read_channel();
}


void vcradio_receive_on(void)
{
  rfmbx_clear();
  m_rx_buf_index = 0;
  cent_cmd_rx(SYS_RX);
}

void vcradio_set_fcs(uint32_t fcs)
{
  m_tx_fcs = fcs;
}

uint32_t vcradio_get_fcs(void)
{
  return m_tx_fcs; 
}

void vcradio_set_data_whitening(uint16_t bEn)
{
  last_dwen = bEn;
  cent_cmd_data_whitening(bEn);
}

void vcradio_set_RFMode(uint32_t _rfmode)
{
  last_rfmode = _rfmode;
  rf_hwset.mCal[15] = last_rfmode;
  // TODO: hwset_var_store();
  SetRFMode(_rfmode);
}

void vcradio_set_opt_mcs(uint32_t _opt, uint32_t _mcs)
{
  unsigned int SwitchHeader = 0;
  last_opt = _opt;
  last_mcs = _mcs;
  rf_hwset.mCal[13] = _opt;
  rf_hwset.mCal[14] = _mcs;
  // TODO: hwset_var_store();
  _opt += 1; // to fit PhyType
  SwitchHeader = (((_opt << 25) & 0x1E000000) |
                  ((_mcs << 21) & 0x01E00000));
  cent_cmd_optmcs(SwitchHeader);
}

void vcradio_host_rxled_off(void)
{
  gpio_write(&RXLED_PIN, 1);
}

void vcradio_host_rxled_on(void)
{
  gpio_write(&RXLED_PIN, 0);
}

void vcradio_host_txled_off(void)
{
  gpio_write(&TXLED_PIN, 1);
}

void vcradio_host_txled_on(void)
{
  gpio_write(&TXLED_PIN, 0);
}

uint32_t vcradio_host_get_timestamp(void)
{
  return us_ticker_read();
}

void vcradio_host_init(void)
{
  hal_rf_init();

  gpio_init(&TXLED_PIN, PC_5);
  gpio_init(&RXLED_PIN, PC_4);

  gpio_write(&TXLED_PIN, 1); // off
  gpio_write(&RXLED_PIN, 1); // off
}

void vcradio_host_event_int_enable(void)
{
  // TODO: make sure not conflict with mbedOS priority number
  NVIC_SetPriority(MSGBOX_IRQn, 1);
  vcmbx_enable_int(1);
}

int _hal_radio_lock_irq(int state)
{
  int res = NVIC_GetEnableIRQ(MSGBOX_IRQn);
  if (state) {
    NVIC_EnableIRQ(MSGBOX_IRQn);
  } else {
    NVIC_DisableIRQ(MSGBOX_IRQn);
  }
  return res;
}

int vcradio_lock_irq(void)
{
  return _hal_radio_lock_irq(0);
}

void vcradio_unlock_irq(int rs)
{
  _hal_radio_lock_irq(rs);
}

uint32_t vcradio_get_dsp_value(void)
{
  int value = (int)cent_cmd_dsp_value();
  return value;
}


uint32_t vcradio_host_get_usec_now(void)
{
  return us_ticker_read();
}

uint32_t OFDM_Counter_Reset(void)
{
  SetDSPRead(0x27, 12);
  return vcradio_get_dsp_value();
}

static void _cent_on_m0_event(RF_EVENT_T *pvnt)
{
  if (pvnt->param & M0_INTERRUPT_SAVE_NVRAM)
  {
    rf_hwset.mCal[GetM0HWSET_IDX()] = GetM0HWSET_VAL();
    // TODO: hwset_var_store();
    SetM0HWSET_Clean();
  }
}

uint32_t vcradio_get_received_len(void)
{
  return m_rx_buf_index;
}

static void _cent_on_pkt_rcvd(void)
{
  if (vcradio_get_received_len() == 3) {
    if (!is_ack()) {
      return;
    }
  }
  if (!m_rx_buf_overflow) {
    if (m_receive_handler != NULL) {
      m_receive_handler(vcradio_get_received_len());
    }
  }
}

static void _cent_on_rxe_rxcmp_event(void)
{
  uint8_t fcs_size;
  uint32_t packet_len;
  uint32_t remain_len;
  if (is_fcs_match()) {
    fcs_size = (fcs_type() == FCS_32) ? 4 : 2;
    packet_len = get_pkt_len();
    m_phr_len = get_phr_len();
    if ((m_phr_len != packet_len) |
      ((packet_len - fcs_size) > m_max_buffer_sz) |
      (packet_len < m_rx_buf_index)) {
      goto exit;
    }
    if (packet_len <= (m_rx_buf_index + fcs_size)) {
      // the trailing bytes in previous ISR_RXB_HITHR read may contains FCS bytes
      m_rx_buf_index = packet_len - fcs_size;
      _cent_on_pkt_rcvd();
      goto exit;
    }
    remain_len = packet_len - m_rx_buf_index;
    if (remain_len > (MAC_BUF_SIZE)) {
      goto exit;
    }
    cent_rxHi_receive((uint8_t *)&m_rx_buffer[m_rx_buf_index], remain_len);
    m_rx_buf_index += remain_len - fcs_size;
    g_rx_complete = 1;
    _cent_on_pkt_rcvd();
  }

exit:
  rfmbx_clear();
  g_rx_complete = 0;
  m_rx_buf_index = 0;
  m_rx_buf_overflow = false;
}

static void _cent_on_phy_event(RF_EVENT_T *pvnt)
{
  if (pvnt->param & PHY_INTERRUPT_CR0__RG_PHY_RX_PMD_IRQ_MASK) {
    m_rx_buf_index = 0;
    m_rx_buf_overflow = false;
  }

  if (pvnt->param & PHY_INTERRUPT_CR0__RG_PHY_RX_PHR_IRQ_MASK) {
    vcradio_host_rxled_on();
    m_timestamp = vcradio_host_get_timestamp();
    m_phr_len = get_phr_len();
  }

  if (pvnt->param & ModeSwitch_Timeout) {
  }

  if (pvnt->param & PHY_INTERRUPT_CR0__RG_PHY_RX_PKT_IRQ_MASK) {
    _cent_on_rxe_rxcmp_event();
    vcradio_host_rxled_off();
  }
}

void vcradio_isr(void)
{
  int rs = vcradio_lock_irq();
  RF_EVENT_T vnt;
  while ((rfmbx_get(&vnt)) == 0) {
    switch(vnt.cmd) {
      case RF_EVENT_PHY_IRQn:
        _cent_on_phy_event(&vnt);
        break;
      case RF_EVENT_M0_IRQn:
        _cent_on_m0_event(&vnt);
        break;
      default:
        break;
    }
  }
  vcradio_unlock_irq(rs);
  vcradio_host_txled_off();
}
