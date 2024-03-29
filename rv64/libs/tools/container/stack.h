#ifndef TPTOGIAROS_STACK_H
#define TPTOGIAROS_STACK_H

#pragma once

#include "link.h"

typedef struct {
    link_t link;
}stack_t;



void stack_construct(stack_t* stack, size_t type_size);

void stack_init_alloc_dealloc(stack_t* stack, void* (*alloc) (size_t), void (*dealloc) (void*));

void stack_push(stack_t* stack, void* v);

void stack_pop(stack_t* stack, void* data);

size_t stack_length(stack_t* stack);

void stack_destory(stack_t* stack);

bool stack_empty(stack_t* stack);







#endif //TPTOGIAROS_STACK_H
