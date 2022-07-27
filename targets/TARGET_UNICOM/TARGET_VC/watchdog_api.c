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

#include "watchdog_api.h"

#if DEVICE_WATCHDOG

#include "vc_wdt.h"

watchdog_status_t hal_watchdog_init(const watchdog_config_t *config)
{
    vcwdt_period_t period;

    if (config->timeout_ms >= 2000) {
        period = VCWDT_PERIOD_2_SECS;
    } else if (config->timeout_ms < 2000 && config->timeout_ms >= 1000) {
        period = VCWDT_PERIOD_1_SECS;
    } else if (config->timeout_ms < 1000 && config->timeout_ms >= 500) {
        period = VCWDT_PERIOD_0_5_SECS;
    } else if (config->timeout_ms < 500 && config->timeout_ms >= 250) {
        period = VCWDT_PERIOD_0_25_SECS;
    } else {
        return WATCHDOG_STATUS_INVALID_ARGUMENT;
    }

    vcwdt_set_period(period);

    return WATCHDOG_STATUS_OK;
}

void hal_watchdog_kick(void)
{
    vcwdt_clear();
    vcwdt_enable();
}

watchdog_status_t hal_watchdog_stop(void)
{
    vcwdt_disable();
    return WATCHDOG_STATUS_OK;
}

uint32_t hal_watchdog_get_reload_value(void)
{
    return vcwdt_get_counter();
}

watchdog_features_t hal_watchdog_get_platform_features(void)
{
    watchdog_features_t features;
    features.max_timeout = 2000;
    features.update_config = false;
    features.disable_watchdog = true;
    return features;
}

#endif
