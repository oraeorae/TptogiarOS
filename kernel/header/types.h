#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// rv32的寄存器是32位，定义该32位类型用以表征一个寄存器
typedef uint32_t reg_t;

#endif /* __TYPES_H__ */