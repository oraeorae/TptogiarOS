//
// Created by root on 2022.07.21.
//
#include "../kernel/c/headers/Os.h"


#define DELAY 1000

extern void userTaskWithTimer(void);

extern void userTaskWithTrap(void);

extern void userTaskWithLock0(void);
extern void userTaskWithLock1(void);

extern void testSyscall(void);


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









void osMain(void) {



    taskCreate(testSyscall);

    //taskCreate(userTaskWithTimer);

    //taskCreate(userTaskWithLock0);
    //taskCreate(userTaskWithLock1);

    //taskCreate(userTask0);
    //taskCreate(userTask1);

    //taskCreate(userTaskWithTrap);
}
