#ifndef VC_MAC_HWMAC_IF_H
#define VC_MAC_HWMAC_IF_H

#include <stdint.h>

#include "vc_lmac_dma.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VC_MAC_DMA_BASE		 0x40010000
#define VC_MAC_CN_BASE		 0x40011000
#define VC_MAC_CN_DEBUG		 0x40011100
#define VC_MAC_G3_BASE		 0x40011200
#define VC_MAC_G3_CSMA_TR1 0x40011280

/*	The VC_DMAC_RX_BUF_SIZE	is set sufficiently large to accommidate a packet that is sent	*/
/*	with multiple pbs. This simplify the implementation in a way that the receiver does not	*/
/*	have to reassembble pbs across the rx descriptors										*/
#define VC_DMAC_RX_NR_DESC 	10		///4
#define VC_DMAC_RX_BUF_SIZE 2116	//Up to three 520 pbs	//1100	//600	//1080
#define VC_DMAC_TX_NR_DESC  15		//Should be large enough to accommodate all vc_lmac_tx_pkt_attach()

/*
#define VC_DMAC_RX_NR_DESC 25
#define VC_DMAC_RX_BUF_SIZE 800
#define VC_DMAC_TX_NR_DESC 16
*/

//#define VC_DMAC_TX_BUF_SIZE 512
typedef enum eLMAC_TX_DONE_IRQ_TYPE {
	LMAC_TX_KICK_BCN = 0x00,
	LMAC_TX_KICK_SOF = 0x01,
	LMAC_TX_KICK_SACK	= 0x02,
	LMAC_TX_KICK_ITNWC = 0x03,
	LMAC_TX_DONE_FINISH	= 0x04,
	LMAC_TX_GPIO_TIMEOUT = 0x05,
	LMAC_TX_FINISH_MOVE_BCN	= 0x06,
	LMAC_TX_FINISH_MOVE_NUNBCN = 0x07,
	LMAC_DSP_STUCK_ISSUE = 0x10,
} eLMAC_TX_DONE_IRQ_TYPE;

typedef enum eVC_LMAC_DMA_ISR{
	dmaISR_Txcmp		  = 0x00000001,
	dmaISR_Txunavail	= 0x00000002,
	dmaISR_Txerror		= 0x00000004,
	dmaISR_Txupdate		= 0x00000008,
	dmaISR_Rxcmp		  = 0x00000100,
	dmaISR_Rxunavail	= 0x00000200,
	dmaISR_Rxerror		= 0x00000400,
	dmaISR_Rxupdate		= 0x00000800,
} eVC_LMAC_DMA_ISR;

typedef enum eVC_CNMAC_ISR{/*1 0000 0000 0000*/
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
} eVC_CNMAC_ISR;

typedef enum eVC_DMAC_OWNER {
	VC_DMAC_OWNER_SW   = 0,    // the desc entry is free to be used by the software
	VC_DMAC_OWNER_DMAC = 1,    // the desc entry is currently in use by the DMA engine
} eVC_DMAC_OWNER;

typedef struct tVCMAC_REGISTER {// BASE=0x4001_1000
	tVC_MAC_CR 	        MAC_CR;			    //0x000	MAC Control Register
	uint32_t			      rsv04;			    //0x004
	uint32_t			      rsv08;			    //0x008
	uint32_t			      rsv0C;			    //0x00c
	tVC_CNMAC_CR 	      CNMAC_CR;		    //0x010	BBPLC MAC Control Register1
	tVC_CNMAC_CR2	      CNRXP_CR;		    //0x014	BBPLC MAC Control Register2 (TXP and RXP)
	uint32_t			      rsv18;			    //0x018
	uint32_t			      rsv1C;			    //0x01c
	tVC_CNMAC_IER 	    CNMAC_IER;	    //0x020	BBPLC MAC Interrupt Enable Register
	tVC_CNMAC_ISR		    CNMAC_ISR;	    //0x024	BBPLC MAC Interrupt Status Register
	uint32_t			      rsv28;			    //0X028
	uint32_t			      rsv2C;			    //0x02C
	tVC_CNRXF_SET1_SR1	CNRXF_SET1_SR1;	//0X030	BBPLC RX Address Filter Group1 Setting Register1
	tVC_CNRXF_SET1_SR2 	CNRXF_SET1_SR2;	//0X034	BBPLC RX Address Filter Group1 Setting Register2
	tVC_CNRXF_SET2_SR1 	CNRXF_SET2_SR1;	//0X038	BBPLC RX Address Filter Group2 Setting Register1
	tVC_CNRXF_SET2_SR2 	CNRXF_SET2_SR2;	//0x03c	BBPLC RX Address Filter Group2 Setting Register2
	tVC_CNRXF_SET2_MR1 	CNRXF_SET2_MR1;	//0x040	BBPLC RX Address Filter Group2 Mask Register1
	tVC_CNRXF_SET2_MR2 	CNRXF_SET2_MR2;	//0x044	BBPLC RX Address Filter Group2 Mask Register2
	tVC_CNRXF_STEI_SR 	CNRXF_STEI_SR;	//0x048	BBPLC RX Address Filter Source TEI Setting Register
	tVC_CNRXF_DT_SR		  CNRXF_DT_SR;	  //0x04C	BBPLC RX Address Filter Source DT Setting Register
	tVC_CNVCS_SR1		    CNVCS_SR1;		  //0x050	BBPLC VCS Setting Register1 (Time Tick)
	tVC_CNVCS_SR2		    CNVCS_SR2;		  //0x054	BBPLC VCS Setting Register2 (EIFS)
	tVC_CNVCS_SR3		    CNVCS_SR3;		  //0x058	BBPLC VCS Setting Register3 (CIFS)
	tVC_CNVCS_SR4		    CNVCS_SR4;		  //0x05C	BBPLC VCS Setting Register4 (RIFS)
	tVC_CNVCS_SR5		    CNVCS_SR5;		  //0x060	BBPLC VCS Setting Register5 (ACK Duration)
	tVC_CNVCS_SR6		    CNVCS_SR6;		  //0x064	BBPLC VCS Setting Register6 (ACK Tolerance)
	tVC_CNVCS_SR7		    CNVCS_SR7;		  //0x068	BBPLC VCS Setting Register7 (Waiting ACK)
	uint32_t			      rsv6C;			    //0x06c
	tVC_CNSCH_CR1		    CNSCH_CR1;		  //0x070	BBPLC Scheduler Control Register1
	tVC_CNSCH_TSR1		  CNSCH_TSR1;		  //0x074	TX Duration, CSMA enable,TDMA enable, TX requires ACK
	tVC_CNSCH_TSR2		  CNSCH_TSR2;		  //0x078	CSMA Back Off time tick
	tVC_CNSCH_TSR3		  CNSCH_TSR3;		  //0x07C	TDMA TX Time (by NTB)
	tVC_CNSCH_TSR4		  CNSCH_TSR4;		  //0x080	BBPLC Scheduler TX Setting Register4
	tVC_CNSCH_TSR5		  CNSCH_TSR5;		  //0x084	BBPLC Scheduler TX Setting Register5
	tVC_CNSCH_RTY_CR	  CNSCH_RTY_CR;	  //0x088	BBPLC Scheduler Retry Control Register [3]csr_dsp_abortpkt
	tVC_CNSCH_IR		    CNSCH_IR;		    //0x08C	BBPLC Scheduler Information Register
	tVC_CNRXARQ_SR		  CNRXARQ_SR;		  //0x090	BBPLC RX ARQ Setting Register
	uint32_t			      rsv94;			    //0x094
	uint32_t			      rsv98;			    //0x098
	uint32_t			      rsv9C;			    //0x09C
	tVC_CNTXARQ_IR		  CNTXARQ_IR;		  //0x0A0	BBPLC TX ARQ Information Register
	uint32_t			      rsvA4;			    //0x0A4
	uint32_t			      rsvA8;			    //0x0A8
	uint32_t			      rsvAC;			    //0x0AC
	tVC_CNRXP_SR1		    CNRXP_SR1;		  //0x0B0	BBPLC RX Processor Setting Register1
	tVC_CNRXP_SR2		    CNRXP_SR2;		  //0x0B4	BBPLC RX Processor Setting Register2
} tVCMAC_REGISTER;

typedef struct tVCMAC_DEBUG_REGISTER { // BASE=0x4001_1100
	tVC_CNTXP_DR1 		CNTXP_DR1;		//0x100	BBPLC MAC TX Processor Debug Register1
	tVC_CNTXP_DR2 		CNTXP_DR2;		//0x104	BBPLC MAC TX Processor Debug Register2
	tVC_CNTXP_DR3 		CNTXP_DR3;		//0x108	BBPLC MAC TX Processor Debug Register3
	tVC_CNTXP_MIB1 		CNTXP_MIB1;		//0x10C	BBPLC MAC TX Processor Debug Counter1
	uint32_t 			rsv10;			//0x110
	uint32_t 			rsv14;			//0x114
	uint32_t 			rsv18;			//0x118
	uint32_t 			rsv1C;			//0x11C
	tVC_CNRXP_DR1 		CNRXP_DR1;		//0x120	BBPLC MAC RX Processor Debug Register1
	tVC_CNRXP_DR2 		CNRXP_DR2;		//0x124	BBPLC MAC RX Processor Debug Register2
	tVC_CNRXP_DR3 		CNRXP_DR3;		//0x128	BBPLC MAC RX Processor Debug Register3
	tVC_CNRXP_MIB1 		CNRXP_MIB1;		//0x12C	BBPLC MAC RX Processor Debug Counter1
	uint32_t 			rsv30;			//0x130
	uint32_t 			rsv34;			//0x134
	uint32_t 			rsv38;			//0x138
	uint32_t 			rsv3C;			//0x13C
	tVC_CNRXF_DR1		CNRXF_DR1;		//0x140	BBPLC MAC RX Address Filter Debug Register1
	tVC_CNRXF_DR2		CNRXF_DR2;		//0x144	BBPLC MAC RX Address Filter Debug Register2
	tVC_CNRXF_MIB1		CNRXF_MIB1;		//0x148	BBPLC MAC RX Address Filter Debug Counter1
	tVC_CNRXF_MIB2		CNRXF_MIB2;		//0x14C	BBPLC MAC RX Address Filter Debug Counter2
	uint32_t			rsv50;			//0x150
	tVC_CNTXARQ_MIB1	CNTXARQ_MIB;	//0x154	BBPLC MAC TX ARQ Debug Counter1
	uint32_t 			rsv58;			//0x158
	uint32_t 			rsv5C;			//0x15c
	tVC_CNRXARQ_DR 		CNRXARQ_DR;		//0x160 BBPLC MAC RX ARQ Debug Register
	tVC_CNRXARQ_MIB1	CNRXARQ_MIB;	//0x164 BBPLC MAC RX ARQ Debug Counter1
	uint32_t			rsv68;			//0x168
	uint32_t			rsv6C;			//0x16C
	tVC_CNVCS_DR1		CNVCS_DR1;		//0x170 BBPLC MAC VCS Debug Register1
	tVC_CNVCS_DR2		CNVCS_DR2;		//0x174 BBPLC MAC VCS Debug Register2
	tVC_CNVCS_MIB1		CNVCS_MIB1;		//0x178 BBPLC MAC VCS Debug Counter1
	uint32_t			rsv7C;			//0x17C
	tVC_CNSCH_DR1		CNSCH_DR1;		//0x180 BBPLC MAC Scheduler Debug Register1
	uint32_t			rsv84;			//0x184
	tVC_CNSCH_MIB1		CNSCH_MIB1;		//0x188 BBPLC MAC Scheduler Debug Counter1
	tVC_CNSCH_MIB2		CNSCH_MIB2;		//0x18C BBPLC MAC Scheduler Debug Counter2
} tVCMAC_DEBUG_REGISTER;

typedef struct tVC_G3MAC_REG {
	tVC_HWMAC_DMA_CR CR;					// 0x00
	uint32_t rsv_04;						// 0x04
	uint32_t rsv_08;						// 0x08
	uint32_t rsv_0C;						// 0x0C
	tVC_HWMAC_DMA_TM_CR TM_CR;				// 0x0C
	tVC_HWMAC_DMA_TXE_CR TXE_CR;			// 0x10
	tVC_HWMAC_DMA_TXE_SR TXE_SR;			// 0x14
	tVC_HWMAC_DMA_TXE_KR TXE_KR;			// 0x18
	tVC_HWMAC_DMA_TXE_BA_SR TXE_BA_SR;		// 0x1C
	tVC_HWMAC_DMA_TXE_NA_SR TXE_NA_SR;		// 0x20
	tVC_HWMAC_DMA_TXE_CA_IR TXE_CA_IR;		// 0x24
	tVC_HWMAC_DMA_TXE_REQ_IR TXE_REQ_IR;	// 0x28
	uint32_t rsv_2C;						// 0x2C
	tVC_HWMAC_DMA_RXE_CR RXE_CR;			// 0x30
	tVC_HWMAC_DMA_RXE_SR RXE_SR;			// 0x34
	tVC_HWMAC_DMA_RXE_KR RXE_KR;			// 0x38
	tVC_HWMAC_DMA_RXE_BA_SR RXE_BA_SR;		// 0x3C
	tVC_HWMAC_DMA_RXE_NA_SR RXE_NA_SR;		// 0x40
	tVC_HWMAC_DMA_RXE_CA_IR RXE_CA_IR;		// 0x44
	tVC_HWMAC_DMA_RXE_REQ_IR RXE_REQ_IR;	// 0x48
	tVC_HWMAC_DMA_RXE_SA_IR RXE_SA_IR;		// 0X4C
	tVC_HWMAC_DMA_IER IER;					// 0x50
	tVC_HWMAC_DMA_ISR ISR;					// 0x54
	tVC_HWMAC_DMA_ISTR ISTR;				// 0x58
} tVC_G3MAC_REG;

typedef struct tVC_DMA_REG {         // BASE=0x4001_0000
	tVC_DMA_CR CR;                          // 0x00
	uint32_t rsv_04;                       // 0x04
	uint32_t rsv_08;                       // 0x08
	tVC_DMA_TM_CR TM_CR;                    // 0x0C
	tVC_DMA_TXE_CR TXE_CR;                  // 0x10
	tVC_DMA_TXE_SR TXE_SR;                  // 0x14
	tVC_DMA_TXE_KR TXE_KR;                  // 0x18
	tVC_DMA_TXE_BA_SR TXE_BA_SR;            // 0x1C
	tVC_DMA_TXE_NA_SR TXE_NA_SR;            // 0x20
	tVC_DMA_TXE_CA_IR TXE_CA_IR;            // 0x24
	tVC_DMA_TXE_REQ_IR TXE_REQ_IR;          // 0x28
	uint32_t rsv_2C;                       // 0x2C
	tVC_DMA_RXE_CR RXE_CR;                  // 0x30
	tVC_DMA_RXE_SR RXE_SR;                  // 0x34
	tVC_DMA_RXE_KR RXE_KR;                  // 0x38
	tVC_DMA_RXE_BA_SR RXE_BA_SR;            // 0x3C
	tVC_DMA_RXE_NA_SR RXE_NA_SR;            // 0x40
	tVC_DMA_RXE_CA_IR RXE_CA_IR;            // 0x44
	tVC_DMA_RXE_REQ_IR RXE_REQ_IR;          // 0x48
	tVC_DMA_RXE_SA_IR RXE_SA_IR;            // 0X4C
	tVC_DMA_IER IER;                        // 0x50
	tVC_DMA_ISR ISR;                        // 0x54
	tVC_DMA_ISTR ISTR;                      // 0x58
} tVC_DMA_REG;

typedef struct tVC_DMA_CTRL_DESC {
	union {
		struct {
			// rx-only fields
			uint32_t pkt_len		: 16;	// [15:0]   packet length
			uint32_t reserved_17	: 1;
			uint32_t ADD_MISS		: 1;
			uint32_t FCS			: 1;
			uint32_t reserved_20	: 8;
			// common fields between tx and rx
			uint32_t last			: 1;	// [27] last descriptor of the packet
			uint32_t first			: 1;	// [28] first descriptor of the packet
			uint32_t int_en		: 1;	// [29] interrupt enable for this descriptor
			uint32_t eor			: 1;	// [30] end of ring
			uint32_t owner			: 1;	// [31] the one who is locking on this descriptor (enum VTDMAC_OWNER)
		} fields;
		uint32_t value;
	};
} __attribute__((packed))tVC_DMA_CTRL_DESC;

typedef struct tVC_DMAC_DESC {
	tVC_DMA_CTRL_DESC ctrl;
	uint32_t ptr;
} __attribute__((packed))tVC_DMAC_DESC;

typedef enum tVC_LMAC_TX_CTRL_HDR_MODE{
	TX_CTRL_HDR_CNBPLC_MODE = 0x01,
	TX_CTRL_HDR_1901_MODE 	= 0x02,
	TX_CTRL_HDR_BYPASS_MODE = 0x04,	
} tVC_LMAC_TX_CTRL_HDR_MODE;

typedef enum tVC_LMAC_TX_CTRL_HDR_TYPE{
	TX_CTRL_HDR_CN_TX_TYPE		=1,
	TX_CTRL_HDR_CN_RX_TYPE		=2,
	TX_CTRL_HDR_G3_TX_TYPE		=3,
	TX_CTRL_HDR_G3_RX_TYPE		=4,
	TX_CTRL_HDR_BBP_TX_TYPE		=5,
	TX_CTRL_HDR_BBP_RX_TYPE		=6,
	TX_CTRL_HDR_BEACON_TYPE		=7,
	TX_CTRL_HDR_PHY_TEST_TYPE	=8,
} tVC_LMAC_TX_CTRL_HDR_TYPE;

typedef struct tVC_PLC_CTRL  {
	union {
		struct {
			uint32_t 	mode 		: 4;  // 
			uint32_t	type 		: 4;  // 1=AES, 3=SM, 5=CRC
			uint32_t 	config		: 8;  // (rw) Receive DMA Enable
			uint32_t 	head_len	: 16;
		} fields;
		uint32_t value;
	};
} __attribute__((packed)) tVC_PLC_CTRL;

typedef struct tVC_LMAC_CTRL_MAC{
	tVC_PLC_CTRL ctrl;	 
	uint32_t 	seq 		:8; 
	uint32_t 	reserved	:8;
	uint32_t 	pkt_len		:16;
	uint32_t 	dur;
} __attribute__((packed)) tVC_LMAC_CTRL_MAC;

typedef struct tVC_LMAC_TX_CTRL_HEADER {	
	tVC_PLC_CTRL ctrl;
	
	uint32_t 	seq			:8;
	uint32_t 	rsv0		:8;
	uint32_t 	pktLen		:16;
	
	uint32_t 	DT			:3;
	uint32_t 	rsv1		:1;
	uint32_t 	PBNum		:3;
	uint32_t 	rsv2		:1;
	uint32_t 	TMI			:4;
	uint32_t 	TMIType		:1;
	uint32_t 	BandPlan	:1;
	uint32_t 	rsv3		:2;
	uint32_t 	rsv4		:16;
	
	uint32_t bcnNTB		:32;
} __attribute__((packed)) tVC_LMAC_TX_CTRL_HEADER;

typedef struct tVC_LMAC_RX_CTRL_HEADER {
	uint32_t type			:4;
	uint32_t mode			:4;
	uint32_t config		:8;
	uint32_t chdrLen		:16;

	uint32_t pbcsStatus	:8;
	uint32_t linkQuality	:8;
	uint32_t pktLen		:16;

	uint32_t bcnFnCurrent	:8;
	uint32_t rxDuration	:24;

	uint32_t recNTB		:32;

	uint32_t RSSI			:8;
	uint32_t PPM			:8;
	uint32_t FNPLLK		:16;

} __attribute__((packed)) tVC_LMAC_RX_CTRL_HEADER;

typedef struct tVC_DMAC_payload {
  void *dma_ptr;
  uint16_t dma_size;
} __attribute__((packed)) tVC_DMAC_payload;

typedef struct tVC_DMAC_PACKET{
	tVC_DMAC_payload pld[VC_DMAC_TX_NR_DESC];
	uint8_t nr_desc;
} tVC_DMAC_PACKET;

typedef struct tVC_BBP_RX_statistics {
	uint32_t rxMibCnt;
	uint32_t preamb_det_cnt;
	uint32_t rx_data_fch_correct_cnt;
	uint32_t rx_data_fch_error_cnt;
	uint32_t rx_becn_correct_cnt;
	uint32_t rx_becn_error_cnt;
	uint32_t rx_sof_correct_cnt;
	uint32_t rx_sof_error_cnt;
	uint32_t rx_sack_correct_cnt;
	uint32_t rx_sack_error_cnt;  
	uint32_t rx_itnwc_correct_cnt;
	uint32_t rx_itnwc_error_cnt;
	uint32_t syncp_sym_cnt; 
	uint32_t syncm_det_flag;
} tVC_BBP_RX_statistics;

typedef struct tVC_BBP_TX_statistics{ 
  uint32_t rxMibCnt;
  uint32_t tx_mac_send_data_cnt;
  uint32_t tx_mac_send_ack_cnt;
  uint32_t tx_mac_send_sof_cnt;
  uint32_t tx_mac_send_nwc_cnt;
  uint32_t tx_mac_send_beacon_cnt;
  uint32_t tx_mac_abort_data_cnt;
  uint32_t tx_mac_abort_sack_cnt;
  uint32_t tx_phy_abort_beacon_cnt;
  uint32_t tx_beacon_ntb;
} tVC_BBP_TX_statistics;

typedef struct tVC_BBP_freq_offset{ 
	uint32_t sign;
	uint32_t offset;
} tVC_BBP_freq_offset;

extern void vc_lmac_tx_pkt_init(tVC_DMAC_PACKET *pkt);
extern void vc_lmac_tx_pkt_attach(tVC_DMAC_PACKET *pkt,void *pData, uint16_t pDataLen);
extern void vc_lmac_send_tx_pkt_to_dma(tVC_DMAC_PACKET *pkt);

#ifdef __cplusplus
}
#endif

#endif // VC_MAC_HWMAC_IF_H
