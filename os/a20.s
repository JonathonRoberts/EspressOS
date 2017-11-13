[bits 64]

; Check A20 line
; and enable if required

global is_A20_on

is_A20_on:
	pushaq
	mov rdi,0x112345  ;odd megabyte address.
	mov rsi,0x012345  ;even megabyte address.
	mov [rsi],rsi     ;making sure that both addresses contain diffrent values.
	mov [rdi],rdi     ;(if A20 line is cleared the two pointers would point to the address 0x012345 that would contain 0x112345 (rdi))
	cmpsq             ;compare addresses to see if the're equivalent.
	popaq
	jne A20_on        ;if not equivalent: return

enable_A20:
        cli

        call    a20wait
        mov     al,0xAD
        out     0x64,al

        call    a20wait
        mov     al,0xD0
        out     0x64,al

        call    a20wait2
        in      al,0x60
        push    rax

        call    a20wait
        mov     al,0xD1
        out     0x64,al

        call    a20wait
        pop     rax
        or      al,2
        out     0x60,al

        call    a20wait
        mov     al,0xAE
        out     0x64,al

        call    a20wait
        sti
	jmp is_A20_on

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

A20_on:
	ret
