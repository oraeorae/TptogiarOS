//
// Created by root on 2022.07.23.
//
#include "headers/os.h"

extern void trapVector(void);
extern void uartInterruptHandler(void);


void trapInit(){
    write_mtvec((reg_t)trapVector);
};

static void externalInterruptHandler(){
    int interruptId = plicClaim();
    if (interruptId == UART0_IRQ){
        uartInterruptHandler();
    } else if (interruptId) {
        printf(" 暂为支持的中断类型！ \n",interruptId);
    }

    if (interruptId) {
        plicComplete();
    }
}


reg_t trapHandler(reg_t epc,reg_t cause){

    reg_t returnPc = epc;
    //
    reg_t causeCode = cause & 0xfff;


    // 0x8000000,即1000 0000 0000 0000 0000 0000 0000,
    // 与运算后可以判断第一位是1还是0，
    // 1 表示中断，0表示常
    if (cause & 0x80000000){
        switch (causeCode) {
            case 3:
                printf("软中断software interruption \n");
                break;
            case 7:
                printf("定时器中断timer interruption \n");
                break;
            case 11:
                printf("Machine模式下的外部中断external interruption \n");
                externalInterruptHandler();
                break;
            default:
                printf("暂未处理或是未知的中断类型 \n");
                break;
        }
    } else {
        printf("发生异常，异常码为：%d \n",causeCode);
        panic("啥也没处理 \n");
        //returnPc += 4;
    }
    return returnPc;
}








