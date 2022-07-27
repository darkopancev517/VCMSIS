/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __CENT_PMU_CSR_H
#define __CENT_PMU_CSR_H

#ifdef __cplusplus
extern "C" {
#endif

#define CENT_RTN_REG_COUNT                  16          // review it ..
/* retention register mapping */
#define CENT_RTN_REG_BASE                   0x4002C0A0

#define CENTI_REG_HCMD_INTR              0x4002C048
#define HCMD_TRIGGER_MASK              0x00000001

#define __IO volatile
typedef struct __PMU_CSR_T 
{
    __IO uint32_t PMU_CCMD_CR;                    // 0x0
    __IO uint32_t PMU_CR;                         // 0x4
    __IO uint32_t PMU_CGCR;                       // 0x8
    __IO uint32_t PMU_REV0[1];                    // 0xc ~ 0xc
    __IO uint32_t PMU_FEPWD_CR;                   // 0x10
    __IO uint32_t PMU_REV1[1];                    // 0x14 ~ 0x14
    __IO uint32_t PMU_PROBE_CR;                   // 0x18
    __IO uint32_t PMU_4M_TIMER_SR;                // 0x1c
    __IO uint32_t PMU_REV2[1];                    // 0x20 ~ 0x20
    __IO uint32_t PMU_32K_TIMER_SR1;              // 0x24
    __IO uint32_t PMU_REV3[1];                    // 0x28 ~ 0x28
    __IO uint32_t PMU_32K_TIMER_IR;               // 0x2c
    __IO uint32_t PMU_HCMD_CR;                    // 0x30
    __IO uint32_t PMU_REV4[2];                    // 0x34 ~ 0x38
    __IO uint32_t PMU_CST_IR;                     // 0x3c
    __IO uint32_t PMU_IER;                        // 0x40
    __IO uint32_t PMU_ISR;                        // 0x44
    __IO uint32_t PMU_HOST_INTR_TR;               // 0x48
    __IO uint32_t PMU_REV5[13];                   // 0x4c ~ 0x7c
    __IO uint32_t SEM1;                           // 0x80
    __IO uint32_t SEM2;                           // 0x84
    __IO uint32_t SEM3;                           // 0x88
    __IO uint32_t SEM4;                           // 0x8c
    __IO uint32_t HCMD_ITCR1;                     // 0x90
    __IO uint32_t HCMD_ITCR2;                     // 0x94
    __IO uint32_t HCMD_ITCR3;                     // 0x98
    __IO uint32_t HCMD_ITCR4;                     // 0x9c
    __IO uint32_t RESR1;                          // 0xa0
    __IO uint32_t RESR2;                          // 0xa4
    __IO uint32_t RESR3;                          // 0xa8
    __IO uint32_t RESR4;                          // 0xac
    __IO uint32_t RESR5;                          // 0xb0
    __IO uint32_t RESR6;                          // 0xb4
    __IO uint32_t RESR7;                          // 0xb8
    __IO uint32_t RESR8;                          // 0xbc [0x20003F7C]// for m0 hwset idx
    __IO uint32_t RESR9;                          // 0xc0 [0x20003F80]// for m0 hwset val
    __IO uint32_t RESR10;                         // 0xc4 [0x20003F84]// CENT_MODESWITCH_HighBandSet
    __IO uint32_t RESR11;                         // 0xc8 [0x20003F88]// CENT_PMU_PHR_ADDR_RX
    __IO uint32_t RESR12;                         // 0xcc [0x20003F8C]// Get M3 DSP_CMD
    __IO uint32_t RESR13;                         // 0xd0 [0x20003F90]// Get M3 DSP_CMD_EXT
    __IO uint32_t RESR14;                         // 0xd4 [0x20003F94]// Set DSP Read Value to M3
    __IO uint32_t RESR15;                         // 0xd8
    __IO uint32_t RESR16;                         // 0xdc
    __IO uint32_t RESR17;                         // 0xe0
    __IO uint32_t RESR18;                         // 0xe4
    __IO uint32_t RESR19;                         // 0xe8
    __IO uint32_t RESR20;                         // 0xec
    __IO uint32_t RESR21;                         // 0xf0
    __IO uint32_t RESR22;                         // 0xf4
    __IO uint32_t RESR23;                         // 0xf8
    __IO uint32_t RESR24;                         // 0xfc
    __IO uint32_t RESR25;                         // 0x100
    __IO uint32_t RESR26;                         // 0x104
    __IO uint32_t RESR27;                         // 0x108
    __IO uint32_t RESR28;                         // 0x10c
    __IO uint32_t RESR29;                         // 0x110
    __IO uint32_t RESR30;                         // 0x114
    __IO uint32_t RESR31;                         // 0x118
    __IO uint32_t RESR32;                         // 0x11c  
    __IO uint32_t RESR33;                         // 0x120   
    __IO uint32_t RESR34;                         // 0x124 
    __IO uint32_t RESR35;                         // 0x128
    __IO uint32_t RESR36;                         // 0x12c [0x20003FEC] for switch fsk and ofdm mode
    __IO uint32_t RESR37;                         // 0x130 [0x20003FF0] for mode switch cca result
    __IO uint32_t RESR38;                         // 0x134 [0x20003FF4] for mode switch tx settling time result
    __IO uint32_t RESR39;                         // 0x138 [0x20003FF8] CENT_BASEMODE
    __IO uint32_t RESR40;                         // 0x13c [0x20003FFc] for mode switch tx settling time result
}PMU_CSR_T;

#define CENT_PMU_ADDR(reg)              (PMU_CSR_BASE + offsetof(PMU_CSR_T, reg))

#define RF_CHANNEL_FREQ                 CENT_PMU_ADDR(RESR3)
#define M0_HWSET_IDX                    CENT_PMU_ADDR(RESR8)
#define M0_HWSET_VAL                    CENT_PMU_ADDR(RESR9)
//#define PMU_CSR__ROM_RG2              CENT_PMU_ADDR(RESR10)
//#define PMU_CSR__ROM_RG1              CENT_PMU_ADDR(RESR11)
#define CENT_DSP_ADDR1                  CENT_PMU_ADDR(RESR12) //Get M3 DSP_CMD
#define CENT_DSP_ADDR2                  CENT_PMU_ADDR(RESR13) //Get M3 DSP_CMD_EXT
#define CENT_DSP_ADDR3                  CENT_PMU_ADDR(RESR14) //Set DSP Read Value to M3
//#define PMU_CSR__ROM_IQC2             CENT_PMU_ADDR(RESR13)
//#define PMU_CSR__RXADC_DACREFIQ       CENT_PMU_ADDR(RESR14)
//-- #define CENT_RTN_RX_PARAM3         CENT_PMU_ADDR(RESR15)
#define CENT_RTN_LP_LISTEN              CENT_PMU_ADDR(RESR16)
#define CENT_RTN_RX_PARAM2              CENT_PMU_ADDR(RESR17)
#define CENT_RTN_RX_PARAM1              CENT_PMU_ADDR(RESR18)
//-- #define CENT_RTN_CAL32K4M_RESULT   CENT_PMU_ADDR(RESR19)
//-- #define CENT_RTN_STATE             CENT_PMU_ADDR(RESR20)
#define CENT_RTN_HOSTIF_PHYINT          CENT_PMU_ADDR(RESR21)
#define CENT_RTN_REG_PROBE_PIN          CENT_PMU_ADDR(RESR22)
#define CENT_RTN_REG_FUN_SWITCH         CENT_PMU_ADDR(RESR23)
#define CENT_RTN_PERIOD_TIME            CENT_PMU_ADDR(RESR24)           // ms uint
#define CENT_RTN_PERIOD_TOLERANCE       CENT_PMU_ADDR(RESR25)           // ms uint
#define CENT_RTN_32K_CTRL_ADDR          CENT_PMU_ADDR(RESR26)
#define CENT_RTN_REG_SYS_CTRL           CENT_PMU_ADDR(RESR27)
#define CENT_RTN_CMD_ACK_PARAM          CENT_PMU_ADDR(RESR28)
#define CENT_RTN_SW_CTRL                CENT_PMU_ADDR(RESR29)
#define CENT_RTN_CALI_SETTING           CENT_PMU_ADDR(RESR30)
//-- #define CENT_RTN_HOSTIF_INT_MASK_1 CENT_PMU_ADDR(RESR31)
#define CENT_RTN_HOSTIF_INT_MASK_0      CENT_PMU_ADDR(RESR32)
#define CENT_RTN_BAND                   CENT_PMU_ADDR(RESR33)
#define CENT_MODESWITCH                 CENT_PMU_ADDR(RESR34)
#define CENT_RFCHANNEL                  CENT_PMU_ADDR(RESR35)
#define CENT_RFMODE                     CENT_PMU_ADDR(RESR36)
#define CENT_MODESWITCH_CCA             CENT_PMU_ADDR(RESR37)
#define CENT_MODESWITCH_TX_SettlingTime CENT_PMU_ADDR(RESR38)
#define CENT_BASEMODE                   CENT_PMU_ADDR(RESR39)
#define CENT_TXPWRMODE                  CENT_PMU_ADDR(RESR40)


// PMU csr
#ifndef CSR_ACCESS
#define CSR_ACCESS(x) (*((volatile unsigned long *)(x)))
#endif

/** Block pmu_csr

*/
#define PMU_CSR_BASE 0x20003EC0 //m0 address space

/** Reg PMU_CR
PMU Control Register
*/
#define PMU_CSR__PMU_CR CSR_ACCESS(PMU_CSR_BASE + 0x00000004)

/** Field csr_ldstr_en
Load/Store Enable, default 0 (nothing to load back at the first boot-up)
*/
#define PMU_CR__CSR_LDSTR_EN_POS 2
#define PMU_CR__CSR_LDSTR_EN_MASK 0x00000004
// end of PMU csr

#ifdef __cplusplus
}
#endif

#endif

