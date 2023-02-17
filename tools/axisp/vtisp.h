// Intel Hexadecimal Object File Reader
//
// [2014-??-??]
//
//

#ifndef __VTISP_INC__
#define __VTISP_INC__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

#include "isp.h"
#include "bin_object.h"

//#define VTISP_WORD_READ_DELAY(w)          0
#define VTISP_WORD_READ_DELAY(w)          (100 + 3 * (w))

//#define VTISP_WORD_WRITE_DELAY(w)         0
#define VTISP_WORD_WRITE_DELAY(w)         (100 + 15 * (w))

#define VTISP_PAGE_PRGROAM_DELAY(w)       2200 //(1000 + 15 * (w))

#define VTISP_EFC_ERASE_UNLOCK_DELAY      (500)
#define VTISP_EFC_ERASE_LOCK_DELAY        (2000)

#define VTISP_EFC_WRONLY_UNLOCK_DELAY     (500)
#define VTISP_EFC_WRONLY_LOCK_DELAY       (3000)

#define VTISP_EFC_PROG_UNLOCK_DELAY       (5000)
#define VTISP_EFC_PROG_LOCK_DELAY         (7000)

class vtisp_packet : public isp_packet
{
public:

    enum CONSTANTS {
        VTISP_RAW_DATA_SIZE     = 4096,
    };

    enum VTISP_CMD {
        VTISP_CMD_PING          = 0x00,
        VTISP_CMD_ACK           = 0xff,

        VTISP_CMD_BREAK         = 0xcc,

        VTISP_CMD_WORD_READ     = 0x01,
        VTISP_CMD_WORD_WRITE    = 0x02,
        VTISP_CMD_READ_CHECKSUM = 0x03,
        VTISP_CMD_WRITE_DMA     = 0x04,
        VTISP_CMD_PAGE_PROGRAM  = 0x05,
        VTISP_CMD_VTEFC_INIT    = 0x06,
    };

    //enum VTISP_CMD_FLAGS {
    //    VTISP_CMDF_WORD_DATA    = 0x00,
    //    VTISP_CMDF_BYTE_DATA    = 0x01,
    //};

    enum VTISP_ACK_STATUS {
        // host status
        VTISP_ACKH_MASK         = 0xf0,
        VTISP_ACKH_OK           = 0x00,
        VTISP_ACKH_CHECKSUM     = 0x10,  // checksum mismatch
        VTISP_ACKH_TIMEOUT      = 0x20,
        VTISP_ACKH_UNKNOWN      = 0xe0,  // unknown command (not VTISP_CMD_ACK)
        // remote status
        VTISP_ACKT_MASK         = 0x0f,
        VTISP_ACKT_OK           = 0x00,
        VTISP_ACKT_CHECKSUM     = 0x01,  // checksum mismatch
        VTISP_ACKT_UNKNOWN      = 0x0e,  // unknown command
    };

    int _fd;

    uint32_t _size_out;
    uint32_t _size_in;

    uint8_t _data_out[VTISP_RAW_DATA_SIZE];
    uint8_t _data_in[VTISP_RAW_DATA_SIZE];

    vtisp_packet() : _fd(-1), _size_out(0), _size_in(0) {}
    vtisp_packet(int fd) : _fd(fd), _size_out(0), _size_in(0) {}
    virtual ~vtisp_packet() {}

    virtual void do_cmd_ping();
    virtual void do_cmd_break();

    virtual void do_cmd_word_read(uint32_t addr, uint32_t size);
    virtual void do_cmd_read_checksum(uint32_t addr, uint32_t size);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t size);
    virtual void do_cmd_page_program(uint32_t addr, uint32_t *data, uint32_t size, bool DMAFlag);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t size, bool DMAFlag);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t data);
    virtual void do_cmd_word_write(uint32_t addr, uint32_t data, bool DMAFlag);
    virtual void do_cmd_setup(uint32_t index, uint32_t value);
    virtual void do_vtefc_init(uint32_t type);

    uint8_t do_checksum(uint8_t *data, uint32_t length);

    virtual int send_out(bool wait_ack = true, uint32_t data_in_delay = 0);

    int get_byte(uint8_t *data);
    int get_ack();
    int get_raw(uint32_t delay = 750000);
};

class vtisp : public isp
{
public:

    enum CONSTANTS {
        VTISP_IRAM_BURST_SIZE   = 256,
    };

protected:

    char _sz_dev[CONFIG_MAX_PATH];
    int  _fd_dev;

    bool _quiet;

public:

    vtisp();
    virtual ~vtisp();

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

    int open_dev(const char *path, bool do_setup);

    int do_remap_get(uint32_t &remap);
    int vtefc_init(uint32_t type);
    int prog_iram(uint32_t base, void *data, uint32_t size);
    int prog_eflash(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size);
    int prog_eflash_fast(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size);
    int prog_eflash_raw(bin_object &bin_obj);
    int prog_eflash_sum(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size);

    int do_raw_isp(bin_object &bin_obj, uint32_t addr);
    int do_eflash_isp(bin_object &bin_obj);
    int do_eflash_fast_isp(bin_object &bin_obj);
    int do_eflash_sum_isp(bin_object &bin_obj);

    uint32_t serial_std_speed(uint32_t baudrate);

    uint32_t u8le_to_u32(uint8_t *u8_data);

    void print_raw(vtisp_packet &pkt);
};

#endif  // __VTISP_INC__

