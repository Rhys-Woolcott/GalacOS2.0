#include <manio.h>
#include <display.h>
#include <math.h>
#include <keyboard.h>
#include <rand.h>
#include <stdbool.h>

#define KEYBD_DATA 0x60
#define KEYBD_CMD 0x64
#define MASTER_CMD 0x20
#define MASTER_DATA 0x21
#define SLAVE_CMD 0xA0
#define SLAVE_DATA 0xA1
#define PIC_EOI 0x20


void wait() {
    for (uint8_t i = 0; i < 255; i++);
}

void _main() {
    char c = 0;

    spc(VGA_COLOR_BLACK, VGA_COLOR_WHITE);
    cls();
    strp("Welcome To Floofy OS!\n");
}