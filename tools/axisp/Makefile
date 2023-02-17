##
# (c)copyright axflasher, 2015
#
HOST_OS     := $(shell uname -s)
CC          := gcc
CPP         := gcc
AS          := as
LD          := gcc
AR          := ar
RANLIB      := ranlib
NM          := nm
OBJCOPY     := objcopy
OBJDUMP     := objdump
SIZE        := size

OUTPATH     := ./out

DEPS        := config.h bin_object.h ftisp.h vtisp.h vtspisp.h vtiicisp.h isp.h xmodem.h ftefc.h mkimg.h vtprobe.h

SRCS_C      :=
SRCS_CPP    := main.cpp isp.cpp ftisp.cpp vtisp.cpp vtspisp.cpp vtiicisp.cpp xmodem.cpp ftefc.cpp bin_object.cpp mkimg.cpp vtprobe.cpp
SRCS        := $(SRCS_C) $(SRCS_CPP)

OBJS        := $(SRCS_C:.c=.o) $(SRCS_CPP:.cpp=.o)
OBJS        := $(patsubst %,$(OUTPATH)/%,$(OBJS))

BIN         := axisp

#INCPATH     := ./libftdi1/libftdi/src ./libftdi1/libftdi/ftdipp /usr/include/libusb-1.0 ./libmpsse/libmpsse-1.3/src /usr/local/include
#INCPATH     := ./libftdi1/libftdi/src ./libftdi1/libftdi/ftdipp /usr/include/libusb-1.0
INCPATH     := ./libftdi1/libftdi/src ./libftdi1/libftdi/ftdipp /usr/include/libusb-1.0 ./libmpsse/libmpsse-1.3/src /usr/local/include
INCPATH     := $(patsubst %,-I%,$(INCPATH))

#LIBPATH     := ./libftdi1/libftdi/build/src ./libmpsse/libmpsse-1.3/src
#LIBPATH     :=
#LIBPATH     := $(patsubst %,-L%,$(LIBPATH))

#LIBS        := ftdi1 usb-1.0 mpsse stdc++
LIBS        := usb-1.0 stdc++
LIBS        := $(patsubst %,-l%,$(LIBS))

CFLAGS      := $(INCPATH)
CFLAGS      += -O0 -g
CFLAGS      += -Werror -Wall -Wno-misleading-indentation

#LDFLAGS    := -rdynamic ./libftdi1/libftdi/build/src/libftdi1.so.2.2.0 -lusb-1.0 -Wl,-rpath,./libftdi1/libftdi/build/src
LDFLAGS     := -Wl,-Bdynamic $(LIBPATH)

ODFLAGS     := -dSt

.PHONY: all clean update od gdb ddd

all: $(OUTPATH)/$(BIN)

$(OUTPATH)/$(BIN): $(OBJS)
	@mkdir -p $(OUTPATH)
	@echo ""
ifeq ($(HOST_OS),Linux)
	${LD} $(LDFLAGS) -o $@ -Wl,--start-group ./libftdi1/libftdi/build/src/libftdi1.a ./libmpsse/libmpsse-1.3/src/libmpsse.a $(OBJS) -Wl,--end-group $(LIBS)
else
	${LD} $(LDFLAGS) -o $@ -Wl,--start-group ./libftdi1/Cygwin/$(shell uname -m)/libftdi1.a ./libmpsse/Cygwin/$(shell uname -m)/libmpsse.a $(OBJS) -Wl,--end-group $(LIBS)
endif
	@echo ""i
	${SIZE} $@

$(OUTPATH)/%.o: %.c Makefile $(DEPS)
	@mkdir -p $(OUTPATH)
	${CC} $(CFLAGS) -o $@ -c $<

$(OUTPATH)/%.o: %.cpp Makefile $(DEPS)
	@mkdir -p $(OUTPATH)
	${CC} $(CFLAGS) -o $@ -c $<



clean: FORCE
	@rm -f *~
	@rm -fr $(OUTPATH)


update:
	@if [ -f $(OUTPATH)/$(BIN) ]; then cp -f $(OUTPATH)/$(BIN) ~/ws/vtec/ws/mcs51/at89s52/tools; echo "done updating ~/ws/vtec/ws/mcs51/at89s52/tools/$(BIN)\n"; fi

od:
	@if [ -e $(OUTPATH)/$(BIN) ]; then ${OBJDUMP} $(ODFLAGS) $(OUTPATH)/$(BIN) > $(OUTPATH)/$(BIN).objdump; fi

gdb:
	[ -e $(OUTPATH)/$(BIN) ] && gdb -tui -x gdb.x $(OUTPATH)/$(BIN)

ddd:
	[ -e $(OUTPATH)/$(BIN) ] && ddd --gdb -x gdb.x $(OUTPATH)/$(BIN)

FORCE:

