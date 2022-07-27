#ifndef PKE_H
#define PKE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "register_base_addr.h"
#include "pke_common.h"
#include "../crypto_common/eccp_curve.h"






#define SUPPORT_SM2
//#define SUPPORT_C25519


#ifdef SUPPORT_SM2
extern const eccp_curve_t sm2_curve[1];
#endif

#ifdef SUPPORT_C25519
extern const edward_curve_t ed25519[1];
#endif


/***************** PKE register *******************/
#define PKE_CTRL           (*((volatile uint32_t *)(PKE_BASE_ADDR)))
#define PKE_CFG            (*((volatile uint32_t *)(PKE_BASE_ADDR+0x04)))
#define PKE_MC_PTR         (*((volatile uint32_t *)(PKE_BASE_ADDR+0x08)))
#define PKE_RISR           (*((volatile uint32_t *)(PKE_BASE_ADDR+0x0C)))
#define PKE_IMCR           (*((volatile uint32_t *)(PKE_BASE_ADDR+0x10)))
#define PKE_MISR           (*((volatile uint32_t *)(PKE_BASE_ADDR+0x14)))
#define PKE_RT_CODE        (*((volatile uint32_t *)(PKE_BASE_ADDR+0x24)))
#define PKE_EXE_CONF       (*((volatile uint32_t *)(PKE_BASE_ADDR+0x50)))   //
#define PKE_VERSION        (*((volatile uint32_t *)(PKE_BASE_ADDR+0xFC)))
#define PKE_A(a, step)     ((volatile uint32_t *)(PKE_BASE_ADDR+0x0400+(a)*(step)))
#define PKE_B(a, step)     ((volatile uint32_t *)(PKE_BASE_ADDR+0x1000+(a)*(step)))


/*********** PKE register action offset ************/
#define PKE_START_CALC                        (1)

#define PKE_EXE_OUTPUT_AFFINE                 (0x10)
#define PKE_EXE_R1_MONT_R0_AFFINE             (0x09)
#define PKE_EXE_R1_MONT_R0_MONT               (0x0A)
#define PKE_EXE_R1_AFFINE_R0_AFFINE           (0x05)
#define PKE_EXE_R1_AFFINE_R0_MONT             (0x06)
#define PKE_EXE_ECCP_POINT_MUL                (PKE_EXE_OUTPUT_AFFINE + PKE_EXE_R1_AFFINE_R0_MONT)
#define PKE_EXE_ECCP_POINT_ADD                (PKE_EXE_OUTPUT_AFFINE + PKE_EXE_R1_AFFINE_R0_AFFINE)
#define PKE_EXE_ECCP_POINT_DBL                (PKE_EXE_OUTPUT_AFFINE + PKE_EXE_R1_MONT_R0_AFFINE)
#define PKE_EXE_ECCP_POINT_VER                (PKE_EXE_OUTPUT_AFFINE + PKE_EXE_R1_AFFINE_R0_MONT)

#define PKE_EXE_CFG_ALL_MONT                  (0x002A)
#define PKE_EXE_CFG_ALL_NON_MONT              (0x0000)
#define PKE_EXE_CFG_MODEXP                    (0x0316)


/***************** PKE microcode ******************/
#define MICROCODE_PDBL                        (0x04)
#define MICROCODE_PADD                        (0x08)
#define MICROCODE_PVER                        (0x0C)
#define MICROCODE_PMUL                        (0x10)
#define MICROCODE_MODEXP                      (0x14)
#define MICROCODE_MODMUL                      (0x18)
#define MICROCODE_MODINV                      (0x1C)
#define MICROCODE_MODADD                      (0x20)
#define MICROCODE_MODSUB                      (0x24)
#define MICROCODE_MGMR_PRE                    (0x28)
#define MICROCODE_INTMUL                      (0x2C)
#define MICROCODE_Ed25519_PMUL                (0x30)
#define MICROCODE_Ed25519_PADD                (0x34)
#define MICROCODE_C25519_PMUL                 (0x38)


/*********** some PKE algorithm operand length ************/
#define OPERAND_MAX_BIT_LEN                   (4096)
#define OPERAND_MAX_WORD_LEN                  (GET_WORD_LEN(OPERAND_MAX_BIT_LEN))

#define ECCP_MAX_BIT_LEN                      (521)  //ECC521
#define ECCP_MAX_BYTE_LEN                     (GET_BYTE_LEN(ECCP_MAX_BIT_LEN))
#define ECCP_MAX_WORD_LEN                     (GET_WORD_LEN(ECCP_MAX_BIT_LEN))

#define C25519_BYTE_LEN                       (256/8)
#define C25519_WORD_LEN                       (256/32)

#define Ed25519_BYTE_LEN                      C25519_BYTE_LEN
#define Ed25519_WORD_LEN                      C25519_WORD_LEN

#define MAX_RSA_WORD_LEN                      OPERAND_MAX_WORD_LEN
#define MAX_RSA_BIT_LEN                       (MAX_RSA_WORD_LEN<<5)
#define MIN_RSA_BIT_LEN                       (512)


/******************* PKE return code ********************/
enum PKE_RET_CODE
{
	PKE_SUCCESS = 0,
	PKE_STOP,
	PKE_NO_MODINV,
	PKE_NOT_ON_CURVE,
	PKE_INVALID_MC,
	PKE_ZERO_ALL,                   //for ECCP input check
	PKE_INTEGER_TOO_BIG,            //for ECCP input check
	PKE_INVALID_INPUT,
	PKE_ERROR,
};











//APIs

uint32_t pke_get_version(void);

void pke_set_operand_width(uint32_t bitLen);

uint32_t pke_get_operand_bytes(void);

void pke_set_exe_cfg(uint32_t cfg);

uint32_t pke_modinv(const uint32_t *modulus, const uint32_t *a, uint32_t *ainv, uint32_t modWordLen,
		uint32_t aWordLen);

uint32_t pke_modadd(const uint32_t *modulus, const uint32_t *a, const uint32_t *b,
		uint32_t *out, uint32_t wordLen);

uint32_t pke_modsub(const uint32_t *modulus, const uint32_t *a, const uint32_t *b,
		uint32_t *out, uint32_t wordLen);

uint32_t pke_add(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t wordLen);

uint32_t pke_sub(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t wordLen);

uint32_t pke_mul_internal(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t a_wordLen, 
		uint32_t b_wordLen, uint32_t out_wordLen);

uint32_t pke_mul(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t ab_wordLen);

uint32_t pke_pre_calc_mont(const uint32_t *modulus, uint32_t bitLen, uint32_t *H, uint32_t *n0);

uint32_t pke_pre_calc_mont_no_output(const uint32_t *modulus, uint32_t wordLen);

uint32_t pke_load_modulus_and_pre_monts(uint32_t *modulus, uint32_t *modulus_h, uint32_t *modulus_n0, uint32_t bitLen);

uint32_t pke_set_modulus_and_pre_monts(uint32_t *modulus, uint32_t *modulus_h, uint32_t *modulus_n0, uint32_t bitLen);

uint32_t pke_modmul_internal(const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t wordLen);

uint32_t pke_modmul(const uint32_t *modulus, const uint32_t *a, const uint32_t *b, uint32_t *out, uint32_t wordLen);

uint32_t pke_modexp(const uint32_t *modulus, const uint32_t *exponent, const uint32_t *base,
		uint32_t *out, uint32_t mod_wordLen, uint32_t exp_wordLen);

uint32_t pke_mod(uint32_t *a, uint32_t aWordLen, uint32_t *b, uint32_t *b_h, uint32_t *b_n0, uint32_t bWordLen,
		uint32_t *c);

uint32_t eccp_pointMul(eccp_curve_t *curve, uint32_t *k, uint32_t *Px, uint32_t *Py,
		uint32_t *Qx, uint32_t *Qy);

uint32_t eccp_pointAdd(eccp_curve_t *curve, uint32_t *P1x, uint32_t *P1y, uint32_t *P2x, uint32_t *P2y,
		uint32_t *Qx, uint32_t *Qy);

//#define ECCP_POINT_DOUBLE   //not recommended to define
#ifdef ECCP_POINT_DOUBLE
uint32_t eccp_pointDouble(eccp_curve_t *curve, uint32_t *Px, uint32_t *Py, uint32_t *Qx, uint32_t *Qy);
#endif

uint32_t eccp_pointVerify(eccp_curve_t *curve, uint32_t *Px, uint32_t *Py);

uint32_t eccp_get_pubkey_from_prikey(eccp_curve_t *curve, uint8_t *priKey, uint8_t *pubKey);

uint32_t eccp_getkey(eccp_curve_t *curve, uint8_t *priKey, uint8_t *pubKey);


#ifdef SUPPORT_C25519
uint32_t x25519_pointMul(mont_curve_t *curve, uint32_t *k, uint32_t *Pu, uint32_t *Qu);

uint32_t ed25519_pointMul(edward_curve_t *curve, uint32_t *k, uint32_t *Px, uint32_t *Py,
		uint32_t *Qx, uint32_t *Qy);

uint32_t ed25519_pointAdd(edward_curve_t *curve, uint32_t *P1x, uint32_t *P1y, uint32_t *P2x, uint32_t *P2y,
		uint32_t *Qx, uint32_t *Qy);

#endif




#ifdef __cplusplus
}
#endif

#endif
