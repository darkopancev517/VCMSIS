#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include "magpie2.h"
#include "phy.h"
#include "pll.h"
#include "vc_bbp_drv.h"
#include "vc_type.h"
#include "vc_string.h"
#include "hal_pmu.h"

static int vc_memcpy32(void *pDest, void *pSrc, unsigned long n)
{
	unsigned long *dest = (unsigned long *)pDest;
	unsigned long *src = (unsigned long *)pSrc;
	for ( ; n-- ; dest++, src++) {
		*dest = *src;
	}
	return 0;
}

void phy_reset(bool release)
{
	volatile PHY_REG *phyReg = (volatile PHY_REG *)PHY_REG_BASEADDR;
	uint32_t reg = 0;
	if (release){
		reg |= 0x03;
	}else{
		reg &= ~0x03;
	}	
	phyReg->phy_cr1 = reg;
	/*NEO: Debug used for YY*/
	//reg_space->phy_cr1 = 0x00001003;
	//printf("PHY_CR1<- %08x\r\n",  reg);   
}

#define PHOENIX_FLASH_START	0x0
#define BUILD_OFFSET        (0x00080000)
#define OFFSET_TO_BBP_IND		0xc0
#define OFFSET_TO_BBP_CODE	0x800

volatile uint32_t * info_hb0 = (volatile uint32_t *)(PHOENIX_FLASH_START+BUILD_OFFSET+OFFSET_TO_BBP_IND);

// ---------------------------------------------------------------------------
// BBP/PHY control

#define DSP_IRAM_BASE		0x20080000/*192*/
#define DSP_DATA0_BASE	0x200C0000/*96*/
#define DSP_DATA1_BASE	0x200E0000/*96*/
#define DSP_END					0x20100000

#define DSP_ACCURATE_IRAM	 0x30000 /*192 KByte*/
#define DSP_ACCURATE_DATA0 0x18000 /*96 KByte*/
#define DSP_ACCURATE_DATA1 0x18000 /*96 KByte*/

#define DSP_IRAM_SIZE	 DSP_DATA0_BASE - DSP_IRAM_BASE
#define DSP_DATA0_SIZE DSP_DATA1_BASE - DSP_DATA0_BASE
#define DSP_DATA1_SIZE DSP_END - DSP_DATA1_BASE

uint32_t phyInitDelay = 0;
vc_uint32 vc_phy_do_crc_32(vc_uint32 *buf, vc_uint32 len)
{
	unsigned int byte, crc, mask;
	int i, j;
	crc = 0xFFFFFFFF;
	for (i = 0; i < len; i++) {
		byte = buf[i];
		crc = crc ^ byte;
		for (j = 7; j >= 0; j--) {
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
		}
	}
	crc ^= 0xFFFFFFFF;
	return crc;
}

void vc_phy_check_dsp_memory(vc_uint32 parameter)
{
	volatile vc_uint32 *dspIram = (volatile vc_uint32 *)DSP_IRAM_BASE;
	volatile vc_uint32 *dspData0 = (volatile vc_uint32 *)DSP_DATA0_BASE;
	volatile vc_uint32 *dspData1 = (volatile vc_uint32 *)DSP_DATA1_BASE;
	unsigned long int i = 0;
	
	for(i = 0;i <(DSP_ACCURATE_IRAM/4);i++){
		if(*(dspIram + i)!=parameter){
			//ULOG(ULL_INF, "ErrorBitIram: %d, 0x%08X, %08X!=%08X",i, dspIram + i, *(dspIram + i),parameter);
      printf("ErrorBitIram\r\n");
		}
	}
	for(i=0;i<(DSP_ACCURATE_DATA0/4); i++){
		if(*(dspData0 + i)!=parameter){
			//ULOG(ULL_INF, "ErrorBitData0: %d, 0x%08X, %08X!=%08X",i, dspData0 + i, *(dspData0 + i),parameter);
      printf("ErrorBitData0\r\n");
		}
	}
	for(i=0;i<(DSP_ACCURATE_DATA1/4); i++){
		if(*(dspData1 + i)!=parameter){
			//ULOG(ULL_INF, "ErrorBitData1: %d, 0x%08X, %08X!=%08X",i, dspData1 + i, *(dspData1 + i),parameter);
      printf("ErrorBitData1\r\n");
		}
	}
}

void vc_phy_init(void)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	//vc_uint32 dspIdx = 0;
	vc_uint32 *reloc_info = (vc_uint32*)&info_hb0[0];
	//vc_uint32 i = 0;
	vc_uint32 dspRamCrc = 0x00;
	vc_uint32 dspFlashCrc = 0x00;
	
	fnpll_bplc();

	if(*reloc_info == 0xFFFFFFFF){
		//ULOG(ULL_INF, "BBP Flash Data NOT written");
    printf("BBP Flash Data NOT written\r\n");
		phy_reset(true);
		return;
	}
	phy_reset(false);
	// clear bbp memory ...
	vc_memset((void *)DSP_IRAM_BASE, 0xFF, DSP_IRAM_SIZE);
	vc_memset((void *)DSP_DATA0_BASE, 0xFF, DSP_DATA0_SIZE);
	vc_memset((void *)DSP_DATA1_BASE, 0xFF, DSP_DATA1_SIZE);
	vc_phy_check_dsp_memory(0xFFFFFFFF);
	vc_memset((void *)DSP_IRAM_BASE, 0x00, DSP_IRAM_SIZE);
	vc_memset((void *)DSP_DATA0_BASE, 0x00, DSP_DATA0_SIZE);
	vc_memset((void *)DSP_DATA1_BASE, 0x00, DSP_DATA1_SIZE);
	vc_phy_check_dsp_memory(0x00000000);
	// relocate bbp program and data ..
	while (*reloc_info != 0){
		vc_memcpy32((void*)reloc_info[0], (void*)reloc_info[1], reloc_info[2]/4);
		dspRamCrc = 
			vc_phy_do_crc_32((void*)reloc_info[0],reloc_info[2]/4);
		dspFlashCrc = 
			vc_phy_do_crc_32((void*)reloc_info[1],reloc_info[2]/4);		
		if(dspRamCrc != dspFlashCrc){
			//ULOG(ULL_INF, "%08X,%08X,%d. Warning!! DSP RAM Data is not Correct!!Please Check Flash and DSP SRAM!!",(void*)reloc_info[0], (void*)reloc_info[1], reloc_info[2]/4);
			printf("%08X,%08X,%d. Warning!! DSP RAM Data is not Correct!!Please Check Flash and DSP SRAM!!\r\n",
             (unsigned int)(void*)reloc_info[0],
             (unsigned int)(void*)reloc_info[1],
             (unsigned int)reloc_info[2]/4);
		}
		reloc_info += 4;
	}	
	phy_reset(true);
	//phyReg->phy_cr1 |= 0x00020000;//disable rx by default, then enable rx by lmac later
	phyReg->phy_cr1 |= 0x8000;
	//vcwdt_disable();
 	//vcwdt_set_period(3);
 	//vcwdt_enable();
	/*while (((phyReg->phy_ir1 & 0x20) != 0x20)){
		ULOG(ULL_INF, "phyReg->phy_cr1 0x%08x", phyReg->phy_cr1);
		ULOG(ULL_INF, "phyReg->phy_ir1 0x%08x", phyReg->phy_ir1);
		ULOG(ULL_INF, "phyReg->phy_ir2 0x%08x", phyReg->phy_ir2);
		ULOG(ULL_INF, "phyReg->phy_ir3 0x%08x", phyReg->phy_ir3);
		ULOG(ULL_INF, "phyReg->phy_ir4 0x%08x", phyReg->phy_ir4);
		ULOG(ULL_INF, "Phase 1 Wait DSP Ready...%lu", phyInitDelay);
		phyInitDelay++;
	}*/
	while (((phyReg->phy_ir1 & 0x20) != 0x20)){
		// ULOG(ULL_INF, 
		// 	"[PHY] cr1:0x%08x,ir1:0x%08x,ir2:0x%08x,ir3:0x%08x,ir4:0x%08x, Wait DSP Ready...%lu",
		// 	phyReg->phy_cr1, phyReg->phy_ir1, phyReg->phy_ir2, phyReg->phy_ir3, phyReg->phy_ir4, phyInitDelay);

		printf("[PHY] cr1:0x%08x,ir1:0x%08x,ir2:0x%08x,ir3:0x%08x,ir4:0x%08x, Wait DSP Ready...%lu\r\n",
			     phyReg->phy_cr1, phyReg->phy_ir1, phyReg->phy_ir2, phyReg->phy_ir3, phyReg->phy_ir4, (unsigned long)phyInitDelay);

		phyInitDelay++;

		phyInitDelay++;
	}
	//vcwdt_disable();
	if ((phyReg->phy_ir1 & 0x20) == 0x20){
		phyReg->phy_cr1 |= 0x100;/*DyingGaspEnable*/
    //phyReg->phy_cr1 |= 0x10000;/*Sw notify Dsp Sw init finished Flag*/
		#if (CHIP_IS_MP_VERSION) /*MP_VERSION_CONFIG*/
		phyReg->phy_cr3 |= 0x4;/*6320A1 Used clock gating*/
		hal_pmu_LDO_ctrl_config_vout_sel(0x5);
		hal_pmu_BUCK_ctrl_config_vout_sel(0x5);
		#endif
		
	}else{
		//ULOG(ULL_INF, "PLC DSP Not Idle ~ !");
    printf("PLC DSP Not Idle ~ !\r\n");
	}
	/*Disable unused GPIO*/
	//hal_gpio_high(IOB, 1);
	//hal_gpio_high(IOC, 4);
	//hal_gpio_high(IOC, 5);

  printf("PLC PHY init done\r\n");
}

vc_uint32 vc_phy_get_dsp_state()
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	return phyReg->phy_ir1;
}

vc_uint8 vc_phy_check_idle()
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	vc_uint8 plcDspIdle = 0;
	if((phyReg->phy_ir1 & PHY_IDLE_MASK) == PHY_IDLE_MASK){
		plcDspIdle = 1;
	}else{
		plcDspIdle = 0;
	}
	return plcDspIdle;
}

vc_uint32 vc_phy_get_busy_state()
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	return (phyReg->phy_ir2 & PHY_BUSY_MASK);
}

vc_ntb32 vc_phy_get_ntb()
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	vc_uint32 currentNTB = 0;
	//vc_uint32 mask=0;	
	//mask = OS_EnterCritical();
	currentNTB = phyReg->ntb_cnt;
	//OS_ExitCritical(mask);
	return currentNTB;
}

vc_uint8 vc_phy_sw_setting_idle()
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	phyReg->phy_cr1 |= (0x1 << 16);
	return 0;
}

vc_uint8 vc_phy_enable_bit_reversal()
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	phyReg->phy_cr1 |= (0x1 << 15);
	return 0;
}

vc_uint8 vc_phy_disable_bit_reversal()
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	phyReg->phy_cr1 &= ~(0x1 << 15);
	return 0;
}

vc_uint8 vc_phy_enable_phy_reply_mode()
{	
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
#if 0	
	phyReg->phy_cr2 |= 0x8;
#else	
	/*20201023 Rearrangement CR Table*/ 
	phyReg->phy_cr3 |= (0x1 << 28);
#endif
	return 0;
}

vc_uint8 vc_phy_disable_phy_reply_mode()
{	
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
#if 0	
	phyReg->phy_cr2 &= ~0x8;
#else
	/*20201023 Rearrangement CR Table*/ 
	phyReg->phy_cr3 &= ~(0x1 << 28);
#endif
	return 0;
}

vc_uint8 vc_phy_enable_phy_not_check_pbcs()
{
	//volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	//phyReg->phy_cr2 |= 0x4;
	return 0;
}

vc_uint8 vc_phy_disable_phy_not_check_pbcs()
{
	//volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	//phyReg->phy_cr2 &= ~0x4;
	return 0;
}

vc_uint8 vc_phy_lmac_cfg_phy_NID(vc_uint32 NID)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;

  /* Clear NID and Update. */
  phyReg->phy_cr3 &= ~(0xFFFFFF << 4);
	phyReg->phy_cr3 |= ((NID & 0xFFFFFF) << 4);
	phyReg->phy_cr1 |= (0x1 << 19);
	//ULOG(ULL_INF, "#cfgPhyNID:%08X,%08X",phyReg->phy_cr1,phyReg->phy_cr3);
	printf("#cfgPhyNID:%08X,%08X\r\n",phyReg->phy_cr1,phyReg->phy_cr3);
	return 0;
}
vc_uint8 vc_phy_lmac_clean_phy_NID()
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	phyReg->phy_cr1 &= ~(0x1 << 19);
	phyReg->phy_cr3 &= ~(0xFFFFFF << 4);	
	//ULOG(ULL_INF, "#cleanPhyNID:%08X,%08X",phyReg->phy_cr1,phyReg->phy_cr3);
	printf("#cleanPhyNID:%08X,%08X\r\n",phyReg->phy_cr1,phyReg->phy_cr3);
	return 0;
}

vc_uint8 vc_phy_lmac_cfg_phy_PTEI(vc_uint16 PTEI)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
#if 0	
	phyReg->phy_cr1 |= 0x100000;
	phyReg->phy_cr2 |= ((PTEI & 0xFFF) << 16);
#else
	/*20201023 Rearrangement CR Table*/	
	phyReg->phy_cr2 &= ~(0x1 << 28);
	phyReg->phy_cr2 &= ~(0xFFF << 16);
	
	phyReg->phy_cr2 |= ((PTEI & 0xFFF) << 16);	
	phyReg->phy_cr2 |= (0x1 << 28);	
#endif
	//ULOG(ULL_INF, "#PTEI:0x%03X",PTEI);
	//ULOG(ULL_INF, "#cfgPhyPTEI:%08X,%08X",phyReg->phy_cr1,phyReg->phy_cr2);
	printf("#PTEI:0x%03X\r\n",PTEI);
	printf("#cfgPhyPTEI:%08X,%08X\r\n",phyReg->phy_cr1,phyReg->phy_cr2);

	return 0;
}

vc_uint8 vc_phy_lmac_clean_phy_PTEI()
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
#if 0	
	phyReg->phy_cr1 &= ~0x100000;
	phyReg->phy_cr2 &= ~0x0FFF0000;	
#else
	/*20201023 Rearrangement CR Table*/ 
	phyReg->phy_cr2 &= ~(0x1 << 28);
	phyReg->phy_cr2 &= ~(0xFFF << 16);
#endif
	//ULOG(ULL_INF, "#cleanPhyPTEI:%08X,%08X",phyReg->phy_cr1,phyReg->phy_cr2);
	printf("#cleanPhyPTEI:%08X,%08X\r\n",phyReg->phy_cr1,phyReg->phy_cr2);
	return 0;
}

vc_uint8 vc_phy_lmac_cfg_phy_disconnect(vc_uint8 disconnect)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;	
#if 0	
	if(disconnect){
		phyReg->phy_cr1 &= ~0x180000;	
		phyReg->phy_cr1 |= 0x200000;
	}else{
		phyReg->phy_cr1 &= ~0x380000;
	}
#else
	/*20201023 Rearrangement CR Table*/ 
	if(disconnect){
		phyReg->phy_cr1 &= ~(0x1<<19);	/*ConfigPhyNID -> Off*/
		phyReg->phy_cr2 &= ~(0x1<<28);	/*ConfigPhyPTEI -> Off*/
		phyReg->phy_cr2 |= (0x1<<29);	/*ConfigPhyDisconnect -> On*/
	}else{
		phyReg->phy_cr1 &= ~(0x1<<19);	/*ConfigPhyNID -> Off*/
		phyReg->phy_cr2 &= ~(0x1<<28);	/*ConfigPhyPTEI  -> Off*/
		phyReg->phy_cr2 &= ~(0x1<<29);	/*ConfigPhyDisconnect  -> Off*/
	}
#endif
	//ULOG(ULL_INF, "#cfgPhyDisconnect:%08X",phyReg->phy_cr1);
	printf("#cfgPhyDisconnect:%08X\r\n",phyReg->phy_cr1);
	return 0;
}
vc_uint8 vc_phy_lmac_cfg_3p_gpio_finish(vc_uint8 isFinish)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	/*20201119 add feature 3p gpio finish nofity dsp*/
	if(isFinish){
		phyReg->phy_cr1 |= ((isFinish & 0x01) << 20);
	}else{
		phyReg->phy_cr1 &= ~(0x1 << 20);
	}
	return 0;
}
vc_uint8 vc_phy_lmac_cfg_disable_phy_reply_nack(vc_uint8 disableNack)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	
	//ULOG(ULL_INF, "#cfgDisablePhyReplyNack:%d",disableNack);
  printf("#cfgDisablePhyReplyNack:%d\r\n",disableNack);

	if(disableNack){
		phyReg->phy_cr1 |= ((disableNack & 0x01) << 21);
	}else{
		phyReg->phy_cr1 &= ~((0x01) << 21);
	}
	return 0;
}
vc_uint8 vc_phy_lmac_cfg_bcn_time_slot(vc_uint8 bcnTimeSlotLens)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	vc_uint16 phy_bcn_unit_5_us = 0;
	// The max value is 255 for the BPLC_B_CN_34D6_20200922_02.dat(8 bits)
	/*20201214 change into 6 bit, cause disablePhyRepelyNACK*/
	/*20201119 change into 7 bit, cause 3p gpio finish*/
	/*20201023 Rearrangement CR Table*/
	//ULOG(ULL_ERR,"BTSL:%u",bcnTimeSlotLens);
	phy_bcn_unit_5_us = (bcnTimeSlotLens / 5);
	if(phy_bcn_unit_5_us >= 0 && phy_bcn_unit_5_us <= 255){
		phyReg->phy_cr1 |= ((phy_bcn_unit_5_us & 0x3F) << 22);
	} else {
		phyReg->phy_cr1 &= ~(0x3F << 22);
	}
	//printf("#cfgPhyBcnTimeSlot:%08X\r\n",phyReg->phy_cr2);
	return 0;
}
vc_uint8 vc_phy_lmac_cfg_phy_RIFS(vc_uint16 timeRIFS)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;
	vc_uint16 phy_RIFS_unit_200_us = 0;

	phy_RIFS_unit_200_us = (timeRIFS / 200);	
#if 0 
	if(timeRIFS){
		phyReg->phy_cr2 |= (phy_RIFS_unit_200_us << 12);
	}else{
		phyReg->phy_cr2 &= ~0xF000;
	}
#else
	/*20201023 Rearrangement CR Table*/ 
	if(timeRIFS){
		phyReg->phy_cr2 |= (phy_RIFS_unit_200_us & 0xF);
	}else{
		phyReg->phy_cr2 &= ~(0xF);
	}
#endif
	//ULOG(ULL_INF, "#cfgPhyRIFS:%d,%08X",timeRIFS,phyReg->phy_cr2);
	printf("#cfgPhyRIFS:%d,%08X\r\n",timeRIFS,phyReg->phy_cr2);
	return 0;
}
vc_uint8 vc_phy_lmac_cfg_payload_crc_filter(vc_uint8 onOff)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR; 
	/*Default setting filter same crc*/
#if 0
	if(onOff){
		phyReg->phy_cr1 &= ~0x400000;
	}else{
		phyReg->phy_cr1 |= 0x400000;
	}
#else
	/*20201023 Rearrangement CR Table*/ 
	if(onOff){
		phyReg->phy_cr1 &= ~(0x1 << 13);
	}else{
		phyReg->phy_cr1 |= (0x1 << 13);
	}
#endif
	//ULOG(ULL_INF, "#cfgPhyCrcFilter:%d,0x%08X",onOff,phyReg->phy_cr1); 
	printf("#cfgPhyCrcFilter:%d,0x%08X\r\n",onOff,phyReg->phy_cr1); 
	return 0;

}
vc_uint8 vc_phy_lmac_cfg_fnpll_correction(vc_uint8 onOff)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR;	
	
	if(onOff){
		phyReg->phy_cr2 |= (0x1 << 30);
	}else{
		phyReg->phy_cr2 &= ~(0x1 << 30);
	}
	//ULOG(ULL_INF, "#cfgPhyFnpllCorrection CR1 :0x%08X, #cfgPhyFnpllCorrection CR2 :%d,0x%08X #cfgPhyFnpllCorrection CR3 :0x%08X", phyReg->phy_cr1, onOff, phyReg->phy_cr2, phyReg->phy_cr3);
	return 0;

}
vc_uint8 vc_phy_lmac_cfg_dsp_ARQ(vc_uint8 onOff)
{
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR; 
#if 0	
	if(onOff){
		phyReg->phy_cr1 |= 0x800000;
	}else{
		phyReg->phy_cr1 &= ~0x800000;
	}
#else
	/*20201023 Rearrangement CR Table*/	
	if(onOff){
		phyReg->phy_cr1 |= (0x1 << 14);
	}else{
		phyReg->phy_cr1 &= ~(0x1 << 14);
	}
#endif
	//ULOG(ULL_INF, "#cfgPhyDspARQ:0x%08X",phyReg->phy_cr1);
	printf("#cfgPhyDspARQ:0x%08X\r\n",phyReg->phy_cr1);
	return 0;

}
vc_uint8 vc_phy_lmac_cfg_dsp_ARQ_STEI(vc_uint16 mySTEI)
{	
	volatile PHY_REG* phyReg = (volatile PHY_REG*)PHY_REG_BASEADDR; 
	/*20201023 Rearrangement CR Table*/	
	if(mySTEI < 0xFFF){
		phyReg->phy_cr2 |= ((mySTEI & 0xFFF) << 4);
	}
	//ULOG(ULL_INF, "#cfgDspARQMyTEI:0x%08X",phyReg->phy_cr2);
	return 0;
}

void vc_lmac_cfg_phy_NID(vc_uint32 pNID)
{
	#if CFG_NID_PTEI_BY_RAW_CMD
	tBbpRawCmd bbpRawCmd;
	vc_memset(&bbpRawCmd, 0x00, sizeof(tBbpRawCmd));
	bbpRawCmd.bbpCmd[0] = VC_LMAC_RCMD_CFG_NID;
	bbpRawCmd.bbpCmd[1] = pNID;
	bbpRawCmd.bbpCmdLen = 8;
	vc_lmac_tx_bbp_pkt_f_cmd(&bbpRawCmd);
	#else
	vc_phy_lmac_cfg_phy_disconnect(0);
	vc_phy_lmac_cfg_phy_NID(pNID);
	#endif
}
