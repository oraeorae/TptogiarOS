cross_compile = riscv64-unknown-elf-
qemu = qemu-system-riscv32
qemu_args = -nographic -smp 1 -machine virt -bios none
# gcc -w 关闭警告信息  -W 显示警告信息
gcc_args = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -w
gdb = gdb-multiarch

SRCS_ASM = \
	kernel/./assembly/Start.S \
	kernel/./assembly/Mem.S \
	kernel/./assembly/Switch.S \
	kernel/./assembly/Trap.S \
	kernel/./assembly/macro/Context.S \
	kernel/../TptogiarOS-example/syscall/TestCSR.S \

SRCS_C = \
	kernel/c/Kernel.c \
	kernel/c/Uart.c \
	kernel/c/Printf.c \
	kernel/c/Page.c \
	kernel/c/Schedule.c \
	kernel/c/Trap.c \
	kernel/c/Plic.c \
	kernel/c/Timer.c \
	kernel/c/Lock.c \
	kernel/c/syscall/Syscall.c \
	kernel/c/syscall/Csr.c \
	kernel/../TptogiarOS-example/TestTask.c \
	kernel/../TptogiarOS-example/TestPage.c \
	kernel/../TptogiarOS-example/TestTrap.c \
	kernel/../TptogiarOS-example/TestLock.c \
	kernel/../TptogiarOS-example/TestTimer.c \
	kernel/../TptogiarOS-example/syscall/TestSyscall.c \


gcc = ${cross_compile}gcc
objcopy = ${cross_compile}objcopy
objdump = ${cross_compile}objdump


OBJS = $(SRCS_ASM:.S=.o)
OBJS += $(SRCS_C:.c=.o)


.DEFAULT_GOAL := all
all: TptogiarOS.elf






# start.o must be the first in dependency!
TptogiarOS.elf: ${OBJS}
	${gcc} ${gcc_args} -T kernel/scripts/os.ld -o TptogiarOS.elf $^
	${objcopy} -O binary TptogiarOS.elf TptogiarOS.bin
	echo "\e[;31;1m Success! \e[m"

%.o : %.c
	${gcc} ${gcc_args} -c -o $@ $<

%.o : %.S
	${gcc} ${gcc_args} -c -o $@ $<

Run: all
	@${qemu} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit qemu"
	@echo "------------------------------------"
	@${qemu} ${qemu_args} -kernel TptogiarOS.elf


.PHONY : debug
Debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit gdb and qemu"
	@echo "-------------------------------------------------------"
	@${qemu} ${qemu_args} -kernel TptogiarOS.elf -s -S &
	@${gdb} TptogiarOS.elf -q -x ./gdbinit

.PHONY : code
Code: all
	@${objdump} -S TptogiarOS.elf | less

.PHONY : clean
Clean:
	rm -rf *.bin *.elf
	cd kernel/c && rm -rf  *.o
	cd kernel/c/syscall && rm -rf  *.o
	cd kernel/assembly && rm -rf *.o
	cd kernel/assembly/macro && rm -rf *.o
	cd kernel/../TptogiarOS-example && rm -rf *.o
	cd kernel/../TptogiarOS-example/syscall && rm -rf *.o
	echo "\e[;31;1m Success! \e[m"


