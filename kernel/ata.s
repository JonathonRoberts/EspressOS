global ata_lba_read28:
global ata_lba_read48:
extern sponge

check_ready:
	mov  dx, 0x1f7
	in   al, dx
	test al, 0x80
	jz   check_ready
	ret

check_read_complete:
	mov  dx, 0x1f7
	in   al, dx
	test al, 0x40
	jz   check_ready
	ret

check_bsy:
.wait_for_bsy:
	in al, dx
	test al, 0x80
	jnz .wait_for_bsy
.wait_for_drq:
	in al, dx
	test al, 0x8
	jz .wait_for_bsy
	ret

pio_delay:
	nop
	nop
	nop
	nop
	ret

ata_lba_read28:
	pushfq
	and rax, 0x0FFFFFFF
	push rax
	push rbx
	push rcx
	push rdx
	push rdi

	mov rax, 1	; LBA of sector
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

	call check_bsy

	mov rax, 256         ; to read 256 words
	xor bx, bx
	mov bl, cl           ; read CL sectors
	mul bx
	mov rcx, rax         ; RCX is counter for INSW
	mov rdx, 0x1F0       ; Data port, in and out
	rep insw             ; in to [RDI]

	pop rdi
	pop rdx
	pop rcx
	pop rbx
	pop rax
	popfq
	ret

ata_reset:
	mov dx, 0x3f6
	mov al, 4
	out dx, al
	mov al, 2
	out dx, al
	in al, dx
	in al, dx
	in al, dx
	in al, dx
	ret

ata_lba_read48:
	push rbp
	mov  rbp, rsp

	push rax
	push rbx
	push rcx
	push rdx
	push rdi

	mov rax, 19	; LBA of sector
	mov cx, 14	; Sectors to Read

	mov rax, 1	; LBA of sector
	mov cx, 1	; Sectors to Read
	mov rdi, 0x100000	; buffer location
	mov rbx, rax ; store rax in rbx

	; Disable Interrupts
	mov dx, 0x3F6
	mov al, 2
	out dx, al

	call check_ready

	mov rdx, 0x1f5		;0x1f5 - LBA6
	mov rax, rbx         ; Get LBA from RBX
	shr rax, 40
	out dx, al
	call pio_delay

	mov rdx, 0x1f5		;0x1F5 - LBA3
	shr rax, 16
	out dx, al
	call pio_delay

	mov rdx, 0x1f4		;0x1f4 - LBA5
	mov rax, rbx         ; Get LBA from RBX
	shr rax, 32
	out dx, al
	call pio_delay

	mov rdx, 0x1f4		;0x1F4 - LBA2
	shr rax, 8
	out dx, al
	call pio_delay

	mov rdx, 0x1f3		;0x1f3 - LBA4
	mov rax, rbx         ; Get LBA from RBX
	shr rax, 24
	out dx, al
	call pio_delay

	mov rdx, 0x1f3		;0x1f3 - LBA1
	mov rax, rbx         ; Get LBA from RBX
	out dx, al
	call pio_delay

	mov rdx, 0x1f2 		;0x1f2 - Sector Count High
	;mov al, ch
	xor al, al
	out dx, al
	call pio_delay

	mov rdx, 0x1f2 		;0x1f2 - Sector Count Low
	mov al, cl
	out dx, al
	call pio_delay

	mov rdx, 0x1f1 		; 0x1f1
	mov al, 0x0		; Master
	out dx, al
	call pio_delay

	mov rdx, 0x1f1 		; 0x1f1 - Feature
	mov al, 0x0		; Master
	out dx, al
	call pio_delay

	mov rdx, 0x1f6 		; 0x1f6 - Drive
	mov al, 11100000b		; Master
	out dx, al
	call pio_delay

	mov rdx, 0x1f7		;0x1F7 - Command port
	mov al, 0x24         ; Read with retry.
	out dx, al

	call check_read_complete

	mov  rax, 256
	xor rbx, rbx
	mov bl, cl
	mul  bx

	mov  rcx,  rax
	mov  rdx,  0x1f0
	rep  insw

	pop  rdi
	pop  rdx
	pop  rcx
	pop  rbx
	pop  rax
	pop  rbp
	xor  rax, rax
	ret
