void disable_8259PIC()
{
	__asm__ __volatile(
			"mov $0xff, %al\n"
			"out %al, $0xa1\n"
			"out %al, $0x21"
			);
}
/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

/*
arguments:
	offset1 - vector offset for master PIC
		vectors on the master become offset1..offset1+7
	offset2 - same for slave PIC: offset2..offset2+7
*/
void PIC_remap(int offset1, int offset2)
{
	unsigned char a1, a2;

	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();

	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}

void init_apic()
{
	disable_8259PIC();
}

/* 64 bit IDT structure */
struct IDTDescr
{
	/* base address = offset_3::offset_2::offset_1 */
	uint16_t offset_1; /* offset bits 0..15 */
	uint16_t selector; /* a code segment selector in GDT or LDT */
	uint8_t ist;       /* bits 0..2 holds Interrupt Stack Table offset, rest of bits zero. */
	uint8_t type_attr; /* 1st Present, 2nd,3rd Ring 0-3, 4th 0, 5th,6th,7th,8th Type */
	uint16_t offset_2; /* offset bits 16..31 */
	uint32_t offset_3; /* offset bits 32..63 */
	uint32_t zero;     /* reserved */
}__attribute__((packed));


/* 64 bit IDT pointer */
struct IDTPointer
{
	/* lidt instruction takes this as an argument */
	uint16_t DTLimit;
	uint64_t *BaseAddress;
}__attribute__((packed));


struct IDTDescr IDT[256];
void setIDT(uint8_t i, uint64_t functionPtr, uint16_t selector, uint8_t ist,uint8_t type_attr)
{
	uint16_t offset1 = (uint16_t)(functionPtr & 0xffff);
	uint16_t offset2 = (uint16_t)(functionPtr >> 16) & 0xffff;
	uint32_t offset3 = (uint32_t)(functionPtr >> 32) & 0xffffffff;
	IDT[i].offset_1 = offset1;
	IDT[i].selector = selector;
	IDT[i].ist = ist;
	IDT[i].type_attr = type_attr;
	IDT[i].offset_2 = offset2;
	IDT[i].offset_3 = offset3;
	IDT[i].zero = 0;
}

void* memset(void* bufptr, int value, size_t size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}
#define memset(b,c,n)	__builtin_memset((b),(c),(n))

extern void isr0();
extern void loadidt(uint64_t rax);
void init_IDT()
{
	PIC_remap(0x20, 0x28);

	/* Create IDT */
	struct IDTPointer IDTP;
	IDTP.DTLimit = (60 * 16) -1;
	IDTP.BaseAddress = (uint64_t*)&IDT;

	int i;
	for(i=0;i<60;i++){
		//setIDT(i,(uint64_t)isr0,0x8,0x8e,128+15);
		setIDT(i,0,0,0,0);
		//memset(&IDT[i],0,15);
	}
//	__asm__ __volatile("lidtq (%0)"::"m"(&IDTP));
	outb(0x21,0xfd);/* Only allow keyboard interrupts */
	outb(0xa1,0xff);
	loadidt((uint64_t)&IDTP);
	//__asm__ __volatile("lidtq (%0)"::"m"(idtp));
}

