cross_compile = riscv64-unknown-elf-
qemu = qemu-system-riscv32
qemu_args = -nographic -smp 1 -machine virt -bios none
# gcc -w 关闭警告信息  -W 显示警告信息
gcc_args = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -w
gdb = gdb-multiarch

SRCS_ASM = \
	.././assembly/start.S \
	.././assembly/mem.S \
	.././assembly/switch.S \
	.././assembly/trap.S \
	.././assembly/macro/context.S \
	../../TptogiarOS-example/syscall/testCSR.S \

SRCS_C = \
	../c/kernel.c \
	../c/uart.c \
	../c/printf.c \
	../c/page.c \
	../c/schedule.c \
	../c/trap.c \
	../c/plic.c \
	../c/timer.c \
	../c/lock.c \
	../c/syscall/syscall.c \
	../c/syscall/csr.c \
	../../TptogiarOS-example/testTask.c \
	../../TptogiarOS-example/testPage.c \
	../../TptogiarOS-example/testTrap.c \
	../../TptogiarOS-example/testLock.c \
	../../TptogiarOS-example/testTimer.c \
	../../TptogiarOS-example/syscall/testSyscall.c \


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

run: all
	@${qemu} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit qemu"
	@echo "------------------------------------"
	@${qemu} ${qemu_args} -kernel TptogiarOS.elf


.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit gdb and qemu"
	@echo "-------------------------------------------------------"
	@${qemu} ${qemu_args} -kernel TptogiarOS.elf -s -S &
	@${gdb} TptogiarOS.elf -q -x ./gdbinit

.PHONY : code
code: all
	@${objdump} -S TptogiarOS.elf | less

.PHONY : clean
clean:
	rm -rf *.bin *.elf
	cd ../c && rm -rf  *.o
	cd ../c/syscall && rm -rf  *.o
	cd ../assembly && rm -rf *.o
	cd ../assembly/macro && rm -rf *.o
	cd ../../TptogiarOS-example && rm -rf *.o
	cd ../../TptogiarOS-example/syscall && rm -rf *.o
	echo "\e[;31;1m Success! \e[m"


