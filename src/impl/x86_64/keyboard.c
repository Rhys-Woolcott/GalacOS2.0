#include "keyboard.h"
#include "manio.h"

#include "idt.h"
#include "display.h"
#include "hal.h"
#include "tasking.h"
#include "mutex.h"
#include "memory.h"

void keyboard_irq();
uint8_t lastkey = 0;
uint8_t *keycache = 0;
uint16_t key_loc = 0;
uint8_t __kbd_enabled = 0;

/*
 * Scan code   Key                         Scan code   Key                     Scan code   Key                     Scan code   Key
 * 0x01        escape pressed              0x02        1 pressed               0x03        2 pressed
 * 0x04        3 pressed                   0x05        4 pressed               0x06        5 pressed               0x07        6 pressed
 * 0x08        7 pressed                   0x09        8 pressed               0x0A        9 pressed               0x0B        0 (zero) pressed
 * 0x0C        - pressed                   0x0D        = pressed               0x0E        backspace pressed       0x0F        tab pressed
 * 0x10        Q pressed                   0x11        W pressed               0x12        E pressed               0x13        R pressed
 * 0x14        T pressed                   0x15        Y pressed               0x16        U pressed               0x17        I pressed
 * 0x18        O pressed                   0x19        P pressed               0x1A        [ pressed               0x1B        ] pressed
 * 0x1C        enter pressed               0x1D        left control pressed    0x1E        A pressed               0x1F        S pressed
 * 0x20        D pressed                   0x21        F pressed               0x22        G pressed               0x23        H pressed
 * 0x24        J pressed                   0x25        K pressed               0x26        L pressed               0x27        ; pressed
 * 0x28        ' (single quote) pressed    0x29        ` (back tick) pressed   0x2A        left shift pressed      0x2B        \ pressed
 * 0x2C        Z pressed                   0x2D        X pressed               0x2E        C pressed               0x2F        V pressed
 * 0x30        B pressed                   0x31        N pressed               0x32        M pressed               0x33        , pressed
 * 0x34        . pressed                   0x35        / pressed               0x36        right shift pressed     0x37        (keypad) * pressed
 * 0x38        left alt pressed            0x39        space pressed           0x3A        CapsLock pressed        0x3B        F1 pressed
 * 0x3C        F2 pressed                  0x3D        F3 pressed              0x3E        F4 pressed              0x3F        F5 pressed
 * 0x40        F6 pressed                  0x41        F7 pressed              0x42        F8 pressed              0x43        F9 pressed
 * 0x44        F10 pressed                 0x45        NumberLock pressed      0x46        ScrollLock pressed      0x47        (keypad) 7 pressed
 * 0x48        (keypad) 8 pressed          0x49        (keypad) 9 pressed      0x4A        (keypad) - pressed      0x4B        (keypad) 4 pressed
 * 0x4C        (keypad) 5 pressed          0x4D        (keypad) 6 pressed      0x4E        (keypad) + pressed      0x4F        (keypad) 1 pressed
 * 0x50        (keypad) 2 pressed          0x51        (keypad) 3 pressed      0x52        (keypad) 0 pressed      0x53        (keypad) . pressed
 * 0x57        F11 pressed                 0x58        F12 pressed
*/

enum KEYCODE {
	NULL_KEY = 0,
	Q_PRESSED = 0x10,
	Q_RELEASED = 0x90,
	W_PRESSED = 0x11,
	W_RELEASED = 0x91,
	E_PRESSED = 0x12,
	E_RELEASED = 0x92,
	R_PRESSED = 0x13,
	R_RELEASED = 0x93,
	T_PRESSED = 0x14,
	T_RELEASED = 0x94,
	Z_PRESSED = 0x15,
	Z_RELEASED = 0x95,
	U_PRESSED = 0x16,
	U_RELEASED = 0x96,
	I_PRESSED = 0x17,
	I_RELEASED = 0x97,
	O_PRESSED = 0x18,
	O_RELEASED = 0x98,
	P_PRESSED = 0x19,
	P_RELEASED = 0x99,
	A_PRESSED = 0x1E,
	A_RELEASED = 0x9E,
	S_PRESSED = 0x1F,
	S_RELEASED = 0x9F,
	D_PRESSED = 0x20,
	D_RELEASED = 0xA0,
	F_PRESSED = 0x21,
	F_RELEASED = 0xA1,
	G_PRESSED = 0x22,
	G_RELEASED = 0xA2,
	H_PRESSED = 0x23,
	H_RELEASED = 0xA3,
	J_PRESSED = 0x24,
	J_RELEASED = 0xA4,
	K_PRESSED = 0x25,
	K_RELEASED = 0xA5,
	L_PRESSED = 0x26,
	L_RELEASED = 0xA6,
	Y_PRESSED = 0x2C,
	Y_RELEASED = 0xAC,
	X_PRESSED = 0x2D,
	X_RELEASED = 0xAD,
	C_PRESSED = 0x2E,
	C_RELEASED = 0xAE,
	V_PRESSED = 0x2F,
	V_RELEASED = 0xAF,
	B_PRESSED = 0x30,
	B_RELEASED = 0xB0,
	N_PRESSED = 0x31,
	N_RELEASED = 0xB1,
	M_PRESSED = 0x32,
	M_RELEASED = 0xB2,

	ZERO_PRESSED = 0x29,
	ONE_PRESSED = 0x2,
	NINE_PRESSED = 0xA,

	POINT_PRESSED = 0x34,
	POINT_RELEASED = 0xB4,

	SLASH_RELEASED = 0xB5,

	BACKSPACE_PRESSED = 0xE,
	BACKSPACE_RELEASED = 0x8E,
	SPACE_PRESSED = 0x39,
	SPACE_RELEASED = 0xB9,
	ENTER_PRESSED = 0x1C,
	ENTER_RELEASED = 0x9C,

};

#define KBD_SEND(byt) outb(0x64, byt);

void keyboard_init()
{
	printf("PS/2 Keyboard init sequence activated.\n");
	keycache = (uint8_t*)malloc(256);
	memset(keycache, 0, 256);
	/* Install IRQ */
	set_int(33, (uint32_t)keyboard_irq);
	__kbd_enabled = 1;
	_kill(); /* end me */
}

uint8_t keyboard_enabled()
{
	return __kbd_enabled;
}

void keyboard_read_key()
{
	lastkey = 0;
	if(inb(0x64) & 1)
		lastkey = inb(0x60);
}

DEFINE_MUTEX(m_getkey);
static char c = 0;
char keyboard_get_key()
{
	mutex_lock(&m_getkey);
	c = 0;
	if(key_loc == 0) goto out;
	c = *keycache;
	key_loc --;
	for(int i = 0; i < 256; i++)
	{
		keycache[i] = keycache[i+1];
	}
out:
	mutex_unlock(&m_getkey);
	return c;
}
static char* _qwertzuiop = "qwertzuiop"; // 0x10-0x1c
static char* _asdfghjkl = "asdfghjkl";
static char* _yxcvbnm = "yxcvbnm";
static char* _num = "123456789";
uint8_t keyboard_to_ascii(uint8_t key)
{
	//kprintf("key=0x%x\n", key);
	if(key == 0x1C) return '\n';
	if(key == 0x39) return ' ';
	if(key == 0xE) return '\r';
	if(key == POINT_RELEASED) return '.';
	if(key == SLASH_RELEASED) return '/';
	if(key == ZERO_PRESSED) return '0';
	if(key >= ONE_PRESSED && key <= NINE_PRESSED)
		return _num[key - ONE_PRESSED];
	if(key >= 0x10 && key <= 0x1C)
	{
		return _qwertzuiop[key - 0x10];
	} else if(key >= 0x1E && key <= 0x26)
	{
		return _asdfghjkl[key - 0x1E];
	} else if(key >= 0x2C && key <= 0x32)
	{
		return _yxcvbnm[key - 0x2C];
	}
	return 0;
}

void keyboard_irq()
{
	IRQ_START;
	keycache[key_loc++] = keyboard_to_ascii(inportb(0x60));
	send_eoi(1);
	IRQ_END;
}