%macro PUSH_ALL 0
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push rbp
%endmacro
%macro POP_ALL 0
	pop rbp
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro
