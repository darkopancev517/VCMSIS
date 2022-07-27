/*
 * Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved.
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

#ifndef HAL_RF_H
#define HAL_RF_H

#include <stdio.h>
#include <stdint.h>

#include "vc_mbox.h"
#include "vc_misc.h"

#ifdef __cplusplus
extern "C" {
#endif

//for mcu vc7351
void hal_rf_init(void);

uint64_t hal_rf_int_get_sts();

void hal_rf_int_clear_sts(uint64_t sts);

void hal_rf_reset_assert(void);

void hal_rf_load_code(void);

int _hal_rf_read(const char *msg, uint8_t *dst, uint32_t srcm0, uint32_t blen);
#define hal_rf_read(dst, srcm0, blen) _hal_rf_read(__func__, dst, srcm0, blen)

int _hal_rf_write(const char *msg, uint32_t dstm0, uint8_t *src, uint32_t blen);
#define hal_rf_write(dstm0, src, blen) _hal_rf_write(__func__, dstm0, src, blen)

int _hal_rf_get(const char *msg, uint32_t srcm0, uint32_t *pxw);
#define hal_rf_get(srcm0, pxw) _hal_rf_get(__func__, srcm0, pxw)

int _hal_rf_put(const char *msg, uint32_t dstm0, uint32_t xw);
#define hal_rf_put(dstm0, xw) _hal_rf_put(__func__, dstm0, xw)

#ifdef __cplusplus
}
#endif

#endif // HAL_RF_H
