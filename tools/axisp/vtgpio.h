// GPIO
//
// [2014-??-??]
//
//

#ifndef __VTGPIO_INC__
#define __VTGPIO_INC__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

enum GPIO_ERRORS {
    VTGPIO_ERR_SUCCESS             = 0,
    VTGPIO_ERR_FAILED              = -1,
    VTGPIO_ERR_INVALID_DEVICE      = -2,
    VTGPIO_ERR_ARGUMENT            = -3,
    VTGPIO_ERR_IO_READ             = -10,
    VTGPIO_ERR_IO_WRITE            = -11,
    VTGPIO_ERR_IO_GENERIC          = -12,
    VTGPIO_ERR_IO_SIZE             = -13,
    VTGPIO_ERR_ACK                 = -20,
    VTGPIO_ERR_CHECKSUM            = -21,
    VTGPIO_ERR_FORMAT              = -22,
    VTGPIO_ERR_ALLOC               = -30,
};

class vtgpio
{
public:
protected:

    struct ftdi_context *_ftdi_ctxt;
    struct mpsse_context *_mpsse_spi;

public:

    vtgpio();
    ~vtgpio();

    int open();
    void close();

    int do_gpio_cmd();

protected:

};

#endif  // __VTGPIO_INC__

