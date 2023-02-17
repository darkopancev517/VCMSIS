// SPI Prober
//
// [2014-??-??]
//
//

#ifndef __VTPROBE_INC__
#define __VTPROBE_INC__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

#include "bin_object.h"

enum PROBE_ERRORS {
    VTPROBE_ERR_SUCCESS             = 0,
    VTPROBE_ERR_FAILED              = -1,
    VTPROBE_ERR_INVALID_DEVICE      = -2,
    VTPROBE_ERR_ARGUMENT            = -3,
    VTPROBE_ERR_IO_READ             = -10,
    VTPROBE_ERR_IO_WRITE            = -11,
    VTPROBE_ERR_IO_GENERIC          = -12,
    VTPROBE_ERR_IO_SIZE             = -13,
    VTPROBE_ERR_ACK                 = -20,
    VTPROBE_ERR_CHECKSUM            = -21,
    VTPROBE_ERR_FORMAT              = -22,
    VTPROBE_ERR_ALLOC               = -30,
};

struct vtprobe_packet
{
    enum CONSTANTS {
        VTPROBE_IO_DATA_SIZE                    = 512,
    };

    enum VTPROBE_CMD {
        VTPROBE_CMD_BASE_REG_IN                 = 0x44,
        VTPROBE_CMD_BASE_REG_OUT                = 0x64,

        VTPROBE_CMD_STATUS_REG_IN               = 0x51,
        VTPROBE_CMD_STATUS_REG_OUT              = 0x71,

        VTPROBE_CMD_WORD_IN                     = 0x04,
        VTPROBE_CMD_WORD_IN_DELAY               = 0x14,
        VTPROBE_CMD_WORD_IN_OFFSET              = 0x84,
        VTPROBE_CMD_WORD_IN_OFFSET_DELAY        = 0x94,
        VTPROBE_CMD_WORD_OUT                    = 0x24,
        VTPROBE_CMD_WORD_OUT_OFFSET             = 0xa4,

        VTPROBE_CMD_HALF_IN                     = 0x02,
        VTPROBE_CMD_HALF_IN_DELAY               = 0x12,
        VTPROBE_CMD_HALF_IN_OFFSET              = 0x82,
        VTPROBE_CMD_HALF_IN_OFFSET_DELAY        = 0x92,
        VTPROBE_CMD_HALF_OUT                    = 0x22,
        VTPROBE_CMD_HALF_OUT_OFFSET             = 0xa2,

        VTPROBE_CMD_BYTE_IN                     = 0x01,
        VTPROBE_CMD_BYTE_IN_DELAY               = 0x11,
        VTPROBE_CMD_BYTE_IN_OFFSET              = 0x81,
        VTPROBE_CMD_BYTE_IN_OFFSET_DELAY        = 0x91,
        VTPROBE_CMD_BYTE_OUT                    = 0x21,
        VTPROBE_CMD_BYTE_OUT_OFFSET             = 0xa1,
    };

    struct mpsse_context *_mpsse_spi;

    uint32_t _size_out;
    uint32_t _size_in;

    uint8_t _data_out[VTPROBE_IO_DATA_SIZE];
    uint8_t _data_in[VTPROBE_IO_DATA_SIZE];

    vtprobe_packet() : _mpsse_spi(NULL), _size_out(0), _size_in(0) {}
    vtprobe_packet(struct mpsse_context *mpsse) : _mpsse_spi(mpsse), _size_out(0), _size_in(0) {}
    ~vtprobe_packet() {}

    void do_cmd_base_reg_in();
    void do_cmd_base_reg_out(uint32_t base_addr);

    void do_cmd_delay_reg_in();
    void do_cmd_delay_reg_out(uint32_t status);

    void do_cmd_word_in(uint32_t addr, uint32_t delay);
    void do_cmd_word_in_offset(uint32_t offset, uint32_t delay);
    void do_cmd_word_out(uint32_t addr, uint32_t data);
    void do_cmd_word_out_offset(uint32_t offset, uint32_t data);

    void do_cmd_hword_in(uint32_t addr, uint32_t delay);
    void do_cmd_hword_in_offset(uint32_t offset, uint32_t delay);
    void do_cmd_hword_out(uint32_t addr, uint32_t data);
    void do_cmd_hword_out_offset(uint32_t offset, uint32_t data);

    void do_cmd_byte_in(uint32_t addr, uint32_t delay);
    void do_cmd_byte_in_offset(uint32_t offset, uint32_t delay);
    void do_cmd_byte_out(uint32_t addr, uint8_t data);
    void do_cmd_byte_out_offset(uint32_t offset, uint8_t data);

    int send_out();

    // private ...
    // ...
};

class vtprobe
{
public:

    enum CONSTANTS {
        VTPROBE_IRAM_BURST_SIZE     = 256,
        VTPROBE_RAW_DATA_SIZE       = 2048,
        VTPROBE_READ_DELAY_CYCLE    = 0xf,
    };

protected:

    struct ftdi_context *_ftdi_ctxt;
    struct mpsse_context *_mpsse_spi;

public:

    vtprobe();
    ~vtprobe();

    int open();
    void close();

    int do_probe_cmd();

protected:

    int spi_open();
    int spi_close();

    int do_base_cmd();
    int do_delay_cmd();

    int do_word_read_cmd(bool indirect);
    int do_word_write_cmd(bool indirect);

};

#endif  // __VTPROBE_INC__

