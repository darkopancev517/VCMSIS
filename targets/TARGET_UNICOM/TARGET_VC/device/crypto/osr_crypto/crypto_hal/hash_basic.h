#ifndef HASH_BASIC_H
#define HASH_BASIC_H



#include "register_base_addr.h"



#ifdef __cplusplus
extern "C" {
#endif




#define SUPPORT_HASH_SM3
//#define SUPPORT_HASH_MD5
#define SUPPORT_HASH_SHA256
//#define SUPPORT_HASH_SHA384
//#define SUPPORT_HASH_SHA512
#define SUPPORT_HASH_SHA1
//#define SUPPORT_HASH_SHA224
//#define SUPPORT_HASH_SHA512_224
//#define SUPPORT_HASH_SHA512_256
//#define SUPPORT_HASH_SHA3_224
//#define SUPPORT_HASH_SHA3_256
//#define SUPPORT_HASH_SHA3_384
//#define SUPPORT_HASH_SHA3_512



//#define HASH_CPU_BIG_ENDIAN        //endian choice.


//#define HASH_DMA_FUNCTION


//#define HMAC_SECURE_PORT_FUNCTION
#ifdef HMAC_SECURE_PORT_FUNCTION
#define HMAC_MAX_KEY_IDX                             (8)   //if key is from secure port, the max key index(or the number of keys)
#define HMAC_MAX_SP_KEY_SIZE                         (64)  //for secure port key, max bytes of one key
#endif



//some register offset
#define HASH_LAST_OFFSET                             (24)
#define HASH_DMA_OFFSET                              (17)
#define HASH_INTERRUPTION_OFFSET                     (16)


//HASH register struct
typedef struct {
	uint32_t HASH_CTRL;						/* Offset: 0x000 (W1S)  Control register */
	uint32_t HASH_CFG;						/* Offset: 0x004 (R/W)  Config register */
	uint32_t HASH_SR1;						/* Offset: 0x008 (R)    Status register 1 */
	uint32_t HASH_SR2;						/* Offset: 0x00C (W1C)  Status register 2 */
	uint32_t REV_1[4];
	uint32_t HASH_PCR_LEN[4];				/* Offset: 0x020 (R/W)  message length register */
	uint32_t HASH_OUT[16];					/* Offset: 0x030 (R)    Output register */
	uint32_t HASH_IN[16];					/* Offset: 0x070 (W)    Hash iterator Input register */
	uint32_t HASH_VERSION;					/* Offset: 0x0B0 (R)    Version register */
	uint32_t REV_2[19];
	uint32_t HASH_M_DIN[32];				/* Offset: 0x100 (R/W)  Hash message Input register */
	uint32_t DMA_SA;						/* Offset: 0x180 (R/W)  DMA Source Address register */
	uint32_t DMA_DA;						/* Offset: 0x184 (R/W)  DMA Destination Address register */
	uint32_t DMA_RLEN;						/* Offset: 0x188 (R/W)  DMA Input Length register */
	uint32_t DMA_WLEN;						/* Offset: 0x18C (R/W)  DMA Output Length register */
} HASH_REG;


//HASH max length
#if (defined(SUPPORT_HASH_SHA384) || defined(SUPPORT_HASH_SHA512) ||defined(SUPPORT_HASH_SHA512_224) ||defined(SUPPORT_HASH_SHA512_256))
#define HASH_DIGEST_MAX_WORD_LEN       (16)
#define HASH_BLOCK_MAX_WORD_LEN        (32)
#define HASH_TOTAL_LEN_MAX_WORD_LEN    (4)
#else
#define HASH_DIGEST_MAX_WORD_LEN       (8)
#define HASH_BLOCK_MAX_WORD_LEN        (16)
#define HASH_TOTAL_LEN_MAX_WORD_LEN    (2)
#endif

#define HASH_ITERATOR_MAX_WORD_LEN     HASH_DIGEST_MAX_WORD_LEN
#define HASH_BLOCK_MAX_BYTE_LEN        (HASH_BLOCK_MAX_WORD_LEN<<2)


//HASH algorithm definition
typedef enum {
#ifdef SUPPORT_HASH_SM3
	HASH_SM3                      = 0,
#endif

#ifdef SUPPORT_HASH_MD5
	HASH_MD5                      = 1,
#endif

#ifdef SUPPORT_HASH_SHA256
	HASH_SHA256                   = 2,
#endif

#ifdef SUPPORT_HASH_SHA384
	HASH_SHA384                   = 3,
#endif

#ifdef SUPPORT_HASH_SHA512
	HASH_SHA512                   = 4,
#endif

#ifdef SUPPORT_HASH_SHA1
	HASH_SHA1                     = 5,
#endif

#ifdef SUPPORT_HASH_SHA224
	HASH_SHA224                   = 6,
#endif

#ifdef SUPPORT_HASH_SHA512_224
	HASH_SHA512_224               = 7,
#endif

#ifdef SUPPORT_HASH_SHA512_256
	HASH_SHA512_256               = 8,
#endif

#ifdef SUPPORT_HASH_SHA3_224
	HASH_SHA3_224                 = 9,
#endif

#ifdef SUPPORT_HASH_SHA3_256
	HASH_SHA3_256                 = 10,
#endif

#ifdef SUPPORT_HASH_SHA3_384
	HASH_SHA3_384                 = 11,
#endif

#ifdef SUPPORT_HASH_SHA3_512
	HASH_SHA3_512                 = 12,
#endif
} HASH_ALG;


//HASH return code
enum HASH_RET_CODE
{
	HASH_SUCCESS = 0,
	HASH_BUFFER_NULL,
	HASH_CONFIG_INVALID,
	HASH_INPUT_INVALID,
	HASH_LEN_OVERFLOW,
	HASH_ERROR,
};


//hash callback function type
typedef void (*HASH_CALLBACK)(void);



//APIs

uint32_t hash_get_version(void);

void hash_set_cpu_mode(void);

void hash_set_dma_mode(void);

void hash_set_alg(HASH_ALG hash_alg);

void hash_enable_interruption(void);

void hash_disable_interruption(void);

void hash_set_last_block(uint32_t tag);

void hash_get_iterator(uint8_t *iterator, uint32_t hash_iterator_words);

void hash_set_iterator(uint32_t *iterator, uint32_t hash_iterator_words);

void hash_clear_msg_len(void);

void hash_set_msg_total_byte_len(uint32_t *msg_total_bytes, uint32_t words);

void hash_start(void);

void hash_wait_till_done(void);

void hash_set_dma_output_len(uint32_t bytes);

void hash_input_msg(uint8_t *msg, uint32_t msg_words);

#ifdef HASH_DMA_FUNCTION
void hash_dma_operate(uint32_t *in, uint32_t *out, uint32_t inByteLen, HASH_CALLBACK callback);
#endif




#ifdef __cplusplus
}
#endif

#endif 

