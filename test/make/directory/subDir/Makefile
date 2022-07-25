


test.elf:test.o
	gcc test.o -o test.elf
test.o:../test.c
	gcc ../test.c -c -o test.o


all:
	echo all




run:
	echo run
	make debug


debug:
	echo debug


cd:
	echo cd
	pwd
	cd ../..
	pwd

clean:
	rm -rf *.elf *.bin *.o
	cd .. && rm -rf *.elf *.bin *.o





