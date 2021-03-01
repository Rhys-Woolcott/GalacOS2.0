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

enum keyboard {
	// Numbers
	kb_1 = 0x02,
	kb_2 = 0x03,
	kb_3 = 0x04,
	kb_4 = 0x05,
	kb_5 = 0x06,
	kb_6 = 0x07,
	kb_7 = 0x08,
	kb_8 = 0x09,
	kb_9 = 0x0a,
	kb_0 = 0x0b,
	// Letters
	kb_a = 0x11,
	kb_b = 0x11,
	kb_c = 0x11,
	kb_d = 0x11,
	kb_e = 0x11,
	kb_f = 0x11,
	kb_g = 0x11,
	kb_h = 0x11,
	kb_i = 0x11,
	kb_j = 0x11,
	kb_k = 0x11,
	kb_l = 0x11,
	kb_m = 0x11,
	kb_n = 0x11,
	kb_o = 0x11,
	kb_p = 0x11,
	kb_q = 0x11,
	kb_r = 0x11,
	kb_s = 0x11,
	kb_t = 0x11,
	kb_u = 0x11,
	kb_v = 0x11,
	kb_w = 0x11,
	kb_x = 0x11,
	kb_y = 0x11,
	kb_z = 0x11,
};

void cls();                                        // print_clear
void charp(char character);                        // print_char
void strp(char* string);                           // print_str
void spc(uint8_t foreground, uint8_t background);  // print_set_color
char* int_tostring(int num);                        // convert int to string