//
// Created by root on 2022.07.21.
//
#include "../../kernel/headers/os.h"


#define DELAY 1000





void userTask0(void) {
    printf("Task 0 : 任务被创建！ \n");
    taskYield();
    printf("Task 0 : come back \n");
    while (1) {
        printf("Task 0 : Running \n");
        taskDelayCount(5000);
    }
}

void userTask1(void) {
    printf("Task 1 : 任务被创建！ \n");
    while (1) {
        printf("Task 1 : Running \n");
        taskDelayCount(5000);
    }
}

void userTaskWithTrap(void) {
    printf("Task 2 : 任务被创建！ \n");
    while (1) {
        printf("Task 2 : Running \n");
        testTrap();
        taskDelayCount(5000);
    }
}

void userTaskWithLock0(void){
    printf("Lock0 Task : 任务被创建！ \n");
    int count = 0;
    struct SpinLock* lock = getSpinLock();

    while (1) {
        if (count<20){
            lock = spinLock(lock);
        } else {
            spinUnlock(lock);
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


void osMain(void) {

    taskCreate(userTaskWithLock0);
    taskCreate(userTaskWithLock1);
    //taskCreate(userTask0);
    //taskCreate(userTask1);
    //taskCreate(userTaskWithTrap);
}
