/*#include "../include/sys/param.h"
#include "../include/sys/io.h"
#include <stddef.h>
#include <stdint.h>

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

static void init_idt()
{
	// Remap the irq table.
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
	idt_set_gate(32,(uint32_t)irq0,0x08,0x8E);
	idt_set_gate(32,(uint32_t)irq1,0x08,0x8E);
	idt_set_gate(32,(uint32_t)irq2,0x08,0x8E);
	idt_set_gate(32,(uint32_t)irq3,0x08,0x8E);
	idt_set_gate(32,(uint32_t)irq4,0x08,0x8E);
	idt_set_gate(32,(uint32_t)irq5,0x08,0x8E);
	idt_set_gate(32,(uint32_t)irq6,0x08,0x8E);
	idt_set_gate(32,(uint32_t)irq7,0x08,0x8E);
	idt_set_gate(32,(uint32_t)irq8,0x08,0x8E);
	idt_set_gate(32,(uint32_t)irq9,0x08,0x8E);
	idt_set_gate(47,(uint32_t)irq10,0x08,0x8E);
	idt_set_gate(47,(uint32_t)irq11,0x08,0x8E);
	idt_set_gate(47,(uint32_t)irq12,0x08,0x8E);
	idt_set_gate(47,(uint32_t)irq13,0x08,0x8E);
	idt_set_gate(47,(uint32_t)irq14,0x08,0x8E);
	idt_set_gate(47,(uint32_t)irq15,0x08,0x8E);
}
*/
