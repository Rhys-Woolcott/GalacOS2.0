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

enum scancodes {
	// IDK
	ESC                       = 0x76,
	SPACE                     = 0x76,

	// FUNCTION KEYS
	F1                        = 0x05,
	F2                        = 0x06,
	F3                        = 0x04,
	F4                        = 0x0C,
	F5                        = 0x03,
	F6                        = 0x0B,
	F7                        = 0x83,
	F8                        = 0x0A,
	F9                        = 0x01,
	F10                       = 0x09,
	F11                       = 0x78,
	F12                       = 0x07,

	// TOP ROW
	BACKTICK                  = 0x0E,
	NUM_0                     = 0x45,
	NUM_1                     = 0x16,
	NUM_2                     = 0x1E,
	NUM_3                     = 0x26,
	NUM_4                     = 0x25,
	NUM_5                     = 0x2E,
	NUM_6                     = 0x36,
	NUM_7                     = 0x3D,
	NUM_8                     = 0x3E,
	NUM_9                     = 0x46,

	// MATHEMATICS
	MINUS                     = 0x4E,
	EQUAL                     = 0x55,

	// GENERAL
	BACKSPACE                 = 0x66,
	TAB                       = 0x0D,
	CAPSLOCK                  = 0x58,
	ENTER                     = 0x5A,

	// SHIFT KEYS
	L_SHIFT                   = 0x12,
	R_SHIFT                   = 0x59,

	// CONTROL KEYS
	L_CTRL                    = 0x14,
	R_CTRL                    = 0xE014,

	// ALT KEYS
	L_ALT                     = 0x11,
	R_ALT                     = 0xE011,

	// FUNC KEYS
	INSERT                    = 0xE070,
	HOME                      = 0xE06C,
	DELETE                    = 0xE071,
	END                       = 0xE069,
	PG_UP                     = 0xE07D,
	PG_DOWN                   = 0xE07A,
	SCRL_LOCK                 = 0x7E,

	// ARROW KEYS
	ARR_UP                    = 0xE075,
	ARR_DOWN                  = 0xE072,
	ARR_LEFT                  = 0xE06B,
	ARR_RIGHT                 = 0xE074,

	// MAIN KEYS (LETTERS)
	LETTER_Q                  = 0x15,
	LETTER_W                  = 0x1D,
	LETTER_E                  = 0x24,
	LETTER_R                  = 0x2D,
	LETTER_T                  = 0x2C,
	LETTER_Y                  = 0x35,
	LETTER_U                  = 0x3C,
	LETTER_I                  = 0x43,
	LETTER_O                  = 0x44,
	LETTER_P                  = 0x4D,

	LETTER_A                  = 0x1C,
	LETTER_S                  = 0x1B,
	LETTER_D                  = 0x23,
	LETTER_F                  = 0x2B,
	LETTER_G                  = 0x34,
	LETTER_H                  = 0x33,
	LETTER_J                  = 0x3B,
	LETTER_K                  = 0x42,
	LETTER_L                  = 0x4B,

	LETTER_Z                  = 0x1A,
	LETTER_X                  = 0x22,
	LETTER_C                  = 0x21,
	LETTER_V                  = 0x2A,
	LETTER_B                  = 0x32,
	LETTER_N                  = 0x31,
	LETTER_M                  = 0x3A,

	// NUMPAD
	N_ENTER                   = 0xE05A,
};

void cls();                                        // print_clear
void charp(char character);                        // print_char
void strp(char* string);                           // print_str
void spc(uint8_t foreground, uint8_t background);  // print_set_color
char* itoa(int val, int base);                     // convert int to string