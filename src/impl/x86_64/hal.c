#include "hal.h"
#include "display.h"
#include "pic.h"
#include "tasking.h"
#include "idt.h"

#include <stdint.h>

MODULE("HAL");

void hal_init()
{
	mprint("Init done.\n");
}

void send_eoi(uint8_t irq)
{
	pic_send_eoi(irq);
}

void set_int(int i, uint32_t addr)
{
	mprint("Installing INT#%d to address: 0x%x\n", i, addr);
	idt_register_interrupt(i, addr);
}

uint8_t inportb(uint16_t portid)
{
	uint8_t ret;
	asm volatile("inb %%dx, %%al":"=a"(ret):"d"(portid));
	return ret;
}
uint16_t inportw(uint16_t portid)
{
	uint16_t ret;
	asm volatile("inw %%dx, %%ax":"=a"(ret):"d"(portid));
	return ret;
}
uint32_t inportl(uint16_t portid)
{
	uint32_t ret;
	asm volatile("inl %%dx, %%eax":"=a"(ret):"d"(portid));
	return ret;
}
void outportb(uint16_t portid, uint8_t value)
{
	asm volatile("outb %%al, %%dx": :"d" (portid), "a" (value));
}
void outportw(uint16_t portid, uint16_t value)
{
	asm volatile("outw %%ax, %%dx": :"d" (portid), "a" (value));
}
void outportl(uint16_t portid, uint32_t value)
{
	asm volatile("outl %%eax, %%dx": :"d" (portid), "a" (value));
}

