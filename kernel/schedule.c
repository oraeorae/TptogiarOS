//
// Created by root on 2022.07.20.
//

#include "header/os.h"

//
extern void switch_to(struct Context *context);

#define STACK_SIZE 1024
#define MAX_TASK 10



uint8_t taskStack[MAX_TASK][STACK_SIZE];
struct Context taskContexts[MAX_TASK];

static int topTaskPointer = 0;
static int currentTaskPointer = -1;


static void modifyMscratchRegister(reg_t value){
    asm volatile("csrw mscratch,%0"
                  :
                  :"r"(value)
                );
}


void schedule_init(){
    modifyMscratchRegister(0);
}


void schedule(){
    if (topTaskPointer<=0){
        panic("There are nothing task to execute !");
    }
    currentTaskPointer = (currentTaskPointer+1)%topTaskPointer;
    struct Context* nextContext = &taskContexts[currentTaskPointer];
    switch_to(nextContext);
}

int taskCreate(void (*taskAddress)(void)){
    if (topTaskPointer < MAX_TASK){
        taskContexts[topTaskPointer].sp = (reg_t)&taskStack[topTaskPointer][STACK_SIZE - 1];
        // 此处将任务地址放入当前这个context的ra中，
        // 是因为在switch_to函数内会把这个context加载进寄存器，然后函数放回到ra寄存器记录的地址处
        // 而此时ra寄存器就是还task的地址
        taskContexts[topTaskPointer].ra = (reg_t)taskAddress;
        topTaskPointer++;
        return 0;
    } else{
        return -1;
    }
}


// TODO 待改进的sleep
void taskDelayCount(volatile int count){
    count*=10000;
    while (count--);
}


void taskYield(){
    schedule();
}




