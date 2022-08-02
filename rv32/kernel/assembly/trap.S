#include "macro/context.S"

.text

.globl trapVector
.align 4

trapVector:
    # 宏，保存当前Context
    allRegSaveAndMEPC

    # 读取异常代号，即详细原因,并传入处理函数
    csrr a0, mepc
    csrr a1, mcause
    csrr a2, mscratch
    call trapHandler

    # 将被trapHandler修改后的mepc的值放入mepc
    csrw mepc, a0
    # 恢复上下文
    csrr t6, mscratch
    reg_restore t6


    # 返回
    mret




.end
