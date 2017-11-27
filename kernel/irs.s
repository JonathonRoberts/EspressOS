global isr0

isr0:
	push rax
	in al, 0x20
	mov ax, 0x20
	out 0x20, ax
	pop rax
	iretq
