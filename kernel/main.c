#include <stddef.h>
#include <stdint.h>
#include "../include/sys/io.h"
#include "../include/sys/param.h"

#include "../include/sys/idt.c"

extern void init_IDT();
extern void setuphw();

void sponge(){
	kprint(0x2, "Sponge\n");
	isr0();
	return;
}
int main()
{

	//disable_cursor();
	kclearscreen();
	setuphw();
	init_IDT();
	outb(0x21,0xff);
	outb(0xa1,0xff);
	//__asm__("sti");
	kprint(0x2, "Hello world!\n");
	kprint(0x2, "Hello world!\n");
	kprint(0x2, "Implementing tabs\n1234567890\n\ttab\n123\ttab\n");

	while(1){
		kputs(0x2,getchar());
	}
	__asm__("hlt");
	return 0;
}
