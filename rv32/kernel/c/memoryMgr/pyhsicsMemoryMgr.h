//
// Created by root on 2022.08.01.
//

#ifndef TPTOGIAROS_PYHSICSMEMORYMGR_H
#define TPTOGIAROS_PYHSICSMEMORYMGR_H

#include "../headers/types.h"
#include "../headers/func/list.h"




struct Page {
    int ref;
    uint64_t flags;
    unsigned int property;
    ListEntry pageLink;
};



















#endif //TPTOGIAROS_PYHSICSMEMORYMGR_H
