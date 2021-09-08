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

static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
                                unsigned int *ecx, unsigned int *edx)
{
        /* ecx is often an input as well as an output. */
        asm volatile("cpuid"
            : "=a" (*eax),
              "=b" (*ebx),
              "=c" (*ecx),
              "=d" (*edx)
            : "0" (*eax), "2" (*ecx));
}

char* cpudetails() {
    unsigned eax, ebx, ecx, edx;

  eax = 1; /* processor info and feature bits */
  native_cpuid(&eax, &ebx, &ecx, &edx);

  printf("stepping %d\n", eax & 0xF);
  printf("model %d\n", (eax >> 4) & 0xF);
  printf("family %d\n", (eax >> 8) & 0xF);
  printf("processor type %d\n", (eax >> 12) & 0x3);
  printf("extended model %d\n", (eax >> 16) & 0xF);
  printf("extended family %d\n", (eax >> 20) & 0xFF);

  /* EDIT */
  eax = 3; /* processor serial number */
  native_cpuid(&eax, &ebx, &ecx, &edx);

  /** see the CPUID Wikipedia article on which models return the serial 
      number in which registers. The example here is for 
      Pentium III */
  printf("serial number 0x%08x%08x\n", edx, ecx);
}

void _main() {
    char c = 0;

    spc(VGA_COLOR_BLACK, VGA_COLOR_WHITE);
    cls();
    strp("Welcome To Floofy OS!");
    
    do {
        if (inb(0x60) != c) {
            c = inb(0x60);
            if (c > 0) {
                strp(translate(c, false));
            }
        }
    } while (c != 1);
}