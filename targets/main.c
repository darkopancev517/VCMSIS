#include "hal/gpio_api.h"
#include "hal/us_ticker_api.h"
#include "hal/serial_api.h"
#include "hal/log.h"
#include "hal/rtc_api.h"
#include "hal/lp_ticker_api.h"

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

  hal_log("Hello World\r\n");

  while (1) {
    if ((systick_counter % 1000) == 0) {
      hal_log("systick counter: %lu\r\n", second_counter++);
      const ticker_data_t *us_ticker = get_us_ticker_data();
      hal_log("usticker read: %lu\r\n", us_ticker->interface->read());
    }
  }

  return 0;
}

void SysTick_Handler(void)
{
  systick_counter++;
}
