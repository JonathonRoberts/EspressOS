ENTRY(main)
OUTPUT_FORMAT(elf64-x86-64)

PHDRS{
	headers PT_PHDR FILEHDR PHDRS;
	code PT_LOAD;
}

SECTIONS{
	.text 0x7f00: ALIGN(0x100)
	{
		*(.text)
	} :code

	.rodata :
	{
		*(.rodata)
	}

	.data :
	{
		*(.data)
	}

	.bss :
	{
		*(COMMON)
		*(.bss)
	}
	/DISCARD/ :
	{
		*(.eh_frame)
	}
}
