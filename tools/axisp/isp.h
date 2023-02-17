// Intel Hexadecimal Object File Reader
//
// [2014-??-??]
//
//

#ifndef __BASE_ISP_INC__
#define __BASE_ISP_INC__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "xmodem.h"

#define ISP_IRAM0_BASE                  0x20000000
#define ISP_IRAM0_SIZE                  0x8000

#define ISP_IRAM1_BASE                  0x30000000
#define ISP_IRAM1_SIZE                  0x8000

#define ISP_BIST_BURST_SIZE             XMODEM_MAX_DATA_SIZE

#define ISP_FALSE_RETRY_COUNT           6

#define ISP_ACK_WAIT_SLEEP_US           (100)
#define ISP_ACK_TIMEOUT                 (10000)

enum ERRORS {
    ISP_ERR_SUCCESS           = 0,
    ISP_ERR_FAILED            = -1,
    ISP_ERR_INVALID_DEVICE    = -2,
    ISP_ERR_ARGUMENT          = -3,
    ISP_ERR_IO_READ           = -10,
    ISP_ERR_IO_WRITE          = -11,
    ISP_ERR_IO_GENERIC        = -12,
    ISP_ERR_IO_SIZE           = -13,
    ISP_ERR_ACK               = -20,
    ISP_ERR_CHECKSUM          = -21,
    ISP_ERR_FORMAT            = -22,
    ISP_ERR_ALLOC             = -30,
    ISP_ERR_PROTOCOL          = -90,
};

class isp_packet
{
public:
    isp_packet() {}
    //isp_packet(int fd) {}
    //isp_packet(struct mpsse_context *mpsse) {}
    virtual ~isp_packet() {}

    virtual void do_cmd_ping() = 0;
    virtual void do_cmd_break() = 0;

    virtual void do_cmd_word_read(uint32_t addr, uint32_t nr_words) = 0;
    virtual void do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t nr_words) = 0;
    virtual void do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t nr_words, bool DMAFlag) = 0;
    virtual void do_cmd_word_write(uint32_t addr, uint32_t data) = 0;
    virtual void do_cmd_word_write(uint32_t addr, uint32_t data, bool DMAFlag) = 0;
    virtual void do_cmd_setup(uint32_t index, uint32_t value) = 0;
    virtual void do_cmd_read_checksum(uint32_t addr, uint32_t size) = 0;

    virtual int send_out(bool wait_ack = true, uint32_t data_in_delay = 0) = 0;
};

class isp
{
public:

    isp() {}
    virtual ~isp() {}

    virtual int open() = 0;
    virtual void close() = 0;

    virtual void quiet(bool q = true) = 0;

    virtual int do_dev_list() = 0;

    virtual int do_cli_cmd() = 0;

    virtual int do_word_read() = 0;
    virtual int do_word_write() = 0;
    virtual int do_bist(uint32_t bist_base, uint32_t bist_size, uint32_t pattern) = 0;

    virtual int do_isp() = 0;
    virtual int do_fastisp() = 0;
    virtual int do_sumisp() = 0;

    virtual int do_ping() = 0;
    virtual int do_break() = 0;
    virtual int do_reboot() = 0;
    virtual int do_setup() = 0;
};

#endif  // __BASE_ISP_INC__

