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

#ifndef HAL_MISC_H
#define HAL_MISC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool hal_misc_assert_m0_addr_range(uint32_t addrm0);

void _hal_misc_m0mem_read(const char *msg, uint32_t *dst, uint32_t srcm0, uint32_t len);
#define hal_misc_m0mem_read(dst, srcm0, len) _hal_misc_m0mem_read(__func__, dst, srcm0, len)

void _hal_misc_m0mem_write(const char *msg, uint32_t dstm0, uint32_t *src, uint32_t len);
#define hal_misc_m0mem_write(dstm0, src, len) _hal_misc_m0mem_write(__func__, dstm0, src, len)

uint32_t _hal_misc_m0mem_get(const char *msg, uint32_t srcm0);
#define hal_misc_m0mem_get(srcm0) _hal_misc_m0mem_get(__func__, srcm0)

void _hal_misc_m0mem_put(const char *msg, uint32_t dstm0, uint32_t xw);
#define hal_misc_m0mem_put(dstm0, xw) _hal_misc_m0mem_put(__func__, dstm0, xw)

void hal_misc_m0_start(bool bEn);

#ifdef __cplusplus
}
#endif

#endif /* HAL_MISC_H */
