extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void LIDT();

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

/*
 *
 * IDT
 *
 */

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

/* Declare IDT and IDTP */
struct IDTDescr IDT[256];
struct IDTPointer IDTP;

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

void init_IDT()
{
	PIC_remap(0x20, 0x28);

	outb(0x21,0xfd);/* Only allow keyboard interrupts */
	outb(0xa1,0xff);

	/* Create IDT */
	IDTP.DTLimit = (255 * 8);
	IDTP.BaseAddress = (uint64_t*)&IDT;

	int i;
	for(i=0;i<256;i++){
		setIDT(i,(uint64_t)isr0,0x8,0x8e,128+15);
	}
	LIDT();

	//setIDT(0,(uint64_t)isr0,0x8,0x8e,128+15);
	//setIDT(1,(uint64_t)isr1,0x8,0x8e,128+15);
	//setIDT(2,(uint64_t)isr2,0x8,0x8e,128+15);
	//setIDT(3,(uint64_t)isr3,0x8,0x8e,128+15);
	//setIDT(4,(uint64_t)isr4,0x8,0x8e,128+15);
	//setIDT(5,(uint64_t)isr5,0x8,0x8e,128+15);
	//setIDT(5,(uint64_t)isr5,0x8,0x8e,128+15);
	//setIDT(6,(uint64_t)isr6,0x8,0x8e,128+15);
	//setIDT(7,(uint64_t)isr7,0x8,0x8e,128+15);
	//setIDT(8,(uint64_t)isr8,0x8,0x8e,128+15);
	//setIDT(8,(uint64_t)isr8,0x8,0x8e,128+15);
	//setIDT(9,(uint64_t)isr9,0x8,0x8e,128+15);
	//setIDT(10,(uint64_t)isr10,0x8,0x8e,128+15);
	//setIDT(11,(uint64_t)isr11,0x8,0x8e,128+15);
	//setIDT(12,(uint64_t)isr12,0x8,0x8e,128+15);
	//setIDT(13,(uint64_t)isr13,0x8,0x8e,128+15);
	//setIDT(14,(uint64_t)isr14,0x8,0x8e,128+15);
	//setIDT(15,(uint64_t)isr15,0x8,0x8e,128+15);
	//setIDT(15,(uint64_t)isr15,0x8,0x8e,128+15);
	//setIDT(16,(uint64_t)isr16,0x8,0x8e,128+15);
	//setIDT(17,(uint64_t)isr17,0x8,0x8e,128+15);
	//setIDT(18,(uint64_t)isr18,0x8,0x8e,128+15);
	//setIDT(18,(uint64_t)isr18,0x8,0x8e,128+15);
	//setIDT(19,(uint64_t)isr19,0x8,0x8e,128+15);
	//setIDT(20,(uint64_t)isr20,0x8,0x8e,128+15);
	//setIDT(21,(uint64_t)isr21,0x8,0x8e,128+15);
	//setIDT(22,(uint64_t)isr22,0x8,0x8e,128+15);
	//setIDT(23,(uint64_t)isr23,0x8,0x8e,128+15);
	//setIDT(24,(uint64_t)isr24,0x8,0x8e,128+15);
	//setIDT(25,(uint64_t)isr25,0x8,0x8e,128+15);
	//setIDT(25,(uint64_t)isr25,0x8,0x8e,128+15);
	//setIDT(26,(uint64_t)isr26,0x8,0x8e,128+15);
	//setIDT(27,(uint64_t)isr27,0x8,0x8e,128+15);
	//setIDT(28,(uint64_t)isr28,0x8,0x8e,128+15);
	//setIDT(28,(uint64_t)isr28,0x8,0x8e,128+15);
	//setIDT(29,(uint64_t)isr29,0x8,0x8e,128+15);
	//setIDT(30,(uint64_t)isr30,0x8,0x8e,128+15);
	//setIDT(31,(uint64_t)isr31,0x8,0x8e,128+15);
}

