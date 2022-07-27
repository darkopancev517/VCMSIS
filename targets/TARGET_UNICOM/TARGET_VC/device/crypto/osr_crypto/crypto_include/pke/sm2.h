#ifndef SM2_H
#define SM2_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../crypto_hal/pke.h"
#include "../hash_hmac/hash.h"



//#define SM2_HIGH_SPEED        //only available for PKE_HP



//some sm2 length
#define SM2_BIT_LEN               (256)
#define SM2_BYTE_LEN              (32)
#define SM2_WORD_LEN              (8)
#define SM3_DIGEST_BYTE_LEN       SM2_BYTE_LEN
#define SM2_MAX_ID_BYTE_LEN       (1<<13)




//SM2 error code
enum SM2_RET_CODE
{
	SM2_SUCCESS = 0,
	SM2_BUFFER_NULL = PKE_SUCCESS+0x40,
	SM2_NOT_ON_CURVE,
	SM2_EXCHANGE_ROLE_INVALID,
	SM2_INPUT_INVALID,
	SM2_ZERO_ALL,
	SM2_INTEGER_TOO_BIG,
	SM2_VERIFY_FAILED,
	SM2_DECRYPT_VERIFY_FAILED
};


//SM2 key exchange role
typedef enum {
	SM2_Role_Sponsor = 0,
	SM2_Role_Responsor
} sm2_exchange_role_e;


// SM2 ciphertext order
typedef enum {
	SM2_C1C3C2   = 0,
	SM2_C1C2C3,
} sm2_cipher_order_e;



//APIs

uint32_t sm2_getZ(uint8_t *ID, uint32_t byteLenofID, uint8_t pubKey[65], uint8_t Z[32]);

uint32_t sm2_getE(uint8_t *M, uint32_t byteLen, uint8_t Z[32], uint8_t E[32]);

//#define SM2_GETE_BY_STEPS
#ifdef SM2_GETE_BY_STEPS
uint32_t sm2_getE_init(HASH_CTX *ctx, uint8_t Z[32]);

uint32_t sm2_getE_update(HASH_CTX *ctx, uint8_t *msg, uint32_t msg_bytes);

uint32_t sm2_getE_final(HASH_CTX *ctx, uint8_t E[32]);
#endif

uint32_t sm2_get_pubkey_from_prikey(uint8_t priKey[32], uint8_t pubKey[65]);

uint32_t sm2_getkey(uint8_t priKey[32], uint8_t pubKey[65]);

uint32_t sm2_sign(uint8_t E[32], uint8_t rand_k[32], uint8_t priKey[32], uint8_t signature[64]);

uint32_t sm2_verify(uint8_t E[32], uint8_t pubKey[65], uint8_t signature[64]);

uint32_t sm2_encrypt(uint8_t *M, uint32_t MByteLen, uint8_t rand_k[32], uint8_t pubKey[65],
		sm2_cipher_order_e order, uint8_t *C, uint32_t *CByteLen);

uint32_t sm2_decrypt(uint8_t *C, uint32_t CByteLen, uint8_t priKey[32],
		sm2_cipher_order_e order, uint8_t *M, uint32_t *MByteLen);

uint32_t sm2_exchangekey(sm2_exchange_role_e role,
						uint8_t *dA, uint8_t *PB,
						uint8_t *rA, uint8_t *RA,
						uint8_t *RB,
						uint8_t *ZA, uint8_t *ZB,
						uint32_t kByteLen,
						uint8_t *KA, uint8_t *S1, uint8_t *SA);


#ifdef PKE_SEC

#define SM2_SEC
#ifdef SM2_SEC

enum SM2_RET_CODE_S
{
	SM2_SUCCESS_S = 0x3E2FDB1A,
	SM2_ERROR_S = 0xCBAD735E
};

uint32_t sm2_sign_s(uint8_t E[32], uint8_t rand_k[32], uint8_t priKey[32], uint8_t signature[64]);

uint32_t sm2_verify_s(uint8_t E[32], uint8_t pubKey[65], uint8_t signature[64]);

uint32_t sm2_encrypt_s(uint8_t *M, uint32_t MByteLen, uint8_t rand_k[32], uint8_t pubKey[65],
		sm2_cipher_order_e order, uint8_t *C, uint32_t *CByteLen);

uint32_t sm2_decrypt_s(uint8_t *C, uint32_t CByteLen, uint8_t priKey[32],
		sm2_cipher_order_e order, uint8_t *M, uint32_t *MByteLen);

uint32_t sm2_exchangekey_s(sm2_exchange_role_e role,
						uint8_t *dA, uint8_t *PB,
						uint8_t *rA, uint8_t *RA,
						uint8_t *RB,
						uint8_t *ZA, uint8_t *ZB,
						uint32_t kByteLen,
						uint8_t *KA, uint8_t *S1, uint8_t *SA);

#endif
#endif


#ifdef __cplusplus
}
#endif

#endif
