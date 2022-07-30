#include "../user-api/syscall.h"


.global getHartId

getHartId:
    li a7, SYS_getHartId
    ecall
    ret