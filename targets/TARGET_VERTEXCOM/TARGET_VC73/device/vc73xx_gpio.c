#include "vc73xx_gpio.h"

void vcgpio_init(PinName pin)
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
    temp |= VC_GPIO_IOX_OEN_IOXOEN_Enabled(pinNum);
    gpio->OEN = temp;

    temp = gpio->IE;
    temp &= ~VC_GPIO_IOX_IE_IOXIE_Msk(pinNum);
    temp |= VC_GPIO_IOX_IE_IOXIE_Disabled(pinNum);
    gpio->IE = temp;

    temp = gpio->ATT;
    temp &= ~VC_GPIO_IOX_ATT_IOXATT_Msk(pinNum);
    temp |= VC_GPIO_IOX_ATT_IOXATT_CMOS(pinNum);
    gpio->ATT = temp;

    switch (portNum) {
        case PortA:
            if (pinNum < 8) {
                temp = VC_GPIOA->SEL0;
                temp &= ~VC_GPIO_IOA_SEL0_IOAx_SEL_Msk(pinNum);
                temp |= VC_GPIO_SEL0_IOAx_GPIO(pinNum);
                VC_GPIOA->SEL0 = temp;
            } else {
                temp = VC_GPIOA->SEL1;
                temp &= ~VC_GPIO_IOA_SEL1_IOAx_SEL_Msk(pinNum);
                temp |= VC_GPIO_SEL1_IOAx_GPIO(pinNum);
                VC_GPIOA->SEL1 = temp;
            }
            break;
        case PortB:
            if (pinNum < 8) {
                temp = VC_GPIOB->SEL0;
                temp &= ~VC_GPIO_IOB_SEL0_IOBx_SEL_Msk(pinNum);
                temp |= VC_GPIO_SEL0_IOBx_GPIO(pinNum);
                VC_GPIOB->SEL0 = temp;
            } else {
                temp = VC_GPIOB->SEL1;
                temp &= ~VC_GPIO_IOB_SEL1_IOBx_SEL_Msk(pinNum);
                temp |= VC_GPIO_SEL1_IOBx_GPIO(pinNum);
                VC_GPIOB->SEL1 = temp;
            }
            break;
        case PortC:
            if (pinNum < 8) {
                temp = VC_GPIOC->SEL0;
                temp &= ~VC_GPIO_IOC_SEL0_IOCx_SEL_Msk(pinNum);
                temp |= VC_GPIO_SEL0_IOCx_GPIO(pinNum);
                VC_GPIOC->SEL0 = temp;
            } else {
                temp = VC_GPIOC->SEL1;
                temp &= ~VC_GPIO_IOC_SEL1_IOCx_SEL_Msk(pinNum);
                temp |= VC_GPIO_SEL1_IOCx_GPIO(pinNum);
                VC_GPIOC->SEL1 = temp;
            }
            break;
        case PortD:
            temp = VC_GPIOD->SEL;
            temp &= ~VC_GPIO_IOD_SEL_IODx_SEL_Msk(pinNum);
            temp |= VC_GPIO_SEL_IODx_GPIO(pinNum);
            VC_GPIOD->SEL = temp;
            break;
        default:
            return;
    }
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
