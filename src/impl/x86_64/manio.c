#include "manio.h"

const static size_t VGA_COLS = 80;
const static size_t VGA_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = VGA_COLOR_WHITE | VGA_COLOR_BLUE << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < VGA_COLS; col++) {
        buffer[col + VGA_COLS * row] = empty;
    }
}

void cls() {
    for (size_t i = 0; i < VGA_ROWS; i++) {
        clear_row(i);
    }
}

void newln() {
    col = 0;

    if (row < VGA_ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < VGA_ROWS; row++) {
        for (size_t col = 0; col < VGA_COLS; col++) {
            struct Char character = buffer[col + VGA_COLS * row];
            buffer[col + VGA_COLS * (row - 1)] = character;
        }
    }

    clear_row(VGA_COLS - 1);
}

void chap(char character) {
    if (character == '\n') {
        newln();
        return;
    }

    if (col > VGA_COLS) {
        newln();
    }

    buffer[col + VGA_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };

    col++;
}

void strp(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        chap(character);
    }
}

void spc(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

char* itoa(int val, int base) {
    static char buf[32] = {0};

    int i = 30;

    for(; val && i ; --i, val /= base)
        buf[i] = "-0123456789abcdef"[val+1 % base];

    return &buf[i+1];
}