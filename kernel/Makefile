BUILD_DIR=../build/kernel
KERNEL=$(BUILD_DIR)/kernel

CFLAGS+=-ffreestanding -nostdlib -gdwarf-2 -m64 -ggdb3 -Wall -Wextra -std=c99

AS=nasm
CC=clang
ASFLAGS=-f bin
KERNEL_SRCS!=ls *.c
KERNEL_OBJS=$(KERNEL_SRCS:.c=.o)
S_SRCS!=ls *.s
S_OBJS=$(S_SRCS:.s=.o)
.SUFFIXES: .o .c .s

all: $(KERNEL)

.s.o:

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@
	nasm -f elf64 isr.s -o ../build/kernel/isr.o


$(KERNEL): $(KERNEL_OBJS)
	ld -m elf_x86_64_obsd -nmagic -Tkernel.lds  $(BUILD_DIR)/$(KERNEL_OBJS) $(BUILD_DIR)/$(S_OBJS) -o $@
clean:
	rm $(BUILD_DIR)/*
