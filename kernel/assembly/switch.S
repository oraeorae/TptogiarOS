#include "macro/context.S"

.text

.globl switch_to
.align 4

# 函数原型：void switch_to(struct Context *next);
switch_to:
    # 将t5寄存器和mscratch寄存器的值进行交换
	csrrw	t6, mscratch, t6
	# 用mscratch来指向内存的的Context结构体，但原mscratch的值可能为空
	beqz	t6, 1f
	reg_save t6			

	# 原t6的值被置换进mscratch里面，且作为基地址没有在宏中保存进内存，故需要再此将t6写进内存

	# t5的值同其他通用寄存器一样已经被保存进内存，可以任意修改，所以换他来当基地址
    mv	t5, t6		

    # 再次置换，t6变原原值
    csrr	t6, mscratch	
    sw	t6, 120(t5)

1:
    
    # a0是给函数参数，即Context的存放位置
	csrw	mscratch, a0

	mv	t6, a0
	reg_restore t6

	# 将Context加载回通用寄存器后ra寄存器的值已经改为该Context内ra的值了，所以只需调用ret，让他返回到该Context的ra处执行即可
	ret

.end




