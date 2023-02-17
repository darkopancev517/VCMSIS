#include "magpie2.h"
#include "pll.h"

int _hclk= 25000000;
/***********************************************************************
// About DLL calibration value for all kinds of IC and projects.
// Oct 17, 2018
Project     SGCC   G3      SGCC    G3     SGCC(test IC)  G3(test IC)  SGCC(20210909)
Fref (Xtal) 25     25      32      32     24.576         24.576       25    (MHz)
FNPLL Fout  900    864     900     864    900            864          900   (MHz)
Fout/Fref   36     34.56   28.125  27     36.6211        35.15625     35    (Rate)
N           36     34      28      27     36             35           35
offset      0      35      8       0      39             10           63
K           0      880804  0       0      786432         0            1048575
test_in     0x900  0x8888  0x710   0x6C0  0x900          0x8BF        0x900
Note: test_in is the value of RG_SOC_FNPLL_TESTIN
***********************************************************************/
/*
Fout=150MHz
Fref=Xtal=25MHz
N = 6
k = 0
Fref=Xtal=32MHz
N = 4
k = 720896
Fout = Fref * (N + k / K) / posdiv
N: DDSM_IN[25:20]
k: DDSM_IN[19:0]
K: 2^20
*/
void gpll_150mhz(void)
{
	uint32_t gppll_ctrl0;
	uint32_t n, k;
	int i;
	if(*PMU_STRAP & XTAL_25MHZ_MASK) {
		n = 12;
		//HS suggested GPLL output frequency should be higher as 600MHz and POSDIV=/4 to
		//get better clock jitter performance.
		//n = 24;
		k = 0;
	}else{
		n = 3;//4;
		k = 720896;
	}
	gppll_ctrl0 = *RG_GPPLL_CTRL0 & (~RG_GPPLL_POSDIV_MASK);
	*RG_GPPLL_CTRL0 = gppll_ctrl0 | RG_GPPLL_EN | RG_GPPLL_POSDIV_2;
	//HS suggested GPLL output frequency should be higher as 600MHz and POSDIV=/4 to
	//get better clock jitter performance.
	//*RG_GPPLL_CTRL0 = gppll_ctrl0 | RG_GPPLL_EN | RG_GPPLL_POSDIV_4;
	*RG_GPPLL_CTRL1 = RG_GPPLL_DDSM_EN  | (n << 20) | k;
	//*MISC2_CLKDIVH =1;
	for(i=0; i<1000; i++) n=i;
	*MISC2_CLKSEL = 0x02;  // change to GPLL
	_hclk =150000000;
}
/*
FNPLL
Fout = Fref * (N + offset/2^6 + k/K*2^6)
N: DDSM_IN[25:20]
k: DDSM_IN[19:0]
K: 2^20
offset: DDSM_IN_OFFSET[6:0]
*/
void fnpll(uint32_t n, uint32_t k, uint32_t offset, uint32_t test_in)
{
	uint32_t timeout=5000;
	int i;
	*RG_SOC_FNPLL_CTRL  = DDSM_TEST;
	*RG_SOC_FNPLL_TESTIN = test_in;
	*RG_SOC_FNPLL_METER_CTRL= FN_FNPLL_IBAND_RST | FN_PLL_WAIT_TIME | FN_FM_BINARYMODE;
	*RG_FNPLL_CTRL =
		RG_FNPLL_IC | RG_FNPLL_IR | RG_FNPLL_ADCCLK_EN | RG_FNPLL_DACCLK_EN | RG_FNPLL_WBSARCLK_EN;
		//(ww 4004b00c 112C04)  (IR/PC can't be 0)
	*RG_FNPLL_CTRL |= RG_FNPLL_EN;	//(ww 4004b00c 11AC04 ) (RG_FNPLL_EN=1)
	for(i=0; i<10000; i++) ; // delay wait for FNPLL stable
	*RG_SOC_FNPLL_METER_CTRL =  FN_PLL_WAIT_TIME | FN_FM_BINARYMODE | FN_FM_EN ;
	while (((*RG_SOC_FNPLL_METER_CTRL & FN_FM_DONE) == 0x0) && (--timeout)){
			for(i=0; i<100000; i++) ;
	}; // wait for FNPLL calibration done
	#if 0
	if(timeout==0) {
		vc_printf(LF"RG_SOC_FNPLL_METER_CTRL timeout=%X"LF, *RG_SOC_FNPLL_METER_CTRL);
	}
	#endif
	*RG_SOC_FNPLL_DDSMIN =  (n << 20) + k;
	*RG_SOC_FNPLL_OFFSETIN = offset;
	*RG_SOC_FNPLL_CTRL = DDSM_EN;
}
static uint8_t cal_as_test_ic()
{
	if(((*RG_XTAL_CTRL & 0xFF)==0x10)||
		((*RG_FNPLL_CTRL  & 0xFF00)==0)){
		return 0;/*20200227:Not need to check test ic, mp version, just used B1 Version */
	}
	else{
		return 0;
	}

}
/******************************************
G3-PLC mode, ADC=288MHz, PLL Fout need 864MHz
Fref=Xtal=25MHz
864/25 = 34.56
N = 34
offset/2^6 + k/(K*2^6) = 0.56
offset = 35, k/K = 0.84, k = 0.84*2^20 = 880803.84
Fref=Xtal=32MHz
864/32 = 27
N = 27, offset = 0, k =0
Fout = Fref * (N + offset/2^6 + k/K*2^6)
N: DDSM_IN[25:20]
k: DDSM_IN[19:0]
K: 2^20
offset: DDSM_IN_OFFSET[6:0]
******************************************/
void fnpll_g3plc(void)
{
	uint32_t n, k, offset, test_in;

	if (*PMU_STRAP & XTAL_25MHZ_MASK) {
		if(cal_as_test_ic())
		{
			n = 35;
			k = 0;
			offset = 10;
			test_in=	0x8BF;
		}else {
			n = 34;
			k = 880803;
			offset = 35;
			test_in= 0x8888;
		}
	}else{
		n = 27;
		k = 0;
		offset = 0;
		test_in= 0x6C0;
	}
	fnpll(n, k, offset, test_in);
}
/******************************************
SGCC BPLC mode, ADC=300MHz, PLL Fout need 900MHz
Fref=Xtal=25MHz ³
N=36, k=0, offset=0
Fref=Xtal=32MHz
900/32=28.125
N=28, offset=8, k=0
N: DDSM_IN[25:20]
k: DDSM_IN[19:0]
K: 2^20
offset: DDSM_IN_OFFSET[6:0]
*******************************************/
void fnpll_bplc(void)
{
	uint32_t n, k, offset, test_in;
	if(*PMU_STRAP & XTAL_25MHZ_MASK) {
		if(cal_as_test_ic()){
			n = 36;
			k = 786432;
			offset = 39;
			test_in = 0x900;
		} else {
			n = 35;
			k = 1048575;
			offset = 63;
			test_in= 0x900;
		}
	} else {
		n = 28;
		k = 0;
		offset = 8;
		test_in= 0x710;
	}
	fnpll(n, k, offset, test_in);

}
