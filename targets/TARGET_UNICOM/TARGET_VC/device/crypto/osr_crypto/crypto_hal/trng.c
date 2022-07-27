#include <stdio.h>
#include "../crypto_include/utility.h"
#include "trng.h"


static uint32_t error_counter = 0;

typedef uint32_t GET_RAND_WORDS(uint32_t *a, uint32_t words);


/* function: get trng IP version
 * parameters: none
 * return: trng IP version
 * caution:
 */
uint32_t trng_get_version(void)
{
	return TRNG_VERSION;
}


/* function: TRNG global interruption enable
 * parameters: none
 * return: none
 * caution:
 */
void trng_global_int_enable(void)
{
	volatile uint32_t flag = (((uint32_t)1)<<TRNG_GLOBAL_INT_OFFSET);

	TRNG_CR |= flag;
}


/* function: TRNG global interruption disable
 * parameters: none
 * return: none
 * caution:
 */
void trng_global_int_disable(void)
{
	volatile uint32_t mask = ~(((uint32_t)1)<<TRNG_GLOBAL_INT_OFFSET);

	TRNG_CR &= mask;
}


/* function: TRNG empty-read interruption enable
 * parameters: none
 * return: none
 * caution:
 *     1. works when global interruption is enabled
 */
void trng_empty_read_int_enable(void)
{
	volatile uint32_t flag = (((uint32_t)1)<<TRNG_READ_EMPTY_INT_OFFSET);

	TRNG_CR |= flag;
}


/* function: TRNG empty-read interruption disable
 * parameters: none
 * return: none
 * caution:
 */
void trng_empty_read_int_disable(void)
{
	volatile uint32_t mask = ~(((uint32_t)1)<<TRNG_READ_EMPTY_INT_OFFSET);

	TRNG_CR &= mask;
}


/* function: TRNG data interruption enable
 * parameters: none
 * return: none
 * caution:
 *     1. works when global interruption is enabled
 */
void trng_data_int_enable(void)
{
	volatile uint32_t flag = (((uint32_t)1)<<TRNG_DATA_INT_OFFSET);

	TRNG_CR |= flag;
}


/* function: TRNG data interruption disable
 * parameters: none
 * return: none
 * caution:
 */
void trng_data_int_disable(void)
{
	volatile uint32_t mask = ~(((uint32_t)1)<<TRNG_DATA_INT_OFFSET);

	TRNG_CR &= mask;
}


/* function: TRNG enable
 * parameters: none
 * return: none
 * caution:
 */
void trng_enable(void)
{
	volatile uint32_t flag = 1;
	volatile uint32_t i;

	TRNG_CR |= flag;

	//sleep for a while
	i=0xFFF;
	while(i--)
	{;}
}


/* function: TRNG disable
 * parameters: none
 * return: none
 * caution:
 */
void trng_disable(void)
{
	volatile uint32_t mask = ~((uint32_t)1);

	TRNG_CR &= mask;
}


/* function: set RO entropy config
 * parameters:
 *     cfg ------------------------ RO entropy config, only the low 4 bits are valid, every bit
 *                                  indicates one RO entropy, the MSB is RO 0, and LSB is RO 3
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 *     1. only the low 4 bits of cfg are valid
 *     2. if the low 4 bits of cig is 0, that means to disable all RO entropy
 */
uint32_t trng_ro_entropy_config(uint8_t cfg)
{
	volatile uint32_t mask = ~(0x0000000F<<TRNG_RO_ENTROPY_OFFSET);

	if(cfg > 15)
	{
		return TRNG_INVALID_INPUT;
	}
	else
	{;}

	TRNG_CR &= mask;
	TRNG_CR |= (((uint32_t)cfg)&0x0000000F)<<TRNG_RO_ENTROPY_OFFSET;

	return TRNG_SUCCESS;
}


/* function: set sub RO entropy config
 * parameters:
 *     sn ------------------------- input, RO entropy source series number, must be in [0,3]
 *     value ---------------------- input, the config value of RO sn
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 */
uint32_t trng_ro_sub_entropy_config(uint8_t sn, uint16_t cfg)
{
	volatile uint32_t mask_high = ~0xFFFF0000;
	volatile uint32_t mask_low  = ~0x0000FFFF;

	switch(sn)
	{
		case 0:
		RO_SRC_EN1 &= mask_high;
		RO_SRC_EN1 |= ((uint32_t)cfg)<<16;
		break;

		case 1:
		RO_SRC_EN1 &= mask_low;
		RO_SRC_EN1 |= (uint32_t)cfg;
		break;

		case 2:
		RO_SRC_EN2 &= mask_high;
		RO_SRC_EN2 |= ((uint32_t)cfg)<<16;
		break;

		case 3:
		RO_SRC_EN2 &= mask_low;
		RO_SRC_EN2 |= (uint32_t)cfg;
		break;

		default:
			return TRNG_INVALID_INPUT;
	}

	return TRNG_SUCCESS;
}


/* function: set TRNG mode
 * parameters:
 *     with_post_processing ------- 0:no,  other:yes
 * return: none
 * caution:
 */
void trng_set_mode(uint8_t with_post_processing)
{
	volatile uint32_t mask = ~((uint32_t)1);
	volatile uint32_t flag = 1;
	volatile uint32_t clear_flag = 0x00000007;

	if(with_post_processing)
	{
		TRNG_MSEL |= flag;
	}
	else
	{
		TRNG_MSEL &= mask;
	}

	TRNG_SR |= clear_flag; //write 1 to clear
}


/* function: reseed TRNG(works when DRBG is enabled)
 * parameters: none
 * return: none
 * caution:
 *     1. used for DRBG
 */
void trng_reseed(void)
{
	volatile uint32_t flag = 1;
	volatile uint32_t clear_flag = 0x00000007;

	TRNG_RESEED |= flag;

	TRNG_SR |= clear_flag; //write 1 to clear
}


/* function: TRNG set frequency
 * parameters:
 *     freq ----------------------- input, frequency config, must be in [0,3], and
 *                                  0: 1/4 of input frequency,
 *                                  1: 1/8 ...,
 *                                  2: 1/16 ...,
 *                                  3: 1/32 ...,
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 */
uint32_t trng_set_freq(uint8_t freq)
{
	if(freq > 3)
	{
		return TRNG_INVALID_INPUT;
	}
	else
	{;}

	SCLK_FREQ = freq;

	return TRNG_SUCCESS;
}


/* function: get some rand words
 * parameters:
 *     a -------------------------- output, random words
 *     words ---------------------- input, word number of output, must be in [1, 8]
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the two parameters are valid
 */
uint32_t get_rand_uint32(uint32_t *a, uint32_t words)
{
	volatile uint32_t DT_ready_flag = 2;
	volatile uint32_t HT_error_flag = 1;
	uint32_t i;

	while(0 == (TRNG_SR & DT_ready_flag))
	{
		if(TRNG_SR & HT_error_flag)
		{
			return TRNG_HT_ERROR;
		}
		else
		{;}
	}

	for(i=0; i<words; i++)
	{
		*(a++) = TRNG_DR;  //printf("\r\n %08x", *(a-1));
	}

	TRNG_SR |= DT_ready_flag;  //clear

	return TRNG_SUCCESS;
}


/* function: get some rand words(with reseed)
 * parameters:
 *     a -------------------------- output, random words
 *     words ---------------------- input, word number of output, must be in [1, 8]
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the two parameters are valid
 */
uint32_t get_rand_uint32_with_reseed(uint32_t *a, uint32_t words)
{
	volatile uint32_t DT_ready_flag = 2;
	volatile uint32_t HT_error_flag = 1;
	volatile uint32_t clear_flag = 7;
	uint32_t i;

	trng_reseed();

	while(0 == (TRNG_SR & DT_ready_flag))
	{
		if(TRNG_SR & HT_error_flag)
		{
			trng_disable();
			TRNG_SR |= clear_flag;  //clear (alarm) status
			trng_enable();

			//if error times does not exceed the threshold, reset and go on, otherwise return error
			error_counter++;
			if(error_counter >= TRNG_ERROR_COUNTER_THRESHOLD)
			{
				error_counter = 0;
				return TRNG_HT_ERROR;
			}
			else
			{;}
		}
		else
		{;}
	}

	for(i=0; i<words; i++)
	{
		*(a++) = TRNG_DR;  //printf("\r\n %08x", *(a-1));
	}

	TRNG_SR |= DT_ready_flag;  //clear

	return TRNG_SUCCESS;
}

#include "vc6330.h"


/* function: get rand buffer(internal basis interface)
 * parameters:
 *     rand ----------------------- input, byte buffer rand
 *     bytes ---------------------- input, byte length of rand
 *     get_rand_words ------------- input, function pointer to get some random words(at most 8 words)
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 */
uint32_t get_rand_buffer(uint8_t *rand, uint32_t bytes, GET_RAND_WORDS get_rand_words)
{
	volatile uint32_t enable_flag = 1;
	volatile uint32_t HT_error_flag = 1;
	volatile uint32_t ro_entropy_mask = (0x0000000F<<TRNG_RO_ENTROPY_OFFSET);
	uint32_t i;
	uint32_t tmp, tmp_len, rng_data;
	uint32_t count, ret;
	uint8_t *a = rand;

	//check input parameters
	if(NULL == rand || NULL == get_rand_words)
	{
		return TRNG_BUFFER_NULL;
	}
	else if(0 == bytes)
	{
		return TRNG_SUCCESS;
	}
	else
	{;}

	//make sure trng and ro are enabled
	if(0 == (TRNG_CR & enable_flag))
	{
		return TRNG_INVALID_CONFIG;
	}
	else if(0 == (TRNG_CR & ro_entropy_mask))
	{
		return TRNG_INVALID_CONFIG;
	}
	else
	{;}

	tmp_len = bytes;

	tmp = ((uint32_t)a) & 3;
	if(tmp)
	{
		i = 4-tmp;

		ret = get_rand_words(&rng_data, 1);
		if(TRNG_SUCCESS != ret)
		{
			goto END;
		}
		else
		{
			if(tmp_len > i)
			{
				memcpy_(a, &rng_data, i);
				a += i;
				tmp_len -= i;
			}
			else
			{
				memcpy_(a, &rng_data, tmp_len);
				goto END;
			}
		}
	}
	else
	{;}

	tmp = tmp_len/4;
	while(tmp)
	{
		if(tmp>8)
		{
			count = 8;
		}
		else
		{
			count = tmp;
		}

		ret = get_rand_words((uint32_t *)a, count);
		if(TRNG_SUCCESS != ret)
		{
			goto END;
		}
		else
		{
			a += count<<2;
			tmp -= count;
		}
	}

	tmp_len = tmp_len & 3;
	if(tmp_len)
	{
		ret = get_rand_words(&rng_data, 1);
		if(TRNG_SUCCESS != ret)
		{
			goto END;
		}
		else
		{
			memcpy_(a, &rng_data, tmp_len);
		}
	}

	ret = TRNG_SUCCESS;

END:

	//if now hw error appears, output data may be cleared by hw
	if((TRNG_SR & HT_error_flag) != 0)
	{
		ret = TRNG_HT_ERROR;

        //NOTE: temporary disable this error for FPGA verification

        //ret = TRNG_SUCCESS;

#if 0
        printf("\r\n\r\n");
        printf("0x%08lx - TRNG_CR      : 0x%08lx\r\n", (uint32_t)&TRNG_CR, TRNG_CR);
        printf("0x%08lx - TRNG_MSEL    : 0x%08lx\r\n", (uint32_t)&TRNG_MSEL, TRNG_MSEL);
        printf("0x%08lx - TRNG_SR      : 0x%08lx\r\n", (uint32_t)&TRNG_SR, TRNG_SR);
        printf("0x%08lx - TRNG_DR      : 0x%08lx\r\n", (uint32_t)&TRNG_DR, TRNG_DR);
        printf("0x%08lx - TRNG_VERSION : 0x%08lx\r\n", (uint32_t)&TRNG_VERSION, TRNG_VERSION);
        printf("0x%08lx - TRNG_RESEED  : 0x%08lx\r\n", (uint32_t)&TRNG_RESEED, TRNG_RESEED);
        printf("0x%08lx - TRNG_HT_CR   : 0x%08lx\r\n", (uint32_t)&TRNG_HT_CR, TRNG_HT_CR);
        printf("0x%08lx - TRNG_HT_SR   : 0x%08lx\r\n", (uint32_t)&TRNG_HT_SR, TRNG_HT_SR);
        printf("0x%08lx - RO_SRC_EN1   : 0x%08lx\r\n", (uint32_t)&RO_SRC_EN1, RO_SRC_EN1);
        printf("0x%08lx - RO_SRC_EN2   : 0x%08lx\r\n", (uint32_t)&RO_SRC_EN2, RO_SRC_EN2);
        printf("0x%08lx - SCLK_FREQ    : 0x%08lx\r\n", (uint32_t)&SCLK_FREQ, SCLK_FREQ);
        printf("------------------------------------------------\r\n");
        printf("0x%08lx - AHBMISC_TRNGCTRL : 0x%08lx\r\n",
               (uint32_t)&VC_AHBMISC->TRNGCTRL, VC_AHBMISC->TRNGCTRL);
        printf("0x%08lx - AHBMISC_TRNGSTS  : 0x%08lx\r\n",
               (uint32_t)&VC_AHBMISC->TRNGSTS, VC_AHBMISC->TRNGSTS);
#endif

	}
	else
	{;}

	if(TRNG_SUCCESS != ret)
	{
		memset_(rand, 0, bytes);
	}
	else
	{;}

#ifdef TRNG_POKER_TEST
	if(TRNG_SUCCESS == ret)
	{
		poker_test(rand, bytes);
	}
#endif

	return ret;
}


/* function: get rand(for internal test)
 * parameters:
 *     rand ----------------------- input, byte buffer rand
 *     bytes ---------------------- input, byte length of rand
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 */
uint32_t get_rand_internal(uint8_t *rand, uint32_t bytes)
{
	return get_rand_buffer(rand, bytes, get_rand_uint32);
}


/* function: get rand with fast speed(with entropy reducing, for such as clearing tmp buffer)
 * parameters:
 *     rand ----------------------- input, byte buffer rand
 *     bytes ---------------------- input, byte length of rand
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 */
uint32_t get_rand_fast(uint8_t *rand, uint32_t bytes)
{
#if 1
	volatile uint32_t flag = 0;

	//with post-processing
	if(flag == TRNG_MSEL)
	{
		trng_disable();
		trng_set_mode(1);
		trng_enable();
	}
	else
	{;}

	return get_rand_buffer(rand, bytes, get_rand_uint32);
#else
	//return get_rand(rand, bytes);
	volatile uint32_t i;

	for(i=0;i<2;i++)
		memset_(rand, 0, bytes);

	return TRNG_SUCCESS;
#endif
}


#if 1
/* function: get rand(without entropy reducing)
 * parameters:
 *     rand ----------------------- input, byte buffer rand
 *     bytes ---------------------- input, byte length of rand
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 */
uint32_t get_rand(uint8_t *rand, uint32_t bytes)
{
	volatile uint32_t flag = 0;

	//with post-processing
	if(flag == TRNG_MSEL)
	{
		trng_disable();
		trng_set_mode(1);
		trng_enable();
	}
	else
	{;}

	return get_rand_buffer(rand, bytes, get_rand_uint32_with_reseed);
}
#else

extern uint8_t SM3_Hash(uint8_t * message, uint32_t byteLen, uint8_t digest[32]);

uint32_t seed=0x23ba78de;
uint8_t sm3_buf[32];
uint8_t buf_index=0;
//trng config flag
static uint32_t trng_cfg_flag = 0;


uint32_t get_rand_register(void)
{
	static uint32_t i=0;
	uint8_t buf[32];
	uint32_t tmp = 0;

	if(0 == trng_cfg_flag)
	{
		SM3_Hash((uint8_t *)&seed, 4, sm3_buf);

		trng_cfg_flag=1;
	}

	if(buf_index<28)
	{
		tmp = *((uint32_t *)(sm3_buf+buf_index));
		buf_index+=4;
	}
	else if(buf_index == 28)
	{
		tmp = *((uint32_t *)(sm3_buf+28));
		memcpy_(buf, sm3_buf, 32);
		i++;
		*((uint32_t *)(buf+16)) += 1;
		SM3_Hash(buf, 32, sm3_buf);
		buf_index=0;
	}

	return tmp;
}

uint32_t get_rand(uint8_t *rand, uint32_t byteLen)
{
	uint8_t *rand_bak = rand;
	uint32_t len_bak = byteLen;
	uint32_t word_len, result = 0;
	uint8_t left_len = ((uint32_t)rand) & 0x3;

	// if the data addr is not aligned by word
	if (left_len)
	{
		// wait the data is ready
		result = get_rand_register();

		if (byteLen > (4 - left_len)) {
			memcpy_(rand, &result, 4 - left_len);
			byteLen -= (4 - left_len);
			rand += (4 - left_len);
		}
		else
		{
			memcpy_(rand, &result, byteLen);
			//trng_disable();
//			print_buf_U8(rand_bak, len_bak, "rand");
			return 0;//TRNG_SUCCESS;
		}
	}

	word_len = byteLen >> 2;
	left_len = byteLen & 0x3;

	// obtain the data by word
	while (word_len--)
	{
		*((uint32_t *)rand) = get_rand_register();
		rand += 4;
	}

	// if the byteLen is not aligned by word
	if (left_len)
	{
		result = get_rand_register();
		memcpy_(rand, &result, left_len);
	}

//	print_buf_U8(rand_bak, len_bak, "rand");
	return 0;//TRNG_SUCCESS;
}

#endif


/*********************************** TREO ************************************/

/* function: TERO RNG enable
 * parameters: none
 * return: none
 * caution:
 */
void tero_enable(void)
{
	volatile uint32_t flag = 1;
	volatile uint32_t i;

	TERO_CR |= flag;

	//sleep for a while
	i=0xFFF;
	while(i--)
	{;}
}


/* function: TERO RNG disable
 * parameters: none
 * return: none
 * caution:
 */
void tero_disable(void)
{
	volatile uint32_t mask = ~((uint32_t)1);

	TERO_CR &= mask;
}


/* function: TERO RNG set the system cycle threshold of the TERO counter kept,
 * parameters:
 *     threshold_value ------------ input, threshold value
 * return: none
 * caution:
 */
uint32_t tero_set_stop_threshold(uint8_t threshold_value)
{
	volatile uint32_t mask = ~(0x000000FF<<TRNG_TERO_THRESHOLD_OFFSET);

	if(0 == threshold_value)
	{
		return TRNG_INVALID_INPUT;
	}
	else
	{;}

	TERO_CR &= mask;
	TERO_CR |= (((uint32_t)threshold_value)<<TRNG_TERO_THRESHOLD_OFFSET);

	return TRNG_SUCCESS;
}


/* function: set TERO entropy config
 * parameters:
 *     cfg ------------------------ RO entropy config, only the low 4 bits are valid, every bit
 *                                  indicates one RO entropy, the LSB is TERO 0, and MSB is RO 3
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 *     1. only the low 4 bits of cfg are valid
 *     2. if the low 4 bits of cig is 0, that means to disable all TERO entropy
 */
uint32_t tero_entropy_config(uint8_t cfg)
{
	volatile uint32_t mask = ~(0x0000000F<<TRNG_TERO_ENTROPY_OFFSET);

	if(cfg > 15)
	{
		return TRNG_INVALID_INPUT;
	}
	else
	{;}

	TERO_CR &= mask;
	TERO_CR |= (((uint32_t)cfg)&0x0000000F)<<TRNG_TERO_ENTROPY_OFFSET;

	return TRNG_SUCCESS;
}


/* function: TERO RNG set output as rng
 * parameters: none
 * return: none
 * caution:
 */
void tero_set_output_rng(void)
{
	volatile uint32_t mask = ~(((uint32_t)1)<<1);

	TERO_CR &= mask;
}


/* function: TERO RNG set output as oscillation times
 * parameters: none
 * return: none
 * caution:
 */
void tero_set_output_osc_times(void)
{
	volatile uint32_t flag = (((uint32_t)1)<<1);

	TERO_CR |= flag;
}


/* function: select TREO 1&2 or TERO 3&4 when output is oscillation times
 * parameters:
 *     cfg ------------------------ input, 0:TREO 1&2, other:TREO 3&4
 * return: none
 * caution:
 */
void tero_set_osc_sel(uint8_t cfg)
{
	volatile uint32_t mask = ~(((uint32_t)1)<<2);
	volatile uint32_t flag = (((uint32_t)1)<<2);

	if(0 == cfg)
	{
		TERO_CR &= mask;
	}
	else
	{
		TERO_CR |= flag;
	}
}


/* function: set lower limit of oscillation times
 * parameters:
 *     value ---------------------- input, lower limit value
 * return: none
 * caution:
 */
void tero_set_osc_times_lower_limit(uint16_t value)
{
	volatile uint32_t mask = ~(0x000000FF<<16);

	TERO_THOLD &= mask;
	TERO_THOLD |= ((uint32_t)value)<<16;
}


/* function: set upper limit of oscillation times
 * parameters:
 *     value ---------------------- input, upper limit value
 * return: none
 * caution:
 */
void tero_set_osc_times_upper_limit(uint16_t value)
{
	volatile uint32_t mask = ~(0x000000FF);

	TERO_THOLD &= mask;
	TERO_THOLD |= ((uint32_t)value);
}


/* function: get tero rand
 * parameters:
 *     a -------------------------- input, byte buffer a
 *     bytes ---------------------- input, byte length of rand
 * return: TRNG_SUCCESS(success), other(error)
 * caution:
 */
uint32_t get_tero_rand(uint8_t *a, uint32_t bytes)
{
	volatile uint32_t flag_1 = 1;
	volatile uint32_t flag_2 = 2;
	volatile uint32_t tero_entropy_mask = (0x0000000F<<TRNG_TERO_ENTROPY_OFFSET);
	uint32_t i;
	uint32_t tmp, rng_data;

#ifdef TRNG_POKER_TEST
	uint32_t tmp_len = bytes;
#endif

	//check input parameters
	if(NULL == a)
	{
		return TRNG_BUFFER_NULL;
	}
	else if(0 == bytes)
	{
		return TRNG_SUCCESS;
	}
	else
	{;}

	//make sure tero config is valid
	if(0 == (TERO_CR & flag_1))
	{
		return TRNG_INVALID_CONFIG;
	}
	else if(TERO_CR & flag_2)
	{
		return TRNG_INVALID_CONFIG;
	}
	else if(0 == (TERO_CR & tero_entropy_mask))
	{
		return TRNG_INVALID_CONFIG;
	}
	else
	{;}

	tmp = ((uint32_t)a) & 3;
	if(tmp)
	{
		i = 4-tmp;

		while(0 == (TERO_SR & flag_1))
		{;}
		rng_data = TERO_DR;//printf("\r\n %08x", rng_data);
		if(bytes > i)
		{
			memcpy_(a, &rng_data, i);
			a += i;
			bytes -= i;
		}
		else
		{
			memcpy_(a, &rng_data, bytes);
			return TRNG_SUCCESS;
		}
	}

	tmp = bytes/4;
	while(tmp)
	{
		while(0 == (TERO_SR & flag_1))
		{;}
		*((uint32_t *)a) = TERO_DR;//printf("\r\n %08x", *((uint32_t *)a));

		a += 4;
		tmp--;
	}

	bytes = bytes & 3;
	if(bytes)
	{
		while(0 == (TERO_SR & flag_1))
		{;}
		rng_data = TERO_DR;//printf("\r\n %08x", rng_data);
		memcpy_(a, &rng_data, bytes);
	}

#ifdef TRNG_POKER_TEST
	poker_test(a-tmp_len, tmp_len);
#endif

	return TRNG_SUCCESS;
}

