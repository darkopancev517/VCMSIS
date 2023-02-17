# 
#  Copyright (c) 2022, Hangzhou Lianxintong Semiconductor Co.,Ltd.
#  All rights reserved.
# 
#  SPDX-License-Identifier: Apache-2.0
# 
#  Licensed under the Apache License, Version 2.0 (the License); you may
#  not use this file except in compliance with the License.
#  You may obtain a copy of the License at
# 
#  www.apache.org/licenses/LICENSE-2.0
# 
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an AS IS BASIS, WITHOUT
#  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

# ------------ GCC MAKEFILE -------------

# Set verbosity
ifeq ($(v), 1)
Q =
else
Q = @
endif

HOST_MACHINE = $(shell uname -s)

export CC       = $(Q)arm-none-eabi-gcc
export AS       = $(Q)arm-none-eabi-as
export LD       = $(Q)arm-none-eabi-ld
export AR       = $(Q)arm-none-eabi-ar
export CPP      = $(Q)arm-none-eabi-cpp
export SIZE     = $(Q)arm-none-eabi-size
export STRIP    = $(Q)arm-none-eabi-strip -s
export OBJCOPY  = $(Q)arm-none-eabi-objcopy
export OBJDUMP  = $(Q)arm-none-eabi-objdump
export RM       = $(Q)rm
export MKDIR    = $(Q)mkdir
export ECHO     = $(Q)@echo
export CP       = $(Q)cp
export CAT      = $(Q)cat
export DD       = $(Q)dd
ifeq ($(v),1)
export MAKE     = $(Q)make
else
export MAKE     = $(Q)make -s
endif

ifeq ($(HOST_MACHINE),Darwin)
export STAT = gstat
export AWK = gawk
else
export STAT = stat
export AWK = awk
endif

export VENDOR     ?= UNICOM
export MCU_FAM    ?= VC
export MCU_DEVICE ?= VC7351
export MCU_BOARD  ?= VC7351_DK

export TOP_DIR           = $(shell pwd)
export BUILD_DIR         = build/$(MCU_BOARD)
export TARGET_FAM_DIR    = targets/TARGET_$(VENDOR)/TARGET_$(MCU_FAM)
export TARGET_DEVICE_DIR = $(TARGET_FAM_DIR)/TARGET_$(MCU_DEVICE)
export TARGET_BOARD_DIR  = $(TARGET_DEVICE_DIR)/TARGET_$(MCU_BOARD)
export PLC_BBP_DIR       = $(TOP_DIR)/$(TARGET_FAM_DIR)/device/plc/bbp
export CMSIS_DIR         = CMSIS_5/CMSIS
export HAL_DIR           = hal

BUILD = $(TOP_DIR)/$(BUILD_DIR)

export MCU_DEVICE_LC = $(shell echo $(MCU_DEVICE) | tr A-Z a-z)

CFLAGS += -I$(TOP_DIR)
CFLAGS += -I$(TOP_DIR)/$(CMSIS_DIR)/Core/Include
CFLAGS += -I$(TOP_DIR)/$(HAL_DIR)/include
CFLAGS += -I$(TOP_DIR)/$(HAL_DIR)/include/hal
CFLAGS += -I$(TOP_DIR)/targets
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/atcmd
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/lib

ifeq ($(MCU_DEVICE),VC7351)
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/rf
endif

ifeq ($(MCU_DEVICE),VC6330)
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/plc
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/plc/hplc
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto/crypto_common
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto/crypto_hal
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto/crypto_include
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto/crypto_include/hash_hmac
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto/crypto_include/pke
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto/crypto_include/ske
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto/crypto_lib
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/hash_hmac
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/pke
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/ske
endif

ifeq ($(MCU_DEVICE),VC6320)
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/plc
CFLAGS += -I$(TOP_DIR)/$(TARGET_FAM_DIR)/device/plc/hplc
endif

ifeq ($(MCU_DEVICE),VC6330)
CFLAGS += -I$(TOP_DIR)/tests/hplc_crypto
CFLAGS += -I$(TOP_DIR)/tests/osr_crypto
CFLAGS += -I$(TOP_DIR)/tests/osr_crypto/hash_hmac_test
CFLAGS += -I$(TOP_DIR)/tests/osr_crypto/pke_test
CFLAGS += -I$(TOP_DIR)/tests/osr_crypto/ske_test
endif

CFLAGS += -I$(TOP_DIR)/$(TARGET_DEVICE_DIR)
CFLAGS += -I$(TOP_DIR)/$(TARGET_DEVICE_DIR)/CMSIS
CFLAGS += -I$(TOP_DIR)/$(TARGET_BOARD_DIR)

# MBED-HAL FLAGS
CFLAGS += -DDEVICE_INTERRUPTIN=1
CFLAGS += -DDEVICE_SERIAL=1
CFLAGS += -DDEVICE_SERIAL_ASYNCH=0
CFLAGS += -DDEVICE_FLASH=1
CFLAGS += -DDEVICE_LPTICKER=1
CFLAGS += -DDEVICE_RTC=1
CFLAGS += -DDEVICE_LPTICKER=1
CFLAGS += -DDEVICE_WATCHDOG=1
CFLAGS += -DDEVICE_SPI=1
CFLAGS += -DDEVICE_SPISLAVE=0
CFLAGS += -DDEVICE_SPI_ASYNCH=0
CFLAGS += -DDEVICE_I2C=1
CFLAGS += -DDEVICE_I2C_ASYNCH=0
CFLAGS += -DDEVICE_ANALOGIN=1
CFLAGS += -DDEVICE_MCU_$(MCU_DEVICE)=1

# SONATA RF DRIVER FLAGS
CFLAGS += -DCSR_ACCESS=

CFLAGS += -Wall -Werror
CFLAGS += -std=gnu99 -g -O0
CFLAGS += -mcpu=cortex-m3 -mthumb -mno-unaligned-access
CFLAGS += -ffunction-sections -fdata-sections

LDFLAGS += -g -O0 -Xlinker --gc-sections
LDFLAGS += -mcpu=cortex-m3 -mthumb -mno-unaligned-access
LDFLAGS += --specs=nosys.specs -static
LDFLAGS += -Wl,--wrap,_malloc_r -Wl,--wrap,_free_r -Wl,--wrap,_realloc_r -Wl,--wrap,_calloc_r

LDSCRIPT = $(TOP_DIR)/$(TARGET_DEVICE_DIR)/CMSIS/TOOLCHAIN_GCC_ARM/gcc_arm_$(MCU_DEVICE_LC).ld

BUILD_TARGET_DIR = $(TOP_DIR)/$(BUILD_DIR)

export LIB_TARGET_HAL     = libtarget_hal_$(MCU_DEVICE_LC).a
export LIB_TARGET_MAIN    = libtarget_main.a
export LIB_TARGET_TESTS   = libtarget_tests.a

MAIN_LIBS += $(BUILD_TARGET_DIR)/$(LIB_TARGET_HAL)
MAIN_LIBS += $(BUILD_TARGET_DIR)/$(LIB_TARGET_MAIN)
MAIN_LIBS += $(BUILD_TARGET_DIR)/$(LIB_TARGET_TESTS)

MAIN_IMAGE = $(BUILD)/$(MCU_BOARD)_soc
MAIN_IMAGE_WITH_RADIO = $(BUILD)/$(MCU_BOARD)_with_radio
MAIN_IMAGE_WITH_PLC = $(BUILD)/$(MCU_BOARD)_with_plc

ifeq ($(MCU_DEVICE),VC7351)
RADIOFW_IMAGE = $(BUILD_TARGET_DIR)/sonata_radio
RADIODSP_DATA_IMAGE = $(BUILD_TARGET_DIR)/sonata_dsp_dram0
RADIODSP_IRAM_IMAGE = $(BUILD_TARGET_DIR)/sonata_dsp_iram
DSP_IMAGE = $(BUILD_TARGET_DIR)/sonata_dsp
endif

ifeq ($(MCU_DEVICE),VC6330)
PLCDSP_DATA_IMAGE = $(BUILD_TARGET_DIR)/phoenix_dsp_dram0
PLCDSP_IRAM_IMAGE = $(BUILD_TARGET_DIR)/phoenix_dsp_iram
DSP_IMAGE = $(BUILD_TARGET_DIR)/phoenix_dsp
endif

all: $(VENDOR) BUILD_FINISHED_INFO

$(BUILD):
	$(MKDIR) -p $@

objects:
	$(MAKE) -C targets BUILD=$(BUILD_TARGET_DIR) CFLAGS="$(CFLAGS) -MMD"

$(MAIN_IMAGE).elf: $(MAIN_LIBS) $(LDSCRIPT)
	$(CC) $(LDFLAGS) $(patsubst %,-L%,$(patsubst %/,%,$(sort $(dir $(MAIN_LIBS))))) \
	-Wl,--whole-archive $(patsubst %,-l%,$(patsubst lib%,%,$(sort $(basename $(notdir $(MAIN_LIBS)))))) \
	-Wl,--no-whole-archive -T $(LDSCRIPT) \
	-Wl,-Map,$(BUILD)/$(MCU_DEVICE_LC)_main.map -o $@

$(MAIN_IMAGE).bin: $(MAIN_IMAGE).elf
	$(OBJCOPY) -O binary $< $@

$(MAIN_IMAGE).lst: $(MAIN_IMAGE).elf
	$(OBJDUMP) -h -S $< > $@

main: objects $(MAIN_IMAGE).bin $(MAIN_IMAGE).lst
	$(SIZE) --format=berkeley $(MAIN_IMAGE).elf

$(VENDOR): main | $(BUILD)

BUILD_FINISHED_INFO:
	$(ECHO) ""
	$(ECHO) "---------------------------------------------------------------------"
	$(ECHO) "\033[32mFinished Building\033[0m : $(VENDOR) DEVICE [$(MCU_DEVICE)] in $(HOST_MACHINE)"
	$(ECHO) "---------------------------------------------------------------------"
	$(ECHO) "build/$(MCU_BOARD)/\033[32m$(MCU_BOARD)_soc.bin\033[0m"
ifeq ($(MCU_DEVICE),VC7351)
	$(ECHO) "build/$(MCU_BOARD)/\033[32m$(MCU_BOARD)_with_radio.bin\033[0m"
endif
ifneq (, $(filter $(MCU_DEVICE), VC6320))
	$(ECHO) "build/$(MCU_BOARD)/\033[32m$(MCU_BOARD)_with_plc.bin\033[0m"
endif
	$(ECHO) "---------------------------------------------------------------------"

.PHONY: all clean

clean:
	-rm -rf $(BUILD)
