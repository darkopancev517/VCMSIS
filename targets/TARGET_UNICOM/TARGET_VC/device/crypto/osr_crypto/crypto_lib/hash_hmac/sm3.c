#include "../../crypto_include/hash_hmac/sm3.h"





#ifdef SUPPORT_HASH_SM3


/* function: init sm3
 * parameters:
 *     ctx ------------------------ input, SM3_CTX context pointer
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1.
 */
uint32_t sm3_init(SM3_CTX *ctx)
{
	return hash_init(ctx, HASH_SM3);
}


/* function: sm3 update message
 * parameters:
 *     ctx ------------------------ input, SM3_CTX context pointer
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the input message
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the three parameters are valid, and ctx is initialized
 */
uint32_t sm3_update(SM3_CTX *ctx, const uint8_t *msg, uint32_t msg_bytes)
{
	return hash_update(ctx, msg, msg_bytes);
}


/* function: message update done, get the sm3 digest
 * parameters:
 *     digest --------------------- output, sm3 digest, 32 bytes
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the digest buffer is sufficient
 */
uint32_t sm3_final(SM3_CTX *ctx, uint8_t *digest)
{
	return hash_final(ctx, digest);
}


/* function: input whole message and get its sm3 digest
 * parameters:
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the input message, it could be 0
 *     digest --------------------- output, sm3 digest, 32 bytes
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the digest buffer is sufficient
 */
uint32_t sm3(uint8_t *msg, uint32_t msg_bytes, uint8_t *digest)
{
	return hash(HASH_SM3, msg, msg_bytes, digest);
}


#ifdef HASH_DMA_FUNCTION
/* function: init dma sm3
 * parameters:
 *     ctx ------------------------ input, SM3_DMA_CTX context pointer
 *     callback ------------------- callback function pointer
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 */
uint32_t sm3_dma_init(SM3_DMA_CTX *ctx, HASH_CALLBACK callback)
{
	return hash_dma_init(ctx, HASH_SM3, callback);
}


/* function: dma sm3 update some message blocks
 * parameters:
 *     ctx ------------------------ input, SM3_DMA_CTX context pointer
 *     msg ------------------------ input, message blocks
 *     msg_words ------------------ input, word length of the input message, must be a multiple of sm3
 *                                  block word length(16)
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the four parameters are valid, and ctx is initialized
 */
uint32_t sm3_dma_update_blocks(SM3_DMA_CTX *ctx, uint32_t *msg, uint32_t msg_words)
{
	return hash_dma_update_blocks(ctx, msg, msg_words);
}


/* function: dma sm3 final(input the remainder message and get the digest)
 * parameters:
 *     ctx ------------------------ input, SM3_DMA_CTX context pointer
 *     remainder_msg -------------- input, remainder message
 *     remainder_bytes ------------ input, byte length of the remainder message, must be in [0, BLOCK_BYTE_LEN-1],
 *                                  here BLOCK_BYTE_LEN is block byte length of sm3, it is 64.
 *     digest --------------------- output, sm3 digest, 32 bytes
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the four parameters are valid, and ctx is initialized
 */
uint32_t sm3_dma_final(SM3_DMA_CTX *ctx, uint32_t *remainder_msg, uint32_t remainder_bytes, uint32_t *digest)
{
	return hash_dma_final(ctx, remainder_msg, remainder_bytes, digest);
}


/* function: dma sm3 digest calculate
 * parameters:
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the message, it could be 0
 *     digest --------------------- output, sm3 digest, 32 bytes
 *     callback ------------------- callback function pointer
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the four parameters are valid
 */
uint32_t sm3_dma(uint32_t *msg, uint32_t msg_bytes, uint32_t *digest, HASH_CALLBACK callback)
{
	return hash_dma(HASH_SM3, msg, msg_bytes, digest, callback);
}
#endif

#endif
