#include <stdio.h>
#include <stdlib.h>

#include "phy.h"
#include "vc_lmac_txh.h"
#include "vc_lmac.h"
#include "vc_lmac_dma_if.h"
#include "vc_string.h"

static vc_lmac_pkt_sym_mapping gMapSymTMI_ALL = {
	BPLC_BAND_0, BPLC_TMI, 40.96, 59.28, 51.52, {
		{ 520, 2, 4, 8 },   /*0*/
		{ 520, 2, 2, 8 },   /*1*/
		{ 136, 2, 5, 10 },  /*2*/
		{ 136, 1, 11, 11 }, /*3*/
		{ 136, 1, 7, 14 },  /*4*/
		{ 136, 2, 11, 11 }, /*5*/
		{ 136, 2, 7, 14 },  /*6*/
		{ 520, 1, 7, 14 },  /*7*/
		{ 520, 1, 4, 8 },   /*8*/
		{ 520, 2, 7, 14 },  /*9*/
		{ 520, 1, 2, 8 },   /*10*/
		{ 264, 2, 7, 14 },  /*11*/
		{ 264, 1, 7, 14 },  /*12*/
		{ 72, 2, 7, 14 },   /*13*/
		{ 72, 1, 7, 14 }    /*14*/
	}
};

static vc_lmac_pkt_sym_mapping gMapSymTMI_ALL_E = {
	BPLC_BAND_0, BPLC_E_TMI, 40.96, 59.28, 51.52, {
		{ 0, 0, 0, 0 },     /*0*/
		{ 520, 4, 1, 1 },   /*1*/
		{ 520, 4, 2, 8 },   /*2*/
		{ 520, 4, 1, 1 },   /*3*/
		{ 520, 4, 2, 8 },   /*4*/
		{ 520, 4, 4, 8 },   /*5*/
		{ 520, 2, 1, 1 },   /*6*/
		{ 0, 0, 0, 0 },     /*7*/
		{ 0, 0, 0, 0 },     /*8*/
		{ 0, 0, 0, 0 },     /*9*/
		{ 136, 4, 5, 10 },  /*10*/
		{ 136, 2, 2, 8 },   /*11*/
		{ 136, 4, 2, 8 },   /*12*/
		{ 136, 2, 1, 1 },   /*13*/
		{ 136, 4, 1, 1 }    /*14*/
	}
};

extern vc_uint8 vc_phy_check_idle();
extern vc_ntb32 vc_phy_get_ntb();
extern void vc_lmac_cfg_arq_MyTEI(vc_uint16 pMyTEI);
extern void vc_lmac_cfg_phy_rx_enable();

tVC_LMAC_TX_CTRL_HEADER gTxCtrlHdrSigTest;
tVC_LMAC_TX_CTRL_HEADER gTxCtrlHdrBbpCmd;
tVC_LMAC_TX_CTRL_HEADER gTxCtrlHdrBCN;
tCN_BEACON_FC gTxCnBconFc;
tCN_SOF_FC gTxCnSofFc;
vc_extend_cmd gExtendCmd;
vc_uint8 pTheLastCsma = 0;
vc_uint8 ctrlSeqNum = 0;
vc_uint8 lastTypeOfLMAC_WAIT_CSMA_NON = 0;
vc_uint32 lastTypeOfBBPcmdType = 0;
vc_uint8 lmac_proformance_test_mode = 0;
vc_uint8 lmac_num_of_backoffs = 0;
vc_uint8 lmac_csma_backoff_exponent = 0;
static vc_uint32 csmaCurrFrameLengthUs = 0;
static vc_uint32 csmaLastBackoffPeriodUs = 0;
vc_uint8 csmaAbortFlagEnable = 0;
static vc_uint32 curr_csma_end_ms = 0;
vc_uint8 gTxBbpRawCmdCount = 0;
vc_uint8 gTxBbpRawCmdIdx = 0;
gTxRawCmdDelaySend gTxRawCmdSend[VC_LMAC_RAW_CMD_DELAY_SEND_NUM];
vc_uint8 waitTxpDoneFlag = 0;
vc_uint32 waitTxpDoneNTB = 0;
vc_uint8 txpDoneNotFinished = 0;
vc_uint32 gPhyTestCount = 0;
vc_uint8 dma_tx_data[520];

void LMAC_KICK_RX_DMA()
{
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	vc_uint32 value = 0;
	((tVC_DMA_RXE_KR *)&value)->fields.csr_rxe_kick = 1;
	dmaReg->RXE_KR.value = value;
}

void LMAC_KICK_TX_DMA()
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	vc_uint32 value = 0;

	gLMAC->lmacIrqCount.kickDma++;
	((tVC_DMA_TXE_KR *)&value)->fields.csr_txe_kick = 1;
	dmaReg->TXE_KR.value = value;
}

vc_uint8 vc_lmac_incrase_ctrl_seq_num()
{
	ctrlSeqNum++;
	return ctrlSeqNum;
}

void vc_lmac_tx_pkt_init(tVC_DMAC_PACKET *pkt)
{
	vc_memset(pkt, 0x00, sizeof(tVC_DMAC_PACKET));
	pkt->nr_desc = 0;
}

void vc_lmac_tx_pkt_attach(tVC_DMAC_PACKET *pkt, void *pData, vc_uint16 pDataLen)
{
	pkt->pld[pkt->nr_desc].dma_ptr = pData;
	pkt->pld[pkt->nr_desc].dma_size = pDataLen;
	pkt->nr_desc++;
}

void vc_lmac_change_state(tLmac_state state)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	gLMAC->lmacState = state;
}

vc_int32 vcLessMod2p32(vc_uint32 a, vc_uint32 b)
{
	return (vc_int32)(a - b) < 0;
}

vc_uint8 vc_lmac_fill_dma_owner_bit(tVC_DMAC_PACKET *pkt)
{
	vc_uint8 i = 0;
	for (i = 0; i < pkt->nr_desc; i++) {
		g_dmaTxDesc[i].ctrl.fields.owner = VC_DMAC_OWNER_DMAC;
	}
	return 1;
}

vc_uint8 vc_lmac_fill_dma_desc(tVC_DMAC_PACKET *pkt)
{
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	vc_uint8 i = 0;
	if (g_dmaTxDesc[pkt->nr_desc - 1].ctrl.fields.owner == VC_DMAC_OWNER_DMAC) {
		return 0;
	}
	for (i = 0; i < pkt->nr_desc; i++) {
		g_dmaTxDesc[i].ctrl.fields.last = 0;
		g_dmaTxDesc[i].ctrl.fields.first = 0;
		g_dmaTxDesc[i].ctrl.fields.int_en = 0;
		g_dmaTxDesc[i].ctrl.fields.eor = 0;
		//g_dmaTxDesc[i].ctrl.fields.owner = VC_DMAC_OWNER_DMAC;
		if (i == 0) {
			g_dmaTxDesc[i].ctrl.fields.first = 1;
		}
		if (i + 1 == pkt->nr_desc) {
			g_dmaTxDesc[i].ctrl.fields.int_en = 1;
			g_dmaTxDesc[i].ctrl.fields.last = 1;
		}
		if (i + 1 == VC_DMAC_TX_NR_DESC) {
			g_dmaTxDesc[i].ctrl.fields.eor = 1;
		}
		g_dmaTxDesc[i].ctrl.fields.pkt_len = pkt->pld[i].dma_size;
		g_dmaTxDesc[i].ptr = (vc_uint32)pkt->pld[i].dma_ptr;
		if (g_dmaTxDesc[i].ctrl.fields.pkt_len <= 0) {
			printf("[DMA] Warning!TxDmaLen is 0!!\r\n");
			//ULOG(ULL_ERR, "[DMA] Warning!TxDmaLen is 0!!");
      while(1);
		}
		if ((g_dmaTxDesc[i].ctrl.fields.pkt_len % 4) != 0) {
			printf("[DMA] Warning!TxDmaLen is not word alignments!!\r\n");
			//ULOG(ULL_ERR, "[DMA] Warning!TxDmaLen is not word alignments!!");
      while(1);
		}
	}
	dmaReg->TXE_BA_SR.value = (vc_uint32) & g_dmaTxDesc[0];
	return 1;
}

vc_uint8 vc_lmac_send_tx_pkt_to_dma(tVC_DMAC_PACKET *pkt, vc_uint8 type, vc_uint8 txType)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	//volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	vc_uint32 timeoutDmaCheck = 0;
	//vc_uint32 mask = 0;
	//vc_uint16 i = 0;
	vc_uint8 retval = 0;
	if (waitTxpDoneFlag) {
		if (vcLessMod2p32((waitTxpDoneNTB + (25000) * 50), vc_phy_get_ntb()) == 1) {
			//UERR(UNIERR_STATE_ERR, "TxpDoneNotFinish!!%u", (vc_phy_get_ntb() - waitTxpDoneNTB) / 25);
			//vc_lmac_log_dsp_dump();
      printf("TxpDoneNotFinish!!%u\r\n", (unsigned int)((vc_phy_get_ntb() - waitTxpDoneNTB) / 25));
			waitTxpDoneFlag = 0;
		}
	}
	if (txpDoneNotFinished) {
		//ULOG(ULL_ERR, "KickDmaFail!!\r\n");
    printf("KickDmaFail!!\r\n");
		return 1;
	} else {
		txpDoneNotFinished = 1;
	}

	gLMAC->lmacIrqCount.kickDmaWant++;

	// if (1) {
	// 	lmac_dbg_tx pDbgTx;
	// 	vc_memset(&pDbgTx, 0x00, sizeof(lmac_dbg_tx));
	// 	pDbgTx.kickDmaType = type;
	// 	pDbgTx.kickDmaSeqNum = ctrlSeqNum;
	// 	pDbgTx.ntb = vc_phy_get_ntb();
	// 	pDbgTx.txType = txType;
	// 	vc_lmac_dbg_tx_handler(&pDbgTx);
	// }

	//mask = OS_EnterCritical();

	// if (gLMAC->lmacState != LMAC_IDLE) {
	// 	vc_lmac_tx_led_blink();
	// }

	timeoutDmaCheck = vc_phy_get_ntb();

	do {
		retval = vc_lmac_fill_dma_desc(pkt);
		if (vcLessMod2p32(timeoutDmaCheck + 2500, vc_phy_get_ntb()) == 1) {
			break;
		}
	} while (retval == 0);

	if (retval) {
		if (type == VC_KICK_DMA_API_ITNWC_SNED) {
			gLMAC->lmacIrqCount.kickItnwc++;
		} else if (type == VC_KICK_DMA_BBP_PKT) {
			gLMAC->lmacIrqCount.kickBbpRaw++;
		} else if (type == VC_KICK_DMA_TXQ_SEND) {
			gLMAC->lmacIrqCount.kickSof++;
			if ((cnMacReg->CNSCH_TSR1 & 0x00FFFFFF) == 0) {
        printf("Error!! Kick Sof but TxDur is 0!!\r\n");
				//URESPONSE("Error!! Kick Sof but TxDur is 0!!\r\n");
				//VC_ASSERT(0, "TxDur is Zero!!");
			}
		} else {
			gLMAC->lmacIrqCount.kickOther++;
		}
		vc_lmac_fill_dma_owner_bit(pkt);
		LMAC_KICK_TX_DMA();
		//vc_lmac_log_dsp_ir(1);
		waitTxpDoneFlag = 1;
		waitTxpDoneNTB = vc_phy_get_ntb();
	} else {
		if (vc_phy_check_idle() == 0) {
			gLMAC->lmacIrqCount.kickDmaDspBusy++;
		}
		//ULOG(ULL_ERR, "SofDmaBusy!!");
    printf("SofDmaBusy!!\r\n");
		txpDoneNotFinished = 0;
		//OS_ExitCritical(mask);
		return 1;
	}
	//OS_ExitCritical(mask);
	return 0;
}

void vc_lmac_tx_bbp_pkt_f_cmd(tBbpRawCmd *pBbpRawCmd)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	tVC_DMAC_PACKET pkt;
	vc_uint16 ctrlLen = 0;
	vc_uint8 bbpIsIdle = 0;
	//vc_uint32 mask = 0;
	vc_uint8 i = 0;

	//ULOG(ULL_DUMP, "[BBPRAW] 0x%X,", pBbpRawCmd->bbpCmd[0]);
	printf("[BBPRAW] 0x%X,", (unsigned int)pBbpRawCmd->bbpCmd[0]);
	for (i = 1; i < (pBbpRawCmd->bbpCmdLen / 4); i++) {
		//ULOG(ULL_DUMP, "0x%X,", pBbpRawCmd->bbpCmd[i]);
		printf("0x%X,", (unsigned int)pBbpRawCmd->bbpCmd[i]);
	}
	//ULOG(ULL_DUMP, LF);
  printf("\r\n");

	//mask = OS_EnterCritical();
	bbpIsIdle = vc_phy_check_idle();
	if (bbpIsIdle && (gLMAC->lmacState <= LMAC_CSMA_IDLE)) {
		vc_memset(&gTxCtrlHdrBbpCmd, 0x00, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		gTxCtrlHdrBbpCmd.ctrl.fields.type = TX_CTRL_HDR_BBP_TX_TYPE;
		gTxCtrlHdrBbpCmd.ctrl.fields.mode = TX_CTRL_HDR_CNBPLC_MODE;
		ctrlLen = sizeof(tVC_LMAC_TX_CTRL_HEADER);
		gTxCtrlHdrBbpCmd.ctrl.fields.head_len = VC_SWAP_16(ctrlLen);
		gTxCtrlHdrBbpCmd.seq = vc_lmac_incrase_ctrl_seq_num();
		gTxCtrlHdrBbpCmd.pktLen = VC_SWAP_16(pBbpRawCmd->bbpCmdLen);
		gTxCtrlHdrBbpCmd.PBNum = 0;
		gTxCtrlHdrBbpCmd.DT = 0;
		gTxCtrlHdrBbpCmd.TMI = 0;
		//vc_lmac_log_ctrl_header((vc_uint8 *)&gTxCtrlHdrBbpCmd, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		vc_lmac_tx_pkt_init(&pkt);
		vc_lmac_tx_pkt_attach(&pkt, &gTxCtrlHdrBbpCmd, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		vc_lmac_tx_pkt_attach(&pkt, &pBbpRawCmd->bbpCmd[0], pBbpRawCmd->bbpCmdLen);

		if (pBbpRawCmd->bandSetting) {
			gLMAC->lmacBand = pBbpRawCmd->band;
			gLMAC->lmacBandSearch.BeaconReceive = 1;
			gLMAC->lmacBandSearch.bandSearchingRunning = 0;
		}
		if (pBbpRawCmd->toneMaskSetting) {
			gLMAC->lmacToneMask = pBbpRawCmd->toneMaskSetting;
		}
		LMAC_CHANGE_STATE(LMAC_WAIT_CSMA_NON);
		vc_lmac_send_tx_pkt_to_dma(&pkt, VC_KICK_DMA_BBP_PKT, gTxCtrlHdrBbpCmd.ctrl.fields.type);
		lastTypeOfLMAC_WAIT_CSMA_NON = 3;
		lastTypeOfBBPcmdType = pBbpRawCmd->bbpCmd[0];
	} else {
    printf("LMAC is busy, state: %u \r\n", gLMAC->lmacState);
		gTxRawCmdSend[gTxBbpRawCmdIdx].isUsed = 1;
		vc_memcpy(&gTxRawCmdSend[gTxBbpRawCmdIdx].RawCmd,
				  pBbpRawCmd,
				  sizeof(tBbpRawCmd));
		gTxBbpRawCmdIdx++;
		gTxBbpRawCmdIdx %= VC_LMAC_RAW_CMD_DELAY_SEND_NUM;
		gTxBbpRawCmdCount++;
	}
	//OS_ExitCritical(mask);
}

vc_uint16 vc_lmac_cal_ofdma_symbol_number(vc_uint8 eTmi, vc_uint8 iTmi, vc_uint16 fcToneNum, vc_uint8 toneMaskNum)
{
	vc_uint16 usedCarrierNum = 0;
	vc_uint16 carrNumPerGroup = 0;
	vc_uint16 ofdmaNum = 0;

	if (eTmi) {
		usedCarrierNum =
			((fcToneNum - toneMaskNum) / gMapSymTMI_ALL_E.InfoTMI[eTmi].intNum) * gMapSymTMI_ALL_E.InfoTMI[eTmi].intNum;
		carrNumPerGroup =
			usedCarrierNum / gMapSymTMI_ALL_E.InfoTMI[eTmi].copyNum;
		if (eTmi == 1 || eTmi == 2) {
			ofdmaNum =
				(((((gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize * 8 * 18) / 16) - 1) / carrNumPerGroup) / gMapSymTMI_ALL_E.InfoTMI[eTmi].BPC) + 1;
		} else {
			ofdmaNum =
				((((gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize * 8 * 2) - 1) / carrNumPerGroup) / gMapSymTMI_ALL_E.InfoTMI[eTmi].BPC) + 1;
		}
	} else {
		usedCarrierNum =
			((fcToneNum - toneMaskNum) / gMapSymTMI_ALL.InfoTMI[iTmi].intNum) * gMapSymTMI_ALL.InfoTMI[iTmi].intNum;
		carrNumPerGroup =
			(usedCarrierNum / gMapSymTMI_ALL.InfoTMI[iTmi].copyNum);
		ofdmaNum =
			((((gMapSymTMI_ALL.InfoTMI[iTmi].PbSize * 8 * 2) - 1) / carrNumPerGroup) / gMapSymTMI_ALL.InfoTMI[iTmi].BPC) + 1;
	}
	return ofdmaNum;
}

vc_uint8 vc_lmac_get_pkt_info_by_tmi(
	vc_lmac_band_plan band,
	vc_uint8 pbNum,
	vc_uint8 eTmi,
	vc_uint8 iTmi,
	vc_uint16 *pktLen,
	vc_uint16 *FL,
	vc_uint16 *symNum,
	vc_uint16 *ackDur)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;

	vc_uint16 pPktLen = 0;
	//vc_uint16 pFL = 0;
	vc_uint16 pSymNum = 0;
	vc_uint8 retval = 0;
	vc_uint16 calSymboNum = 0;
	vc_uint8 toneMask = 0;
	float pAckDur = 0;
	float pPktPer = 0;
	float pPktTime = 0;

	/*+----------------------------------------------------------------------------------------------------------+*/
	/*|                         |                                  FL with SACK                                  |*/
	/*+----------------------------------------------------------------------------------------------------------+*/
	/*|     Pmb    |     FC     |               Payload              |  RIFS  |            Sack         |  CIFS  |*/
	/*+----------------------------------------------------------------------------------------------------------+*/
	/*|13*40.96(us)| 4*59.28(us)|2*59.28|((symNum*pbNum)-2)*51.52(us)| 400(us)|13*40.96(us)| 4*59.28(us)| 400(us)|*/
	/*+----------------------------------------------------------------------------------------------------------+*/
	/*|13*40.96(us)|12*59.28(us)|2*59.28|((symNum*pbNum)-2)*51.52(us)| 400(us)|13*40.96(us)|12*59.28(us)| 400(us)|*/
	/*+----------------------------------------------------------------------------------------------------------+*/

	switch (band)
	{
		case BPLC_BAND_0: {
			if (gLMAC->lmacToneMask != 0) {
				toneMask = 40;
			}
			if (eTmi == 0) {
				pAckDur = ((gMapSymTMI_ALL.pmbTime * 13) + (gMapSymTMI_ALL.fcTime * 4));
				pPktLen = gMapSymTMI_ALL.InfoTMI[iTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL.fcTime * 2);
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 411, toneMask);
				pSymNum = calSymboNum;
				//pPktTime = (gMapSymTMI_ALL.pldTime * pbNum * pSymNum) / 100;
				pPktTime = (((pbNum * pSymNum) - 2) * gMapSymTMI_ALL.pldTime);
			} else if (eTmi > 0) {
				pAckDur = ((gMapSymTMI_ALL_E.pmbTime * 13) + (gMapSymTMI_ALL_E.fcTime * 4));
				pPktLen = gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL_E.fcTime * 2);
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 411, toneMask);
				pSymNum = calSymboNum;
				//pPktTime = (gMapSymTMI_ALL_E.pldTime * pbNum * pSymNum) / 100;
				pPktTime = ((((pbNum * pSymNum) - 2) * gMapSymTMI_ALL_E.pldTime));
			}
			break;
		}

		case BPLC_BAND_1: {
			if (gLMAC->lmacToneMask != 0) {
				toneMask = 5;
			}
			if (eTmi == 0) {
				pAckDur = ((gMapSymTMI_ALL.pmbTime * 13) + (gMapSymTMI_ALL.fcTime * 12));
				pPktLen = gMapSymTMI_ALL.InfoTMI[iTmi].PbSize;
				pPktPer = ((gMapSymTMI_ALL.fcTime * 2));
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 131, toneMask);
				pSymNum = calSymboNum;
				//pPktTime = (gMapSymTMI_ALL.pldTime * pbNum * pSymNum) / 100;
				pPktTime = (((pbNum * pSymNum) - 2) * gMapSymTMI_ALL.pldTime);
			} else if (eTmi != 0) {
				pAckDur = ((gMapSymTMI_ALL_E.pmbTime * 13) + (gMapSymTMI_ALL_E.fcTime * 12));
				pPktLen = gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL_E.fcTime * 2);
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 131, toneMask);
				pSymNum = calSymboNum;
				//pPktTime = (gMapSymTMI_ALL_E.pldTime * pbNum * pSymNum) / 100;
				pPktTime = ((((pbNum * pSymNum) - 2) * gMapSymTMI_ALL_E.pldTime));
			}
			break;
		}

		case BPLC_BAND_2: {
			if (gLMAC->lmacToneMask != 0) {
				toneMask = 5;
			}
			if (eTmi == 0) {
				pAckDur = ((gMapSymTMI_ALL.pmbTime * 13) + (gMapSymTMI_ALL.fcTime * 12));
				pPktLen = gMapSymTMI_ALL.InfoTMI[iTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL.fcTime * 2);
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 89, toneMask);
				pSymNum = calSymboNum;
				//pPktTime = (gMapSymTMI_ALL.pldTime * pbNum * pSymNum) / 100;
				pPktTime = (((pbNum * pSymNum) - 2) * gMapSymTMI_ALL.pldTime);
			} else if (eTmi > 0) {
				pAckDur = ((gMapSymTMI_ALL_E.pmbTime * 13) + (gMapSymTMI_ALL_E.fcTime * 12));
				pPktLen = gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL_E.fcTime * 2);
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 89, toneMask);
				pSymNum = calSymboNum;
				//pPktTime = (gMapSymTMI_ALL_E.pldTime * pbNum * pSymNum) / 100;
				pPktTime = ((((pbNum * pSymNum) - 2) * gMapSymTMI_ALL_E.pldTime));
			}
			break;
		}

		case BPLC_BAND_3: {
			if (gLMAC->lmacToneMask != 0) {
				toneMask = 49;
			}
			if (eTmi == 0) {
				pAckDur = ((gMapSymTMI_ALL.pmbTime * 13) + (gMapSymTMI_ALL.fcTime * 12));
				pPktLen = gMapSymTMI_ALL.InfoTMI[iTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL.fcTime * 2);
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 49, toneMask);
				pSymNum = calSymboNum;
				//pPktTime = (gMapSymTMI_ALL.pldTime * pbNum * pSymNum) / 100;
				pPktTime = (((pbNum * pSymNum) - 2) * gMapSymTMI_ALL.pldTime);
			} else if (eTmi > 0) {
				pAckDur = ((gMapSymTMI_ALL_E.pmbTime * 13) + (gMapSymTMI_ALL_E.fcTime * 12));
				pPktLen = gMapSymTMI_ALL_E.InfoTMI[eTmi].PbSize;
				pPktPer = (gMapSymTMI_ALL_E.fcTime * 2);
				calSymboNum = vc_lmac_cal_ofdma_symbol_number(eTmi, iTmi, 49, toneMask);
				pSymNum = calSymboNum;
				//pPktTime = (gMapSymTMI_ALL_E.pldTime * pbNum * pSymNum) / 100;
				pPktTime = ((((pbNum * pSymNum) - 2) * gMapSymTMI_ALL_E.pldTime));
			}
			break;
		}
	}
	*(pktLen) = pPktLen * pbNum;
	*(FL) = ((pPktPer + pPktTime + LMAC_CIFS + LMAC_RIFS_OFFSET) / 10);
	*(symNum) = (pSymNum);
	*(ackDur) = ((pAckDur + LMAC_RIFS) / 10);
	#if 0
	ULOG(ULL_DBG, "symb:%d, pktPer: %d,pktTime: %d,AckDur: %d",
		 pSymNum, (int)pPktPer, (int)pPktTime, (int)pAckDur);
	#endif
	if (pPktLen != 0 && pSymNum != 0) {
		retval = 1;
	} else {
		retval = 0;
	}
	return retval;
}

vc_uint32 vc_lmac_get_NID()
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	return gLMAC->LMAC_NID;
}

vc_uint32 vc_lmac_get_NNID()
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	return gLMAC->LMAC_NNID;
}

vc_uint16 vc_lmac_get_PCO()
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	return gLMAC->LMAC_PTEI;
}

void vc_lmac_fill_tx_desc(
	tVC_LMAC_TX_CTRL_HEADER *pTxCtrlHdr,
	vc_uint8 pbType,
	vc_uint8 extTMI,
	vc_uint8 tmi,
	vc_uint16 pktLen,
	vc_uint8 pbNum,
	vc_uint32 NTB)
{
	vc_uint16 tmpLen = 0;

	if (pbType == BEACON_F) {
		pTxCtrlHdr->ctrl.fields.type = TX_CTRL_HDR_CN_BEACON_TYPE;
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
	if (extTMI == 0) {
		pTxCtrlHdr->TMI = tmi;
		pTxCtrlHdr->TMIType = 0;
	} else {
		pTxCtrlHdr->TMI = extTMI;
		pTxCtrlHdr->TMIType = 1;
	}
}

vc_uint8 isDeviceInExtendCmdBandSetting()
{
  return 0;
}

extern volatile uint32_t systick_counter;
vc_uint32 LMAC_GET_CURRENT_TIME()
{
	return systick_counter;
}

vc_uint32 vc_lmac_random()
{
	vc_uint32 randomSeed;
	randomSeed = LMAC_GET_CURRENT_TIME() + rand() * 1103515245 + 12345678;
	return randomSeed;
}

vc_uint32 vc_lmac_get_csma_backoff(vc_uint8 backoff_exponent)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	vc_uint32 backoff_period = 0;
	vc_uint16 unitPeriod = 0;

	unitPeriod = gLMAC->lmacCsma.period;
	backoff_period = ((vc_lmac_random() % ((1 << backoff_exponent) - 1))) * unitPeriod;
	if (backoff_period == 0) {
		backoff_period = LMAC_CSMA_DEFAULT_PERIOD;
	}
	return backoff_period;
}

vc_uint32 vc_lmac_sch_get_current_ms()
{
	return systick_counter;
}

vc_uint32 vc_lmac_sch_get_csma_end_ms()
{
	return curr_csma_end_ms;
}

void vc_lmac_cfg_hw_csma_retry(vc_uint32 backoffTime)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	vc_int32 csmaProtectValue = 0;
	vc_uint8 dbgLevel = 0;

	csmaProtectValue = vc_lmac_sch_get_csma_end_ms() - vc_lmac_sch_get_current_ms();

	if ((csmaProtectValue < 1000) && (csmaProtectValue >= 500)) {
		if (backoffTime > (50 * 1000)) {
			backoffTime = (vc_lmac_random() % 50000);
		}
		dbgLevel = 1;
	} else if ((csmaProtectValue < 500) && (csmaProtectValue >= 300)) {
		if (backoffTime > (25 * 1000)) {
			backoffTime = (vc_lmac_random() % 25000);
		}
		dbgLevel = 2;
	} else if ((csmaProtectValue < 300) && (csmaProtectValue >= 100)) {
		if (backoffTime > (20 * 1000)) {
			backoffTime = ((vc_lmac_random() % 20000) + 1);
		}
		dbgLevel = 3;
	} else if ((csmaProtectValue < 100) && (csmaProtectValue >= 50)) {
		if (backoffTime > (10 * 1000)) {
			backoffTime = (vc_lmac_random() % 10000) + 1;
		}
		dbgLevel = 4;
	} else if (csmaProtectValue < 50) {
		if (backoffTime > (5 * 1000)) {
			backoffTime = (vc_lmac_random() % 5000) + 1;
		}
		dbgLevel = 5;
	} else {
	}
	/*if any random backoffTime is too lager, set the limint*/
	if (backoffTime >= ((csmaProtectValue * 1000) / 2)) {
		backoffTime = (vc_lmac_random() % 25000);
	}

	printf("BOFT:%d,%u,%u\r\n", csmaProtectValue, dbgLevel, backoffTime);
	cnMacReg->CNSCH_TSR2 = backoffTime;
	cnMacReg->CNSCH_RTY_CR = 0x04;
	return;
}

vc_uint8 vc_lmac_init_csma(
	eVC_SACK_TYPE ackNeed,
	eVC_CSMA_PKT_TYPE pktType,
	vc_uint8 fromQ,
	vc_uint32 txDuration,
	vc_uint16 ackDur,
	vc_uint8 rtyTimes)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	vc_uint32 lmacCsmaFrameLengthUs = 0;
	vc_uint32 value = 0x00;
	vc_uint32 backoff_period;
	//vc_int32 checkCsmaTail = 0;
	if (isDeviceInExtendCmdBandSetting() == 1) {
		gLMAC->lmacCsma.minBE = 3;
		gLMAC->lmacCsma.maxBE = 10;
		gLMAC->lmacCsma.maxRetryCnt = 12;
	}
	#if 0
	if (rtyTimes <= 5) {
		gLMAC->lmacCsma.minBE = 3;
		gLMAC->lmacCsma.maxBE = 10;
	} else if ((rtyTimes > 5) && (rtyTimes <= 10)) {
		gLMAC->lmacCsma.minBE = 6;
		gLMAC->lmacCsma.maxBE = 10;
	} else {
		gLMAC->lmacCsma.minBE = 8;
		gLMAC->lmacCsma.maxBE = 10;
	}
	#endif
	gLMAC->lmacCsma.sackNeed = ackNeed;
	gLMAC->lmacCsma.sackGet = 0;
	gLMAC->lmacCsma.sackDuration = ((ackDur * 10) / 1000) + 6;
	gLMAC->lmacCsma.pktType = pktType;
	gLMAC->lmacCsma.fromQ = fromQ;
	if (ackNeed) {
		value = 0x11000000;
	} else {
		value = 0x01000000;
	}
	if (txDuration == 0) {
		lmacCsmaFrameLengthUs = 0x6912;
		value |= lmacCsmaFrameLengthUs;                   /*0x3E8*/
	} else {
		if (ackNeed) {
			lmacCsmaFrameLengthUs = (txDuration * 10) +   /*FL*/
									(ackDur * 10) + 1000; /*SACK*/
			value |= lmacCsmaFrameLengthUs;
		} else {
			lmacCsmaFrameLengthUs = (txDuration * 10);    /*FL*/
			value |= lmacCsmaFrameLengthUs;
		}
	}
	gLMAC->lmacCsma.kickSofFL = lmacCsmaFrameLengthUs;
	cnMacReg->CNSCH_TSR1 = value;
	if ((cnMacReg->CNSCH_TSR1 & 0x00FFFFFF) == 0) {
		//VC_ASSERT(0, "TxDur is Zero!!");
    printf("TxDur is Zero!!!\r\n");
    while(1);
	}
	lmac_csma_backoff_exponent = gLMAC->lmacCsma.minBE;
	// if (pktType == ITNWC_PKT) {
	// 	backoff_period = 1;
	// } else {
	// 	if (gExtendCmd.mode == extCmdMode4_phyReply ||
	// 		gExtendCmd.mode == extCmdMode8_vertexcomTesting ||
	// 		lmac_proformance_test_mode ||
	// 		gLMAC->lmacCsma.csmaDefaultForce) {
	// 		backoff_period = 1;
	// 		gLMAC->lmacCsma.csmaDefaultForce = 0;//reset
	// 	} else {
	// 		backoff_period = vc_lmac_get_csma_backoff(lmac_csma_backoff_exponent);
	// 		checkCsmaTail = vc_lmac_sch_get_csma_end_ms() - vc_lmac_sch_get_current_ms();
	// 		if (checkCsmaTail <= VC_LMAC_CSMA_TAIL_PROTECT) {
	// 			printf("InitCsmaAsTail!!! %d ms\r\n", checkCsmaTail);
	// 			return 1;
	// 		}
	// 		if (vcLessMod2p32(checkCsmaTail, CEIL_DIV(backoff_period + lmacCsmaFrameLengthUs, 1000))) {
	// 			printf("CsmaBackoff > Tail!!! %d ms\r\n", checkCsmaTail);
	// 			return 1;
	// 		}
	// 	}
	// }
  backoff_period = 1;
	vc_lmac_cfg_hw_csma_retry(backoff_period);
	lmac_num_of_backoffs = 1;
	csmaCurrFrameLengthUs = lmacCsmaFrameLengthUs;
	csmaLastBackoffPeriodUs = backoff_period;
	return 0;
}

void vc_lmac_cfg_hw_csma_abort(vc_uint8 debug)
{
	//LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	cnMacReg->CNSCH_TSR2 = LMAC_CSMA_DEFAULT_PERIOD;
	cnMacReg->CNSCH_RTY_CR = 0x01;
	csmaAbortFlagEnable = 1;
	//printf("#csmaAbort:%d\r\n", debug);
	return;
}

void vc_lmac_get_next_csma_para()
{
	 LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;

	// vc_uint32 backoffTime = 0;
	// vc_uint32 curr_ms = 0;
	// vc_uint32 csma_end_ms = 0;
	// vc_int32 csmaProtectValueMs = 0;
	// vc_uint32 csmaSchedLengthUs = 0;
	//
	// if (lmac_csma_backoff_exponent < gLMAC->lmacCsma.maxBE) {
	// 	lmac_csma_backoff_exponent++;
	// } else {
	// 	lmac_csma_backoff_exponent = gLMAC->lmacCsma.maxBE;
	// }
	// backoffTime = vc_lmac_get_csma_backoff(lmac_csma_backoff_exponent);
	//
	// if (gLMAC->lmacCsma.pktType == ITNWC_PKT) {
	// 	if (lmac_num_of_backoffs > 1) {
	// 	} else {
	// 		vc_lmac_cfg_hw_csma_abort(0);
	// 		lmac_num_of_backoffs++;
	// 	}
	// } else {
	// 	curr_ms = vc_lmac_sch_get_current_ms();
	// 	csma_end_ms = vc_lmac_sch_get_csma_end_ms();
	// 	csmaProtectValueMs = csma_end_ms - curr_ms;
	// 	if (csmaProtectValueMs <= VC_LMAC_CSMA_TAIL_PROTECT) {
	// 		vc_lmac_cfg_hw_csma_abort(4);
	// 		lmac_num_of_backoffs++;
	// 		return;
	// 	}
	// 	if (lmac_num_of_backoffs >= gLMAC->lmacCsma.maxRetryCnt) {
	// 		vc_lmac_cfg_hw_csma_abort(1);
	// 		lmac_num_of_backoffs++;
	// 	} else {
	// 		curr_ms = vc_lmac_sch_get_current_ms();
	// 		csma_end_ms = vc_lmac_sch_get_csma_end_ms();
	// 		if (vcLessMod2p32(csma_end_ms, curr_ms)) {
	// 			vc_lmac_cfg_hw_csma_abort(2);
	// 			lmac_num_of_backoffs++;
	// 		} else {
	// 			csmaSchedLengthUs = csmaLastBackoffPeriodUs + backoffTime + csmaCurrFrameLengthUs;
	// 			if ((csmaProtectValueMs * 1000) >= csmaSchedLengthUs) {
	// 				vc_lmac_cfg_hw_csma_retry(backoffTime);
	// 				lmac_num_of_backoffs++;
	// 			} else {
	// 				vc_lmac_cfg_hw_csma_abort(3);
	// 				lmac_num_of_backoffs++;
	// 			}
	// 		}
	// 	}
	// }

  if (lmac_num_of_backoffs >= gLMAC->lmacCsma.maxRetryCnt)
  {
    vc_lmac_cfg_hw_csma_abort(0);
    printf("#abort csma\r\n");
  }

  lmac_num_of_backoffs++;

  return;
}

void vc_lmac_tx_sof_pkt_f_cmd_sig_test(
	vc_uint8 isPassPkt,
	vc_uint16 DTEI,
	vc_uint8 extTmi,
	vc_uint8 tmi,
	vc_uint8 pbCount,
	vc_uint8 *macAddr,
	vc_uint8 ledBitMap,
	vc_uint8 ledSwitch)
{

	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	tVC_DMAC_PACKET pkt;
	tVC_phy_test_payload pPhyTest;
	vc_uint16 tx_len = 0;
	vc_uint8 bbpIsIdle = 0;
	//vc_uint16 onePbLen = 0;
	vc_uint16 FL = 0;
	vc_uint16 symNum = 0;
	vc_uint16 ackDur = 0;
	vc_uint16 i;
	vc_ntb32 pNTB = 0x00;

	vc_lmac_get_pkt_info_by_tmi(gLMAC->lmacBand, pbCount, extTmi, tmi, &tx_len, &FL, &symNum, &ackDur);

	vc_memset(&gTxCtrlHdrSigTest, 0x00, sizeof(tVC_LMAC_TX_CTRL_HEADER));
	vc_lmac_fill_tx_desc(&gTxCtrlHdrSigTest, SOF_F, extTmi, tmi, (tx_len * pbCount), pbCount, 0);
	vc_memset(&gTxCnSofFc, 0x0, sizeof(tCN_SOF_FC));

	gTxCnSofFc.delType = SOF_F;
	gTxCnSofFc.NID = vc_lmac_get_NID();
	gTxCnSofFc.netType = 0;
	gTxCnSofFc.SofVarSTEI = gLMAC->LMAC_STEI;
	gTxCnSofFc.SofVarDTEI = DTEI;
	gTxCnSofFc.SofVarLID = 0xAA;
	gTxCnSofFc.SofVarFL = FL;
	gTxCnSofFc.SofVarPBCount = (pbCount);
	gTxCnSofFc.SofVarTMI = tmi;
	gTxCnSofFc.SofVarExtTMI = extTmi;
	gTxCnSofFc.SofVarSymbolNum = symNum;

	//print_fc_sof_param(&gTxCnSofFc);
	vc_lmac_cfg_arq_MyTEI(gLMAC->LMAC_STEI);

	printf("<-T:SigTest,%d,%d,%d,%06X\r\n", tmi, extTmi, pbCount, gTxCnSofFc.NID);

	pNTB = vc_phy_get_ntb();
	vc_memset(&pPhyTest, 0x00, sizeof(tVC_phy_test_payload));

	pPhyTest.VCTAG = 0xF1ABF2CD;
	pPhyTest.NTB = pNTB;
	pPhyTest.SEQNUM = gPhyTestCount;
	pPhyTest.testMode = 1;

	if (isPassPkt) {
		pPhyTest.pktType = 2;
		vc_memcpy(&pPhyTest.passAddress[0], macAddr, 6);
	}

	gPhyTestCount++;
	vc_memcpy(
		&dma_tx_data[0],
		&pPhyTest,
		sizeof(tVC_phy_test_payload));

	bbpIsIdle =	vc_phy_check_idle();

	if (bbpIsIdle) {
		//vc_lmac_log_ctrl_header((vc_uint8 *)&gTxCtrlHdrSigTest, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		vc_lmac_tx_pkt_init(&pkt);
		vc_lmac_tx_pkt_attach(&pkt, &gTxCtrlHdrSigTest, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		vc_lmac_tx_pkt_attach(&pkt, &gTxCnSofFc, sizeof(tCN_SOF_FC));
		for (i = 0; i < pbCount; i++) {
			vc_lmac_tx_pkt_attach(&pkt, &dma_tx_data, tx_len);
		}
		pTheLastCsma = LAST_CSMA_LONGP;
		gLMAC->lmacCsma.sackNeed = 0;
		LMAC_CHANGE_STATE(LMAC_WAIT_CSMA_NON);
		vc_lmac_init_csma(VC_SACK_NOT, SOF_PKT, MAC_TXQ_RADIO_NULL, FL, ackDur, 0);
		vc_lmac_send_tx_pkt_to_dma(&pkt, VC_KICK_DMA_LONG_PKT, gTxCtrlHdrSigTest.ctrl.fields.type);
		lastTypeOfLMAC_WAIT_CSMA_NON = 5;
	}
	return;
}

vc_int8 vc_lmac_decide_bcn_tmi(vc_uint16 bcnPayloadLens)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	vc_uint8 bcnTmi = 0;
	//static vc_uint8 extra_tx_power = 0;

	if (gLMAC->lmacBand == BPLC_BAND_0) {
		if (bcnPayloadLens == 136) {
			bcnTmi = 4;
		} else {
			bcnTmi = 7;
		}
	} else if (gLMAC->lmacBand == BPLC_BAND_1) {
		if (bcnPayloadLens == 136) {
			bcnTmi = 4;
		} else {
			bcnTmi = 7;
		}
	} else if (gLMAC->lmacBand == BPLC_BAND_2) {
		if (bcnPayloadLens == 136) {
			bcnTmi = 4;
		} else {
			bcnTmi = 8;
		}
	} else if (gLMAC->lmacBand == BPLC_BAND_3) {
		if (bcnPayloadLens == 136) {
			bcnTmi = 4;
		} else {
			bcnTmi = 10;
		}
	} else {
		bcnTmi = 20;
	}
	return bcnTmi;
}

extern vc_uint8 vc_phy_lmac_cfg_bcn_time_slot(vc_uint8 bcnTimeSlotLens);

#define xCRC32_INIT 0xFFFFFFFF
#define xCRC32_POLY 0xEDB88320

vc_uint32 MAC_DO_XCRC_32(vc_uint8 *buf, vc_uint16 len)
{
	unsigned int byte, crc, mask;
	int i, j;
	crc = xCRC32_INIT;
	for (i = 0; i < len; i++) {
		byte = buf[i];
		crc = crc ^ byte;
		for (j = 7; j >= 0; j--) {
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (xCRC32_POLY & mask);
		}
	}
	crc ^= 0xFFFFFFFF;
	return crc;
}

void vc_lmac_fill_tx_bcn_fc(
	tCN_BEACON_FC *pTxCnBconFc,
	vc_uint32 tdmaNTB,
	vc_uint8 tmi,
	vc_uint16 symNum,
	vc_uint8 phase)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	pTxCnBconFc->delType = BEACON_F;
	pTxCnBconFc->netType = 0;
	pTxCnBconFc->NID = vc_lmac_get_NID();
	pTxCnBconFc->BconVar_timeStamp = tdmaNTB + 12500;
	if (gLMAC->lmacSch.bconRole == LMAC_ROLE_CCO) {
		pTxCnBconFc->BconVar_STEI = 0x001;
	} else {
		pTxCnBconFc->BconVar_STEI = gLMAC->LMAC_STEI;
	}
	pTxCnBconFc->BconVar_TMI = tmi;
	pTxCnBconFc->BconVar_symboNum = symNum;
	pTxCnBconFc->BconVar_phaseLine = phase;
	pTxCnBconFc->BconVar_rsv2 = 0;
	return;
}

void vc_lmac_send_tx_bcon_pkt_to_dma(
	tVC_DMAC_PACKET *pkt,
	vc_uint32 tdmaNTB,
	vc_uint8 bcnTSlot,
	vc_uint8 txType,
	vc_uint32 ntb,
	vc_uint8 phase,
	vc_uint32 wNTB)
{
	//volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	vc_uint32 timeoutDmaCheck = 0;
	//vc_uint32 mask = 0x00;
	vc_uint8 retval = 0;
	//vc_uint32 currNTB = 0;
	//vc_uint16 i = 0;

	if (waitTxpDoneFlag) {
		if (vcLessMod2p32((waitTxpDoneNTB + (25000) * 50), vc_phy_get_ntb()) == 1) {
			printf("TxpDoneNotFinish!!%u us\r\n", (vc_phy_get_ntb() - waitTxpDoneNTB) / 25);
			//vc_lmac_log_dsp_dump();
			waitTxpDoneFlag = 0;
		}
	}
	txpDoneNotFinished = 1;
	//mask = OS_EnterCritical();
	gLMAC->lmacIrqCount.kickDmaWant++;
	// if (1) {
	// 	/*debugTx*/
	// 	lmac_dbg_tx pDbgTx;
	// 	vc_memset(&pDbgTx, 0x00, sizeof(lmac_dbg_tx));
	// 	pDbgTx.kickDmaType = VC_KICK_DMA_BEACON_SEND;
	// 	pDbgTx.kickDmaSeqNum = ctrlSeqNum;
	// 	pDbgTx.ntb = vc_phy_get_ntb();
	// 	pDbgTx.txType = txType;
	// 	vc_lmac_dbg_tx_handler(&pDbgTx);
	// }
	if (gLMAC->lmacState != LMAC_IDLE) {
		//vc_lmac_tx_led_blink();
	}

	timeoutDmaCheck = vc_phy_get_ntb();

	do {
		retval = vc_lmac_fill_dma_desc(pkt);
		if (vcLessMod2p32(timeoutDmaCheck + 2500, vc_phy_get_ntb()) == 1) {
			break;
		}
	} while (retval == 0);

	if (retval) {
    gLMAC->lmacIrqCount.kickBcn++;
    vc_lmac_fill_dma_owner_bit(pkt);
    LMAC_KICK_TX_DMA();
    //vc_lmac_log_dsp_ir(1);
    waitTxpDoneFlag = 1;
    waitTxpDoneNTB = vc_phy_get_ntb();
	} else {
		if (vc_phy_check_idle() == 0) {
			gLMAC->lmacIrqCount.kickDmaDspBusy++;
		}
		printf("[Warning]->DmaNotReturnIdle!!\r\n");
		//lmac_dump_tx_desc();
		//vc_lmac_dump_dsp_hwmac_info();
	}
	//OS_ExitCritical(mask);
}

void vc_lmac_tx_bcon_pkt_f_sch(
	vc_uint32 tdmaNTB,
	vc_uint8 phase,
	vc_uint8 role,
	vc_uint16 beaconLen,
	vc_uint8 *beaconPtr,
	vc_bcn_timeslot_s *timeslotPtr,
	vcCsmaSlotInfo_s *csmainfoPtr,
	vc_uint32 ntb)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	tVC_DMAC_PACKET pkt;
	vc_uint16 tx_len = 0;
	vc_uint8 pbNum = 1;
	vc_uint8 etmi = 0;
	vc_uint8 tmi = 0;
	vc_uint16 FL = 0;
	vc_uint16 ackDur = 0;
	vc_uint16 symNum = 0;
	vc_uint32 BPCS = 0;
	vc_uint8 bbpIsIdle = 0;

	tmi = vc_lmac_decide_bcn_tmi(beaconLen);
	if (tmi > 15) {
		return;
	}

	if (vcLessMod2p32(tdmaNTB, vc_phy_get_ntb()) == 1) {
		printf("Phase %d BcnIsExpire!!\r\n", phase);
		return;
	}

	if (lmac_proformance_test_mode) {
		vc_phy_lmac_cfg_bcn_time_slot(25 + 5);
	} else {
		vc_phy_lmac_cfg_bcn_time_slot(timeslotPtr->bcn_slot_length);
	}

	#if 0
	bcnStartntb = vc_phy_get_ntb();
	do {
		bbpIsIdle = vc_phy_check_idle();
		if (bbpIsIdle == 0) {
			for (j = 0; j <= 10000; j++) {
				k++;
			}
		}
		if (i > 100) {
			break;
		}
		i++;
	} while (bbpIsIdle == 0);
	#endif

	bbpIsIdle =	vc_phy_check_idle();

	if (bbpIsIdle) {
		LMAC_CHANGE_STATE(LMAC_CSMA_IDLE);
	}

	if ((bbpIsIdle && (gLMAC->lmacState <= LMAC_CSMA_IDLE))) {
		BPCS = MAC_DO_XCRC_32(beaconPtr, beaconLen - 7);
		vc_memcpy(&beaconPtr[beaconLen - 7], &BPCS, 4);
		vc_lmac_get_pkt_info_by_tmi(
			gLMAC->lmacBand, pbNum, etmi, tmi, &tx_len, &FL, &symNum, &ackDur);
		vc_memset(&gTxCtrlHdrBCN, 0x00, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		vc_lmac_fill_tx_desc(&gTxCtrlHdrBCN, BEACON_F, 0, tmi, tx_len, pbNum, tdmaNTB);
		vc_memset(&gTxCnBconFc, 0x00, sizeof(tCN_BEACON_FC));
		vc_lmac_fill_tx_bcn_fc(&gTxCnBconFc, tdmaNTB, tmi, symNum, phase);
		//vc_lmac_log_ctrl_header((vc_uint8 *)&gTxCtrlHdrBCN, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		vc_lmac_tx_pkt_init(&pkt);
		vc_lmac_tx_pkt_attach(&pkt, &gTxCtrlHdrBCN, sizeof(tVC_LMAC_TX_CTRL_HEADER));
		vc_lmac_tx_pkt_attach(&pkt, &gTxCnBconFc, sizeof(tCN_BEACON_FC));
		vc_lmac_tx_pkt_attach(&pkt, beaconPtr, beaconLen);
		gLMAC->lmacBcn.checkbcnSendComplete = 1;
		LMAC_CHANGE_STATE(LMAC_WAIT_BCN_TXP_DONE);

		vc_lmac_send_tx_bcon_pkt_to_dma(
			&pkt,
			tdmaNTB,
			timeslotPtr->bcn_slot_length,
			gTxCtrlHdrBCN.ctrl.fields.type,
			ntb,
			phase,
			tdmaNTB);

	} else {
		vc_lmac_cfg_phy_rx_enable();
    printf("#TxBeaconAbort!!!\r\n");
	}

  return;
}

