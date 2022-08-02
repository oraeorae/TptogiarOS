//
// Created by root on 2022.07.24.
//
extern int printf(const char *s, ...);

void testTrap(){

    // 取00000000地址，设置
    *(int*)0x00000000 = 100;


    printf("异常处理完毕...\n");





}

void userTaskWithTrap(void) {
    printf("Task 2 : 任务被创建！ \n");
    while (1) {
        printf("Task 2 : Running \n");
        testTrap();
        taskDelayCount(5000);
    }
}

