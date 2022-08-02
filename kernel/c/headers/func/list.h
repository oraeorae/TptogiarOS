//
// Created by root on 2022.08.01.
//

#ifndef TPTOGIAROS_LIST_H
#define TPTOGIAROS_LIST_H


#include "../Types.h"



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





satic inline void listInit(ListEntry* elm){
    elm->prev = elm->next =elm;
}

static inline void listAppend(ListEntry* listElm,ListEntry* elm){
    listaddAfter(listElm,elm);
}

static inline void listaddBefore(ListEntry* listElm,ListEntry* elm){
    listInsert(elm,listElm->prev,listElm);
}

static inline void listaddAfter(ListEntry* listElm,ListEntry* elm){
    listInsert(elm,listElm,listElm->next);
}

static inline void listDel(ListEntry* listElm){
   listPickOff(listElm->prev,listElm->next);
}

static inline void listDelInit(ListEntry* listElm){
    listDel(listElm);
    listInit(listElm);
}

static inline bool listEmpty(ListEntry* list){
    return list->next == list;
}

static inline ListEntry* listNext(ListEntry* listElm){
    return listElm->next;
}

static inline ListEntry* listPrev(ListEntry* listElm){
    return listElm->prev;
}

static inline void listInsert(ListEntry* elm,ListEntry* prev,ListEntry* next){
    prev->next = elm = next->prev;
    elm->prev =  prev;
    elm->next = next;
}

static inline void listPickOff(ListEntry* prev,ListEntry next){
    prev->next = next;
    next.prev = prev;
}


#endif //TPTOGIAROS_LIST_H
