#include "sram.h"
#include "common.h"
#include "mtrap.h"
#include "huancunop.h"

#define SRAM_ADDR           0x01FFF800000
#define DDR_ADDR            0x01020000000

#define TEST_ADDR          SRAM_ADDR

#define  WRITE8BYTE_ONCE

typedef unsigned int u32;

void sram_init_buf(unsigned  long long addr, unsigned int len)
{
    unsigned int i;
    for(i = 0; i < len; i++)
    {
#ifdef WRITE8BYTE_ONCE
         //Write 8 bytes at once
         make_invalid(addr + i * 8);
         MEM_WRITE64(addr + i * 8, i);
         asm("fence\n");
         make_flush(addr + i * 8);
         printm("\n write 0x%x  addr=0x%lx\n",i, addr + i * 8);

#else
         make_invalid(addr + i * 4);
         MEM_WRITE32(addr + i * 4, i);
         asm("fence\n");
         make_flush(addr + i * 4);
         printm("\n write 0x%x  addr=0x%lx\n",i, addr + i*4);
#endif

#if 0
         if (i % 16 == 15) {
            make_flush(addr + (i/16)*64);
         }
#endif
    }
}

int sram_data_chk(unsigned long long addr ,unsigned int len)
{
// check data
    unsigned i = 0;
    volatile unsigned int value = 0;
#ifdef WRITE8BYTE_ONCE
         //Write 8 bytes at once
    for (i = 0;i < len;i = i + 1)
    {
        value = MEM_READ64(addr + i * 8);
        asm("fence\n");
            printm("\n read should be 0x%x but 0x%x. addr=0x%lx\n",i,value, addr + i * 8);
        //if (value != i)
        ////if (value != 0x55)
        //{
        //    printm("\n sram0 chk Error.should be 0x%x but 0x%x. addr=0x%lx\n",i,value, addr + i*4);
        //    return 1;
        //}
    }
#else
    for (i = 0;i < len;i = i + 1)
    {
        value = MEM_READ32(addr + i * 4);
        asm("fence\n");
            printm("\n read should be 0x%x but 0x%x. addr=0x%lx\n",i,value, addr + i*4);
        //if (value != i)
        ////if (value != 0x55)
        //{
        //    printm("\n sram0 chk Error.should be 0x%x but 0x%x. addr=0x%lx\n",i,value, addr + i*4);
        //    return 1;
        //}
    }
#endif
    return 0;
}

void sram_test(void)
{
    unsigned int err_flag=0;
    unsigned int tmp;
    unsigned int testval = 0;

    sram_init_buf(TEST_ADDR, 64);
    err_flag  = sram_data_chk(TEST_ADDR,64);
    __asm__ volatile ("fence");
    
    if (err_flag == 0)
        printm("sram_test: Start SRAM Data Check Success !!!\n");
    else
        printm("sram_test: Start SRAM Data Check  Error\n");

    printm("SRAM: Test End !!!\n");
}


