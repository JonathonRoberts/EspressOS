#include <stddef.h>
#include <stdint.h>
////#include "../include/string.h"
#include "../include/sys/io.h"
#include "../include/sys/param.h"
#include "../include/sys/idt.h"
#include "../include/sys/debug.h"
//#include "../include/sys/fat.h"

int main()
{

	//disable_cursor();
	init_IDT();
//	init_FAT();
	kclearscreen();
	/*
	sponge();
	__asm__("int3");
	*/
	kprint(0x2, "\t\t\tWelcommen to Mein Operating System\t\t        \n");
	kprint(0x2, "\t\t\t\tEspressOS v0.01\t\t\t\t        \n");
	//kprint(0x2, " Todo:\n");
//	kprint(0x2, "\t* Kprintf function\n");
//	kprint(0x2, "\t* Dump Registers function\n");
//	kprint(0x2, "\t* Filesystem\n");
//	kprint(0x2, "\t* LibC\n");
//	kprint(0x2, "\t* Malloc and Free\n");
//
//	skprint("\t\t\tWelcommen to Mein Operating System\n");
//	skprint("\t\t\t\tEspressOS v0.01\n");
//	skprint(" Todo:\n");
//	skprint("\t* Kprintf function\n");
//	skprint("\t* Dump Registers function\n");
//	skprint("\t* Filesystem\n");
//	skprint("\t* LibC\n");
//	skprint("\t* Malloc and Free\n");
//	char a;
	while(1){
//		a = read_serial();
//		if(a =='q')
//		{
//			qemushutdown();
//		}
//		else
//		{
//		write_serial(a);
//		}

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
