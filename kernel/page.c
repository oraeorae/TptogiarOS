#include "os.h"

// 内存起始位置
extern uint32_t TEXT_START;
extern uint32_t TEXT_END;
extern uint32_t DATA_START;
extern uint32_t DATA_END;
extern uint32_t RODATA_START;
extern uint32_t RODATA_END;
extern uint32_t BSS_START;
extern uint32_t BSS_END;
extern uint32_t HEAP_START;
extern uint32_t HEAP_SIZE;


static uint32_t _page_alloc_start_address = 0;
static uint32_t _page_alloc_end_address = 0;
static uint32_t _num_pages = 0;

// 页大小
#define PAGE_SIZE 4096
// 页掩码
#define PAGE_ORDER 12
// 为页索引预留的空间（以页为单位)
#define PAGE_INDEX_SPACE 8



// 该页被使用
#define PAGE_TOKEN (uint8_t)(1 << 0)

// 该页是连续分配的page中的最后一页
#define PAGE_LAST  (uint8_t)(1 << 1)


struct Page {
    uint8_t flags;
};

static inline void _clean_page(struct Page *page) {
    page->flags = 0;
}

static inline uint32_t _align_page(uint32_t address) {
    // 4096-1 即0000，1111，1111，1111   取非得1111，0000，0000，0000 ,
    // 相当于一轮-1，所以加上次数要么刚好在下一轮初，
    // 要么有余，所以模掉后一定在下一轮，即对齐
    uint32_t circle = (1<< PAGE_ORDER) - 1;
    uint32_t nextAddress = (address + circle) & (~circle);
    return nextAddress;
}

static inline int _is_free_page(struct Page * page){
    if (page->flags & PAGE_TOKEN){
        return 0;
    } else{
        return 1;
    }
}

static inline void _set_page_flag(struct Page * page,uint8_t flags){
    page->flags |= flags;
}

static inline int _is_last_page(struct Page * page){
    if(page->flags & PAGE_LAST){
        return 1;
    } else{
        return 0;
    }
}

void page_init() {
    _num_pages = (HEAP_SIZE / PAGE_SIZE) - PAGE_INDEX_SPACE;

    printf("HEAP_START = %x , HEAP_SIZE = %x , num of pages = %d \n", HEAP_START, HEAP_SIZE, _num_pages);

    struct Page *pagePointer = (struct Page *) HEAP_START;
    for (int i = 0; i < _num_pages; ++i) {
        _clean_page(pagePointer);
        pagePointer++;
    }

    _page_alloc_start_address = _align_page(HEAP_START + PAGE_INDEX_SPACE * PAGE_SIZE);
    _page_alloc_end_address = _page_alloc_start_address + (PAGE_SIZE * _num_pages);

    printf("Text: 0x%x --> 0x%x \n",TEXT_START,TEXT_END);
    printf("RODATA: 0x%x --> 0x%x \n",RODATA_START,RODATA_END);
    printf("DATA: 0x%x --> 0x%x \n",DATA_START,DATA_END);
    printf("BSS: 0x%x --> 0x%x \n",BSS_START,BSS_END);
    printf("HEAP: 0x%x --> 0x%x \n",_page_alloc_start_address,_page_alloc_end_address);

}


void * page_alloc(int pageCount){
    int foundPageCount = 0;
    struct Page *pagePointer = (struct Page *)HEAP_START;
    for (int i = 0; i < (_num_pages - pageCount); ++i) {
        if(_is_free_page(pagePointer)){
            foundPageCount =1;
            struct Page * pagePointer2Find = pagePointer;
            for (int j = 0; j < (i + pageCount); ++j) {
                if (! _is_free_page(pagePointer2Find)){
                    foundPageCount = 0;
                    break;
                }
                pagePointer2Find++;
            }

            if (foundPageCount){
                struct Page *pagePointer2Take = pagePointer;
                for (int j = i; j < (i + pageCount); ++j) {
                    _set_page_flag(pagePointer2Take,PAGE_TOKEN);
                    pagePointer2Take++;
                }
                pagePointer2Take--;
                _set_page_flag(pagePointer2Take,PAGE_LAST);
                return (void *)(_page_alloc_start_address +i*PAGE_SIZE);
            }
        }
        pagePointer++;
    }
    return NULL;
}


void free_page(void * pointer){
    if (!pointer || (uint32_t)pointer >= _page_alloc_end_address){
        return;
    }
    struct Page * page = (struct Page *)HEAP_START;
    page += ((uint32_t)pointer - _page_alloc_start_address)/PAGE_SIZE;
    while (! _is_free_page(page)){
        if (_is_last_page(page)){
            _clean_page(page);
            break;
        } else{
            _clean_page(page);
            page++;
        }
    }

}


void page_test(){

    free_page((void*)_page_alloc_start_address);

    void* p = page_alloc(1);
    printf("pageAllocCount = %d, curPoint = 0x%x \n",1,p);

    void* p2 = page_alloc(10);
    printf("pageAllocCount = %d, curPoint = 0x%x \n",10,p2);


    void* p3 = page_alloc(4);
    printf("pageAllocCount = %d, curPoint = 0x%x \n",4,p3);

     p = page_alloc(1);
    printf("pageAllocCount = %d, curPoint = 0x%x \n",1,p);

     p2 = page_alloc(10);
    printf("pageAllocCount = %d, curPoint = 0x%x \n",10,p2);
    free_page(p2);

     p3 = page_alloc(4);
    printf("pageAllocCount = %d, curPoint = 0x%x \n",4,p3);

}


