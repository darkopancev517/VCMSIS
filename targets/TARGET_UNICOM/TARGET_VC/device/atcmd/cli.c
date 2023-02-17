#include "cli.h"
#include "hal/serial_api.h"

extern int stdio_uart_inited;
extern serial_t stdio_uart;

static uint8_t esc = 0;
static const cli_command_t *user_commands = NULL;
static uint8_t user_commands_length = 0;

static uint8_t cmd_history_store_index = 0;
static uint8_t cmd_history_cur_index = 0;
static char cmd_history[CLI_NUMOF_CMD_HISTORY][CLI_UART_RX_BUFFER_SIZE];
static char uart_rx_buffer[CLI_UART_RX_BUFFER_SIZE];
static uint16_t uart_rx_length = 0;

static char uart_tx_buffer[CLI_UART_TX_BUFFER_SIZE];
static uint16_t uart_tx_head = 0;
static uint16_t uart_tx_length = 0;
static uint16_t uart_send_length = 0;

static const char command_prompt[] = {'>', ' '};
static const char erase_string[] = {'\b', ' ', '\b'};
static const char newline[] = {'\r', '\n'};

static int process_line(char *inbuf, uint16_t length);
static void set_user_commands(const cli_command_t *commands, uint8_t length);
static void uart_receive_task(const uint8_t *buf, uint16_t buf_length);
static int uart_process_command();
static int uart_output(const char *buf, uint16_t buf_length);
static int uart_output_format(const char *fmt, ...);
static void uart_send();

static const cli_command_t *lookup_command(const char *name, int len);
static int proc_onecmd(vc_cmd_info_struct *cmdInfo, int argc, char *argv[]);
static void Str2UCase(char *str, int len);
static int vc_string_search_chr(char *token, char s);
static char *vc_string_remove_chr(char *str, char *bad);
static void vc_result_code_fmttr(vc_rsp_type_enum rspType, char *rspCmd);
static long vc_strlen(const char *s);
static char *vc_strchr(const char *s, int c);

void cli_uart_init()
{
  memset((void *)uart_tx_buffer, 0, sizeof(uart_tx_buffer));
  memset((void *)uart_rx_buffer, 0, sizeof(uart_rx_buffer));

  for (int i = 0; i < CLI_NUMOF_CMD_HISTORY; i++)
  {
    memset((void *)cmd_history[i], 0, sizeof(cmd_history[i]));
  }

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

static long vc_strlen(const char *s)
{
  long i;
  for (i = 0; s[i] != '\0'; i++) ;
  return i;
}

static char *vc_strchr(const char *s, int c)
{
  while (*s != (char)c)
  {
    if (!*s++) {
      return 0;
    }
  }
  return (char *)s;
}

static const cli_command_t *lookup_command(const char *name, int len)
{
  const cli_command_t *command = NULL;

  for (int i = 0; i < user_commands_length; i++)
  {
    if (len != 0)
    {
      if (strncmp(name, user_commands[i].name, len) == 0)
      {
        command = &user_commands[i];
        break;
      }
    }
    else
    {
      if (strcmp(name, user_commands[i].name) == 0)
      {
        command = &user_commands[i];
        break;
      }
    }
  }

  return command;
}

static int proc_onecmd(vc_cmd_info_struct *cmdInfo, int argc, char *argv[])
{
  const cli_command_t *command = NULL;
  const char *p;
  int i = 0;
  int res = 0;

  if (argc < 1)
  {
    uart_output_format("argc %d\r\n", argc);
    return 0;
  }

	i = ((p = vc_strchr(argv[0], '.')) == NULL) ? 0 : (p - argv[0]);

  command = lookup_command(argv[0], i);

  if (command == NULL)
  {
    uart_output_format("command not found\r\n");
    return 1;
  }

  if (cmdInfo->cmd_type == VC_NORMAL_CMD)
  {
    if (cmdInfo->cmd_exe == VC_EXE_TEST_CMD)
    {
      vc_result_code_fmttr(VC_RCODE_OK, argv[0]);
    }
    else if (cmdInfo->cmd_exe == VC_EXE_READ_CMD || cmdInfo->cmd_exe == VC_EXE_SET_CMD)
    {
      res = command->function(cmdInfo->cmd_exe, argc, argv);

      switch (res)
      {
        case VC_RCODE_OK:
          vc_result_code_fmttr(VC_RCODE_OK, argv[0]);
          break;

        case VC_RCODE_READ_ERROR:
          vc_result_code_fmttr(VC_RCODE_READ_ERROR, argv[0]);
          break;

        case VC_RCODE_DISABLED:
          vc_result_code_fmttr(VC_RCODE_DISABLED, argv[0]);
          break;

        case VC_RCODE_HELP:
          uart_output_format("%s\r\n\r\n", command->help);
          break;
      }
    }
  }
  else
  {
    vc_result_code_fmttr(VC_RCODE_ERROR, argv[0]);
  }

  return 0;
}

static int process_line(char *inbuf, uint16_t length)
{
  static char *argvall[CLI_MAX_ONCECMD_NUM][CLI_MAX_ARG_NUM];
	int argcall[CLI_MAX_ONCECMD_NUM] = { 0 };
	vc_cmd_info_struct vc_cmd_info;
	stat_struct stat;
	int cmdnum = 0;
	int *pargc = &argcall[0];
	int inbufLen = length;
	int i = 0;
  int ret = 0;

  memset((void *)&argvall, 0, sizeof(argvall));
  memset((void *)&argcall, 0, sizeof(argcall));
  memset(&stat, 0, sizeof(stat));

  vc_string_remove_chr(inbuf, " .");
  Str2UCase(inbuf, inbufLen);

  if (inbufLen > 0)
  {
    if(inbuf[0] == 'H' && inbuf[1] == 'E' && inbuf[2] == 'L' && inbuf[3] == 'P')
    {
      vc_cmd_info.cmd_type = VC_NORMAL_CMD;
      vc_cmd_info.cmd_exe = VC_EXE_SET_CMD;
      argvall[0][0] = &inbuf[0];
      argvall[0][1] = &inbuf[1];
      argvall[0][2] = &inbuf[2];
      argvall[0][3] = &inbuf[3];
      ret |= proc_onecmd(&vc_cmd_info, 1, argvall[0]);
      return ret;
    }

		if (inbuf[0] != VC_CHAR_V && inbuf[1] != VC_CHAR_C) {
      uart_output_format("\r\n+CME ERROR: Command header is VC\r\n");
			return ret;
    }
    else
    {
      if (inbuf[2] == VC_CHAR_PLUS)
      {
        vc_cmd_info.cmd_type = VC_NORMAL_CMD;
        vc_cmd_info.cmd_exe = VC_EXE_SET_CMD;
      }
      else if (inbuf[2] == VC_HASH)
      {
        vc_cmd_info.cmd_type = VC_EXTEND_CMD;
      }
      else if (inbuf[2] == VC_HAT)
      {
        vc_cmd_info.cmd_type = VC_INTERNAL_CMD;
      }
      else
      {
        vc_cmd_info.cmd_type = VC_UNKNOW_CMD;
      }

      i = 3;

      do {
        switch (inbuf[i])
        {
          case '\0':
          {
            if (stat.inQuote)
            {
              return 2;
            }
            stat.done = 1;
            break;
          }

          case VC_DOUBLE_QUOTE:
          {
            if (i > 0 && inbuf[i - 1] == '\\' && stat.inArg)
            {
              memcpy(&inbuf[i - 1], &inbuf[i], vc_strlen(&inbuf[i]) + 1);
              --i;
              break;
            }
						if (!stat.inQuote && stat.inArg)
            {
							break;
						}
						if (stat.inQuote && !stat.inArg)
            {
							return 2;
						}
						if (!stat.inQuote && !stat.inArg)
            {
							stat.inArg = 1;
							stat.inQuote = 1;
							(*pargc)++;
							argvall[cmdnum][(*pargc) - 1] = &inbuf[i + 1];
						}
            else if (stat.inQuote && stat.inArg)
            {
							stat.inArg = 0;
							stat.inQuote = 0;
							inbuf[i] = '\0';
						}
						break;
          }

          case VC_SPACE:
          {
						if (i > 0 && inbuf[i - 1] == '\\' && stat.inArg)
            {
							memcpy(&inbuf[i - 1], &inbuf[i], vc_strlen(&inbuf[i]) + 1);
							--i;
							break;
						}
						if (!stat.inQuote && stat.inArg)
            {
							stat.inArg = 0;
							inbuf[i] = '\0';
						}
						break;
          }

          case VC_QUESTION_MARK:
          {
						vc_cmd_info.cmd_exe = VC_EXE_READ_CMD;
						if (i > 0 && inbuf[i - 1] == '\\' && stat.inArg)
            {
							memcpy(&inbuf[i - 1], &inbuf[i], vc_strlen(&inbuf[i]) + 1);
							--i;
							break;
						}
						if (!stat.inQuote && stat.inArg)
            {
							stat.inArg = 0;
							inbuf[i] = '\0';
						}
						break;
          }

          case VC_EQUAL:
          {
						if (inbuf[i + 1] == VC_QUESTION_MARK)
            {
							vc_cmd_info.cmd_exe = VC_EXE_TEST_CMD;
							inbuf[i + 1] = '\0';
						}
            else
            {
							vc_cmd_info.cmd_exe = VC_EXE_SET_CMD;
						}
						if (i > 0 && inbuf[i - 1] == '\\' && stat.inArg)
            {
							memcpy(&inbuf[i - 1], &inbuf[i], vc_strlen(&inbuf[i]) + 1);
							--i;
							break;
						}
						if (!stat.inQuote && stat.inArg)
            {
							stat.inArg = 0;
							inbuf[i] = '\0';
						}
						break;
          }

          case VC_COMMA:
          {
						if (i > 0 && inbuf[i - 1] == '\\' && stat.inArg)
            {
							memcpy(&inbuf[i - 1], &inbuf[i], vc_strlen(&inbuf[i]) + 1);
							--i;
							break;
						}
						if (!stat.inQuote && stat.inArg)
            {
							stat.inArg = 0;
							inbuf[i] = '\0';
						}
						break;
          }

          case VC_SEMI_COLON:
          {
						if (i > 0 && inbuf[i - 1] == '\\' && stat.inArg)
            {
							memcpy(&inbuf[i - 1], &inbuf[i], vc_strlen(&inbuf[i]) + 1);
							--i;
							break;
						}
						if (stat.inQuote)
            {
							return 2;
						}
						if (!stat.inQuote && stat.inArg)
            {
							stat.inArg = 0;
							inbuf[i] = '\0';
							if (*pargc)
              {
								if (++cmdnum < CLI_MAX_ONCECMD_NUM)
                {
									pargc = &argcall[cmdnum];
								}
							}
						}
						break;
          }

          default:
          {
						if (!stat.inArg)
            {
							stat.inArg = 1;
							(*pargc)++;
							argvall[cmdnum][(*pargc) - 1] = &inbuf[i];
						}
						break;
          }
        }
			} while (!stat.done && ++i < CLI_UART_RX_BUFFER_SIZE && cmdnum < CLI_MAX_ONCECMD_NUM && (*pargc) < CLI_MAX_ARG_NUM);

      if (stat.inQuote)
      {
        return 2;
      }

      for (i = 0; i <= cmdnum && i < CLI_MAX_ONCECMD_NUM; i++)
      {
        ret |= proc_onecmd(&vc_cmd_info, argcall[i], argvall[i]);
      }
    }
  }

  return ret;
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
      {
        uart_output(newline, sizeof(newline));

        if (uart_rx_length > 0)
        {
            uart_rx_buffer[uart_rx_length] = '\0';
            uart_process_command();
        }

        uart_output(command_prompt, sizeof(command_prompt));
        break;
      }

      case '\b':
      case 127:
        if (uart_rx_length > 0)
        {
          uart_output(erase_string, sizeof(erase_string));
          uart_rx_buffer[--uart_rx_length] = '\0';
        }
        break;

      case 0x41: // UP
      {
        char *cmd = cmd_history[cmd_history_cur_index];
        cmd_history_cur_index = (cmd_history_cur_index + CLI_NUMOF_CMD_HISTORY - 1) % CLI_NUMOF_CMD_HISTORY;
        strncpy(uart_rx_buffer, cmd, CLI_UART_RX_BUFFER_SIZE); 
        uart_rx_length = vc_strlen(uart_rx_buffer);
        uart_output(newline, sizeof(newline));
        uart_output(command_prompt, sizeof(command_prompt));
        uart_output(uart_rx_buffer, uart_rx_length);
        break;
      }

      case 0x42: // DOWN
      {
        char *cmd = cmd_history[cmd_history_cur_index];
        cmd_history_cur_index = (cmd_history_cur_index + 1) % CLI_NUMOF_CMD_HISTORY;
        strncpy(uart_rx_buffer, cmd, CLI_UART_RX_BUFFER_SIZE); 
        uart_rx_length = vc_strlen(uart_rx_buffer);
        uart_output(newline, sizeof(newline));
        uart_output(command_prompt, sizeof(command_prompt));
        uart_output(uart_rx_buffer, uart_rx_length);
        break;
      }

      case 0x1b: // ESC
        esc = 1;
        break;

      default:
        if (esc && *buf == 0x5b) {
          esc = 0;
          break;
        }

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

  cmd_history_store_index = (cmd_history_store_index + 1) % CLI_NUMOF_CMD_HISTORY;
  cmd_history_cur_index = cmd_history_store_index;

  memset(cmd_history[cmd_history_cur_index], 0, CLI_UART_RX_BUFFER_SIZE);
  strncpy(cmd_history[cmd_history_cur_index], uart_rx_buffer, uart_rx_length);

  int ret = process_line(uart_rx_buffer, uart_rx_length);

  (void)ret;

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
  static char buf[CLI_UART_MAX_LINE_LENGTH];

  memset(buf, 0, sizeof(buf));

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

static void Str2UCase(char *str, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		if (islower((int)str[i])) {
			str[i] = toupper((int)str[i]);
		}
	}
}

/* search for character 's' */
static int vc_string_search_chr(char *token, char s)
{
	if (!token || s == '\0')
		return 0;

	for (; *token; token++)
		if (*token == s)
			return 1;

	return 0;
}

static char *vc_string_remove_chr(char *str, char *bad)
{
	char *src = str, *dst = str;

	/* validate input */
	if (!(str && bad))
		return NULL;

	while (*src)
		if (vc_string_search_chr(bad, *src))
			src++;
		else
			*dst++ = *src++;          /* assign first, then incement */

	*dst = '\0';
	return str;
}

static void vc_result_code_fmttr(vc_rsp_type_enum rspType, char *rspCmd)
{
	switch (rspType)
	{
		case VC_RCODE_OK: {
			uart_output_format("+%s:OK\r\n", rspCmd);
			break;
		}
		case VC_RCODE_DISABLED: {
      uart_output_format("\r\n+CME Error: %s disabled!!\r\n", rspCmd);
			break;
		}

		case VC_RCODE_ERROR: {
			uart_output_format("\r\n+CME Error: %s not support!!\r\n", rspCmd);
			break;
		}

    case VC_RCODE_READ_ERROR: {
			uart_output_format("\r\n+CME Error: %s not support read\r\n", rspCmd);
			break;
		}

    case VC_RCODE_HELP: {
			break;
		}
        
		case VC_RCODE_NOTFIND: {
			uart_output_format("\r\n+CME ERROR: Command +%s not found\r\n", rspCmd);
			break;
		}
	}
}
