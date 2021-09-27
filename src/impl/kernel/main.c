#include <manio.h>
#include <math.h>
#include <keyboard.h>
#include <mouse.h>
#include <stdbool.h>

#define INT_DISABLE 0
#define INT_ENABLE  0x200
#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

void init_pics(int pic1, int pic2)
{
   /* send ICW1 */
   outb(PIC1, ICW1);
   outb(PIC2, ICW1);

   /* send ICW2 */
   outb(PIC1 + 1, pic1);   
   outb(PIC2 + 1, pic2);   

   /* send ICW3 */
   outb(PIC1 + 1, 4);   
   outb(PIC2 + 1, 2);

   /* send ICW4 */
   outb(PIC1 + 1, ICW4);
   outb(PIC2 + 1, ICW4);

   /* disable all IRQs */
   outb(PIC1 + 1, 0xFF);
}


void _main() {
    char c = 0;

    spc(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    cls();
    printf("Loading...");

    sleep(0xffffff * 0x00005f);
    spc(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
    cls();
    printf("Welcome to GalacOS!");

    enable_cursor(0x00, 0x0f);
    sleep(0x00000f);
}