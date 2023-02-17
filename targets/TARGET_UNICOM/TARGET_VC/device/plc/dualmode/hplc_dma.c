#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include "hplc.h"
#include "hplc_bbp.h"
#include "hplc_dma.h"
#include "hplc_lmac.h"

tVC_DMAC_DESC g_dmaTxDesc[VC_DMAC_TX_NR_DESC];
tVC_DMAC_DESC g_dmaRxDesc[VC_DMAC_RX_NR_DESC];
uint8_t g_dmaRxBuf[VC_DMAC_RX_NR_DESC][VC_DMAC_RX_BUF_SIZE];

void lmac_dump_tx_desc()
{
	uint8_t i;
  printf("LMAC TX DESC:\r\n");
	for(i = 0; i < VC_DMAC_TX_NR_DESC; i++){
		printf("%d | %08X : %08X %08X\r\n", i, 
			(unsigned int)&g_dmaTxDesc[i],  
			(unsigned int)g_dmaTxDesc[i].ctrl.value, 
			(unsigned int)g_dmaTxDesc[i].ptr);	
	}
}

void lmac_dump_rx_desc()
{
	uint8_t i;
  printf("LMAC RX DESC:\r\n");
	for(i = 0; i < VC_DMAC_RX_NR_DESC; i++){
		printf("%d | %08X : %08X %08X\r\n", i, 
			(unsigned int)&g_dmaRxDesc[i],  
			(unsigned int)g_dmaRxDesc[i].ctrl.value, 
			(unsigned int)g_dmaRxDesc[i].ptr);	
	}
}

void LMAC_KICK_RX_DMA()
{
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	uint32_t value = 0;
	((tVC_DMA_RXE_KR *)&value)->fields.csr_rxe_kick = 1;
	dmaReg->RXE_KR.value = value;
}

void LMAC_KICK_TX_DMA()
{
	volatile PHY_REG *phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	uint32_t value = 0;
	//VINFO(LMAC_PRINT, "kickNTB:%x", phyReg->ntb_cnt);
  printf("LMAC KICK TX DMA - ntb_count: %x, addr: %08x\r\n", (unsigned int)phyReg->ntb_cnt, (unsigned int)&phyReg->ntb_cnt);
	((tVC_DMA_TXE_KR *)&value)->fields.csr_txe_kick = 1;
	dmaReg->TXE_KR.value = value;
	//printf("#kickDma2\n");
}
void LMAC_KICK_CSMA_ABORT()
{	
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	cnMacReg->CNMAC_IER.value |=0x80000; /*Csma Abort*/
}

void vc_lmac_cfg_dma()
{
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	uint32_t value = 0;
	uint8_t i;

	value = 0x303;
	dmaReg->CR.value = value;
	value = 0;
	((tVC_DMA_TM_CR *)&value)->fields.csr_dma_lb = 0;
	((tVC_DMA_TM_CR *)&value)->fields.csr_buf_lb = 0;
	((tVC_DMA_TM_CR *)&value)->fields.csr_rxstatus_drop = 0;
	dmaReg->TM_CR.value = value;
	value = 0;
	((tVC_DMA_TXE_CR *)&value)->fields.csr_txe_byteswap = 1;
	((tVC_DMA_TXE_CR *)&value)->fields.csr_txe_chkfd = 1;
	dmaReg->TXE_CR.value = value;
	dmaReg->RXE_CR.value = value;
	value = 0;
	((tVC_DMA_TXE_SR *)&value)->fields.csr_txe_desc_gap = 0;
	dmaReg->TXE_SR.value = value;
	dmaReg->RXE_SR.value = value;
	value = 0;
	((tVC_DMA_IER *)&value)->fields.ier_txcmp = 1;
	((tVC_DMA_IER *)&value)->fields.ier_txunavail = 1;
	((tVC_DMA_IER *)&value)->fields.ier_txerror = 1;
	((tVC_DMA_IER *)&value)->fields.ier_txupdate = 1;
	((tVC_DMA_IER *)&value)->fields.ier_rxcmp = 1;
	((tVC_DMA_IER *)&value)->fields.ier_rxunavail = 1;
	((tVC_DMA_IER *)&value)->fields.ier_rxerror = 1;
	((tVC_DMA_IER *)&value)->fields.ier_rxupdate = 1;
	((tVC_DMA_IER *)&value)->fields.ier_rxreclaim = 1;
	((tVC_DMA_IER *)&value)->fields.ier_msterr = 1;
	//dmaReg->IER.value = 0;//value;
	dmaReg->IER.value = value;
	dmaReg->ISR.value = 0xFFFFFFFF;
	
	for (i = 0; i < VC_DMAC_RX_NR_DESC; i++){
		memset(&g_dmaRxDesc[i], 0, sizeof(tVC_DMAC_DESC));
		g_dmaRxDesc[i].ctrl.fields.int_en = 1;
		g_dmaRxDesc[i].ctrl.fields.owner = VC_DMAC_OWNER_DMAC;
		g_dmaRxDesc[i].ctrl.fields.pkt_len = VC_DMAC_RX_BUF_SIZE;
		g_dmaRxDesc[i].ptr = (uint32_t) & g_dmaRxBuf[i][0];
	}
	g_dmaRxDesc[VC_DMAC_RX_NR_DESC - 1].ctrl.fields.eor = 1;
	dmaReg->RXE_BA_SR.value = (uint32_t) & g_dmaRxDesc[0];
  //lmac_dump_rx_desc();
	
	for(i=0;i<VC_DMAC_TX_NR_DESC;i++){
		g_dmaTxDesc[i].ctrl.fields.last = 0;
		g_dmaTxDesc[i].ctrl.fields.first = 0;
		g_dmaTxDesc[i].ctrl.fields.int_en = 0;
		g_dmaTxDesc[i].ctrl.fields.eor = 0;
		g_dmaTxDesc[i].ctrl.fields.owner = VC_DMAC_OWNER_SW;
	}
	dmaReg->TXE_BA_SR.value = (uint32_t) & g_dmaTxDesc[0];
  //lmac_dump_tx_desc();
	
	LMAC_KICK_RX_DMA();
	//dmaReg->ISR.value = 0xFFFFFFFF;
	//dmaReg->IER.value= 0xFFFFFFFF;
}

void vc_lmac_tx_pkt_init(tVC_DMAC_PACKET *pkt)
{
	memset(pkt, 0x0, sizeof(tVC_DMAC_PACKET));
	pkt->nr_desc=0;
}

void vc_lmac_tx_pkt_attach(tVC_DMAC_PACKET *pkt,void *pData, uint16_t pDataLen)
{
	//printf("TX DEC %d"LF, pkt->nr_desc);
	//word_dump(0, " ", pData, (pDataLen%4)? (pDataLen/4)+1:(pDataLen/4) );
	pkt->pld[pkt->nr_desc].dma_ptr = pData;
	pkt->pld[pkt->nr_desc].dma_size = pDataLen;
	pkt->nr_desc++;
}




