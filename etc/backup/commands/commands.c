#include "hal/gpio_api.h"
#include "hal/us_ticker_api.h"
#include "hal/serial_api.h"
#include "hal/rtc_api.h"
#include "hal/lp_ticker_api.h"

#ifndef DEVICE_ATCMD
#include "cli.h"
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

extern void cmd_mem(int argc, char **argv);
extern void cmd_timer(int argc, char **argv);
#ifdef DEVICE_MCU_VC6330
extern void cmd_plc(int argc, char **argv);
extern void cmd_crypto(int argc, char **argv);
#endif
#ifdef DEVICE_MCU_VC7351
extern void cmd_rf(int argc, char **argv);
#endif

#ifndef DEVICE_ATCMD
const cli_command_t user_command_list[] = {
  { "mem", cmd_mem },
  { "timer", cmd_timer },
#ifdef DEVICE_MCU_VC6330
  { "plc", cmd_plc },
  { "crypto", cmd_crypto },
#endif
#ifdef DEVICE_MCU_VC7351
  { "rf", cmd_rf },
#endif
};

uint8_t user_command_length = sizeof(user_command_list) / sizeof(cli_command_t);
#endif
