#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>

#include "phoenix.h"

#include "hplc.h"
#include "hplc_bbp.h"
#include "hplc_dma.h"
#include "hplc_lmac.h"
#include "hplc_pll.h"
#include "hplc_tx.h"

#if defined(DEVICE_MCU_VC6320)
#define DSP_IRAM_BASE	 0x20080000
#define DSP_DATA0_BASE 0x200C0000
#define DSP_DATA1_BASE 0x200E0000
#define DSP_END 0x20100000

#define DSP_IRAM_SIZE	 (DSP_DATA0_BASE - DSP_IRAM_BASE)
#define DSP_DATA0_SIZE (DSP_DATA1_BASE - DSP_DATA0_BASE)
#define DSP_DATA1_SIZE (DSP_END - DSP_DATA1_BASE)

#define DSP_READY_FLAG (0x20)
#endif

#if defined(DEVICE_MCU_VC6330)
#define DSP_IRAM_BASE	 0x20110000
#define DSP_DATA0_BASE 0x20150000
#define DSP_DATA1_BASE 0x20170000

#define DSP_IRAM_SIZE	 (DSP_DATA0_BASE - DSP_IRAM_BASE)
#define DSP_DATA0_SIZE (0x14000) // 80Kb
#define DSP_DATA1_SIZE (0x1C000) // 80Kb+32Kb

#define DSP_READY_FLAG (0x7)
#endif

// static void phy_reset(bool release)
// {
// 	volatile PHY_REG *reg_space = (volatile PHY_REG *)PHY_REG_BASEADDR;
// 	uint32_t reg = 0;
// 	if (release){
// 		reg |= 0x03;
// 	}else{
// 		reg &= ~0x03;
// 	}	
// 	reg_space->phy_cr1 = reg;
// }

void vc_lmac_phy_band(uint32_t band)
{
	bbpRawCmdStruct bbpRawCmd;
	memset(&bbpRawCmd, 0x00, sizeof(bbpRawCmdStruct));

	bbpRawCmd.bbpCmd[0] = VC_LMAC_RCMD_BAND;
	bbpRawCmd.bbpCmdLen += 4;
	bbpRawCmd.bbpCmd[1]= band;
	bbpRawCmd.bbpCmdLen += 4;

	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

void vc_lmac_phy_cfg_txpwr(uint8_t txpwr)
{
	bbpRawCmdStruct bbpRawCmd;

	memset(&bbpRawCmd, 0x00, sizeof(bbpRawCmdStruct));

	bbpRawCmd.bbpCmd[0] = VC_LMAC_RCMD_CFG_PHY_TX_SWING;
	bbpRawCmd.bbpCmd[1] = 0;
	bbpRawCmd.bbpCmd[2] = 0;
	bbpRawCmd.bbpCmd[3] = txpwr;
	bbpRawCmd.bbpCmdLen += 16;

	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);

	/*********************************************************************/
	/*  |-12  |-11  |-10  |-09  |**|+00  |**|+10  |+11  |+12  |(+-dB) |  */
	/*  |-------------------------------------------------------------|  */
	/*  |0x00 |0x01 |0x02 |0x03 |**|0x0C |**|0x16 |0x17 |0x18 |(Hex)  |  */
	/*********************************************************************/
}

void vc_lmac_pwr()
{
	bbpRawCmdStruct bbpRawCmd;
	memset(&bbpRawCmd, 0x00, sizeof(bbpRawCmdStruct));

	bbpRawCmd.bbpCmd[0] = LMAC_BBP_RAW_CMD_PWR_CNF;
	bbpRawCmd.bbpCmdLen += 4;

	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

void vc_lmac_rxc()
{
	bbpRawCmdStruct bbpRawCmd;
	memset(&bbpRawCmd, 0x00, sizeof(bbpRawCmdStruct));

	bbpRawCmd.bbpCmd[0] = LMAC_BBP_RAW_CMD_RXC_CNF;
	bbpRawCmd.bbpCmdLen += 4;

	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

void vc_lmac_txc()
{
	bbpRawCmdStruct bbpRawCmd;
	memset(&bbpRawCmd, 0x00, sizeof(bbpRawCmdStruct));

	bbpRawCmd.bbpCmd[0] = LMAC_BBP_RAW_CMD_TXC_CNF;
	bbpRawCmd.bbpCmdLen += 4;

	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

void vc_lmac_ver()
{
	bbpRawCmdStruct bbpRawCmd;
	memset(&bbpRawCmd, 0x00, sizeof(bbpRawCmdStruct));

	bbpRawCmd.bbpCmd[0] = LMAC_BBP_RAW_CMD_VER_CNF;
	bbpRawCmd.bbpCmdLen += 4;

	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

void vc_lmac_tx_pkt()
{
	bbpRawCmdStruct bbpRawCmd;
	memset(&bbpRawCmd, 0x00, sizeof(bbpRawCmdStruct));

	bbpRawCmd.bbpCmd[0] = 0x72;
	bbpRawCmd.bbpCmdLen += 4;

	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

void vc_lmac_vc6320a1_mp_version_setting()
{
	bbpRawCmdStruct bbpRawCmd;
	memset(&bbpRawCmd, 0x00, sizeof(bbpRawCmdStruct));

	bbpRawCmd.bbpCmd[0] = 0x02;
	bbpRawCmd.bbpCmdLen += 4;

	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
}

#define FLASH_START        (0x04000000)
#define FLASH_DSP_OFFSET   (0x00080000)
#define OFFSET_TO_BBP_IND  (0xc0)
#define OFFSET_TO_BBP_CODE (0x800)

void vc_lmac_setting_phy_band(void)
{
	volatile PHY_REG *reg_space = (volatile PHY_REG *)PHY_REG_BASEADDR;

	// #if(CHIP_IS_MP_VERSION)
	volatile uint32_t *add114 = (volatile uint32_t *)0x4004b114;
	volatile uint32_t *add118 = (volatile uint32_t *)0x4004b118;
	volatile uint32_t *add110 = (volatile uint32_t *)0x4004b110;
	volatile uint32_t *add1c8 = (volatile uint32_t *)0x400111c8;
	// #endif
	//
	// #if(CHIP_IS_MP_VERSION)
	*(add114)=0x2400000;/*FnPL,INT*/
	*(add118)=0x00;/*FnPL,Float*/
	*(add110)=0x1;/*Enable*/
	*(add1c8)=0x0c;/*ClockGathering*/
	// //vc_lmac_vc6320a1_mp_version_setting();
	// #endif

	#if 1
	reg_space->phy_cr2 |= 0x80000000;
	//printf("ConfigPHY: CCO role!\r\n"); //read dsp tx info
	#else
	reg_space->phy_cr2 &= 0x7FFFFFFF;
	//printf("ConfigPHY: STA role!\r\n");
	#endif
}

// static int vc_memcpy32(void *s1, void *s2, unsigned long n)
// {
// 	unsigned long *desc=(unsigned long *)s1;
// 	unsigned long *src=(unsigned long *)s2;
// 	for ( ; n-- ; desc++, src++) {
// 		*desc = *src;
// 	}
// 	return 0;
// }
//
// volatile uint32_t *info_hb0 = (volatile uint32_t *)(FLASH_START+FLASH_DSP_OFFSET+OFFSET_TO_BBP_IND);

void vc_phy_init(void)
{
	volatile PHY_REG* reg_space = (volatile PHY_REG*)PHY_REG_BASEADDR;
	uint32_t timeout = 50;
  //uint32_t *reloc_info = (uint32_t *)&info_hb0[0];

 
  // if (*reloc_info == 0xffffffff)
  // {
  //   printf("BBP flash data not written\r\n");
  //   return;
  // }

 //  #if defined(DEVICE_MCU_VC6320)
	// BplcFnPll();
 //  #endif

	//phy_reset(false);

  // NOTE: Phoenix 2 real chip need to use JLink to load DSP image

	//  memset((void *)DSP_IRAM_BASE, 0, DSP_IRAM_SIZE);
	//  memset((void *)DSP_DATA0_BASE, 0, DSP_DATA0_SIZE);
	//  memset((void *)DSP_DATA1_BASE, 0, DSP_DATA1_SIZE);
	//
  //  // relocate bbp program and data
  //  while (*reloc_info != 0)
  //  {
  //    //printf("Relocation info: 0x%08x 0x%08x 0x%08x 0x%08x\r\n", (unsigned int)reloc_info[0], (unsigned int)reloc_info[1], (unsigned int)reloc_info[2], (unsigned int)reloc_info[3]);
	//
  //    vc_memcpy32((void *)reloc_info[0], (void *)reloc_info[1], reloc_info[2]/4);
  //
  //    if (memcmp((void *)reloc_info[0], (void *)reloc_info[1], reloc_info[2]/4) == 0)
  //    {
  //      reloc_info += 4;
  //    }
  //    else
  //    {
  //      printf("DSP load failed: 0x%08x 0x%08x 0x%08x 0x%08x\r\n",
  //             (unsigned int)reloc_info[0], (unsigned int)reloc_info[1], (unsigned int)reloc_info[2], (unsigned int)reloc_info[3]);
  //      break;
  //    }
  //  }

	//phy_reset(true);

  reg_space->phy_cr1 = 0;

	timeout=0x1000*100;
	while(timeout--);

	reg_space->phy_cr1 |= 0x10C003;

  timeout = 50;

  while (((reg_space->phy_ir1 & DSP_READY_FLAG) != DSP_READY_FLAG) && (timeout-- > 0))
  {
		//printf("0x%08x | 0x%08x | 0x%08x | 0x%08x | 0x%08x\r\n", reg_space->phy_cr1, reg_space->phy_ir1, reg_space->phy_ir2, reg_space->phy_ir3, reg_space->phy_ir4);
    printf("Wait for DSP ready...%u\r\n", (unsigned int)(50 - timeout));
	}

  if (timeout == 0)
  {
    printf("Wait for DSP ready is Timeout, init failed\r\n");
    return;
  }

  if ((reg_space->phy_ir1 & DSP_READY_FLAG) == DSP_READY_FLAG)
  {
		//reg_space->phy_cr1 |=0x100;/*DyingGaspEnable*/
		reg_space->phy_cr3 |= 0xc; // enable CNMAC clock

  //   #if(CHIP_IS_MP_VERSION)
		// *RG_BUCK_CTRL &= 0xFFFFFFF8;
		// //*RG_BUCK_CTRL |= 0x4;
		// *RG_BUCK_CTRL |= 0x5;
		// *RG_LDO_CTRL &= 0xFFFFFFF8;
		// //*RG_LDO_CTRL |= 0x4;
		// *RG_LDO_CTRL |= 0x5;
  //   #endif
  }
  else
  {
    printf("INIT failed: DSP not idle!\r\n");
    return;
  }

  printf("PHY_INIT: OK\r\n");
	printf("PHY_IR1=%x\r\n", (unsigned int)reg_space->phy_ir1);
	printf("PHY_IR3=%x\r\n", (unsigned int)reg_space->phy_ir3);

  vc_lmac_setting_phy_band();

	timeout=0x1000*100;
	while(timeout--);

	vc_lmac_phy_band(BPLC_BAND_1);
  vc_lmac_phy_cfg_txpwr(0xf);

  //reg_space->phy_cr1 |= 0x10000;
}

uint8_t vc_phy_check_idle()
{
	volatile PHY_REG* reg_space = (volatile PHY_REG*)PHY_REG_BASEADDR;
	uint8_t plcDspIdle=0;
	if((reg_space->phy_ir1 & PHY_IDLE_MASK) == PHY_IDLE_MASK) {
		plcDspIdle = 1;
	}else{
		plcDspIdle = 0;
	}
	return plcDspIdle;
}

uint32_t vc_phy_get_ntb()
{
	uint32_t currentNTB=0;
	volatile PHY_REG* reg_space = (volatile PHY_REG*)PHY_REG_BASEADDR;
	currentNTB = reg_space->ntb_cnt;
	return currentNTB;
}
