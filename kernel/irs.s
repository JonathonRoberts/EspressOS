global isr0
extern sponge

isr0:
	cli
	;call sponge
	hlt
	push rax
	in al, 0x20
	mov ax, 0x20
	out 0x20, ax
	pop rax
	iretq
