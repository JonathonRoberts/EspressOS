global isr0
global loadidt

loadidt:
	sti
	lidt [rax]
	ret

isr0:
	cli
	hlt
	iretq
