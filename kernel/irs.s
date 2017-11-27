global isr0
global loadidt

loadidt:
	lidt [rax]
	sti
	ret

isr0:
	cli
	PUSH_ALL
	POP_ALL
	add rsp, 8
	pop rax
	pop rax
	pop rax
	pop rax
	pop rax
	pop rax
	pop rax
	pop rax
	sti
	iretq
