#include "header/os.h"


extern void uart_init(void);
extern void uart_puts(char *s);


extern void schedule_init(void);
extern void schedule(void);


extern void osMain(void);

void start_kernel(void) {

    uart_init();
    uart_puts("\n\n======  Hello TptogiarOS kernel !  ======\n\n\n");

    page_init();
    page_test();


    schedule_init();

    osMain();

    schedule();

    uart_puts(" 将不会执行到这里(任务切换) \n");


    while (1) {

    }

}
