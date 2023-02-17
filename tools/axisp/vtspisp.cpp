
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include <libusb.h>
#include <ftdi.h>
#include <mpsse.h>

//#include "xmodem.h"
#include "vtspisp.h"
#include "ftefc.h"
#include "bin_object.h"

#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif

// ---------------------------------------------------------------------------
// SPI ISP configuration ...
//
//   GPIO[7] <- RST
//   MPSSE_A <- SPI
//
//   FT4232H           ISP       MINI    51
//   ----------------  --------  ------  --
//   ADBUS[0]  TCK/SK  SPI_CLK   CN2_7    8
//   ADBUS[1]  TDI/DO  SPI_MOSI  CN2_10   6
//   ADBUS[2]  TDO/DI  SPI_MISO  CN2_9    7
// //DDBUS[7]  GPIO    RST       CN3_9    9
//   DDBUS[0]  GPIO    RST       CN3_17   9
//
//
//   FT4232H HUB       ISP       MINI    51
//   ----------------  --------  ------  --
//   ADBUS[0]  TCK/SK  SPI_CLK   CN3_9    8
//   ADBUS[1]  TDI/DO  SPI_MOSI  CN3_10   6
//   ADBUS[2]  TDO/DI  SPI_MISO  CN3_11   7
//   DDBUS[0]  GPIO    RST       CN3_4    9
//
//
// pin [7]x [6]x [5]IRQ [4]CE [3]CS [2]DI [1]DO [0]TCK
//        x    x    in     out   out   in    out   out
//
// ---------------------------------------------------------------------------

/* Sets the read and write timeout periods for bulk usb data transfers. */
static void ftdi_spi_set_timeouts(struct mpsse_context *mpsse, int timeout)
{
    if (mpsse->mode) {
        mpsse->ftdi.usb_read_timeout = timeout;
        mpsse->ftdi.usb_write_timeout = timeout;
    }

    return;
}

static struct mpsse_context *ftdi_spi_open(int index, int vid, int pid, enum modes mode, int freq, int endianess, int interface, const char *description, const char *serial)
{
    int status = 0;
    struct mpsse_context *mpsse = NULL;

    //if (freq > 32000000)
    //    freq = 32000000;

    //freq &= ~0x7ffff;
    //if (freq < 100000)
    //    freq = 100000;

    mpsse = (struct mpsse_context *)malloc(sizeof(struct mpsse_context));
    if(mpsse)
    {
        memset(mpsse, 0, sizeof(struct mpsse_context));

        /* Legacy; flushing is no longer needed, so disable it by default. */
        FlushAfterRead(mpsse, 0);

        /* ftdilib initialization */
        if(ftdi_init(&mpsse->ftdi) == 0)
        {
            /* Set the FTDI interface  */
            ftdi_set_interface(&mpsse->ftdi, (enum ftdi_interface)interface);

            /* Open the specified device */
            if(ftdi_usb_open_desc_index(&mpsse->ftdi, vid, pid, description, serial, index) == 0)
            {
                mpsse->mode = mode;
                mpsse->vid = vid;
                mpsse->pid = pid;
                mpsse->status = STOPPED;
                mpsse->endianess = endianess;

                /* Set the appropriate transfer size for the requested protocol */
                if(mpsse->mode == I2C)
                {
                    mpsse->xsize = I2C_TRANSFER_SIZE;
                }
                else
                {
                    mpsse->xsize = SPI_RW_SIZE;
                }

                status |= ftdi_usb_reset(&mpsse->ftdi);
                status |= ftdi_set_latency_timer(&mpsse->ftdi, LATENCY_MS);
                status |= ftdi_write_data_set_chunksize(&mpsse->ftdi, CHUNK_SIZE);
                status |= ftdi_read_data_set_chunksize(&mpsse->ftdi, CHUNK_SIZE);
                status |= ftdi_set_bitmode(&mpsse->ftdi, 0, BITMODE_RESET);

                if(status == 0)
                {
                    /* Set the read and write timeout periods */
                    ftdi_spi_set_timeouts(mpsse, USB_TIMEOUT);

                    if(mpsse->mode != BITBANG)
                    {
                        ftdi_set_bitmode(&mpsse->ftdi, 0, BITMODE_MPSSE);

                        if(SetClock(mpsse, freq) == MPSSE_OK)
                        {
                            if(SetMode(mpsse, endianess) == MPSSE_OK)
                            {
                                mpsse->open = 1;

                                /* Give the chip a few mS to initialize */
                                usleep(SETUP_DELAY);

                                /*
                                 * Not all FTDI chips support all the commands that SetMode may have sent.
                                 * This clears out any errors from unsupported commands that might have been sent during set up.
                                 */
                                ftdi_tcioflush(&mpsse->ftdi);
                            }
                        }
                    }
                    else
                    {
                        /* Skip the setup functions if we're just operating in BITBANG mode */
                        if(ftdi_set_bitmode(&mpsse->ftdi, 0xFF, BITMODE_BITBANG) == 0)
                        {
                            mpsse->open = 1;
                        }
                    }
                }
            }
        }
    }

    return mpsse;
}

// ---------------------------------------------------------------------------

void vtspisp_packet::do_cmd_ping()
{
    // mo: 0f 1f 2f 3f
    // so: 6d 67 70 69 ('m' 'g' 'p' 'i')

    _size_out = 4;
    _size_in = 4;

    //::memset(_data_out, 0, _size_out);
    ::memset(_data_in, 0, _size_in);

    _data_out[0] = (uint8_t)VTSPISP_CMD_PING;
    _data_out[1] = (uint8_t)VTSPISP_CMD_PING + 0x10;
    _data_out[2] = (uint8_t)VTSPISP_CMD_PING + 0x20;
    _data_out[3] = (uint8_t)VTSPISP_CMD_PING + 0x30;

    //_data_out[4] = (uint8_t)'m';
    //_data_out[5] = (uint8_t)'g';
    //_data_out[6] = (uint8_t)'p';
    //_data_out[7] = (uint8_t)'i';

    //_data_out[8] = (uint8_t)'p';
    //_data_out[9] = (uint8_t)'i';
    //_data_out[10] = (uint8_t)'n';
    //_data_out[11] = (uint8_t)'g';
}

void vtspisp_packet::do_cmd_break()
{
}

void vtspisp_packet::do_vtefc_init(uint32_t type)
{
        _size_out = 5;
        _size_in = (1 + 1 ) * 4;

        ::memset(_data_in, 0, _size_in);

        _data_out[0] = (uint8_t)VTSPISP_CMD_VTEFC_INIT;

        *((uint32_t *)(&_data_out[1])) = type;
}

void vtspisp_packet::do_cmd_read_checksum(uint32_t addr, uint32_t size)
{
        // mo: 12 addr[31:0]
        // so: garbage_word + data ...

        _size_out = 5;
        _size_in = (1 + 1 ) * 4;

        //::memset(_data_out, 0, _size_out);
        ::memset(_data_in, 0, _size_in);

        _data_out[0] = (uint8_t)VTSPISP_CMD_PAGE_CHECKSUM;

        *((uint32_t *)(&_data_out[1])) = addr;
}
void vtspisp_packet::do_cmd_word_read(uint32_t addr, uint32_t nr_words)
{
    if (nr_words == 0) {

        _size_out = 0;
        _size_in = 0;
        return;

    } else if (nr_words == 1) {

        // mo: 11 addr[31:0]
        // so: garbage_word + data[31:0]

        _size_out = 5;
        _size_in = 4 + 4;

        //::memset(_data_out, 0, _size_out);
        ::memset(_data_in, 0, _size_in);

        _data_out[0] = (uint8_t)VTSPISP_CMD_WORD_READ;

        *((uint32_t *)(&_data_out[1])) = addr;

    } else if (nr_words == (VTSPISP_SPI_PAGE_SIZE / 4)) {

        // mo: 12 addr[31:0]
        // so: garbage_word + data ...

        _size_out = 5;
        _size_in = (1 + nr_words) * 4;

        //::memset(_data_out, 0, _size_out);
        ::memset(_data_in, 0, _size_in);

        _data_out[0] = (uint8_t)VTSPISP_CMD_PAGE_READ;

        *((uint32_t *)(&_data_out[1])) = addr;

    } else {

        // mo: 13 addr[31:0] nr_words[31:0]
        // so: garbage_word + data ...

        _size_out = 9;
        _size_in = (1 + nr_words) * 4;

        //::memset(_data_out, 0, _size_out);
        ::memset(_data_in, 0, _size_in);

        _data_out[0] = (uint8_t)VTSPISP_CMD_WORDS_READ;

        *((uint32_t *)(&_data_out[1])) = addr;
        *((uint32_t *)(&_data_out[5])) = nr_words;
    }
}

void vtspisp_packet::do_cmd_page_program(uint32_t addr, uint32_t *data, uint32_t size, bool DMAFlag)
{
    if(DMAFlag == true)
        _data_out[0] = (uint8_t)VTSPISP_CMD_WRITE_DMA;
    else
        _data_out[0] = (uint8_t)VTSPISP_CMD_PAGE_PROGRAM;
    _data_out[1] = 0;//(uint8_t)VTISP_CMDF_WORD_DATA;
    _data_out[2] = (uint8_t)(size & 0xff);
    _data_out[3] = (uint8_t)((size >> 8) & 0xff);

    _data_out[4] = (uint8_t)(addr & 0xff);
    _data_out[5] = (uint8_t)((addr >> 8) & 0xff);
    _data_out[6] = (uint8_t)((addr >> 16) & 0xff);
    _data_out[7] = (uint8_t)((addr >> 24) & 0xff);

    _size_out = 8;

    // copy data to output buffer, if necessary ...
    if (data != NULL) {
        uint8_t *out_iter = &_data_out[8];

        while (size-- > 0) {
            out_iter[0] = ((uint8_t *)data)[0];
            out_iter[1] = ((uint8_t *)data)[1];
            out_iter[2] = ((uint8_t *)data)[2];
            out_iter[3] = ((uint8_t *)data)[3];

            out_iter += 4;
            ++data;
            _size_out += 4;
        }
    } else {
        _size_out += (size * 4);
    }

    _size_in = 0;
}

void vtspisp_packet::do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t nr_words, bool DMAFlag)
{
}
void vtspisp_packet::do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t nr_words)
{
    assert((nr_words * 4) < (VTSPISP_RAW_DATA_SIZE - 16));

    if (nr_words == 0) {

        _size_out = 0;
        _size_in = 0;
        return;

    } else if (nr_words == 1) {

        // mo: 21 21 21 21 addr[31:0] data[31:0]
        // so: n/a

        _size_out = 4 + 4 + 4;
        _size_in = 0;

        //::memset(_data_out, 0, _size_out);
        //::memset(_data_in, 0, _size_in);

        _data_out[0] = (uint8_t)VTSPISP_CMD_WORD_WRITE;
        _data_out[1] = (uint8_t)VTSPISP_CMD_WORD_WRITE;
        _data_out[2] = (uint8_t)VTSPISP_CMD_WORD_WRITE;
        _data_out[3] = (uint8_t)VTSPISP_CMD_WORD_WRITE;

        *((uint32_t *)(&_data_out[4])) = addr;

        if (data != NULL)
            *((uint32_t *)(&_data_out[8])) = data[0];

    } else if (nr_words == (VTSPISP_SPI_PAGE_SIZE / 4)) {

        // mo: 22 22 22 22 addr[31:0] data ...
        // so: n/a

        _size_out = 4 + 4 + 4 * nr_words;
        _size_in = 0;

        //::memset(_data_out, 0, _size_out);
        //::memset(_data_in, 0, _size_in);

        _data_out[0] = (uint8_t)VTSPISP_CMD_PAGE_WRITE;
        _data_out[1] = (uint8_t)VTSPISP_CMD_PAGE_WRITE;
        _data_out[2] = (uint8_t)VTSPISP_CMD_PAGE_WRITE;
        _data_out[3] = (uint8_t)VTSPISP_CMD_PAGE_WRITE;

        *((uint32_t *)(&_data_out[4])) = addr;

        if (data != NULL)
            ::memcpy(&_data_out[8], data, 4 * nr_words);

    } else {

        // mo: 23 23 23 23 addr[31:0] nr_words[31:0] data ...
        // so: n/a

        _size_out = 4 + 4 + 4 + 4 * nr_words;
        _size_in = 0;

        //::memset(_data_out, 0, _size_out);
        //::memset(_data_in, 0, _size_in);

        _data_out[0] = (uint8_t)VTSPISP_CMD_WORDS_WRITE;
        _data_out[1] = (uint8_t)VTSPISP_CMD_WORDS_WRITE;
        _data_out[2] = (uint8_t)VTSPISP_CMD_WORDS_WRITE;
        _data_out[3] = (uint8_t)VTSPISP_CMD_WORDS_WRITE;

        *((uint32_t *)(&_data_out[4])) = addr;
        *((uint32_t *)(&_data_out[8])) = nr_words;

        if (data != NULL)
            ::memcpy(&_data_out[12], data, 4 * nr_words);
    }
}

void vtspisp_packet::do_cmd_word_write(uint32_t addr, uint32_t data, bool DMAFlag)
{
}
void vtspisp_packet::do_cmd_word_write(uint32_t addr, uint32_t data)
{
    // mo: 21 21 21 21 addr[31:0] data[31:0]
    // so: n/a

    _size_out = 4 + 4 + 4;
    _size_in = 0;

    //::memset(_data_out, 0, _size_out);
    //::memset(_data_in, 0, _size_in);

    _data_out[0] = (uint8_t)VTSPISP_CMD_WORD_WRITE;
    _data_out[1] = (uint8_t)VTSPISP_CMD_WORD_WRITE;
    _data_out[2] = (uint8_t)VTSPISP_CMD_WORD_WRITE;
    _data_out[3] = (uint8_t)VTSPISP_CMD_WORD_WRITE;

    *((uint32_t *)(&_data_out[4])) = addr;
    *((uint32_t *)(&_data_out[8])) = data;
}

void vtspisp_packet::do_cmd_setup(uint32_t index, uint32_t value)
{
    // mo: 88 88 index[7:0] index[15:8] value[31:0]
    // so: n/a

    _size_out = 4 + 4;
    _size_in = 0;

    //::memset(_data_out, 0, _size_out);
    //::memset(_data_in, 0, _size_in);

    _data_out[0] = (uint8_t)VTSPISP_CMD_SETUP;
    _data_out[1] = (uint8_t)VTSPISP_CMD_SETUP;
    _data_out[2] = (uint8_t)index;
    _data_out[3] = (uint8_t)(index >> 8);

    *((uint32_t *)(&_data_out[4])) = value;
}

int vtspisp_packet::send_out(bool wait_ack, uint32_t data_in_delay)
{
    uint8_t *data_in = NULL;

    if (_size_out <= 0)
        return ISP_ERR_IO_SIZE;

    if (::Start(_mpsse_spi) < 0)
        return (int)ISP_ERR_IO_GENERIC;

    if (::Write(_mpsse_spi, (char *)_data_out, (int)_size_out) < 0)
        return (int)ISP_ERR_IO_WRITE;

    if (_size_in > 0) {
        if (data_in_delay != 0)
            ::usleep(data_in_delay);
        data_in = (uint8_t *)::Read(_mpsse_spi, _size_in);
        if (data_in == NULL)
            return (int)ISP_ERR_IO_READ;
    }

    ::Stop(_mpsse_spi);

    if (data_in != NULL) {
        ::memcpy(_data_in, data_in, _size_in);
        ::free(data_in);
    }

    return ISP_ERR_SUCCESS;
}

// ------------------

vtspisp::vtspisp() : _mpsse_spi(NULL)
{
}

vtspisp::~vtspisp()
{
    this->close();
}

void vtspisp::quiet(bool q)
{
}

int vtspisp::spi_dev_list()
{
    int d = 0, r = 0;  // d -- dev-index; r -- return value

    struct ftdi_device_list *dev_list = NULL, *dev_iter = NULL;
    struct ftdi_version_info ver_info;

    char sz_mfg[CONFIG_MAX_PATH] = {0};
    char sz_desc[CONFIG_MAX_PATH] = {0};
    char sz_serial[CONFIG_MAX_PATH] = {0};

    struct libusb_device_descriptor usbdev_desc = {0};

    // ----------------------------

    ver_info = ::ftdi_get_library_version();

    ::printf("\nlibftdi %s (major: %d, minor: %d, micro: %d, snapshot ver: %s)\n",
           ver_info.version_str, ver_info.major, ver_info.minor, ver_info.micro, ver_info.snapshot_str);

    if ((_ftdi_ctxt = ::ftdi_new()) == NULL) {
        ::printf("failed on ftdi_new() for gpio context !\n");
        return (int)ISP_ERR_ALLOC;
    }

    if ((r = ::ftdi_usb_find_all(_ftdi_ctxt, &dev_list, 0, 0)) < 0) {
        ::printf("failed on ftdi_usb_find_all() ... %d (%s)\n", r, ::ftdi_get_error_string(_ftdi_ctxt));
        r = ISP_ERR_IO_GENERIC;
        goto _safe_exit;
    }

    ::printf("\nnumber of FTDI devices: %d\n---------------------------\n", r);

    d = 0;
    dev_iter = dev_list;

    while (dev_iter != NULL) {

        struct libusb_config_descriptor *usbdev_config;

        sz_mfg[0] = 0;
        sz_desc[0] = 0;
        sz_serial[0] = 0;

        if ((r = ::libusb_get_device_descriptor(dev_iter->dev, &usbdev_desc)) != 0) {
            ::printf("failed on libusb_get_device_descriptor() ... %d\n", r);
            r = ISP_ERR_IO_GENERIC;
            goto _safe_exit;
        }

        if ((r = ::ftdi_usb_get_strings(_ftdi_ctxt, dev_iter->dev, sz_mfg, CONFIG_MAX_PATH, sz_desc, CONFIG_MAX_PATH, sz_serial, CONFIG_MAX_PATH)) < 0) {
            ::printf("failed on ftdi_usb_get_strings() ... %d (%s)\n", r, ::ftdi_get_error_string(_ftdi_ctxt));
            r = ISP_ERR_IO_GENERIC;
            goto _safe_exit;
        }

        ::printf("dev[%02d] bus)0x%02x addr)0x%02x vid)0x%04x pid)0x%04x mfg)%s serial)%s - %s\n", d,
                 (uint32_t)::libusb_get_bus_number(dev_iter->dev), (uint32_t)::libusb_get_device_address(dev_iter->dev),
                 (uint32_t)usbdev_desc.idVendor, (uint32_t)usbdev_desc.idProduct,
                 sz_mfg, sz_serial, sz_desc);

        for (uint8_t c = 0; c < usbdev_desc.bNumConfigurations; ++c) {

            struct libusb_device_handle *usbdev_handle = NULL;
            char sz_cfg[CONFIG_MAX_PATH];

            uint8_t i;

            if ((r = ::libusb_get_config_descriptor(dev_iter->dev, c, &usbdev_config)) < 0) {
                ::printf("  failed on libusb_get_config_descriptor() ... %d\n", r);
                r = ISP_ERR_IO_GENERIC;
                continue;
            }

            if ((r = ::libusb_open(dev_iter->dev, &usbdev_handle)) < 0) {
                ::printf("  failed on libusb_open() ... %d\n", r);
                r = ISP_ERR_IO_GENERIC;
                continue;
            }

            sz_cfg[0] = 0;
            ::libusb_get_string_descriptor_ascii(usbdev_handle, usbdev_config->iConfiguration, (uint8_t *)sz_cfg, CONFIG_MAX_PATH);

            ::printf("  cfg[%02d] cfg_val)%d nr_interfaces)%d  %s\n", c, (uint32_t)usbdev_config->bConfigurationValue, (uint32_t)usbdev_config->bNumInterfaces, sz_cfg);

            for (i = 0; i < usbdev_config->bNumInterfaces; ++i) {
                const struct libusb_interface *usbdev_if = &usbdev_config->interface[i];

                for (int a = 0; a < usbdev_if->num_altsetting; ++a) {
                    const struct libusb_interface_descriptor *usbif_desc = &usbdev_if->altsetting[a];
                    char sz_if[CONFIG_MAX_PATH];

                    sz_if[0] = 0;
                    ::libusb_get_string_descriptor_ascii(usbdev_handle, usbif_desc->iInterface, (uint8_t *)sz_if, CONFIG_MAX_PATH);

                    ::printf("    if[%02d] alt)%d if_val)%d nr_ep)%d class)0x%02x sub_class)0x%02x protocol)0x%02x  %s\n", (uint32_t)i,
                             (uint32_t)usbif_desc->bAlternateSetting, (uint32_t)usbif_desc->bInterfaceNumber, (uint32_t)usbif_desc->bNumEndpoints,
                             (uint32_t)usbif_desc->bInterfaceClass, (uint32_t)usbif_desc->bInterfaceSubClass, (uint32_t)usbif_desc->bInterfaceProtocol, sz_if);
                }
            }

            ::libusb_close(usbdev_handle);

            ::libusb_free_config_descriptor(usbdev_config);
        }

        dev_iter = dev_iter->next;
    }

    ::printf("\n");

    if (dev_list != NULL)
        ::ftdi_list_free(&dev_list);

    spi_close();

    return (int)ISP_ERR_SUCCESS;

_safe_exit:

    if (dev_list != NULL)
        ::ftdi_list_free(&dev_list);

    spi_close();

    return r;
}

int vtspisp::spi_open()
{
    int d = 0, s = 0, r = 0;  // d -- dev-index; s -- selected-dev-index; r -- return value

    struct ftdi_device_list *dev_list = NULL, *dev_iter = NULL, *dev_sel = NULL;
    struct ftdi_version_info ver_info;

    int vid_sel, pid_sel;

    char sz_mfg[CONFIG_MAX_PATH] = {0};
    char sz_desc[CONFIG_MAX_PATH] = {0};
    char sz_serial[CONFIG_MAX_PATH] = {0};

    struct libusb_device_descriptor usbdev_desc = {0};

    // ----------------------------

    if (axisp_ctxt.fname_dev[0] != 0) {
        s = (int)::strtoul(axisp_ctxt.fname_dev, NULL, 10);
    }

    // ----------------------------

    ver_info = ::ftdi_get_library_version();

    ::printf("\nlibftdi %s (major: %d, minor: %d, micro: %d, snapshot ver: %s)\n",
           ver_info.version_str, ver_info.major, ver_info.minor, ver_info.micro, ver_info.snapshot_str);

    if ((_ftdi_ctxt = ::ftdi_new()) == NULL) {
        ::printf("failed on ftdi_new() for gpio context !\n");
        return (int)ISP_ERR_ALLOC;
    }

    if ((r = ::ftdi_usb_find_all(_ftdi_ctxt, &dev_list, 0, 0)) < 0) {
        ::printf("failed on ftdi_usb_find_all() ... %d (%s)\n", r, ::ftdi_get_error_string(_ftdi_ctxt));
        r = ISP_ERR_IO_GENERIC;
        goto _safe_exit;
    }

    ::printf("\nnumber of FTDI devices: %d (selected: %u)\n---------------------------\n", r, s);

    d = 0;
    dev_iter = dev_list;

    while (dev_iter != NULL) {

        struct libusb_config_descriptor *usbdev_config;

        sz_mfg[0] = 0;
        sz_desc[0] = 0;
        sz_serial[0] = 0;

        if ((r = ::libusb_get_device_descriptor(dev_iter->dev, &usbdev_desc)) != 0) {
            ::printf("failed on libusb_get_device_descriptor() ... %d\n", r);
            r = ISP_ERR_IO_GENERIC;
            goto _safe_exit;
        }

        if ((r = ::ftdi_usb_get_strings(_ftdi_ctxt, dev_iter->dev, sz_mfg, CONFIG_MAX_PATH, sz_desc, CONFIG_MAX_PATH, sz_serial, CONFIG_MAX_PATH)) < 0) {
            ::printf("failed on ftdi_usb_get_strings() ... %d (%s)\n", r, ::ftdi_get_error_string(_ftdi_ctxt));
            r = ISP_ERR_IO_GENERIC;
            goto _safe_exit;
        }

        ::printf("dev[%02d] bus)0x%02x addr)0x%02x vid)0x%04x pid)0x%04x mfg)%s serial)%s - %s\n", d,
                 (uint32_t)::libusb_get_bus_number(dev_iter->dev), (uint32_t)::libusb_get_device_address(dev_iter->dev),
                 (uint32_t)usbdev_desc.idVendor, (uint32_t)usbdev_desc.idProduct,
                 sz_mfg, sz_serial, sz_desc);

        for (uint8_t c = 0; c < usbdev_desc.bNumConfigurations; ++c) {

            struct libusb_device_handle *usbdev_handle = NULL;
            char sz_cfg[CONFIG_MAX_PATH];

            uint8_t i;

            if ((r = ::libusb_get_config_descriptor(dev_iter->dev, c, &usbdev_config)) < 0) {
                ::printf("  failed on libusb_get_config_descriptor() ... %d\n", r);
                r = ISP_ERR_IO_GENERIC;
                continue;
            }

            if ((r = ::libusb_open(dev_iter->dev, &usbdev_handle)) < 0) {
                ::printf("  failed on libusb_open() ... %d\n", r);
                r = ISP_ERR_IO_GENERIC;
                continue;
            }

            sz_cfg[0] = 0;
            ::libusb_get_string_descriptor_ascii(usbdev_handle, usbdev_config->iConfiguration, (uint8_t *)sz_cfg, CONFIG_MAX_PATH);

            ::printf("  cfg[%02d] cfg_val)%d nr_interfaces)%d  %s\n", c, (uint32_t)usbdev_config->bConfigurationValue, (uint32_t)usbdev_config->bNumInterfaces, sz_cfg);

            for (i = 0; i < usbdev_config->bNumInterfaces; ++i) {
                const struct libusb_interface *usbdev_if = &usbdev_config->interface[i];

                for (int a = 0; a < usbdev_if->num_altsetting; ++a) {
                    const struct libusb_interface_descriptor *usbif_desc = &usbdev_if->altsetting[a];
                    char sz_if[CONFIG_MAX_PATH];

                    sz_if[0] = 0;
                    ::libusb_get_string_descriptor_ascii(usbdev_handle, usbif_desc->iInterface, (uint8_t *)sz_if, CONFIG_MAX_PATH);

                    ::printf("    if[%02d] alt)%d if_val)%d nr_ep)%d class)0x%02x sub_class)0x%02x protocol)0x%02x  %s\n", (uint32_t)i,
                             (uint32_t)usbif_desc->bAlternateSetting, (uint32_t)usbif_desc->bInterfaceNumber, (uint32_t)usbif_desc->bNumEndpoints,
                             (uint32_t)usbif_desc->bInterfaceClass, (uint32_t)usbif_desc->bInterfaceSubClass, (uint32_t)usbif_desc->bInterfaceProtocol, sz_if);
                }
            }

            ::libusb_close(usbdev_handle);

            ::libusb_free_config_descriptor(usbdev_config);
        }

        if (s == d++) {
            dev_sel = dev_iter;
            vid_sel = usbdev_desc.idVendor;
            pid_sel = usbdev_desc.idProduct;
            //break;
        }

        dev_iter = dev_iter->next;
    }

    ::printf("\n");

    if (dev_sel == NULL) {
        ::printf("\ndevice selected #%u not found!!\n", s);
        r = ISP_ERR_IO_GENERIC;
        goto _safe_exit;
    }

    // ----------------------------

    _mpsse_spi = ::ftdi_spi_open(s, vid_sel, pid_sel, SPI0, (int)axisp_ctxt.data_rate, MSB, axisp_ctxt.hw_if, NULL, NULL);
    if ((_mpsse_spi == NULL) || (_mpsse_spi->open == 0)) {
        ::printf("failed on libstdspi::Open() !\n");
        r = ISP_ERR_IO_GENERIC;
        goto _safe_exit;
    }

    if (dev_list != NULL)
        ::ftdi_list_free(&dev_list);

    return (int)ISP_ERR_SUCCESS;

_safe_exit:

    if (dev_list != NULL)
        ::ftdi_list_free(&dev_list);

    spi_close();

    return r;
}

int vtspisp::spi_close()
{
    if (_mpsse_spi != NULL)
        ::Close(_mpsse_spi);
    _mpsse_spi = NULL;

    if (_ftdi_ctxt != NULL) {
        ::ftdi_usb_close(_ftdi_ctxt);

        if (_ftdi_ctxt != NULL)
            ::ftdi_free(_ftdi_ctxt);
    }
    _ftdi_ctxt = NULL;

    return (int)ISP_ERR_SUCCESS;
}

int vtspisp::do_dev_list()
{
    return this->spi_dev_list();
}

int vtspisp::open()
{
    return this->spi_open();
}

void vtspisp::close()
{
    this->spi_close();
}

int vtspisp::do_word_read()
{
    if (axisp_ctxt.isp_nr_args < 1) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    const char *sz_addr = axisp_ctxt.isp_args[1];
    const char *sz_counts = axisp_ctxt.isp_args[2];

    if (::axisp_context::validate_hex(sz_addr)) {
        ::printf("\n[err] invalid data-read address!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    if (axisp_ctxt.isp_nr_args >= 2) {
        if (::axisp_context::validate_hex(sz_counts)) {
            ::printf("\n[err] invalid data-read counts!\n\n");
            return (int)ISP_ERR_ARGUMENT;
        }
    } else {
        sz_counts = "1";
    }

    uint32_t r_addr = ::strtoul(sz_addr, 0, 16);
    uint32_t r_counts = ::strtoul(sz_counts, 0, 16);

    r_addr = r_addr & ~0x03;
    r_counts = min(r_counts, (vtspisp_packet::VTSPISP_RAW_DATA_SIZE - 8) / 4);

    vtspisp_packet pkt(_mpsse_spi);

    pkt.do_cmd_word_read(r_addr, r_counts);

    ::printf("\nreading ... ");

    int r = pkt.send_out(false, VTSPISP_WORD_READ_DELAY(r_counts));
    if (r < 0) {
        ::printf("(failed %d)\n", r);
        goto _safe_exit;
    }

    ::printf("done\n\n");

    {
        uint32_t addr = r_addr;
        uint32_t *data = (uint32_t *)&pkt._data_in[4];

        uint32_t nr_lines = r_counts / 4;

        ::printf("addr       0        4          8        C       \n");
        ::printf("-------- | -------- --------   -------- --------\n");

        while (nr_lines--) {
            ::printf("%08X | %08X %08X - %08X %08X\n", addr, data[0], data[1], data[2], data[3]);
            addr += 16;
            data += 4;
        }

        uint32_t nr_words = r_counts % 4;

        if (nr_words) {

            ::printf("%08x |", addr);

            for (uint32_t i = 0; i < nr_words; ++i) {
                if (i == 2)
                    ::printf(" -");
                ::printf(" %08x", data[i]);
            }

            ::printf("\n");
        }
    }

    return (int)ISP_ERR_SUCCESS;

_safe_exit:

    return r;
}

#define MAX_BUFFERED_WORDS 32

int vtspisp::do_word_write()
{
    vtspisp_packet pkt(_mpsse_spi);
    ftefc efc;
    uint32_t nr_words = axisp_ctxt.isp_nr_args - 1;

    uint32_t w_data[MAX_BUFFERED_WORDS];

    if (axisp_ctxt.isp_nr_args < 2) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    const char *sz_addr = axisp_ctxt.isp_args[1];

    if (::axisp_context::validate_hex(sz_addr)) {
        ::printf("\n[err] invalid data-write address!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    uint32_t w_addr = ::strtoul(sz_addr, 0, 16);

    for (uint32_t i = 0; i < nr_words; ++i) {

        const char *sz_data = axisp_ctxt.isp_args[2 + i];

        if (::axisp_context::validate_hex(sz_data)) {
            ::printf("\n[err] invalid data-write data at data[%d] !\n\n", i);
            return (int)ISP_ERR_ARGUMENT;
        }

        w_data[i] = (uint32_t)::strtoul(sz_data, 0, 16);
    }

    w_addr &= ~0x03;

    uint32_t remap = 0;

    int r = do_remap_get(remap);
    if (r < 0)
        return (int)ISP_ERR_FAILED;

    //::usleep(1000);

    uint32_t efc_memb_base = FTEFC_MEMB_BASE;
    uint32_t efc_memb_limit = FTEFC_MEMB_BASE + FTEFC_MEMB_SIZE;

    uint32_t efc_infb_base = FTEFC_INFB_BASE;
    uint32_t efc_infb_limit = FTEFC_INFB_BASE + FTEFC_INFB_SIZE;

    if (remap == 2) {
        efc_memb_base -= FTREG_BASE_EFC;
        efc_memb_limit -= FTREG_BASE_EFC;

        efc_infb_base -= FTREG_BASE_EFC;
        efc_infb_limit -= FTREG_BASE_EFC;
    }

    if ((w_addr >= efc_memb_base) && (w_addr < efc_memb_limit)) {
        goto _efc_memb;
    } else if ((w_addr >= efc_infb_base) && (w_addr < efc_infb_limit)) {
        goto _efc_infb;
    }

    if (nr_words == 1) {
        pkt.do_cmd_word_write(w_addr, w_data[0]);

        ::printf("\n[0x%08x] <- 0x%08x ", w_addr, w_data[0]);

        r = pkt.send_out();
        if (r < 0) {
            ::printf("(failed %d)\n", r);
            goto _safe_exit;
        }

    } else {
        // normal path
        pkt.do_cmd_word_write(w_addr, w_data, nr_words);

        ::printf("\n[0x%08x] <- 0x%08x.~.~.~.~.~.~ ", w_addr, w_data[0]);

        r = pkt.send_out();
        if (r < 0) {
            ::printf("(failed %d)\n", r);
            goto _safe_exit;
        }
    }

    ::printf("(ok)\n");

    return (int)ISP_ERR_SUCCESS;

_efc_memb:

    {
        uint32_t page = (w_addr - efc_memb_base) / FTEFC_PAGE_SIZE;

        ::printf("\n[0x%08x] <- 0x%08x ... efc-memb-page)%d ", w_addr, w_data[0], page);

        // unlock the page for programming ...
        uint32_t page_base = efc.page_unlock(pkt, efc_memb_base, page, false);

        if (page_base == (uint32_t)-1) {
            ::printf("unlock failed (prog)\n");  ::fflush(stdout);
            r = (int)ISP_ERR_FAILED;
            goto _safe_exit;
        }

        ::usleep(VTSPISP_EFC_PROG_UNLOCK_DELAY);  // page-buffering delay

        // write-out the data ...
        pkt.do_cmd_word_write(w_addr, w_data, nr_words);

        if ((r = pkt.send_out()) < 0) {
            ::printf("programming failed (%d)\n", r);  ::fflush(stdout);
            goto _safe_exit;
        }

        // done flashing and re-lock the page
        if (efc.page_lock(pkt, page_base) < 0) {
            ::printf("lock failed (prog)\n");  ::fflush(stdout);
            r = (int)ISP_ERR_FAILED;
            goto _safe_exit;
        }

        ::usleep(VTSPISP_EFC_PROG_LOCK_DELAY);  // page write-back delay
    }

    ::printf("ok\n");  ::fflush(stdout);

    return (int)ISP_ERR_SUCCESS;

_efc_infb:

    {
        uint32_t page = (w_addr - efc_infb_base) / FTEFC_PAGE_SIZE;

        ::printf("\n[0x%08x] <- 0x%08x ... efc-infb-page)%d ", w_addr, w_data[0], page);

        // unlock the page for programming ...
        uint32_t page_base = efc.page_unlock(pkt, efc_infb_base, page, false);

        if (page_base == (uint32_t)-1) {
            ::printf("unlock failed (prog)\n");  ::fflush(stdout);
            r = (int)ISP_ERR_FAILED;
            goto _safe_exit;
        }

        ::usleep(VTSPISP_EFC_PROG_UNLOCK_DELAY);  // page-buffering delay

        // write-out the data ...
        pkt.do_cmd_word_write(w_addr, w_data, nr_words);

        if ((r = pkt.send_out()) < 0) {
            ::printf("programming failed (%d)\n", r);  ::fflush(stdout);
            goto _safe_exit;
        }

        // done flashing and re-lock the page
        if (efc.page_lock(pkt, page_base) < 0) {
            ::printf("lock failed (prog)\n");  ::fflush(stdout);
            r = (int)ISP_ERR_FAILED;
            goto _safe_exit;
        }

        ::usleep(VTSPISP_EFC_PROG_LOCK_DELAY);  // page write-back delay
    }

    ::printf("ok\n");  ::fflush(stdout);

    return (int)ISP_ERR_SUCCESS;

_safe_exit:

    return r;
}

int vtspisp::do_remap_get(uint32_t &remap)
{
    uint32_t r_addr = 0x54000020;

    vtspisp_packet pkt(_mpsse_spi);

    pkt.do_cmd_word_read(r_addr, 1);

    ::printf("\nreading current remap setting ... ");

    int r = pkt.send_out(false, 500);
    if (r < 0) {
        ::printf("(failed %d)\n", r);
        return r;
    }

    remap = pkt._data_in[7] & 0x0f;

    ::printf("done (remap = %d)\n", remap);

    return (int)ISP_ERR_SUCCESS;
}

int vtspisp::vtefc_init(uint32_t type)
{
    vtspisp_packet pkt(_mpsse_spi);

    pkt.do_vtefc_init(type);

    ::printf("\nConfig flash controller to type(%d) ... ", type);

    int r = pkt.send_out(false, 500);
    if (r < 0) {
        ::printf("(failed %d)\n", r);
        return r;
    }
    // TODO: ack?

    //if(pkt._data_in[0] != vtspisp_packet::VTSPISP_CMD_ACK) {
    if(pkt._data_in[1] != type) {
        ::printf("fail (result = %d, type = %d)\n", pkt._data_in[0], pkt._data_in[1]);
        return (int)ISP_ERR_FAILED;
    }

    ::printf("done (result = %d, type = %d)\n", pkt._data_in[0], pkt._data_in[1]);
    return (int)ISP_ERR_SUCCESS;
}

int vtspisp::do_bist(uint32_t bist_base, uint32_t bist_size, uint32_t pattern)
{
    return (int)ISP_ERR_SUCCESS;
}

int vtspisp::prog_eflash(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size)
{
    vtspisp_packet pkt(_mpsse_spi);
    ftefc efc;
    int r;

    uint32_t efcblk_base, efcblk_limit;

    if (infb) {
        efcblk_base = FTEFC_INFB_BASE;
        efcblk_limit = FTEFC_INFB_BASE + FTEFC_INFB_SIZE;
    } else {
        efcblk_base = FTEFC_MEMB_BASE;
        efcblk_limit = FTEFC_MEMB_BASE + FTEFC_MEMB_SIZE;
    }

    if (remap == 2) {
        efcblk_base -= FTREG_BASE_EFC;
        efcblk_limit -= FTREG_BASE_EFC;
    }

    uint32_t addr_b = ((uint32_t)efcblk_base + offset) & ~0x03;
    uint32_t addr_e = (addr_b + size + 3) & ~0x03;

    uint32_t page_b = (addr_b - efcblk_base) / FTEFC_PAGE_SIZE;
    uint32_t page_e = (addr_e - efcblk_base) / FTEFC_PAGE_SIZE;

    // programming ...
    ::printf("\nprogramming %s (0x%08x ~ 0x%08x size 0x%08x) ...\n\n", infb ? "infb" : "memb", addr_b, addr_e, addr_e - addr_b);  ::fflush(stdout);

    if (addr_e > efcblk_limit) {
        ::printf("error: range is out of valid eflash region (0x%08x ~ 0x%08x)!\n\n", (uint32_t)efcblk_base, efcblk_limit);  ::fflush(stdout);
        return (int)ISP_ERR_FAILED;
    }

    uint32_t addr_iter = addr_b;
    uint8_t *data_iter = (uint8_t *)data;

#if 1
    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {

        uint32_t p_off;
        uint32_t p_size;

        ::printf("%s [0x%08x] page)%d <- ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, p);  ::fflush(stdout);

        if (axisp_ctxt.erase_prog) {

            ::printf("erase ");  ::fflush(stdout);

            uint32_t page_base = efc.page_unlock(pkt, efcblk_base, p, true);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (erase)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            //::usleep(VTSPISP_EFC_ERASE_UNLOCK_DELAY);

            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (erase)\n");  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }

            ::usleep(VTSPISP_EFC_ERASE_LOCK_DELAY);

            ::printf("ok <- ");  ::fflush(stdout);

            // unlock the page for data-write ...
            page_base = efc.page_unlock(pkt, efcblk_base, p);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (prog)\n");  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }

            //::usleep(VTSPISP_EFC_WRONLY_UNLOCK_DELAY);

            p_off = addr_iter - page_base;
            p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);

            ::printf("(%d bytes) ", p_size);  ::fflush(stdout);

            // compose the packet (command) and send it out ...
            pkt.do_cmd_word_write(addr_iter, (uint32_t *)data_iter, p_size / 4);
            data_iter += p_size;

            if ((r = pkt.send_out()) < 0) {
                ::printf("programming failed (%d)\n", r);  ::fflush(stdout);
                goto _safe_exit;
            }

            ::usleep(VTSPISP_WORD_WRITE_DELAY(p_size));

            // done flashing and re-lock the page
            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (prog)\n");  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }

            ::usleep(VTSPISP_EFC_WRONLY_LOCK_DELAY);

        } else {

            // unlock the page for programming ...
            uint32_t page_base = efc.page_unlock(pkt, efcblk_base, p, false);
            //::usleep(100);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (prog)\n");  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }

            ::usleep(VTSPISP_EFC_PROG_UNLOCK_DELAY);

            p_off = addr_iter - page_base;
            p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);

            ::printf("(%d bytes) ", p_size);  ::fflush(stdout);

            // compose the packet (command) and send it out ...
            pkt.do_cmd_word_write(addr_iter, (uint32_t *)data_iter, p_size / 4);
            data_iter += p_size;

            if ((r = pkt.send_out()) < 0) {
                ::printf("programming failed (%d)\n", r);  ::fflush(stdout);
                goto _safe_exit;
            }

            ::usleep(VTSPISP_WORD_WRITE_DELAY(p_size));

            // done flashing and re-lock the page (requires 5ms in eflash prog command)
            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (prog)\n");  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }

            ::usleep(VTSPISP_EFC_PROG_LOCK_DELAY);
        }

        ::printf("ok");  ::fflush(stdout);

        addr_iter += p_size;
    }
#endif
#if 1
    // verification
    ::printf("\n\nverifying %s (0x%08x - 0x%08x size 0x%08x) ...\n\n", infb ? "infb" : "memb", addr_b, addr_e, addr_e - addr_b);  ::fflush(stdout);

    addr_iter = addr_b;
    data_iter = (uint8_t *)data;

    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {

        ::printf("%s [0x%08x] page)%d -> ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, p);  ::fflush(stdout);

        uint32_t page_base = FTEFC_PAGE_BASE(efcblk_base, p);

        uint32_t p_off = addr_iter - page_base;
        uint32_t p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);

        // compose the packet (read-back command) and send it out ...
        pkt.do_cmd_word_read(addr_iter, p_size / 4);

        if ((r = pkt.send_out(false, VTSPISP_WORD_READ_DELAY(p_size))) < 0) {
            ::printf("read-back failed (%d)!! \n", r);  ::fflush(stdout);
            goto _safe_exit;
        }

        ::printf("(%d bytes)", pkt._size_in - 4);  ::fflush(stdout);

        // verify the image ...
        for (uint32_t w = 0; w < (p_size / 4); ++w) {
            if (((uint32_t *)pkt._data_in)[w + 1] != ((uint32_t *)data_iter)[w]) {
                ::printf(" | off)0x%04x|0x%08x <-> image)0x%08x|0x%08x (mismatch)\n",
                    w * 4, ((uint32_t *)pkt._data_in)[w + 1], addr_iter - addr_b + w * 4, ((uint32_t *)data_iter)[w]);  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }
        }

        ::printf(" ok");  ::fflush(stdout);

        addr_iter += p_size;
        data_iter += p_size;
    }
#endif
    ::printf("\n");  ::fflush(stdout);

    //if (axisp_ctxt.reboot) {
    //    do_reboot();
    //}

_safe_exit:

    return r;
}

int vtspisp::prog_eflash_fast(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size)
{
    vtspisp_packet pkt(_mpsse_spi);
    ftefc efc;
    int r;

    uint32_t efcblk_base, efcblk_limit;

    if (infb) {
        efcblk_base = FTEFC_INFB_BASE;
        efcblk_limit = FTEFC_INFB_BASE + FTEFC_INFB_SIZE;
    } else {
        efcblk_base = FTEFC_MEMB_BASE;
        efcblk_limit = FTEFC_MEMB_BASE + FTEFC_MEMB_SIZE;
    }

    if (remap == 2) {
        efcblk_base -= FTREG_BASE_EFC;
        efcblk_limit -= FTREG_BASE_EFC;
    }

    uint32_t addr_b,addr_e,page_b,page_e;
#define VTREG_BASE_EFC 0x04000000

    if (infb) {
        addr_b = 508 * 1024;
        addr_e = 510 * 1024;

        page_b = 508 * 4;
        page_e = 510 * 4;
    } else {
        addr_b = 0x0;
        addr_e = 506 * 1024;

        page_b = 0;
        page_e = 506 * 4;
    }

    // programming ...
    ::printf("\nprogramming %s (0x%08x ~ 0x%08x size 0x%08x) ...\n\n", infb ? "infb" : "memb", addr_b, addr_e, addr_e - addr_b);  ::fflush(stdout);
/*
    if (addr_e > efcblk_limit) {
        ::printf("error: range is out of valid eflash region (0x%08x ~ 0x%08x)!\n\n", (uint32_t)efcblk_base, efcblk_limit);  ::fflush(stdout);
        return (int)ISP_ERR_FAILED;
    }
*/
    uint32_t addr_iter = addr_b;
    uint8_t *data_iter = (uint8_t *)data;

    if (infb) {
        addr_iter = addr_b;
    } else {
        addr_iter = 0;
    }

#if 1
//    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {
    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {

        uint32_t p_size = 256;

        ::printf("%s [0x%08x] page)%d <- ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, p);  ::fflush(stdout);

        if (axisp_ctxt.erase_prog) {
            ::printf("erase program not supported yet !!!\n");  ::fflush(stdout);
        } else {

            // read one page of image data ...
            ::memcpy(&pkt._data_out[8], data_iter, p_size);
            data_iter += p_size;

            // compose the packet (command) and send it out ...
            pkt.do_cmd_page_program(addr_iter, NULL, p_size / 4, false);

            if (pkt.send_out() < 0) {
                ::printf("programming failed\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTSPISP_PAGE_PRGROAM_DELAY(p_size));
        }

        ::printf("ok");  ::fflush(stdout);

        addr_iter += p_size;
    }
#endif
#if 1
    // verification
    ::printf("\n\nverifying %s (0x%08x - 0x%08x size 0x%08x) ...\n\n", infb ? "infb" : "memb", addr_b, addr_e, addr_e - addr_b);  ::fflush(stdout);

    addr_iter = addr_b;
    data_iter = (uint8_t *)data;

    if (infb) {
        addr_iter = addr_b;
    } else {
        addr_iter = 0;
    }

    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {

        uint32_t tmp_checksum = 0;
        uint32_t p_size = 256;

        ::printf("%s [0x%08x] page)%d -> ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, p);  ::fflush(stdout);

        pkt.do_cmd_read_checksum(addr_iter + VTREG_BASE_EFC, p_size / 4);

        if (pkt.send_out(false, 1000) < 0) {

            ::printf("read-back failed !! \n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        // verify the image ...
        for (uint32_t w = 0; w < (p_size / 4); ++w) {
            tmp_checksum += ((uint32_t *)data_iter)[w];
        }
        ::printf("tmp_checksum = 0x%x\n",tmp_checksum );
        ::printf("checksum = 0x%x\n",((uint32_t *)pkt._data_in)[1] );
        if(((uint32_t *)pkt._data_in)[1] != tmp_checksum){
            ::printf("(mismatch)\n"); ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }
        addr_iter += p_size;
        data_iter += p_size;
    }
#endif
    ::printf("\n");  ::fflush(stdout);

    //if (axisp_ctxt.reboot) {
    //    do_reboot();
    //}

_safe_exit:

    return r;
}

int vtspisp::prog_eflash_sum(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size)
{
    vtspisp_packet pkt(_mpsse_spi);
    ftefc efc;
    int r;

    uint32_t efcblk_base, efcblk_limit;

    if (infb) {
        efcblk_base = FTEFC_INFB_BASE;
        efcblk_limit = FTEFC_INFB_BASE + FTEFC_INFB_SIZE;
    } else {
        efcblk_base = FTEFC_MEMB_BASE;
        efcblk_limit = FTEFC_MEMB_BASE + FTEFC_MEMB_SIZE;
    }

    if (remap == 2) {
        efcblk_base -= FTREG_BASE_EFC;
        efcblk_limit -= FTREG_BASE_EFC;
    }

    uint32_t addr_b = ((uint32_t)efcblk_base + offset) & ~0x03;
    uint32_t addr_e = (addr_b + size + 3) & ~0x03;

    uint32_t page_b = (addr_b - efcblk_base) / FTEFC_PAGE_SIZE;
    uint32_t page_e = (addr_e - efcblk_base) / FTEFC_PAGE_SIZE;

    // programming ...
    ::printf("\nprogramming %s (0x%08x ~ 0x%08x size 0x%08x) ...\n\n", infb ? "infb" : "memb", addr_b, addr_e, addr_e - addr_b);  ::fflush(stdout);

    if (addr_e > efcblk_limit) {
        ::printf("error: range is out of valid eflash region (0x%08x ~ 0x%08x)!\n\n", (uint32_t)efcblk_base, efcblk_limit);  ::fflush(stdout);
        return (int)ISP_ERR_FAILED;
    }

    uint32_t addr_iter = addr_b;
    uint8_t *data_iter = (uint8_t *)data;

#if 1
    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {

        uint32_t p_off;
        uint32_t p_size;

        ::printf("%s [0x%08x] page)%d <- ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, p);  ::fflush(stdout);

        if (axisp_ctxt.erase_prog) {

            ::printf("erase ");  ::fflush(stdout);

            uint32_t page_base = efc.page_unlock(pkt, efcblk_base, p, true);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (erase)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            //::usleep(VTSPISP_EFC_ERASE_UNLOCK_DELAY);

            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (erase)\n");  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }

            ::usleep(VTSPISP_EFC_ERASE_LOCK_DELAY);

            ::printf("ok <- ");  ::fflush(stdout);

            // unlock the page for data-write ...
            page_base = efc.page_unlock(pkt, efcblk_base, p);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (prog)\n");  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }

            //::usleep(VTSPISP_EFC_WRONLY_UNLOCK_DELAY);

            p_off = addr_iter - page_base;
            p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);

            ::printf("(%d bytes) ", p_size);  ::fflush(stdout);

            // compose the packet (command) and send it out ...
            pkt.do_cmd_word_write(addr_iter, (uint32_t *)data_iter, p_size / 4);
            data_iter += p_size;

            if ((r = pkt.send_out()) < 0) {
                ::printf("programming failed (%d)\n", r);  ::fflush(stdout);
                goto _safe_exit;
            }

            ::usleep(VTSPISP_WORD_WRITE_DELAY(p_size));

            // done flashing and re-lock the page
            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (prog)\n");  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }

            ::usleep(VTSPISP_EFC_WRONLY_LOCK_DELAY);

        } else {

            // unlock the page for programming ...
            uint32_t page_base = efc.page_unlock(pkt, efcblk_base, p, false);
            //::usleep(100);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (prog)\n");  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }

            ::usleep(VTSPISP_EFC_PROG_UNLOCK_DELAY);

            p_off = addr_iter - page_base;
            p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);

            ::printf("(%d bytes) ", p_size);  ::fflush(stdout);

            // compose the packet (command) and send it out ...
            pkt.do_cmd_word_write(addr_iter, (uint32_t *)data_iter, p_size / 4);
            data_iter += p_size;

            if ((r = pkt.send_out()) < 0) {
                ::printf("programming failed (%d)\n", r);  ::fflush(stdout);
                goto _safe_exit;
            }

            ::usleep(VTSPISP_WORD_WRITE_DELAY(p_size));

            // done flashing and re-lock the page (requires 5ms in eflash prog command)
            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (prog)\n");  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }

            ::usleep(VTSPISP_EFC_PROG_LOCK_DELAY);
        }

        ::printf("ok");  ::fflush(stdout);

        addr_iter += p_size;
    }
#endif
#if 1
    // verification
    ::printf("\n\nverifying %s (0x%08x - 0x%08x size 0x%08x) ...\n\n", infb ? "infb" : "memb", addr_b, addr_e, addr_e - addr_b);  ::fflush(stdout);

    addr_iter = addr_b;
    data_iter = (uint8_t *)data;

    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {

        ::printf("%s [0x%08x] page)%d -> ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, p);  ::fflush(stdout);

        uint32_t tmp_checksum = 0;
        uint32_t page_base = FTEFC_PAGE_BASE(efcblk_base, p);

        uint32_t p_off = addr_iter - page_base;
        uint32_t p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);

        // compose the packet (read-back command) and send it out ...
        pkt.do_cmd_read_checksum(addr_iter, p_size / 4);

        if ((r = pkt.send_out(false, VTSPISP_WORD_READ_DELAY(p_size))) < 0) {
            ::printf("read-back failed (%d)!! \n", r);  ::fflush(stdout);
            goto _safe_exit;
        }

        ::printf("(%d bytes)", pkt._size_in - 4);  ::fflush(stdout);

        // verify the image ...
        for (uint32_t w = 0; w < (p_size / 4); ++w) {
            tmp_checksum += ((uint32_t *)data_iter)[w];
        }
        
        if (((uint32_t *)pkt._data_in)[1] != tmp_checksum)
        {
            ::printf(" | off)0x%08x <-> image)0x%08x (mismatch)\n",
                    ((uint32_t *)pkt._data_in)[1], tmp_checksum); ::fflush(stdout);
            r = (int)ISP_ERR_FAILED;
            goto _safe_exit;
        }

        ::printf(" ok");  ::fflush(stdout);

        addr_iter += p_size;
        data_iter += p_size;
    }
#endif
    ::printf("\n");  ::fflush(stdout);

    //if (axisp_ctxt.reboot) {
    //    do_reboot();
    //}

_safe_exit:

    return r;
}

int vtspisp::prog_iram(uint32_t base, void *data, uint32_t size)
{
    vtspisp_packet pkt(_mpsse_spi);

    int r;

    uint32_t addr_b = base;
    uint32_t addr_e = base + size;

    uint32_t nr_writes = ((addr_e - addr_b) + (vtspisp_packet::VTSPISP_SPI_PAGE_SIZE - 1)) / vtspisp_packet::VTSPISP_SPI_PAGE_SIZE;

    // programming ...
    ::printf("\nprogramming iram (0x%08x ~ 0x%08x size 0x%08x) ...\n\n", addr_b, addr_e, size);  ::fflush(stdout);

    uint32_t addr_iter = addr_b;
    uint8_t *data_iter = (uint8_t *)data;

    for (uint32_t i = 0; i < nr_writes; ++i) {

        ::printf("%s [0x%08x] page)%d <- ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, i);  ::fflush(stdout);

        uint32_t p_size = min(vtspisp_packet::VTSPISP_SPI_PAGE_SIZE, addr_e - addr_iter);

        ::printf("(%d bytes) ", p_size);  ::fflush(stdout);

        // compose the packet (command) and send it out ...
        pkt.do_cmd_word_write(addr_iter, (uint32_t *)data_iter, p_size / 4);
        data_iter += p_size;

        if ((r = pkt.send_out()) < 0) {
            ::printf("programming failed (%d)\n", r);  ::fflush(stdout);
            goto _safe_exit;
        }

        ::printf("ok");  ::fflush(stdout);

        addr_iter += p_size;

        ::usleep(VTSPISP_WORD_WRITE_DELAY(p_size));
    }

    // verification
    ::printf("\n\nverifying iram (0x%08x - 0x%08x size 0x%08x) ...\n\n", addr_b, addr_e, addr_e - addr_b);  ::fflush(stdout);

    addr_iter = addr_b;
    data_iter = (uint8_t *)data;

    for (uint32_t i = 0; i < nr_writes; ++i) {

        ::printf("%s [0x%08x] burst)%d -> ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, i);  ::fflush(stdout);

        uint32_t p_size = min(vtspisp_packet::VTSPISP_SPI_PAGE_SIZE, addr_e - addr_iter);

        // compose the packet (read-back command) and send it out ...
        pkt.do_cmd_word_read(addr_iter, p_size / 4);

        if ((r = pkt.send_out(false, VTSPISP_WORD_READ_DELAY(p_size))) < 0) {
            ::printf("read-back failed (%d)!! \n", r);  ::fflush(stdout);
            goto _safe_exit;
        }

        ::printf("(%d bytes)", pkt._size_in - 5);  ::fflush(stdout);

        // verify the image ...
        for (uint32_t w = 0; w < (p_size / 4); ++w) {
            if (((uint32_t *)pkt._data_in)[w + 1] != ((uint32_t *)data_iter)[w]) {
                ::printf(" | off)0x%04x|0x%08x <-> image)0x%08x|0x%08x (mismatch)\n",
                    w * 4, ((uint32_t *)pkt._data_in)[w + 1], addr_iter - addr_b + w * 4, ((uint32_t *)data_iter)[w]);  ::fflush(stdout);
                r = (int)ISP_ERR_FAILED;
                goto _safe_exit;
            }
        }

        ::printf(" ok");  ::fflush(stdout);

        addr_iter += p_size;
        data_iter += p_size;

        //::usleep(0x1000);
    }

    ::printf("\n");  ::fflush(stdout);

_safe_exit:

    return r;
}

int vtspisp::do_eflash_isp(bin_object &bin_obj)
{
    struct image_info {

        uint32_t    magic;
        uint32_t    nr_firmware;
        uint32_t    boostrap;
        uint32_t    bbp_reloc;

        uint32_t    infi;               // info block start location in the eflash memory region
        uint32_t    einfi;              // info block end location in the eflash memory region
        uint32_t    infi_size;          // info block size in the firmware image
        uint32_t    image_size;         // the total size of the firmware image (including infi)

        uint32_t    info_h0;            // location of info header of firmware image#0
        uint32_t    info_h1;            // location of info header of firmware image#1
        uint32_t    reserved_10;
        uint32_t    reserved_11;

    } infi;

    // read image information header ...
    if (bin_obj.read(&infi, 0x30) < 0) {
        ::printf("\n[err] image-read failed!\n");
        return (int)ISP_ERR_FAILED;
    }

    if (infi.magic != 0x6970676d) {
        ::printf("\n[err] unknown image-format!\n");
        return (int)ISP_ERR_FAILED;
    }

    uint32_t remap = 0;

    int r = do_remap_get(remap);
    if (r < 0)
        return r;

    r = prog_eflash(false, remap, 0, bin_obj.offset(infi.infi_size, true), infi.image_size - infi.infi_size);
    if (r < 0)
        return r;

    return prog_eflash(true, remap, 0, bin_obj.offset(0, true), infi.infi_size);
}

int vtspisp::prog_eflash_raw(bin_object &bin_obj)
{
	vtspisp_packet pkt(_mpsse_spi);
    ftefc        efc;

	::printf("\nimage_size %d\n",bin_obj.size());
	
#define VTREG_BASE_EFC 0x04000000
#define PAGE_SIZE		256

	int r = 0;

    uint32_t page_b,page_e;
	
    uint32_t addr_iter;
    uint32_t size = bin_obj.size();
	int32_t read_size;	

	int32_t i = 0;
	
	bin_obj.offset(0, true);	

	page_b = 0;
	page_e = (size & 0xffffff00) + 1;

    addr_iter = VTREG_BASE_EFC;



	usleep(65535);
	usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);
	usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);
	usleep(65535);
	usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);
	usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);
		usleep(65535);
	usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);
	usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);usleep(65535);


    for (uint32_t p = page_b; (p <= page_e); ++p) {
       
        // read one page of image data ...
		read_size = bin_obj.read(&pkt._data_out[8], PAGE_SIZE);

		::printf("read_size %d\n",  read_size);

		if (read_size > 0) {
			for (i=0; i<read_size; i++) {
				::printf(" %x", pkt._data_out[8+i]);	
			}

			// compose the packet (command) and send it out ...
	        pkt.do_cmd_page_program(addr_iter, (uint32_t *)&pkt._data_out[8], PAGE_SIZE / 4, false);

			usleep(100000);
			
	        if (pkt.send_out() < 0) {
	            ::printf("Fprogramming failed\n");  ::fflush(stdout);
	            r = -1;
	            goto _safe_exit;
	        }

	        ::printf("ok");  ::fflush(stdout);
		
	        addr_iter += read_size;
			
		} else {
			break;
		}
    }

	_safe_exit:
	
	if (r < 0) {
		// try to capture exception dump messages, if any ...
	//	if (pkt.get_raw() > 0) 
			{
			::printf("!!!!!!!\n\n");
		//	print_raw(pkt);
		}
	}

    return r;
}


int vtspisp::do_eflash_fast_isp(bin_object &bin_obj)
{

#if 1

  int r;

    r = vtefc_init(2);
    if (r < 0)
        return r;

	sleep(1);
	
	/* chenying test */	
	return prog_eflash_raw(bin_obj);

	
	return 1;


#else
    struct image_info {

        uint32_t    magic;
        uint32_t    nr_firmware;
        uint32_t    boostrap;
        uint32_t    bbp_reloc;

        uint32_t    infi;               // info block start location in the eflash memory region
        uint32_t    einfi;              // info block end location in the eflash memory region
        uint32_t    infi_size;          // info block size in the firmware image
        uint32_t    image_size;         // the total size of the firmware image (including infi)

        uint32_t    info_h0;            // location of info header of firmware image#0
        uint32_t    info_h1;            // location of info header of firmware image#1
        uint32_t    reserved_10;
        uint32_t    reserved_11;

    } infi;

    // read image information header ...
    if (bin_obj.read(&infi, 0x30) < 0) {
        ::printf("\n[err] image-read failed!\n");
        return (int)ISP_ERR_FAILED;
    }

    if (infi.magic != 0x6970676d) {
        ::printf("\n[err] unknown image-format!\n");
        return (int)ISP_ERR_FAILED;
    }

    uint32_t remap = 0;

    int r = do_remap_get(remap);
    if (r < 0)
        return r;

    r = vtefc_init(2);
    if (r < 0)
        return r;

    // chip erase tooks about 650ms
    ::usleep(800*1000);

    // program info block 1st
    if (prog_eflash_fast(true, remap, 0, bin_obj.offset(0, true), infi.infi_size) < 0)
        return -1;

    return prog_eflash_fast(false, remap, 0, bin_obj.offset(infi.infi_size, true), infi.image_size - infi.infi_size);
#endif
	
}

int vtspisp::do_eflash_sum_isp(bin_object &bin_obj)
{
    struct image_info {

        uint32_t    magic;
        uint32_t    nr_firmware;
        uint32_t    boostrap;
        uint32_t    bbp_reloc;

        uint32_t    infi;               // info block start location in the eflash memory region
        uint32_t    einfi;              // info block end location in the eflash memory region
        uint32_t    infi_size;          // info block size in the firmware image
        uint32_t    image_size;         // the total size of the firmware image (including infi)

        uint32_t    info_h0;            // location of info header of firmware image#0
        uint32_t    info_h1;            // location of info header of firmware image#1
        uint32_t    reserved_10;
        uint32_t    reserved_11;

    } infi;

    // read image information header ...
    if (bin_obj.read(&infi, 0x30) < 0) {
        ::printf("\n[err] image-read failed!\n");
        return (int)ISP_ERR_FAILED;
    }

    if (infi.magic != 0x6970676d) {
        ::printf("\n[err] unknown image-format!\n");
        return (int)ISP_ERR_FAILED;
    }

    uint32_t remap = 0;

    int r = do_remap_get(remap);
    if (r < 0)
        return r;

    r = prog_eflash_sum(false, remap, 0, bin_obj.offset(infi.infi_size, true), infi.image_size - infi.infi_size);
    if (r < 0)
        return r;

    return prog_eflash_sum(true, remap, 0, bin_obj.offset(0, true), infi.infi_size);
}

int vtspisp::do_raw_isp(bin_object &bin_obj, uint32_t addr)
{
    uint32_t remap = 0;

    int r = do_remap_get(remap);
    if (r < 0)
        return r;

    uint32_t efc_memb_base = FTEFC_MEMB_BASE;
    uint32_t efc_memb_limit = FTEFC_MEMB_BASE + FTEFC_MEMB_SIZE;

    uint32_t efc_infb_base = FTEFC_INFB_BASE;
    uint32_t efc_infb_limit = FTEFC_INFB_BASE + FTEFC_INFB_SIZE;

    if (remap == 2) {
        efc_memb_base -= FTREG_BASE_EFC;
        efc_memb_limit -= FTREG_BASE_EFC;

        efc_infb_base -= FTREG_BASE_EFC;
        efc_infb_limit -= FTREG_BASE_EFC;
    }

    if ((addr >= efc_memb_base) && (addr < efc_memb_limit)) {
        return prog_eflash(false, remap, 0, bin_obj.offset(0, true), bin_obj.size());
    } else if ((addr >= efc_infb_base) && (addr < efc_infb_limit)) {
        return prog_eflash(true, remap, 0, bin_obj.offset(0, true), bin_obj.size());
    }

    return prog_iram(addr, bin_obj.offset(0, true), bin_obj.size());
}

int vtspisp::do_isp()
{
    if (axisp_ctxt.isp_nr_args < 1) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    const char *sz_image = axisp_ctxt.isp_args[1];

    if (sz_image[0] == 0) {
        ::printf("\n[err] invlaid image file name!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    if (::access(sz_image, R_OK) != 0) {
        ::printf("\n[err] failed to access image file!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    bool raw_isp = false;
    uint32_t raw_isp_addr = 0;

    if (axisp_ctxt.isp_nr_args >= 2) {

        const char *sz_addr = axisp_ctxt.isp_args[2];

        if (::axisp_context::validate_hex(sz_addr)) {
            ::printf("\n[err] invalid isp target address!\n\n");
            return (int)ISP_ERR_ARGUMENT;
        }

        raw_isp_addr = ::strtoul(sz_addr, 0, 16);

        raw_isp = true;
    }

    bin_object bin_obj;

    int r = bin_obj.open(sz_image);
    if (r < 0) {
        ::printf("\nfailed to open binary image !!\n\n");
        return (int)ISP_ERR_FAILED;
    }

    if (raw_isp) {
        r = do_raw_isp(bin_obj, raw_isp_addr);
    } else {
        r = do_eflash_isp(bin_obj);
    }

    bin_obj.close();

    return r;
}

int vtspisp::do_fastisp()
{
    if (axisp_ctxt.isp_nr_args < 1) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    const char *sz_image = axisp_ctxt.isp_args[1];

    if (sz_image[0] == 0) {
        ::printf("\n[err] invlaid image file name!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    if (::access(sz_image, R_OK) != 0) {
        ::printf("\n[err] failed to access image file!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    bool raw_isp = false;
    uint32_t raw_isp_addr = 0;

    if (axisp_ctxt.isp_nr_args >= 2) {

        const char *sz_addr = axisp_ctxt.isp_args[2];

        if (::axisp_context::validate_hex(sz_addr)) {
            ::printf("\n[err] invalid isp target address!\n\n");
            return (int)ISP_ERR_ARGUMENT;
        }

        raw_isp_addr = ::strtoul(sz_addr, 0, 16);

        raw_isp = true;
    }

    bin_object bin_obj;

    int r = bin_obj.open(sz_image);
    if (r < 0) {
        ::printf("\nfailed to open binary image !!\n\n");
        return (int)ISP_ERR_FAILED;
    }

    if (raw_isp) {
        r = do_raw_isp(bin_obj, raw_isp_addr);
    } else {
        r = do_eflash_fast_isp(bin_obj);
    }

    bin_obj.close();

    return r;
}

int vtspisp::do_sumisp()
{
    if (axisp_ctxt.isp_nr_args < 1) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    const char *sz_image = axisp_ctxt.isp_args[1];

    if (sz_image[0] == 0) {
        ::printf("\n[err] invlaid image file name!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    if (::access(sz_image, R_OK) != 0) {
        ::printf("\n[err] failed to access image file!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    bool raw_isp = false;
    uint32_t raw_isp_addr = 0;

    if (axisp_ctxt.isp_nr_args >= 2) {

        const char *sz_addr = axisp_ctxt.isp_args[2];

        if (::axisp_context::validate_hex(sz_addr)) {
            ::printf("\n[err] invalid isp target address!\n\n");
            return (int)ISP_ERR_ARGUMENT;
        }

        raw_isp_addr = ::strtoul(sz_addr, 0, 16);

        raw_isp = true;
    }

    bin_object bin_obj;

    int r = bin_obj.open(sz_image);
    if (r < 0) {
        ::printf("\nfailed to open binary image !!\n\n");
        return (int)ISP_ERR_FAILED;
    }

    if (raw_isp) {
        r = do_raw_isp(bin_obj, raw_isp_addr);
    } else {
        r = do_eflash_sum_isp(bin_obj);
    }

    bin_obj.close();

    return r;
}

int vtspisp::do_reboot()
{
    if (axisp_ctxt.isp_nr_args < 1) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    const char *sz_remap = axisp_ctxt.isp_args[1];

    if (::axisp_context::validate_dec(sz_remap)) {
        ::printf("\n[err] invalid remap value!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    int r = 0;
    uint32_t remap = ::strtoul(sz_remap, 0, 10);

    vtspisp_packet pkt(_mpsse_spi);

    if (remap > 2) {

        if (remap != 9) {
            ::printf("\n[err] invalid remap value!\n\n");
            return (int)ISP_ERR_FAILED;
        }

        // [2015-08-24]
        //
        // Keil/IAR support of FA606TE will always download debug code to address 0x00000000.
        // - write a valid instruction (loops itself) at the iRAM bootstrap address
        //   and then remap/reboot into iRAM so that Keil/IAR will be happy on the prepared
        //   target state.
        //
        uint32_t w_addr = 0x20000000;  // iRAM
        uint32_t w_data = 0xeafffffe;  // b 0

        pkt.do_cmd_word_write(w_addr, &w_data, 1);

        ::printf("\n[0x%08x] <- 0x%08x ", w_addr, w_data);

        r = pkt.send_out();
        if (r < 0) {
            ::printf("(failed %d)\n", r);
            return r;
        }

        ::printf("(ok)\n");
    }

    uint32_t reg_addr = 0x54000020;  // SCU::PWR_MOD
    uint32_t reg_val  = 0x00000080;  // reset

    reg_val |= ((remap & 0x0f) << 24);

    pkt.do_cmd_word_write(reg_addr, &reg_val, 1);

    ::printf("[0x%08x] <- 0x%08x ", reg_addr, reg_val);

    // ignore ack-back messages since it may not be available after issuing the reboot request
    r = pkt.send_out(false);
    if (r < 0) {
        ::printf("(failed)\n");
        return r;
    }

    ::printf("(ok)\n");

    return (int)ISP_ERR_SUCCESS;
}

int vtspisp::do_cli_cmd()
{
    return 0;
}

int vtspisp::do_ping()
{
    vtspisp_packet pkt(_mpsse_spi);

    // mo: 0f 1f 2f 3f
    // so: 6d 67 70 69 ('m' 'g' 'p' 'i')

    pkt.do_cmd_ping();

    ::printf("ping ->");

    int r = pkt.send_out();
    if (r < 0) {
        ::printf("failed (%d) !!\n", r);
        //::printf("ack-pkt status-cmd)0x%02x-0x%02x size_in)0x%04x\n", (uint32_t)pkt._data_in[0], (uint32_t)pkt._data_in[1], pkt._size_in);
        return r;
    }

    //if (pkt._data_in[1] != (vtspisp_packet::VTSPISP_CMD_ACK + 1)) {
    if ((pkt._data_in[1] != 'g') || (pkt._data_in[2] != 'p') || (pkt._data_in[3] != 'i')) {
        ::printf("failed !! (acked-data: %02x %02x %02x %02x)\n", pkt._data_in[0], pkt._data_in[1], pkt._data_in[2], pkt._data_in[3]);
        return (int)ISP_ERR_PROTOCOL;
    } else if (pkt._data_in[0] != 'm') {
        ::printf("acked with bad first byte !! (acked-data: %02x %02x %02x %02x)\n", pkt._data_in[0], pkt._data_in[1], pkt._data_in[2], pkt._data_in[3]);
        return (int)ISP_ERR_SUCCESS;
    }
	
    ::printf("acked (acked-data: %02x %02x %02x %02x)\n", pkt._data_in[0], pkt._data_in[1], pkt._data_in[2], pkt._data_in[3]);

    return (int)ISP_ERR_SUCCESS;
}

int vtspisp::do_break()
{
    return (int)ISP_ERR_SUCCESS;
}

int vtspisp::do_setup()
{
    if (axisp_ctxt.isp_nr_args < 2) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    const char *sz_index = axisp_ctxt.isp_args[1];
    const char *sz_value = axisp_ctxt.isp_args[2];

    if (::axisp_context::validate_dec(sz_index)) {
        ::printf("\n[err] invalid setting index!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    if (::axisp_context::validate_hex(sz_value)) {
        ::printf("\n[err] invalid setting value!\n\n");
        return (int)ISP_ERR_ARGUMENT;
    }

    uint32_t s_index = ::strtoul(sz_index, 0, 10);
    uint32_t s_value = ::strtoul(sz_value, 0, 16);

    vtspisp_packet pkt(_mpsse_spi);

    // mo: 88 88 index[7:0] index[15:8] value[31:0]
    // so: n/a

    pkt.do_cmd_setup(s_index, s_value);

    ::printf("setup <- index)%d value)0x%08x ... ", s_index, s_value);

    int r = pkt.send_out();
    if (r < 0) {
        ::printf("failed (%d) !!\n", r);
        return r;
    }

    ::printf("done\n");

    return (int)ISP_ERR_SUCCESS;
}