#include "vc_plc_phy.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define DSP_DATA0_SIZE (0x14000UL)
#define DSP_DATA1_SIZE (0x14000UL)
#define DSP_IRAM_SIZE  (0x40000UL)

#define DSP_IRAM_BASE  (0x20080000UL)
#define DSP_DATA0_BASE (0x200C0000UL)
#define DSP_DATA1_BASE (0x200E0000UL)
#define DSP_END			   (0x20100000UL)

#define FLASH_START       (0x04000000UL)
#define FLASH_DSP_OFFSET  (0x00084000UL)
#define FLASH_IRAM_START  (FLASH_START + FLASH_DSP_OFFSET)
#define FLASH_DATA0_START (FLASH_IRAM_START + DSP_IRAM_SIZE)

static void phy_reset(bool release)
{
  uint32_t temp = 0;

  if (release)
  {
    temp |= 0x03;
  }
  else
  {
    temp &= 0x03;
  }

  VC_PLC_PHY->CR1 = temp;
}

void vc_plc_phy_init(void)
{
  phy_reset(false /* release */);

  // clear bbp memory
  memset((void *)DSP_IRAM_BASE, 0, DSP_IRAM_SIZE);
  memset((void *)DSP_DATA0_BASE, 0, DSP_DATA0_SIZE);
  memset((void *)DSP_DATA1_BASE, 0, DSP_DATA1_SIZE);

  // relocate bbp program and data
  memcpy((void *)DSP_IRAM_BASE, (void *)FLASH_IRAM_START, DSP_IRAM_SIZE);
  memcpy((void *)DSP_DATA0_BASE, (void *)FLASH_DATA0_START, DSP_DATA0_SIZE);

  if (memcmp((void *)DSP_IRAM_BASE, (void *)FLASH_IRAM_START, DSP_IRAM_SIZE) != 0)
  {
    printf("DSP IRAM load failed\r\n");
    while(1);
  }

  if (memcmp((void *)DSP_DATA0_BASE, (void *)FLASH_DATA0_START, DSP_DATA0_SIZE) != 0)
  {
    printf("DSP DATA0 load failed\r\n");
    while(1);
  }

  phy_reset(true /* release */);

  VC_PLC_PHY->CR1 |= 0x10C000;

  uint32_t timeout = 50;

  // wait for phy to be ready
	while (((VC_PLC_PHY->IR1 & 0x20) != 0x20) && (timeout-- > 0))
  {
		printf("CR1: 0x%08lx | IR1: 0x%08lx | IR2: 0x%08lx | IR3: 0x%08lx | IR4: 0x%08lx\r\n",
           VC_PLC_PHY->CR1, VC_PLC_PHY->IR1, VC_PLC_PHY->IR2, VC_PLC_PHY->IR3, VC_PLC_PHY->IR4);

    printf("Wait DSP Ready...%lu\r\n", (50-timeout));
  }
}


