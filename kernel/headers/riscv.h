//
// Created by root on 2022.07.23.
//

#ifndef TPTOGIAROS_RISCV_H
#define TPTOGIAROS_RISCV_H

#include "types.h"

#define MSTATUS_MPP (3<<11)
#define MSTATUS_SPP (1<<8)

#define MSTATUS_MPIE (1<<7)
#define MSTATUS_SPIE (1<<5)
#define MSTATUS_UPIE (1<<4)

#define MSTATUS_MIE (1<<3)
#define MSTATUS_SIE (1<<1)
#define MSTATUS_UIE (1<<0)


#define MIE_MEIE (1<<11)
#define MIE_MTIE (1<<7)
#define MIE_MSIE (1<<3)




// tp,即x4，用于存放栈指针
static inline reg_t read_tp() {
    reg_t x;
    asm volatile("mv %0, tp":"=r"(x));
    return x;
}


// mhartid存放了核的id
static inline reg_t read_mhartid() {
    reg_t x;
    asm volatile ("csrr %0, mhartid":"=r"(x));
    return x;
}


// mstatus寄存器存放了进入trap时的状态等信息，比如中断是否禁用，处于M，S，U哪种状态等
static inline reg_t read_mstatus() {
    reg_t x;
    asm volatile ("csrr %0, mstatus":"=r"(x));
    return x;
}
static inline void write_mstatus(reg_t x){
    asm volatile ("csrw mstatus, %0"::"r"(x));
}


// mepc存放了trap处理后需要返回执行的地址，异常时当前pc位置，中断时是下一条命令的位置
static inline void write_mepc(reg_t x){
    asm volatile ("csrw mepc, %0"::"r"(x));
}
static inline reg_t read_mepc(){
    reg_t x;
    asm volatile ("csrr %0, mepc":"=r"(x));
    return x;
}


// mscratch存放Context结构体指针
static inline void write_mscratch(reg_t x){
    asm volatile ("csrw mscratch, %0"::"r"(x));
}


// mtvec用于存放trap处理程序的入口地址
static inline void write_mtvec(reg_t x){
    asm volatile ("csrw mtvec, %0"::"r"(x));
}


// mie用于打开或关闭中断
static inline void write_mie(reg_t x){
    asm volatile ("csrw mie, %0"::"r"(x));
}
static inline reg_t read_mie(){
    reg_t x;
    asm volatile ("csrr %0, mie":"=r"(x));
    return x;
}


// mcause存放了异常代号
static inline reg_t read_mcause(){
    reg_t x;
    asm volatile ("csrr %0, mcause":"=r"(x));
    return x;
}



#endif //TPTOGIAROS_RISCV_H
