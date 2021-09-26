#include <manio.h>
#include <math.h>
#include <keyboard.h>
#include <mouse.h>
#include <stdbool.h>

void _main() {
    char c = 0;

    spc(VGA_COLOR_BLACK, VGA_COLOR_WHITE);
    cls();
    enable_cursor(0x00, 0x0f);
}