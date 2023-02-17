#include "hal/gpio_api.h"
#include "hal/us_ticker_api.h"
#include "hal/serial_api.h"
#include "hal/rtc_api.h"
#include "hal/lp_ticker_api.h"

#include "cli.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

extern volatile uint32_t systick_counter;
static volatile uint32_t second_counter = 0;

void cmd_timer(int argc, char **argv);

static void run_timer_test(void)
{
  uint8_t test_count = 10;

  while (test_count != 0)
  {
    if ((systick_counter % 1000) == 0) {
      printf("systick counter: %lu\r\n", second_counter++);
      const ticker_data_t *us_ticker = get_us_ticker_data();
      printf("usticker read: %lu\r\n", us_ticker->interface->read());
      test_count--;
    }
  }
}

static void cmd_timer_usage(void)
{
  cli_output_format("Available timer command:\r\n");
  cli_output_format("  timer test\r\n");
}

void cmd_timer(int argc, char **argv)
{
  if (argc == 0)
  {
    cmd_timer_usage();
    return;
  }

   if (strcmp(argv[0], "test") == 0)
  {
    run_timer_test();
  }
  else if (strcmp(argv[0], "help") == 0)
  {
    cmd_timer_usage();
  }
  else
  {
    cli_output_format("Unknown command: timer %s\r\n", argv[0]);
  }
}
