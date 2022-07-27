/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __CENT_PROBER_H
#define __CENT_PROBER_H

#define NOTCARE     0xffffffff
#define REGCLEAR    0

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void _cent_spi_regW(const char *msg, uint32_t address, uint32_t val, uint32_t clear);
#define cent_spi_regW(address, val, clear) _cent_spi_regW(__func__, address, val, clear)

void _cent_spi_readW(const char *msg, uint32_t address, uint32_t *val);
#define cent_spi_readW(address, val) _cent_spi_readW(__func__, address, val)

void _cent_spi_writeW(const char *msg, uint32_t address, uint32_t val);
#define cent_spi_writeW(address, val) _cent_spi_writeW(__func__, address, val)

uint32_t _CentauriCsrRead(const char *msg, uint32_t csr_addr);
#define CentauriCsrRead(csr_addr) _CentauriCsrRead(__func__, csr_addr)

void _CentauriCsrWrite(const char *msg, uint32_t csr_addr, uint32_t csr_val);
#define CentauriCsrWrite(csr_addr, csr_val) _CentauriCsrWrite(__func__, csr_addr, csr_val)

#ifdef __cplusplus
}
#endif

#endif /* __CENT_PROBER_H */
