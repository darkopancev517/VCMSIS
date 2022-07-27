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

#include "analogin_api.h"

#if DEVICE_ANALOGIN

#include "vc_ana.h"

typedef struct {
    struct analogin_s *owner;
} vcanalogin_state_t;

static vcanalogin_state_t vcanalogin_state[8] = { 0 };

static void _analogin_configure_driver_instance(analogin_t *obj);

void analog_init(analogin_t *obj, PinName pin)
{
    struct analogin_s *ana_inst = obj;
    int instance = pin_instance_adc(pin);
    if (instance == NC) {
        return; /* Invalid ADC Pin */
    }

    /* Initialize ADC object */
    ana_inst->instance = instance;
    ana_inst->pin = pin;
    if (!ana_inst->frequency) {
        ana_inst->frequency = 1000000; /* 1MHz */
    }
    ana_inst->continous_mode = false;
    ana_inst->update = true;

    _analogin_configure_driver_instance(obj);
}

void analogin_free(analogin_t *obj)
{
    (void) obj;
}

uint16_t analogin_read_u16(analogin_t *obj)
{
    struct analogin_s *ana_inst = obj;
    int instance = ana_inst->instance;
    return vcana_mread(instance);
}

const PinMap vcadc_pinmap[] = {
    {PA_0, 0, 0},
    {PA_1, 0, 0},
    {PA_2, 0, 0},
    {PA_3, 0, 0},
    {PA_4, 0, 0},
    {PA_8, 0, 0},
    {PC_6, 0, 0},
    {PC_12, 0, 0},
    {NC, NC, 0}
};

/** Get the pins that support analogin
 *
 * Return a PinMap array of pins that support analogin. The
 * array is terminated with {NC, NC, 0}.
 *
 * @return PinMap array
 */
const PinMap *analogin_pinmap(void)
{
    return vcadc_pinmap;
}

static void _analogin_configure_driver_instance(analogin_t *obj)
{
    struct analogin_s *ana_inst = obj;
    int instance = ana_inst->instance;
    if ((ana_inst != vcanalogin_state[instance].owner) || (ana_inst->update)) {
        ana_inst->update = false;
        vcana_init_adc(instance, &ana_inst->frequency);
        vcanalogin_state[instance].owner = ana_inst;
    }
}

#endif /* #if DEVICE_ANALOGIN */
