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
	j start_kernel



	

park:
	# 其他核执行的命令
	wfi
	j park



stacks:
	.skip STACK_SIZE * MAXNUM_CPU

	.end
