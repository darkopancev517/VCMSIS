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

#ifndef VC_RADIO_H
#define VC_RADIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FSK_MODE  0
#define OFDM_MODE 1

typedef void (*receive_handler)(int rx_length);

void     vcradio_init(uint8_t *rxbuffer, int size, receive_handler handler);
int      vcradio_transmit(uint8_t *txdata, uint32_t txlen);

void     vcradio_load_dsp(void);
void     vcradio_reinit(void);
int      vcradio_lock_irq(void);
void     vcradio_unlock_irq(int rs);
void     vcradio_receive_on(void);
uint32_t vcradio_get_dsp_value(void);
void     vcradio_set_data_whitening(uint16_t bEn);
void     vcradio_set_RFMode(uint32_t _rfmode);
void     vcradio_set_opt_mcs(uint32_t _opt, uint32_t _mcs);
uint32_t vcradio_get_received_len(void);
void     vcradio_set_fcs(uint32_t fcs);
uint32_t vcradio_get_fcs(void);
void     vcradio_set_preamble_len(uint16_t pmblen);
uint16_t vcradio_get_preamble_len(void);
void     vcradio_set_data_rate(uint32_t rate);
int      vcradio_set_frequency(uint32_t freq);
uint32_t vcradio_get_frequency(void);

void     vcradio_host_init(void);
void     vcradio_host_event_int_enable(void);
uint32_t vcradio_host_get_usec_now(void);
void     vcradio_host_rxled_off();
void     vcradio_host_rxled_on();
void     vcradio_host_txled_off();
void     vcradio_host_txled_on();
uint32_t vcradio_host_get_timestamp(void);

uint32_t OFDM_Counter_Reset(void);

#ifdef __cplusplus
}
#endif

#endif /* VC_RADIO_H */
