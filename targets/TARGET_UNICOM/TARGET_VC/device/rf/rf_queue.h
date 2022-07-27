/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __CENT_QUEUE_H
#define __CENT_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------

//  typedef enum __CALI_STATUS_E {
//      CALI32K_KICK = 0x01,
//      CALI4M_KICK = 0x02,
//      CALI32K_DONE = 0x03,
//      CALI4M_DONE = 0x04,
//      CALI_TIMEOUT = 0x05,
//      CALI_BEFORE_IQ = 0x06,
//      CALI_BEFORE_DTUNE = 0x07,
//      CALI_PERIOD_VCOIQ_DONE = 0x08,
//  }CALI_STATUS_E;

//  typedef struct __SYS_STATUS_T {
//      uint32_t system : 8;
//      uint32_t cali32k : 8;
//      uint32_t cali4m : 8;
//      uint32_t period_expire : 8;
//  }SYS_STATUS_T;

typedef struct __COMM_INFO_T
{
    /* Base address (M0) = 0x20002740 */
    uint32_t carrir_sense;      //offset : 0x0000
    uint32_t packet_receiving;	//offset : 0x0004
	uint32_t reserved_08;       //offset : 0x0008   //SYS_STATUS_T    status;     //offset : 0x0008
	uint32_t state;             //offset : 0x000C   
	uint32_t pkt_sr;            //offset : 0x0010 
	uint32_t packet_len;        //offset : 0x0014
	uint32_t pkt_rssi;          //offset : 0x0018
	uint32_t cca_rssi;          //offset : 0x001C
	uint32_t lqi;               //offset : 0x0020
    uint32_t cca; 	            //offset : 0x0024
	uint32_t saradc;            //offset : 0x0028
    uint32_t cmd_status;        //offset : 0x002C
    uint32_t rx_packet_period;  //offset : 0x0030
    uint32_t hcmd_duration;     //offset : 0x0034
    uint32_t sys_event;         //offset : 0x0038
    uint32_t phy_event;         //offset : 0x003C
    uint32_t snr;               //offset : 0x0040
    uint32_t phr_len;           //offset : 0x0044
    // CONFIG_M0_DSP_COMMAND
    uint32_t ofdm_version;      //offset : 0x0048
    uint32_t ofdm_pkt_snr;      //offset : 0x004c, S13
    uint32_t ofdm_opt_mcs;      //offset : 0x0050
    uint32_t txpwr;             //offset : 0x0054
    uint32_t m0_git_commit;     //offset : 0x0058
}COMM_INFO_T;   // __attribute__((packed))

typedef struct __STAT_INFO_T
{
    /* Base address(M0) = 0x20002600 */
    uint32_t pmb;                //offset : 0x0000
    uint32_t sfd;                //offset : 0x0004
    uint32_t phr;                //offset : 0x0008
    uint32_t antenna;	         //offset : 0x000c
    uint32_t rx_pkt;             //offset : 0x0010
    uint32_t sfd_timeout;        //offset : 0x0014
    uint32_t rssi_less;          //offset : 0x0018
	uint32_t rssi_over;          //offset : 0x001c
	uint32_t rx_drop_by_len;     //offset : 0x0020
    uint32_t tx_en;              //offset : 0x0024
    uint32_t txcmp;              //offset : 0x0028
	uint32_t rxcmp;              //offset : 0x002c
	uint32_t fcs_err;            //offset : 0x0030
    uint32_t rx_drop_by_addr;    //offset : 0x0034
    uint32_t rev2;               //offset : 0x0038
    uint32_t rev3;               //offset : 0x003c
}STAT_INFO_T;


//#define CENT_MSG_LEN                    0x40
//#define COMM_INFO_LEN                   0x60

//#define CENT_MSG_QUEUE_ADDR             0x20002700 
//#define CENT_COMM_INFO_ADDR             (CENT_MSG_QUEUE_ADDR + CENT_MSG_LEN)
#define CENT_COMM_INFO_ADDR             0x20002740
#define CENT_STAT_INFO_ADDR             0x20002600 

//---------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // __CENT_QUEUE_H

