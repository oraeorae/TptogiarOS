#include "../link.h"
#include "../type.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>


void* alloc(size_t type_size) {
    return malloc(type_size);
}

void dealloc(void* p) {
    free(p);
}





int test_example[500][500] = {
        {0},
        {},
        {1,2,3,4},
        {1,2,3,8,4},
        {1,2,3,8,100},
        {8,100},
};




void test(link_t* link, int a[500], int len) {
    static int cnt = 1;
    assert(link_length(link) == len);

    link_node_t* nodeA = link_begin(link);

    for (int i = 0; i < link_length(link); i++) {
        assert(*((int*)nodeA->data) == a[i]);
        nodeA = nodeA->next;
    }
    printf("%d pass\n", cnt);
    cnt++;
    link_clear(link);
}

void test1(link_t* link)
{
    int a = 0;
    link_node_t* n;
    link_push(link, &a);
    test(link, test_example[0], 1);
}

void test2(link_t* link)
{
    int a = 0;
    link_node_t* n;
    n = link_push(link, &a);
    link_delete(link, n);

    test(link, test_example[1], 0);
}

void test3(link_t* link)
{
    int a = 0;
    link_node_t* n;
    a = 1;
    link_push(link, &a);
    a = 2;
    link_push(link, &a);
    a = 3;
    link_push(link, &a);
    a = 4;
    link_push(link, &a);
    test(link, test_example[2], 4);
}
bool compare(const void* a, const void* b) {
    return *(int*)a == *(int*)b;
}
void test4(link_t* link)
{
    int a = 0;
    link_node_t* n;
    a = 1;
    link_push(link, &a);
    a = 2;
    link_push(link, &a);
    a = 3;
    link_push(link, &a);
    a = 4;
    link_push(link, &a);
    n = link_find(link, &a, compare);
    a = 8;
    link_insert(link, n, &a);
    test(link, test_example[3], 5);
}


void test5(link_t* link)
{
    int a = 0;
    link_node_t* n;
    a = 1;
    link_push(link, &a);
    a = 2;
    link_push(link, &a);
    a = 3;
    link_push(link, &a);
    a = 4;
    link_push(link, &a);
    n = link_find(link, &a, compare);
    a = 8;
    link_insert(link, n, &a);
    a = 100;
    link_set_element(link, n, &a);
    test(link, test_example[4], 5);
}

void test6(link_t* link)
{
    int a = 0;
    link_node_t* n;
    a = 1;
    link_push(link, &a);
    a = 2;
    link_push(link, &a);
    a = 3;
    link_push(link, &a);
    a = 4;
    link_push(link, &a);
    n = link_find(link, &a, compare);
    a = 8;
    link_insert(link, n, &a);
    a = 100;
    link_set_element(link, n, &a);

    a = 1;
    n = link_find(link, &a, compare);
    link_delete(link, n);
    a = 2;
    n = link_find(link, &a, compare);
    link_delete(link, n);
    a = 3;
    n = link_find(link, &a, compare);
    link_delete(link, n);

    test(link, test_example[5], 2);
}



int main(){
    printf("start link test... \n\n");

    int a = 0;
    link_t test_link;
    link_init_alloc_dealloc(&test_link, alloc, dealloc);
    link_construct(&test_link, sizeof(int));

    test1(&test_link);
    //test2(&test_link);
    //test3(&test_link);
    //test4(&test_link);
    //test5(&test_link);
    //test6(&test_link);

    link_destory(&test_link);


}


