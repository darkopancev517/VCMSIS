#include <stdio.h>

#include "phy.h"
#include "vc_lmac.h"
#include "vc_lmac_dma_if.h"
#include "vc_string.h"
#include "vc_lmac_txh.h"
#include "device.h"

extern vc_uint8 vc_phy_lmac_cfg_dsp_ARQ(vc_uint8 onOff);
extern vc_uint8 vc_phy_lmac_cfg_disable_phy_reply_nack(vc_uint8 disableNack);
extern vc_uint8 vc_phy_lmac_cfg_dsp_ARQ_STEI(vc_uint16 mySTEI);
extern vc_uint8 vc_phy_lmac_cfg_phy_RIFS(vc_uint16 timeRIFS);
extern vc_uint8 vc_phy_sw_setting_idle();
extern vc_uint8 vc_phy_lmac_cfg_payload_crc_filter(vc_uint8 onOff);
extern vc_uint8 vc_phy_lmac_cfg_3p_gpio_finish(vc_uint8 isFinish);

extern void LMAC_KICK_RX_DMA();

static lmac_context_struct lmac_context;

volatile LMAC_CONTEXT_PTR lmac_ptr_g;
volatile tVC_DMAC_DESC g_dmaTxDesc[VC_DMAC_TX_NR_DESC];
volatile tVC_DMAC_DESC g_dmaRxDesc[VC_DMAC_RX_NR_DESC];
vc_uint8 g_dmaRxBuf[VC_DMAC_RX_NR_DESC][VC_DMAC_RX_BUF_SIZE];
volatile vc_uint8 dmaRxDescIdx = 0;

lmac_dsp_watch_dog g_lmac_dsp_watch_dog;

phy_nv_cfg_t phyNvCfg = {
	.nvramIdx = 0x1,
	.band = 0x1,
	.fnpllInitN = 0x24,
	.fnpllInitK = 0x0,
	.fnpllForceFlag = 0x0,
	.fnpllForceN = 0x24,
	.fnpllForceK = 0x0,
	.ntbOffset = 0x2710,
	.cfgTxSwing = 0x32
};

phy_nv_cfg_cmd_t phyNvCfgCmdList[NV_PHY_CFG_TOTAL_NUM] = {
	{ "NVI", &phyNvCfg.nvramIdx },
	{ "BAND", &phyNvCfg.band },
	{ "FNPLL_INIT_N", &phyNvCfg.fnpllInitN },
	{ "FNPLL_INIT_K", &phyNvCfg.fnpllInitK },
	{ "FNPLL_FORCE_FLAG", &phyNvCfg.fnpllForceFlag },
	{ "FNPLL_FORCE_N", &phyNvCfg.fnpllForceN },
	{ "FNPLL_FORCE_K", &phyNvCfg.fnpllForceK },
	{ "NTB_OFFSET", &phyNvCfg.ntbOffset },
	{ "PHY_TX_SWING", &phyNvCfg.cfgTxSwing },
};

void vc_lmac_phy_fnpll_init(vc_uint32 initN, vc_uint32 initK)
{
	tBbpRawCmd bbpRawCmd;
	//vc_uint32 bbpCmd = 0x00;
	vc_memset(&bbpRawCmd, 0x00, sizeof(tBbpRawCmd));
	bbpRawCmd.bbpCmd[0] = VC_LMAC_RCMD_FNPLL_INIT;
	bbpRawCmd.bbpCmd[1] = initN;
	bbpRawCmd.bbpCmd[2] = initK;
	bbpRawCmd.bbpCmdLen = 12;
	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

void vc_lmac_phy_fnpll_force(vc_uint32 flag, vc_uint32 forceN, vc_uint32 forceK)
{
	tBbpRawCmd bbpRawCmd;
	//vc_uint32 bbpCmd = 0x00;
	vc_memset(&bbpRawCmd, 0x00, sizeof(tBbpRawCmd));
	bbpRawCmd.bbpCmd[0] = VC_LMAC_RCMD_FNPLL_FORCE;
	bbpRawCmd.bbpCmd[1] = flag;
	bbpRawCmd.bbpCmd[2] = forceN;
	bbpRawCmd.bbpCmd[3] = forceK;
	bbpRawCmd.bbpCmdLen = 16;
	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

void vc_lmac_g_cfg_init(void)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;

	gLMAC->lmacState = LMAC_IDLE;
	gLMAC->lmacCsma.minBE = LMAC_CSMA_MIN_BE;
	gLMAC->lmacCsma.maxBE = LMAC_CSMA_MAX_BE;
	gLMAC->lmacCsma.period = LMAC_CSMA_BACKOFF_PERIOD;
	gLMAC->lmacCsma.maxRetryCnt = LMAC_CSMA_MAX_BACKOFFS;
	gLMAC->lmacBcn.checkbcnSendComplete = 0;
	gLMAC->lmacConfig.hv_flag = 0;
	gLMAC->lmacToneMask = 0;
	gLMAC->LMAC_NNID = 0;
	gLMAC->lmacConfig.init_flag = 1;
	gLMAC->lmacBandSearch.BeaconReceive = 0;
	gLMAC->lmacBandSearch.bandSearchingRunning = 0;
	gLMAC->lmacLeaveReason = VC_LEAVE_REASON_NONE;

	gLMAC->lmacLEDState = LMAC_LED_METER_NOT_GET_STATE;
	gLMAC->lmacREGState = LMAC_NOT_REG_STATE;
	gLMAC->lmacSch.bconRole = LMAC_ROLE_STA;
	gLMAC->LMAC_NID = 0x000000;
	gLMAC->LMAC_DTEI = 0x0000;
	gLMAC->LMAC_STEI = 0x0000;
	gLMAC->LMAC_PTEI = 0x0000;
	gLMAC->LMAC_CTEI = VC_BPLC_CIU_SERVICE_TEI;

  gLMAC->lmacBand = LMAC_DEFAULT_BAND;
  gLMAC->lmacBandSearch.currentBand = LMAC_DEFAULT_BAND;

	//gLMAC->lmacSch.mutexCsmaTxKickOut_g = NULL;
	vc_memset(&(gLMAC->lmacZxInfo), 0x00, sizeof(lmac_Zx_Info));
	vc_memset(&(gLMAC->lmacIrqCount), 0x00, sizeof(lmac_irq_struct));
	vc_memset(&(gLMAC->lmacRtCount), 0x00, sizeof(lmac_rt_cnt));
	vc_memset(&(gLMAC->lmacMacCsmaUsage), 0x00, sizeof(lmac_mac_csma_usage));
	return;
}

void vc_lmac_cfg_init(void)
{
  LMAC_PTR = &lmac_context;
  vc_lmac_g_cfg_init();
	vc_memset(&g_lmac_dsp_watch_dog, 0x00, sizeof(lmac_dsp_watch_dog));
	vc_phy_lmac_cfg_disable_phy_reply_nack(1);
}

void vc_lmac_cfg_cnmac(void)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	volatile tVC_G3MAC_REG *g3MacReg = (volatile tVC_G3MAC_REG *)VC_MAC_G3_BASE;
	//vc_uint32 value=0x00;
	cnMacReg->MAC_CR = 0x00040001;
	cnMacReg->CNMAC_CR = 0x0000007F;
	cnMacReg->CNMAC_ISR = 0xFFFFFFFF;
	cnMacReg->CNMAC_IER = 0xFFFFFFFF;
	cnMacReg->CNVCS_SR2 = LMAC_EIFS + LMAC_RIFS;
	cnMacReg->CNVCS_SR3 = LMAC_CIFS;
	cnMacReg->CNVCS_SR4 = LMAC_RIFS;
	cnMacReg->CNSCH_TSR1 = 0x01006912;
	g3MacReg->CR.value = 0x0;
	vc_phy_lmac_cfg_phy_RIFS(LMAC_RIFS);
}

void vc_lmac_cfg_dma(void)
{
	volatile tVC_DMA_REG *dmaReg = (volatile tVC_DMA_REG *)VC_MAC_DMA_BASE;
	vc_uint32 value = 0;
	vc_uint8 i;

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
	dmaReg->IER.value = value;
	dmaReg->ISR.value = 0xFFFFFFFF;
	for (i = 0; i < VC_DMAC_RX_NR_DESC; i++) {
		g_dmaRxDesc[i].ctrl.fields.int_en = 1;
		g_dmaRxDesc[i].ctrl.fields.owner = VC_DMAC_OWNER_DMAC;
		g_dmaRxDesc[i].ctrl.fields.pkt_len = VC_DMAC_RX_BUF_SIZE;
		g_dmaRxDesc[i].ptr = (vc_uint32)&g_dmaRxBuf[i][0];
	}
	g_dmaRxDesc[VC_DMAC_RX_NR_DESC - 1].ctrl.fields.eor = 1;
	dmaReg->RXE_BA_SR.value = (vc_uint32) & g_dmaRxDesc[0];
	//lmac_dump_rx_desc();

	for (i = 0; i < VC_DMAC_TX_NR_DESC; i++) {
		g_dmaTxDesc[i].ctrl.fields.last = 0;
		g_dmaTxDesc[i].ctrl.fields.first = 0;
		g_dmaTxDesc[i].ctrl.fields.int_en = 0;
		g_dmaTxDesc[i].ctrl.fields.eor = 0;
		g_dmaTxDesc[i].ctrl.fields.owner = VC_DMAC_OWNER_SW;
	}
	dmaReg->TXE_BA_SR.value = (vc_uint32) & g_dmaTxDesc[0];

	LMAC_KICK_RX_DMA();
}

void vc_lmac_cfg_arq_NID(vc_uint32 pNID)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	vc_uint32 pSwapData = 0x00000000;

	//printf("#ConfigNID:0x%06X", (unsigned int)pNID);

	pSwapData = ((pNID & 0x00FF0000) >> 16) | (pNID & 0x0000FF00) | ((pNID & 0x000000FF) << 16);
	cnMacReg->CNRXF_SET1_SR1 = pSwapData;
	gLMAC->LMAC_NID = (pNID & 0x00FFFFFF);
}

void vc_lmac_cfg_arq_ReceiveTEI(vc_uint32 pSTEI)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	/*0x48*/
	cnMacReg->CNRXF_STEI_SR = 0xFFF;//pSTEI;/*0xFFF*/
	gLMAC->LMAC_DTEI = pSTEI;
}

void vc_lmac_cfg_phy_arq_MyTEI(vc_uint16 pMyTEI)
{
	vc_phy_lmac_cfg_dsp_ARQ_STEI(pMyTEI);
	return;
}

void vc_lmac_cfg_arq_MyTEI(vc_uint16 pMyTEI)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	/*0x34: 0x00456*/
	cnMacReg->CNRXF_SET1_SR2 = (pMyTEI & 0x000F) << 8 | (pMyTEI & 0x0FF0) >> 4;
	gLMAC->LMAC_STEI = pMyTEI;
	vc_lmac_cfg_phy_arq_MyTEI(pMyTEI);
}

void vc_lmac_cfg_sack_arq(void)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	vc_uint16 myTEI = 0x0000;
	//vc_uint32 value = 0;
	/*ARQRxCfg*/
	//cnMacReg->CNRXF_SET1_SR1 = 0x332211; /*NID*/
	//cnMacReg->CNRXF_SET1_SR2 = 0xFFF;/*DTEI*/
	vc_lmac_cfg_arq_NID(gLMAC->LMAC_NID);
	vc_lmac_cfg_arq_MyTEI(myTEI);
	vc_lmac_cfg_arq_ReceiveTEI(0xFFF);
	cnMacReg->CNSCH_CR1 = 0x0161012C;
	//cnMacReg->CNSCH_CR1 = 0x0021012C;/*SchedulerCtrlCR->Neo:Modify[24]disable first before back-off*/
	cnMacReg->CNVCS_SR5 = 0x514;/*ACK Duration*/
#if VC_HPLC_DSP_AUTO_ACK_ARQ
	cnMacReg->CNMAC_CR = 0x77;
#else
	cnMacReg->CNMAC_CR = 0x7F;
#endif
	/*ARQTxCfg*/
	cnMacReg->CNSCH_TSR1 = 0x01006912;
	gLMAC->startWaitAckNTB = 0;
	return;
}

void vc_lmac_cfg_csma(void)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	cnMacReg->CNSCH_TSR2 = 26898;
}

void vc_lmac_hwmac_init(void)
{
  vc_lmac_cfg_cnmac();
  vc_lmac_cfg_dma();
#if VC_HPLC_DSP_AUTO_ACK_ARQ
	vc_phy_lmac_cfg_dsp_ARQ(1);
	vc_lmac_cfg_sack_arq();
#else
	vc_phy_lmac_cfg_dsp_ARQ(0);
	vc_lmac_cfg_sack_arq();
#endif
	vc_lmac_cfg_csma();
  NVIC_EnableIRQ(PLC_DMA_IRQn);
  NVIC_EnableIRQ(PLC_MAC_IRQn);
}

void vc_lmac_nv_cfg_init()
{
	vc_lmac_phy_fnpll_init(
		*(phyNvCfgCmdList[NV_FNPLL_INIT_N_IDX].value),
		*(phyNvCfgCmdList[NV_FNPLL_INIT_K_IDX].value));

	vc_lmac_phy_fnpll_force(
		*(phyNvCfgCmdList[NV_FNPLL_FORCE_FLAG_IDX].value),
		*(phyNvCfgCmdList[NV_FNPLL_FORCE_N_IDX].value),
		*(phyNvCfgCmdList[NV_FNPLL_FORCE_K_IDX].value));
}

extern volatile uint32_t systick_counter;

void delay(uint32_t msec)
{
  uint32_t delay = systick_counter + msec;
  while (delay > systick_counter);
}

void vc_lmac_cfg_dsp_auto_report_cnt(vc_uint8 onOff)
{
	tBbpRawCmd bbpRawCmd;
	vc_memset(&bbpRawCmd, 0x00, sizeof(tBbpRawCmd));
	bbpRawCmd.bbpCmd[0] = VC_LMAC_RCMD_CFG_DSP_AUTO_CNT;
	bbpRawCmd.bbpCmd[1] = onOff;
	bbpRawCmd.bbpCmd[2] = 205; /*how many PmbHit times report TxCnt*/
	bbpRawCmd.bbpCmd[3] = 200; /*how many PmbHit times report RxCnt*/
	bbpRawCmd.bbpCmdLen = 16;
	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
	printf("#lmacCfgDspAutoReportCnt:%d", onOff);
	return;
}

void vc_lmac_phy_band(vc_uint32 band)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;
	tBbpRawCmd bbpRawCmd;
	//vc_uint32 bbpCmd = 0x00;
	printf("#SettingPhyBand:%d\r\n", band);
	gLMAC->lmacBand = band;
	vc_memset(&bbpRawCmd, 0x00, sizeof(tBbpRawCmd));
	bbpRawCmd.bbpCmd[0] = VC_LMAC_RCMD_BAND;
	bbpRawCmd.bbpCmd[1] = band;
	bbpRawCmd.bbpCmdLen = 8;
	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
	vc_lmac_cfg_dsp_auto_report_cnt(1);
}

void vc_lmac_cfg_phy_role(vc_uint8 role)
{
	volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	if (role) {
		phyReg->phy_cr2 |= 0x80000000;
	} else {
		phyReg->phy_cr2 &= 0x7FFFFFFF;
	}
}

void vc_lmac_phy_cfg_cui_tei(vc_uint16 CTEI)
{
	tBbpRawCmd bbpRawCmd;
	//vc_uint32 bbpCmd = 0x00;
	vc_memset(&bbpRawCmd, 0x00, sizeof(tBbpRawCmd));
	bbpRawCmd.bbpCmd[0] = VC_LMAC_RCMD_CFG_CIU;
	bbpRawCmd.bbpCmd[1] = 1;
	bbpRawCmd.bbpCmd[2] = CTEI;
	bbpRawCmd.bbpCmdLen = 12;
	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

void vc_lmac_cfg_dsp_tx_dual_bcn(vc_uint32 cfgValue)
{
	tBbpRawCmd bbpRawCmd;
	vc_memset(&bbpRawCmd, 0x00, sizeof(tBbpRawCmd));
	bbpRawCmd.bbpCmd[0] = VC_LMAC_RCMD_CFG_DSP_DUAL_BCN;
	bbpRawCmd.bbpCmd[1] = cfgValue;
	bbpRawCmd.bbpCmd[2] = 0;
	bbpRawCmd.bbpCmdLen = 12;
	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

void vc_lmac_setting_phy_band(void)
{
	LMAC_CONTEXT_PTR gLMAC = LMAC_PTR;

	vc_lmac_phy_band(gLMAC->lmacBandSearch.currentBand);

  // STA role
	{
		tBbpRawCmd bbpRawCmd;
		vc_uint32 bbpCmd = 0x00;
		vc_memset(&bbpRawCmd, 0x00, sizeof(tBbpRawCmd));
		bbpRawCmd.bbpCmdLen = 4;
		bbpCmd = 0x1055;
		vc_memcpy(&bbpRawCmd.bbpCmd[0], &bbpCmd, 4);
		vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);

		bbpCmd = 0x1065;
		vc_memcpy(&bbpRawCmd.bbpCmd[0], &bbpCmd, 4);
		vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
	  vc_lmac_cfg_phy_role(0);
	}

  vc_lmac_nv_cfg_init();
  gLMAC->lmacConfig.init_flag = 0;
  vc_phy_sw_setting_idle();
  vc_phy_lmac_cfg_payload_crc_filter(0);
	vc_lmac_phy_cfg_cui_tei(gLMAC->LMAC_CTEI);

  vc_lmac_cfg_dsp_tx_dual_bcn(0);
}

void vc_lmac_misc_clock_gating_cfg()
{
  // TODO: disable unused periph clock
}

void vc_lmac_cfg_phy_rx_enable()
{
	volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	phyReg->phy_cr1 &= 0xFFFDFFFF;
	return;
}

void vc_lmac_init(void)
{
	printf("vc_lmac_init\r\n");

  vc_lmac_cfg_init();
  vc_lmac_hwmac_init();

  delay(1000);

  vc_lmac_setting_phy_band();

#if VC_HPLC_DSP_AUTO_ACK_ARQ
	printf("DSP ARQ\r\n");
#else
	printf("MAC ARQ\r\n");
#endif

	vc_phy_lmac_cfg_3p_gpio_finish(1);
  vc_lmac_misc_clock_gating_cfg();
	vc_lmac_cfg_phy_rx_enable();

  printf("PLC LMAC init done\r\n");
}
