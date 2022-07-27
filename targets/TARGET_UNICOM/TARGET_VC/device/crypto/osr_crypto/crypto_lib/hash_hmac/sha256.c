#include "../../crypto_include/hash_hmac/sha256.h"





#ifdef SUPPORT_HASH_SHA256


/* function: init sha256
 * parameters:
 *     ctx ------------------------ input, SHA256_CTX context pointer
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1.
 */
uint32_t sha256_init(SHA256_CTX *ctx)
{
	return hash_init(ctx, HASH_SHA256);
}


/* function: sha256 update message
 * parameters:
 *     ctx ------------------------ input, SHA256_CTX context pointer
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the input message
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the three parameters are valid, and ctx is initialized
 */
uint32_t sha256_update(SHA256_CTX *ctx, const uint8_t *msg, uint32_t msg_bytes)
{
	return hash_update(ctx, msg, msg_bytes);
}


/* function: message update done, get the sha256 digest
 * parameters:
 *     digest --------------------- output, sha256 digest, 32 bytes
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the digest buffer is sufficient
 */
uint32_t sha256_final(SHA256_CTX *ctx, uint8_t *digest)
{
	return hash_final(ctx, digest);
}


/* function: input whole message and get its sha256 digest
 * parameters:
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the input message, it could be 0
 *     digest --------------------- output, sha256 digest, 32 bytes
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the digest buffer is sufficient
 */
uint32_t sha256(uint8_t *msg, uint32_t msg_bytes, uint8_t *digest)
{
	return hash(HASH_SHA256, msg, msg_bytes, digest);
}


#ifdef HASH_DMA_FUNCTION
/* function: init dma sha256
 * parameters:
 *     ctx ------------------------ input, SHA256_DMA_CTX context pointer
 *     callback ------------------- callback function pointer
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 */
uint32_t sha256_dma_init(SHA256_DMA_CTX *ctx, HASH_CALLBACK callback)
{
	return hash_dma_init(ctx, HASH_SHA256, callback);
}


/* function: dma sha256 update some message blocks
 * parameters:
 *     ctx ------------------------ input, SHA256_DMA_CTX context pointer
 *     msg ------------------------ input, message blocks
 *     msg_words ------------------ input, word length of the input message, must be a multiple of sha256
 *                                  block word length(16)
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the four parameters are valid, and ctx is initialized
 */
uint32_t sha256_dma_update_blocks(SHA256_DMA_CTX *ctx, uint32_t *msg, uint32_t msg_words)
{
	return hash_dma_update_blocks(ctx, msg, msg_words);
}


/* function: dma sha256 final(input the remainder message and get the digest)
 * parameters:
 *     ctx ------------------------ input, SHA256_DMA_CTX context pointer
 *     remainder_msg -------------- input, remainder message
 *     remainder_bytes ------------ input, byte length of the remainder message, must be in [0, BLOCK_BYTE_LEN-1],
 *                                  here BLOCK_BYTE_LEN is block byte length of sha256, it is 64.
 *     digest --------------------- output, sha256 digest, 32 bytes
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the four parameters are valid, and ctx is initialized
 */
uint32_t sha256_dma_final(SHA256_DMA_CTX *ctx, uint32_t *remainder_msg, uint32_t remainder_bytes, uint32_t *digest)
{
	return hash_dma_final(ctx, remainder_msg, remainder_bytes, digest);
}


/* function: dma sha256 digest calculate
 * parameters:
 *     msg ------------------------ input, message
 *     msg_bytes ------------------ input, byte length of the message, it could be 0
 *     digest --------------------- output, sha256 digest, 32 bytes
 *     callback ------------------- callback function pointer
 * return: HASH_SUCCESS(success), other(error)
 * caution:
 *     1. please make sure the four parameters are valid
 */
uint32_t sha256_dma(uint32_t *msg, uint32_t msg_bytes, uint32_t *digest, HASH_CALLBACK callback)
{
	return hash_dma(HASH_SHA256, msg, msg_bytes, digest, callback);
}
#endif

#endif
