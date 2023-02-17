#ifndef _PHY_H_
#define _PHY_H_

#include <stdint.h>

#if defined(DEVICE_MCU_VC6320)
#define PHY_REG_BASEADDR 0x400111c0
#elif defined(DEVICE_MCU_VC6330)
#define PHY_REG_BASEADDR 0x400111a0
#else
#error "Invalid PLC Device MCU"
#endif

typedef struct PHY_REG {
#if defined(DEVICE_MCU_VC6330)
  uint32_t ntb_cnt; //0x1A0
  uint32_t ntb_zc1; //0x1A4
  uint32_t ntb_zc2; //0x1A8
  uint32_t ntb_zc3; //0x1AC
  uint32_t zc_cr;   //0x1B0
  uint32_t zc_sr1;  //0x1B4
  uint32_t zc_sr2;  //0x1B8
  uint32_t zc_pdc;  //0x1BC
#endif
	uint32_t phy_cr1; //0x1C0
	uint32_t phy_cr2; //0x1C4
	uint32_t phy_cr3; //0x1C8
	uint32_t phy_cr4;	//0x1CC
	uint32_t phy_ir1;	//0x1D0
	uint32_t phy_ir2;	//0x1D4
	uint32_t phy_ir3;	//0x1D8
	uint32_t phy_ir4;	//0x1DC
#if defined(DEVICE_MCU_VC6330)
  uint32_t phy_cr5; //0x1E0
  uint32_t phy_cr6; //0x1E4
  uint32_t phy_cr7; //0x1E8
  uint32_t phy_cr8; //0x1EC
  uint32_t phy_ir5; //0x1F0
  uint32_t phy_ir6; //0x1F4
  uint32_t phy_ir7; //0x1F8
  uint32_t phy_ir8; //0x1FC
#endif
#if defined(DEVICE_MCU_VC6320)
	uint32_t ntb_cnt;	//0x1E0
	uint32_t ntb_zc1;	//0x1E4
	uint32_t ntb_zc2;	//0x1E8
	uint32_t ntb_zc3;	//0x1EC
#endif
} PHY_REG;

#endif
