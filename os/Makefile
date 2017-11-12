BUILD_DIR=../build/os
OS=$(BUILD_DIR)/os

CFLAGS+=-ffreestanding -nostdlib -gdwarf-2 -m32 -ggdb3 -Wall -std=c99

AS=nasm
CC=gcc
ASFLAGS=-f bin
OS_SRCS!=ls *.c
OS_OBJS=$(OS_SRCS:.c=.o)
.SUFFIXES: .o .c

all: $(OS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@

$(OS): $(OS_OBJS)
#	ld -m elf_i386 -Tos.lds $(BUILD_DIR)/$(OS_OBJS) -o $@
	ld -m elf_i386 -nmagic -Tos.lds $(BUILD_DIR)/$(OS_OBJS) -o $@
clean:
	rm $(BUILD_DIR)/*
