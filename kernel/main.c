#include <stddef.h>
#include <stdint.h>
#include "../include/sys/io.h"
#include "../include/sys/param.h"

int main()
{
	disable_cursor();
	kclearscreen();
	kprint(0x2, "Hello world!\n");
	kprint(0x2, "Hello world!\n");
	kprint(0x2, "Implementing tabs\n1234567890\n\ttab\n123\ttab\n");
	while(1)
		kputs(0x2,getchar());
	__asm__("hlt");
	return 0;
}
