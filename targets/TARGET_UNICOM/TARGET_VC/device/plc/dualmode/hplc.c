#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include "device.h"
#include "pinmap.h"
#include "pinmap_ex.h"

#include "hplc.h"
#include "hplc_bbp.h"
#include "hplc_lmac.h"
#include "hplc_dma.h"
#include "hplc_tx.h"
#include "hplc_rx.h"

LMAC_CONTEXT_PTR lmac_ptr_g;

void vc_lmac_cfg_cnmac(void)
{
	volatile tVCMAC_REGISTER *cnMacReg = (volatile tVCMAC_REGISTER *)VC_MAC_CN_BASE;
	volatile tVC_G3MAC_REG *g3MacReg = (volatile tVC_G3MAC_REG *)VC_MAC_G3_BASE;

	cnMacReg->MAC_CR.value		=	0x00040001;
	cnMacReg->CNMAC_CR.value	=	0x00000077;
	cnMacReg->CNMAC_IER.value	=	0xFFFFFFFF;
	cnMacReg->CNMAC_ISR.value	=	0xFFFFFFFF;
	cnMacReg->CNRXF_SET1_SR1.fields.csr_cnrxf_nid1	=	WISUN_NID;
	cnMacReg->CNRXF_SET1_SR2.fields.csr_cnrxf_dtei1	=	WISUN_TEI;
	cnMacReg->CNVCS_SR1.fields.csr_cnvcs_tt			=	300;
	cnMacReg->CNVCS_SR2.value	=	30000;
	cnMacReg->CNVCS_SR3.value	=	LMAC_CIFS;
	cnMacReg->CNVCS_SR4.value	=	LMAC_RIFS;
	cnMacReg->CNSCH_CR1.fields.csr_cnsch_md_hwretry	=	0;
	cnMacReg->CNSCH_CR1.fields.csr_cnsch_chksp		=	0;
	//cnMacReg->CNSCH_TSR1.fields.csr_cnsch_txdur		=	0;
	cnMacReg->CNSCH_TSR1.fields.csr_cnsch_csma		=	0;
	g3MacReg->CR.value			=	0;
}

void vc_lmac_cfg_init(void)
{
	//LMAC_PTR = &g_lmac;//get_ctrl_buffer(sizeof(lmac_context_struct));
	LMAC_PTR->lmacCsma.minBE = LMAC_CSMA_MIN_BE;
	LMAC_PTR->lmacCsma.maxBE = LMAC_CSMA_MAX_BE;
	LMAC_PTR->lmacCsma.period = LMAC_CSMA_BACKOFF_PERIOD;
	LMAC_PTR->lmacCsma.retry = LMAC_CSMA_MAX_BACKOFFS;
	LMAC_PTR->lmacConfig.hv_flag = 0;
	LMAC_PTR->lmacBand = BPLC_BAND_1;
	LMAC_PTR->lmacToneMask = 0;
	LMAC_PTR->LMAC_DTEI = 0x0000;
	LMAC_PTR->LMAC_STEI = 0x0000;
}

#define IRQ_PRIO_PLCDMA			7//6
#define IRQ_PRIO_PLCMAC			6//5

void vcplc_init()
{
	vc_lmac_cfg_init();
	vc_lmac_cfg_cnmac();
	vc_lmac_cfg_dma();
	//vc_lmac_cfg_sack_arq();
	//vc_lmac_cfg_csma();

	vc_phy_init();

  NVIC_EnableIRQ(PLC_DMA_IRQn);
  NVIC_EnableIRQ(PLC_MAC_IRQn);
}

int vcplc_transmit(const uint8_t *data, uint32_t len)
{
	int ret;

	ret = vc_lmac_tx_sof_pkt_f_cmd_txdata(0x0FFF, 0, 1, (uint8_t *)data, len);

	if (ret == HPLC_TX_OK)
		return PLC_TX_OK;
	else if (ret == HPLC_TX_ERR)
		return PLC_TX_ERR;
	else if (ret == HPLC_TX_BUSY)
		return PLC_TX_BUSY;
	else if (ret == HPLC_TX_COLLISION)
		return PLC_TX_COLLISION;

	return ret;

}

int _s_hplc_send(int argc, char **argv)
{
  uint8_t data[300];

	uint32_t i, count;
	uint8_t tim;

	if(argc==1)
  {
		count=1;
		tim=13;
		printf("htx 1\n");
	}
  else if (argc==2)
  {
		count=1;
		tim=(uint32_t)strtoul(argv[1], NULL, 16);
		printf("htx 2\n");
	}
  else
  {
		count=(uint32_t)strtoul(argv[2], NULL, 16);
		tim=(uint8_t)strtoul(argv[1], NULL, 16);
		printf("htx k\n");
	}

	if(tim > 14) tim=13;

	for(i=0; i<300; i++) data[i]=i;

	for(i=0; i<count; i++)
		vc_lmac_tx_sof_pkt_f_cmd_txdata(0x0FFF, 0, 1, data, 100);
	
	return 3;
}

/*	To check whether the medium is idle or not. This translates to checking whether VCS and PHY are idle. 	*/
int vcplc_isMediumIdle()
{
	if(vc_lmac_check_vcs_idle() && vc_phy_check_idle()){
		return 1;
	}

	return 0;
}

int _bplcPingCmd(int argc, char **argv)
{
	int i = 0;
	printf("VC+BPING:%d\n",argc);
	for(i=0;i<argc;i++){
		printf("%s, ",argv[i]);
	}
	printf("\r\n");

	 if (strcmp(argv[1], "t") == 0) {
		vc_lmac_tx_sof_pkt_f_phy_ping(
			0xFFF,
			0,
			0,
			1);
	}
	 if (strcmp(argv[1], "sof") == 0) {
		vc_lmac_tx_sof_pkt_f_cmd_ping(
			0xFFF,
			0,
			0,
			1,
			1);
	}
	 if (strcmp(argv[1], "rxc") == 0) {
		vc_lmac_rxc();
	}
	if (strcmp(argv[1], "txc") == 0) {
		vc_lmac_txc();
	}
	if (strcmp(argv[1], "txpkt") == 0) {
		vc_lmac_tx_pkt();
	}
	printf("+BPING : OK!!\n");
	return 0;
}

int _hplc(int argc, char **argv)
{
	if(argc==1)
	{	vcplc_init();
		return 3;
	}
	
	return 3;
}

int _hplc_lmac_dump_tx_desc(int argc, char **argv)
{
	lmac_dump_tx_desc();
	return 0;
}

int _hplc_lmac_dump_rx_desc(int argc, char **argv)
{
	lmac_dump_rx_desc();
	return 0;
}

int _hplc_lmac_dump_bbp_rxc(int argc, char **argv)
{
	vc_lmac_rxc();
	return 0;
}

int _hplc_lmac_dump_bbp_txc(int argc, char **argv)
{
	vc_lmac_txc();
	return 0;
}

int _hplc_lmac_txpwr(int argc, char **argv)
{
	if(argc == 2) {
		uint8_t value = atoi(argv[1]) + 0x0c;
		if(value > 0x18) {
			printf("%s, error to setting txpwr as: %d\n", __func__, (value - 0x0c));
			return 0;
		}
		printf("setting plc power as :%d\n", (value - 0x0c));
		vc_lmac_phy_cfg_txpwr(value);
	} else {
		vc_lmac_pwr();
	}
	return 0;
}

int _hplc_lmac_dump_ver(int argc, char **argv)
{
	vc_lmac_ver();
	return 0;
}

