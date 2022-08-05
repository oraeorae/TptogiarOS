//
// Created by root on 8/5/22.
//
#include <assert.h>
#include <defs.h>
#include <stdio.h>


void printKernelInfo(void) {
    extern char etext[], edata[], end[], kern_init[];
    cprintf("Special kernel symbols:\n");
    cprintf("  entry  0x%016x (virtual)\n", kern_init);
    cprintf("  etext  0x%016x (virtual)\n", etext);
    cprintf("  edata  0x%016x (virtual)\n", edata);
    cprintf("  end    0x%016x (virtual)\n", end);
    cprintf("Kernel executable memory footprint: %dKB\n",(end - kern_init + 1023) / 1024);
}


void printDebugInfo(uintptr_t eip) { panic("Not Implemented!"); }


void printStackFrame(void) {

    panic("Not Implemented!");
}
