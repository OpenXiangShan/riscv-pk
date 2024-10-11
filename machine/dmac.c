#include "dmac.h"
#include "mtrap.h"
//#define set_bit1(in,pos) (in)=(in|(1<<pos))
//#define set_bit0(in,pos) (in)=(in&(~(1<<pos)))
#define CH1_SRCADDR_BASE    0x10000A0000
#define CH1_DSTADDR_BASE    0x10000B0000
#define CH2_SRCADDR_BASE    0x10000C0000
#define CH2_DSTADDR_BASE    0x10000D0000

#define CACHE_LINE_SIZE         (64)

#define L1I_CACHE_SIZE          (64*KiB)
#define L1I_CACHE_WAY           (4)

#define L1D_CACHE_SIZE          (64*KiB)
#define L1D_CACHE_WAY           (4)

#define L2_CACHE_SIZE           (256*KiB)
#define L2_CACHE_WAY            (8)

#define L3_CACHE_SIZE           (4*MiB)
#define L3_CACHE_WAY            (8)
#define L3_SET_SIZE             (L3_CACHE_SIZE / L3_CACHE_WAY)
#define L3_SET_STRIDE           (L3_SET_SIZE)


typedef unsigned int u32;

void dmac_init_buf(unsigned  long long addr, unsigned int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
         MEM_WRITE32(addr + i * 4, i);
    }
}

void dmac_ch1_single_transfer(u32 type, unsigned long long src_hs, unsigned long long des_hs, \
        unsigned long long src_addr, unsigned long long des_addr, u32 blockTS, u32 src_addr_inc, \
        u32 des_addr_inc, u32 src_width, u32 des_width, \
        u32 src_burstsize, u32 des_burstsize)
{
    unsigned int tmp;
    unsigned int ch1_cfg;
    unsigned int ch1_cfg_high;
    unsigned int ch1_ctl;

    // enable dmac_axi0
    REG_WRITE(DMAC_AXI0_COMMON_CFG, 0x1);

    // check dmac reset complete
    // ???to do set 0x1 to reset
    tmp = REG_READ(DMAC_AXI0_COMMON_RST_REG);
    while ((tmp & 0x1) != 0x0) {
        tmp = REG_READ(DMAC_AXI0_COMMON_RST_REG);
    }

    // check CH1 is idle
    tmp = REG_READ(DMAC_AXI0_COMMON_CH_EN);
    while ((tmp & 0x1) != 0x0) {
        tmp = REG_READ(DMAC_AXI0_COMMON_CH_EN);
    }

    /* CHANNEL_CFG */
    ch1_cfg = REG_READ(DMAC_AXI0_CH1_CFG);
    ch1_cfg_high = REG_READ(DMAC_AXI0_CH1_CFG + 0x4);

    // multi-block type
    ch1_cfg = (ch1_cfg & 0xfffffffc) | (DWAXIDMAC_MBLK_TYPE_CONTIGUOUS << CH_CFG_L_SRC_MULTBLK_TYPE_POS);  // src multi-block type -> contiguous
    ch1_cfg = (ch1_cfg & 0xfffffff3) | (DWAXIDMAC_MBLK_TYPE_CONTIGUOUS << CH_CFG_L_DST_MULTBLK_TYPE_POS);  // des multi-block type -> contiguous
    REG_WRITE(DMAC_AXI0_CH1_CFG, ch1_cfg);

    // transfer type and flow control 
    ch1_cfg_high = (ch1_cfg_high & 0xfffffff8) | (type << CH_CFG_H_TT_FC_POS); //MEM_TO_MEM_DMAC,dmac is flow control

    // hardware handshake select
    ch1_cfg_high = (ch1_cfg_high & 0xffffffe7) | (DWAXIDMAC_HS_SEL_HW << CH_CFG_H_HS_SEL_SRC_POS); // src hw handshake
    ch1_cfg_high = (ch1_cfg_high & 0xffffffef) | (DWAXIDMAC_HS_SEL_HW << CH_CFG_H_HS_SEL_DST_POS); // des sw handshake

    // handshake polarity
    ch1_cfg_high = (ch1_cfg_high & 0xffffffdf) | (0x0 << 5); // src hw handshake high active
    ch1_cfg_high = (ch1_cfg_high & 0xffffffbf) | (0x0 << 6); // des hw handshake high active

    // hw handshake interface
    ch1_cfg_high = (ch1_cfg_high & 0xffffff7f) | (src_hs << 7); // src hw interface 1
    ch1_cfg_high = (ch1_cfg_high & 0xffffefff) | (des_hs << 12); // des hw interface 1

    // channel priority
    ch1_cfg_high = (ch1_cfg_high & 0xfff1ffff) | (0x7 << CH_CFG_H_PRIORITY_POS); // the highest priority
    REG_WRITE(DMAC_AXI0_CH1_CFG + 0x4, ch1_cfg_high);

    /* CHANNEL_SRC_ADDR */
    REG_WRITE64(DMAC_AXI0_CH1_SAR, src_addr); // src address -> 0x0

    /* CHANNEL_DES_ADDR */
    REG_WRITE64(DMAC_AXI0_CH1_DAR, des_addr); // des address -> 0x1f0000

    /* TRANSFER_BLOCK_SIZE */
    REG_WRITE(DMAC_AXI0_CH1_BLOCK_TS, blockTS); // block size 14*32bit = 56 bytes

    /* CHANNEL_CTRL */
    ch1_ctl = REG_READ(DMAC_AXI0_CH1_CTL);
    //ch1_ctl_high = REG_READ(DMAC_AXI0_CH1_CTL + 0x4);

   
    // address increment
    ch1_ctl = (ch1_ctl & 0xffffffef) | (src_addr_inc << CH_CTL_L_SRC_INC_POS); // src address increment
    ch1_ctl = (ch1_ctl & 0xffffffbf) | (des_addr_inc << CH_CTL_L_DST_INC_POS); // des address increment

    // transfer width
    ch1_ctl = (ch1_ctl & 0xfffff8ff) | (src_width << CH_CTL_L_SRC_WIDTH_POS); // src transfer width 32bit
    ch1_ctl = (ch1_ctl & 0xffffc7ff) | (des_width << CH_CTL_L_DST_WIDTH_POS); // des transfer width 32bit


    // burst transanction size
    ch1_ctl = (ch1_ctl & 0xfffc3fff) | (src_burstsize << CH_CTL_L_SRC_MSIZE_POS); // src 1 data item
    ch1_ctl = (ch1_ctl & 0xffc3ffff) | (des_burstsize << CH_CTL_L_DST_MSIZE_POS); // des 1 data item

    REG_WRITE(DMAC_AXI0_CH1_CTL, ch1_ctl);

    /* CHANNEL_ENABLE */
    //REG_WRITE(DMAC_AXI0_COMMON_CH_EN, tmp | 0x101);
    REG_WRITE(DMAC_AXI0_COMMON_CH_EN, tmp | 0x1 << DMAC_CHAN_EN_WE_SHIFT | 0x1 << DMAC_CHAN_EN_SHIFT);
}

void dmac_ch2_single_transfer(u32 type, unsigned long long src_hs, unsigned long long des_hs, \
            unsigned long long src_addr, unsigned long long des_addr, u32 blockTS, \
            u32 src_addr_inc, u32 des_addr_inc, u32 src_width, \
            u32 des_width, u32 src_burstsize, u32 des_burstsize)
{
    unsigned int tmp;
    unsigned int ch2_cfg;
    unsigned int ch2_cfg_high;
    unsigned int ch2_ctl;

    // enable dmac_axi0
    REG_WRITE(DMAC_AXI0_COMMON_CFG, 0x1);

// check dmac reset complete
    // ???to do set 0x1 to reset
    tmp = REG_READ(DMAC_AXI0_COMMON_RST_REG);
    while ((tmp & 0x1) != 0x0) {
        tmp = REG_READ(DMAC_AXI0_COMMON_RST_REG);
    }

// check CH2 is idle
    tmp = REG_READ(DMAC_AXI0_COMMON_CH_EN);
    while ((tmp & 0x2) != 0x0) {
        tmp = REG_READ(DMAC_AXI0_COMMON_CH_EN);
    }

    /* CHANNEL_CFG */
    ch2_cfg = REG_READ(DMAC_AXI0_CH2_CFG);
    ch2_cfg_high = REG_READ(DMAC_AXI0_CH2_CFG + 0x4);
    
    // multi-block type
    ch2_cfg = (ch2_cfg & 0xfffffffc) | (DWAXIDMAC_MBLK_TYPE_CONTIGUOUS << CH_CFG_L_SRC_MULTBLK_TYPE_POS);  // src multi-block type -> contiguous
    ch2_cfg = (ch2_cfg & 0xfffffff3) | (DWAXIDMAC_MBLK_TYPE_CONTIGUOUS << CH_CFG_L_DST_MULTBLK_TYPE_POS);  // des multi-block type -> contiguous
    REG_WRITE(DMAC_AXI0_CH2_CFG, ch2_cfg);

    // transfer type and flow control 
    ch2_cfg_high = (ch2_cfg_high & 0xfffffff8) | (type << CH_CFG_H_TT_FC_POS); // MEM_TO_MEM_DMAC, dmac is flow control

    // hardware handshake select
    ch2_cfg_high = (ch2_cfg_high & 0xffffffe7) | (DWAXIDMAC_HS_SEL_HW << CH_CFG_H_HS_SEL_SRC_POS); // src hw handshake
    ch2_cfg_high = (ch2_cfg_high & 0xffffffef) | (DWAXIDMAC_HS_SEL_HW << CH_CFG_H_HS_SEL_DST_POS); // des sw handshake

    // handshake polarity
    ch2_cfg_high = (ch2_cfg_high & 0xffffffdf) | (0x0 << 5); // src hw handshake high active
    ch2_cfg_high = (ch2_cfg_high & 0xffffffbf) | (0x0 << 6); // des hw handshake high active
    // hw handshake interface
    ch2_cfg_high = (ch2_cfg_high & 0xffffff7f) | (src_hs << 7); // src hw interface 1
    ch2_cfg_high = (ch2_cfg_high & 0xffffefff) | (des_hs << 12); // des hw interface 1
    // channel priority
    ch2_cfg_high = (ch2_cfg_high & 0xfff1ffff) | (0x7 << CH_CFG_H_PRIORITY_POS); // the highest priority
    REG_WRITE(DMAC_AXI0_CH2_CFG + 0x4, ch2_cfg_high);
    
    /* CHANNEL_SRC_ADDR */
    REG_WRITE64(DMAC_AXI0_CH2_SAR, src_addr); // src address -> 0x0
    /* CHANNEL_DES_ADDR */
    REG_WRITE64(DMAC_AXI0_CH2_DAR, des_addr); // des address -> 0x1f0000
    
    /* TRANSFER_BLOCK_SIZE */
    REG_WRITE(DMAC_AXI0_CH2_BLOCK_TS, blockTS); // block size 14*32bit = 56 bytes
    
    /* CHANNEL_CTRL */
    ch2_ctl = REG_READ(DMAC_AXI0_CH2_CTL);
    //   ch2_ctl_high = REG_READ(DMAC_AXI0_CH2_CTL + 0x4);
       
    // address increment
    ch2_ctl = (ch2_ctl & 0xffffffef) | (src_addr_inc << 4); // src address increment
    ch2_ctl = (ch2_ctl & 0xffffffbf) | (des_addr_inc << 6); // des address increment
       
    // transfer width
    ch2_ctl = (ch2_ctl & 0xfffff8ff) | (src_width << CH_CTL_L_SRC_WIDTH_POS); // src transfer width 32bit
    ch2_ctl = (ch2_ctl & 0xffffc7ff) | (des_width << CH_CTL_L_DST_WIDTH_POS); // des transfer width 32bit
    
    // burst transanction size
    ch2_ctl = (ch2_ctl & 0xfffc3fff) | (src_burstsize << CH_CTL_L_SRC_MSIZE_POS); // src 1 data item
    ch2_ctl = (ch2_ctl & 0xffc3ffff) | (des_burstsize << CH_CTL_L_DST_MSIZE_POS); // des 1 data item
    
    REG_WRITE(DMAC_AXI0_CH2_CTL, ch2_ctl);
    
    /* CHANNEL_ENABLE */
    //REG_WRITE(DMAC_AXI0_COMMON_CH_EN, tmp | 0x202);
    REG_WRITE(DMAC_AXI0_COMMON_CH_EN, tmp | 0x2 << DMAC_CHAN_EN_WE_SHIFT | 0x2 << DMAC_CHAN_EN_SHIFT);
}

int dma_data_chk()
{
// check data
    int i; 
    unsigned  int value;
    for (i=0;i<64;i=i+1) 
    {
        value = MEM_READ32(CH1_DSTADDR_BASE + i*4);
        if (value != i) 
        {
            printm("\n dma chk Error.should be %0x but %0x. addr=%0x",i,value, CH1_DSTADDR_BASE + i*4);
            return 1;
        }
    }
    for (i=0;i<64;i=i+1) 
    {
        value = MEM_READ32(CH2_DSTADDR_BASE + i*4);
        if (value != i) 
        {
            printm("\n dma chk Error.should be %0x but %0x. addr=%0x",i,value, CH2_DSTADDR_BASE + i*4);
            return 1;
        }
    }
    return 0;
}

int dma_data_check(unsigned long dstmem, unsigned long srcmem, unsigned long size)
{
    unsigned  int value, i;

    for (i = 0; i < 64;i = i + 1) 
    {
        value = MEM_READ32(dstmem + i*4);
        if (value != i) 
        {
            printm("\n dma chk Error.should be %0x but %0x. addr=%0x",i,value, dstmem + i*4);
            return 1;
        }
    }
    return 0;
}

void dmac_test(void)
{
    unsigned int err_flag=0;
    unsigned int tmp;
    unsigned int testval = 0;

    //Initialize source data for channel 1
    dmac_init_buf(CH1_SRCADDR_BASE,64);
    __asm__ volatile ("fence");

    //Initialize source data for channel 2
    dmac_init_buf(CH2_SRCADDR_BASE , 64); 
    __asm__ volatile ("fence");
    REG_WRITE(0x6400084,0x100);
// enable dmac_axi0
    REG_WRITE(DMAC_AXI0_COMMON_CFG, 0x1);
    testval = REG_READ(DMAC_AXI0_COMMON_CFG);
    printm("DMAC: Start dmac config testval:0x%x !!!\n", testval);

    // check dmac reset complete 
    // ???to do set 0x1 to reset
    tmp = REG_READ(DMAC_AXI0_COMMON_RST_REG);
    while ((tmp & 0x1) != 0x0) {
        tmp = REG_READ(DMAC_AXI0_COMMON_RST_REG);
    }
    printm("***REG_READ(DMAC_AXI0_COMMON_RST_REG):0x%x !!!\n", tmp);
    dmac_ch1_single_transfer(DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC, 0, 0, \
            CH1_SRCADDR_BASE, CH1_DSTADDR_BASE, \
            63, DWAXIDMAC_CH_CTL_L_INC, DWAXIDMAC_CH_CTL_L_INC, \
            DWAXIDMAC_TRANS_WIDTH_32, DWAXIDMAC_TRANS_WIDTH_32, \
            DWAXIDMAC_BURST_TRANS_LEN_1, DWAXIDMAC_BURST_TRANS_LEN_1);
    printm("dmac_ch1_single_transfer\n");
    dmac_ch2_single_transfer(DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC, 0, 0, \
            CH2_SRCADDR_BASE, CH2_DSTADDR_BASE, \
            63, DWAXIDMAC_CH_CTL_L_INC, DWAXIDMAC_CH_CTL_L_INC, \
            DWAXIDMAC_TRANS_WIDTH_32, DWAXIDMAC_TRANS_WIDTH_32, \
            DWAXIDMAC_BURST_TRANS_LEN_1, DWAXIDMAC_BURST_TRANS_LEN_1);
    printm("dmac_ch2_single_transfer\n");
    tmp = REG_READ(DMAC_AXI0_CH1_INTR_STATUS);
    while ((tmp & 0x2) == 0x0) {
        tmp = REG_READ(DMAC_AXI0_CH1_INTR_STATUS);
    }
    printm("REG_READ(DMAC_AXI0_CH1_INTR_STATUS)=%d\n", tmp);
    tmp = REG_READ(DMAC_AXI0_CH2_INTR_STATUS);
    while ((tmp & 0x2) == 0x0) {
         tmp = REG_READ(DMAC_AXI0_CH2_INTR_STATUS);
    }
printm("REG_READ(DMAC_AXI0_CH2_INTR_STATUS)=%d\n", tmp);
// data transfer complete
// check data
    printm("DMAC: Start DDR Data Check  !!!\n");

    __asm__ volatile ("fence");
    err_flag  = dma_data_chk();
    __asm__ volatile ("fence");
    
    if (err_flag == 0)
        printm("DMAC: Start DDR Data Check Success !!!\n");
    else
        printm("DMAC: Start DDR Data Check  Error\n");

    printm("DMAC: Test End !!!\n");
}


void dma_test_cacheline(unsigned long dstmem, unsigned long srcmem, unsigned long size)
{
    unsigned int err_flag = 0;
    unsigned int tmp;
    unsigned int testval = 0;
    //Initialize source data for channel 1
    dmac_init_buf(srcmem, size);
    __asm__ volatile ("fence");

// enable dmac_axi0
    REG_WRITE(DMAC_AXI0_COMMON_CFG, 0x1);
    testval = REG_READ(DMAC_AXI0_COMMON_CFG);
    printm("DMAC: Start dmac config testval:0x%x !!!\n", testval);

    // check dmac reset complete 
    // ???to do set 0x1 to reset
    tmp = REG_READ(DMAC_AXI0_COMMON_RST_REG);
    while ((tmp & 0x1) != 0x0) {
        tmp = REG_READ(DMAC_AXI0_COMMON_RST_REG);
    }
    
    dmac_ch1_single_transfer(DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC, 0, 0, \
            srcmem, dstmem, \
            63, DWAXIDMAC_CH_CTL_L_INC, DWAXIDMAC_CH_CTL_L_INC, \
            DWAXIDMAC_TRANS_WIDTH_32, DWAXIDMAC_TRANS_WIDTH_32, \
            DWAXIDMAC_BURST_TRANS_LEN_1, DWAXIDMAC_BURST_TRANS_LEN_1);

    
    tmp = REG_READ(DMAC_AXI0_CH1_INTR_STATUS);
    while ((tmp & 0x2) == 0x0) {
        tmp = REG_READ(DMAC_AXI0_CH1_INTR_STATUS);
    }

// data transfer complete
// check data
    printm("DMAC: Start DDR Data Check  !!!\n");

    __asm__ volatile ("fence");
    err_flag  = dma_data_check(dstmem, srcmem, size);
    __asm__ volatile ("fence");
    
    if (err_flag == 0)
        printm("DMAC: dstmem:0x%lx srcmem:0x%lx size:0x%lx Data Check Success !!!\n", dstmem, srcmem, size);
    else
        printm("DMAC: dstmem:0x%lx srcmem:0x%lx size:0x%lx Data Check  Error\n", dstmem, srcmem, size);


}

void test_same_setindex(unsigned long dstmem, unsigned long srcmem, unsigned long size)
{
        int set_index = 0;
        unsigned long tmp_dstaddr, tmp_srcaddr, tmpsize;
        tmp_srcaddr = srcmem;

        for (tmp_dstaddr = dstmem; tmp_dstaddr <= dstmem + size ; \
                tmp_dstaddr += L3_SET_STRIDE, \
                tmp_srcaddr += L3_SET_STRIDE) {

                if (tmp_dstaddr > dstmem + size)
                        break;

                dma_test_cacheline(tmp_dstaddr, tmp_srcaddr, CACHE_LINE_SIZE); //dma test cacheline size
        }
    printm("DMAC: Test End !!!\n");

}

void traverse_all_cache(unsigned long dstmem, unsigned long srcmem, unsigned long size)
{
        int set_index = 0;
        unsigned long tmp_dstaddr, tmp_srcaddr, tmpsize;
        tmp_dstaddr = dstmem;
        tmp_srcaddr = srcmem;

        for (set_index = 0; set_index < L3_SET_SIZE;set_index++) {
                tmp_dstaddr += CACHE_LINE_SIZE;
                tmp_srcaddr += CACHE_LINE_SIZE;
                if (tmp_dstaddr > dstmem + size)
                        break;
                dma_test_cacheline(tmp_dstaddr, tmp_srcaddr, CACHE_LINE_SIZE); //dma test cacheline size
        }
    printm("DMAC: Test End !!!\n");
}

