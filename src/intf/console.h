#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include <stdint.h>

typedef struct {
	uint32_t bgcol;
	uint32_t fgcol;
	uint32_t cx;
	uint32_t cy;
} CONSOLE;

#endif