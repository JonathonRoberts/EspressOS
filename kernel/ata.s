global ata_lba_read:
global ReadPSector:
ata_lba_read:
	pushfq
	and rax, 0x0FFFFFFF
	push rax
	push rbx
	push rcx
	push rdx
	push rdi

	mov rax, 19	; LBA of sector
	mov cl, 14	; Sectors to Read
	mov rdi, 0x100000	; buffer location

	mov rbx, rax         ; Save LBA in RBX

	mov rdx, 0x01F1      ; Using PIO
	xor al, al           ; Get number of sectors from CL
	out dx, al

	inc rdx      		;0x1f2 - Sector Count
	mov al, cl           ; Get number of sectors from CL
	out dx, al

	inc rdx			;0x1f3 - Sector Number
	mov rax, rbx         ; Get LBA from RBX
	out dx, al

	inc rdx			;0x1f4 - Cylinder Low
	mov rax, rbx         ; Get LBA from RBX
	shr rax, 8           ; Get bit 8 - 15 in AL
	out dx, al

	inc rdx			;0x1f5 - Cylinder High
	mov rax, rbx         ; Get LBA from RBX
	shr rax, 16          ; Get bit 16 - 23 in AL
	out dx, al

	inc rdx			;0x1F6 - Drive
	shr rax, 24          ; Get bit 24 - 27 in al
	or al, 11100000b     ; Set bit 6 in al for LBA mode
	out dx, al

	inc rdx			;0x1F7 - Command port
	mov al, 0x20         ; Read with retry.
	out dx, al

.wait_for_bsy:
	in al, dx
	test al, 0x80
	jnz .wait_for_bsy
.wait_for_drq:
	in al, dx
	test al, 0x8
	jz .wait_for_bsy

	mov rax, 256         ; to read 256 words
	xor bx, bx
	mov bl, cl           ; read CL sectors
	mul bx
	mov rcx, rax         ; RCX is counter for INSW
	mov rdx, 0x1F0       ; Data port, in and out
	rep insw             ; in to [RDI]

.error:
	pop rdi
	pop rdx
	pop rcx
	pop rbx
	pop rax
	popfq
	ret


;ReadPSector:
;; Load one sector from IDE HD to memory
;; rdi address to load too
;; esi sector number
;	pushfq
;	and rax, 0x0FFFFFFF
;	push rax
;	push rbx
;	push rcx
;	push rdx
;	push rdi
;
;	mov rdi, 0x100000
;	mov esi, 19
;
;
;	mov dx,0x01F7
;.again2
;	in al, dx
;	test al, 0x80
;	jnz .again2
;
;	mov dx, 0x01F2
;	mov al, 1
;	out dx, al
;
;	inc dx,
;	mov eax, esi
;	and al, 0xff
;	out dx, al
;
;	inc dx
;	mov eax, esi
;	and ah, 0xff
;	mov al, ah
;	out dx, al
;
;	inc dx
;	mov eax, esi
;	shr eax, 16
;	and al, 0xff
;	out dx, al
;
;	inc dx
;	and ah, 0xf
;	mov al, ah
;	add al, 0x40
;	out dx, al
;
;	inc dx
;	mov ax, 0x20
;	out dx, al
;.again3
;	in al, dx
;	test al, 0x80
;	jnz .again3
;	mov dx, 0x1f0
;	mov eax, 0
;	mov rcx, 256
;	cld
;	rep
;	insw
;	ret
;
;	pop rdi
;	pop rdx
;	pop rcx
;	pop rbx
;	pop rax
;	popfq
;	ret
