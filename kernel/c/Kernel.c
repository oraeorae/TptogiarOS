#include "headers/Os.h"


extern void uartInit(void);
extern void uart_puts(char *s);


extern void schedule_init(void);
extern void schedule(void);


extern void osMain(void);

extern void trapInit(void);

extern void plicInit(void);

extern void timerInit(void);

void start_kernel(void) {

    uartInit();
    uart_puts("\n\n======  Hello TptogiarOS kernel !  ======\n\n\n");

    pageInit();
    pageTest();

    trapInit();

    plicInit();

    timerInit();

    schedule_init();

    osMain();

    schedule();

    uart_puts(" 将不会执行到这里(任务切换) \n");


    while (1) {

    }

}
