#include <stddef.h>
#include <stdint.h>
/* implement this */
#include <amd64/i8259.h>

#define VIDEO_MEM 0xB8000
#define VIDEO_COLS 80
#define VIDEO_ROWS 25
#define TAB_SPACE 8

void test64(){
	__asm__ __volatile__(
		"mov %rax, 0x01"/* x64 test */
	);
}
void kprint( char colour, const char *string ){
	volatile char *video = (volatile char*)VIDEO_MEM;
	int col = 0;
	while(*string) {
		switch(*string){
			case '\t': {
				if(col<VIDEO_COLS-TAB_SPACE){
					string++;
					do{
						video++;
						*video++ = colour;
						col++;
					}while(col%TAB_SPACE);
				}
					break;
			}
			case '\n': {
				video+=(VIDEO_COLS-col)*2;
				col = 0;
				string++;
				break;
			}
			default:
				*video++ = *string++;
				*video++ = colour;
				col++;
		}
	}
}

int main(){
	kprint(2, "Hello World!\nNewlines implemented!\nAlso\ttabs\thave\tbeen\timplemented\nin\ta\tway\tthat\tthey\nline\tup!");
	test64();
	__asm__("hlt");
	return 0;
}

