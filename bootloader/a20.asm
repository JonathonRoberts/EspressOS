; Check A20 line
; and enable if required
global Test_A20

Test_A20
        call is_A20_on
        cmp ax, 1
        je Enabled_A20

        call Keyboard_Enable_A20
        call is_A20_on
        cmp ax, 1
        je Enabled_A20

        call BIOS_Enable_A20
        cmp ax, 0
        je FastA20
        call is_A20_on
        cmp ax, 1
        je Enabled_A20

FastA20:
        in al, 0x92
        or al, 2
        out 0x92, al

        call is_A20_on
        cmp ax, 1
        je Enabled_A20
        hlt
Enabled_A20:
	ret

is_A20_on:
	pushf
	push ds
	push es
	push di
	push si

	xor ax, ax
	mov es, ax

	not ax
	mov ds, ax

	mov di, 0x0500
	mov si, 0x0510

	mov al, byte [es:di]
	push ax

	mov al, byte [ds:si]
	push ax

	mov byte [es:di], 0x00
	mov byte [ds:si], 0xff

	cmp byte [es:di], 0xff

	pop ax
	mov byte [ds:si], al

	pop ax
	mov byte [es:di], al

	mov ax, 0
	je test_exit

	mov ax, 1

test_exit:
	pop si
	pop di
	pop es
	pop ds
	popf
	ret

Keyboard_Enable_A20:
        call    a20wait
        mov     al,0xAD
        out     0x64,al

        call    a20wait
        mov     al,0xD0
        out     0x64,al

        call    a20wait2
        in      al,0x60
        push    ax

        call    a20wait
        mov     al,0xD1
        out     0x64,al

        call    a20wait
        pop     ax
        or      al,2
        out     0x60,al

        call    a20wait
        mov     al,0xAE
        out     0x64,al

        jmp    a20wait
        sti
	ret

a20wait:
        in      al,0x64
        test    al,2
        jnz     a20wait
        ret


a20wait2:
        in      al,0x64
        test    al,1
        jz      a20wait2
        ret

BIOS_Enable_A20:
	mov     ax,0x2403
	int     15h
	jb      A20_BIOS_FAIL	; int 15h is unsupported
	cmp     ah,0
	jnz     A20_BIOS_FAIL	; int 15h is unsupported

	mov     ax,0x2402
	int     15h
	jb      A20_BIOS_FAIL	; Couldn't get status
	cmp     ah,0
	jnz     A20_BIOS_FAIL	; Couldn't get status

	cmp     al,1
	jz      a20_Activated

	mov     ax,0x2401
	int     15h
	jb      A20_BIOS_FAIL	; failed
	cmp     ah,0
	jnz     A20_BIOS_FAIL	; failed

a20_Activated:
	mov ax, 1
	ret

A20_BIOS_FAIL:
	mov ax, 0
	ret
