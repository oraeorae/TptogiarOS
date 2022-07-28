#include "../headers/platform.h"


	.equ STACK_SIZE,1024

	.global _start

	.text





_start:
	csrr t0,mhartid
	mv tp,t0   #存起来以备用
	bnez t0,park


	# 第一个核执行的命令
	
	# 准备栈指针
	slli t0,t0,10
	la sp,stacks + STACK_SIZE
	add sp,sp,t0

	# 在执行第一次switch_to内的mret指令时，会根据原先mstatus的值调整mstatus的值，
	# 而原先mstatus寄存器的值为0，调整后还是为0，会使得一些开关被置为关的状态,
	# 所以在此处需要先对mstatus进行初始化
    li t0, 3 << 11 | 1<< 7
    csrr a1, mstatus
    or t0, t0, a1
    csrw mstatus, t0


	j start_kernel



	

park:
	# 其他核执行的命令
	wfi
	j park



stacks:
	.skip STACK_SIZE * MAXNUM_CPU

	.end
