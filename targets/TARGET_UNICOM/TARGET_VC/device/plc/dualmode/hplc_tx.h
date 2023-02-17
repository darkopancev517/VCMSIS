#ifndef HPLC_TX_H
#define HPLC_TX_H

#include <stdint.h>

#include "hplc_bbp.h"

#ifdef __cplusplus
extern "C" {
#endif

//#define LMAC_RIFS 2300 /*us*/

#define LMAC_RIFS	400		/*us*/
#define LMAC_CIFS	400		/*us*/

#define WISUN_NID	(uint32_t)0x112233
#define WISUN_TEI	0xFEF

#define LMAC_SIZE_OF_PBCS_IN_PB					3	//MMM
#define LMAC_RESERVED_BYTES_FOR_LEN_IN_PB		4	//MMM

/*CSMA PARAMETER*/
#define LMAC_BROADCAST_MAX_RETRY_TIMES 	1
#define LMAC_RETRANSMIT_MAX_RETRY_TIMES 	6
#define LMAC_CSMA_MAX_BE 			5
#define LMAC_CSMA_MIN_BE 			3
#define LMAC_CSMA_MAX_BACKOFFS		(LMAC_CSMA_MAX_BE - LMAC_CSMA_MIN_BE + 1)
#define LMAC_CSMA_BACKOFF_PERIOD 	400 /*us*/
//#define LMAC_CSMA_DEFAULT_PERIOD 	1
#define LMAC_CSMA_DEFAULT_PERIOD 	100

#define LMAC_PB_SIZE_72		72
#define LMAC_PB_SIZE_136	136
#define LMAC_PB_SIZE_264	264
#define LMAC_PB_SIZE_520	520

#define ACK_FL  (((gMapSymTMI_ALL.fcTime * 2) + (gMapSymTMI_ALL.pldTime * 1 * vc_lmac_cal_ofdma_symbol_number(0, 14, 131, 0)))/100 + LMAC_RIFS) / 10
#define ACK_DUR (gMapSymTMI_ALL.pmbTime * 13 + gMapSymTMI_ALL.fcTime * 12) / 1000 + ACK_FL

typedef enum efc_delimiter {
	BEACON_F = 0,
	SOF_F=1,
	SACK_F = 2,
	INTER_NET_COR_F =3,
	RTS_CTS_F=4,
	RSV =5,
	PHY_TEST=6,
} efc_delimiter;

typedef enum vc_lmac_extTMI{
	BPLC_TMI,
	BPLC_E_TMI
} vc_lmac_extTMI;

/* HPLC return values for transmissions. */
enum {
  HPLC_TX_OK,
  HPLC_TX_ERR,
  HPLC_TX_BUSY,
  HPLC_TX_COLLISION,
};

typedef struct tCN_SOF_VAR{
	uint32_t 	STEI: 12;
	uint32_t 	DTEI: 12;
	uint32_t 	LID: 8;

	uint32_t	FL:12;
	uint32_t 	PBCount: 4;
	uint32_t	symbolNum: 9;
	uint32_t	bcastFlag:1;
	uint32_t	resendFlag:1;
	uint32_t	encryptFlag:1;
	uint32_t	TMI:4;

	uint8_t	extTMI:4;
	uint8_t version: 4;
} __attribute__((packed)) tCN_SOF_VAR;

typedef struct tCN_SOF_FC{
	/*0~3*/
	uint32_t	delType: 3;
	uint32_t 	netType: 5;
	uint32_t 	NID: 24;
	/*4~7*/
	uint32_t	SofVarSTEI: 12;
	uint32_t	SofVarDTEI: 12;
	uint32_t 	SofVarLID: 8;	
	uint32_t	SofVarFL:12;
	/*8~11*/
	uint32_t 	SofVarPBCount: 4;
	uint32_t	SofVarSymbolNum: 9;
	uint32_t	SofVarBcastFlag:1;
	uint32_t	SofVarResendFlag:1;
	uint32_t	SofVarEncryptFlag:1;
	uint32_t	SofVarTMI:4;
	/*12*/
	uint8_t	SofVarExtTMI:4;
	uint8_t version: 4;
	/*13~15*/
	uint8_t fccs[3];
} __attribute__((packed)) tCN_SOF_FC;

typedef struct vc_lmac_pkt_symbol_by_cal {
	uint16_t PbSize;
	uint16_t BPC;
	uint16_t copyNum;
	uint16_t intNum;
} vc_lmac_pkt_symbol_by_cal;

typedef struct vc_lmac_pkt_sym_mapping {
	uint8_t band;
	uint8_t TypeTMI;
	uint32_t pmbTime;
	uint32_t fcTime;/*59.28us*/
	uint32_t pldTime;/*51.52us*/
	vc_lmac_pkt_symbol_by_cal InfoTMI[15];
} vc_lmac_pkt_sym_mapping;

typedef enum eVC_SACK_TYPE{
	VC_SACK_NOT,
	VC_SACK_NEED,
} eVC_SACK_TYPE;

typedef enum eVC_CSMA_PKT_TYPE{
	BCON_PKT = 0,
	SOF_PKT=1,
	SACK_PKT = 2,
	ITNWC_PKT =3,
	RCTS_PKT =4,
} eVC_CSMA_PKT_TYPE;

typedef enum eVC_CSMA_FROMQ_TYPE{
	CSMA_F_NXQ,
	CSMA_F_TXQ,
	CSMA_F_FXQ,
	CSMA_F_OXQ
} eVC_CSMA_FROMQ_TYPE;

extern volatile uint8_t plc_m_csma_success;
extern volatile uint8_t plc_m_csma_fail;
extern volatile uint8_t plc_m_csma_abort;
extern volatile uint8_t plc_m_csma_abort;
extern volatile uint8_t plc_m_dsp_abortpkt;
extern volatile uint8_t plc_m_csma_get_para;
extern volatile uint8_t plc_m_txp_done;
extern volatile uint8_t plc_m_tx_info_start;
extern volatile uint8_t plc_m_tx_info_finish;

extern uint32_t vc_lmac_check_vcs_idle();
extern int vc_lmac_det_tmi_pbNum_pbSize(const uint16_t len, uint8_t *vcTmi, uint8_t *targetPbNum, uint16_t *targetPbSize);
extern int vc_lmac_tx_sof_pkt_f_cmd_txdata_asap(uint16_t DTEI, uint8_t extTmi, uint8_t tmi, uint8_t *pTxData, uint16_t dataLen, uint8_t vcPbNum, uint16_t vcPbSize, uint32_t startNTB, uint8_t ack_needed, int* rfstat);
extern int8_t vc_lmac_tx_sof_pkt_f_cmd_txack_asap(uint8_t *pTxData, uint16_t dataLen, uint32_t startNTB);
extern int vc_lmac_tx_sof_pkt_f_cmd_txdata(uint16_t DTEI, uint8_t extTmi, uint8_t tmi, uint8_t *pTxData,uint16_t pDataLen);
extern void vc_lmac_tx_sof_pkt_f_cmd_ping(uint16_t DTEI, uint8_t extTmi, uint8_t tmi, uint8_t pbCount,uint8_t startFlag);
extern void vc_lmac_tx_sof_pkt_f_phy_ping(uint16_t DTEI, uint8_t extTmi, uint8_t tmi, uint8_t pbCount);

#ifdef __cplusplus
}
#endif

#endif // HPLC_TX_H
