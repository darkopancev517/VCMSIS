#include "hal/gpio_api.h"
#include "hal/us_ticker_api.h"
#include "hal/serial_api.h"
#include "hal/rtc_api.h"
#include "hal/lp_ticker_api.h"

#include "vc_plc_phy.h"

#include <stdio.h>

extern int stdio_uart_inited;
extern serial_t stdio_uart;

static volatile uint32_t systick_counter = 0;
static volatile uint32_t second_counter = 0;

int main(void)
{
  SysTick_Config(SystemCoreClock / 1000); /* 1ms systick interrupt */
  us_ticker_init();

  if (!stdio_uart_inited) {
    serial_init(&stdio_uart, STDIO_UART_TX, STDIO_UART_RX);
  }

  printf("VC6300 PSO verification start\r\n");

  vc_plc_phy_init();

  printf("VC6300 PSO verification done\r\n");

  while (1) {
  }

  return 0;
}

void SysTick_Handler(void)
{
  systick_counter++;
}
