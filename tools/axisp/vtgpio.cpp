
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

#include "vtgpio.h"

static struct mpsse_context *ftdi_spi_open(int vid, int pid, enum modes mode, int freq, int endianess, int interface, const char *description, const char *serial)
{
    int status = 0;
    struct mpsse_context *mpsse = NULL;
    int index = 0;

    if (freq > 2000000)
        freq = 2000000;

    freq &= ~0x7ffff;
    if (freq < 400000)
        freq = 400000;

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
                                ftdi_usb_purge_buffers(&mpsse->ftdi);
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

void vtprobe_packet::do_cmd_base_reg_in()
{
    _data_out[0] = (uint8_t)VTPROBE_CMD_BASE_REG_IN;

    _size_out = 1;
    _size_in = 4;
}

void vtprobe_packet::do_cmd_base_reg_out(uint32_t base_addr)
{
    _data_out[0] = (uint8_t)VTPROBE_CMD_BASE_REG_OUT;
    _data_out[1] = (uint8_t)(base_addr >> 24);
    _data_out[2] = (uint8_t)(base_addr >> 16);
    _data_out[3] = (uint8_t)(base_addr >> 8);
    _data_out[4] = (uint8_t)base_addr;

    _size_out = 5;
    _size_in = 0;
}

void vtprobe_packet::do_cmd_delay_reg_in()
{
    _data_out[0] = (uint8_t)VTPROBE_CMD_STATUS_REG_IN;

    _size_out = 1;
    _size_in = 1;
}

void vtprobe_packet::do_cmd_delay_reg_out(uint32_t delay)
{
    delay = (delay + 7) / 8;
    delay *= 8;

    _data_out[0] = (uint8_t)VTPROBE_CMD_STATUS_REG_OUT;
    _data_out[1] = (uint8_t)((delay - 1) & 0x1f);

    _size_out = 2;
    _size_in = 0;
}

void vtprobe_packet::do_cmd_word_in(uint32_t addr, uint32_t delay)
{
    _data_out[1] = (uint8_t)(addr >> 24);
    _data_out[2] = (uint8_t)(addr >> 16);
    _data_out[3] = (uint8_t)(addr >> 8);
    _data_out[4] = (uint8_t)addr;

    if (delay == 0)
        _data_out[0] = (uint8_t)VTPROBE_CMD_WORD_IN;
    else
        _data_out[0] = (uint8_t)VTPROBE_CMD_WORD_IN_DELAY;

    _size_out = 5;

    while (delay > 8) {
        _data_out[_size_out] = 0;
        ++_size_out;
        delay -= 4;
    }

    if (delay > 0) {
        _data_out[_size_out] = 0;
        ++_size_out;
    }

    _size_in = 4;
}

void vtprobe_packet::do_cmd_word_in_offset(uint32_t offset, uint32_t delay)
{
    _data_out[1] = (uint8_t)offset;

    if (delay == 0)
        _data_out[0] = (uint8_t)VTPROBE_CMD_WORD_IN_OFFSET;
    else
        _data_out[0] = (uint8_t)VTPROBE_CMD_WORD_IN_OFFSET_DELAY;

    _size_out = 2;

    while (delay > 8) {
        _data_out[_size_out] = 0;
        ++_size_out;
        delay -= 4;
    }

    if (delay > 0) {
        _data_out[_size_out] = 0;
        ++_size_out;
    }

    _size_in = 4;
}

void vtprobe_packet::do_cmd_word_out(uint32_t addr, uint32_t data)
{
    _data_out[0] = (uint8_t)VTPROBE_CMD_WORD_OUT;

    _data_out[1] = (uint8_t)(addr >> 24);
    _data_out[2] = (uint8_t)(addr >> 16);
    _data_out[3] = (uint8_t)(addr >> 8);
    _data_out[4] = (uint8_t)addr;

    _data_out[5] = (uint8_t)(data >> 24);
    _data_out[6] = (uint8_t)(data >> 16);
    _data_out[7] = (uint8_t)(data >> 8);
    _data_out[8] = (uint8_t)data;

#if 0
    // hw debug
    _data_out[9] = (uint8_t)VTPROBE_CMD_WORD_OUT;

    _data_out[10] = (uint8_t)(addr >> 24);
    _data_out[11] = (uint8_t)(addr >> 16);
    _data_out[12] = (uint8_t)(addr >> 8);
    _data_out[13] = (uint8_t)(addr + 4);

    _data_out[14] = (uint8_t)(data >> 24);
    _data_out[15] = (uint8_t)(data >> 16);
    _data_out[16] = (uint8_t)(data >> 8);
    _data_out[17] = (uint8_t)data;

    _size_out = 18;
#endif

    _size_out = 9;
    _size_in = 0;
}

void vtprobe_packet::do_cmd_word_out_offset(uint32_t offset, uint32_t data)
{
    _data_out[0] = (uint8_t)VTPROBE_CMD_WORD_OUT_OFFSET;
    _data_out[1] = (uint8_t)offset;

    _data_out[2] = (uint8_t)(data >> 24);
    _data_out[3] = (uint8_t)(data >> 16);
    _data_out[4] = (uint8_t)(data >> 8);
    _data_out[5] = (uint8_t)data;

    _size_out = 6;
    _size_in = 0;
}

void vtprobe_packet::do_cmd_hword_in(uint32_t addr, uint32_t delay)
{
    _data_out[1] = (uint8_t)(addr >> 24);
    _data_out[2] = (uint8_t)(addr >> 16);
    _data_out[3] = (uint8_t)(addr >> 8);
    _data_out[4] = (uint8_t)addr;

    if (delay == 0)
        _data_out[0] = (uint8_t)VTPROBE_CMD_HALF_IN;
    else
        _data_out[0] = (uint8_t)VTPROBE_CMD_HALF_IN_DELAY;

    _size_out = 5;

    while (delay > 8) {
        _data_out[_size_out] = 0;
        ++_size_out;
        delay -= 4;
    }

    if (delay > 0) {
        _data_out[_size_out] = 0;
        ++_size_out;
    }

    _size_in = 2;
}

void vtprobe_packet::do_cmd_hword_in_offset(uint32_t offset, uint32_t delay)
{
    _data_out[1] = (uint8_t)offset;

    if (delay == 0)
        _data_out[0] = (uint8_t)VTPROBE_CMD_HALF_IN_OFFSET;
    else
        _data_out[0] = (uint8_t)VTPROBE_CMD_HALF_IN_OFFSET_DELAY;

    _size_out = 2;

    while (delay > 8) {
        _data_out[_size_out] = 0;
        ++_size_out;
        delay -= 4;
    }

    if (delay > 0) {
        _data_out[_size_out] = 0;
        ++_size_out;
    }

    _size_in = 2;
}

void vtprobe_packet::do_cmd_hword_out(uint32_t addr, uint32_t data)
{
    _data_out[0] = (uint8_t)VTPROBE_CMD_HALF_OUT;

    _data_out[1] = (uint8_t)(addr >> 24);
    _data_out[2] = (uint8_t)(addr >> 16);
    _data_out[3] = (uint8_t)(addr >> 8);
    _data_out[4] = (uint8_t)addr;

    _data_out[5] = (uint8_t)(data >> 8);
    _data_out[6] = (uint8_t)data;

    _size_out = 7;
    _size_in = 0;
}

void vtprobe_packet::do_cmd_hword_out_offset(uint32_t offset, uint32_t data)
{
    _data_out[0] = (uint8_t)VTPROBE_CMD_HALF_OUT_OFFSET;
    _data_out[1] = (uint8_t)offset;

    _data_out[2] = (uint8_t)(data >> 8);
    _data_out[3] = (uint8_t)data;

    _size_out = 4;
    _size_in = 0;
}

void vtprobe_packet::do_cmd_byte_in(uint32_t addr, uint32_t delay)
{
    _data_out[1] = (uint8_t)(addr >> 24);
    _data_out[2] = (uint8_t)(addr >> 16);
    _data_out[3] = (uint8_t)(addr >> 8);
    _data_out[4] = (uint8_t)addr;

    if (delay == 0)
        _data_out[0] = (uint8_t)VTPROBE_CMD_BYTE_IN;
    else
        _data_out[0] = (uint8_t)VTPROBE_CMD_BYTE_IN_DELAY;

    _size_out = 5;

    while (delay > 8) {
        _data_out[_size_out] = 0;
        ++_size_out;
        delay -= 4;
    }

    if (delay > 0) {
        _data_out[_size_out] = 0;
        ++_size_out;
    }

    _size_in = 1;
}

void vtprobe_packet::do_cmd_byte_in_offset(uint32_t offset, uint32_t delay)
{
    _data_out[1] = (uint8_t)offset;

    if (delay == 0)
        _data_out[0] = (uint8_t)VTPROBE_CMD_BYTE_IN_OFFSET;
    else
        _data_out[0] = (uint8_t)VTPROBE_CMD_BYTE_IN_OFFSET_DELAY;

    while (delay > 8) {
        _data_out[_size_out] = 0;
        ++_size_out;
        delay -= 4;
    }

    if (delay > 0) {
        _data_out[_size_out] = 0;
        ++_size_out;
    }

    _size_in = 1;
}

void vtprobe_packet::do_cmd_byte_out(uint32_t addr, uint8_t data)
{
    _data_out[0] = (uint8_t)VTPROBE_CMD_BYTE_OUT;

    _data_out[1] = (uint8_t)(addr >> 24);
    _data_out[2] = (uint8_t)(addr >> 16);
    _data_out[3] = (uint8_t)(addr >> 8);
    _data_out[4] = (uint8_t)addr;

    _data_out[5] = (uint8_t)data;

    _size_out = 6;
    _size_in = 0;
}

void vtprobe_packet::do_cmd_byte_out_offset(uint32_t offset, uint8_t data)
{
    _data_out[0] = (uint8_t)VTPROBE_CMD_BYTE_OUT_OFFSET;
    _data_out[1] = (uint8_t)offset;

    _data_out[2] = (uint8_t)data;

    _size_out = 3;
    _size_in = 0;
}

int vtprobe_packet::send_out()
{
    uint8_t *data_in = NULL;

    if (_size_out <= 0)
        return VTPROBE_ERR_IO_SIZE;

    if (::Start(_mpsse_spi) < 0)
        return (int)VTPROBE_ERR_IO_GENERIC;

    if (::Write(_mpsse_spi, (char *)_data_out, (int)_size_out) < 0)
        return (int)VTPROBE_ERR_IO_WRITE;

    if (_size_in > 0) {
        data_in = (uint8_t *)::Read(_mpsse_spi, _size_in);
        if (data_in == NULL)
            return (int)VTPROBE_ERR_IO_READ;
    }

    ::Stop(_mpsse_spi);

    if (data_in != NULL) {
        ::memcpy(_data_in, data_in, _size_in);
        ::free(data_in);
    }

    return VTPROBE_ERR_SUCCESS;
}

// ------------------

vtprobe::vtprobe() : _ftdi_ctxt(NULL), _mpsse_spi(NULL)
{

}

vtprobe::~vtprobe()
{
    this->close();
}

int vtprobe::spi_open()
{
    int d = 0, s = 0, r = 0;

    struct ftdi_device_list *dev_list = NULL, *dev_iter = NULL, *dev_sel = NULL;
    struct ftdi_version_info ver_info;

    int vid_sel, pid_sel;

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
        return (int)VTPROBE_ERR_ALLOC;
    }

    if ((r = ::ftdi_usb_find_all(_ftdi_ctxt, &dev_list, 0, 0)) < 0) {
        ::printf("failed on ftdi_usb_find_all() ... %d (%s)\n", r, ::ftdi_get_error_string(_ftdi_ctxt));
        r = VTPROBE_ERR_IO_GENERIC;
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
            r = VTPROBE_ERR_IO_GENERIC;
            goto _safe_exit;
        }

        if ((r = ::ftdi_usb_get_strings(_ftdi_ctxt, dev_iter->dev, sz_mfg, CONFIG_MAX_PATH, sz_desc, CONFIG_MAX_PATH, sz_serial, CONFIG_MAX_PATH)) < 0) {
            ::printf("failed on ftdi_usb_get_strings() ... %d (%s)\n", r, ::ftdi_get_error_string(_ftdi_ctxt));
            r = VTPROBE_ERR_IO_GENERIC;
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
                r = VTPROBE_ERR_IO_GENERIC;
                continue;
            }

            if ((r = ::libusb_open(dev_iter->dev, &usbdev_handle)) < 0) {
                ::printf("  failed on libusb_open() ... %d\n", r);
                r = VTPROBE_ERR_IO_GENERIC;
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
        r = VTPROBE_ERR_IO_GENERIC;
        goto _safe_exit;
    }

    // ----------------------------

    _mpsse_spi = ::ftdi_spi_open(vid_sel, pid_sel, SPI0, (int)axisp_ctxt.data_rate, MSB, IFACE_A, NULL, NULL);
    if ((_mpsse_spi == NULL) || (_mpsse_spi->open == 0)) {
        ::printf("failed on libstdspi::Open() !\n");
        r = VTPROBE_ERR_IO_GENERIC;
        goto _safe_exit;
    }

    if (dev_list != NULL)
        ::ftdi_list_free(&dev_list);

    return (int)VTPROBE_ERR_SUCCESS;

_safe_exit:

    if (dev_list != NULL)
        ::ftdi_list_free(&dev_list);

    spi_close();

    return r;
}

int vtprobe::spi_close()
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

    return (int)VTPROBE_ERR_SUCCESS;
}

int vtprobe::open()
{
    return this->spi_open();
}

void vtprobe::close()
{
    this->spi_close();
}

int vtprobe::do_base_cmd()
{
    vtprobe_packet pkt(_mpsse_spi);

    if (axisp_ctxt.isp_nr_args > 1) {

        const char *sz_addr = axisp_ctxt.isp_args[2];

        if (::axisp_context::validate_hex(sz_addr)) {
            ::printf("\n[err] invalid data-write address!\n\n");
            return (int)VTPROBE_ERR_ARGUMENT;
        }

        uint32_t b_addr = ::strtoul(sz_addr, 0, 16);

        pkt.do_cmd_base_reg_out(b_addr);

        ::printf("\nbase <- 0x%08x ... ", b_addr);

        int r = pkt.send_out();
        if (r < 0) {
            ::printf("failed (%d) ", r);
            return r;
        }

        ::printf("done.\n\n");

    } else {

        pkt.do_cmd_base_reg_in();

        ::printf("\nbase -> ");

        int r = pkt.send_out();
        if (r < 0) {
            ::printf("failed (%d) ", r);
            return r;
        }

        uint32_t b_addr = ((uint32_t)pkt._data_in[0] << 24) | ((uint32_t)pkt._data_in[1] << 16) | ((uint32_t)pkt._data_in[2] << 8) | (uint32_t)pkt._data_in[3];

        ::printf("0x%08x\n\n", b_addr);
    }

    return VTPROBE_ERR_SUCCESS;
}

int vtprobe::do_delay_cmd()
{
    vtprobe_packet pkt(_mpsse_spi);

    if (axisp_ctxt.isp_nr_args > 1) {

        const char *sz_delay = axisp_ctxt.isp_args[2];

        if (::axisp_context::validate_hex(sz_delay)) {
            ::printf("\n[err] invalid data-write address!\n\n");
            return (int)VTPROBE_ERR_ARGUMENT;
        }

        uint32_t delay = ::strtoul(sz_delay, 0, 16);

        pkt.do_cmd_delay_reg_out(delay);

        ::printf("\ndelay <- 0x%02x ... ", delay);

        int r = pkt.send_out();
        if (r < 0) {
            ::printf("failed (%d) ", r);
            return r;
        }

        ::printf("done.\n\n");

    } else {

        pkt.do_cmd_delay_reg_in();

        ::printf("\ndelay -> ");

        int r = pkt.send_out();
        if (r < 0) {
            ::printf("failed (%d) ", r);
            return r;
        }

        uint32_t delay = (uint32_t)pkt._data_in[0];

        ::printf("0x%08x\n\n", delay);
    }

    return VTPROBE_ERR_SUCCESS;
}

int vtprobe::do_word_read_cmd(bool indirect)
{
    if (axisp_ctxt.isp_nr_args < 3) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return (int)VTPROBE_ERR_ARGUMENT;
    }

    const char *sz_delay = axisp_ctxt.isp_args[2];
    const char *sz_addr = axisp_ctxt.isp_args[3];
    uint32_t nr_words = 1;

    if (::axisp_context::validate_hex(sz_delay)) {
        ::printf("\n[err] invalid delay value!\n\n");
        return (int)VTPROBE_ERR_ARGUMENT;
    }

    if (::axisp_context::validate_hex(sz_addr)) {
        ::printf("\n[err] invalid data address!\n\n");
        return (int)VTPROBE_ERR_ARGUMENT;
    }

    uint32_t delay = ::strtoul(sz_delay, 0, 16);
    uint32_t addr_base = ::strtoul(sz_addr, 0, 16);
    uint32_t addr = addr_base;

    if (axisp_ctxt.isp_nr_args > 3) {

        const char *sz_words = axisp_ctxt.isp_args[4];

        if (::axisp_context::validate_hex(sz_words)) {
            ::printf("\n[err] invalid data counts!\n\n");
            return (int)VTPROBE_ERR_ARGUMENT;
        }

        nr_words = ::strtoul(sz_words, 0, 16);
    }

    if (nr_words >= (VTPROBE_RAW_DATA_SIZE / 4))
        nr_words = VTPROBE_RAW_DATA_SIZE / 4;

    uint32_t data_in[VTPROBE_RAW_DATA_SIZE / 4];
    uint32_t *data = data_in;

    vtprobe_packet pkt(_mpsse_spi);

    uint32_t addr_e = addr + nr_words * 4;

    ::printf("\n[0x%08x] -> (0x%x words) ... ", addr, nr_words);

    while (addr < addr_e) {

        if (indirect)
            pkt.do_cmd_word_in_offset(addr, delay);
        else
            pkt.do_cmd_word_in(addr, delay);

        int r = pkt.send_out();
        if (r < 0) {
            ::printf("failed @0x%08x (%d) ", addr, r);
            return r;
        }

        *data++ = ((uint32_t)pkt._data_in[0] << 24) | ((uint32_t)pkt._data_in[1] << 16) | ((uint32_t)pkt._data_in[2] << 8) | (uint32_t)pkt._data_in[3];
        addr += 4;
    }

    ::printf("done.\n\n");

    {
        addr = addr_base;
        data = data_in;

        uint32_t nr_lines = nr_words / 4;

        ::printf("addr       0        4          8        C       \n");
        ::printf("-------- | -------- --------   -------- --------\n");

        while (nr_lines--) {
            ::printf("%08X | %08X %08X - %08X %08X\n", addr, data[0], data[1], data[2], data[3]);
            addr += 16;
            data += 4;
        }

        uint32_t w = nr_words % 4;

        if (w > 0) {

            ::printf("%08x |", addr);

            for (uint32_t i = 0; i < w; ++i) {
                if (i == 2)
                    ::printf(" -");
                ::printf(" %08x", data[i]);
            }

            ::printf("\n");
        }
    }

    return VTPROBE_ERR_SUCCESS;
}

int vtprobe::do_word_write_cmd(bool indirect)
{
    if (axisp_ctxt.isp_nr_args < 3) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return (int)VTPROBE_ERR_ARGUMENT;
    }

    const char *sz_addr = axisp_ctxt.isp_args[2];
    uint32_t nr_words = axisp_ctxt.isp_nr_args - 2;

    if (nr_words >= (VTPROBE_RAW_DATA_SIZE / 4))
        nr_words = VTPROBE_RAW_DATA_SIZE / 4;

    uint32_t data_out[VTPROBE_RAW_DATA_SIZE / 4];
    uint32_t *data = data_out;

    if (::axisp_context::validate_hex(sz_addr)) {
        ::printf("\n[err] invalid data address!\n\n");
        return (int)VTPROBE_ERR_ARGUMENT;
    }

    uint32_t addr_base = ::strtoul(sz_addr, 0, 16);
    uint32_t addr = addr_base;

    for (uint32_t i = 0; i < nr_words; ++i) {

        const char *sz_data = axisp_ctxt.isp_args[3 + i];

        if (::axisp_context::validate_hex(sz_data)) {
            ::printf("\n[err] invalid data value (%s)!\n\n", sz_data);
            return (int)VTPROBE_ERR_ARGUMENT;
        }

        *data++ = ::strtoul(sz_data, 0, 16);
    }

    vtprobe_packet pkt(_mpsse_spi);

    uint32_t addr_e = addr + nr_words * 4;
    data = data_out;

    ::printf("\n[0x%08x] <- (0x%x words) ... ", addr, nr_words);

    while (addr < addr_e) {

        if (indirect)
            pkt.do_cmd_word_out_offset(addr, *data);
        else
            pkt.do_cmd_word_out(addr, *data);

        int r = pkt.send_out();
        if (r < 0) {
            ::printf("failed @0x%08x (%d) ", addr, r);
            return r;
        }

        ++data;
        addr += 4;
    }

    ::printf("done.\n\n");

    return VTPROBE_ERR_SUCCESS;
}

int vtprobe::do_probe_cmd()
{
    const char *sz_cmd = axisp_ctxt.isp_args[1];

    if (axisp_ctxt.isp_nr_args < 1) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return -1;
    }

    if (::strncmp(sz_cmd, "ba", 1) == 0) {
        return do_base_cmd();
    } else if (::strncmp(sz_cmd, "de", 1) == 0) {
        return do_delay_cmd();
    } else if (::strncmp(sz_cmd, "dw", 2) == 0) {
        return do_word_read_cmd(false);
    } else if (::strncmp(sz_cmd, "idw", 3) == 0) {
        return do_word_read_cmd(true);
    } else if (::strncmp(sz_cmd, "ww", 2) == 0) {
        return do_word_write_cmd(false);
    } else if (::strncmp(sz_cmd, "iww", 3) == 0) {
        return do_word_write_cmd(true);
    } else {
        ::printf("\n[err] unknown probe command !\n\n");
        return (int)VTGPIO_ERR_ARGUMENT;
    }

    return VTGPIO_ERR_SUCCESS;
}

