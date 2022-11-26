#ifndef TPTOGIAROS_LINK_H
#define TPTOGIAROS_LINK_H


#pragma once
#include "type.h"

void type_copy(void* src, void* dst, size_t type_size);

typedef struct link_node_t{
    void* data;

    struct link_node_t* next;
    struct link_node_t* prev;
}link_node_t;

link_node_t* link_node_alloc(void* value, size_t type_size, void* (*alloc) (size_t));

void link_node_dealloc(link_node_t* node, void (*dealloc) (void*));

void link_node_set_element(link_node_t* node, void* value, size_t type_size);

link_node_t* link_node_next(link_node_t* node);

link_node_t* link_node_prev(link_node_t* node);

void* link_node_data(link_node_t* node);

typedef struct {
    link_node_t* head;
    size_t len;

    size_t type_size;
    void* (*alloc) (size_t);
    void (*dealloc) (void*);
}link_t;

void link_construct(link_t* link, size_t type_size);

void link_init_alloc_dealloc(link_t* link,void* (*alloc) (size_t), void (*dealloc) (void*));

link_node_t* link_find(link_t* link, void* value, bool (*compare)(const void*, const void*));

link_node_t* link_begin(link_t* link);

link_node_t* link_end(link_t* link);

link_node_t* link_insert(link_t* link, link_node_t* node,void* v);

link_node_t* link_push(link_t* link, void* v);

void link_set_element(link_t* link, link_node_t* node, void* v);

void link_delete(link_t* link, link_node_t* node);

void link_clear(link_t* link);

void link_destory(link_t* link);

size_t link_length(link_t* link);

bool link_empty(link_t* link);





#endif //TPTOGIAROS_LINK_H
