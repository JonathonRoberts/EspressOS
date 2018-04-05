BUILD_DIR=../build/bootloader
BOOTLOADER=bootloader.bin

AS=yasm
BOOTLOADER_SRCS!=ls *.s
BOOTLOADER_OBJS=$(BOOTLOADER_SRCS:.s=.o)
.SUFFIXES: .o .s

all: $(BOOTLOADER_OBJS)

.s.o:
	$(AS) -f elf $< -g DWARF2 -o $(BUILD_DIR)/$@
	ld -m elf_i386 -z notext -T bootloader.lds $(BUILD_DIR)/$@ -o $(BUILD_DIR)/$(BOOTLOADER)
	objcopy -O binary $(BUILD_DIR)/$(BOOTLOADER) $(BUILD_DIR)/$@

clean:
	rm $(BUILD_DIR)/*
