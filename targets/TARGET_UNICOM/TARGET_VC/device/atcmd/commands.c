#include "hal/gpio_api.h"
#include "hal/us_ticker_api.h"
#include "hal/serial_api.h"
#include "hal/rtc_api.h"
#include "hal/lp_ticker_api.h"

#include "cli.h"
#include "vc_lib.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#if defined(DEVICE_MCU_VC6330) || defined(DEVICE_MCU_VC6320)
#include "vc_lmac.h"
#include "vc_lmac_txh.h"
extern void vc_phy_init(void);
extern void vc_lmac_init(void);
#endif

int cli_cmd_help(vc_cmd_exe atype, int argc, char **argv);
int cli_cmd_mem_wm(vc_cmd_exe atype, int argc, char **argv);
int cli_cmd_mem_dm(vc_cmd_exe atype, int argc, char **argv);
#if defined(DEVICE_MCU_VC6330) || defined(DEVICE_MCU_VC6320)
int cli_cmd_bbp(vc_cmd_exe atype, int argc, char **argv);
int cli_cmd_tx(vc_cmd_exe atype, int argc, char **argv);
#endif

const cli_command_t user_command_list[] = {
  { "HELP", NULL, cli_cmd_help },
  { "WM", "+WM=mem_addr, mem_data", cli_cmd_mem_wm },
  { "DM", "+DM=mem_addr, numof_words (default=16)", cli_cmd_mem_dm },
#if defined(DEVICE_MCU_VC6330) || defined(DEVICE_MCU_VC6320)
  { "BBP", "+BBP", cli_cmd_bbp },
  { "TX", "+TX=packet_number, length, idle_time", cli_cmd_tx },
#endif
};

uint8_t user_command_length = sizeof(user_command_list) / sizeof(cli_command_t);

int cli_cmd_help(vc_cmd_exe atype, int argc, char **argv)
{
  if (atype == VC_EXE_READ_CMD)
  {
    return VC_RCODE_READ_ERROR;
  }
  else if (atype == VC_EXE_SET_CMD)
  {
    printf("num %u\r\n", user_command_length);
    for (int i = 1; i < user_command_length; i++)
    {
      printf("%s\r\n", user_command_list[i].help);
    }
  }
  return VC_RCODE_OK;
}

void word_dump(const char *indent, const void *data, uint32_t nr_words)
{
  volatile uint32_t *addr = (volatile uint32_t *)(((uint32_t)data + 3) & ~3);
  uint32_t nr_lines, i;

  if (nr_words <= 0)
  {
    return;
  }

  nr_lines = nr_words / 4;

  while (nr_lines--)
  {
    printf("%08X | %08X %08X - %08X %08X\r\n",  (unsigned int)addr, (unsigned int)addr[0], (unsigned int)addr[1], (unsigned int)addr[2], (unsigned int)addr[3]);
    addr += 4;
  }

  nr_words = nr_words & 3;

  if (nr_words) 
  {
    printf("%08X | ",  (unsigned int)addr);

    for (i = 0; i < nr_words; ++i)
    {
      if (i == 2)
      {
        printf(" -");
      }
      printf("%08X ", (unsigned int)addr[i]);
    }
    printf("\r\n");
  }
}

int cli_cmd_mem_wm(vc_cmd_exe atype, int argc, char **argv)
{
  uint32_t addr=0, data=0;
  uint32_t nr_words=3, nr, a;

  if(atype == VC_EXE_READ_CMD)
  {
    return VC_RCODE_READ_ERROR;
  }

  if(atype == VC_EXE_SET_CMD)
  {
    if(argc < 5)
    {
      addr = (uint32_t)vc_strtox(argv[1],NULL);
      data = (uint32_t)vc_strtox(argv[2],NULL);

      if(argc == 4)
      {
        nr_words = (uint32_t)vc_strtox(argv[3],NULL);
      }
      else if(argc == 3)
      {
        nr_words = 1;
      }
      else
      {
        return VC_RCODE_DISABLED;
      }

      a = addr;
      nr = nr_words;

      while(nr-- > 0)
      {
        *((volatile uint32_t *)a) = data;
        a += 4;
      }

      word_dump(NULL, (void *)(addr & ~0x3), nr_words);
    }
    else
    {
      return VC_RCODE_HELP;
    }
  }
  return VC_RCODE_OK;
}

int cli_cmd_mem_dm(vc_cmd_exe atype, int argc, char **argv)
{
  uint32_t addr=0;
  uint32_t nr_words = 0;

  if(atype == VC_EXE_READ_CMD)
  {
    return VC_RCODE_READ_ERROR;
  }
  else if(atype == VC_EXE_SET_CMD)
  {
    if(argc <2)
    {
      return VC_RCODE_DISABLED;
    }
    else
    {
      addr = (uint32_t)vc_strtox(argv[1], NULL);
      if(argc == 3)
      {
        nr_words = (uint32_t)vc_strtoul(argv[2], NULL);
      }
      else
      {
        nr_words =16;
      }
      printf("Addr=%X, len=%d\r\n\r\n", (unsigned int)addr, (int)nr_words);
      word_dump(NULL, (void *)(addr & ~0x3), nr_words);
    }
  }
  return VC_RCODE_OK;
}

#if defined(DEVICE_MCU_VC6330) || defined(DEVICE_MCU_VC6320)
 uint32_t vc_cli_read_array(char **argv, uint32_t start, uint32_t end, uint32_t *data, bool hex)
{
  uint32_t nr_words = end - start;
  uint32_t i;

  for (i = 0; i < nr_words; ++i)
  {
    ((volatile uint32_t *)data)[i] = hex ? (uint32_t)vc_strtox(argv[start + i], NULL) : (uint32_t)vc_strtoul(argv[start + i], NULL);
  }

  return nr_words;
}

int cli_cmd_bbp(vc_cmd_exe atype, int argc, char **argv)
{
  if (atype == VC_EXE_READ_CMD)
  {
    return VC_RCODE_READ_ERROR;
  }
  else if (atype == VC_EXE_SET_CMD)
  {
    if (strcmp(argv[1], "INIT") == 0)
    {
      vc_phy_init();
      vc_lmac_init();
    }
    else // bbp raw
    {
      uint32_t nr_words;
      uint32_t data[8];

      tBbpRawCmd bbpRawCmd;
      memset(&bbpRawCmd, 0, sizeof(tBbpRawCmd));

      memset(data, 0, sizeof(data));

      nr_words = vc_cli_read_array(argv, 1, min(argc, 8), data, true);

      memcpy(&bbpRawCmd.bbpCmd[0], data, sizeof(data));
      bbpRawCmd.bbpCmdLen = nr_words * 4;

      printf("input: [ ");

      for (int i = 0; i < nr_words; i++)
      {
        printf("%x ", (unsigned int)data[i]);
      }

      printf("]\r\n");

      vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
    }
  }

  return VC_RCODE_OK;
}

extern void vc_lmac_cfg_phy_NID(vc_uint32 pNID);
extern vc_ntb32 vc_phy_get_ntb();

vc_uint8 dummyBcn[520] = { 0 };

int cli_cmd_tx(vc_cmd_exe atype, int argc, char **argv)
{
  int res = VC_RCODE_OK;

  if (atype == VC_EXE_SET_CMD)
  {
    if (strcmp(argv[1], "TEST") == 0)
    {
      // vc_lmac_tx_sof_pkt_f_cmd_sig_test(
      //   0,
      //   0xFFF,
      //   0,
      //   4,
      //   1,
      //   NULL,
      //   0x00,
      //   0x00);

      LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
      vc_ntb32 pNTB = 0x00;
      vc_ntb32 wNTB = 0x00;
      vc_uint16 i = 0;

      vc_lmac_cfg_phy_NID(0xDEBEEF);

      pNTB = vc_phy_get_ntb();
      wNTB = pNTB + (5 * 25000);
      gLMAC->LMAC_STEI = 0x001;
      gLMAC->LMAC_NID = 0xDEBEEF;

      for (i = 0; i < 520; i++) {
        dummyBcn[i] = 0xAB;
      }

      vc_lmac_tx_bcon_pkt_f_sch(
        wNTB,
        1,
        4,
        136,
        (vc_uint8 *)&dummyBcn[0],
        (vc_bcn_timeslot_s *)&dummyBcn[0],
        (vcCsmaSlotInfo_s *)&dummyBcn[0],
        pNTB);
    }
  }

  return res;
}
#endif
