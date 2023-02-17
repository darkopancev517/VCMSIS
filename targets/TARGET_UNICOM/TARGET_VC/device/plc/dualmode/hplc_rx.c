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

extern tVC_DMAC_DESC g_dmaRxDesc[VC_DMAC_RX_NR_DESC];
extern uint8_t g_dmaRxBuf[VC_DMAC_RX_NR_DESC][VC_DMAC_RX_BUF_SIZE];
extern vc_lmac_pkt_sym_mapping gMapSymTMI_ALL;

uint16_t dmaRxDescIdx = 0;

uint32_t plc_m_timestamp = 0;

void vc_plc_dma_disable_ire()
{
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	dmaReg->IER.value = 0;
}
void vc_plc_dma_enable_ire()
{
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	dmaReg->IER.value = 0xFFFFFFFF;
}
void vc_cn_mac_disable_ire()
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	cnMacReg->CNMAC_IER.value = 0;
}
void vc_cn_mac_enable_ire()
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	cnMacReg->CNMAC_IER.value = 0xFFFFFFFF;
}

void vc_plc_enable_ire(void)
{
	vc_cn_mac_enable_ire();
	vc_plc_dma_enable_ire();
}
void vc_plc_disable_ire(void)
{
	vc_cn_mac_disable_ire();
	vc_plc_dma_disable_ire();
}

void vc_lmac_cfg_hw_csma_retry_stop()		//MMM
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	cnMacReg->CNSCH_RTY_CR.value = 0x01;
}

void vc_lmac_cfg_hw_csma_retry_abort()		//MMM
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	cnMacReg->CNSCH_RTY_CR.value = 0x02;
}


void vc_lmac_cfg_hw_csma_dsp_abort()	//MMM
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	//VINFO(LMAC_PRINT,"dspAbort!!");
	cnMacReg->CNSCH_RTY_CR.value = 0x08;
}

void vc_lmac_cfg_phy_rx_disable()
{
	volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	phyReg->phy_cr1 |= 0x00020000;
	return;
}

void vc_lmac_cfg_phy_rx_enable()
{
	volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	phyReg->phy_cr1 &= 0xFFFDFFFF;
	return;
}


void lmac_process_mac_rxq_complete(uint8_t dmaDescIdx)
{
	g_dmaRxDesc[dmaDescIdx].ctrl.fields.int_en = 1;
	g_dmaRxDesc[dmaDescIdx].ctrl.fields.owner = VC_DMAC_OWNER_DMAC;
	g_dmaRxDesc[dmaDescIdx].ctrl.fields.pkt_len = VC_DMAC_RX_BUF_SIZE;
	g_dmaRxDesc[dmaDescIdx].ctrl.fields.first = 0;
	g_dmaRxDesc[dmaDescIdx].ctrl.fields.last = 0;
}

uint8_t mac_ctrl_header_parser(tVC_LMAC_RX_CTRL_HEADER *pCtrlHdr, uint8_t *pData)
{
	uint16_t tmpLen = 0;
	//VMUST(LMAC_PRINT, "CR:", pData, sizeof(tVC_LMAC_RX_CTRL_HEADER));
	/*CR: 21000010-11000098 - 00003F9E-3CD22D5D*/
	/*0*/
	pCtrlHdr->type = (pData[tmpLen] & 0xF0) >> 4;
	pCtrlHdr->mode = pData[tmpLen] & 0x0F;
	tmpLen += 1;
	/*1*/
	pCtrlHdr->config = pData[tmpLen];
	tmpLen += 1;
	/*2 3*/
	pCtrlHdr->chdrLen = pData[tmpLen] << 8 | (pData[tmpLen + 1]);
	tmpLen += 2;
	/*4*/
	pCtrlHdr->pbcsStatus = pData[tmpLen];
	tmpLen += 1;
	/*5*/
	pCtrlHdr->linkQuality = pData[tmpLen];
	tmpLen += 1;
	/*6 7*/
	pCtrlHdr->pktLen = (pData[tmpLen] << 8) | (pData[tmpLen + 1]);
	tmpLen += 2;
	/*8*/
	pCtrlHdr->bcnFnCurrent = pData[tmpLen] & 0x01;
	//pCtrlHdr->rxRssi = (pData[tmpLen] & 0xFE) >> 0x01;
	tmpLen += 1;
	/*9 10 11*/
	pCtrlHdr->rxDuration = pData[tmpLen] << 16 | (pData[tmpLen + 1] << 8) | (pData[tmpLen + 2]);
	tmpLen += 3;
	/*12 13 14 15*/
	pCtrlHdr->recNTB = pData[tmpLen] << 24 | (pData[tmpLen + 1] << 16) | (pData[tmpLen + 2] << 8) | (pData[tmpLen + 3]);
	tmpLen += 4;
	/*16*/
	pCtrlHdr->RSSI = pData[tmpLen];
	tmpLen += 1;
	/*17 18 19*/
	pCtrlHdr->PPM = pData[tmpLen];
	tmpLen += 1;
	pCtrlHdr->FNPLLK = (pData[tmpLen] << 8) | pData[tmpLen + 1];
	tmpLen += 2;
	//print_ctrl_hdr_param(pCtrlHdr);
	return tmpLen;
}


static void mem_dump(const void *data, uint32_t nr_bytes)
{
  volatile uint8_t *addr = (volatile uint8_t *)data;
  uint32_t nr_lines, i;

  if (nr_bytes <= 0)
    return;

  nr_lines = nr_bytes / 16;

  printf("LEN: %d\r\n", (unsigned int)nr_bytes);

  while (nr_lines--) {
    printf("%08X : ", (unsigned int)addr);
    printf("%02X %02X %02X %02X %02X %02X %02X %02X", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
    printf(" - ");
    printf("%02X %02X %02X %02X %02X %02X %02X %02X", addr[8], addr[9], addr[10], addr[11], addr[12], addr[13], addr[14], addr[15]);
    printf("\r\n");
    addr += 16;
  }

  nr_bytes = nr_bytes & 0x0f;

  if (nr_bytes) {
    printf("%08X :", (unsigned int)addr);

    for (i = 0; i < nr_bytes; ++i) {
      if (i == 8) {
        printf(" -");
      }
      printf(" %02X", addr[i]);
    }

    printf("\r\n");
  }
}

void lmac_receive_bbp_raw_handler(uint8_t descIdx){

	lmacBbpRawCmdType bbpRawCmdType = 0x0000;
	
	bbpRawCmdType = ((g_dmaRxBuf[descIdx][8]) | (g_dmaRxBuf[descIdx][9] << 8));

  uint8_t *data = &g_dmaRxBuf[descIdx][0];
  uint16_t length = g_dmaRxDesc[descIdx].ctrl.fields.pkt_len;

  printf("RX BBP RAW CMD [%08x]\r\n", bbpRawCmdType);
  mem_dump((void *)data, length);
}

__attribute__((weak)) void vcplc_upper_callback(uint8_t *data, uint16_t len, int16_t rssi, uint16_t lqi, uint32_t timestamp)
{
  printf("Weak function vcplc_upper_callback() called.\n");
}

uint8_t mac_rx_fc_sof_parser(tCN_SOF_FC *pFc, uint8_t *pData)
{
	uint8_t pTmpLen = 0;
	memcpy(pFc, pData, sizeof(tCN_SOF_FC));

	pTmpLen = sizeof(tCN_SOF_FC);
	return pTmpLen;
}

//uint8_t gExtractRxData[1030];			//MMM
uint8_t gExtractRxData[VC_DMAC_RX_BUF_SIZE];	//MMM
void lmac_receive_one_rx_data_handler(uint8_t descIdx){


	tVC_LMAC_RX_CTRL_HEADER pCtrlHdr;
	tCN_SOF_FC pParsFcSof;	//MMM
	uint8_t tmi;			//MMM
	uint8_t pbNum;			//MMM
	uint16_t pbSize;		//MMM 

	

	/* These are arguments to be passed to upper callback function */
	//uint8_t *data;
	uint32_t rx_len;		//MMM
	int8_t rssi;				//Currently not used; todo
	int8_t lqi;			//Remember that the value is actually an signed 8-bit integer
	uint32_t timestamp;

	memset(&pCtrlHdr, 0x00, sizeof(tVC_LMAC_RX_CTRL_HEADER));
	mac_ctrl_header_parser(&pCtrlHdr, &g_dmaRxBuf[descIdx][0]);
	//printf("rx:%08lX %08lX %08lX %08lX %08X\r\n", *(uint32_t*)(&pCtrlHdr), *(uint32_t*)((uint32_t)(&pCtrlHdr)+4), *(uint32_t*)((uint32_t)(&pCtrlHdr)+8), *(uint32_t*)((uint32_t)(&pCtrlHdr)+12), *(uint32_t*)((uint32_t)(&pCtrlHdr)+16));
	//word_dump(0, "RXD ", &g_dmaRxDesc[descIdx], 2);
	//word_dump(0, "RXB ", &g_dmaRxBuf[descIdx][0],(pCtrlHdr.pktLen+4)/4);

	rx_len = *(uint32_t *)&g_dmaRxBuf[descIdx][sizeof(tVC_LMAC_RX_CTRL_HEADER) + sizeof(tCN_SOF_FC)];
	if(rx_len == 0 || rx_len > VC_DMAC_RX_BUF_SIZE - 100){	//100 is a rough over-estimate of rx control header, FC, and CRC
		printf("Received abnormal HPLC rx_len. rx_len = %lu.\n", rx_len);
		return;
	}
	//if((pCtrlHdr.pbcsStatus & 0x08) == 0 && rx_len < VC_DMAC_RX_BUF_SIZE){
	if((pCtrlHdr.pbcsStatus & 0x08) == 0 && pCtrlHdr.pktLen < VC_DMAC_RX_BUF_SIZE){
		uint16_t CHPlusFCLen = sizeof(tVC_LMAC_RX_CTRL_HEADER) + sizeof(tCN_SOF_FC);
		memset(&pParsFcSof, 0x00, sizeof(tCN_SOF_FC));
		mac_rx_fc_sof_parser(&pParsFcSof, (uint8_t *)&g_dmaRxBuf[descIdx][sizeof(tVC_LMAC_RX_CTRL_HEADER)]);
		if(pParsFcSof.NID != WISUN_NID || pParsFcSof.SofVarDTEI != 0x0FEF){
			printf("Received hplc packet from other network. NID = 0x%X, DTEI = 0x%X\n", pParsFcSof.NID, pParsFcSof.SofVarDTEI);
			return;
		}

		pbNum = pParsFcSof.SofVarPBCount;
		tmi = pParsFcSof.SofVarTMI;
		pbSize = gMapSymTMI_ALL.InfoTMI[tmi].PbSize;
		uint16_t firstPbValidLen = pbSize - LMAC_RESERVED_BYTES_FOR_LEN_IN_PB - LMAC_SIZE_OF_PBCS_IN_PB;
		uint16_t otherPbValidLen = pbSize - LMAC_SIZE_OF_PBCS_IN_PB;
		if(rx_len > firstPbValidLen + otherPbValidLen * (pbNum - 1))
			return;
		if(pbNum == 1){
			//printf("Rx pbNum 1, rx_len = %u, tmi = %u, pbSize=%u\n", rx_len, tmi, pbSize);
			memcpy(&gExtractRxData[0],
					&g_dmaRxBuf[descIdx][CHPlusFCLen + LMAC_RESERVED_BYTES_FOR_LEN_IN_PB],
					rx_len);
		}else if(pbNum == 2){
			//printf("Rx pbNum 2, rx_len = %u, tmi = %u, pbSize=%u\n", rx_len, tmi, pbSize);
			memcpy(	&gExtractRxData[0],
					&g_dmaRxBuf[descIdx][CHPlusFCLen + LMAC_RESERVED_BYTES_FOR_LEN_IN_PB],
					firstPbValidLen);
			memcpy(	&gExtractRxData[firstPbValidLen],
					&g_dmaRxBuf[descIdx][CHPlusFCLen + pbSize],
					rx_len - firstPbValidLen);
		}else if(pbNum == 3){
			//printf("Rx pbNum 3, rx_len = %u, tmi = %u, pbSize=%u\n", rx_len, tmi, pbSize);
			memcpy(	&gExtractRxData[0],
					&g_dmaRxBuf[descIdx][CHPlusFCLen + LMAC_RESERVED_BYTES_FOR_LEN_IN_PB],
					firstPbValidLen);
			memcpy(	&gExtractRxData[firstPbValidLen],
					&g_dmaRxBuf[descIdx][CHPlusFCLen + pbSize],
					otherPbValidLen);
			memcpy(	&gExtractRxData[firstPbValidLen + otherPbValidLen],
					&g_dmaRxBuf[descIdx][CHPlusFCLen + 2 * pbSize],
					rx_len - firstPbValidLen - otherPbValidLen);
		}else if(pbNum == 4){
			//printf("Rx pbNum 4, rx_len = %u, tmi = %u, pbSize=%u\n", rx_len, tmi, pbSize);
			memcpy(	&gExtractRxData[0],
					&g_dmaRxBuf[descIdx][CHPlusFCLen + LMAC_RESERVED_BYTES_FOR_LEN_IN_PB],
					firstPbValidLen);
			memcpy(	&gExtractRxData[firstPbValidLen],
					&g_dmaRxBuf[descIdx][CHPlusFCLen + pbSize],
					otherPbValidLen);
			memcpy(	&gExtractRxData[firstPbValidLen + otherPbValidLen],
					&g_dmaRxBuf[descIdx][CHPlusFCLen + 2 * pbSize],
					otherPbValidLen);
			memcpy(	&gExtractRxData[firstPbValidLen + otherPbValidLen + otherPbValidLen],
					&g_dmaRxBuf[descIdx][CHPlusFCLen + 3 * pbSize],
					rx_len - firstPbValidLen - otherPbValidLen - otherPbValidLen);
		}else{
			printf("Abnormal pbNum\n.");
			return;
		}

		//data = &g_dmaRxBuf[descIdx][sizeof(tVC_LMAC_RX_CTRL_HEADER) + sizeof(tCN_SOF_FC) + 4];
		rssi = (int8_t)pCtrlHdr.RSSI;
		lqi = (int8_t)pCtrlHdr.linkQuality;

    (void)rssi;
    (void)lqi;

		timestamp = plc_m_timestamp;
	  //mapping_rssi = mapping_plc_to_rf_rssi(rssi, lqi);
    //mapping_lqi = mapping_plc_to_rf_lqi(lqi);
		printf("PLC pkt received. rx_len=%lu, tmi=%u, linkQuality=%d, rssi=%d, NID=%x\n",
			rx_len,
			tmi,
			(int8_t)pCtrlHdr.linkQuality,
			(int8_t)pCtrlHdr.RSSI,
			pParsFcSof.NID);
		{
			vcplc_upper_callback(&gExtractRxData[0], rx_len, 0, 0, timestamp);
		}
	}else {
    printf("RX ERROR");
	}
}





void lmac_receive_desc_data_ind(uint8_t descIdx)
{
	uint32_t ntb_curr, ntb_pmbHit;
	uint32_t ms_curr, ms_pmbHit;
	uint8_t ctrlhdr_type = (g_dmaRxBuf[descIdx][0]&0xF0) >> 4;
	
	//lmac_meas_rx_desc_usage();
	
	//memset(&pCtrlHdr, 0x00, sizeof(tVC_LMAC_RX_CTRL_HEADER));
	//mac_ctrl_header_parser(&pCtrlHdr, &g_dmaRxBuf[descIdx][0]);
	//printf("NTB: %08lx %08lx\r\n", pCtrlHdr.recNTB, (g_dmaRxBuf[descIdx][12] << 24 | g_dmaRxBuf[descIdx][13] << 16 | g_dmaRxBuf[descIdx][14] << 8 | g_dmaRxBuf[descIdx][15]));
	//printf("type: %01lx %01lx\r\n", pCtrlHdr.type, ((g_dmaRxBuf[descIdx][0]&0xF0) >> 4));
	if(g_dmaRxDesc[descIdx].ctrl.fields.first == 1 && g_dmaRxDesc[descIdx].ctrl.fields.last == 1 && g_dmaRxDesc[descIdx].ctrl.fields.pkt_len <= VC_DMAC_RX_BUF_SIZE)
	{

		/*	The plc_m_timestamp is supposed to record the preambie hit time of this packet			*/
		/*	The preamble hit time, in NTB, is carried in the control header of the received packet	*/
		/*	What we do here is to backtrace the preamble hit time in ms from current time in ms		*/
		ntb_curr = vc_phy_get_ntb();
    //TODO: ms_curr = hal_misc_milli_get_now();
    ms_curr = 0;
		ntb_pmbHit =  (g_dmaRxBuf[descIdx][12] << 24 | g_dmaRxBuf[descIdx][13] << 16 | g_dmaRxBuf[descIdx][14] << 8 | g_dmaRxBuf[descIdx][15]);//pCtrlHdr.recNTB
		ms_pmbHit = 0xffffffff - (0xffffffff - ntb_pmbHit + ntb_curr + 1)/25000 + ms_curr + 1;
		plc_m_timestamp = ms_pmbHit;
		if(ctrlhdr_type == TX_CTRL_HDR_BBP_RX_TYPE){//(g_dmaRxBuf[descIdx][0]&0xF0) >> 4,pCtrlHdr.type
			lmac_receive_bbp_raw_handler(descIdx);
		}
		if(ctrlhdr_type == TX_CTRL_HDR_CN_RX_TYPE){
			lmac_receive_one_rx_data_handler(descIdx);
		}
	}else {
		printf("Packet rx crossing descriptors is not supported yet!! crtl=%lx\r\n", g_dmaRxDesc[descIdx].ctrl.value);
	}
	
	lmac_process_mac_rxq_complete(descIdx);	
}

void lmac_process_dsp_tx_info_irq()
{

	//uint32_t *phyIR2 = (vc_uint32 *)0x400111D4;
	//uint16_t txFinish = *(phyIR2) >> 12;
	//printf("IR2:%d"LF,txFinish);
	volatile uint8_t txFinish = (*(uint32_t*)0x400111D4) >> 12;
	switch (txFinish)
	{
		case LMAC_TX_KICK_BCN: {
			//printf("#DspKickvBcn!\r\n");
			//vc_lmac_cfg_phy_rx_disable();
			//break;
		}

		case LMAC_TX_KICK_SOF:
		case LMAC_TX_KICK_SACK:
		case LMAC_TX_KICK_ITNWC: {
			//printf("#DspKickPkt!\r\n");
			//ta = vc_phy_get_ntb();
			plc_m_tx_info_start = 1;
			break;
		}

		case LMAC_TX_GPIO_TIMEOUT: {
			//printf("#DspRecvTimeout!\r\n");
			//vcLogWarning("#Cfg gpio notify Dsp Timer out!! 500 (us)");
			break;
		}

		case LMAC_TX_FINISH_MOVE_BCN: {
			//printf("#DspRecvBcn!\r\n");
			break;
		}

		case LMAC_TX_FINISH_MOVE_NUNBCN: {
			//printf("#DspRecvPkt!\r\n");
			break;
		}

		case LMAC_TX_DONE_FINISH: {
			plc_m_tx_info_finish = 1;
			//printf("#DspTxDone!\r\n");
			//tb = vc_phy_get_ntb();
			//printf("tx,%lu,%lu,%lu,%lu"LF, t0/25, ta/25, tb/25, t1/25);
			break;
		}

		default:
		break;
	}
	return;
}


void lmac_process_isrRxComplete()
{
	//rxCompleteCount++;
	//rxTime[rxInd] = vc_phy_get_ntb();
	//rxReg174[rxInd] =  *(volatile uint32_t *)0x40011174; /* CNVCS_DR2 */
	//rxInd = (rxInd + 1) % 10;
	while(g_dmaRxDesc[dmaRxDescIdx].ctrl.fields.owner == VC_DMAC_OWNER_SW){	
		lmac_receive_desc_data_ind(dmaRxDescIdx);
		dmaRxDescIdx++;
		dmaRxDescIdx %= VC_DMAC_RX_NR_DESC;
	}
}

//extern void vc_lmac_tx_sof_pkt_f_cmd_ping(uint16_t DTEI, uint8_t extTmi, uint8_t tmi, uint8_t pbCount,uint8_t startFlag);
uint16_t neoDebugTxPingTotal = 0;
uint16_t neoDebugTxPingCurr = 0;
int rfst;
/*in lastest bbp if Ctrhdr is BEACON_F it only txp_done int triggered. */ 
void PLC_MAC_Handler()
{
	uint32_t pCnmacIrq ;
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	//LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;

	vc_cn_mac_disable_ire();

	pCnmacIrq = cnMacReg->CNMAC_ISR.value;
	cnMacReg->CNMAC_ISR.value = pCnmacIrq;
	//cnMacReg->CNMAC_ISR = 0xFFFFFFFF;

	printf("MAC ISR=%X\r\n", (unsigned int)pCnmacIrq);

	if (pCnmacIrq & cnmmacISR_dsp_info) {
		//printf("#dspInfo!\r\n");
		lmac_process_dsp_tx_info_irq();
	}
	if(pCnmacIrq & cnmacISR_cnsch_kickphy){
		//printf("#csma kickphy"LF);
		//printf("#cnsch_kickphy, ntb = %u, CNVCS_DR1 = 0x%X, phy_ir1 = 0x%X\n",
		//		vc_phy_get_ntb(), *(volatile uint32_t *)0x40011170, *(volatile vc_uint32 *)0x400111d0);	//MMM
	}
	if(pCnmacIrq & cnmacISR_cntxp_done){
		//printf("#txpDone!\r\n");
		//lmac_process_isrTxPDone();
		if(pCnmacIrq & cnmacISR_cnsch_csma_abort){
			plc_m_txp_done = 1;
		} else {
			plc_m_txp_done = 1;
		}
		//if(neoDebugTxPingCurr < neoDebugTxPingTotal){
		//	vc_lmac_tx_sof_pkt_f_cmd_ping(0xFFF,0,0,1,0);
		//	neoDebugTxPingCurr++;
		//}
	}
	if(pCnmacIrq & cnmacISR_dsp_abortpkt){
		//printf("#dsp_abortpkt\n");
		plc_m_dsp_abortpkt = 1;
	}
	if(pCnmacIrq & cnmacISR_cnrxp_done){
		//printf("#rxp_done\n");
	}
	if(pCnmacIrq & cnmacISR_cnmac_ackto){
		//printf("#sack:timeOut");
	}
	if(pCnmacIrq & cnmacISR_cnmac_get_sack){
		//printf("#sack:get");
	}
	if(pCnmacIrq & cnmacISR_cnmac_resp_sack){
	}
	if(pCnmacIrq & cnmacISR_cnmac_abortack){
	}
	if(pCnmacIrq & cnmacISR_cnsch_get_para){
		if(cnMacReg->CNSCH_TSR1.fields.csr_cnsch_csma == 1){
			//printf("#cnsch_get_para\r\n");//, ntb = %u, CNVCS_DR1 = 0x%X, phy_ir1 = 0x%X\n",
			//	vc_phy_get_ntb(), *(volatile uint32_t *)0x40011170, *(volatile vc_uint32 *)0x400111d0);	//MMM
			plc_m_csma_get_para = 1;
			vc_lmac_cfg_hw_csma_retry_stop();
		}
	}
	if(pCnmacIrq & cnmacISR_cnsch_csma_success){
		plc_m_csma_success = 1;
	}
	if(pCnmacIrq & cnmacISR_cnsch_csma_fail){
		//printf("#csma fail"LF);
		plc_m_csma_fail = 1;
	}
	if(pCnmacIrq & cnmacISR_cnsch_csma_abort){
		//printf("#csma:abort"LF);
		vc_lmac_cfg_hw_csma_dsp_abort();
		plc_m_csma_abort = 1;
	}
	if(pCnmacIrq & cnmacISR_cnsch_tdma_timeup){
	}
	if(pCnmacIrq & cnmacISR_cnsch_tdma_fail){
		//printf("#tdma:f");
	}

	vc_cn_mac_enable_ire();
}


void PLC_DMA_Handler()
{
	uint32_t pDmaIrq ;
	volatile tVC_DMA_REG *cnDMAReg = (volatile  tVC_DMA_REG *)VC_MAC_DMA_BASE;
	//LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;

	vc_plc_dma_disable_ire();

	pDmaIrq = cnDMAReg->ISR.value;
	cnDMAReg->ISR.value = pDmaIrq;

  printf("DMA ISR=%X\r\n",(unsigned int)pDmaIrq);

	if (pDmaIrq & dmaISR_Txcmp) {
		//lmac_process_isrTxComplete();
		printf("DmaTxcmp\r\n");
	}

  if (pDmaIrq & dmaISR_Txunavail)
  {
    printf("DmaTxunavail\r\n");
  }

	if (pDmaIrq & dmaISR_Txupdate) {
    printf("DmaTxUpdate\r\n");
	}

	if(pDmaIrq & dmaISR_Txerror){
		printf("DmaTxError!!\r\n");
	}

	if (pDmaIrq & dmaISR_Rxcmp) {
    printf("DmaRxcmp\r\n");
		lmac_process_isrRxComplete();
	}

	if(pDmaIrq & dmaISR_Rxunavail){
		//lmac_dump_rx_desc();
		LMAC_KICK_RX_DMA();
		printf("Rxunavailable ID:%d!!!\r\n", dmaRxDescIdx);
		//OS_TaskDump();
		//vcASSERT(0);
	}

	if(pDmaIrq & dmaISR_Rxerror){
		printf("DmaRxError!!\r\n");
	}

	if(pDmaIrq & dmaISR_Rxupdate){
    printf("DmaRxUpdate\r\n");
	}

	vc_plc_dma_enable_ire();
}

