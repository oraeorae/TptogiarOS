//
// Created by root on 2022.07.29.
//
#include "headers/os.h"

struct SpinLock{
    int state;
};


struct SpinLock* getSpinLock(){
    struct SpinLock lock = {.state = 1};
    return &lock;
}

int spinLock(struct SpinLock* lock){
    //printf(" before while \n");
    //while (__sync_lock_test_and_set(&lock->state,1) != 0){
    //}
    //printf(" after while \n ");
    //return 1;
    write_mstatus(read_mstatus() & ~MSTATUS_MIE);
    return 0;
}


int spinUnlock(struct SpinLock* lock){
    //lock->state = 0;
    write_mstatus(read_mstatus() | MSTATUS_MIE);
}