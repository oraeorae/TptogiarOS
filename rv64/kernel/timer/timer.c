//
// Created by root on 8/3/22.
//
#include "timer.h"
#include <defs.h>
#include <sbi.h>
#include <stdio.h>
#include <riscv.h>

volatile size_t ticks;

static inline uint64_t get_cycles(void) {
#if __riscv_xlen == 64
    uint64_t n;
    __asm__ __volatile__("rdtime %0" : "=r"(n));
    return n;
#else
    uint32_t lo, hi, tmp;
    __asm__ __volatile__(
            "1:\n"
            "rdtimeh %0\n"
            "rdtime %1\n"
            "rdtimeh %2\n"
            "bne %0, %2, 1b"
            : "=&r"(hi), "=&r"(lo), "=&r"(tmp));
    return ((uint64_t)hi << 32) | lo;
#endif
}


// Hardcode timebase
static uint64_t timeDelay = 100000;

// 打开时间中断  100 times per second
void timerInit(void) {
    // 打开时间中断
    set_csr(sie, MIP_STIP);
    // divided by 500 when using Spike(2MHz)
    // divided by 100 when using QEMU(10MHz)
    // timebase = sbi_timebase() / 500;
    sbi_set_timer(get_cycles() + timeDelay);
    ticks = 0;
}

void timerHandler(void) {
    sbi_set_timer(get_cycles() + timeDelay);
}
