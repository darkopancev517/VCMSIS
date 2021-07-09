//#include "mbed_assert.h"
#include "gpio_api.h"
#include "gpio_irq_api.h"
#include "pinmap.h"
#include <stddef.h>

#include "vc73xx_gpio.h"

//static vcgpio_mask_t m_gpio_initialized;
static vcgpio_cfg_t  m_gpio_cfg[GPIO_PIN_COUNT];

//static gpio_irq_handler m_irq_handler;
//static uint32_t m_channel_ids[GPIO_PIN_COUNT] = {0};
//static vcgpio_mask_t m_gpio_irq_enabled;

void PMU_Handler(void);  /* GPIOA IRQ handler */
void GPIO_Handler(void); /* GPIOC IRQ handler */

uint32_t gpio_set(PinName pin)
{
    //MBED_ASSERT(pin != (PinName)NC);
    m_gpio_cfg[pin].used_as_gpio = true;
    m_gpio_cfg[pin].direction = PIN_INPUT;
    m_gpio_cfg[pin].pull = PullNone;
    m_gpio_cfg[pin].used_as_irq = false;
    m_gpio_cfg[pin].irq_fall = false;
    m_gpio_cfg[pin].irq_rise = false;
    m_gpio_cfg[pin].irq_both = false;

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

    vcgpio_init(pin);

    m_gpio_cfg[obj->pin].used_as_gpio = true;
}

void gpio_free(gpio_t *obj)
{
    (void)obj;
}

void gpio_mode(gpio_t *obj, PinMode mode)
{
    //MBED_ASSERT(obj->pin != (PinName)NC);

    //vcgpio_pin_uninit(obj->pin);

    m_gpio_cfg[obj->pin].pull = mode;
    //gpio_apply_config(obj->pin);
}

void gpio_dir(gpio_t *obj, PinDirection direction)
{
    //MBED_ASSERT(obj->pin != (PinName)NC);

    //vcgpio_pin_uninit(obj->pin);

    m_gpio_cfg[obj->pin].direction = direction;
    //gpio_apply_config(obj->pin);
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
