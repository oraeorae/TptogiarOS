#include "../stack.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>


void* alloc(size_t type_size){
    return malloc(type_size);
}

void dealloc(void* p){
    free(p);
}










int main(){

    printf("start test stack ...\n");

    stack_t test_stack;

    stack_init_alloc_dealloc(&test_stack,alloc,dealloc);
    stack_construct(&test_stack,sizeof(int));

    int value = 2;
    stack_push(&test_stack,&value);
    value = 5;
    stack_push(&test_stack,&value);
    value = 2;
    stack_push(&test_stack,&value);
    value = 8;
    stack_push(&test_stack,&value);


    while (stack_length(&test_stack)){
        int res;
        stack_pop(&test_stack,&res);
        printf("%d ",res);
    }
    printf("\n");


    printf("end test stack ...\n");
    return 0;
}