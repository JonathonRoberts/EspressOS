#include <stddef.h>
#include <stdint.h>
//#include "../include/string.h"
#include "../include/sys/io.h"
#include "../include/sys/param.h"
#include "../include/sys/idt.h"
#include "../include/sys/debug.h"

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
	char a;
	while(1){
		a = read_serial();
		if(a =='q')
		{
			qemushutdown();
		}
		else
		{
		write_serial(a);
		}

//		kputs(0x2,getchar());

	}
	/*
	__asm__(
			"cli\n"
			"hlt"
			);
	*/
	return 0;
}
