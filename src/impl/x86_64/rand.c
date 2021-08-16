#include "rand.h"

static unsigned long int next = 1;
 
// RAND_MAX assumed to be 32767
int rand() {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}
 
void srand(unsigned int seed) {
    next = seed;
}