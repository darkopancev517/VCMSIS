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

#include "spi_api.h"

#if DEVICE_SPI

#include "vc_spi.h"
#include "vc_gpio.h"

typedef struct {
    struct spi_s *owner;
} vcspi_state_t;

static vcspi_state_t vcspi_state[4] = { 0 };

static void spi_configure_driver_instance(spi_t *obj);

void spi_get_capabilities(PinName ssel, bool slave, spi_capabilities_t *cap)
{
    if (slave) {
        cap->minimum_frequency = 250000;            // 250 KHz
        cap->maximum_frequency = 30000000;          // 30 MHz
        cap->word_length = 0x00000080;              // 8 bit symbols
        cap->support_slave_mode = false;            // to be determined later based on ssel
        cap->hw_cs_handle = false;                  // to be determined later based on ssel
        cap->slave_delay_between_symbols_ns = 2500; // 2.5 us
        cap->clk_modes = 0x0f;                      // all clock modes
        cap->tx_rx_buffers_equal_length = true;     // rx/tx buffers must have same sizes
        cap->async_mode = false;                    // not supported yet
    } else {
        cap->minimum_frequency = 937500;            // 937500 Hz
        cap->maximum_frequency = 7500000;           // 7.5 MHz
        cap->word_length = 0x00000080;              // 8 bit symbols
        cap->support_slave_mode = false;            // to be determined later based on ssel
        cap->hw_cs_handle = false;                  // to be determined later based on ssel
        cap->slave_delay_between_symbols_ns = 0;    // irrelevent in master mode
        cap->clk_modes = 0x0f;                      // all clock modes
        cap->tx_rx_buffers_equal_length = true;     // rx/tx buffers must have same sizes
        cap->async_mode = false;                    // not supported yet
    }

    if (ssel != NC) {
#if DEVICE_SPISLAVE
        cap->support_slave_mode = true;
#endif
        cap->hw_cs_handle = true;
    }
}

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
    struct spi_s *spi_inst = obj;

    /* Get instance based on requested pins */
    spi_inst->instance = pin_instance_spi(sclk, miso, mosi);

    if (spi_inst->instance == 0 || spi_inst->instance > DEVICE_SPI_COUNT) {
        /* not supported SPI0 or pin definitions is wrong */
        return;
    }

    /* Store chip select separately for manual enabling */
    spi_inst->cs = ssel;

    /* Store pins except chip select */
    spi_inst->miso = miso;
    spi_inst->mosi = mosi;
    spi_inst->sck = sclk;
    spi_inst->cpha = 0;
    spi_inst->cpol = 0;
    spi_inst->frequency = 3750000;
    spi_inst->mode = 0;             /* 0: master mode, 1: slave mode */
    spi_inst->bit_order = 0;        /* 0: MSB first, 1: LSB first */
    spi_inst->csgpio = 1;           /* 0: SPI H/W, 1: GPIO setting */
    spi_inst->width = 0;            /* 0: 8 bits mode transfer width */
    spi_inst->swap = 0;

    spi_inst->update = true;

    /* Configure SPI peripheral */
    spi_configure_driver_instance(obj);

    /* Configure GPIO pin if chip select has been set */
    if (spi_inst->cs != NC) {
        vcgpio_cfg_t cfg = {
            .used_as_gpio = true,
            .direction = PIN_OUTPUT,
            .pull = PullNone,
        };
        vcgpio_init(spi_inst->cs, &cfg);
        vcgpio_pin_set(spi_inst->cs);
    }
}

void spi_free(spi_t *obj)
{
    struct spi_s *spi_inst = obj;
    int instance = spi_inst->instance;
    vcspi_uninit(instance);
}

void spi_format(spi_t *obj, int bits, int mode, int slave)
{
    (void) bits;    /* SPI module only support 8 bit transfers */
    (void) slave;   /* SPI module doesn't support Mbed HAL Slave API */
    vcspi_format_mode(obj->instance, mode);
}

void spi_frequency(spi_t *obj, int hz)
{
    struct spi_s *spi_inst = obj;
    int instance = spi_inst->instance;
    uint32_t correct_hz = vcspi_update_frequency(instance, hz);
    if (correct_hz != hz) {
        spi_inst->frequency = correct_hz;
    }
}

/** Write a byte out in master mode and receive a value */
int spi_master_write(spi_t *obj, int value)
{
    struct spi_s *spi_inst = obj;
    int instance = spi_inst->instance;

    /* Local variables used in transfer */
    const uint8_t tx_data = (uint8_t) value;
    uint8_t rx_data;

    /* Configure peripheral if necessary */
    spi_configure_driver_instance(obj);

    /* Manually clear chip select pin if defined */
    if (spi_inst->cs != NC) {
        vcgpio_pin_clear(spi_inst->cs);
    }

    /* Transfer 1 byte */
    rx_data = vcspi_master_write(instance, tx_data);

    /* Manually set chip select pin if defined */
    if (spi_inst->cs != NC) {
        vcgpio_pin_set(spi_inst->cs);
    }

    return rx_data;
}

int spi_master_block_write(spi_t *obj,
                           const char *tx_buffer,
                           int tx_length,
                           char *rx_buffer,
                           int rx_length,
                           char write_fill)
{
    struct spi_s *spi_inst = obj;
    int instance = spi_inst->instance;

    /* Configure peripheral if necessary */
    spi_configure_driver_instance(obj);

    /* Manually clear chip select pin if defined */
    if (spi_inst->cs != NC) {
        vcgpio_pin_clear(spi_inst->cs);
    }

    int res = vcspi_master_block_write(instance,
                                       tx_buffer,
                                       tx_length,
                                       rx_buffer,
                                       rx_length,
                                       write_fill);

    /* Manually set chip select pin if defined */
    if (spi_inst->cs != NC) {
        vcgpio_pin_set(spi_inst->cs);
    }

    return res;
}

int spi_busy(spi_t *obj)
{
    /* Legacy API call. Always return zero */
    return 0;
}

uint8_t spi_get_module(spi_t *obj)
{
    struct spi_s *spi_inst = obj;
    return spi_inst->instance;
}

static void spi_configure_driver_instance(spi_t *obj)
{
    struct spi_s *spi_inst = obj;
    int instance = spi_inst->instance;
    if ((spi_inst != vcspi_state[instance].owner) || (spi_inst->update)) {
        spi_inst->update = false;
        vcspi_disable(instance);
        vcspi_cfg_t spi_cfg = {
            .sckpha = spi_inst->cpha,
            .sckpol = spi_inst->cpol,
            .swap = spi_inst->swap,
            .frequency = spi_inst->frequency,
            .spi_mode = spi_inst->mode,
            .bit_order = spi_inst->bit_order,
            .csgpio = spi_inst->csgpio,
            .transfer_width = spi_inst->width
        };
        vcspi_init(instance, &spi_cfg);
        vcspi_reset(instance);
        vcspi_enable(instance);
        /* Update frequency if it was corrected by the driver */
        if (spi_cfg.frequency != spi_inst->frequency) {
            spi_inst->frequency = spi_cfg.frequency;
        }
        vcspi_state[instance].owner = spi_inst;
    }
}

#endif /* #if DEVICE_SPI */
