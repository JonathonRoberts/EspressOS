;---
; bootloader.s
;---
	[bits 16]
start:
	jmp boot
;	%include "a20.asm" ; loads but does not execute
	nop

; DOS 2.0 BPB (21 bytes)
OEMIdentifier		db 0x45, 0x53, 0x50, 0x52, 0x45, 0x53, 0x53, 0x4f
BytesPerSector		dw 0x0200
SectorsPerCluster	db 0x01
ReservedSectors		dw 0x001
NoOfFATs		db 0x02
RootdirEntries		dw 0x00E0
LogicalSectors		dw 0x0060
MediaDescriptor		db 0xF0
SectorsPerFAT		dw 0x0009
; DOS 3.1 BPB (12 bytes)
SectorsperTrack		dw 0x0012
NumberofHeads		dw 0x0001
HiddenSectors		dd 0x0000
LargeTotalSectors	dd 0x0000
; DOS 3.4 BPB (13 bytes)
DriveNumber		db 0x00
Flags			db 0x0001
ExtendedBootSig		db 0x29
OsSectors		dd 0x0064
SystemIdentifier	db 0x45, 0x53, 0x50, 0x52, 0x45, 0x53, 0x53, 0x4f


;; Useful functions for debugging
;; constant and variable definitions
;_CurX db 0
;_CurY db 0
;
;
;MovCur:
;	; dh = row
;	; dl = col
;	mov bh, 0 ; page number (0..7)
;	mov ah, 2 ; ah = 2 - sets cursor position
;	int 10h
;	ret
;
;ClrScr:
;	mov dl, 0
;	mov dh, 0
;	call MovCur
;	mov al, ' '
;	mov bl, 0
;	mov cx, 80*25
;	call PutChar
;	mov dl, 0
;	mov dh, 0
;	mov [_CurY], dh
;	mov [_CurX], dl
;	call MovCur
;	ret
;
;PutChar:
;	; print character
;	mov ah, 0ah ; ah = 0ah - write character at cursor position
;	int 10h
;
;	; Increment cursor position
;	add [_CurX], cx
;	mov dh, [_CurY]
;	mov dl, [_CurX]
;	call MovCur;
;	ret
;
;Print:
;	call MovCur
;	mov cx, 1	; number of times to display each character
;
;.loop:
;	lodsb		; AL <- [DS:SI] && SI++
;	or	al, al	; strings are 0 terminated
;	jz	.done
;	call PutChar;
;	jmp 	.loop
;.done:
;	ret

GDT:	; 64 bit Global Descriptor Table
	.Null: equ $ - GDT
	dw 0
	dw 0
	db 0
	db 0
	db 0
	db 0

	.Code: equ $ - GDT
	dw 0 ; Segment limit (low)
	dw 0 ; Base address (low)
	db 0 ; Base address (middle)
	db 10011000b ; 1 Present bit, 2&3 ring level, 4&5=1, 6 conform, 7 readable, 8 cpu access bit
	db 00100000b ; Granularity
	db 0 ; Base address (high)

	.Data: equ $ - GDT
	dw 0 ; Segment limit (low)
	dw 0 ; Base address (low)
	db 10000000b ; Base address (middle)
	db 10010000b ; 1 Present bit, 2&3 ring level, 4=1, 5=0, 6 extend down, 7 writeable, 8 cpu access bit
	db 0 ; Granularity
	db 0 ; Base address (high)

	.Pointer:
	dw $ - GDT - 1 ; Limit
	dd GDT ; Base
	dd 0

Paging:
	; zero 0x1000 - 0x1496
	mov edi, 0x1000
	mov cr3, edi
	xor eax, eax
	mov ecx, 4096
	rep stosd
	mov edi, 0x1000

	; PML4T @ 0x1000
	; PDPT  @ 0x2000
	; PDT   @ 0x3000
	; PT    @ 0x4000

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
	or eax, 1 << 5 ; PAE
	mov cr4, eax

	mov ecx, 0xc0000080
	rdmsr
	or eax, 1 << 8 ; Enables Long Mode
	wrmsr

	ret

boot:
	cld; Clear direction flag

	mov [DriveNumber], dl
	;call ClrScr
	;mov si, msg	; SI points to message
	;call Print

	; set video mode
	mov ah, 0x00; teletype output
	mov al, 0x03; vga 3
	mov bh, 0 ; page number (0..7)
	int 10h

	;;---
	;; Read more sectors
	;;---

	; Start loading at data buffer es:bx = 0x7e00
	mov ax, 0x7e0
	mov es, ax
	xor bx, bx

	mov al, 64 	; Number of sectors to read
	mov ch, 0	; cylinder
	mov cl, 2	; sector to start reading at
	mov dh, 0	; head number
	mov dl, [DriveNumber]	; drive number

	mov ah, 0x02	; read sectors from disk into memory
	int 0x13	; call the BIOS routine

	;mov ax, 0xbe0
	;mov es, ax

	;mov al, 100 	; Number of sectors to read
	;mov ch, 1	; cylinder
	;mov cl, 0	; sector to start reading at

	;mov ah, 0x02	; read sectors from disk into memory
	;int 0x13	; call the BIOS routine

	;mov ax, 0xce0
	;mov es, ax

	;mov al, 100 	; Number of sectors to read
	;mov ch, 2	; cylinder
	;mov cl, 0	; sector to start reading at

	;mov ah, 0x02	; read sectors from disk into memory
	;int 0x13	; call the BIOS routine


	;;---
	;; Long Mode
	;;---

	; Notify BIOS we are going into Long mode
	mov ax, 0xEC00
	mov bl, 2
	int 15h

	;call Test_A20 	; Test for and try to enable A20 line

	cli; Disable interrupts

	call Paging	; Load Page tables

	lgdt[GDT.Pointer] ; Load GDT

	mov eax, cr0
	or eax, 1 ; Enable Protected Mode
	or eax, 1 << 31 ; Enable Paging and use CR3 Register
	mov cr0, eax

	jmp GDT.Code:LongMode

LongMode:
	[bits 64]

	;; Long Mode printing
	;;VID_MEM equ 0xb8000
	;mov edi, 0xb8000
	;mov rax, 0x1f201f201f201f20 ;blue bg, space
	;mov ecx, 501
	;rep stosq
	mov esp, 0x7e00		; move stack pointer

	jmp [0x7e00 +18h]	; Jump to and execute the loaded sector

;; Required to boot
;times 446 -($-$$) db 0
; False partition table entry required by some BIOS vendors.
;db 0x80, 0x00, 0x01, 0x00, 0xEB, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF

; Fill rest boot sector with 0's, required to boot from floppy
times 510 - ($-$$) db 0
; Boot signature the bios looks for
sign dw 0xAA55
