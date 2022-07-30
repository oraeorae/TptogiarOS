//
// Created by root on 2022.07.26.
//
#include "headers/os.h"

extern void schedule(void);

//
#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ
// 最大软件定时器数
#define MAX_TIMER 100


static uint32_t tick = 0;
static struct Timer timerList[MAX_TIMER];



void timerLoad(int interval){
    // 每个hart都有独一里一套寄存器，所以mtime是独立的，
    // 所以需要针对每个hart单独设置
    int hartId = read_mhartid();
    // 设置mtimecmp为当前mtime再加上一定的时间间隔
    uint64_t * timecmpAddress = (uint64_t*)CLINT_MTIMECMP(hartId);
    uint64_t * timeAddress = (uint64_t*) CLINT_MTIME;
    uint64_t nextTime = *timeAddress +interval * 5;
    *timecmpAddress = nextTime;
}


void timerInit(){

    struct Timer* timerPointer = &(timerList[0]);
    for (int i = 0; i < MAX_TIMER; ++i) {
        timerPointer->func = NULL;
        timerPointer->args = NULL;
        timerPointer++;
    }


    timerLoad(TIMER_INTERVAL);
    // 对于当前CPU，打开Meachine模式下的定时器中断
    write_mie(read_mie() | MIE_MTIE);
    // 对于当前CPU，打开全局中断开关
    write_mstatus(read_mstatus() | MSTATUS_MIE);


}

struct Timer *timerCreate(void (*handler)(void *args), void *args, uint32_t timeout){
    if (NULL == handler || 0 ==timeout){
        return NULL;
    }

    spinLock();

    struct Timer * timerPointer = &(timerList[0]);
    for (int i = 0; i < MAX_TIMER; ++i) {
        if (NULL == timerPointer->func){
            break;
        }
        timerPointer++;
    }
    //if (NULL != timerPointer->func){
    //
    //}
    timerPointer->func = handler;
    timerPointer->args = args;
    timerPointer->timeoutTick = tick + timeout;
    spinUnlock();
    return timerPointer;
}

void timerDelete(struct Timer* timer){
    spinLock();
    struct Timer* timerPointer = &(timerList[0]);
    for (int i = 0; i < MAX_TIMER; ++i) {
        if (timerPointer == timer){
            timerPointer->func = NULL;
            timerPointer->args = NULL;
            break;
        }
        timerPointer++;
    }
    spinUnlock();
}

static inline void timerCheck(){
    struct Timer* timerPointer = &(timerList[0]);
    for (int i = 0; i < MAX_TIMER; ++i) {
        if (NULL != timerPointer->func){
            if (tick >= timerPointer->timeoutTick){
                timerPointer->func(timerPointer->args);

                timerPointer->func = NULL;
                timerPointer->args = NULL;
                break;
            }
        }
        timerPointer++;
    }
}



void timerHandler(){
    tick++;
    printf("当前已经产生的定时器中断的次数 = %d \n",tick);
    timerCheck();
    timerLoad(TIMER_INTERVAL);
    schedule();
}



