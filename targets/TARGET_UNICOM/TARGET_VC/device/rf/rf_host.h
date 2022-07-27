/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __CENT_HOST_H
#define __CENT_HOST_H

#ifdef __cplusplus
extern "C" {
#endif

#define HCMD_BLOCK

/* China standard DL/T 698.44  */
#define DLT_698p44_FLAG 0

/* centauri front-end state */
#define FRONT_END_STATE_ELNA_EN                 0x1
#define FRONT_END_STATE_EPA_EN                  0x2
#define FRONT_END_STATE_ANT_DIVERSITY_EN        0x4

#define FCS_32                          0
#define FCS_16                          1
#define FCS_NONE                        2
#if DLT_698p44_FLAG
#define FCS_MODE                        FCS_16      /* FCS_32, FCS_16, FCS_NONE */
#else
#define FCS_MODE                        FCS_32      /* FCS_32, FCS_16, FCS_NONE */
#endif
/*****************************************************************************/
//ofdm: must sync. with m0

enum cmd_cat_t {
    CMD_CAT_NON_DSP
   ,CMD_CAT_DSPCMD_READ
   ,CMD_CAT_DSPCMD_WRITE
   ,CMD_CAT_DSPCMD_WRITE_EXT
   ,CMD_CAT_DSP_TX_DSPCMD_WRITE
};

#define CMD_RES_NONE                     0
#define CMD_RES_FIXPNT_OVERFLOW          (1<<0)
#define CMD_RES_REENTRANT                (1<<1)
#define CMD_RES_UNEXPECTED_SUCCESS       (1<<2)
#define CMD_RES_GOT_VALUE_SHOW_TYPE_SHF  3
#define CMD_RES_GOT_VALUE_SHOW_TYPE_MASK 0x03
#define CMD_RES_GOT_VALUE                (1<<5)

#define CMD_RES_AGC_TIMEOUT              (1<<12)
//  #define CMD_RES_STATE_1                  (1<<13)
//  #define CMD_RES_STATE_2                  (1<<14)
//  #define CMD_RES_STATE_TRANS              (1<<15)

#define CMD_RES_UNKNOWN                  (1<<16)
#define CMD_RES_STS_TIMEOUT              (1<<17)

#define CMD_RES_BAD_PARAM                (1<<18)
#define CMD_RES_SEQ_MISMATCH             (1<<19) //seq!=seq2
#define CMD_RES_DSP_BUSY_TIMEOUT         (1<<20)
#define CMD_RES_M3_SEQ_TIMEOUT           (1<<21) //m3 uses this bit 
#define CMD_RES_PROCESS_M3_CMD           (1<<22)
#define CMD_RES_M3_TIMEOUT               (1<<23) //m3 uses this bit 

//  #define CMD_RES_CAT_BITNO                24
//  #define CMD_RES_CAT                      (1<<24)
//  #define CMD_RES_CAT_1                    (1<<25)
//  #define CMD_RES_CAT_2                    (1<<26)

#define CMD_RES_RF_MODULE_OFF            (1<<27)

#define CMD_RES_RCVD                     (1<<28)

#define CMD_RES_RX_DUP                   (1<<29)

#define CMD_RES_SUCCESS                  (1<<30)
#define CMD_RES_COMPLETE                 (1<<31)
//
//rc1
//
#define CMD_RES_STATE_BITNO              (32+12)
#define CMD_RES_STATE                    (1<<(32+12))
#define CMD_RES_STATE_1                  (1<<(32+13))
#define CMD_RES_STATE_2                  (1<<(32+14))
#define CMD_RES_STATE_TRANS              (1<<(32+15))
                                         
#define CMD_RES_CAT_BITNO                (32+24)
#define CMD_RES_CAT                      (1<<(32+24))
#define CMD_RES_CAT_1                    (1<<(32+25))
#define CMD_RES_CAT_2                    (1<<(32+26))
//

typedef enum
{
	/* below command will send to centauri */
	RF_HCMD_INIT, //0
	RF_HCMD_SYSTEM_STATUS,
	RF_HCMD_IDLE,
	RF_HCMD_SLEEP,
	RF_HCMD_SHUTDOWN,
	RF_HCMD_CALIB_32K,
	RF_HCMD_CALIB_4M,
	RF_HCMD_CALIB_VCO,
	RF_HCMD_CALIB_IQ,
	RF_HCMD_CALIB_RX_ADC,
	RF_HCMD_CALIB_PERIOD_CHG, //10
	RF_HCMD_CCA,
	RF_HCMD_TX,
	RF_HCMD_TX_REFILLED,
	RF_HCMD_RX,
	RF_HCMD_RX_READED,
	RF_HCMD_TXPWR,
	RF_HCMD_RSSI,
	RF_HCMD_RSSI_OFFSET,
	RF_HCMD_BAND,
	RF_HCMD_MODI, //20
	RF_HCMD_RATE,
	RF_HCMD_TXCW,
	RF_HCMD_TXCM,
	RF_HCMD_GFILTER,
	RF_HCMD_PSDU_ORDER,
	RF_HCMD_DW,
	RF_HCMD_PMB,
	RF_HCMD_RXLP,
	RF_HCMD_PASEL,
	RF_HCMD_FEC, //30
	RF_HCMD_ADC,
	RF_HCMD_SW_CTRL_TEST,
	RF_HCMD_GPIO_TEST,
	RF_HCMD_STATE_CHANGE,
	RF_HCMD_MAC_LOOPBACK,
	RF_HCMD_STAT_CLEAR,
	RF_HCMD_ANTENNA,
	RF_HCMD_ELNA,
	RF_HCMD_MRFSK,
	RF_HCMD_BASEMODE,
	RF_HCMD_NEWMODE,
	RF_HCMD_OFDM_TXPWR,
	RF_HCMD_OFDM_OPTMCS,
	RF_HCMD_MS_TXDELAY,
	RF_HCMD_RFMODE,
	RF_HCMD_DSP_READ,
	RF_HCMD_DSP_WRITE,
	RF_HCMD_MS_ALGORITHM,
} RF_HCMD_CMD_T;

typedef enum {
    RF_EVENT_PMU_HOST_IRQn = 1,
    RF_EVENT_MAC_IRQn      = 2,
    RF_EVENT_PHY_IRQn      = 3,
    RF_EVENT_M0_IRQn       = 4,

    RF_EVENT_STATE_CHANGE = 16,
    RF_EVENT_PMB_DET = 17,
    RF_EVENT_CMD_ACK = 18,
    RF_EVENT_STATUS = 19,
    RF_EVENT_CMD_ERR = 20,
    RF_EVENT_CAL_HANDLE = 21,
    RF_EVENT_SLEEP_WAKEUP = 22,
    RF_EVENT_POWER_WAKEUP = 23,
} CENT_EVENT_T;

typedef enum {
    PMU_HOST_IRQn_MASK = (0x01 << RF_EVENT_PMU_HOST_IRQn),
    MAC_IRQn_MASK = (0x01 << RF_EVENT_MAC_IRQn),
    PHY_IRQn_MASK = (0x01 << RF_EVENT_PHY_IRQn),

    STATE_CHANGE_MASK = (0x01 << RF_EVENT_STATE_CHANGE),
    PMB_DET_MASK = (0x01 << RF_EVENT_PMB_DET),
    CMD_ACK_MASK = (0x01 << RF_EVENT_CMD_ACK),
    CCMD_STATUS_MASK = (0x01 << RF_EVENT_STATUS),
    CMD_ERR_MASK = (0x01 << RF_EVENT_CMD_ERR),
    CAL_DONE_MASK = (0x01 << RF_EVENT_CAL_HANDLE),
    SLEEP_WAKEUP_MASK = (0x01 << RF_EVENT_SLEEP_WAKEUP),
    POWER_WAKEUP_MASK = (0x01 << RF_EVENT_POWER_WAKEUP),
}CENT_EVENT_NOTIFY_T;


typedef struct {
    uint32_t cmd : 15;
	uint32_t ack : 1;
    uint32_t param : 16;
} RF_CMD_T;

typedef struct {
    uint32_t cmd : 15;
	uint32_t ack : 1;
    uint32_t param : 16;
} RF_EVENT_T;

// ---------------------------------------------------------

typedef enum
{
	SYS_IDLE,
	SYS_STANDBY_TX,
	SYS_STANDBY_RX,
	SYS_TX,
	SYS_RX,
	SYS_STATE_ALL,
	SYS_CAL,
	SYS_SLEEP,
	SYS_PWR_DWN,
	SYS_STATE_EVENT_END,

}SYS_STATE_T;

#define DEFAULT_PERIOD_TIME     5000


typedef struct CENT_NV_PARA {
    uint32_t series_number;
	uint32_t date;
    uint32_t carrier_frequency;
    uint32_t xtal_offset;
    uint32_t pa_sel;
    uint32_t tx_power_default;
	uint32_t tx_power_cal_offset;
	uint32_t rssi_offset;
}cent_nv_para_t;

struct STAT_INFO_T
{
    uint32_t pmb;
    uint32_t sfd;    
    uint32_t phr;
    uint32_t antenna;	
    uint32_t rx_pkt;
	uint32_t sfd_timeout;
	uint32_t rssi_less;
	uint32_t rssi_over;
	uint32_t rx_drop_by_len;
	uint32_t tx_en;
	uint32_t txcmp;
	uint32_t rxcmp;
	uint32_t fcs_err;
    uint32_t rx_drop_by_addr;
    uint32_t rev2;
    uint32_t rev3;        
};

void cent_reset(void);
void cent_cal_load(void);
void cent_get_statistic(struct STAT_INFO_T *pStatInfo);
uint32_t get_cmd_status(void);
uint32_t get_state(void);
uint32_t get_pkt_len(void);
uint32_t get_pkt_sr(void);
uint32_t get_pkt_lqi(void);
uint32_t get_pkt_snr(void);
int32_t get_pkt_rssi(void);
int32_t get_rssi(void);
int32_t GetModeSwitchCCA(void);
int32_t GetTxSettlingTime(void);
uint32_t GetDspValue(void);
uint32_t rfmode_is_ofdm(void);
int get_receiving_status(void);

// centauri nvram API

uint32_t cent_nv_get_front_end(void);
int32_t cent_nv_get_elna_rssi_offset(void);
void cent_nv_set_front_end(uint32_t febs);
void cent_nv_set_pa_select(int bOn);

#ifdef __cplusplus
}
#endif

#endif /* __CENT_HOST_H */
