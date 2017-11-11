BUILD_DIR=../build/bootloader

AS=nasm
ASFLAGS=-f bin
BOOTLOADER_SRCS != ls *.asm
BOOTLOADER_OBJS = $(BOOTLOADER_SRCS:.asm=.o)
.SUFFIXES: .o .asm

all: $(BOOTLOADER_OBJS)

.asm.o:
	$(AS) $(ASFLAGS) $< -o $(BUILD_DIR)/$@

clean:
	rm $(BUILD_DIR)/*
