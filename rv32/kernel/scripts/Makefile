cross_compile = riscv64-unknown-elf-
qemu = qemu-system-riscv32
qemu_args = -nographic -smp 1 -machine virt -bios none
# gcc -w 关闭警告信息  -W 显示警告信息
gcc_args = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -w
gdb = gdb-multiarch

SRCS_ASM = \
	rv32/kernel/./assembly/start.S \
	rv32/kernel/./assembly/mem.S \
	rv32/kernel/./assembly/switch.S \
	rv32/kernel/./assembly/trap.S \
	rv32/kernel/./assembly/macro/context.S \
	rv32/kernel/../TptogiarOS-example/syscall/testCSR.S \

SRCS_C = \
	rv32/kernel/c/kernel.c \
	rv32/kernel/c/uart.c \
	rv32/kernel/c/printf.c \
	rv32/kernel/c/page.c \
	rv32/kernel/c/schedule.c \
	rv32/kernel/c/trap.c \
	rv32/kernel/c/plic.c \
	rv32/kernel/c/timer.c \
	rv32/kernel/c/lock.c \
	rv32/kernel/c/syscall/syscall.c \
	rv32/kernel/c/syscall/csr.c \
	rv32/kernel/../TptogiarOS-example/testTask.c \
	rv32/kernel/../TptogiarOS-example/testPage.c \
	rv32/kernel/../TptogiarOS-example/testTrap.c \
	rv32/kernel/../TptogiarOS-example/testLock.c \
	rv32/kernel/../TptogiarOS-example/testTimer.c \
	rv32/kernel/../TptogiarOS-example/syscall/testSyscall.c \


gcc = ${cross_compile}gcc
objcopy = ${cross_compile}objcopy
objdump = ${cross_compile}objdump


OBJS = $(SRCS_ASM:.S=.o)
OBJS += $(SRCS_C:.c=.o)


.DEFAULT_GOAL := all32
all32: TptogiarOS.elf






# start.o must be the first in dependency!
TptogiarOS.elf: ${OBJS}
	${gcc} ${gcc_args} -T rv32/kernel/scripts/os.ld -o TptogiarOS.elf $^
	${objcopy} -O binary TptogiarOS.elf TptogiarOS.bin
	echo "\e[;31;1m Success! \e[m"

%.o : %.c
	${gcc} ${gcc_args} -c -o $@ $<

%.o : %.S
	${gcc} ${gcc_args} -c -o $@ $<

run32: all32
	@${qemu} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit qemu"
	@echo "------------------------------------"
	@${qemu} ${qemu_args} -kernel TptogiarOS.elf


.PHONY : debug32
debug32: all32
	@echo "Press Ctrl-C and then input 'quit' to exit gdb and qemu"
	@echo "-------------------------------------------------------"
	@${qemu} ${qemu_args} -kernel TptogiarOS.elf -s -S &
	@${gdb} TptogiarOS.elf -q -x ./gdbinit

.PHONY : code32
code32: all32
	@${objdump} -S TptogiarOS.elf | less

.PHONY : clean32
clean32:
	rm -rf *.bin *.elf
	cd rv32/kernel/c && rm -rf  *.o
	cd rv32/kernel/c/syscall && rm -rf  *.o
	cd rv32/kernel/assembly && rm -rf *.o
	cd rv32/kernel/assembly/macro && rm -rf *.o
	cd rv32/kernel/../TptogiarOS-example && rm -rf *.o
	cd rv32/kernel/../TptogiarOS-example/syscall && rm -rf *.o
	echo "\e[;31;1m Success! \e[m"


