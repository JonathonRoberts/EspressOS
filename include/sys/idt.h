//extern void isr0();
void isr0();
extern void isr1();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr8();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr18();
extern void isr19();

extern void isr32();
extern void isr33();
//extern void isr32();
//extern void isr33();
//extern void isr34();
//extern void isr35();
//extern void isr35();
//extern void isr36();
//extern void isr37();
//extern void isr38();
//extern void isr38();
//extern void isr39();
//extern void isr40();
//extern void isr41();
//extern void isr42();
//extern void isr43();
//extern void isr44();
//extern void isr45();
//extern void isr45();
//extern void isr46();
//extern void isr47();
//extern void isr48();
//extern void isr48();
//extern void isr49();
//extern void isr50();
//extern void isr51();
//extern void isr52();
//extern void isr53();
//extern void isr54();
//extern void isr55();
//extern void isr55();
//extern void isr56();
//extern void isr57();
//extern void isr58();
//extern void isr59();
//extern void isr60();
//extern void isr61();

extern void LIDT();

/*
 *
 * PIC
 *
 */

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

#define OFFSET1		0x20		/* Master PIC offset */
#define OFFSET2		0x28		/* Slave PIC offset */

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
struct IDTDescr IDT[512];
struct IDTPointer IDTP;

void setIDT(uint8_t i, uint64_t functionPtr, uint16_t selector, uint8_t ist,uint8_t type_attr)
{
	//i += OFFSET1;
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
	PIC_remap(OFFSET1, OFFSET2);

	/* Create IDT */
	IDTP.DTLimit = (511 * 8);
	IDTP.BaseAddress = (uint64_t*)&IDT;

	/* Initialise IDT array with present bit of 0 for all interrupts */
	int i;
	for(i=0;i<512;i++){
		IDT[i].type_attr = 0;
	}

	/*
	 *
	 * Exceptions
	 * Traps, Faults, and Aborts
	 *
	 */
	setIDT(0,(uint64_t)isr0,0x8,0x8,128+15);	/* F - Divide by Zero */
	//setIDT(1,(uint64_t)isr1,0x8,0x8,128+15);	/* T - Debug */
	setIDT(3,(uint64_t)isr3,0x8,0x8,128+15);	/* T - Breakpoint */
	///setIDT(4,(uint64_t)isr4,0x8,0x8,128+15);	/* T - Overflow */
	//setIDT(5,(uint64_t)isr5,0x8,0x8,128+15);	/* F - Bound Range Exceeded */
	//setIDT(6,(uint64_t)isr6,0x8,0x8,128+15);	/* F - Invalid Opcode */
	//setIDT(7,(uint64_t)isr7,0x8,0x8,128+15);	/* F - Device Not Available */
	//setIDT(8,(uint64_t)isr8,0x8,0x8,128+15);	/* A - Double Fault */
	//setIDT(10,(uint64_t)isr10,0x8,0x8,128+15);	/* F - Invalid TSS  */
	//setIDT(11,(uint64_t)isr11,0x8,0x8,128+15);	/* F - Segment Not Present */
	//setIDT(12,(uint64_t)isr12,0x8,0x8,128+15);	/* F - Stack-Segment Fault */
	//setIDT(13,(uint64_t)isr13,0x8,0x8,128+15);	/* F - General Protection Fault */
	//setIDT(14,(uint64_t)isr14,0x8,0x8,128+15);	/* F - Page Fault */
	//setIDT(16,(uint64_t)isr16,0x8,0x8,128+15);	/* F - x87 Floating-Point Exception */
	//setIDT(17,(uint64_t)isr17,0x8,0x8,128+15);	/* F - Alignment Check */
	//setIDT(18,(uint64_t)isr18,0x8,0x8,128+15);	/* A - Machine Check */
	//setIDT(19,(uint64_t)isr19,0x8,0x8,128+15);	/* F - SIMD Floating-Point Exception */
	//setIDT(20,(uint64_t)isr19,0x8,0x8,128+15);	/* F - Virtualisation Exception */
	//setIDT(30,(uint64_t)isr19,0x8,0x8,128+15);	/* F - Security Exception */

	/* Interrupts */
	setIDT(32,(uint64_t)isr32,0x8,0x8,128+15);	/* Timer */
	setIDT(33,(uint64_t)isr33,0x8,0x8,128+15);	/* Keyboard */
	//setIDT(33,(uint64_t)isr33,0x8,0x8,128+15);	/* Cascade */
	//setIDT(34,(uint64_t)isr34,0x8,0x8,128+15);	/* COM2 */
	//setIDT(35,(uint64_t)isr35,0x8,0x8,128+15);	/* COM1 */
	//setIDT(36,(uint64_t)isr36,0x8,0x8,128+15);	/* LPT2 */
	//setIDT(37,(uint64_t)isr37,0x8,0x8,128+15);	/* Floppy Disk */
	//setIDT(38,(uint64_t)isr38,0x8,0x8,128+15);	/* LTP1 */
	//setIDT(39,(uint64_t)isr39,0x8,0x8,128+15);	/* CMOS real time clock */
	//setIDT(40,(uint64_t)isr40,0x8,0x8,128+15);	/* Peripherals/legacy SCSI/NIC */
	//setIDT(41,(uint64_t)isr41,0x8,0x8,128+15);	/* Peripherals/legacy SCSI/NIC */
	//setIDT(42,(uint64_t)isr42,0x8,0x8,128+15);	/* PS2 Mouse */
	//setIDT(43,(uint64_t)isr43,0x8,0x8,128+15);	/* FPU/Coprocessor/Inter-processor */
	//setIDT(44,(uint64_t)isr44,0x8,0x8,128+15);	/* Primary ATA Hard Disk */
	//setIDT(45,(uint64_t)isr45,0x8,0x8,128+15);	/* Secondary ATA Hard Disk */
	LIDT();
}

/*
 *
 * Interrupts
 *
 */
void isr0(){
	/* #DE Divide by Zero */
	kprint(0x02, "#DE - Division by Zero");
	__asm__ __volatile__(
			"cli\n"
			"hlt"
			);
}
