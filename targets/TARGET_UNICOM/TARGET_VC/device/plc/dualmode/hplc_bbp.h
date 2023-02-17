#ifndef HPLC_BBP_H
#define HPLC_BBP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_MCU_VC6320)
#define PHY_REG_BASEADDR 0x400111c0
#endif

#if defined(DEVICE_MCU_VC6330)
#define PHY_REG_BASEADDR 0x400111a0
#endif

#define PHY_IDLE_MASK	 (1 << 2)

typedef struct PHY_REG {
#if defined(DEVICE_MCU_VC6330)
  uint32_t ntb_cnt; //0x1A0
  uint32_t ntb_zc1; //0x1A4
  uint32_t ntb_zc2; //0x1A8
  uint32_t ntb_zc3; //0x1AC
  uint32_t zc_cr;   //0x1B0
  uint32_t zc_sr1;  //0x1B4
  uint32_t zc_sr2;  //0x1B8
  uint32_t zc_pdc;  //0x1BC
#endif
	uint32_t phy_cr1; //0x1C0
	uint32_t phy_cr2; //0x1C4
	uint32_t phy_cr3; //0x1C8
	uint32_t phy_cr4; //0x1CC
	uint32_t phy_ir1; //0x1D0
	uint32_t phy_ir2; //0x1D4
	uint32_t phy_ir3; //0x1D8
	uint32_t phy_ir4; //0x1DC
#if defined(DEVICE_MCU_VC6330)
  uint32_t phy_cr5; //0x1E0
  uint32_t phy_cr6; //0x1E4
  uint32_t phy_cr7; //0x1E8
  uint32_t phy_cr8; //0x1EC
  uint32_t phy_ir5; //0x1F0
  uint32_t phy_ir6; //0x1F4
  uint32_t phy_ir7; //0x1F8
  uint32_t phy_ir8; //0x1FC
#endif
#if defined(DEVICE_MCU_VC6320)
	uint32_t ntb_cnt; //0x1E0
	uint32_t ntb_zc1; //0x1E4
	uint32_t ntb_zc2; //0x1E8
	uint32_t ntb_zc3; //0x1EC
#endif
} PHY_REG;

typedef struct bbpRawCmdStruct{
	uint8_t direct;
	uint8_t bandSetting;
	uint8_t band;
	uint8_t toneMaskSetting;
	uint8_t toneMask;
	uint32_t bbpCmd[16];
	uint16_t bbpCmdLen;
} bbpRawCmdStruct;

typedef enum vc_lmac_raw_cmd {
	VC_LMAC_RCMD_BAND = 0x01,
	VC_LMAC_RCMD_SAR_ADC = 0x10,
	VC_LMAC_RCMD_FNPLL_INIT=0x4F,
	VC_LMAC_RCMD_FNPLL_FORCE = 0x50,
	VC_LMAC_RCMD_TONEMASK = 0x54,
	VC_LMAC_RCMD_CFG_PHY_TX_SWING =0x55,
	VC_LMAC_RCMD_BCN_NTB_OFFSET = 0x76,
	VC_LMAC_RCMD_NOTIFY_PHY_DISCONNECT =0x78,
	VC_LMAC_RCMD_CFG_CIU = 0xCC,
	VC_LMAC_RCMD_CFG_NID = 0xAA9,
	VC_LMAC_RCMD_CFG_NID_TEI = 0xAAA,
} vc_lmac_raw_cmd;

typedef enum lmacBbpRawCmdType {
	LMAC_BBP_RAW_CMD_VER_CNF = 0x1002,
	LMAC_BBP_RAW_CMD_RXC_CNF = 0x100F,
	LMAC_BBP_RAW_CMD_TXC_CNF = 0x1037,
	LMAC_BBP_RAW_CMD_PWR_CNF = 0x1055,
} lmacBbpRawCmdType;

extern void vc_phy_init(void);
extern void vc_lmac_phy_band(uint32_t band);
extern uint8_t vc_phy_check_idle();
extern uint32_t vc_phy_get_ntb();
extern uint8_t vc_lmac_dw(uint32_t hexAddr, uint16_t nrByte);
extern void vc_lmac_phy_cfg_txpwr(uint8_t txpwr);
extern void vc_lmac_pwr();
extern void vc_lmac_rxc();
extern void vc_lmac_txc();
extern void vc_lmac_ver();
extern void vc_lmac_tx_pkt();
extern void vc_lmac_tx_bbp_pkt_f_cmd(bbpRawCmdStruct *pBbpRawCmd);
extern void vc_bbp_init(void);

#ifdef __cplusplus
}
#endif

#endif // HPLC_BBP_H
