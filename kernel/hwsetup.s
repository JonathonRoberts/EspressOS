%define HD_PORT=0x1F0
global setuphw
setuphw:
	; set up interrupt controller
	mov al, 0b00010001
	out  0x20,al
	out  0xa0,al
	mov  al,0x20
	out  0x21,al
	mov  al,0x28
	out 0xa1,al
	mov al,0b00000100
	out 0x21,al
	mov al,0b00000010
	out 0xa1,al
	mov al,0x00000001
	out  0x21, al
	out  0xa1, al
	mov al,0b11111011     ; disable all interrupts,
	out 0x21,al
	mov al,0b11111111
	out 0xa1,al

	; set up keyboard controller
	call InBuffEmpty
	mov al,0x0FA
	out 0x60,al
	call OutBuffFull
	in al,0x60
	call InBuffEmpty
	mov al,0xF0
	out 0x60,al
	call OutBuffFull
	in al,0x60
	call InBuffEmpty
	mov al,0x2
	out 0x60,al
	call OutBuffFull
	in al,0x60
	call InBuffEmpty
	mov al,0x60
	out 0x64,al
	call InBuffEmpty
	mov al,0x45
	out 0x60,al

	in   al,0x60        ; Clear any pending Kbd interrupt
	; enable interrupts
	;mov al, 0b11111000    ; enable keyboard + timer interrupt
	;mov al,0b11111010     ; enable timer interrupt
	;out 0x21,al

	; reset ide controller
	;       mov al,0b00000100
	;       out 0x3f6,al
	; enable hd interrupt
	mov al,0b10111111
	out 0xa1,al

	; set up timer hardware for interrupts every 10ms
	mov al,0x9C
	out 0x40,al
	mov al,0x2e
	out 0x40,al

	; set up ide controller
again1:
	mov  dx, 0x1f7
	in al,dx
	test al,0x80
	jnz again1
	mov  dx,0x1f6
	mov al,0
	out dx,al
	mov  dx,0x1f7
	mov al,0x10
	out dx,al
	ret


InBuffEmpty:
	push rax
	push rcx
	mov rcx,0x2FFFF
ibe:
	in al,0x64
	test al,2
	loopnz ibe
	pop rcx
	pop rax
	ret

OutBuffFull:
	push rax
	push rcx
	mov ecx,0x2FFFF
obf:
	in al,0x64
	test al,1
	loopz   obf
	pop rcx
	pop rax
	ret
