/*
 * Copyright (c) 2022 Unicom Semiconductor, Inc. All rights reserved.
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

#include "vc_spi.h"

static void _spi_sfio_enable(int spi_id);
static uint8_t _spi_get_clock_divider(uint32_t *hz);
static void _spi_transmit_byte(int spi_id, const uint8_t byte);
static uint8_t _spi_receive_byte(int spi_id);

int vcspi_init(int spi_id, vcspi_cfg_t *cfg)
{
    if ((spi_id == 0 || spi_id > DEVICE_SPI_COUNT) || (cfg == NULL))
        return -1;

    uint32_t temp = 0;

    vcspi_power_on(spi_id);

    /* Corrected frequency and get spi clock divider */
    uint32_t correct_freq = cfg->frequency;
    uint8_t clk_div = _spi_get_clock_divider(&correct_freq);
    cfg->frequency = correct_freq;

    temp = VC_SPI(spi_id)->CTRL;
    temp &= ~VC_SPI_CTRL_CLKDIVL_Msk;
    temp &= ~VC_SPI_CTRL_CLKDIVH_Msk;
    temp &= ~VC_SPI_CTRL_SCKPOL_Msk;
    temp &= ~VC_SPI_CTRL_SCKPHA_Msk;
    temp &= ~VC_SPI_CTRL_WIDTH_Msk;
    temp &= ~VC_SPI_CTRL_MOD_Msk;
    temp &= ~VC_SPI_CTRL_SWAP_Msk;
    temp &= ~VC_SPI_CTRL_CSGPIO_Msk;
    temp &= ~VC_SPI_CTRL_LSBF_Msk;
    temp &= ~VC_SPI_CTRL_SPIEN_Msk;

    temp |= ((clk_div & 0xFUL) << VC_SPI_CTRL_CLKDIVL_Pos);             /* low-nibble */
    temp |= (((clk_div >> 4) & 0xFUL) << VC_SPI_CTRL_CLKDIVH_Pos);      /* high-nible */
    temp |= (cfg->sckpol << VC_SPI_CTRL_SCKPOL_Pos);
    temp |= (cfg->sckpha << VC_SPI_CTRL_SCKPHA_Pos);
    temp |= (cfg->transfer_width << VC_SPI_CTRL_WIDTH_Pos);
    temp |= (cfg->spi_mode << VC_SPI_CTRL_MOD_Pos);
    temp |= (cfg->swap << VC_SPI_CTRL_SWAP_Pos);
    temp |= (cfg->csgpio << VC_SPI_CTRL_CSGPIO_Pos);
    temp |= (cfg->bit_order << VC_SPI_CTRL_LSBF_Pos);

    VC_SPI(spi_id)->CTRL = temp;

    /* Config SPI pin special function */
    _spi_sfio_enable(spi_id);

    return spi_id;
}

int vcspi_uninit(int spi_id)
{
    return spi_id;
}

void vcspi_enable(int spi_id)
{
    uint32_t temp = VC_SPI(spi_id)->CTRL;
    temp |= (1UL << VC_SPI_CTRL_SPIEN_Pos);
    VC_SPI(spi_id)->CTRL = temp;
}

void vcspi_disable(int spi_id)
{
    uint32_t temp = VC_SPI(spi_id)->CTRL;
    temp &= ~VC_SPI_CTRL_SPIEN_Msk;
    VC_SPI(spi_id)->CTRL = temp;
}

void vcspi_reset(int spi_id)
{
    uint32_t temp = VC_SPI(spi_id)->CTRL;
    temp |= (1UL << VC_SPI_CTRL_SPIRST_Pos);
    VC_SPI(spi_id)->CTRL = temp;
}

void vcspi_power_on(int spi_id)
{
    uint32_t temp = VC_MISC2->PCLKEN;
    temp |= (1UL << VC_MISC2_PCLKEN_SPI_Pos(spi_id));
    VC_MISC2->CLKEN_UNLOCK = (0x55AAAA55 << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos);
    VC_MISC2->PCLKEN = temp;
}

void vcspi_power_off(int spi_id)
{
    uint32_t temp = VC_MISC2->PCLKEN;
    temp &= ~VC_MISC2_PCLKEN_SPI_Msk(spi_id);
    VC_MISC2->CLKEN_UNLOCK = (0x55AAAA55 << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos);
    VC_MISC2->PCLKEN = temp;
}

void vcspi_format_mode(int spi_id, int mode)
{
    uint32_t temp = VC_SPI(spi_id)->CTRL;

    temp &= ~VC_SPI_CTRL_SCKPOL_Msk;
    temp &= ~VC_SPI_CTRL_SCKPHA_Msk;

    switch (mode) {
    case VCSPI_MODE_0:
        temp |= (0UL << VC_SPI_CTRL_SCKPOL_Pos);
        temp |= (0UL << VC_SPI_CTRL_SCKPHA_Pos);
        break;

    case VCSPI_MODE_1:
        temp |= (0UL << VC_SPI_CTRL_SCKPOL_Pos);
        temp |= (1UL << VC_SPI_CTRL_SCKPHA_Pos);
        break;

    case VCSPI_MODE_2:
        temp |= (1UL << VC_SPI_CTRL_SCKPOL_Pos);
        temp |= (0UL << VC_SPI_CTRL_SCKPHA_Pos);
        break;

    case VCSPI_MODE_3:
        temp |= (1UL << VC_SPI_CTRL_SCKPOL_Pos);
        temp |= (1UL << VC_SPI_CTRL_SCKPHA_Pos);
        break;

    default:
        break;
    }

    VC_SPI(spi_id)->CTRL = temp;
}

uint32_t vcspi_update_frequency(int spi_id, uint32_t hz)
{
    uint32_t correct_freq = hz;
    uint8_t clk_div = _spi_get_clock_divider(&correct_freq);
    vcspi_disable(spi_id);
    uint32_t temp = VC_SPI(spi_id)->CTRL;
    temp &= ~VC_SPI_CTRL_CLKDIVL_Msk;
    temp &= ~VC_SPI_CTRL_CLKDIVH_Msk;
    temp |= ((clk_div & 0xFUL) << VC_SPI_CTRL_CLKDIVL_Pos);             /* low-nibble */
    temp |= (((clk_div >> 4) & 0xFUL) << VC_SPI_CTRL_CLKDIVH_Pos);      /* high-nible */
    VC_SPI(spi_id)->CTRL = temp;
    vcspi_reset(spi_id);
    vcspi_enable(spi_id);
    return correct_freq;
}

uint8_t vcspi_master_write(int spi_id, const uint8_t tx_data)
{
    _spi_transmit_byte(spi_id, tx_data);
    return _spi_receive_byte(spi_id);
}

static void _spi_transmit_byte(int spi_id, const uint8_t byte)
{
    // wait until transmit fifo is empty
    while ((VC_SPI(spi_id)->TXSTS & VC_SPI_TXSTS_TXEMPTY_Msk) == 0);
    VC_SPI(spi_id)->TXDAT = byte;
}

static uint8_t _spi_receive_byte(int spi_id)
{
    // wait until receive fifo not empty
    while ((VC_SPI(spi_id)->RXSTS & VC_SPI_RXSTS_RXFFLAG_Msk) == 0);
    return (uint8_t)VC_SPI(spi_id)->RXDAT;
}

int vcspi_master_block_write(int spi_id,
                             const char *tx_buffer,
                             int tx_length,
                             char *rx_buffer,
                             int rx_length,
                             char write_fill)
{
    int tx_offset = 0;
    int rx_offset = 0;
    int i = 0;

    /* Loop until all data is sent and recived */
    while ((tx_length > 0) || (rx_length > 0)) {

        /* Check if tx_length is larger than 255 and if so, limit to 255 */
        int tx_actual_length = (tx_length > 255) ? 255 : tx_length;

        /* Set tx buffer pointer. Set to NULL if no data is going to be transmitted */
        const uint8_t *tx_actual_buffer = (tx_actual_length > 0) ?
                                          (const uint8_t *)(tx_buffer + tx_offset) :
                                          NULL;

        /* Check if rx_length is larger than 255 and if so, limit to 255 */
        int rx_actual_length = (rx_length > 255) ? 255 : rx_length;

        /* Set rx buffer pointer. Set to NULL if no data is going to be received */
        uint8_t *rx_actual_buffer = (rx_actual_length > 0) ?
                                    (uint8_t *)(rx_buffer + rx_offset) :
                                    NULL;

        /* Blocking transfer */
        for (i = 0; i < tx_actual_length; i++) {
            _spi_transmit_byte(spi_id, tx_actual_buffer[i]);
            (void) _spi_receive_byte(spi_id);
        }
        /* Blocking receive */
        for (i = 0; i < rx_actual_length; i++) {
            _spi_transmit_byte(spi_id, write_fill);
            rx_actual_buffer[i] = _spi_receive_byte(spi_id);
        }

        /* Update loop variables */
        tx_length -= tx_actual_length;
        tx_offset += tx_actual_length;

        rx_length -= rx_actual_length;
        rx_offset += rx_actual_length;
    }

    return (rx_offset < tx_offset) ? tx_offset : rx_offset;
}

static void _spi_sfio_enable(int spi_id)
{
    uint32_t temp = 0;

    switch (spi_id) {
    case 1:
        /* SPI1 SCK MISO MOSI - IOB10 IOB11 IOB12 */
        temp = VC_GPIOB->SEL1;
        temp &= ~VC_GPIO_IOB_SEL1_IOBx_SEL_Msk(10);
        temp &= ~VC_GPIO_IOB_SEL1_IOBx_SEL_Msk(11);
        temp &= ~VC_GPIO_IOB_SEL1_IOBx_SEL_Msk(12);
        temp |= VC_GPIO_SEL1_IOB10_SPI1_CLK;
        temp |= VC_GPIO_SEL1_IOB11_SPI1_MISO;
        temp |= VC_GPIO_SEL1_IOB12_SPI1_MOSI;
        VC_GPIOB->SEL1 = temp;
        break;

    case 2:
        /* SPI2 SCK MISO MOSI - IOC1 IOC2 IOC3 */
        temp = VC_GPIOC->SEL0;
        temp &= ~VC_GPIO_IOC_SEL0_IOCx_SEL_Msk(1);
        temp &= ~VC_GPIO_IOC_SEL0_IOCx_SEL_Msk(2);
        temp &= ~VC_GPIO_IOC_SEL0_IOCx_SEL_Msk(3);
        temp |= VC_GPIO_SEL0_IOC1_SPI2_CLK;
        temp |= VC_GPIO_SEL0_IOC2_SPI2_MISO;
        temp |= VC_GPIO_SEL0_IOC3_SPI2_MOSI;
        VC_GPIOC->SEL0 = temp;
        break;

    case 3:
        /* SPI3 SCK MISO MOSI - IOC9 IOC10 IOC11 */
        temp = VC_GPIOC->SEL1;
        temp &= ~VC_GPIO_IOC_SEL1_IOCx_SEL_Msk(9);
        temp &= ~VC_GPIO_IOC_SEL1_IOCx_SEL_Msk(10);
        temp &= ~VC_GPIO_IOC_SEL1_IOCx_SEL_Msk(11);
        temp |= VC_GPIO_SEL1_IOC9_SPI3_CLK;
        temp |= VC_GPIO_SEL1_IOC10_SPI3_MISO;
        temp |= VC_GPIO_SEL1_IOC11_SPI3_MOSI;
        VC_GPIOC->SEL1 = temp;
        break;

    default:
        break;
    }
}

static uint8_t _spi_get_clock_divider(uint32_t *hz)
{
    uint8_t divider = 0;
    uint32_t old_hz = *hz;
    uint32_t new_hz = 0;

    /* APBCLK = SystemCoreClock / 2 = 120MHz / 2 = 60MHz */
    /* SPICLK = APBCLK / (divider + 1) */

    /* Convert frequency and return the clock divider */
    if (old_hz < 500000) {
        new_hz = 250000;                /* 250KHz */
        divider = 240 - 1;
    } else if (old_hz < 1000000) {
        new_hz = 500000;                /* 500KHz */
        divider = 120 - 1;
    } else if (old_hz < 2000000) {
        new_hz = 1000000;               /* 1MHz */
        divider = 60 - 1;
    } else if (old_hz < 4000000) {
        new_hz = 2000000;               /* 2MHz */
        divider = 30 - 1;
    } else if (old_hz < 6000000) {
        new_hz = 4000000;               /* 4MHz */
        divider = 15 - 1;
    } else if (old_hz < 10000000) {
        new_hz = 6000000;               /* 6MHz */
        divider = 10 - 1;
    } else if (old_hz < 12000000) {
        new_hz = 10000000;              /* 10MHz */
        divider = 6 - 1;
    } else {
        new_hz = 12000000;              /* 12MHz */
        divider = 5 - 1;
    }

    *hz = new_hz;

    return divider;
}
