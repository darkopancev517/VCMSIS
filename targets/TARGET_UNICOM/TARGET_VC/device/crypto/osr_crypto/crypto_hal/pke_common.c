#include <stdio.h>
#include "pke_common.h"








/* function: load input operand to baseaddr
 * parameters:
 *     baseaddr ------------------- output, destination data
 *     data ----------------------- input, source data
 *     wordLen -------------------- input, word length of data
 * return: none
 * caution:
 */
void pke_load_operand(uint32_t *baseaddr, uint32_t *data, uint32_t wordLen)
{
	uint32_t i;

	if(baseaddr != data)
	{
		for (i = 0; i < wordLen; i++)
		{
			*((volatile uint32_t *)baseaddr+i) = data[i];
		}
	}
	else
	{;}
}


/* function: get result operand from baseaddr
 * parameters:
 *     baseaddr ------------------- input, source data
 *     data ----------------------- output, destination data
 *     wordLen -------------------- input, word length of data
 * return: none
 * caution:
 */
void pke_read_operand(uint32_t *baseaddr, uint32_t *data, uint32_t wordLen)
{
	uint32_t i;

	if(baseaddr != data)
	{
		for (i = 0; i < wordLen; i++)
		{
			data[i] = *((volatile uint32_t *)baseaddr+i);
		}
	}
	else
	{;}
}


/* function: set operand with an uint32_t value
 * parameters:
 *     a -------------------------- output, operand a
 *     wordLen -------------------- input, word length of operand a
 *     b -------------------------- input, uint32_t value b
 * return: none
 * caution:
 *     1. aWordLen can not be 0
 */
void pke_set_operand_uint32_value(uint32_t *a, uint32_t aWordLen, uint32_t b)
{
	uint32_t i = aWordLen;

	while(i>1)
	{
		a[--i] = 0;
	}

	a[0] = b;
}

