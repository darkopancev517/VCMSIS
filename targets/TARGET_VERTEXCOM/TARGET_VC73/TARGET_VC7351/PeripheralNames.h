#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    UART_0 = (int)VC_UART0_BASE,
    UART_1 = (int)VC_UART1_BASE,
    UART_2 = (int)VC_UART2_BASE,
    UART_3 = (int)VC_UART3_BASE
} UARTName;

#define DEVICE_SPI_COUNT 2
typedef enum {
    SPI_1 = (int)VC_SPI1_BASE,
    SPI_2 = (int)VC_SPI2_BASE
} SPIName;

#ifdef __cplusplus
}
#endif

#endif /* MBED_PERIPHERALNAMES_H */
