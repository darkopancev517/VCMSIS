#include "hal/gpio_api.h"
#include "hal/us_ticker_api.h"
#include "hal/serial_api.h"
#include "hal/rtc_api.h"
#include "hal/lp_ticker_api.h"
#include "cli.h"

#include "vc_plc_phy.h"

static volatile uint32_t systick_counter = 0;

int main(void)
{
  SysTick_Config(SystemCoreClock / 1000); /* 1ms systick interrupt */
  us_ticker_init();
  cli_uart_init();

  vc_plc_phy_init();

  cli_uart_run();

  return 0;
}

void SysTick_Handler(void)
{
  systick_counter++;
}
