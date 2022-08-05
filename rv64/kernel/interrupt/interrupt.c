//
// Created by root on 8/3/22.
//
#include "interrupt.h"
#include <riscv.h>

// 打开supervisor模式下的全局中断开关
void interruptEnable(void) { set_csr(sstatus, SSTATUS_SIE); }

// 关闭supervisor模式下的全局中断开关
void interruptDisable(void) { clear_csr(sstatus, SSTATUS_SIE); }
