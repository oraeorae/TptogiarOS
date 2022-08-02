#include "../user-api/Syscall.h"


.global getHartId

getHartId:
    li a7, SYS_getHartId
    ecall
    ret