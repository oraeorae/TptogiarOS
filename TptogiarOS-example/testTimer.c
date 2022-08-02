//
// Created by root on 2022.07.30.
//
#include "../kernel/c/headers/os.h"



struct TestUser{
    int counter;
    char *str;
};

struct TestUser person = {0,"Tptogiar"};


void timerFunc(void *arg){
    if(NULL == arg){
        return;
    }
    struct TestUser* user = (struct TestUser*)arg;
    user->counter++;
    printf("======> time out : %s: %d \n ",user->str,user->counter);
}



void userTaskWithTimer(void){
    printf("Timer task : Created! \n");

    struct Timer* timer1 = timerCreate(timerFunc,&person,3);
    if(NULL == timer1){
        printf(" timer1 create failed! \n");
    }

    struct Timer* timer2 = timerCreate(timerFunc,&person,5);
    if(NULL == timer2){
        printf(" timer2 create failed! \n");
    }

    struct Timer* timer3 = timerCreate(timerFunc,&person,10);
    if(NULL == timer3){
        printf(" timer3 create failed! \n");
    }

    while (1){
        printf("Timer task : Running... \n");
        taskDelayCount(50000);
    }

}