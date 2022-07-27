#include <stdio.h>
#include "pke.h"
#include "trng.h"
#include "../crypto_include/utility.h"
#ifdef PKE_SEC
#include "../crypto_include/utility_sec.h"
#endif




static uint32_t g_step;


/* function: get pke IP version
 * parameters: none
 * return: pke IP version
 * caution:
 */
uint32_t pke_get_version(void)
{
	return PKE_VERSION;
}


/* function: clear finished and interrupt tag
 * parameters: none
 * return: none
 * caution:
 */
void pke_clear_interrupt(void)
{
	volatile uint32_t mask = ~1;

#if 1
	PKE_RISR &= mask;      //write 0 to clear
#else
	volatile uint32_t flag = 1;

	if(PKE_RISR & flag)
	{
		PKE_RISR &= mask;    //write 0 to clear
	}
	else
	{;}
#endif
}


/* function: enable pke interrupt
 * parameters: none
 * return: none
 * caution:
 */
void pke_enable_interrupt(void)
{
	volatile uint32_t flag = (uint32_t)1;

	PKE_IMCR |= flag;
}


/* function: disable pke interrupt
 * parameters: none
 * return: none
 * caution:
 */
void pke_disable_interrupt(void)
{
	volatile uint32_t mask = ~((uint32_t)1);

	PKE_IMCR &= mask;
}


/* function: set operand width
 * parameters:
 *     bitLen --------------------- input, bit length of operand
 * return: none
 * caution: please make sure 0 < bitLen <= OPERAND_MAX_BIT_LEN
 */
void pke_set_operand_width(uint32_t bitLen)
{
	volatile uint32_t mask = ~(0x07FFFF);
	uint32_t cfg, len;

	len = (bitLen+255)/256;

	if(1 == len)
	{
		cfg = 2;
		g_step = 0x24;
	}
	else if(2 == len)
	{
		cfg = 3;
		g_step = 0x44;
	}
	else if(len <= 4)
	{
		cfg = 4;
		g_step = 0x84;
	}
	else if(len <= 8)
	{
		cfg = 5;
		g_step = 0x104;
	}
	else if(len <= 16)
	{
		cfg = 6;
		g_step = 0x204;
	}
	else
	{;}

	cfg = (cfg<<16)|(bitLen);//cfg = (cfg<<16)|(len<<8);

	PKE_CFG &= mask;
	PKE_CFG |= cfg;  //printf("\r\n %d, PKE_CFG = %08x", len, PKE_CFG);
}


/* function: get current operand byte length
 * parameters: none
 * return: current operand byte length
 * caution: none
 */
uint32_t pke_get_operand_bytes(void)
{
	return g_step;
}


/* function: set operation micro code
 * parameters:
 *     addr ----------------------- input, specific micro code
 * return: none
 * caution:
 */
void pke_set_microcode(uint32_t addr)
{
	PKE_MC_PTR = addr;
}


/* function: set exe config
 * parameters:
 *     cfg ------------------------ input, specific config value
 * return: none
 * caution:
 */
void pke_set_exe_cfg(uint32_t cfg)
{
	PKE_EXE_CONF = cfg;
}


/* function: start pke calc
 * parameters: none
 * return: none
 * caution:
 */
void pke_start(void)
{
	volatile uint32_t flag = PKE_START_CALC;

	PKE_CTRL |= flag;
}


/* function: return calc return code
 * parameters: none
 * return 0(success), other(error)
 * caution:
 */
uint32_t pke_check_rt_code(void)
{
	volatile uint32_t mask = 0x07u;

	return (uint8_t)(PKE_RT_CODE & mask);
}


/* function: wait till done
 * parameters: none
 * return: none
 * caution:
 */
void pke_wait_till_done(void)
{
	volatile uint32_t flag = 1;

	while(!(PKE_RISR & flag))
	{;}
}


/* function: set operation micro code, start hardware, wait till done, and return code
 * parameters:
 *     micro_code ----------------- input, specific micro code
 * return: PKE_SUCCESS(success), other(inverse not exists or error)
 * caution:
 */
uint32_t pke_set_micro_code_start_wait_return_code(uint32_t micro_code)
{
	pke_set_microcode(micro_code);

	pke_clear_interrupt();

	pke_start();

	pke_wait_till_done();

	return pke_check_rt_code();
}


/* function: ainv = a^(-1) mod modulus
 * parameters:
 *     modulus -------------------- input, modulus
 *     a -------------------------- input, integer a
 *     ainv ----------------------- output, ainv = a^(-1) mod modulus
 *     modWordLen ----------------- input, word length of modulus and ainv
 *     aWordLen ------------------- input, word length of a
 * return: PKE_SUCCESS(success), other(inverse not exists or error)
 * caution:
 *     1. please make sure aWordLen <= modWordLen <= OPERAND_MAX_WORD_LEN and a < modulus
 */
uint32_t pke_modinv(const uint32_t *modulus, const uint32_t *a, uint32_t *ainv, uint32_t modWordLen,
		uint32_t aWordLen)
{
	uint32_t ret;

	pke_set_operand_width(modWordLen<<5);

	pke_load_operand((uint32_t *)(PKE_B(3,g_step)), (uint32_t *)modulus, modWordLen); //B3 modulus
	if((g_step/4) > modWordLen)
	{
		uint32_clear((uint32_t *)(PKE_B(3,g_step))+modWordLen, (g_step/4)-modWordLen);
	}
	else
	{;}

	pke_load_operand((uint32_t *)(PKE_B(0,g_step)), (uint32_t *)a, aWordLen);         //B0 a
	if((g_step/4) > aWordLen)
	{
		uint32_clear((uint32_t *)(PKE_B(0,g_step))+aWordLen, (g_step/4)-aWordLen);
	}
	else
	{;}

	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_MODINV);
	if(PKE_SUCCESS == ret)
	{
		pke_read_operand((uint32_t *)(PKE_A(0,g_step)), ainv, modWordLen);            //A0 ainv
	}
	else if(PKE_NO_MODINV != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_B(3,g_step)), modWordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(0,g_step)), aWordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(0,g_step)), modWordLen<<2);
#endif
	}
	else
	{;}

	return ret;
}


/* function: out = (a+b) mod modulus or out = (a-b) mod modulus
 * parameters:
 *     modulus -------------------- input, modulus
 *     a -------------------------- input, integer a
 *     b -------------------------- input, integer b
 *     out ------------------------ output, out = a+b mod modulus or out = (a-b) mod modulus
 *     wordLen -------------------- input, word length of modulus, a, b
 *     micro_code ----------------- input, must be MICROCODE_MODADD or MICROCODE_MODSUB
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. a,b must be less than modulus
 *     2. wordLen must not be bigger than OPERAND_MAX_WORD_LEN
 */
uint32_t pke_modadd_modsub_internal(const uint32_t *modulus, const uint32_t *a, const uint32_t *b,
		uint32_t *out, uint32_t wordLen, uint32_t micro_code)
{
	uint32_t ret;

	pke_set_operand_width(wordLen<<5);

	pke_load_operand((uint32_t *)(PKE_B(3,g_step)), (uint32_t *)modulus, wordLen);    //B3 modulus
	pke_load_operand((uint32_t *)(PKE_A(0,g_step)), (uint32_t *)a, wordLen);          //A0 a
	pke_load_operand((uint32_t *)(PKE_B(0,g_step)), (uint32_t *)b, wordLen);          //B0 b

	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)(PKE_B(3,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(0,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_B(0,g_step))+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	ret = pke_set_micro_code_start_wait_return_code(micro_code);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_B(3,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(0,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(0,g_step)), wordLen<<2);
#endif
		return ret;
	}
	else
	{
		pke_read_operand((uint32_t *)(PKE_A(0, g_step)), out, wordLen);               //A0 result

		return PKE_SUCCESS;
	}
}


/* function: out = (a+b) mod modulus
 * parameters:
 *     modulus -------------------- input, modulus
 *     a -------------------------- input, integer a
 *     b -------------------------- input, integer b
 *     out ------------------------ output, out = a+b mod modulus
 *     wordLen -------------------- input, word length of modulus, a, b
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. a,b must be less than modulus
 *     2. wordLen must not be bigger than OPERAND_MAX_WORD_LEN
 */
uint32_t pke_modadd(const uint32_t *modulus, const uint32_t *a, const uint32_t *b,
		uint32_t *out, uint32_t wordLen)
{
	return pke_modadd_modsub_internal(modulus, a, b, out, wordLen, MICROCODE_MODADD);
}


/* function: out = (a-b) mod modulus
 * parameters:
 *     modulus -------------------- input, modulus
 *     a -------------------------- input, integer a
 *     b -------------------------- input, integer b
 *     out ------------------------ output, out = a-b mod modulus
 *     wordLen -------------------- input, word length of modulus, a, b
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. a,b must be less than modulus
 *     2. wordLen must not be bigger than OPERAND_MAX_WORD_LEN
 */
uint32_t pke_modsub(const uint32_t *modulus, const uint32_t *a, const uint32_t *b,
		uint32_t *out, uint32_t wordLen)
{
	return pke_modadd_modsub_internal(modulus, a, b, out, wordLen, MICROCODE_MODSUB);
}


/* function: out = a+b or out = a-b
 * parameters:
 *     a -------------------------- input, integer a
 *     b -------------------------- input, integer b
 *     out ------------------------ output, out = a+b or out = a-b
 *     wordLen -------------------- input, word length of a, b, out
 *     micro_code ----------------- input, must be MICROCODE_INTADD or MICROCODE_INTSUB
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. if a+b output may overflow, if a-b please make sure a > b
 *     2. wordLen must not be bigger than OPERAND_MAX_WORD_LEN

uint32_t pke_add_sub_internal(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t wordLen,
		uint32_t micro_code)
{
	uint32_t ret;

	pke_set_operand_width(wordLen<<5);

	pke_load_operand((uint32_t *)(PKE_A(1,g_step)), (uint32_t *)a, wordLen);          //A1 a
	pke_load_operand((uint32_t *)(PKE_B(1,g_step)), (uint32_t *)b, wordLen);          //B1 b

	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)(PKE_A(1,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_B(1,g_step))+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	ret = pke_set_micro_code_start_wait_return_code(micro_code);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_A(1,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(1,g_step)), wordLen<<2);
#endif
		return ret;
	}
	else
	{
		pke_read_operand((uint32_t *)(PKE_A(1,g_step)), out, wordLen);                //A1 result

		return PKE_SUCCESS;
	}
} */


/* function: out = a+b
 * parameters:
 *     a -------------------------- input, integer a
 *     b -------------------------- input, integer b
 *     out ------------------------ output, out = a+b
 *     wordLen -------------------- input, word length of a, b, out
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. a+b may overflow
 *     2. wordLen must not be bigger than OPERAND_MAX_WORD_LEN
 */
uint32_t pke_add(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t wordLen)
{
#if 0
	return pke_add_sub_internal(a, b, out, wordLen, MICROCODE_INTADD);
#else
	uint32_t i, carry, temp, temp2;

	carry = 0;
	for(i=0; i<wordLen; i++)
	{
		temp2 = a[i];
		temp = a[i]+b[i];
		out[i] = temp+carry;
		if(temp < temp2 || out[i] < carry)
		{
			carry = 1;
		}
		else
		{
			carry = 0;
		}
	}

	return PKE_SUCCESS;
#endif
}


/* function: out = a-b
 * parameters:
 *     a -------------------------- input, integer a
 *     b -------------------------- input, integer b
 *     out ------------------------ output, out = a-b
 *     wordLen -------------------- input, word length of a, b, out
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure a > b
 *     2. wordLen must not be bigger than OPERAND_MAX_WORD_LEN
 */
uint32_t pke_sub(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t wordLen)
{
#if 0
	return pke_add_sub_internal(a, b, out, wordLen, MICROCODE_INTSUB);
#else
	uint32_t i, carry, tmp, tmp2;

	carry = 0;
	for(i=0; i<wordLen; i++)
	{
		tmp = a[i]-b[i];
		tmp2 = tmp-carry;
		if(tmp > a[i] || tmp2 > tmp)
		{
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		out[i] = tmp2;
	}

	return PKE_SUCCESS;
#endif
}


/* function: out = a*b
 * parameters:
 *     a -------------------------- input, integer a
 *     a_wordLen ------------------ input, word length of a
 *     b -------------------------- input, integer b
 *     b_wordLen ------------------ input, word length of b
 *     out ------------------------ output, out = a*b
 *     out_wordLen----------------- input, word length of out
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure out buffer word length is bigger than (2*max_bit_len(a,b)+0x1F)>>5
 *     2. please make sure a_wordLen/b_wordLen is not bigger than OPERAND_MAX_WORD_LEN/2
 */
uint32_t pke_mul_internal(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t a_wordLen,
		uint32_t b_wordLen, uint32_t out_wordLen)
{
	uint32_t ret;

	pke_set_operand_width(out_wordLen<<5);  //for pke lp
	//pke_set_operand_width(GET_MAX_LEN(out_wordLen<<5,512));  //for pke hp

	pke_load_operand((uint32_t *)(PKE_A(0,g_step)), (uint32_t *)a, a_wordLen);       //A0 a
	pke_load_operand((uint32_t *)(PKE_B(0,g_step)), (uint32_t *)b, b_wordLen);       //B0 b

	uint32_clear((uint32_t *)(PKE_A(0,g_step))+a_wordLen, (g_step/4)-a_wordLen);
	uint32_clear((uint32_t *)(PKE_B(0,g_step))+b_wordLen, (g_step/4)-b_wordLen);

	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_INTMUL);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_A(0,g_step)), a_wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(0,g_step)), b_wordLen<<2);
#endif
		return ret;
	}
	else
	{
		pke_read_operand((uint32_t *)(PKE_A(1,g_step)), out, out_wordLen);	         //A1 result

		return PKE_SUCCESS;
	}
}


/* function: out = a*b
 * parameters:
 *     a -------------------------- input, integer a
 *     b -------------------------- input, integer b
 *     out ------------------------ output, out = a*b
 *     ab_wordLen ----------------- input, word length of a, b
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure out buffer word length is bigger than (2*max_bit_len(a,b)+0x1F)>>5
 *     2. please make sure ab_wordLen is not bigger than OPERAND_MAX_WORD_LEN/2
 */
#if 1
uint32_t pke_mul(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t ab_wordLen)
{
	uint32_t bitLen, tempLen;

	bitLen = get_valid_bits(a, ab_wordLen);
	tempLen = get_valid_bits(b, ab_wordLen);

	bitLen = GET_MAX_LEN(bitLen,tempLen);
	tempLen = GET_WORD_LEN(bitLen<<1);
	if(tempLen < (ab_wordLen<<1))
	{
		tempLen = (ab_wordLen<<1)-1;
	}
	else
	{
		tempLen = (ab_wordLen<<1);
	}

	return pke_mul_internal(a, b, out, ab_wordLen, ab_wordLen, tempLen);
}
#else
uint32_t pke_mul(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t ab_wordLen)
{
	uint64_t UV;
	uint32_t i,j,*U,*V;
	uint32_t bitLen, tempLen;

	bitLen = get_valid_bits(a, ab_wordLen);
	tempLen = get_valid_bits(b, ab_wordLen);

	bitLen = GET_MAX_LEN(bitLen,tempLen);
	tempLen = GET_WORD_LEN(bitLen<<1);
	if(tempLen < (ab_wordLen<<1))
	{
		tempLen = (ab_wordLen<<1)-1;
	}
	else
	{
		tempLen = (ab_wordLen<<1);
	}

	uint32_clear(out, tempLen);

	V = (uint32_t *)(&UV);
	U = V+1;
	for(i=0; i<ab_wordLen; i++)
	{
		*U = 0;
		for(j=0; j<ab_wordLen; j++)
		{
			UV = ((uint64_t)a[i])*b[j]+out[i+j]+(*U);
			out[i+j] = (*V);
		}
		out[i+j] = (*U);
	}

	return PKE_SUCCESS;
}
#endif


/* function: calc n0(- modulus ^(-1) mod 2^w) for modMul, and pointMul. etc.
 * parameters: none
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. before calling, please make sure the modulus is set in PKE_A(a, 0)
 *     2. please make sure the modulus is odd, and word length of the modulus
 *        is not bigger than OPERAND_MAX_WORD_LEN
 *     3. the result is set in the internal register, no need to output.

uint32_t pke_pre_calc_mont_N0()
{
	return pke_set_micro_code_start_wait_return_code(MICROCODE_MGMR_PRE_N0);;
} */


/* function: calc H(R^2 mod modulus) and n0'( - modulus ^(-1) mod 2^w ) for modMul,modExp, and pointMul. etc.
 *           here w is bit width of word, i,e. 32.
 * parameters:
 *     modulus -------------------- input, modulus
 *     bitLen --------------------- input, bit length of modulus
 *     H -------------------------- output, R^2 mod modulus
 *     n0 ------------------------- output,  - modulus ^(-1) mod 2^w, here w is 32 actually
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. modulus must be odd
 *     2. please make sure word length of buffer H is equal to wordLen(word length of modulus),
 *        and n0 only need one word.
 *     3. bitLen must not be bigger than OPERAND_MAX_BIT_LEN
 */
uint32_t pke_pre_calc_mont(const uint32_t *modulus, uint32_t bitLen, uint32_t *H, uint32_t *n0)
{
	uint32_t wordLen = GET_WORD_LEN(bitLen);
	uint32_t ret;

	pke_set_operand_width(bitLen);

	pke_load_operand((uint32_t *)(PKE_B(3,g_step)), (uint32_t *)modulus, wordLen);    //B3 modulus

	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)(PKE_B(3,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(3,g_step))+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_MGMR_PRE);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_B(3,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(3,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(4,g_step)), 1<<2);
#endif
		return ret;
	}

	if(NULL != H)
	{
		pke_read_operand((uint32_t *)(PKE_A(3,g_step)), H, wordLen);                  //A3 H
	}
	else
	{;}

	if(NULL != n0)
	{
		pke_read_operand((uint32_t *)(PKE_B(4,g_step)), n0, 1);                       //B4 n0
	}
	else
	{;}

	return PKE_SUCCESS;
}


/* function: like function pke_pre_calc_mont(), but this one is without output here
 * parameters:
 *     modulus -------------------- input, modulus
 *     wordLen -------------------- input, word length of modulus
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. modulus must be odd
 *     2. wordLen must not be bigger than OPERAND_MAX_WORD_LEN
 */
uint32_t pke_pre_calc_mont_no_output(const uint32_t *modulus, uint32_t wordLen)
{
	return pke_pre_calc_mont(modulus, get_valid_bits(modulus, wordLen), NULL, NULL);
}


/* function: load modulus and pre-calculated mont parameters H(R^2 mod modulus) and n0'(- modulus ^(-1) mod 2^w) for hardware operation
 * parameters:
 *     modulus -------------------- input, modulus
 *     modulus_h ------------------ input, R^2 mod modulus
 *     modulus_n0 ----------------- input, - modulus ^(-1) mod 2^w, here w is 32 actually
 *     bitLen --------------------- input, bit length of modulus
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. modulus must be odd
 *     2. bitLen must not be bigger than OPERAND_MAX_BIT_LEN
 */
uint32_t pke_load_modulus_and_pre_monts(uint32_t *modulus, uint32_t *modulus_h, uint32_t *modulus_n0, uint32_t bitLen)
{
	uint32_t wordLen = GET_WORD_LEN(bitLen);

	pke_set_operand_width(bitLen);

	pke_load_operand((uint32_t *)(PKE_B(3,g_step)), (uint32_t *)modulus, wordLen);    //B3 modulus
	pke_load_operand((uint32_t *)(PKE_A(3,g_step)), modulus_h, wordLen);              //A3 h
	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)(PKE_B(3,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(3,g_step))+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	pke_load_operand((uint32_t *)(PKE_B(4,g_step)), modulus_n0, 1);

	return PKE_SUCCESS;
}


/* function: set modulus and pre-calculated mont parameters H(R^2 mod modulus) and n0'(- modulus ^(-1) mod 2^w) for hardware operation
 * parameters:
 *     modulus -------------------- input, modulus
 *     modulus_h ------------------ input, R^2 mod modulus
 *     modulus_n0 ----------------- input, - modulus ^(-1) mod 2^w, here w is 32 actually
 *     bitLen --------------------- input, bit length of modulus
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. modulus must be odd
 *     2. bitLen must not be bigger than OPERAND_MAX_BIT_LEN
 */
uint32_t pke_set_modulus_and_pre_monts(uint32_t *modulus, uint32_t *modulus_h, uint32_t *modulus_n0, uint32_t bitLen)
{
	if((NULL == modulus_h) || (NULL == modulus_n0))
	{
		return pke_pre_calc_mont(modulus, bitLen, NULL, NULL);
	}
	else
	{
		return pke_load_modulus_and_pre_monts(modulus, modulus_h, modulus_n0, bitLen);
	}
}


/* function: out = a*b (mod modulus)
 * parameters:
 *     a -------------------------- input, integer a
 *     b -------------------------- input, integer b
 *     out ------------------------ output, out = a*b mod modulus
 *     wordLen -------------------- input, word length of modulus, a, b
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. modulus must be odd
 *     2. a, b must less than modulus
 *     3. wordLen must not be bigger than OPERAND_MAX_WORD_LEN
 *     4. before calling this function, please make sure the modulus and the pre-calculated mont arguments
 *        of modulus are located in the right address.
 */
uint32_t pke_modmul_internal(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t wordLen)
{
	uint32_t ret;

	//pke_set_operand_width(wordLen<<5);

	pke_load_operand((uint32_t *)(PKE_A(0,g_step)), (uint32_t *)a, wordLen);          //A0 a
	pke_load_operand((uint32_t *)(PKE_B(0,g_step)), (uint32_t *)b, wordLen);          //B0 b
	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)(PKE_A(0,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_B(0,g_step))+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	//pke_set_exe_cfg(PKE_EXE_CFG_ALL_NON_MONT);
	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_MODMUL);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_B(3,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(0,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(0,g_step)), wordLen<<2);
#endif
		return ret;
	}
	else
	{
		pke_read_operand((uint32_t *)(PKE_A(0,g_step)), out, wordLen);                //A0 out

		return PKE_SUCCESS;
	}
}


/* function: out = a*b mod modulus
 * parameters:
 *     modulus -------------------- input, modulus
 *     a -------------------------- input, integer a
 *     b -------------------------- input, integer b
 *     out ------------------------ output, out = a*b mod modulus
 *     wordLen -------------------- input, word length of modulus, a, b
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. modulus must be odd
 *     2. a, b must less than modulus
 *     3. wordLen must not be bigger than OPERAND_MAX_WORD_LEN
 */
uint32_t pke_modmul(const uint32_t *modulus, const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t wordLen)
{
	uint32_t ret;

	ret = pke_pre_calc_mont(modulus, get_valid_bits(modulus, wordLen), NULL, NULL);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{
		pke_set_exe_cfg(PKE_EXE_CFG_ALL_NON_MONT);

		return pke_modmul_internal(a, b, out, wordLen);
	}
}


/* function: mod exponent, this could be used for rsa encrypting,decrypting,signing,verifing.
 * parameters:
 *     modulus -------------------- input, modulus
 *     exponent ------------------- input, exponent
 *     base ----------------------- input, base number
 *     out ------------------------ output, out = base^(exponent) mod modulus
 *     mod_wordLen ---------------- input, word length of modulus and base number
 *     exp_wordLen ---------------- input, word length of exponent
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. before calling this function, please make sure the pre-calculated mont arguments of modulus are
 *        located in the right address
 *     2. modulus must be odd
 *     3. please make sure exp_wordLen <= mod_wordLen <= OPERAND_MAX_WORD_LEN
 */
uint32_t pke_modexp(const uint32_t *modulus, const uint32_t *exponent, const uint32_t *base,
		uint32_t *out, uint32_t mod_wordLen, uint32_t exp_wordLen)
{
	uint32_t ret;

	pke_set_operand_width(mod_wordLen<<5);

	pke_load_operand((uint32_t *)(PKE_A(1,g_step)), (uint32_t *)exponent, exp_wordLen);   //A1 exponent
	if((g_step/4) > exp_wordLen)
	{
		uint32_clear((uint32_t *)(PKE_A(1,g_step))+exp_wordLen, (g_step/4)-exp_wordLen);
	}
	else
	{;}

	pke_load_operand((uint32_t *)(PKE_B(3,g_step)), (uint32_t *)modulus, mod_wordLen);    //B3 modulus
	pke_load_operand((uint32_t *)(PKE_B(0,g_step)), (uint32_t *)base, mod_wordLen);       //B0 base

	if((g_step/4) > mod_wordLen)
	{
		uint32_clear((uint32_t *)(PKE_B(3,g_step))+mod_wordLen, (g_step/4)-mod_wordLen);
		uint32_clear((uint32_t *)(PKE_B(0,g_step))+mod_wordLen, (g_step/4)-mod_wordLen);
	}
	else
	{;}

	pke_set_exe_cfg(PKE_EXE_CFG_MODEXP);

	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_MODEXP);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_A(0,g_step)), mod_wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(0,g_step)), mod_wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(1,g_step)), exp_wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(3,g_step)), mod_wordLen<<2);
#endif
		return ret;
	}
	else
	{
		pke_read_operand((uint32_t *)(PKE_A(0,g_step)), out, mod_wordLen);                //A0 result

		return PKE_SUCCESS;
	}
}


/* function: c = a mod b
 * parameters:
 *     a -------------------------- input, integer a
 *     aWordLen ------------------- input, word length of integer
 *     b -------------------------- input, integer b, modulus
 *     b_h ------------------------ input, H parameter of b
 *     b_n0 ----------------------- input, - modulus ^(-1) mod 2^w, here w is 32 actually
 *     bWordLen ------------------- input, word length of integer b and b_h
 *     c -------------------------- output, c = a mod b
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. b must be odd, and please make sure bWordLen is real word length of b
 *     2. real bit length of a can not be bigger than 2*(real bit length of b), so aWordLen can 
 *        not be bigger than 2*bWordLen
 *     3. pleae make sure aWordLen <= 2*OPERAND_MAX_WORD_LEN, bWordLen <= OPERAND_MAX_WORD_LEN
 */
uint32_t pke_mod(uint32_t *a, uint32_t aWordLen, uint32_t *b, uint32_t *b_h, uint32_t *b_n0, uint32_t bWordLen,
		uint32_t *c)
{
	int32_t flag;
	uint32_t bBitLen, bitLen, tmpLen;
	uint32_t *A1, *B2;
//	uint32_t A1[OPERAND_MAX_WORD_LEN], B2[OPERAND_MAX_WORD_LEN];
	uint32_t ret;

	flag = uint32_BigNumCmp(a, aWordLen, b, bWordLen);
	if(flag < 0)
	{
		aWordLen = get_valid_words(a, aWordLen);
		uint32_copy(c, a, aWordLen);
		uint32_clear(c+aWordLen, bWordLen-aWordLen);

		return PKE_SUCCESS;
	}
	else if(0 == flag)
	{
		uint32_clear(c, bWordLen);

		return PKE_SUCCESS;
	}
	else
	{;}

	bBitLen = get_valid_bits(b, bWordLen);
	pke_set_operand_width(bBitLen);

	A1 = (uint32_t *)(PKE_A(1, g_step));
	B2 = (uint32_t *)(PKE_B(2, g_step));

	bitLen = bBitLen & 0x1F;

	//get B2 = a high part mod b
	if(bitLen)
	{
		tmpLen = aWordLen-bWordLen+1;
		uint32_copy(B2, a+bWordLen-1, tmpLen);
		Big_Div2n(B2, tmpLen, bitLen);
		if(tmpLen < bWordLen)
		{
			uint32_clear(B2+tmpLen, bWordLen-tmpLen);
		}
		else if(uint32_BigNumCmp(B2, bWordLen, b, bWordLen) >= 0)
		{
			ret = pke_sub(B2, b, B2, bWordLen);
			if(PKE_SUCCESS != ret)
			{
				return ret;
			}
			else
			{;}
		}
		else
		{;}
	}
	else
	{
		tmpLen = aWordLen - bWordLen;
		if(uint32_BigNumCmp(a+bWordLen, tmpLen, b, bWordLen) >= 0)
		{
			ret = pke_sub(a+bWordLen, b, B2, bWordLen);
			if(PKE_SUCCESS != ret)
			{
				return ret;
			}
			else
			{;}
		}
		else
		{
			uint32_copy(B2, a+bWordLen, tmpLen);
			uint32_clear(B2+tmpLen, bWordLen-tmpLen);
		}
	}

	//set the pre-calculated mont parameters
	ret = pke_set_modulus_and_pre_monts(b, b_h, b_n0, bBitLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//get A1 = 1000...000 mod b
	uint32_clear(A1, bWordLen);
	if(bitLen)
	{
		A1[bWordLen-1] = 1<<(bitLen);
	}
	else
	{;}

	ret = pke_sub(A1, b, A1, bWordLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//get B2 = a_high * 1000..000 mod b
	pke_set_exe_cfg(PKE_EXE_CFG_ALL_NON_MONT);
	ret = pke_modmul_internal(A1, B2, B2, bWordLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//get A1 = a low part mod b
	if(bitLen)
	{
		uint32_copy(A1, a, bWordLen);
		A1[bWordLen-1] &= ((1<<(bitLen))-1);
		if(uint32_BigNumCmp(A1, bWordLen, b, bWordLen) >= 0)
		{
			ret = pke_sub(A1, b, A1, bWordLen);
			if(PKE_SUCCESS != ret)
			{
				return ret;
			}
			else
			{;}
		}
		else
		{;}
	}
	else
	{
		if(uint32_BigNumCmp(a, bWordLen, b, bWordLen) >= 0)
		{
			ret = pke_sub(a, b, A1, bWordLen);
			if(PKE_SUCCESS != ret)
			{
				return ret;
			}
			else
			{;}
		}
		else
		{
			A1 = a;
		}
	}

	return pke_modadd(b, A1, B2, c, bWordLen);
}


/********************************** ECCp functions *************************************/

/* function: ECCP curve point mul(random point), Q=[k]P
 * parameters:
 *     curve ---------------------- input, eccp_curve_t curve struct pointer
 *     k -------------------------- input, scalar
 *     Px ------------------------- input, x coordinate of point P
 *     Py ------------------------- input, y coordinate of point P
 *     Qx ------------------------- output, x coordinate of point Q
 *     Qy ------------------------- output, y coordinate of point Q
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure k in [1,n-1], n is order of ECCP curve
 *     2. please make sure input point P is on the curve
 *     3. please make sure bit length of the curve is not bigger than ECCP_MAX_BIT_LEN
 *     4. even if the input point P is valid, the output may be infinite point, in this case
 *        it will return error.
 */
uint32_t eccp_pointMul(eccp_curve_t *curve, uint32_t *k, uint32_t *Px, uint32_t *Py,
		uint32_t *Qx, uint32_t *Qy)
{
	uint32_t wordLen = GET_WORD_LEN(curve->eccp_p_bitLen);
	uint32_t ret;

	//set ecc_p, ecc_p_h, ecc_p_n0, etc.
	ret = pke_set_modulus_and_pre_monts(curve->eccp_p, curve->eccp_p_h, curve->eccp_p_n0, curve->eccp_p_bitLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	pke_load_operand((uint32_t *)(PKE_B(0,g_step)), Px, wordLen);                     //B0 Px
	pke_load_operand((uint32_t *)(PKE_B(1,g_step)), Py, wordLen);                     //B1 Py
	pke_load_operand((uint32_t *)(PKE_A(5,g_step)), curve->eccp_a, wordLen);          //A5 a
	pke_load_operand((uint32_t *)(PKE_A(4,g_step)), k, wordLen);                      //A4 k
	//pke_load_operand((uint32_t *)(PKE_B(5,g_step)), curve->eccp_n, wordLen);          //B5 n

	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)(PKE_B(0,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_B(1,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(5,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(4,g_step))+wordLen, (g_step/4)-wordLen);
		//uint32_clear((uint32_t *)(PKE_B(5,g_step))+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	pke_set_exe_cfg(PKE_EXE_ECCP_POINT_MUL);

	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_PMUL);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	pke_read_operand((uint32_t *)(PKE_A(0,g_step)), Qx, wordLen);                     //A0 Qx
	if(NULL != Qy)
	{
		pke_read_operand((uint32_t *)(PKE_A(1,g_step)), Qy, wordLen);                 //A1 Qy
	}
	else
	{;}

	return PKE_SUCCESS;
}


/* function: ECCP curve point add, Q=P1+P2
 * parameters:
 *     curve ---------------------- input, eccp_curve_t curve struct pointer
 *     P1x ------------------------ input, x coordinate of point P1
 *     P1y ------------------------ input, y coordinate of point P1
 *     P2x ------------------------ input, x coordinate of point P2
 *     P2y ------------------------ input, y coordinate of point P2
 *     Qx ------------------------- output, x coordinate of point Q=P1+P2
 *     Qy ------------------------- output, y coordinate of point Q=P1+P2
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure input point P1 and P2 are both on the curve
 *     2. please make sure bit length of the curve is not bigger than ECCP_MAX_BIT_LEN
 *     3. even if the input point P1 and P2 are valid, the output may be infinite point,
 *        in this case it will return error.
 */
uint32_t eccp_pointAdd(eccp_curve_t *curve, uint32_t *P1x, uint32_t *P1y, uint32_t *P2x, uint32_t *P2y,
		uint32_t *Qx, uint32_t *Qy)
{
	uint32_t wordLen = GET_WORD_LEN(curve->eccp_p_bitLen);
	uint32_t ret;

	//set ecc_p, ecc_p_h, ecc_p_n0, etc.
	ret = pke_set_modulus_and_pre_monts(curve->eccp_p, curve->eccp_p_h, curve->eccp_p_n0, curve->eccp_p_bitLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//pke_pre_calc_mont() may cover A1, so load A1(P1x) here
	pke_load_operand((uint32_t *)(PKE_A(0,g_step)), P1x, wordLen);                    //A0 P1x
	pke_load_operand((uint32_t *)(PKE_A(1,g_step)), P1y, wordLen);                    //A1 P1y
	pke_load_operand((uint32_t *)(PKE_B(0,g_step)), P2x, wordLen);                    //B0 P2x
	pke_load_operand((uint32_t *)(PKE_B(1,g_step)), P2y, wordLen);                    //B1 P2y
	pke_load_operand((uint32_t *)(PKE_A(5,g_step)), curve->eccp_a, wordLen);          //A5 a

	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)(PKE_A(0,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(1,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_B(0,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_B(1,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(5,g_step))+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	pke_set_exe_cfg(PKE_EXE_ECCP_POINT_ADD);

	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_PADD);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_A(0,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(1,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(0,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(1,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(5,g_step)), wordLen<<2);
#endif
		return ret;
	}
	else
	{;}

	pke_read_operand((uint32_t *)(PKE_A(0,g_step)), Qx, wordLen);                     //A0 Qx
	if(NULL != Qy)
	{
		pke_read_operand((uint32_t *)(PKE_A(1,g_step)), Qy, wordLen);                 //A1 Qy
	}
	else
	{;}

	return PKE_SUCCESS;
}

#ifdef ECCP_POINT_DOUBLE
/* function: ECCP curve point double, Q=[2]P
 * parameters:
 *     curve ---------------------- input, eccp_curve_t curve struct pointer
 *     Px ------------------------- input, x coordinate of point P
 *     Py ------------------------- input, y coordinate of point P
 *     Qx ------------------------- output, x coordinate of point Q=[2]P
 *     Qy ------------------------- output, y coordinate of point Q=[2]P
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure input point P is on the curve
 *     2. please make sure bit length of the curve is not bigger than ECCP_MAX_BIT_LEN
 */
uint32_t eccp_pointDouble(eccp_curve_t *curve, uint32_t *Px, uint32_t *Py, uint32_t *Qx, uint32_t *Qy)
{
	uint32_t wordLen = GET_WORD_LEN(curve->eccp_p_bitLen);
	uint32_t ret;

	//set ecc_p, ecc_p_h, ecc_p_n0, etc.
	ret = pke_set_modulus_and_pre_monts(curve->eccp_p, curve->eccp_p_h, curve->eccp_p_n0, curve->eccp_p_bitLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//pke_pre_calc_mont() may cover A1, so load A1(Px) and other paras here
	pke_load_operand((uint32_t *)(PKE_A(0,g_step)), Px, wordLen);                     //A0 Px
	pke_load_operand((uint32_t *)(PKE_A(1,g_step)), Py, wordLen);                     //A1 Py
	pke_load_operand((uint32_t *)(PKE_A(5,g_step)), curve->eccp_a, wordLen);          //A5 a

	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)(PKE_A(0,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(1,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(5,g_step))+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	pke_set_exe_cfg(PKE_EXE_ECCP_POINT_DBL);

	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_PDBL);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_A(0,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(1,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(5,g_step)), wordLen<<2);
#endif
		return ret;
	}
	else
	{
		pke_read_operand((uint32_t *)(PKE_A(0,g_step)), Qx, wordLen);                 //A0 Qx
		pke_read_operand((uint32_t *)(PKE_A(1,g_step)), Qy, wordLen);                 //A1 Qy

		return PKE_SUCCESS;
	}
}
#endif

/* function: check whether the input point P is on ECCP curve or not
 * parameters:
 *     curve ---------------------- input, eccp_curve_t curve struct pointer
 *     Px ------------------------- input, x coordinate of point P
 *     Py ------------------------- input, y coordinate of point P
 * return: PKE_SUCCESS(success, on the curve), other(error or not on the curve)
 * caution:
 *     1. please make sure bit length of the curve is not bigger than ECCP_MAX_BIT_LEN
 *     2. after calculation, A1 and A2 will be changed!
 */
uint32_t eccp_pointVerify(eccp_curve_t *curve, uint32_t *Px, uint32_t *Py)
{
	uint32_t wordLen = GET_WORD_LEN(curve->eccp_p_bitLen);
	uint32_t ret;

	//set ecc_p, ecc_p_h, ecc_p_n0, etc.
	ret = pke_set_modulus_and_pre_monts(curve->eccp_p, curve->eccp_p_h, curve->eccp_p_n0, curve->eccp_p_bitLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//pke_pre_calc_mont() may cover A1, so load A1(Px) and other paras here
	pke_load_operand((uint32_t *)(PKE_B(0,g_step)), Px, wordLen);                     //B0 Px
	pke_load_operand((uint32_t *)(PKE_B(1,g_step)), Py, wordLen);                     //B1 Py
	pke_load_operand((uint32_t *)(PKE_A(5,g_step)), curve->eccp_a, wordLen);          //A5 a
	pke_load_operand((uint32_t *)(PKE_A(4,g_step)), curve->eccp_b, wordLen);          //A4 b

	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)(PKE_B(0,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_B(1,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(5,g_step))+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)(PKE_A(4,g_step))+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	pke_set_exe_cfg(PKE_EXE_ECCP_POINT_VER);
	
	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_PVER);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_B(0,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(1,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(5,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(4,g_step)), wordLen<<2);
#endif
		return ret;
	}
	else
	{
		return PKE_SUCCESS;
	}
}


/* function: get ECCP public key from private key(the key pair could be used in SM2/ECDSA/ECDH, etc.)
 * parameters:
 *     curve ---------------------- input, eccp_curve_t curve struct pointer
 *     priKey --------------------- input, private key, big-endian
 *     pubKey --------------------- output, public key, big-endian
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure bit length of the curve is not bigger than ECCP_MAX_BIT_LEN
 */
uint32_t eccp_get_pubkey_from_prikey(eccp_curve_t *curve, uint8_t *priKey, uint8_t *pubKey)
{
	uint32_t nByteLen = GET_BYTE_LEN(curve->eccp_n_bitLen);
	uint32_t nWordLen = GET_WORD_LEN(curve->eccp_n_bitLen);
	uint32_t pByteLen = GET_BYTE_LEN(curve->eccp_p_bitLen);
	uint32_t k[ECCP_MAX_WORD_LEN];
	uint32_t *x;
	uint32_t *y;
	uint32_t ret;

	pke_set_operand_width(curve->eccp_p_bitLen);
	x = (uint32_t *)(PKE_A(0,g_step));
	y = (uint32_t *)(PKE_A(1,g_step));

	k[nWordLen - 1] = 0;   //clear if curve->eccp_n_bitLen is not a multiple of 32
	reverse_byte_array(priKey, (uint8_t *)k, nByteLen);

	//make sure k in [1, n-1]
	ret = uint32_integer_check(k, curve->eccp_n, nWordLen, PKE_ZERO_ALL, PKE_INTEGER_TOO_BIG,
			PKE_SUCCESS);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

#ifdef SUPPORT_SM2
	if(curve == sm2_curve)
	{
		if((k[0] == sm2_curve->eccp_n[0]-1) && (0 == uint32_BigNumCmp(k+1, nWordLen-1, (curve->eccp_n)+1, nWordLen-1)))
		{
			return PKE_INTEGER_TOO_BIG;
		}
		else
		{;}
	}
	else
	{;}
#endif

	//get pubKey
	ret = eccp_pointMul(curve, k, curve->eccp_Gx, curve->eccp_Gy, x, y);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{
		reverse_byte_array((uint8_t *)x, pubKey, pByteLen);
		reverse_byte_array((uint8_t *)y, pubKey+pByteLen, pByteLen);

		return PKE_SUCCESS;
	}
}


/* function: get ECCP key pair(the key pair could be used in SM2/ECDSA/ECDH)
 * parameters:
 *     curve ---------------------- input, eccp_curve_t curve struct pointer
 *     priKey --------------------- output, private key, big-endian
 *     pubKey --------------------- output, public key, big-endian
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure bit length of the curve is not bigger than ECCP_MAX_BIT_LEN
 */
uint32_t eccp_getkey(eccp_curve_t *curve, uint8_t *priKey, uint8_t *pubKey)
{
	uint32_t tmpLen;
	uint32_t nByteLen = GET_BYTE_LEN(curve->eccp_n_bitLen);
	uint32_t ret;

ECCP_GETKEY_LOOP:

	ret = get_rand(priKey, nByteLen);
	if(TRNG_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//make sure k has the same bit length as n
	tmpLen = (curve->eccp_n_bitLen)&7;
	if(tmpLen)
	{
		priKey[0] &= (1<<(tmpLen))-1;
	}
	else
	{;}

	ret = eccp_get_pubkey_from_prikey(curve, priKey, pubKey);
	if(PKE_ZERO_ALL == ret || PKE_INTEGER_TOO_BIG == ret)
	{
		goto ECCP_GETKEY_LOOP;
	}
	else
	{
		return ret;
	}
}

/****************************** ECCp functions finished ********************************/


#ifdef SUPPORT_C25519
/**************************** X25519 & Ed25519 functions *******************************/

/* function: c25519 point mul(random point), Q=[k]P
 * parameters:
 *     curve ---------------------- input, c25519 curve struct pointer
 *     k -------------------------- input, scalar
 *     Pu ------------------------- input, u coordinate of point P
 *     Qu ------------------------- output, u coordinate of point Q
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure input point P is on the curve
 *     2. even if the input point P is valid, the output may be infinite point, in this case return error.
 *     3. please make sure the curve is c25519
 */
uint32_t x25519_pointMul(mont_curve_t *curve, uint32_t *k, uint32_t *Pu, uint32_t *Qu)
{
	uint32_t wordLen = GET_WORD_LEN(curve->p_bitLen);
	uint32_t ret;

	//set ecc_p, ecc_p_h, ecc_p_n0, etc.
	ret = pke_set_modulus_and_pre_monts(curve->p, curve->p_h, curve->p_n0, curve->p_bitLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	pke_load_operand((uint32_t *)PKE_A(0,g_step), Pu, wordLen);                     //A0 Pu
	pke_load_operand((uint32_t *)PKE_B(0,g_step), curve->a24, wordLen);             //B0 a24
	pke_load_operand((uint32_t *)PKE_A(4,g_step), k, wordLen);                      //A4 k

	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)PKE_A(0,g_step)+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)PKE_B(0,g_step)+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)PKE_A(4,g_step)+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)PKE_B(3,g_step)+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	pke_set_exe_cfg(PKE_EXE_CFG_ALL_NON_MONT);

	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_C25519_PMUL);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_A(0,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(4,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(0,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(3,g_step)), wordLen<<2);
#endif
		return ret;
	}
	else
	{;}

	pke_read_operand((uint32_t *)PKE_A(1,g_step), Qu, wordLen);                     //A1 Qu

	return PKE_SUCCESS;
}

#if 0
/* function: out = a^b mod n
 * parameters:
 *     a -------------------------- input, base number, 8 words
 *     b -------------------------- input, exponent number, 8 words
 *     n -------------------------- input, modulus number, 8 words
 *     out ------------------------ output, out = a^b mod n
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure n is odd, b is not zero
 *     2. this function is used in Ed25519 to decode point
 */
uint32_t mod_exp(uint32_t a[8], uint32_t b[8], uint32_t n[8], uint32_t out[8])
{
	uint32_t t[8];
	int32_t cfg_bak, bitLen;
	uint32_t ret;

	pke_pre_calc_mont(n, 256, NULL, NULL);

	cfg_bak = PKE_EXE_CONF;
	pke_set_exe_cfg(PKE_EXE_CFG_ALL_MONT);

	//t = A0 = aR mod n
	ret = pke_modmul_internal(a, (uint32_t *)(PKE_A(3,g_step)), t, Ed25519_WORD_LEN);     //A3: R^2 mod n
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	bitLen = get_valid_bits(b, Ed25519_WORD_LEN);
	bitLen -= 2;
	for(; bitLen>=0; bitLen--)
	{
		ret = pke_modmul_internal((uint32_t *)(PKE_A(0,g_step)), (uint32_t *)(PKE_A(0,g_step)), (uint32_t *)(PKE_A(0,g_step)), Ed25519_WORD_LEN);
		if(PKE_SUCCESS != ret)
		{
			return ret;
		}
		else if(b[bitLen/32] & (1<<(bitLen&31)))
		{
			ret = pke_modmul_internal((uint32_t *)(PKE_A(0,g_step)), t, (uint32_t *)(PKE_A(0,g_step)), Ed25519_WORD_LEN);
			if(PKE_SUCCESS != ret)
			{
				return ret;
			}
			else
			{;}
		}
		else
		{;}
	}

	//t = 1
	pke_set_operand_uint32_value(t, 8, 1);

	//get result
	ret = pke_modmul_internal((uint32_t *)(PKE_A(0,g_step)), t, out, Ed25519_WORD_LEN);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	pke_set_exe_cfg(cfg_bak);

	return PKE_SUCCESS;
}
#endif

/* function: Ed25519 decode point
 * parameters:
 *     in_y ----------------------- input, encoded Ed25519 point
 *     out_x ---------------------- output, x coordinate of input point
 *     out_y ---------------------- output, y coordinate of input point
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1.
 */
uint32_t ed25519_decode_point(uint8_t in_y[32], uint8_t out_x[32], uint8_t out_y[32])
{
	uint32_t u[Ed25519_WORD_LEN];
	uint32_t v[Ed25519_WORD_LEN];
	uint32_t t[Ed25519_WORD_LEN]={0};
	uint32_t t2[Ed25519_WORD_LEN];
	uint32_t t3[Ed25519_WORD_LEN];
	uint32_t ret;

	//get y
	memcpy_(u, in_y, Ed25519_BYTE_LEN);
	u[Ed25519_WORD_LEN-1] &= 0x7FFFFFFF;

	//make sure y < prime p
	if(uint32_BigNumCmp(u, Ed25519_WORD_LEN, ed25519->p, Ed25519_WORD_LEN) >= 0)
	{
		return PKE_INVALID_INPUT;
	}
	else
	{;}

	//set type
	pke_set_exe_cfg(PKE_EXE_CFG_ALL_NON_MONT);

	//set pre-calculated paras
	ret = pke_set_modulus_and_pre_monts(ed25519->p, ed25519->p_h, ed25519->p_n0, ed25519->p_bitLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(u, u, v, Ed25519_WORD_LEN);                        //v = y^2
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	t[0]=1;
	ret = pke_modsub(ed25519->p, v, t, u, Ed25519_WORD_LEN);                     //u = y^2 - 1
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(ed25519->d, v, v, Ed25519_WORD_LEN);               //v = d*y^2
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modadd(ed25519->p, v, t, v, Ed25519_WORD_LEN);                     //v = d*y^2 + 1
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(v, v, t2, Ed25519_WORD_LEN);                       //t2 = v^2
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(v, t2, t3, Ed25519_WORD_LEN);                      //t3 = v^3
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(t3, u, t, Ed25519_WORD_LEN);                       //t = u*v^3
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(t2, t2, t2, Ed25519_WORD_LEN);                     //t2 = v^4
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(t2, t3, t2, Ed25519_WORD_LEN);                     //t2 = v^7
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(t2, u, t2, Ed25519_WORD_LEN);                      //t2 = u*v^7
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//t3 = (p-5)/8
	uint32_copy(t3, ed25519->p, Ed25519_WORD_LEN);
	t3[0] -= 5;
	Big_Div2n(t3, Ed25519_WORD_LEN, 3);

	//t2 = (u*v^7 )^((p-5)/8)
#if 0
	ret = mod_exp(t2, t3, ed25519->p, t2);
#else
	ret = pke_modexp(ed25519->p, t3, t2, t2, Ed25519_WORD_LEN, Ed25519_WORD_LEN);
	pke_set_exe_cfg(PKE_EXE_CFG_ALL_NON_MONT);
#endif
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(t2, t, t, Ed25519_WORD_LEN);                       //t = x = (u*v^3)*(u*v^7 )^((p-5)/8)
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(t, t, t2, Ed25519_WORD_LEN);                       //t2 = x^2
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = pke_modmul_internal(t2, v, t2, Ed25519_WORD_LEN);                      //t2 = v*x^2
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	if(0 == uint32_BigNumCmp(t2, Ed25519_WORD_LEN, u, Ed25519_WORD_LEN))         //if v x^2 = u (mod p), x is a square root.
	{
		goto result;
	}
	else
	{;}

	ret = pke_sub(ed25519->p, u, t3, Ed25519_WORD_LEN);                          //t3 = -u mod p
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else if(0 == uint32_BigNumCmp(t2, Ed25519_WORD_LEN, t3, Ed25519_WORD_LEN))
	{
		//v = (p-1)/4
		uint32_copy(v, ed25519->p, Ed25519_WORD_LEN);
		v[0] -= 1;
		Big_Div2n(v, Ed25519_WORD_LEN, 2);

		//t2 = 2
		pke_set_operand_uint32_value(t2, Ed25519_WORD_LEN, 2);

		//u = 2^((p-1)/4)
#if 0
		ret = mod_exp(t2, v, ed25519->p, u);
#else
		ret = pke_modexp(ed25519->p, v, t2, u, Ed25519_WORD_LEN, Ed25519_WORD_LEN);
		pke_set_exe_cfg(PKE_EXE_CFG_ALL_NON_MONT);
#endif
		if(PKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{;}

		ret = pke_modmul_internal(t, u, t, Ed25519_WORD_LEN);                    //t = x*(2^((p-1)/4))
		if(PKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{;}

		goto result;
	}
	else
	{;}

	return PKE_INVALID_INPUT;   //root not exist

result:

	//if x=0 and x is odd, decode fail
	if(uint32_BigNum_Check_Zero(t, Ed25519_WORD_LEN) && (in_y[Ed25519_BYTE_LEN-1] & 0x80))
	{
		return PKE_INVALID_INPUT;
	}
	else
	{;}

	//get out_x
	if((uint8_t)((t[0]&1)<<7) == (in_y[Ed25519_BYTE_LEN-1] & 0x80))
	{
		memcpy_(out_x, t, Ed25519_BYTE_LEN);
	}
	else
	{
		ret = pke_sub(ed25519->p, t, v, Ed25519_WORD_LEN);                             //v = -x mod p
		if(PKE_SUCCESS != ret)
		{
			return ret;
		}
		else
		{
			memcpy_(out_x, v, Ed25519_BYTE_LEN);
		}
	}

	//get out_y
	memcpy_(out_y, in_y, Ed25519_BYTE_LEN);
	out_y[Ed25519_BYTE_LEN-1] &= 0x7F;

	return PKE_SUCCESS;
}


/* function: edwards25519 curve point mul(random point), Q=[k]P
 * parameters:
 *     curve ---------------------- input, edwards25519 curve struct pointer
 *     k -------------------------- input, scalar
 *     Px ------------------------- input, x coordinate of point P
 *     Py ------------------------- input, y coordinate of point P
 *     Qx ------------------------- output, x coordinate of point Q
 *     Qy ------------------------- output, y coordinate of point Q
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure input point P is on the curve
 *     2. even if the input point P is valid, the output may be neutral point (0, 1), it is valid
 *     3. please make sure the curve is edwards25519
 *     4. k could not be zero now.
 */
uint32_t ed25519_pointMul(edward_curve_t *curve, uint32_t *k, uint32_t *Px, uint32_t *Py,
		uint32_t *Qx, uint32_t *Qy)
{
	uint32_t wordLen = GET_WORD_LEN(curve->p_bitLen);
	uint32_t ret;

	//set ecc_p, ecc_p_h, ecc_p_n0, etc.
	ret = pke_set_modulus_and_pre_monts(curve->p, curve->p_h, curve->p_n0, curve->p_bitLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	pke_load_operand((uint32_t *)PKE_A(1,g_step), Px, wordLen);                    //A1 Px
	pke_load_operand((uint32_t *)PKE_A(2,g_step), Py, wordLen);                    //A2 Py
	pke_load_operand((uint32_t *)PKE_B(0,g_step), curve->d, wordLen);              //B0 d
	pke_load_operand((uint32_t *)PKE_A(0,g_step), k, wordLen);                     //A0 k

	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)PKE_A(1,g_step)+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)PKE_A(2,g_step)+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)PKE_B(0,g_step)+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)PKE_A(0,g_step)+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	pke_set_exe_cfg(PKE_EXE_CFG_ALL_NON_MONT);

	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_Ed25519_PMUL);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_A(0,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(1,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(2,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(0,g_step)), wordLen<<2);
#endif
		return ret;
	}
	else
	{;}

	pke_read_operand((uint32_t *)PKE_A(1,g_step), Qx, wordLen);                    //A1 Qx
	if(NULL != Qy)
	{
		pke_read_operand((uint32_t *)PKE_A(2,g_step), Qy, wordLen);                //A2 Qx
	}
	else
	{;}

	return PKE_SUCCESS;
}


/* function: edwards25519 point add, Q=P1+P2
 * parameters:
 *     curve ---------------------- input, edwards25519 curve struct pointer
 *     P1x ------------------------ input, x coordinate of point P1
 *     P1y ------------------------ input, y coordinate of point P1
 *     P2x ------------------------ input, x coordinate of point P2
 *     P2y ------------------------ input, y coordinate of point P2
 *     Qx ------------------------- output, x coordinate of point Q=P1+P2
 *     Qy ------------------------- output, y coordinate of point Q=P1+P2
 * return: PKE_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure input point P1 and P2 are both on the curve
 *     2. the output point may be neutral point (0, 1), it is valid
 *     3. please make sure the curve is edwards25519
 */
uint32_t ed25519_pointAdd(edward_curve_t *curve, uint32_t *P1x, uint32_t *P1y, uint32_t *P2x, uint32_t *P2y,
		uint32_t *Qx, uint32_t *Qy)
{
	uint32_t wordLen = GET_WORD_LEN(curve->p_bitLen);
	uint32_t ret;

	//set ecc_p, ecc_p_h, ecc_p_n0, etc.
	ret = pke_set_modulus_and_pre_monts(curve->p, curve->p_h, curve->p_n0, curve->p_bitLen);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//pke_pre_calc_mont() may cover some addresses, so load parameters here
	pke_load_operand((uint32_t *)PKE_A(1,g_step), P1x, wordLen);                      //A1 P1x
	pke_load_operand((uint32_t *)PKE_A(2,g_step), P1y, wordLen);                      //A2 P1y
	pke_load_operand((uint32_t *)PKE_B(1,g_step), P2x, wordLen);                      //B1 P2x
	pke_load_operand((uint32_t *)PKE_B(2,g_step), P2y, wordLen);                      //B2 P2y
	pke_load_operand((uint32_t *)PKE_B(0,g_step), curve->d, wordLen);                 //B0 d

	if((g_step/4) > wordLen)
	{
		uint32_clear((uint32_t *)PKE_A(1,g_step)+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)PKE_A(2,g_step)+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)PKE_B(1,g_step)+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)PKE_B(2,g_step)+wordLen, (g_step/4)-wordLen);
		uint32_clear((uint32_t *)PKE_B(0,g_step)+wordLen, (g_step/4)-wordLen);
	}
	else
	{;}

	pke_set_exe_cfg(PKE_EXE_CFG_ALL_NON_MONT);

	ret = pke_set_micro_code_start_wait_return_code(MICROCODE_Ed25519_PADD);
	if(PKE_SUCCESS != ret)
	{
#ifdef PKE_SEC
		get_rand_fast((uint8_t *)(PKE_A(1,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_A(2,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(0,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(1,g_step)), wordLen<<2);
		get_rand_fast((uint8_t *)(PKE_B(2,g_step)), wordLen<<2);
#endif
		return ret;
	}
	else
	{;}

	pke_read_operand((uint32_t *)PKE_A(1,g_step), Qx, wordLen);                       //A1 Qx
	pke_read_operand((uint32_t *)PKE_A(2,g_step), Qy, wordLen);                       //A2 Qy

	return PKE_SUCCESS;
}

/**************************** X25519 & Ed25519 finished ********************************/
#endif
