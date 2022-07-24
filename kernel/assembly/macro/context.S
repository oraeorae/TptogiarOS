
# struct Context *base = &ctx_task;
# base -> ra = ra; 执行switch_to之前，switch_to的下一跳语句的地址已经被放进ra寄存器中，一遍返回是继续执行
# 将所有通用寄存器存至内存，其中所有通用寄存器用Context来表征了
# 需要用一个寄存器来存放内存的基地址，其中选用的是t6
# 故t6寄存器存放到内存的操作需要在这个宏之外特殊处理一下
.macro reg_save base
	sw ra, 0(\base)
	sw sp, 4(\base)
	sw gp, 8(\base)
	sw tp, 12(\base)
	sw t0, 16(\base)
	sw t1, 20(\base)
	sw t2, 24(\base)
	sw s0, 28(\base)
	sw s1, 32(\base)
	sw a0, 36(\base)
	sw a1, 40(\base)
	sw a2, 44(\base)
	sw a3, 48(\base)
	sw a4, 52(\base)
	sw a5, 56(\base)
	sw a6, 60(\base)
	sw a7, 64(\base)
	sw s2, 68(\base)
	sw s3, 72(\base)
	sw s4, 76(\base)
	sw s5, 80(\base)
	sw s6, 84(\base)
	sw s7, 88(\base)
	sw s8, 92(\base)
	sw s9, 96(\base)
	sw s10, 100(\base)
	sw s11, 104(\base)
	sw t3, 108(\base)
	sw t4, 112(\base)
	sw t5, 116(\base)
	# 这里没有存放t6寄存器，因为t6寄存器在调用这个宏之前，已经被置换为Context的地址了
    # 其原先的值也在调用这个宏之前被置换进msrcratch寄存器了
.endm

# 将内存中某上下文中存放的寄存器的通用寄存器的值全部恢复回寄存器中
# struct Context *base = &ctx_task;
# ra = base->ra;
.macro reg_restore base
	lw ra, 0(\base)
	lw sp, 4(\base)
	lw gp, 8(\base)
	lw tp, 12(\base)
	lw t0, 16(\base)
	lw t1, 20(\base)
	lw t2, 24(\base)
	lw s0, 28(\base)
	lw s1, 32(\base)
	lw a0, 36(\base)
	lw a1, 40(\base)
	lw a2, 44(\base)
	lw a3, 48(\base)
	lw a4, 52(\base)
	lw a5, 56(\base)
	lw a6, 60(\base)
	lw a7, 64(\base)
	lw s2, 68(\base)
	lw s3, 72(\base)
	lw s4, 76(\base)
	lw s5, 80(\base)
	lw s6, 84(\base)
	lw s7, 88(\base)
	lw s8, 92(\base)
	lw s9, 96(\base)
	lw s10, 100(\base)
	lw s11, 104(\base)
	lw t3, 108(\base)
	lw t4, 112(\base)
	lw t5, 116(\base)
	lw t6, 120(\base)
.endm


.macro allRegSave
    csrrw t6, mscratch, t6
    reg_save t6
    mv t5, t6
    csrr t6, mscratch
    sw t6, 120(t5)
    # 还原mscratch的值，使其还指向原Context的位置
    csrw mscratch, t5
.endm