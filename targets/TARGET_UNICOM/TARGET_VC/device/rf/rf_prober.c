/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "rf_prober.h"
#include "hal/rf.h"
#include "hal/misc.h"

//setmask, clearmask 
void _cent_spi_regW(const char *msg, uint32_t address, uint32_t val, uint32_t clear)
{
    uint32_t reg_val;
    _hal_rf_get(msg, address, &reg_val);
    reg_val &= clear;
    reg_val |= val;
    _hal_rf_put(msg, address, reg_val);
}

void _cent_spi_readW(const char *msg, uint32_t address, uint32_t *pval)
{
    _hal_rf_get(msg, address, pval);
}

void _cent_spi_writeW(const char *msg, uint32_t address, uint32_t val)
{
    _hal_rf_put(msg, address, val);
}

uint32_t _CentauriCsrRead(const char *msg, uint32_t csr_addr)
{
    uint32_t val = 0xdeadbeef;
    _hal_rf_get(msg, csr_addr, &val);
    return val;
}

void _CentauriCsrWrite(const char *msg, uint32_t csr_addr, uint32_t csr_val)
{
    _hal_rf_put(msg, csr_addr, csr_val);
}
