#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include "display.h"
#include "string.h"
#include "mutex.h"
/* variables */
static DISPLAY *dispis[DISPLAY_MAX_DISPIS];
static uint8_t _last_register = 1;
static uint8_t current = 0;


static DISPLAY* cd = 0;

void __kprintf_va_list(char* str, va_list ap);

MODULE("DISP");

DEFINE_MUTEX(m_kprintf);

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void __itoa(unsigned i,unsigned base,char* buf) {
	int pos = 0;
	int opos = 0;
	int top = 0;

	if (i == 0 || base > 16) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	while (i != 0) {
		tbuf[pos] = bchars[i % base];
		pos++;
		i /= base;
	}
	top=pos--;
	for (opos=0; opos<top; pos--,opos++)
		buf[opos] = tbuf[pos];
	buf[opos] = 0;
}

void __itoa_s(int i,unsigned base,char* buf) {
   if (base > 16) return;
   if (i < 0) {
      *buf++ = '-';
      i *= -1;
   }
   __itoa(i,base,buf);
}

DEFINE_MUTEX(m_mprintf);
void __mprintf(char *m, ...)
{
	mutex_lock(&m_mprintf);
	va_list ap;
	va_start(ap, m);
	kprintf("[%s]: ", m);
	char *fmt = va_arg(ap, char*);
	__kprintf_va_list(fmt, ap);
	mutex_unlock(&m_mprintf);
}

/* abstraction methods */
int kprintf (const char* str, ...) {
	if(!str)
		return 0;
	va_list ap;
	va_start(ap, str);
	__kprintf_va_list((char *)str, ap);
	return 1;
}


void __kprintf_va_list(char* str, va_list ap)
{
	mutex_lock(&m_kprintf);
	char* s = 0;
	//cd->putc('c');
	for(size_t i = 0; i < strlen((string)str); i++)
	{
		if(str[i] == '%')
		{
			switch(str[i+1])
			{
				/** string **/
				case 's':
					s = va_arg(ap, char*);
					cd->puts(s);
					i++;
					continue;
				/** decimal **/
				case 'd': {
					int c = va_arg(ap, int);
					char str[32] = {0};
					__itoa_s(c, 10, str);
					cd->puts(str);
					i++;
					continue;
				}
				case 'x': {
					int c = va_arg(ap, int);
					char str[32]= {0};
					__itoa(c, 16, str);
					cd->puts(str);
					i++;
					continue;
				}
				/** character **/
				case 'c': {
					// char gets promoted to int for va_arg!
					// clean it.
					char c = (char)(va_arg(ap, int) & ~0xFFFFFF00);
					cd->putc(c);
					i++;
					continue;
				}
				default:
					break;
			}
		} else {
			cd->putc(str[i]);
		}
	}
	mutex_unlock(&m_kprintf);
	va_end(ap);
}

/* interface methods */

/* Registers the DISPLAY and returns its ID */
uint8_t display_register(DISPLAY *d)
{
	dispis[_last_register] = d;
	dispis[_last_register]->onregister();
	return _last_register++;
}
/* Sets it as current display, calling d->onset(id) to let the display
   set itself up */
uint8_t display_setcurrent(uint8_t id)
{
	if(current == id) return 0;
	current = id;
	dispis[current]->onset(id);
	cd = dispis[current];
	return 1;
}
/* returns current DISPLAY */
DISPLAY* display_getcurrent()
{
	return cd;
}

