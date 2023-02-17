#include <stdio.h>

#include "vc_lmac.h"
#include "vc_lmac_dma_if.h"
#include "vc_lmac_txh.h"
#include "vc_string.h"

void vc_lmac_setting_band(vc_uint8 band)
{
	tBbpRawCmd bbpRawCmd;
	vc_memset(&bbpRawCmd, 0x00, sizeof(tBbpRawCmd));
	bbpRawCmd.bandSetting = 1;
	//bbpRawCmd.bandSetting = band;
	bbpRawCmd.band = band;
	bbpRawCmd.bbpCmd[0] = VC_LMAC_RCMD_BAND;
	bbpRawCmd.bbpCmd[1] = band;
	bbpRawCmd.bbpCmdLen = 8;
	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
	printf("#lmacSetBand:%d\r\n", band);
	return;
}
