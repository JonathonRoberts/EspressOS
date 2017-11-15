BUILD_DIR=../build/os
OS=$(BUILD_DIR)/os

CFLAGS+=-ffreestanding -nostdlib -gdwarf-2 -m64 -ggdb3 -Wall -Wextra -std=c99

AS=nasm
CC=clang
ASFLAGS=-f bin
OS_SRCS!=ls *.c
OS_OBJS=$(OS_SRCS:.c=.o)
S_SRCS!=ls *.s
S_OBJS=$(S_SRCS:.s=.o)
.SUFFIXES: .o .c .s

all: $(OS)

.s.o:

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@
	nasm -f elf64 print.s -o ../build/os/print.o


$(OS): $(OS_OBJS)
	ld -m elf_x86_64_obsd -nmagic -Tos.lds $(BUILD_DIR)/print.o $(BUILD_DIR)/$(OS_OBJS) -o $@
clean:
	rm $(BUILD_DIR)/*
