#ifndef _VC_MAC_HWMAC_DMA_H_
#define _VC_MAC_HWMAC_DMA_H_

#include "vc_type.h"

/*************************************
* Address		: 0x00000000
* Default		: 0x00000000
* Name		: DMA_CR
* Description	: DMA Control Register
*************************************/
#define DMA_CR              0x00
typedef struct tVC_DMA_CR {
	union {
		struct {
			vc_uint32 csr_txeng_rstn : 1;
			vc_uint32 csr_rxeng_rstn : 1;
			vc_uint32 rsv2_7 : 6;
			vc_uint32 csr_txbuf_rstn : 1;
			vc_uint32 csr_rxbuf_rstn : 1;
			vc_uint32 rsv10_31 : 22;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_CR;
/*************************************
* Address		: 0x0000000C
* Default		: 0x00000000
* Name		: DMA_TM_CR
* Description	: DMA Test Mode Control Register
*************************************/
#define DMA_TM_CR           0x0C
typedef struct tVC_DMA_TM_CR {
	union {
		struct {
			vc_uint32 csr_dma_lb : 1;
			vc_uint32 csr_buf_lb : 1;
			vc_uint32 rsv2_7 : 6;
			vc_uint32 csr_rxstatus_drop : 1;
			vc_uint32 rsv9_31 : 23;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_TM_CR;
/*************************************
* Address		: 0x00000010
* Default		: 0x00000001
* Name		: TXE_CR
* Description	: TX Engine Control Register
*************************************/
#define DMA_TXE_CR              0x10
typedef struct tVC_DMA_TXE_CR {
	union {
		struct {
			vc_uint32 csr_txe_byteswap : 1;
			vc_uint32 csr_txe_chkfd : 1;
			vc_uint32 rsv2_31 : 30;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_TXE_CR;
/*************************************
* Address		: 0x00000014
* Default		: 0x00000000
* Name		: TXE_SR
* Description	: TX Engine Setting Register
*************************************/
#define DMA_TXE_SR              0x14
typedef struct tVC_DMA_TXE_SR {
	union {
		struct {
			vc_uint32 csr_txe_desc_gap : 8;
			vc_uint32 rsv8_31 : 24;
		}fields;
		vc_uint32 value;
	};
}tVC_DMA_TXE_SR;
/*************************************
* Address		: 0x00000018
* Default		: 0x00000000
* Name		: TXE_KR
* Description	: TX Engine Transmit Kick Register
*************************************/
#define DMA_TXE_KR              0x18
typedef struct tVC_DMA_TXE_KR {
	union {
		struct {
			vc_uint32 csr_txe_kick : 1;
			vc_uint32 rsv1_31 : 31;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_TXE_KR;
/*************************************
* Address		: 0x0000001C
* Default		: 0x00000000
* Name		: TXE_BA_SR
* Description	: TX Engine Transmit Descriptor Base Address Setting Register
*************************************/
#define DMA_TXE_BA_SR              0x1C
typedef struct tVC_DMA_TXE_BA_SR {
	union {
		struct {
			vc_uint32 csr_txbase_addr : 32;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_TXE_BA_SR;
/*************************************
* Address		: 0x00000020
* Default		: 0x00000000
* Name		: TXE_NA_SR
* Description	: TX Engine Next Transmit Descriptor Address Setting Register
*************************************/
#define DMA_TXE_NA_SR              0x20
typedef struct tVC_DMA_TXE_NA_SR {
	union {
		struct {
			vc_uint32 csr_txnext_addr : 32;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_TXE_NA_SR;
/*************************************
* Address		: 0x00000024
* Default		: 0x00000000
* Name		: TXE_CA_IR
* Description	: TX Engine Current Transmit Descriptor Address Information Register
*************************************/
#define DMA_TXE_CA_IR              0x24
typedef struct tVC_DMA_TXE_CA_IR {
	union {
		struct {
			vc_uint32 csr_txcurr_addr : 32;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_TXE_CA_IR;
/*************************************
* Address		: 0x00000028
* Default		: 0x00000000
* Name		: TXE_REQ_IR
* Description	: TX Engine Current Request Address Information Register
*************************************/
#define DMA_TXE_REQ_IR              0x28
typedef struct tVC_DMA_TXE_REQ_IR {
	union {
		struct {
			vc_uint32 csr_txreq_addr : 32;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_TXE_REQ_IR;
/*************************************
* Address		: 0x00000030
* Default		: 0x00000001
* Name		: RXE_CR
* Description	: RX Engine Control Register
*************************************/
#define DMA_RXE_CR              0x30
typedef struct tVC_DMA_RXE_CR {
	union {
		struct {
			vc_uint32 csr_rxe_byteswap : 1;
			vc_uint32 rsv1_31 : 31;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_RXE_CR;
/*************************************
* Address		: 0x00000034
* Default		: 0x00000000
* Name		: RXE_SR
* Description	: RX Engine Setting Register
*************************************/
#define DMA_RXE_SR              0x34
typedef struct tVC_DMA_RXE_SR {
	union {
		struct {
			vc_uint32 csr_rxe_desc_gap : 8;
			vc_uint32 rsv8_31 : 24;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_RXE_SR;
/*************************************
* Address		: 0x00000038
* Default		: 0x00000000
* Name		: RXE_KR
* Description	: RX Engine Transmit Kick Register
*************************************/
#define DMA_RXE_KR              0x38
typedef struct tVC_DMA_RXE_KR {
	union {
		struct {
			vc_uint32 csr_rxe_kick : 1;
			vc_uint32 rsv1_31 : 31;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_RXE_KR;
/*************************************
* Address		: 0x0000003C
* Default		: 0x00000000
* Name		: RXE_BA_SR
* Description	: RX Engine Transmit Descriptor Base Address Setting Register
*************************************/
#define DMA_RXE_BA_SR              0x3C
typedef struct tVC_DMA_RXE_BA_SR {
	union {
		struct {
			vc_uint32 csr_rxbase_addr : 32;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_RXE_BA_SR;
/*************************************
* Address		: 0x00000040
* Default		: 0x00000000
* Name		: RXE_NA_SR
* Description	: RX Engine Next Transmit Descriptor Address Setting Register
*************************************/
#define DMA_RXE_NA_SR              0x40
typedef struct tVC_DMA_RXE_NA_SR {
	union {
		struct {
			vc_uint32 csr_rxnext_addr : 32;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_RXE_NA_SR;
/*************************************
* Address		: 0x00000044
* Default		: 0x00000000
* Name		: RXE_CA_IR
* Description	: RX Engine Current Transmit Descriptor Address Information Register
*************************************/
#define DMA_RXE_CA_IR              0x44
typedef struct tVC_DMA_RXE_CA_IR {
	union {
		struct {
			vc_uint32 csr_rxcurr_addr  : 32;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_RXE_CA_IR;
/*************************************
* Address		: 0x00000048
* Default		: 0x00000000
* Name		: RXE_REQ_IR
* Description	: RX Engine Current Request Address Information Register
*************************************/
#define DMA_RXE_REQ_IR              0x48
typedef struct tVC_DMA_RXE_REQ_IR {
	union {
		struct {
			vc_uint32 csr_rxreq_addr  : 32;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_RXE_REQ_IR;
/*************************************
* Address		: 0x0000004C
* Default		: 0x00000000
* Name		: RXE_SA_IR
* Description	: RX Engine Start Address Information Register
*************************************/
#define DMA_RXE_SA_IR              0x4C
typedef struct tVC_DMA_RXE_SA_IR {
	union {
		struct {
			vc_uint32 csr_rxstart_addr  : 32;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_RXE_SA_IR;
/*************************************
* Address		: 0x00000050
* Default		: 0x00000000
* Name		: DMA_IER
* Description	: Interrupt Enable Register
*************************************/
#define DMA_IER              0x50
typedef struct tVC_DMA_IER {
	union {
		struct {
			vc_uint32 ier_txcmp : 1;
			vc_uint32 ier_txunavail : 1;
			vc_uint32 ier_txerror : 1;
			vc_uint32 ier_txupdate : 1;
			vc_uint32 rsv4_7 : 4;
			vc_uint32 ier_rxcmp : 1;
			vc_uint32 ier_rxunavail : 1;
			vc_uint32 ier_rxerror : 1;
			vc_uint32 ier_rxupdate : 1;
			vc_uint32 ier_rxreclaim : 1;
			vc_uint32 rsv13_15 : 3;
			vc_uint32 ier_msterr : 1;
			vc_uint32 rsv17_31 : 15;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_IER;
/*************************************
* Address		: 0x00000054
* Default		: 0x00000000
* Name		: DMA_ISR
* Description	: Interrupt Status Register
*************************************/
#define DMA_ISR              0x54
typedef struct tVC_DMA_ISR {
	union {
		struct {
			vc_uint32 isr_txcmp : 1;
			vc_uint32 isr_txunavail : 1;
			vc_uint32 isr_txerror : 1;
			vc_uint32 isr_txupdate : 1;
			vc_uint32 rsv4_7 : 4;
			vc_uint32 isr_rxcmp : 1;
			vc_uint32 isr_rxunavail : 1;
			vc_uint32 isr_rxerror : 1;
			vc_uint32 isr_rxupdate : 1;
			vc_uint32 isr_rxreclaim : 1;
			vc_uint32 rsv13_15 : 3;
			vc_uint32 isr_msterr : 1;
			vc_uint32 rsv17_31 : 15;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_ISR;
/*************************************
* Address		: 0x00000058
* Default		: 0x00000000
* Name		: DMA_ISTR
* Description	: Interrupt Status Test Register
*************************************/
#define DMA_ISTR              0x58
typedef struct tVC_DMA_ISTR {
	union {
		struct {
			vc_uint32 istr_txcmp : 1;
			vc_uint32 istr_txunavail : 1;
			vc_uint32 istr_txerror : 1;
			vc_uint32 istr_txupdate : 1;
			vc_uint32 rsv4_7 : 4;
			vc_uint32 istr_rxcmp : 1;
			vc_uint32 istr_rxunavail : 1;
			vc_uint32 istr_rxerror : 1;
			vc_uint32 istr_rxupdate : 1;
			vc_uint32 istr_rxreclaim : 1;
			vc_uint32 rsv13_15 : 3;
			vc_uint32 istr_msterr : 1;
			vc_uint32 rsv17_31 : 15;
		} fields;
		vc_uint32 value;
	};
}tVC_DMA_ISTR;

/******************************************************************/
/******************************************************************/

/*************************************
* Address		: 0x00000000
* Default		: 0x00040000
* Name		: MAC_CR
* Description	: MAC Control Register
*************************************/
#if 1
//#define MAC_CR        0x00
typedef struct tVC_MAC_CR {
	union {
		struct {
			vc_uint32 csr_sgmac_rstn  : 1;
			vc_uint32 csr_g3mac_rstn  : 1;
			vc_uint32 rsv2_3  : 2;
			vc_uint32 csr_bufif_g3  : 1;
			vc_uint32 csr_dspif_g3   : 1;
			vc_uint32 csr_plcmac_lb   : 1;
			vc_uint32 rsv7_15 : 9;
			vc_uint32 csr_access_dly : 4;
			vc_uint32 rsv20_31 : 12;
		}fields;
		vc_uint32 value;
	};
}tVC_MAC_CR;
/*************************************
* Address		: 0x00000010
* Default		: 0x00000000
* Name		: CNMAC_CR
* Description	: CN MAC Control Register
*************************************/
//#define CNMAC_CR        0x10
typedef struct tVC_CNMAC_CR {
	union {
		struct {
			vc_uint32 csr_cnmac_txen  : 1;   /*0*/
			vc_uint32 csr_cnmac_rxen  : 1;   /*1*/
			vc_uint32 csr_cnmac_rfen  : 1;   /*2-3*/
			vc_uint32 csr_cnmac_rxarqen : 1; /*4*/
			vc_uint32 csr_cnmac_vcsen  : 1;  /*5*/
			vc_uint32 csr_cnmac_schen  : 1;  /*6*/
			vc_uint32 csr_cnmac_vcstten : 1; /*7-15*/
			vc_uint32 rsv7_31 : 25;          /*11*/
		}fields;
		vc_uint32 value;
	};
}tVC_CNMAC_CR;
/*************************************
* Address		: 0x00000014
* Default		: 0x00030045
* Name		: CNMAC_CR2
* Description	: CN MAC Control Register2 for TXP and RXP
*************************************/
//#define CNMAC_CR2    0x14
typedef struct tVC_CNMAC_CR2 {
	union {
		struct {
			vc_uint32 csr_cnrxp_pdumatch_mac  : 1;
			vc_uint32 csr_cnrxp_pdumatch_dsp  : 1;
			vc_uint32 csr_cnrxp_ackreq_mac   : 1;
			vc_uint32 csr_cnrxp_ackreq_dsp  : 1;
			vc_uint32 csr_cnrxp_drop_mismatch   : 1;
			vc_uint32 csr_cnrxp_drop_crcerror   : 1;
			vc_uint32 csr_cnrxp_swapin  : 1;
			vc_uint32 rsv7_15 : 9;
			vc_uint32 csr_cntxp_chksch   : 1;
			vc_uint32 csr_cntxp_swapout   : 1;
			vc_uint32 rsv18_31 : 14;
		}fields;
		vc_uint32 value;
	};
}tVC_CNMAC_CR2;
/*************************************
* Address		: 0x00000020
* Default		: 0x00000000
* Name		: CNMAC_IER
* Description	: CN MAC IER
*************************************/
//#define CNMAC_IER    0x20
typedef struct tVC_CNMAC_IER {
	union {
		struct {
			vc_uint32 ier_cntxp_done   : 1;
			vc_uint32 ier_dsp_abortpkt   : 1;
			vc_uint32 rsv2_3 : 2;
			vc_uint32 ier_cnrxp_done    : 1;
			vc_uint32 rsv5_7 : 3;
			vc_uint32 ier_cnmac_ackto   : 1;
			vc_uint32 ier_cnmac_get_sack    : 1;
			vc_uint32 rsv10_11 : 2;
			vc_uint32 ier_cnmac_resp_sack    : 1;
			vc_uint32 ier_cnmac_abortack   : 1;
			vc_uint32 rsv14_15 : 1;
			vc_uint32 ier_cnsch_get_para    : 1;
			vc_uint32 ier_cnsch_csma_success   : 1;
			vc_uint32 ier_cnsch_csma_fail  : 1;
			vc_uint32 ier_cnsch_csma_abort  : 1;
			vc_uint32 ier_cnsch_tdma_timeup  : 1;
			vc_uint32 ier_cnsch_kickphy    : 1;
			vc_uint32 rsv23_27 : 5;
			vc_uint32 ier_zc1   : 1;
			vc_uint32 ier_zc2  : 1;
			vc_uint32 ier_zc3   : 1;
		}fields;
		vc_uint32 value;
	};
}tVC_CNMAC_IER;
/*************************************
* Address		: 0x00000024
* Default		: 0x00000000
* Name		: CNMAC_ISR
* Description	: CN MAC IER
*************************************/
//#define CNMAC_ISR    0x24
typedef struct tVC_CNMAC_ISR {
	union {
		struct {
			vc_uint32 isr_cntxp_done    : 1;
			vc_uint32 isr_dsp_abortpkt    : 1;
			vc_uint32 rsv2_3 : 2;
			vc_uint32 isr_cnrxp_done     : 1;
			vc_uint32 rsv5_7 : 3;
			vc_uint32 isr_cnmac_ackto    : 1;
			vc_uint32 isr_cnmac_get_sack     : 1;
			vc_uint32 rsv10_11 : 2;
			vc_uint32 isr_cnmac_resp_sack     : 1;
			vc_uint32 isr_cnmac_abortack    : 1;
			vc_uint32 rsv14_15 : 2;
			vc_uint32 isr_cnsch_get_para     : 1;
			vc_uint32 isr_cnsch_csma_success   : 1;
			vc_uint32 isr_cnsch_csma_fail   : 1;
			vc_uint32 isr_cnsch_csma_abort   : 1;
			vc_uint32 isr_cnsch_tdma_timeup  : 1;
			vc_uint32 isr_cnsch_tdma_fail     : 1;
			vc_uint32 isr_cnsch_kickphy  : 1;
			vc_uint32 rsv_23_27   : 5;
			vc_uint32 isr_zc1    : 1;
			vc_uint32 isr_zc2   : 1;
			vc_uint32 isr_zc3    : 1;
			vc_uint32 rsv_31    : 1;
		}fields;
		vc_uint32 value;
	};
}tVC_CNMAC_ISR;
/*************************************
* Address		: 0x00000030
* Default		: 0x00000000
* Name		: CNRXF_SET1_SR1
* Description	: CN RX Filter SET1 Setting Register1
*************************************/
//#define CNRXF_SET1_SR1    0x30
typedef struct tVC_CNRXF_SET1_SR1 {
	union {
		struct {
			vc_uint32 csr_cnrxf_nid1     : 24;
			vc_uint32 rsv24_31    : 8;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXF_SET1_SR1;
/*************************************
* Address		: 0x00000034
* Default		: 0x00000000
* Name		: CNRXF_SET1_SR2
* Description	: CN RX Filter SET1 Setting Register2
*************************************/
//#define CNRXF_SET1_SR2    0x34
typedef struct tVC_CNRXF_SET1_SR2 {
	union {
		struct {
			vc_uint32 csr_cnrxf_dtei1 : 12;
			vc_uint32 rsv12_31 : 20;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXF_SET1_SR2;
/*************************************
* Address		: 0x00000038
* Default		: 0x00000000
* Name		: CNRXF_SET2_SR1
* Description	: CN RX Filter SET2 Setting Register1
*************************************/
//#define CNRXF_SET2_SR1    0x38
typedef struct tVC_CNRXF_SET2_SR1 {
	union {
		struct {
			vc_uint32 csr_cnrxf_nid2 : 24;
			vc_uint32 rsv24_31 : 8;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXF_SET2_SR1;
/*************************************
* Address		: 0x0000003C
* Default		: 0x00000000
* Name		: CNRXF_SET2_SR2
* Description	: CN RX Filter SET2 Setting Register2
*************************************/
//#define CNRXF_SET2_SR2    0x3C
typedef struct tVC_CNRXF_SET2_SR2 {
	union {
		struct {
			vc_uint32 csr_cnrxf_dtei2  : 12;
			vc_uint32 rsv24_31 : 20;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXF_SET2_SR2;
/*************************************
* Address		: 0x00000040
* Default		: 0x00FFFFFF
* Name		: CNRXF_SET2_MR1
* Description	: CN RX Filter SET2 Setting Register1
*************************************/
//#define CNRXF_SET2_MR1    0x40
typedef struct tVC_CNRXF_SET2_MR1 {
	union {
		struct {
			vc_uint32 csr_cnrxf_nidmask  : 24;
			vc_uint32 rsv24_31 : 8;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXF_SET2_MR1;
/*************************************
* Address		: 0x00000044
* Default		: 0x00000FFF
* Name		: CNRXF_SET2_MR2
* Description	: CN RX Filter SET2 Setting Register2
*************************************/
//#define CNRXF_SET2_MR2    0x44
typedef struct tVC_CNRXF_SET2_MR2 {
	union {
		struct {
			vc_uint32 csr_cnrxf_dteimask  : 12;
			vc_uint32 rsv24_31 : 20;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXF_SET2_MR2;
/*************************************
* Address		: 0x00000048
* Default		: 0x00000000
* Name		: CNRXF_STEI_SR
* Description	: CN RX Filter Source TEI Setting Register
*************************************/
//#define CNRXF_STEI_SR    0x48
typedef struct tVC_CNRXF_STEI_SR {
	union {
		struct {
			vc_uint32 csr_cnrxf_sack_stei  : 12;
			vc_uint32 rsv12_31 : 20;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXF_STEI_SR;
/*************************************
* Address		: 0x0000004C
* Default		: 0x00000210
* Name		: CNRXF_DT_SR
* Description	: CN RX Filter Source DT Setting Register
*************************************/
//#define CNRXF_DT_SR    0x4C
typedef struct tVC_CNRXF_DT_SR {
	union {
		struct {
			vc_uint32 csr_cnrxf_dt_beacon  : 3;
			vc_uint32 rsv3 : 1;
			vc_uint32 csr_cnrxf_dt_sof   : 3;
			vc_uint32 rsv7 : 1;
			vc_uint32 csr_cnrxf_dt_sack    : 3;
			vc_uint32 rsv11_31 : 21;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXF_DT_SR;
/*************************************
* Address		: 0x00000050
* Default		: 0x00010025
* Name		: CNVCS_SR1
* Description	: CN VCS Setting Register1 (Time Tick)
*************************************/
//#define CNVCS_SR1    0x50
typedef struct tVC_CNVCS_SR1 {
	union {
		struct {
			vc_uint32 csr_cnvcs_tt   : 12;
			vc_uint32 rsv12_15 : 4;
			vc_uint32 csr_cnvcs_ttsync   : 1;
			vc_uint32 csr_cnvcs_rxinrx  : 1;
			vc_uint32 csr_cnvcs_rxintx     : 1;
			vc_uint32 rsv19_23 : 5;
			vc_uint32 csr_cnvcs_swsync : 1;
			vc_uint32 rsv25_31 : 7;
		}fields;
		vc_uint32 value;
	};
}tVC_CNVCS_SR1;
/*************************************
* Address		: 0x00000054
* Default		: 0x00004E20
* Name		: CNVCS_SR2
* Description	: CN VCS Setting Register2 (EIFS)
*************************************/
//#define CNVCS_SR2    0x54
typedef struct tVC_CNVCS_SR2 {
	union {
		struct {
			vc_uint32 csr_cnvcs_eifs    : 24;
			vc_uint32 rsv24_31 : 4;
		}fields;
		vc_uint32 value;
	};
}tVC_CNVCS_SR2;
/*************************************
* Address		: 0x00000058
* Default		: 0x00000190
* Name		: CNVCS_SR3
* Description	: CN VCS Setting Register3 (CIFS)
*************************************/
//#define CNVCS_SR3    0x58
typedef struct tVC_CNVCS_SR3 {
	union {
		struct {
			vc_uint32 csr_cnvcs_cifs     : 24;
			vc_uint32 rsv24_31 : 4;
		}fields;
		vc_uint32 value;
	};
}tVC_CNVCS_SR3;
/*************************************
 * Address		: 0x0000005C
 * Default		: 0x000008FC
 * Name		: CNVCS_SR4
 * Description	: CN VCS Setting Register4 (RIFS)
 ************************************/
//#define CNVCS_SR4    0x5C
typedef struct tVC_CNVCS_SR4 {
	union {
		struct {
			vc_uint32 csr_cnvcs_rifs      : 24;
			vc_uint32 rsv24_31 : 4;
		}fields;
		vc_uint32 value;
	};
}tVC_CNVCS_SR4;
/*************************************
 * Address		: 0x00000060
 * Default		: 0x000004B0
 * Name		: CNVCS_SR5
 * Description	: CN VCS Setting Register5 (ACK Duration)
 ************************************/
//#define CNVCS_SR5    0x60
typedef struct tVC_CNVCS_SR5 {
	union {
		struct {
			vc_uint32 csr_cnvcs_ackdur      : 24;
			vc_uint32 rsv24_31 : 4;
		}fields;
		vc_uint32 value;
	};
}tVC_CNVCS_SR5;
/*************************************
 * Address		: 0x00000064
 * Default		: 0x00000000
 * Name		: CNVCS_SR6
 * Description	: CN VCS Setting Register6 (ACK Tolerance)
 ************************************/
//#define CNVCS_SR6    0x64
typedef struct tVC_CNVCS_SR6 {
	union {
		struct {
			vc_uint32 csr_cnvcs_acktol      : 24;
			vc_uint32 rsv24_31 : 4;
		}fields;
		vc_uint32 value;
	};
}tVC_CNVCS_SR6;
/*************************************
 * Address		: 0x00000068
 * Default		: 0x00000A8C
 * Name		: CNVCS_SR7
 * Description	: CN VCS Setting Register7 (WAIT ACK)
 ************************************/
//#define CNVCS_SR7    0x68
typedef struct tVC_CNVCS_SR7 {
	union {
		struct {
			vc_uint32 csr_cnvcs_waitack      : 24;
			vc_uint32 rsv24_31 : 4;
		}fields;
		vc_uint32 value;
	};
}tVC_CNVCS_SR7;
/*************************************
 * Address		: 0x00000070
 * Default		: 0x01210025
 * Name		: CNSCH_CR1
 * Description	: CN Scheduler Control Register 1
 ************************************/
//#define CNSCH_CR1    0x70
typedef struct tVC_CNSCH_CR1 {
	union {
		struct {
			vc_uint32 csr_cnsch_tt       : 12;
			vc_uint32 rsv12_15 : 4;
			vc_uint32 csr_cnsch_ttsync        : 1;
			vc_uint32 rsv17_19 : 3;
			vc_uint32 csr_cnsch_md_dbdet         : 1;
			vc_uint32 csr_cnsch_md_hwretry        : 1;
			vc_uint32 csr_cnsch_md_hold         : 1;
			vc_uint32 rsv23 : 1;
			vc_uint32 csr_cnsch_chksp : 1;
			vc_uint32 rsv25_31 : 7;
		}fields;
		vc_uint32 value;
	};
}tVC_CNSCH_CR1;
/*************************************
 * Address		: 0x00000074
 * Default		: 0x010003E8
 * Name		: CNSCH_TSR1
 * Description	: CN Scheduler TX Setting Register1
 ************************************/
//#define CNSCH_TSR1    0x74
typedef struct tVC_CNSCH_TSR1 {
	union {
		struct {
			vc_uint32 csr_cnsch_txdur : 12;
			vc_uint32 csr_cnsch_csma : 4;
			vc_uint32 csr_cnsch_tdma : 1;
			vc_uint32 rsv26_27 : 3;
			vc_uint32 csr_cnsch_ackreq : 1;
			vc_uint32 rsv29_31 : 1;
		}fields;
		vc_uint32 value;
	};
}tVC_CNSCH_TSR1;
/*************************************
 * Address		: 0x00000078
 * Default		: 0x000003E8
 * Name		: CNSCH_TSR2
 * Description	: CN Scheduler TX Setting Register2
 ************************************/
//#define CNSCH_TSR2    0x78
typedef struct tVC_CNSCH_TSR2 {
	union {
		struct {
			vc_uint32 csr_cnsch_backoff : 24;
			vc_uint32 rsv24_31 : 8;
		}fields;
		vc_uint32 value;
	};
}tVC_CNSCH_TSR2;
/*************************************
 * Address		: 0x0000007C
 * Default		: 0x00000000
 * Name		: CNSCH_TSR3
 * Description	: CN Scheduler TX Setting Register3
 ************************************/
//#define CNSCH_TSR3    0x7C
typedef struct tVC_CNSCH_TSR3 {
	union {
		struct {
			vc_uint32 csr_cnsch_txtime : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_CNSCH_TSR3;
/*************************************
 * Address		: 0x00000080
 * Default		: 0x00000000
 * Name		: CNSCH_TSR4
 * Description	: CN Scheduler TX Setting Register4
 ************************************/
//#define CNSCH_TSR4    0x80
typedef struct tVC_CNSCH_TSR4 {
	union {
		struct {
			vc_uint32 csr_cnsch_ttg : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_CNSCH_TSR4;
/*************************************
 * Address		: 0x00000084
 * Default		: 0x00000000
 * Name		: CNSCH_TSR5
 * Description	: CN Scheduler TX Setting Register5
 ************************************/
//#define CNSCH_TSR5    0x84
typedef struct tVC_CNSCH_TSR5 {
	union {
		struct {
			vc_uint32 csr_cnsch_diff  : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_CNSCH_TSR5;
/*************************************
 * Address		: 0x00000088
 * Default		: 0x00000000
 * Name		: CNSCH_RTY_CR
 * Description	: CNCSMA Retry Control Register
 ************************************/
//#define CNSCH_RTY_CR    0x88
typedef struct tVC_CNSCH_RTY_CR {
	union {
		struct {
			vc_uint32 csr_cnsch_retry_stop  : 1;
			vc_uint32 csr_cnsch_retry_abort  : 1;
			vc_uint32 csr_cnsch_retry   : 1;
			vc_uint32 csr_dsp_abortpkt   : 1;
			vc_uint32 rsv4_31 : 28;
		}fields;
		vc_uint32 value;
	};
}tVC_CNSCH_RTY_CR;
/*************************************
 * Address		: 0x0000008C
 * Default		: 0x00000000
 * Name		: CNSCH_IR
 * Description	: CNScheduler Information Register
 ************************************/
//#define CNSCH_IR    0x8C
typedef struct tVC_CNSCH_IR {
	union {
		struct {
			vc_uint32 csr_cnsch_cursq  : 8;
			vc_uint32 rsv4_31 : 24;
		}fields;
		vc_uint32 value;
	};
}tVC_CNSCH_IR;
/*************************************
 * Address		: 0x00000090
 * Default		: 0x00000000
 * Name		: CNRXARQ_SR
 * Description	: ARQ RX Side Setting Register
 ************************************/
//#define CNRXARQ_SR    0x90
typedef struct tVC_CNRXARQ_SR {
	union {
		struct {
			vc_uint32 csr_cnrxp_load  : 8;
			vc_uint32 rsv4_31 : 24;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXARQ_SR;
/*************************************
 * Address		: 0x000000A0
 * Default		: 0x00000000
 * Name		: CNTXARQ_IR
 * Description	: ARQ TX Side Information Register
 ************************************/
//#define CNTXARQ_IR    0xA0
typedef struct tVC_CNTXARQ_IR {
	union {
		struct {
			vc_uint32 csr_tarq_sack_status  : 8;
			vc_uint32 rsv4_31 : 24;
		}fields;
		vc_uint32 value;
	};
}tVC_CNTXARQ_IR;
/*************************************
 * Address		: 0x000000B0
 * Default		: 0x00000004
 * Name		: CNRXP_SR1
 * Description	: CN RXP Setting Register1
 ************************************/
//#define CNRXP_SR1    0xB0
typedef struct tVC_CNRXP_SR1 {
	union {
		struct {
			vc_uint32 csr_cnrxp_fcwdlen  : 8;
			vc_uint32 rsv4_31 : 24;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXP_SR1;
/*************************************
 * Address		: 0x000000B4
 * Default		: 0x82422212
 * Name		: CNRXP_SR2
 * Description	: CN RXP Setting Register2
 ************************************/
//#define CNRXP_SR2    0xB4
typedef struct tVC_CNRXP_SR2 {
	union {
		struct {
			vc_uint32 csr_cnrxp_pbsize0  : 8;
			vc_uint32 csr_cnrxp_pbsize1 : 8;
			vc_uint32 csr_cnrxp_pbsize2  : 8;
			vc_uint32 csr_cnrxp_pbsize3  : 8;
		}fields;
		vc_uint32 value;
	};
}tVC_CNRXP_SR2;
#endif

/******************************************************************/
/******************************************************************/
//#define DMA_CR    0x00
typedef struct tVC_HWMAC_DMA_CR {
	union {
		struct {
			vc_uint32 csr_sgmac_rstn : 1; /*0*/
			vc_uint32 csr_g3mac_rstn : 1; /*1*/
			vc_uint32 rsv2_3 : 2;         /*2-3*/
			vc_uint32 csr_bufif_g3 : 1;   /*4*/
			vc_uint32 csr_dspif_g3 : 1;   /*5*/
			vc_uint32 csr_plcmac_lb : 1;  /*6*/
			vc_uint32 rsv7_15 : 8;        /*7-15*/
			vc_uint32 csr_access_dly : 3; /*16-19*/
			vc_uint32 rsv20_31 : 11;      /*11*/
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_CR;
/************************************/
//#define DMA_TM_CR    0x0C
typedef struct tVC_HWMAC_DMA_TM_CR {
	union {
		struct {
			vc_uint32 csr_dma_lb        : 1;
			vc_uint32 csr_buf_lb        : 1;
			vc_uint32 csr_rxstatus_drop : 1;
		}         fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_TM_CR;
/************************************/
//#define DMA_TXE_CR    0x10
typedef struct tVC_HWMAC_DMA_TXE_CR {
	union {
		struct {
			vc_uint32 csr_txe_byteswap : 1;
			vc_uint32 csr_txe_chkfd    : 1;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_TXE_CR;
/************************************/
/*==========================================*/
typedef struct tVC_HWMAC_DMA_TXE_SR {
	union {
		struct {
			vc_uint32 csr_txe_desc_gap : 8;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_TXE_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_TXE_KR {
	union {
		struct {
			vc_uint32 csr_txe_kick : 1;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_TXE_KR;
/************************************/
typedef struct tVC_HWMAC_DMA_TXE_BA_SR {
	union {
		struct {
			vc_uint32 csr_txbase_addr : 32;
		}         fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_TXE_BA_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_TXE_NA_SR {
	union {
		struct {
			vc_uint32 csr_txnext_addr : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_TXE_NA_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_TXE_CA_IR {
	union {
		struct {
			vc_uint32 csr_txcurr_addr : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_TXE_CA_IR;
/************************************/
typedef struct  tVC_HWMAC_DMA_TXE_REQ_IR {
	union {
		struct {
			vc_uint32 csr_txreq_addr : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_TXE_REQ_IR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_CR {
	union {
		struct {
			vc_uint32 csr_rxe_byteswap : 1;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_RXE_CR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_SR {
	union {
		struct {
			vc_uint32 csr_rxe_desc_gap : 8;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_RXE_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_KR {
	union {
		struct {
			vc_uint32 csr_rxe_kick : 1;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_RXE_KR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_BA_SR {
	union {
		struct {
			vc_uint32 csr_rxbase_addr : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_RXE_BA_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_NA_SR {
	union {
		struct {
			vc_uint32 csr_rxnext_addr : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_RXE_NA_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_CA_IR {
	union {
		struct {
			vc_uint32 csr_rxcurr_addr : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_RXE_CA_IR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_REQ_IR {
	union {
		struct {
			vc_uint32 csr_rxreq_addr : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_RXE_REQ_IR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_SA_IR {
	union {
		struct {
			vc_uint32 csr_rxstart_addr : 32;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_RXE_SA_IR;
/************************************/
typedef struct tVC_HWMAC_DMA_IER {
	union {
		struct {
			vc_uint32 ier_txcmp     : 1;
			vc_uint32 ier_txunavail : 1;
			vc_uint32 ier_txerror   : 1;
			vc_uint32 ier_txupdate  : 1;
			vc_uint32 reserved7_4   : 4;
			vc_uint32 ier_rxcmp     : 1;
			vc_uint32 ier_rxunavail : 1;
			vc_uint32 ier_rxerror   : 1;
			vc_uint32 ier_rxupdate  : 1;
			vc_uint32 ier_rxreclaim : 1;
			vc_uint32 ier_msterr    : 1;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_IER;
/************************************/
typedef struct tVC_HWMAC_DMA_ISR {
	union {
		struct {
			vc_uint32 isr_txcmp     : 1;
			vc_uint32 isr_txunavail : 1;
			vc_uint32 isr_txerror   : 1;
			vc_uint32 isr_txupdate  : 1;
			vc_uint32 reserved7_4   : 4;
			vc_uint32 isr_rxcmp     : 1;
			vc_uint32 isr_rxunavail : 1;
			vc_uint32 isr_rxerror   : 1;
			vc_uint32 isr_rxupdate  : 1;
			vc_uint32 isr_rxreclaim : 1;
			vc_uint32 isr_msterr    : 1;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_ISR;
/************************************/
typedef struct tVC_HWMAC_DMA_ISTR {
	union {
		struct {
			vc_uint32 istr_txcmp     : 1;
			vc_uint32 istr_txunavail : 1;
			vc_uint32 istr_txerror   : 1;
			vc_uint32 istr_txupdate  : 1;
			vc_uint32 reserved7_4    : 4;
			vc_uint32 istr_rxcmp     : 1;
			vc_uint32 istr_rxunavail : 1;
			vc_uint32 istr_rxerror   : 1;
			vc_uint32 istr_rxupdate  : 1;
			vc_uint32 istr_rxreclaim : 1;
			vc_uint32 istr_msterr    : 1;
		}fields;
		vc_uint32 value;
	};
}tVC_HWMAC_DMA_ISTR;
/************************************/
/************************************/
/************************************/
/************************************/
/************************************/

#endif
