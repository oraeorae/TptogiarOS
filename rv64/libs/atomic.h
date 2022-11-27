#ifndef __LIBS_ATOMIC_H__
#define __LIBS_ATOMIC_H__

/* Atomic operations that C can't guarantee us. Useful for resource counting
 * etc.. */

static inline void set_bit(int nr, volatile void *addr)
    __attribute__((always_inline));
static inline void clear_bit(int nr, volatile void *addr)
    __attribute__((always_inline));
static inline void change_bit(int nr, volatile void *addr)
    __attribute__((always_inline));
static inline bool test_bit(int nr, volatile void *addr)
    __attribute__((always_inline));
static inline bool test_and_set_bit(int nr, volatile void *addr)
    __attribute__((always_inline));
static inline bool test_and_clear_bit(int nr, volatile void *addr)
    __attribute__((always_inline));

#define BITS_PER_LONG __riscv_xlen

#if (BITS_PER_LONG == 64)
#define __AMO(op) "amo" #op ".d"
#elif (BITS_PER_LONG == 32)
#define __AMO(op) "amo" #op ".w"
#else
#error "Unexpected BITS_PER_LONG"
#endif

#define BIT_MASK(nr) (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr) ((nr) / BITS_PER_LONG)

#define __test_and_op_bit(op, mod, nr, addr)                         \
    ({                                                               \
        unsigned long __res, __mask;                                 \
        __mask = BIT_MASK(nr);                                       \
        __asm__ __volatile__(__AMO(op) " %0, %2, %1"                 \
                             : "=r"(__res), "+A"(addr[BIT_WORD(nr)]) \
                             : "r"(mod(__mask)));                    \
        ((__res & __mask) != 0);                                     \
    })

#define __op_bit(op, mod, nr, addr)                 \
    __asm__ __volatile__(__AMO(op) " zero, %1, %0"  \
                         : "+A"(addr[BIT_WORD(nr)]) \
                         : "r"(mod(BIT_MASK(nr))))

/* Bitmask modifiers */
#define __NOP(x) (x)
#define __NOT(x) (~(x))


static inline void set_bit(int nr, volatile void *addr) {
    __op_bit(or, __NOP, nr, ((volatile unsigned long *)addr));
}


static inline void clear_bit(int nr, volatile void *addr) {
    __op_bit(and, __NOT, nr, ((volatile unsigned long *)addr));
}


static inline void change_bit(int nr, volatile void *addr) {
    __op_bit (xor, __NOP, nr, ((volatile unsigned long *)addr));
}


static inline bool test_bit(int nr, volatile void *addr) {
    return (((*(volatile unsigned long *)addr) >> nr) & 1);
}


static inline bool test_and_set_bit(int nr, volatile void *addr) {
    return __test_and_op_bit(or, __NOP, nr, ((volatile unsigned long *)addr));
}


static inline bool test_and_clear_bit(int nr, volatile void *addr) {
    return __test_and_op_bit(and, __NOT, nr, ((volatile unsigned long *)addr));
}

#endif /* !__LIBS_ATOMIC_H__ */
