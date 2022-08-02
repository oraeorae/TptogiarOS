
rv32Dir = ./rv32/kernel/scripts/
rv64Dir = ./rv64/

.PHONY:rv64
rv64:
	cd $(rv64Dir) && make
	echo "\e[;31;1m rv64 make Success! \e[m"
.PHONY:run64
run64:
	cd $(rv64Dir) && make qemu



.PHONY:rv32
rv32:
	cd $(rv32Dir) && make
	echo "\e[;31;1m rv32 make Success! \e[m"
.PHONY:run64
run32:
	cd $(rv32Dir) && make run32




.PHONY:clean
clean:
	cd $(rv32Dir) && make clean32
	cd $(rv64Dir) && make clean
	echo "\e[;31;1m clean Success! \e[m"
