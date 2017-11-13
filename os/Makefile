BUILD_DIR=../build/os
OS=$(BUILD_DIR)/os

CFLAGS+=-ffreestanding -nostdlib -gdwarf-2 -m64 -ggdb3 -Wall -std=c99

AS=nasm
CC=clang
ASFLAGS=-f bin
OS_SRCS!=ls *.c
OS_OBJS=$(OS_SRCS:.c=.o)
.SUFFIXES: .o .c

all: $(OS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@

$(OS): $(OS_OBJS)
	ld -m elf_x86_64_obsd -nmagic -Tos.lds $(BUILD_DIR)/$(OS_OBJS) -o $@
clean:
	rm $(BUILD_DIR)/*
