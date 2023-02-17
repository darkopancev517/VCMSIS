#ifndef _PLL_H_
#define _PLL_H_

#include <stdint.h>

// GPLLCTRL
#define RG_GPPLL_EN		0x1 << 15
#define RG_GPPLL_DDSM_EN        0x1 << 26

#define RG_GPPLL_POSDIV_MASK 	(0x3 << 5)
#define RG_GPPLL_POSDIV_1 		(0x0 << 5)
#define RG_GPPLL_POSDIV_2 		(0x1 << 5)
#define RG_GPPLL_POSDIV_4 		(0x3 << 5)


// RCO100KCTRL
#define FM_EN		0x1 << 0
#define FM_DONE		0x1 << 8
#define FM_FAIL		0x1 << 9
#define BIN_MODE 0x1 << 5
#define FM_110K 0x2 << 3

// FNPLLCTRL
#define FN_FM_DONE             0x1 << 19
#define FN_FNPLL_IBAND_RST     0x1 << 18
#define FN_PLL_WAIT_TIME       0x3F << 11
#define FN_MANU_IBAND          0x1 << 5
#define FN_FM_MANUALSEL        0x1 << 4
#define FN_FM_BINARYMODE       0x1 << 3
#define FN_WIN                 0x1 << 1
#define FN_FM_EN               0x1 << 0

#define DDSM_ACC5B_EN   1 << 5
#define DDSM_TEST       1 << 4
#define DDSM_LFSR_EN    1 << 1
#define DDSM_EN         1 << 0


#define RG_FNPLL_IC 	1<<13
#define RG_FNPLL_IR 	3<<10

#define RG_FNPLL_ADCCLK_EN		(0x1 << 20)
#define RG_FNPLL_DACCLK_EN		(0x1 << 16)
#define RG_FNPLL_EN				(0x1 << 15)
#define RG_FNPLL_WBSARCLK_EN	(0x1 << 2)

#define XTAL_25MHZ_MASK 0x10

extern void gpll_150mhz(void);
extern void fnpll_g3plc(void);
extern void fnpll_bplc(void);

extern void vtclv_pll(void);

#endif
