#include <stddef.h>
#include <stdint.h>
//#include "../include/string.h"
#include "../include/sys/io.h"
#include "../include/sys/param.h"
#include "../include/sys/idt.h"

void sponge(){
	kprint(0x2, "Sponge\n");
	return;
}

int main()
{

	//disable_cursor();
	init_IDT();
	kclearscreen();
	kprint(0x2, "Hello world!\n");
	kprint(0x2, "Hello world!\n");
	kprint(0x2, "Implementing tabs\n1234567890\n\ttab\n123\ttab\n");
	sponge();
	__asm__("int3");
	while(1){
//		kputs(0x2,getchar());

	}
	__asm__("hlt");
	return 0;
}
