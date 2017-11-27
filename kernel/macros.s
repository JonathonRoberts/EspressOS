%macro PUSH_ALL 0
push %rax
push %rbx
push %rcx
push %rdx
push %rsi
push %rdi
push %rbp
%endmacro
%macro POP_ALL 0
pop %rax
pop %rbx
pop %rcx
pop %rdx
pop %rsi
pop %rdi
pop %rbp
%endmacro
