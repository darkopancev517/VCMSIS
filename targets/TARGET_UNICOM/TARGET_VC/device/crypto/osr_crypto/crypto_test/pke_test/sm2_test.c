#include <stdio.h>

#include "../../crypto_include/utility.h"
#include "../../crypto_include/pke/sm2.h"
#include "../../crypto_include/trng.h"

// NOTE: skipped SM2 random test until TRNG has been fixed
#define SM2_RANDOM_TEST 0


#ifdef SUPPORT_SM2


#define SM2_SPEED_TEST_KEYGET_ROUND    (1000)
#define SM2_SPEED_TEST_SIGN_ROUND      (1000)
#define SM2_SPEED_TEST_VERIFY_ROUND    (800)

#define SM2_SPEED_TEST_PLAIN_BYTE_LEN  (32)   //明文字节长度
#define SM2_SPEED_TEST_ENCRYPT_ROUND   (800)
#define SM2_SPEED_TEST_DECRYPT_ROUND   (1000)
#define SM2_SPEED_TEST_EXCHANGE_ROUND  (800)


#define SM2_SIGN_VERIFY_ROUND1         2
#define SM2_ENCRYPT_DECRYPT_ROUND1     2
#define SM2_KEY_EXCHANGE_ROUND1        2

#define SM2_EXCHANGE_MAX_LEN           (200)

extern const eccp_curve_t sm2_curve[1];

extern uint32_t get_systick_micros(void);

void SM2_keyget_speed_test(void)
{
	uint8_t prikey[32];
	uint8_t pubkey[65];
	uint32_t i=0;
	uint32_t ret;

	//speed test
	printf("\r\n keyget begin");fflush(stdout);
	for(i=0;i<SM2_SPEED_TEST_KEYGET_ROUND;i++)
	{
		ret = sm2_getkey(prikey, pubkey);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n sm2 get key failure, ret=%lx", ret);
			return;
		}
	}
	printf("\r\n keyget finished");fflush(stdout);
}


void SM2_sign_speed_test(void)
{
	uint8_t prikey[32];
	uint8_t pubkey[65];
	uint8_t	E[32]={
		0xDD,0x9E,0xB8,0x55,0xA7,0x18,0x37,0xB3,0x2F,0x93,0x5A,0x3D,0x37,0x81,0x80,0xDD,
		0xB9,0xD2,0x9C,0x7F,0x5A,0x83,0x30,0x36,0x1F,0xE8,0x08,0xD7,0xAA,0x3A,0x1E,0x00,};
	uint8_t signature[64];
	uint32_t i=0;
	uint32_t ret;

	//a small loop for sleeping
	for(i=0;i<30;i++)
	{
		ret = sm2_getkey(prikey, pubkey);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n sm2 get key failure, ret=%lx", ret);
			return;
		}
	}

	//speed test
	printf("\r\n sign begin");fflush(stdout);
	for(i=0;i<SM2_SPEED_TEST_SIGN_ROUND;i++)
	{
		ret = sm2_sign(E, NULL, prikey, signature);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n sm2 sign test failure, ret=%lx", ret);
		}
	}
	printf("\r\n sign finished");fflush(stdout);
}

void SM2_verify_speed_test(void)
{
	uint8_t prikey[32];
	uint8_t pubkey[65];
	uint8_t	E[32]={
		0xDD,0x9E,0xB8,0x55,0xA7,0x18,0x37,0xB3,0x2F,0x93,0x5A,0x3D,0x37,0x81,0x80,0xDD,
		0xB9,0xD2,0x9C,0x7F,0x5A,0x83,0x30,0x36,0x1F,0xE8,0x08,0xD7,0xAA,0x3A,0x1E,0x00,};
	uint8_t signature[64];
	uint32_t i=0;
	uint32_t ret;

	//a small loop for sleeping
	for(i=0;i<30;i++)
	{
		ret = sm2_getkey(prikey, pubkey);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n sm2 get key failure, ret=%lx", ret);
			return;
		}
	}

	ret = sm2_sign(E, NULL, prikey, signature);
	if(SM2_SUCCESS != ret)
	{
		printf("\r\n sm2 sign test failure, ret=%lx", ret);
		return;
	}

	//speed test
	printf("\r\n verify begin");fflush(stdout);
	for(i=0;i<SM2_SPEED_TEST_VERIFY_ROUND;i++)
	{
		ret = sm2_verify(E, pubkey, signature);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n sm2 verify test failure, ret=%lx", ret);
		}
	}
	printf("\r\n verify finished");fflush(stdout);
}

void SM2_encrypt_speed_test(void)
{
	uint8_t prikey[32];
	uint8_t pubkey[65];
	uint8_t	plain[SM2_SPEED_TEST_PLAIN_BYTE_LEN];
	uint8_t cipher[SM2_SPEED_TEST_PLAIN_BYTE_LEN+97];
	uint32_t bytelen, i=0;
	uint32_t ret;

	//a small loop for sleeping
	for(i=0;i<30;i++)
	{
		ret = sm2_getkey(prikey, pubkey);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n sm2 get key failure, ret=%lx", ret);
			return;
		}
	}

	//speed test
	printf("\r\n encrypt begin");fflush(stdout);
	for(i=0;i<SM2_SPEED_TEST_ENCRYPT_ROUND;i++)
	{
		ret = sm2_encrypt(plain, SM2_SPEED_TEST_PLAIN_BYTE_LEN, NULL, pubkey, 0, cipher, &bytelen);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n encrypt failure");
		}
	}
	printf("\r\n encrypt finished");fflush(stdout);
}

void SM2_decrypt_speed_test(void)
{
	uint8_t prikey[32];
	uint8_t pubkey[65];
	uint8_t	plain[SM2_SPEED_TEST_PLAIN_BYTE_LEN];
	uint8_t cipher[SM2_SPEED_TEST_PLAIN_BYTE_LEN+97];
	uint8_t	replain[SM2_SPEED_TEST_PLAIN_BYTE_LEN];
	uint32_t bytelen, bytelen2, i=0;
	uint32_t ret;

	//a small loop for sleeping
	for(i=0;i<30;i++)
	{
		ret = sm2_getkey(prikey, pubkey);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n sm2 get key failure, ret=%lx", ret);
			return;
		}
	}
	ret = sm2_encrypt(plain, SM2_SPEED_TEST_PLAIN_BYTE_LEN, NULL, pubkey, 0, cipher, &bytelen);
	if(SM2_SUCCESS != ret)
	{
		printf("\r\n encrypt failure");
	}

	//speed test
	printf("\r\n decrypt begin");fflush(stdout);
	for(i=0;i<SM2_SPEED_TEST_DECRYPT_ROUND;i++)
	{
		ret = sm2_decrypt(cipher, bytelen, prikey, 0, replain, &bytelen2);
		if(SM2_SUCCESS != ret)// || (SM2_SPEED_TEST_PLAIN_BYTE_LEN != bytelen2)|| memcmp_(plain, replain, bytelen))
		{
			printf("\r\n decrypt failure");
		}
	}
	printf("\r\n decrypt finished");fflush(stdout);
}


void SM2_exchange_speed_test(void)
{
	uint8_t ZA[32], ZB[32], KA[32], KB[32], S1[32], SA[32], S2[32], SB[32];
	uint8_t PA[65];//A的公钥
	uint8_t RA[65];//A的临时公钥
	uint8_t dA[32];//A的私钥
	uint8_t rA[32];//A的临时私钥
	uint8_t PB[65];//B的公钥
	uint8_t RB[65];//B的临时公钥
	uint8_t dB[32];//B的私钥
	uint8_t rB[32];//B的临时私钥
	uint32_t i=0;
	uint32_t ret;

	//random key exchange test
	//a small loop for sleeping
	for(i=0;i<5;i++)
	{
		ret = sm2_getkey(dA, PA);
		ret |= sm2_getkey(rA, RA);
		ret |= sm2_getkey(dB, PB);
		ret |= sm2_getkey(rB, RB);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n get key failure");
			return;
		}
	}

	memset_(KA, 0x11, 16);
	memset_(KB, 0x55, 16);
	memset_(S1, 0x11, 32);
	memset_(S2, 0x55, 32);
	memset_(SA, 0x11, 32);
	memset_(SB, 0x55, 32);

	//speed test
	printf("\r\n exchange begin");fflush(stdout);
	for(i=0;i<SM2_SPEED_TEST_EXCHANGE_ROUND;i++)
	{
		ret = sm2_exchangekey(SM2_Role_Sponsor,
						dA, PB,
						rA, RA,
						RB,
						ZA, ZB,
						16,
						KA, S1, SA);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n SM2 key exchange test error. ret=%02lx", ret);
		}
	}
	printf("\r\n exchange finished");fflush(stdout);

	ret |= sm2_exchangekey(SM2_Role_Responsor,
					dB, PA,
					rB, RB,
					RA,
					ZB, ZA,
					16,
					KB, S2, SB);
	if((SM2_SUCCESS != ret) || memcmp_(KA, KB, 16) || memcmp_(S1, SB, 32) ||  memcmp_(S2, SA, 32))
	{
		printf("\r\n SM2 key exchange test error. ret=%02lx", ret);
		print_buf_U8(KA, 16, "KA");
		print_buf_U8(S1, 32, "S1");
		print_buf_U8(SA, 32, "SA");
		print_buf_U8(KB, 16, "KB");
		print_buf_U8(S2, 32, "S2");
		print_buf_U8(SB, 32, "SB");
	}
}





uint32_t sm2_get_key_test_internal(uint8_t *prikey, uint8_t *pubkey, uint32_t ret_value, char *info)
{
	uint8_t buf[65]={0};
	uint32_t ret;
    uint32_t start = 0;
    uint32_t duration = 0;

    start = get_systick_micros();
	ret = sm2_get_pubkey_from_prikey(prikey, buf);
    duration = get_systick_micros() - start;

	if((ret_value != ret))
	{
		printf("\r\n SM2 get key %s failure 1, ret=%lu", info, ret);fflush(stdout);
		return 1;
	}

	if((SM2_SUCCESS == ret) && memcmp_(buf, pubkey, 65))
	{
		printf("\r\n SM2 get key %s failure 2, ret=%lu", info, ret);fflush(stdout);
		return 1;
	}

	printf("\r\n SM2 get key %s success, duration: %lu us", info, duration);fflush(stdout);

	return 0;
}

uint32_t sm2_get_key_test(void)
{
	//standard private key and public key
	uint8_t prikey[32]={
		0x39,0x45,0x20,0x8F,0x7B,0x21,0x44,0xB1,0x3F,0x36,0xE3,0x8A,0xC6,0xD3,0x9F,0x95,
		0x88,0x93,0x93,0x69,0x28,0x60,0xB5,0x1A,0x42,0xFB,0x81,0xEF,0x4D,0xF7,0xC5,0xB8,
	};
	uint8_t pubkey[65]={
		0x04,0x09,0xF9,0xDF,0x31,0x1E,0x54,0x21,0xA1,0x50,0xDD,0x7D,0x16,0x1E,0x4B,0xC5,
		0xC6,0x72,0x17,0x9F,0xAD,0x18,0x33,0xFC,0x07,0x6B,0xB0,0x8F,0xF3,0x56,0xF3,0x50,
		0x20,0xCC,0xEA,0x49,0x0C,0xE2,0x67,0x75,0xA5,0x2D,0xC6,0xEA,0x71,0x8C,0xC1,0xAA,
		0x60,0x0A,0xED,0x05,0xFB,0xF3,0x5E,0x08,0x4A,0x66,0x32,0xF6,0x07,0x2D,0xA9,0xAD,
		0x13,
	};

	//public key for the case private key is 1
	uint8_t pubkey_1[65]={
		0x04,0x32,0xC4,0xAE,0x2C,0x1F,0x19,0x81,0x19,0x5F,0x99,0x04,0x46,0x6A,0x39,0xC9,
		0x94,0x8F,0xE3,0x0B,0xBF,0xF2,0x66,0x0B,0xE1,0x71,0x5A,0x45,0x89,0x33,0x4C,0x74,
		0xC7,0xBC,0x37,0x36,0xA2,0xF4,0xF6,0x77,0x9C,0x59,0xBD,0xCE,0xE3,0x6B,0x69,0x21,
		0x53,0xD0,0xA9,0x87,0x7C,0xC6,0x2A,0x47,0x40,0x02,0xDF,0x32,0xE5,0x21,0x39,0xF0,
		0xA0,
	};

	//public key for the case private key is 2
	uint8_t pubkey_2[65]={
		0x04,0x56,0xCE,0xFD,0x60,0xD7,0xC8,0x7C,0x00,0x0D,0x58,0xEF,0x57,0xFA,0x73,0xBA,
		0x4D,0x9C,0x0D,0xFA,0x08,0xC0,0x8A,0x73,0x31,0x49,0x5C,0x2E,0x1D,0xA3,0xF2,0xBD,
		0x52,0x31,0xB7,0xE7,0xE6,0xCC,0x81,0x89,0xF6,0x68,0x53,0x5C,0xE0,0xF8,0xEA,0xF1,
		0xBD,0x6D,0xE8,0x4C,0x18,0x2F,0x6C,0x8E,0x71,0x6F,0x78,0x0D,0x3A,0x97,0x0A,0x23,
		0xC3,
	};

	//public key for the case private key is n-2
	uint8_t pubkey_n_minus_2[65]={
		0x04,0x56,0xCE,0xFD,0x60,0xD7,0xC8,0x7C,0x00,0x0D,0x58,0xEF,0x57,0xFA,0x73,0xBA,
		0x4D,0x9C,0x0D,0xFA,0x08,0xC0,0x8A,0x73,0x31,0x49,0x5C,0x2E,0x1D,0xA3,0xF2,0xBD,
		0x52,0xCE,0x48,0x18,0x18,0x33,0x7E,0x76,0x09,0x97,0xAC,0xA3,0x1F,0x07,0x15,0x0E,
		0x42,0x92,0x17,0xB3,0xE6,0xD0,0x93,0x71,0x8F,0x90,0x87,0xF2,0xC5,0x68,0xF5,0xDC,
		0x3C,
	};

	printf("\r\n -------------- SM2 get key test -------------- ");fflush(stdout);

	/********** sm2 get key standard data test **********/
	if(sm2_get_key_test_internal(prikey, pubkey, SM2_SUCCESS, "standard data test"))
		return 1;

	/********** prikey is 0 **********/
	memset_(prikey, 0, 32);
	if(sm2_get_key_test_internal(prikey, NULL, PKE_ZERO_ALL, "test(prikey=0)"))
		return 1;

	/********** prikey is 1 **********/
	memset_(prikey, 0, 32);
	prikey[31]=1;
	if(sm2_get_key_test_internal(prikey, pubkey_1, SM2_SUCCESS, "test(prikey=1)"))
		return 1;

	/********** prikey is 2 **********/
	memset_(prikey, 0, 32);
	prikey[31]=2;
	if(sm2_get_key_test_internal(prikey, pubkey_2, SM2_SUCCESS, "test(prikey=2)"))
		return 1;

	/********** prikey is n-2 **********/
	reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), prikey, 32);
	prikey[31]-=2;
	if(sm2_get_key_test_internal(prikey, pubkey_n_minus_2, SM2_SUCCESS, "test(prikey=n-2)"))
		return 1;

	/********** prikey is n-1 **********/
	reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), prikey, 32);
	prikey[31]-=1;
	if(sm2_get_key_test_internal(prikey, NULL, PKE_INTEGER_TOO_BIG, "test(prikey=n-1)"))
		return 1;

	/********** prikey is n **********/
	reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), prikey, 32);
	if(sm2_get_key_test_internal(prikey, NULL, PKE_INTEGER_TOO_BIG, "test(prikey=n)"))
		return 1;

	/********** prikey is n+1 **********/
	reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), prikey, 32);
	prikey[31]+=1;
	if(sm2_get_key_test_internal(prikey, NULL, PKE_INTEGER_TOO_BIG, "test(prikey=n+1)"))
	{
		return 1;
	}
	else
	{
		printf("\r\n");
		return 0;
	}
}


uint32_t sm2_sign_verify_test_internal(uint8_t *E, uint8_t *prikey, uint8_t *rand_k, uint8_t *pubkey,
									  uint8_t *signature, uint32_t sign_ret_value, char *info)
{
	uint8_t buf[64];
	uint8_t tmp[65];
	uint32_t ret;
	char *inf="";
    uint32_t start = 0;
    uint32_t duration = 0;

	if(info)
		inf=info;

    start = get_systick_micros();

	ret = sm2_sign(E, rand_k, prikey, buf);

	if((sign_ret_value != ret))
	{
		printf("\r\n SM2 sign %s failure, ret=%08lx", inf, ret);
		return 1;
	}

	if(SM2_SUCCESS == ret)
	{
		if((NULL != rand_k) && (NULL != signature))
		{
			if(memcmp_(buf, signature, 64))
			{
				printf("\r\n SM2 sign %s failure, ret=%08lx", inf, ret);
				print_buf_U8(buf, 64, "signature");
				return 1;
			}
		}

		ret = sm2_verify(E, pubkey, buf);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n SM2 verify %s failure, ret=%lx", inf, ret);
			print_buf_U8(buf, 64, "signature");
			return 1;
		}

		//invalid E
		memcpy_(tmp, E, 32);
		tmp[0]+=3;
		ret = sm2_verify(tmp, pubkey, buf);
		if(SM2_VERIFY_FAILED != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid E), ret=%lx", inf, ret);
			return 1;
		}

		//invalid pubkey test 1
		memcpy_(tmp, pubkey, 65);
		tmp[0]+=3;
		ret = sm2_verify(E, tmp, buf);
		if(SM2_INPUT_INVALID != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid public key 1), ret=%lx", inf, ret);
			return 1;
		}

		//invalid pubkey test 2
		memcpy_(tmp, pubkey, 65);
		tmp[1]+=3;
		ret = sm2_verify(E, tmp, buf);
		if(SM2_NOT_ON_CURVE != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid public key 2), ret=%lx", inf, ret);
			return 1;
		}

		//invalid pubkey test 3
		memcpy_(tmp, pubkey, 65);
		tmp[64]+=3;
		ret = sm2_verify(E, tmp, buf);
		if(SM2_NOT_ON_CURVE != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid public key 3), ret=%lx", inf, ret);
			return 1;
		}

		//invalid signature test 1(corrupted r)
		memcpy_(tmp, buf, 64);
		tmp[0]+=3;
		ret = sm2_verify(E, pubkey, tmp);
		if((SM2_VERIFY_FAILED != ret) && (SM2_INTEGER_TOO_BIG != ret))
		{
			printf("\r\n SM2 verify %s failure(invalid signature: corrupted r), ret=%lx", inf, ret);
			return 1;
		}

		//invalid signature test 2(r=0)
		memcpy_(tmp, buf, 64);
		memset_(tmp, 0, 32);
		ret = sm2_verify(E, pubkey, tmp);
		if(SM2_ZERO_ALL != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid signature: r=0), ret=%lx", inf, ret);
			return 1;
		}

		//invalid signature test 3(r=n-1)
		memcpy_(tmp, buf, 64);
		reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), tmp, 32);
		tmp[31]-=1;
		ret = sm2_verify(E, pubkey, tmp);
		if(SM2_VERIFY_FAILED != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid signature: r=n-1), ret=%lx", inf, ret);
			return 1;
		}

		//invalid signature test 4(r=n)
		memcpy_(tmp, buf, 64);
		reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), tmp, 32);
		ret = sm2_verify(E, pubkey, tmp);
		if(SM2_INTEGER_TOO_BIG != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid signature: r=n), ret=%lx", inf, ret);
			return 1;
		}

		//invalid signature test 5(r=n+1)
		memcpy_(tmp, buf, 64);
		reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), tmp, 32);
		tmp[31]+=1;
		ret = sm2_verify(E, pubkey, tmp);
		if(SM2_INTEGER_TOO_BIG != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid signature: r=n+1), ret=%lx", inf, ret);
			return 1;
		}

		//invalid signature test 6(corrupted s)
		memcpy_(tmp, buf, 64);
		tmp[63]+=3;
		ret = sm2_verify(E, pubkey, tmp);
		if(SM2_VERIFY_FAILED != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid signature: corrupted s), ret=%lx", inf, ret);
			return 1;
		}

		//invalid signature test 7(s=0)
		memcpy_(tmp, buf, 64);
		memset_(tmp+32, 0, 32);
		ret = sm2_verify(E, pubkey, tmp);
		if(SM2_ZERO_ALL != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid signature: s=0), ret=%lx", inf, ret);
			return 1;
		}

		//invalid signature test 8(s=n-1)
		memcpy_(tmp, buf, 64);
		reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), tmp+32, 32);
		tmp[63]-=1;
		ret = sm2_verify(E, pubkey, tmp);
		if(SM2_VERIFY_FAILED != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid signature: s=n-1), ret=%lx", inf, ret);
			return 1;
		}

		//invalid signature test 9(s=n)
		memcpy_(tmp, buf, 64);
		reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), tmp+32, 32);
		ret = sm2_verify(E, pubkey, tmp);
		if(SM2_INTEGER_TOO_BIG != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid signature: s=n), ret=%lx", inf, ret);
			return 1;
		}

		//invalid signature test 10(s=n+1)
		memcpy_(tmp, buf, 64);
		reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), tmp+32, 32);
		tmp[63]+=1;
		ret = sm2_verify(E, pubkey, tmp);
		if(SM2_INTEGER_TOO_BIG != ret)
		{
			printf("\r\n SM2 verify %s failure(invalid signature: r=n+1), ret=%lx", inf, ret);
			return 1;
		}
	}

    duration = get_systick_micros() - start;

	if(NULL != info)
		printf("\r\n SM2 sign & verify %s success, duration: %lu us", inf, duration);

	return 0;
}


uint32_t sm2_sign_verify_test(void)
{
	uint8_t prikey[32]={
		0x39,0x45,0x20,0x8F,0x7B,0x21,0x44,0xB1,0x3F,0x36,0xE3,0x8A,0xC6,0xD3,0x9F,0x95,
		0x88,0x93,0x93,0x69,0x28,0x60,0xB5,0x1A,0x42,0xFB,0x81,0xEF,0x4D,0xF7,0xC5,0xB8,
	};
	uint8_t pubkey[65]={
		0x04,0x09,0xF9,0xDF,0x31,0x1E,0x54,0x21,0xA1,0x50,0xDD,0x7D,0x16,0x1E,0x4B,0xC5,
		0xC6,0x72,0x17,0x9F,0xAD,0x18,0x33,0xFC,0x07,0x6B,0xB0,0x8F,0xF3,0x56,0xF3,0x50,
		0x20,0xCC,0xEA,0x49,0x0C,0xE2,0x67,0x75,0xA5,0x2D,0xC6,0xEA,0x71,0x8C,0xC1,0xAA,
		0x60,0x0A,0xED,0x05,0xFB,0xF3,0x5E,0x08,0x4A,0x66,0x32,0xF6,0x07,0x2D,0xA9,0xAD,
		0x13,
	};
	uint8_t rand_k[32]={
		0x59,0x27,0x6E,0x27,0xD5,0x06,0x86,0x1A,0x16,0x68,0x0F,0x3A,0xD9,0xC0,0x2D,0xCC,
		0xEF,0x3C,0xC1,0xFA,0x3C,0xDB,0xE4,0xCE,0x6D,0x54,0xB8,0x0D,0xEA,0xC1,0xBC,0x21,
	};
	//"message digest"
	uint8_t msg[100] = {
		0x6D,0x65,0x73,0x73,0x61,0x67,0x65,0x20,0x64,0x69,0x67,0x65,0x73,0x74};
	//"1234567812345678"
	uint8_t id[16] = {
		0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
	uint8_t	std_Z[]={
		0xB2,0xE1,0x4C,0x5C,0x79,0xC6,0xDF,0x5B,0x85,0xF4,0xFE,0x7E,0xD8,0xDB,0x7A,0x26,
		0x2B,0x9D,0xA7,0xE0,0x7C,0xCB,0x0E,0xA9,0xF4,0x74,0x7B,0x8C,0xCD,0xA8,0xA4,0xF3,};
	uint8_t	std_E[]={
		0xF0,0xB4,0x3E,0x94,0xBA,0x45,0xAC,0xCA,0xAC,0xE6,0x92,0xED,0x53,0x43,0x82,0xEB,
		0x17,0xE6,0xAB,0x5A,0x19,0xCE,0x7B,0x31,0xF4,0x48,0x6F,0xDF,0xC0,0xD2,0x86,0x40,};
	uint8_t	std_signature[64]={
		0xF5,0xA0,0x3B,0x06,0x48,0xD2,0xC4,0x63,0x0E,0xEA,0xC5,0x13,0xE1,0xBB,0x81,0xA1,
		0x59,0x44,0xDA,0x38,0x27,0xD5,0xB7,0x41,0x43,0xAC,0x7E,0xAC,0xEE,0xE7,0x20,0xB3,
		0xB1,0xB6,0xAA,0x29,0xDF,0x21,0x2F,0xD8,0x76,0x31,0x82,0xBC,0x0D,0x42,0x1C,0xA1,
		0xBB,0x90,0x38,0xFD,0x1F,0x7F,0x42,0xD4,0x84,0x0B,0x69,0xC4,0x85,0xBB,0xC1,0xAA,};

#if SM2_RANDOM_TEST
	uint8_t	*k;
#endif

	uint8_t	Z[32],E[32];

	//e=0
	uint8_t signature_e_0[64] = {
		0x04,0xEB,0xFC,0x71,0x8E,0x8D,0x17,0x98,0x62,0x04,0x32,0x26,0x8E,0x77,0xFE,0xB6,
		0x41,0x5E,0x2E,0xDE,0x0E,0x07,0x3C,0x0F,0x4F,0x64,0x0E,0xCD,0x2E,0x14,0x9A,0x73,
		0x74,0x0F,0x49,0x4C,0x6B,0x9D,0xCC,0xA0,0x75,0x8F,0xD4,0xCF,0x0E,0xAA,0x8B,0xA8,
		0xCD,0x76,0xE9,0xB7,0xE4,0xFD,0x91,0x6F,0x7C,0x48,0x41,0x68,0xF6,0xA4,0xB3,0x8F};

	//e=1
	uint8_t signature_e_1[64] = {
		0x04,0xEB,0xFC,0x71,0x8E,0x8D,0x17,0x98,0x62,0x04,0x32,0x26,0x8E,0x77,0xFE,0xB6,
		0x41,0x5E,0x2E,0xDE,0x0E,0x07,0x3C,0x0F,0x4F,0x64,0x0E,0xCD,0x2E,0x14,0x9A,0x74,
		0xC2,0x0D,0xE6,0xE8,0x8A,0xF6,0xCE,0x75,0x5C,0x85,0x63,0x1D,0xD2,0x7A,0xD1,0x10,
		0x4F,0xA4,0x0F,0x08,0xDE,0xB6,0x1F,0xF1,0xE9,0x63,0x9C,0xA3,0xB0,0x71,0xC3,0x6E};

	//e=n
	uint8_t signature_e_n[64] = {
		0x04,0xEB,0xFC,0x71,0x8E,0x8D,0x17,0x98,0x62,0x04,0x32,0x26,0x8E,0x77,0xFE,0xB6,
		0x41,0x5E,0x2E,0xDE,0x0E,0x07,0x3C,0x0F,0x4F,0x64,0x0E,0xCD,0x2E,0x14,0x9A,0x73,
		0x74,0x0F,0x49,0x4C,0x6B,0x9D,0xCC,0xA0,0x75,0x8F,0xD4,0xCF,0x0E,0xAA,0x8B,0xA8,
		0xCD,0x76,0xE9,0xB7,0xE4,0xFD,0x91,0x6F,0x7C,0x48,0x41,0x68,0xF6,0xA4,0xB3,0x8F};

	//e=0xFFF...FFF
	uint8_t signature_e_FF[64] = {
		0x04,0xEB,0xFC,0x72,0x8E,0x8D,0x17,0x98,0x62,0x04,0x32,0x26,0x8E,0x77,0xFE,0xB6,
		0xCF,0x5A,0x4F,0x72,0xEC,0x41,0x36,0xE3,0xFB,0xA8,0x1A,0xC3,0xF4,0x3F,0x59,0x4F,
		0xC8,0x26,0x83,0x8A,0x13,0x67,0x62,0xB3,0x6B,0xD9,0x88,0xEF,0xC2,0xC6,0x5E,0x76,
		0xEB,0xE3,0x77,0x4C,0xD3,0xE8,0x08,0x1F,0xE1,0xAA,0x0A,0x76,0x14,0x30,0xAB,0x2C};

#if SM2_RANDOM_TEST
	uint32_t i,j;
#endif

	uint32_t ret;
#ifdef SM2_GETE_BY_STEPS
	HASH_CTX ctx[1];
#endif

    uint32_t start = 0;
    uint32_t duration = 0;

	printf("\r\n -------------- SM2 get Z, E, key, sign and verify test -------------- ");


	/********** sm2 get Z standard data test **********/
    start = get_systick_micros();
	ret = sm2_getZ(id, 16, pubkey, Z);
    duration = get_systick_micros() - start;

	if(SM2_SUCCESS != ret || memcmp_(Z, std_Z, 32))
	{
		printf("\r\n SM2 get Z standard data test failure, ret=%lx", ret);
		return 1;
	}
	else
	{
		printf("\r\n SM2 get Z standard data test success, duration: %lu us", duration);
	}

	/********** sm2 get E standard data test **********/
    start = get_systick_micros();
	ret = sm2_getE(msg, 14, Z, E);
    duration = get_systick_micros() - start;

	if(SM2_SUCCESS != ret || memcmp_(E, std_E, 32))
	{
		printf("\r\n SM2 get E standard data test failure, ret=%lx", ret);
	}
	else
	{
		printf("\r\n SM2 get E standard data test success, duration: %lu us", duration);
	}

#ifdef SM2_GETE_BY_STEPS
	memset_(E, 0, 32);
	ret = sm2_getE_init(ctx, Z);
	ret |= sm2_getE_update(ctx, msg, 1);
	ret |= sm2_getE_update(ctx, msg+1, 3);
	ret |= sm2_getE_update(ctx, msg+4, 5);
	ret |= sm2_getE_update(ctx, msg+9, 3);
	ret |= sm2_getE_update(ctx, msg+12, 2);
	ret |= sm2_getE_final(ctx, E);
	if(SM2_SUCCESS != ret || memcmp_(E, std_E, 32))
	{
		printf("\r\n SM2 get E standard data stepwise test failure, ret=%lx", ret);
	}
	else
	{
		printf("\r\n SM2 get E standard data stepwise test success");
	}
#endif

	/********** sm2 sign & verify standard data test **********/
	if(sm2_sign_verify_test_internal(std_E, prikey, rand_k, pubkey, std_signature, SM2_SUCCESS, "standard data test"))
		return 1;


	/********** e = 0 **********/
	memset_(E, 0, 32);
	if(sm2_sign_verify_test_internal(E, prikey, rand_k, pubkey, signature_e_0, SM2_SUCCESS, "test(e=0)"))
		return 1;

	/********** e = 1 **********/
	memset_(E, 0, 32);
	E[31]=1;
	if(sm2_sign_verify_test_internal(E, prikey, rand_k, pubkey, signature_e_1, SM2_SUCCESS, "test(e=1)"))
		return 1;

	/********** e = n **********/
	reverse_byte_array((uint8_t *)(sm2_curve->eccp_n), E, 32);
	if(sm2_sign_verify_test_internal(E, prikey, rand_k, pubkey, signature_e_n, SM2_SUCCESS, "test(e=n)"))
		return 1;

	/********** e = 0xFF...FF **********/
	memset_(E, 0xFF, 32);
	if(sm2_sign_verify_test_internal(E, prikey, rand_k, pubkey, signature_e_FF, SM2_SUCCESS, "test(e=0xFF...FF)"))
		return 1;


#if SM2_RANDOM_TEST
	/********* sm2 get key, sign, verify random test **********/
	printf("\r\n\r\n SM2 sign & verify random data test: \r\n");

	for(i=0;i<SM2_SIGN_VERIFY_ROUND1;i++)
	{
		//random E
		ret = get_rand(E, 32);
		if(TRNG_SUCCESS != ret)
		{
			printf("\r\n get rand error 1, ret = %02lx", ret);
			return 1;
		}

		//random key pair
		memset_(prikey,0,32);
		memset_(pubkey,0,65);
		ret = sm2_getkey(prikey, pubkey);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n sm2 get key failure, ret=%lx", ret);
			return 1;
		}
		//random k
		if(prikey[0]>0x80)
		{
			k=NULL;
		}
		else
		{
			k=rand_k;
			ret = get_rand(k, 32);
			if(TRNG_SUCCESS != ret)
			{
				printf("\r\n get rand error 2, ret = %02lx", ret);
				return 1;
			}
			k[0] = 0x7F;  //make sure k < n
		}

		for(j=0;j<50;j++)
		{
			printf("\r\n SM2 sign & verify round1=%lu, round2=%lu", i+1, j+1);

			if(sm2_sign_verify_test_internal(E, prikey, k, pubkey, NULL, SM2_SUCCESS, NULL))
				return 1;
		}
	}
#endif

	fflush(stdout);

	return 0;
}




#define SM2_PLAIN_MAX_LEN  (200)
uint32_t sm2_encrypt_decrypt_test(void)
{
	uint8_t prikey[32]={
		0x39,0x45,0x20,0x8F,0x7B,0x21,0x44,0xB1,0x3F,0x36,0xE3,0x8A,0xC6,0xD3,0x9F,0x95,
		0x88,0x93,0x93,0x69,0x28,0x60,0xB5,0x1A,0x42,0xFB,0x81,0xEF,0x4D,0xF7,0xC5,0xB8,
	};
	uint8_t pubkey[65]={
		0x04,0x09,0xF9,0xDF,0x31,0x1E,0x54,0x21,0xA1,0x50,0xDD,0x7D,0x16,0x1E,0x4B,0xC5,
		0xC6,0x72,0x17,0x9F,0xAD,0x18,0x33,0xFC,0x07,0x6B,0xB0,0x8F,0xF3,0x56,0xF3,0x50,
		0x20,0xCC,0xEA,0x49,0x0C,0xE2,0x67,0x75,0xA5,0x2D,0xC6,0xEA,0x71,0x8C,0xC1,0xAA,
		0x60,0x0A,0xED,0x05,0xFB,0xF3,0x5E,0x08,0x4A,0x66,0x32,0xF6,0x07,0x2D,0xA9,0xAD,
		0x13,
	};
	uint8_t rand_k[32]={
		0x59,0x27,0x6E,0x27,0xD5,0x06,0x86,0x1A,0x16,0x68,0x0F,0x3A,0xD9,0xC0,0x2D,0xCC,
		0xEF,0x3C,0xC1,0xFA,0x3C,0xDB,0xE4,0xCE,0x6D,0x54,0xB8,0x0D,0xEA,0xC1,0xBC,0x21,
	};

	uint8_t plain[SM2_PLAIN_MAX_LEN]={
		0x65,0x6E,0x63,0x72,0x79,0x70,0x74,0x69,0x6F,0x6E,0x20,0x73,0x74,0x61,0x6E,0x64,
		0x61,0x72,0x64,
	};
	//C1C3C2
	uint8_t std_cipher[19+97]={
		0x04,0x04,0xEB,0xFC,0x71,0x8E,0x8D,0x17,0x98,0x62,0x04,0x32,0x26,0x8E,0x77,0xFE,
		0xB6,0x41,0x5E,0x2E,0xDE,0x0E,0x07,0x3C,0x0F,0x4F,0x64,0x0E,0xCD,0x2E,0x14,0x9A,
		0x73,0xE8,0x58,0xF9,0xD8,0x1E,0x54,0x30,0xA5,0x7B,0x36,0xDA,0xAB,0x8F,0x95,0x0A,
		0x3C,0x64,0xE6,0xEE,0x6A,0x63,0x09,0x4D,0x99,0x28,0x3A,0xFF,0x76,0x7E,0x12,0x4D,
		0xF0,0x59,0x98,0x3C,0x18,0xF8,0x09,0xE2,0x62,0x92,0x3C,0x53,0xAE,0xC2,0x95,0xD3,
		0x03,0x83,0xB5,0x4E,0x39,0xD6,0x09,0xD1,0x60,0xAF,0xCB,0x19,0x08,0xD0,0xBD,0x87,
		0x66,0x21,0x88,0x6C,0xA9,0x89,0xCA,0x9C,0x7D,0x58,0x08,0x73,0x07,0xCA,0x93,0x09,
		0x2D,0x65,0x1E,0xFA
	};
	uint8_t cipher[SM2_PLAIN_MAX_LEN+97];
	uint8_t replain[SM2_PLAIN_MAX_LEN+97];
#if SM2_RANDOM_TEST
	uint32_t i,j;
	uint8_t *k;
	sm2_cipher_order_e order=0;
#endif
    uint32_t bytelen, bytelen2;
	uint32_t ret;
    uint32_t start = 0;
    uint32_t duration = 0;

	printf("\r\n\r\n -------------- SM2 encrypt & decrypt test -------------- ");


	/********** encrypt & decrypt standard data test **********/
	//standard data test 1

	memset_(replain, 0, 200);

    start = get_systick_micros();
	ret = sm2_encrypt(plain, 19, rand_k, pubkey, SM2_C1C3C2, cipher, &bytelen);

	if((SM2_SUCCESS != ret) || (bytelen!=19+97) || memcmp_(cipher, std_cipher, bytelen))
	{
		printf("\r\n SM2 encrypt & decrypt standard data test 1 encrypt failure, ret=%lu", ret);
		return 1;
	}

	ret = sm2_decrypt(cipher, bytelen, prikey, SM2_C1C3C2, replain, &bytelen2);
    duration = get_systick_micros() - start;

	if((SM2_SUCCESS != ret) || (19 != bytelen2)|| memcmp_(plain, replain, bytelen2))
	{
		printf("\r\n SM2 encrypt & decrypt standard data test 1 failure, ret=%lu", ret);
		return 1;
	}

    printf("\r\n SM2 encrypt & decrypt standard data test 1 success, duration: %lu us", duration);


	//transform to C1C2C3
	memcpy_(replain, std_cipher+65, 32);  //store C3
	memcpy_(std_cipher+65, std_cipher+65+32, 19);
	memcpy_(std_cipher+65+19, replain, 32);

	//standard data test 2
	memset_(cipher, 0x11, 19+97);
	memset_(replain, 0, 200);

    start = get_systick_micros();
	ret = sm2_encrypt(plain, 19, rand_k, pubkey, SM2_C1C2C3, cipher, &bytelen);

	if((SM2_SUCCESS != ret) || (bytelen!=19+97) || memcmp_(cipher, std_cipher, bytelen))
	{
		printf("\r\n SM2 encrypt & decrypt standard data test 2 encrypt failure, ret=%lu", ret);
		return 1;
	}

	ret = sm2_decrypt(cipher, bytelen, prikey, SM2_C1C2C3, replain, &bytelen2);
    duration = get_systick_micros() - start;

	if((SM2_SUCCESS != ret) || (19 != bytelen2)|| memcmp_(plain, replain, bytelen2))
	{
		printf("\r\n SM2 encrypt & decrypt standard data test 2 decrypt failure, ret=%lu", ret);
		return 1;
	}

    printf("\r\n SM2 encrypt & decrypt standard data test 2 success, duration: %lu us", duration);
	printf("\r\n SM2 encrypt & decrypt standard data test success");

#if SM2_RANDOM_TEST
	/********** encrypt & decrypt random data test **********/
	printf("\r\n\r\n SM2 encrypt & decrypt random data test: \r\n");
	for(i=0;i<SM2_ENCRYPT_DECRYPT_ROUND1;i++)
	{
		//random key pair
		memset_(prikey,0,32);
		memset_(pubkey,0,65);
		ret = sm2_getkey(prikey, pubkey);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n SM2 get key pair error, ret = %02lx", ret);
			return 1;
		}

		//random plaintext
		ret = get_rand(plain, SM2_PLAIN_MAX_LEN);
		if(TRNG_SUCCESS != ret)
		{
			printf("\r\n get rand error 1, ret = %02lx", ret);
			return 1;
		}

		//random order
		order ^= (plain[0]+plain[1]+plain[2])&1;

		//random k
		if(plain[0]>0x80)
		{
			k=NULL;
		}
		else
		{
			k=rand_k;
			ret = get_rand(k, 32);
			if(TRNG_SUCCESS != ret)
			{
				printf("\r\n get rand error 2, ret = %02lx", ret);
				return 1;
			}
			k[0] = 0x7F;  //make sure k < n
		}

		//明文长度可以从1字节开始递增，但这里测试明文长度从10开始，是因为如果太短，如明文只有1字节，则约有1/256的概率加密失败，即kdf的结果是全0，从而返回失败。
		//实际应用中，若明文很短，且加密返回失败（SM2_ZERO_ALL），则重新尝试下加密就好了，这是正常的。
		for(j=10; j<=SM2_PLAIN_MAX_LEN; j++)
		{
			printf("\r\n SM2 encrypt & decrypt round1=%lu, plaintext byte length=%lu, order=%d", i+1, j, order);

			if(j&1)
			{
				ret = sm2_encrypt(plain, j, k, pubkey, order, cipher, &bytelen);
			}
			else
			{
				memcpy_(cipher, plain, j);
				ret = sm2_encrypt(cipher, j, k, pubkey, order, cipher, &bytelen);
			}
			if((SM2_SUCCESS != ret) || (j+97 != bytelen))
			{
				print_buf_U8(plain, j, "plain");
				print_buf_U8(prikey, 32, "prikey");
				print_buf_U8(pubkey, 65, "pubkey");
				if(k)
					print_buf_U8(k, 32, "k");
				print_buf_U8(cipher, bytelen, "cipher");
				printf("\r\n encrypt failure, ret = %02lx", ret);
				return 1;
			}

			if(j&1)
			{
				memset_(replain, 0, SM2_PLAIN_MAX_LEN);
				ret = sm2_decrypt(cipher, bytelen, prikey, order, replain, &bytelen2);
			}
			else
			{
				memcpy_(replain, cipher, bytelen);
				ret = sm2_decrypt(replain, bytelen, prikey, order, replain, &bytelen2);
			}
			if((SM2_SUCCESS != ret) || (j != bytelen2)|| memcmp_(plain, replain, bytelen2))
			{
				print_buf_U8(plain, bytelen, "plain");
				print_buf_U8(prikey, 32, "prikey");
				print_buf_U8(pubkey, 65, "pubkey");
				printf("\r\n decrypt failure, ret = %02lx", ret);
				return 1;
			}
			else
			{
				//printf("\r\n decrypt pass");
			}
		}
	}
#endif

	fflush(stdout);

	return 0;
}



uint32_t sm2_key_exchange_test(void)
{
	uint8_t KA[SM2_EXCHANGE_MAX_LEN], KB[SM2_EXCHANGE_MAX_LEN], S1[32]={0}, SA[32]={0}, S2[32]={0}, SB[32]={0};

	uint8_t ZA[32]={
		0x3B,0x85,0xA5,0x71,0x79,0xE1,0x1E,0x7E,0x51,0x3A,0xA6,0x22,0x99,0x1F,0x2C,0xA7,
		0x4D,0x18,0x07,0xA0,0xBD,0x4D,0x4B,0x38,0xF9,0x09,0x87,0xA1,0x7A,0xC2,0x45,0xB1,
	};
	uint8_t ZB[32]={
		0x79,0xC9,0x88,0xD6,0x32,0x29,0xD9,0x7E,0xF1,0x9F,0xE0,0x2C,0xA1,0x05,0x6E,0x01,
		0xE6,0xA7,0x41,0x1E,0xD2,0x46,0x94,0xAA,0x8F,0x83,0x4F,0x4A,0x4A,0xB0,0x22,0xF7,
	};

	//A的身份
	uint8_t IDa[16]= {
		0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
	};
	//A的公钥
	uint8_t PA[65] = {0x04,
		0x16,0x0E,0x12,0x89,0x7D,0xF4,0xED,0xB6,0x1D,0xD8,0x12,0xFE,0xB9,0x67,0x48,0xFB,
		0xD3,0xCC,0xF4,0xFF,0xE2,0x6A,0xA6,0xF6,0xDB,0x95,0x40,0xAF,0x49,0xC9,0x42,0x32,
		0x4A,0x7D,0xAD,0x08,0xBB,0x9A,0x45,0x95,0x31,0x69,0x4B,0xEB,0x20,0xAA,0x48,0x9D,
		0x66,0x49,0x97,0x5E,0x1B,0xFC,0xF8,0xC4,0x74,0x1B,0x78,0xB4,0xB2,0x23,0x00,0x7F,
	};
	//A的临时公钥
	uint8_t RA[65] = {0x04,
		0x64,0xCE,0xD1,0xBD,0xBC,0x99,0xD5,0x90,0x04,0x9B,0x43,0x4D,0x0F,0xD7,0x34,0x28,
		0xCF,0x60,0x8A,0x5D,0xB8,0xFE,0x5C,0xE0,0x7F,0x15,0x02,0x69,0x40,0xBA,0xE4,0x0E,
		0x37,0x66,0x29,0xC7,0xAB,0x21,0xE7,0xDB,0x26,0x09,0x22,0x49,0x9D,0xDB,0x11,0x8F,
		0x07,0xCE,0x8E,0xAA,0xE3,0xE7,0x72,0x0A,0xFE,0xF6,0xA5,0xCC,0x06,0x20,0x70,0xC0,
	};
	//A的私钥
	uint8_t dA[32] = {
		0x81,0xEB,0x26,0xE9,0x41,0xBB,0x5A,0xF1,0x6D,0xF1,0x16,0x49,0x5F,0x90,0x69,0x52,
		0x72,0xAE,0x2C,0xD6,0x3D,0x6C,0x4A,0xE1,0x67,0x84,0x18,0xBE,0x48,0x23,0x00,0x29,
	};
	//A的临时私钥
	uint8_t rA[32] = {
		0xD4,0xDE,0x15,0x47,0x4D,0xB7,0x4D,0x06,0x49,0x1C,0x44,0x0D,0x30,0x5E,0x01,0x24,
		0x00,0x99,0x0F,0x3E,0x39,0x0C,0x7E,0x87,0x15,0x3C,0x12,0xDB,0x2E,0xA6,0x0B,0xB3,
	};
	//B的身份
	uint8_t IDb[16]= {
		0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
	};
	//B的公钥
	uint8_t PB[65] = {0x04,
		0x6A,0xE8,0x48,0xC5,0x7C,0x53,0xC7,0xB1,0xB5,0xFA,0x99,0xEB,0x22,0x86,0xAF,0x07,
		0x8B,0xA6,0x4C,0x64,0x59,0x1B,0x8B,0x56,0x6F,0x73,0x57,0xD5,0x76,0xF1,0x6D,0xFB,
		0xEE,0x48,0x9D,0x77,0x16,0x21,0xA2,0x7B,0x36,0xC5,0xC7,0x99,0x20,0x62,0xE9,0xCD,
		0x09,0xA9,0x26,0x43,0x86,0xF3,0xFB,0xEA,0x54,0xDF,0xF6,0x93,0x05,0x62,0x1C,0x4D,
	};
	//B的临时公钥
	uint8_t RB[65] = {0x04,
		0xAC,0xC2,0x76,0x88,0xA6,0xF7,0xB7,0x06,0x09,0x8B,0xC9,0x1F,0xF3,0xAD,0x1B,0xFF,
		0x7D,0xC2,0x80,0x2C,0xDB,0x14,0xCC,0xCC,0xDB,0x0A,0x90,0x47,0x1F,0x9B,0xD7,0x07,
		0x2F,0xED,0xAC,0x04,0x94,0xB2,0xFF,0xC4,0xD6,0x85,0x38,0x76,0xC7,0x9B,0x8F,0x30,
		0x1C,0x65,0x73,0xAD,0x0A,0xA5,0x0F,0x39,0xFC,0x87,0x18,0x1E,0x1A,0x1B,0x46,0xFE,
	};
	//B的私钥
	uint8_t dB[32] = {
		0x78,0x51,0x29,0x91,0x7D,0x45,0xA9,0xEA,0x54,0x37,0xA5,0x93,0x56,0xB8,0x23,0x38,
		0xEA,0xAD,0xDA,0x6C,0xEB,0x19,0x90,0x88,0xF1,0x4A,0xE1,0x0D,0xEF,0xA2,0x29,0xB5,
	};
	//B的临时私钥
	uint8_t rB[32] = {
		0x7E,0x07,0x12,0x48,0x14,0xB3,0x09,0x48,0x91,0x25,0xEA,0xED,0x10,0x11,0x13,0x16,
		0x4E,0xBF,0x0F,0x34,0x58,0xC5,0xBD,0x88,0x33,0x5C,0x1F,0x9D,0x59,0x62,0x43,0xD6,
	};
	uint8_t const std_key[16] = {
		0x6C,0x89,0x34,0x73,0x54,0xDE,0x24,0x84,0xC6,0x0B,0x4A,0xB1,0xFD,0xE4,0xC6,0xE5,
	};
	uint8_t const std_S1_SB[32] = {
		0xD3,0xA0,0xFE,0x15,0xDE,0xE1,0x85,0xCE,0xAE,0x90,0x7A,0x6B,0x59,0x5C,0xC3,0x2A,
		0x26,0x6E,0xD7,0xB3,0x36,0x7E,0x99,0x83,0xA8,0x96,0xDC,0x32,0xFA,0x20,0xF8,0xEB
	};
	uint8_t const std_S2_SA[32] = {
		0x18,0xC7,0x89,0x4B,0x38,0x16,0xDF,0x16,0xCF,0x07,0xB0,0x5C,0x5E,0xC0,0xBE,0xF5,
		0xD6,0x55,0xD5,0x8F,0x77,0x9C,0xC1,0xB4,0x00,0xA4,0xF3,0x88,0x46,0x44,0xDB,0x88
	};

#if SM2_RANDOM_TEST
	uint32_t i;
	uint32_t keyByteLen;
#endif
	uint32_t ret;
    uint32_t start = 0;
    uint32_t duration = 0;

	printf("\r\n\r\n -------------- SM2 key exchange --------------");

	/********** get key standard data test **********/
	//get key standard data test
    start = get_systick_micros();
	ret = sm2_get_pubkey_from_prikey(dA, KA);

	if((SM2_SUCCESS != ret) || memcmp_(PA, KA, 65))
	{
		printf("\r\n SM2 get key standard data test 1 failure, ret=%lu", ret);
		return 1;
	}
	ret = sm2_get_pubkey_from_prikey(rA, KA);
	if((SM2_SUCCESS != ret) || memcmp_(RA, KA, 65))
	{
		printf("\r\n SM2 get key standard data test 2 failure, ret=%lu", ret);
		return 1;
	}
	ret = sm2_get_pubkey_from_prikey(dB, KA);
	if((SM2_SUCCESS != ret) || memcmp_(PB, KA, 65))
	{
		printf("\r\n SM2 get key standard data test 3 failure, ret=%lu", ret);
		return 1;
	}
	ret = sm2_get_pubkey_from_prikey(rB, KA);
	if((SM2_SUCCESS != ret) || memcmp_(RB, KA, 65))
	{
		printf("\r\n SM2 get key standard data test 4 failure, ret=%lu", ret);
		return 1;
	}

    duration = get_systick_micros() - start;

	printf("\r\n SM2 get key standard data test success, duration: %lu us", duration);


	/********** key exchange standard data test **********/
    start = get_systick_micros();
	ret = sm2_getZ(IDa, 16, PA, KA);

	if((SM2_SUCCESS != ret) || memcmp_(ZA, KA, 32))
	{
		print_buf_U8(KA, 32, "ZA");
		printf("\r\n SM2 get Z test 1 failure, ret=%lu", ret);
		return 1;
	}
	ret = sm2_getZ(IDb, 16, PB, KA);
	if((SM2_SUCCESS != ret) || memcmp_(ZB, KA, 32))
	{
		print_buf_U8(KA, 32, "ZB");
		printf("\r\n SM2 get Z test 2 failure, ret=%lu", ret);
		return 1;
	}

    duration = get_systick_micros() - start;

	printf("\r\n SM2 get Z standard data test success, duration: %lu us", duration);

    start = get_systick_micros();

	ret = sm2_exchangekey(SM2_Role_Sponsor,
					dA, PB,
					rA, RA,
					RB,
					ZA, ZB,
					16,
					KA, S1, SA);
	ret |= sm2_exchangekey(SM2_Role_Responsor,
					dB, PA,
					rB, RB,
					RA,
					ZB, ZA,
					16,
					KB, S2, SB);

    duration = get_systick_micros() - start;

	if((SM2_SUCCESS != ret) || memcmp_((void *)std_key, KA, 16) || memcmp_((void *)std_key, KB, 16) || memcmp_((void *)std_S1_SB, S1, 32)
			|| memcmp_((void *)std_S1_SB, SB, 32) || memcmp_((void *)std_S2_SA, S2, 32) || memcmp_((void *)std_S2_SA, SA, 32))
	{
		printf("\r\n SM2 key exchange standard data test error. ret=%08lx", ret);
		print_buf_U8(KA, 16, "KA");
		print_buf_U8(S1, 32, "S1");
		print_buf_U8(SA, 32, "SA");
		print_buf_U8(KB, 16, "KB");
		print_buf_U8(S2, 32, "S2");
		print_buf_U8(SB, 32, "SB");
		return 1;
	}
	else
	{
		printf("\r\n SM2 key exchange standard data test success, duration: %lu us", duration);
	}

#if SM2_RANDOM_TEST
	/********** key exchange random data test **********/
	printf("\r\n\r\n SM2 key exchange random data test: \r\n");
	for(i=0; i<SM2_KEY_EXCHANGE_ROUND1; i++)
	{
		//random key pairs
		memset_(dA,0,32);
		memset_(PA,0,65);
		memset_(rA,0,32);
		memset_(RA,0,65);
		memset_(dB,0,32);
		memset_(PB,0,65);
		memset_(rB,0,32);
		memset_(RB,0,65);
		ret = sm2_getkey(dA, PA);
		ret |= sm2_getkey(rA, RA);
		ret |= sm2_getkey(dB, PB);
		ret |= sm2_getkey(rB, RB);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n SM2 key exchange random data test get key failure, ret = %02lx", ret);
			return 1;
		}

		//random ZA & ZB
		ret = get_rand(ZA, 32);
		ret |= get_rand(ZB, 32);
		if(TRNG_SUCCESS != ret)
		{
			printf("\r\n get rand error, ret = %02lx", ret);
			return 1;
		}

		//类似加解密，协商出来的密钥若是全0，则协商失败，1个字节时可能会协商失败
		for(keyByteLen=8; keyByteLen<=SM2_EXCHANGE_MAX_LEN; keyByteLen++)
		{
			printf("\r\n SM2 key exchange round1=%lu, keyByteLen=%lu", i+1, keyByteLen);
			//get random key pairs
			memset_(KA, 0x11, keyByteLen);
			memset_(KB, 0x55, keyByteLen);
			memset_(S1, 0x11, 32);
			memset_(S2, 0x55, 32);
			memset_(SA, 0x11, 32);
			memset_(SB, 0x55, 32);

			ret = sm2_exchangekey(SM2_Role_Sponsor,
							dA, PB,
							rA, RA,
							RB,
							ZA, ZB,
							keyByteLen,
							KA, S1, SA);
			ret |= sm2_exchangekey(SM2_Role_Responsor,
							dB, PA,
							rB, RB,
							RA,
							ZB, ZA,
							keyByteLen,
							KB, S2, SB);
			if((SM2_SUCCESS != ret) || memcmp_(KA, KB, keyByteLen) || memcmp_(S1, SB, 32) ||  memcmp_(S2, SA, 32))
			{
				printf("\r\n SM2 key exchange random data test error. ret=%02lx", ret);
				print_buf_U8(KA, keyByteLen, "KA");
				print_buf_U8(S1, 32, "S1");
				print_buf_U8(SA, 32, "SA");
				print_buf_U8(KB, keyByteLen, "KB");
				print_buf_U8(S2, 32, "S2");
				print_buf_U8(SB, 32, "SB");
				return 1;
			}
		}
	}
#endif

	printf("\r\n ");

	return 0;
}

#ifdef TRNG_POKER_TEST
uint32_t sm2_rng_test(void)
{
	uint8_t prikey[32];
	uint8_t pubkey[65];
	uint8_t buf1[32];
	uint8_t buf2[164];
	uint8_t buf3[164];
	uint32_t i, bytelen;
	uint32_t ret=0;

	for(i=0;i<3000;i++)
	{
		//get key
		ret |= sm2_getkey(prikey, pubkey);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n SM2 get key failure, ret = %02lx", ret);
			return 1;
		}

		//sign & verify
		ret = sm2_sign(buf1, NULL, prikey, buf2);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n SM2 sign failure, ret=%lu", ret);
			return 1;
		}
		ret = sm2_verify(buf1, pubkey, buf2);
		if(SM2_SUCCESS != ret)
		{
			printf("\r\n SM2 verify failure, ret=%lx", ret);
			return 1;
		}

		//encrypt & decrypt
		ret = sm2_encrypt(buf1, 32, NULL, pubkey, pubkey[2]&1, buf2, &bytelen);
		if((SM2_SUCCESS != ret) || (32+97 != bytelen))
		{
			printf("\r\n encrypt failure, ret = %02lx", ret);
			return 1;
		}

		ret = sm2_decrypt(buf2, bytelen, prikey, pubkey[2]&1, buf3, &bytelen);
		if((SM2_SUCCESS != ret) || (32 != bytelen)|| memcmp_(buf1, buf3, bytelen))
		{
			printf("\r\n decrypt failure, ret = %02lx", ret);
			return 1;
		}
	}

	return 0;
}
#endif



uint32_t SM2_all_test(void)
{
	uint32_t ret;

	printf("\r\n\r\n =================== SM2 test =================== ");fflush(stdout);

	//test internal random numbers in sm2 get_key,sign and encrypt
#ifdef TRNG_POKER_TEST
	if(sm2_rng_test())
		return 1;
#endif

#if 0
	//SM2_keyget_speed_test();
	//SM2_sign_speed_test();
	//SM2_verify_speed_test();
	//SM2_encrypt_speed_test();
	//SM2_decrypt_speed_test();
	SM2_exchange_speed_test();

#else
/**/
	ret = sm2_get_key_test();
	if(ret)
		return 1;

	ret = sm2_sign_verify_test();
	if(ret)
		return 1;

	ret = sm2_encrypt_decrypt_test();
	if(ret)
		return 1;

	ret = sm2_key_exchange_test();
	if(ret)
		return 1;
#endif


	return 0;
}


#endif
