#ifndef __PLATFORM_H__
#define __PLATFORM_H__



// CPU核心数
#define MAXNUM_CPU 8



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
// UART地址映射后的起始地址
#define UART0 0x10000000L





// UART的中断编号为10
/*
 * UART0 interrupt source
 * see https://github.com/qemu/qemu/blob/master/include/hw/riscv/virt.h
 * enum {
 *     UART0_IRQ = 10,
 *     ......
 * };
 */
#define UART0_IRQ 10





/*
 * This machine puts platform-level interrupt controller (PLIC) here.
 * Here only list PLIC registers in Machine mode.
 * see https://github.com/qemu/qemu/blob/master/include/hw/riscv/virt.h
 * #define VIRT_PLIC_HART_CONFIG "MS"
 * #define VIRT_PLIC_NUM_SOURCES 127
 * #define VIRT_PLIC_NUM_PRIORITIES 7
 * #define VIRT_PLIC_PRIORITY_BASE 0x04
 * #define VIRT_PLIC_PENDING_BASE 0x1000
 * #define VIRT_PLIC_ENABLE_BASE 0x2000
 * #define VIRT_PLIC_ENABLE_STRIDE 0x80
 * #define VIRT_PLIC_CONTEXT_BASE 0x200000
 * #define VIRT_PLIC_CONTEXT_STRIDE 0x1000
 * #define VIRT_PLIC_SIZE(__num_context) \
 *     (VIRT_PLIC_CONTEXT_BASE + (__num_context) * VIRT_PLIC_CONTEXT_STRIDE)
 */
// PLIC内存映射之后的基地址
#define PLIC_BASE 0x0c000000L
// 设置某路中断源的
#define PLIC_PRIORITY(interputId) (PLIC_BASE + (interputId) * 4)
// 获取某个中断源是否发生了中断
#define PLIC_PENDING(interputId) (PLIC_BASE + 0x1000 + ((interputId) / 32) * 4)
// 在某个hart上设置打开或关闭某路中断源
#define PLIC_MENABLE(hart) (PLIC_BASE + 0x2000 + (hart) * 0x80)
// 在某个hart上设置某路中断源的优先级阀值
#define PLIC_MTHRESHOLD(hart) (PLIC_BASE + 0x200000 + (hart) * 0x1000)
// 收到外部中断后，通过在PLIC中读取Claim寄存器来获取具体是那个设备产生的中断
#define PLIC_MCLAIM(hart) (PLIC_BASE + 0x200004 + (hart) * 0x1000)
// 当CPU中断处理完毕后，通过向Complete寄存器写入数据来告知PLIC下一个中断信号可以进来了
#define PLIC_MCOMPLETE(hart) (PLIC_BASE + 0x200004 + (hart) * 0x1000)


#endif
