//
// Created by root on 8/3/22.
//

#ifndef TPTOGIAROS_TIMER_H
#define TPTOGIAROS_TIMER_H


#include <defs.h>

extern volatile size_t ticks;

void timerInit(void);
void timerHandler(void);




#endif //TPTOGIAROS_TIMER_H
