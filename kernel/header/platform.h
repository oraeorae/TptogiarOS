#ifndef __PLATFORM_H__
#define __PLATFORM_H__



// CPU核心数
#define MAXNUM_CPU 8

// UART地址映射后的起始地址
#define UART0 0x10000000L
/*
 * MemoryMap
 * see https://github.com/qemu/qemu/blob/master/hw/riscv/virt.c, virt_memmap[]
 * 0x00001000 -- boot ROM, provided by qemu
 * 0x02000000 -- CLINT
 * 0x0C000000 -- PLIC
 * 0x10000000 -- UART0
 * 0x10001000 -- virtio disk
 * 0x80000000 -- boot ROM jumps here in machine mode, where we load our kernel
 */





#endif
