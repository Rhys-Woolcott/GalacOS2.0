#include "mouse.h"
#include "manio.h"

void enable_cursor(uint8_t start, uint8_t end) {
    sleep(0xffffff * 0x00000d);
    outb(0x3d4, 0x0a);
    outb(0x3d5, (inb(0x3d5) & 0xc0) | start);

    outb(0x3d4, 0x0b);
    outb(0x3d5, (inb(0x3d5) & 0xe4) | end);
    printf("\nMouse Enabled");
}