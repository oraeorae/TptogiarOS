#include "stack.h"


void stack_construct(stack_t* stack, size_t type_size)
{
    link_construct(&stack->link, type_size);
}

void stack_init_alloc_dealloc(stack_t* stack, void* (*alloc) (size_t), void (*dealloc) (void*))
{
    link_init_alloc_dealloc(&stack->link,alloc, dealloc);
}

void stack_push(stack_t* stack, void* v)
{
    link_push(&stack->link, v);
}

void stack_pop(stack_t* stack, void* data)
{
    link_node_t* node = link_end(&stack->link);
    type_copy(node->data, data, stack->link.type_size);
    link_delete(&stack->link, node);
}

size_t stack_length(stack_t* stack)
{
    return link_length(&stack->link);
}

void stack_destory(stack_t* stack)
{
    link_destory(&stack->link);
}


