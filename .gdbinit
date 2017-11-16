symbol-file build/kernel/kernel
target remote localhost:26000

set disassembly-flavor intel

layout asm
layout reg
layout split

#For debugging bootloader code
# set architecture i8086
# For debugging OS code
set architecture i386:x86-64

b *0x7c00

define hook-stop
	# Translate the segment:offset into a physical address
	#printf "[%4x:%4x]", $cs, $eip
	#x/i $cs*16+$eip
end
