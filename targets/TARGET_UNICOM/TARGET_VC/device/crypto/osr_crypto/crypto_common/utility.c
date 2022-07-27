#include <stdio.h>
#include "utility.h"


#ifdef PKE_PRINT_BUF
//#include "xil_printf.h"

void print_buf_U8(uint8_t buf[], uint32_t byteLen, char name[])
{
	uint32_t i;

	printf("\r\n %s: ",name); fflush(stdout);
	for(i=0; i<byteLen; i++)
	{
		//if(i%16 ==0 && i>0)
		//	printf("\r\n");
		//printf("%02x", buf[byteLen-1-i]);
		printf("%02x", buf[i]);
	}

	printf("\r\n");
}

void print_buf_U32(uint32_t buf[], uint32_t wordLen, char name[])
{
	uint32_t i;

	printf("\r\n %s: %08lx\r\n",name, (uint32_t)buf);fflush(stdout);
	for(i=0; i<wordLen; i++)
	{
		//if(i%16 ==0 && i>0)
		//	printf("\r\n");
		//printf("%08x", buf[wordLen-1-i]);
		printf("%08lx", buf[i]);fflush(stdout);
	}

	printf("\r\n");fflush(stdout);
}

void print_BN_buf_U32(uint32_t buf[], uint32_t wordLen, char name[])
{
	uint32_t i;

	printf("\r\n %08lx %s: ", (uint32_t)buf, name);fflush(stdout);
	for(i=0; i<wordLen; i++)
	{
		//if(i%16 ==0 && i>0)
		//	printf("\r\n");
		printf("%08lx", buf[wordLen-1-i]);
	}
	printf("\r\n");fflush(stdout);
}
#endif


void memcpy_(void *dst, void *src, uint32_t size)
{
	uint8_t *a = (uint8_t *)dst;
	uint8_t *b = (uint8_t *)src;
#if 0
	while(size--)
	{
		*a++ = *b++;
	}
#else
	uint32_t *aa = (uint32_t *)dst;
	uint32_t *bb = (uint32_t *)src;
	uint32_t i, count, tmp;

	if((((uint32_t)dst) & 3) || (((uint32_t)src) & 3))
	{
		while(size--)
		{
			*a++ = *b++;
		}
	}
	else
	{
		count = size/4;
		for(i=0; i<count; i++)
		{
			*aa++ = *bb++;
		}

		tmp = size&3;
		if(tmp)
		{
			a+=(size&(~0x03));
			b+=(size&(~0x03));
			while(tmp--)
			{
				*a++ = *b++;
			}
		}
		else
		{;}
	}
#endif
}

void memset_(void *dst, uint8_t value, uint32_t size)
{
	uint8_t *a = (uint8_t *)dst;
#if 0
	while(size--)
	{
		*a++ = value;
	}
#else
	uint32_t i, count, tmp;

	tmp = ((uint32_t)dst) & 3;
	if(tmp)
	{
		if(size > 4-tmp)
		{
			for(i=0; i<4-tmp; i++)
			{
				*a++ = value;
			}
			size -= (4-tmp);
		}
		else
		{
			for(i=0; i<size; i++)
			{
				*a++ = value;
			}
			return;
		}
	}
	else
	{;}

	count = size/4;
	if(count)
	{
		tmp = value;
		tmp = (tmp<<8)|value;
		tmp = (tmp<<8)|value;
		tmp = (tmp<<8)|value;
		for(i=0; i<count; i++)
		{
			*((uint32_t *)a) = tmp;
			a+=4;
		}
	}
	else
	{;}

	tmp = size&3;
	if(tmp)
	{
		for(i=0; i<tmp; i++)
		{
			*a++ = value;
		}
	}
	else
	{;}
#endif
}

int8_t memcmp_(void *m1, void *m2, uint32_t size)
{
	int8_t *a = (int8_t *)m1;
	int8_t *b = (int8_t *)m2;
	int8_t c;

	while(size--)
	{
		c = (*a++ - *b++);
		if(c)
		{
			return c;
		}
		else
		{;}
	}

	return 0;
}

/* function: set uint32 buffer
 * parameters:
 *     a -------------------------- output, output word buffer
 *     value ---------------------- input, input word value
 *     wordLen -------------------- input, word length of buffer a
 * return: none
 * caution:
 */
void uint32_set(uint32_t *a, uint32_t value, uint32_t wordLen)
{
	while(wordLen)
	{
		a[--wordLen] = value;
	}
}

/* function: copy uint32 buffer
 * parameters:
 *     dst ------------------------ output, output word buffer 
 *     src ------------------------ input, input word buffer
 *     wordLen -------------------- input, word length of buffer dst or src
 * return: none
 * caution:  
 */
void uint32_copy(uint32_t *dst, uint32_t *src, uint32_t wordLen)
{
	uint32_t i;

	if(dst != src)
	{
		for(i=0; i<wordLen; i++)
		{
			dst[i] = src[i];
		}
	}
	else
	{;}
}


/* function: clear uint32 buffer
 * parameters:
 *     a -------------------------- input&output, word buffer a
 *     aWordLen ------------------- input, word length of buffer a
 * return: none
 * caution:  
 */
void uint32_clear(uint32_t *a, uint32_t wordLen)
{
#if 1
	volatile uint32_t i = wordLen;

	while(i)
	{
		a[--i] = 0;
	}
#else
	volatile uint32_t i = 0;
	for(i=0;i<wordLen;i++)
		a[i] = 0;
#endif
}

/*
static void uint32_sleep1(uint32_t count)
{
	volatile uint32_t a=0;
	volatile uint32_t b=0;
	volatile uint32_t result=0;
	volatile uint32_t i;

	for(i=0;i<count;i++)
	{
		result |= ((a+i) - (b+i));
	}
}

static void uint32_sleep2(uint32_t count)
{
	volatile uint32_t a=0;
	volatile uint32_t b=0;
	volatile uint32_t result=0;
	volatile uint32_t i;

	for(i=0;i<count;i++)
	{
		result |= ((a+i) ^ (b+i));
	}
} */


/* function: sleep for a while
 * parameters:
 *     count ---------------------- input, count  
 * return: none
 * caution:  

void uint32_sleep(uint32_t count, uint8_t rand)
{
	uint8_t rand1 = rand & 0x01;

	if(0 == rand1)
	{
		uint32_sleep1(count);
	}
	else
	{
		uint32_sleep2(count);
	}
} */


/* function: convert 0x1122334455667788 to 0x4433221188776655
 * parameters:
 *     in ------------------------- source address
 *     out ------------------------ destination address
 *     wordLen -------------------- word length of in/out
 * return: none
 * caution:

void uint32_endian_reverse(uint8_t *in, uint8_t *out, uint32_t wordLen)
{
	uint8_t tmp;

	if(in == out)
	{
		while(wordLen>0)
		{
			tmp=*in;
			*in=*(in+3);
			*(in+3)=tmp;
			in+=1;
			tmp=*in;
			*in=*(in+1);
			*(in+1)=tmp;
			wordLen--;
			in+=3;
		}
	}
	else
	{
		while(wordLen>0)
		{
			*(out)   = *(in+3);
			*(out+1) = *(in+2);
			*(out+2) = *(in+1);
			*(out+3) = *(in);
			wordLen--;
			in += 4;
			out += 4;
		}
	}
} */


/* function: reverse word array
 * parameters:
 *     in ------------------------- input, input buffer
 *     out ------------------------ output, output buffer
 *     wordLen -------------------- input, word length of in or out
 * return: none
 * caution:
 *    1. in and out could point the same buffer

void reverse_word_array(uint8_t *in, uint32_t *out, uint32_t wordLen)
{
	uint32_t idx, round = wordLen >> 1;
	uint32_t tmp;
	uint32_t *p_in;

	if(((uint32_t)(in))&3)
	{
		memcpy_(out, in, wordLen<<2);
		p_in = out;
	}
	else
	{
		p_in = (uint32_t *)in;
	}

	for (idx = 0; idx < round; idx++)
	{
		tmp = p_in[idx];
		out[idx] = p_in[wordLen - 1 - idx];
		out[wordLen - 1 - idx] = tmp;
	}

	if ((wordLen & 0x1) && (p_in != out))
	{
		out[round] = p_in[round];
	}
	else
	{;}
} */


/* function: reverse byte array
 * parameters:
 *     in ------------------------- input, input buffer
 *     out ------------------------ output, output buffer
 *     byteLen -------------------- input, byte length of in or out
 * return: none
 * caution:
 *    1. in and out could point the same buffer
 */
void reverse_byte_array(uint8_t *in, uint8_t *out, uint32_t byteLen)
{
	uint32_t idx, round = byteLen >> 1;
	uint8_t tmp;

	for (idx = 0; idx < round; idx++)
	{
		tmp = in[idx];
		out[idx] = in[byteLen - 1 - idx];
		out[byteLen - 1 - idx] = tmp;
	}

	if ((byteLen & 0x1) && (in != out))
	{
		out[round] = in[round];
	}
	else
	{;}
}


/* function: reverse byte order in every uint32_t word
 * parameters:
 *     in ------------------------- input, input byte buffer
 *     out ------------------------ output, output word buffer
 *     bytelen -------------------- input, byte length of buffer in or out
 * return: none
 * caution:  1. byteLen must be multiple of 4

void reverse_word(uint8_t *in, uint8_t *out, uint32_t bytelen)
{
	uint32_t i, len;
	uint8_t tmp;
	uint8_t *p = in;

	if(in == out)
	{
		while(bytelen>0)
		{
			tmp=*p;
			*p=*(p+3);
			*(p+3)=tmp;
			p+=1;
			tmp=*p;
			*p=*(p+1);
			*(p+1)=tmp;
			bytelen-=4;
			p+=3;
		}
	}
	else
	{
		for (i = 0; i < bytelen; i++)
		{
			len = i >> 2;
			len = len << 3;
			out[i] = p[len + 3 - i];
		}
	}
}*/


/* function: reverse word order
 * parameters:
 *     in ------------------------- input, input word buffer
 *     out ------------------------ output, output word buffer
 *     wordLen -------------------- input, word length of buffer in or out
 *     reverse_word --------------- input, whether to reverse byte order in every word, 0:no, other:yes
 * return: none
 * caution:
 *     1. in DAM mode, the memory may be accessed by words, not by bytes, this function is designed
 *        for the case

void dma_reverse_word_array(uint32_t *in, uint32_t *out, uint32_t wordLen, uint32_t reverse_word)
{
	uint32_t i, j;
	uint32_t tmp;
	uint32_t *p=out;

	if(in == out)
	{
		for(i=0; i<wordLen; i+=4)
		{
			for (j = 0; j < 2; j++)
			{
				tmp = p[j];
				p[j] = p[4 - 1 - j];
				p[4 - 1 - j] = tmp;
			}
			p+=4;
		}
	}
	else
	{
		for(i=0; i<wordLen; i+=4)
		{
			p[0] = in[3];
			p[1] = in[2];
			p[2] = in[1];
			p[3] = in[0];
			p+=4;
			in+=4;
		}
	}

	if(reverse_word)
	{
		for (i = 0; i < wordLen; i++)
		{
			tmp = *out;
			*out = tmp&0xFF;
			*out <<= 8;
			*out |= (tmp>>8)&0xFF;
			*out <<= 8;
			*out |= (tmp>>16)&0xFF;
			*out <<= 8;
			*out |= (tmp>>24)&0xFF;

			out++;
		}
	}
	else
	{;}
} */


/* function: C = A XOR B
 * parameters:
 *     A -------------------------- input, byte buffer a
 *     B -------------------------- input, byte buffer b
 *     C -------------------------- output, C = A XOR B
 *     byteLen -------------------- input, byte length of A,B,C
 * return: none
 * caution:
 */
void uint8_XOR(uint8_t *A, uint8_t *B, uint8_t *C, uint32_t byteLen)
{
	uint32_t i;

	for(i=0; i<byteLen; i++)
	{
		C[i] = A[i] ^ B[i];
	}
}


/* function: C = A XOR B
 * parameters:
 *     A -------------------------- input, word buffer a
 *     B -------------------------- input, word buffer b
 *     C -------------------------- output, C = A XOR B
 *     byteLen -------------------- input, word length of A,B,C
 * return: none
 * caution:
 */
void uint32_XOR(uint32_t *A, uint32_t *B, uint32_t *C, uint32_t wordLen)
{
	uint32_t i;

	for(i=0; i<wordLen; i++)
	{
		C[i] = A[i] ^ B[i];
	}
}


/* function: get real bit length of big number a of wordLen words
 */
uint32_t get_valid_bits(const uint32_t *a, uint32_t wordLen)
{
	uint32_t i = 0;
	uint32_t j = 0;

	if(0 == wordLen)
	{
		return 0;
	}
	else
	{;}

	for (i = wordLen; i > 0; i--)
	{
		if (a[i - 1])
		{
			break;
		}
		else
		{;}
	}

	if(0 == i)
	{
		return 0;
	}
	else
	{;}

	for (j = 32; j > 0; j--)
	{
		if (a[i - 1] & (((uint32_t)0x1) << (j - 1)))
		{
			break;
		}
		else
		{;}
	}

	return ((i - 1) << 5) + j;
}


/* function: get real word lenth of big number a of max_words words
 * parameters:
 *     a -------------------------- input, big integer a
 *     max_words ------------------ input, max word length of a
 * return: real word length of big number a
 * caution:
 */
uint32_t get_valid_words(uint32_t *a, uint32_t max_words)
{
	uint32_t i;

	for (i = max_words; i > 0; i--)
	{
		if (a[i - 1])
		{
			return i;
		}
		else
		{;}
	}

	return 0;
}


/* function: check whether big number or uint8_t buffer a is all zero or not
 * parameters:
 *     a -------------------------- input, byte buffer a
 *     aByteLen ------------------- input, byte length of a
 * return: 0(a is not zero),1(a is all zero)
 * caution:
 */
uint8_t uint8_BigNum_Check_Zero(uint8_t a[], uint32_t aByteLen)
{
	uint32_t i;

	for(i=0; i<aByteLen; i++)
	{
		if(a[i])
		{
			return 0;
		}
		else
		{;}
	}

	return 1;
}


/* function: check whether big number or uint32_t buffer a is all zero or not
 * parameters:
 *     a -------------------------- input, big integer or word buffer a
 *     aWordLen ------------------- input, word length of a
 * return: 0(a is not zero), 1(a is all zero)
 * caution:
 */
uint32_t uint32_BigNum_Check_Zero(uint32_t a[], uint32_t aWordLen)
{
	uint32_t i;

	for(i=0; i<aWordLen; i++)
	{
		if(a[i])
		{
			return 0;
		}
		else
		{;}
	}

	return 1;
}


/* function: compare big integer a and b
 * parameters:
 *     a -------------------------- input, big integer a
 *     aWordLen ------------------- input, word length of a
 *     b -------------------------- input, big integer b
 *     bWordLen ------------------- input, word length of b
 * return:
 *     0:a=b,   1:a>b,   -1: a<b
 * caution:
 */
int32_t uint32_BigNumCmp(uint32_t *a, uint32_t aWordLen, uint32_t *b, uint32_t bWordLen)
{
	int32_t i;

	aWordLen = get_valid_words(a, aWordLen);
	bWordLen = get_valid_words(b, bWordLen);

	if(aWordLen > bWordLen)
	{
		return 1;
	}
	else if(aWordLen < bWordLen)
	{
		return -1;
	}
	else
	{;}

	for(i=(aWordLen-1);i>=0;i--)
	{
		if(a[i] > b[i])
		{
			return 1;
		}
		else if(a[i] < b[i])
		{
			return -1;
		}
		else
		{;}
	}

	return 0;
}

/* function: for a = b*2^t, b is odd, get t
 * parameters:
 *     a -------------------------- big integer a
 * return:
 *     number of multiple by 2, for a
 * caution:
 *     1. make sure a != 0
 */
uint32_t Get_Multiple2_Number(uint32_t a[])
{
	uint32_t t, i=0, j=0;

	while(0 == (a[i]))
	{
		i++;
	}

	t = a[i];
	while(!(t&1))
	{
		j++;
		t>>=1;
	}

	return (i<<5)+j;
}


/* function: a = a/(2^n)
 * parameters:
 *     a -------------------------- big integer a
 *     aWordLen ------------------- word length of a
 *     n -------------------------- exponent of 2^n
 * return:
 *     word length of a = a/(2^n)
 * caution:
 *     1. make sure aWordLen is real word length of a
 *     2. to make sure aWordLen-1 is available, so data type of aWordLen is int32_t, not uint32_t
 *     3. please make sure aWordLen*32 is not less than n
 */
uint32_t Big_Div2n(uint32_t a[], int32_t aWordLen, uint32_t n)
{
	int32_t i;
	uint32_t j;

	aWordLen = get_valid_words(a, aWordLen);

	if(0 == n)
	{
		return aWordLen;
	}
	else if(!aWordLen)
	{
		return 0;
	}
	else
	{;}

	//now a is not zero(aWordLen is not zero), and n is not zero either.

	if(n<32)
	{
		for(i=0; i<aWordLen-1; i++)
		{
			a[i] >>= n;
			a[i] |= (a[i+1]<<(32-n));
		}
		a[i] >>= n;

		if(!a[i])
		{
			return i;
		}
		else
		{
			return aWordLen;
		}
	}
	else
	{;}

	j=n>>5; //j=n/32;
	n&=31;  //n=n%32;

	if(j<aWordLen)
	{
		if(n)   //n is in [1, 31]
		{
			for(i=0; i<aWordLen-(int32_t)j-1; i++)
			{
				a[i] = a[i+j]>>n;
				a[i] |= (a[i+j+1]<<(32-n));
			}
			a[i] = a[i+j]>>n;
			uint32_clear(a+aWordLen-j, j);

			if(!a[i])
			{
				return i;
			}
			else
			{
				return aWordLen-j;
			}
		}
		else    //n is 0
		{
			for(i=0; i<aWordLen-(int32_t)j; i++)
			{
				a[i] = a[i+j];
			}
			uint32_clear(a+aWordLen-j, j);

			return aWordLen-j;
		}
	}
	else
	{
		uint32_clear(a, aWordLen);
		return 0;
	}
}


/* Function: check whether a is equal to 1 or not
 * Parameters:
 *     a ---------------- pointer to uint32_t big integer a
 *     aWordLen --------- word length of big integer a
 * Return: 1(a is 1), 0(a is not 1)
 * Caution:
 */
uint8_t Bigint_Check_1(uint32_t a[], uint32_t aWordLen)
{
	uint32_t i;

	if(!aWordLen)
	{
		return 0;
	}
	else if(a[0] != 1)
	{
		return 0;
	}
	else
	{;}

	for(i=1; i<aWordLen; i++)
	{
		if(a[i])
		{
			return 0;
		}
		else
		{;}
	}

	return 1;
}


/* function: check whether a is equal to p-1 or not
 * parameters:
 *     a ---------------- pointer to uint32_t big integer a
 *     p ---------------- pointer to uint32_t big integer p, p must be odd
 *     wordLen ---------- word length of a and p
 * return: 1(a is p-1), 0(a is not p-1)
 * caution:
 *     1. make sure p is odd
 */
uint8_t Bigint_Check_p_1(uint32_t a[], uint32_t p[], uint32_t wordLen)
{
	uint32_t i;

	if(!wordLen)
	{
		return 0;
	}
	else if(a[0] != p[0] - 1)
	{
		return 0;
	}
	else
	{;}

	for(i=1; i<wordLen; i++)
	{
		if(a[i] != p[i])
		{
			return 0;
		}
		else
		{;}
	}

	return 1;
}


/* function: check whether integer k is in [1, n-1]
 * parameters:
 *     k -------------------------- input, big number k
 *     n -------------------------- input, big number n
 *     wordLen -------------------- input, word length of k and n
 * return:
 *     ret_zero ------------------- k is zero
 *     ret_big -------------------- k is greater/bigger than or equal to n
 *     ret_success ---------------- k is in [1, n-1]
 * caution:
 *     1.
 */
uint32_t uint32_integer_check(uint32_t *k, uint32_t *n, uint32_t wordLen, uint32_t ret_zero, uint32_t ret_big,
		uint32_t ret_success)
{
	if(uint32_BigNum_Check_Zero(k, wordLen))
	{
		return ret_zero;
	}
	else if(uint32_BigNumCmp(k, wordLen, n, wordLen) >= 0)
	{
		return ret_big;
	}
	else
	{;}

	return ret_success;
}

