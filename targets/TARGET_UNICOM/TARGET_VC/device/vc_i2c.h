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

#ifndef VC_I2C_H
#define VC_I2C_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "device.h"
#include "pinmap.h"
#include "pinmap_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

void    vci2c_init(int i2c_id, uint32_t *freq);
void    vci2c_power_on(int i2c_id);
void    vci2c_power_off(int i2c_id);
void    vci2c_enable(int i2c_id);
void    vci2c_disable(int i2c_id);
void    vci2c_ack_enable(int i2c_id);
void    vci2c_ack_disable(int i2c_id);
int     vci2c_send_start(int i2c_id);
int     vci2c_send_stop(int i2c_id);
uint8_t vci2c_get_status(int i2c_id);
int     vci2c_send_byte(int i2c_id, uint8_t data);
uint8_t vci2c_read_byte(int i2c_id);

#ifdef __cplusplus
}
#endif

#endif /* VC_I2C_H */
