#ifndef TPTOGIAROS_QUEUE_H
#define TPTOGIAROS_QUEUE_H


#pragma once

#include "link.h"

typedef struct {
    link_t link;
}queue_t;



void queue_construct(queue_t* queue, size_t type_size);

void queue_init_alloc_dealloc(queue_t* queue, void* (*alloc) (size_t), void (*dealloc) (void*));

void queue_push(queue_t* queue, void* v);

void queue_pop(queue_t* queue, void* data);

size_t queue_length(queue_t* queue);

void queue_destory(queue_t* queue);

bool queue_empty(queue_t* queue);




#endif //TPTOGIAROS_QUEUE_H
