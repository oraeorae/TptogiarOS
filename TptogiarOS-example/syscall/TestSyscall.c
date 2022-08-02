//
// Created by root on 2022.07.30.
//
#include "../../kernel/c/headers/Os.h"

extern int getHartId(unsigned int* hartId);


void testSyscall(void){
    printf("Syscall Task : Created ! \n");


    int hartId = -1;
    int executeResult = getHartId(&hartId);
    if (!executeResult){
        printf("syscall getHartId success, hartid = %d \n",hartId);
    } else {
        printf("syscall getHartId() execute failed, return code = %d \n",executeResult);
    }


    while (1) {
        printf("Syscall Task : Running \n");
        taskDelayCount(5000);
    }



}


