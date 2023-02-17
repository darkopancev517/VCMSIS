// ---------------------------------------------------------------------------
// axflasher (c)copyright 2015, vt-axif
//
// ---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

//#include <libusb.h>
//#include <ftdi.h>
#include <mpsse.h>

#include "config.h"
#include "bin_object.h"
//#include "hex_object.h"
//#include "axftdi.h"

#include "ftisp.h"
#include "vtisp.h"
#include "vtspisp.h"
#include "vtiicisp.h"
#include "vtprobe.h"
#include "mkimg.h"

// ---------------------------------------------------------------------------

static void axisp_usage(void)
{
    ::printf("\n%s ver-%s (c)copyright vt-axisp, 2015\n", CONFIG_PROGRAM, CONFIG_VERSION);
    ::printf("\nUsage: %s <options> command <args>\n", CONFIG_PROGRAM);
    ::printf("\n options\n\n");
    ::printf("  -h or -?        Command line help.\n");
    ::printf("  -l              List ISP devices.\n");
    ::printf("  -d dev          ISP device path(serial) or index(spi). Default (serial: %s) (spi: 0)\n", CONFIG_DEFAULT_SERIAL_DEVICE);
    ::printf("  -i hwif         SPI hardware interface on FTDI Port. Default (IFACE_A: %d)\n", CONFIG_DEFAULT_SPI_INTERFACE);
    ::printf("  -s data_rate    ISP device data rate. Default (bps): serial)%d spi)%d.\n", CONFIG_DEFAULT_SERIAL_BAUDRATE, CONFIG_DEFAULT_SPI_DATARATE);
    ::printf("  -k              Do not remap and reboot after ISP (xmodem mode only).\n");
    ::printf("  -v              Verbose ISP progress list.\n");
    ::printf("  -p protocol     Communication protocol 0)xmodem 1)vtisp.\n");
    ::printf("  -x interface    Communication interface 0)serial 1)SPI 2)I2C.\n");
    ::printf("  -z              Do page erase before programming.\n");

    ::printf("\n commands\n\n");
    ::printf("  mkimg   mcu bbp v out Make production image\n");
    ::printf("                          mcu  MCU/SoC firmware image (.bin)\n");
    ::printf("                          bbp  BBP/DSP firmware image description file (.txt)\n");
    ::printf("                          v    BBP/DSP firmware image version file (.bin)\n");
    ::printf("                          out  Output file name (.bin)\n");
    ::printf("  ping                  Send peer-ping command.\n");
    ::printf("  cli     cmd           Execute console command.\n");
    ::printf("  break                 Send break/cancel-ISP request.\n");
    ::printf("  setup   index value   ISP settings setup.\n");
    ::printf("                          0    slave_out_timeout (hex)\n");
    ::printf("                          1    isp-page-size (hex)\n");
    ::printf("  dw      addr (nr)     Read nr 32-bit data at given address (hex).\n");
    ::printf("  ww      addr data ..  Write 32-bit data(s) at given address (hex).\n");
    //::printf("  iw      addr image    In-system-program image into the target system at given address (hex).\n");
    ::printf("  isp     image (addr)  In-system-program image into the target system at given address.\n");
    ::printf("  sumisp  image (addr)  In-system-program image into the target system at given address. Use DMA and Check sum method.\n");
    ::printf("  bist    pattern       32-bit data read/write BIST scan (hex).\n");
    ::printf("  reboot  remap         Setup remap 0)iROM 1)iRAM 2)eFlash 9)Debug-Trace and then send reboot command.\n");
    ::printf("  probe   base (addr)          (SPI Probe) Show/Set 32-bit offset-cmd base address (hex).\n");
    ::printf("  probe   delay (cycles)       (SPI Probe) Show/Set 8-bit prober read delay cycles (hex [4:0]cycles).\n");
    ::printf("  probe   dw  delay addr (nr)  (SPI Probe) Read nr 32-bit data at given address (hex).\n");
    ::printf("  probe   idw delay off (nr)   (SPI Probe) Read nr 32-bit data at given offset from the base address (hex).\n");
    ::printf("  probe   ww  addr data ..     (SPI Probe) Write 32-bit data(s) at given address (hex).\n");
    ::printf("  probe   iww off addr data .. (SPI Probe) Write 32-bit data(s) at given offset from the base address (hex).\n");

    ::printf("\n");
}

// first ':' disables glibc err-msg
static char axisp_options[] = ":s:d:i:p:x:lvkzh?";

int axisp_context::validate_hex(const char *sz_nr)
{
    while (*sz_nr == ' ')
        ++sz_nr;

    if (::strncmp("0x", sz_nr, 2) == 0)
        sz_nr += 2;

    if (::strlen(sz_nr) == 0)
        return -1;

    if (::strlen(sz_nr) > 8)
        return -1;

    while (*sz_nr) {
        if (*sz_nr > '9') {
            if (*sz_nr < 'A') {
                return -1;
            } else if (*sz_nr > 'F') {
                if (*sz_nr < 'a') {
                    return -1;
                } else if (*sz_nr > 'f') {
                    return -1;
                }
            }
        } else if (*sz_nr < '0') {
            return -1;
        }

        ++sz_nr;
    }

    return 0;
}

int axisp_context::validate_dec(const char *sz_nr)
{
    while (*sz_nr == ' ')
        ++sz_nr;

    if (strlen(sz_nr) == 0)
        return -1;

    while (*sz_nr) {
        if (*sz_nr > '9') {
            return -1;
        } else if (*sz_nr < '0') {
            return -1;
        }

        ++sz_nr;
    }

    return 0;
}

// ---------------------------------------------------------------------------

// instanciate program context
struct axisp_context axisp_ctxt;

// instanciate isp controller
class ftisp ftisp;
class vtisp vtisp;
class vtspisp vtspisp;
class vtiicisp vtiicisp;
class vtprobe vtprb;

// ---------------------------------------------------------------------------

int axisp_do_dev_list()
{
    isp *isp = axisp_ctxt.isp_obj;

    isp->quiet(false);

    isp->do_dev_list();

    ::printf("\n");

    return 0;
}

int axisp_do_ping()
{
    isp *isp = axisp_ctxt.isp_obj;

    isp->quiet(false);

    int r = isp->open();
    if (r < 0)
        return r;
	
    isp->do_ping();

    isp->close();

    ::printf("close\n");

    return 0;
}

int axisp_do_cli()
{
    isp *isp = axisp_ctxt.isp_obj;

    isp->quiet(false);

    int r = isp->open();
    if (r < 0)
        return r;

    isp->do_cli_cmd();

    isp->close();

    ::printf("\n");

    return 0;
}

int axisp_do_break()
{
    isp *isp = axisp_ctxt.isp_obj;

    isp->quiet(false);

    int r = isp->open();
    if (r < 0)
        return r;

    isp->do_break();

    isp->close();

    ::printf("\n");

    return 0;
}

int axisp_do_word_read()
{
    isp *isp = axisp_ctxt.isp_obj;

    int r = 0;

    isp->quiet(false);

    r = isp->open();
    if (r < 0)
        return r;

    isp->do_word_read();

    isp->close();

    ::printf("\n");

    return r;
}

int axisp_do_word_write()
{
    isp *isp = axisp_ctxt.isp_obj;

    int r = 0;

    isp->quiet(false);

    r = isp->open();
    if (r < 0)
        return r;

    isp->do_word_write();

    isp->close();

    ::printf("\n");

    return r;
}

int axisp_do_bist()
{
    isp *isp = axisp_ctxt.isp_obj;

    isp->quiet(false);

    int r = isp->open();
    if (r < 0)
        return r;

    //isp->do_bist(0x20000000, 0x8000, axisp_ctxt.pattern);

    isp->close();

    ::printf("\n");

    return r;
}

int axisp_do_isp()
{
    isp *isp = axisp_ctxt.isp_obj;

    isp->quiet(false);

    int r = isp->open();
    if (r < 0)
        return r;

    isp->do_isp();

    isp->close();

    ::printf("\n");

    return r;
}

int axisp_do_fastisp()
{
    isp *isp = axisp_ctxt.isp_obj;

    isp->quiet(false);

    int r = isp->open();
    if (r < 0)
        return r;

    isp->do_fastisp();

    isp->close();

    ::printf("\n");

    return r;
}

int axisp_do_sumisp()
{
    isp *isp = axisp_ctxt.isp_obj;

    isp->quiet(false);

    int r = isp->open();
    if (r < 0)
        return r;

    isp->do_sumisp();

    isp->close();

    ::printf("\n");

    return r;
}

int axisp_do_reboot()
{
    isp *isp = axisp_ctxt.isp_obj;

    isp->quiet(false);

    int r = isp->open();
    if (r < 0)
        return r;

    isp->do_reboot();

    isp->close();

    ::printf("\n");

    return r;
}

int axisp_do_setup()
{
    isp *isp = axisp_ctxt.isp_obj;

    isp->quiet(false);

    int r = isp->open();
    if (r < 0)
        return r;

    isp->do_setup();

    isp->close();

    ::printf("\n");

    return r;
}

int axisp_do_make_image()
{
    mkimg mkimg_obj;

    return mkimg_obj.do_make_image();
}

int axisp_do_probe()
{
    int r = vtprb.open();
    if (r < 0)
        return r;

    vtprb.do_probe_cmd();

    vtprb.close();

    ::printf("\n");

    return r;
}

// ---------------------------------------------------------------------------

int axisp_dispatch_command()
{
    const char *sz_cmd = &axisp_ctxt.isp_args[0][0];

    ::printf("\n%s ver-%s (c)copyright vt-axif, 2015\n\n", CONFIG_PROGRAM, CONFIG_VERSION);

    if (axisp_ctxt.interface == 0) {
        if (axisp_ctxt.data_rate == (uint32_t)-1)
            axisp_ctxt.data_rate = CONFIG_DEFAULT_SERIAL_BAUDRATE;
        ::printf("serial device      : %s\n", axisp_ctxt.fname_dev);
        ::printf("serial baudrate    : %d\n", axisp_ctxt.data_rate);
    } else if (axisp_ctxt.interface == 1) {
        if (axisp_ctxt.data_rate == (uint32_t)-1)
            axisp_ctxt.data_rate = CONFIG_DEFAULT_SPI_DATARATE;
        ::printf("spi data-rate      : %d\n", axisp_ctxt.data_rate);
    } else if (axisp_ctxt.interface == 2) {
        if (axisp_ctxt.data_rate == (uint32_t)-1)
            axisp_ctxt.data_rate = CONFIG_DEFAULT_I2C_DATARATE;
        ::printf("i2c data-rate      : %d\n", axisp_ctxt.data_rate);
    } else {
        return -1;
    }

    ::printf("protocol           : %s\n", (axisp_ctxt.protocol == 0) ? "ftisp" : "vtisp");
    ::printf("interface          : %s\n", (axisp_ctxt.interface == 0) ? "serial" : ((axisp_ctxt.interface == 1) ? "spi" : "i2c"));

    ::printf("\ncommand            : %s (args %d)\n", sz_cmd[0] == 0 ? "null" : sz_cmd, axisp_ctxt.isp_nr_args);

    if (axisp_ctxt.isp_nr_args > 0) {
        for (int i = 1; i <= axisp_ctxt.isp_nr_args; ++i) {
            ::printf("  arg[%d]           : %s\n", i, &axisp_ctxt.isp_args[i][0]);
        }
    }
    ::printf("\n");

    if (axisp_ctxt.dev_list)
        return axisp_do_dev_list();

    if (::strncmp(sz_cmd, "ping", 2) == 0) {
        return axisp_do_ping();
    } else if (::strncmp(sz_cmd, "cli", 2) == 0) {
        return axisp_do_cli();
    } else if (::strncmp(sz_cmd, "break", 2) == 0) {
        return axisp_do_break();
    } else if (::strncmp(sz_cmd, "dw", 2) == 0) {
        return axisp_do_word_read();
    } else if (::strncmp(sz_cmd, "ww", 2) == 0) {
        return axisp_do_word_write();
    //} else if (::strncmp(sz_cmd, "rawisp", 2) == 0) {
    } else if (::strncmp(sz_cmd, "isp", 2) == 0) {
        return axisp_do_isp();
    } else if (::strncmp(sz_cmd, "fastisp", 7) == 0) {
        return axisp_do_fastisp();
    } else if (::strncmp(sz_cmd, "sumisp", 6) == 0) {
        return axisp_do_sumisp();
    } else if (::strncmp(sz_cmd, "bist", 2) == 0) {
       return axisp_do_bist();
    } else if (::strncmp(sz_cmd, "reboot", 3) == 0) {
        return axisp_do_reboot();
    } else if (::strncmp(sz_cmd, "setup", 3) == 0) {
        return axisp_do_setup();
    } else if (::strncmp(sz_cmd, "mkimg", 2) == 0) {
        return axisp_do_make_image();
    } else if (::strncmp(sz_cmd, "probe", 2) == 0) {
        return axisp_do_probe();
    } else {
        ::printf("\n[err] unknown command !\n\n");
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int nr_args = 0;

    if (argc < 2)
        goto _usage;

    axisp_ctxt.isp_obj = &ftisp;
    axisp_ctxt.data_rate = (uint32_t)-1;

    // get command line options ...
    while (1) {

        int c = ::getopt(argc, argv, axisp_options);

        if (c < 0) {

            if (optind >= argc) {
                break;
            }

            ::strncpy(&axisp_ctxt.isp_args[nr_args++][0], argv[optind], CONFIG_MAX_PATH - 1);

            for (int i = optind + 1; i < argc; ++i) {

                if (nr_args >= CONFIG_MAX_ARGS)
                    break;

                ::strncpy(&axisp_ctxt.isp_args[nr_args++][0], argv[i], CONFIG_MAX_PATH - 1);
            }

            axisp_ctxt.isp_nr_args = nr_args - 1;
            break;
        }

        switch (c) {
        case 'd':
            //if (::access(optarg, R_OK | W_OK) != 0) {
            //    ::printf("\n[err] invalid isp interface device : %s\n\n", optarg);
            //    goto _usage;
            //}

            ::strncpy(axisp_ctxt.fname_dev, optarg, CONFIG_MAX_PATH);
            break;

        case 's':
            if (::axisp_context::validate_dec(optarg)) {
                ::printf("\n[err] invalid data-rate value: %s\n\n", optarg);
                goto _usage;
            }

            axisp_ctxt.data_rate = ::strtoul(optarg, 0, 10);
            break;

        case 'i':
            if (::axisp_context::validate_dec(optarg)) {
                ::printf("\n[err] invalid ftdi interface value: %s\n\n", optarg);
                goto _usage;
            }

            axisp_ctxt.hw_if = ::strtoul(optarg, 0, 10);
            if(axisp_ctxt.hw_if > IFACE_D) {
                ::printf("\n[err] invalid ftdi interface value: %s\n\n", optarg);
                axisp_ctxt.hw_if = CONFIG_DEFAULT_SPI_INTERFACE;
            }
            break;

        case 'l':
            axisp_ctxt.dev_list = true;
            break;

        case 'k':
            axisp_ctxt.reboot = false;
            break;

        case 'v':
            axisp_ctxt.verbose = true;
            break;

        case 'p':
            if (::axisp_context::validate_dec(optarg)) {
                ::printf("\n[err] invalid protocol value: %s\n\n", optarg);
                goto _usage;
            }

            axisp_ctxt.protocol = ::strtoul(optarg, 0, 10);

            if (axisp_ctxt.protocol > 1) {
                ::printf("\n[err] invalid protocol value: %s\n\n", optarg);
                goto _usage;
            }
            break;

        case 'x':
            if (::axisp_context::validate_dec(optarg)) {
                ::printf("\n[err] invalid interface value: %s\n\n", optarg);
                goto _usage;
            }

            axisp_ctxt.interface = ::strtoul(optarg, 0, 10);

            if (axisp_ctxt.interface > 2) {
                ::printf("\n[err] invalid interface value: %s\n\n", optarg);
                goto _usage;
            }
            break;

        case 'z':
            axisp_ctxt.erase_prog = true;
            break;

        case '?':
        case 'h':
            goto _usage;

        case '!':
            ::printf("\n[err] invalid option: %s\n\n", argv[optind - 1]);
            goto _usage;

        default:
            ::printf("\n[err] invalid option: %s\n\n", argv[optind]);
            goto _usage;
        }
    }

    if (axisp_ctxt.protocol == 0) {
        axisp_ctxt.isp_obj = &ftisp;
    } else if (axisp_ctxt.protocol == 1) {
        if (axisp_ctxt.interface == 0)
            axisp_ctxt.isp_obj = &vtisp;
        else if (axisp_ctxt.interface == 1)
            axisp_ctxt.isp_obj = &vtspisp;
        else if (axisp_ctxt.interface == 2)
            axisp_ctxt.isp_obj = &vtiicisp;
        else
            goto _usage;
    } else {
        goto _usage;
    }

    return axisp_dispatch_command();

_usage:

    axisp_usage();

    return -1;
}
