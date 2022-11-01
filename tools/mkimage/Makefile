CC :=gcc
RM := rm -rf
src_file := main.c
out_file := mkimg

ifeq ($(shell uname -s),Darwin)
CFLAGS += -Wno-constant-logical-operand
endif

all:
	$(CC) $(CFLAGS) $(src_file) -o $(out_file)
	@mv mkimg $(shell uname -s)
	@echo "finished building mkimg...."

clean:
	$(RM) *.o
