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


	# https://lore.kernel.org/qemu-devel/20201223192553.332508-1-atish.patra@wdc.com/
	# For qemu version >= 6.0, exception would be raised if no PMP enty is
	# configured. So just configure one entny, which allows all the whole
	# 32-bits physical address range is R/W/X.
	# FIXME: I say it is a temporary workaroud due to I think the patch
	# above contains bug, and I have raised new issue to qemu but it has not
	# been rootcaused till now. Details please refer to
	# https://gitlab.com/qemu-project/qemu/-/issues/585 or
	# https://gitee.com/unicornx/riscv-operating-system-mooc/issues/I441IC (in chinese)
	# So it's just a temporary workaround till now to not block people who
	# want to try newer qemu (>= 6.0).
	li      t0, 0xffffffff
	csrw    pmpaddr0, t0
	li      t0, 0xf
	csrw    pmpcfg0, t0



	# 在执行第一次switch_to内的mret指令时，会根据原先mstatus的值调整mstatus的值，
	# 而原先mstatus寄存器的值为0，调整后还是为0，会使得一些开关被置为关的状态,
    # 此外，原先mstatus中的值还会影响调用mret后CPU所处的模式，
    # 比如mstatus.MPP就决定了调用mret后所处的模式，3,2,1,0分别表示Machine,Reserved,Supervisor,User模式
    # 而mstatus.MPIE就决定了调用mret后Machine模式下的中断是否打开
	# 所以在此处需要先对mstatus进行初始化

	# 设置mstatus.MPP为0，mstatus.MPIE为
    li t0, 1<< 7
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
