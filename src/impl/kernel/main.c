#include <manio.h>
#include <display.h>
#include <math.h>
#include <keyboard.h>
#include <rand.h>
#include <interrupts.h>
#include <stdbool.h>
int *serparateDigits(int n);

static __inline unsigned char inb(unsigned short int port) {
	unsigned char _v;
    
    // What the fuck, How does this work?
	__asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (port));
	return _v;
}

void outb(unsigned short port, unsigned char val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline void cpuid(int code, uint32_t* a, uint32_t* d) {};

void _main() {
    char c = 0;

    spc(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    cls();
    
    do {
        if (inb(0x60) != c) {
            c = inb(0x60);
            if (c > 0) {
                strp(translate(c, false));
            }
        }
    } while (c != 1);
}