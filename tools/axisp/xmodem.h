// Intel Hexadecimal Object File Reader
//
// [2014-??-??]
//
//

#ifndef __XMODEM_INC__
#define __XMODEM_INC__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

// ---------------------------------------------------------------------------

#define XMODEM_MAX_DATA_SIZE            256

#define XMODEM_PKT_OUT_SIZE(data_size)  (4 + data_size + 2)     // header + data_size + crc

// ---------------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class xmodem16
{
public:

    enum HEADER {
        XH_SOH              = 0x01,             // start of header (isp: command)
        XH_STX              = 0x02,             // start of header (isp: command and data)
        XH_EOT              = 0x04,             // end of transmission
        XH_ACK              = 0x06,             // positive acknowledge
        XH_DLE              = 0x10,             // data link escape (isp: not used)
        XH_NAK              = 0x15,             // negative acknowledge
        XH_ETB              = 0x17,             // ? (isp: nop, keep-alive)
        XH_SYN              = 0x16,             // synchronous idle (isp: not used)
        XH_CAN              = 0x18,             // cancel transmission
        XH_CTRLZ            = 0x1a,
    };

    enum ISP_CMD {
        ISPCMD_SCSI         = 0xf1,
    };

    enum ISP_SUBCMD {
        ISPSUBCMD_REG_W     = 0x67,
        ISPSUBCMD_REG_R     = 0x66,
        ISPSUBCMD_EFLASH_W  = 0x80,
        ISPSUBCMD_EFLASH_R  = 0x81,
        ISPSUBCMD_CODE_W    = 0xa0,
        ISPSUBCMD_CODE_R    = 0xa1,
    };

    enum ISP_DIR {
        ISP_DIR_OUT         = 0x00,             // down-stream (host -> device)
        ISP_DIR_IN          = 0x80,             // up-stream (device -> host)
    };

    struct isp_cmd
    {
        uint8_t             cmd;                // enum ISP_CMD (ISP_U320_SCSI_CMD_CODE)
        uint8_t             sub_cmd;            // enum ISP_SUBCMD
        uint8_t             reg_width;          // memory read/write width (1~4 bytes)
        uint8_t             reserved;
        uint32_t            address;            // data address
        uint32_t            size;               // data size

        //isp_cmd() : cmd(0), sub_cmd(0), reg_width(0), reserved(0), address(0), size(0) {}
    };

    struct packet
    {
        uint8_t             header;             // xmodem size
        uint8_t             dir;                // direction (enum ISP_DIR) (not used)
        uint16_t            size;               // data size (not including crc)

        // data and 2-byte crc field
        union {
            struct isp_cmd  cmd;                // isp-command
            struct {
                uint8_t     ovl[sizeof(struct isp_cmd)];    // overlaps isp_cmd cmd
                uint8_t     out[XMODEM_MAX_DATA_SIZE + 2];  // data-out + crc
            } data;
        };

        //packet() : header(XH_SOH), dir(ISP_DIR_OUT), size(0) {}

    } pkt_out;

    uint32_t pkt_out_size;

    uint8_t ack;
    uint8_t pkt_in[XMODEM_MAX_DATA_SIZE];      // buffer for ack/nak or any other returned data
    uint32_t pkt_in_size;

public:

    xmodem16() {}
    ~xmodem16() {}

    xmodem16(enum HEADER h, enum ISP_DIR dir = ISP_DIR_OUT, uint16_t size = 0) {
        pkt_out.header = h;
        pkt_out.dir = dir;
        pkt_out.size = size;

        ::memset(&pkt_out.cmd, 0, sizeof(struct isp_cmd));
    }

    //void soh();
    //void can();
    //void eot();

    void do_crc();

};

#pragma pack(pop)

#endif  // __XMODEM_INC__

