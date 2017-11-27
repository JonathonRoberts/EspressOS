BUILD_DIR=../build/kernel
KERNEL=$(BUILD_DIR)/kernel

AS=nasm
ASFLAGS=-f bin
CC=clang
CFLAGS+=-ffreestanding -nostdlib -gdwarf-2 -m64 -ggdb3 -Wall -Wextra -std=c99 -fno-stack-protector
C_SRCS!=ls *.c
C_OBJS=$(C_SRCS:.c=.o)
S_SRCS!=ls *.s
S_OBJS=$(S_SRCS:.s=.o)
KERNEL_OBJS=$(S_OBJS)
KERNEL_OBJS+=$(C_OBJS)
.SUFFIXES: .o .c .s

all: $(KERNEL)

.s.o:
	$(AS) -f elf64 $< -o $(BUILD_DIR)/$@
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@

$(KERNEL): $(KERNEL_OBJS)
	ld -m elf_x86_64_obsd -nmagic -Tkernel.lds `ls $(BUILD_DIR)/*.o` -o $@
clean:
	rm $(BUILD_DIR)/*
