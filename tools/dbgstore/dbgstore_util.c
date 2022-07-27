/**
 * Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
 */

#include "dbgstore.h"

#if DBGSTORE_ENABLE

// platform dependent header
#if !DBGSTORE_USE_PRINTF
#include "hal/serial_api.h"
#endif

#include "vc_flash.h"

void dbg_store_flash_erase(uint32_t addr, uint32_t size)
{
    uint32_t start_addr = addr;
    while (size > 0) {
        vcflash_erase_sector(start_addr);
        start_addr += DBGSTORE_PARTITION_SIZE;
        size -= DBGSTORE_PARTITION_SIZE;
    }
}

int dbg_store_flash_write(uint32_t addr, const uint8_t *data, uint32_t size)
{
    uint32_t dest_addr = addr;
    uint32_t remain_size = size;
    uint32_t write_length = 0;

    while (remain_size) {

        if (remain_size > 256) {
            write_length = 256;
        } else {
            write_length = remain_size;
        }

        vcflash_disable_cache();
        vcflash_program_page(dest_addr, data, write_length);
        vcflash_enable_cache();

        remain_size -= write_length;
        dest_addr += write_length;
        data += write_length;
    }

    return size;
}

void dbg_store_mem_dump(const void *address, uint32_t bytes)
{
    volatile uint8_t *addr = (volatile uint8_t *)address;
    uint32_t lines = 0;

    if (bytes == 0)
        return;

    lines = bytes / 16;

    dbg_store_log("\r\n");

    while (lines--) {
        dbg_store_log("%08X : ", addr);
        dbg_store_log("%02X %02X %02X %02X %02X %02X %02X %02X",
                addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
        dbg_store_log(" - ");
        dbg_store_log("%02X %02X %02X %02X %02X %02X %02X %02X",
                addr[8], addr[9], addr[10], addr[11], addr[12], addr[13], addr[14], addr[15]);
        dbg_store_log("\r\n");
        addr += 16;
    }

    bytes = bytes & 0x0f;

    if (bytes) {
        dbg_store_log("%08X :", addr);
        for (int i = 0; i < bytes; ++i) {
            if (i == 8) {
                dbg_store_log(" -");
            }
            dbg_store_log(" %02X", addr[i]);
        }
        dbg_store_log("\r\n");
    }
}

uint32_t dbg_store_started_index(void)
{
    /* Note: if the platform support NVRAM it's better to use that mechanism */
    uint32_t started_index_addr = DBGSTORE_BASE_ADDR - DBGSTORE_PARTITION_SIZE;
    uint32_t updated_value = 0;
    uint32_t result = 0;;

    if (*(uint32_t *)started_index_addr == 0xFFFFFFFF) {
        updated_value = (DBGSTORE_PARTITION_NUM / 2);
        result = 0;
    } else if (*(uint32_t *)started_index_addr == 0) {
        updated_value = DBGSTORE_PARTITION_NUM / 2;
        result = 0;
    } else if (*(uint32_t *)started_index_addr == (DBGSTORE_PARTITION_NUM / 2)) {
        updated_value = 0;
        result = (DBGSTORE_PARTITION_NUM / 2);
    } else {
        /* Note: this should not happen */
        updated_value = 0;
        result = 0;
    }

    vcflash_erase_sector(started_index_addr);

    vcflash_disable_cache();
    vcflash_program_page(started_index_addr, (const uint8_t *)&updated_value, 4);
    vcflash_enable_cache();

    return result;
}

#if !DBGSTORE_USE_PRINTF
extern int stdio_uart_inited;
extern serial_t stdio_uart;

int dbg_store_log(const char *_format, ...)
{
    if (!stdio_uart_inited) {
        serial_init(&stdio_uart, STDIO_UART_TX, STDIO_UART_RX);
    }

    char log_string[256];
    int chars_written;
    va_list args;

    va_start(args, _format);
    chars_written = vsnprintf(&log_string[0], sizeof(log_string), _format, args);
    va_end(args);

    if ((chars_written == 0) || (chars_written > sizeof(log_string)))
        return -1;

    for (int i = 0; i < chars_written; i++) {
        serial_putc(&stdio_uart, log_string[i]);
    }

    return chars_written;
}
#endif

#endif /* #if DBGSTORE_ENABLE */
