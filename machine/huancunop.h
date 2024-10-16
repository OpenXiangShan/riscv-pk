#ifndef _HUANCUNOP_H
#define _HUANCUNOP_H
#include "common.h"

#define CACHE_CTRL_BASE 0x39000100
#define CACHE_RDY_REG 0x39000180
#define CACHE_CMD_BASE 0x39000200

#define CMD_CMO_INV (0 + 16)
#define CMD_CMO_CLEAN (1 + 16)
#define CMD_CMO_FLUSH (2 + 16)
#define CTRL_TAG_OFFSET 0
#define CTRL_SET_OFFSET 8

#define CACHE_SPECIFICATION_2M

#ifdef CACHE_SPECIFICATION_8M
#define SET_SIZE 8192 
#define SET_LEN 13      // log2(SET_SIZE)
#define OFFSET_LEN 6
#endif

#ifdef CACHE_SPECIFICATION_2M
#define SET_SIZE 4096 
#define SET_LEN 12      // log2(SET_SIZE)
#define OFFSET_LEN 6
#endif

#ifdef CACHE_SPECIFICATION_1M
#define SET_SIZE 2048 
#define SET_LEN 11      // log2(SET_SIZE)
#define OFFSET_LEN 6
#endif

#define CACHE_LINE_SIZE_BIT 512
#define CACHE_LINE_SIZE_BYTE (CACHE_LINE_SIZE_BIT / 8)

void wait(int);
void wait_for_ready();

inline uint64_t is_ready() {
  return *((uint64_t*)CACHE_RDY_REG);
}

inline volatile uint64_t get_tag(uint64_t paddr) {
  return (paddr >> OFFSET_LEN) >> SET_LEN;
}

inline volatile uint64_t get_set(uint64_t paddr) {
  return (paddr >> OFFSET_LEN) & (SET_SIZE-1);
}

// regular flow to issue a CMO
void make_invalid(uint64_t);
void make_clean(uint64_t);
void make_flush(uint64_t);

// operate on a memory region
void make_region_invalid(uint64_t, uint64_t);
void make_region_clean(uint64_t, uint64_t);
void make_region_flush(uint64_t, uint64_t);

#endif
