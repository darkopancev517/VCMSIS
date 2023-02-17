/*
 * Copyright (c) 2015, Vango Technologies, Inc. - http://www.vangotech.com/tw/
 * All rights reserved.
 *
 */
/**
 * \addtogroup fa606te
 * @{
 *
 * \defgroup fa606te-efc fa606te eflash controller
 *
 * Driver for the fa606te eflash controller
 * @{
 *
 * \file
 * Header file for the fa606te eflash driver
 */
#ifndef __FA606TE_FTEFLASH_INC__
#define __FA606TE_FTEFLASH_INC__


// ----------------------------------------------------------------------------

#define FTREG_BASE_EFC                  0x04000000

#define FTEFC_MEMB_BASE                 ((FTREG_BASE_EFC))
#define FTEFC_INFB_BASE                 ((FTREG_BASE_EFC) + 0x00200000)

#define FTEFC_MEMB_ERASE_BASE           ((FTREG_BASE_EFC) + 0x00400000)
#define FTEFC_MEMB_ERASE_OFFSET         ((FTEFC_MEMB_ERASE_BASE) - (FTEFC_MEMB_BASE))

#define FTEFC_INFB_ERASE_BASE           ((FTREG_BASE_EFC) + 0x00600000)
#define FTEFC_INFB_ERASE_OFFSET         ((FTEFC_INFB_ERASE_BASE) - (FTEFC_INFB_BASE))

#if (FTEFC_MEMB_ERASE_OFFSET != FTEFC_INFB_ERASE_OFFSET)
#error "FTEFC_MEMB_ERASE_OFFSET != FTEFC_INFB_ERASE_OFFSET"
#define FTEFC_ERASE_OFFSET              0x00400000
#else
#define FTEFC_ERASE_OFFSET              FTEFC_MEMB_ERASE_OFFSET
#endif

#define FTEFC_MEMB_MASS_ERASE_BASE      ((FTREG_BASE_EFC) + 0x00800000)
#define FTEFC_MASS_ERASE_BASE           ((FTREG_BASE_EFC) + 0x00a00000)

#define FTEFC_CR_BASE                   ((FTREG_BASE_EFC) + 0x00c00000)

// ----------------------------------------------------------------------------

// eflash addressing mode
//
//                (sector)               (page)               (column)              (macro)           (byte)
//              haddr[17:15]          haddr[14:09]          haddr[08:04]          haddr[03:02]        haddr[01:00]
//          --------------------  --------------------  --------------------  --------------------  ------------------------------------
// macro_0   eflash_addr[13:11]    eflash_addr[10:05]    eflash_addr[04:00]          2'b00            2'b00 ~ 2'b11  (byte resolution)
// macro_1                                                                           2'b01            2'b00 ~ 2'b11
// macro_2                                                                           2'b10            2'b00 ~ 2'b11
// macro_3                                                                           2'b11            2'b00 ~ 2'b11
//

#define FTEFC_NR_MACROS                 (4)     // number of macros (should == FTEFC_REG_HW_ATTR1::NR_MACROS) (todo: using register setting instead of hard-coded here ??)

#define FTEFC_COLUMN_WIDTH              (5)     // 5-bit addressing resolution (should == FTEFC_REG_HW_ATTR1::COL_WIDTH) (todo: using register setting instead of hard-coded here ??)
#define FTEFC_PAGE_WIDTH                (6)     // 6-bit addressing resolution (should == FTEFC_REG_HW_ATTR1::PAG_WIDTH) (todo: using register setting instead of hard-coded here ??)
#define FTEFC_SECTOR_WIDTH              (3)     // 3-bit addressing resolution (should == FTEFC_REG_HW_ATTR1::SEC_WIDTH) (todo: using register setting instead of hard-coded here ??)

#define FTEFC_BYTES_PER_COLUMN          (4)
#define FTEFC_COLUMN_SIZE               ((uint32_t)(FTEFC_BYTES_PER_COLUMN) * (FTEFC_NR_MACROS))

#define FTEFC_COLUMNS_PER_PAGE          (32)
#define FTEFC_PAGE_SIZE                 ((uint32_t)(FTEFC_COLUMN_SIZE) * (FTEFC_COLUMNS_PER_PAGE))

#define FTEFC_PAGES_PER_SECTOR          (64)
#define FTEFC_SECTOR_SIZE               ((uint32_t)(FTEFC_PAGE_SIZE) * (FTEFC_PAGES_PER_SECTOR))
#define FTEFC_SECTOR_BASE(b,s)          ((uint32_t)(b) + (FTEFC_SECTOR_SIZE) * (s))

#define FTEFC_MEMB_NR_SECTORS           (8)
#define FTEFC_MEMB_NR_PAGES             ((uint32_t)(FTEFC_MEMB_NR_SECTORS) * (FTEFC_PAGES_PER_SECTOR))
#define FTEFC_MEMB_SIZE                 ((uint32_t)(FTEFC_MEMB_NR_SECTORS) * (FTEFC_SECTOR_SIZE))
#define FTEFC_MEMB_PAGE_BASE(p)         ((uint32_t)(FTEFC_MEMB_BASE) + (FTEFC_PAGE_SIZE) * (p))

#define FTEFC_INFB_NR_PAGES             (16)
#define FTEFC_INFB_SIZE                 ((uint32_t)(FTEFC_INFB_NR_PAGES) * (FTEFC_PAGE_SIZE))
#define FTEFC_INFB_PAGE_BASE(p)         ((uint32_t)(FTEFC_INFB_BASE) + (FTEFC_PAGE_SIZE) * (p))

#define FTEFC_PAGE_BASE(b,p)            ((uint32_t)(b) + (FTEFC_PAGE_SIZE) * (p))

// ----------------------------------------------------------------------------

class isp_packet;

class ftefc
{
public:

    enum FTEFC_CMD_KEY
    {
        // unlock keys ...
        FTEFC_KEY_SECTOR_ERASE      = 0x30,
        FTEFC_KEY_PAGE_ERASE        = 0x20,
        FTEFC_KEY_MASS_ERASE        = 0x20,
        FTEFC_KEY_WRONLY            = 0xe8,     // 1  -> 0  (should do erase before performing this action, 2ms)
        FTEFC_KEY_PROG              = 0xf8,     // 1 <-> 0  (auto-erase, 5ms)

        // lock keys ...
        FTEFC_KEY_LOCK              = 0xd0,
    };

public:

    ftefc() {}
    ~ftefc() {}

    // sector functions only works for the main memory block
    uint32_t sector_unlock(isp_packet &pkt, uint32_t blk_base, uint32_t sector, bool erase);

    // page functions works for both the main memory block and the info block
    uint32_t page_unlock(isp_packet &pkt, uint32_t blk_base, uint32_t page, bool erase);  // PROG / ERASE
    uint32_t page_unlock(isp_packet &pkt, uint32_t blk_base, uint32_t page);  // WRONLY

    // finalize/lock-back all erase- and access-unlock functions
    int access_lock(isp_packet &pkt, uint32_t base);
    int access_lock_DMA(isp_packet &pkt, uint32_t base);
    int sector_lock(isp_packet &pkt, uint32_t base)  { return access_lock(pkt, base); }
    int page_lock(isp_packet &pkt, uint32_t base)  { return access_lock(pkt, base); }
    int page_lock_DMA(isp_packet &pkt, uint32_t base)  { return access_lock_DMA(pkt, base); }

    // utility functions
    int mass_erase(isp_packet &pkt, bool infb);
};

/** @} */

#endif  // __FA606TE_FTEFLASH_INC__

/**
 * @}
 * @}
 */
