//
// Created by root on 2022.07.26.
//
#include "headers/os.h"

#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

static uint32_t tick = 0;

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

    timerLoad(TIMER_INTERVAL);
    // 对于当前CPU，打开Meachine模式下的定时器中断
    write_mie(read_mie() | MIE_MTIE);
    // 对于当前CPU，打开全局中断开关
    write_mstatus(read_mstatus() | MSTATUS_MIE);


}

void timerHandler(){
    tick++;
    printf("当前已经产生的定时器中断的次数 = %d \n",tick);
    timerLoad(TIMER_INTERVAL);
}



