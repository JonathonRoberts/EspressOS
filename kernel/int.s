global isr0
global isr1
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr10
global isr11
global isr12
global isr13
global isr14
global isr16
global isr17
global isr18
global isr19

global oisr0
global oisr1
;global oisr2
;global oisr3
;global oisr4
;global oisr5
;global oisr6
;global oisr7
;global oisr8
;global oisr9
;global oisr10
;global oisr11
;global oisr12
;global oisr13
;global oisr14
;global oisr15
;global oisr16
;global oisr17
;global oisr18
;global oisr19
;global oisr20
;global oisr21
;global oisr22
;global oisr23
;global oisr24
;global oisr25
;global oisr26
;global oisr27
;global oisr28
;global oisr29
;global oisr30
;global oisr31

%include "macros.s"
extern sponge

extern IDTP
global LIDT
LIDT:
	lidt [rel IDTP]
	sti
	ret

isr0:
;#DE Divide by Zero
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr1:
;#DB Debug
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr3:
;#BP Breakpoint
	cli
	push qword 0
	PUSH_ALL
	call sponge
	jmp isr_ret
isr4:
;#OF Overflow
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr5:
;#BR BOUND Range Exceeded
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr6:
;#UD Invalid Opcode
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr7:
;#NM Device Not available (No Math Coprocessor)
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr8:
;#DF Double Fault
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr10:
;#TS INvalid TSS
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr11:
;#NP Segment Not Present
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr12:
;#SS Stack segment Fault
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr13:
;#GP General Protection
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr14:
;#PF Page Fault
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr16:
;#MF Flauting Point Error (Math Fault)
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr17:
;#AC Alignment Check
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr18:
;#MC Machine Check
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr19:
;#XM SIMD Floating Point Numeric Error
	cli
	push qword 0 ;push faux error code to create uniform stack size
	PUSH_ALL
	jmp isr_ret
oisr0:
;Time
	cli
	push qword 0 ;push faux error code to create uniform stack size
	PUSH_ALL
	jmp isr_ret
oisr1:
;Keyboard interrupt
	cli
	PUSH_ALL
	in al,60h		; Read keypress from port 60h
	mov [0xb8000], al	; print scancode

	mov ah, 0x02		; colour
	mov [0xb8001], ah

	push qword 0
	jmp isr_ret
oisr2:
oisr3:

isr_ret:
	mov ax, 0x20
	out 0x20, ax	; Send end of interrupt command to master PIC
	POP_ALL
	cld
	sti
	add rsp, 8
	iretq
