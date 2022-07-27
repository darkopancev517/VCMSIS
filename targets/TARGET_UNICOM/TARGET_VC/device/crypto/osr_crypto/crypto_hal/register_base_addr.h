#ifndef REGISTER_BASE_ADDR_H
#define REGISTER_BASE_ADDR_H



#include <stdint.h>    //including int32_t definition




#ifdef __cplusplus
extern "C" {
#endif


#define DMA_RAM_BASE				(0x20080000UL)   //just for temporary use


//register base address
//#define SKE_HP_BASE_ADDR			(0xB0010000UL)            //SKE_HP register base address
#define SKE_LP_BASE_ADDR			(0x40008000UL)            //SKE_HP register base address
#define HASH_BASE_ADDR				(0x40018000UL)            //HASH register base address
#define TRNG_BASE_ADDR				(0x40014000UL)            //TRNG register base address
#define PKE_BASE_ADDR				(0x4000C000UL)            //PKE register base address








#ifdef __cplusplus
}
#endif

#endif
