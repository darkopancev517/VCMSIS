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

#include "vc_uart.h"
#include "vc_gpio.h"

static void _uart_sfio_enable(int uart_id);

int vcuart_init(int uart_id, uint32_t baudrate, uint8_t parity, uint8_t databits, uint8_t stopbits)
{
  uint32_t temp = 0;

  if (uart_id == NC) {
    return -1;
  }

  vcuart_power_on(uart_id);

  temp = VC_UART(uart_id)->CTRL;
  temp &= ~VC_UART_CTRL_TXEN_Msk;
  temp &= ~VC_UART_CTRL_RXEN_Msk;
  temp |= (1UL << VC_UART_CTRL_TXEN_Pos);
  temp |= (1UL << VC_UART_CTRL_RXEN_Pos);
  VC_UART(uart_id)->CTRL = temp;

  /* Default LSB transmit first */
  temp = VC_UART(uart_id)->CTRL2;
  temp &= ~VC_UART_CTRL2_MSB_Msk;
  temp |= (0UL << VC_UART_CTRL2_MSB_Pos); /* LSB transmit first */
  VC_UART(uart_id)->CTRL2 = temp;

  vcuart_set_baudrate(uart_id, baudrate);

  vcuart_set_mode(uart_id, parity, databits, stopbits);

  /* Config UARTFIFO */
  temp = VC_UART(uart_id)->FIFOCTRL;
  temp &= ~VC_UART_FIFOCTRL_SFTRST_Msk;
  temp &= ~VC_UART_FIFOCTRL_OVMODE_Msk;
  temp &= ~VC_UART_FIFOCTRL_TXFIFOLVL_Msk;
  temp &= ~VC_UART_FIFOCTRL_RXFIFOLVL_Msk;
  temp |= (0UL << VC_UART_FIFOCTRL_SFTRST_Pos);     /* SFTRST disable */
  temp |= (0UL << VC_UART_FIFOCTRL_OVMODE_Pos);     /* OVMODE discard */
  temp |= (7UL << VC_UART_FIFOCTRL_TXFIFOLVL_Pos);  /* TXFIFOLVL: 7 */
  temp |= (0UL << VC_UART_FIFOCTRL_RXFIFOLVL_Pos);  /* RXFIFOLVL: 0 */
  VC_UART(uart_id)->FIFOCTRL = temp;

  _uart_sfio_enable(uart_id);

  return uart_id;
}

void vcuart_set_mode(int uart_id, uint8_t parity, uint8_t databits, uint8_t stopbits)
{
  uint32_t temp = 0;

  temp = VC_UART(uart_id)->CTRL2;
  temp &= ~VC_UART_CTRL2_LENGTH_Msk;
  temp &= ~VC_UART_CTRL2_STOPLEN_Msk;
  temp &= ~VC_UART_CTRL2_PEN_Msk;
  temp &= ~VC_UART_CTRL2_PMODE_Msk;

  temp |= (databits == 7U) ? (1UL << VC_UART_CTRL2_LENGTH_Pos) : (0UL << VC_UART_CTRL2_LENGTH_Pos);
  temp |= (stopbits == 1U) ? (0UL << VC_UART_CTRL2_STOPLEN_Pos) : (1UL << VC_UART_CTRL2_STOPLEN_Pos);

  switch (parity) {
    case VCUART_PARITY_NONE:
      temp |= (0UL << VC_UART_CTRL2_PEN_Pos);
      break;

    case VCUART_PARITY_ODD:
      temp |= (1UL << VC_UART_CTRL2_PEN_Pos);
      temp |= (1UL << VC_UART_CTRL2_PMODE_Pos);
      break;

    case VCUART_PARITY_EVEN:
      temp |= (1UL << VC_UART_CTRL2_PEN_Pos);
      temp |= (0UL << VC_UART_CTRL2_PMODE_Pos);
      break;

    case VCUART_PARITY_FORCED1:
      temp |= (1UL << VC_UART_CTRL2_PEN_Pos);
      temp |= (3UL << VC_UART_CTRL2_PMODE_Pos);
      break;

    case VCUART_PARITY_FORCED0:
      temp |= (1UL << VC_UART_CTRL2_PEN_Pos);
      temp |= (2UL << VC_UART_CTRL2_PMODE_Pos);
      break;

    default:
      break;
  }

  VC_UART(uart_id)->CTRL2 = temp;
}

void vcuart_power_on(int uart_id)
{
  uint32_t temp = VC_MISC2->PCLKEN;
  temp |= (1UL << VC_MISC2_PCLKEN_UART_Pos(uart_id));
  VC_MISC2->CLKEN_UNLOCK = (0x55AAAA55 << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos);
  VC_MISC2->PCLKEN = temp;
}

void vcuart_power_off(int uart_id)
{
  uint32_t temp = VC_MISC2->PCLKEN;
  temp &= ~VC_MISC2_PCLKEN_UART_Msk(uart_id);
  VC_MISC2->CLKEN_UNLOCK = (0x55AAAA55 << VC_MISC2_CLKEN_UNLOCK_UNLOCK_Pos);
  VC_MISC2->PCLKEN = temp;
}

void vcuart_set_baudrate(int uart_id, int baudrate)
{
  uint32_t ahb_div  = ((VC_MISC2->CLKDIVH & VC_MISC2_CLKDIVH_CLKDIVH_Msk) >> VC_MISC2_CLKDIVH_CLKDIVH_Pos) + 1;

  uint32_t apb_div = 0;

#if defined(DEVICE_MCU_VC7351)
  apb_div  = ((VC_MISC2->CLKDIVP & VC_MISC2_CLKDIVP_CLKDIVP_Msk) >> VC_MISC2_CLKDIVP_CLKDIVP_Pos) + 1;
#endif

#if defined(DEVICE_MCU_VC6330) || defined(DEVICE_MCU_VC6320)
  apb_div = (((VC_MISC2->CLKDIVP & VC_MISC2_CLKDIVP_CLKDIVP_Msk) >> VC_MISC2_CLKDIVP_CLKDIVP_Pos) == 0) ? 2 : 4;
#endif

  uint32_t apb_clk  = (SystemCoreClock / ahb_div) / apb_div;
  uint32_t baud_div = apb_clk / baudrate;

  /* Round-up baud-div */
  if ((apb_clk & baudrate) > (baudrate / 2)) {
    baud_div++;
  }

  VC_UART(uart_id)->BAUDDIV = baud_div;
}

void vcuart_set_irq(int uart_id, uint32_t irqmask)
{
  if (irqmask & VCUART_RX_IRQ) {
    /* Set uart rx gpio input pullup */
    vcgpio_cfg_t uart_rx_cfg = {
        .used_as_gpio = false,
        .direction = PIN_INPUT,
        .pull = PullUp,
    };

    vcgpio_init(PinMap_UART[uart_id].rx, &uart_rx_cfg);

    /* Enable uart rx interrupt */
    uint32_t temp = VC_UART(uart_id)->CTRL;
    temp &= ~VC_UART_CTRL_RXIE_Msk;
    temp |= (1UL << VC_UART_CTRL_RXIE_Pos);
    VC_UART(uart_id)->CTRL = temp;
  } else if (irqmask & VCUART_TX_IRQ) {
    /* Enable uart tx interrupt */
    uint32_t temp = VC_UART(uart_id)->CTRL;
    temp &= ~VC_UART_CTRL_TXIE_Msk;
    temp |= (1UL << VC_UART_CTRL_TXIE_Pos);
    VC_UART(uart_id)->CTRL = temp;
  } else {
    return;
  }

  NVIC_EnableIRQ(PinMap_UART[uart_id].irqn);
}

void vcuart_putchar(int uart_id, char c)
{
  VC_UART(uart_id)->DATA = c;
  while ((VC_UART(uart_id)->STATE & VC_UART_STATE_TXDONE_Msk) == 0);
  uint32_t temp = VC_UART(uart_id)->STATE;
  temp |= (1UL << VC_UART_STATE_TXDONE_Pos);
  VC_UART(uart_id)->STATE = temp;
}

// Helper functions

static void _uart_sfio_enable(int uart_id)
{
  uint32_t temp = 0;

  switch (uart_id) {
    case 0:
      temp = VC_GPIOB->SEL0;
      temp &= ~VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(2);
      temp |= VC_GPIO_SEL0_IOB2_UART0_TX;
      VC_GPIOB->SEL0 = temp;
      temp = VC_GPIOA->SEL1;
      temp &= ~VC_GPIO_IOA_SEL1_IOAx_SEL_Msk(12);
      temp |= VC_GPIO_SEL1_IOA12_UART0_RX;
      VC_GPIOA->SEL1 = temp;
      break;

    case 1:
      temp = VC_GPIOB->SEL0;
      temp &= ~VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(3);
      temp |= VC_GPIO_SEL0_IOB3_UART1_TX;
      VC_GPIOB->SEL0 = temp;
      temp = VC_GPIOA->SEL1;
      temp &= ~VC_GPIO_IOA_SEL1_IOAx_SEL_Msk(13);
      temp |= VC_GPIO_SEL1_IOA13_UART1_RX;
      VC_GPIOA->SEL1 = temp;
      break;

    case 2:
      temp = VC_GPIOB->SEL0;
      temp &= ~VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(4);
      temp |= VC_GPIO_SEL0_IOB4_UART2_TX;
      VC_GPIOB->SEL0 = temp;
      temp = VC_GPIOA->SEL1;
      temp &= ~VC_GPIO_IOA_SEL1_IOAx_SEL_Msk(14);
      temp |= VC_GPIO_SEL1_IOA14_UART2_RX;
      VC_GPIOA->SEL1 = temp;
      break;

    case 3:
      temp = VC_GPIOB->SEL0;
      temp &= ~VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(5);
      temp |= VC_GPIO_SEL0_IOB5_UART3_TX;
      VC_GPIOB->SEL0 = temp;
      temp = VC_GPIOA->SEL1;
      temp &= ~VC_GPIO_IOA_SEL1_IOAx_SEL_Msk(15);
      temp |= VC_GPIO_SEL1_IOA15_UART3_RX;
      VC_GPIOA->SEL1 = temp;
      break;

    case 4:
      temp = VC_GPIOB->SEL0;
      temp &= ~VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(6);
      temp |= VC_GPIO_SEL0_IOB6_UART4_TX;
      VC_GPIOB->SEL0 = temp;
      temp = VC_GPIOB->SEL0;
      temp &= ~VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(0);
      temp |= VC_GPIO_SEL0_IOB0_UART4_RX;
      VC_GPIOB->SEL0 = temp;
      break;

    case 5:
      temp = VC_GPIOB->SEL0;
      temp &= ~VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(7);
      temp |= VC_GPIO_SEL0_IOB7_UART5_TX;
      VC_GPIOB->SEL0 = temp;
      temp = VC_GPIOB->SEL0;
      temp &= ~VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(1);
      temp |= VC_GPIO_SEL0_IOB1_UART5_RX;
      VC_GPIOB->SEL0 = temp;
      break;

    case 6:
      temp = VC_GPIOB->SEL1;
      temp &= ~VC_GPIO_IOB_SEL1_IOBx_SEL_Msk(8);
      temp |= VC_GPIO_SEL1_IOB8_UART6_TX;
      VC_GPIOB->SEL1 = temp;
      temp = VC_GPIOB->SEL1;
      temp &= ~VC_GPIO_IOB_SEL1_IOBx_SEL_Msk(15);
      temp |= VC_GPIO_SEL1_IOB15_UART6_RX;
      VC_GPIOB->SEL1 = temp;
      break;

    default:
      break;
  }
}
