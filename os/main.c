#include <stddef.h>
#include <stdint.h>
/* implement this */
#include <amd64/i8259.h>

void test64(){
	__asm__ __volatile__(
		"mov %rax, 0x01"/* x64 test */
	);
}

int main(){
	is_A20_on();
	test64();
	__asm__("hlt");
	return 0;
}

