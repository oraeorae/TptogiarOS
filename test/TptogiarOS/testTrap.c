//
// Created by root on 2022.07.24.
//
extern int printf(const char *s, ...);

void testTrap(){

    // 取00000000地址，设置
    *(int*)0x00000000 = 100;


    printf("异常处理完毕...\n");





}



