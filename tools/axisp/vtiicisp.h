// Intel Hexadecimal Object File Reader
//
// [2014-??-??]
//
//

#ifndef __VTISP_I2C_INC__
#define __VTISP_I2C_INC__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

#include "isp.h"
#include "bin_object.h"

//#define VTIICISP_WORD_READ_DELAY(w)         0
#define VTIICISP_WORD_READ_DELAY(w)         (100 + 3 * (w))

//#define VTIICISP_WORD_WRITE_DELAY(w)        0
#define VTIICISP_WORD_WRITE_DELAY(w)        (100 + 15 * (w))

#define VTIICISP_EFC_ERASE_UNLOCK_DELAY     (500)
#define VTIICISP_EFC_ERASE_LOCK_DELAY       (2000)

#define VTIICISP_EFC_WRONLY_UNLOCK_DELAY    (500)
#define VTIICISP_EFC_WRONLY_LOCK_DELAY      (3000)

#define VTIICISP_EFC_PROG_UNLOCK_DELAY      (2000)
#define VTIICISP_EFC_PROG_LOCK_DELAY        (7000)

class vtiicisp_packet : public isp_packet
{
public:

    enum CONSTANTS {
        VTIICISP_RAW_DATA_SIZE          = 2048,
        VTIICISP_I2C_PAGE_SIZE          = 512,
        //VTIICISP_I2C_ACK_SIZE           = 4,
        VTIICISP_I2C_PING_ACK_DELAY     = 0,
        //VTIICISP_I2C_DATA_IN_DELAY      = 1000,
        VTIICISP_I2C_SALVE_ADDR_7BIT    = 0x7b,
        VTIICISP_I2C_SALVE_ADDR_READ    = (0x7b << 1) | 1,
        VTIICISP_I2C_SALVE_ADDR_WRITE   = (0x7b << 1),
        VTIICISP_I2C_WRITE              = 0,
        VTIICISP_I2C_READ               = 0x01,
    };

    enum SETUP_INDEX {
        VTIICISP_SETID_DATA_OUT_TIMEOUT = 0,
    };

    enum VTIICISP_CMD {
        // hint: 0x00 && 0xff is not suitable for command encoding since the default
        // state on the data bus is either 0x00 or 0xff and could be a garbage data
        // if the master and slave state-switch is out of sync.
        VTIICISP_CMD_PING               = 0x0f,
        VTIICISP_CMD_ACK                = 0xf0,

        VTIICISP_CMD_WORD_READ          = 0x11,
        VTIICISP_CMD_PAGE_READ          = 0x12,
        VTIICISP_CMD_WORDS_READ         = 0x13,

        VTIICISP_CMD_WORD_WRITE         = 0x21,
        VTIICISP_CMD_PAGE_WRITE         = 0x22,
        VTIICISP_CMD_WORDS_WRITE        = 0x23,

        VTIICISP_CMD_SETUP              = 0x88,
    };

    struct mpsse_context *_mpsse_i2c;

    uint32_t _size_out;
    uint32_t _size_in;
    //uint32_t _delay;

    uint8_t _data_out[VTIICISP_RAW_DATA_SIZE];
    uint8_t _data_in[VTIICISP_RAW_DATA_SIZE];

    vtiicisp_packet() : _mpsse_i2c(NULL), _size_out(0), _size_in(0) {}
    vtiicisp_packet(struct mpsse_context *mpsse) : _mpsse_i2c(mpsse), _size_out(0), _size_in(0) {}
    virtual ~vtiicisp_packet() {}

    virtual void do_cmd_ping();
    virtual void do_cmd_break();

    virtual void do_cmd_word_read(uint32_t addr, uint32_t nr_words);
    virtual void do_cmd_read_checksum(uint32_t addr, uint32_t size);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t nr_words);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t nr_words, bool DMAFlag);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t data);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t data, bool DMAFlag);

    virtual void do_cmd_setup(uint32_t index, uint32_t value);

    virtual int send_out(bool wait_ack = true, uint32_t data_in_delay = 0);

private:

};

class vtiicisp : public isp
{
protected:

    struct ftdi_context *_ftdi_ctxt;
    struct mpsse_context *_mpsse_i2c;

public:

    vtiicisp();
    virtual ~vtiicisp();

    virtual int open();
    virtual void close();

    virtual void quiet(bool q = true);

    virtual int do_dev_list();

    virtual int do_cli_cmd();

    virtual int do_word_read();
    virtual int do_word_write();
    virtual int do_bist(uint32_t bist_base, uint32_t bist_size, uint32_t pattern);

    virtual int do_isp();
    virtual int do_fastisp();
    virtual int do_sumisp();

    virtual int do_ping();
    virtual int do_break();
    virtual int do_reboot();

    virtual int do_setup();

protected:

    int i2c_open();
    int i2c_close();

    int do_remap_get(uint32_t &remap);

    int prog_iram(uint32_t base, void *data, uint32_t size);
    int prog_eflash(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size);

    int do_raw_isp(bin_object &bin_obj, uint32_t addr);
    int do_eflash_isp(bin_object &bin_obj);

    //uint32_t serial_std_speed(uint32_t baudrate);

    //uint32_t u8le_to_u32(uint8_t *u8_data);

    //void print_raw(vtiicisp_packet &pkt);
};

#endif  // __VTISP_I2C_INC__

