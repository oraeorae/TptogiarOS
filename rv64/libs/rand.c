#include <riscv.h>
#include <stdlib.h>

static unsigned long long next = 1;


int
rand(void) {
    next = (next * 0x5DEECE66DLL + 0xBLL) & ((1LL << 48) - 1);
    unsigned long long result = (next >> 12);
    return (int)do_div(result, RAND_MAX + 1);
}


void
srand(unsigned int seed) {
    next = seed;
}

