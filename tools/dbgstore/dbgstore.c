/**
 * Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary.
 *
 * Author: Darko Pancev <darkopancev@vertexcom.com>
 */

#include "dbgstore.h"

#if DBGSTORE_ENABLE

#define DBGSTORE_PARTITION_USE (DBGSTORE_PARTITION_NUM / 2)

static volatile uint32_t curr_partition_started_index = 0; 
static volatile uint32_t curr_partition = 0;
static volatile uint32_t curr_partition_max = 0;
static dbg_store_t *dbg_store[DBGSTORE_PARTITION_NUM] = { 0 };

static int dbg_store_update_item(void);
static int dbg_store_update_head(void);

void dbg_store_init(void)
{
    curr_partition_started_index = dbg_store_started_index();
    curr_partition = curr_partition_started_index;
    curr_partition_max = curr_partition_started_index + DBGSTORE_PARTITION_USE;

    for (int i = curr_partition_started_index; i < curr_partition_max; i++) {
        dbg_store_flash_erase(DBGSTORE_BASE_ADDR + (i * DBGSTORE_PARTITION_SIZE),
                              DBGSTORE_PARTITION_SIZE);
    }
}

static dbg_store_t *_dbg_store_alloc(void)
{
    dbg_store_t *store = (dbg_store_t *)malloc(sizeof(dbg_store_t));
    memset(store, 0, sizeof(dbg_store_t));

    store->head.next = NULL;
    store->base_addr = DBGSTORE_BASE_ADDR + (curr_partition * DBGSTORE_PARTITION_SIZE);
    store->max_len = DBGSTORE_PARTITION_SIZE;
    store->added_len = sizeof(dbg_store_t);
    store->stored_len = 0;

    return store;
}

static void _append_item(dbg_node_t *list, dbg_node_t *new_node)
{
    while (list->next) {
        list = list->next;
    }
    new_node->next = list->next;
    list->next = new_node;
}

int dbg_store_add(uint32_t line, const char *_format, ...)
{
    if (curr_partition >= curr_partition_max) {
        /* we don't have enough memory to store this item */
        dbg_store_log("*** NOT ENOUGH MEMORY FOR DBGSTORE ***\r\n");
        return -1;
    }

    dbg_item_t *item = NULL;
    int msg_len = 0;
    va_list args;

    // get message length
    va_start(args, _format);
    msg_len = vsnprintf(NULL, 0, _format, args);
    va_end(args);

    if (msg_len <= 0)
        return -1;

    // Note: make space to store trailing '\0' otherwise last char may missing
    // eventhough it was not exceeding DBGSTORE_MSG_MAX_SIZE
    msg_len += 1;

    if (msg_len > DBGSTORE_MSG_MAX_SIZE)
        msg_len = DBGSTORE_MSG_MAX_SIZE;

    // Note: make sure message length is 8 byte aligned, std library
    // use 8 byte alignment
    if (msg_len % 8) {
        msg_len = msg_len + (8 - (msg_len % 8));
    }

    // make sure it's not exceed the DBGSTORE_MSG_MAX_SIZE
    if (msg_len > DBGSTORE_MSG_MAX_SIZE)
        msg_len = DBGSTORE_MSG_MAX_SIZE;

    // allocate dbg_item_t
    item = (dbg_item_t *)malloc(sizeof(dbg_item_t));
    if (item == NULL)
        return -1;

    // allocate, format and set message information
    item->line = line;
    item->msg_len = msg_len;
    item->msg = (void *)malloc(item->msg_len);
    if (item->msg == NULL)
        return -1;

    // format the message
    memset(item->msg, 0, item->msg_len);
    va_start(args, _format);
    vsnprintf(item->msg, item->msg_len, _format, args);
    va_end(args);

    // allocate curr_partition_store (HEAD) if needed
    if (dbg_store[curr_partition] == NULL) {
        dbg_store[curr_partition] = _dbg_store_alloc();
    }

    int len_to_add = dbg_store[curr_partition]->added_len + sizeof(dbg_item_t) + item->msg_len;

    if (len_to_add >= DBGSTORE_THRES_BEFORE_UPDATE) {
        // store previous added_len to the flash
        if (dbg_store_update_item() != 0) {
            // not enough partition to store these debug messages
            free(item->msg);
            free(item);
            return -1;
        }
    }

    // update list
    _append_item(&dbg_store[curr_partition]->head, &item->node);

    // increase numof added data
    dbg_store[curr_partition]->added_len += sizeof(dbg_item_t) + item->msg_len;

    return (int)item->msg_len;
}

static int dbg_store_update_item(void)
{
    uint32_t curr_partition_base = DBGSTORE_BASE_ADDR + (curr_partition * DBGSTORE_PARTITION_SIZE);
    uint32_t write_addr = curr_partition_base;

    write_addr += sizeof(dbg_store_t);

    dbg_node_t *list = NULL;

    // get correct starting address if there was an item stored

    if (*(uint32_t *)write_addr != 0xFFFFFFFF) {
        list = (dbg_node_t *)write_addr;
        dbg_node_t *prev = NULL;
        while (list->next) {
            dbg_item_t *temp = (dbg_item_t *)list->next;
            if (temp->line == 0xFFFFFFFF) {
                if (prev != NULL) {
                    write_addr = *(uint32_t *)(prev->next);
                } else {
                    uint32_t value = *(uint32_t *)write_addr;
                    write_addr = value;
                }
                break;
            }
            prev = list;
            list = list->next;
        }
    }

    // start write items from the `write_addr` value

write_items:

    list = &dbg_store[curr_partition]->head;

    while (list->next) {

        dbg_item_t *item = (dbg_item_t *)list->next;

        uint32_t next_item_addr = (write_addr + sizeof(dbg_item_t) + item->msg_len);
        uint32_t next_item_base = next_item_addr & 0xFFFFF000;
        uint32_t start_page = write_addr & 0xFFFFFF00;

        int remain_in_page = DBGSTORE_FLASH_PAGE_SIZE - (write_addr - start_page);

        if (next_item_base != curr_partition_base) {
            if (curr_partition == (curr_partition_max - 1)) {
                // last partition doesn't have enough space to store this debug item
                dbg_store[curr_partition]->head.next = list->next;
                dbg_store_update_head();
                return -1;
            }
            // Note: curr_partition doesn't have enough space to store this debug item
            // get next partition if it still available
            dbg_store[curr_partition]->head.next = list->next;
            if (dbg_store_update_head() != 0) {
                return -1;
            }
            curr_partition_base = DBGSTORE_BASE_ADDR + (curr_partition * DBGSTORE_PARTITION_SIZE);
            write_addr = curr_partition_base;
            write_addr += sizeof(dbg_store_t);
            goto write_items;
        }

        // make sure we have space for dummy item, when we reach the end of
        // DBGSTORE_FLASH_PAGE_SIZE. Otherwise just use next page.

        int remain_after_add_item = remain_in_page - (sizeof(dbg_item_t) + item->msg_len);

        if (remain_after_add_item < sizeof(dbg_item_t)) {
            if ((write_addr & 0xF00) != 0xF00) {
                // we are not in last page of this curr_partition
                next_item_addr = start_page + DBGSTORE_FLASH_PAGE_SIZE;
            }
        } else {
            // check if the message fit in this flash page
            if ((write_addr & 0xFFFFFF00) != (next_item_addr & 0xFFFFFF00)) {
                uint32_t next_page = write_addr + remain_in_page;
                if (remain_in_page >= sizeof(dbg_item_t)) {
                    // create dummy item that point to the next page
                    dbg_store_flash_write(write_addr, (const uint8_t *)&next_page, 4);
                    write_addr += 4;
                    uint32_t dummy_line = 0xdeadbeef;
                    dbg_store_flash_write(write_addr, (const uint8_t *)&dummy_line, 4);
                    // advance to next page
                    write_addr = next_page;
                    next_item_addr = (write_addr + sizeof(dbg_item_t) + item->msg_len);
                } else {
                    // just advance to next page
                    write_addr = next_page;
                    next_item_addr = (write_addr + sizeof(dbg_item_t) + item->msg_len);
                }
            }
        }

        // write dbg_item_t info
        dbg_store_flash_write(write_addr, (const uint8_t *)&next_item_addr, 4);
        write_addr += 4;
        dbg_store_flash_write(write_addr, (const uint8_t *)&item->line, 4);
        write_addr += 4;
        dbg_store_flash_write(write_addr, (const uint8_t *)&item->msg_len, 4);
        write_addr += 4;
        uint32_t msg_addr = write_addr + 4;
        dbg_store_flash_write(write_addr, (const uint8_t *)&msg_addr, 4);
        write_addr += 4;

        // write item->msg
        dbg_store_flash_write(write_addr, (const uint8_t *)item->msg, item->msg_len);
        write_addr += item->msg_len;

        // update dbg_store information
        dbg_store[curr_partition]->stored_len += (sizeof(dbg_item_t) + item->msg_len);
        dbg_store[curr_partition]->added_len -= (sizeof(dbg_item_t) + item->msg_len);

        list = list->next;

        // free memory used by this item
        free(item->msg);
        free(item);
    }

    // we have transfer all the list to the flash
    dbg_store[curr_partition]->head.next = NULL;
    dbg_store[curr_partition]->added_len = 0;

    return 0;
}

static int dbg_store_update_head(void)
{
    // store previous partition and increase current partition number

    uint32_t prev_partition = curr_partition;
    curr_partition += 1;

    // check if there was unstored debug messages

    if (curr_partition < curr_partition_max) {
        if (dbg_store[prev_partition]->added_len != 0) {
            // allocate dbg_store
            dbg_store[curr_partition] = _dbg_store_alloc();
            if (dbg_store[curr_partition] == NULL) {
                return -1;
            }

            // transfer unstored items to new partition
            dbg_node_t *list = &dbg_store[prev_partition]->head;
            while (list->next) {
                dbg_item_t *item = (dbg_item_t *)list->next;
                dbg_store[curr_partition]->added_len += (sizeof(dbg_item_t) + item->msg_len);
                list = list->next;
            }
            dbg_store[curr_partition]->head.next = dbg_store[prev_partition]->head.next;
            dbg_store[prev_partition]->head.next = NULL;
            dbg_store[prev_partition]->added_len = 0;
        }
    } else {
        if (dbg_store[prev_partition]->added_len != 0) {
            // we have reach the end on the last partition and have item still allocated
            // in ram by malloc, free those items
            dbg_node_t *list = &dbg_store[prev_partition]->head;
            while (list->next) {
                dbg_item_t *item = (dbg_item_t *)list->next;
                dbg_store[prev_partition]->added_len -= (sizeof(dbg_item_t) + item->msg_len);
                list = list->next;
                free(item->msg);
                free(item);
            }
            dbg_store[prev_partition]->head.next = NULL;
            //dbg_store[prev_partition]->added_len = 0;
        }
    }

    // write dbg_store_t or previous partition head to flash

    uint32_t write_addr = DBGSTORE_BASE_ADDR + (prev_partition * DBGSTORE_PARTITION_SIZE);
    uint32_t next_item_addr = write_addr + sizeof(dbg_store_t);

    dbg_store_flash_write(write_addr, (const uint8_t *)&next_item_addr, 4);
    write_addr += 4;
    dbg_store_flash_write(write_addr, (const uint8_t *)&dbg_store[prev_partition]->base_addr, 16);

    // free previous partition dbg_store_t
    free(dbg_store[prev_partition]);
    dbg_store[prev_partition] = NULL;

    return 0;
}

static void _print_stored_list(dbg_node_t *list)
{
    uint32_t partition_base = *(uint32_t *)list & 0xFFFFF000;

    while (list->next) {
        if ((*(uint32_t *)list->next & 0xFFFFF000) == partition_base) {
            dbg_item_t *item = (dbg_item_t *)list->next;
            if (item->line != 0xFFFFFFFF) {
                if (item->line != 0xdeadbeef) {
                    dbg_store_log("line: %d - %s\r\n", item->line, (char *)item->msg);
                }
            } else {
                break;
            }
        } else {
            break;
        }
        list = list->next;
    }
}

static void _print_added_list(dbg_node_t *list)
{
    while (list->next) {
        dbg_item_t *item = (dbg_item_t *)list->next;
        dbg_store_log("line: %d - %s\r\n", item->line, (char *)item->msg);
        list = list->next;
    }
}

static void _dbg_store_print_current(int started_index, int max_index)
{
    dbg_node_t *list = NULL;

    for (int i = started_index; i < max_index; i++) {

        uint32_t partition_base = DBGSTORE_BASE_ADDR + (i * DBGSTORE_PARTITION_SIZE);

        dbg_store_log("\r\n");
        dbg_store_log("-------------------------------------------\r\n");
        dbg_store_log("CURRENT DBGSTORE PARTITION: %d - 0x%08X\r\n", i, partition_base);
        dbg_store_log("-------------------------------------------\r\n");

        if ((dbg_store[i] != NULL) || (*(uint32_t *)partition_base != 0xFFFFFFFF)) {
            if (*(uint32_t *)partition_base != 0xFFFFFFFF) {
                dbg_store_t *dbg = (dbg_store_t *)partition_base;
                if (dbg->stored_len != 0) {
                    dbg_node_t *list = &dbg->head;
                    _print_stored_list(list);
                }
            } else {
                uint32_t dbgstore_data = dbg_store[i]->stored_len + dbg_store[i]->added_len;
                if (dbgstore_data != 0) {
                    if ((*(uint32_t *)partition_base == 0xFFFFFFFF) && dbg_store[i]->stored_len != 0) {
                        dbg_item_t *first_item = (dbg_item_t *)(partition_base + sizeof(dbg_store_t));
                        dbg_store_log("line: %d - %s\r\n", first_item->line, (char *)first_item->msg);
                        list = (dbg_node_t *)(partition_base + sizeof(dbg_store_t));
                        _print_stored_list(list);
                    }
                    list = &dbg_store[i]->head;
                    _print_added_list(list);
                }
            }
        } else {
            dbg_store_log("\r\n**** THIS PARTITION IS EMPTY ****\r\n");
            dbg_store_log("\r\n");
            break;
        }
    }
}

static void _dbg_store_print_previous(int started_index, int max_index)
{
    dbg_node_t *list = NULL;

    for (int i = started_index; i < max_index; i++) {

        uint32_t partition_base = DBGSTORE_BASE_ADDR + (i * DBGSTORE_PARTITION_SIZE);

        dbg_store_log("\r\n");
        dbg_store_log("-------------------------------------------\r\n");
        dbg_store_log("PREVIOUS DBGSTORE PARTITION: %d - 0x%08X\r\n", i, partition_base);
        dbg_store_log("-------------------------------------------\r\n");

        if (*(uint32_t *)partition_base != 0xFFFFFFFF) {
            dbg_store_t *store_ptr = (dbg_store_t *)partition_base;
            if (store_ptr->stored_len != 0) {
                list = &store_ptr->head;
                _print_stored_list(list);
            } else {
                dbg_store_log("\r\n**** THIS PARTITION IS EMPTY ****\r\n");
                dbg_store_log("\r\n");
                break;
            }
        } else {
            partition_base += sizeof(dbg_store_t);
            if (*(uint32_t *)partition_base != 0xFFFFFFFF) {
                dbg_item_t *first_item = (dbg_item_t *)partition_base;
                dbg_store_log("line: %d - %s\r\n", first_item->line, (char *)first_item->msg);
                list = (dbg_node_t *)partition_base;
                _print_stored_list(list);
            } else {
                dbg_store_log("\r\n**** THIS PARTITION IS EMPTY ****\r\n");
                dbg_store_log("\r\n");
                break;
            }
        }
    }
}

void dbg_store_dump_previous(void)
{
    int previous_started_index = 0;
    if (curr_partition_started_index == 0) {
        previous_started_index = DBGSTORE_PARTITION_USE;
    }
    int previous_started_index_max = previous_started_index + DBGSTORE_PARTITION_USE;
    _dbg_store_print_previous(previous_started_index, previous_started_index_max);
}

void dbg_store_dump_current(void)
{
    _dbg_store_print_current(curr_partition_started_index, curr_partition_max);
}

void dbg_store_stats(void)
{
    dbg_store_log("\r\n");
    dbg_store_log("-------------------------------------------\r\n");
    dbg_store_log("DBGSTORE CURRENT STATISTICS\r\n");
    dbg_store_log("-------------------------------------------\r\n");
    dbg_store_log("partitions       : %d (%d backup - %d current)\r\n",
            DBGSTORE_PARTITION_NUM, DBGSTORE_PARTITION_USE, DBGSTORE_PARTITION_USE);

    dbg_store_log("partition size   : %d bytes\r\n", DBGSTORE_PARTITION_SIZE);
    dbg_store_log("max message size : %d bytes\r\n", DBGSTORE_MSG_MAX_SIZE);
    dbg_store_log("dbg_store_t size : %d bytes\r\n", sizeof(dbg_store_t));
    dbg_store_log("dbg_item_t size  : %d bytes\r\n", sizeof(dbg_item_t));
    if (dbg_store[curr_partition] != NULL) {
        dbg_store_log("max capacity     : %d bytes\r\n", (dbg_store[curr_partition]->max_len * DBGSTORE_PARTITION_USE));
    }

    uint32_t total_stored_items = 0;

    for (int i = curr_partition_started_index; i < curr_partition_max; i++) {
        if (dbg_store[i] != NULL) {
            total_stored_items += (dbg_store[i]->stored_len + dbg_store[i]->added_len);
        }
    }

    dbg_store_log("capacity remains : %d bytes\r\n", (dbg_store[curr_partition]->max_len * DBGSTORE_PARTITION_USE) - total_stored_items);

    dbg_store_log("\r\nCURRENTLY USE PARTITION:\r\n");

    for (int p = curr_partition_started_index; p < curr_partition_max; p++) {

        uint32_t partition_base = DBGSTORE_BASE_ADDR + (p * DBGSTORE_PARTITION_SIZE);

        dbg_store_log("\r\n");
        dbg_store_log("PARTITION: %d - 0x%08X\r\n", p, partition_base);

        if ((dbg_store[p] != NULL) || (*(uint32_t *)partition_base != 0xFFFFFFFF)) {
            if ((*(uint32_t *)partition_base) != 0xFFFFFFFF) {
                dbg_store_t *dbg = (dbg_store_t *)partition_base;
                if (dbg->stored_len != 0) {
                    dbg_store_log("capacity : %d bytes\r\n", dbg->max_len);
                    dbg_store_log("malloc   : %d bytes\r\n", dbg->added_len);
                    dbg_store_log("stored   : %d bytes\r\n", dbg->stored_len);
                }
            } else {
                uint32_t dbgstore_items = dbg_store[p]->stored_len + dbg_store[p]->added_len;
                if (dbgstore_items != 0) {
                    dbg_store_log("capacity : %d bytes\r\n", dbg_store[p]->max_len);
                    dbg_store_log("malloc   : %d bytes\r\n", dbg_store[p]->added_len);
                    dbg_store_log("stored   : %d bytes\r\n", dbg_store[p]->stored_len);
                }
            }
        } else {
            dbg_store_log("\r\n**** THIS PARTITION IS EMPTY ****\r\n");
            break;
        }
    }
}

int dbg_store_force_update(void)
{
    if (dbg_store[curr_partition] != NULL) {
        if (dbg_store[curr_partition]->added_len != 0) {
            if (dbg_store_update_item() != 0) {
                // not enough partition to store these debug messages
                return -1;
            }
            return dbg_store[curr_partition]->added_len;
        }
    }
    return 0;
}

#else
void dbg_store_init(void) {}
int  dbg_store_add(uint32_t line, const char *_format, ...)
{
    (void) line;
    (void) _format;
    return 0;
}
void dbg_store_dump_previous(void) {}
void dbg_store_dump_current(void) {}
void dbg_store_stats(void) {}
int  dbg_store_force_update(void)
{
    return 0;
}
#endif /* #if DBGSTORE_ENABLE */
