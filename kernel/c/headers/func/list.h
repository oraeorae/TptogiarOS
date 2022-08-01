//
// Created by root on 2022.08.01.
//

#ifndef TPTOGIAROS_LIST_H
#define TPTOGIAROS_LIST_H


#include "../types.h"



struct ListEntry{
    struct ListEntry* prev;
    static ListEntry* next;
};


static inline void listInit(ListEntry* elm) __attribute__((always_inline));
static inline void listAppend(ListEntry* listElm,ListEntry* elm) __attribute__((always_inline));
static inline void listaddBefore(ListEntry* listElm,ListEntry* elm) __attribute__((always_inline));
static inline void listaddAfter(ListEntry* listElm,ListEntry* elm) __attribute__((always_inline));
static inline void listDel(ListEntry* listElm) __attribute__((always_inline));
static inline void listDelInit(ListEntry* listElm) __attribute__((always_inline));
static inline bool listEmpty(ListEntry* list) __attribute__((always_inline));
static inline ListEntry* listNext(ListEntry* listElm) __attribute__((always_inline));
static inline ListEntry* listPrev(ListEntry* listElm) __attribute__((always_inline));
static inline void listInsert(ListEntry* elm,ListEntry* prev,ListEntry* next) __attribute__((always_inline));
static inline void listPickOff(ListEntry* prev,ListEntry next) __attribute__((always_inline));

















#endif //TPTOGIAROS_LIST_H
