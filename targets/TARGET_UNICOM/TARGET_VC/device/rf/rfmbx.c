/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "rfmbx.h"
#include "hal/rf.h"
#include "hal/misc.h"

#define MAX_RFMBX_NODE (1<<8) //power of 2 , for ease of modulo

#define CIRC_INC(p) ((p+1)&(MAX_RFMBX_NODE-1))

//typedef struct rfmbx_t{
//    uint32_t front,rear;
//    RF_EVENT_T que[MAX_RFMBX_NODE];
//} __rfmbx_t;

#define RFMBX_front_ADDR 0x20000010
#define RFMBX_rear_ADDR  0x20000014
#define RFMBX_que_ADDR   0x20000018

//static struct rfmbx_t m_mbx;

void rfmbx_init()
{
    //m_mbx.front=0;
    //m_mbx.rear=0;
    hal_misc_m0mem_put(RFMBX_front_ADDR,0);
    hal_misc_m0mem_put(RFMBX_rear_ADDR,0);
}

void rfmbx_clear()
{
    //m_mbx.front=m_mbx.rear;
    hal_misc_m0mem_put(RFMBX_front_ADDR,
                       hal_misc_m0mem_get(RFMBX_rear_ADDR));
}

int rfmbx_get(RF_EVENT_T *px)
{
    uint32_t front=hal_misc_m0mem_get(RFMBX_front_ADDR);
    //if (m_mbx.front==m_mbx.rear)
    if (front==hal_misc_m0mem_get(RFMBX_rear_ADDR)){
        return -2; //queue empty
    }
    //*px=m_mbx.que[m_mbx.front];
    *(uint32_t *)px=hal_misc_m0mem_get(RFMBX_que_ADDR+front*4);
    hal_misc_m0mem_put(RFMBX_front_ADDR,
                       CIRC_INC(front));
    return 0;
}

void rfmbx_dump()
{
#if 0
    RF_EVENT_T vnt;
    int i=0;
    printf("rfmbx: idx  cmd  ack  param\n");
    while (rfmbx_get(&vnt)==0){
        printf("       %3d  %3d  %3d  %d\n"
                       ,i++
                       ,vnt.cmd
                       ,vnt.ack
                       ,vnt.param);
    }
#endif
}
