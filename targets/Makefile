MCU_FAM_DIR    = TARGET_$(VENDOR)/TARGET_$(MCU_FAM)
MCU_DEVICE_DIR = $(MCU_FAM_DIR)/TARGET_$(MCU_DEVICE)
MCU_BOARD_DIR  = $(MCU_DEVICE_DIR)/TARGET_$(MCU_BOARD)

SRCS_HAL += $(MCU_FAM_DIR)/gpio_api.c
SRCS_HAL += $(MCU_FAM_DIR)/pinmap.c
SRCS_HAL += $(MCU_FAM_DIR)/pinmap_ex.c
SRCS_HAL += $(MCU_FAM_DIR)/serial_api.c
SRCS_HAL += $(MCU_FAM_DIR)/ticker_api.c
SRCS_HAL += $(MCU_FAM_DIR)/us_ticker_api.c
SRCS_HAL += $(MCU_FAM_DIR)/us_ticker.c

SRCS_HAL += $(MCU_FAM_DIR)/device/vc73xx_ana.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc73xx_flash.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc73xx_gpio.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc73xx_uart.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc73xx_pwm.c

SRCS_HAL += $(MCU_BOARD_DIR)/device/system_$(MCU_DEVICE_LC).c

SRCS_HAL_STARTUP += $(MCU_BOARD_DIR)/device/TOOLCHAIN_GCC_ARM/startup_$(MCU_DEVICE_LC).s

SRCS_MAIN += main.c

OBJS_HAL += $(addprefix $(BUILD)/, $(SRCS_HAL:.c=.o))
OBJS_HAL_STARTUP += $(addprefix $(BUILD)/, $(SRCS_HAL_STARTUP:.s=.o))
OBJS_MAIN += $(addprefix $(BUILD)/, $(SRCS_MAIN:.c=.o))

OBJS_DIR += $(sort $(dir $(OBJS_HAL)))
OBJS_DIR += $(sort $(dir $(OBJS_HAL_STARTUP)))
OBJS_DIR += $(sort $(dir $(OBJS_MAIN)))

LIB_TARGET_HAL_A = $(BUILD)/$(LIB_TARGET_HAL)
LIB_TARGET_HAL_OBJS += $(OBJS_HAL)
LIB_TARGET_HAL_OBJS += $(OBJS_HAL_STARTUP)

LIB_TARGET_MAIN_A = $(BUILD)/$(LIB_TARGET_MAIN)
LIB_TARGET_MAIN_OBJS += $(OBJS_MAIN)

A_FILES += $(LIB_TARGET_HAL_A)
A_FILES += $(LIB_TARGET_MAIN_A)

all: | $(OBJS_DIR) $(A_FILES)

$(OBJS_DIR):
	$(MKDIR) -p $@

$(BUILD)/%.o: %.c
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.o: %.s
	$(ECHO) "AS $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.a:
	$(ECHO) "AR $@"
	$(AR) -cr $@ $^

$(LIB_TARGET_HAL_A): $(LIB_TARGET_HAL_OBJS)

$(LIB_TARGET_MAIN_A): $(LIB_TARGET_MAIN_OBJS)

-include $(OBJS_HAL:%.o=%.d)
-include $(OBJS_MAIN:%.o=%.d)
