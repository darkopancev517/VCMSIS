/*
 * Copyright (c) 2015, Vango Technologies, Inc. - http://www.vangotech.com/tw/
 * All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "vtisp.h"
#include "vtspisp.h"
#include "ftefc.h"

// ---------------------------------------------------------------------------

uint32_t ftefc::sector_unlock(isp_packet &pkt, uint32_t blk_base, uint32_t sector, bool erase)
{
    uint32_t sector_base = FTEFC_SECTOR_BASE(blk_base, sector) + (erase ? FTEFC_ERASE_OFFSET : 0);

    pkt.do_cmd_word_write(sector_base, (erase ? (uint32_t)FTEFC_KEY_SECTOR_ERASE : (uint32_t)FTEFC_KEY_PROG));

    if (pkt.send_out() < 0)
        return (uint32_t)-1;

    return sector_base;
}

uint32_t ftefc::page_unlock(isp_packet &pkt, uint32_t blk_base, uint32_t page, bool erase)
{
    uint32_t page_base = FTEFC_PAGE_BASE(blk_base, page) + (erase ? FTEFC_ERASE_OFFSET : 0);

    pkt.do_cmd_word_write(page_base, (erase ? (uint32_t)FTEFC_KEY_PAGE_ERASE : (uint32_t)FTEFC_KEY_PROG));

    if (pkt.send_out() < 0)
        return (uint32_t)-1;

    return page_base;
}

uint32_t ftefc::page_unlock(isp_packet &pkt, uint32_t blk_base, uint32_t page)
{
    uint32_t page_base = FTEFC_PAGE_BASE(blk_base, page);

    pkt.do_cmd_word_write(page_base, (uint32_t)FTEFC_KEY_WRONLY);

    if (pkt.send_out() < 0)
        return (uint32_t)-1;

    return page_base;
}

int ftefc::access_lock(isp_packet &pkt, uint32_t base)
{
    pkt.do_cmd_word_write(base, FTEFC_KEY_LOCK);

    return pkt.send_out();
}

int ftefc::access_lock_DMA(isp_packet &pkt, uint32_t base)
{
    pkt.do_cmd_word_write(base, FTEFC_KEY_LOCK, true);

    return pkt.send_out();
}

int ftefc::mass_erase(isp_packet &pkt, bool infb)
{
    if (infb) {
        pkt.do_cmd_word_write((uint32_t)FTEFC_MASS_ERASE_BASE, (uint32_t)FTEFC_KEY_MASS_ERASE);

        if (pkt.send_out() < 0)
            return -1;

        ::usleep(100000);

        pkt.do_cmd_word_write((uint32_t)FTEFC_MASS_ERASE_BASE, (uint32_t)FTEFC_KEY_LOCK);

        return pkt.send_out();
    }

    pkt.do_cmd_word_write((uint32_t)FTEFC_MEMB_MASS_ERASE_BASE, (uint32_t)FTEFC_KEY_MASS_ERASE);

    if (pkt.send_out() < 0)
        return -1;

    ::usleep(100000);

    pkt.do_cmd_word_write((uint32_t)FTEFC_MASS_ERASE_BASE, (uint32_t)FTEFC_KEY_LOCK);

    return pkt.send_out();
}

