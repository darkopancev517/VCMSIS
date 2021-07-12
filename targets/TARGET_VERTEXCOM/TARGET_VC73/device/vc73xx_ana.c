/*
 * Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "vc73xx_ana.h"

void vcana_init(void)
{
  uint32_t temp = VC_ANA->RG_LFXO_CTRL;
  temp &= ~VC_ANA_RG_LFXO_CURSEL_Msk;
  temp &= ~VC_ANA_RG_LFXO_IBBG_EN_Msk;
  temp |= (0x3UL << VC_ANA_RG_LFXO_CURSEL_Pos);       /* CURSEL: 500nA */
  temp |= (0UL << VC_ANA_RG_LFXO_IBBG_EN_Pos);        /* CURSOURCE: ANABG */
  VC_ANA->RG_LFXO_CTRL = temp;

  temp = VC_ANA->RG_LFRCO_CTRL;
  temp &= ~VC_ANA_RG_LFRCO_RSEL_Msk;
  temp &= ~VC_ANA_RG_LFRCO_CSEL_Msk;
  temp |= (0xEUL << VC_ANA_RG_LFRCO_RSEL_Pos);        /* LFRCO resistor selection */
  temp |= (0x65UL << VC_ANA_RG_LFRCO_CSEL_Pos);       /* LFRCO capacitor selection */
  VC_ANA->RG_LFRCO_CTRL = temp;

  temp = VC_ANA->RG_HFXO_CTRL;
  temp &= ~VC_ANA_RG_HFXO_EN_Msk;
  temp |= (1UL << VC_ANA_RG_HFXO_EN_Pos);
  VC_ANA->RG_HFXO_CTRL = temp;

  temp = VC_ANA->RG_HFRCO_CTRL0;
  temp &= ~VC_ANA_RG_HFRCO_CTRL0_AC_PERIOD_Msk;
  temp |= (1UL << VC_ANA_RG_HFRCO_CTRL0_AC_PERIOD_Pos);
  VC_ANA->RG_HFRCO_CTRL0 = temp;

  temp = VC_ANA->RG_HFRCO_CTRL1;
  temp &= ~VC_ANA_RG_HFRCO_CTRL1_AC_TGT_Msk;
  temp |= (0x5B9UL << VC_ANA_RG_HFRCO_CTRL1_AC_TGT_Pos);
  VC_ANA->RG_HFRCO_CTRL1 = temp;

  VC_ANA->RG_LDO_CTRL = 0; /* setl RF LDO CTRL register to 0 */
}

void vcana_set_gppll_120mhz(void)
{
  uint32_t temp = VC_ANA->RG_GPPLL_CTRL1;
  temp &= ~VC_ANA_RG_GPPLL_PREDIV_Msk;
  temp &= ~VC_ANA_RG_GPPLL_DDSM_IN_Msk;
  temp &= ~VC_ANA_RG_GPPLL_DDSM_EN_Msk;
  temp |= (1UL << VC_ANA_RG_GPPLL_PREDIV_Pos);
  temp |= (20UL << VC_ANA_RG_GPPLL_DDSM_IN_Integer_Pos);
  temp |= (0UL << VC_ANA_RG_GPPLL_DDSM_IN_Fraction_Pos);
  temp |= (0UL << VC_ANA_RG_GPPLL_DDSM_EN_Pos);
  VC_ANA->RG_GPPLL_CTRL1 = temp;

  temp = VC_ANA->RG_GPPLL_CTRL0;
  temp &= ~VC_ANA_RG_GPPLL_POSDIV_Msk;
  temp &= ~VC_ANA_RG_GPPLL_EN_Msk;
  temp |= (2UL << VC_ANA_RG_GPPLL_POSDIV_Pos);
  temp |= (1UL << VC_ANA_RG_GPPLL_EN_Pos);
  VC_ANA->RG_GPPLL_CTRL0 = temp;

  for (int i = 0; i < 0x1000; i++);

  temp = VC_MISC2->CLKSEL;
  temp &= ~VC_MISC2_CLKSEL_CLKSEL_Msk;
  temp |= (2UL << VC_MISC2_CLKSEL_CLKSEL_Pos); /* AHB clock source: GPLL */
  VC_MISC2->CLKSEL = temp;
}

void vcana_set_bbpll_192mhz(void)
{
  uint32_t timeout = 5000;

  /* Enable DDSM_TEST */
  uint32_t temp = VC_ANA->RG_SOC_BBPLL_CTRL;
  temp &= ~VC_ANA_RG_SOC_BBPLL_DDSM_TEST_Msk;
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_DDSM_TEST_Pos);
  VC_ANA->RG_SOC_BBPLL_CTRL = temp;

  /* Set DDSM_TESTIN */
  temp = VC_ANA->RG_SOC_BBPLL_TESTIN;
  temp &= ~VC_ANA_RG_SOC_BBPLL_TESTIN_Msk;
  temp |= (16UL << VC_ANA_RG_SOC_BBPLL_TESTIN_Integer_Pos);
  temp |= (0UL << VC_ANA_RG_SOC_BBPLL_TESTIN_Fraction_Pos);
  VC_ANA->RG_SOC_BBPLL_TESTIN = temp;

  /* Filled BBPLL parameter needed */
  temp = VC_ANA->RG_SOC_BBPLL_METER_CTRL;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FM_BINMODE_Msk;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_PLL_WAIT_TIME_Msk;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FNPLL_IBAND_RST_Msk;
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_METER_FM_BINMODE_Pos);
  temp |= (63UL << VC_ANA_RG_SOC_BBPLL_METER_PLL_WAIT_TIME_Pos);
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_METER_FNPLL_IBAND_RST_Pos);
  VC_ANA->RG_SOC_BBPLL_METER_CTRL = temp;

  temp = VC_ANA->RG_BBPLL_CTRL;
  temp &= ~VC_ANA_RG_BBPLL_PDADCCLK_EN_Msk;
  temp &= ~VC_ANA_RG_BBPLL_IR_Msk;
  temp &= ~VC_ANA_RG_BBPLL_IC_Msk;
  temp &= ~VC_ANA_RG_BBPLL_TXDACCLK_EN_Msk;
  temp &= ~VC_ANA_RG_BBPLL_IQADCCLK_EN_Msk;
  temp |= (1UL << VC_ANA_RG_BBPLL_PDADCCLK_EN_Pos);
  temp |= (3UL << VC_ANA_RG_BBPLL_IR_Pos);
  temp |= (1UL << VC_ANA_RG_BBPLL_IC_Pos);
  temp |= (1UL << VC_ANA_RG_BBPLL_TXDACCLK_EN_Pos);
  temp |= (1UL << VC_ANA_RG_BBPLL_IQADCCLK_EN_Pos);
  VC_ANA->RG_BBPLL_CTRL = temp;

  /* Enable BBPPLL */
  temp = VC_ANA->RG_BBPLL_CTRL;
  temp &= ~VC_ANA_RG_BBPLL_EN_Msk;
  temp |= (1UL << VC_ANA_RG_BBPLL_EN_Pos);
  VC_ANA->RG_BBPLL_CTRL;

  temp = VC_ANA->RG_SOC_BBPLL_METER_CTRL;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_MANU_IBAND_Msk;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FM_EN_Msk;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FNPLL_IBAND_RST_Msk;
  temp |= (8UL << VC_ANA_RG_SOC_BBPLL_METER_MANU_IBAND_Pos);
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_METER_FM_EN_Pos);
  temp |= (0UL << VC_ANA_RG_SOC_BBPLL_METER_FNPLL_IBAND_RST_Pos);
  VC_ANA->RG_SOC_BBPLL_METER_CTRL = temp;

  while (((VC_ANA->RG_SOC_BBPLL_METER_CTRL & VC_ANA_RG_SOC_BBPLL_METER_FM_DONE_Msk) == 0) && (--timeout))
  {
    for(int i = 0; i < 100000; i++);
  }

  /* Set DDSMIN */
  temp = VC_ANA->RG_SOC_BBPLL_DDSMIN;
  temp &= ~VC_ANA_RG_SOC_BBPLL_DDSMIN_Msk;
  temp |= (16UL << VC_ANA_RG_SOC_BBPLL_DDSMIN_Integer_Pos);
  temp |= (0UL << VC_ANA_RG_SOC_BBPLL_DDSMIN_Fraction_Pos);
  VC_ANA->RG_SOC_BBPLL_DDSMIN = temp;

  temp = VC_ANA->RG_BBPLL_CTRL;
  temp &= ~VC_ANA_RG_BBPLL_SOCCLK_DIV3_Msk;
  temp |= (0UL << VC_ANA_RG_BBPLL_SOCCLK_DIV3_Pos);
  VC_ANA->RG_BBPLL_CTRL = temp;

  /* Set OFFSET */
  temp = VC_ANA->RG_SOC_BBPLL_OFFSETIN;
  temp &= ~VC_ANA_RG_SOC_BBPLL_OFFSETIN_Msk;
  temp |= (0UL << VC_ANA_RG_SOC_BBPLL_OFFSETIN_Pos);
  VC_ANA->RG_SOC_BBPLL_OFFSETIN = temp;

  /* Enable DDSM */
  temp = VC_ANA->RG_SOC_BBPLL_CTRL;
  temp &= ~VC_ANA_RG_SOC_BBPLL_DDSM_TEST_Msk;
  temp &= ~VC_ANA_RG_SOC_BBPLL_DDSM_EN_Msk;
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_DDSM_TEST_Pos);
  temp |= (0UL << VC_ANA_RG_SOC_BBPLL_DDSM_EN_Pos);
  VC_ANA->RG_SOC_BBPLL_CTRL = temp;

  temp = VC_ANA->RG_SOC_BBPLL_METER_CTRL;
  temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FM_MANUALSEL_Msk;
  temp |= (1UL << VC_ANA_RG_SOC_BBPLL_METER_FM_MANUALSEL_Pos);
  VC_ANA->RG_SOC_BBPLL_METER_CTRL = temp;
}
