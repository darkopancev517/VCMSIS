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

#ifndef VC73XX_USTICKER_H
#define VC73XX_USTICKER_H

#include <stdint.h>
#include <stddef.h>
#include "device.h"
#include "pinmap.h"
#include "pinmap_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VC73XX_USTICKER_SECOND (937500UL) /* 120MHz SystemCoreClock */
#define VC73XX_USTICKER_WIDTH  (16UL)

void vc73xx_usticker_init(void);
void vc73xx_usticker_start(void);
void vc73xx_usticker_stop(void);
void vc73xx_usticker_set(uint32_t value);
void vc73xx_usticker_clear(void);
uint32_t vc73xx_usticker_read(void);

#ifdef __cplusplus
}
#endif

#endif /* VC73XX_USTICKER_H */
