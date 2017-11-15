;---
; bootloader.s
;---
	bits 16
	start: jmp boot

;; constant and variable definitions
msg db "Welcommen to mein operating system!", 0
_CurX db 0
_CurY db 0


MovCur:
	; dh = row
	; dl = col
	mov bh, 0 ; page number (0..7)
	mov ah, 2 ; ah = 2 - sets cursor position
	int 10h
	ret

ClrScr:
	mov dl, 0
	mov dh, 0
	call MovCur
	mov al, ' '
	mov bl, 0
	mov cx, 80*25
	call PutChar
	mov dl, 0
	mov dh, 0
	mov [_CurY], dh
	mov [_CurX], dl
	call MovCur
	ret

PutChar:
	; print character
	mov ah, 0ah ; ah = 0ah - write character at cursor position
	int 10h

	; Increment cursor position
	add [_CurX], cx
	mov dh, [_CurY]
	mov dl, [_CurX]
	call MovCur;
	ret

Print:
	call MovCur
	;mov ah, 0x0e	; print char service
	mov cx, 1	; number of times to display each character

.loop:
	lodsb		; AL <- [DS:SI] && SI++
	or	al, al	; end of string?
	jz	.done
	call PutChar;
	jmp 	.loop
.done:
	ret

GDT:
	.Null: equ $ - GDT
	dw 0
	dw 0
	db 0
	db 0
	db 0
	db 0

	.Code: equ $ - GDT
	dw 0
	dw 0
	db 0
	db 10011000b
	db 00100000b
	db 0

	.Data: equ $ - GDT
	dw 0
	dw 0
	db 10000000b
	db 0
	db 0
	db 0

	.Pointer:
	dw $ - GDT - 1
	dq GDT

Paging:
	; zero 0x1000 - 0x1496
	mov edi, 0x1000
	mov cr3, edi
	xor eax, eax
	mov ecx, 4096
	rep stosd
	mov edi, 0x1000

	;PML4T @ 0x1000
	;PDPT  @ 0x2000
	;PDT   @ 0x3000
	;PT    @ 0x4000

	mov dword [edi], 0x2003
	add edi, 0x1000
	mov dword [edi], 0x3003
	add edi, 0x1000
	mov dword [edi], 0x4003
	add edi, 0x1000

	mov dword ebx, 3 ;
	mov ecx, 512 ; loop 512 times

	.setEntry:
		mov dword [edi], ebx
		add ebx, 0x1000
		add edi, 8
	loop .setEntry

	; Turn Paging on
	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov ecx, 0xc0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	ret

boot:
	;Protected Mode
	cld; Clear direction flag

	;call ClrScr
	;mov si, msg	; SI points to message
	;call Print

	; set video mode
	mov ah, 0x00; teletype output
	mov al, 0x03; vga 3
	mov bh, 0 ; page number (0..7)
	int 10h
	;write test char
	mov al, 0x00
	mov bh, 0 ; page number (0..7)
	int 10h

	;; set the buffer
	mov ax, 0x50
	mov es, ax
	xor bx, bx

	mov al, 2	; read sector 2
	mov ch, 0	; track 0
	mov cl, 2	; sector to read
	mov dh, 0	; head number
	mov dl, 0	; drive number

	mov ah, 0x02	; read sectors from disk
	int 0x13	; call the BIOS routine

	;protected mode
	cli; Disable interrupts

	;A20 line
	; Not very portable way to enable a20
	mov	al, 2
	out	0x92, al

	call Paging

	lgdt[GDT.Pointer]

	mov eax, cr0
	or eax, 1
	or eax, 1 << 31
	mov cr0, eax


	jmp [500h + 18h]	; jump and execute the sector

halt:

	hlt

; we have to be 512 bytes. Clear the rest of the bytes with 0

	times 510 - ($-$$) db 0
	dw 0xAA55 ; Boot signiture
