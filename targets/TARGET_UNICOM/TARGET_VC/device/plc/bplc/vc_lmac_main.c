#include <stdio.h>
#include "phy.h"
#include "vc_lmac.h"
#include "vc_lmac_dma_if.h"
#include "vc_lmac_rxh.h"

extern vc_ntb32 vc_phy_get_ntb();
extern void LMAC_KICK_RX_DMA();
extern void vc_lmac_get_next_csma_para();
extern vc_uint8 vc_phy_lmac_cfg_3p_gpio_finish(vc_uint8 isFinish);

vc_uint32 vc_lmac_ntb_before_rxcmp = 0;
vc_uint32 phy_rx_unavail_count = 0;
 
extern vc_uint8 waitTxpDoneFlag;
extern vc_uint8 txpDoneNotFinished;
extern vc_uint8 csmaAbortFlagEnable;

extern volatile tVC_DMAC_DESC g_dmaTxDesc[VC_DMAC_TX_NR_DESC];
extern volatile tVC_DMAC_DESC g_dmaRxDesc[VC_DMAC_RX_NR_DESC];
extern volatile vc_uint8 dmaRxDescIdx;

vc_uint8 lmac_process_dsp_arq(vc_uint16 *STEI, vc_uint16 *DTEI)
{
	volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	vc_uint16 tmpSTEI = ((phyReg->phy_ir2 >> 20) & 0xFFF);
	vc_uint16 tmpDTEI = ((phyReg->phy_cr2 >> 4) & 0xFFF);
	vc_uint8 nackAck = ((phyReg->phy_ir2 >> 11) & 0x01);

	//ULOG(ULL_INF, "ACK:%d,%03X->%03X", nackAck, tmpSTEI, tmpDTEI);
	if (nackAck) { /*NACK*/
		*DTEI = tmpDTEI;
		*STEI = tmpSTEI;
		return 0;
	} else {       /*ACK*/
		*DTEI = tmpDTEI;
		*STEI = tmpSTEI;
		return 1;
	}
	return 1;
}

void lmac_process_sack_irq_handler()
{
  printf("#cnmmacISR_dsp_sack not implemented\r\n");
}

void lmac_process_isrTxPDone()
{
	//volatile tVCMAC_DEBUG_REGISTER *macDebug = (volatile tVCMAC_DEBUG_REGISTER *)VC_MAC_CN_DEBUG;
	//volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	//MAC_CONTEXT_PTR gMAC = MAC_PTR;
	//vc_uint32 hPingDelay = 0;
	//vc_uint32 curr_ms;
	//vc_uint32 csma_end_ms;

	if (gLMAC->lmacHighPing.Enable) {
    printf("lmacHighPing not implemented\r\n");
		return;
	}

	if (gLMAC->lmacBcn.checkbcnSendComplete) {
		gLMAC->lmacBcn.checkbcnSendComplete = 0;
		LMAC_CHANGE_STATE(LMAC_CSMA_IDLE);
	}

  if (gLMAC->lmacCsma.csmaAbort == 1) {
    gLMAC->lmacCsma.csmaAbort = 0;
  } else {
    if (gLMAC->lmacState == LMAC_WAIT_CSMA_ACK) {
			// sof sack txp done, wait sack
			//vc_lmac_mac_tx_cal_csma_usage(gLMAC->lmacCsma.kickSofFL);
			//gLMAC->lmacCsma.kickSofFL = 0;
			//LMAC_CHANGE_STATE(LMAC_CHECK_CSMA_ACK);
			//vc_lmac_start_sack(LMAC_CSMA_TIMESLOT_UNIT);
      printf("LMAC_WAIT_CSMA_ACK handler not implemented\r\n");
    } else if (gLMAC->lmacState == LMAC_WAIT_CSMA_NON) {
			// sof no sack txp done, delete current node & back to idle
			//vc_lmac_mac_tx_cal_csma_usage(gLMAC->lmacCsma.kickSofFL);
			//gLMAC->lmacCsma.kickSofFL = 0;
			//vc_lmac_delete_txq();
			LMAC_CHANGE_STATE(LMAC_CSMA_IDLE);
		} else {
      LMAC_CHANGE_STATE(LMAC_CSMA_IDLE);
    }
  }

  //printf("kickphy count: %u\r\n", gLMAC->lmacIrqCount.kickphy);
  //printf("kickBcn count: %u\r\n", gLMAC->lmacIrqCount.kickBcn);
}

void lmac_process_dsp_tx_info_irq()
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	vc_uint32 *phyIR2 = (vc_uint32 *)0x400111D4;
	//vc_uint32 *CNVCS = (vc_uint32 *)0x40011170;
	//vc_uint32 *CNSCH = (vc_uint32 *)0x40011180;
	vc_uint16 txFinish = (*(phyIR2) >> 12) & 0xFF;
	//vc_uint8 vcsFSM = (*(CNVCS)) & 0x0F;
	//vc_uint8 schFSM = (*(CNSCH)) & 0x0F;

	if (txFinish == LMAC_TX_KICK_BCN) {
		gLMAC->lmacIrqCount.kickBcn++;
	} else if (txFinish == LMAC_TX_KICK_SOF) {
		gLMAC->lmacIrqCount.kickSof++;
	} else if (txFinish == LMAC_TX_KICK_SACK) {
		gLMAC->lmacIrqCount.resp_sack++;
		gLMAC->lmacIrqCount.kickSack++;
	} else if (txFinish == LMAC_TX_KICK_ITNWC) {
		gLMAC->lmacIrqCount.kickItnwc++;
	} else if (txFinish == LMAC_TX_WAIT_KPHY_RXDROP) {
		gLMAC->lmacIrqCount.kickWPhyRxDp++;
	} else if (txFinish == LMAC_TX_FINISH_MOVE_BCN) {
	} else if (txFinish == LMAC_TX_DONE_FINISH) {
		gLMAC->lmacIrqCount.kickTxFinish++;
	} else if (txFinish == LMAC_TX_PBNUM_OV4PB_DROP_PKT) {
		printf("TxPktOver4PbDropPkt!!!\r\n");
		gLMAC->lmacIrqCount.tx_over4pb++;
		return;
	} else if (txFinish == LMAC_TX_DSP_WAIT_KICK_TIMEOUT) {
		printf("#### Dsp Wait Kick hw mac Kick Phy Timeout!!!\r\n");
		gLMAC->lmacIrqCount.kickDspWaitTimeout++;
		return;
	} else {
	}

  // STA START
	vc_phy_lmac_cfg_3p_gpio_finish(1);

	switch (txFinish)
	{
		case LMAC_TX_KICK_SACK: {
			printf("<a\r\n");
			break;
		}

		case LMAC_DSP_TRIGGLE_HV_DROP_LD_ON: {
			printf("#Dsp HV drop,LD ON!!!\r\n");
			break;
		}

		case LMAC_DSP_TRIGGLE_HV_DROP_LD_OFF: {
			printf("#Dsp HV drop, LD OFF!!!\r\n");
			break;
		}

		case LMAC_DSP_TRIGGLE_DYING_GASP_LD_ON: {
			printf("#Dsp Triggle Dying gasp, LD ON!!!\r\n");
			break;
		}

		case LMAC_DSP_TRIGGLE_DYING_GASP_LD_OFF: {
			printf("#Dsp Triggle Dying gasp, LD OFF!!!\r\n");
			break;
		}

		case LMAC_DSP_TRIGGLE_RETURN_82V_LD_ON: {
			printf("#DSP:8.2V LD ON\r\n");
			break;
		}

		case LMAC_DSP_TRIGGLE_RETURN_82V_LD_OFF: {
			printf("#DSP:8.2V LD OFF\r\n");
			break;
		}

		case LMAC_DSP_TRIGGLE_OT_DROP_LD_ON: {
			printf("#DSP:Triggle over temperature, LD ON!!!\r\n");
			break;
		}

		case LMAC_DSP_TRIGGLE_OT_DROP_LD_OFF: {
			printf("#DSP:Triggle over temperature, LD OFF!!!\r\n");
			break;
		}
	}
}

void vc_lmac_cfg_hw_csma_dsp_abort()
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	cnMacReg->CNSCH_RTY_CR = 0x08;
	//printf("#DspAbort!!\r\n");
	return;
}

extern void vc_lmac_cfg_hw_csma_retry(vc_uint32 backoffTime);

void PLC_MAC_Handler()
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	//volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	vc_uint32 pCnmacIrq = 0x00;
	pCnmacIrq = cnMacReg->CNMAC_ISR;
	cnMacReg->CNMAC_ISR = pCnmacIrq;

  printf("MAC ISR: 0x%08x\r\n", pCnmacIrq);

  if (pCnmacIrq & cnmmacISR_dsp_info) {
    lmac_process_dsp_tx_info_irq();
  }

  if (pCnmacIrq & cnmmacISR_dsp_sack) {
    lmac_process_sack_irq_handler();
    gLMAC->lmacIrqCount.get_sack++;
    txpDoneNotFinished = 0;
  }

  if (pCnmacIrq & cnmacISR_cnrxp_done) {
    gLMAC->lmacIrqCount.cnrxp_done++;
  }

  if (pCnmacIrq & cnmacISR_cnmac_abortack) {
    gLMAC->lmacIrqCount.abortack++;
  }

  if (pCnmacIrq & cnmacISR_cnmac_resp_sack) {
    gLMAC->lmacIrqCount.resp_sack++;
  }

  if (pCnmacIrq & cnmacISR_cnsch_get_para) {
    if (cnMacReg->CNSCH_TSR1 & 0x01000000) {
      vc_lmac_get_next_csma_para();
    }
    gLMAC->lmacIrqCount.get_para++;
  }

  if (pCnmacIrq & cnmacISR_cnsch_tdma_timeup) {
    gLMAC->lmacIrqCount.tdma_timeup++;
  }

  if (pCnmacIrq & cnmacISR_cnsch_tdma_fail) {
    gLMAC->lmacIrqCount.tdma_fail++;
  }

  if (pCnmacIrq & cnmacISR_cnsch_csma_success) {
    gLMAC->lmacIrqCount.csma_success++;
  }

  if (pCnmacIrq & cnmacISR_cnsch_csma_fail) {
    gLMAC->lmacIrqCount.csma_fail++;
  }

  if (pCnmacIrq & cnmacISR_cnsch_csma_abort) {
    gLMAC->lmacCsma.csmaAbort = 1;
    gLMAC->lmacIrqCount.csma_abort++;
    if (csmaAbortFlagEnable)
    {
      vc_lmac_cfg_hw_csma_dsp_abort();
      csmaAbortFlagEnable = 0;
    }
    else
    {
      csmaAbortFlagEnable = 0;
    }
  }

  if (pCnmacIrq & cnmacISR_cnsch_kickphy) {
    gLMAC->lmacIrqCount.kickphy++;
  }

  if (pCnmacIrq & cnmacISR_cntxp_done) {
    if (waitTxpDoneFlag) {
      waitTxpDoneFlag = 0;
    }
    if (!gLMAC->lmacCsma.csmaAbort)
    {
      lmac_process_isrTxPDone();
      txpDoneNotFinished = 0;
    }
    gLMAC->lmacIrqCount.cntxp_done++;
  }

  if (pCnmacIrq & cnmacISR_dsp_abortpkt) {
    gLMAC->lmacIrqCount.dsp_abortpkt++;
    lmac_process_isrTxPDone();
    gLMAC->lmacCsma.csmaAbort = 0;
    txpDoneNotFinished = 0;
    LMAC_CHANGE_STATE(LMAC_CSMA_IDLE);
  }

  if (pCnmacIrq & cnmacISR_cnmac_get_sack) {
    gLMAC->lmacPing.ackPingTimes++;
    gLMAC->lmacIrqCount.get_sack++;
  }

  if (pCnmacIrq & cnmacISR_zc1) {
    //vc_lmac_area_idf_zx_a_phase();
  }
  if (pCnmacIrq & cnmacISR_zc2) {
    //vc_lmac_area_idf_zx_b_phase();
  }
  if (pCnmacIrq & cnmacISR_zc3) {
    //vc_lmac_area_idf_zx_c_phase();
  }
}

void lmac_process_isrRxComplete()
{
	while (g_dmaRxDesc[dmaRxDescIdx].ctrl.fields.owner == VC_DMAC_OWNER_SW) {
		lmac_receive_desc_data_ind(dmaRxDescIdx);
		dmaRxDescIdx++;
		dmaRxDescIdx %= VC_DMAC_RX_NR_DESC;
	}
}

void lmac_process_isrTxComplete()
{
}

void PLC_DMA_Handler()
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	vc_uint32 pDmaIrq = 0x00;

	pDmaIrq = dmaReg->ISR.value;
	dmaReg->ISR.value = pDmaIrq;

	if (pDmaIrq & dmaISR_Txcmp) {
		lmac_process_isrTxComplete();
		gLMAC->lmacDmaCount.txCmp++;
	}

	if (pDmaIrq & dmaISR_Txupdate) {
		gLMAC->lmacDmaCount.txUpdate++;
	}

	if (pDmaIrq & dmaISR_Txerror) {
		gLMAC->lmacDmaCount.txError++;
	}

	if (pDmaIrq & dmaISR_Rxcmp) {
		vc_lmac_ntb_before_rxcmp = vc_phy_get_ntb();
		lmac_process_isrRxComplete();
		gLMAC->lmacDmaCount.rxCmp++;
	}

	if (pDmaIrq & dmaISR_Rxunavail) {
		LMAC_KICK_RX_DMA();
		printf("######DmaRxUnavail!!######\r\n");
		gLMAC->lmacDmaCount.rxUnavail++;
		phy_rx_unavail_count++;
	}

	if (pDmaIrq & dmaISR_Rxerror) {
		gLMAC->lmacDmaCount.rxError++;
	}

	if (pDmaIrq & dmaISR_Rxupdate) {
		gLMAC->lmacDmaCount.rxUpdate++;
	}
}
