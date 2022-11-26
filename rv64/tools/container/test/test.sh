#!/bin/bash


for arg in "$@"
    do
        echo ${arg}
        gcc -g ${arg}.c ../*.c -o ${arg}.bin
    done

for arg in "$*"
    do
        ./${arg}.bin
    done


#valgrind --leak-check=yes ./list
