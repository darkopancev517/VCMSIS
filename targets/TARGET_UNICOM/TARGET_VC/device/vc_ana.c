/*
 * Copyright (c) 2022 Unicom Semiconductor, Inc. All rights reserved.
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

#include "vc_ana.h"

#ifdef DEVICE_MCU_VC7351

static void _vcana_init_vc7351(void)
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

static uint8_t _ana_get_clockdiv(uint32_t *hz)
{
    uint8_t clkdiv = 0;
    uint32_t old_hz = *hz;
    uint32_t new_hz = 0;

    if (old_hz < 500000) {
        new_hz = 250000;        /* 250KHz */
        clkdiv = 240 - 1;
    } else if (old_hz < 1000000) {
        new_hz = 500000;        /* 500KHz */
        clkdiv = 120 - 1;
    } else if (old_hz < 1500000) {
        new_hz = 1000000;       /* 1MHz */
        clkdiv = 60 - 1;
    } else if (old_hz < 2000000) {
        new_hz = 1500000;       /* 1.5MHz */
        clkdiv = 40 - 1;
    } else if (old_hz < 4000000) {
        new_hz = 2000000;       /* 2MHz */
        clkdiv = 30 - 1;
    } else if (old_hz < 6000000) {
        new_hz = 4000000;       /* 4MHz */
        clkdiv = 15 - 1;
    } else if (old_hz < 12000000) {
        new_hz = 6000000;       /* 6MHz */
        clkdiv = 10 - 1;
    } else if (old_hz < 15000000) {
        new_hz = 12000000;      /* 12MHz */
        clkdiv = 5 - 1;
    } else {
        new_hz = 15000000;      /* 15MHz */
        clkdiv = 4 - 1;
    }

    *hz = new_hz;

    return clkdiv;
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
    VC_ANA->RG_BBPLL_CTRL = temp;

    temp = VC_ANA->RG_SOC_BBPLL_METER_CTRL;
    temp &= ~VC_ANA_RG_SOC_BBPLL_METER_MANU_IBAND_Msk;
    temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FM_EN_Msk;
    temp &= ~VC_ANA_RG_SOC_BBPLL_METER_FNPLL_IBAND_RST_Msk;
    temp |= (8UL << VC_ANA_RG_SOC_BBPLL_METER_MANU_IBAND_Pos);
    temp |= (1UL << VC_ANA_RG_SOC_BBPLL_METER_FM_EN_Pos);
    temp |= (0UL << VC_ANA_RG_SOC_BBPLL_METER_FNPLL_IBAND_RST_Pos);
    VC_ANA->RG_SOC_BBPLL_METER_CTRL = temp;

    while ((VC_ANA->RG_SOC_BBPLL_METER_CTRL & VC_ANA_RG_SOC_BBPLL_METER_FM_DONE_Msk) == 0);

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

void vcana_set_adc_delay(uint8_t adc_clocks)
{
    uint32_t temp = VC_ANA->ADCCTRL;
    temp &= ~VC_ANA_ADCCTRL_ADC_DELAY_Msk;
    temp |= (adc_clocks << VC_ANA_ADCCTRL_ADC_DELAY_Pos);
    VC_ANA->ADCCTRL = temp;
}

#endif /* #ifdef DEVICE_MCU_VC7351 */

#ifdef DEVICE_MCU_VC6330

static void _vcana_init_vc6330(void)
{

}

#endif /* #ifdef DEVICE_MCU_VC6330 */

void vcana_init(void)
{
#ifdef DEVICE_MCU_VC7351
  _vcana_init_vc7351();
#endif

#ifdef DEVICE_MCU_VC6330
  _vcana_init_vc6330();
#endif
}

void vcana_init_adc(int channel, uint32_t *frequency)
{
    uint32_t temp = 0;

#ifdef DEVICE_MCU_VC7351

    if ((channel < 0 || channel > 7) || frequency == NULL) {
        return; 
    }

    uint32_t corrected_freq = *frequency;
    uint8_t clkdiv = _ana_get_clockdiv(&corrected_freq);
    *frequency = corrected_freq;

    /* Setup ADC clock and enable ADC engine */
    temp = VC_ANA->ADCCTRL;
    temp &= ~VC_ANA_ADCCTRL_ADC_CLKDIV_Msk;
    temp &= ~VC_ANA_ADCCTRL_ADC_CLKSEL_Msk;
    temp |= (clkdiv << VC_ANA_ADCCTRL_ADC_CLKDIV_Pos);
    temp |= (0UL << VC_ANA_ADCCTRL_ADC_CLKSEL_Pos);
    temp |= (1UL << VC_ANA_ADCCTRL_ADC_EN_Pos);
    temp |= (1UL << VC_ANA_ADCCTRL_ADC_FEN_Pos);
    VC_ANA->ADCCTRL = temp;

    /* Enable ADC channel */
    temp = VC_ANA->ADCMCHEN;
    temp |= (1UL << channel);
    VC_ANA->ADCMCHEN = temp;

#endif

#ifdef DEVICE_MCU_VC6330

    if (channel < 0 || channel > 15) {
        return;
    }

    //TODO: set adc frequency if needed

    temp = VC_ANA->ADCCTRL;
    temp &= ~VC_ANA_ADCCTRL_ADC_SMP_TIME_Msk;
    temp &= ~VC_ANA_ADCCTRL_ADC_RDY_TIME_Msk;
    temp &= ~VC_ANA_ADCCTRL_ADC_ALIGN_Msk;
    temp &= ~VC_ANA_ADCCTRL_ADC_TRG_SEL_Msk;
    temp |= (1UL << VC_ANA_ADCCTRL_ADC_EN_Pos);
    temp |= (0UL << VC_ANA_ADCCTRL_ADC_TRG_SEL_Pos); /* Software start */
    VC_ANA->ADCCTRL = temp;

    /* Enable ADC channel */
    temp = VC_ANA->ADCCHEN;
    temp |= (1UL << channel);
    VC_ANA->ADCCHEN = temp;

#endif
}

void vcana_conti_mode_enable(void)
{
    uint32_t temp = VC_ANA->ADCCTRL;
    temp |= (1UL << VC_ANA_ADCCTRL_ADC_CONTI_Pos);
    VC_ANA->ADCCTRL = temp;
}

void vcana_conti_mode_disable(void)
{
    uint32_t temp = VC_ANA->ADCCTRL;
    temp &= ~VC_ANA_ADCCTRL_ADC_CONTI_Msk;
    VC_ANA->ADCCTRL = temp;
}

static void _ana_mcov_start(void)
{
#ifdef DEVICE_MCU_VC7351
    while ((VC_ANA->ADCCTRL & VC_ANA_ADCCTRL_ADC_MSTART_Msk) != 0);
    uint32_t temp = VC_ANA->ADCCTRL;
    temp |= (1UL << VC_ANA_ADCCTRL_ADC_MSTART_Pos);
    VC_ANA->ADCCTRL = temp;
#endif

#ifdef DEVICE_MCU_VC6330
    while ((VC_ANA->ADCCTRL & VC_ANA_ADCCTRL_ADC_START_Msk) != 0);
    uint32_t temp = VC_ANA->ADCCTRL;
    temp |= (1UL << VC_ANA_ADCCTRL_ADC_START_Pos);
    VC_ANA->ADCCTRL = temp;
#endif
}

static void _ana_mcov_stop(void)
{
    while ((VC_ANA->ADCCTRL & VC_ANA_ADCCTRL_ADC_STOP_Msk) != 0);
    uint32_t temp = VC_ANA->ADCCTRL;
    temp |= (1UL << VC_ANA_ADCCTRL_ADC_STOP_Pos);
    VC_ANA->ADCCTRL = temp;
}

uint16_t vcana_mread(int channel)
{
#ifdef DEVICE_MCU_VC7351
    if (channel < 0 || channel > 7)
        return 0;
#endif

#ifdef DEVICE_MCU_VC6330
    if (channel < 0 || channel > 15)
        return 0;
#endif

    uint16_t result = 0;

    _ana_mcov_start();

#ifdef DEVICE_MCU_VC7351
    if (channel < 4) {
        result = (VC_ANA->ADCDATA0_3[channel] & 0xFFFFUL);
    } else {
        result = (VC_ANA->ADCDATA4_15[channel] & 0xFFFFUL);
    }
#endif

#ifdef DEVICE_MCU_VC6330
    result = VC_ANA->ADCDATAx[channel];
#endif

    _ana_mcov_stop();

    return result;
}


