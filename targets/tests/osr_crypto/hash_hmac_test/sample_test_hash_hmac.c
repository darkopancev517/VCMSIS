#include <stdio.h>
#include <stdint.h>
#include "../../crypto_include/hash_hmac/hash.h"


uint32_t sample_test_sm3(void);
uint32_t sample_test_hmac_sm3(void);
uint32_t sample_test_md5(void);
uint32_t sample_test_hmac_md5(void);
uint32_t sample_test_sha256(void);
uint32_t sample_test_hmac_sha256(void);
uint32_t sample_test_sha384(void);
uint32_t sample_test_hmac_sha384(void);
uint32_t sample_test_sha512(void);
uint32_t sample_test_hmac_sha512(void);
uint32_t sample_test_sha1(void);
uint32_t sample_test_hmac_sha1(void);
uint32_t sample_test_sha224(void);
uint32_t sample_test_hmac_sha224(void);
uint32_t sample_test_sha512_224(void);
uint32_t sample_test_hmac_sha512_224(void);
uint32_t sample_test_sha512_256(void);
uint32_t sample_test_hmac_sha512_256(void);


uint32_t HASH_HMAC_sample_test(void)
{
	printf("\r\n\r\n\r\n =================== HASH HMAC sample test =================== ");


#ifdef SUPPORT_HASH_SM3
	if(sample_test_sm3())
		return 1;

	if(sample_test_hmac_sm3())
		return 1;
#endif

#ifdef SUPPORT_HASH_MD5
	if(sample_test_md5())
		return 1;

	if(sample_test_hmac_md5())
		return 1;
#endif

#ifdef SUPPORT_HASH_SHA256
	if(sample_test_sha256())
		return 1;

	if(sample_test_hmac_sha256())
		return 1;
#endif

#ifdef SUPPORT_HASH_SHA384
	if(sample_test_sha384())
		return 1;

	if(sample_test_hmac_sha384())
		return 1;
#endif

#ifdef SUPPORT_HASH_SHA512
	if(sample_test_sha512())
		return 1;

	if(sample_test_hmac_sha512())
		return 1;
#endif

#ifdef SUPPORT_HASH_SHA1
	if(sample_test_sha1())
		return 1;

	if(sample_test_hmac_sha1())
		return 1;
#endif

#ifdef SUPPORT_HASH_SHA224
	if(sample_test_sha224())
		return 1;

	if(sample_test_hmac_sha224())
		return 1;
#endif

#ifdef SUPPORT_HASH_SHA512_224
	if(sample_test_sha512_224())
		return 1;

	if(sample_test_hmac_sha512_224())
		return 1;
#endif

#ifdef SUPPORT_HASH_SHA512_256
	if(sample_test_sha512_256())
		return 1;

	if(sample_test_hmac_sha512_256())
		return 1;
#endif

	printf("\r\n\r\n HASH HMAC sample test success \r\n\r\n");fflush(stdout);

	return 0;
}





