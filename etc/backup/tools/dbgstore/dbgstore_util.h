/**
 * Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
 */

#ifndef DBGSTORE_UTIL_H
#define DBGSTORE_UTIL_H

#include <stdint.h>
#include <stdio.h>

#include "dbgstore_config.h"

#ifdef __cplusplus
extern "C" {
#endif

void     dbg_store_flash_erase(uint32_t addr, uint32_t size);
int      dbg_store_flash_write(uint32_t addr, const uint8_t *data, uint32_t size);
void     dbg_store_mem_dump(const void *address, uint32_t bytes);
uint32_t dbg_store_started_index(void);

#if DBGSTORE_USE_PRINTF
#define dbg_store_log(...) printf(__VA_ARGS__)
#else
int dbg_store_log(const char *_format, ...);
#endif

#ifdef __cplusplus
}
#endif

#endif /* DBGSTORE_UTIL_H */
