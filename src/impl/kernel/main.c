#include <manio.h>
#include <display.h>

void _main() {
    cls();
    spc(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    strp("Welcome To GalacOS\nCopyright Rhys Woolcott 2021\n\nroot:/ $ _");
}