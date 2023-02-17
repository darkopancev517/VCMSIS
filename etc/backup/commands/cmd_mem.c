#include "hal/gpio_api.h"
#include "hal/us_ticker_api.h"
#include "hal/serial_api.h"
#include "hal/rtc_api.h"
#include "hal/lp_ticker_api.h"

#include "cli.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void cmd_mem(int argc, char **argv);

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

void cmd_mem(int argc, char **argv)
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
