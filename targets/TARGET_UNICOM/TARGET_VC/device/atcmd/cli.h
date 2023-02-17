#ifndef CLI_H
#define CLI_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CLI_NUMOF_CMD_HISTORY 10

#define CLI_MAX_ARG_NUM 16
#define CLI_MAX_ONCECMD_NUM 6

#define CLI_UART_RX_BUFFER_SIZE 128
#define CLI_UART_TX_BUFFER_SIZE 128
#define CLI_UART_MAX_LINE_LENGTH 128

#define DPrintf(fmt, ...) \
	printf(fmt "\r\n", ## __VA_ARGS__)
#define DDump(fmt, ...) \
	printf(fmt, ## __VA_ARGS__)
#define vcCmdPrintf(fmt, ...) \
	printf(fmt "\r\n", ## __VA_ARGS__)
#define vcCmdDump(fmt, ...) \
	printf(fmt, ## __VA_ARGS__)
#define vcSnifPrintf(fmt, ...) \
	printf(fmt "\r\n", ## __VA_ARGS__)
#define vcSnifDump(fmt, ...) \
	printf(fmt, ## __VA_ARGS__)

enum {
	VC_CHAR_V = 'V',
	vc_char_v = 'v',
	VC_CHAR_C='C',
	vc_char_c = 'c',
  VC_CHAR_A = 'A',
  VC_CHAR_T = 'T',
  VC_CHAR_a = 'a',
  VC_CHAR_t = 't',    
	VC_SPACE=' ',
	VC_EQUAL= '=',
	VC_COMMA = ',',
	VC_DOUBLE_QUOTE  = '"',
	VC_SEMI_COLON  = ';',
	VC_QUESTION_MARK='?',
	VC_CHAR_PLUS='+',
	VC_HASH = '#',
	VC_HAT = '^',
};

typedef enum vc_rsp_type_enum {
	VC_RCODE_OK,
	VC_RCODE_DISABLED,
	VC_RCODE_ERROR,
	VC_RCODE_READ_ERROR,
	VC_RCODE_NOTFIND,
	VC_RCODE_HELP
} vc_rsp_type_enum;

typedef enum vc_cmd_type {
	VC_NULL_CMD,	  
	VC_NORMAL_CMD,	  
	VC_EXTEND_CMD,	 
	VC_INTERNAL_CMD,
	VC_READ_CMD,  
	VC_HELP_CMD,
	VC_UNKNOW_CMD	  
} vc_cmd_type;

typedef enum vc_cmd_exe {
	VC_EXE_NULL_CMD,
	VC_EXE_TEST_CMD,
	VC_EXE_READ_CMD,
	VC_EXE_SET_CMD,
	VC_EXE_NUKNOW_CMD,
} vc_cmd_exe;

typedef struct vc_cmd_info_struct {
	vc_cmd_type cmd_type;
	vc_cmd_exe cmd_exe;
} vc_cmd_info_struct;

typedef struct stat_struct {
	unsigned inArg : 1;
	unsigned inQuote : 1;
	unsigned done : 1;
} stat_struct;

typedef struct cli_command {
	const char *name;
	const char *help;
	int (*function)(vc_cmd_exe exeType, int argc, char **argv);
} cli_command_t;

void cli_uart_init();
void cli_uart_run();
void cli_set_user_commands(const cli_command_t *user_commands, uint8_t length);

#ifdef __cplusplus
}
#endif

#endif // CLI_H
