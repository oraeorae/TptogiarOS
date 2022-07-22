//
// Created by root on 2022.07.20.
//

#include "header/os.h"

//
extern void switch_to(struct Context *context);

#define STACK_SIZE 1024

uint8_t taskStack[STACK_SIZE];

struct Context taskContext;

void userTask(void);

static void modifyMscratchRegister(reg_t value){
    asm volatile("csrw mscratch,%0"
                  :
                  :"r"(value)
                );
}


void schedule_init(){

    modifyMscratchRegister(0);

    taskContext.sp = (reg_t) & taskStack[STACK_SIZE -1];
    taskContext.ra = (reg_t) userTask;

}


void schedule(){

    switch_to(&taskContext);

}

// TODO 待改进的sleep
void taskDelayCount(volatile int count){
    count*=10000;
    while (count--);
}



void userTask(void){
    printf("Task 0 : 任务被创建！ \n");
    while (1){
        printf("Task 0 : Running \n");
        taskDelayCount(5000);
    }
}
