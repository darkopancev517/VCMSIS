#include <stdio.h>

#include "../../crypto_include/utility.h"
#include "../../crypto_include/pke/eccp_curve.h"
#include "../../crypto_hal/pke.h"

extern uint32_t get_systick_micros(void);


#if 1

const uint32_t brainpoolp256r1_p[8]        = {0x1F6E5377,0x2013481D,0xD5262028,0x6E3BF623,0x9D838D72,0x3E660A90,0xA1EEA9BC,0xA9FB57DB};
const uint32_t brainpoolp256r1_p_h[8];
const uint32_t brainpoolp256r1_p_n0[1];
const uint32_t brainpoolp256r1_a[8]        = {0xF330B5D9,0xE94A4B44,0x26DC5C6C,0xFB8055C1,0x417AFFE7,0xEEF67530,0xFC2C3057,0x7D5A0975};
const uint32_t brainpoolp256r1_b[8]        = {0xFF8C07B6,0x6BCCDC18,0x5CF7E1CE,0x95841629,0xBBD77CBF,0xF330B5D9,0xE94A4B44,0x26DC5C6C};
const uint32_t brainpoolp256r1_Gx[8]       = {0x9ACE3262,0x3A4453BD,0xE3BD23C2,0xB9DE27E1,0xFC81B7AF,0x2C4B482F,0xCB7E57CB,0x8BD2AEB9};
const uint32_t brainpoolp256r1_Gy[8]       = {0x2F046997,0x5C1D54C7,0x2DED8E54,0xC2774513,0x14611DC9,0x97F8461A,0xC3DAC4FD,0x547EF835};
const uint32_t brainpoolp256r1_n[8]        = {0x974856A7,0x901E0E82,0xB561A6F7,0x8C397AA3,0x9D838D71,0x3E660A90,0xA1EEA9BC,0xA9FB57DB};
const uint32_t brainpoolp256r1_n_h[8];
const uint32_t brainpoolp256r1_n_n0[1];


const eccp_curve_t brainpoolp256r1[1]={
	{
		256,
		256,
		(uint32_t *)brainpoolp256r1_p,
		NULL,//(uint32_t *)brainpoolp256r1_p_h,
		NULL,//(uint32_t *)brainpoolp256r1_p_n0,
		(uint32_t *)brainpoolp256r1_a,
		(uint32_t *)brainpoolp256r1_b,
		(uint32_t *)brainpoolp256r1_Gx,
		(uint32_t *)brainpoolp256r1_Gy,
		(uint32_t *)brainpoolp256r1_n,
		NULL,//(uint32_t *)brainpoolp256r1_n_h,
		NULL,//(uint32_t *)brainpoolp256r1_n_n0,
	},
};

uint32_t brainpoolp256r1_get_curve_paras_test()
{
	uint32_t p_h[8];
	uint32_t p_n0[1];
	uint32_t n_h[8];
	uint32_t n_n0[1];

	uint32_t std_brainpoolp256r1_p_h[8]      = {0xA6465B6C,0x8CFEDF7B,0x614D4F4D,0x5CCE4C26,0x6B1AC807,0xA1ECDACD,0xE5957FA8,0x4717AA21};
	uint32_t std_brainpoolp256r1_p_n0[1]     = {0xCEFD89B9};
	uint32_t std_brainpoolp256r1_n_h[8]      = {0x3312FCA6,0xE1D8D8DE,0x1134E4A0,0xF35D176A,0x6C815CB0,0x9B7F25E7,0xC3236762,0x0B25F1B9};
	uint32_t std_brainpoolp256r1_n_n0[1]     = {0xCBB40EE9};

	uint32_t ret;

    uint32_t start1 = get_systick_micros();
	ret = pke_pre_calc_mont((const uint32_t *)brainpoolp256r1_p, 256, p_h, p_n0);
    uint32_t duration1 = get_systick_micros() - start1;

	if((PKE_SUCCESS != ret) || uint32_BigNumCmp(p_h, 8, std_brainpoolp256r1_p_h, 8) || (p_n0[0] != std_brainpoolp256r1_p_n0[0]))
	{
		printf("\r\n get p_h error");
		print_BN_buf_U32(p_h, 8, "p_h");
		return 1;
	}

    uint32_t start2 = get_systick_micros();
	ret = pke_pre_calc_mont((const uint32_t *)brainpoolp256r1_n, 256, n_h, n_n0);
    uint32_t duration2 = get_systick_micros() - start2;

	if((PKE_SUCCESS != ret) || uint32_BigNumCmp(n_h, 8, std_brainpoolp256r1_n_h, 8) || (n_n0[0] != std_brainpoolp256r1_n_n0[0]))
	{
		printf("\r\n get n_h error");
		print_BN_buf_U32((uint32_t *)brainpoolp256r1_n, 8, "n");
		print_BN_buf_U32(n_h, 8, "n_h");
		return 1;
	}

	printf("\r\n brainpoolp256r1_get_curve_paras_test success - duration: %lu us\r\n", duration1 + duration2);

	return 0;
}



uint32_t ECCp_get_curve_paras_test(void)
{
	printf("\r\n\r\n =================== ECCp_get_key test =================== \r\n");


	if(brainpoolp256r1_get_curve_paras_test())
		return 1;


	return 0;
}


#endif
