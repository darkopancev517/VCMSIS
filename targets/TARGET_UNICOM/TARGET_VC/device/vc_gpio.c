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

#include "vc_gpio.h"

static void _gpio_select_sf(uint8_t portNum, uint8_t pinNum, uint8_t funcid);
static void _gpio_select_exti_sf(uint8_t portNum, uint8_t pinNum, vcgpio_cfg_t *cfg);

void vcgpio_init(PinName pin, vcgpio_cfg_t *cfg)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);
  uint32_t temp = 0;

  VC_GPIO_TypeDef *gpio = NULL;

  if (portNum == PortA) {
    gpio = (VC_GPIO_TypeDef *)VC_GPIOA;
  } else {
    gpio = (VC_GPIO_TypeDef *)VC_GPIO(portNum);
  }

  if (cfg->direction == PIN_OUTPUT) {
    /* OUTPUT */
    temp = gpio->OEN;
    temp &= ~VC_GPIO_IOX_OEN_IOXOEN_Msk(pinNum);
    temp |= VC_GPIO_IOX_OEN_IOXOEN_Enabled(pinNum);
    gpio->OEN = temp;

    temp = gpio->IE;
    temp &= ~VC_GPIO_IOX_IE_IOXIE_Msk(pinNum);
    temp |= VC_GPIO_IOX_IE_IOXIE_Disabled(pinNum);
    gpio->IE = temp;

    temp = gpio->ATT;
    temp &= ~VC_GPIO_IOX_ATT_IOXATT_Msk(pinNum);
    temp |= VC_GPIO_IOX_ATT_IOXATT_OPEN_DRAIN(pinNum);
    gpio->ATT = temp;
  } else {
    /* INPUT */
    temp = gpio->OEN;
    temp &= ~VC_GPIO_IOX_OEN_IOXOEN_Msk(pinNum);
    temp |= VC_GPIO_IOX_OEN_IOXOEN_Disabled(pinNum);
    gpio->OEN = temp;

    temp = gpio->IE;
    temp &= ~VC_GPIO_IOX_IE_IOXIE_Msk(pinNum);
    temp |= VC_GPIO_IOX_IE_IOXIE_Enabled(pinNum);
    gpio->IE = temp;

    temp = gpio->ATT;
    temp &= ~VC_GPIO_IOX_ATT_IOXATT_Msk(pinNum);
    temp |= VC_GPIO_IOX_ATT_IOXATT_OPEN_DRAIN(pinNum);
    gpio->ATT = temp;
  }

  switch (cfg->pull) {
    case PullUp:
      temp = gpio->DAT;
      temp &= ~VC_GPIO_IOX_DAT_IOXDAT_Msk(pinNum);
      temp |= VC_GPIO_IOX_DAT_IOXDAT_Enabled(pinNum);
      gpio->DAT = temp;
      break;

    case PullDown:
      temp = gpio->DAT;
      temp &= ~VC_GPIO_IOX_DAT_IOXDAT_Msk(pinNum);
      temp |= VC_GPIO_IOX_DAT_IOXDAT_Disabled(pinNum);
      gpio->DAT = temp;
      break;

    default:
      /* PullNone */
      temp = gpio->ATT;
      temp &= ~VC_GPIO_IOX_ATT_IOXATT_Msk(pinNum);
      temp |= VC_GPIO_IOX_ATT_IOXATT_CMOS(pinNum);
      gpio->ATT = temp;
      break;
  }

  if (cfg->used_as_gpio) {
    _gpio_select_sf(portNum, pinNum, 0);
  }

  if (cfg->used_as_irq) {
    _gpio_select_exti_sf(portNum, pinNum, cfg);
  }
}

void vcgpio_free(PinName pin)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);
  uint32_t temp = 0;

  VC_GPIO_TypeDef *gpio = NULL;

  if (portNum == PortA) {
    gpio = (VC_GPIO_TypeDef *)VC_GPIOA;
  } else {
    gpio = (VC_GPIO_TypeDef *)VC_GPIO(portNum);
  }

  temp = gpio->OEN;
  temp &= ~VC_GPIO_IOX_OEN_IOXOEN_Msk(pinNum);
  temp |= VC_GPIO_IOX_OEN_IOXOEN_Disabled(pinNum);
  gpio->OEN = temp;

  temp = gpio->IE;
  temp &= ~VC_GPIO_IOX_IE_IOXIE_Msk(pinNum);
  temp |= VC_GPIO_IOX_IE_IOXIE_Disabled(pinNum);
  gpio->IE = temp;

  temp = gpio->ATT;
  temp &= ~VC_GPIO_IOX_ATT_IOXATT_Msk(pinNum);
  gpio->ATT = temp;

  temp = gpio->DAT;
  temp &= ~VC_GPIO_IOX_DAT_IOXDAT_Msk(pinNum);
  gpio->DAT = temp;

  _gpio_select_sf(portNum, pinNum, 0);
}

int vcgpio_pin_out_read(PinName pin)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);

  VC_GPIO_TypeDef *gpio = NULL;

  if (portNum == PortA) {
    gpio = (VC_GPIO_TypeDef *)VC_GPIOA;
  } else {
    gpio = (VC_GPIO_TypeDef *)VC_GPIO(portNum);
  }

  return (gpio->DAT & VC_GPIO_IOX_DAT_IOXDAT_Msk(pinNum)) ? 1 : 0;
}

int vcgpio_pin_read(PinName pin)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);
  int res = 0;

  switch (portNum) {
    case PortA:
      res = (VC_GPIOA->STS & VC_GPIO_IOX_STS_IOXSTS_Msk(pinNum)) ? 1 : 0;
      break;
    case PortB:
      res = (VC_GPIOB->STS & VC_GPIO_IOX_STS_IOXSTS_Msk(pinNum)) ? 1 : 0;
      break;
    case PortC:
      res = (VC_GPIOC->STS & VC_GPIO_IOX_STS_IOXSTS_Msk(pinNum)) ? 1 : 0;
      break;
    case PortD:
      res = (VC_GPIOD->STS & VC_GPIO_IOX_STS_IOXSTS_Msk(pinNum)) ? 1 : 0;
      break;
    default:
      res = -1;
      break;
  }

  return res;
}

void vcgpio_pin_set(PinName pin)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);

  VC_GPIO_TypeDef *gpio = NULL;

  if (portNum == PortA) {
    gpio = (VC_GPIO_TypeDef *)VC_GPIOA;
  } else {
    gpio = (VC_GPIO_TypeDef *)VC_GPIO(portNum);
  }

  uint32_t temp = gpio->DAT;
  temp &= ~VC_GPIO_IOX_DAT_IOXDAT_Msk(pinNum);
  temp |= VC_GPIO_IOX_DAT_IOXDAT_Enabled(pinNum);
  gpio->DAT = temp;
}

void vcgpio_pin_clear(PinName pin)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);

  VC_GPIO_TypeDef *gpio = NULL;

  if (portNum == PortA) {
    gpio = (VC_GPIO_TypeDef *)VC_GPIOA;
  } else {
    gpio = (VC_GPIO_TypeDef *)VC_GPIO(portNum);
  }

  uint32_t temp = gpio->DAT;
  temp &= ~VC_GPIO_IOX_DAT_IOXDAT_Msk(pinNum);
  temp |= VC_GPIO_IOX_DAT_IOXDAT_Disabled(pinNum);
  gpio->DAT = temp;
}

void vcgpio_out_uninit(PinName pin)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);
  uint32_t temp = 0;

  VC_GPIO_TypeDef *gpio = NULL;

  if (portNum == PortA) {
    gpio = (VC_GPIO_TypeDef *)VC_GPIOA;
  } else {
    gpio = (VC_GPIO_TypeDef *)VC_GPIO(portNum);
  }

  temp = gpio->OEN;
  temp &= ~VC_GPIO_IOX_OEN_IOXOEN_Msk(pinNum);
  temp |= VC_GPIO_IOX_OEN_IOXOEN_Disabled(pinNum);
  gpio->OEN = temp;

  temp = gpio->ATT;
  temp &= ~VC_GPIO_IOX_ATT_IOXATT_Msk(pinNum);
  gpio->ATT = temp;

  temp = gpio->DAT;
  temp &= ~VC_GPIO_IOX_DAT_IOXDAT_Msk(pinNum);
  gpio->DAT = temp;

  _gpio_select_sf(portNum, pinNum, 0);
}

void vcgpio_in_uninit(PinName pin)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);
  uint32_t temp = 0;

  VC_GPIO_TypeDef *gpio = NULL;

  if (portNum == PortA) {
    gpio = (VC_GPIO_TypeDef *)VC_GPIOA;
  } else {
    gpio = (VC_GPIO_TypeDef *)VC_GPIO(portNum);
  }

  temp = gpio->IE;
  temp &= ~VC_GPIO_IOX_IE_IOXIE_Msk(pinNum);
  temp |= VC_GPIO_IOX_IE_IOXIE_Disabled(pinNum);
  gpio->IE = temp;

  temp = gpio->ATT;
  temp &= ~VC_GPIO_IOX_ATT_IOXATT_Msk(pinNum);
  gpio->ATT = temp;

  temp = gpio->DAT;
  temp &= ~VC_GPIO_IOX_DAT_IOXDAT_Msk(pinNum);
  gpio->DAT = temp;

  _gpio_select_sf(portNum, pinNum, 0);
}

void vcgpio_irq_enable(PinName pin)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);
  uint32_t temp = 0;
  if (portNum == PortA) {
    temp = VC_GPIOA->WKUEN;
    temp |= (1UL << VC_GPIO_IOx_WKUEN_Pos(pinNum));
    VC_GPIOA->WKUEN = temp;
    NVIC_EnableIRQ(PMU_IRQn);
  }
  else if (portNum == PortC) {
    temp = VC_GPIOC->WKUEN;
    temp |= (1UL << VC_GPIO_IOx_WKUEN_Pos(pinNum));
    VC_GPIOC->WKUEN = temp;
    NVIC_EnableIRQ(GPIO_IRQn);
  }
}

void vcgpio_irq_disable(PinName pin)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);
  uint32_t temp = 0;
  if (portNum == PortA) {
    temp = VC_GPIOA->WKUEN;
    temp &= ~(1UL << VC_GPIO_IOx_WKUEN_Pos(pinNum));
    VC_GPIOA->WKUEN = temp;
  } else if (portNum == PortC) {
    temp = VC_GPIOC->WKUEN;
    temp &= ~(1UL << VC_GPIO_IOx_WKUEN_Pos(pinNum));
    VC_GPIOC->WKUEN = temp;
  }
}

void vcgpio_select_function(PinName pin, uint8_t funcid)
{
  uint8_t portNum = VC_PORT(pin);
  uint8_t pinNum = VC_PIN(pin);
  _gpio_select_sf(portNum, pinNum, funcid);
}

// Helper functions

static void _gpio_select_sf(uint8_t portNum, uint8_t pinNum, uint8_t funcid)
{
  uint32_t temp = 0;

  switch (portNum) {
    case PortA:
      if (pinNum < 8) {
          temp = VC_GPIOA->SEL0;
          temp &= ~VC_GPIO_IOA_SEL0_IOAx_SEL_Msk(pinNum);
          temp |= funcid << VC_GPIO_IOA_SEL0_IOAx_SEL_Pos(pinNum);
          VC_GPIOA->SEL0 = temp;
      } else {
          temp = VC_GPIOA->SEL1;
          temp &= ~VC_GPIO_IOA_SEL1_IOAx_SEL_Msk(pinNum);
          temp |= funcid << VC_GPIO_IOA_SEL1_IOAx_SEL_Pos(pinNum);
          VC_GPIOA->SEL1 = temp;
      }
      break;

    case PortB:
      if (pinNum < 8) {
          temp = VC_GPIOB->SEL0;
          temp &= ~VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(pinNum);
          temp |= funcid << VC_GPIO_IOB_SEL0_IOBx_SEL_Pos(pinNum);
          VC_GPIOB->SEL0 = temp;
      } else {
          temp = VC_GPIOB->SEL1;
          temp &= ~VC_GPIO_IOB_SEL1_IOBx_SEL_Msk(pinNum);
          temp |= funcid << VC_GPIO_IOB_SEL1_IOBx_SEL_Pos(pinNum);
          VC_GPIOB->SEL1 = temp;
      }
      break;

    case PortC:
    {
#if defined(DEVICE_MCU_VC7351)
      if (pinNum < 8) {
          temp = VC_GPIOC->SEL0;
          temp &= ~VC_GPIO_IOC_SEL0_IOCx_SEL_Msk(pinNum);
          temp |= funcid << VC_GPIO_IOC_SEL0_IOCx_SEL_Pos(pinNum);
          VC_GPIOC->SEL0 = temp;
      } else {
          temp = VC_GPIOC->SEL1;
          temp &= ~VC_GPIO_IOC_SEL1_IOCx_SEL_Msk(pinNum);
          temp |= funcid << VC_GPIO_IOC_SEL1_IOCx_SEL_Pos(pinNum);
          VC_GPIOC->SEL1 = temp;
      }
#endif
#if defined(DEVICE_MCU_VC6330) || defined(DEVICE_MCU_VC6320)
      temp = VC_GPIOC->SEL;
      temp &= ~VC_GPIO_IOC_SEL_IOCx_SEL_Msk(pinNum);
      temp |= funcid << VC_GPIO_IOC_SEL_IOCx_SEL_Pos(pinNum);
      VC_GPIOC->SEL = temp;
#endif
        break;
      }

    case PortD:
      temp = VC_GPIOD->SEL;
      temp &= ~VC_GPIO_IOD_SEL_IODx_SEL_Msk(pinNum);
      temp |= funcid << VC_GPIO_IOD_SEL_IODx_SEL_Pos(pinNum);
      VC_GPIOD->SEL = temp;
      break;

    default:
      return;
  }
}

static void _gpio_select_exti_sf(uint8_t portNum, uint8_t pinNum, vcgpio_cfg_t *cfg)
{
  uint32_t temp = 0;
  uint32_t temp1 = 0;

  switch (portNum) {
    case PortA:
    {
      temp = VC_PMU->IOANODEG;
      temp |= (1 << pinNum);
      VC_PMU->IOANODEG = temp;

      temp = VC_PMU->CTRL;
      temp &= ~VC_PMU_CTRL_INTEN_Msk;
      temp |= (1UL << VC_PMU_CTRL_INTEN_Pos);
      VC_PMU->CTRL = temp;

      temp  = VC_GPIOA->WKUEN;
      temp1 = VC_GPIOA->DAT;

      temp  &= ~VC_GPIO_IOx_WKUEN_Msk(pinNum);
      temp1 &= ~VC_GPIO_IOX_DAT_IOXDAT_Msk(pinNum);

      if (cfg->irq_fall) {
        temp  |= (1UL << VC_GPIO_IOx_WKUEN_Pos(pinNum));
        temp1 |= (1UL << pinNum);
      }

      if (cfg->irq_rise) {
        temp |= (1UL << VC_GPIO_IOx_WKUEN_Pos(pinNum));
      }

      if (cfg->irq_both) {
        temp |= (3UL << VC_GPIO_IOx_WKUEN_Pos(pinNum));
      }

      VC_GPIOA->WKUEN = temp;
      VC_GPIOA->DAT = temp1;

      if (pinNum < 8) {
        temp = VC_GPIOA->SEL0;
        temp &= ~VC_GPIO_IOA_SEL0_IOAx_SEL_Msk(pinNum);
        temp |= VC_GPIO_SEL0_IOAx_EINTx(pinNum);
        VC_GPIOA->SEL0 = temp;
      } else {
        temp = VC_GPIOA->SEL1;
        temp &= ~VC_GPIO_IOA_SEL1_IOAx_SEL_Msk(pinNum);
        temp |= VC_GPIO_SEL1_IOAx_EINTx(pinNum);
        VC_GPIOA->SEL1 = temp;
      }
      break;
    }

    case PortC:
    {
      temp  = VC_GPIOC->WKUEN;
      temp1 = VC_GPIOC->DAT;

      temp  &= ~VC_GPIO_IOx_WKUEN_Msk(pinNum);
      temp1 &= ~VC_GPIO_IOX_DAT_IOXDAT_Msk(pinNum);

      if (cfg->irq_fall) {
        temp  |= (1UL << VC_GPIO_IOx_WKUEN_Pos(pinNum));
        temp1 |= (1UL << pinNum);
      }

      if (cfg->irq_rise) {
        temp |= (1UL << VC_GPIO_IOx_WKUEN_Pos(pinNum));
      }

      if (cfg->irq_both) {
        temp |= (3UL << VC_GPIO_IOx_WKUEN_Pos(pinNum));
      }

      VC_GPIOC->WKUEN = temp;
      VC_GPIOC->DAT = temp1;

#if defined(DEVICE_MCU_VC7351)
      if (pinNum < 8) {
        temp = VC_GPIOC->SEL0;
        temp &= ~VC_GPIO_IOC_SEL0_IOCx_SEL_Msk(pinNum);
        temp |= VC_GPIO_SEL0_IOCx_EINTx(pinNum);
        VC_GPIOC->SEL0 = temp;
      } else {
        temp = VC_GPIOC->SEL1;
        temp &= ~VC_GPIO_IOC_SEL1_IOCx_SEL_Msk(pinNum);
        temp |= VC_GPIO_SEL1_IOCx_EINTx(pinNum);
        VC_GPIOC->SEL1 = temp;
      }
#endif
#if defined(DEVICE_MCU_VC6330) || defined(DEVICE_MCU_VC6320)
      // TODO: find VC_GPIOC_SEL_IOCx_ENITx(pinNum) ?
#endif
      break;
    }

    default:
      return;
  }
}
