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

	__asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (port));
	return _v;
}

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