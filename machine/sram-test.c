#include "sram.h"
#include "common.h"
#include "mtrap.h"

#define SRAM_ADDR0           0x01FFF800000
#define SRAM_ADDR1           0x01FFFa00000

typedef unsigned int u32;

void sram_init_buf(unsigned  long long addr, unsigned int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
         MEM_WRITE32(addr + i * 4, i);
    }
}

int sram_data_chk(void)
{
// check data
    int i; 
    unsigned  int value;
    for (i=0;i<64;i=i+1) 
    {
        value = MEM_READ32(SRAM_ADDR0 + i*4);
        if (value != i) 
        {
            printm("\n sram0 chk Error.should be %0x but %0x. addr=%0x",i,value, SRAM_ADDR0 + i*4);
            return 1;
        }
    }
    for (i=0;i<64;i=i+1) 
    {
        value = MEM_READ32(SRAM_ADDR1 + i*4);
        if (value != i) 
        {
            printm("\n sram1 chk Error.should be %0x but %0x. addr=%0x",i,value, SRAM_ADDR1 + i*4);
            return 1;
        }
    }
    return 0;
}

void sram_test(void)
{
    unsigned int err_flag=0;
    unsigned int tmp;
    unsigned int testval = 0;

    //Initialize source data for channel 1
    sram_init_buf(SRAM_ADDR0,64);
    __asm__ volatile ("fence");

    //Initialize source data for channel 2
    sram_init_buf(SRAM_ADDR1, 64); 

    __asm__ volatile ("fence");
    err_flag  = sram_data_chk();
    __asm__ volatile ("fence");
    
    if (err_flag == 0)
        printm("SRAM_ADDR0: Start SRAM Data Check Success !!!\n");
    else
        printm("SRAM_ADDR0: Start SRAM Data Check  Error\n");

    printm("SRAM: Test End !!!\n");
}


