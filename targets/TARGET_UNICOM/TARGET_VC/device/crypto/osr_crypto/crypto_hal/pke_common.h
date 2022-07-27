#ifndef PKE_COMMON_H
#define PKE_COMMON_H


#include <stdint.h>



//define available PKE IP
#define PKE_LP





//define secure version(hardware & software driver)
//#define PKE_SEC




#define POINT_NOT_COMPRESSED      (0x04)



//define KDF
typedef void *(*KDF_FUNC)(const void *input, uint32_t byteLen, uint8_t *key, uint32_t keyByteLen);


//APIs

void pke_load_operand(uint32_t *baseaddr, uint32_t *data, uint32_t wordLen);

void pke_read_operand(uint32_t *baseaddr, uint32_t *data, uint32_t wordLen);

void pke_set_operand_uint32_value(uint32_t *a, uint32_t aWordLen, uint32_t b);



#endif
