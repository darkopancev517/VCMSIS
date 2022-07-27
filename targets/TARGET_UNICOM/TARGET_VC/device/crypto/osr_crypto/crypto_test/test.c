#include <stdio.h>

#include "../crypto_hal/pke.h"
//#include "../crypto_include/trng.h"
//#include "../crypto_include/utility.h"


#include "test.h"








/*
void test(void)
{
	uint32_t *p;
	uint64_t a,b,c;

	p = (uint32_t *)&a;
	a=0x1122334455667788;
	b=0x1111111111111111;

	printf("\r\n %lx", a+b);   // 2233445566778899
	printf("\r\n %lx", a-b);   // 11223344556677
	printf("\r\n %08x %08x", *p, *(p+1));  // 55667788 11223344
	printf("\r\n %lx ", ((uint64_t)0x22334455)*0x11223344);  //249F93204851594

}
*/




uint32_t crypto_test(void)
{

	printf("PKE Version: %08x\n\r", PKE_VERSION);fflush(stdout);

//	hal_pke_basic_test();
//	pke_big_mod_little_test();
//	hal_pke_eccp_test();
//	hal_pke_mod_test();
//	hal_pke_x25519_test();
//	hal_pke_ed25519_test();

#if 0
	if(SKE_all_test())
		return 1;
#endif

#if 0
	if(HASH_all_test())
		return 1;
#endif

#if 0
	if(HMAC_all_test())
		return 1;
#endif

#if 0
	if(HASH_HMAC_sample_test())
		return 1;
#endif

#if 0
	if(SM2_all_test())
		return 1;
#endif

#if 0
	if(ECCp_get_curve_paras_test())
		return 1;
#endif

#if 0
	if(ECCp_get_key_all_test())
		return 1;
#endif

#if 0
	if(ECDH_all_test())
		return 1;
#endif

#if 1
	if(ECDSA_all_test())
		return 1;
#endif

#if 0
	if(RSA_all_test())
		return 1;
#endif

#if 0
	if(X25519_all_test())
		return 1;
#endif

#if 0
	if(Ed25519_all_test())
		return 1;
#endif

#if 0
	if(sm9_test())
		return 1;
#endif


	printf("\r\n TEST OVER \r\n");//fflush(stdout);
	return 0;
}

