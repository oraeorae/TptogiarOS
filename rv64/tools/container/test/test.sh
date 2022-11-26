#!/bin/bash


for arg in "$*"
    do
        gcc -g ${arg}.c ../${arg}.c -o ${arg}.bin
    done

for arg in "$*"
    do
        ./${arg}.bin
    done


#valgrind --leak-check=yes ./list
