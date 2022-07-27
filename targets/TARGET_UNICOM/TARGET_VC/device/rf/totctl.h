/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
 * woody.yang@vertexcom.com
*/

#ifndef __TOTCTL_H
#define __TOTCTL_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct totdbg_t
{
    uint32_t wpmac_ier;                //0x20003dc0 +  0*4 = 0x00
    uint32_t wpmac_isr_ored;           //0x20003dc0 +  1*4 = 0x04
    uint32_t rmac_phy_mode;            //0x20003dc0 +  2*4 = 0x08
    uint32_t rmac_wpmac_txp_pktlen;    //0x20003dc0 +  3*4 = 0x0c
    uint32_t rmac__wpmac_txp_fcs_ctrl; //0x20003dc0 +  4*4 = 0x10
    uint32_t tx_dmadesc_before;        //0x20003dc0 +  5*4 = 0x14
    uint32_t tx_dmadesc_after;         //0x20003dc0 +  6*4 = 0x18
    uint32_t rx_dmadesc_before;        //0x20003dc0 +  7*4 = 0x1c
    uint32_t rx_dmadesc_after;         //0x20003dc0 +  8*4 = 0x20
    uint32_t rmac_isr_cnt_before;      //0x20003dc0 +  9*4 = 0x24
    uint32_t rmac_isr_cnt;             //0x20003dc0 + 10*4 = 0x28
    uint32_t dma_isr_cnt_before;       //0x20003dc0 + 11*4 = 0x2c
    uint32_t dma_isr_cnt;              //0x20003dc0 + 12*4 = 0x30
    uint32_t dma_rxe_kick_before;      //0x20003dc0 + 13*4 = 0x34
    uint32_t dsp_cmd;                  //0x20003dc0 + 14*4 = 0x38
    uint32_t dsp_cmd_ext;              //0x20003dc0 + 15*4 = 0x3c
    uint32_t ir1_ored;                 //0x20003dc0 + 16*4 = 0x40
    uint32_t dsp_idle_tmr;             //0x20003dc0 + 17*4 = 0x44
    uint32_t tmr;                      //0x20003dc0 + 18*4 = 0x48
    uint32_t dma_isr;                  //0x20003dc0 + 19*4 = 0x4c
    uint32_t dma_isr_ored;             //0x20003dc0 + 20*4 = 0x50
    uint32_t wpmac_isr;                //0x20003dc0 + 21*4 = 0x54
    uint32_t rsvrd_58;                 //0x20003dc0 + 22*4 = 0x58
    uint32_t rsvrd_5c;                 //0x20003dc0 + 23*4 = 0x5c
    uint32_t rsvrd_60;                 //0x20003dc0 + 24*4 = 0x60
    uint32_t rsvrd_64;                 //0x20003dc0 + 25*4 = 0x64
    uint32_t rsvrd_68;                 //0x20003dc0 + 26*4 = 0x68
    uint32_t rsvrd_6c;                 //0x20003dc0 + 27*4 = 0x6c
    uint32_t msp;                      //0x20003dc0 + 28*4 = 0x70  msp max
    uint32_t psp;                      //0x20003dc0 + 29*4 = 0x74  psp max
    uint32_t loc_isr;                  //0x20003dc0 + 30*4 = 0x78  loc_id @ isr
    uint32_t pc;                       //0x20003dc0 + 31*4 = 0x7c  pc
    uint32_t maybe_bitmap;             //0x20003dc0 + 32*4 = 0x80
} __totdbg_t;

typedef struct totcmd_t
{
    uint32_t cmd_ret_val;              //0x20003e44 +  0*4 = 0x00
    uint32_t cmd_param_ext;            //0x20003e44 +  1*4 = 0x04
    uint32_t cmd;                      //0x20003e44 +  2*4 = 0x08
    uint32_t cmd_name0;                //0x20003e44 +  3*4 = 0x0c
    uint32_t cmd_name1;                //0x20003e44 +  4*4 = 0x10
    uint32_t cmd_name2;                //0x20003e44 +  5*4 = 0x14
    uint32_t cmd_name3;                //0x20003e44 +  6*4 = 0x18
    uint32_t cmd_name4;                //0x20003e44 +  7*4 = 0x1c
    uint32_t time_getphr;              //0x20003e44 +  8*4 = 0x20
    uint32_t time_rxpdone;             //0x20003e44 +  9*4 = 0x24
    uint32_t time_dma_rxcmp;           //0x20003e44 + 10*4 = 0x28
    uint32_t time_phy_notify;          //0x20003e44 + 11*4 = 0x2c
    uint32_t time_getphr_to_notify;    //0x20003e44 + 12*4 = 0x30
    uint32_t phymode;                  //0x20003e44 + 13*4 = 0x34 0: fsk, 1:ofdm
    uint32_t hcmd;                     //0x20003e44 + 0x38 HCMD_ITCR1: [31:16] val, [15:0] cmd, [15] ack(phase out),   change m3
    uint32_t seq;                      //0x20003e44 + 0x3c totctl_seq, change m3
    uint32_t m3m0_sync_pttn;           //0x20003e44 + 0x40 totctl_m3m0_sync_pttn, change m3
    uint32_t seq2;                     //0x20003e44 + 0x44 totctl_seq2, change m3
    uint32_t rc;                       //0x20003e44 + 0x48 totctl_rc, change m3
    uint32_t rc1;                      //0x20003e44 + 0x4c totctl_rc1, change m3
    uint32_t rc2;                      //0x20003e44 + 0x50 totctl_rc2, change m3
    uint32_t rc3;                      //0x20003e44 + 0x54 totctl_rc3, change m3
    uint32_t rc4;                      //0x20003e44 + 0x58 totctl_rc4, change m3
    uint32_t rc5;                      //0x20003e44 + 0x5c totctl_rc5, change m3
    uint32_t rc6;                      //0x20003e44 + 0x60 totctl_rc6, change m3
    uint32_t rc7;                      //0x20003e44 + 0x64 totctl_rc7, change m3
    uint32_t rc8;                      //0x20003e44 + 0x68 totctl_rc8, change m3
    uint32_t rc9;                      //0x20003e44 + 0x6c totctl_rc9, change m3
    uint32_t rc10;                     //0x20003e44 + 0x70 totctl_rc10, change m3
    uint32_t rc11;                     //0x20003e44 + 0x74 totctl_rc11, change m3
    uint32_t rc12;                     //0x20003e44 + 0x78 totctl_rc12, change m3
                                       //no more space
} __totcmd_t;

enum show_type_t {
    UNSIGNED_INT_SHOW_TYPE
   ,SIGNED_INT_SHOW_TYPE
   ,HEX_SHOW_TYPE
};

//extern uint32_t __totctl_start__;

#define TOTDBG ((struct totdbg_t *)0x20003dc0)  // caution: must match m0 address space
#define TOTCMD ((struct totcmd_t *)0x20003e44)  // caution: must match m0 address space

#ifdef CONFIG_DEBUG_M3M0CMD_W_PKT_RCVD
    void totctl_dump_pkt_rcvd(int sz, const uint8_t *buf);
#else // CONFIG_DEBUG_M3M0CMD_W_PKT_RCVD
    #define totctl_dump_pkt_rcvd(sz, buf)
#endif // CONFIG_DEBUG_M3M0CMD_W_PKT_RCVD

#define TOTCTL_DEBUG_RCERR_VERBOSE 1

void totctl_debug_set(uint32_t en);

uint32_t totctl_debug_get();

#ifdef CONFIG_DEBUG_M3M0CMD

void totctl_dump_m0_info();

bool totctl_get_cmdname(char *buf);

void totctl_dump_seq_sync_timeout(uint32_t seq, uint32_t seq2, uint16_t cmd, uint16_t param, uint32_t t0, uint32_t t1);

void totctl_dump_complete(uint32_t seq, uint16_t cmd, uint16_t param, uint32_t rc, uint32_t t0);

void totctl_dump_timeout(uint32_t seq, uint16_t cmd, uint16_t param, uint32_t rc, uint32_t t0);

#else // CONFIG_DEBUG_M3M0CMD

#define totctl_dump_m0_info()

#define totctl_get_cmdname(buf) (buf[0]=0)

#define totctl_dump_seq_sync_timeout(seq, seq2, cmd, param, t0, t1)

#define totctl_dump_complete(seq, cmd, param, rc, t0)

#define totctl_dump_timeout(seq, cmd, param, rc, t0)

#endif // CONFIG_DEBUG_M3M0CMD

#ifdef __cplusplus
}
#endif

#endif // __TOTCTL_H

