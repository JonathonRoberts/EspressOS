#include <stddef.h>
#include <stdint.h>
#include "../include/string.h"
#include "../include/sys/io.h"
#include "../include/sys/param.h"
//#include "../include/sys/idt.h"
#include "../include/sys/debug.h"
#include "findpcidevice.h"
//#include "../include/sys/alloc.h"
//#include "../include/sys/fat.h"
//#include "boot.h"
#include "ahci.h"

int main()
{

	uint16_t pcicount = enumeratepci();

/*
	disable_cursor();
	init_IDT();

	kprint(0x2, "\t\t\tWelcommen to Mein Operating System\t\t        \n");
	kprint(0x2, "\t\t\t\tEspressOS v0.01\t\t\t\t        \n");

	skprint("\t\t\tWelcommen to Mein Operating System\n");
	skprint("\t\t\t\tEspressOS v0.01\n");
	while(1){
		char a = read_serial();
		if(a =='q')
		{
			qemushutdown();
		}
		else
		{
		write_serial(a);
		}

		kputs(0x2,getchar());

	}
	__asm__(
			"cli\n"
			"hlt"
			);
*/
	return 0;
}
