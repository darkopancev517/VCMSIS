// Intel Hexadecimal Object File Reader
//
// [2014-??-??]
//
//

#ifndef __ISP_INC__
#define __ISP_INC__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "xmodem.h"

#include "isp.h"

#if ((ISP_BIST_BURST_SIZE) > (XMODEM_MAX_DATA_SIZE))
#error "ISP_BIST_BURST_SIZE should be less than or equal to XMODEM_MAX_DATA_SIZE !"
#endif

class ftisp : public isp
{
protected:

    char _sz_dev[CONFIG_MAX_PATH];
    int  _fd_dev;

    bool _quiet;

public:

    ftisp();
    virtual ~ftisp();

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

    int do_reboot_internal(uint32_t remap);

    uint32_t std_speed(uint32_t baudrate);
    int get_ack(xmodem16 &x, uint32_t sleep_us, bool quiet = false);
    int get_ack_data(xmodem16 &x, bool reg = false, bool quiet = false);
};

#endif  // __ISP_INC__

