#include "cli.h"
#include "hal/serial_api.h"

extern int stdio_uart_inited;
extern serial_t stdio_uart;

#define CLI_MAX_ARGS 32

#define CLI_UART_RX_BUFFER_SIZE 128
#define CLI_UART_TX_BUFFER_SIZE 128
#define CLI_UART_MAX_LINE_LENGTH 128

static const cli_command_t *user_commands = NULL;
static uint8_t user_commands_length = 0;

static char uart_rx_buffer[CLI_UART_RX_BUFFER_SIZE];
static uint16_t uart_rx_length = 0;

static char uart_tx_buffer[CLI_UART_TX_BUFFER_SIZE];
static uint16_t uart_tx_head = 0;
static uint16_t uart_tx_length = 0;
static uint16_t uart_send_length = 0;

static const char command_prompt[] = {'>', ' '};
static const char erase_string[] = {'\b', ' ', '\b'};
static const char newline[] = {'\r', '\n'};

static void output_bytes(const uint8_t *bytes, uint8_t length) ;
//static int parse_long(char *string, long *result);
//static int parse_unsigned_long(char *string, unsigned long *result);
static void process_line(char *buf, uint16_t length);
static void set_user_commands(const cli_command_t *commands, uint8_t length);

static void uart_receive_task(const uint8_t *buf, uint16_t buf_length);
static int uart_process_command();
static int uart_output(const char *buf, uint16_t buf_length);
static int uart_output_format(const char *fmt, ...);
static void uart_send();

void cli_uart_init()
{
  if (!stdio_uart_inited) {
    serial_init(&stdio_uart, STDIO_UART_TX, STDIO_UART_RX);
  }
  serial_irq_set(&stdio_uart, RxIrq, 1);
}

void cli_uart_run()
{
  uart_output(command_prompt, sizeof(command_prompt));

  char c;

  while (1)
  {
    c = (char)serial_getc(&stdio_uart);
    uart_receive_task((const uint8_t *)&c, 1);
  }

  /* should not reach here */

  return;
}

void cli_set_user_commands(const cli_command_t *user_commands, uint8_t length)
{
  set_user_commands(user_commands, length);
}

void cli_output_bytes(const uint8_t *bytes, uint8_t length)
{
  output_bytes(bytes, length);
}

void cli_output_format(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  uart_output_format(fmt, ap);
  va_end(ap);
}

void cli_output(const char *string, uint16_t length)
{
  uart_output(string, length);
}

// PRIVATE ---------------------------------------------------------------------------------

static void output_bytes(const uint8_t *bytes, uint8_t length)
{
  for (int i = 0; i < length; i++)
  {
    uart_output_format("%02x", bytes[i]);
  }
}

// static int parse_long(char *string, long *result)
// {
//   char *endptr;
//   *result = strtol(string, &endptr, 0);
//   return (*endptr == '\0') ? 1 : 0;
// }

// static int parse_unsigned_long(char *string, unsigned long *result)
// {
//   char *endptr;
//   *result = strtoul(string, &endptr, 0);
//   return (*endptr == '\0') ? 1 : 0;
// }

static void process_line(char *buf, uint16_t length)
{
  char *argv[CLI_MAX_ARGS];
  char *cmd;
  uint8_t argc = 0, i = 0;

  if (buf == NULL)
  {
    return;
  }

  for (; *buf == ' '; buf++, length--);

  for (cmd = buf + 1; (cmd < buf + length) && (cmd != NULL); ++cmd)
  {
    if (argc > CLI_MAX_ARGS)
    {
      return;
    }

    if (*cmd == ' ' || *cmd == '\r' || *cmd == '\n')
    {
      *cmd = '\0';
    }

    if (*(cmd - 1) == '\0' && *cmd != ' ')
    {
      argv[argc++] = cmd;
    }
  }

  cmd = buf;

  if (user_commands == NULL || user_commands_length == 0)
  {
    return;
  }

  for (i = 0; i < user_commands_length; i++)
  {
    if (strcmp(cmd, user_commands[i].name) == 0)
    {
      user_commands[i].command_handler_func(argc, argv);
      break;
    }
  }

  if (strcmp(cmd, "help") == 0)
  {
    for (i = 0; i < user_commands_length; i++)
    {
      uart_output_format("%s\r\n", user_commands[i].name);
    }

    i = 0;
  }

  if (i == user_commands_length)
  {
    uart_output_format("Unknown command: %s\r\n", cmd);
  }
  else
  {
    uart_output_format("Done\r\n");
  }
}

static void set_user_commands(const cli_command_t *commands, uint8_t length)
{
  user_commands = commands;
  user_commands_length = length;
}

static void uart_receive_task(const uint8_t *buf, uint16_t buf_length)
{
  const uint8_t *end;

  end = buf + buf_length;

  for (; buf < end; buf++)
  {
    switch (*buf)
    {
      case '\r':
      case '\n':
        uart_output(newline, sizeof(newline));

        if (uart_rx_length > 0)
        {
            uart_rx_buffer[uart_rx_length] = '\0';
            uart_process_command();
        }

        uart_output(command_prompt, sizeof(command_prompt));
        break;

      case '\b':
      case 127:
        if (uart_rx_length > 0)
        {
          uart_output(erase_string, sizeof(erase_string));
          uart_rx_buffer[--uart_rx_length] = '\0';
        }
        break;

      default:
        if (uart_rx_length < CLI_UART_RX_BUFFER_SIZE)
        {
          uart_output((const char *)buf, 1);
          uart_rx_buffer[uart_rx_length++] = *buf;
        }
        break;
    }
  }
}

static int uart_process_command()
{
  if (uart_rx_buffer[uart_rx_length - 1] == '\n')
  {
    uart_rx_buffer[--uart_rx_length] = '\0';
  }

  if (uart_rx_buffer[uart_rx_length - 1] == '\r')
  {
    uart_rx_buffer[--uart_rx_length] = '\0';
  }

  process_line(uart_rx_buffer, uart_rx_length);

  uart_rx_length = 0;

  return 0;
}

static int uart_output(const char *buf, uint16_t buf_length)
{
  uint16_t remaining = CLI_UART_TX_BUFFER_SIZE - uart_tx_length;
  uint16_t tail;

  if (buf_length > remaining)
  {
    buf_length = remaining;
  }

  for (int i = 0; i < buf_length; i++)
  {
    tail = (uart_tx_head + uart_tx_length) % CLI_UART_TX_BUFFER_SIZE;
    uart_tx_buffer[tail] = *buf++;
    uart_tx_length++;
  }

  uart_send();

  return buf_length;
}

static int uart_output_format(const char *fmt, ...)
{
  char buf[CLI_UART_MAX_LINE_LENGTH];

  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);

  return uart_output(buf, (uint16_t)strlen(buf));
}

static void uart_send()
{
  while (uart_tx_length > 0)
  {
    if (uart_tx_length > CLI_UART_TX_BUFFER_SIZE - uart_tx_head)
    {
      uart_send_length = CLI_UART_TX_BUFFER_SIZE - uart_tx_head;
    }
    else
    {
      uart_send_length = uart_tx_length;
    }

    if (uart_send_length > 0)
    {
      for (uint16_t i = 0; i < uart_send_length; i++)
      {
        serial_putc(&stdio_uart, uart_tx_buffer[uart_tx_head + i]);
        fflush(stdout);
      }
    }

    uart_tx_head = (uart_tx_head + uart_send_length) % CLI_UART_TX_BUFFER_SIZE;
    uart_tx_length -= uart_send_length;
    uart_send_length = 0;
  }
}
