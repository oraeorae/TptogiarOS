CROSS_COMPILE = riscv64-unknown-elf-
# gcc -w 关闭警告信息  -W 显示警告信息
CFLAGS = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -w

QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 1 -machine virt -bios none

GDB = gdb-multiarch
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump

SRCS_ASM = \
	.././assembly/start.S \
	.././assembly/mem.S \
	.././assembly/switch.S \
	.././assembly/trap.S \
	.././assembly/macro/context.S \

SRCS_C = \
	../kernel.c \
	../uart.c \
	../printf.c \
	../page.c \
	../schedule.c \
	../trap.c \
	../plic.c \
	../timer.c \
	../lock.c \
	../../test/TptogiarOS/testTask.c \
	../../test/TptogiarOS/testPage.c \
	../../test/TptogiarOS/testTrap.c \
	../../test/TptogiarOS/testLock.c \
	../../test/TptogiarOS/testTimer.c \


OBJS = $(SRCS_ASM:.S=.o)
OBJS += $(SRCS_C:.c=.o)

.DEFAULT_GOAL := all
all: TptogiarOS.elf

# start.o must be the first in dependency!
TptogiarOS.elf: ${OBJS}
	${CC} ${CFLAGS} -T ./os.ld -o TptogiarOS.elf $^
	${OBJCOPY} -O binary TptogiarOS.elf TptogiarOS.bin
	echo "\e[;31;1m Success! \e[m"

%.o : %.c
	${CC} ${CFLAGS} -c -o $@ $<

%.o : %.S
	${CC} ${CFLAGS} -c -o $@ $<

run: all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel TptogiarOS.elf


.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel TptogiarOS.elf -s -S &
	@${GDB} TptogiarOS.elf -q -x ./gdbinit

.PHONY : code
code: all
	@${OBJDUMP} -S TptogiarOS.elf | less

.PHONY : clean
clean:
	rm -rf *.bin *.elf
	cd .. && rm -rf  *.o
	cd ../assembly && rm -rf *.o
	cd ../assembly/macro && rm -rf *.o
	cd ../../test/TptogiarOS && rm -rf *.o


