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

#ifndef VC_SPI_H
#define VC_SPI_H

#include <stdint.h>
#include <stddef.h>
#include "device.h"
#include "pinmap.h"
#include "pinmap_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t sckpol;
    uint32_t sckpha;
    uint32_t swap;
    uint32_t frequency;
    uint32_t spi_mode;
    uint32_t bit_order;
    uint32_t csgpio;
    uint32_t transfer_width;
} vcspi_cfg_t;

#define VCSPI_MODE_0 0 /* CPOL=0, CPHA=0 */
#define VCSPI_MODE_1 1 /* CPOL=0, CPHA=1 */
#define VCSPI_MODE_2 2 /* CPOL=1, CPHA=0 */
#define VCSPI_MODE_3 3 /* CPOL=1, CPHA=1 */

int      vcspi_init(int spi_id, vcspi_cfg_t *cfg);
int      vcspi_uninit(int spi_id);
void     vcspi_enable(int spi_id);
void     vcspi_disable(int spi_id);
void     vcspi_reset(int spi_id);
void     vcspi_power_on(int spi_id);
void     vcspi_power_off(int spi_id);
void     vcspi_format_mode(int spi_id, int mode);
uint32_t vcspi_update_frequency(int spi_id, uint32_t hz);
uint8_t  vcspi_master_write(int spi_id, const uint8_t tx_data);
int      vcspi_master_block_write(int spi_id,
                                  const char *tx_buffer,
                                  int tx_length,
                                  char *rx_buffer,
                                  int rx_length,
                                  char write_fill);

#ifdef __cplusplus
}
#endif

#endif /* VC_SPI_H */
