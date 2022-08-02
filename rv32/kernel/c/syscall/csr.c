//
// Created by root on 2022.07.30.
//
#include "../headers/os.h"


int sys_getHartId(unsigned int* ptrHartId){

    printf("==> sys_getHartId , arg0 = 0x%x \n",ptrHartId);

    if (ptrHartId == NULL){
        return -1;
    } else {
        *ptrHartId = read_mhartid();
        return 0;
    }
}
