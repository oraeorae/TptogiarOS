#ifndef __KERN_DEBUG_MONITOR_H__
#define __KERN_DEBUG_MONITOR_H__

#include <trap.h>

void kmonitor(struct TrapFrame *tf);

int mon_help(int argc, char **argv, struct TrapFrame *tf);
int mon_kerninfo(int argc, char **argv, struct TrapFrame *tf);
int mon_backtrace(int argc, char **argv, struct TrapFrame *tf);

#endif /* !__KERN_DEBUG_MONITOR_H__ */

