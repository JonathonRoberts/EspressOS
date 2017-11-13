void PutChar(){
	__asm__(
		"mov %rax, 0x01"//row

	);
}

int main(){
	PutChar();
	__asm__("hlt");
	return 0;
}
