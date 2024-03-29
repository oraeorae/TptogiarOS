#include <kdebug.h>
#include <kmonitor.h>
#include <mmu.h>
#include <sbi.h>
#include <stdio.h>
#include <string.h>
#include <trap.h>



struct command {
    const char *name;
    const char *desc;
    // return -1 to force monitor to exit
    int (*func)(int argc, char **argv, struct trapframe *tf);
};

static struct command commands[] = {
    {"help", "Display this list of commands.", mon_help},
    {"kerninfo", "Display information about the kernel.", mon_kerninfo},
    {"backtrace", "Print backtrace of stack frame.", mon_backtrace},
};


bool is_kernel_panic(void);

#define NCOMMANDS (sizeof(commands) / sizeof(struct command))



#define MAXARGS 16
#define WHITESPACE " \t\n\r"


static int parse(char *buf, char **argv) {
    int argc = 0;
    while (1) {
        // find global whitespace
        while (*buf != '\0' && strchr(WHITESPACE, *buf) != NULL) {
            *buf++ = '\0';
        }
        if (*buf == '\0') {
            break;
        }

        // save and scan past next arg
        if (argc == MAXARGS - 1) {
            cprintf("Too many arguments (max %d).\n", MAXARGS);
        }
        argv[argc++] = buf;
        while (*buf != '\0' && strchr(WHITESPACE, *buf) == NULL) {
            buf++;
        }
    }
    return argc;
}


static int runcmd(char *buf, struct trapframe *tf) {
    char *argv[MAXARGS];
    int argc = parse(buf, argv);
    if (argc == 0) {
        return 0;
    }
    int i;
    for (i = 0; i < NCOMMANDS; i++) {
        if (strcmp(commands[i].name, argv[0]) == 0) {
            return commands[i].func(argc - 1, argv + 1, tf);
        }
    }
    cprintf("Unknown command '%s'\n", argv[0]);
    return 0;
}


void kmonitor(struct trapframe *tf) {
    cprintf("Welcome to the kernel debug monitor!!\n");
    cprintf("Type 'help' for a list of commands.\n");

    if (tf != NULL) {
        print_trapframe(tf);
    }

    char *buf;
    sbi_shutdown();
    while (1) {
        if ((buf = readline("K> ")) != NULL) {
            if (runcmd(buf, tf) < 0) {
                break;
            }
        }
    }
}


int mon_help(int argc, char **argv, struct trapframe *tf) {
    int i;
    for (i = 0; i < NCOMMANDS; i++) {
        cprintf("%s - %s\n", commands[i].name, commands[i].desc);
    }
    return 0;
}


int mon_kerninfo(int argc, char **argv, struct trapframe *tf) {
    print_kerninfo();
    return 0;
}


int mon_backtrace(int argc, char **argv, struct trapframe *tf) {
    print_stackframe();
    return 0;
}
