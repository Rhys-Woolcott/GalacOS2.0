// #include <interrupts.h>

// static __inline unsigned char inb(unsigned short int port) {
// 	unsigned char _v;

// 	__asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (port));
// 	return _v;
// }