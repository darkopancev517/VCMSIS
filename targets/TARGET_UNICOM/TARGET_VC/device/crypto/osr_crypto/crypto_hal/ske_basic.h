#ifndef SKE_BASIC_H
#define SKE_BASIC_H


#include "register_base_addr.h"


#ifdef __cplusplus
extern "C" {
#endif



//#define SUPPORT_SKE_DES
#if 0                               //warning: hardware does not support 3DES directly, here the 4 MACRO should be defined or not defined simultaneously
#define SUPPORT_SKE_TDES_128
#define SUPPORT_SKE_TDES_192
#define SUPPORT_SKE_TDES_EEE_128
#define SUPPORT_SKE_TDES_EEE_192
#endif
#define SUPPORT_SKE_AES_128
#define SUPPORT_SKE_AES_192
#define SUPPORT_SKE_AES_256
#define SUPPORT_SKE_SM4

//#define SUPPORT_SKE_IRQ

#define SUPPORT_SKE_MODE_ECB
#define SUPPORT_SKE_MODE_CBC
#define SUPPORT_SKE_MODE_CFB
#define SUPPORT_SKE_MODE_OFB
#define SUPPORT_SKE_MODE_CTR
//#define SUPPORT_SKE_MODE_XTS        //warning: hardware does not support directly
#define SUPPORT_SKE_MODE_GCM
#ifdef SUPPORT_SKE_MODE_GCM
//#define SUPPORT_SKE_MODE_GMAC       //GMAC is specialization of GCM mode
#endif
//#define SUPPORT_SKE_MODE_CMAC       //warning: hardware does not support directly
//#define SUPPORT_SKE_MODE_CBC_MAC    //warning: hardware does not support directly
//#define SUPPORT_SKE_MODE_CCM




//#define SKE_LP_CPU_BIG_ENDIAN               //endian choice.

#define SKE_LP_DMA_FUNCTION

//these two macro is for SKE LP
#define SKE_LP_DMA_ENABLE                              (1)
#define SKE_LP_DMA_DISABLE                             (0)


//#define SKE_SECURE_PORT_FUNCTION
#ifdef SKE_SECURE_PORT_FUNCTION
#define SKE_MAX_KEY_IDX	                               (8)   //if key is from secure port, the max key index(or the number of keys)
#endif

//some register offset
#define SKE_LP_REVERSE_BYTE_ORDER_IN_WORD_OFFSET       (24)
#define SKE_LP_MODE_OFFSET                             (28)
#define SKE_LP_CRYPTO_OFFSET                           (11)
#define SKE_LP_IRQ_OFFSET                              (17)
#define SKE_LP_UP_CFG_OFFSET                           (12)
#define SKE_LP_DMA_OFFSET                              (16)
#define SKE_LP_LAST_DATA_OFFSET                        (16)


//SKE register struct
typedef struct {
	uint32_t ctrl;              /* Offset: 0x000 (W1S) SKE Control Register */
	uint32_t cfg;               /* Offset: 0x004 (R/W) SKE Config Register */
	uint32_t sr1;               /* Offset: 0x008 (R)   SKE Status Register 1 */
	uint32_t sr2;               /* Offset: 0x00C (W0C) SKE Status Register 2 */
	uint32_t key1[8];           /* Offset: 0x010 (R/W) Key1 */
	uint32_t rev1[12];
	uint32_t ske_a_len_l;       /* Offset: 0x060 (R/W) CCM/GCM mode AAD length low Register */
	uint32_t ske_a_len_h;       /* Offset: 0x064 (R/W) CCM/GCM mode AAD length high Register */
	uint32_t ske_c_len_l;       /* Offset: 0x068 (R/W) CCM/GCM/XTS mode plaintext/ciphertext length low Register */
	uint32_t ske_c_len_h;       /* Offset: 0x06C (R/W) CCM/GCM/XTS mode plaintext/ciphertext length high Register */
	uint32_t iv[4];             /* Offset: 0x070 (R/W) Initial Vector */
	uint32_t m_din_cr;          /* Offset: 0x080 (R/W) SKE Input falg Register */
	uint32_t rev3[3];
	uint32_t m_din[4];          /* Offset: 0x090 (R/W) SKE Input Register */
	uint32_t rev4[4];
	uint32_t m_dout[4];         /* Offset: 0x0B0 (R)   SKE Output Register */
	uint32_t dma_sa_l;          /* Offset: 0x0C0 (R/W) DMA Source Address Low part register */
	uint32_t dma_da_l;          /* Offset: 0x0C4 (R/W) DMA Destination Address Low part register */
	uint32_t dma_rlen;          /* Offset: 0x0C8 (R/W) DMA Source Data Length register */
	uint32_t dma_wlen;          /* Offset: 0x0CC (R/W) DMA Destination Data Length register */
	uint32_t rev5[11];
	uint32_t ske_version;       /* Offset: 0x0FC (R)   SKE Version Register */
} ske_lp_reg_t;





//SKE Operation Mode
typedef enum
{
	SKE_MODE_BYPASS               = 0,   // BYPASS Mode

#ifdef SUPPORT_SKE_MODE_ECB
	SKE_MODE_ECB                  = 1,   // ECB Mode
#endif

#ifdef SUPPORT_SKE_MODE_XTS
	SKE_MODE_XTS                  = 2,   // XTS Mode
#endif

#ifdef SUPPORT_SKE_MODE_CBC
	SKE_MODE_CBC                  = 3,   // CBC Mode
#endif

#ifdef SUPPORT_SKE_MODE_CFB
	SKE_MODE_CFB                  = 4,   // CFB Mode
#endif

#ifdef SUPPORT_SKE_MODE_OFB
	SKE_MODE_OFB                  = 5,   // OFB Mode
#endif

#ifdef SUPPORT_SKE_MODE_CTR
	SKE_MODE_CTR                  = 6,   // CTR Mode
#endif

#ifdef SUPPORT_SKE_MODE_CMAC
	SKE_MODE_CMAC                 = 7,   // CMAC Mode
#endif

#ifdef SUPPORT_SKE_MODE_CBC_MAC
	SKE_MODE_CBC_MAC              = 8,   // CBC-MAC Mode
#endif

#ifdef SUPPORT_SKE_MODE_GCM
	SKE_MODE_GCM                  = 9,   // GCM Mode
#endif

#ifdef SUPPORT_SKE_MODE_CCM
	SKE_MODE_CCM                  = 10,  // CCM Mode
#endif

#ifdef SUPPORT_SKE_MODE_GMAC
	SKE_MODE_GMAC                 = 18,  // GMAC Mode
#endif
} SKE_MODE;


//SKE Crypto Action
typedef enum {
	SKE_CRYPTO_ENCRYPT       = 0,   // encrypt
	SKE_CRYPTO_DECRYPT          ,   // decrypt
} SKE_CRYPTO;


//SKE MAC Action
typedef enum {
	SKE_GENERATE_MAC = SKE_CRYPTO_ENCRYPT,
	SKE_VERIFY_MAC   = SKE_CRYPTO_DECRYPT,
} SKE_MAC;



//SKE Algorithm
typedef enum {
#ifdef SUPPORT_SKE_DES
	SKE_ALG_DES            = 0,      // DES
#endif

#ifdef SUPPORT_SKE_TDES_128
	SKE_ALG_TDES_128       = 1,      // TDES 128 bits key
#endif

#ifdef SUPPORT_SKE_TDES_192
	SKE_ALG_TDES_192       = 2,      // TDES 192 bits key
#endif

#ifdef SUPPORT_SKE_TDES_EEE_128
	SKE_ALG_TDES_EEE_128   = 3,      // TDES_EEE 128 bits key
#endif

#ifdef SUPPORT_SKE_TDES_EEE_192
	SKE_ALG_TDES_EEE_192   = 4,      // TDES_EEE 192 bits key
#endif

#ifdef SUPPORT_SKE_AES_128
	SKE_ALG_AES_128        = 5,      // AES 128 bits key
#endif

#ifdef SUPPORT_SKE_AES_192
	SKE_ALG_AES_192        = 6,      // AES 192 bits key
#endif

#ifdef SUPPORT_SKE_AES_256
	SKE_ALG_AES_256        = 7,      // AES 256 bits key
#endif

#ifdef SUPPORT_SKE_SM4
	SKE_ALG_SM4            = 8,      // SM4
#endif
} SKE_ALG;


//SKE return code
enum SKE_RET_CODE
{
	SKE_SUCCESS = 0,
	SKE_BUFFER_NULL,
	SKE_CONFIG_INVALID,
	SKE_INPUT_INVALID,
	SKE_ATTACK_ALARM,
	SKE_ERROR,
};


//SKE padding scheme
typedef enum{
	SKE_NO_PADDING,
	SKE_ZERO_PADDING,
} SKE_PADDING;


//SKE block length
typedef struct{
	uint8_t block_bytes;
	uint8_t block_words;
} SKE_CTX;


//DMA_LL node
typedef struct{
	uint32_t src_addr;
	uint32_t dst_addr;
	uint32_t next_llp;
	uint32_t last_len;
} DMA_LL_node;



//hash callback function type
typedef void (*SKE_CALLBACK)(void);



//APIs

uint32_t ske_lp_get_version(void);

void ske_lp_set_cpu_mode(void);

void ske_lp_set_dma_mode(void);

void ske_lp_set_endian_uint32(void);

void ske_lp_set_crypto(SKE_CRYPTO crypto);

void ske_lp_set_alg(SKE_ALG ske_alg);

void ske_lp_set_mode(SKE_MODE mode);

void ske_lp_set_last_block(uint32_t is_last_block);

void ske_lp_set_last_block_len(uint32_t bytes);

void ske_lp_start(void);

uint32_t ske_lp_wait_till_done(void);

void ske_lp_set_key_uint32(uint32_t *key, uint32_t idx, uint32_t key_words);

void ske_lp_set_iv_uint32(uint32_t *iv, uint32_t block_words);

#if (defined(SUPPORT_SKE_MODE_GCM) || defined(SUPPORT_SKE_MODE_CCM))
void ske_lp_set_aad_len_uint32(uint32_t aad_bytes);
#endif

#if (defined(SUPPORT_SKE_MODE_GCM) || defined(SUPPORT_SKE_MODE_CCM) || defined(SUPPORT_SKE_MODE_XTS))
void ske_lp_set_c_len_uint32(uint32_t c_bytes);
#endif

void ske_lp_simple_set_input_block(uint32_t *in, uint32_t block_words);

void ske_lp_simple_get_output_block(uint32_t *out, uint32_t block_words);

uint32_t ske_lp_expand_key(uint32_t dma_en);

#ifdef SKE_LP_DMA_FUNCTION
uint32_t ske_lp_dma_calc_wait_till_done(SKE_CALLBACK callback);

uint32_t ske_lp_dma_operate(SKE_CTX *ctx, uint32_t *in, uint32_t *out, uint32_t in_words, uint32_t out_words,
		SKE_CALLBACK callback);

void clear_block_tail(uint32_t in[4], uint32_t bytes);
#endif

uint32_t ske_lp_update_blocks_no_output(SKE_CTX *ctx, uint8_t *in, uint32_t bytes);

uint32_t ske_lp_update_blocks_internal(SKE_CTX *ctx, uint8_t *in, uint8_t *out, uint32_t bytes);


#ifdef SUPPORT_SKE_MODE_GMAC
uint32_t ske_lp_gmac_update_blocks_internal(uint8_t *in, uint32_t bytes);
#endif

#if (defined(SUPPORT_SKE_TDES_128))
uint32_t tdes_ecb_update_one_block(uint32_t is_EEE, uint32_t key[6], SKE_CRYPTO crypto, uint32_t in[2], uint32_t out[2]);
#endif


#ifdef __cplusplus
}
#endif


#endif
