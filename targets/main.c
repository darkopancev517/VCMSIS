#include "hal/gpio_api.h"
#include "hal/us_ticker_api.h"
#include "hal/serial_api.h"
#include "hal/rtc_api.h"
#include "hal/lp_ticker_api.h"

#include "cli.h"
#include "vc_plc_phy.h"

#include <stdint.h>
#include <stdlib.h>

static volatile uint32_t systick_counter = 0;
static volatile uint32_t second_counter = 0;

static void cmd_test(int argc, char **argv);
static void cmd_mem(int argc, char **argv);

const cli_command_t user_command_list[] = {
  { "test", cmd_test },
  { "mem", cmd_mem },
};

int main(void)
{
  SysTick_Config(SystemCoreClock / 1000); /* 1ms systick interrupt */
  us_ticker_init();

  cli_uart_init();
  cli_set_user_commands(user_command_list, 2);

  cli_uart_run();

  return 0;
}

void SysTick_Handler(void)
{
  systick_counter++;
}

static void run_phy_test(void)
{
  vc_plc_phy_init();
}

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

static void cmd_test_usage(void)
{
  cli_output_format("Available test command:\r\n");
  cli_output_format("  test phy\r\n");
  cli_output_format("  test timer\r\n");
}

static void cmd_test(int argc, char **argv)
{
  if (argc == 0)
  {
    cmd_test_usage();
    return;
  }

  if (strcmp(argv[0], "phy") == 0)
  {
    run_phy_test();
  }
  else if (strcmp(argv[0], "timer") == 0)
  {
    run_timer_test();
  }
  else
  {
    cli_output_format("Unknown command: test %s\r\n", argv[0]);
  }
}

static void mem_dump_word(const void *address, uint32_t size)
{
  volatile uint32_t *addr = (volatile uint32_t *)address;
  uint32_t value = 0;

  for (int i = 0 ; i < size ; i++)
  {
    value = *(volatile uint32_t *)(addr + i);

    if((i % 4) == 0)
    {
      printf("%08lx : %08lx", (uint32_t)(addr + i), value);
    }
    else if((i % 4) == 1)
    {
      printf(" %08lx", value);
    }
    else if((i % 4) == 2)
    {
      printf(" - %08lx", value);
    }
    else
    {
      printf(" %08lx\r\n", value);
    }
  }

  if (size %4 != 0)
  {
    printf("\r\n");
  }
}

static void cmd_mem_usage(void)
{
  cli_output_format("Usage: mem [addr]\r\n");
  cli_output_format("       mem [addr] [value]\r\n");
  cli_output_format("       mem dump [addr] [size: in word]\r\n");
}

static void cmd_mem(int argc, char **argv)
{
  uint32_t val, valr, size;
  volatile uint32_t *addr;

  if (argc < 1 || argc > 3)
  {
    cmd_mem_usage();
    return;
  }

  if (strcmp(argv[0], "dump") == 0)
  {
    if (argc != 3)
    {
      cmd_mem_usage();
      return;
    }

    addr = (volatile uint32_t *)strtoul(argv[1], NULL, 16);
    size = strtoul(argv[2], NULL, 16);
    mem_dump_word((void *)addr, size);
    return;
  }

  addr = (volatile uint32_t *)strtoul(argv[0], NULL, 16);

  if (argc == 1)
  {
    val = *(volatile uint32_t *)addr;
    printf("read mem  %08lx  : %08lx\r\n", (uint32_t)addr, val);
  }
  else
  {
    val = strtoul(argv[1], NULL, 16);
    *(volatile uint32_t *)addr = val;
    printf("write mem %08lx <= %08lx\r\n", (uint32_t)addr, val);
    valr = *(volatile uint32_t *)addr;
    printf("read back %08lx  : %08lx\r\n", (uint32_t)addr, valr);
  }
}
