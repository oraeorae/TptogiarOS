#ifndef TPTOGIAROS_SKIP_H
#define TPTOGIAROS_SKIP_H

#pragma once
#include "type.h"
#include "link.h"


#define SKIP_LIST_MALLOC(size) malloc(size);
#define SKIP_LIST_CALLOC(n, size) calloc(size);
#define SKIP_LIST_FREE(p) free(p);


typedef struct skip_node_t{
    int key;
    int value;
    int maxLevel;
    struct skip_node_t* next[];
}skip_node_t;

typedef struct skip_t{
    int level;
    int nodeCount;
    struct skip_node_t* head;

    void* (*alloc) (size_t);
    void (*dealloc) (void*);
}skip_t;


skip_t* skip_init(int maxLevel,size_t type_size);

skip_node_t* skip_node_alloc(int level, int key, int value);

int skip_get_level(skip_t* list);

int skip_insert(skip_t* list, int key, int value);

int skip_delete(skip_t *skip, int key);

int skip_modify(skip_t *list, int key, int value);

int skip_find(skip_t *list, int key, int *value);

int skip_destroy(skip_t *list);

skip_node_t* skip_begin(skip_t* skip);

//int skip_insert(struct SkipList* list,int key,int value);
//
//int skip_delete(struct SkipList* list,int key);
//
//int skip_modify(struct SkipList* list,int key,int value);
//
//int skip_search(struct SkipList* list,int key,int *value);
//
//int skip_destroy(struct SkipList* list);

#endif //TPTOGIAROS_SKIP_H
