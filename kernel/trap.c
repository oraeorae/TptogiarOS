//
// Created by root on 2022.07.23.
//
#include "headers/os.h"

extern void trapVector(void);
extern void uartInterruptHandler(void);
extern void timerHandler(void);
extern void schedule(void);

void trapInit(){
    // 设置trap处理程序入口函数
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
        plicComplete(interruptId);
    }
}


reg_t trapHandler(reg_t epc,reg_t cause){

    // 进入trap前指令的执行位置
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
                int hartId = read_mhartid();
                *(uint32_t*) CLINT_MSIP(hartId) = 0;
                schedule();
                break;
            case 7:
                printf("Mechine模式下的定时器中断timer interruption \n");
                timerHandler();
                break;
            case 11:
                // TODO Bug 只会响应一次，待修复
                printf("Machine模式下的外部中断external interruption \n");
                externalInterruptHandler();
                break;
            default:
                printf("暂未处理或是未知的中断类型 \n");
                break;
        }
    } else {
        printf("发生异常，reg_epc = %x , reg_cause = %x ,异常码为：%d \n",epc,cause,causeCode);
        panic("啥也没处理 \n");
        //returnPc += 4;
    }
    return returnPc;
}







