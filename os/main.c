#include <stdio.h>
#include <ctype.h>

void PutChar(){
	__asm__(
		"mov %eax, 0x3"
	);
}


int main(){
	PutChar();
}

