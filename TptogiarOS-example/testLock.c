//
// Created by root on 2022.07.30.
//
#include "../kernel/c/headers/os.h"




void userTaskWithLock0(void){
    printf("Lock0 Task : 任务被创建！ \n");
    int count = 0;


    while (1) {
        if (count<20){
            spinLock();
        } else {
            spinUnlock();
        }
        printf("Lock0 Task : Running \n");
        taskDelayCount(5000);
        count++;
    }
}

void userTaskWithLock1(void){
    printf("Lock1 Task : 任务被创建！ \n");
    while (1) {
        printf("Lock1 Task : Running \n");
        taskDelayCount(5000);
    }
}
