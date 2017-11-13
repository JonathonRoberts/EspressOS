#include <stdio.h>
#include <ctype.h>

void PutChar(){
	__asm__(
		"mov %rax, 0x3"
	);
}


int main(){
	PutChar();
}

