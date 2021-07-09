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

//#include "mbed_assert.h"
#include "gpio_api.h"
#include "gpio_irq_api.h"
#include "pinmap.h"
#include <stddef.h>
#include <string.h>

#include "vc73xx_gpio.h"

extern PinMode g_pin_mode[GPIO_PIN_COUNT];

vcgpio_mask_t m_gpio_initialized;
vcgpio_cfg_t  m_gpio_cfg[GPIO_PIN_COUNT];

gpio_irq_handler m_irq_handler;
uint32_t m_channel_ids[GPIO_PIN_COUNT] = {0};
vcgpio_mask_t m_gpio_irq_enabled;

static void gpio_pin_uninit(uint8_t pin);
static void gpio_apply_config(uint8_t pin);

void PMU_Handler(void);  /* GPIOA IRQ handler */
void GPIO_Handler(void); /* GPIOC IRQ handler */

uint32_t gpio_set(PinName pin)
{
    //MBED_ASSERT(pin != (PinName)NC);
    m_gpio_cfg[pin].used_as_gpio = true;
    m_gpio_cfg[pin].direction = PIN_INPUT;
    m_gpio_cfg[pin].used_as_irq = false;
    m_gpio_cfg[pin].irq_fall = false;
    m_gpio_cfg[pin].irq_rise = false;
    m_gpio_cfg[pin].irq_both = false;

    if (g_pin_mode[pin] == PullNone) {
        m_gpio_cfg[pin].pull = PullNone; 
    } else {
        m_gpio_cfg[pin].pull = g_pin_mode[pin];
    }

    return (uint32_t)(1 << pin);
}

int gpio_is_connected(const gpio_t *obj)
{
    return obj->pin != (PinName)NC;
}

void gpio_init(gpio_t *obj, PinName pin)
{
    obj->pin = pin;
    if (pin == (PinName)NC) {
        return;
    }
    //MBED_ASSERT((uint32_t)pin < GPIO_PIN_COUNT);

    m_gpio_cfg[obj->pin].used_as_gpio = true;
    m_gpio_cfg[obj->pin].direction = PIN_OUTPUT;

    if (g_pin_mode[obj->pin] == PullNone) {
        m_gpio_cfg[obj->pin].pull = PullNone; 
    } else {
        m_gpio_cfg[obj->pin].pull = g_pin_mode[obj->pin];
    }

    vcgpio_init(pin, &m_gpio_cfg[obj->pin]);
}

void gpio_free(gpio_t *obj)
{
    vcgpio_free(obj->pin);
}

void gpio_mode(gpio_t *obj, PinMode mode)
{
    //MBED_ASSERT(obj->pin != (PinName)NC);

    gpio_pin_uninit(obj->pin);

    m_gpio_cfg[obj->pin].pull = mode;
    pin_mode(obj->pin, mode);

    gpio_apply_config(obj->pin);
}

void gpio_dir(gpio_t *obj, PinDirection direction)
{
    //MBED_ASSERT(obj->pin != (PinName)NC);

    gpio_pin_uninit(obj->pin);

    m_gpio_cfg[obj->pin].direction = direction;
    gpio_apply_config(obj->pin);
}

void gpio_write(gpio_t *obj, int value)
{
    //MBED_ASSERT(obj->pin != (PinName)NC);
    if (value) {
        vcgpio_pin_set(obj->pin);
    } else {
        vcgpio_pin_clear(obj->pin);
    }
}

int gpio_read(gpio_t *obj)
{
    //MBED_ASSERT(obj->pin != (PinName)NC);
    if (m_gpio_cfg[obj->pin].direction == PIN_OUTPUT) {
        return vcgpio_pin_out_read(obj->pin);
    } else {
        return vcgpio_pin_read(obj->pin);
    }
}

/***********
  GPIO IRQ
***********/

int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id)
{
    if (pin == NC) {
        return -1;
    }
    uint8_t portNum = VC_PORT(obj->ch);
    if (portNum == PortA || portNum == PortC) {
        //MBED_ASSERT((uint32_t)pin < GPIO_PIN_COUNT);
        gpio_pin_uninit(pin); /* try to uninitialize gpio before a change. */
        m_gpio_cfg[pin].used_as_irq = true;
        m_gpio_cfg[pin].direction = PIN_INPUT;
        if (g_pin_mode[pin] == PullNone) {
            m_gpio_cfg[pin].pull = PullNone; 
        } else {
            m_gpio_cfg[pin].pull = g_pin_mode[pin];
        }
        obj->ch = pin;
        m_irq_handler = handler;
        m_channel_ids[pin] = id;
        gpio_apply_config(pin);
        return 0;
    } else {
        return -1;
    }
}

void gpio_irq_free(gpio_irq_t *obj)
{
    uint8_t portNum = VC_PORT(obj->ch);
    if (portNum == PortA || portNum == PortC) {
        vcgpio_in_uninit(obj->ch);
        m_gpio_cfg[obj->ch].used_as_irq = false;
        m_channel_ids[obj->ch] = 0;
        gpio_apply_config(obj->ch);
    }
}

void gpio_irq_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable)
{
    uint8_t portNum = VC_PORT(obj->ch);
    if (portNum == PortA || portNum == PortC) {
        vcgpio_cfg_t *cfg = &m_gpio_cfg[obj->ch];
        bool irq_enabled_before =
            (m_gpio_irq_enabled & ((vcgpio_mask_t)1UL << obj->ch)) &&
            (cfg->irq_rise || cfg->irq_fall || cfg->irq_both);

        if (event == IRQ_RISE) {
            cfg->irq_rise = enable ? true : false;
        } else if (event == IRQ_FALL) {
            cfg->irq_fall = enable ? true : false;
        }

        bool irq_enabled_after = cfg->irq_rise || cfg->irq_fall;

        if (irq_enabled_before != irq_enabled_after) {
            if (irq_enabled_after) {
                gpio_irq_enable(obj);
            } else {
                gpio_irq_disable(obj);
            }
        }
    }
}

void gpio_irq_enable(gpio_irq_t *obj)
{
    uint8_t portNum = VC_PORT(obj->ch);
    if (portNum == PortA || portNum == PortC) {
        m_gpio_irq_enabled |= ((vcgpio_mask_t)1UL << obj->ch);
        if (m_gpio_cfg[obj->ch].irq_rise || m_gpio_cfg[obj->ch].irq_fall) {
            vcgpio_irq_enable(portNum);
        }
    }
}

void gpio_irq_disable(gpio_irq_t *obj)
{
    uint8_t portNum = VC_PORT(obj->ch);
    if (portNum == PortA || portNum == PortC) {
        m_gpio_irq_enabled &= ~((vcgpio_mask_t)1UL << obj->ch);
        vcgpio_irq_disable(portNum);
    }
}

// Helper functions

static void gpio_pin_uninit(uint8_t pin)
{
    if (m_gpio_initialized & ((vcgpio_mask_t)1UL << pin)) {
        if ((m_gpio_cfg[pin].direction == PIN_OUTPUT) && (!m_gpio_cfg[pin].used_as_irq)) {
            vcgpio_out_uninit(pin);
        } else if (m_gpio_cfg[pin].used_as_irq) {
            vcgpio_in_uninit(pin);
        }
    }
}

static void gpio_apply_config(uint8_t pin)
{
    if (m_gpio_cfg[pin].used_as_gpio || m_gpio_cfg[pin].used_as_irq) {
        vcgpio_init(pin, &m_gpio_cfg[pin]);
        m_gpio_initialized |= ((vcgpio_mask_t)1UL << pin);
    } else {
        m_gpio_initialized &= ~((vcgpio_mask_t)1UL << pin);
    }
}

void PMU_Handler(void)   /* GPIOA IRQ handler */
{
    for (uint8_t pin= 0; pin < 16; pin++) {
        if (VC_GPIOA->INT & VC_GPIO_IOX_INT_IOXINT_Msk(pin)) {
            uint32_t temp = VC_GPIOA->INT;
            temp |= (1UL << pin);
            VC_GPIOA->INT = temp;
            gpio_irq_event event = (VC_GPIOA->DAT & VC_GPIO_IOX_DAT_IOXDAT_Msk(pin)) ? IRQ_FALL : IRQ_RISE;
            if (m_gpio_irq_enabled & ((vcgpio_mask_t)1UL << pin)) {
                if (((event == IRQ_RISE) && m_gpio_cfg[pin].irq_rise)
                        || ((event == IRQ_FALL) && m_gpio_cfg[pin].irq_fall)) {
                    m_irq_handler(m_channel_ids[pin], event);
                }
            }
        }
    }
}

void GPIO_Handler(void) /* GPIOC IRQ handler */
{
    for (uint8_t pin = 0; pin < 16; pin++) {
        if (VC_GPIOC->INT & VC_GPIO_IOX_INT_IOXINT_Msk(pin)) {
            uint32_t temp = VC_GPIOC->INT;
            temp |= (1UL << pin);
            VC_GPIOC->INT = temp;
            gpio_irq_event event = (VC_GPIOC->DAT & VC_GPIO_IOX_DAT_IOXDAT_Msk(pin)) ? IRQ_FALL : IRQ_RISE;
            if (m_gpio_irq_enabled & ((vcgpio_mask_t)1UL << pin)) {
                if (((event == IRQ_RISE) && m_gpio_cfg[pin].irq_rise)
                        || ((event == IRQ_FALL) && m_gpio_cfg[pin].irq_fall)) {
                    m_irq_handler(m_channel_ids[pin], event);
                }
            }
        }
    }
}
