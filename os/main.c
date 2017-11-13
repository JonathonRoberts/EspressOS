void test64(){
	__asm__ __volatile__(
		"mov %rax, 0x01"//x64 test
	);
}
int main(){
	test64();
	__asm__("hlt");
	return 0;
}
