DBGSTORE_DIR = dbgstore
HEAP_DIR = heap

SRCS_DBGSTORE += $(wildcard $(DBGSTORE_DIR)/*.c)
SRCS_HEAP += $(wildcard $(HEAP_DIR)/*.c)

OBJS_DBGSTORE += $(addprefix $(BUILD)/, $(SRCS_DBGSTORE:.c=.o))
OBJS_HEAP += $(addprefix $(BUILD)/, $(SRCS_HEAP:.c=.o))

OBJS_DIR += $(sort $(dir $(OBJS_DBGSTORE)))
OBJS_DIR += $(sort $(dir $(OBJS_HEAP)))

LIB_TOOLS_DBGSTORE_A = $(BUILD)/$(LIB_TOOLS_DBGSTORE)
LIB_TOOLS_DBGSTORE_OBJS += $(OBJS_DBGSTORE)

LIB_TOOLS_HEAP_A = $(BUILD)/$(LIB_TOOLS_HEAP)
LIB_TOOLS_HEAP_OBJS += $(OBJS_HEAP)

A_FILES += $(LIB_TOOLS_DBGSTORE_A)
A_FILES += $(LIB_TOOLS_HEAP_A)

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

$(LIB_TOOLS_DBGSTORE_A): $(LIB_TOOLS_DBGSTORE_OBJS)

$(LIB_TOOLS_HEAP_A): $(LIB_TOOLS_HEAP_OBJS)

-include $(OBJS_DBGSTORE:%.o=%.d)
-include $(OBJS_HEAP:%.o=%.d)
