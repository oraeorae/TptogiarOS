#include <sbi.h>
#include <console.h>

/* kbd_intr - try to feed input characters from keyboard */
void kbd_intr(void) {}

/* serial_intr - try to feed input characters from serial port */
void serial_intr(void) {}

// 初始化控制台
void consoleInit(void) {}

void cons_putc(int c) { sbi_console_putchar((unsigned char)c); }

int cons_getc(void) {
    int c = 0;
    c = sbi_console_getchar();
    return c;
}
