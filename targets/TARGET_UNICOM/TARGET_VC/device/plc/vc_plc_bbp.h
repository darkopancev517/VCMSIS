#ifndef VC_PLC_BBP_H_
#define VC_PLC_BBP_H_

#include "vc_plc_flash_map.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DSP_IRAM_SIZE  (72 * 1024)
#define DSP_DATA0_SIZE (76 * 1024)
#define DSP_DATA1_SIZE (64 * 1024)

#define DSP_IRAM_BASE  0x20080000
#define DSP_DATA0_BASE 0x200C0000
#define DSP_DATA1_BASE 0x200E0000
#define DSP_END			   0x20100000

#define BBP_READ_FLAG	0x1000

#define MAX_BBP_STALL_TIME 20

#define FLASH_TS2_LD_CH3_OFFSET 0x1FFFF4
#define EEPROM_TS2_85C			    0x4004F018


#define FLASH_HVIN_03V 0x1FFFD0
#define FLASH_HVIN_09V 0x1FFFD4
#define EEPROM_HVIN	0x4004F01C


enum BBP_CMD {
  BBP_CMD_SET_BANDPLAN = 0x1,
  BBP_CMD_SET_MODULATION = 0x6,
  BBP_CMD_PMB_DET_SCALE = 0x7,
  BBP_CMD_NOISE_ADDR_READ=0xE,
  BBP_CMD_NOISE_DUMP=0xAAA,
  BBP_CMD_FW_ABORT_EIFS = 0x72,
  BBP_CMD_SET_RX_THRESHOLD = 0x68,
  BBP_CMD_SET_NBIE = 0x3F,
  BBP_CMD_SET_CALIBRATE = 0x10,
  BBP_CMD_SET_CALIBRATE_OT = 0x0,
  BBP_CMD_SET_CALIBRATE_HVIN = 0x1,
  BBP_CMD_SET_MAX_SWING = 0x90,
  BBP_CMD_SET_IMPN = 0x56,
  BBP_CMD_SET_62 = 0x62,
  BBP_CMD_SET_TX_SWING =0x59,
  BBP_CMD_SET_DSP_INTERRUPT =0x8D,
  BBP_CMD_SET_TONEMAP_BAND =0x8F,
  BBP_CMD_SET_NOTIFY_TX_ADEAD = 0x8E,
  BBP_CMD_SET_SYNCP_LEN = 0x2D,
  BBP_CMD_GET_TEMPERATURE = 0x99,

  BBP_CMD_PMB_NOISE_THRSH = 0x13,
  BBP_CMD_SET_URGENTIN_EN = 0x2A,
  BBP_CMD_PMB_SYNCP_SYMB = 0x2D,
  BBP_CMD_VERTEX_BAND_FREQ = 0x2E,
  BBP_CMD_TDP_FIR3_SCALE = 0x2F,
  BBP_CMD_LD_VOLT_MODE = 0x30,
  BBP_CMD_PGA_MODE = 0x31,
  BBP_CMD_PMB_DET_SCALE_MISC = 0x33,
  BBP_CMD_PMB_FIX_RX_FILT_PWR = 0x34,
  BBP_CMD_PMB_DET_IDLE_GAIN_MISC = 0x35,
  BBP_CMD_NOISE_FLOOR = 0xFFF,
  BBP_CMD_GET_RX_GAIN_PWR = 0x36,
  BBP_CMD_AGC_ANALOG_EXT_GAIN = 0x3A,
  BBP_CMD_PMB_DET_IDLE_GAIN_SENSE_TIME = 0x3B,
  BBP_CMD_TRANSFORMER_105_SET_ENABLE = 0x3C,
};

typedef struct _BBP_GLOBAL {
  NVDM_BBP_VER_SECTION bbp_ver;
  uint32_t ir4_value;
  uint8_t	bbp_idle;
  uint32_tnoise_addr;		
  uint32_t f_bbp_sniffer_mode:1;
  uint32_t f_reserved:31;
  int	swing;
  uint16_t	tx_notify;
} BBP_GLOBAL;

extern BBP_GLOBAL	gBBP;

#define BBP_CMD_MAX_PARAM 7

typedef struct _BBP_CMD_PARAM {
  uint32_t cmd;
  uint32_t param[BBP_CMD_MAX_PARAM];
  uint32_t total_len;
} BBP_CMD_PARAM;

void vc_bbp_init();
void vc_bbp_uninit();
int vc_cli_bbp(vc_cmd_exe eType, char *buf, int len, int argc, char **argv);
void vc_ver_time(uint32_t version_time);
void vc_nvram_get_bbp_version();
void vc_bbp_rx_data_porcess(uint32_t *prt_data, int prt_num);
void vc_check_bbp_alive();
void vcg3_disable_ire();
void vcg3_enable_ire();
void vc_bbp_get_temperature();

#ifdef __cplusplus
}
#endif

#endif /* VC_PLC_BBP_H_ */
