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

#ifndef VC_ANA_H
#define VC_ANA_H

#include <stdint.h>
#include <stddef.h>
#include "device.h"
#include "pinmap.h"
#include "pinmap_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

void     vcana_init(void);
void     vcana_init_adc(int channel, uint32_t *frequency);
void     vcana_conti_mode_enable(void);
void     vcana_conti_mode_disable(void);
uint16_t vcana_mread(int channel);
void     vcana_set_gppll_120mhz(void);
void     vcana_set_gppll_150mhz(void);
void     vcana_set_gppll_200mhz(void);
void     vcana_set_bbpll_192mhz(void);
void     vcana_set_bbpll_300mhz(void);
void     vcana_set_adc_delay(uint8_t adc_clocks);

#ifdef __cplusplus
}
#endif

#endif /* VC_ANA_H */
