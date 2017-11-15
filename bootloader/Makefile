BUILD_DIR=../build/bootloader

AS=nasm
BOOTLOADER_SRCS != ls *.s
BOOTLOADER_OBJS = $(BOOTLOADER_SRCS:.s=.o)
.SUFFIXES: .o .s

all: $(BOOTLOADER_OBJS)

.s.o:
#	$(AS) -f bin $< -o $(BUILD_DIR)/$@
	$(AS) -f elf $< -F dwarf -g -o $(BUILD_DIR)/$@
	ld -m elf_i386 -z notext -T bootloader.lds $(BUILD_DIR)/$@ -o $(BUILD_DIR)/$@.elf
	objcopy -O binary $(BUILD_DIR)/bootloader.o.elf $(BUILD_DIR)/$@

clean:
	rm $(BUILD_DIR)/*
