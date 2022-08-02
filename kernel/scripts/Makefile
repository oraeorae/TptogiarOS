cross_compile = riscv64-unknown-elf-
qemu = qemu-system-riscv32
qemu_args = -nographic -smp 1 -machine virt -bios none
# gcc -w 关闭警告信息  -W 显示警告信息
gcc_args = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -w
gdb = gdb-multiarch

SRCS_ASM = \
	.././assembly/Start.S \
	.././assembly/Mem.S \
	.././assembly/Switch.S \
	.././assembly/Trap.S \
	.././assembly/macro/Context.S \
	../../TptogiarOS-example/syscall/TestCSR.S \

SRCS_C = \
	../c/Kernel.c \
	../c/Uart.c \
	../c/Printf.c \
	../c/Page.c \
	../c/Schedule.c \
	../c/Trap.c \
	../c/Plic.c \
	../c/Timer.c \
	../c/Lock.c \
	../c/syscall/Syscall.c \
	../c/syscall/Csr.c \
	../../TptogiarOS-example/TestTask.c \
	../../TptogiarOS-example/TestPage.c \
	../../TptogiarOS-example/TestTrap.c \
	../../TptogiarOS-example/TestLock.c \
	../../TptogiarOS-example/TestTimer.c \
	../../TptogiarOS-example/syscall/TestSyscall.c \


gcc = ${cross_compile}gcc
objcopy = ${cross_compile}objcopy
objdump = ${cross_compile}objdump


OBJS = $(SRCS_ASM:.S=.o)
OBJS += $(SRCS_C:.c=.o)


.DEFAULT_GOAL := all
all: TptogiarOS.elf






# start.o must be the first in dependency!
TptogiarOS.elf: ${OBJS}
	${gcc} ${gcc_args} -T ./os.ld -o TptogiarOS.elf $^
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
	cd ../c && rm -rf  *.o
	cd ../c/syscall && rm -rf  *.o
	cd ../assembly && rm -rf *.o
	cd ../assembly/macro && rm -rf *.o
	cd ../../TptogiarOS-example && rm -rf *.o
	cd ../../TptogiarOS-example/syscall && rm -rf *.o
	echo "\e[;31;1m Success! \e[m"


