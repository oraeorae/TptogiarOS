#include "link.h"


void type_copy(void* src, void* dst, size_t type_size)
{
    char* c_dst = (char*)dst;
    char* c_src = (char*)src;
    while (type_size--) {
        *c_dst = *c_src;
        c_dst++;
        c_src++;
    }
}

void link_init_alloc_dealloc(link_t* link,void* (*alloc) (size_t), void (*dealloc) (void*))
{
    link->alloc = alloc;
    link->dealloc = dealloc;
}

link_node_t* link_node_alloc(void* value, size_t type_size, void* (*alloc) (size_t))
{
    void* data = alloc(type_size);
    link_node_t* new_node = (link_node_t*)alloc(sizeof(link_node_t));
    new_node->data = data;
    // copy the value from frame to node.data
    type_copy(value, new_node->data, type_size);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void link_node_dealloc(link_node_t* node, void (*dealloc) (void*))
{
    dealloc(node->data);
    dealloc(node);
}


void link_node_set_element(link_node_t* node, void* value, size_t type_size)
{
    type_copy(value, node->data, type_size);
}

link_node_t* link_node_next(link_node_t* node)
{
    return node->next;
}

link_node_t* link_node_prev(link_node_t* node)
{
    return node->prev;
}

void* link_node_data(link_node_t* node)
{
    return node->data;
}

//  init link_t struct
void link_construct(link_t* link, size_t type_size)
{
    int value = 0;
    link_node_t* new_node = link_node_alloc(&value, type_size, link->alloc);
    link->head = new_node;
    link->head->next = NULL;
    link->len = 0;
    link->type_size = type_size;
}


link_node_t* link_find(link_t* link, void* value, bool (*compare)(const void*, const void*))
{
    link_node_t* traverse_node = link->head->next;
    link_node_t* traverse_next_node = NULL;
    for (int i = 0; i < link->len; i++) {
        traverse_next_node = traverse_node->next;
        if (compare(traverse_node->data, value)) {
            return traverse_node;
        }
        traverse_node = traverse_next_node;
    }
    return NULL;
}

link_node_t* link_begin(link_t* link)
{
    return link->head->next;
}

link_node_t* link_end(link_t* link)
{
    link_node_t* begin = link_begin(link);
    if (begin == NULL) {
        return NULL;
    }
    return begin->prev;
}

// insert before node
link_node_t* link_insert(link_t* link, link_node_t* node, void* value)
{
    link_node_t* new_node = link_node_alloc(value, link->type_size, link->alloc);
    if (node == link->head->next) {
        link->head->next = new_node;
    }

    link_node_t* prev_node = node->prev;

    prev_node->next = new_node;
    node->prev = new_node;
    new_node->next = node;
    new_node->prev = prev_node;
    link->len++;
    return new_node;
}

link_node_t* link_push(link_t* link, void* value)
{
    link_node_t* new_node = link_node_alloc(value, link->type_size, link->alloc);
    link->len++;
    // only one node
    if (link->head->next == NULL) {
        new_node->next = new_node;
        new_node->prev = new_node;
        link->head->next = new_node;
        return new_node;
    }
    // push into link head
    link_node_t* head = link->head->next;
    link_node_t* tail = head->prev;

    head->prev = new_node;
    tail->next = new_node;
    new_node->prev = tail;
    new_node->next = head;
    return new_node;
}

void link_set_element(link_t* link, link_node_t* node, void* value)
{
    link_node_set_element(node, value, link->type_size);
}


void link_delete(link_t* link, link_node_t* node)
{
    if (link->head->next == node) {
        if (node->next == node) {
            link->head->next = NULL;
        }
        else{
            link->head->next = node->next;
        }
    }
    link_node_t* prev_node = node->prev;
    prev_node->next = node->next;
    prev_node->next->prev = prev_node;

    link_node_dealloc(node, link->dealloc);
    link->len--;
}

void link_clear(link_t* link)
{
    link_node_t* traverse_node = link->head->next;
    link_node_t* traverse_next_node = NULL;
    for (int i = 0; i < link->len; i++) {
        traverse_next_node = traverse_node->next;
        link_node_dealloc(traverse_node, link->dealloc);
        traverse_node = traverse_next_node;
    }
    link->len = 0;
    link->head->next = NULL;
}
void link_destory(link_t* link)
{
    link_clear(link);
    link_node_dealloc(link->head, link->dealloc);
}


size_t link_length(link_t* link)
{
    return link->len;
}

bool link_empty(link_t* link)
{
    return link->len == 0;
}
