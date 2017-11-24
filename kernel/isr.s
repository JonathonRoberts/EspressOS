global ISR
global load_idt


; load_idt - Loads the interrupt descriptor table (IDT).
; stack: [esp + 4] the address of the first entry in the IDT
;        [esp    ] the return address
load_idt:
mov	rax, [rsp+4]    ; load the address of the IDT into register eax
lidt	[rax]           ; load the IDT
ret                     ; return to the calling function


ISR:
	ret
