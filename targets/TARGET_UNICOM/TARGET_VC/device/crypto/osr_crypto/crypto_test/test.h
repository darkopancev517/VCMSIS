#ifndef TEST_H
#define TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

uint32_t crypto_test(void);



uint32_t ECCp_get_curve_paras_test(void);

uint32_t ECCp_get_key_all_test(void);

uint32_t ECDH_all_test(void);

uint32_t ECDSA_all_test(void);

uint32_t RSA_all_test(void);

uint32_t SM2_all_test(void);

uint32_t SKE_all_test(void);

uint32_t HASH_all_test(void);

uint32_t HMAC_all_test(void);

uint32_t HASH_HMAC_sample_test(void);

uint32_t X25519_all_test(void);

uint32_t Ed25519_all_test(void);

uint32_t sm9_test(void);


#ifdef __cplusplus
}
#endif

#endif
