#ifndef _VC_LMAC_H_
#define _VC_LMAC_H_

#include "vc_type.h"

#define VC_SWAP_16(n) (vc_uint16)((((vc_uint16)(n)) << 8) | (((vc_uint16)(n)) >> 8))

#define LMAC_CHANGE_STATE(state) \
	vc_lmac_change_state(state)

#define VC_HPLC_DSP_AUTO_ACK_ARQ 1

#define LMAC_ZERO_CROSSING_RETRIEVE_RECORD_MAX  340 //140  5000ms
#define BBP_RAW_ASYN_PRINT_MAX 50
#define BBP_RAW_ASYN_TASK_PRINT_DELAY 100

#define LMAC_RETRANSMIT_MAX_RETRY_TIMES     18
#define LMAC_CSMA_MAX_BE                    10
#define LMAC_CSMA_MIN_BE                    5
#define LMAC_CSMA_MAX_BACKOFFS              (LMAC_CSMA_MAX_BE - LMAC_CSMA_MIN_BE + 3)
#define LMAC_CSMA_BACKOFF_PERIOD            400
#define LMAC_CSMA_DEFAULT_PERIOD            400
#define LMAC_CSMA_SEGMENT_US                10000
#define VC_BPLC_CIU_SERVICE_TEI             (vc_uint16)0x0EEEu
#define LMAC_DEFAULT_BAND                   2
#define LMAC_MAX_BAND_SEARCH_RETRY_ROUND    5

#define LMAC_ARQ_ENABLE           1
#define LMAC_SACK_ENABLE          1
#define LMAC_RIFS                 400   /*us*/
#define LMAC_RIFS_OFFSET          10    /*us*/
#define LMAC_CIFS                 400   /*us*/
#define LMAC_EIFS                 28500 /*us*/
#define LMAC_WAIT_SACK_TOLERANCE  2000  /*us, the tolerance is for system process time*/
#define LMAC_WAIT_SACK_TIME       (LMAC_RIFS + LMAC_WAIT_SACK_TOLERANCE) * LMAC_NTB2US_UNIT

typedef struct lmac_dsp_watch_dog {
	vc_uint8 dsp_tx;
	vc_uint8 dsp_rx;
	vc_uint8 dsp_sys;
	vc_uint8 dsp_tx_cnt;
	vc_uint8 dsp_rx_cnt;
	vc_uint8 dsp_sys_cnt;
	vc_uint8 dsp_non_idle;
}lmac_dsp_watch_dog;

typedef enum vc_lmac_band_plan {
	BPLC_BAND_0,
	BPLC_BAND_1,
	BPLC_BAND_2,
	BPLC_BAND_3
}vc_lmac_band_plan;

typedef enum eVC_LMAC_ROLE {
	LMAC_ROLE_UNKNOW=0x00,
	LMAC_ROLE_CCO =0x01,
	LMAC_ROLE_STA = 0x02,
}eVC_LMAC_ROLE;

typedef enum eLMAC_NX_SCH {
	LMAC_SCH_PREPARE = 0,
	LMAC_SCH_BCON,
	LMAC_SCH_CSMA,
}eLMAC_NX_SCH;

typedef struct lmac_sch_struct {
	vc_uint8 csmaUrgent;
	eVC_LMAC_ROLE bconRole;
	eLMAC_NX_SCH nextSCHState;
	vc_uint32 startBcnNTB;
	vc_uint32 startCsmaNTB;
	vc_uint32 centBcnCnt;
	vc_uint32 nonCentBcnCnt;
	vc_uint32 proxyBcnCnt;
	vc_uint32 bcnSlotTime;
	vc_uint32 csmaSlotTime;
	vc_uint32 csmaSlotTotal;
	vc_uint32 csmaSlotCurrent;
	vc_uint32 csmaSlotLength;
	//OsMutex mutexCsmaTxKickOut_g;
} lmac_sch_struct;

typedef enum tLmac_state {
	LMAC_IDLE              = 0,
	LMAC_CAMPON            = 1,
	LMAC_CSMA_IDLE         = 2,
	LMAC_WAIT_CSMA_NON     = 3,
	LMAC_WAIT_CSMA_ACK     = 4,
	LMAC_CHECK_CSMA_ACK    = 5,
	LMAC_WAIT_BCN_TXP_DONE = 6,
	LMAC_WAIT_CSMA_ITNWC   = 7,
}tLmac_state;

typedef enum tLmac_LED_state {
	LMAC_LED_METER_NOT_GET_STATE,
	LMAC_LED_IDLE_STATE,
	LMAC_LED_REG_STATE,
	LMAC_LED_LEAVE_STATE,
	LMAC_LED_UPGRADE_STATE,
	LMAC_LED_DYING_GASP_STATE,
	LMAC_LED_TEST_STATE,
	LMAC_LED_SIG_STATE,
	LMAC_LED_SIG_OFF_STATE,
}tLmac_LED_state;

typedef enum tLmac_REG_state {
	LMAC_NOT_REG_STATE,
	LMAC_ON_REG_STATE,
	LMAC_LEAVE_REG_STATE
}tLmac_REG_state;

typedef enum {
	VC_LEAVE_REASON_NONE = 0x00,
	VC_LEAVE_REASON_NMS_RECEIVE_LEAVE_IND = 0x01,
	VC_LEAVE_REASON_NMS_SELF_LEAVE = 0x02,
	VC_LEAVE_REASON_BCN_TRIGGLE_LEAVE = 0x03,
	VC_LEAVE_REASON_UNKONW_LEAVE = 0x04,
}vc_adapt_leave_reason;

// typedef struct lmac_tmr_struct {
// 	vcTimer PingTmr;
// 	ilm_struct PingTmr_ilm;
// 	vcTimer hPingTmr;
// 	ilm_struct hPingTmr_ilm;
// }lmac_tmr_struct;

typedef enum eLmacPingType {
	VC_LMAC_PING_NORMAL,
	VC_LMAC_PING_ITNWC,
	VC_LMAC_PING_LONG,
	VC_LMAC_PING_ETMI,
	VC_LMAC_PING_PHY_TEST,
}eLmacPingType;

typedef struct lmac_ping_struct {
	eLmacPingType PingType;
	vc_uint8 PingPBCount;
	vc_uint8 PingExtTMI;
	vc_uint8 PingTMI;
	vc_uint16 DTEI;
	vc_uint32 currPingTimes;
	vc_uint32 wantPingTimes;
	vc_uint32 ackPingTimes;
	vc_uint32 startPingTimes;
	vc_uint32 endPingTimes;
	vc_uint32 beaconNTB[10];
}lmac_ping_struct;

typedef struct lmac_high_ping_struct {
	vc_uint8 Enable;
	vc_uint32 Times;
	vc_uint16 Count;
	vc_uint16 DTEI;
	vc_uint8 Tmi;
	vc_uint8 ETmi;
	vc_uint8 PbCount;
	vc_uint8 Interval;/*ms*/
}lmac_high_ping_struct;

typedef struct lmac_bcn_struct {
	vc_uint8 checkbcnSendComplete;
}lmac_bcn_struct;

typedef struct lmac_csma_struct {
	vc_uint8 fromQ;/*0:TxQ, 1:FxQ, 2:OxQ*/
	vc_uint8 minBE;
	vc_uint8 maxBE;
	vc_uint8 sackNeed;
	vc_uint8 sackGet;
	vc_uint16 sackDuration;
	vc_uint8 pktType;
	vc_uint8 maxRetryCnt;
	vc_uint8 csmaAbort;
	vc_uint8 csmaDefaultForce;
	vc_uint32 period;
	vc_uint32 firstCsmaTime;
	vc_uint32 kickSofFL;
}lmac_csma_struct;

typedef struct lmac_band_search_struct {
	vc_uint8 currentBand;
	vc_uint8 BeaconReceive;
	vc_uint8 bandSearchingRunning;
}lmac_band_search_struct;

typedef struct lmac_config_struct {
	vc_uint8 hv_flag;
	vc_uint8 init_flag;
}lmac_config_struct;

typedef struct lmac_irq_struct {
	vc_uint32 kickDma;
	vc_uint32 kickDmaWant;
	vc_uint32 kickBcn;
	vc_uint32 kickSof;
	vc_uint32 kickSack;
	vc_uint32 kickItnwc;
	vc_uint32 kickBbpRaw;
	vc_uint32 kickOther;
	vc_uint32 kickDmaDspBusy;
	vc_uint32 kickTxFinish;
	vc_uint32 kickWPhyRxDp;
	vc_uint32 kickDspWaitTimeout;
	vc_uint32 cntxp_done;
	vc_uint32 dsp_abortpkt;
	vc_uint32 cnrxp_done;
	vc_uint32 cnmac_ackto;
	vc_uint32 get_sack;
	vc_uint32 resp_sack;
	vc_uint32 abortack;
	vc_uint32 get_para;
	vc_uint32 csma_success;
	vc_uint32 csma_fail;
	vc_uint32 csma_abort;
	vc_uint32 tdma_timeup;
	vc_uint32 tdma_fail;
	vc_uint32 kickphy;
	vc_uint32 zc1;
	vc_uint32 zc2;
	vc_uint32 zc3;
	vc_uint32 dma_rx_complete;
	vc_uint32 rx_bcn;
	vc_uint32 rx_sof;
	vc_uint32 rx_itnwc;
	vc_uint32 rx_bbpRaw;
	vc_uint32 rx_pbcsErr;
	vc_uint32 tx_over4pb;
	vc_uint32 bcnTooLateCnt;
	vc_uint32 sof_sack_expired;
	vc_uint32 sof_sack_recv;
}lmac_irq_struct;

typedef struct lmac_dmacnt_struct {
	vc_uint32 txCmp;
	vc_uint32 txUnavail;
	vc_uint32 txError;
	vc_uint32 txUpdate;
	vc_uint32 txDone;
	vc_uint32 rxCmp;
	vc_uint32 rxProcessCmp;
	vc_uint32 rxUnavail;
	vc_uint32 rxError;
	vc_uint32 rxUpdate;
}lmac_dmacnt_struct;

typedef struct lmac_dsp_cnt {
	vc_uint32 dspTBcn;
	vc_uint32 dspTAbortBcn;
	vc_uint32 dspTData;
	vc_uint32 dspTAbort;
	vc_uint32 dspTSack;
	vc_uint32 dspTAbortSack;
	vc_uint32 dspTSot;
	vc_uint32 dspTItnwc;
	vc_uint32 dspTWaitTimeout;
	/***********************/
	vc_uint32 dspRPmb;
	vc_uint32 dspRFalseAlarm;
	vc_uint32 dspRFch;
	vc_uint32 dspRFchErr;
	vc_uint32 dspRBcn;
	vc_uint32 dspRBcnErr;
	vc_uint32 dspRSof;
	vc_uint32 dspRSofErr;
	vc_uint32 dspRSack;
	vc_uint32 dspRSackErr;
	vc_uint32 dspRItnwc;
	vc_uint32 dspRItnwcErr;
}lmac_dsp_cnt;

typedef struct lmac_rt_cnt {
	vc_uint32 rtSearchFail;
	vc_uint32 rtTxqInsertExpire;
	vc_uint32 rtTxqDropExpire;
	vc_uint32 rtTxqDropOverBcastRetry;
	vc_uint32 rtTxqDropOverUcastRetry;
}lmac_rt_cnt;

typedef struct lmac_mac_csma_usage {
	vc_uint8 isStartCsmaUsageMeasment;
	vc_uint32 macRxTotalCnt;
	vc_uint32 macRxTotalFL;
	vc_uint32 macTxTotalCnt;
	vc_uint32 macTxTotalFL;
}lmac_mac_csma_usage;

typedef struct lmac_Zx_Info {
	vc_uint8 state;
	vc_uint32 startNTB;
	vc_uint16 caputreTimes;
	vc_uint16 captureReminds;
	vc_uint16 captureCurrent;
	vc_uint32 result[LMAC_ZERO_CROSSING_RETRIEVE_RECORD_MAX + 1];
}lmac_Zx_Info;

typedef enum lmacZxCollectionCcoState {
	LMAC_ZX_COLLECTION_NONE,
	LMAC_ZX_COLLECTION_GOING,
	LMAC_ZX_COLLECTION_STOP
}lmacZxCollectionCcoState;

typedef struct lmac_zx_collection_cco {
	lmacZxCollectionCcoState state;
	vc_uint32 startNTB;
	vc_uint32 zcA_Cnt;
	vc_uint32 zcA_Capture_Cnt;
	vc_uint32 zcA[LMAC_ZERO_CROSSING_RETRIEVE_RECORD_MAX + 1];
	vc_uint8 zcA_State;
	vc_uint32 zcB_Cnt;
	vc_uint32 zcB_Capture_Cnt;
	vc_uint32 zcB[LMAC_ZERO_CROSSING_RETRIEVE_RECORD_MAX + 1];
	vc_uint8 zcB_State;
	vc_uint32 zcC_Cnt;
	vc_uint32 zcC_Capture_Cnt;
	vc_uint32 zcC[LMAC_ZERO_CROSSING_RETRIEVE_RECORD_MAX + 1];
	vc_uint8 zcC_State;
}lmac_zx_collection_cco;

typedef struct tBbpRawCmdAsynPrint {
	vc_uint8 isUsed;
	vc_uint16 pktLens;
	vc_uint8 *logData;
}tBbpRawCmdAsynPrint;

typedef struct lmac_bbp_aysn_print {
	vc_uint16 lmacBbpRawAysnReadCnt;
	vc_uint16 lmacBbpRawAysnWriteCnt;
	tBbpRawCmdAsynPrint lmacBbpRawAysnInfo[BBP_RAW_ASYN_PRINT_MAX];
}lmac_bbp_aysn_print;

typedef struct lmac_context_struct {
	vc_uint32 LMAC_NID;
	vc_uint32 LMAC_NNID;
	vc_uint16 LMAC_PTEI;
	vc_uint16 LMAC_DTEI;
	vc_uint16 LMAC_STEI;
	vc_uint16 LMAC_CTEI;
	vc_lmac_band_plan lmacBand;
	vc_uint8 lmacToneMask;
	vc_uint8 bcnTriggleThresholdMs; //BEACON_TRIG_THRESHOLD_MS
	vc_uint8 lmacTxDoneCnt;         // counting tx done in this csma period
	lmac_sch_struct lmacSch;
	tLmac_state lmacState;
	tLmac_LED_state lmacLEDState;
	tLmac_REG_state lmacREGState;
	vc_adapt_leave_reason lmacLeaveReason;
	//lmac_tmr_struct lmacTmr;
	lmac_ping_struct lmacPing;
	lmac_high_ping_struct lmacHighPing;
	lmac_bcn_struct lmacBcn;
	lmac_csma_struct lmacCsma;
	lmac_band_search_struct lmacBandSearch;
	lmac_config_struct lmacConfig;
	lmac_irq_struct lmacIrqCount;
	lmac_dmacnt_struct lmacDmaCount;
	lmac_dsp_cnt lmacDspCount;
	lmac_rt_cnt lmacRtCount;
	lmac_mac_csma_usage lmacMacCsmaUsage;
	lmac_Zx_Info lmacZxInfo;
	lmac_zx_collection_cco lmacZxCollectionCco;
	lmac_bbp_aysn_print lmacBbpAysnPrint;
	vc_uint32 startWaitAckNTB;
}lmac_context_struct;

typedef enum eLMAC_TX_DONE_IRQ_TYPE {
	LMAC_TX_KICK_BCN = 0x00,
	LMAC_TX_KICK_SOF = 0x01,
	LMAC_TX_KICK_SACK = 0x02,
	LMAC_TX_KICK_ITNWC = 0x03,
	LMAC_TX_DONE_FINISH = 0x04,
	LMAC_TX_GPIO_TIMEOUT = 0x05,
	LMAC_TX_FINISH_MOVE_BCN = 0x06,
	LMAC_TX_FINISH_MOVE_NUNBCN = 0x07,
	LMAC_TX_WAIT_KPHY_RXDROP = 0x30,
	LMAC_TX_PBNUM_OV4PB_DROP_PKT = 0x31,
	LMAC_TX_DSP_WAIT_KICK_TIMEOUT = 0x33,
	LMAC_DSP_TRIGGLE_HV_DROP_LD_ON = 0x50,
	LMAC_DSP_TRIGGLE_HV_DROP_LD_OFF = 0x51,
	LMAC_DSP_TRIGGLE_DYING_GASP_LD_ON = 0x52,
	LMAC_DSP_TRIGGLE_DYING_GASP_LD_OFF = 0x53,
	LMAC_DSP_TRIGGLE_OT_DROP_LD_ON = 0x54,
	LMAC_DSP_TRIGGLE_OT_DROP_LD_OFF = 0x55,
	LMAC_DSP_TRIGGLE_RETURN_82V_LD_ON = 0x56,
	LMAC_DSP_TRIGGLE_RETURN_82V_LD_OFF = 0x57,
	LMAC_DSP_TRIGGLE_AM_DRM_SIGNAL = 0xA5,/*EN50561 only*/
}eLMAC_TX_DONE_IRQ_TYPE;

typedef enum phy_nv_cfg_e {
	NV_RAM_IDX,
	NV_BAND_IDX,
	NV_FNPLL_INIT_N_IDX,
	NV_FNPLL_INIT_K_IDX,
	NV_FNPLL_FORCE_FLAG_IDX,
	NV_FNPLL_FORCE_N_IDX,
	NV_FNPLL_FORCE_K_IDX,
	NV_NTB_OFFSET_IDX,
	NV_CFG_PHY_TX_SWING_IDX,
	NV_PHY_CFG_TOTAL_NUM
}phy_nv_cfg_e;

typedef struct phy_nv_cfg_t {
	vc_uint32 nvramIdx;
	vc_uint32 band;
	vc_uint32 fnpllInitN;
	vc_uint32 fnpllInitK;
	vc_uint32 fnpllForceFlag;
	vc_uint32 fnpllForceN;
	vc_uint32 fnpllForceK;
	vc_uint32 ntbOffset;
	vc_uint32 cfgTxSwing;
}phy_nv_cfg_t;

typedef struct phy_nv_cfg_cmd_t {
	const char cmd[30];
	vc_uint32 *value;
}phy_nv_cfg_cmd_t;

#define LMAC_PTR lmac_ptr_g
typedef struct lmac_context_struct *LMAC_CONTEXT_PTR;
extern volatile LMAC_CONTEXT_PTR lmac_ptr_g;

extern void vc_lmac_change_state(tLmac_state state);

#endif
