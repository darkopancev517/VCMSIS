#include <unistd.h>
#include <reent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <stdint.h>

#include "hal/serial_api.h"

extern int stdio_uart_inited;
extern serial_t stdio_uart;

void _exit(int n)
{
    while(1);
}

/**
 * Allocate memory from the heap.
 */
void *_sbrk_r(struct _reent *r, ptrdiff_t incr)
{
    return NULL;
}

_ssize_t _read_r(struct _reent *r, int fd, void *buffer, size_t count)
{
    if (!stdio_uart_inited) {
        serial_init(&stdio_uart, STDIO_UART_TX, STDIO_UART_RX);
    }

    (void) r;
    (void) fd;

    for (int i = 0; i < count; i++) {
        *(char *)buffer = serial_getc(&stdio_uart);
        buffer++;
    }

    return count;
}

_ssize_t _write_r(struct _reent *r, int fd, const void *data, size_t count)
{
    if (!stdio_uart_inited) {
        serial_init(&stdio_uart, STDIO_UART_TX, STDIO_UART_RX);
    }

    (void) r;
    (void) fd;

    for (int i = 0; i < count; i++) {
        serial_putc(&stdio_uart, *(const char *)data);
        data++;
    }

    return count;
}

/* Stubs to avoid linking errors, these functions do not have any effect */
int _open_r(struct _reent *r, const char *name, int flags, int mode)
{
    (void) name;
    (void) flags;
    (void) mode;
    r->_errno = ENODEV;
    return -1;
}

int _close_r(struct _reent *r, int fd)
{
    (void) fd;
    r->_errno = ENODEV;
    return -1;
}

_off_t _lseek_r(struct _reent *r, int fd, _off_t pos, int dir)
{
    (void) fd;
    (void) pos;
    (void) dir;
    r->_errno = ENODEV;
    return -1;
}

int _fstat_r(struct _reent *r, int fd, struct stat *st)
{
    (void) fd;
    (void) st;
    r->_errno = ENODEV;
    return -1;
}

int _stat_r(struct _reent *r, const char *name, struct stat *st)
{
    (void) name;
    (void) st;
    r->_errno = ENODEV;
    return -1;
}

int _unlink_r(struct _reent *r, const char *path)
{
    (void) path;
    r->_errno = ENODEV;
    return -1;
}

int _isatty_r(struct _reent *ptr, int fd)
{
    if (fd >= 0 && fd < 3) {
        return 1;
    }

    ptr->_errno = ENOTSUP;
    return -1;
}
