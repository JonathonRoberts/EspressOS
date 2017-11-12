BUILD_DIR=../build/bootloader

AS=nasm
BOOTLOADER_SRCS != ls *.asm
BOOTLOADER_OBJS = $(BOOTLOADER_SRCS:.asm=.o)
.SUFFIXES: .o .asm

all: $(BOOTLOADER_OBJS)

.asm.o:
#	$(AS) -f bin $< -o $(BUILD_DIR)/$@
	$(AS) -f elf $< -F dwarf -g -o $(BUILD_DIR)/$@
	ld -m elf_i386 -T bootloader.lds $(BUILD_DIR)/$@ -o $(BUILD_DIR)/$@.elf
	objcopy -O binary $(BUILD_DIR)/bootloader.o.elf $(BUILD_DIR)/$@

clean:
	rm $(BUILD_DIR)/*
