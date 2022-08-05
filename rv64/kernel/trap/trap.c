//
// Created by root on 8/5/22.
//


#include <assert.h>
#include <timer.h>
#include <console.h>
#include <defs.h>
#include <kernelDebug.h>
#include <memlayout.h>
#include <mmu.h>
#include <riscv.h>
#include <stdio.h>
#include <trap.h>

#define TICK_NUM 100

static void printTicks() {
    cprintf("%d ticks\n", TICK_NUM);
#ifdef DEBUG_GRADE
    cprintf("End of Test.\n");
    panic("EOT: kernel seems ok.");
#endif
}


void trapInit(void) {
    extern void __alltraps(void);
    write_csr(sscratch, 0);
    // 设置trap处理程序入口
    write_csr(stvec, &__alltraps);
}


bool testTrap(struct TrapFrame *tf) {
    return (tf->status & SSTATUS_SPP) != 0;
}

void print_TrapFrame(struct TrapFrame *tf) {
    cprintf("TrapFrame at %p\n", tf);
    print_regs(&tf->context);
    cprintf("  status   0x%08x\n", tf->status);
    cprintf("  epc      0x%08x\n", tf->epc);
    cprintf("  badvaddr 0x%08x\n", tf->badvaddr);
    cprintf("  cause    0x%08x\n", tf->cause);
}

void print_regs(struct Context *context) {
    cprintf("  zero     0x%08x\n", context->zero);
    cprintf("  ra       0x%08x\n", context->ra);
    cprintf("  sp       0x%08x\n", context->sp);
    cprintf("  gp       0x%08x\n", context->gp);
    cprintf("  tp       0x%08x\n", context->tp);
    cprintf("  t0       0x%08x\n", context->t0);
    cprintf("  t1       0x%08x\n", context->t1);
    cprintf("  t2       0x%08x\n", context->t2);
    cprintf("  s0       0x%08x\n", context->s0);
    cprintf("  s1       0x%08x\n", context->s1);
    cprintf("  a0       0x%08x\n", context->a0);
    cprintf("  a1       0x%08x\n", context->a1);
    cprintf("  a2       0x%08x\n", context->a2);
    cprintf("  a3       0x%08x\n", context->a3);
    cprintf("  a4       0x%08x\n", context->a4);
    cprintf("  a5       0x%08x\n", context->a5);
    cprintf("  a6       0x%08x\n", context->a6);
    cprintf("  a7       0x%08x\n", context->a7);
    cprintf("  s2       0x%08x\n", context->s2);
    cprintf("  s3       0x%08x\n", context->s3);
    cprintf("  s4       0x%08x\n", context->s4);
    cprintf("  s5       0x%08x\n", context->s5);
    cprintf("  s6       0x%08x\n", context->s6);
    cprintf("  s7       0x%08x\n", context->s7);
    cprintf("  s8       0x%08x\n", context->s8);
    cprintf("  s9       0x%08x\n", context->s9);
    cprintf("  s10      0x%08x\n", context->s10);
    cprintf("  s11      0x%08x\n", context->s11);
    cprintf("  t3       0x%08x\n", context->t3);
    cprintf("  t4       0x%08x\n", context->t4);
    cprintf("  t5       0x%08x\n", context->t5);
    cprintf("  t6       0x%08x\n", context->t6);
}

void interrupt_handler(struct TrapFrame *tf) {
    intptr_t cause = (tf->cause << 1) >> 1;
    switch (cause) {
        case InterruptNum_U_SOFT:
            cprintf("User software interrupt\n");
            break;
        case InterruptNum_S_SOFT:
            cprintf("Supervisor software interrupt\n");
            break;
        case InterruptNum_H_SOFT:
            cprintf("Hypervisor software interrupt\n");
            break;
        case InterruptNum_M_SOFT:
            cprintf("Machine software interrupt\n");
            break;
        case InterruptNum_U_TIMER:
            cprintf("User software interrupt\n");
            break;
        case InterruptNum_S_TIMER:
            timerHandler();
            if (++ticks % TICK_NUM == 0) {
                printTicks();
            }
            break;
        case InterruptNum_H_TIMER:
            cprintf("Hypervisor timer interrupt\n");
            break;
        case InterruptNum_M_TIMER:
            cprintf("Machine timer interrupt\n");
            break;
        case InterruptNum_U_EXT:
            cprintf("User software interrupt\n");
            break;
        case InterruptNum_S_EXT:
            cprintf("Supervisor external interrupt\n");
            break;
        case InterruptNum_H_EXT:
            cprintf("Hypervisor software interrupt\n");
            break;
        case InterruptNum_M_EXT:
            cprintf("Machine software interrupt\n");
            break;
        default:
            print_TrapFrame(tf);
            break;
    }
}

void exception_handler(struct TrapFrame *tf) {
    switch (tf->cause) {
        case CAUSE_MISALIGNED_FETCH:
            break;
        case CAUSE_FAULT_FETCH:
            break;
        case CAUSE_ILLEGAL_INSTRUCTION:
            break;
        case CAUSE_BREAKPOINT:
            cprintf("ebreak caught at 0x%016llx\n", tf->epc);
            tf->epc += 2;
            break;
        case CAUSE_MISALIGNED_LOAD:
            break;
        case CAUSE_FAULT_LOAD:
            break;
        case CAUSE_MISALIGNED_STORE:
            break;
        case CAUSE_FAULT_STORE:
            break;
        case CAUSE_USER_ECALL:
            break;
        case CAUSE_SUPERVISOR_ECALL:
            break;
        case CAUSE_HYPERVISOR_ECALL:
            break;
        case CAUSE_MACHINE_ECALL:
            break;
        default:
            print_TrapFrame(tf);
            break;
    }
}


static inline void trap_dispatch(struct TrapFrame *tf) {
    if ((intptr_t)tf->cause < 0) {
        interrupt_handler(tf);
    } else {
        exception_handler(tf);
    }
}


void trap(struct TrapFrame *tf) { trap_dispatch(tf); }
