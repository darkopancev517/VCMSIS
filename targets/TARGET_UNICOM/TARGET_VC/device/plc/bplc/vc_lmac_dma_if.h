#ifndef _VC_MAC_HWMAC_IF_H_
#define _VC_MAC_HWMAC_IF_H_

#include "vc_lmac_dma.h"

#define SGCC_CERTIFICATE 1
#define BEACON_BY_RAW_CMD_SEND 1
#define VC_MAC_DMA_BASE           0x40010000
#define VC_MAC_CN_BASE            0x40011000
#define VC_MAC_CN_DEBUG           0x40011100
#define VC_MAC_G3_BASE            0x40011200
#define VC_MAC_G3_CSMA_TR1        0x40011280

#define VC_DMAC_RX_NR_DESC 25
#define VC_DMAC_RX_BUF_SIZE 800
#define VC_DMAC_TX_NR_DESC 16

typedef enum eVC_LMAC_DMA_ISR {
	dmaISR_Txcmp    = 0x00000001,
	dmaISR_Txunavail    = 0x00000002,
	dmaISR_Txerror  = 0x00000004,
	dmaISR_Txupdate = 0x00000008,
	dmaISR_TxpDone = 0x00000010,
	dmaISR_Rxcmp    = 0x00000100,
	dmaISR_Rxunavail    = 0x00000200,
	dmaISR_Rxerror  = 0x00000400,
	dmaISR_Rxupdate = 0x00000800,
}eVC_LMAC_DMA_ISR;
typedef enum eVC_CNMAC_ISR {/*1 0000 0000 0000*/
	cnmacISR_cntxp_done         = 0x00000001,
	cnmacISR_dsp_abortpkt       = 0x00000002,
	cnmacISR_cnrxp_done         = 0x00000010,
	cnmacISR_cnmac_ackto        = 0x00000100,
	cnmacISR_cnmac_get_sack     = 0x00000200,
	cnmacISR_cnmac_resp_sack    = 0x00001000,
	cnmacISR_cnmac_abortack     = 0x00002000,
	cnmacISR_cnsch_get_para     = 0x00010000,
	cnmacISR_cnsch_csma_success = 0x00020000,
	cnmacISR_cnsch_csma_fail    = 0x00040000,
	cnmacISR_cnsch_csma_abort   = 0x00080000,
	cnmacISR_cnsch_tdma_timeup  = 0x00100000,
	cnmacISR_cnsch_tdma_fail    = 0x00200000,
	cnmacISR_cnsch_kickphy      = 0x00400000,
	cnmmacISR_ntb_tmr0          = 0x01000000,
	cnmmacISR_ntb_tmr1          = 0x02000000,
	cnmmacISR_dsp_info          = 0x04000000,
	cnmmacISR_dsp_sack          = 0x08000000,
	cnmacISR_zc1                = 0x10000000,
	cnmacISR_zc2                = 0x20000000,
	cnmacISR_zc3                = 0x40000000,
}eVC_CNMAC_ISR;
typedef enum eVC_DMAC_OWNER {
	VC_DMAC_OWNER_SW      = 0,         // the desc entry is free to be used by the software
	VC_DMAC_OWNER_DMAC    = 1,         // the desc entry is currently in use by the DMA engine
}eVC_DMAC_OWNER;
typedef struct tVCMAC_REGISTER {       // BASE=0x4001_1000
	vc_uint32 MAC_CR;                  //0x00
	vc_uint32 rsv04;
	vc_uint32 rsv08;
	vc_uint32 rsv0C;
	vc_uint32 CNMAC_CR;                // 0x10 BBPLC MAC Control Register1
	vc_uint32 CNRXP_CR;                // 0x14 BBPLC MAC Control Register2 (TXP and RXP)
	vc_uint32 rsv18;
	vc_uint32 rsv1C;
	vc_uint32 CNMAC_IER;               //0x20 BBPLC MAC Interrupt Enable Register
	vc_uint32 CNMAC_ISR;               //0x24 BBPLC MAC Interrupt Status Register
	vc_uint32 rsv28;                   //0X28
	vc_uint32 rsv2C;                   //0x2C
	vc_uint32 CNRXF_SET1_SR1;          // 0X30 BBPLC RX Address Filter Group1 Setting Register1
	vc_uint32 CNRXF_SET1_SR2;          //0X34 BBPLC RX Address Filter Group1 Setting Register2
	vc_uint32 CNRXF_SET2_SR1;          //0X38 BBPLC RX Address Filter Group2 Setting Register1
	vc_uint32 CNRXF_SET2_SR2;          //0x3c BBPLC RX Address Filter Group2 Setting Register2
	vc_uint32 CNRXF_SET2_MR1;          //0x40 BBPLC RX Address Filter Group2 Mask Register1
	vc_uint32 CNRXF_SET2_MR2;          // 0x44 BBPLC RX Address Filter Group2 Mask Register2
	vc_uint32 CNRXF_STEI_SR;           // 0x48 BBPLC RX Address Filter Source TEI Setting Register
	vc_uint32 CNRXF_DT_SR;             //0x4C BBPLC RX Address Filter Source DT Setting Register
	vc_uint32 CNVCS_SR1;               //0x050    BBPLC VCS Setting Register1 (Time Tick)
	vc_uint32 CNVCS_SR2;               //0x054    BBPLC VCS Setting Register2 (EIFS)
	vc_uint32 CNVCS_SR3;               //0x058    BBPLC VCS Setting Register3 (CIFS)
	vc_uint32 CNVCS_SR4;               //0x05C    BBPLC VCS Setting Register4 (RIFS)
	vc_uint32 CNVCS_SR5;               //0x060   BBPLC VCS Setting Register5 (ACK Duration)
	vc_uint32 CNVCS_SR6;               //0x064    BBPLC VCS Setting Register6 (ACK Tolerance)
	vc_uint32 CNVCS_SR7;               //0x068    BBPLC VCS Setting Register7 (Waiting ACK)
	vc_uint32 rsv6C;
	vc_uint32 CNSCH_CR1;               //0x070    BBPLC Scheduler Control Register1
	vc_uint32 CNSCH_TSR1;              //0x074    TX Duration, CSMA enable,TDMA enable, TX requires ACK
	vc_uint32 CNSCH_TSR2;              //0x078    CSMA Back Off time tick
	vc_uint32 CNSCH_TSR3;              //0x07C    TDMA TX Time (by NTB)
	vc_uint32 CNSCH_TSR4;              //0x080   BBPLC Scheduler TX Setting Register4
	vc_uint32 CNSCH_TSR5;              //0x084    BBPLC Scheduler TX Setting Register5
	vc_uint32 CNSCH_RTY_CR;            //0x088    BBPLC Scheduler Retry Control Register [3]csr_dsp_abortpkt
	vc_uint32 CNSCH_IR;                //0x08C    BBPLC Scheduler Information Register
	vc_uint32 CNRXARQ_SR;              //0x090    BBPLC RX ARQ Setting Register
	vc_uint32 rsv94;
	vc_uint32 rsv98;
	vc_uint32 rsv9C;
	vc_uint32 CNTXARQ_IR;              //0x0A0    BBPLC TX ARQ Information Register
	vc_uint32 rsvA4;
	vc_uint32 rsvA8;
	vc_uint32 rsvAC;
	vc_uint32 CNRXP_SR1;               //0x0B0    BBPLC RX Processor Setting Register1
	vc_uint32 CNRXP_SR2;               //0x0B4    BBPLC RX Processor Setting Register2
} tVCMAC_REGISTER;
typedef struct tVCMAC_DEBUG_REGISTER { // BASE=0x4001_1100
	vc_uint32 CNTXP_DR1;               //0x00 BBPLC MAC TX Processor Debug Register1
	vc_uint32 CNTXP_DR2;               // 0x04 BBPLC MAC TX Processor Debug Register2
	vc_uint32 CNTXP_DR3;               // 0x08 BBPLC MAC TX Processor Debug Register3
	vc_uint32 CNTXP_MIB1;              // 0x0C BBPLC MAC TX Processor Debug Counter1
	vc_uint32 rsv10;
	vc_uint32 rsv14;
	vc_uint32 rsv18;
	vc_uint32 rsv1C;
	vc_uint32 CNRXP_DR1;  // 0x20 BBPLC MAC RX Processor Debug Register1
	vc_uint32 CNRXP_DR2;  // 0x24 BBPLC MAC RX Processor Debug Register2
	vc_uint32 CNRXP_DR3;  // 0x28 BBPLC MAC RX Processor Debug Register3
	vc_uint32 CNRXP_MIB1; // 0x2C BBPLC MAC RX Processor Debug Counter1
	vc_uint32 rsv30;
	vc_uint32 rsv34;
	vc_uint32 rsv38;
	vc_uint32 rsv3C;
	vc_uint32 CNRXF_DR1;   // 0x40 BBPLC MAC RX Address Filter Debug Register1
	vc_uint32 CNRXF_DR2;   // 0x44 BBPLC MAC RX Address Filter Debug Register2
	vc_uint32 CNRXF_MIB1;  // 0x48 BBPLC MAC RX Address Filter Debug Counter1
	vc_uint32 CNRXF_MIB2;  // 0x4C BBPLC MAC RX Address Filter Debug Counter2
	vc_uint32 rsv50;
	vc_uint32 CNTXARQ_MIB; // 0x54 1  BBPLC MAC TX ARQ Debug Counter1
	vc_uint32 rsv58;
	vc_uint32 rsv5C;
	vc_uint32 CNRXARQ_DR;  // 0x60 BBPLC MAC RX ARQ Debug Register
	vc_uint32 CNRXARQ_MIB; // 0x64 1  BBPLC MAC RX ARQ Debug Counter1
	vc_uint32 rsv68;
	vc_uint32 rsv6C;
	vc_uint32 CNVCS_DR1;   // 0x70 BBPLC MAC VCS Debug Register1
	vc_uint32 CNVCS_DR2;   // 0x74 BBPLC MAC VCS Debug Register2
	vc_uint32 CNVCS_MIB1;  // 0x78 BBPLC MAC VCS Debug Counter1
	vc_uint32 rsv7C;
	vc_uint32 CNSCH_DR1;   // 0x80 BBPLC MAC Scheduler Debug Register1
	vc_uint32 rsv84;
	vc_uint32 CNSCH_MIB1;  // 0x88 BBPLC MAC Scheduler Debug Counter1
	vc_uint32 CNSCH_MIB2;  // 0x8C BBPLC MAC Scheduler Debug Counter2
} tVCMAC_DEBUG_REGISTER;
#if 0
typedef struct tVC_CNMAC_REG {
	tVC_MAC_CR CR;
	tVC_CNMAC_CR CR1;  /*0x10*/
	tVC_CNMAC_CR2 CR2; /*0x14*/
	tVC_CNMAC_IER IER;
	tVC_CNMAC_ISR ISR;
	tVC_CNRXF_SET1_SR1 RXF_SET1_SR1;
	tVC_CNRXF_SET1_SR2 RXF_SET1_SR2;
	tVC_CNRXF_SET2_SR1 RXF_SET2_SR1;
	tVC_CNRXF_SET2_SR2 RXF_SET2_SR2;
	tVC_CNRXF_SET2_MR1 RXF_SET2_MR1;
	tVC_CNRXF_SET2_MR2 RXF_SET2_MR2;
	tVC_CNRXF_STEI_SR RXF_STEI_SR;
	tVC_CNRXF_DT_SR RXF_DT_SR;
	tVC_CNVCS_SR1 VCS_SR1;
	tVC_CNVCS_SR2 VCS_SR2;
	tVC_CNVCS_SR3 VCS_SR3;
	tVC_CNVCS_SR4 VCS_SR4;
	tVC_CNVCS_SR5 VCS_SR5;
	tVC_CNVCS_SR6 VCS_SR6;
	tVC_CNVCS_SR7 VCS_SR7;
	tVC_CNSCH_CR1 SCH_CR1;
	tVC_CNSCH_TSR1 SCH_TSR1;
	tVC_CNSCH_TSR2 SCH_TSR2;
	tVC_CNSCH_TSR3 SCH_TSR3;
	tVC_CNSCH_TSR4 SCH_TSR4;
	tVC_CNSCH_TSR5 SCH_TSR5;
	tVC_CNSCH_RTY_CR SCH_RTY_CR;
	tVC_CNSCH_IR SCH_IR;
	tVC_CNRXARQ_SR RXARQ_SR;
	tVC_CNTXARQ_IR TXARQ_IR;
	tVC_CNRXP_SR1 RXP_SR1;
	tVC_CNRXP_SR2 RXP_SR2;
}tVC_CNMAC_REG;
#endif
typedef struct tVC_G3MAC_REG {
	tVC_HWMAC_DMA_CR CR;                 // 0x00
	vc_uint32 rsv_04;                    // 0x04
	vc_uint32 rsv_08;                    // 0x08
	vc_uint32 rsv_0C;                    // 0x0C
	tVC_HWMAC_DMA_TM_CR TM_CR;           // 0x0C
	tVC_HWMAC_DMA_TXE_CR TXE_CR;         // 0x10
	tVC_HWMAC_DMA_TXE_SR TXE_SR;         // 0x14
	tVC_HWMAC_DMA_TXE_KR TXE_KR;         // 0x18
	tVC_HWMAC_DMA_TXE_BA_SR TXE_BA_SR;   // 0x1C
	tVC_HWMAC_DMA_TXE_NA_SR TXE_NA_SR;   // 0x20
	tVC_HWMAC_DMA_TXE_CA_IR TXE_CA_IR;   // 0x24
	tVC_HWMAC_DMA_TXE_REQ_IR TXE_REQ_IR; // 0x28
	vc_uint32 rsv_2C;                    // 0x2C
	tVC_HWMAC_DMA_RXE_CR RXE_CR;         // 0x30
	tVC_HWMAC_DMA_RXE_SR RXE_SR;         // 0x34
	tVC_HWMAC_DMA_RXE_KR RXE_KR;         // 0x38
	tVC_HWMAC_DMA_RXE_BA_SR RXE_BA_SR;   // 0x3C
	tVC_HWMAC_DMA_RXE_NA_SR RXE_NA_SR;   // 0x40
	tVC_HWMAC_DMA_RXE_CA_IR RXE_CA_IR;   // 0x44
	tVC_HWMAC_DMA_RXE_REQ_IR RXE_REQ_IR; // 0x48
	tVC_HWMAC_DMA_RXE_SA_IR RXE_SA_IR;   // 0X4C
	tVC_HWMAC_DMA_IER IER;               // 0x50
	tVC_HWMAC_DMA_ISR ISR;               // 0x54
	tVC_HWMAC_DMA_ISTR ISTR;             // 0x58
} tVC_G3MAC_REG;

typedef struct tVC_DMA_REG {             // BASE=0x4001_0000
	tVC_DMA_CR CR;                       // 0x00
	vc_uint32 rsv_04;                    // 0x04
	vc_uint32 rsv_08;                    // 0x08
	tVC_DMA_TM_CR TM_CR;                 // 0x0C
	tVC_DMA_TXE_CR TXE_CR;               // 0x10
	tVC_DMA_TXE_SR TXE_SR;               // 0x14
	tVC_DMA_TXE_KR TXE_KR;               // 0x18
	tVC_DMA_TXE_BA_SR TXE_BA_SR;         // 0x1C
	tVC_DMA_TXE_NA_SR TXE_NA_SR;         // 0x20
	tVC_DMA_TXE_CA_IR TXE_CA_IR;         // 0x24
	tVC_DMA_TXE_REQ_IR TXE_REQ_IR;       // 0x28
	vc_uint32 rsv_2C;                    // 0x2C
	tVC_DMA_RXE_CR RXE_CR;               // 0x30
	tVC_DMA_RXE_SR RXE_SR;               // 0x34
	tVC_DMA_RXE_KR RXE_KR;               // 0x38
	tVC_DMA_RXE_BA_SR RXE_BA_SR;         // 0x3C
	tVC_DMA_RXE_NA_SR RXE_NA_SR;         // 0x40
	tVC_DMA_RXE_CA_IR RXE_CA_IR;         // 0x44
	tVC_DMA_RXE_REQ_IR RXE_REQ_IR;       // 0x48
	tVC_DMA_RXE_SA_IR RXE_SA_IR;         // 0X4C
	tVC_DMA_IER IER;                     // 0x50
	tVC_DMA_ISR ISR;                     // 0x54
	tVC_DMA_ISTR ISTR;                   // 0x58
} tVC_DMA_REG;

typedef struct tVC_DMA_CTRL_DESC {
	union {
		struct {
			// rx-only fields
			vc_uint32 pkt_len    : 16;  // [15:0]   packet length
			vc_uint32 reserved_17 : 1;
			vc_uint32 ADD_MISS : 1;
			vc_uint32 FCS : 1;
			vc_uint32 reserved_20 : 8;
			// common fields between tx and rx
			vc_uint32 last : 1;     // [27] last descriptor of the packet
			vc_uint32 first : 1;    // [28] first descriptor of the packet
			vc_uint32 int_en : 1;   // [29] interrupt enable for this descriptor
			vc_uint32 eor : 1;      // [30] end of ring
			vc_uint32 owner : 1;    // [31] the one who is locking on this descriptor (enum VTDMAC_OWNER)
		} fields;
		vc_uint32 value;
	};
}__attribute__((packed)) tVC_DMA_CTRL_DESC;

typedef struct tVC_DMAC_DESC {
	tVC_DMA_CTRL_DESC ctrl;
	vc_uint32 ptr;
}__attribute__((packed)) tVC_DMAC_DESC;
typedef enum tVC_LMAC_TX_CTRL_HDR_MODE {
	TX_CTRL_HDR_CNBPLC_MODE = 0x01,
	TX_CTRL_HDR_1901_MODE = 0x02,
	TX_CTRL_HDR_BYPASS_MODE = 0x04,
}tVC_LMAC_TX_CTRL_HDR_MODE;
typedef enum tVC_LMAC_TX_CTRL_HDR_TYPE {
	TX_CTRL_HDR_CN_TX_TYPE=1,
	TX_CTRL_HDR_CN_RX_TYPE=2,
	TX_CTRL_HDR_G3_TX_TYPE=3,
	TX_CTRL_HDR_G3_RX_TYPE=4,
	TX_CTRL_HDR_BBP_TX_TYPE=5,
	TX_CTRL_HDR_BBP_RX_TYPE=6,
	TX_CTRL_HDR_CN_BEACON_TYPE=7,
	TX_CTRL_HDR_PHY_TEST_TYPE=8,
	TX_CTRL_HDR_PBCS_FAIL_TYPE=9,
	TX_CTRL_HDR_CN_ITNWC_TYPE=10,
}tVC_LMAC_TX_CTRL_HDR_TYPE;

typedef struct tVC_PLC_CTRL {
	union {
		struct {
			vc_uint32 mode        : 4;    //
			vc_uint32 type        : 4;    // 1=AES, 3=SM, 5=CRC
			vc_uint32 config      : 8;    // (rw) Receive DMA Enable
			vc_uint32 head_len    : 16;
		} fields;
		vc_uint32 value;
	};
}__attribute__((packed)) tVC_PLC_CTRL;
typedef struct tVC_LMAC_CTRL_MAC {
	tVC_PLC_CTRL ctrl;
	vc_uint32 seq         : 8;
	vc_uint32 reserved    : 8;
	vc_uint32 pkt_len     : 16;
	vc_uint32 dur;
}__attribute__((packed)) tVC_LMAC_CTRL_MAC;
typedef struct tVC_LMAC_TX_CTRL_HEADER {
	tVC_PLC_CTRL ctrl;

	vc_uint32 seq : 8;
	vc_uint32 txSwing : 8;
	vc_uint32 pktLen : 16;

	vc_uint32 DT : 3;
	vc_uint32 rsv1 : 1;
	vc_uint32 PBNum : 3;
	vc_uint32 rsv2 : 1;
	vc_uint32 TMI : 4;
	vc_uint32 TMIType : 1;
	vc_uint32 BandPlan : 1;
	vc_uint32 rsv3 : 2;
	vc_uint32 rsv4 : 16;

	vc_uint32 bcnNTB : 32;
}__attribute__((packed)) tVC_LMAC_TX_CTRL_HEADER;
typedef struct tVC_LMAC_RX_CTRL_HEADER {
	vc_uint32 type : 4;
	vc_uint32 mode : 4;
	vc_uint32 config : 8;
	vc_uint32 chdrLen : 16;

	vc_uint32 pbcsStatus : 8;
	vc_uint32 linkQuality : 8;
	vc_uint32 pktLen : 16;

	vc_uint32 bcnFnCurrent : 8;
	vc_uint32 rxDuration : 24;

	vc_uint32 recNTB;

	vc_uint32 RSSI : 8;
	vc_uint32 PPM : 8;
	vc_uint32 FNPLLK : 16;
}__attribute__((packed)) tVC_LMAC_RX_CTRL_HEADER;
typedef struct tVC_DMAC_payload {
	void *dma_ptr;
	vc_uint16 dma_size;
}__attribute__((packed)) tVC_DMAC_payload;
typedef struct tVC_DMAC_PACKET {
	tVC_DMAC_payload pld[VC_DMAC_TX_NR_DESC];
	vc_uint8 nr_desc;
}tVC_DMAC_PACKET;
typedef struct tVC_BBP_RXV_statistics {
	vc_uint32 DT;
	vc_uint32 BEACON_PHASE;
	vc_uint32 STEI;
	vc_uint32 DTEI;
	vc_uint32 NTB;
	vc_uint32 Band;
	vc_uint32 TMI;
	vc_uint32 ETMI;
	vc_uint32 N_PB;
	vc_uint32 N_SYM;
	vc_uint32 FL;
	vc_uint32 BDnum;
	vc_uint32 FCHerr;
	vc_uint32 PLDerr;
	vc_uint32 PD_scale;
	vc_uint32 PD_sgn_th_L;
	vc_uint32 PD_ma_enb;
	vc_uint32 PD_auto_scale_enb;
	vc_uint32 PD_as_target;
	vc_uint32 PD_auto_scale;
	vc_uint32 IMPNS_enb;
	vc_uint32 IMPNS_scale;
	vc_uint32 NBIE_enb;
	vc_uint32 HPF_enb;
	vc_uint32 Notch_enb;
	vc_uint32 CAGC_g1;
	vc_uint32 CAGC_g2;
	vc_uint32 CAGC_WBrssi;
	vc_uint32 CAGC_IBrssi;
	vc_uint32 FAGC_g1;
	vc_uint32 FAGC_g2;
	vc_uint32 FAGC_WBrssi;
	vc_uint32 FAGC_IBrssi;
	vc_uint32 DGC;
	vc_uint32 SNR_dB;
	vc_uint32 eta;
	vc_uint32 Impn_valid;
	vc_uint32 Impn_peak_num;
	vc_uint32 Impn_ratio;
	vc_uint32 NBI_valid;
	vc_uint32 NBIE_idx1;
	vc_uint32 NBIE_idx2;
}tVC_BBP_RXV_statistics;
typedef struct tVC_BBP_RX_statistics {
	vc_uint32 rxMibCnt;
	vc_uint32 preamb_det_cnt;
	vc_uint32 rx_fch_cnt;
	vc_uint32 rx_fch_err_cnt;
	vc_uint32 rx_bcn_cnt;
	vc_uint32 rx_bcn_err_cnt;
	vc_uint32 rx_sof_cnt;
	vc_uint32 rx_sof_errcnt;
	vc_uint32 rx_sack_cnt;
	vc_uint32 rx_sack_errcnt;
	vc_uint32 rx_itnwc_cnt;
	vc_uint32 rx_itnwc_errcnt;
	vc_uint32 syncp_sym_cnt;
	vc_uint32 syncm_det_flag;
	vc_uint32 rx_false_alarm;
	vc_uint32 current_ntb;
}tVC_BBP_RX_statistics;
typedef struct tVC_BBP_TX_statistics {
	vc_uint32 rxMibCnt;
	vc_uint32 tx_data_cnt;
	vc_uint32 tx_sack_cnt;
	vc_uint32 tx_sof_cnt;
	vc_uint32 tx_itnwc_cnt;
	vc_uint32 tx_bcn_cnt;
	vc_uint32 tx_abort_data_cnt;
	vc_uint32 tx_abort_sack_cnt;
	vc_uint32 tx_abort_bcn_cnt;
	vc_uint32 tx_bcn_ntb;
	vc_uint32 current_ntb;
	vc_uint32 dsp_wait_kick_timeout_cnt;
}tVC_BBP_TX_statistics;
typedef struct tVC_BBP_BCN_TOO_LATE {
	vc_uint32 rsv1;
	vc_uint32 ntb1;
	vc_uint32 ntb2;
	vc_uint32 rsv2;
}tVC_BBP_BCN_TOO_LATE;

typedef struct tVC_BBP_freq_offset {
	vc_uint32 sign;
	vc_uint32 offset;
}tVC_BBP_freq_offset;

typedef struct tVC_BBP_ERROR_statistics {
	vc_uint32 hw_fagc_done_timeout_cnt;
	vc_uint32 hw_dgc_done_timeout_cnt;
	vc_uint32 hw_rx_fifo_empty_timeout_cnt;
	vc_uint32 hw_gir_timeout_cnt;
	vc_uint32 hw_gir_valid_sample_timeout_cnt;
	vc_uint32 hw_nbie_pd_hit_timeout_cnt;
	vc_uint32 hw_nbie_fagc_done_timeout_cnt;
	vc_uint32 hw_nbie_dgc_done_timeout_cnt;
	vc_uint32 hw_dtune_loop1_timeout_cnt;
	vc_uint32 hw_dtune_loop2_timeout_cnt;
	vc_uint32 hw_tx_end_timeout_cnt;
	vc_uint32 mac_ctrl_header_mode_error_cnt;
	vc_uint32 mac_ctrl_header_etmi_error_cnt;
	vc_uint32 mac_fifo_etmi_error_cnt;
}tVC_BBP_ERROR_statistics;

typedef struct tVC_phy_test_payload {
	vc_uint32 VCTAG;
	vc_uint32 NTB;
	vc_uint32 NTB2;
	vc_uint32 NTB3;
	vc_uint32 NTB4;
	vc_uint32 SEQNUM;
	vc_int8 txRSSI;
	vc_int8 txLQI;
	vc_uint8 testMode;
	vc_uint8 pktType;/*0:NormalTx, 1:Ack, 2: LedCtrl, 3:dyingGasp*/
	vc_uint8 macAddress[6];
	vc_uint8 passAddress[6];
	vc_uint8 ledBitMap;
	vc_uint8 ledCtrl;
}__attribute__((packed)) tVC_phy_test_payload;

extern volatile tVC_DMAC_DESC g_dmaTxDesc[VC_DMAC_TX_NR_DESC];
extern volatile tVC_DMAC_DESC g_dmaRxDesc[VC_DMAC_RX_NR_DESC];
extern vc_uint8 g_dmaRxBuf[VC_DMAC_RX_NR_DESC][VC_DMAC_RX_BUF_SIZE];

#endif
