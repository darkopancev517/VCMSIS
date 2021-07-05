# 
#  Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved.
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

# Git helper
GIT_REPO_COMMIT	?= $(shell git describe --long --all --always --abbrev=8 | sed 's/.*-g\(.*\)/\1/')
GIT_REPO_BRANCH	?= $(shell git describe --long --all --always --abbrev=8 | cut -d- -f1 | cut -d/ -f2)
GIT_REPO_DESC	?= $(shell git describe --long --dirty --all --always --abbrev=8)
GIT_COMMIT_DATE ?= $(shell git show -s --format=%ci | cut -c1-10 | sed -e 's/-//g')
GIT_COMMIT_TIME ?= $(shell git show -s --format=%ci | cut -c12-19 | sed -e 's/://g')
ifeq ($(findstring dirty, $(GIT_REPO_DESC)), dirty)
GIT_REPO_DIRTY ?= 1
else
GIT_REPO_DIRTY ?= 0
endif

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
ifeq ($(v),1)
export MAKE     = $(Q)make
else
export MAKE     = $(Q)make -s
endif

export VENDOR ?= VERTEXCOM
export DEVICE ?= VC7351

export TOP_DIR    = $(shell pwd)
export BUILD_DIR  = Build
export DEVICE_DIR = Device/$(VENDOR)/$(DEVICE)
export CMSIS_DIR  = CMSIS_5/CMSIS

BUILD = $(TOP_DIR)/$(BUILD_DIR)

DEVICE_LC = $(shell echo $(DEVICE) | tr A-Z a-z)

CFLAGS += -I$(TOP_DIR)
CFLAGS += -I$(TOP_DIR)/$(CMSIS_DIR)/Core/Include
CFLAGS += -I$(TOP_DIR)/$(CMSIS_DIR)/Driver/Include
CFLAGS += -I$(TOP_DIR)/$(DEVICE_DIR)/Include

CFLAGS += -Wall -Werror
CFLAGS += -std=gnu99 -g -O0
CFLAGS += -mcpu=cortex-m3 -mthumb -mno-unaligned-access
CFLAGS += -ffunction-sections -fdata-sections

LDFLAGS += -g -O0 -Xlinker --gc-sections
LDFLAGS += -mcpu=cortex-m3 -mthumb -mno-unaligned-access
LDFLAGS += --specs=nosys.specs -static

LDSCRIPT = $(TOP_DIR)/$(DEVICE_DIR)/Source/GCC/gcc_arm_$(DEVICE_LC).ld

BUILD_DEVICE_DIR = $(TOP_DIR)/$(BUILD_DIR)/$(DEVICE_DIR)

export LIB_DEVICE_DRIVER = libdevice_driver_$(DEVICE_LC).a
export LIB_DEVICE_SYSTEM = libdevice_system_$(DEVICE_LC).a
export LIB_DEVICE_MAIN   = libdevice_main.a
export LIB_DEVICE_TEST   = libdevice_test.a

#MAIN_LIBS += $(BUILD_DEVICE_DIR)/$(LIB_DEVICE_DRIVER)
MAIN_LIBS += $(BUILD_DEVICE_DIR)/$(LIB_DEVICE_SYSTEM)
MAIN_LIBS += $(BUILD_DEVICE_DIR)/$(LIB_DEVICE_MAIN)

#TEST_LIBS += $(BUILD_DEVICE_DIR)/$(LIB_DEVICE_DRIVER)
TEST_LIBS += $(BUILD_DEVICE_DIR)/$(LIB_DEVICE_SYSTEM)
TEST_LIBS += $(BUILD_DEVICE_DIR)/$(LIB_DEVICE_TEST)

MAIN_IMAGE = $(BUILD)/$(DEVICE_LC)_main
TEST_IMAGE = $(BUILD)/$(DEVICE_LC)_test

all: $(VENDOR) BUILD_FINISHED_INFO

$(BUILD):
	$(MKDIR) -p $@

objects:
	$(MAKE) -C $(DEVICE_DIR) BUILD=$(BUILD_DEVICE_DIR) CFLAGS="$(CFLAGS) -MMD"

$(MAIN_IMAGE).elf: $(MAIN_LIBS) $(LDSCRIPT)
	$(CC) $(LDFLAGS) $(patsubst %,-L%,$(patsubst %/,%,$(sort $(dir $(MAIN_LIBS))))) \
	-Wl,--whole-archive $(patsubst %,-l%,$(patsubst lib%,%,$(sort $(basename $(notdir $(MAIN_LIBS)))))) \
	-Wl,--no-whole-archive -T $(LDSCRIPT) \
	-Wl,-Map,$(BUILD)/$(DEVICE_LC)_main.map -o $@

$(TEST_IMAGE).elf: $(TEST_LIBS) $(LDSCRIPT)
	$(CC) $(LDFLAGS) $(patsubst %,-L%,$(patsubst %/,%,$(sort $(dir $(TEST_LIBS))))) \
	-Wl,--whole-archive $(patsubst %,-l%,$(patsubst lib%,%,$(sort $(basename $(notdir $(TEST_LIBS)))))) \
	-Wl,--no-whole-archive -T $(LDSCRIPT) \
	-Wl,-Map,$(BUILD)/$(DEVICE_LC)_test.map -o $@

$(MAIN_IMAGE).bin: $(MAIN_IMAGE).elf
	$(OBJCOPY) -O binary $< $@

$(TEST_IMAGE).bin: $(TEST_IMAGE).elf
	$(OBJCOPY) -O binary $< $@

$(MAIN_IMAGE).lst: $(MAIN_IMAGE).elf
	$(OBJDUMP) -h -S $< > $@

$(TEST_IMAGE).lst: $(TEST_IMAGE).elf
	$(OBJDUMP) -h -S $< > $@

main: objects $(MAIN_IMAGE).bin $(MAIN_IMAGE).lst
	$(SIZE) --format=berkeley $(MAIN_IMAGE).elf

test: objects $(TEST_IMAGE).bin $(TEST_IMAGE).lst
	$(SIZE) --format=berkeley $(TEST_IMAGE).elf

$(VENDOR): main test | $(BUILD)

BUILD_FINISHED_INFO:
	$(ECHO) ""
	$(ECHO) "---------------------------------------------------------------------"
	$(ECHO) "\033[32mFinished Building\033[0m : $(VENDOR) DEVICE [$(DEVICE)] in $(HOST_MACHINE)"
	$(ECHO) "---------------------------------------------------------------------"
	$(ECHO) "MAIN image        : Build/\033[32m$(DEVICE_LC)_main.bin\033[0m"
	$(ECHO) "TEST image        : Build/\033[32m$(DEVICE_LC)_test.bin\033[0m"
	$(ECHO) "---------------------------------------------------------------------"
	$(ECHO) "Repository info   : $(GIT_REPO_COMMIT) @ [\033[33m$(GIT_REPO_BRANCH)\033[0m], dirty = $(GIT_REPO_DIRTY)"

.PHONY: all clean

clean:
	-rm -rf $(BUILD)
