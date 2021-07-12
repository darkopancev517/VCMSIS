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

#include "pinmap_ex.h"

const PinMapUART PinMap_UART[] = {
    {PB_2, PA_12, 0, (int)UART0_IRQn},
    {PB_3, PA_13, 1, (int)UART1_IRQn},
    {PB_4, PA_14, 2, (int)UART2_IRQn},
    {PB_5, PA_15, 3, (int)UART3_IRQn},
    {PB_6, PB_0,  4, (int)UART4_IRQn},
    {PB_7, PB_1,  5, (int)UART5_IRQn},
    {PB_8, PB_15, 6, (int)UART6_IRQn},
    {NC, NC, 0, 0}
};

int pin_instance_uart(PinName tx, PinName rx)
{
    int instance = NC;
    for (int i = 0; ((PinMap_UART[i].tx != NC) && (PinMap_UART[i].rx != NC)); i++) {
        if ((PinMap_UART[i].tx == tx) && (PinMap_UART[i].rx == rx)) {
            instance = PinMap_UART[i].instance;
            break;
        }
    }
    return instance;
}
