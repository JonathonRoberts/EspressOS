BUILD_DIR=build
BOOTLOADER=$(BUILD_DIR)/bootloader/bootloader.o
OS=$(BUILD_DIR)/os/os
FLOPPY_IMG=disk.img
DISK_IMG=disk.iso

all: bootdisk cdrom

.PHONY: bootdisk bootloader os

bootloader:
	make -C bootloader

os:
	make -C os

bootdisk: bootloader os
	dd if=/dev/zero of=$(FLOPPY_IMG) bs=512 count=2880
	dd conv=notrunc if=$(BOOTLOADER) of=$(FLOPPY_IMG) bs=512 count=1 seek=0
	dd conv=notrunc if=$(OS) of=$(FLOPPY_IMG) bs=512 count=`du -k $(OS)|cut -f1` seek=1

cdrom:
	cp $(FLOPPY_IMG) $(BUILD_DIR)/tmp
	mkisofs -o $(DISK_IMG) -V OS -b $(FLOPPY_IMG) $(BUILD_DIR)/tmp

qemu-gdb:
	qemu-system-x86_64 -machine q35 -cdrom $(DISK_IMG) -gdb tcp::26000 -S
qemu:
	qemu-system-x86_64 -machine q35 -cdrom $(DISK_IMG)

clean:
	make -C bootloader clean
	make -C os clean
	rm $(BUILD_DIR)/tmp/*
