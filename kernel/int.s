global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

%include "macros.s"
extern sponge

extern IDTP
global LIDT
LIDT:
	lidt [rel IDTP]
	sti
	ret

isr0:
	cli
	push qword 9
	PUSH_ALL
	call sponge
	jmp isr_ret
isr1:
;Keyboard interrupt
	cli
	PUSH_ALL
	in al,60h		; Read keypress from port 60h
	mov [0xb8000], al	; print scancode

	mov ah, 0x02		; colour
	mov [0xb8001], ah

	push qword 0
	jmp isr_ret
isr2:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr3:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr4:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr5:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr6:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr7:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr8:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr9:
	cli
	push qword 0 ;push faux error code to create uniform stack size
	PUSH_ALL
	jmp isr_ret
isr10:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr11:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr12:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr13:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr14:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr15:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr16:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr17:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr18:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr19:
	cli
	push qword 0 ;push faux error code to create uniform stack size
	PUSH_ALL
	jmp isr_ret
isr20:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr21:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr22:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr23:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr24:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr25:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr26:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr27:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr28:
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr29:
	cli
	push qword 0 ;push faux error code to create uniform stack size
	PUSH_ALL
	jmp isr_ret
isr30:
	cli
	push qword 0 ;push faux error code to create uniform stack size
	PUSH_ALL
	jmp isr_ret
isr31:
	cli
	push qword 0 ;push faux error code to create uniform stack size
	PUSH_ALL
	jmp isr_ret

isr_ret:
	mov ax, 0x20
	out 0x20, ax	; Send end of interrupt command to master PIC
	POP_ALL
	cld
	sti
	add rsp, 8
	iretq
