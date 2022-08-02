//
// Created by root on 2022.07.30.
//
#include "../headers/os.h"
#include "../headers/syscall.h"


void doSyscall(struct Context *context) {

    uint32_t syscallNum = context->a7;

    switch (syscallNum) {

        case SYS_getHartId:
            context->a0 = sys_getHartId((unsigned int *) context->a0);
            break;

        default:
            printf("暂未定义的系统调用号,请重试... \n");
            context->a0 = -1;
            break;
    }


}
