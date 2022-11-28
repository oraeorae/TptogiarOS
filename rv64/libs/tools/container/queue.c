
#include "queue.h"


void queue_construct(queue_t* queue, size_t type_size)
{
    link_construct(&queue->link, type_size);
}

void queue_init_alloc_dealloc(queue_t* queue, void* (*alloc) (size_t), void (*dealloc) (void*))
{
    link_init_alloc_dealloc(&queue->link,alloc, dealloc);
}

void queue_push(queue_t* queue, void* v)
{
    link_push(&queue->link, v);
}

void queue_pop(queue_t* queue, void* data)
{
    link_node_t* node = link_begin(&queue->link);
    type_copy(node->data, data, queue->link.type_size);
    link_delete(&queue->link, node);
}

size_t queue_length(queue_t* queue)
{
    return link_length(&queue->link);
}

void queue_destory(queue_t* queue)
{
    link_destory(&queue->link);
}

bool queue_empty(queue_t* queue)
{
    return link_empty(&queue->link);
}
