;global isr0
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

global isr32
global isr33
;global isr33
;global isr34
;global isr35
;global isr36
;global isr37
;global isr38
;global isr39
;global isr40
;global isr41
;global isr42
;global isr43
;global isr44
;global isr45
;global isr46
;global isr47
;global isr48
;global isr49
;global isr50
;global isr51
;global isr52
;global isr53
;global isr54
;global isr55
;global isr56
;global isr57
;global isr58
;global isr59
;global isr60
;global isr61

%include "macros.s"
extern sponge

extern IDTP
global LIDT
LIDT:
	lidt [rel IDTP]
	sti
	ret
;isr0:
;;#DE Divide by Zero
;	cli
;	push qword 0
;	PUSH_ALL
;	jmp isr_ret
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
isr32:
;Time
	cli
	push qword 0 ;push faux error code to create uniform stack size
	PUSH_ALL
	jmp isr_ret
isr33:
;Cascade
	cli
	PUSH_ALL
	push qword 0
	jmp isr_ret
isr34:
;#COM2
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr35:
;#COM1
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr36:
;#LTP2
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr37:
;#Floppy Disk
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr38:
;#LTP1
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr39:
;#CMOS Real Time Clock
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr40:
;#Peripherals/Legacy SCSI/NIC
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr41:
;#Peripherals/Legacy SCSI/NIC
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr42:
;#PS2 Mouse
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr43:
;#FPU/CoProcessor/Inter-Processor
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr44:
;#Primary ATA Hard Drive
	cli
	push qword 0
	PUSH_ALL
	jmp isr_ret
isr45:
;#Secondary ATA Hard Drive
	cli
	push qword 0
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
