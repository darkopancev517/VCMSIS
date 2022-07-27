/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "rf_cmd.h"
#include "rf_host.h"
#include "rf_prober.h"
#include "rf_cfg.h"
#include "rf_pmu_csr.h"
#include "rf_queue.h"
#include "hal/rf.h"
#include "totctl.h"

#include "vc_radio.h"
#include "hal/log.h"

//uint32_t iqc_a_b_pmu = 0,iqc_c_pmu = 0;
//extern uint32_t ic_ver;
//extern uint32_t adc_staus;

static uint32_t hcmd_fail = 0;
//static uint32_t hcmd_fail_max = 0;
uint8_t g_rtt_flag = 0;

uint32_t cent_hcmd_fail(void)
{
    if(hcmd_fail > 5)
        return 1;

    return 0;
}

void cent_init_pre_powerup()
{
    //hal_rf_put((uint32_t)&(TOTCMD->m3m0_sync_pttn), 0x5a5abeef);
    hal_rf_put((uint32_t)&(TOTCMD->seq), (uint32_t)(0));
}

int cent_is_powerup()
{
    uint32_t pttn, pttn0=0xdead5a5a;
    do {
        hal_rf_get((uint32_t)&(TOTCMD->m3m0_sync_pttn), &pttn);
        if (pttn!=0xdead5a5a) {
            if (pttn!=pttn0) {
                //printf("pttn=%x\n", pttn);
                pttn0=pttn;
            }
        }
    } while (pttn!=0xdead5a5a);
    //printf("itcr4 <= 0x3333beef\n");
    hal_rf_put((uint32_t)&(TOTCMD->m3m0_sync_pttn), 0x3333beef);
    return 1;
}

static void __lltmrinc(uint32_t *ph, uint32_t *pl)
{
    *pl=*pl+1;
    if (*pl==0) *ph=*ph+1;
}

static bool __wait_for_seq_sync(uint32_t seq, uint32_t t0, uint32_t *pseq2, uint32_t *pt1)
{
    uint32_t tmrcnt_h=0, tmrcnt_l=0;
    do {
        hal_rf_get((uint32_t)&(TOTCMD->seq2), pseq2);

        if (*pseq2==seq){
            *pt1=vcradio_host_get_usec_now();
            return 1;//success
        }
        __lltmrinc(&tmrcnt_h, &tmrcnt_l);
        if (tmrcnt_l >= 7680000){
            *pt1=vcradio_host_get_usec_now();
            return 0; //timeout
        }
    } while (1);
}

bool cent_cmd_res_check(uint32_t rc)
{
    if ( ( rc& ( CMD_RES_FIXPNT_OVERFLOW | CMD_RES_REENTRANT | CMD_RES_UNEXPECTED_SUCCESS | CMD_RES_AGC_TIMEOUT
               | CMD_RES_UNKNOWN | CMD_RES_STS_TIMEOUT | CMD_RES_BAD_PARAM | CMD_RES_SEQ_MISMATCH 
               | CMD_RES_DSP_BUSY_TIMEOUT | CMD_RES_M3_SEQ_TIMEOUT | CMD_RES_M3_TIMEOUT ) )
       || !( rc& CMD_RES_SUCCESS) )
    {
        return 0;
    }
    return 1;
}

void print_rc(uint16_t id, uint16_t seq, uint16_t cmd, uint32_t rc, uint32_t t0, uint32_t t1, uint32_t cntl)
{
    uint32_t rc1,rc2,rc3,rc4,rc5,rc6,rc7;
    hal_rf_get((uint32_t)&(TOTCMD->rc1), &rc1);
    hal_rf_get((uint32_t)&(TOTCMD->rc2), &rc2);
    hal_rf_get((uint32_t)&(TOTCMD->rc3), &rc3);
    hal_rf_get((uint32_t)&(TOTCMD->rc4), &rc4);
    hal_rf_get((uint32_t)&(TOTCMD->rc5), &rc5);
    hal_rf_get((uint32_t)&(TOTCMD->rc6), &rc6);
    hal_rf_get((uint32_t)&(TOTCMD->rc7), &rc7);
    hal_log("rcerr.%d: %x/%x/%x/%x/%x/%x/%x/%x/%x/%x/%x/%x\r\n", id, seq, cmd, rc
            , rc1, rc2, rc3, rc4, rc5, rc6, rc7
            , t1 >= t0? (t1-t0):0xffffffff
            , cntl);
}


uint32_t cent_send_cmd(RF_HCMD_CMD_T cmd, uint16_t param, uint32_t param_ext, uint32_t *pval)
{
    extern void vcmbx_put_msg0(uint32_t mw);
    int rs=vcradio_lock_irq();
    static uint16_t s_seq=0;
    RF_CMD_T hcmd;

    hcmd.cmd = cmd;
    hcmd.param = param; //if cmd==RF_HCMD_DSPCMD, param = dspcmd code
        
    cent_spi_writeW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, cmd_status),0x0);

    hal_rf_put((uint32_t)&(TOTCMD->cmd_param_ext), param_ext);
            
    cent_spi_writeW((uint32_t)&(TOTCMD->hcmd), *((uint32_t*)&hcmd));

    hal_rf_put((uint32_t)&(TOTCMD->seq), (uint32_t)(++s_seq));
   
    uint32_t ts0 = vcradio_host_get_usec_now();
    uint32_t ts1;
    uint32_t seqs2;
    if (!__wait_for_seq_sync(s_seq,ts0,&seqs2,&ts1))
    {
        totctl_dump_seq_sync_timeout(s_seq, seqs2, cmd, param, ts0, ts1);
        vcradio_unlock_irq(rs);
        print_rc(1, s_seq, cmd, CMD_RES_M3_SEQ_TIMEOUT, ts0, ts1, 0);
        return CMD_RES_M3_SEQ_TIMEOUT;
    }

    uint32_t tmrcnt_h=0, tmrcnt_l=0;
    uint32_t t0 = vcradio_host_get_usec_now();
    uint32_t rc;

    do {

        hal_rf_get((uint32_t)&(TOTCMD->rc), &rc);

        if (rc&CMD_RES_COMPLETE) {

            rc&=~(CMD_RES_M3_TIMEOUT|CMD_RES_M3_SEQ_TIMEOUT);//make sure M3 bit not set by M0
            if ((rc&CMD_RES_GOT_VALUE) && pval!=NULL)
            {
                hal_rf_get((uint32_t)&(TOTCMD->cmd_ret_val), pval);
            }
            totctl_dump_complete(s_seq, cmd, param, rc, t0);
            

            if ( !cent_cmd_res_check(rc) )
            {
                print_rc(2, s_seq, cmd, rc, t0, vcradio_host_get_usec_now(), tmrcnt_l);
            }
            else{
                if (totctl_debug_get() & TOTCTL_DEBUG_RCERR_VERBOSE)
                {
                    print_rc(0, s_seq, cmd, rc, t0, vcradio_host_get_usec_now(), tmrcnt_l);
                }
            }

            break; //done
        } else {
            //print_rc(5, s_seq, cmd, rc, t0, vcradio_host_get_usec_now(), tmrcnt_l);
        }

        __lltmrinc(&tmrcnt_h, &tmrcnt_l);
        if (tmrcnt_l >= 4294967290){ //large timeout
            hcmd_fail++;
            rc&=~(CMD_RES_M3_SEQ_TIMEOUT);//make sure M3 bit not set by M0
            rc|=CMD_RES_M3_TIMEOUT;
            totctl_dump_timeout(s_seq, cmd, param, rc, t0);
            print_rc(4, s_seq, cmd, rc, t0, vcradio_host_get_usec_now(), tmrcnt_l);
            break;
        }
    } while (1);

  //printf("exit cent_send_cmd\n");

    //cent_log_add(cmd);

    hcmd_fail = 0;

    vcradio_unlock_irq(rs);
                                    // #ifndef CONFIG_DISABLE_DEBUG_CENT_SEND_CMD_DEBUG
                                    //     printf("cent_send_cmd.9\n");
                                    // #endif
    return rc;
}

uint32_t cent_write_cmd_ext(RF_HCMD_CMD_T cmd, uint16_t param, uint32_t paramExt)
{
    hal_rf_put((uint32_t)&TOTDBG->dsp_cmd_ext, paramExt);
    // cmd[14]: new protocol extension command, implies dsp_cmd_ext contains paramExt
    return cent_send_cmd(0x4000|cmd, param, 0, NULL); 
}

uint32_t cent_cmd_status(void)
{
    return cent_send_cmd(RF_HCMD_SYSTEM_STATUS, 0, 0, NULL);
}


#define MS2TICK     32

#define TICK_1MS    (MS2TICK)
#define TICK_500US  (MS2TICK / 2)
#define TICK_250US  (MS2TICK / 4)
#define TICK_125US  (MS2TICK / 8)

uint8_t time2tick[SLP_RES_ALL] = { TICK_1MS, TICK_500US, TICK_250US, TICK_125US };

void cent_sleep_time_setting(uint32_t period)
{    

    uint32_t target_tick;

    volatile TIMER_32K_FIELDS_T timer_setting;

    cent_spi_readW(CENT_RTN_32K_CTRL_ADDR, (uint32_t*)&timer_setting);

    /* sleep time = period * timer_setting.resl */

    if ((timer_setting.resl >= SLP_RES_1ms) && (timer_setting.resl < SLP_RES_ALL)) {
        target_tick = period * time2tick[timer_setting.resl - SLP_RES_1ms];
    }else
        target_tick = period * time2tick[0];

    if (target_tick > TIMER32K_TICK_MAX)
        target_tick = TIMER32K_TICK_MAX;

    timer_setting.target = target_tick;

    cent_spi_writeW(CENT_RTN_32K_CTRL_ADDR, *((uint32_t*)&timer_setting));

    //  cent_spi_writeW(CENT_RTN_SLEEP_PERIOD, period);

}

uint32_t cent_cmd_idle(void)
{

    return cent_send_cmd(RF_HCMD_IDLE, 0, 0, NULL);

  	//--sonata.woody TransceiverDcocSetting();
}


uint32_t cent_cmd_sleep(uint32_t period)
{
 
    cent_sleep_time_setting(period);
    return cent_send_cmd(RF_HCMD_SLEEP, 0, 0, NULL);
}

uint32_t cent_cmd_shutdown(void)
{
    return cent_send_cmd(RF_HCMD_SHUTDOWN, 0, 0, NULL);
}

//rco32k_cal_cmd {auto_restore(2bit)}
//00: do not restore, 01: restore if done, 10: restore if timeout, 11: restore if done or timeout
uint32_t cent_cmd_cal_32k(void)
{
    uint32_t res=cent_send_cmd(RF_HCMD_CALIB_32K, 1, 0, NULL);
    return res;
}

//rco4m_cal_cmd {auto_restore(2bit)}
//00: do not restore, 01: restore if done, 10: restore if timeout, 11: restore if done or timeout
uint32_t cent_cmd_cal_4m(void)
{
    uint32_t res=cent_send_cmd(RF_HCMD_CALIB_4M, 1, 0, NULL);
    return res;
}

uint32_t cent_cmd_cal_vco(void)
{
    return cent_send_cmd(RF_HCMD_CALIB_VCO, 0, 0, NULL);
}           

uint32_t cent_cmd_cal_iq(void)
{
    return cent_send_cmd(RF_HCMD_CALIB_IQ, 0, 0, NULL);
        //--sonata.woody if(0x7000B3 == ic_ver)
	//--sonata.woody {
            //--sonata.woody /* Gear Shift Bias setting */
            //--sonata.woody GearShiftBiasSetForIqCal();
            //--sonata.woody 
            //--sonata.woody /* TBD IQ No hand shake */
            //--sonata.woody cent_busy_wait(6000);
            //--sonata.woody 
            //--sonata.woody iqc_a_b_pmu = (CentauriCsrRead(0x4002c0cc)&0x7fff7fff);
            //--sonata.woody iqc_c_pmu = (CentauriCsrRead(0x4002c0d0)&0x7fff);
            //--sonata.woody  
            //--sonata.woody /* Gear shfit  DCOC setting  */
            //--sonata.woody TransceiverDcocSetting();
            //--sonata.woody  
            //--sonata.woody cent_spi_writeW(0x20010074, 0x0);
	//--sonata.woody }else {
            //--sonata.woody 
	    //--sonata.woody cent_busy_wait(6000);
            //--sonata.woody 
        //--sonata.woody }
	
}

uint32_t cent_cmd_cal_rxadc(void)
{

    uint32_t res=cent_send_cmd(RF_HCMD_CALIB_RX_ADC, 0, 0, NULL);
    return res;
}

uint32_t cent_cmd_period_config(uint32_t period, uint32_t tolerance)
{
    cent_spi_writeW(CENT_RTN_PERIOD_TOLERANCE, tolerance);
    cent_spi_writeW(CENT_RTN_PERIOD_TIME, period);

    return cent_send_cmd(RF_HCMD_CALIB_PERIOD_CHG, 0, 0, NULL);
}

//init_cmd {iqc_cal(1bit), vco_cal (1bit), adc_cal(1bit)}
uint32_t cent_cmd_init(void)
{

	cent_spi_writeW(CENT_RTN_CMD_ACK_PARAM, 0);
	
	//--sonata.woody if(0x7000B3 == ic_ver)
        //--sonata.woody {
            //--sonata.woody cent_send_cmd(RF_HCMD_INIT, 0x2, 0);
            //--sonata.woody /* Set error_power k = 3 */
            //--sonata.woody U32 csr_tmp;
            //--sonata.woody csr_tmp = CentauriCsrRead(0x4002417c);
            //--sonata.woody csr_tmp = (csr_tmp & 0xFFCFFFFF);
            //--sonata.woody csr_tmp |= (3<<20);
            //--sonata.woody CentauriCsrWrite(0x4002417c,csr_tmp);
        //--sonata.woody }else
        //--sonata.woody {
    return cent_send_cmd(RF_HCMD_INIT, 0x3, 0, NULL);
        //--sonata.woody }
	
//--sonata.woody #ifndef HCMD_BLOCK
	//--sonata.woody uint32_t value;
	//--sonata.woody do{
		//--sonata.woody cent_spi_readW(CENT_RTN_CMD_ACK_PARAM, &value);
	//--sonata.woody }while(value == 0);
//--sonata.woody #endif
	
}


// {next_state(3bit), fcs_type(2bit), packet_len(11bit)}
uint32_t cent_cmd_tx(uint32_t fcs, uint32_t packet_len)
{
    /* workaround TX issue after wakup */
//	extern  void RfTxPaPwrDownCtrlAuto(void);
//    RfTxPaPwrDownCtrlAuto(); 

	uint32_t param;

	param = (fcs & 0x3) << 11;
	param |= packet_len & 0x7ff;

    return cent_send_cmd(RF_HCMD_TX, param, 0, NULL);
	
//--sonata.woody #if	DLT_698p44_FLAG
		//--sonata.woody PhyExtraPsduConfig(0);
		//--sonata.woody //printf("%x \n",(int) CentauriCsrRead(0x40024008));
//--sonata.woody 
//--sonata.woody #endif

}

// {write_len(8bit)}
uint32_t cent_cmd_tx_refilled(uint32_t write_len)
{
	uint32_t param;

	param = write_len & 0xff;
	
    return cent_send_cmd(RF_HCMD_TX_REFILLED, param, 0, NULL);

}

//rx {next_state(3bit), fcs(2bit)}
uint32_t cent_cmd_rx(uint32_t next_state)
{
	uint32_t param;
    #ifdef CONFIG_DEBUG_PHY_CSR_RX_TEST
        uint32_t while_cnt=0;
        uint32_t csr;
        uint32_t csr2;
        uint32_t csr3;
    #endif

	if(next_state >= SYS_STATE_ALL)
		next_state = SYS_IDLE;
	
	param = next_state << 2;	// next_state

        uint32_t res=cent_send_cmd(RF_HCMD_RX, param, 0, NULL);


        return res;
}

// {read_len(8bit)}
uint32_t cent_cmd_rx_read(uint32_t read_len)
{
    uint32_t param;

    param = read_len & 0xff;
    
    return cent_send_cmd(RF_HCMD_RX_READED, param, 0, NULL);

}

uint32_t cent_cmd_txdelay(uint32_t delay)
{
    return cent_send_cmd(RF_HCMD_MS_TXDELAY, delay, 0, NULL);
}


//txpwr {pwr(16bit)} 
uint32_t cent_cmd_txpwr(int16_t txpwr)
{
    if(txpwr < 0)
        txpwr = (txpwr * -1) + 0x80;
	
    return cent_send_cmd(RF_HCMD_TXPWR, (uint16_t)txpwr, 0, NULL);
}

//txpwr {pwr(16bit)}
uint32_t cent_cmd_ofdm_txpwr(int16_t txpwr)
{
    if (txpwr < 0)
        txpwr = (txpwr * -1) + 0x80;

    return cent_send_cmd(RF_HCMD_OFDM_TXPWR, (uint16_t)txpwr, 0, NULL);
}

uint32_t cent_cmd_rssi(int *prssi)
{

    uint32_t res=cent_send_cmd(RF_HCMD_RSSI, 0, 0, (uint32_t *)prssi);
#ifndef HCMD_BLOCK
    cent_busy_wait(CCA_DELAY*20+20);
#endif
    *prssi = get_rssi(); //TODO: intermediate change for stage 1, approach 1

    return res;
}

int32_t cent_cmd_ModeSwitch_CCA(void)
{
    int32_t rssi = GetModeSwitchCCA();

    return rssi;
}

int32_t cent_cmd_tx_settling_time(void)
{
    int32_t time = GetTxSettlingTime();

    return time;
}

uint32_t cent_cmd_dsp_value(void)
{
    uint32_t value = GetDspValue();

    return value;
}

//rssi_offset {offset(8bit)} 
uint32_t cent_cmd_rssi_offset(int16_t offset)
{
    if(offset > 15)
            offset = 15;
    else if(offset < -15)
            offset = -15;
    
    offset = (offset * 8) & 0xFF;

    //RSSI offset value, format <1,4,3>
    uint32_t res=cent_send_cmd(RF_HCMD_RSSI_OFFSET, (uint16_t)offset, 0, NULL);
    return res;
}

//channel { rw(1bit), iqc_cal(1bit), vco_cal (1bit), next_state(3bit)}
// chn_band(32bits) in PMU_RTN_CMD_PARAM
uint32_t cent_cmd_set_channel(uint32_t chn_band)
{
    uint32_t res;

    int rs=vcradio_lock_irq();
    extern uint32_t last_channel;
    last_channel = chn_band;
    cent_spi_writeW(CENT_RTN_BAND, chn_band);
    res = cent_send_cmd(RF_HCMD_BAND, 0x8, chn_band, NULL);
    vcradio_unlock_irq(rs);

    return res;
}

uint32_t cent_cmd_read_channel(void)
{
	uint32_t chn_band;
	
    chn_band = CentauriCsrRead(CENT_RTN_BAND);
	return chn_band;

}

//modi {mod_index(16bit)}
uint32_t cent_cmd_set_modi(uint32_t modi)
{
    uint32_t rc=cent_send_cmd(RF_HCMD_MODI, modi, 0, NULL);
    rc|=cent_cmd_rx(SYS_RX);
    return rc;
}

// rate(32bits) in PMU_RTN_CMD_PARAM
// clk_sel(1bit)
uint32_t cent_cmd_set_rate(uint32_t rate)
{
    int rs=vcradio_lock_irq();
    
    cent_spi_writeW(CENT_RTN_CMD_ACK_PARAM, rate);

    uint32_t rc=cent_send_cmd(RF_HCMD_RATE, 0, 0, NULL);

    vcradio_unlock_irq(rs);
    return rc;
}

// txcw {flag(1bit)}
uint32_t cent_cmd_txcw(uint16_t enable)
{

    uint32_t rc=cent_send_cmd(RF_HCMD_TXCW, enable, 0, NULL);
    return rc;
}

// txcm {auto_pattern(1bit), flag(1bit)}
uint32_t cent_cmd_txcm(uint16_t enable)
{
    uint32_t rc;
    if (enable)
    {
        rc=cent_send_cmd(RF_HCMD_TXCM, 0x2 | enable, 0, NULL);
    }
    else
    {
        cent_cmd_idle();
        vcradio_reinit();
        rc=CMD_RES_COMPLETE|CMD_RES_SUCCESS;
    }
    return rc;
}


// gfilter {switch(1bit), bt(1bit)}
uint32_t cent_cmd_gfilter(uint16_t sw, uint16_t bt)
{
	uint16_t param;
	
    param = ((sw&0x1) << 1) + (bt & 0x1);
	
    return cent_send_cmd(RF_HCMD_GFILTER, param, 0, NULL);
}

// psduorder {order(1bit)}
uint32_t cent_cmd_psdu_order(uint16_t order)
{
	
    return cent_send_cmd(RF_HCMD_PSDU_ORDER, order, 0, NULL);
}

// dw {dw_en(1bit)}
uint32_t cent_cmd_data_whitening(uint16_t dw)
{
	
    return cent_send_cmd(RF_HCMD_DW, dw, 0, NULL);
}

//Round Time Trip
uint32_t cent_cmd_rtt(uint16_t bEn)
{
    g_rtt_flag = ((bEn>0) ? 1 : 0);
    return CMD_RES_COMPLETE | CMD_RES_SUCCESS;
}

// pmb {length(16bit)}
uint32_t cent_cmd_pmb_length(uint16_t length)
{
    return cent_send_cmd(RF_HCMD_PMB, length, 0, NULL);
}

// rxlp {flag(1bit)}
uint32_t cent_cmd_rx16mhz(uint16_t rx16m)
{
	
    return cent_send_cmd(RF_HCMD_RXLP, rx16m, 0, NULL);

}


// pasel {pa(1bit)}
uint32_t cent_cmd_pa_select(uint16_t pa)
{
	
    return cent_send_cmd(RF_HCMD_PASEL, pa, 0, NULL);
}

uint32_t cent_cmd_dctune(uint16_t dctune)
{
    uint32_t csr_val;

    csr_val = *(volatile unsigned *)0x4004B000;
    csr_val &= (~0x1FE000);
    csr_val |= (dctune << 13);
    *(volatile unsigned *)0x4004B000 = csr_val;
    return CMD_RES_COMPLETE | CMD_RES_SUCCESS;
}

//TODO: return res
uint16_t cent_cmd_read_dctune(void)
{
	uint32_t dctune;

    dctune = *(volatile unsigned *)0x4004B000;
    dctune &= 0x1FE000;
    dctune >>= 13;

	return (uint16_t)(dctune&0xff);
}


//TODO: return res
// adc {vin_sel(2bit)}
uint16_t cent_cmd_saradc(uint16_t vin_sel)
{
	uint32_t value;
	int rs=vcradio_lock_irq();
    cent_send_cmd(RF_HCMD_ADC, vin_sel, 0, NULL);
#ifndef HCMD_BLOCK
	cent_busy_wait(1000);
#endif	
	cent_spi_readW(CENT_RTN_CMD_ACK_PARAM, &value);
    vcradio_unlock_irq(rs);

	return (uint16_t)(value&0xffff);
}

uint32_t cent_cmd_elna_enable(uint16_t sw)
{
	
    return cent_send_cmd(RF_HCMD_ELNA, sw, 0, NULL);

}


uint32_t cent_cmd_switch_test(uint16_t sw)
{
	
    return cent_send_cmd(RF_HCMD_SW_CTRL_TEST, sw, 0, NULL);

}


// {auto_pattern(1bit),fcs_type(2bit), packet_len(11bit)}
uint32_t cent_cmd_mac_loopback(uint32_t fcs, uint32_t packet_len)
{
	uint32_t param;

	param = (fcs & 0x3) << 11;
	param |= packet_len & 0x7ff;
	
    return cent_send_cmd(RF_HCMD_MAC_LOOPBACK, param, 0, NULL);

}

//change_state {state(3bit)}
uint32_t cent_cmd_state_change(uint32_t state)
{

    return cent_send_cmd(RF_HCMD_STATE_CHANGE, state, 0, NULL);
}

uint32_t cent_cmd_statistic_clear(void)
{
    if (rfmode_is_ofdm())
    {
        cent_send_cmd(RF_HCMD_STAT_CLEAR, 0, 0, NULL);
        return OFDM_Counter_Reset();
    }
    else
    {
        OFDM_Counter_Reset();
        return cent_send_cmd(RF_HCMD_STAT_CLEAR, 0, 0, NULL);
    }

}

uint32_t cent_wakeup(void)
{
    return cent_cmd_statistic_clear();

}

uint32_t cent_cmd_txpower(uint32_t txpwrmode)
{
    cent_spi_writeW(CENT_TXPWRMODE, txpwrmode);
    return CMD_RES_COMPLETE|CMD_RES_SUCCESS;
}
uint32_t cent_cmd_basemode(uint32_t basemode)
{
    cent_spi_writeW(CENT_BASEMODE, basemode);
    return cent_send_cmd(RF_HCMD_BASEMODE, 0x08, 0, NULL);
}
uint32_t cent_cmd_newmode(uint8_t CH_ID, uint8_t CH_NO, uint8_t PHY_TYPE, uint8_t PHY_MODE, uint8_t TXPWR)
{
    return cent_send_cmd(RF_HCMD_MRFSK, 0x08, 0, NULL);
}
uint16_t mrfsk_on = 0;
uint32_t cent_cmd_mrfsk(uint32_t parmFSK,uint32_t rf_channel)
{
    mrfsk_on = (parmFSK & 0x0000FFFF);
    cent_spi_writeW(CENT_MODESWITCH, parmFSK);
    cent_spi_writeW(CENT_RFCHANNEL, rf_channel);
    return cent_send_cmd(RF_HCMD_MRFSK, 0x08, 0, NULL);
}
uint32_t cent_cmd_optmcs(uint32_t parmFSK)
{
    cent_spi_writeW(CENT_MODESWITCH, parmFSK);
    return cent_send_cmd(RF_HCMD_OFDM_OPTMCS, 0x08, 0, NULL);
}
uint32_t SetRFMode(uint32_t rfmode)
{
    cent_send_cmd(RF_HCMD_RFMODE, (rfmode&0x01), 0, NULL);
    return cent_cmd_idle();
}
uint32_t SetDSPRead(uint8_t cmd, uint32_t param)
{
    cent_spi_writeW(CENT_DSP_ADDR1, ((cmd & 0x7F) << 24) + (param&0xFFF));
    cent_send_cmd(RF_HCMD_DSP_READ, 0, 0, NULL);
    return cent_cmd_idle();
}
uint32_t SetDSPWrite(uint8_t cmd, uint32_t param,uint32_t IsEXTCMD)
{
    if (IsEXTCMD)
    {
        cent_spi_writeW(CENT_DSP_ADDR1, ((cmd & 0x7F) << 24));
        cent_spi_writeW(CENT_DSP_ADDR2, param);
    }
    else
    {
        cent_spi_writeW(CENT_DSP_ADDR1, ((cmd & 0x7F) << 24) + (param & 0xFFF));
    }
    cent_send_cmd(RF_HCMD_DSP_WRITE, IsEXTCMD, 0, NULL);
    return cent_cmd_idle();
}
uint32_t SetMSAlgo(uint32_t param)
{
    cent_send_cmd(RF_HCMD_MS_ALGORITHM, (param&0x01), 0, NULL);
    return cent_cmd_idle();
}

uint32_t GetRFMode(void)
{
    uint32_t m;
    cent_spi_readW(CENT_RFMODE, &m);
    return m;
}
extern uint32_t g_fec_en;
uint32_t TransceiverFecCtrlSwMode(uint32_t fec_en, uint32_t fec_type)
{
    uint16_t parm = 0;
    parm = ((fec_en & 0x0F) << 4) + (fec_type & 0x0F);
    g_fec_en = fec_en;
    return cent_send_cmd(RF_HCMD_FEC, parm, 0, NULL);
}

uint32_t rf_cmd_get_ofdm_version()
{
    uint32_t ver;
    cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, ofdm_version), &ver);
    return ver;
}

uint32_t rf_cmd_get_m0_version()
{
    uint32_t hash;
    cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, m0_git_commit), &hash);
    return hash;
}
uint32_t GetM0HWSET_IDX(void)
{
    uint32_t m;
    cent_spi_readW(M0_HWSET_IDX, &m);
    return (m&0x0f);
}
void SetM0HWSET_Clean(void)
{
    cent_spi_writeW(M0_HWSET_IDX, 0x00000000);
}
uint32_t GetM0HWSET_VAL(void)
{
    uint32_t m;
    cent_spi_readW(M0_HWSET_VAL, &m);
    return m;
}
