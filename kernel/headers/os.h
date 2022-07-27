#ifndef __OS_H__
#define __OS_H__


#include "types.h"
#include "platform.h"
#include "riscv.h"

#include <stddef.h>
#include <stdarg.h>

/* uart */
extern int uart_putc(char ch);
extern void uart_puts(char *s);
extern int uartGets(void);

/* printf */
extern int printf(const char *s, ...);

extern void panic(char *s);

/* memory management */
extern void *page_alloc(int npages);

extern void page_free(void *p);

extern int taskCreate(void (*taskAddress)(void));

extern void taskDelayCount(volatile int count);

extern void taskYield();

extern int plicClaim(void);
extern void plicComplete(int interruptId);

// 用以表征CPU内的全部寄存器，以便于上下文切换
struct Context {

    reg_t ra;
    reg_t sp;
    reg_t gp;
    reg_t tp;

    reg_t t0;
    reg_t t1;
    reg_t t2;


    reg_t s0;
    reg_t s1;


    reg_t a0;
    reg_t a1;
    reg_t a2;
    reg_t a3;
    reg_t a4;
    reg_t a5;
    reg_t a6;
    reg_t a7;


    reg_t s2;
    reg_t s3;
    reg_t s4;
    reg_t s5;
    reg_t s6;
    reg_t s7;
    reg_t s8;
    reg_t s9;
    reg_t s10;
    reg_t s11;

    reg_t t3;
    reg_t t4;
    reg_t t5;
    reg_t t6;
};




#endif /* __OS_H__ */
