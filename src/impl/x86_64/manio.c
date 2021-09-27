#include "manio.h"

const static size_t VGA_COLS = 80;
const static size_t VGA_ROWS = 25;

struct Char
{
    uint8_t character;
    uint8_t color;
};

struct Char volatile *buffer = (struct Char *) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = VGA_COLOR_WHITE | VGA_COLOR_BLUE << 4;

void clear_row(size_t row)
{
    struct Char empty = (struct Char){
        character : ' ',
        color : color,
    };

    for (size_t col = 0; col < VGA_COLS; col++)
    {
        buffer[col + VGA_COLS * row] = empty;
    }
}

void clear_col(size_t col)
{
    struct Char empty = (struct Char){
        character : ' ',
        color : color,
    };

    for (size_t col = 0; col < VGA_ROWS; col++)
    {
        buffer[col + VGA_ROWS * col] = empty;
    }
}

void cls()
{
    for (size_t i = 0; i < VGA_ROWS; i++)
    {
        clear_row(i);
        col = 0;
        row = 0;
    }
}

void newln()
{
    col = 0;

    if (row < VGA_ROWS - 1)
    {
        row++;
        return;
    }

    for (size_t row = 1; row < VGA_ROWS; row++)
    {
        for (size_t col = 0; col < VGA_COLS; col++)
        {
            struct Char character = buffer[col + VGA_COLS * row];
            buffer[col + VGA_COLS * (row - 1)] = character;
        }
    }

    clear_row(VGA_COLS - 1);
}

void handleError(char* err) {
    cls();
    spc(VGA_COLOR_BLACK, VGA_COLOR_RED);
    return strp(err);
}

char* backspace() {
    if (col > 0) {
        col--;
        strp(" ");
        col--;
        return "";
    }
}

void chap(char character)
{
    if (character == '\n')
    {
        newln();
        return;
    }
    if (character == "\r") {
        backspace();
        return;
    }

    if (col >= VGA_COLS)
    {
        newln();
    }

    buffer[col + VGA_COLS * row] = (struct Char){
        character : (uint8_t)character,
        color : color,
    };

    col++;
}

void strp(char *str)
{
    for (size_t i = 0; 1; i++)
    {
        char character = (uint8_t)str[i];

        if (character == '\0')
        {
            return;
        }

        chap(character);
    }
}

void spc(uint8_t foreground, uint8_t background)
{
    color = foreground + (background << 4);
}

char *itoa(int val, int base)
{
    static char buf[32] = {0};

    int i = 30;

    for (; val && i; --i, val /= base)
        buf[i] = "-0123456789abcdef"[val + 1 % base];

    return &buf[i + 1];
}

int *separateDigits(int n);

typedef __builtin_va_list va_list;
#define va_start(ap, X) __builtin_va_start(ap, X)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_end(ap) __builtin_va_end(ap)

void _putc(unsigned char c) { chap((char)c); }

void printf(const char* fmt, ...) {
    const char digits[] = "0123456789abcdef";
    va_list ap;
    char buf[10];
    char* s;
    unsigned char u;
    int c, i, pad;

    va_start(ap, fmt);
    while ((c = *fmt++) != 0) {
        if (c == '%') {
            c = *fmt++;
            if (c == 'l')
                c = *fmt++;
            switch (c) {
            case 'c':
                _putc(va_arg(ap, int));
                continue;
            case 's':
                s = va_arg(ap, char*);
                if (s == (void*)0)
                    s = (char*)"<NULL>";
                for (; *s; s++)
                    _putc((int)*s);
                continue;
            case '%':
                _putc('%');
                continue;
            case 'd':
            case 'i':
                c = 'u';
            case 'u':
            case 'x':
            case 'X':
                u = va_arg(ap, unsigned);
                s = buf;
                if (c == 'u') {
                    do
                        *s++ = digits[u % 10U];
                    while (u /= 10U);
                } else {
                    pad = 0;
                    for (i = 0; i < 8; i++) {
                        if (pad)
                            *s++ = '0';
                        else {
                            *s++ = digits[u % 16U];
                            if (!(u /= 16U))
                                pad = 1;
                        }
                    }
                }
                while (--s >= buf)
                    _putc((int)*s);
                continue;
            }
        }
        _putc((int)c);
    }
    va_end(ap);
}

static __inline unsigned char inbp(unsigned short int port) {
	unsigned char _v;
    
    // What the fuck, How does this work?
	__asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (port));
	return _v;
}

unsigned char inb(unsigned short int port) {
    return inb(port);
}

void outb(unsigned short port, unsigned char val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) );
}

void wait_for_io(uint32_t timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}
void sleep(uint32_t s) {
    wait_for_io(s);
}