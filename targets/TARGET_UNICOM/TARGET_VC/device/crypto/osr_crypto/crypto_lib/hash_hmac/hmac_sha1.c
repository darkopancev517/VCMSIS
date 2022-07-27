#include "../../crypto_include/hash_hmac/hmac_sha1.h"





#ifdef SUPPORT_HASH_SHA1


/* function: init hmac-sha1
 * parameters:
 *     ctx ------------------------ input, HMAC_SHA1_CTX context pointer
 *     key ------------------------ input, key
 *     sp_key_idx ----------------- input, index of secure port key
 *     key_bytes ------------------ input, byte length of key, it could be 0
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1.
 */
uint32_t hmac_sha1_init(HMAC_SHA1_CTX *ctx, uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes)
{
	return hmac_init(ctx, HASH_SHA1, key, sp_key_idx, key_bytes);
}


/* function: hmac-sha1 update message
 * parameters:
 *     ctx ------------------------ input, HMAC_SHA1_CTX context pointer
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the input message
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the three parameters are valid, and ctx is initialized
 */
uint32_t hmac_sha1_update(HMAC_SHA1_CTX *ctx, const uint8_t *msg, uint32_t msg_bytes)
{
	return hmac_update(ctx, msg, msg_bytes);
}


/* function: message update done, get the hmac
 * parameters:
 *     ctx ------------------------ input, HMAC_CTX context pointer
 *     mac ------------------------ output, hmac
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the ctx is valid and initialized
 *     2. please make sure the mac buffer is sufficient
 */
uint32_t hmac_sha1_final(HMAC_SHA1_CTX *ctx, uint8_t *mac)
{
	return hmac_final(ctx, mac);
}


/* function: input key and whole message, get the hmac
 * parameters:
 *     key ------------------------ input, key
 *     sp_key_idx ----------------- input, index of secure port key
 *     key_bytes ------------------ input, byte length of the key
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the input message
 *     mac ------------------------ output, hmac
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the mac buffer is sufficient
 */
uint32_t hmac_sha1(uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes, uint8_t *msg, uint32_t msg_bytes, uint8_t *mac)
{
	return hmac(HASH_SHA1, key, sp_key_idx, key_bytes, msg, msg_bytes, mac);
}


#ifdef HASH_DMA_FUNCTION
/* function: init dma hmac-sha1
 * parameters:
 *     ctx ------------------------ input, HMAC_SHA1_DMA_CTX context pointer
 *     key ------------------------ input, key
 *     sp_key_idx ----------------- input, index of secure port key
 *     key_bytes ------------------ input, key byte length
 *     callback ------------------- callback function pointer
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 */
uint32_t hmac_sha1_dma_init(HMAC_SHA1_DMA_CTX *ctx, const uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes,
		HASH_CALLBACK callback)
{
	return hmac_dma_init(ctx, HASH_SHA1, key, sp_key_idx, key_bytes, callback);
}


/* function: dma hmac-sha1 update message
 * parameters:
 *     ctx ------------------------ input, HMAC_SHA1_DMA_CTX context pointer
 *     msg ------------------------ input, message
 *     msg_words ------------------ input, word length of the input message, must be a multiple of block word length
 *                                  of SHA1(16)
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the four parameters are valid, and ctx is initialized
 */
uint32_t hmac_sha1_dma_update_blocks(HMAC_SHA1_DMA_CTX *ctx, uint32_t *msg, uint32_t msg_words)
{
	return hmac_dma_update_blocks(ctx, msg, msg_words);
}


/* function: dma hmac-sha1 message update done, get the hmac
 * parameters:
 *     ctx ------------------------ input, HMAC_SHA1_DMA_CTX context pointer
 *     remainder_msg -------------- input, message
 *     remainder_bytes ------------ input, byte length of the last message, must be in [0, BLOCK_BYTE_LEN-1],
 *                                  here BLOCK_BYTE_LEN is block byte length of SHA1(64)
 *     mac ------------------------ output, hmac
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the three parameters are valid, and ctx is initialized
 */
uint32_t hmac_sha1_dma_final(HMAC_SHA1_DMA_CTX *ctx, uint32_t *remainder_msg, uint32_t remainder_bytes, uint32_t *mac)
{
	return hmac_dma_final(ctx, remainder_msg, remainder_bytes, mac);
}


/* function: dma hmac-sha1 input key and message, get the hmac
 * parameters:
 *     key ------------------------ input, key
 *     sp_key_idx ----------------- input, index of secure port key
 *     key_bytes ------------------ input, key byte length
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the input message
 *     mac ------------------------ output, hmac
 *     callback ------------------- callback function pointer
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 */
uint32_t hmac_sha1_dma(uint8_t *key, uint16_t sp_key_idx, uint32_t key_bytes, uint32_t *msg, uint32_t msg_bytes, uint32_t *mac,
		HASH_CALLBACK callback)
{
	return hmac_dma(HASH_SHA1, key, sp_key_idx, key_bytes, msg, msg_bytes, mac, callback);
}

#endif


#endif
