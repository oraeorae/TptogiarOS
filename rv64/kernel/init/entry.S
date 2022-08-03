#include <mmu.h>
#include <memlayout.h>

    .section .text,"ax",%progbits
    .globl kern_entry



# 链接后的其实地址存放的指令
kern_entry:
    la sp, bootstacktop
    # 调用函数
    tail kern_init

.section .data
    # 按4KB对其
    .align PGSHIFT
    .global bootstack

# 定义内核栈空间
bootstack:
    .space KSTACKSIZE
    .global bootstacktop
bootstacktop: