#include <stdio.h>
#include "phy.h"
#include "vc_lmac.h"
#include "vc_lmac_dma_if.h"
#include "vc_lmac_rxh.h"
#include "vc_string.h"

extern vc_ntb32 vc_phy_get_ntb();

vc_uint8 lmacRxPkt = 0;

vc_uint8 ChecklmacRxPkt()
{
	return lmacRxPkt;
}
void ResetlmacRxPkt()
{
	lmacRxPkt = 0;
}

vc_uint8 mac_ctrl_header_parser(tVC_LMAC_RX_CTRL_HEADER *pCtrlHdr, vc_uint8 *pData)
{
	vc_uint16 tmpLen = 0;
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
	//print_rx_ctrl_hdr_param(pCtrlHdr);
	return tmpLen;
}

void lmac_receive_bbp_raw_handler(vc_uint8 descIdx)
{
	//volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	//LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	lmacBbpRawCmdType bbpRawCmdType = 0x0000;
	//tVC_LMAC_RX_CTRL_HEADER pCtrlHdr;
	//tCN_BEACON_FC pParsFcBcon;
	//tCN_SOF_FC pParsFcSof;
	vc_uint32 bbp_value = 0;
	//vc_int32 bbp_single_value = 0;
	vc_uint16 pktLen = 0;
	vc_uint32 i = 0;

	bbpRawCmdType = ((g_dmaRxBuf[descIdx][8]) | (g_dmaRxBuf[descIdx][9] << 8));

  pktLen = (g_dmaRxDesc[descIdx].ctrl.fields.pkt_len - 12);
  printf("+BBP: 0x%04X, ", bbpRawCmdType);
  for (i = 0; i < (pktLen / 4); i++) {
    bbp_value = 0;
    bbp_value =
      (g_dmaRxBuf[descIdx][12 + (4 * i)]) |
      ((g_dmaRxBuf[descIdx][12 + (4 * i) + 1 ]) << 8) |
      ((g_dmaRxBuf[descIdx][12 + (4 * i) + 2]) << 16) |
      ((g_dmaRxBuf[descIdx][12 + (4 * i) + 3]) << 24);
    printf("0x%X,", bbp_value);
  }
  printf("\r\n");
}

void lmac_receive_one_rx_data_handler(vc_uint8 descIdx, vc_ntb32 lmacNTB)
{
}

void lmac_receive_pbcs_error_data_handler(vc_uint8 descIdx)
{
}

void lmac_receive_desc_data_ind(vc_uint8 descIdx)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	tVC_LMAC_RX_CTRL_HEADER pCtrlHdr;
	vc_ntb32 lmacNTB = 0x00;

	gLMAC->lmacDmaCount.rxProcessCmp++;
	lmacNTB = vc_phy_get_ntb();
	lmacRxPkt = 1;

  if (gLMAC->lmacREGState == LMAC_LEAVE_REG_STATE) {
    printf("#LeaveState\r\n");
    lmac_process_mac_rxq_complete(descIdx);
    return;
  }

	vc_memset(&pCtrlHdr, 0x00, sizeof(tVC_LMAC_RX_CTRL_HEADER));
	mac_ctrl_header_parser(&pCtrlHdr, (vc_uint8 *)&g_dmaRxBuf[descIdx][0]);

	if (g_dmaRxDesc[descIdx].ctrl.fields.first == 1 && g_dmaRxDesc[descIdx].ctrl.fields.last == 1) {
    if (pCtrlHdr.type == TX_CTRL_HDR_PHY_TEST_TYPE) {
      printf("PhyTestModeCnf\r\n");
      //lmac_phy_ping_status = 0;
    } else if (pCtrlHdr.type == TX_CTRL_HDR_BBP_RX_TYPE) {
      lmac_receive_bbp_raw_handler(descIdx);
      gLMAC->lmacIrqCount.rx_bbpRaw++;
    } else if (pCtrlHdr.type == TX_CTRL_HDR_CN_RX_TYPE) {
      lmac_receive_one_rx_data_handler(descIdx, lmacNTB);
    } else if (pCtrlHdr.type == TX_CTRL_HDR_PBCS_FAIL_TYPE) {
      lmac_receive_pbcs_error_data_handler(descIdx);
      gLMAC->lmacIrqCount.rx_pbcsErr++;
    } else {
      printf("#NotSupportType:%d\r\n", pCtrlHdr.type);
      while(1);
    }
		lmac_process_mac_rxq_complete(descIdx);
    return;
	} else if (g_dmaRxDesc[descIdx].ctrl.fields.first == 1 && g_dmaRxDesc[descIdx].ctrl.fields.last == 0) {
		lmac_process_mac_rxq_complete(descIdx);
    return;
  } else if (g_dmaRxDesc[descIdx].ctrl.fields.first == 0 && g_dmaRxDesc[descIdx].ctrl.fields.last == 0) {
		lmac_process_mac_rxq_complete(descIdx);
    return;
  } else if (g_dmaRxDesc[descIdx].ctrl.fields.first == 0 && g_dmaRxDesc[descIdx].ctrl.fields.last == 1) {
		lmac_process_mac_rxq_complete(descIdx);
    return;
  } else {
    printf("#InvalidCtrlHdr\r\n");
		lmac_process_mac_rxq_complete(descIdx);
    return;
  }
}

void lmac_process_mac_rxq_complete(vc_uint8 dmaDescIdx)
{
	g_dmaRxDesc[dmaDescIdx].ctrl.fields.int_en = 1;
	g_dmaRxDesc[dmaDescIdx].ctrl.fields.owner = VC_DMAC_OWNER_DMAC;
	g_dmaRxDesc[dmaDescIdx].ctrl.fields.pkt_len = VC_DMAC_RX_BUF_SIZE;
	g_dmaRxDesc[dmaDescIdx].ctrl.fields.first = 0;
	g_dmaRxDesc[dmaDescIdx].ctrl.fields.last = 0;
	vc_memset(&g_dmaRxBuf[dmaDescIdx][0], 0x00, VC_DMAC_RX_BUF_SIZE);
	return;
}
