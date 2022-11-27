#!/bin/bash


for arg in "$@"
    do
        gcc -g ${arg}.c ../*.c -o ${arg}.bin
        echo compile ${arg} succeed!
    done

for arg in "$*"
    do
        ./${arg}.bin
    done


#valgrind --leak-check=yes ./list
