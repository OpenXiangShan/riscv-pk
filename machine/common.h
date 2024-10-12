// See LICENSE for license details.

#ifndef _COMMON_H
#define _COMMON_H

#define MEM_WRITE32(addr, value)  (*((volatile unsigned int*)(((unsigned long long)addr)))) = (value)
#define MEM_READ32(addr)  (*((volatile unsigned int*)(((unsigned long long)addr))))

#endif
