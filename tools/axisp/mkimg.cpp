
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "config.h"
#include "mkimg.h"

mkimg::mkimg()
{
    ::memset(dsp_version, 0, 16);

    list_iram = NULL;
    list_data0 = NULL;
    list_data1 = NULL;
    list_compressed = NULL;

    nr_iram_slots = 0;
    nr_data0_slots = 0;
    nr_data1_slots = 0;
    nr_compressed_slots = 0;
}

mkimg::~mkimg()
{
    release_sections(list_iram);
    release_sections(list_data0);
    release_sections(list_data1);
    release_sections(list_compressed);
}

void mkimg::release_sections(struct dsp_section *sect)
{
    while (sect != NULL) {
        struct dsp_section *next = sect->next;
        delete sect;
        sect = next;
    }
}

void mkimg::dump_sections(struct dsp_section *list)
{
    while (list != NULL) {
        ::printf("  region)%08x offset)%08x size)%08x size_image)%08x size_out)%08x %s\n", list->region, list->offset, list->size, list->size_image, list->size_out, list->sz_image);
        list = list->next;
    }
}

void mkimg::attach_section(struct dsp_section *sect)
{
    struct dsp_section **list_head = NULL;

    switch (sect->region) {
    case DSP_IRAM_BASE:
        if (nr_iram_slots >= 19) {
            ::printf("[warning] info-slots is full (19 entreis max)! following section was dropped ...\n");
            ::printf("  region)%08x offset)%08x size)%08x size_image)%08x size_out)%08x %s\n", sect->region, sect->offset, sect->size, sect->size_image, sect->size_out, sect->sz_image);
            return;
        }
        ++nr_iram_slots;

        if (list_iram == NULL) {
            list_iram = sect;
            return;
        }

        list_head = &list_iram;
        break;

    case DSP_DATA0_BASE:
        if (nr_data0_slots >= 19) {
            ::printf("[warning] info-slots is full (19 entreis max)! following section was dropped ...\n");
            ::printf("  region)%08x offset)%08x size)%08x size_image)%08x size_out)%08x %s\n", sect->region, sect->offset, sect->size, sect->size_image, sect->size_out, sect->sz_image);
            return;
        }
        ++nr_data0_slots;

        if (list_data0 == NULL) {
            list_data0 = sect;
            return;
        }

        list_head = &list_data0;
        break;

    case DSP_DATA1_BASE:
        if (nr_data1_slots >= 19) {
            ::printf("[warning] info-slots is full (19 entreis max)! following section was dropped ...\n");
            ::printf("  region)%08x offset)%08x size)%08x size_image)%08x size_out)%08x %s\n", sect->region, sect->offset, sect->size, sect->size_image, sect->size_out, sect->sz_image);
            return;
        }
        ++nr_data1_slots;

        if (list_data1 == NULL) {
            list_data1 = sect;
            return;
        }

        list_head = &list_data1;
        break;

    case DSP_LZMA_INFO_IRAM:
    case DSP_LZMA_INFO_DATA0:
    case DSP_LZMA_INFO_DATA1:
    case DSP_LZMA_IRAM:
    case DSP_LZMA_DATA0:
    case DSP_LZMA_DATA1:
        if (nr_compressed_slots >= 19) {
            ::printf("[warning] info-slots is full (19 entreis max)! following section was dropped ...\n");
            ::printf("  region)%08x offset)%08x size)%08x size_image)%08x size_out)%08x %s\n", sect->region, sect->offset, sect->size, sect->size_image, sect->size_out, sect->sz_image);
            return;
        }
        ++nr_compressed_slots;

        if (list_compressed == NULL) {
            list_compressed = sect;
            return;
        }

        list_head = &list_compressed;
        break;
    }

    if (list_head == NULL)
        return;

    struct dsp_section *list_iter = *list_head;

    while (list_iter != NULL) {
        if (sect->offset >= list_iter->offset) {
            if (list_iter->next == NULL) {
                sect->attach_after(list_iter);
                break;
            }
            list_iter = list_iter->next;
            continue;
        }

        sect->attach_before(list_iter);
        if (list_iter == *list_head)
            *list_head = sect;
        break;
    }
}

int mkimg::do_dsp_version(const char *sz_ver)
{
    int r = 0;

    bin_object f_ver;

    r = f_ver.open(sz_ver);
    if (r < 0)
        return r;

    r = f_ver.read(this->dsp_version, 16);
    if (r < 4)
        return -2;

    f_ver.close();

    return 0;
}

bool mkimg::comment_line(const uint8_t *line_buff)
{
    while (*line_buff != 0) {
        if (*line_buff == '#')
            return true;
        if (*line_buff != ' ')
            break;
        ++line_buff;
    }

    return false;
}

uint8_t *mkimg::trim_spaces(uint8_t *line_buff)
{
    while (*line_buff != 0) {
        if (*line_buff != ' ')
            break;
        ++line_buff;
    }

    return line_buff;
}

uint8_t *mkimg::get_section_image(uint8_t *line_buff, uint8_t *sz_out, uint32_t out_size)
{
    uint8_t *line_iter = line_buff;

    line_iter = trim_spaces(line_iter);
    if (*line_iter == 0)
        return NULL;

    line_buff = line_iter;

    while (*line_iter != 0) {
        if (*line_iter == ' ') {
            break;
        }
        ++line_iter;
    }

    *line_iter++ = 0;

    uint32_t copy_size = (uint32_t)::strlen((const char *)line_buff);
    if (copy_size > out_size)
        copy_size = out_size;

    if (copy_size == 0)
        return NULL;

    strcpy((char *)sz_out, (const char *)line_buff);

    return line_iter;
}

uint8_t *mkimg::get_section_region(uint8_t *line_buff, uint32_t &region)
{
    uint8_t *line_iter = line_buff;

    line_iter = trim_spaces(line_iter);
    if (*line_iter == 0)
        return NULL;

    line_buff = line_iter;

    while (*line_iter != 0) {
        if (*line_iter == ' ') {
            break;
        }
        ++line_iter;
    }

    *line_iter++ = 0;

    if (::strlen((const char *)line_buff) == 0)
        return NULL;

    if (::strcmp((const char *)line_buff, "iram") == 0) {
        region = DSP_IRAM_BASE;
 //   } else if (::strcmp((const char *)line_buff, "data0") == 0) {
 //       region = DSP_DATA0_BASE;
 //   } else if (::strcmp((const char *)line_buff, "data1") == 0) {
 //       region = DSP_DATA1_BASE;
 //   } else if (::strstr((const char *)line_buff, "z_iram")) {
 //       region = DSP_LZMA_INFO_IRAM;
//    } else if (::strstr((const char *)line_buff, "z_data0")) {
//        region = DSP_LZMA_INFO_DATA0;
//    } else if (::strstr((const char *)line_buff, "z_data1")) {
//        region = DSP_LZMA_INFO_DATA1;
    } else if (::strcmp((const char *)line_buff, "o_iram") == 0) {
       // region = DSP_LZMA_IRAM;
        region = DSP_IRAM_BASE;
    } else if (::strcmp((const char *)line_buff, "o_data0") == 0) {
        //region = DSP_LZMA_DATA0;
       region = DSP_DATA0_BASE;
    } else if (::strcmp((const char *)line_buff, "o_data1") == 0) {
       // region = DSP_LZMA_DATA1;
       region = DSP_DATA1_BASE;
    } else {
        return NULL;
    }

    return line_iter;
}

uint8_t *mkimg::get_hex_value(uint8_t *line_buff, uint32_t &value)
{
    uint8_t *line_iter = line_buff;

    line_iter = trim_spaces(line_iter);
    if (*line_iter == 0)
        return NULL;

    line_buff = line_iter;

    while (*line_iter != 0) {
        if (*line_iter == ' ') {
            break;
        }
        ++line_iter;
    }

    *line_iter++ = 0;

    if (::strlen((const char *)line_buff) == 0)
        return NULL;

    value = (uint32_t)::strtoul((const char *)line_buff, 0, 16);

    return line_iter;
}

int mkimg::do_dsp_parsing()
{
    uint8_t line_buff[LINE_BUFF_SIZE + 4];
    uint8_t *line_iter;
    int r = 0;

    struct dsp_section *sect = NULL;

    const char *sz_map = axisp_ctxt.isp_args[2];
    bin_object f_map;

    r = f_map.open(sz_map);
    if (r < 0) {
        ::printf("\n[err] failed to open dsp image map file: %s\n\n", sz_map);
        goto _safe_exit;
    }

    sect = new struct dsp_section();
    if (sect == NULL) {
        ::printf("\n[err] failed on allocating dsp section info\n\n");
        goto _safe_exit;
    }

    while (1) {

        ::memset(line_buff, 0, LINE_BUFF_SIZE + 4);

        r = f_map.read_line(line_buff, LINE_BUFF_SIZE);
        if (r == 0) {
            continue;
        } else if (r < 0) {
            r = 0;
            break;
        }

        if (comment_line(line_buff))
            continue;

        line_iter = get_section_image(line_buff, (uint8_t *)sect->sz_image, MAX_PATH);
        if (line_iter == NULL)
            continue;

        line_iter = get_section_region(line_iter, sect->region);
        if (line_iter == NULL)
            continue;

        line_iter = get_hex_value(line_iter, sect->offset);
        if (line_iter == NULL)
            continue;

        line_iter = get_hex_value(line_iter, sect->size);
        if (line_iter == NULL)
            continue;

        r = sect->f_image.open(sect->sz_image);
        if (r < 0) {
            ::printf("\n[err] failed on open image file: %s\n\n", sect->sz_image);
            r = -1;
            goto _safe_exit;
        }

        sect->size_image = sect->f_image._size;

        //sect->size_out = sect->size;
        //if (sect->size_out < sect->f_image._size)
            sect->size_out = sect->f_image._size;
        sect->size_out = (sect->size_out + 15) & ~15;

        attach_section(sect);

        sect = new struct dsp_section();
        if (sect == NULL) {
            ::printf("\n[err] failed on allocating dsp section info\n\n");
            r = -1;
            goto _safe_exit;
        }
    }

_safe_exit:

    if (sect != NULL)
        delete sect;

    f_map.close();

    if (r >= 0) {
        ::printf("\niram sections ...\n");
        dump_sections(list_iram);
        ::printf("\ndata0 sections ...\n");
        dump_sections(list_data0);
        ::printf("\ndata1 sections ...\n");
        dump_sections(list_data1);
        ::printf("\ncompressed sections ...\n");
        dump_sections(list_compressed);
        ::printf("\n");
    }

    return r;
}

int mkimg::do_make_reloc_info(struct dsp_section *list, uint32_t *&info_lma, uint32_t &image_lma, uint32_t flag)
{
    struct dsp_section *sect = list;

    while (sect != NULL) {

        if (flag != DSP_IRAM_BASE){
            if (sect->region == DSP_LZMA_IRAM || sect->region == DSP_LZMA_INFO_IRAM){
                sect = sect->next;
                continue;
            }
        }

        if (flag != DSP_DATA0_BASE){
            if (sect->region == DSP_LZMA_DATA0 || sect->region == DSP_LZMA_INFO_DATA0){
                sect = sect->next;
                continue;
            }
        }    

        if (flag != DSP_DATA1_BASE){
            if (sect->region == DSP_LZMA_DATA1 || sect->region == DSP_LZMA_INFO_DATA1){
                sect = sect->next;
                continue;
            }
        }
        
        if (sect->region == DSP_LZMA_IRAM){
            //this section do not write data to flash
            info_lma[0] = DSP_IRAM_BASE + sect->offset;
            info_lma[1] = DSP_UNLZMA_BASE;
            info_lma[2] = (sect->size_image + 3) & ~3;
            sect->size_out = 0;
            info_lma[3] = sect->size_out;
        }else if (sect->region == DSP_LZMA_DATA0){
            //this section do not write data to flash
            info_lma[0] = DSP_DATA0_BASE + sect->offset;
            info_lma[1] = DSP_UNLZMA_BASE;
            info_lma[2] = (sect->size_image + 3) & ~3;
            sect->size_out = 0;
            info_lma[3] = sect->size_out;
        }else if (sect->region == DSP_LZMA_DATA1){
            //this section do not write data to flash
            info_lma[0] = DSP_DATA1_BASE + sect->offset;
            info_lma[1] = DSP_UNLZMA_BASE;
            info_lma[2] = (sect->size_image + 3) & ~3;
            sect->size_out = 0;
            info_lma[3] = sect->size_out;
        } else if (sect->region == DSP_LZMA_INFO_IRAM){
            info_lma[0] = DSP_LZMA_INFO;
            info_lma[1] = image_lma;
            info_lma[2] = (sect->size_image + 3) & ~3;
            info_lma[3] = sect->size_out;
        } else if (sect->region == DSP_LZMA_INFO_DATA0){
            info_lma[0] = DSP_LZMA_INFO;
            info_lma[1] = image_lma;
            info_lma[2] = (sect->size_image + 3) & ~3;
            info_lma[3] = sect->size_out;
        } else if (sect->region == DSP_LZMA_INFO_DATA1){
            info_lma[0] = DSP_LZMA_INFO;
            info_lma[1] = image_lma;
            info_lma[2] = (sect->size_image + 3) & ~3;
            info_lma[3] = sect->size_out;
        } else {
            info_lma[0] = sect->region + sect->offset;
            info_lma[1] = image_lma;
            info_lma[2] = (sect->size_image + 3) & ~3;
            info_lma[3] = sect->size_out;
       }

        ::printf("    vma)%08x lma)%08x size_dma)%08x size_out)%08x %s\n", info_lma[0], info_lma[1], info_lma[2], info_lma[3], sect->sz_image);

        info_lma += 4;
        image_lma += sect->size_out;
        sect = sect->next;
    }

    return 0;
}

int mkimg::do_binary_out(bin_object &f_out, struct dsp_section *list)
{
    uint8_t image_buff[IMAGE_HEADER_SIZE + 16];

    struct dsp_section *sect = list;

    while (sect != NULL) {

        sect->f_image.offset(0, true); //Tab Tseng added 16/07/18, need to read the same section twice

        if (sect->region == DSP_LZMA_IRAM 
            || sect->region == DSP_LZMA_DATA0
            || sect->region == DSP_LZMA_DATA1){
            //this section do not write data to flash
            sect = sect->next;
            continue;
        }

        while (1) {
            int r = sect->f_image.read(image_buff, IMAGE_HEADER_SIZE);
            if (r <= 0) {
                r = 0;
                break;
            }

            uint32_t copy_size = ((uint32_t)r + 15) & ~15;
            if (copy_size > (uint32_t)r)
                ::memset((void *)&image_buff[r], 0, (copy_size - r));

            r = f_out.write(image_buff, copy_size);
            if (r <= 0) {
                ::printf("  [err] failed to write output file!\n");
                return -1;
            }
        }

        sect = sect->next;
    }

    return 0;
}
#if 0
int mkimg::do_make_image()
{
    uint8_t image_buff[IMAGE_HEADER_SIZE + 16];
    uint32_t *info_lma = NULL;
    uint32_t image_lma = 0, image_size = 0;
    uint32_t bbp_iram_lma = 0, bbp_data0_lma = 0, bbp_data1_lma = 0;
    int r = 0;//, uint32_t id = 0;

    const char *sz_mcu = axisp_ctxt.isp_args[1];
    const char *sz_ver = axisp_ctxt.isp_args[3];
    const char *sz_out = axisp_ctxt.isp_args[4];
//    const char *sz_xzmcu = axisp_ctxt.isp_args[5];
    const char *sz_upg_info = "../../out/upg_info.bin";
    const char *sz_upg_soc = "../../out/upg_soc.bin";
    const char *sz_upg_bbp = "../../out/upg_bbp.bin";

    bin_object f_mcu, f_out, f_u_info, f_u_soc, f_u_bbp;

    if (axisp_ctxt.isp_nr_args < 5) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return -1;
    }

    //id = (uint32_t)::strtoul(sz_id, 0, 10);
    //if (id > 1) {
    //    ::printf("\n[err] invalid firmware slot id: %d\n\n", id);
    //    goto _safe_exit;
    //}

    r = do_dsp_version(sz_ver);
    if (r < 0) {
        ::printf("\n[err] failed to parse dsp version file: %s\n\n", sz_ver);
        goto _safe_exit;
    }

    r = do_dsp_parsing();
    if (r < 0) {
        ::printf("\n[err] failed to parse dsp image mapping file: %s\n\n", axisp_ctxt.isp_args[2]);
        goto _safe_exit;
    }

    r = f_mcu.open(sz_mcu);
    if (r < 0) {
        ::printf("\n[err] failed to open mcu image: %s\n\n", sz_mcu);
        goto _safe_exit;
    }

    r = f_u_info.open(sz_upg_info, true);
    if (r < 0) {
        ::printf("\n[err] failed to open output file: %s\n\n", sz_upg_info);
        goto _safe_exit;
    }

    r = f_u_bbp.open(sz_upg_bbp, true);
    if (r < 0) {
        ::printf("\n[err] failed to open output file: %s\n\n", sz_upg_bbp);
        goto _safe_exit;
    }

    r = f_u_soc.open(sz_upg_soc, true);
    if (r < 0) {
        ::printf("\n[err] failed to open output file: %s\n\n", sz_upg_soc);
        goto _safe_exit;
    }

    r = f_out.open(sz_out, true);
    if (r < 0) {
        ::printf("\n[err] failed to open output file: %s\n\n", sz_out);
        goto _safe_exit;
    }


    r = f_mcu.read(image_buff, IMAGE_HEADER_SIZE);
    if (r != IMAGE_HEADER_SIZE) {
        ::printf("\n[err] invalid image header!\n\n");
        r = -1;
        goto _safe_exit;
    }


//==============Write Header================================

    ::printf("updating image header ... \n");

    // __bbp_reloc
    info_lma = (uint32_t *)&image_buff[0x0c];  // __bbp_reloc
    *info_lma = 1;

    // __info_hb0
    info_lma = (uint32_t *)&image_buff[0xb0];  // bbp version
    ::memcpy((void *)info_lma, (void *)dsp_version, 16);
    info_lma += 4;

    //image_lma = ((f_mcu._size - IMAGE_HEADER_SIZE) + 15) & ~15;  //TabTseng removed, to fixed bbp start address 
   /image_lma = REMAP2_IMAGE_SOC_MAX;   // same as (IMAGE_BBP - 0x800(infoblock)) in remap2

	//image_lma =(f_mcu._size+ 15) & ~15;
	//image_lma +=0x800;

    bbp_iram_lma = image_lma;
    ::printf("\n  bbp_iram reloc info#0 ... lma_base)0x%08x\n", bbp_iram_lma);
    do_make_reloc_info(list_iram, info_lma, image_lma, 0);

    bbp_data0_lma = image_lma;
    ::printf("\n  bbp_data0 reloc info#0 ... lma_base)0x%08x\n", bbp_data0_lma);
    do_make_reloc_info(list_data0, info_lma, image_lma, 0);

    bbp_data1_lma = image_lma;
    ::printf("\n  bbp_data1 reloc info#0 ... lma_base)0x%08x\n", bbp_data1_lma);
    do_make_reloc_info(list_data1, info_lma, image_lma, 0);

    ::printf("\n  bbp_compress reloc info#1 ... lma_base)0x%08x\n", image_lma);
    do_make_reloc_info(list_compressed, info_lma, image_lma, DSP_DATA1_BASE);
    do_make_reloc_info(list_compressed, info_lma, image_lma, DSP_DATA0_BASE);
    do_make_reloc_info(list_compressed, info_lma, image_lma, DSP_IRAM_BASE);


    // __info_hb1
    info_lma = (uint32_t *)&image_buff[0x330];
    ::memcpy((void *)info_lma, (void *)dsp_version, 16);  // version
    info_lma += 4;

    image_lma = (image_lma + 15) &~15;

    bbp_iram_lma = image_lma;
    ::printf("\n  bbp_iram reloc info#1 ... lma_base)0x%08x\n", bbp_iram_lma);
    do_make_reloc_info(list_iram, info_lma, image_lma, 0);

    bbp_data0_lma = image_lma;
    ::printf("\n  bbp_data0 reloc info#1 ... lma_base)0x%08x\n", bbp_data0_lma);
    do_make_reloc_info(list_data0, info_lma, image_lma, 0);

    bbp_data1_lma = image_lma;
    ::printf("\n  bbp_data1 reloc info#1 ... lma_base)0x%08x\n", bbp_data1_lma);
    do_make_reloc_info(list_data1, info_lma, image_lma, 0);

    ::printf("\n  bbp_compress reloc info#1 ... lma_base)0x%08x\n", image_lma);
    do_make_reloc_info(list_compressed, info_lma, image_lma, DSP_DATA1_BASE);
    do_make_reloc_info(list_compressed, info_lma, image_lma, DSP_DATA0_BASE);
    do_make_reloc_info(list_compressed, info_lma, image_lma, DSP_IRAM_BASE);
#if 0
    // write compressed soc image info
    compressed_soc_lma = (image_lma + 15) & ~15;

    info_lma = (uint32_t *)&image_buff[0x80];
    *info_lma = compressed_soc_lma;
    info_lma = (uint32_t *)&image_buff[0x84];
    *info_lma = f_xzmcu._size;

    ::printf("\n  __compressed_soc #0 address... 0x%08x\n", compressed_soc_lma);
    ::printf("  __size_compressed_soc_ #0 vlaue... 0x%08x\n", f_xzmcu._size);

    info_lma = (uint32_t *)&image_buff[0x100];
    *info_lma = compressed_soc_lma;
    info_lma = (uint32_t *)&image_buff[0x104];
    *info_lma = f_xzmcu._size;

    ::printf("\n  __compressed_soc #1 address... 0x%08x\n", compressed_soc_lma);
    ::printf("  __size_compressed_soc_ #1 vlaue... 0x%08x\n", f_xzmcu._size);

    image_lma = compressed_soc_lma + ((f_xzmcu._size + 15) & ~15);
#endif
    // __image_size
    image_size = image_lma + IMAGE_HEADER_SIZE;

    info_lma = (uint32_t *)&image_buff[0x1c];  // __image_size
    *info_lma = image_size;

    ::printf("\n  final image size)0x%08x\n", image_size);





    // write out image header ...
    r = f_out.write(image_buff, IMAGE_HEADER_SIZE);
    if (r != IMAGE_HEADER_SIZE) {
        ::printf("  [err] failed to write output file: %s\n", sz_out);
        r = -1;
        goto _safe_exit;
    }

    // this is for upgrade image
    /* 
     * 2017/02/07, Tab modified, upgrade's info only h0+hb0
     */
    r = f_u_info.write(image_buff+0x30, 0x280);
    if (r != 0x280) {
        ::printf("  [err] failed to write output file: %s\n", sz_upg_soc);
        r = -1;
        goto _safe_exit;
    }

//====== Write Header



//====== Write SOC=======================

    ::printf("\nflushing out SoC #0 image binary ... ");

    // write out SoC image binary ...
    while (1) {

        r = f_mcu.read(image_buff, IMAGE_HEADER_SIZE);
        if (r <= 0) {
            r = 0;
            break;
        }

        uint32_t copy_size = ((uint32_t)r + 15) & ~15;
        if (copy_size > (uint32_t)r)
            ::memset((void *)&image_buff[r], 0, (copy_size - r));

        r = f_out.write(image_buff, copy_size);
        if (r <= 0) {
            ::printf("  [err] failed to write output file: %s\n", sz_out);
            r = -1;
            goto _safe_exit;
        }
        
        // for upgrade image
        r = f_u_soc.write(image_buff, copy_size);
        if (r <= 0) {
            ::printf("  [err] failed to write output file: %s\n", sz_out);
            r = -1;
            goto _safe_exit;
        }

    }

//====== Write SOC





	
    ::printf("  --->accumulate write %d btyes \n",f_out._size);
    ::printf("  done!\n\n");

    ::printf("flushing out BBP/DSP #0 image binaries ... ");

    r = f_out.seek(REMAP2_IMAGE_SOC_MAX+IMAGE_HEADER_SIZE);

    r = do_binary_out(f_out, list_iram);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_out, list_data0);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_out, list_data1);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_out, list_compressed);
    if (r < 0)
        goto _safe_exit;

    // for upgrade image
    r = do_binary_out(f_u_bbp, list_iram);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_u_bbp, list_data0);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_u_bbp, list_data1);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_u_bbp, list_compressed);
    if (r < 0)
        goto _safe_exit;

    ::printf("  --->accumulate write %d btyes \n",f_out._size);
    ::printf("  done!\n\n");
#if 0
    ::printf("flushing out BBP/DSP #1 image binaries ... ");
    r = do_binary_out(f_out, list_iram);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_out, list_compressed);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_out, list_data0);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_out, list_data1);
    if (r < 0)
        goto _safe_exit;

    ::printf("  --->accumulate %d btyes \n",f_out._size);
    ::printf("  done!\n\n");

    ::printf("flushing out compressed SoC #1 image binaries ... \n");
    while (1) {

        r = f_xzmcu.read(image_buff, IMAGE_HEADER_SIZE);
        if (r <= 0) {
            r = 0;
            break;
        }

        uint32_t copy_size = ((uint32_t)r + 15) & ~15;
        if (copy_size > (uint32_t)r)
            ::memset((void *)&image_buff[r], 0, (copy_size - r));

        r = f_out.write(image_buff, copy_size);
        if (r <= 0) {
            ::printf("  [err] failed to write output file: %s\n", sz_out);
            r = -1;
            goto _safe_exit;
        }
    }
#endif


_safe_exit:

    f_mcu.close();
    f_out.close();
    f_u_info.close();
    f_u_soc.close();
    f_u_bbp.close();

    return r;
}

#endif

int mkimg::do_make_image()
{
    uint8_t image_buff[IMAGE_HEADER_SIZE + 16];
    uint32_t *info_lma = NULL;
    uint32_t image_lma = 0, image_size = 0;
    uint32_t bbp_iram_lma = 0, bbp_data0_lma = 0, bbp_data1_lma = 0;
    int r = 0;//, uint32_t id = 0;

    const char *sz_mcu = axisp_ctxt.isp_args[1];
    const char *sz_ver = axisp_ctxt.isp_args[3];
    const char *sz_out = axisp_ctxt.isp_args[4];
#define REMAP2_IMAGE_SOC_MAX    		atol(axisp_ctxt.isp_args[6])//0x80000
#define REMAP2_IMAGE_BOOTLOADER_MAX 	atol(axisp_ctxt.isp_args[7])//0x4000
    bin_object f_mcu, f_out;

    if (axisp_ctxt.isp_nr_args < 5) {
        ::printf("\n[err] insufficient number of arguments!\n\n");
        return -1;
    }

    //id = (uint32_t)::strtoul(sz_id, 0, 10);
    //if (id > 1) {
    //    ::printf("\n[err] invalid firmware slot id: %d\n\n", id);
    //    goto _safe_exit;
    //}

    r = do_dsp_version(sz_ver);
    if (r < 0) {
        ::printf("\n[err] failed to parse dsp version file: %s\n\n", sz_ver);
        goto _safe_exit;
    }

    r = do_dsp_parsing();
    if (r < 0) {
        ::printf("\n[err] failed to parse dsp image mapping file: %s\n\n", axisp_ctxt.isp_args[2]);
        goto _safe_exit;
    }

    r = f_mcu.open(sz_mcu);
    if (r < 0) {
        ::printf("\n[err] failed to open mcu image: %s\n\n", sz_mcu);
        goto _safe_exit;
    }

    r = f_out.open(sz_out, true);
    if (r < 0) {
        ::printf("\n[err] failed to open output file: %s\n\n", sz_out);
        goto _safe_exit;
    }

//====== Write SOC=======================

    ::printf("\nflushing out SoC #0 image binary ... ");

    // write out SoC image binary ...
    while (1) {

        r = f_mcu.read(image_buff, IMAGE_HEADER_SIZE);
        if (r <= 0) {
            r = 0;
            break;
        }

        uint32_t copy_size = ((uint32_t)r + 15) & ~15;
        if (copy_size > (uint32_t)r)
            ::memset((void *)&image_buff[r], 0, (copy_size - r));

        r = f_out.write(image_buff, copy_size);
        if (r <= 0) {
            ::printf("  [err] failed to write output file: %s\n", sz_out);
            r = -1;
            goto _safe_exit;
        }
    }

//====== Write SOC

	
	//==============Write Header================================
	
		::printf("updating image header ... \n");

		::memset(image_buff, 0x00, sizeof(image_buff));
		
		// __bbp_reloc
		info_lma = (uint32_t *)&image_buff[0x0c];  // __bbp_reloc
		*info_lma = 1;
	
		// __info_hb0
		info_lma = (uint32_t *)&image_buff[0xb0];  // bbp version
		::memcpy((void *)info_lma, (void *)dsp_version, 16);
		info_lma += 4;
	
		//image_lma = ((f_mcu._size - IMAGE_HEADER_SIZE) + 15) & ~15;  //TabTseng removed, to fixed bbp start address 
	   	image_lma = REMAP2_IMAGE_SOC_MAX + IMAGE_HEADER_SIZE + REMAP2_IMAGE_BOOTLOADER_MAX;
	
		//image_lma =(f_mcu._size+ 15) & ~15;
		//image_lma +=0x800;
	
		bbp_iram_lma = image_lma;
		::printf("\n  bbp_iram reloc info#0 ... lma_base)0x%08x\n", bbp_iram_lma);
		do_make_reloc_info(list_iram, info_lma, image_lma, 0);
	
		bbp_data0_lma = image_lma;
		::printf("\n  bbp_data0 reloc info#0 ... lma_base)0x%08x\n", bbp_data0_lma);
		do_make_reloc_info(list_data0, info_lma, image_lma, 0);
	
		bbp_data1_lma = image_lma;
		::printf("\n  bbp_data1 reloc info#0 ... lma_base)0x%08x\n", bbp_data1_lma);
		do_make_reloc_info(list_data1, info_lma, image_lma, 0);
		
		// __info_hb1
		info_lma = (uint32_t *)&image_buff[0x330];
		::memcpy((void *)info_lma, (void *)dsp_version, 16);  // version
		info_lma += 4;
		
		image_lma = (image_lma + 15) &~15;
		// __image_size
		image_size = image_lma - (REMAP2_IMAGE_SOC_MAX + IMAGE_HEADER_SIZE  + REMAP2_IMAGE_BOOTLOADER_MAX);
		info_lma = (uint32_t *)&image_buff[0x1c];  // __image_size
		*info_lma = image_size;
	
		::printf("\n  final image size)0x%08x\n", image_size);
	
  //Clifford : to define the end of image file
  #define IMAGE_END	REMAP2_IMAGE_SOC_MAX
  
	r = f_out.seek(IMAGE_END);
#if 1
	
		// write out image header ...
		r = f_out.write(image_buff, IMAGE_HEADER_SIZE);
		if (r != IMAGE_HEADER_SIZE) {
			::printf("	[err] failed to write output file: %s\n", sz_out);
			r = -1;
			goto _safe_exit;
		}
#endif	
	//====== Write Header
	




	
    ::printf("  --->accumulate write %d btyes \n",f_out._size);
    ::printf("  done!\n\n");

    ::printf("flushing out BBP/DSP #0 image binaries ... ");
    //Clifford : to define the end of image file

    r = f_out.seek(IMAGE_END+IMAGE_HEADER_SIZE);

    r = do_binary_out(f_out, list_iram);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_out, list_data0);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_out, list_data1);
    if (r < 0)
        goto _safe_exit;

//+++ why need to duplicate data section!?
    r = do_binary_out(f_out, list_data0);
    if (r < 0)
        goto _safe_exit;

    r = do_binary_out(f_out, list_data1);
    if (r < 0)
        goto _safe_exit;
//---

    ::printf("  --->accumulate write %d btyes \n",f_out._size);
    ::printf("  done!\n\n");

_safe_exit:

    f_mcu.close();
    f_out.close();

    return r;
}



