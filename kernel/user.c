//
// Created by root on 2022.07.21.
//
#include "header/os.h"


#define DELAY 1000


extern void testTrap();

void userTask0(void) {
    printf("Task 0 : 任务被创建！ \n");
    while (1) {
        printf("Task 0 : Running \n");
        testTrap();
        taskDelayCount(5000);
        taskYield();
    }
}

void userTask1(void) {
    printf("Task 1 : 任务被创建！ \n");
    while (1) {
        printf("Task 1 : Running \n");
        taskDelayCount(5000);
        taskYield();
    }
}


void osMain(void) {

    taskCreate(userTask0);
    taskCreate(userTask1);

}
