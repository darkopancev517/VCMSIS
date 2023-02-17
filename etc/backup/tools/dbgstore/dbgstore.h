/**
 * Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary.
 *
 * Author: Darko Pancev <darkopancev@vertexcom.com>
 */

#ifndef DBGSTORE_H
#define DBGSTORE_H

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "dbgstore_config.h"
#include "dbgstore_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Enable/Disable DBGSTORE operation.
 */
#ifndef DBGSTORE_ENABLE
#define DBGSTORE_ENABLE (0)
#endif

/** Max number of `char` message that can be store for every DBGSTORE
 *  items. Please make sure it's 4 byte aligned.
 */
#ifndef DBGSTORE_MSG_MAX_SIZE
#define DBGSTORE_MSG_MAX_SIZE (48)
#endif

#if (DBGSTORE_MSG_MAX_SIZE > 48)
#error "DBGSTORE_MSG_MAX_SIZE can't larger than 48 to avoid large fragmentation in FLASH_PAGE"
#endif

#ifndef DBGSTORE_FLASH_PAGE_SIZE
#define DBGSTORE_FLASH_PAGE_SIZE (256)
#endif

/** Max data (in bytes) will be stored in malloc before
 *  it's save into the flash. Increasing this number will increase ram 
 *  requirement but reduce number of flash operation.
 *  Default is 256 bytes, must equal or less than FLASH_PAGE_SIZE
 */
#ifndef DBGSTORE_THRES_BEFORE_UPDATE
#define DBGSTORE_THRES_BEFORE_UPDATE DBGSTORE_FLASH_PAGE_SIZE
#endif

/** Set DBGSTORE_USE_MALLOC to 1, DBGSTORE must use malloc.
 */
#ifndef DBGSTORE_USE_MALLOC
#error "DBGSTORE_USE_MALLOC must be defined."
#else
#if !DBGSTORE_USE_MALLOC
#error "DBGSTORE_USE_MALLOC is 0, DBGSTORE must use malloc function."
#endif
#endif

/** This is the first partition address (PARTITION 0) in the
 *  flash memory space. Make sure it's the start address for
 *  specific flash sector.
 */
#ifndef DBGSTORE_BASE_ADDR
#error "DBGSTORE_BASE_ADDR must be defined."
#endif

/** Number of partition started from DBGSTORE_BASE_ADDR.
 *  Make sure it's even number. Half of the partition will be
 *  used as a backup and the other half will be use as current
 *  working partition. Which partition will be used as a backup
 *  and current working partition will be determined by
 *  `dbg_store_started_index()` function in dbgstore_util.h
 *  for every boot up.
 */
#ifndef DBGSTORE_PARTITION_NUM
#define DBGSTORE_PARTITION_NUM (6)
#endif

/** Flash sector size will be used as the PARTITION SIZE.
 *  The total flash memory allocation for DBGSTORE will equal
 *  to DBGSTORE_PARTITION_NUM * DBGSTORE_PARTITION_SIZE.
 */
#ifndef DBGSTORE_PARTITION_SIZE
#define DBGSTORE_PARTITION_SIZE (0x1000)
#endif

typedef struct dbg_node {
    struct dbg_node *next;
} dbg_node_t;

typedef struct dbg_item
{
    dbg_node_t node;
    uint32_t line;
    uint32_t msg_len;
    void *msg;
} dbg_item_t;

typedef struct {
    dbg_node_t head;
    uint32_t base_addr;
    uint32_t max_len;
    uint32_t added_len;
    uint32_t stored_len;
} dbg_store_t;

/** Initialize the DBGSTORE.
 *
 *  Configure current working partition base address, `dbg_store`
 *  parameter and erase current working partition sector.
 *
 *  @param  None
 *  @return None
 */
void dbg_store_init(void);

/** Add debug message to DBGSTORE.
 *
 *  Set the `line` number and debug message to be stored.
 *  Example:
 *      dbg_store_add(__LINE__, "%s", __func__);
 *      dbg_store_add(__LINE__, "%s: system init failed", __func__);
 *      dbg_store_add(__LINE__, "system init done");
 *
 *  @param  source code line number
 *  @param  print message format just like when we use `printf`
 *  @return 0 if dbg_store_add succeed, -1 if dbg_store_add failed
 */
int  dbg_store_add(uint32_t line, const char *_format, ...);

/** Print previous stored DBGSTORE messages or print backup partition.
 *  
 *  @param  None
 *  @return None
 */
void dbg_store_dump_previous(void);

/** Print current stored DBGSTORE messages or print current working
 *  partition.
 *
 *  @param  None
 *  @return None
 */
void dbg_store_dump_current(void);

/** Print DBGSTORE statistic.
 *
 *  Print the information about dbg_item_t and dbg_store_t.
 *
 *  @param  None
 *  @return None
 */
void dbg_store_stats(void);

/** Force update dbg_store if any items left, usually in Hardfault, System
 *  Reset or Dying gasp situation.
 *
 * @param  None
 * @return (int) numof added message to the flash, -1: failed (not enough partition to store the message)
 */
int dbg_store_force_update(void);

#ifdef __cplusplus
}
#endif

#endif /* DBGSTORE_H */
