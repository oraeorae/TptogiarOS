//
// Created by root on 2022.07.23.
//

void page_test() {

    //free_page((void*)_page_alloc_start_address);

    void *p = page_alloc(1);
    printf("pageAllocCount = %d, curPoint = 0x%x \n", 1, p);

    void *p2 = page_alloc(10);
    printf("pageAllocCount = %d, curPoint = 0x%x \n", 10, p2);


    void *p3 = page_alloc(4);
    printf("pageAllocCount = %d, curPoint = 0x%x \n", 4, p3);

    p = page_alloc(1);
    printf("pageAllocCount = %d, curPoint = 0x%x \n", 1, p);

    p2 = page_alloc(10);
    printf("pageAllocCount = %d, curPoint = 0x%x \n", 10, p2);
    free_page(p2);

    p3 = page_alloc(4);
    printf("pageAllocCount = %d, curPoint = 0x%x \n", 4, p3);

}