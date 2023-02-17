#ifndef _VC_BPLC_DRV_H_
#define _VC_BPLC_DRV_H_

#include "phy.h"
#include "vc_type.h"

#define PHY_IDLE_MASK			(1 << 2)
#define PHY_BUSY_MASK			((1 << 1) | (1 << 3) | (1 << 9) )
#define PHY_BUSY_NORMAL_TX_MASK	(1 << 1)
#define PHY_BUSY_RX_MASK		(1 << 3)
#define PHY_BUSY_RESP_ACK_MASK	(1 << 9)

vc_uint8 vc_phy_check_idle();
vc_uint32 vc_phy_get_busy_state();
vc_uint32 vc_phy_get_dsp_state();
vc_uint32 vc_phy_get_ntb();
vc_uint8 vc_phy_sw_setting_idle();
vc_uint8 vc_phy_disable_bit_reversal();
vc_uint8 vc_phy_enable_phy_reply_mode();
vc_uint8 vc_phy_disable_phy_reply_mode();
vc_uint8 vc_phy_enable_phy_not_check_pbcs();
vc_uint8 vc_phy_disable_phy_not_check_pbcs();
vc_uint8 vc_phy_lmac_cfg_phy_NID(vc_uint32 NID);
vc_uint8 vc_phy_lmac_clean_phy_NID();
vc_uint8 vc_phy_lmac_cfg_phy_PTEI(vc_uint16 PTEI);
vc_uint8 vc_phy_lmac_clean_phy_PTEI();
vc_uint8 vc_phy_lmac_cfg_phy_disconnect(vc_uint8 disconnect);
vc_uint8 vc_phy_lmac_cfg_3p_gpio_finish(vc_uint8 isFinish);
vc_uint8 vc_phy_lmac_cfg_disable_phy_reply_nack(vc_uint8 disableNack);
vc_uint8 vc_phy_lmac_cfg_bcn_time_slot(vc_uint8 bcnTimeSlotLens);
vc_uint8 vc_phy_lmac_cfg_phy_RIFS(vc_uint16 timeRIFS);
vc_uint8 vc_phy_lmac_cfg_payload_crc_filter(vc_uint8 onOff);
vc_uint8 vc_phy_lmac_cfg_fnpll_correction(vc_uint8 onOff);
vc_uint8 vc_phy_lmac_cfg_dsp_ARQ(vc_uint8 onOff);
vc_uint8 vc_phy_lmac_cfg_dsp_ARQ_STEI(vc_uint16 mySTEI);

#endif
