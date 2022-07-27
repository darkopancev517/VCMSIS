#ifndef UTILITY_H
#define UTILITY_H


#include <stdint.h>    //including int32_t definition



#ifdef __cplusplus
extern "C" {
#endif



#define GET_MAX_LEN(a,b)         (((a)>(b))?(a):(b))
#define GET_MIN_LEN(a,b)         (((a)>(b))?(b):(a))
#define GET_WORD_LEN(bitLen)     (((bitLen)+31)/32)
#define GET_BYTE_LEN(bitLen)     (((bitLen)+7)/8)





//APIs

#define PKE_PRINT_BUF
#ifdef PKE_PRINT_BUF
extern void print_buf_U8(uint8_t buf[], uint32_t byteLen, char name[]);
extern void print_buf_U32(uint32_t buf[], uint32_t wordLen, char name[]);
extern void print_BN_buf_U32(uint32_t buf[], uint32_t wordLen, char name[]);
#endif

void memcpy_(void *dst, void *src, uint32_t size);

void memset_(void *dst, uint8_t value, uint32_t size);

int8_t memcmp_(void *m1, void *m2, uint32_t size);

void uint32_set(uint32_t *a, uint32_t value, uint32_t wordLen);

void uint32_copy(uint32_t *dst, uint32_t *src, uint32_t wordLen);

void uint32_clear(uint32_t *a, uint32_t wordLen);

void uint32_sleep(uint32_t count, uint8_t rand);

void uint32_endian_reverse(uint8_t *in, uint8_t *out, uint32_t wordLen);


void reverse_byte_array(uint8_t *in, uint8_t *out, uint32_t byteLen);

//void reverse_word(uint8_t *in, uint8_t *out, uint32_t bytelen);

//void dma_reverse_word_array(uint32_t *in, uint32_t *out, uint32_t wordlen, uint32_t reverse_word);

void uint8_XOR(uint8_t *A, uint8_t *B, uint8_t *C, uint32_t byteLen);

void uint32_XOR(uint32_t *A, uint32_t *B, uint32_t *C, uint32_t wordLen);

uint32_t get_valid_bits(const uint32_t *a, uint32_t wordLen);

uint32_t get_valid_words(uint32_t *a, uint32_t max_words);

uint8_t uint8_BigNum_Check_Zero(uint8_t a[], uint32_t aByteLen);

uint32_t uint32_BigNum_Check_Zero(uint32_t a[], uint32_t aWordLen);

int32_t uint32_BigNumCmp(uint32_t *a, uint32_t aWordLen, uint32_t *b, uint32_t bWordLen);

uint32_t Get_Multiple2_Number(uint32_t a[]);

uint32_t Big_Div2n(uint32_t a[], int32_t aWordLen, uint32_t n);

uint8_t Bigint_Check_1(uint32_t a[], uint32_t aWordLen);

uint8_t Bigint_Check_p_1(uint32_t a[], uint32_t p[], uint32_t wordLen);

uint32_t uint32_integer_check(uint32_t *k, uint32_t *n, uint32_t wordLen, uint32_t ret_zero, uint32_t ret_big,
		uint32_t ret_success);

#ifdef __cplusplus
}
#endif

#endif
