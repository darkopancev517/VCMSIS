// Intel Hexadecimal Object File Reader
//
// [2014-??-??]
//
//

#ifndef __MAKE_IMAGE_INC__
#define __MAKE_IMAGE_INC__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "bin_object.h"

#ifndef MAX_PATH
#define MAX_PATH                256
#endif

//#define DSP_VERSION_IMAGE       "dsp_version.bin"

//==== Magpie 
//#define DSP_IRAM_BASE         0xa0200000
//#define DSP_DATA0_BASE        0xa0220000
//#define DSP_DATA1_BASE        0xa0240000

//==== Phoenix 1 (VC6320)
//#define DSP_IRAM_BASE        	0x20080000
//#define DSP_DATA0_BASE        0x200C0000
//#define DSP_DATA1_BASE        0x200E0000

//==== Phoenix 2 (VC6330)
#define DSP_IRAM_BASE        	0x20110000
#define DSP_DATA0_BASE        0x20150000
#define DSP_DATA1_BASE        0x20170000

#define DSP_LZMA_INFO         0x76907765  //LZMA
#define DSP_UNLZMA_BASE       0x73826577  //BASE

enum DSP_RELOC_CAT {
    DSP_LZMA_INFO_IRAM = 1,           
    DSP_LZMA_INFO_DATA0,           
    DSP_LZMA_INFO_DATA1,           
    DSP_LZMA_IRAM,           
    DSP_LZMA_DATA0,           
    DSP_LZMA_DATA1,
};

// bootloader 16K + main partition 512K = 528K
//#define REMAP2_IMAGE_SOC_MAX    0x80000
//#define REMAP2_IMAGE_BOOTLOADER_MAX    0x4000
#define IMAGE_HEADER_SIZE       0x800
#define LINE_BUFF_SIZE          256

#define DSP_NR_INFO_SLOTS       19                      // 20 - 1 version slot

class mkimg
{
public:

    struct dsp_section
    {
        char        sz_image[MAX_PATH];
        uint32_t    region;
        uint32_t    offset;
        uint32_t    size;
        uint32_t    size_image;
        uint32_t    size_out;

        bin_object  f_image;

        struct dsp_section  *prev;
        struct dsp_section  *next;

        dsp_section() : offset(0), size(0), size_image(0), size_out(0), prev(NULL), next(NULL)
        {
            sz_image[0] = 0;
        }

        ~dsp_section() {
            f_image.close();
        }

        void detach() {
            if (this->prev != NULL)
                this->prev->next = this->next;
            if (this->next != NULL)
                this->next->prev = this->prev;

            this->prev = NULL;
            this->next = NULL;
        }

        void attach_before(struct dsp_section *s) {
            if (s->prev != NULL)
                s->prev->next = this;
            this->prev = s->prev;
            this->next = s;
            s->prev = this;
        }

        void attach_after(struct dsp_section *s) {
            if (s->next != NULL)
                s->next->prev = this;
            this->next = s->next;
            this->prev = s;
            s->next = this;
        }
    };

    uint8_t dsp_version[16];

    struct dsp_section *list_iram;
    struct dsp_section *list_data0;
    struct dsp_section *list_data1;
    struct dsp_section *list_compressed;

    uint32_t nr_iram_slots;
    uint32_t nr_data0_slots;
    uint32_t nr_data1_slots;
    uint32_t nr_compressed_slots;

public:

    mkimg();
    virtual ~mkimg();

    int do_make_image();

private:

    int do_dsp_version(const char *sz_ver);
    int do_dsp_parsing();

    void release_sections(struct dsp_section *sect);
    void attach_section(struct dsp_section *sect);
    void dump_sections(struct dsp_section *list);
    int do_make_reloc_info(struct dsp_section *list_iram, uint32_t *&info_lma, uint32_t &image_lma, uint32_t flag);
    int do_binary_out(bin_object &f_out, struct dsp_section *list);

    bool comment_line(const uint8_t *line_buff);
    uint8_t *trim_spaces(uint8_t *line_buff);
    uint8_t *get_section_image(uint8_t *line_buff, uint8_t *sz_out, uint32_t out_size);
    uint8_t *get_section_region(uint8_t *line_buff, uint32_t &region);
    uint8_t *get_hex_value(uint8_t *line_buff, uint32_t &value);

};

#endif  // __MAKE_IMAGE_INC__

