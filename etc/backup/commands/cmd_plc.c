#include "hal/gpio_api.h"
#include "hal/us_ticker_api.h"
#include "hal/serial_api.h"
#include "hal/rtc_api.h"
#include "hal/lp_ticker_api.h"

#include "cli.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef DEVICE_MCU_VC6330
void cmd_plc(int argc, char **argv);

extern void vcplc_init(void);
extern uint8_t vc_phy_check_idle(void);

static void cmd_plc_usage(void)
{
  cli_output_format("Available plc command:\r\n");
  cli_output_format("  plc init : to initialize plc\r\n");
  cli_output_format("  plc idle : to see whether plc is idle or not\r\n");
}

void cmd_plc(int argc, char **argv)
{
  if (argc == 0)
  {
    cmd_plc_usage();
    return;
  }

  if (strcmp(argv[0], "init") == 0)
  {
    vcplc_init();
  }
  else if (strcmp(argv[0], "idle") == 0)
  {
    if (vc_phy_check_idle() == 1)
    {
      cli_output_format("true\r\n");
    }
    else
    {
      cli_output_format("false\r\n");
    }
  }
  else if (strcmp(argv[0], "help") == 0)
  {
    cmd_plc_usage();
  }
  else
  {
    cli_output_format("Unknown command: plc %s\r\n", argv[0]);
  }
}
#endif // #ifdef DEVICE_MCU_VC6330
