
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
//#include <mpsse.h>

//#include "xmodem.h"
#include "vtisp.h"
#include "ftefc.h"
#include "bin_object.h"

#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif

#if 0
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
#endif


//unsigned long flash_addr;
// ---------------------------------------------------------------------------

void vtisp_packet::do_cmd_ping()
{
    _data_out[0] = (uint8_t)VTISP_CMD_PING;
    _data_out[1] = 0;
    _data_out[2] = 0;
    _data_out[3] = 0;

    _size_out = 4;
    _size_in = 0;
}

void vtisp_packet::do_cmd_break()
{
    _data_out[0] = (uint8_t)VTISP_CMD_BREAK;
    _data_out[1] = 0;
    _data_out[2] = 0;
    _data_out[3] = 0;

    _size_out = 4;
    _size_in = 0;
}

void vtisp_packet::do_vtefc_init(uint32_t type)
{
    uint32_t size = 1;
    _data_out[0] = (uint8_t)VTISP_CMD_VTEFC_INIT;
    _data_out[1] = 0;
    _data_out[2] = (uint8_t)(size & 0xff);
    _data_out[3] = (uint8_t)((size >> 8) & 0xff);

    _data_out[4] = (uint8_t)(type & 0xff);
    _data_out[5] = (uint8_t)((type >> 8) & 0xff);
    _data_out[6] = (uint8_t)((type >> 16) & 0xff);
    _data_out[7] = (uint8_t)((type >> 24) & 0xff);

    _data_out[8] = do_checksum(&_data_out[4], 4);

    _size_out = 9;
    _size_in = 0;
}

void vtisp_packet::do_cmd_word_read(uint32_t addr, uint32_t size)
{
    _data_out[0] = (uint8_t)VTISP_CMD_WORD_READ;
    _data_out[1] = 0;//(uint8_t)VTISP_CMDF_WORD_DATA;
    _data_out[2] = (uint8_t)(size & 0xff);
    _data_out[3] = (uint8_t)((size >> 8) & 0xff);

    _data_out[4] = (uint8_t)(addr & 0xff);
    _data_out[5] = (uint8_t)((addr >> 8) & 0xff);
    _data_out[6] = (uint8_t)((addr >> 16) & 0xff);
    _data_out[7] = (uint8_t)((addr >> 24) & 0xff);

    _data_out[8] = do_checksum(&_data_out[4], 4);

    _size_out = 9;
    _size_in = 0;
}

void vtisp_packet::do_cmd_read_checksum(uint32_t addr, uint32_t size)
{
    _data_out[0] = (uint8_t)VTISP_CMD_READ_CHECKSUM;
    _data_out[1] = 0;//(uint8_t)VTISP_CMDF_WORD_DATA;
    _data_out[2] = (uint8_t)(size & 0xff);
    _data_out[3] = (uint8_t)((size >> 8) & 0xff);

    _data_out[4] = (uint8_t)(addr & 0xff);
    _data_out[5] = (uint8_t)((addr >> 8) & 0xff);
    _data_out[6] = (uint8_t)((addr >> 16) & 0xff);
    _data_out[7] = (uint8_t)((addr >> 24) & 0xff);

    _data_out[8] = do_checksum(&_data_out[4], 4);

    _size_out = 9;
    _size_in = 0;
}

void vtisp_packet::do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t size)
{
    assert((size * 4) < (VTISP_RAW_DATA_SIZE - 8));

    _data_out[0] = (uint8_t)VTISP_CMD_WORD_WRITE;
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

    _data_out[_size_out] = do_checksum(&_data_out[4], _size_out - 4);
    ++_size_out;

    _size_in = 0;
}

void vtisp_packet::do_cmd_page_program(uint32_t addr, uint32_t *data, uint32_t size, bool DMAFlag)
{
    assert((size * 4) < (VTISP_RAW_DATA_SIZE - 8));

    if(DMAFlag == true)
        _data_out[0] = (uint8_t)VTISP_CMD_WRITE_DMA;
    else
        _data_out[0] = (uint8_t)VTISP_CMD_PAGE_PROGRAM;
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

    _data_out[_size_out] = do_checksum(&_data_out[4], _size_out - 4);
    ++_size_out;

    _size_in = 0;
}

void vtisp_packet::do_cmd_word_write(uint32_t addr, uint32_t *data, uint32_t size, bool DMAFlag)
{
    assert((size * 4) < (VTISP_RAW_DATA_SIZE - 8));

    if(DMAFlag == true)
        _data_out[0] = (uint8_t)VTISP_CMD_WRITE_DMA;
    else
        _data_out[0] = (uint8_t)VTISP_CMD_WORD_WRITE;
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

    _data_out[_size_out] = do_checksum(&_data_out[4], _size_out - 4);
    ++_size_out;

    _size_in = 0;
}

void vtisp_packet::do_cmd_word_write(uint32_t addr, uint32_t data)
{
    _data_out[0] = (uint8_t)VTISP_CMD_WORD_WRITE;
    _data_out[1] = 0;//(uint8_t)VTISP_CMDF_WORD_DATA;
    _data_out[2] = (uint8_t)1;
    _data_out[3] = (uint8_t)0;

    _data_out[4] = (uint8_t)(addr & 0xff);
    _data_out[5] = (uint8_t)((addr >> 8) & 0xff);
    _data_out[6] = (uint8_t)((addr >> 16) & 0xff);
    _data_out[7] = (uint8_t)((addr >> 24) & 0xff);

    _data_out[8]  = ((uint8_t *)&data)[0];
    _data_out[9]  = ((uint8_t *)&data)[1];
    _data_out[10] = ((uint8_t *)&data)[2];
    _data_out[11] = ((uint8_t *)&data)[3];

    _data_out[12] = do_checksum(&_data_out[4], 8);
    _size_out = 13;

    _size_in = 0;
}

void vtisp_packet::do_cmd_word_write(uint32_t addr, uint32_t data, bool DMAFlag)
{
    if(DMAFlag == true)
        _data_out[0] = (uint8_t)VTISP_CMD_WRITE_DMA;
    else
        _data_out[0] = (uint8_t)VTISP_CMD_WORD_WRITE;
    _data_out[1] = 0;//(uint8_t)VTISP_CMDF_WORD_DATA;
    _data_out[2] = (uint8_t)1;
    _data_out[3] = (uint8_t)0;

    _data_out[4] = (uint8_t)(addr & 0xff);
    _data_out[5] = (uint8_t)((addr >> 8) & 0xff);
    _data_out[6] = (uint8_t)((addr >> 16) & 0xff);
    _data_out[7] = (uint8_t)((addr >> 24) & 0xff);

    _data_out[8]  = ((uint8_t *)&data)[0];
    _data_out[9]  = ((uint8_t *)&data)[1];
    _data_out[10] = ((uint8_t *)&data)[2];
    _data_out[11] = ((uint8_t *)&data)[3];

    _data_out[12] = do_checksum(&_data_out[4], 8);
    _size_out = 13;

    _size_in = 0;
}

void vtisp_packet::do_cmd_setup(uint32_t index, uint32_t value)
{
    _size_out = 0;
    _size_in = 0;
}

uint8_t vtisp_packet::do_checksum(uint8_t *data, uint32_t length)
{
    uint8_t checksum = 0;

    while (length-- > 0) {
        checksum += *data++;
    }

    return checksum;
}

int vtisp_packet::send_out(bool wait_ack, uint32_t data_in_delay)
{
    if (_fd < 0) {	
        return -1;
    }	
/*
	uint32_t i;
	
	for (i=0; i<_size_out; i++) {
		if(i%16==0) 	::printf("\n%04X| ", i);	::fflush(stdout);
		::printf("%02X ",_data_out[i]);	::fflush(stdout);
	}

	::printf("\n==========\n");	::fflush(stdout);
*/	
    int r = ::write(_fd, _data_out, _size_out);
	
	::printf("\n\n_fd %d,_size_out %d, w_size %d\n",_fd,_size_out, r);	::fflush(stdout);
	
    if (r != (int)_size_out) {
        //::printf("failed to send out request!!\n");  ::fflush(stdout);
        return -1;
    }

    if (wait_ack) {
		//int g_ack=
			get_ack();
	//	::printf("Wait ACK %d..\n", g_ack);	::fflush(stdout);	

        return 1;//g_ack; 
   }
	
    return 0;
}

int vtisp_packet::get_byte(uint8_t *data)
{
    if (_fd < 0)
        return -1;

    int timeout = ISP_ACK_TIMEOUT;

    while (timeout-- >= 0) {

        int r = ::read(_fd, data, 1);
		
        if (r == 1)
        {
        	//::printf("GET BYTE %X..\n", *data );	::fflush(stdout);	
            return 0;
        }

        if (r < 0){
        	::printf("GET FAIL...\n" );	::fflush(stdout);
            return -1;  // error
        }
        ::usleep(ISP_ACK_WAIT_SLEEP_US);
    }

    return -2;  // timeout
}

int vtisp_packet::get_ack()
{
    if (_fd < 0)
        return -1;

    int r = 0;

    uint8_t *data_iter = _data_in;

    _size_in = 0;
    _data_in[1] = 0;

    // get cmd-byte
   //_get_again:
    r = get_byte(data_iter++);
//    ::printf("@0x%lld: 0x%x", (long long)(data_iter-1), *(data_iter-1));

    if (r != 0) {
		
        _data_in[1] = (uint8_t)VTISP_ACKH_TIMEOUT;
        return -2;
    }

    _size_in = 1;

    if (_data_in[0] != (uint8_t)VTISP_CMD_ACK) {
        _data_in[1] = (uint8_t)VTISP_ACKH_UNKNOWN;
	//	 	_size_in = 0;
    //			_data_in[1] = 0;
	//		data_iter = _data_in;
		//::printf("GET no ACK=%X\n", _data_in[0]);
		//goto _get_again;
        return -3;
    }

    // get remaing cmd-header
    for (uint32_t i = 1; i < 4; i++) {
        r = get_byte(data_iter++);
//    ::printf("[%d]@0x%lld: 0x%x, @0x%lld: 0x%x", i, (long long)(data_iter-1), *(data_iter-1), (long long)&_data_in[i], _data_in[i]);

        if (r != 0) {
            _data_in[1] |= (uint8_t)VTISP_ACKH_TIMEOUT;
		
            return -4;
        }
    }




    _size_in = 4;

    if (_data_in[1] != 0) {
	
        return -5;
    }


    // get remaining data, if any ...
    uint32_t data_size = ((uint32_t)_data_in[3] << 8) | ((uint32_t)_data_in[2]);



    if (data_size > (VTISP_RAW_DATA_SIZE - 4))
        data_size = VTISP_RAW_DATA_SIZE - 4;



    if (data_size > 0) {

        data_size *= 4;

        for (uint32_t i = 0; i <= data_size; ++i) {

            r = get_byte(data_iter++);
            if (r != 0) {
                _data_in[1] |= (uint8_t)VTISP_ACKH_TIMEOUT;

                return -6;
            }

            ++_size_in;
        }

        // verify checksum
        uint8_t checksum = do_checksum(&_data_in[4], data_size);

        if (checksum != _data_in[_size_in - 1]) {
            _data_in[1] |= (uint8_t)VTISP_ACKH_CHECKSUM;
			
            return -7;
        }
    }



    return 0;
}

int vtisp_packet::get_raw(uint32_t delay)
{
    if (_fd < 0)
        return -1;

    if (delay > 0)
        ::usleep(delay);

    int r = 0;
    uint32_t timeout = 100;

    uint8_t *data_iter = _data_in;

    _size_in = 0;
    ::memset(_data_in, 0, VTISP_RAW_DATA_SIZE);

    while (_size_in < (VTISP_RAW_DATA_SIZE - 4)) {

        r = get_byte(data_iter);
        if (r >= 0) {
            ++data_iter;
            ++_size_in;
            continue;
        }

        if (r < -1) {
            --timeout;
            if (timeout <= 0)
                break;
        }

        break;
    }

    return _size_in;
}

// ------------------

vtisp::vtisp() : _fd_dev(-1), _quiet(true)
{
    _sz_dev[0] = 0;
}

vtisp::~vtisp()
{
}

void vtisp::quiet(bool q)
{
    _quiet = q;
}

uint32_t vtisp::serial_std_speed(uint32_t baudrate)
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

int vtisp::open_dev(const char *path, bool do_setup)
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
        speed_t baudrate = serial_std_speed(axisp_ctxt.data_rate);
        ::cfsetispeed(&tc_spec, baudrate);
        ::cfsetospeed(&tc_spec, baudrate);

        ::tcflush(_fd_dev, TCIOFLUSH);

        ::tcsetattr(_fd_dev, TCSANOW, &tc_spec);
    }

    return 0;
}

int vtisp::do_dev_list()
{
    char path[255];

    for (int i = 0; i < 10; ++i) {
        ::sprintf(path, "/dev/ttyUSB%d", i);
        open_dev(path, true);
        close();
    }

    return 0;
}

int vtisp::open()
{
    return open_dev(axisp_ctxt.fname_dev, true);
}

void vtisp::close()
{
    if (_fd_dev >= 0)
        ::close(_fd_dev);
    _fd_dev = -1;
}

/*
uint32_t vtisp::u8le_to_u32(uint8_t *u8_data)
{
    return (uint32_t)u8_data[0] | (uint32_t)(u8_data[1] << 8) | (uint32_t)(u8_data[2] << 16) | (uint32_t)(u8_data[3] << 24);
}*/

void vtisp::print_raw(vtisp_packet &pkt)
{
    ::printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    bool ascii = true;
    uint32_t bin_cnt = 0;

    for (uint32_t c = 0; c < pkt._size_in; ++c) {
        if ((pkt._data_in[c] < 0x20) || (pkt._data_in[c] > 0x7e)) {
            if ((pkt._data_in[c] != 0x0d) && (pkt._data_in[c] != 0x0a)) {
                ascii = false;
                ++bin_cnt;
            }
        }
    }

    if (ascii || (bin_cnt < 4)) {
        ::printf("%s\n", (const char *)pkt._data_in);
    }

    for (uint32_t c = 0; c < pkt._size_in; ++c) {
        if ((c & 0x0f) == 0) {
            ::printf("\n%04X | %02X ", c, (uint32_t)pkt._data_in[c]);
        } else {
            if ((c & 7) == 0) {
                ::printf("- ");
            } else if ((c & 3) == 0) {
                ::printf(" ");
            }

            ::printf("%02X ", (uint32_t)pkt._data_in[c]);
        }
    }

    ::printf("\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    ::fflush(stdout);
}

int vtisp::do_word_read()
{
    if (axisp_ctxt.isp_nr_args < 1) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return -1;
    }

    const char *sz_addr = axisp_ctxt.isp_args[1];
    const char *sz_counts = axisp_ctxt.isp_args[2];

    if (::axisp_context::validate_hex(sz_addr)) {
        ::printf("\n[err] invalid data-read address!\n\n");
        return -1;
    }

    if (axisp_ctxt.isp_nr_args >= 2) {
        if (::axisp_context::validate_hex(sz_counts)) {
            ::printf("\n[err] invalid data-read counts!\n\n");
            return -1;
        }
    } else {
        sz_counts = "1";
    }

    uint32_t r_addr = ::strtoul(sz_addr, 0, 16);
    uint32_t r_counts = ::strtoul(sz_counts, 0, 16);

    r_addr = r_addr & ~0x03;
    r_counts = min(r_counts, (vtisp_packet::VTISP_RAW_DATA_SIZE - 8) / 4);

    vtisp_packet pkt(_fd_dev);

    pkt.do_cmd_word_read(r_addr, r_counts);

    ::printf("\nreading ... ");

    int r = pkt.send_out();
    if ((r < 0) || (pkt._size_in <= 4)) {
        ::printf("(failed) ");
        ::printf("ack-pkt status)0x%02x size)0x%04x\n", (uint32_t)pkt._data_in[1], pkt._size_in);
        r = -1;
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

    return 0;

_safe_exit:

    if (r < 0) {
        // try to capture exception dump messages, if any ...
        if (pkt.get_raw() > 0) {
            ::printf("\n\n");
            print_raw(pkt);
        }
    }

    return r;
}

int vtisp::do_word_write()
{
    vtisp_packet pkt(_fd_dev);
    ftefc        efc;

    if (axisp_ctxt.isp_nr_args < 2) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return -1;
    }

    const char *sz_addr = axisp_ctxt.isp_args[1];
    const char *sz_data = axisp_ctxt.isp_args[2];
    const char *sz_counts = axisp_ctxt.isp_args[3];

    if (::axisp_context::validate_hex(sz_addr)) {
        ::printf("\n[err] invalid data-write address!\n\n");
        return -1;
    }

    if (::axisp_context::validate_hex(sz_data)) {
        ::printf("\n[err] invalid data-write data!\n\n");
        return -1;
    }

    if (axisp_ctxt.isp_nr_args >= 3) {
        if (::axisp_context::validate_hex(sz_counts)) {
            ::printf("\n[err] invalid data-write counts!\n\n");
            return -1;
        }
    } else {
        sz_counts = "1";
    }

    uint32_t w_addr = ::strtoul(sz_addr, 0, 16);
    uint32_t w_data = ::strtoul(sz_data, 0, 16);
    //uint32_t w_counts = ::strtoul(sz_counts, 0, 16);

    w_addr &= ~0x03;

    uint32_t remap = 0;

    int r = do_remap_get(remap);
    if (r < 0)
        return -1;

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

    pkt.do_cmd_word_write(w_addr, &w_data, 1);

    ::printf("\n[0x%08x] <- 0x%08x ", w_addr, w_data);

    r = pkt.send_out();
    if ((r < 0) || (pkt._data_in[1] != 0)) {
        ::printf("(failed) ");
        ::printf("ack-pkt status)0x%02x size)0x%04x\n", (uint32_t)pkt._data_in[1], pkt._size_in);
        r = -1;
        goto _safe_exit;
    }

    ::printf("(ok)\n");

    return 0;

_efc_memb:

    {
        uint32_t page = (w_addr - efc_memb_base) / FTEFC_PAGE_SIZE;

        ::printf("\n[0x%08x] <- 0x%08x ... efc-memb-page)%d ", w_addr, w_data, page);

        // unlock the page for programming ...
        uint32_t page_base = efc.page_unlock(pkt, efc_memb_base, page, false);

        if (page_base == (uint32_t)-1) {
            ::printf("unlock failed (prog)\n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        ::usleep(VTISP_EFC_PROG_UNLOCK_DELAY);  // page-buffering delay

        // compose the packet (command) and send it out ...
        pkt.do_cmd_word_write(w_addr, &w_data, 1);

        if (pkt.send_out() < 0) {
            ::printf("programming failed\n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        // done flashing and re-lock the page
        if (efc.page_lock(pkt, page_base) < 0) {
            ::printf("lock failed (prog)\n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        ::usleep(VTISP_EFC_PROG_LOCK_DELAY);  // page write-back delay
    }

    ::printf("ok\n");  ::fflush(stdout);

    return 0;

_efc_infb:

    {
        uint32_t page = (w_addr - efc_infb_base) / FTEFC_PAGE_SIZE;

        ::printf("\n[0x%08x] <- 0x%08x ... efc-infb-page)%d ", w_addr, w_data, page);

        // unlock the page for programming ...
        uint32_t page_base = efc.page_unlock(pkt, efc_infb_base, page, false);

        if (page_base == (uint32_t)-1) {
            ::printf("unlock failed (prog)\n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        ::usleep(VTISP_EFC_PROG_UNLOCK_DELAY);  // page-buffering delay

        // compose the packet (command) and send it out ...
        pkt.do_cmd_word_write(w_addr, &w_data, 1);

        if (pkt.send_out() < 0) {
            ::printf("programming failed\n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        // done flashing and re-lock the page
        if (efc.page_lock(pkt, page_base) < 0) {
            ::printf("lock failed (prog)\n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        ::usleep(VTISP_EFC_PROG_LOCK_DELAY);  // page write-back delay
    }

    ::printf("ok\n");  ::fflush(stdout);

    return 0;

_safe_exit:

    if (r < 0) {
        // try to capture exception dump messages, if any ...
        if (pkt.get_raw() > 0) {
            ::printf("\n\n");
            print_raw(pkt);
        }
    }

    return r;
}

int vtisp::vtefc_init(uint32_t type)
{
    vtisp_packet pkt(_fd_dev);

    pkt.do_vtefc_init(type);

    ::printf("\nConfig flash controller to type(%d) ... ", type);

    int r = pkt.send_out();
    if ((r < 0) || (pkt._size_in < 4)) {
        ::printf("(failed) ");
        r = -1;
        goto _safe_exit;
    }

    // TODO: ack?

    return 0;

_safe_exit:

    if (r < 0) {
        // try to capture exception dump messages, if any ...
        if (pkt.get_raw() > 0) {
            ::printf("\n\n");
            print_raw(pkt);
        }
    }

    return r;
}

int vtisp::do_remap_get(uint32_t &remap)
{
    uint32_t r_addr = 0x54000020;

    vtisp_packet pkt(_fd_dev);

    pkt.do_cmd_word_read(r_addr, 1);

    ::printf("\nreading current remap setting ... ");

    int r = pkt.send_out();
    if ((r < 0) || (pkt._size_in <= 4)) {
        ::printf("(failed) ");
        ::printf("ack-pkt status)0x%02x size)0x%04x\n", (uint32_t)pkt._data_in[1], pkt._size_in);
        r = -1;
        goto _safe_exit;
    }

    remap = (*((uint32_t *)&pkt._data_in[4]) >> 24) & 0x0f;

    ::printf("done (remap = %d)\n", remap);

    return 0;

_safe_exit:

    if (r < 0) {
        // try to capture exception dump messages, if any ...
        if (pkt.get_raw() > 0) {
            ::printf("\n\n");
            print_raw(pkt);
        }
    }

    return r;
}

int vtisp::do_bist(uint32_t bist_base, uint32_t bist_size, uint32_t pattern)
{
    return 0;
}

int vtisp::prog_eflash(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size)
{
    vtisp_packet pkt(_fd_dev);
    ftefc        efc;

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
        return -1;
    }

    uint32_t addr_iter = addr_b;
    uint8_t *data_iter = (uint8_t *)data;

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
            ::usleep(VTISP_EFC_ERASE_UNLOCK_DELAY);

            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (erase)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_EFC_ERASE_LOCK_DELAY);

            ::printf("ok <- ");  ::fflush(stdout);

            // unlock the page for data-write ...
            page_base = efc.page_unlock(pkt, efcblk_base, p);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (prog)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_EFC_WRONLY_UNLOCK_DELAY);

            p_off = addr_iter - page_base;
            p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);

            ::printf("(%d bytes) ", p_size);  ::fflush(stdout);

            // read one page of image data ...
            ::memcpy(&pkt._data_out[8], data_iter, p_size);
            data_iter += p_size;

            // compose the packet (command) and send it out ...
            pkt.do_cmd_word_write(addr_iter, NULL, p_size / 4);

            if (pkt.send_out() < 0) {
                ::printf("programming failed\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_WORD_WRITE_DELAY(p_size));

            // done flashing and re-lock the page
            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (prog)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_EFC_WRONLY_LOCK_DELAY);

        } else {

            // unlock the page for programming ...
            uint32_t page_base = efc.page_unlock(pkt, efcblk_base, p, false);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (prog)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_EFC_PROG_UNLOCK_DELAY);

            p_off = addr_iter - page_base;
            p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);

            ::printf("(%d bytes) ", p_size);  ::fflush(stdout);

            // read one page of image data ...
            ::memcpy(&pkt._data_out[8], data_iter, p_size);
            data_iter += p_size;

            // compose the packet (command) and send it out ...
            pkt.do_cmd_word_write(addr_iter, NULL, p_size / 4);

            if (pkt.send_out() < 0) {
                ::printf("programming failed\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_WORD_WRITE_DELAY(p_size));

            // done flashing and re-lock the page
            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (prog)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_EFC_PROG_LOCK_DELAY);
        }

        ::printf("ok");  ::fflush(stdout);

        addr_iter += p_size;
    }

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

        if (pkt.send_out() < 0) {
            ::printf("read-back failed !! \n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        ::printf("(%d bytes)", pkt._size_in - 5);  ::fflush(stdout);

        // verify the image ...
        for (uint32_t w = 0; w < (p_size / 4); ++w) {

            ::printf("%s [0x%08x] page)%d -> off)0x%04x|0x%08x <-> image)0x%08x|0x%08x ", axisp_ctxt.verbose ? "\n" : "\r",
                addr_iter, p, w * 4, ((uint32_t *)pkt._data_in)[w + 1], addr_iter - addr_b + w * 4, ((uint32_t *)data_iter)[w]);  ::fflush(stdout);

            if (((uint32_t *)pkt._data_in)[w + 1] != ((uint32_t *)data_iter)[w]) {
                ::printf("(mismatch)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            } else {
                ::printf("(ok)");  ::fflush(stdout);
            }
        }

        addr_iter += p_size;
        data_iter += p_size;
    }

    ::printf("\n");  ::fflush(stdout);

    //if (axisp_ctxt.reboot) {
    //    do_reboot();
    //}

_safe_exit:

    if (r < 0) {
        // try to capture exception dump messages, if any ...
        if (pkt.get_raw() > 0) {
            ::printf("\n\n");
            print_raw(pkt);
        }
    }

    return r;
}

int vtisp::prog_eflash_raw(bin_object &bin_obj)
{
	vtisp_packet pkt(_fd_dev);
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
	

	for(i=0; i<4; i++)
		usleep(1000000);
	


	

    for (uint32_t p = page_b; (p <= page_e); ++p) {
       
        // read one page of image data ...
		read_size = bin_obj.read(&pkt._data_out[8], PAGE_SIZE);

		::printf("read_size %d\n",  read_size);


		if (read_size > 0) {
/*			for (i=0; i<read_size; i++) {
				if(i%16==0) 	::printf("\n%04X| ", i);	::fflush(stdout);
				::printf(" %02X", pkt._data_out[8+i]);	
			}
*/
			// compose the packet (command) and send it out ...
	        pkt.do_cmd_page_program(addr_iter, (uint32_t *)&pkt._data_out[8], PAGE_SIZE / 4, false);
		
	        if (pkt.send_out() < 0) {
	            ::printf("programming failed\n");  ::fflush(stdout);
	            r = -1;
	            goto _safe_exit;
	        }

	        ::printf("Page Write %x.. OK\n\n", addr_iter);  ::fflush(stdout);
	
	        addr_iter += read_size;
				usleep(50000);
			
		} else {
			break;
		}
    }

	_safe_exit:
	
	if (r < 0) {
		// try to capture exception dump messages, if any ...
		if (pkt.get_raw() > 0) {
			::printf("!!!!!!!\n\n");
			print_raw(pkt);
		}
	}

    return r;
}

int vtisp::prog_eflash_fast(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size)
{
    vtisp_packet pkt(_fd_dev);
    ftefc        efc;

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
    uint32_t page_nvm = 504 * 4;
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
        return -1;
    }
*/
    uint32_t addr_iter;
    uint8_t *data_iter = (uint8_t *)data;
    if (infb) {
        addr_iter = addr_b;
    } else {
        addr_iter = 0;
    }

//    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {
    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {

        uint32_t p_size = 256;


        if (axisp_ctxt.erase_prog) {
            ::printf("erase program not supported yet !!!\n");  ::fflush(stdout);
        } else {
            // read one page of image data ...
            ::memcpy(&pkt._data_out[8], data_iter, p_size);
            data_iter += p_size;
            
            if (p > size/p_size && p < page_nvm) {
                // skip the dummy data
            }else {

                ::printf("%s [0x%08x] page)%d <- ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter + VTREG_BASE_EFC, p);  ::fflush(stdout);
                // compose the packet (command) and send it out ...
                pkt.do_cmd_page_program(addr_iter, NULL, p_size / 4, false);

                if (pkt.send_out() < 0) {
                    ::printf("programming failed\n");  ::fflush(stdout);
                    r = -1;
                    goto _safe_exit;
                }

                ::printf("ok");  ::fflush(stdout);
            }
            //::usleep(VTISP_WORD_WRITE_DELAY(p_size));
        }


        addr_iter += p_size;
    }

    // verification
    ::printf("\n\nverifying %s (0x%08x - 0x%08x size 0x%08x) ...\n\n", infb ? "infb" : "memb", addr_b, addr_e, addr_e - addr_b);  ::fflush(stdout);

    addr_iter = addr_b;
    data_iter = (uint8_t *)data;

    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {


//        uint32_t page_base = FTEFC_PAGE_BASE(efcblk_base, p);

//        uint32_t p_off = addr_iter - page_base;
        uint32_t p_size = 256; //min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);
        uint32_t tmp_checksum = 0;

        // compose the packet (read-back command) and send it out ...
//        pkt.do_cmd_read_checksum(addr_iter, p_size / 4);
        
        if (p > size/p_size && p < page_nvm) {
            // skip the dummy data
        } else {
            
            ::printf("%s [0x%08x] page)%d -> ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter + VTREG_BASE_EFC, p);  ::fflush(stdout);
            pkt.do_cmd_read_checksum(addr_iter + VTREG_BASE_EFC, p_size / 4);

            if (pkt.send_out() < 0) {

                ::printf("read-back failed !! \n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }   

        //::printf("(%d bytes)", pkt._size_in - 5);  ::fflush(stdout);

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
        }
        addr_iter += p_size;
        data_iter += p_size;
    }

    ::printf("\n");  ::fflush(stdout);

    //if (axisp_ctxt.reboot) {
    //    do_reboot();
    //}

_safe_exit:

    if (r < 0) {
        // try to capture exception dump messages, if any ...
        if (pkt.get_raw() > 0) {
            ::printf("\n\n");
            print_raw(pkt);
        }
    }

    return r;
}

int vtisp::prog_eflash_sum(bool infb, uint32_t remap, uint32_t offset, void *data, uint32_t size)
{
    vtisp_packet pkt(_fd_dev);
    ftefc        efc;

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
        return -1;
    }

    uint32_t addr_iter = addr_b;
    uint8_t *data_iter = (uint8_t *)data;

    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {

        uint32_t p_off;
        uint32_t p_size;

        //::printf("%s [0x%08x] page)%d <- ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, p);  ::fflush(stdout);

        if (axisp_ctxt.erase_prog) {

            ::printf("erase ");  ::fflush(stdout);

            uint32_t page_base = efc.page_unlock(pkt, efcblk_base, p, true);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (erase)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }
            ::usleep(VTISP_EFC_ERASE_UNLOCK_DELAY);

            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (erase)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_EFC_ERASE_LOCK_DELAY);

            ::printf("ok <- ");  ::fflush(stdout);

            // unlock the page for data-write ...
            page_base = efc.page_unlock(pkt, efcblk_base, p);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (prog)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_EFC_WRONLY_UNLOCK_DELAY);

            p_off = addr_iter - page_base;
            p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);

            ::printf("(%d bytes) ", p_size);  ::fflush(stdout);

            // read one page of image data ...
            ::memcpy(&pkt._data_out[8], data_iter, p_size);
            data_iter += p_size;

            // compose the packet (command) and send it out ...
            pkt.do_cmd_word_write(addr_iter, NULL, p_size / 4);

            if (pkt.send_out() < 0) {
                ::printf("programming failed\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_PAGE_PRGROAM_DELAY(p_size));

            // done flashing and re-lock the page
            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (prog)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_EFC_WRONLY_LOCK_DELAY);

        } else {

            // unlock the page for programming ...
            uint32_t page_base = efc.page_unlock(pkt, efcblk_base, p, false);

            if (page_base == (uint32_t)-1) {
                ::printf("unlock failed (prog)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            //::usleep(VTISP_EFC_PROG_UNLOCK_DELAY);

            p_off = addr_iter - page_base;
            p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);

            //::printf("(%d bytes) ", p_size);  ::fflush(stdout);

            // read one page of image data ...
            ::memcpy(&pkt._data_out[8], data_iter, p_size);
            data_iter += p_size;

            // compose the packet (command) and send it out ...
            pkt.do_cmd_word_write(addr_iter, NULL, p_size / 4, true);

            if (pkt.send_out() < 0) {
                ::printf("programming failed\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            ::usleep(VTISP_WORD_WRITE_DELAY(p_size));

            // done flashing and re-lock the page
            if (efc.page_lock(pkt, page_base) < 0) {
                ::printf("lock failed (prog)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            }

            //::usleep(VTISP_EFC_PROG_LOCK_DELAY);
        }

        //::printf("ok");  ::fflush(stdout);

        addr_iter += p_size;
    }

    // verification
    ::printf("\n\nverifying %s (0x%08x - 0x%08x size 0x%08x) ...\n\n", infb ? "infb" : "memb", addr_b, addr_e, addr_e - addr_b);  ::fflush(stdout);

    addr_iter = addr_b;
    data_iter = (uint8_t *)data;

    for (uint32_t p = page_b; (p <= page_e) && (addr_iter < addr_e); ++p) {

        ::printf("%s [0x%08x] page)%d -> ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, p);  ::fflush(stdout);

        uint32_t page_base = FTEFC_PAGE_BASE(efcblk_base, p);

        uint32_t p_off = addr_iter - page_base;
        uint32_t p_size = min(FTEFC_PAGE_SIZE - p_off, addr_e - addr_iter);
        uint32_t tmp_checksum = 0;

        // compose the packet (read-back command) and send it out ...
        pkt.do_cmd_read_checksum(addr_iter, p_size / 4);

        if (pkt.send_out() < 0) {
            ::printf("read-back failed !! \n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        //::printf("(%d bytes)", pkt._size_in - 5);  ::fflush(stdout);

        // verify the image ...
        for (uint32_t w = 0; w < (p_size / 4); ++w) {
            tmp_checksum += ((uint32_t *)data_iter)[w];
        }
        
        if(((uint32_t *)pkt._data_in)[1] != tmp_checksum){
            ::printf("(mismatch)\n"); ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        addr_iter += p_size;
        data_iter += p_size;
    }

    ::printf("\n");  ::fflush(stdout);

    //if (axisp_ctxt.reboot) {
    //    do_reboot();
    //}

_safe_exit:

    if (r < 0) {
        // try to capture exception dump messages, if any ...
        if (pkt.get_raw() > 0) {
            ::printf("\n\n");
            print_raw(pkt);
        }
    }

    return r;
}

int vtisp::prog_iram(uint32_t base, void *data, uint32_t size)
{
    vtisp_packet pkt(_fd_dev);

    int r;

    uint32_t addr_b = base;
    uint32_t addr_e = base + size;

    uint32_t nr_writes = ((addr_e - addr_b) + (VTISP_IRAM_BURST_SIZE - 1)) / VTISP_IRAM_BURST_SIZE;

    // programming ...
    ::printf("\nprogramming iram (0x%08x ~ 0x%08x size 0x%08x) ...\n\n", addr_b, addr_e, size);  ::fflush(stdout);

    uint32_t addr_iter = addr_b;
    uint8_t *data_iter = (uint8_t *)data;

    for (uint32_t i = 0; i < nr_writes; ++i) {

        ::printf("%s [0x%08x] burst)%d <- ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, i);  ::fflush(stdout);

        uint32_t p_size = min(VTISP_IRAM_BURST_SIZE, addr_e - addr_iter);

        ::printf("(%d bytes) ", p_size);  ::fflush(stdout);

        // read a batch burst of image data ...
        ::memcpy(&pkt._data_out[8], data_iter, p_size);
        data_iter += p_size;

        // compose the packet (command) and send it out ...
        pkt.do_cmd_word_write(addr_iter, NULL, p_size / 4);

        if (pkt.send_out() < 0) {
            ::printf("programming failed\n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        ::printf("ok");  ::fflush(stdout);

        addr_iter += p_size;

        ::usleep(VTISP_WORD_WRITE_DELAY(p_size));
    }

    // verification
    ::printf("\nverifying iram (0x%08x - 0x%08x size 0x%08x) ...\n\n", addr_b, addr_e, addr_e - addr_b);  ::fflush(stdout);

    addr_iter = addr_b;
    data_iter = (uint8_t *)data;

    for (uint32_t i = 0; i < nr_writes; ++i) {

        ::printf("%s [0x%08x] burst)%d -> ", axisp_ctxt.verbose ? "\n" : "\r", addr_iter, i);  ::fflush(stdout);

        uint32_t p_size = min(VTISP_IRAM_BURST_SIZE, addr_e - addr_iter);

        // compose the packet (read-back command) and send it out ...
        pkt.do_cmd_word_read(addr_iter, p_size / 4);

        if (pkt.send_out() < 0) {
            ::printf("read-back failed !! \n");  ::fflush(stdout);
            r = -1;
            goto _safe_exit;
        }

        ::printf("(%d bytes)", pkt._size_in - 5);  ::fflush(stdout);

        // verify the image ...
        for (uint32_t w = 0; w < (p_size / 4); ++w) {

            ::printf("%s [0x%08x] burst)%d -> off)0x%04x|0x%08x <-> image)0x%08x|0x%08x ", axisp_ctxt.verbose ? "\n" : "\r",
                addr_iter, i, w * 4, ((uint32_t *)pkt._data_in)[w + 1], addr_iter - addr_b + w * 4, ((uint32_t *)data_iter)[w]);  ::fflush(stdout);

            if (((uint32_t *)pkt._data_in)[w + 1] != ((uint32_t *)data_iter)[w]) {
                ::printf("(mismatch)\n");  ::fflush(stdout);
                r = -1;
                goto _safe_exit;
            } else {
                ::printf("(ok)");  ::fflush(stdout);
            }
        }

        addr_iter += p_size;
        data_iter += p_size;
    }

    ::printf("\n");  ::fflush(stdout);

_safe_exit:

    if (r < 0) {
        // try to capture exception dump messages, if any ...
        if (pkt.get_raw() > 0) {
            ::printf("\n\n");
            print_raw(pkt);
        }
    }

    return r;
}

int vtisp::do_eflash_isp(bin_object &bin_obj)
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
        return -1;
    }

    if (infi.magic != 0x6970676d) {
        ::printf("\n[err] unknown image-format!\n");
        return -1;
    }

    uint32_t remap = 0;

    int r = do_remap_get(remap);
    if (r < 0)
        return -1;

    if (prog_eflash(false, remap, 0, bin_obj.offset(infi.infi_size, true), infi.image_size - infi.infi_size) < 0)
        return -1;

    return prog_eflash(true, remap, 0, bin_obj.offset(0, true), infi.infi_size);
}

int vtisp::do_eflash_fast_isp(bin_object &bin_obj)
{

/* chenying test

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
        return -1;
    }

    if (infi.magic != 0x6970676d) {
        ::printf("\n[err] unknown image-format!\n");
        return -1;
    }

    uint32_t remap = 0;

    int r = do_remap_get(remap);
    if (r < 0)
        return -1;
*/
	/* chenying test */
    int r;


    r = vtefc_init(2);
    if (r < 0)
        return r;
  
	sleep(1);
	
	/* chenying test */	
	return prog_eflash_raw(bin_obj);

	
return 1;
/* chenying test

    // chip erase tooks about 650ms
    ::usleep(5000*1000);

    // program info block 1st
    if (prog_eflash_fast(true, remap, 0, bin_obj.offset(0, true), infi.infi_size) < 0)
        return -1;

    return prog_eflash_fast(false, remap, 0, bin_obj.offset(infi.infi_size, true), infi.image_size - infi.infi_size);
*/

}

int vtisp::do_eflash_sum_isp(bin_object &bin_obj)
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
        return -1;
    }

    if (infi.magic != 0x6970676d) {
        ::printf("\n[err] unknown image-format!\n");
        return -1;
    }

    uint32_t remap = 0;

    int r = do_remap_get(remap);
    if (r < 0)
        return -1;

    if (prog_eflash_sum(false, remap, 0, bin_obj.offset(infi.infi_size, true), infi.image_size - infi.infi_size) < 0)
        return -1;

    return prog_eflash_sum(true, remap, 0, bin_obj.offset(0, true), infi.infi_size);
}

int vtisp::do_raw_isp(bin_object &bin_obj, uint32_t addr)
{
    uint32_t remap = 0;


	/* chenying test 
    int r = do_remap_get(remap);
    if (r < 0)
        return -1;
	*/	

	
    uint32_t efc_memb_base = FTEFC_MEMB_BASE;
    uint32_t efc_memb_limit = FTEFC_MEMB_BASE + FTEFC_MEMB_SIZE;

    uint32_t efc_infb_base = FTEFC_INFB_BASE;
    uint32_t efc_infb_limit = FTEFC_INFB_BASE + FTEFC_INFB_SIZE;

	/* chenying test 

    if (remap == 2) {
        efc_memb_base -= FTREG_BASE_EFC;
        efc_memb_limit -= FTREG_BASE_EFC;

        efc_infb_base -= FTREG_BASE_EFC;
        efc_infb_limit -= FTREG_BASE_EFC;
    }
	*/

	::printf("\naddr 0x%x\n\n",addr);
	::printf("\nefc_memb_base 0x%x\n\n",efc_memb_base);
	::printf("\nefc_memb_limit 0x%x\n\n",efc_memb_limit);
	
    if ((addr >= efc_memb_base) && (addr < efc_memb_limit)) {
        return prog_eflash(false, remap, 0, bin_obj.offset(0, true), bin_obj.size());
    } else if ((addr >= efc_infb_base) && (addr < efc_infb_limit)) {
        return prog_eflash(true, remap, 0, bin_obj.offset(0, true), bin_obj.size());
    }

    return prog_iram(addr, bin_obj.offset(0, true), bin_obj.size());
}

int vtisp::do_isp()
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

    bool raw_isp = false;
    uint32_t raw_isp_addr = 0;

    if (axisp_ctxt.isp_nr_args >= 2) {

        const char *sz_addr = axisp_ctxt.isp_args[2];

        if (::axisp_context::validate_hex(sz_addr)) {
            ::printf("\n[err] invalid isp target address!\n\n");
            return -1;
        }

        raw_isp_addr = ::strtoul(sz_addr, 0, 16);

        raw_isp = true;
    }

    bin_object bin_obj;

    int r = bin_obj.open(sz_image);
    if (r < 0) {
        ::printf("\nfailed to open binary image !!\n\n");
        return -1;
    }

    if (raw_isp) {
		::printf("raw isp\n\n");
        r = do_raw_isp(bin_obj, raw_isp_addr);
    } else {
    ::printf("eflash isp\n\n");
        r = do_eflash_isp(bin_obj);
    }

    bin_obj.close();

    return r;
}

int vtisp::do_fastisp()
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

    bool raw_isp = false;
    uint32_t raw_isp_addr = 0;


    if (axisp_ctxt.isp_nr_args >= 2) {

        const char *sz_addr = axisp_ctxt.isp_args[2];

        if (::axisp_context::validate_hex(sz_addr)) {
            ::printf("\n[err] invalid isp target address!\n\n");
            return -1;
        }

        raw_isp_addr = ::strtoul(sz_addr, 0, 16);
		
        raw_isp = true;
    }

    bin_object bin_obj;
	

    int r = bin_obj.open(sz_image);
    if (r < 0) {
        ::printf("\nfailed to open binary image !!\n\n");
        return -1;
    }

    if (raw_isp) {
		
        r = do_raw_isp(bin_obj, raw_isp_addr);
    } else {

	
        r = do_eflash_fast_isp(bin_obj);
		
    }

    bin_obj.close();
	

    return r;
}

int vtisp::do_sumisp()
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

    bool raw_isp = false;
    uint32_t raw_isp_addr = 0;

    if (axisp_ctxt.isp_nr_args >= 2) {

        const char *sz_addr = axisp_ctxt.isp_args[2];

        if (::axisp_context::validate_hex(sz_addr)) {
            ::printf("\n[err] invalid isp target address!\n\n");
            return -1;
        }

        raw_isp_addr = ::strtoul(sz_addr, 0, 16);

        raw_isp = true;
    }

    bin_object bin_obj;

    int r = bin_obj.open(sz_image);
    if (r < 0) {
        ::printf("\nfailed to open binary image !!\n\n");
        return -1;
    }

    if (raw_isp) {
        r = do_raw_isp(bin_obj, raw_isp_addr);
    } else {
        r = do_eflash_sum_isp(bin_obj);
    }

    bin_obj.close();

    return r;
}

int vtisp::do_reboot()
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

    int r = 0;
    uint32_t remap = ::strtoul(sz_remap, 0, 10);

    vtisp_packet pkt(_fd_dev);

    if (remap > 2) {

        if (remap != 9) {
            ::printf("\n[err] invalid remap value!\n\n");
            return -1;
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
        if ((r < 0) || (pkt._data_in[1] != 0)) {
            ::printf("(failed) ");
            ::printf("ack-pkt status)0x%02x size)0x%04x\n", (uint32_t)pkt._data_in[1], pkt._size_in);
            return -1;
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
        return -1;
    }

    ::printf("(ok)\n");

    if (remap <= 2) {
        // waiting for boot-up messages ...
        ::printf("\nwaiting for bootup message ... ");  ::fflush(stdout);

        if (pkt.get_raw() > 0) {
            ::printf("(%d chars)\n\n", pkt._size_in);
            print_raw(pkt);
        } else {
            ::printf("\n\nno bootup messages !!\n");  ::fflush(stdout);
        }
    }

    return 0;
}

int vtisp::do_cli_cmd()
{
    vtisp_packet pkt(_fd_dev);

    uint32_t cmd_length = (uint32_t)::strlen(axisp_ctxt.isp_args[1]);

    if (cmd_length == 0)
        return 0;

    if (cmd_length > vtisp_packet::VTISP_RAW_DATA_SIZE - 4) {
        cmd_length = vtisp_packet::VTISP_RAW_DATA_SIZE - 4;
    }

    ::memcpy(pkt._data_out, axisp_ctxt.isp_args[1], cmd_length);

    ::strcat((char *)pkt._data_out, "\r\n");
    pkt._size_out = (uint32_t)::strlen((const char *)pkt._data_out);

    // ignore ack-back messages since target is not supposed to be in the isp mode
    int r = pkt.send_out(false);
    if (r < 0) {
        ::printf("failed to send out request!!\n");
        return -1;
    }

    // waiting for cli command messages ...

    ::printf("\nwaiting for CLI command return message ... ");  ::fflush(stdout);

    if (pkt.get_raw() > 0) {
        ::printf("(%d chars)\n\n", pkt._size_in);
        print_raw(pkt);
    } else {
        ::printf("\n\nno return messages !!\n");  ::fflush(stdout);
    }

    return 0;
}

int vtisp::do_ping()
{
    vtisp_packet pkt(_fd_dev);

	::printf("vtisp::do_ping -> ");
	

    pkt.do_cmd_ping();

    ::printf("ping -> ");

    int r = pkt.send_out();
    if ((r < 0) || (pkt._data_in[1] != 0)) {
        ::printf("failed!! ");
        ::printf("ack-pkt status)0x%02x size)0x%04x\n", (uint32_t)pkt._data_in[1], pkt._size_in);
        return r;
    }

    ::printf("acked\n");

    return 0;
}

int vtisp::do_break()
{
    vtisp_packet pkt(_fd_dev);

    pkt.do_cmd_break();

    ::printf("break -> ");

    int r = pkt.send_out();
    if ((r < 0) || (pkt._data_in[1] != 0)) {
        ::printf("failed!! ");
        ::printf("ack-pkt status)0x%02x size)0x%04x\n", (uint32_t)pkt._data_in[1], pkt._size_in);
        return r;
    }

    ::printf("acked\n");

    // waiting for cli command messages ...

    ::printf("\nwaiting for CLI command return message ... ");  ::fflush(stdout);

    if (pkt.get_raw() > 0) {
        ::printf("(%d chars)\n\n", pkt._size_in);
        print_raw(pkt);
    } else {
        ::printf("\n\nno return messages !!\n");  ::fflush(stdout);
    }

    return 0;
}

int vtisp::do_setup()
{
    return 0;
}
