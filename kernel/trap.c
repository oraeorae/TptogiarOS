//
// Created by root on 2022.07.23.
//
#include "header/os.h"

extern void trapVector(void);


void trapInit(){
    write_mtvec((reg_t)trapVector);
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
                printf("时钟中断timer interruption \n");
                break;
            case 11:
                printf("外部中断external interruption \n");
                break;
            default:
                printf("暂未处理或是未知的中断类型 \n");
                break;
        }
    } else {
        printf("发送异常，异常码为：%d \n",causeCode);
        panic("啥也没处理 \n");
        //returnPc += 4;
    }
    return returnPc;
}








