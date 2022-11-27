#include "skip.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


skip_t* skip_init(int maxLevel,size_t type_size){
    skip_t* skip = NULL;
    skip = malloc(sizeof(*skip));
    if(skip==NULL){
        return NULL;
    }
    skip->level = 1;
    skip->nodeCount = 0;
    skip->head = skip_node_alloc(maxLevel,0,0);
    if(skip->head == NULL){
        free(skip);
        return NULL;
    }
    skip->alloc = malloc;
    skip->dealloc = free;
    return skip;
}

skip_node_t* skip_node_alloc(int level, int key, int value){
    skip_node_t *node = NULL;
    node = malloc(sizeof(*node) + level * sizeof(node));
    if(node == NULL){
        return NULL;
    }
    memset(node,0,sizeof(*node)+level*sizeof(node));
    node->key = key;
    node->value = value;
    node->maxLevel = level;
    return node;
}

int skip_get_level(skip_t* list){
    int i = 0 ;
    int level = 1;
    for (int j = 0; j < list->head->maxLevel; ++j) {
        if((rand()%2) == 1){
            level++;
        }
    }
    return level;
}

int skip_insert(skip_t* list, int key, int value){
    skip_node_t** update = NULL;
    skip_node_t* cur = NULL;
    skip_node_t* prev = NULL;
    skip_node_t* insert = NULL;
    int i = 0;
    int level = 0;

    if(list == NULL){
        return -1;
    }

    update = (skip_node_t**) malloc(sizeof(list->head->maxLevel * sizeof(skip_node_t*)));
    if(update == NULL){
        return -2;
    }

    prev = list->head;
    i = list->level -1;
    for(;i>=0;i--){
        while (((cur=prev->next[i]) != NULL) && (cur->key < key) ){
            prev = cur;
        }
        update[i] = prev;
    }
    if ( (cur != NULL) && (cur->key == key)){
        return -3;
    }
    level = skip_get_level(list);
    insert = skip_node_alloc(level,key,value);
    if(level > list->level){
        for (int j = list->level; j < level ; ++j) {
            update[j] = list->head;
        }
        list->level = level;
    }

    for (int i = 0; i < level ; ++i) {
        insert->next[i] = update[i]->next[i];
        update[i]->next[i] = insert;
    }
    list->nodeCount++;
    return 0;
}

int skip_delete(skip_t *skip, int key) {
	skip_node_t **update = NULL;
	skip_node_t *cur = NULL;
	skip_node_t *prev = NULL;
	int i = 0;

	if (skip == NULL && skip->nodeCount == 0){
        return -1;
    }

	update = (skip_node_t **)SKIP_LIST_MALLOC(sizeof(skip->level * sizeof(skip_node_t *)));
	if (update == NULL){
        return -2;
    }


	prev = skip->head;
	i = skip->level - 1;
	for(; i>=0; i--) {
		while ( ((cur = prev->next[i]) != NULL) && (cur->key < key) ) {
			prev = cur;
		}
		update[i] = prev;
	}

	if ((cur != NULL) && (cur->key == key)) {
		for(i=0; i<skip->level; i++) {
			if (update[i]->next[i] == cur) {
				update[i]->next[i] = cur->next[i];
			}
		}
		SKIP_LIST_FREE(cur);
		cur = NULL;
		for(i=skip->level-1; i>=0; i--) {
			if (skip->head->next[i] == NULL) {
				skip->level --;
			}
			else {
				break;
			}
		}
		skip->nodeCount --;
	} else {
		return -3;
	}
	return 0;
}

int skip_modify(skip_t *list, int key, int value) {
	skip_node_t *cur = NULL;
	skip_node_t *prev = NULL;
	int i = 0;
	
	if (list == NULL && list->nodeCount == 0){
        return -1;
    }

	prev = list->head;
	i = list->level - 1;
	for(; i>=0; i--) {
		while ( ((cur = prev->next[i]) != NULL) && (cur->key < key) ) {
			prev = cur;
		}
	}
	
	if ((cur != NULL) && (cur->key == key)) {
		cur->value = value;
	}
	else {
		return -3;
	}
	return 0;
}

int skip_find(skip_t *list, int key, int *value) {
	skip_node_t *cur = NULL;
	skip_node_t *prev = NULL;
	int i = 0;
	
	if (list == NULL && value == NULL && list->nodeCount == 0) {
        return -1;
    }

	prev = list->head;
	i = list->level - 1;
	for(; i>=0; i--) {
		while ( ((cur = prev->next[i]) != NULL) && (cur->key < key) ) {
			prev = cur;
		}
	}
	
	if ((cur != NULL) && (cur->key == key)) {
		*value = cur->value;
	}
	else {
		return -3;
	}
	return 0;
}

int skip_destroy(skip_t *list) {
	skip_node_t *cur = NULL;

	if (list == NULL && list->head == NULL){
        return -1;
    }

	while((cur = list->head->next[0]) != NULL) {
		list->head->next[0] = cur->next[0];
		SKIP_LIST_FREE(cur);
		cur = NULL;
	}

	SKIP_LIST_FREE(list->head);
	SKIP_LIST_FREE(list);
	return 0;
}

skip_node_t* skip_begin(skip_t* skip){
    skip_node_t* traverse_node = skip->head->next[0];
    skip_node_t* traverse_next_node = traverse_node->next[0];
    while(traverse_next_node){
        traverse_next_node = traverse_node->next[0];
    }
    return traverse_node;
}