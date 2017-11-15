#include <stddef.h>
#include <stdint.h>
/* implement this */
#include <amd64/i8259.h>

#define VIDEO_MEM 0xB80000
#define VIDEO_COLS 40
#define VIDEO_ROWS 25

void test64(){
	__asm__ __volatile__(
		"mov %rax, 0x01"/* x64 test */
	);
}
void kprint( int colour, const char *string ){
volatile char *video = (volatile char*)0xB8000;
	while(*string)
	{
		*video++ = *string++;
		*video++ = colour;
	}
}

int main(){
	kprint(2, "Hello World!");
	test64();
	__asm__("hlt");
	return 0;
}

