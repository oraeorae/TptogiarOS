//
// Created by root on 2022.07.25.
//
#include "headers/Os.h"



void plicInit(void){

    int hart = read_mhartid();

    // 对于当前PLIC，设置UART产生的中断的优先级为1
    *(uint32_t*)PLIC_PRIORITY(UART0_IRQ) = 1;

    // 对于当前hart，打开UART中断源
    *(uint32_t*)PLIC_MENABLE(hart) = (1 << UART0_IRQ);

    // 对于当前hart,设置优先级阀值为0
    *(uint32_t*)PLIC_MTHRESHOLD(hart) = 0;

    // 对于当前CPU，打开Meachine模式下的外部中断
    write_mie(read_mie() | MIE_MEIE);

    // 对于当前CPU，打开全局中断开关
    write_mstatus(read_mstatus() | MSTATUS_MIE);

}


int plicClaim(void){
    int hart = read_mhartid();
    int interruptId = *(uint32_t*)PLIC_MCLAIM(hart);
    return interruptId;
}


void plicComplete(int interruptId){
    int hart = read_mhartid();
    *(uint32_t*)PLIC_MCOMPLETE(hart) = interruptId;
}
