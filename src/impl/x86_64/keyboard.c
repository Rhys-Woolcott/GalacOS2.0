#include "keyboard.h"
#include "manio.h"

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

char* ASCIITable[58] = {
	0 ,   0 , "1", "2", // 0x00, ESC,
	"3", "4", "5", "6",
	"7", "8", "9", "0",
	"-", "=",  "\r" ,  0,  // backspace, tab
	"q", "w", "e", "r",
	"t", "y", "u", "i",
	"o", "p", "[", "]",
	"\n",  0, "a", "s", // Enter, left control
	"d", "f", "g", "h",
	"j", "k", "l", ";",
	"'", "`",  0 , "\\", // Left Shift
	"z", "x", "c", "v",
	"b", "n", "m", ",",
	".", "/",  0 , "*", // Right Shift
	0, " " // Left Alt
};

char* ASCIITableUppercase[58] = {
	0 ,   0 , "!", "\"", // 0x00, ESC,
	"£", "$", "%", "^",
	"&", "*", "(", ")",
	"_", "+", "bs" , 0,  // backspace, tab
	"Q", "W", "E", "R",
	"T", "Y", "U", "I",
	"O", "P", "{", "}",
	"\n",  0, "A", "S", // Enter, left control
	"D", "F", "G", "H",
	"J", "K", "L", ";",
	"'", "`",  0 , "\\", // Left Shift
	"Z", "X", "C", "V",
	"B", "N", "M", "<",
	">", "?",  0 , "*", // Right Shift
	0, " " // Left Alt
};

char* translate(uint8_t scancode, bool uppercase) {
	if (scancode > 58) return 0;
	switch (scancode) {
		case 0x0000000e: return "Backspace";
		case 0x0000003a: return "Caps lock";
		case 0x0000001d: return "Control";
		case 0x00000038: return "Alt";
		default: 
			printf("%x", scancode);
			// if (uppercase) return ASCIITableUppercase[scancode];
			return ASCIITable[scancode];
	}
}