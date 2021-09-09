#ifndef __DISPLAY_H_
#define __DISPLAY_H_
#include "string.h"
#include "console.h"
#define DISPLAY_MAX_DISPIS 8

typedef struct {
	/* basic props */
	uint32_t width;
	uint32_t height;
	CONSOLE con;
	/* events */
	void (*onregister)();
	void (*onset)(uint8_t id);
	/* libc crap */
	void (*puts)(string);
	void (*putc)(char);
	void (*clear)();
} DISPLAY;
#define panic(...) {set_task(0); kprintf("***KERNEL PANIC*** in %s at line %d in function: %s\n", __FILE__, __LINE__, __func__); kprintf(__VA_ARGS__); for(;;);}
//#define mprint(...) {kprintf("[%s]: ", __MODULE_NAME); kprintf(__VA_ARGS__);}
#if 1
	#define MODULE(name) static char* __MODULE_NAME = name;
	#define mprint(...) __mprintf(__MODULE_NAME, __VA_ARGS__);
#else
	#define MODULE(name)
	#define mprint(...) {;}
#endif
#define kerror(...) {kprintf("***KERNEL OOPS***: "); kprintf(__VA_ARGS__);}
#define pidprint(...) kprintf(__VA_ARGS__);
#define BUG(...) {set_task(0); kprintf("\n\n*** KERNEL BUG***: "); kprintf(__VA_ARGS__); while(1);}
extern uint8_t display_register(DISPLAY *d);
extern uint8_t display_setcurrent(uint8_t id);
extern DISPLAY* display_getcurrent();
extern void __mprintf(char *m, ...);
extern int kprintf (const char* str, ...);

#endif