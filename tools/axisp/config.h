/* (c)copyright axif-axisp, 2012 */

#ifndef __AXISP_CONFIG_INC__
#define __AXISP_CONFIG_INC__

#define CONFIG_PROGRAM                          "axisp"
#define CONFIG_VERSION                          "0.0.3.3"

#if 0
#ifdef __cplusplus
#define __EXTERN__ extern "C"
#else
#define __EXTERN__ extern
#endif
#endif

#ifndef CONFIG_MAX_PATH
#define CONFIG_MAX_PATH                         256
#endif

#ifndef CONFIG_MAX_ARGS
#define CONFIG_MAX_ARGS                         16
#endif

#define CONFIG_DEFAULT_SERIAL_DEVICE            "/dev/ttyUSB2"
#define CONFIG_DEFAULT_SERIAL_BAUDRATE        115200// 9600// 28800//115200

#define CONFIG_DEFAULT_SPI_INTERFACE            1 //1: IFACE_A, 2: IFACE_B, 3: IFACE_C, 4: IFACE_D


//#define CONFIG_DEFAULT_SPI_DEVICE               0
//#define CONFIG_DEFAULT_SPI_DATARATE             4800000
#define CONFIG_DEFAULT_SPI_DATARATE             1200000

#define CONFIG_DEFAULT_I2C_DATARATE             100000

//#include "isp.h"

#include <stdint.h>
#include <stdbool.h>

struct axisp_context
{
    char            fname_dev[CONFIG_MAX_PATH];
    uint32_t        data_rate;
    uint32_t        hw_if;                     // enum IFACE_A~D
    uint32_t        interface;                 // 0)serial 1)SPI 2)SPI_Probe
    uint32_t        protocol;                  // 0)xmodem 1)vtisp
    bool            erase_prog;                // do page erase before programming
    bool            reboot;                    // reboot after isp
    bool            verbose;
    bool            dev_list;

    class isp       *isp_obj;

    //enum AXISP_CMD  isp_cmd;
    int             isp_nr_args;
    char            isp_args[CONFIG_MAX_ARGS][CONFIG_MAX_PATH];


    axisp_context() : data_rate(CONFIG_DEFAULT_SERIAL_BAUDRATE),hw_if(CONFIG_DEFAULT_SPI_INTERFACE),
                      interface(0), protocol(0), erase_prog(false), reboot(true), verbose(false), dev_list(false),
                      isp_obj(NULL), isp_nr_args(0)
    {
        ::strncpy(fname_dev, CONFIG_DEFAULT_SERIAL_DEVICE, CONFIG_MAX_PATH);

        for (int i = 0; i < CONFIG_MAX_ARGS; ++i) {
            isp_args[i][0] = 0;
        }
    }

    ~axisp_context() {}

    static int validate_hex(const char *sz_nr);
    static int validate_dec(const char *sz_nr);
};

extern struct axisp_context axisp_ctxt;

#endif  // __AXISP_CONFIG_INC__
