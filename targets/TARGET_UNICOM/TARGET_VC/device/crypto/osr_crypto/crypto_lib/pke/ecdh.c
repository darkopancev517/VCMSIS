#include <stdio.h>
#include "../../crypto_hal/pke.h"
#include "../../crypto_include/pke/ecdh.h"
#include "../../crypto_include/utility.h"





/* Function: ECDH compute key
 * Parameters:
 *     local_prikey --------------- input, local private key, big-endian
 *     peer_pubkey ---------------- input, peer public key, big-endian
 *     key ------------------------ output, output key
 *     keyByteLen ----------------- input, byte length of output key
 *     KDF ------------------------ input, KDF function to get key
 * Return:
 *     ECDH_SUCCESS(success); other(error)
 * Caution:
 */
uint32_t ecdh_compute_key(eccp_curve_t *curve, uint8_t *local_prikey, uint8_t *peer_pubkey, uint8_t *key,
		uint32_t keyByteLen, KDF_FUNC kdf)
{
	uint32_t k[ECCP_MAX_WORD_LEN] = {0};
	uint32_t Px[ECCP_MAX_WORD_LEN] = {0};
	uint32_t Py[ECCP_MAX_WORD_LEN] = {0};
	uint32_t byteLen, wordLen;
	uint32_t ret;

	if(NULL == curve || NULL == local_prikey || NULL == peer_pubkey || NULL == key)
	{
		return ECDH_POINTOR_NULL;
	}
	else if(0 == keyByteLen)
	{
		return ECDH_INVALID_INPUT;
	}
	else
	{;}

	byteLen = GET_BYTE_LEN(curve->eccp_n_bitLen);
	wordLen = GET_WORD_LEN(curve->eccp_n_bitLen);

	//make sure private key is in [1, n-1]
	reverse_byte_array((uint8_t *)local_prikey, (uint8_t *)k, byteLen);
	ret = uint32_integer_check(k, curve->eccp_n, wordLen, ECDH_ZERO_ALL, ECDH_INTEGER_TOO_BIG,
			ECDH_SUCCESS);
	if(ECDH_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	//check public key
	byteLen = GET_BYTE_LEN(curve->eccp_p_bitLen);
	reverse_byte_array(peer_pubkey, (uint8_t *)Px, byteLen);
	reverse_byte_array(peer_pubkey+byteLen, (uint8_t *)Py, byteLen);
	ret = eccp_pointVerify(curve, Px, Py);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	ret = eccp_pointMul(curve, k, Px, Py, Px, NULL);
	if(PKE_SUCCESS != ret)
	{
		return ret;
	}
	else
	{;}

	reverse_byte_array((uint8_t *)Px, (uint8_t *)Px, byteLen);

	if(kdf)
	{
		kdf(Px, byteLen, key, keyByteLen);
	}
	else
	{
		if(keyByteLen > byteLen)
		{
			keyByteLen = byteLen;
		}
		else
		{;}

		memcpy_(key, Px, keyByteLen);
	}

	return ECDH_SUCCESS;
}

