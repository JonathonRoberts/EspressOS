BUILD_DIR=build
BOOTLOADER=$(BUILD_DIR)/bootloader/bootloader.o
KERNEL=$(BUILD_DIR)/kernel/kernel.bin
FLOPPY_IMG=disk.img
DISK_IMG=disk.iso
DEBUG_EXIT=-device isa-debug-exit,iobase=0xf4,iosize=0x04
QEMU=qemu-system-x86_64 -machine q35 $(DEBUG_EXIT)

all: bootdisk cdrom

.PHONY: bootdisk bootloader kernel

bootloader:
	make -C bootloader

kernel:
	make -C kernel

bootdisk: bootloader kernel
	dd if=/dev/zero of=$(FLOPPY_IMG) bs=512 count=2880
	dd conv=notrunc if=$(BOOTLOADER) of=$(FLOPPY_IMG) bs=512 count=1 seek=0
	dd conv=notrunc if=$(KERNEL) of=$(FLOPPY_IMG) bs=512 count=`du $(KERNEL)|cut -f1` seek=1

cdrom:
	cp $(FLOPPY_IMG) $(BUILD_DIR)/tmp
	mkisofs -o $(DISK_IMG) -V EspressOS -b $(FLOPPY_IMG) $(BUILD_DIR)/tmp

qemu-gdb:
	$(QEMU)  -cdrom $(DISK_IMG) -gdb tcp::26000 -S
qemu:
	$(QEMU) -cdrom $(DISK_IMG)
qemuf-gdb:
	$(QEMU) -fda $(FLOPPY_IMG) -gdb tcp::26000 -S
qemuf:
	$(QEMU) -fda $(FLOPPY_IMG)

#serial:
#	qemu-system-x86_64 -machine q35 -cdrom $(DISK_IMG) -serial "pty" -nographic
#connect:
#	doas cu -s 38400 -l /dev/ttyp9
serial:
	qemu-system-x86_64 -machine q35 -cdrom $(DISK_IMG) -nographic $(DEBUG_EXIT)

clean:
	make -C bootloader clean
	make -C kernel clean
	rm $(BUILD_DIR)/tmp/*
