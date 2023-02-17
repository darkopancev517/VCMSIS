#ifndef _VC_LMAC_XH_H_
#define _VC_LMAC_XH_H_

#include "vc_type.h"

#define VC_LMAC_RAW_CMD_DELAY_SEND_NUM 10
#define VC_LMAC_CSMA_TAIL_PROTECT 100

typedef enum vc_lmac_kick_dma {
	VC_KICK_DMA_NULL = 0x00,
	VC_KICK_DMA_CXQ_SEND,
	VC_KICK_DMA_CXQ_SEND_2,
	VC_KICK_DMA_BBP_PKT,
	VC_KICK_DMA_ITNWC,
	VC_KICK_DMA_TRANS_MODE,
	VC_KICK_DMA_LONG_PKT,
	VC_KICK_DMA_PHY_ITNWC_PING,
	VC_KICK_DMA_PHY_SOF_PING,
	VC_KICK_DMA_SOF_PING,
	VC_KICK_DMA_TXDATA_SNED,
	VC_KICK_DMA_TXQ_SEND,
	VC_KICK_DMA_API_ITNWC_SNED,
	VC_KICK_DMA_API_SOF_SNED,
	VC_KICK_DMA_BEACON_SEND,
	VC_KICK_DMA_GET_IRQ_TXP_DONE,
	VC_KICK_DMA_GET_IRQ_DSP_ABORT,
	VC_KICK_DMA_GET_IRQ_RXP_DONE,
	VC_KICK_DMA_GET_IRQ_GET_SACK,
	VC_KICK_DMA_GET_IRQ_RESP_SACK,
	VC_KICK_DMA_GET_IRQ_ABORT_SACK,
	VC_KICK_DMA_GET_IRQ_GET_PARA,
	VC_KICK_DMA_GET_IRQ_CSMA_SUCCESS,
	VC_KICK_DMA_GET_IRQ_CSMA_FAIL,
	VC_KICK_DMA_GET_IRQ_CSMA_ABORT,
	VC_KICK_DMA_GET_IRQ_CSMA_TIMEUP,
	VC_KICK_DMA_GET_IRQ_TDMA_TIMEUP,
	VC_KICK_DMA_GET_IRQ_TDMA_FAIL,
	VC_KICK_DMA_GET_IRQ_KICK_PHY,
}vc_lmac_kick_dma;

typedef enum vc_lmac_raw_cmd {
	VC_LMAC_RCMD_BAND = 0x01,
	VC_LMAC_RCMD_CFG_DSP_AUTO_CNT=0x04,
	VC_LMAC_RCMD_SAR_ADC = 0x10,
	VC_LMAC_RCMD_FNPLL_INIT=0x4F,
	VC_LMAC_RCMD_FNPLL_FORCE = 0x50,
	VC_LMAC_RCMD_TONEMASK = 0x54,
	VC_LMAC_RCMD_CFG_PHY_TX_SWING =0x55,
	VC_LMAC_RCMD_BCN_NTB_OFFSET = 0x76,
	VC_LMAC_RCMD_NOTIFY_PHY_DISCONNECT =0x78,
	VC_LMAC_RCMD_CFG_DSP_DUAL_BCN = 0x87,
	VC_LMAC_RCMD_CFG_CIU = 0xCC,
	VC_LMAC_RCMD_CFG_NID = 0xAA9,
	VC_LMAC_RCMD_CFG_NID_TEI = 0xAAA,
}vc_lmac_raw_cmd;

typedef struct tBbpRawCmd {
	vc_uint8 direct;
	vc_uint8 bandSetting;
	vc_uint8 band;
	vc_uint8 toneMaskSetting;
	vc_uint8 toneMask;
	vc_uint32 bbpCmd[8];
	vc_uint16 bbpCmdLen;
}tBbpRawCmd;

typedef struct gTxRawCmdDelaySend {
	vc_uint8 isUsed;
	tBbpRawCmd RawCmd;
}gTxRawCmdDelaySend;

typedef struct vc_lmac_pkt_symbol_by_cal {
	vc_uint16 PbSize;
	vc_uint16 BPC;
	vc_uint16 copyNum;
	vc_uint16 intNum;
}vc_lmac_pkt_symbol_by_cal;

typedef struct vc_lmac_pkt_sym_info {
	vc_uint16 PbSize;
	vc_uint16 symbolNum;
}vc_lmac_pkt_sym_info;

typedef struct vc_lmac_pkt_sym_mapping {
	vc_uint8 band;
	vc_uint8 TypeTMI;
	float pmbTime; /*40.96us*/
	float fcTime;  /*59.28us*/
	float pldTime; /*51.52us*/
	vc_lmac_pkt_symbol_by_cal InfoTMI[16];
}vc_lmac_pkt_sym_mapping;

typedef enum vc_lmac_extTMI {
	BPLC_TMI,
	BPLC_E_TMI
}vc_lmac_extTMI;

typedef enum efc_delimiter {
	BEACON_F        = 0,
	SOF_F           = 1,
	SACK_F          = 2,
	INTER_NET_COR_F = 3,
	RTS_CTS_F       = 4,
	RSV             = 5,
	PHY_TEST        = 6,
}efc_delimiter;

typedef struct tCN_BEACON_FC {
	/*0~3*/
	vc_uint32 delType : 3;
	vc_uint32 netType : 5;
	vc_uint32 NID : 24;
	/*4~7*/
	vc_uint32 BconVar_timeStamp : 32;
	/*8~11*/
	vc_uint32 BconVar_STEI : 12;
	vc_uint32 BconVar_TMI : 4;
	vc_uint32 BconVar_symboNum : 9;
	vc_uint32 BconVar_phaseLine : 2;
	vc_uint32 BconVar_rsv : 5;
	/*12*/
	vc_uint8 BconVar_rsv2 : 4;
	vc_uint8 version : 4;
	/*13~15*/
	vc_uint8 fccs[3];
}__attribute__((packed)) tCN_BEACON_FC;

typedef struct tCN_SACK_FC {
	/*0~3*/
	vc_uint32 delType : 3;
	vc_uint32 netType : 5;
	vc_uint32 NID : 24;
	/*4~7*/
	vc_uint32 SackVar_result : 4;
	vc_uint32 SackVar_status : 4;
	vc_uint32 SackVar_STEI : 12;
	vc_uint32 SackVar_DTEI : 12;
	/*8~11*/
	vc_uint32 SackVar_recPbCount : 3;
	vc_uint32 SackVar_rsv0 : 5;
	vc_uint32 SackVar_chQuality : 8;
	vc_uint32 SackVar_staLoad : 8;
	vc_uint32 SackVar_rsv1 : 8;
	/*12*/
	vc_uint32 SackVar_extFramType : 4;
	vc_uint8 version : 4;
	/*13~15*/
	vc_uint8 fccs[3];
}__attribute__((packed)) tCN_SACK_FC;

typedef struct tCN_ITNWC_FC {
	/*0~3*/
	vc_uint32 delType : 3;
	vc_uint32 netType : 5;
	vc_uint32 NID : 24;
	/*4~7*/
	vc_uint32 continueTime : 16;
	vc_uint32 bandStartShift : 16;
	/*8~11*/
	vc_uint32 receiveNightbor : 24;
	vc_uint32 rsv0 : 8;
	/*12*/
	vc_uint8 rsv1 : 4;
	vc_uint8 version : 4;
	/*13~15*/
	vc_uint8 fccs[3];
}__attribute__((packed)) tCN_ITNWC_FC;

typedef struct tCN_SOF_FC {
	/*0~3*/
	vc_uint32 delType : 3;
	vc_uint32 netType : 5;
	vc_uint32 NID : 24;
	/*4~7*/
	vc_uint32 SofVarSTEI : 12;
	vc_uint32 SofVarDTEI : 12;
	vc_uint32 SofVarLID : 8;
	/*8~11*/
	vc_uint32 SofVarFL : 12;
	vc_uint32 SofVarPBCount : 4;
	vc_uint32 SofVarSymbolNum : 9;
	vc_uint32 SofVarBcastFlag : 1;
	vc_uint32 SofVarResendFlag : 1;
	vc_uint32 SofVarEncryptFlag : 1;
	vc_uint32 SofVarTMI : 4;
	/*12*/
	vc_uint8 SofVarExtTMI : 4;
	vc_uint8 version : 4;
	/*13~15*/
	vc_uint8 fccs[3];
}__attribute__((packed)) tCN_SOF_FC;

#define LAST_CSMA_NONE          0
#define LAST_CSMA_ITNWC         1
#define LAST_CSMA_TRANSPARENT   2
#define LAST_CSMA_LONGP         3
#define LAST_CSMA_PING          4
#define LAST_CSMA_TXDATA        5
#define LAST_CSMA_SACK_YES      7
#define LAST_CSMA_SACK_NO       8

typedef enum eVC_SACK_TYPE {
	VC_SACK_NOT,
	VC_SACK_NEED,
}eVC_SACK_TYPE;

typedef enum eVC_CSMA_PKT_TYPE {
	BCON_PKT   = 0,
	SOF_PKT    = 1,
	SACK_PKT   = 2,
	ITNWC_PKT  = 3,
	RCTS_PKT   = 4,
}eVC_CSMA_PKT_TYPE;

typedef enum extendCmdMode{
  extCmdModeOff=0, // normal mode
	extCmdMode1=1,/*rsv*/
	extCmdMode2,/*rsv*/
	extCmdMode3_phyTransparent,
	extCmdMode4_phyReply,
	extCmdMode5_macTransparent,
	extCmdMode6_bandSetting,
	extCmdMode7_toneMaskSetting,
	extCmdMode8_vertexcomTesting,
}extendCmdMode;

typedef struct vc_extend_cmd{
	extendCmdMode mode;
	extendCmdMode modeReal;
}vc_extend_cmd;

typedef enum {
	MAC_TXQ_RADIO_NULL,
	MAC_TXQ_RADIO_APP,
	MAC_TXQ_RADIO_NMS,
	MAC_TXQ_RADIO_FW,
	MAC_TXQ_RADIO_LINKRP,
	MAC_TXQ_RADIO_HIGH_PRIO,
	MAC_TXQ_RADIO_HIGH_PRIO_FW,
	MAC_TXQ_RADIO_NUM_MAX
}tMacTxQRadio;

typedef struct vc_bcn_timeslot_s {
	// byte 0
	vc_uint8 non_central_bcn_cnt;
	// byte 1
	vc_uint8 central_bcn_cnt : 4;
	vc_uint8 csma_phase_cnt : 2;
	vc_uint8 byte1_padding : 2;
	// byte 2
	vc_uint8 byte2_padding;
	// byte 3
	vc_uint8 proxy_bcn_cnt;
	// byte 4
	vc_uint8 bcn_slot_length;
	// byte 5
	vc_uint8 csma_slot_length;
	// byte 6
	vc_uint8 binding_csma_slot_phase_cnt;
	// byte 7
	vc_uint8 binding_csma_slot_link_id;
	// byte 8
	vc_uint8 tdma_slot_duration;
	// byte 9
	vc_uint8 tdma_slot_link_id;
	// byte 10~13
	vc_ntb32 bcn_start_NTB;
	// byte 14~17
	vc_uint32 beacon_period;
	// byte 18~19
	vc_uint8 reserved[2];
} __attribute__((packed)) vc_bcn_timeslot_s;

typedef struct vcCsmaSlotInfo_s {
	vc_uint32 phase_a_len : 24;
	vc_uint32 phase_a : 2;
	vc_uint32 rsv_a : 6;
	vc_uint32 phase_b_len : 24;
	vc_uint32 phase_b : 2;
	vc_uint32 rsv_b : 6;
	vc_uint32 phase_c_len : 24;
	vc_uint32 phase_c : 2;
	vc_uint32 rsv_c : 6;
} __attribute__((packed)) vcCsmaSlotInfo_s;

void vc_lmac_tx_bbp_pkt_f_cmd(
	tBbpRawCmd *pBbpRawCmd);

void vc_lmac_tx_bcon_pkt_f_sch(
	vc_uint32 tdmaNTB,
	vc_uint8 phase,
	vc_uint8 role,
	vc_uint16 beaconLen,
	vc_uint8 *beaconPtr,
	vc_bcn_timeslot_s *timeslotPtr,
	vcCsmaSlotInfo_s *csmainfoPtr,
	vc_uint32 ntb);

void vc_lmac_tx_sof_pkt_f_cmd_sig_test(
	vc_uint8 isPassPkt,
	vc_uint16 DTEI,
	vc_uint8 extTmi,
	vc_uint8 tmi,
	vc_uint8 pbCount,
	vc_uint8 *macAddr,
	vc_uint8 ledBitMap,
	vc_uint8 ledSwitch);

#endif
