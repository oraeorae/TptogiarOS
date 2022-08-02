#include "macro/Context.S"

.text

.globl switch_to
.align 4

# 函数原型：void switch_to(struct Context *next);
switch_to:

    # a0是给函数参数，即Context的存放位置
	csrw	mscratch, a0


	# 将原mepc的值重新加载会mepc寄存器
    lw a1, 124(a0)
    csrw mepc, a1

	mv	t6, a0
	reg_restore t6


	# 将Context加载回通用寄存器后mepc寄存器的值已经改为该task原来执行的位置，所以只需调用mret，让他返回到该Context的mepc处执行即可
	mret

.end




