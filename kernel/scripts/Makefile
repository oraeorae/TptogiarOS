include ./common.mk

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
	../../test/TptogiarOS/testTask.c \
	../../test/TptogiarOS/testPage.c \
	../../test/TptogiarOS/testTrap.c \


OBJS = $(SRCS_ASM:.S=.o)
OBJS += $(SRCS_C:.c=.o)

.DEFAULT_GOAL := all
all: os.elf

# start.o must be the first in dependency!
os.elf: ${OBJS}
	${CC} ${CFLAGS} -T ./os.ld -o os.elf $^
	${OBJCOPY} -O binary os.elf os.bin
	echo "\e[;31;1m Success! \e[m"

%.o : %.c
	${CC} ${CFLAGS} -c -o $@ $<

%.o : %.S
	${CC} ${CFLAGS} -c -o $@ $<

run: all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel os.elf


.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel os.elf -s -S &
	@${GDB} os.elf -q -x ./gdbinit

.PHONY : code
code: all
	@${OBJDUMP} -S os.elf | less

.PHONY : clean
clean:
	rm -rf *.bin *.elf
	cd .. && rm -rf  *.o
	cd ../assembly && rm -rf *.o
	cd ../../test/TptogiarOS && rm -rf *.o


