#pragma once

#include <stdint.h>
#include <stddef.h>

enum {
    VGA_COLOR_BLACK        = 0,
	VGA_COLOR_BLUE         = 1,
	VGA_COLOR_GREEN        = 2,
	VGA_COLOR_CYAN         = 3,
	VGA_COLOR_RED          = 4,
	VGA_COLOR_MAGENTA      = 5,
	VGA_COLOR_BROWN        = 6,
	VGA_COLOR_LIGHT_GRAY   = 7,
	VGA_COLOR_DARK_GRAY    = 8,
	VGA_COLOR_LIGHT_BLUE   = 9,
	VGA_COLOR_LIGHT_GREEN  = 10,
	VGA_COLOR_LIGHT_CYAN   = 11,
	VGA_COLOR_LIGHT_RED    = 12,
	VGA_COLOR_PINK         = 13,
	VGA_COLOR_YELLOW       = 14,
	VGA_COLOR_WHITE        = 15,
};

void cls();                                        // print_clear
void chap(char character);                        // print_char
void strp(char* string);                           // print_str
void spc(uint8_t foreground, uint8_t background);  // print_set_color
char* itoa(int val, int base);                     // convert int to string
int *separateDigits(int n);
void printf(const char* fmt, ...);
void handleError(char* err);
char* backspace();
void outb(unsigned short port, unsigned char val);
unsigned char inb(unsigned short int port);