DEVICE_DIR = TARGET_$(VENDOR)/TARGET_$(DEVICE)

SRCS_CMSIS += $(DEVICE_DIR)/CMSIS/Source/system_$(DEVICE_LC).c
SRCS_CMSIS_STARTUP = $(DEVICE_DIR)/CMSIS/Source/GCC/startup_$(DEVICE_LC).s

SRCS_HAL += $(DEVICE_DIR)/HAL/Source/pinmap.c
SRCS_HAL += $(DEVICE_DIR)/HAL/Source/gpio_api.c
SRCS_HAL += $(DEVICE_DIR)/HAL/Source/gpio_irq_api.c

SRCS_MAIN += main.c

OBJS_CMSIS += $(addprefix $(BUILD)/, $(SRCS_CMSIS:.c=.o))
OBJS_CMSIS_STARTUP += $(addprefix $(BUILD)/, $(SRCS_CMSIS_STARTUP:.s=.o))
OBJS_HAL += $(addprefix $(BUILD)/, $(SRCS_HAL:.c=.o))
OBJS_MAIN += $(addprefix $(BUILD)/, $(SRCS_MAIN:.c=.o))

OBJS_DIR += $(sort $(dir $(OBJS_CMSIS)))
OBJS_DIR += $(sort $(dir $(OBJS_CMSIS_STARTUP)))
OBJS_DIR += $(sort $(dir $(OBJS_HAL)))
OBJS_DIR += $(sort $(dir $(OBJS_MAIN)))

LIB_TARGET_CMSIS_A = $(BUILD)/$(LIB_TARGET_CMSIS)
LIB_TARGET_CMSIS_OBJS += $(OBJS_CMSIS)
LIB_TARGET_CMSIS_OBJS += $(OBJS_CMSIS_STARTUP)

LIB_TARGET_HAL_A = $(BUILD)/$(LIB_TARGET_HAL)
LIB_TARGET_HAL_OBJS += $(OBJS_HAL)

LIB_TARGET_MAIN_A = $(BUILD)/$(LIB_TARGET_MAIN)
LIB_TARGET_MAIN_OBJS += $(OBJS_MAIN)

A_FILES += $(LIB_TARGET_CMSIS_A)
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

$(LIB_TARGET_CMSIS_A): $(LIB_TARGET_CMSIS_OBJS)

$(LIB_TARGET_HAL_A): $(LIB_TARGET_HAL_OBJS)

$(LIB_TARGET_MAIN_A): $(LIB_TARGET_MAIN_OBJS)

-include $(OBJS_CMSIS:%.o=%.d)
-include $(OBJS_HAL:%.o=%.d)
-include $(OBJS_MAIN:%.o=%.d)
