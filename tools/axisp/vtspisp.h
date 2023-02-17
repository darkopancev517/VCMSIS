// Intel Hexadecimal Object File Reader
//
// [2014-??-??]
//
//

#ifndef __VTISP_SPI_INC__
#define __VTISP_SPI_INC__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

#include "isp.h"
#include "bin_object.h"

//#define VTSPISP_WORD_READ_DELAY(w)          0
#define VTSPISP_WORD_READ_DELAY(w)          (100 + 3 * (w))

//#define VTSPISP_WORD_WRITE_DELAY(w)         0
#define VTSPISP_WORD_WRITE_DELAY(w)         (100 + 15 * (w))

#define VTSPISP_PAGE_PRGROAM_DELAY(w)       (2200)  //(0 + 15 * (w))

#define VTSPISP_EFC_ERASE_UNLOCK_DELAY      (500)
#define VTSPISP_EFC_ERASE_LOCK_DELAY        (2000)

#define VTSPISP_EFC_WRONLY_UNLOCK_DELAY     (500)
#define VTSPISP_EFC_WRONLY_LOCK_DELAY       (3000)

#define VTSPISP_EFC_PROG_UNLOCK_DELAY       (2000)
#define VTSPISP_EFC_PROG_LOCK_DELAY         (7000)

class vtspisp_packet : public isp_packet
{
public:

    enum CONSTANTS {
        VTSPISP_RAW_DATA_SIZE           = 2048,
        VTSPISP_SPI_PAGE_SIZE           = 512,
        //VTSPISP_SPI_ACK_SIZE            = 4,
        VTSPISP_SPI_PING_ACK_DELAY      = 0,
        //VTSPISP_SPI_DATA_IN_DELAY       = 1000,
    };

    enum SETUP_INDEX {
        VTSPISP_SETID_DATA_OUT_TIMEOUT  = 0,
    };

    enum VTSPISP_CMD {
        // hint: 0x00 && 0xff is not suitable for command encoding since the default
        // state on the data bus is either 0x00 or 0xff and could be a garbage data
        // if the master and slave state-switch is out of sync.
        VTSPISP_CMD_PING                = 0x0f,
        VTSPISP_CMD_ACK                 = 0xf0,

        VTSPISP_CMD_WORD_READ           = 0x11,
        VTSPISP_CMD_PAGE_READ           = 0x12,
        VTSPISP_CMD_WORDS_READ          = 0x13,
        VTSPISP_CMD_PAGE_CHECKSUM       = 0x14,
        VTSPISP_CMD_READ_CHECKSUM       = 0x15,
        VTSPISP_CMD_WRITE_DMA           = 0x16,
        VTSPISP_CMD_PAGE_PROGRAM        = 0x17,
        VTSPISP_CMD_VTEFC_INIT          = 0x18,

        VTSPISP_CMD_WORD_WRITE          = 0x21,
        VTSPISP_CMD_PAGE_WRITE          = 0x22,
        VTSPISP_CMD_WORDS_WRITE         = 0x23,

        VTSPISP_CMD_SETUP               = 0x88,
    };

    struct mpsse_context *_mpsse_spi;

    uint32_t _size_out;
    uint32_t _size_in;
    //uint32_t _delay;

    uint8_t _data_out[VTSPISP_RAW_DATA_SIZE];
    uint8_t _data_in[VTSPISP_RAW_DATA_SIZE];

    vtspisp_packet() : _mpsse_spi(NULL), _size_out(0), _size_in(0) {}
    vtspisp_packet(struct mpsse_context *mpsse) : _mpsse_spi(mpsse), _size_out(0), _size_in(0) {}
    virtual ~vtspisp_packet() {}

    virtual void do_cmd_ping();
    virtual void do_cmd_break();

    virtual void do_cmd_word_read(uint32_t addr, uint32_t nr_words);
    virtual void do_cmd_read_checksum(uint32_t addr, uint32_t size);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t nr_words);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t nr_words, bool DMAFlag);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t data);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t data, bool DMAFlag);
    virtual void do_vtefc_init(uint32_t type);
    virtual void do_cmd_page_program(uint32_t addr, uint32_t *data, uint32_t size, bool DMAFlag);

    virtual void do_cmd_setup(uint32_t index, uint32_t value);

    //uint8_t do_checksum(uint8_t *data, uint32_t length);

    virtual int send_out(bool wait_ack = true, uint32_t data_in_delay = 0);

    //int get_raw(uint32_t delay = 750000);

private:

    //int spi_get_ack();
    //int spi_out(uint8_t *data_out, uint32_t bytes_out);
    //int spi_in(uint8_t *data_in, uint32_t bytes_in);
};

class vtspisp : public isp
{
protected:

    struct ftdi_context *_ftdi_ctxt;
    struct mpsse_context *_mpsse_spi;

    //bool _quiet;

public:

    vtspisp();
    virtual ~vtspisp();

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

    int spi_dev_list();

    int spi_open();
    int spi_close();

    int do_remap_get(uint32_t &remap);
    int vtefc_init(uint32_t type);
    int prog_iram(uint32_t base, void *data, uint32_t size);
    int prog_eflash(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size);
    int prog_eflash_raw(bin_object &bin_obj);
    int prog_eflash_sum(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size);
    int prog_eflash_fast(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size);

    int do_raw_isp(bin_object &bin_obj, uint32_t addr);
    int do_eflash_isp(bin_object &bin_obj);
    int do_eflash_fast_isp(bin_object &bin_obj);
    int do_eflash_sum_isp(bin_object &bin_obj);

    //uint32_t serial_std_speed(uint32_t baudrate);

    //uint32_t u8le_to_u32(uint8_t *u8_data);

    //void print_raw(vtspisp_packet &pkt);
};

#endif  // __VTISP_SPI_INC__
