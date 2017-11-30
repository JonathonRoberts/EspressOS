extern IDTP

global LIDT
;global IDT
;IDT:
;	.int0:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int1:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int2:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int3:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int4:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int5:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int6:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int7:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int8:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int9:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int10:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int11:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int12:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int13:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int14:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int15:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int16:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int17:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int18:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;	.int19:
;	dw 0
;	dw 0
;	db 0
;	db 0
;	dw 0
;	dd 0
;	dd 0
;
;	.Pointer:
;	dw $ - IDT - 1; size of IDT in bytes
;	dq IDT; location of idt
;
LIDT:
	;lea rax, [rel IDT.Pointer]
	lidt  [rel IDTP]
	cli

	retq
