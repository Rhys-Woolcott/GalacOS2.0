#include "display.h"
#include "mutex.h"
#include "pit.h"
#include "tasking.h"

#include <stdint.h>

void mutex_lock(mutex* m)
{
	/* if the lock is locked, wait and set its locked state */
	while(m->locked) schedule_noirq();
	m->locked = 1;
}

void mutex_unlock(mutex* m)
{
	/* this code can only be accessed by the holding thread, so unlock it */
	m->locked = 0;
	schedule_noirq();
}