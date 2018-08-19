BUILD_DIR=build
BOOTLOADER=$(BUILD_DIR)/bootloader/bootloader.o
KERNEL=$(BUILD_DIR)/kernel/kernel.bin
FLOPPY_IMG=disk.img
DISK_IMG=disk.iso
DEBUG_EXIT=-device isa-debug-exit,iobase=0xf4,iosize=0x04
QEMU=qemu-system-x86_64 -machine q35 $(DEBUG_EXIT)
#QEMU=qemu-system-x86_64 -machine pc $(DEBUG_EXIT)

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
hd: bootloader kernel
	doas dd if=/dev/zero of=disk.img bs=512 count=2880
	doas vnconfig vnd0 disk.img
	doas newfs_msdos -a 9 -b 512 -c 1 -e 224 -f 2880 -h 1 -I 100 -L ESPRESSO -m 240 -n 2 -O ESPRESSO -o 0 -r 1 -S 512 -u 18 /dev/rvnd0c
	dd conv=notrunc if=build/bootloader/bootloader.o of=disk.img bs=512 count=1 seek=0
	dd conv=notrunc if=build/kernel/kernel.bin of=disk.img bs=512 count=`du build/kernel/kernel.bin|cut -f1` seek=1
	doas mount -t msdos /dev/vnd0c build/tmp
	doas touch build/tmp/TEST.TXT
	doas touch build/tmp/BOOT
	doas umount build/tmp
	doas vnconfig -u vnd0
	doas dd conv=notrunc if=disk.img of=/dev/wd0c bs=512 seek=0

#qemu-gdb:
#	$(QEMU) -hda $(FLOPPY_IMG) -gdb tcp::26000 -S
#qemu:
#	$(QEMU) -hda $(FLOPPY_IMG)
qemu-gdb:
	$(QEMU) -drive id=disk,file=$(FLOPPY_IMG),if=none -device ahci,id=ahci -device ide-drive,drive=disk,bus=ahci.0  -gdb tcp::26000 -S
qemu:
	$(QEMU) -drive id=disk,file=$(FLOPPY_IMG),if=none -device ahci,id=ahci -device ide-drive,drive=disk,bus=ahci.0
qemuf-gdb:
	$(QEMU) -fda $(FLOPPY_IMG) -gdb tcp::26000 -S
qemuf:
	$(QEMU) -fda $(FLOPPY_IMG)
qemuh:
	$(QEMU) -hda $(FLOPPY_IMG)
qemuhd:
	doas $(QEMU) -hda /dev/wd0c

#serial:
#	$(QEMU) -machine q35 -cdrom $(DISK_IMG) -serial "pty" -nographic
#connect:
#	doas cu -s 38400 -l /dev/ttyp9
serial:
	$(QEMU) -hda $(FLOPPY_IMG) -nographic
serial-gdb:
	$(QEMU) -hda $(FLOPPY_IMG) -nographic -gdb tcp::26000 -S

clean:
	make -C bootloader clean
	make -C kernel clean
	rm $(BUILD_DIR)/tmp/*
