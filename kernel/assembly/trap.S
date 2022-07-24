#include "macro/context"

.text

.globl trapVector
.align 4

trapVector:
    # 宏，保存当前Context
    allRegSave

    # 读取异常代号，即详细原因,并传入处理函数
    csrr a0, mepc
    csrr a1, mcause
    call trapHandler

    # 还原mepc的值
    csrw mepc, a0
    # 恢复上下文
    csrr t6, mscratch
    reg_restore t6
    # 返回
    mret




.end
