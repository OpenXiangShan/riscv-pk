// See LICENSE for license details.

#ifndef _COMMON_H
#define _COMMON_H
#include <stdint.h>
#include "mtrap.h"

#define MEM_WRITE32(addr, value)  (*((volatile unsigned int*)(((unsigned long long)addr)))) = (value)
#define MEM_READ32(addr)  (*((volatile unsigned int*)(((unsigned long long)addr))))

#define MEM_WRITE64(addr, value)  (*((volatile unsigned long *)(((unsigned long long)addr)))) = (value)
#define MEM_READ64(addr)  (*((volatile unsigned long*)(((unsigned long long)addr))))

#endif
