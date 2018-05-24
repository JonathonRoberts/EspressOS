#include <stddef.h>
#include <stdint.h>
////#include "../include/string.h"
#include "../include/sys/io.h"
#include "../include/sys/param.h"
//#include "../include/sys/idt.h"
#include "../include/sys/debug.h"
//#include "../include/sys/alloc.h"
//#include "../include/sys/fat.h"
#include "boot.h"
//#include "ata.h"

extern void ata_lba_read28();
extern void ata_lba_read48();

	int *a;
int main()
{

	//disable_cursor();
	//init_IDT();
	//ata_init();
	kputs(0x2, '1');
	//ata_lba_read28();
	ata_lba_read28();
	kputs(0x2, '2');
	a = 0x100000;
		kputs(0x2, '\n');
	if(*a == -1){
		kputs(0x2, '-');
		kputs(0x2, '1');
	}
	else if(*a == 0)
		kputs(0x2, '0');
	else
	kputs(0x2, a);

	init_FAT();
//	kclearscreen();


	/*
	sponge();
	__asm__("int3");
	*/
	//kprint(0x2, "\t\t\tWelcommen to Mein Operating System\t\t        \n");
//	kprint(0x2, "\t\t\t\tEspressOS v0.01\t\t\t\t        \n");
//
//	skprint("\t\t\tWelcommen to Mein Operating System\n");
//	skprint("\t\t\t\tEspressOS v0.01\n");
	while(1){
//		char a = read_serial();
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
