
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "xmodem.h"
#include "ftisp.h"
#include "bin_object.h"

ftisp::ftisp() : _fd_dev(-1), _quiet(true)
{
    _sz_dev[0] = 0;
}

ftisp::~ftisp()
{
}

void ftisp::quiet(bool q)
{
    _quiet = q;
}

uint32_t ftisp::std_speed(uint32_t baudrate)
{
    if (baudrate >= ((115200 + 57600) / 2)) {
        return (uint32_t)B115200;
    } else if (baudrate >= ((57600 + 38400) / 2)) {
        return (uint32_t)B57600;
    } else if (baudrate >= ((38400 + 19200) / 2)) {
        return (uint32_t)B38400;
    } else if (baudrate >= ((19200 + 9600) / 2)) {
        return (uint32_t)B19200;
    } else if (baudrate >= ((9600 + 4800) / 2)) {
        return (uint32_t)B9600;
    } else if (baudrate >= ((4800 + 2400) / 2)) {
        return (uint32_t)B4800;
    } else if (baudrate >= ((2400 + 1800) / 2)) {
        return (uint32_t)B2400;
    } else if (baudrate >= ((1800 + 1200) / 2)) {
        return (uint32_t)B1800;
    }

    return (uint32_t)B1200;
}

int ftisp::open_dev(const char *path, bool do_setup)
{
    ::printf("open serial device %s ... ", path);

    _fd_dev = ::open(path, O_RDWR | O_NOCTTY | O_NDELAY);
    if (_fd_dev < 0) {
        ::printf("failed\n");
        return -1;
    }

    ::printf("done\n");

    if (do_setup) {

        ::fcntl(_fd_dev, F_SETFL, 0);

        struct termios tc_spec;

        ::memset(&tc_spec, 0, sizeof(struct termios));
        //::tcgetattr(_fd_dev, &tc_spec);

        tc_spec.c_cflag = CLOCAL | CREAD | CS8;

        tc_spec.c_iflag = 0;
        tc_spec.c_oflag = 0;
        //tc_spec.c_lflag = ICANON;

        //tc_spec.c_cc[VMIN] = 1;
        speed_t baudrate = std_speed(axisp_ctxt.data_rate);
        ::cfsetispeed(&tc_spec, baudrate);
        ::cfsetospeed(&tc_spec, baudrate);

        ::tcflush(_fd_dev, TCIOFLUSH);

        ::tcsetattr(_fd_dev, TCSANOW, &tc_spec);
    }

    return 0;
}

int ftisp::do_dev_list()
{
    char path[255];

    for (int i = 0; i < 10; ++i) {
        ::sprintf(path, "/dev/ttyUSB%d", i);
        open_dev(path, true);
        close();
    }

    return 0;
}

int ftisp::open()
{
    return open_dev(axisp_ctxt.fname_dev, true);
}

void ftisp::close()
{
    if (_fd_dev >= 0)
        ::close(_fd_dev);
    _fd_dev = -1;
}

int ftisp::do_word_read()
{
    if (axisp_ctxt.isp_nr_args < 1) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return -1;
    }

    const char *sz_addr = axisp_ctxt.isp_args[1];
    //const char *sz_counts = axisp_ctxt.isp_args[2];

    if (::axisp_context::validate_hex(sz_addr)) {
        ::printf("\n[err] invalid data-read address!\n\n");
        return -1;
    }

    //if (::axisp_context::validate_hex(sz_counts)) {
    //    ::printf("\n[err] invalid data-read counts!\n\n");
    //    return -1;
    //}

    uint32_t data_addr = ::strtoul(sz_addr, 0, 16);
    //uint32_t data_counts = ::strtoul(sz_counts, 0, 16);

    xmodem16 x(xmodem16::XH_SOH, xmodem16::ISP_DIR_IN, (uint16_t)sizeof(struct xmodem16::isp_cmd));

    x.pkt_out.cmd.cmd       = xmodem16::ISPCMD_SCSI;
    x.pkt_out.cmd.sub_cmd   = xmodem16::ISPSUBCMD_REG_R;
    x.pkt_out.cmd.reg_width = 4;
    x.pkt_out.cmd.address   = data_addr;
    x.pkt_out.cmd.size      = 0;

    x.do_crc();

    // ----------------------------

    if (!_quiet)
        ::printf("send out register-read request ... ");

    int r = ::write(_fd_dev, &x.pkt_out, x.pkt_out_size);
    if (r != (int)x.pkt_out_size) {
        if (!_quiet)
            ::printf("failed (%d)\n", r);
        return -1;
    }

    if (!_quiet)
        ::printf("done\n");

    // ----------------------------

    r = get_ack(x, ISP_ACK_WAIT_SLEEP_US);
    if (r < 0)
        return r;

    // ----------------------------
    if (x.ack == xmodem16::XH_ACK) {
        r = get_ack_data(x, true);
    }

    return r;
}

int ftisp::do_word_write()
{
    if (axisp_ctxt.isp_nr_args < 2) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return -1;
    }

    const char *sz_addr = axisp_ctxt.isp_args[1];
    const char *sz_data = axisp_ctxt.isp_args[2];
    //const char *sz_counts = axisp_ctxt.isp_args[3];

    if (::axisp_context::validate_hex(sz_addr)) {
        ::printf("\n[err] invalid data-write address!\n\n");
        return -1;
    }

    if (::axisp_context::validate_hex(sz_data)) {
        ::printf("\n[err] invalid data-write data!\n\n");
        return -1;
    }

    /*if (axisp_ctxt.isp_nr_args >= 3) {
        if (::axisp_context::validate_hex(sz_counts)) {
            ::printf("\n[err] invalid data-write counts!\n\n");
            return -1;
        }
    } else {
        sz_counts = "1";
    }*/

    uint32_t w_addr = ::strtoul(sz_addr, 0, 16);
    uint32_t w_data = ::strtoul(sz_data, 0, 16);
    //uint32_t w_counts = ::strtoul(sz_counts, 0, 16);

    xmodem16 x(xmodem16::XH_SOH, xmodem16::ISP_DIR_OUT, (uint16_t)sizeof(struct xmodem16::isp_cmd));

    x.pkt_out.cmd.cmd       = xmodem16::ISPCMD_SCSI;
    x.pkt_out.cmd.sub_cmd   = xmodem16::ISPSUBCMD_REG_W;
    x.pkt_out.cmd.reg_width = 4;
    x.pkt_out.cmd.address   = w_addr;
    x.pkt_out.cmd.size      = w_data;

    x.do_crc();

    // ----------------------------

    if (!_quiet)
        ::printf("send out register-write request ... ");

    int r = ::write(_fd_dev, &x.pkt_out, x.pkt_out_size);
    if (r != (int)x.pkt_out_size) {
        if (!_quiet)
            ::printf("failed (%d)\n", r);
        return -1;
    }

    if (!_quiet)
        ::printf("done\n");

    // ----------------------------

    r = get_ack(x, ISP_ACK_WAIT_SLEEP_US);
    //if (r < 0)
    //    return r;

    // ----------------------------

    //if (x.ack == xmodem16::XH_ACK) {
    //    r = get_ack_data(x);
    //}

    return r;
}

int ftisp::do_bist(uint32_t bist_base, uint32_t bist_size, uint32_t pattern)
{
#if 0
    xmodem16 xw(xmodem16::XH_SOH, xmodem16::ISP_DIR_OUT, (uint16_t)(sizeof(struct xmodem16::isp_cmd) + ISP_BIST_BURST_SIZE));

    xw.pkt_out.cmd.cmd       = xmodem16::ISPCMD_SCSI;
    xw.pkt_out.cmd.sub_cmd   = xmodem16::ISPSUBCMD_CODE_W;
    xw.pkt_out.cmd.reg_width = 4;
    xw.pkt_out.cmd.address   = bist_base;
    xw.pkt_out.cmd.size      = ISP_BIST_BURST_SIZE;

    // prepare data pattern
    for (uint32_t w = 0; w < (ISP_BIST_BURST_SIZE / 4); ++w)
        ((uint32_t *)xw.pkt_out.data.out)[w] = pattern;

    bist_size = (bist_size + 3) & ~0x03;
    uint32_t nr_writes = (bist_size + ISP_BIST_BURST_SIZE - 1) / ISP_BIST_BURST_SIZE;

    if ((nr_writes * ISP_BIST_BURST_SIZE) > ISP_IRAM0_SIZE)
        --nr_writes;

    // pattern programming ...
    if (!_quiet)
        ::printf("\n\npattern programming ...\n\n");  ::fflush(stdout);

    for (uint32_t i = 0; i < nr_writes; ++i, xw.pkt_out.cmd.address += ISP_BIST_BURST_SIZE) {

        xw.do_crc();

        if (!_quiet) {
            ::printf("\r[0x%08x] w", xw.pkt_out.cmd.address);  ::fflush(stdout);
        }

        int r = ::write(_fd_dev, &xw.pkt_out, xw.pkt_out_size);

        if (r != (int)xw.pkt_out_size) {
            if (!_quiet) {
                ::printf("-failed (%d)\n", r);  ::fflush(stdout);
            }
            return -1;
            //continue;
        }

        r = get_ack(xw, ISP_ACK_WAIT_SLEEP_US * 5, true);

        if (!_quiet) {

            ::printf(" a");  ::fflush(stdout);

            if (r < 0) {
                ::printf("-timeout\n");  ::fflush(stdout);
                return -1;
            } else {
                if (xw.ack == xmodem16::XH_ACK) {
                    ::printf("-acked");  ::fflush(stdout);
                } else if (xw.ack == xmodem16::XH_NAK) {
                    ::printf("-naked\n");  ::fflush(stdout);
                    return -1;
                } else {
                    ::printf("-%02x   \n", xw.ack);  ::fflush(stdout);
                    return -1;
                }
            }
        }
    }

    // verification
    if (!_quiet)
        ::printf("\n\nread-back and verify written pattern ...\n\n");  ::fflush(stdout);

    xmodem16 xr(xmodem16::XH_SOH, xmodem16::ISP_DIR_IN, (uint16_t)(sizeof(struct xmodem16::isp_cmd) + ISP_BIST_BURST_SIZE));

    xr.pkt_out.cmd.cmd       = xmodem16::ISPCMD_SCSI;
    xr.pkt_out.cmd.sub_cmd   = xmodem16::ISPSUBCMD_CODE_R;
    xr.pkt_out.cmd.reg_width = 4;
    xr.pkt_out.cmd.address   = bist_base;
    xr.pkt_out.cmd.size      = ISP_BIST_BURST_SIZE;

    for (uint32_t i = 0; i < nr_writes; ++i, xr.pkt_out.cmd.address += ISP_BIST_BURST_SIZE) {

        xr.do_crc();

        if (!_quiet) {
            ::printf("\r[0x%08x] r", xr.pkt_out.cmd.address);  ::fflush(stdout);
        }

        int r = ::write(_fd_dev, &xr.pkt_out, xr.pkt_out_size);

        if (r != (int)xr.pkt_out_size) {
            if (!_quiet) {
                ::printf("-failed (%d)\n", r);  ::fflush(stdout);
            }
            return -1;
            //continue;
        }

        r = get_ack(xr, ISP_ACK_WAIT_SLEEP_US * 5, true);

        if (!_quiet) {

            ::printf(" a");  ::fflush(stdout);

            if (r < 0) {
                ::printf("-timeout\n");  ::fflush(stdout);
                return -1;
            } else {
                if (xr.ack == xmodem16::XH_ACK) {
                    ::printf("-acked");  ::fflush(stdout);
                } else if (xr.ack == xmodem16::XH_NAK) {
                    ::printf("-naked\n");  ::fflush(stdout);
                    return -1;
                } else {
                    ::printf("-%02x   \n", xr.ack);  ::fflush(stdout);
                    return -1;
                }
            }
        }

        r = get_ack_data(xr, false, true);

        if (r != ISP_BIST_BURST_SIZE) {
            if (!_quiet)
                ::printf(" v");  ::fflush(stdout);
            return -1;
        }

        if (!_quiet)
            ::printf(" v");  ::fflush(stdout);

        for (uint32_t w = 0; w < (ISP_BIST_BURST_SIZE / 4); ++w) {

            if (((uint32_t *)xr.pkt_in)[w] != pattern) {
                if (!_quiet)
                    ::printf("-mismatch @0x%08x ptn)0x%08x r)0x%08x\n", xr.pkt_out.cmd.address + w * 4, pattern, ((uint32_t *)xr.pkt_in)[w]);  ::fflush(stdout);
                return -1;
            }
        }

        ::printf("-ok");  ::fflush(stdout);
    }

    ::printf("\n");  ::fflush(stdout);
#endif
    return 0;
}

int ftisp::do_isp()
{
    if (axisp_ctxt.isp_nr_args < 1) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return -1;
    }

    const char *sz_image = axisp_ctxt.isp_args[1];

    if (sz_image[0] == 0) {
        ::printf("\n[err] invlaid image file name!\n\n");
        return -1;
    }

    if (::access(sz_image, R_OK) != 0) {
        ::printf("\n[err] failed to access image file!\n\n");
        return -1;
    }

    xmodem16 xw(xmodem16::XH_SOH, xmodem16::ISP_DIR_OUT, (uint16_t)(sizeof(struct xmodem16::isp_cmd) + ISP_BIST_BURST_SIZE));

    xw.pkt_out.cmd.cmd       = xmodem16::ISPCMD_SCSI;
    xw.pkt_out.cmd.sub_cmd   = xmodem16::ISPSUBCMD_CODE_W;
    xw.pkt_out.cmd.reg_width = 4;
    xw.pkt_out.cmd.address   = ISP_IRAM0_BASE;
    xw.pkt_out.cmd.size      = ISP_BIST_BURST_SIZE;

    // prepare data
    bin_object bin_obj;

    int r = bin_obj.open(sz_image);
    if (r < 0) {
        if (!_quiet)
            ::printf("\n\nfailed to open binary image !!\n\n");
        return -1;
    }

    uint32_t nr_writes = (bin_obj.size() + ISP_BIST_BURST_SIZE - 1) / ISP_BIST_BURST_SIZE;

    if ((nr_writes * ISP_BIST_BURST_SIZE) > ISP_IRAM0_SIZE) {
        if (!_quiet)
            ::printf("\n\nbinary image size overflows target memory size (%d > %d) !!\n\n", bin_obj.size(), ISP_IRAM0_SIZE);
        bin_obj.close();
        return -1;
    }

    // programming ...
    if (!_quiet)
        ::printf("\n\nimage programming (0x%08x - 0x%08x) ...\n\n", ISP_IRAM0_BASE, ISP_IRAM0_BASE + bin_obj.size());  ::fflush(stdout);

    for (uint32_t i = 0; i < nr_writes; ++i, xw.pkt_out.cmd.address += ISP_BIST_BURST_SIZE) {

        if (bin_obj.read(xw.pkt_out.data.out, ISP_BIST_BURST_SIZE) < 0) {
            if (!_quiet)
                ::printf("\n\nfailed on reading binary image file !!\n\n");
            bin_obj.close();
            return -1;
        }

        xw.do_crc();

        uint32_t retry = ISP_FALSE_RETRY_COUNT;

        while (retry--) {

            if (!_quiet) {
                ::printf("\r[0x%08x] w", xw.pkt_out.cmd.address);  ::fflush(stdout);
            }

            r = ::write(_fd_dev, &xw.pkt_out, xw.pkt_out_size);

            if (r != (int)xw.pkt_out_size) {
                if (!_quiet) {
                    ::printf("-failed (%d)\n", r);  ::fflush(stdout);
                }
                bin_obj.close();
                return -1;
                //continue;
            }

            r = get_ack(xw, ISP_ACK_WAIT_SLEEP_US * 5, true);

            if (!_quiet) {

                ::printf(" a");  ::fflush(stdout);

                if (r < 0) {
                    ::printf("-timeout\n");  ::fflush(stdout);
                    //bin_obj.close();
                    //return -1;
                } else {
                    if (xw.ack == xmodem16::XH_ACK) {
                        ::printf("-acked");  ::fflush(stdout);
                        retry = 0;
                    } else if (xw.ack == xmodem16::XH_NAK) {
                        ::printf("-naked\n");  ::fflush(stdout);
                        bin_obj.close();
                        return -1;
                    } else {
                        ::printf("-%02x   \n", xw.ack);  ::fflush(stdout);
                        bin_obj.close();
                        return -1;
                    }
                }
            }
        }
    }

    // verification
    if (!_quiet)
        ::printf("\n\nread-back and verify written pattern ...\n\n");  ::fflush(stdout);

    bin_obj.read(NULL, 0);

    xmodem16 xr(xmodem16::XH_SOH, xmodem16::ISP_DIR_IN, (uint16_t)(sizeof(struct xmodem16::isp_cmd) + ISP_BIST_BURST_SIZE));

    xr.pkt_out.cmd.cmd       = xmodem16::ISPCMD_SCSI;
    xr.pkt_out.cmd.sub_cmd   = xmodem16::ISPSUBCMD_CODE_R;
    xr.pkt_out.cmd.reg_width = 4;
    xr.pkt_out.cmd.address   = ISP_IRAM0_BASE;
    xr.pkt_out.cmd.size      = ISP_BIST_BURST_SIZE;

    for (uint32_t i = 0; i < nr_writes; ++i, xr.pkt_out.cmd.address += ISP_BIST_BURST_SIZE) {

        if (bin_obj.read(xr.pkt_out.data.out, ISP_BIST_BURST_SIZE) < 0) {
            if (!_quiet)
                ::printf("\n\nfailed on reading binary image file !!\n\n");
            bin_obj.close();
            return -1;
        }

        xr.do_crc();

        if (!_quiet) {
            ::printf("\r[0x%08x] r", xr.pkt_out.cmd.address);  ::fflush(stdout);
        }

        r = ::write(_fd_dev, &xr.pkt_out, xr.pkt_out_size);

        if (r != (int)xr.pkt_out_size) {
            if (!_quiet) {
                ::printf("-failed (%d)\n", r);  ::fflush(stdout);
            }
            bin_obj.close();
            return -1;
            //continue;
        }

        r = get_ack(xr, ISP_ACK_WAIT_SLEEP_US * 5, true);

        if (!_quiet) {

            ::printf(" a");  ::fflush(stdout);

            if (r < 0) {
                ::printf("-timeout     \n");  ::fflush(stdout);
                bin_obj.close();
                return -1;
            } else {
                if (xr.ack == xmodem16::XH_ACK) {
                    ::printf("-acked");  ::fflush(stdout);
                } else if (xr.ack == xmodem16::XH_NAK) {
                    ::printf("-naked     \n");  ::fflush(stdout);
                    bin_obj.close();
                    return -1;
                } else {
                    ::printf("-%02x        \n", xr.ack);  ::fflush(stdout);
                    bin_obj.close();
                    return -1;
                }
            }
        }

        r = get_ack_data(xr, false, true);

        if (r != ISP_BIST_BURST_SIZE) {
            if (!_quiet)
                ::printf(" v");  ::fflush(stdout);
            return -1;
        }

        if (!_quiet)
            ::printf(" v");  ::fflush(stdout);

        for (uint32_t w = 0; w < (ISP_BIST_BURST_SIZE / 4); ++w) {
            if (((uint32_t *)xr.pkt_in)[w] != ((uint32_t *)xr.pkt_out.data.out)[w]) {
                if (!_quiet)
                    ::printf(" mismatch @0x%08x image)0x%08x r)0x%08x\n", xr.pkt_out.cmd.address + w * 4, ((uint32_t *)xr.pkt_out.data.out)[w], ((uint32_t *)xr.pkt_in)[w]);  ::fflush(stdout);
                bin_obj.close();
                return -1;
            }
        }

        ::printf("-ok");  ::fflush(stdout);
    }

    bin_obj.close();

    if (axisp_ctxt.reboot) {
        do_reboot_internal(1);
    }

    if (!_quiet)
        ::printf("\n");

    return 0;
}

int ftisp::do_fastisp()
{
    return 0;
}

int ftisp::do_sumisp()
{
    return 0;
}

int ftisp::do_reboot_internal(uint32_t remap)
{
    xmodem16 x(xmodem16::XH_SOH, xmodem16::ISP_DIR_OUT, (uint16_t)sizeof(struct xmodem16::isp_cmd));

    if (remap == 9) {

        x.pkt_out.cmd.cmd       = xmodem16::ISPCMD_SCSI;
        x.pkt_out.cmd.sub_cmd   = xmodem16::ISPSUBCMD_REG_W;
        x.pkt_out.cmd.reg_width = 4;
        x.pkt_out.cmd.address   = 0x20000000;  // iRAM
        x.pkt_out.cmd.size      = 0xeafffffe;  // b 0

        x.do_crc();

        if (!_quiet)
            ::printf("\n\nsending iRAM bootstrap self-loop code ... ");  ::fflush(stdout);

        int r = ::write(_fd_dev, &x.pkt_out, x.pkt_out_size);
        if (r != (int)x.pkt_out_size) {
            if (!_quiet)
                ::printf("failed (%d)\n", r);
            return -1;
        }

        if (!_quiet)
            ::printf("done");
    }

    x.pkt_out.cmd.cmd       = xmodem16::ISPCMD_SCSI;
    x.pkt_out.cmd.sub_cmd   = xmodem16::ISPSUBCMD_REG_W;
    x.pkt_out.cmd.reg_width = 4;
    x.pkt_out.cmd.address   = 0x54000020;
    x.pkt_out.cmd.size      = 0x00020080 | (remap << 24);

    x.do_crc();

    if (!_quiet)
        ::printf("\n\nsending remap and reboot command ... ");  ::fflush(stdout);

    int r = ::write(_fd_dev, &x.pkt_out, x.pkt_out_size);
    if (r != (int)x.pkt_out_size) {
        if (!_quiet)
            ::printf("failed (%d)\n", r);
        return -1;
    }

    if (!_quiet)
        ::printf("done");
#if 0
    // ack-reply is not going to happen after the wrting the reboot register
    r = get_ack(x, ISP_ACK_WAIT_SLEEP_US, true);

    if (!_quiet) {

        ::printf(" a");  ::fflush(stdout);

        if (r < 0) {
            ::printf("-timeout\n");  ::fflush(stdout);
            return -1;
        } else {
            if (x.ack == xmodem16::XH_ACK) {
                ::printf("-acked\n");  ::fflush(stdout);
            } else if (x.ack == xmodem16::XH_NAK) {
                ::printf("-naked\n");  ::fflush(stdout);
                return -1;
            } else {
                ::printf("-%02x   \n", x.ack);  ::fflush(stdout);
                return -1;
            }
        }
    }
#endif

    if (!_quiet) {
        if (remap != 9) {
            ::printf("\nwaiting for bootup message ...");  ::fflush(stdout);

            ::usleep(100000);

            r = get_ack_data(x, false, true);

            if (r <= 0) {
                ::printf(" none!! wait for 3 more seconds ...");  ::fflush(stdout);
                ::usleep(3000000);

                r = get_ack_data(x, false, true);
            }

            if (r <= 0) {
                ::printf("\n\nno bootup messages !!");  ::fflush(stdout);
            } else {
                ::printf("\n\nbootup message ... (%d chars)\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", r);
                ::printf("%s\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<", (const char *)x.pkt_in);
                ::fflush(stdout);
            }
        } else {
            ::printf("\n");  ::fflush(stdout);
        }
    }

    return 0;
}

int ftisp::do_reboot()
{
    if (axisp_ctxt.isp_nr_args < 1) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return -1;
    }

    const char *sz_remap = axisp_ctxt.isp_args[1];

    if (::axisp_context::validate_dec(sz_remap)) {
        ::printf("\n[err] invalid remap value!\n\n");
        return -1;
    }

    uint32_t remap = ::strtoul(sz_remap, 0, 10);

    return do_reboot_internal(remap);
}

int ftisp::do_cli_cmd()
{
    return 0;
}

int ftisp::do_ping()
{
    return 0;
}

int ftisp::do_break()
{
    return 0;
}

int ftisp::do_setup()
{
    return 0;
}

#if 0
int ftisp::do_can()
{
    xmodem16 x(xmodem16::XH_CAN, (enum xmodem16::ISP_DIR)xmodem16::XH_CAN, 2);

    if (!_quiet)
        ::printf("send out cancel-transmission request ... ");

    int r = ::write(_fd_dev, &x.pkt_out, 2);
    if (r != 2) {
        if (!_quiet)
            ::printf("failed (%d)\n", r);
        return -1;
    }

    if (!_quiet)
        ::printf("done\n");

    // ----------------------------

    r = get_ack(x, ISP_ACK_WAIT_SLEEP_US);
    if (r < 0)
        return r;

    // ----------------------------

    return get_ack_data(x);
}

int ftisp::do_eot()
{
    xmodem16 x(xmodem16::XH_EOT);

    if (!_quiet)
        ::printf("send out end-of-transmission request ... ");

    int r = ::write(_fd_dev, &x.pkt_out, 1);
    if (r != 1) {
        if (!_quiet)
            ::printf("failed (%d)\n", r);
        return -1;
    }

    if (!_quiet)
        ::printf("done\n");

    // ----------------------------

    r = get_ack(x, ISP_ACK_WAIT_SLEEP_US);
    if (r < 0)
        return r;

    // ----------------------------

    return get_ack_data(x);
}
#endif

int ftisp::get_ack(xmodem16 &x, uint32_t sleep_us, bool quiet)
{
    if (!quiet)
        ::printf("waiting ack/nak ... ");

    int timeout = ISP_ACK_TIMEOUT;
    int r = 0;

    while (timeout-- >= 0) {

        r = ::read(_fd_dev, &x.ack, 1);
        if (r == 1)
            break;

        if (r < 0) {
            timeout = -1;
            break;
        }

        ::usleep(sleep_us);
    }

    if (timeout < 0) {
        if (!quiet)
            ::printf("timeout (%d)\n", r);
        return -1;
    }

    if (!quiet) {
        if (x.ack == xmodem16::XH_ACK) {
            ::printf("0x%02x (acked)\n", (uint32_t)x.ack);
        } else if (x.ack == xmodem16::XH_NAK) {
            ::printf("0x%02x (nacked)\n", (uint32_t)x.ack);
        } else {
            ::printf("0x%02x (unknown)\n", (uint32_t)x.ack);
        }
    }

    return 0;
}

int ftisp::get_ack_data(xmodem16 &x, bool reg, bool quiet)
{
    x.pkt_in_size = 0;

    ::memset(x.pkt_in, 0, XMODEM_MAX_DATA_SIZE);

    int timeout = ISP_ACK_TIMEOUT;
    int i = 0;

    while ((i < XMODEM_MAX_DATA_SIZE) && (timeout > 0)) {
        int r = ::read(_fd_dev, &x.pkt_in[i], 1);

        if (r < 0)
            break;

        if (r == 1) {
            ++i;
            continue;
        }

        ::usleep(ISP_ACK_WAIT_SLEEP_US);
        --timeout;
    }

    x.pkt_in_size = i;

    if (!quiet) {
        if (i > 0) {
            if (reg)
                ::printf("data-in : 0x%08x\n", *((uint32_t *)x.pkt_in));
            else
                ::printf("ack-msg: %s\n", (const char *)x.pkt_in);
        }
    }

    return i;
}
