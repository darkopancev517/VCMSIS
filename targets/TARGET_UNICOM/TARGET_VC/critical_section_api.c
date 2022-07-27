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

#include "critical_section_api.h"
#include "device.h"
#include "cmsis.h"

static unsigned int m_irqmask;
static bool m_in_critical_section = false;

void hal_critical_section_enter(void)
{
    m_in_critical_section = true;
    m_irqmask = __get_PRIMASK();
    __disable_irq();
}

void hal_critical_section_exit(void)
{
    m_in_critical_section = false;
    __set_PRIMASK(m_irqmask);
}

bool hal_in_critical_section(void)
{
    return m_in_critical_section;
}
