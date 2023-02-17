#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include "hplc.h"
#include "hplc_bbp.h"
#include "hplc_dma.h"
#include "hplc_lmac.h"
#include "hplc_tx.h"
#include "hplc_rx.h"

//static vc_lmac_pkt_sym_mapping gMapSymTMI_ALL = {
vc_lmac_pkt_sym_mapping gMapSymTMI_ALL = {
	BPLC_BAND_0, BPLC_TMI, 4096, 5928, 5152, {
		{ 520, 2, 4, 8 }, { 520, 2, 2, 8 }, { 136, 2, 5, 10 }, { 136, 1, 11, 11 }, { 136, 1, 7, 14 },
		{ 136, 2, 11, 11 }, { 136, 2, 7, 14 }, { 520, 1, 7, 14 }, { 520, 1, 4, 8 }, { 520, 2, 7, 14 },
		{ 520, 1, 2, 8 }, { 264, 2, 7, 14 }, { 264, 1, 7, 14 }, { 72, 2, 7, 14 }, { 72, 1, 7, 14 }
	}
};
//static vc_lmac_pkt_sym_mapping gMapSymTMI_ALL_E = {
vc_lmac_pkt_sym_mapping gMapSymTMI_ALL_E = {
	BPLC_BAND_0, BPLC_E_TMI, 4096, 5928, 5152, {
		{ 0, 0, 0, 0 }, { 520, 4, 1, 1 }, { 520, 4, 2, 8 }, { 520, 4, 1, 1 }, { 520, 4, 2, 8 },
		{ 520, 4, 4, 8 }, { 520, 2, 1, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 136, 4, 5, 10 },
		{ 136, 2, 2, 8 }, { 136, 4, 2, 8 }, { 136, 2, 1, 1 }, { 136, 4, 1, 1 }
	}
};

//uint8_t vc_lmac_sequenceNum = 0;
uint8_t ctrlSeqNum = 0;

volatile uint8_t plc_m_txp_done = 0;
volatile uint8_t plc_m_csma_success = 0;
volatile uint8_t plc_m_csma_fail = 0;
volatile uint8_t plc_m_csma_abort = 0;
volatile uint8_t plc_m_csma_get_para = 0;
volatile uint8_t plc_m_dsp_abortpkt = 0;
volatile uint8_t plc_m_tx_info_start = 0;
volatile uint8_t plc_m_tx_info_finish = 0;

volatile uint32_t plc_data_start_delay_cnt = 0;
volatile uint32_t plc_ack_start_delay_cnt = 0;

uint32_t pLen = 0;
uint8_t dummyTxPbcs[LMAC_SIZE_OF_PBCS_IN_PB] = {0xAB, 0xAB, 0xAB};
uint8_t zeroContent[520];	/*	For padding usage	*/

volatile uint32_t plc_tx_delay_start_counter = 0;
volatile uint32_t plc_tx_delay_finish_counter = 0;
volatile uint32_t plc_ack_delay_start_counter = 0;

tVC_LMAC_TX_CTRL_HEADER gTxCtrlHdr;
tCN_SOF_FC	gTxCnSofFc;
extern tVC_DMAC_DESC g_dmaTxDesc[VC_DMAC_TX_NR_DESC];


uint8_t vc_lmac_incrase_ctrl_seq_num()
{
	ctrlSeqNum++;
	return ctrlSeqNum;
}


void vc_lmac_tx_bbp_pkt_f_cmd(bbpRawCmdStruct *pBbpRawCmd)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	tVC_DMAC_PACKET pkt;
	uint16_t	ctrlLen = 0;
//	uint16_t tmpLen=0;
	uint32_t bbpIsIdle =0;

	bbpIsIdle = vc_phy_check_idle();
	
	if(bbpIsIdle){
		memset(&gTxCtrlHdr, 0x00, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		gTxCtrlHdr.ctrl.fields.type = TX_CTRL_HDR_BBP_TX_TYPE;
    gTxCtrlHdr.ctrl.fields.mode = TX_CTRL_HDR_CNBPLC_MODE;
		ctrlLen = sizeof(tVC_LMAC_TX_CTRL_HEADER);
		gTxCtrlHdr.ctrl.fields.head_len = VC_SWAP_16(ctrlLen);
		gTxCtrlHdr.seq = vc_lmac_incrase_ctrl_seq_num();
		gTxCtrlHdr.pktLen = VC_SWAP_16(pBbpRawCmd->bbpCmdLen);
		gTxCtrlHdr.PBNum = 0;
		gTxCtrlHdr.DT = 0;
		gTxCtrlHdr.TMI = 0;
//		tmpLen = pBbpRawCmd->bbpCmdLen;
		vc_lmac_tx_pkt_init(&pkt);
		vc_lmac_tx_pkt_attach(&pkt, &gTxCtrlHdr, ctrlLen);
		vc_lmac_tx_pkt_attach(&pkt, &pBbpRawCmd->bbpCmd[0], pBbpRawCmd->bbpCmdLen);
		//VMUST(LMAC_PRINT, "#DT:",&pBbpRawCmd->bbpCmd[0], pBbpRawCmd->bbpCmdLen);
		if(pBbpRawCmd->bandSetting){
			gLMAC->lmacBand = pBbpRawCmd->band;
		}
		if(pBbpRawCmd->toneMaskSetting){
			gLMAC->lmacToneMask = pBbpRawCmd->toneMask;
		}
		vc_lmac_send_tx_pkt_to_dma(&pkt);
	}else{
		printf("<- bbp busy!!");
	}
}


void vc_lmac_send_tx_pkt_to_dma(tVC_DMAC_PACKET *pkt)
{
	//LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	uint8_t i;

	for(i=0;i<pkt->nr_desc;i++){
		g_dmaTxDesc[i].ctrl.fields.last = 0;
		g_dmaTxDesc[i].ctrl.fields.first = 0;
		g_dmaTxDesc[i].ctrl.fields.int_en = 0;
		g_dmaTxDesc[i].ctrl.fields.eor = 0;
		g_dmaTxDesc[i].ctrl.fields.owner = VC_DMAC_OWNER_DMAC;

		if(i == 0){
			g_dmaTxDesc[i].ctrl.fields.first = 1;
		}
		if(i+1 == pkt->nr_desc ){
			g_dmaTxDesc[i].ctrl.fields.int_en = 1;
			g_dmaTxDesc[i].ctrl.fields.last = 1;
		}
		if(i+1 == VC_DMAC_TX_NR_DESC){
			g_dmaTxDesc[i].ctrl.fields.eor = 1;
		}
		g_dmaTxDesc[i].ctrl.fields.pkt_len = pkt->pld[i].dma_size;
		g_dmaTxDesc[i].ptr = (uint32_t)pkt->pld[i].dma_ptr;

		if(g_dmaTxDesc[i].ctrl.fields.pkt_len <= 0){
			//printf("[DMA] Warning!TxDmaLen is 0!!");
			printf("[DMA] Warning!TxDmaLen is 0!!, i = %d, len = %d", i, g_dmaTxDesc[i].ctrl.fields.pkt_len);
		}
	}

	dmaReg->TXE_BA_SR.value = (uint32_t) & g_dmaTxDesc[0];
	LMAC_KICK_TX_DMA();
}


uint16_t vc_lmac_cal_ofdma_symbol_number(uint8_t eTmi, uint8_t iTmi, uint16_t fcToneNum, uint8_t toneMaskNum)
{
	uint16_t usedCarrierNum = 0;
	uint16_t carrNumPerGroup = 0;
	uint16_t ofdmaNum = 0;
	if (eTmi) {
		usedCarrierNum =
			((fcToneNum - toneMaskNum) / gMapSymTMI_ALL_E.InfoTMI[eTmi].intNum) * gMapSymTMI_ALL_E.InfoTMI[eTmi].intNum;
		carrNumPerGroup = usedCarrierNum / gMapSymTMI_ALL_E.InfoTMI[eTmi].copyNum;
		if (eTmi == 1 || eTmi == 2) {
			ofdmaNum = (((((gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize * 8 * 18) / 16) - 1) / carrNumPerGroup) / gMapSymTMI_ALL_E.InfoTMI[eTmi].BPC) + 1;
		} else {
			ofdmaNum = ((((gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize * 8 * 2) - 1) / carrNumPerGroup) / gMapSymTMI_ALL_E.InfoTMI[eTmi].BPC) + 1;
		}
	} else {
		usedCarrierNum =
			((fcToneNum - toneMaskNum) / gMapSymTMI_ALL.InfoTMI[iTmi].intNum) * gMapSymTMI_ALL.InfoTMI[iTmi].intNum;
		carrNumPerGroup = usedCarrierNum / gMapSymTMI_ALL.InfoTMI[iTmi].copyNum;
		ofdmaNum = ((((gMapSymTMI_ALL.InfoTMI[iTmi].PbSize * 8 * 2) - 1) / carrNumPerGroup) / gMapSymTMI_ALL.InfoTMI[iTmi].BPC) + 1;
	}
	return ofdmaNum;
}

uint8_t vc_lmac_get_pkt_info_by_tmi(
	vc_lmac_band_plan band,
	uint8_t pbNum,
	uint8_t eTmi,
	uint8_t iTmi,
	uint16_t *pktLen,
	uint16_t *FL,
	uint16_t *symNum,
	uint16_t *ackDur,
	uint16_t *pmbDur,
	uint16_t *fcDur)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	uint16_t pPktPer = 0;
	uint16_t pPktLen = 0;
	//uint16_t pFL = 0;
	uint16_t pSymNum = 0;
	uint16_t pAckDur = 0;
	uint16_t pPktTime = 0;
	uint8_t retval = 0;
	uint16_t calSymboNum = 0;
	uint8_t toneMask = 0;
	uint16_t pPmbDur = 0;		//MMM
	uint16_t pFcDur = 0;		//MMM

	//pbNum = 1;

	switch (band)
	{
		case BPLC_BAND_0: {
			if (gLMAC->lmacToneMask != 0) {
				toneMask = 40;
			}
			if (eTmi == 0) {
				pPmbDur = gMapSymTMI_ALL.pmbTime * 13 / 100;		//MMM
				pFcDur = gMapSymTMI_ALL.fcTime * 4 / 100;			//MMM
				pAckDur = ((gMapSymTMI_ALL.pmbTime * 13) + (gMapSymTMI_ALL.fcTime * 4)) / 100;
				pPktLen = gMapSymTMI_ALL.InfoTMI[iTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL.fcTime * 2) / 100;
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 411, toneMask);
				pSymNum = calSymboNum;
				pPktTime = (gMapSymTMI_ALL.pldTime * pbNum * pSymNum) / 100;
			} else if (eTmi > 0) {
				pPmbDur = gMapSymTMI_ALL_E.pmbTime * 13 / 100;		//MMM
				pFcDur = gMapSymTMI_ALL_E.fcTime * 4 / 100;			//MMM
				pAckDur = ((gMapSymTMI_ALL_E.pmbTime * 13) + (gMapSymTMI_ALL_E.fcTime * 4)) / 100;
				pPktLen = gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL_E.fcTime * 2) / 100;
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 411, toneMask);
				pSymNum = calSymboNum;
				pPktTime = (gMapSymTMI_ALL_E.pldTime * pbNum * pSymNum) / 100;
			}
			break;
		}

		case BPLC_BAND_1: {
			if (gLMAC->lmacToneMask != 0) {
				toneMask = 5;
			}
			if (eTmi == 0) {
				pPmbDur = gMapSymTMI_ALL.pmbTime * 13 / 100;		//MMM
				pFcDur = gMapSymTMI_ALL.fcTime * 12 / 100;			//MMM
				pAckDur = ((gMapSymTMI_ALL.pmbTime * 13) + (gMapSymTMI_ALL.fcTime * 12)) / 100;
				pPktLen = gMapSymTMI_ALL.InfoTMI[iTmi].PbSize;
				pPktPer = ((gMapSymTMI_ALL.fcTime * 2) / 100);
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 131, toneMask);
				pSymNum = calSymboNum;
				pPktTime = (gMapSymTMI_ALL.pldTime * pbNum * pSymNum) / 100;
			} else if (eTmi > 0) {
				pPmbDur = gMapSymTMI_ALL_E.pmbTime * 13 / 100;		//MMM
				pFcDur = gMapSymTMI_ALL_E.fcTime * 12 / 100;		//MMM
				pAckDur = ((gMapSymTMI_ALL_E.pmbTime * 13) + (gMapSymTMI_ALL_E.fcTime * 12)) / 100;
				pPktLen = gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL_E.fcTime * 2) / 100;
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 131, toneMask);
				pSymNum = calSymboNum;
				pPktTime = (gMapSymTMI_ALL_E.pldTime * pbNum * pSymNum) / 100;
			}
			break;
		}

		case BPLC_BAND_2: {
			if (gLMAC->lmacToneMask != 0) {
				toneMask = 5;
			}
			if (eTmi == 0) {
				pPmbDur = gMapSymTMI_ALL.pmbTime * 13 / 100;		//MMM
				pFcDur = gMapSymTMI_ALL.fcTime * 12 / 100;			//MMM
				pAckDur = ((gMapSymTMI_ALL.pmbTime * 13) + (gMapSymTMI_ALL.fcTime * 12)) / 100;
				pPktLen = gMapSymTMI_ALL.InfoTMI[iTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL.fcTime * 2) / 100;
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 89, toneMask);
				pSymNum = calSymboNum;
				pPktTime = (gMapSymTMI_ALL.pldTime * pbNum * pSymNum) / 100;
			} else if (eTmi > 0) {
				pPmbDur = gMapSymTMI_ALL_E.pmbTime * 13 / 100;		//MMM
				pFcDur = gMapSymTMI_ALL_E.fcTime * 12 / 100;		//MMM
				pAckDur = ((gMapSymTMI_ALL_E.pmbTime * 13) + (gMapSymTMI_ALL_E.fcTime * 12)) / 100;
				pPktLen = gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL_E.fcTime * 2) / 100;
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 89, toneMask);
				pSymNum = calSymboNum;
				pPktTime = (gMapSymTMI_ALL_E.pldTime * pbNum * pSymNum) / 100;
			}
			break;
		}

		case BPLC_BAND_3: {
			if (gLMAC->lmacToneMask != 0) {
				toneMask = 49;
			}
			if (eTmi == 0) {
				pPmbDur = gMapSymTMI_ALL.pmbTime * 13 / 100;		//MMM
				pFcDur = gMapSymTMI_ALL.fcTime * 12 / 100;			//MMM
				pAckDur = ((gMapSymTMI_ALL.pmbTime * 13) + (gMapSymTMI_ALL.fcTime * 12)) / 100;
				pPktLen = gMapSymTMI_ALL.InfoTMI[iTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL.fcTime * 2) / 100;
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 49, toneMask);
				pSymNum = calSymboNum;
				pPktTime = (gMapSymTMI_ALL.pldTime * pbNum * pSymNum) / 100;
			} else if (eTmi > 0) {
				pPmbDur = gMapSymTMI_ALL_E.pmbTime * 13 / 100;		//MMM
				pFcDur = gMapSymTMI_ALL_E.fcTime * 12 / 100;		//MMM
				pAckDur = ((gMapSymTMI_ALL_E.pmbTime * 13) + (gMapSymTMI_ALL_E.fcTime * 12)) / 100;
				pPktLen = gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL_E.fcTime * 2) / 100;
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 49, toneMask);
				pSymNum = calSymboNum;
				pPktTime = (gMapSymTMI_ALL_E.pldTime * pbNum * pSymNum) / 100;
			}
			break;
		}
	}
	*(pktLen) = pbNum * pPktLen;
	*(FL) = (pPktPer + pPktTime + LMAC_CIFS) / 10;
	*(symNum) = (pSymNum);
	*(ackDur) = (pAckDur + LMAC_RIFS) / 10;
	*(pmbDur) = pPmbDur / 10;
	*(fcDur) = pFcDur/10;
	if (pPktLen != 0 && pSymNum != 0) {
		retval = 1;
	}
	return retval;
}

void vc_lmac_fill_tx_desc(
	tVC_LMAC_TX_CTRL_HEADER *pTxCtrlHdr,
	uint8_t pbType, 
	uint8_t extTMI,
	uint8_t tmi, 
	uint16_t pktLen, 
	uint8_t pbNum,
	uint32_t NTB)
{
	uint16_t tmpLen=0;

	if (pbType == BEACON_F) {
		pTxCtrlHdr->ctrl.fields.type = TX_CTRL_HDR_BEACON_TYPE;
	} else if (pbType == PHY_TEST) {
		pTxCtrlHdr->ctrl.fields.type = TX_CTRL_HDR_PHY_TEST_TYPE;
	} else {
		pTxCtrlHdr->ctrl.fields.type = TX_CTRL_HDR_CN_TX_TYPE;
	}
	pTxCtrlHdr->bcnNTB = NTB + 12500;
	pTxCtrlHdr->ctrl.fields.mode = TX_CTRL_HDR_CNBPLC_MODE;
	pTxCtrlHdr->ctrl.fields.head_len = VC_SWAP_16(sizeof(tVC_LMAC_TX_CTRL_HEADER));
	pTxCtrlHdr->seq = vc_lmac_incrase_ctrl_seq_num();
	tmpLen = sizeof(tCN_SOF_FC) + pktLen;
	pTxCtrlHdr->pktLen = VC_SWAP_16(tmpLen);
	pTxCtrlHdr->PBNum = pbNum;
	pTxCtrlHdr->DT = pbType;
	if(extTMI == 0){
		pTxCtrlHdr->TMI = tmi;
		pTxCtrlHdr->TMIType = 0;
	}else{
		pTxCtrlHdr->TMI = extTMI;
		pTxCtrlHdr->TMIType = 1;
	}	
}

void vc_lmac_fill_tx_fc(
	tCN_SOF_FC *pTxCnFc, 
	uint32_t wNID, 
	uint16_t wSTEI, 
	uint16_t wDTEI,
	uint16_t FL,
	uint8_t tmi,
	uint8_t etmi,
	uint8_t pbNum,
	uint16_t symNum,
	uint8_t bcastFlag,
	uint8_t resendFlag)
{
//	uint16_t sym_num[15]={41, 21, 14, 59, 38, 30, 19, 144, 82, 72, 41, 37, 73, 10, 20};
	pTxCnFc->delType=SOF_F;	
	pTxCnFc->NID = WISUN_NID;
	pTxCnFc->SofVarSTEI = wSTEI;
	pTxCnFc->SofVarDTEI = wDTEI;
	//vc_lmac_cfg_arq_MyTEI(wSTEI);
	pTxCnFc->SofVarLID = 0x00;
	pTxCnFc->SofVarBcastFlag = bcastFlag;
	pTxCnFc->SofVarResendFlag = resendFlag;
	//pTxCnFc->SofVarFL = FL - 10;
	pTxCnFc->SofVarFL = FL;
	pTxCnFc->SofVarPBCount = pbNum;
	pTxCnFc->SofVarTMI = tmi;
	pTxCnFc->SofVarExtTMI = etmi;
	pTxCnFc->SofVarSymbolNum = symNum * pbNum;
}


void vc_lmac_cfg_hw_csma_retry(uint32_t backoffTime)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;	
	if(backoffTime <= LMAC_CSMA_DEFAULT_PERIOD){
		backoffTime = LMAC_CSMA_DEFAULT_PERIOD;
	}
	#if (LMAC_AUTO_CFG_CSMA)
	cnMacReg->CNSCH_TSR2.value = backoffTime;
	#endif
	//VDEBUG(LMAC_PRINT, "#CSMA:backOff->%d", cnMacReg->CNSCH_TSR2);
	cnMacReg->CNSCH_RTY_CR.value = 0x04;
}

void vc_lmac_init_csma(
	eVC_SACK_TYPE ackNeed, 
	eVC_CSMA_PKT_TYPE pktType, 
	eVC_CSMA_FROMQ_TYPE fromQ,
	uint32_t txDuration, 	
	uint16_t ackDur)
{
	//volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	//uint32_t value = 0x00;
	uint32_t backoff_period;
	//VINFO(LMAC_PRINT,"#csma_init");
	
	gLMAC->lmacCsma.sackNeed = ackNeed;
	gLMAC->lmacCsma.pktType = pktType;
	gLMAC->lmacCsma.fromQ = fromQ;
#if (LMAC_AUTO_CFG_CSMA)
	cnMacReg->CNSCH_TSR1 = 0x0;
	if (ackNeed) {
		value |= 0x11000000;
	} else {
		value |= 0x01000000;
	}
	//VINFO(LMAC_PRINT,"Txdur:%d", txDuration);
	if (txDuration == 0) {
		value |= 0x00006912;
	} else {
		if (ackNeed) {
			value |= (txDuration * 10) +		/*FL*/
				(ackDur * 10);				/*SACK*/
		} else {
			value |= (txDuration * 10);		/*FL*/
		}
	}
	//cnMacReg->CNVCS_SR5 = ackDur;
	cnMacReg->CNSCH_TSR1.value = value;
#endif

	//printf("ackNeed = %d, txDuration = %ld, ackDur = %d, value = %ld\n", ackNeed, txDuration, ackDur, value);

#if 0 //Curently used a fixed value
	lmac_csma_backoff_exponent = gLMAC->lmacCsma.minBE;
	backoff_period = (vc_lmac_random() % ((1 << lmac_csma_backoff_exponent) - 1)) * gLMAC->lmacCsma.period;
	vc_lmac_cfg_hw_csma_retry(backoff_period);
	lmac_num_of_backoffs = 1;
#else	
	backoff_period = LMAC_CSMA_DEFAULT_PERIOD;		//us	//MMM
	vc_lmac_cfg_hw_csma_retry(backoff_period);	//comment off by MMM

#endif

}

uint32_t vc_lmac_check_vcs_idle(void)
{
#if 0
	volatile uint32_t *addr1170 = (volatile uint32_t *)0x40011170; /* CNVCS_DR1 */
	uint32_t vcsDebug;
	uint8_t vcsIdle;
	vcsDebug = *(addr1170);
	if((vcsDebug & 0x0F) > 0){
		vcsIdle = 0;
	}else{
		vcsIdle = 1;
	}
	return vcsIdle;
#endif
	volatile tVCMAC_DEBUG_REGISTER *cnMacDebugReg = (volatile tVCMAC_DEBUG_REGISTER *)VC_MAC_CN_DEBUG;
	uint8_t vcsDebug = cnMacDebugReg->CNVCS_DR1.fields.csr_cnvcs_cs;
	if(vcsDebug > 0){
		return 0;
	}else{
		return 1;
	}
}

/*	To decide the proper tmi, pbNum, pbSize and waiting time (for the tx) simply according to the payload length	*/
/*	Return 0 if len is within valid range; otherwise return error													*/
//int vc_lmac_det_tmi_pbNum_pbSize_waitNTB(const uint16_t len, uint8_t *targetTmi, uint8_t *targetPbNum, uint16_t *targetPbSize, uint32_t *targetWaitNTB)
int vc_lmac_det_tmi_pbNum_pbSize(const uint16_t len, uint8_t *targetTmi, uint8_t *targetPbNum, uint16_t *targetPbSize)

{
	/*	For pbSize of 72, 136, 264 and 520, we use tmi 14, 4, 12 and 7, respectively		*/
	/*	These tmi values are chosen due to they have enough copynum to sustain low PER		*/

	uint8_t iTmi;
	uint16_t pbSize;
	uint8_t pbNum;
#if 0
	uint8_t eTmi;
	uint8_t toneMask;
	uint32_t pmbDur;
	uint32_t fcDur;	
	uint32_t pktPer;
	uint16_t symNum;
	uint32_t pktTime;

	toneMask = 0;
	eTmi = 0;
#endif
	/*	The following mapping is based on an off-line table, BPLC_TMI_table created elsewhere	*/
	if(len == 0){
		printf("HPLC payload size zero. Len = (%u)\n", len);
		return -1;	//The error code to be defined
	}else if(len < 66){
		iTmi = 14;
		pbSize = LMAC_PB_SIZE_72;
		pbNum = 1;
	}else if(len < 130){
		iTmi = 4;
		pbSize = LMAC_PB_SIZE_136;
		pbNum = 1;
	}else if(len < 135){
		iTmi = 14;
		pbSize = LMAC_PB_SIZE_72;
		pbNum = 2;
	}else if(len < 204){
		iTmi = 14;
		pbSize = LMAC_PB_SIZE_72;
		pbNum = 3;
	}else if(len < 258){
		iTmi = 12;
		pbSize = LMAC_PB_SIZE_264;
		pbNum = 1;
	}else if(len < 263){
		iTmi = 4;
		pbSize = LMAC_PB_SIZE_136;
		pbNum = 2;
	}else if(len < 273){
		iTmi = 14;
		pbSize = LMAC_PB_SIZE_72;
		pbNum = 4;
	}else if(len < 396){
		iTmi = 4;
		pbSize = LMAC_PB_SIZE_136;
		pbNum = 3;
	}else if(len < 514){
		iTmi = 7;
		pbSize = LMAC_PB_SIZE_520;
		pbNum = 1;
	}else if(len < 519){
		iTmi = 12;
		pbSize = LMAC_PB_SIZE_264;
		pbNum = 2;
	}else if(len < 529){
		iTmi = 4;
		pbSize = LMAC_PB_SIZE_136;
		pbNum = 4;
	}else if(len < 780){
		iTmi = 12;
		pbSize = LMAC_PB_SIZE_264;
		pbNum = 3;
	}else if(len < 1031){
		iTmi = 7;
		pbSize = LMAC_PB_SIZE_520;
		pbNum = 2;
	}else if(len < 1041){
		iTmi = 12;
		pbSize = LMAC_PB_SIZE_264;
		pbNum = 4;
	}else if(len < 1548){
		iTmi = 7;
		pbSize = LMAC_PB_SIZE_520;
		pbNum = 3;
	}else if(len < 2065){
		iTmi = 7;
		pbSize = LMAC_PB_SIZE_520;
		pbNum = 4;
	}else{
		printf("HPLC payload size too big. Len = (%u)\n", len);
		return -1;	//The error code to be defined
	}
	*targetTmi = iTmi;
	*targetPbNum = pbNum;
	*targetPbSize = pbSize;
#if 0
	symNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 131, toneMask);
	//pbSize = gMapSymTMI_ALL.InfoTMI[iTmi].PbSize;
	//if(len <= pbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - LMAC_SIZE_OF_PBCS_IN_PB){
	//	pbNum = 1;
	//}else if(len <= 2 * pbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - 2 * LMAC_SIZE_OF_PBCS_IN_PB){
	//	pbNum = 2;
	//}else if(len <= 3 * pbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - 3 * LMAC_SIZE_OF_PBCS_IN_PB){
	//	printf("HPLC payload size too big. Len = (%ld)\n", len);
	//	return -1;
	//}else if(len <= 4 * pbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - 4 * LMAC_SIZE_OF_PBCS_IN_PB){
	//	printf("HPLC payload size too big. Len = (%ld)\n", len);
	//	return -1;
	//}else{
	//	printf("HPLC payload size too big. Len = (%ld)\n", len);
	//	return -1;
	//}
	pmbDur = gMapSymTMI_ALL.pmbTime * 13;
	fcDur = gMapSymTMI_ALL.fcTime * 12;
	pktPer = (gMapSymTMI_ALL.fcTime * 2);
	pktTime = (gMapSymTMI_ALL.pldTime * pbNum * symNum);


	*targetWaitNTB = (pmbDur + fcDur + pktPer + pktTime) * 25 / 100 ;

	//printf("len = %lu, tmi = %d, pbNum = %d, pbSize=%d, pmbDur = %lu, fcDur = %lu, pktPer = %lu, pktTime = %lu\n",
	//			len, iTmi, pbNum, pbSize, pmbDur, fcDur, pktPer, pktTime);
#endif
	return 0;
}

/*	This function requires customization in HPLC firmware for wisun dual mode. The packet	*/
/*	will be sent the same way as beacon were sent in HPLC, except that the NTB is ignored	*/
/*	and the packet is transmitted ASAP. 													*/

int vc_lmac_tx_sof_pkt_f_cmd_txdata_asap(uint16_t DTEI, uint8_t extTmi, uint8_t tmi, uint8_t *pTxData,
										uint16_t dataLen, uint8_t vcPbNum, uint16_t vcPbSize, uint32_t startNTB, uint8_t ack_needed, int* rfstat)
{

	//LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	tVC_DMAC_PACKET pkt;

	uint16_t tx_len = 0;
	uint16_t FL = 0;
	uint16_t symNum = 0;
	uint16_t ackDur = 0;
	uint16_t pmbDur = 0;
	uint16_t fcDur = 0;
	uint32_t wNID = WISUN_NID;
	uint16_t wSTEI = 0x0000;
	uint16_t wDTEI = WISUN_TEI;//0x0FEF;
	/* Note that this is a self-defined address to distinguish from the broadcast address defined in HPLC spec.	*/
	uint32_t t0, t1;
	uint32_t vcs_remain_time = 0;
	uint8_t isDelayed = 0;
	uint16_t lenZeroPadding;	//length of zero padding at the end of last pb
	uint32_t vcWaitNTB = 0;
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	volatile tVCMAC_DEBUG_REGISTER *cnMacDebugReg = (volatile tVCMAC_DEBUG_REGISTER *)VC_MAC_CN_DEBUG;
#if 0
	t0 = t1 = vc_phy_get_ntb();
	isVcsIdle = vc_lmac_check_vcs_idle();
	isBbpIdle = vc_phy_check_idle();
	while(!isVcsIdle || !isBbpIdle){
		//rxTime[rxInd] = vc_phy_get_ntb();
		//rxReg170[rxInd] = *(volatile uint32_t *)0x40011170;  /* CNVCS_DR1	*/
		//rxReg174[rxInd] = *(volatile uint32_t *)0x40011174;  /* CNVCS_DR2	*/
		//rxReg1D0[rxInd] = *(volatile uint32_t *)0x400111D0;  /* PHY_IR1		*/
		//isVcsIdle = (rxReg170[rxInd] & 0x0F) > 0 ? 0 : 1;	//vc_lmac_check_vcs_idle();
		//isBbpIdle = (rxReg1D0[rxInd] & 0x04) > 0 ? 1 : 0;	//vc_phy_check_idle();
		//rxInd++;			
		t1 = vc_phy_get_ntb();
		if((t1 + 0xffffffffUL - t0 + 1) > 0.2 * 25000){
			if(!isDelayed){
				isDelayed = 1;
				printf("!! Wait idle: t0 = %lu us, t1 = %lu us\n", t0/25, t1/25);
				return HPLC_TX_BUSY;
			}
		}
		isVcsIdle = vc_lmac_check_vcs_idle();
		isBbpIdle = vc_phy_check_idle();
	}
#endif
	if(dataLen == 0){
		printf("Invalid data length. dataLen = %d\n", dataLen);
		return HPLC_TX_ERR;
	}
	pLen = dataLen;

	vc_lmac_get_pkt_info_by_tmi(
		BPLC_BAND_1,
		vcPbNum,	//pbNum,
		extTmi,
		tmi,
		&tx_len,
		&FL,
		&symNum,
		&ackDur,
		&pmbDur,
		&fcDur);
	memset(&gTxCtrlHdr, 0x00, sizeof(tVC_LMAC_TX_CTRL_HEADER));
	/* The parameter BEACON_F is to inform HWMAC and BBP to treat this packet as a raw packet	*/
	/* The NTB field will be ignored by BBP, who will transmit this packet "ASAP"				*/
	vc_lmac_fill_tx_desc(&gTxCtrlHdr, BEACON_F, extTmi, tmi, tx_len, vcPbNum, 0);
	cnMacReg->CNSCH_TSR1.fields.csr_cnsch_txdur = (FL + pmbDur + fcDur) * 10;
	vcWaitNTB = (FL + pmbDur + fcDur) * 10 * 25;
	if (ack_needed) {
		//FL = FL + pmbDur + fcDur + ackDur;
		FL = FL + ACK_DUR;
	}

	memset(&gTxCnSofFc, 0x00, sizeof(tCN_SOF_FC));
	vc_lmac_fill_tx_fc(&gTxCnSofFc, wNID, wSTEI, wDTEI, FL, tmi, extTmi, vcPbNum, symNum, 1, 0);
	
	//VWORD("#ASAPTest_CR:", &gTxCtrlHdr, sizeof(tVC_LMAC_TX_CTRL_HEADER) / 4);		
	//VWORD("#ASAPTest_FC:", &gTxCnSofFc, 16 / 4);

	vc_lmac_tx_pkt_init(&pkt);
	vc_lmac_tx_pkt_attach(&pkt, &gTxCtrlHdr, sizeof(tVC_LMAC_TX_CTRL_HEADER));
	vc_lmac_tx_pkt_attach(&pkt, &gTxCnSofFc, sizeof(tCN_SOF_FC));
	if(vcPbNum == 1){
		vc_lmac_tx_pkt_attach(&pkt, &pLen, LMAC_RESERVED_BYTES_FOR_LEN_IN_PB);
		vc_lmac_tx_pkt_attach(&pkt, pTxData, pLen);
		lenZeroPadding = vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - pLen - LMAC_SIZE_OF_PBCS_IN_PB;
		if(lenZeroPadding > 0){
			vc_lmac_tx_pkt_attach(&pkt, zeroContent, lenZeroPadding);
		}
		if(lenZeroPadding < 0){
			printf("[HPLC tx] Negative lenZeroPadding!!\n");
		}
		vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);
	}else if(vcPbNum == 2){
		/*	1st	*/
		vc_lmac_tx_pkt_attach(&pkt, &pLen, LMAC_RESERVED_BYTES_FOR_LEN_IN_PB);
		vc_lmac_tx_pkt_attach(&pkt, pTxData, vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - LMAC_SIZE_OF_PBCS_IN_PB);
		vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);
		/*	2nd	*/
		vc_lmac_tx_pkt_attach(&pkt,
							  pTxData + vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - LMAC_SIZE_OF_PBCS_IN_PB,
							  pLen - (vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - LMAC_SIZE_OF_PBCS_IN_PB));
		lenZeroPadding = vcPbSize - (pLen - (vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - LMAC_SIZE_OF_PBCS_IN_PB)) - LMAC_SIZE_OF_PBCS_IN_PB;
		if(lenZeroPadding > 0){
			vc_lmac_tx_pkt_attach(&pkt, zeroContent, lenZeroPadding);
		}
		if(lenZeroPadding < 0){
			printf("[HPLC tx] Negative lenZeroPadding!!\n");
		}
		vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);
	}else if(vcPbNum == 3){
		/* 1st	pb	*/
		vc_lmac_tx_pkt_attach(&pkt, &pLen, LMAC_RESERVED_BYTES_FOR_LEN_IN_PB);
		vc_lmac_tx_pkt_attach(&pkt, pTxData, vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - LMAC_SIZE_OF_PBCS_IN_PB);
		vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);
		/*	2nd	pb	*/
		vc_lmac_tx_pkt_attach(&pkt,
							  pTxData + vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - LMAC_SIZE_OF_PBCS_IN_PB,
							  vcPbSize - LMAC_SIZE_OF_PBCS_IN_PB);
		vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);
		/*	3rd	pb	*/
		vc_lmac_tx_pkt_attach(&pkt,
							  pTxData + 2 * vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - 2 * LMAC_SIZE_OF_PBCS_IN_PB,
							  pLen - (2 * vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - 2 * LMAC_SIZE_OF_PBCS_IN_PB));
		lenZeroPadding = vcPbSize - (pLen - (2 * vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - 2 * LMAC_SIZE_OF_PBCS_IN_PB)) - LMAC_SIZE_OF_PBCS_IN_PB;
		if(lenZeroPadding > 0){
			vc_lmac_tx_pkt_attach(&pkt, zeroContent, lenZeroPadding);
		}
		if(lenZeroPadding < 0){
			printf("[HPLC tx] Negative lenZeroPadding!!\n");
		}
		vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);
	}else if(vcPbNum == 4){
		/*	1st	pb	*/
		vc_lmac_tx_pkt_attach(&pkt, &pLen, LMAC_RESERVED_BYTES_FOR_LEN_IN_PB);
		vc_lmac_tx_pkt_attach(&pkt, pTxData, vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - LMAC_SIZE_OF_PBCS_IN_PB);
		vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);
		/*	2nd	pb	*/
		vc_lmac_tx_pkt_attach(&pkt,
							  pTxData + vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - LMAC_SIZE_OF_PBCS_IN_PB,
							  vcPbSize - LMAC_SIZE_OF_PBCS_IN_PB);
		vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);
		/*	3rd	pb	*/
		vc_lmac_tx_pkt_attach(&pkt,
							  pTxData + 2 * vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - 2 * LMAC_SIZE_OF_PBCS_IN_PB,
							  vcPbSize - LMAC_SIZE_OF_PBCS_IN_PB);
		vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);
		/*	4th	pb	*/
		vc_lmac_tx_pkt_attach(&pkt,
							  pTxData + 3 * vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - 3 * LMAC_SIZE_OF_PBCS_IN_PB,
							  pLen - (3 * vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - 3 * LMAC_SIZE_OF_PBCS_IN_PB));
		lenZeroPadding = vcPbSize - (pLen - (3 * vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - 3 * LMAC_SIZE_OF_PBCS_IN_PB)) - LMAC_SIZE_OF_PBCS_IN_PB;
		if(lenZeroPadding > 0){
			vc_lmac_tx_pkt_attach(&pkt, zeroContent, lenZeroPadding);
		}
		if(lenZeroPadding < 0){
			printf("[HPLC tx] Negative lenZeroPadding!!\n");
		}
		vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);

	}else{
		printf("Invalid pbNum\n.");
		return HPLC_TX_ERR;
	}
//	vc_lmac_tx_pkt_attach(&pkt, &pLen, sizeof(pLen));
//	vc_lmac_tx_pkt_attach(&pkt, pTxData, tx_len-sizeof(pLen));
	/* Use the gcc builin function to guarantee atomicity */
	//__sync_fetch_and_and(&plc_m_txp_done, 0);
	vcs_remain_time = cnMacDebugReg->CNVCS_DR1.fields.csr_cnvcs_tartt + 0xffffffffUL - cnMacDebugReg->CNVCS_DR2.fields.csr_cnvcs_curtt + 1;
	/*in PLC transmit WiSUN 500 byte packet, from start to after attach pkt almost < 120us,	   */
	/*										 from start to after dsp tx start almost < 200us,  */
	if (!vc_lmac_check_vcs_idle() && (vcs_remain_time > 600)) { //600us
		return HPLC_TX_BUSY;
	}
	while(!(vc_lmac_check_vcs_idle() && vc_phy_check_idle())){
		t1 = vc_phy_get_ntb();
		if((t1 + 0xffffffffUL - startNTB + 1) > 15000){ //600us, worst case dsp still have 400us to process
		/*in PLC transmitting PLC_WISUN_SEND_TIMEING_DELAY_NOSEC is 1ms, disable rx must wait 0.5ms*/
		/* pkc attach 1000 bytes packet less then 2000 ntbs = 40us, kickdma to txpdone less then 1000 ntbs = 20us. We give upto 500us as budget*/
			printf("PLC %lu/%u busy: %lu us\n", vc_lmac_check_vcs_idle(), vc_phy_check_idle(), (t1 - startNTB)/25);
			return HPLC_TX_BUSY;
		}
	}
	plc_m_tx_info_start = 0;
	plc_m_tx_info_finish = 0;
	isDelayed = 0;
	vc_lmac_send_tx_pkt_to_dma(&pkt);
	while(plc_m_tx_info_start == 0){
		t1 = vc_phy_get_ntb();
		if((t1 + 0xffffffffUL - startNTB + 1) > 25000){
			volatile PHY_REG *reg_space = (volatile PHY_REG *)PHY_REG_BASEADDR;
			plc_tx_delay_start_counter++;
			if ( (reg_space->phy_ir2 & 0x1) == 0) { //DSP TX it will be 1, if DSP TX not start, try to abort
				extern void vc_lmac_cfg_hw_csma_dsp_abort(void);
				vc_lmac_cfg_hw_csma_dsp_abort();
				printf("PLC dsp not tx state: %lu us\n", (t1 - startNTB)/25);
				return HPLC_TX_BUSY;//maybe can't return now
			}
			printf("PLC TX delay start: %lu us\n", (t1 - startNTB)/25);
		}
	}

	printf("tmi=%d, tx_len=%lu, FL= %d, symNum =%d, ackDur = %d, pb=%d\r\n", tmi, pLen, FL, symNum, ackDur, vcPbNum);
	#if 0
	plc_m_txp_done = 0;
	while(plc_m_txp_done == 0){
		t1 = vc_phy_get_ntb();
		/* Based on the experiment, the time between start of sw kickdma and the txp_done is about 25~32 us. */
		/* So if here we spend longer time than this, we show the warning message. 							 */
		if((t1 + 0xffffffffUL - t0 + 1) > 2 * 25000){
			plc_m_txp_done = 1; /*it's fatal error if txp_done not triggered*/
			if(!isDelayed){
				isDelayed = 1;
			}
		}
	}
	#endif
	t0 = vc_phy_get_ntb();
  //vc_dual_mode_host_plctxled_on();
#if 0//none_loop_tx
	if(vcWaitNTB > WISUN_DUAL_RF_ACK_RESERVED_TIME && *rfstat >= 0){
		vcradio_unlock_irq(*rfstat);
	}
#endif
	while(plc_m_tx_info_finish == 0){
		t1 = vc_phy_get_ntb();
#if 0//none_loop_tx
		if((vcWaitNTB + 0xffffffffUL - t1 + 1) < WISUN_DUAL_RF_ACK_RESERVED_TIME && *rfstat >= 0){
			*rfstat = vcradio_lock_irq();
		}
#endif
		if((t1 + 0xffffffffUL - t0 + 1) > vcWaitNTB){
			if(!isDelayed){
				plc_tx_delay_finish_counter++;
				isDelayed = 1;
			}
			plc_m_tx_info_finish = 1;
		}
	}
	//vc_dual_mode_host_plctxled_off();
	if(isDelayed){
		printf("PLC tx not finish");
		printf(":start = %lu us, waitNTB = %lu us, FL = %u ,len %u, ack %hhu", (t1-t0)/25, (vcWaitNTB/25), FL, tx_len, ack_needed);
		printf("\r\n");
	}
	//*kickoffNTB = vc_phy_get_ntb();
	return HPLC_TX_OK;

}
int8_t vc_lmac_tx_sof_pkt_f_cmd_txack_asap(uint8_t *pTxData, uint16_t dataLen, uint32_t startNTB)
{
	tVC_DMAC_PACKET pkt;
	uint8_t extTmi = 0;
	uint8_t tmi = 14;
	uint8_t vcPbNum = 1; 
	uint16_t vcPbSize = LMAC_PB_SIZE_72;
	uint16_t tx_len = vcPbNum * gMapSymTMI_ALL.InfoTMI[tmi].PbSize;
	uint16_t symNum = vc_lmac_cal_ofdma_symbol_number(extTmi, tmi, 131, 0);
	uint16_t FL = ACK_FL;//(((gMapSymTMI_ALL.fcTime * 2) / 100) + ((gMapSymTMI_ALL.pldTime * vcPbNum * symNum) / 100) + LMAC_CIFS) / 10;
	uint32_t wNID = WISUN_NID;
	uint16_t wSTEI = 0x0000;
	uint16_t wDTEI = WISUN_TEI;
	uint32_t t1, vcs_remain_time;
	uint16_t lenZeroPadding;	//length of zero padding at the end of last pb

	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	volatile tVCMAC_DEBUG_REGISTER *cnMacDebugReg = (volatile tVCMAC_DEBUG_REGISTER *)VC_MAC_CN_DEBUG;

	cnMacReg->CNSCH_TSR1.fields.csr_cnsch_txdur = ACK_DUR * 10;

	if(dataLen == 0){
		printf("Invalid data length. dataLen = %d\n", dataLen);
		return HPLC_TX_ERR;
	}
	pLen = dataLen;
	memset(&gTxCtrlHdr, 0x00, sizeof(tVC_LMAC_TX_CTRL_HEADER));
	vc_lmac_fill_tx_desc(&gTxCtrlHdr, BEACON_F, extTmi, tmi, tx_len, vcPbNum, 0);
	memset(&gTxCnSofFc, 0x00, sizeof(tCN_SOF_FC));
	vc_lmac_fill_tx_fc(&gTxCnSofFc, wNID, wSTEI, wDTEI, FL, tmi, extTmi, vcPbNum, symNum, 1, 0);

	vc_lmac_tx_pkt_init(&pkt);
	vc_lmac_tx_pkt_attach(&pkt, &gTxCtrlHdr, sizeof(tVC_LMAC_TX_CTRL_HEADER));
	vc_lmac_tx_pkt_attach(&pkt, &gTxCnSofFc, sizeof(tCN_SOF_FC));
	vc_lmac_tx_pkt_attach(&pkt, &pLen, LMAC_RESERVED_BYTES_FOR_LEN_IN_PB);
	vc_lmac_tx_pkt_attach(&pkt, pTxData, pLen);
	lenZeroPadding = vcPbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - pLen - LMAC_SIZE_OF_PBCS_IN_PB;
	if(lenZeroPadding > 0){
		vc_lmac_tx_pkt_attach(&pkt, zeroContent, lenZeroPadding);
	}
	if(lenZeroPadding < 0){
		printf("[HPLC tx] Negative lenZeroPadding!!\n");
		return 0;
	}
	vc_lmac_tx_pkt_attach(&pkt, dummyTxPbcs, LMAC_SIZE_OF_PBCS_IN_PB);
	plc_m_tx_info_start = 0;
	vcs_remain_time = cnMacDebugReg->CNVCS_DR1.fields.csr_cnvcs_tartt + 0xffffffffUL - cnMacDebugReg->CNVCS_DR2.fields.csr_cnvcs_curtt + 1;
	while(vc_phy_check_idle() == 0){
		if(((vc_phy_get_ntb() + 0xffffffffUL - startNTB + 1) > 5000)  || (vcs_remain_time < ACK_DUR)){
			printf("PLC ACK BUSY\r\n");
			return -1;
		}
	}
	vc_lmac_send_tx_pkt_to_dma(&pkt);
	while(plc_m_tx_info_start == 0){
		t1 = vc_phy_get_ntb();
		/* Based on the experiment, the time between start of sw kickdma and the txp_done is about 25~32 us. */
		/* So if here we spend longer time than this, we show the warning message. 							 */
		if((t1 + 0xffffffffUL - startNTB + 1) > 25000){
			plc_ack_delay_start_counter++;
			printf("PLC ACK delay\n");
			//plc_m_tx_info_start = 1; /*it's fatal error if txp_done not triggered*/
			return 0;
		}
	}
	return 1;
}

int vc_lmac_tx_sof_pkt_f_cmd_txdata(uint16_t DTEI, uint8_t extTmi, uint8_t tmi, uint8_t *pTxData, uint16_t pDataLen)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	tVC_DMAC_PACKET pkt;
	uint8_t pbNum = 1;
	uint16_t tx_len;
	uint16_t FL = 0;
	uint16_t symNum = 0;
	uint16_t ackDur = 0;
	uint16_t pmbDur = 0;
	uint16_t fcDur = 0;
	uint32_t wNID = 0x00;
	uint16_t wSTEI = 0x0000;	
	uint16_t wDTEI = 0x0FFF;
	uint32_t t0, t1, t2, t3;
	
	if((pDataLen+7) < 72){	
		;//tmi=1;
	}else if ((pDataLen+7) >=72 && (pDataLen+7) < 136 ){ 
		;//tmi=1;
	}else if ((pDataLen+7) >=136 && (pDataLen+7) < 264 ){ 
		;//tmi=1;
	}else if ((pDataLen+7) >=264 && (pDataLen+7) < 520 ){ 
		;//tmi=1;
	}else {
		printf("Not support Len=%d\r\n", pDataLen);		
		return HPLC_TX_ERR;
	}

	/*   In case of channel hopping, should the initial waiting time is too long,  */
	/*   we should return busy. Otherwise the UTT-IE would be out-of-date */
	//t0 = t1 = hal_misc_milli_get_now();
	t0 = t1 = vc_phy_get_ntb();
	while(vc_lmac_check_vcs_idle() == 0 || vc_phy_check_idle() == 0) {
		t1 = vc_phy_get_ntb();
		if((t1 + 0xffffffffUL - t0 + 1) > 10 * 25000){
			//printf("1\n");
			return HPLC_TX_BUSY;
		}
	}
	
	if(plc_m_txp_done == 0){
		printf("Previous tx not completed yet \r\n");
		//plc_m_txp_done = 1;
		/* Use the gcc builin function to guarantee atomicity */
		__sync_fetch_and_or(&plc_m_txp_done, 1);

		return HPLC_TX_ERR;		//MMM
	}

	pLen = pDataLen;
	

	vc_lmac_get_pkt_info_by_tmi(
		BPLC_BAND_1, 
		pbNum,
		extTmi, 
		tmi, 
		&tx_len, 
		&FL, 
		&symNum, 
		&ackDur,
		&pmbDur,
		&fcDur);

	memset(&gTxCtrlHdr,0x00, sizeof(tVC_LMAC_TX_CTRL_HEADER));
	vc_lmac_fill_tx_desc(&gTxCtrlHdr, SOF_F, extTmi, tmi, tx_len, pbNum, 0);
	
	wNID = 0x112233;
	wSTEI = gLMAC->LMAC_STEI;
	wDTEI = DTEI;
	//printf("TX_len=%d, FL= %d, symNum =%d, ackDur = %d, pb=%d, DT=%d"LF, tx_len, FL, symNum, ackDur, pbNum, gTxCtrlHdr.DT);
	memset(&gTxCnSofFc, 0x0, sizeof(tCN_SOF_FC));
	vc_lmac_fill_tx_fc(&gTxCnSofFc, wNID, wSTEI, wDTEI, FL, tmi, extTmi, pbNum, symNum, 1, 0);
	vc_lmac_tx_pkt_init(&pkt);
	vc_lmac_tx_pkt_attach(&pkt, &gTxCtrlHdr, sizeof(tVC_LMAC_TX_CTRL_HEADER));
	vc_lmac_tx_pkt_attach(&pkt, &gTxCnSofFc, sizeof(tCN_SOF_FC));
	//vc_lmac_tx_pkt_attach(&pkt, pTxData, tx_len);
	vc_lmac_tx_pkt_attach(&pkt, &pLen, sizeof(pLen));
	vc_lmac_tx_pkt_attach(&pkt, pTxData, tx_len-sizeof(pLen));

	if((gTxCnSofFc.SofVarDTEI  == 0x0FFF) ||(gTxCnSofFc.SofVarDTEI  == 0x000)){
		vc_lmac_init_csma(VC_SACK_NOT, SOF_PKT,CSMA_F_NXQ, pmbDur + fcDur + FL, ackDur);
	}else{
		vc_lmac_init_csma(VC_SACK_NEED, SOF_PKT,CSMA_F_NXQ, pmbDur + fcDur + FL, ackDur);
	}
	//plc_m_csma_get_para = 0;
	//plc_m_txp_done = 0;
	//plc_m_csma_success = 0;
	//plc_m_csma_fail = 0;
	//plc_m_csma_abort = 0;
	//plc_m_dsp_abortpkt = 0;
	/* Use the gcc builin function to guarantee atomicity */
	__sync_fetch_and_and(&plc_m_csma_get_para, 0);
	__sync_fetch_and_and(&plc_m_txp_done, 0);
	__sync_fetch_and_and(&plc_m_csma_success, 0);
	__sync_fetch_and_and(&plc_m_csma_fail, 0);
	__sync_fetch_and_and(&plc_m_csma_abort, 0);
	__sync_fetch_and_and(&plc_m_dsp_abortpkt, 0);


	t0 = t1 = t2 = t3 = vc_phy_get_ntb();
	vc_lmac_send_tx_pkt_to_dma(&pkt);
		
	while(plc_m_csma_get_para == 0){
		t1 = vc_phy_get_ntb();
		if((t1 + 0xffffffffUL - t0 + 1) > 1 * 25000){
			printf("Waiting too long for plc_m_csma_get_para\n");
			break;
		}
	}

	while(plc_m_txp_done == 0){
		t2 = vc_phy_get_ntb();
		if((t2 + 0xffffffffUL - t0 + 1) > 30 * 25000){
			printf("Waiting too long for plc_m_txp_done\n");
			break;
		}
	}

	if(plc_m_csma_fail == 1){
		while (plc_m_dsp_abortpkt == 0){
			t3 = vc_phy_get_ntb();
			if((t3 + 0xffffffffUL - t0 + 1) > 50 * 25000){
				printf("Waiting too long for plc_m_dsp_abortpkt\n");
				break;
			}
		}
	}		

	//printf("t0 = %lu us, t1 = %lu us, t2 = %lu us, t3 = %lu us\n", t0/25, t1/25, t2/25, t3/25);
	if(plc_m_csma_fail == 1 || plc_m_csma_abort == 1){
		printf("plc_m_csma_success = %d, plc csma fail = %d, plc_m_csma_abort = %d, plc_m_txp_done = %d\n",
				plc_m_csma_success, plc_m_csma_fail, plc_m_csma_abort, plc_m_txp_done);
		return HPLC_TX_COLLISION;
	}else{
		//printf("plc_m_csma_success = %d, plc csma fail = %d, plc_m_csma_abort = %d, plc_m_txp_done = %d\n",
		//		plc_m_csma_success, plc_m_csma_fail, plc_m_csma_abort, plc_m_txp_done);
		return HPLC_TX_OK;
	}

	return 0;
}

void print_tx_ctrl_hdr_param(tVC_LMAC_TX_CTRL_HEADER *ctrlHdr)
{
	printf("ctrlHdr->ctrl: %lx\n", ctrlHdr->ctrl.value);
	printf("ctrlHdr->seq: %d\n", ctrlHdr->seq);
	printf("ctrlHdr->pktLen: %d\n", ctrlHdr->pktLen);
	printf("ctrlHdr->DT: %d\n", ctrlHdr->DT);
	printf("ctrlHdr->PBNum:%d\n", ctrlHdr->PBNum);
	printf("ctrlHdr->TMI:%d\n", ctrlHdr->TMI);
	printf("ctrlHdr->TMIType:%d\n", ctrlHdr->TMIType);
	printf("ctrlHdr->BandPlan:%d\n", ctrlHdr->BandPlan);
	//printf("ctrlHdr->NTB:%d\n", ctrlHdr->bcnNTB);
}
void print_fc_sof_param(tCN_SOF_FC *fc)
{
	printf("fc->delimiterType: %d\n", fc->delType);
	printf("fc->networkType: %d\n", fc->netType);
	printf("fc->NID: %06X\n", fc->NID);
	if (fc->delType == SOF_F) {
		printf("fc->sof.sof_STEI: %03X\n", fc->SofVarSTEI);
		printf("fc->sof.sof_DTEI: %03X\n", fc->SofVarDTEI);
		printf("fc->sof.sof_LID: %02X\n", fc->SofVarLID);
		printf("fc->sof.sof_FL: %03X\n", fc->SofVarFL);
		printf("fc->sof.sof_PBCount: %d\n", fc->SofVarPBCount);
		printf("fc->sof.symbolNum: %d\n", fc->SofVarSymbolNum);
		printf("fc->sof.bcastFlag: %d\n", fc->SofVarBcastFlag);
		printf("fc->sof.resendFlag: %d\n", fc->SofVarResendFlag);
		printf("fc->sof.encryptFlag: %d\n", fc->SofVarEncryptFlag);
		printf("fc->sof.TMI: %d\n", fc->SofVarTMI);
		printf("fc->sof.extTMI: %d\n", fc->SofVarExtTMI);
		printf("fc->version: %d\n", fc->version);
		printf("fc->fccs: %02X%02X%02X\n", fc->fccs[0], fc->fccs[1], fc->fccs[2]);
	}
	
}
uint8_t dma_tx_data[520];
extern uint16_t neoDebugTxPingTotal;
extern uint16_t neoDebugTxPingCurr;

void vc_lmac_tx_sof_pkt_f_cmd_ping(uint16_t DTEI, uint8_t extTmi, uint8_t tmi, uint8_t pbCount, uint8_t startFlag)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	tVC_DMAC_PACKET pkt;
	uint16_t tx_len = 0;
	uint16_t FL = 0;
	uint16_t symNum = 0;
	uint16_t ackDur = 0;
	uint16_t pmbDur = 0;	//MMM
	uint16_t fcDur = 0;		//MMM
	uint16_t i;
	uint8_t bbpIsIdle = 0;

	memset(&pkt, 0x00, sizeof(tVC_DMAC_PACKET));
	
	printf("sendPing\r\n");
	
	if(startFlag){
		neoDebugTxPingTotal = 10;
		neoDebugTxPingCurr = 0;
	}
	bbpIsIdle = 1;
	if (bbpIsIdle) {
		vc_lmac_get_pkt_info_by_tmi(
			//BPLC_BAND_1, pbCount, extTmi, tmi, &tx_len, &FL, &symNum, &ackDur);
			BPLC_BAND_1, pbCount, extTmi, tmi, &tx_len, &FL, &symNum, &ackDur, &pmbDur, &fcDur);

		printf("Len:%d, FL:%d, sNum:%d, ackDur:%d\r\n",tx_len, FL, symNum,ackDur);
		
		memset(&gTxCtrlHdr, 0x00, sizeof(tVC_LMAC_TX_CTRL_HEADER));		
		vc_lmac_fill_tx_desc(&gTxCtrlHdr, SOF_F, extTmi, tmi, (tx_len * pbCount), pbCount, 0);
		memset(&gTxCnSofFc, 0x0, sizeof(tCN_SOF_FC));
		gTxCnSofFc.delType = SOF_F;
		gTxCnSofFc.NID = 0x00;
		gTxCnSofFc.netType = 0;
		gTxCnSofFc.SofVarSTEI = gLMAC->LMAC_STEI;
		gTxCnSofFc.SofVarDTEI = DTEI;
		gTxCnSofFc.SofVarLID = 0xAA;
		gTxCnSofFc.SofVarFL = FL;
		gTxCnSofFc.SofVarPBCount = 1;
		gTxCnSofFc.SofVarTMI = 0;
		gTxCnSofFc.SofVarExtTMI = 0;
		gTxCnSofFc.SofVarSymbolNum = symNum;
		//vc_lmac_cfg_arq_MyTEI(gLMAC->LMAC_STEI);
		for (i = 0; i < tx_len; i++) {
			dma_tx_data[i] = i + 3;
		}
		vc_lmac_tx_pkt_init(&pkt);
		vc_lmac_tx_pkt_attach(&pkt, &gTxCtrlHdr, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		vc_lmac_tx_pkt_attach(&pkt, &gTxCnSofFc, sizeof(tCN_SOF_FC));
		//VWORD("#PING_CR:", &gTxCtrlHdr, sizeof(tVC_LMAC_TX_CTRL_HEADER) / 4);		
		//VWORD("#PING_FC:", &gTxCnSofFc, 16 / 4);
		print_tx_ctrl_hdr_param(&gTxCtrlHdr);
		print_fc_sof_param(&gTxCnSofFc);
		
		for (i = 0; i < pbCount; i++) {
			vc_lmac_tx_pkt_attach(&pkt, &dma_tx_data, tx_len);
		}
		vc_lmac_init_csma(VC_SACK_NOT, SOF_PKT, 0, FL, ackDur);
		vc_lmac_send_tx_pkt_to_dma(&pkt);
	}
}
void vc_lmac_tx_sof_pkt_f_phy_ping(uint16_t DTEI, uint8_t extTmi, uint8_t tmi, uint8_t pbCount)
{	
	tVC_DMAC_PACKET pkt;
	uint16_t tx_len = 0;
	uint16_t FL = 0;
	uint16_t symNum = 0;
	uint16_t ackDur = 0;
	uint16_t pmbDur = 0;
	uint16_t fcDur = 0;
	uint16_t i;
	uint8_t bbpIsIdle = 0;

	memset(&pkt, 0x00, sizeof(tVC_DMAC_PACKET));
	
	printf("vc_lmac_tx_sof_pkt_f_phy_ping\n");
	
	bbpIsIdle = 1;
	if (bbpIsIdle) {
		vc_lmac_get_pkt_info_by_tmi(
			//BPLC_BAND_1, pbCount, extTmi, tmi, &tx_len, &FL, &symNum, &ackDur);
			BPLC_BAND_1, pbCount, extTmi, tmi, &tx_len, &FL, &symNum, &ackDur, &pmbDur, &fcDur);
		memset(&gTxCtrlHdr, 0x00, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		vc_lmac_fill_tx_desc(&gTxCtrlHdr, PHY_TEST, extTmi, tmi, (tx_len * pbCount), pbCount, 0);
		memset(&gTxCnSofFc, 0x0, sizeof(tCN_SOF_FC));
		gTxCnSofFc.delType = SOF_F;
		gTxCnSofFc.NID = 0x00;
		gTxCnSofFc.netType = 0;
		gTxCnSofFc.SofVarSTEI = 0x000;
		gTxCnSofFc.SofVarDTEI = DTEI;
		gTxCnSofFc.SofVarLID = 0xAA;
		gTxCnSofFc.SofVarFL = FL;
		gTxCnSofFc.SofVarPBCount = pbCount;
		gTxCnSofFc.SofVarTMI = tmi;
		gTxCnSofFc.SofVarExtTMI = extTmi;
		gTxCnSofFc.SofVarSymbolNum = symNum;
		//vc_lmac_cfg_arq_MyTEI(0x000);
		for (i = 0; i < tx_len; i++) {
			dma_tx_data[i] = i + 3;
		}
		vc_lmac_tx_pkt_init(&pkt);
		vc_lmac_tx_pkt_attach(&pkt, &gTxCtrlHdr, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		vc_lmac_tx_pkt_attach(&pkt, &gTxCnSofFc, sizeof(tCN_SOF_FC));
		
		//VWORD("#PhyTest_CR:", &gTxCtrlHdr, sizeof(tVC_LMAC_TX_CTRL_HEADER) / 4);		
		//VWORD("#PhyTest_FC:", &gTxCnSofFc, 16 / 4);
		
		print_tx_ctrl_hdr_param(&gTxCtrlHdr);
		print_fc_sof_param(&gTxCnSofFc);

		vc_lmac_dw(0x40011000,0x50);
		vc_lmac_dw(0x400111c0,0x10);

		for (i = 0; i < pbCount; i++) {
			vc_lmac_tx_pkt_attach(&pkt, &dma_tx_data, tx_len);
		}
		vc_lmac_init_csma(VC_SACK_NOT, SOF_PKT, 0, FL, ackDur);
		vc_lmac_send_tx_pkt_to_dma(&pkt);
	}
}
