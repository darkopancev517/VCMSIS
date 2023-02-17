#ifndef CLI_H_
#define CLI_H_

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  const char *name;
  void (*command_handler_func)(int argc, char *argv[]);
} cli_command_t;

void cli_uart_init();
void cli_uart_run();
void cli_set_user_commands(const cli_command_t *user_commands, uint8_t length);
void cli_output_bytes(const uint8_t *bytes, uint8_t length);
void cli_output_format(const char *fmt, ...);
void cli_output(const char *string, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* CLI_H_ */
