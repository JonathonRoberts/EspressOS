void disable_8259PIC()
{
	__asm__ __volatile(
			"mov $0xff, %al\n"
			"out %al, $0xa1\n"
			"out %al, $0x21"
			);
}

void init_apic()
{
	disable_8259PIC();
}

/* 64 bit IDT structure */
struct IDTDescr {
	/* base address = offset_3::offset_2::offset_1 */
	uint16_t offset_1; /* offset bits 0..15 */
	uint16_t selector; /* a code segment selector in GDT or LDT */
	uint8_t ist;       /* bits 0..2 holds Interrupt Stack Table offset, rest of bits zero. */
	uint8_t type_attr; /* 1st Present, 2nd,3rd Ring 0-3, 4th 0, 5th,6th,7th,8th Type */
	uint16_t offset_2; /* offset bits 16..31 */
	uint32_t offset_3; /* offset bits 32..63 */
	uint32_t zero;     /* reserved */
} __attribute__((packed));

struct IDTDescr IDT[256];
void setIDT(uint8_t i, uint64_t functionPtr, uint16_t selector, uint8_t ist,uint8_t type_attr)
{
	uint16_t offset1 = (functionPtr & 0x000000ffUL);
	uint16_t offset2 = (functionPtr & 0x0000ff00UL) >> 16;
	uint32_t offset3 = (functionPtr & 0xffff0000UL) >> 32;
	IDT[i].offset_1 = offset1;
	IDT[i].selector = selector;
	IDT[i].ist = ist;
	IDT[i].type_attr = type_attr;
	IDT[i].offset_2 = offset2;
	IDT[i].offset_3 = offset3;
	IDT[i].zero = 0;
}

void isr0(){
	__asm__ __volatile__("hlt");
	//__asm__ __volatile__("iret");
}

void init_IDT()
{

	/* Create IDT */
	int i;
	for(i=0;i<256;i++)
		setIDT(i,(uint64_t)isr0,0x8,0x8e,128+15);

	/* Load IDT */
	struct IDTDescr *idtp;
	idtp = &IDT[0];
	__asm__ __volatile__("lidt %0" :: "m"(*idtp));

	/* Test IDT */
	outb(0x21,0xfd);
	outb(0xa1,0xff);
	__asm__("sti");
	/*int a, b;
	a = 1;
	b = 0;
	a /=b;
	*/
}

