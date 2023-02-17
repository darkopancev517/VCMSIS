#ifndef VC_MAC_HWMAC_DMA_H
#define VC_MAC_HWMAC_DMA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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
			uint32_t csr_txeng_rstn : 1;
			uint32_t csr_rxeng_rstn : 1;
			uint32_t rsv2_7 : 6;
			uint32_t csr_txbuf_rstn : 1;
			uint32_t csr_rxbuf_rstn : 1;
			uint32_t rsv10_31 : 22;
		} fields;
		uint32_t value;
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
			uint32_t csr_dma_lb : 1;
			uint32_t csr_buf_lb : 1;
			uint32_t rsv2_7 : 6;
			uint32_t csr_rxstatus_drop : 1;
			uint32_t rsv9_31 : 23;
		} fields;
		uint32_t value;
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
			uint32_t csr_txe_byteswap : 1;
			uint32_t csr_txe_chkfd : 1;
			uint32_t rsv2_31 : 30;
		} fields;
		uint32_t value;
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
			uint32_t csr_txe_desc_gap : 8;
			uint32_t rsv8_31 : 24;
		}fields;
		uint32_t value;
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
			uint32_t csr_txe_kick : 1;
			uint32_t rsv1_31 : 31;
		} fields;
		uint32_t value;
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
			uint32_t csr_txbase_addr : 32;
		} fields;
		uint32_t value;
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
			uint32_t csr_txnext_addr : 32;
		} fields;
		uint32_t value;
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
			uint32_t csr_txcurr_addr : 32;
		} fields;
		uint32_t value;
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
			uint32_t csr_txreq_addr : 32;
		} fields;
		uint32_t value;
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
			uint32_t csr_rxe_byteswap : 1;
			uint32_t rsv1_31 : 31;
		} fields;
		uint32_t value;
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
			uint32_t csr_rxe_desc_gap : 8;
			uint32_t rsv8_31 : 24;
		} fields;
		uint32_t value;
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
			uint32_t csr_rxe_kick : 1;
			uint32_t rsv1_31 : 31;
		} fields;
		uint32_t value;
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
			uint32_t csr_rxbase_addr : 32;
		} fields;
		uint32_t value;
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
			uint32_t csr_rxnext_addr : 32;
		} fields;
		uint32_t value;
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
			uint32_t csr_rxcurr_addr  : 32;
		} fields;
		uint32_t value;
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
			uint32_t csr_rxreq_addr  : 32;
		} fields;
		uint32_t value;
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
			uint32_t csr_rxstart_addr  : 32;
		} fields;
		uint32_t value;
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
			uint32_t ier_txcmp : 1;
			uint32_t ier_txunavail : 1;
			uint32_t ier_txerror : 1;
			uint32_t ier_txupdate : 1;
			uint32_t rsv4_7 : 4;
			uint32_t ier_rxcmp : 1;
			uint32_t ier_rxunavail : 1;
			uint32_t ier_rxerror : 1;
			uint32_t ier_rxupdate : 1;
			uint32_t ier_rxreclaim : 1;
			uint32_t rsv13_15 : 3;
			uint32_t ier_msterr : 1;
			uint32_t rsv17_31 : 15;
		} fields;
		uint32_t value;
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
			uint32_t isr_txcmp : 1;
			uint32_t isr_txunavail : 1;
			uint32_t isr_txerror : 1;
			uint32_t isr_txupdate : 1;
			uint32_t rsv4_7 : 4;
			uint32_t isr_rxcmp : 1;
			uint32_t isr_rxunavail : 1;
			uint32_t isr_rxerror : 1;
			uint32_t isr_rxupdate : 1;
			uint32_t isr_rxreclaim : 1;
			uint32_t rsv13_15 : 3;
			uint32_t isr_msterr : 1;
			uint32_t rsv17_31 : 15;
		} fields;
		uint32_t value;
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
			uint32_t istr_txcmp : 1;
			uint32_t istr_txunavail : 1;
			uint32_t istr_txerror : 1;
			uint32_t istr_txupdate : 1;
			uint32_t rsv4_7 : 4;
			uint32_t istr_rxcmp : 1;
			uint32_t istr_rxunavail : 1;
			uint32_t istr_rxerror : 1;
			uint32_t istr_rxupdate : 1;
			uint32_t istr_rxreclaim : 1;
			uint32_t rsv13_15 : 3;
			uint32_t istr_msterr : 1;
			uint32_t rsv17_31 : 15;
		} fields;
		uint32_t value;
	};
}tVC_DMA_ISTR;

/******************************************************************/
/******************************************************************/
//The PLC MAC Registers
/*************************************
* Address		: 0x00000000
* Default		: 0x00040000
* Name			: MAC_CR
* Description	: MAC Control Register
*************************************/
#if 1
//#define MAC_CR        0x00
typedef struct tVC_MAC_CR {
	union {
		struct {
			uint32_t csr_sgmac_rstn			:1;	/*0		Reset for SGMAC (must set to 1 before starting SG MODEM)*/
			uint32_t csr_g3mac_rstn			:1;	/*1		Reset for G3MAC (must set to 1 before starting G3 MODEM)*/
			uint32_t rsv2_3					:2;	/*2-3	Reserved.*/
			uint32_t csr_bufif_g3				:1;	/*4		BUF IF MUX, 1: G3, 0: CN*/
			uint32_t csr_dspif_g3				:1;	/*5		DSP IF MUX, 1: G3, 0: CN*/
			uint32_t csr_plcmac_lb				:1;	/*6		PLCMAC Loopback Mode*/
			uint32_t rsv7_15					:9;	/*7-15	Reserved.*/
			uint32_t csr_access_dly			:4;	/*16-19	The CSR RDY response time*/
			uint32_t rsv20_31					:12;/*20-31	Reserved.*/
		}fields;
		uint32_t value;
	};
}tVC_MAC_CR;
/*************************************
* Address		: 0x00000010
* Default		: 0x00000000
* Name			: CNMAC_CR
* Description	: CN MAC Control Register
*************************************/
//#define CNMAC_CR        0x10
typedef struct tVC_CNMAC_CR {
	union {
		struct {
			uint32_t csr_cnmac_txen			:1;	/*0		CN MAC TX Enable*/
			uint32_t csr_cnmac_rxen			:1;	/*1		CN MAC RX Enable*/
			uint32_t csr_cnmac_rfen			:1;	/*2		CN MAC RF Enable*/
			uint32_t csr_cnmac_rxarqen			:1;	/*3		CN MAC RXARQ Enable*/
			uint32_t csr_cnmac_vcsen			:1;	/*4		CN MAC VCS Enable*/
			uint32_t csr_cnmac_schen			:1;	/*5		CN MAC CSMA Enable*/
			uint32_t csr_cnmac_vcstten			:1;	/*6		CN MAC VCS Time Tick Enable*/
			uint32_t rsv7_31					:25;/*7-31	Reserved.*/
		}fields;
		uint32_t value;
	};
}tVC_CNMAC_CR;
/*************************************
* Address		: 0x00000014
* Default		: 0x00030045
* Name			: CNMAC_CR2
* Description	: CN MAC Control Register2 for TXP and RXP
*************************************/
//#define CNMAC_CR2    0x14
typedef struct tVC_CNMAC_CR2 {
	union {
		struct {
			uint32_t csr_cnrxp_pdumatch_mac	:1;	/*0		Check the PDU(Type NRX) RX or NOT by MAC (RX Filter)*/
			uint32_t csr_cnrxp_pdumatch_dsp	:1;	/*1		Check the PDU(Type NRX) RX or NOT by DSP (OK to enable both)*/
			uint32_t csr_cnrxp_ackreq_mac		:1;	/*2		Check the PDU(Type NRX) require SACK or not by MAC*/
			uint32_t csr_cnrxp_ackreq_dsp		:1;	/*3		Check the PDU(Type NRX) require SACK or not by DSP (OK to enable both)*/
			uint32_t csr_cnrxp_drop_mismatch	:1;	/*4		Drop the mismatch PDU (if enable both => drop all mismatch)*/
			uint32_t csr_cnrxp_drop_crcerror	:1;	/*5		Drop the CRC Error PDU*/
			uint32_t csr_cnrxp_swapin			:1;	/*6		Set 1 for SGCC. Set 0 for G3. Swap the endian. (swap at cnmac)*/
			uint32_t rsv7_15					:9;	/*7-15	Reserved.*/
			uint32_t csr_cntxp_chksch			:1;	/*16	1: TXP FSM will wait SCH_DONE (can't TX another packet before DONE)*/
			uint32_t csr_cntxp_swapout			:1;	/*17	Set 1 for SGCC. Set 0 for G3. Swap the endian*/
			uint32_t rsv18_31					:14;/*18-31	Reserved.*/
		}fields;
		uint32_t value;
	};
}tVC_CNMAC_CR2;
/*************************************
* Address		: 0x00000020
* Default		: 0x00000000
* Name			: CNMAC_IER
* Description	: CN MAC IER
*************************************/
//#define CNMAC_IER    0x20
typedef struct tVC_CNMAC_IER {
	union {
		struct {
			uint32_t ier_cntxp_done			:1;	/*0		CN TXP Done*/
			uint32_t ier_dsp_abortpkt			:1;	/*1		CN TXP Kickphy*/
			uint32_t rsv2_3					:2;	/*2-3	Reserved.*/
			uint32_t ier_cnrxp_done			:1;	/*4		CN RXP Done*/
			uint32_t rsv5_7					:3;	/*5-7	Reserved*/
			uint32_t ier_cnmac_ackto			:1;	/*8		CN TXARQ ACK Timeout*/
			uint32_t ier_cnmac_get_sack		:1;	/*9		CN TXARQ GET SACK*/
			uint32_t rsv10_11					:2;	/*10-11	Reserved.*/
			uint32_t ier_cnmac_resp_sack		:1;	/*12	CN RXARQ Response ACK*/
			uint32_t ier_cnmac_abortack		:1;	/*13	CN RXARQ Abort ACK (too late)*/
			uint32_t rsv14_15					:1;	/*14-15	Reserved*/
			uint32_t ier_cnsch_get_para		:1;	/*16	CN CSMA Get Parameters for the scheduler*/
			uint32_t ier_cnsch_csma_success	:1;	/*17	CN CSMA Success*/
			uint32_t ier_cnsch_csma_fail		:1;	/*18	CN CSMA Fail*/
			uint32_t ier_cnsch_csma_abort		:1;	/*19	CN CSMA Abort*/
			uint32_t ier_cnsch_tdma_timeup		:1;	/*20	CN TDMA Timeup*/
			uint32_t ier_cnsch_tdma_fail		:1;	/*21	CN TDMA Fail*/
			uint32_t ier_cnsch_kickphy			:1;	/*22	CN Kickphy*/
			uint32_t rsv23_27					:5;	/*23-27	Reserved*/
			uint32_t ier_zc1					:1;	/*28	IER Zero Crossing 1 (GPIO)*/
			uint32_t ier_zc2					:1;	/*29	IER Zero Crossing 2 (GPIO)*/
			uint32_t ier_zc3					:1;	/*30	IER Zero Crossing 3 (AFE)*/
			uint32_t rsv31						:1;	/*31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNMAC_IER;
/*************************************
* Address		: 0x00000024
* Default		: 0x00000000
* Name			: CNMAC_ISR
* Description	: CN MAC IER
*************************************/
//#define CNMAC_ISR    0x24
typedef struct tVC_CNMAC_ISR {
	union {
		struct {
			uint32_t isr_cntxp_done			:1;	/*0		CN TXP Done*/
			uint32_t isr_dsp_abortpkt			:1;	/*1		CN TXP Kickphy*/
			uint32_t rsv2_3					:2;	/*2-3	Reserved.*/
			uint32_t isr_cnrxp_done			:1;	/*4		CN RXP Done*/
			uint32_t rsv5_7					:3;	/*5-7	Reserved*/
			uint32_t isr_cnmac_ackto			:1;	/*8		CN TXARQ ACK Timeout*/
			uint32_t isr_cnmac_get_sack		:1;	/*9		CN TXARQ ACK Timeout*/
			uint32_t rsv10_11					:2;	/*10-11	Reserved.*/
			uint32_t isr_cnmac_resp_sack		:1;	/*12	CN RXARQ Response ACK*/
			uint32_t isr_cnmac_abortack		:1;	/*13	CN RXARQ Abort ACK (too late)*/
			uint32_t rsv14_15					:2;	/*14-15	Reserved.*/
			uint32_t isr_cnsch_get_para		:1;	/*16	CN CSMA Get Parameters for the scheduler*/
			uint32_t isr_cnsch_csma_success	:1;	/*17	CN CSMA Success*/
			uint32_t isr_cnsch_csma_fail		:1;	/*18	CN CSMA Fail*/
			uint32_t isr_cnsch_csma_abort		:1;	/*19	CN CSMA Abort*/
			uint32_t isr_cnsch_tdma_timeup		:1;	/*20	CN CSMA Abort*/
			uint32_t isr_cnsch_tdma_fail		:1;	/*21	CN TDMA Fail*/
			uint32_t isr_cnsch_kickphy			:1;	/*22	CN Kickphy*/
			uint32_t rsv_23_27					:5;	/*23-27	Reserved.*/
			uint32_t isr_zc1					:1;	/*28	ISR Zero Crossing 1 (GPIO)*/
			uint32_t isr_zc2					:1;	/*29	ISR Zero Crossing 2 (GPIO)*/
			uint32_t isr_zc3					:1;	/*30	ISR Zero Crossing 3 (AFE)*/
			uint32_t rsv_31					:1;	/*31	Reserved.*/
		}fields;
		uint32_t value;
	};
}tVC_CNMAC_ISR;
/*************************************
* Address		: 0x00000030
* Default		: 0x00000000
* Name			: CNRXF_SET1_SR1
* Description	: CN RX Filter SET1 Setting Register1
*************************************/
//#define CNRXF_SET1_SR1    0x30
typedef struct tVC_CNRXF_SET1_SR1 {
	union {
		struct {
			uint32_t csr_cnrxf_nid1			:24;/*0-23	Network ID*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved.*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXF_SET1_SR1;
/*************************************
* Address		: 0x00000034
* Default		: 0x00000000
* Name			: CNRXF_SET1_SR2
* Description	: CN RX Filter SET1 Setting Register2
*************************************/
//#define CNRXF_SET1_SR2    0x34
typedef struct tVC_CNRXF_SET1_SR2 {
	union {
		struct {
			uint32_t csr_cnrxf_dtei1			:12;/*0-11	DTEI*/
			uint32_t rsv12_31					:20;/*12-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXF_SET1_SR2;
/*************************************
* Address		: 0x00000038
* Default		: 0x00000000
* Name			: CNRXF_SET2_SR1
* Description	: CN RX Filter SET2 Setting Register1
*************************************/
//#define CNRXF_SET2_SR1    0x38
typedef struct tVC_CNRXF_SET2_SR1 {
	union {
		struct {
			uint32_t csr_cnrxf_nid2			:24;/*0-23	Network ID*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnrxf_dtei2			:12;/*0-11	DTEI*/
			uint32_t rsv12_31					:20;/*12-31	Reserved.*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnrxf_nidmask			:24;/*0-23	Network ID Mask*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnrxf_dteimask		:12;/*0-11	DTEI Mask*/
			uint32_t rsv12_31					:20;/*12-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnrxf_sack_stei		:12;/*0-11	Source TEI to check SACK (should set the last SOF DTEI)*/
			uint32_t rsv12_31					:20;/*12-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnrxf_dt_beacon		:3;	/*0-2	DT Beacon*/
			uint32_t rsv3						:1;	/*3		Reserved*/
			uint32_t csr_cnrxf_dt_sof			:3;	/*4-6	DT SoF*/
			uint32_t rsv7						:1;	/*7		Reserved*/
			uint32_t csr_cnrxf_dt_sack			:3;	/*8-10	DT SACK*/
			uint32_t rsv11_31					:21;/*11-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnvcs_tt				:12;/*0-11	Time Tick (default: to us)(300MHz)*/
			uint32_t rsv12_15					:4;	/*12-15	Reserved.*/
			uint32_t csr_cnvcs_ttsync			:1;	/*16	Time Tick sync PMB (1: will reset when pmb_det)*/
			uint32_t csr_cnvcs_rxinrx			:1;	/*17	Allow det_pmb in the ST_VCS_RXDUR*/
			uint32_t csr_cnvcs_rxintx			:1;	/*18	Allow det_pmb in the ST_VCS_TXDUR*/
			uint32_t rsv19_23					:5;	/*19-23	Reserved*/
			uint32_t csr_cnvcs_swsync			:1;	/*24	SW trigger to clear csma or vcs tick as rx_pmb do*/
			uint32_t rsv25_31					:7;	/*25-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnvcs_eifs			:24;/*0-23	EIFS (20ms)*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved.*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnvcs_cifs			:24;/*0-23	CIFS (400us)*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved.*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnvcs_rifs			:24;/*0-23	RIFS (400us~2300us)*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved.*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnvcs_ackdur			:24;/*0-23	ACK Duration*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved.*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnvcs_acktol			:24;/*0-23	ACK Tolerance Duration. ACK TX Latency or for earlier kick*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnvcs_waitack			:24;/*0-23	[G3] WAIT ACK = rifs + ackfrm + cifs + tolerance (time tick)*/
			uint32_t rsv24_31					:8;	/*24-3	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnsch_tt				:12;/*0-11	CSMA Time Tick (default: to us)(300MHz)*/
			uint32_t rsv12_15					:4;	/*12-15	Reserved*/
			uint32_t csr_cnsch_ttsync			:1;	/*16	CSMA Time Tick sync PMB*/
			uint32_t rsv17_19					:3;	/*17-19	Reserved*/
			uint32_t csr_cnsch_md_dbdet		:1;	/*20	Double Detection (G3)*/
			uint32_t csr_cnsch_md_hwretry		:1;	/*21	CSMA HW Auto Retry*/
			uint32_t csr_cnsch_md_hold			:1;	/*22	CSMA Hold Mode Enable*/
			uint32_t rsv23						:1;	/*23	Reserved*/
			uint32_t csr_cnsch_chksp			:1;	/*24	[SGCC] CSMA check VCS_IDLE first before back-off.*/
			uint32_t rsv25_31					:7;	/*25-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnsch_txdur			:24;/*0-23	TX Duration (us)*/
			uint32_t csr_cnsch_csma			:1;	/*24	CSMA enable (CN or G3)*/
			uint32_t csr_cnsch_tdma			:1;	/*25	TDMA enable (CN)*/
			uint32_t rsv26_27					:2;	/*26-27	Reserved.*/
			uint32_t csr_cnsch_ackreq			:1;	/*28	TX requires ACK(SACK)*/
			uint32_t rsv29_31					:3;	/*29-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnsch_backoff			:24;/*0-23	CSMA Back Off time tick*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnsch_txtime			:32;/*0-31	TDMA TX Time (by NTB)*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnsch_ttg				:32;/*0-31	Time to Give (by NTB)*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnsch_diff			:32;/*0-31	The difference between NTB and TTG*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnsch_retry_stop		:1;	/*0		Stop the CSMA retry (when HW auto retry)*/
			uint32_t csr_cnsch_retry_abort		:1;	/*1		Abort the CSMA*/
			uint32_t csr_cnsch_retry			:1;	/*2		Retry the CSMA*/
			uint32_t csr_dsp_abortpkt			:1;	/*3		Abort the DSP*/
			uint32_t rsv4_31					:28;/*4-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnsch_cursq			:8;	/*0-7	The Sequence Number of the on-hand packet*/
			uint32_t rsv8_31					:24;/*8-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnrxp_load			:8;	/*0-7	The system loading. Fill in SACK to response*/
			uint32_t rsv8_31					:24;/*8-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_tarq_sack_status		:8;	/*0-7	The matched SACK we got (Status + PB Num)*/
			uint32_t rsv8_31					:24;/*8-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnrxp_fcwdlen			:8;	/*0-7	The word number of FC field (default 16B = 4W)*/
			uint32_t rsv8_31					:24;/*8-31	Reserved*/
		}fields;
		uint32_t value;
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
			uint32_t csr_cnrxp_pbsize0			:8;	/*0-7	The word number of PB Type 0 (default 72B = 18W)*/
			uint32_t csr_cnrxp_pbsize1			:8;	/*8-15	The word number of PB Type 1 (default 136B = 34W)*/
			uint32_t csr_cnrxp_pbsize2			:8;	/*16-23	The word number of PB Type 2 (default 264B = 66W)*/
			uint32_t csr_cnrxp_pbsize3			:8;	/*24-31	The word number of PB Type 3 (default 520B = 130W)*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXP_SR2;

//BBPLC MAC Debug Registers
/*************************************
 * Address		: 0x00000100
 * Default		: 0x00000000
 * Name		: CNTXP_DR1
 * Description	: CN TXP Debug Register1
 ************************************/
//#define CNTXP_DR1    0x100
typedef struct tVC_CNTXP_DR1 {
	union {
		struct {
			uint32_t csr_cntxp_cs				:4;	/*0-3	CN TXP FSM*/
			uint32_t rsv4_7					:4;	/*4-7	Reserved*/
			uint32_t csr_cntxp_mode			:4;	/*8-11	TXP Mode*/
			uint32_t csr_cntxp_type			:4;	/*12-15	TXP Type*/
			uint32_t rsv16_31					:16;/*16-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNTXP_DR1;

/*************************************
 * Address		: 0x00000104
 * Default		: 0x00000000
 * Name		: CNTXP_DR2
 * Description	: CN TXP Debug Register2
 ************************************/
//#define CNTXP_DR2    0x104
typedef struct tVC_CNTXP_DR2 {
	union {
		struct {
			uint32_t csr_cntxp_chdr_wdcnt		:14;/*0-13	CN TXP CHDR Word Counter*/
			uint32_t rsv14_15					:2;	/*14-15	Reserved*/
			uint32_t csr_cntxp_chdr_lwnum		:14;/*16-29	CN TXP CHDR Last Word Number*/
			uint32_t rsv30_31					:2;	/*30-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNTXP_DR2;

/*************************************
 * Address		: 0x00000108
 * Default		: 0x00000000
 * Name		: CNTXP_DR3
 * Description	: CN TXP Debug Register3
 ************************************/
//#define CNTXP_DR3    0x108
typedef struct tVC_CNTXP_DR3 {
	union {
		struct {
			uint32_t csr_cntxp_pkt_wdcnt		:14;/*0-13	CN TXP Packet Word Counter*/
			uint32_t rsv14_15					:2;	/*14-15	Reserved*/
			uint32_t csr_cntxp_pkt_lwnum		:14;/*16-29	CN TXP Packet Last Word Number*/
			uint32_t rsv30_31					:2;	/*30-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNTXP_DR3;

/*************************************
 * Address		: 0x0000010C
 * Default		: 0x00000000
 * Name		: CNTXP_MIB1
 * Description	: CN TXP Debug Counter1
 ************************************/
//#define CNTXP_MIB1    0x10C
typedef struct tVC_CNTXP_MIB1 {
	union {
		struct {
			uint32_t mibcnt_isr_cntxp_done		:8;	/*0-7	Done*/
			uint32_t mibcnt_isr_dsp_abortpkt	:8;	/*8-15	Abort*/
			uint32_t mibcnt_cntxp_ntx			:8;	/*16-23	TX with Normal TX Type*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNTXP_MIB1;

/*************************************
 * Address		: 0x00000120
 * Default		: 0x00000000
 * Name		: CNRXP_DR1
 * Description	: CN RXP Debug Register1
 ************************************/
//#define CNRXP_DR1    0x120
typedef struct tVC_CNRXP_DR1 {
	union {
		struct {
			uint32_t csr_cnrxp_cs				:4;	/*0-3	CN RXP FSM*/
			uint32_t rsv4_7					:4;	/*4-7	Reserved*/
			uint32_t csr_cnrxp_mode			:4;	/*8-11	RXP Mode*/
			uint32_t csr_cnrxp_type			:4;	/*12-15	RXP Type*/
			uint32_t rsv16_23					:8;	/*16-23	Reserved*/
			uint32_t csr_cnrxp_status			:8;	/*24-31	CN RXP Status*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXP_DR1;

/*************************************
 * Address		: 0x00000124
 * Default		: 0x00000000
 * Name		: CNRXP_DR2
 * Description	: : G3 RXP Debug Register2
 ************************************/
//#define CNRXP_DR2    0x124
typedef struct tVC_CNRXP_DR2 {
	union {
		struct {
			uint32_t csr_cnrxp_chdr_wdcnt		:14;/*0-13	CN RXP CHDR Word Counter*/
			uint32_t rsv14_15					:2;	/*14-15	Reserved*/
			uint32_t csr_cnrxp_chdr_lwnum		:14;/*16-29	CN RXP CHDR Last Word Number*/
			uint32_t rsv30_31					:2;	/*30-31Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXP_DR2;
/*************************************
 * Address		: 0x00000128
 * Default		: 0x00000000
 * Name		: CNRXP_DR3
 * Description	: CN RXP Debug Register3
 ************************************/
//#define CNRXP_DR3    0x128
typedef struct tVC_CNRXP_DR3 {
	union {
		struct {
			uint32_t csr_cnrxp_pkt_wdcnt		:14;/*0-13	CN RXP Packet Word Counter*/
			uint32_t rsv14_15					:2;	/*14-15	Reserved*/
			uint32_t csr_cnrxp_pkt_lwnum		:14;/*16-29	CN RXP Packet Last Word Number*/
			uint32_t rsv30_31					:2;	/*30-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXP_DR3;

/*************************************
 * Address		: 0x0000012C
 * Default		: 0x00000000
 * Name		: CNRXP_MIB1
 * Description	: CN RXP Debug Counter1
 ************************************/
//#define CNRXP_MIB1    0x12C
typedef struct tVC_CNRXP_MIB1 {
	union {
		struct {
			uint32_t mibcnt_isr_cnrxp_done		:8;	/*0-7	Done*/
			uint32_t mibcnt_cnrxp_nrx			:8;	/*8-15	RX a Normal RX Type */
			uint32_t mibcnt_cnrxp_pbcserr		:8;	/*16-23	PBCS Error in the chdr_status[3]*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXP_MIB1;

/*************************************
 * Address		: 0x00000140
 * Default		: 0x00000000
 * Name		: CNRXF_DR1
 * Description	: CN RXF Debug Register 1
 ************************************/
//#define CNRXF_DR1    0x140
typedef struct tVC_CNRXF_DR1 {
	union {
		struct {
			uint32_t csr_cnrxf_cs				:4;	/*0-3	CN RXF FSM*/
			uint32_t csr_cnrxf_beacon			:1;	/*4		CN RXF Type Beacon*/
			uint32_t csr_cnrxf_sof				:1;	/*5		CN RXF Type SOF*/
			uint32_t csr_cnrxf_sack			:1;	/*6		CN RXF Type SACK*/
			uint32_t csr_cnrxf_else			:1;	/*7		CN RXF Type Else*/
			uint32_t csr_cnrxf_stei			:12;/*8-19	CN RXF Source TEI*/
			uint32_t csr_cnrxf_dtei			:12;/*20-31	CN RXF Destination TEI*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXF_DR1;

/*************************************
 * Address		: 0x00000144
 * Default		: 0x00000000
 * Name		: CNRXF_DR2
 * Description	: CN RXF Debug Register 2
 ************************************/
//#define CNRXF_DR2    0x144
typedef struct tVC_CNRXF_DR2 {
	union {
		struct {
			uint32_t csr_cnrxf_nid				:24;/*0-23	CN RXF Network ID*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXF_DR2;

/*************************************
 * Address		: 0x00000148
 * Default		: 0x00000000
 * Name		: CNRXF_MIB1
 * Description	: CN TXP Debug Register1
 ************************************/
//#define CNRXF_MIB1    0x148
typedef struct tVC_CNRXF_MIB1 {
	union {
		struct {
			uint32_t mibcnt_cnrxf_match		:8;	/*0-7	RXF Match*/
			uint32_t mibcnt_cnrxf_mismatch		:8;	/*8-15	RXF Mismatch*/
			uint32_t mibcnt_cnrxf_ackreq		:8;	/*16-23	RXF SOF with ack request*/
			uint32_t mibcnt_cnrxf_getsack		:8;	/*24-31	RXF SACK*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXF_MIB1;

/*************************************
 * Address		: 0x0000014C
 * Default		: 0x00000000
 * Name		: CNRXF_MIB2
 * Description	: CN RXF MIB Counter2
 ************************************/
//#define CNRXF_MIB2    0x14C
typedef struct tVC_CNRXF_MIB2 {
	union {
		struct {
			uint32_t mibcnt_cnrxf_beacon		:8;	/*0-7	Beacon*/
			uint32_t mibcnt_cnrxf_sof			:8;	/*8-15	SoF*/
			uint32_t mibcnt_cnrxf_sack			:8;	/*16-23	SACK*/
			uint32_t mibcnt_cnrxf_else			:8;	/*24-31	ELSE*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXF_MIB2;

/*************************************
 * Address		: 0x00000154
 * Default		: 0x00000000
 * Name		: CNTXARQ_MIB1
 * Description	: CN RXF Debug Register 2
 ************************************/
//#define CNTXARQ_MIB1    0x154
typedef struct tVC_CNTXARQ_MIB1 {
	union {
		struct {
			uint32_t mibcnt_isr_cnmac_ackto	:8;	/*0-7	ACK Timeout*/
			uint32_t mibcnt_isr_cnmac_get_sack	:8;	/*8-15	GET SACK*/
			uint32_t rsv16_31					:16;/*16-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNTXARQ_MIB1;

/*************************************
 * Address		: 0x00000160
 * Default		: 0x00000000
 * Name		: CNRXARQ_DR
 * Description	: CN RX ARQ Debug Register
 ************************************/
//#define CNRXARQ_DR    0x160
typedef struct tVC_CNRXARQ_DR {
	union {
		struct {
			uint32_t csr_cnrarq_cs				:3;	/*0-2	CN RX ARQ FSM*/
			uint32_t rsv3_31					:29;/*3-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXARQ_DR;

/*************************************
 * Address		: 0x00000164
 * Default		: 0x00000000
 * Name		: CNRXARQ_MIB1
 * Description	: CN RXARQ Debug Counter1
 ************************************/
//#define CNRXARQ_MIB1    0x164
typedef struct tVC_CNRXARQ_MIB1 {
	union {
		struct {
			uint32_t mibcnt_isr_cnmac_abortack	:8;	/*0-7	Abort*/
			uint32_t rsv8_15					:8;	/*8-15	Reserved*/
			uint32_t mibcnt_isr_cnmac_resp_sack:8;	/*16-23	ACK*/
			uint32_t rsv24_31					:8;	/*24-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNRXARQ_MIB1;

/*************************************
 * Address		: 0x00000170
 * Default		: 0x00000000
 * Name		: CNVCS_DR1
 * Description	: CN VCS Debug Register1
 ************************************/
//#define CNVCS_DR1    0x170
typedef struct tVC_CNVCS_DR1 {
	union {
		struct {
			uint32_t csr_cnvcs_cs				:4;	/*0-3	CN VCS FSM*/
			uint32_t rsv4_7					:4;	/*4-7	Reserved*/
			uint32_t csr_cnvcs_tartt			:24;/*8-31	CN VCS Target Time Tick*/
		}fields;
		uint32_t value;
	};
}tVC_CNVCS_DR1;

/*************************************
 * Address		: 0x00000174
 * Default		: 0x00000000
 * Name		: CNVCS_DR2
 * Description	: CN VCS Debug Register2
 ************************************/
//#define CNVCS_DR2    0x174
typedef struct tVC_CNVCS_DR2 {
	union {
		struct {
			uint32_t rsv0_7					:8;	/*0-7	Reserved*/
			uint32_t csr_cnvcs_curtt			:24;/*8-23	CN VCS Current Time Tick*/
		}fields;
		uint32_t value;
	};
}tVC_CNVCS_DR2;

/*************************************
 * Address		: 0x00000178
 * Default		: 0x00000000
 * Name		: CNVCS_MIB1
 * Description	: SGMAC VCS Debug Counter1
 ************************************/
//#define CNVCS_MIB1    0x178
typedef struct tVC_CNVCS_MIB1 {
	union {
		struct {
			uint32_t mibcnt_rx_errfch			:8;	/*0-7	RX FCH Error (FC)*/
			uint32_t rsv8_31					:24;/*8-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNVCS_MIB1;

/*************************************
 * Address		: 0x00000180
 * Default		: 0x00000000
 * Name		: CNSCH_DR1
 * Description	: CN SCH Debug Register
 ************************************/
//#define CNSCH_DR1    0x180
typedef struct tVC_CNSCH_DR1 {
	union {
		struct {
			uint32_t csr_cnsch_cs				:4;	/*0-3	CN Scheduler FSM*/
			uint32_t rsv4_7					:4;	/*4-7	Reserved*/
			uint32_t csr_cnsch_boff_tcnt		:24;/*8-31	SGMAC back-off time tick counter*/
		}fields;
		uint32_t value;
	};
}tVC_CNSCH_DR1;

/*************************************
 * Address		: 0x00000188
 * Default		: 0x00000000
 * Name		: CNSCH_MIB1
 * Description	: Description: G3 SCH Debug Counter1
 ************************************/
//#define CNSCH_MIB1    0x188
typedef struct tVC_CNSCH_MIB1 {
	union {
		struct {
			uint32_t mibcnt_isr_cnsch_csma_success	:8;	/*0-7	CSMA Success*/
			uint32_t mibcnt_isr_cnsch_csma_fail	:8;	/*8-15	CSMA Fail*/
			uint32_t mibcnt_isr_cnsch_csma_abort	:8;	/*16-23	CSMA Abort*/
			uint32_t mibcnt_isr_cnsch_get_para		:8;	/*24-31	Get Parameters*/
		}fields;
		uint32_t value;
	};
}tVC_CNSCH_MIB1;

/*************************************
 * Address		: 0x0000018C
 * Default		: 0x00000000
 * Name		: CNSCH_MIB2
 * Description	: G3 SCH Debug Counter2
 ************************************/
//#define CNSCH_MIB2    0x18C
typedef struct tVC_CNSCH_MIB2 {
	union {
		struct {
			uint32_t mibcnt_isr_cnsch_tdma_timeup	:8;	/*0-7	TDMA Timeup*/
			uint32_t mibcnt_isr_cnsch_tdma_fail	:8;	/*8-15	TDMA Fail*/
			uint32_t mibcnt_isr_cnsch_kickphy		:8;	/*16-23	Kickphy*/
			uint32_t rsv24_31						:8;	/*24-31	Reserved*/
		}fields;
		uint32_t value;
	};
}tVC_CNSCH_MIB2;
#endif

/******************************************************************/
/******************************************************************/
//#define DMA_CR    0x00
typedef struct tVC_HWMAC_DMA_CR {
	union {
		struct {
			uint32_t csr_sgmac_rstn : 1; /*0*/
			uint32_t csr_g3mac_rstn : 1; /*1*/
			uint32_t rsv2_3 : 2;         /*2-3*/
			uint32_t csr_bufif_g3 : 1;   /*4*/
			uint32_t csr_dspif_g3 : 1;   /*5*/
			uint32_t csr_plcmac_lb : 1;  /*6*/
			uint32_t rsv7_15 : 8;        /*7-15*/
			uint32_t csr_access_dly : 3; /*16-19*/
			uint32_t rsv20_31 : 11;      /*11*/
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_CR;
/************************************/
//#define DMA_TM_CR    0x0C
typedef struct tVC_HWMAC_DMA_TM_CR {
	union {
		struct {
			uint32_t csr_dma_lb        : 1;
			uint32_t csr_buf_lb        : 1;
			uint32_t csr_rxstatus_drop : 1;
		}         fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_TM_CR;
/************************************/
//#define DMA_TXE_CR    0x10
typedef struct tVC_HWMAC_DMA_TXE_CR {
	union {
		struct {
			uint32_t csr_txe_byteswap : 1;
			uint32_t csr_txe_chkfd    : 1;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_TXE_CR;
/************************************/
/*==========================================*/
typedef struct tVC_HWMAC_DMA_TXE_SR {
	union {
		struct {
			uint32_t csr_txe_desc_gap : 8;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_TXE_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_TXE_KR {
	union {
		struct {
			uint32_t csr_txe_kick : 1;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_TXE_KR;
/************************************/
typedef struct tVC_HWMAC_DMA_TXE_BA_SR {
	union {
		struct {
			uint32_t csr_txbase_addr : 32;
		}         fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_TXE_BA_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_TXE_NA_SR {
	union {
		struct {
			uint32_t csr_txnext_addr : 32;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_TXE_NA_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_TXE_CA_IR {
	union {
		struct {
			uint32_t csr_txcurr_addr : 32;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_TXE_CA_IR;
/************************************/
typedef struct  tVC_HWMAC_DMA_TXE_REQ_IR {
	union {
		struct {
			uint32_t csr_txreq_addr : 32;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_TXE_REQ_IR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_CR {
	union {
		struct {
			uint32_t csr_rxe_byteswap : 1;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_RXE_CR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_SR {
	union {
		struct {
			uint32_t csr_rxe_desc_gap : 8;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_RXE_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_KR {
	union {
		struct {
			uint32_t csr_rxe_kick : 1;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_RXE_KR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_BA_SR {
	union {
		struct {
			uint32_t csr_rxbase_addr : 32;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_RXE_BA_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_NA_SR {
	union {
		struct {
			uint32_t csr_rxnext_addr : 32;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_RXE_NA_SR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_CA_IR {
	union {
		struct {
			uint32_t csr_rxcurr_addr : 32;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_RXE_CA_IR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_REQ_IR {
	union {
		struct {
			uint32_t csr_rxreq_addr : 32;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_RXE_REQ_IR;
/************************************/
typedef struct tVC_HWMAC_DMA_RXE_SA_IR {
	union {
		struct {
			uint32_t csr_rxstart_addr : 32;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_RXE_SA_IR;
/************************************/
typedef struct tVC_HWMAC_DMA_IER {
	union {
		struct {
			uint32_t ier_txcmp     : 1;
			uint32_t ier_txunavail : 1;
			uint32_t ier_txerror   : 1;
			uint32_t ier_txupdate  : 1;
			uint32_t reserved7_4   : 4;
			uint32_t ier_rxcmp     : 1;
			uint32_t ier_rxunavail : 1;
			uint32_t ier_rxerror   : 1;
			uint32_t ier_rxupdate  : 1;
			uint32_t ier_rxreclaim : 1;
			uint32_t ier_msterr    : 1;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_IER;
/************************************/
typedef struct tVC_HWMAC_DMA_ISR {
	union {
		struct {
			uint32_t isr_txcmp     : 1;
			uint32_t isr_txunavail : 1;
			uint32_t isr_txerror   : 1;
			uint32_t isr_txupdate  : 1;
			uint32_t reserved7_4   : 4;
			uint32_t isr_rxcmp     : 1;
			uint32_t isr_rxunavail : 1;
			uint32_t isr_rxerror   : 1;
			uint32_t isr_rxupdate  : 1;
			uint32_t isr_rxreclaim : 1;
			uint32_t isr_msterr    : 1;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_ISR;
/************************************/
typedef struct tVC_HWMAC_DMA_ISTR {
	union {
		struct {
			uint32_t istr_txcmp     : 1;
			uint32_t istr_txunavail : 1;
			uint32_t istr_txerror   : 1;
			uint32_t istr_txupdate  : 1;
			uint32_t reserved7_4    : 4;
			uint32_t istr_rxcmp     : 1;
			uint32_t istr_rxunavail : 1;
			uint32_t istr_rxerror   : 1;
			uint32_t istr_rxupdate  : 1;
			uint32_t istr_rxreclaim : 1;
			uint32_t istr_msterr    : 1;
		}fields;
		uint32_t value;
	};
}tVC_HWMAC_DMA_ISTR;
/************************************/
/************************************/
/************************************/
/************************************/
/************************************/

#ifdef __cplusplus
}
#endif

#endif // VC_MAC_HWMAC_DMA_H
