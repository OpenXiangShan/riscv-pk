#ifndef _REGS_DMAC_AXI_H_
#define _REGS_DMAC_AXI_H_

#define REG_AP_DMAC_AXI0_BASE          (0x30040000)

#define DMAC_AXI_COMMON_REG     0x0
#define DMAC_AXI_CH1_REG        0x100
#define DMAC_AXI_CH2_REG        0x200

#define DMAC_AXI_ID                     0x0
#define DMAC_AXI_COMP_VER               0x08
#define DMAC_AXI_CFG                    0x10 
#define DMAC_AXI_CH_EN                  0x18
#define DMAC_AXI_INTR_STATUS            0x30
#define DMAC_AXI_COMMON_INTR_CLEAR      0x38
#define DMAC_AXI_COMMON_STATUS_ENABLE   0x40
#define DMAC_AXI_COMMON_SIGNAL_ENABLE   0x48
#define DMAC_AXI_COMMON_INTR_STATUS     0x50
#define DMAC_AXI_RST_REG                0x58

#define DMAC_AXI_CH_SAR                 0x0
#define DMAC_AXI_CH_DAR                 0x08
#define DMAC_AXI_CH_BLOCK_TS            0x10
#define DMAC_AXI_CH_CTL                 0x18
#define DMAC_AXI_CH_CFG                 0x20
#define DMAC_AXI_CH_LLP                 0x28
#define DMAC_AXI_CH_STATUS              0x30
#define DMAC_AXI_CH_SWHSSRC_REQ         0x38
#define DMAC_AXI_CH_SWHSDST_REQ         0x40
#define DMAC_AXI_CH_BLK_TFR_RESUME_REQ  0x48
#define DMAC_AXI_CH_AXI_ID              0x50
#define DMAC_AXI_CH_AXI_QOS             0x58
#define DMAC_AXI_CH_SSTAT               0x60
#define DMAC_AXI_CH_DSTAT               0x68
#define DMAC_AXI_CH_STATAR              0x70
#define DMAC_AXI_CH_DSTATAR             0x78
#define DMAC_AXI_CH_INTR_STATUS_ENABLE  0x80
#define DMAC_AXI_CH_INTR_STATUS         0x88
#define DMAC_AXI_CH_INTR_SIGNAL_ENABLE  0x90
#define DMAC_AXI_CH_INTR_CLEAR          0x98

#define DMAC_AXI0_COMMON_ID                    REG_AP_DMAC_AXI0_BASE + DMAC_AXI_COMMON_REG + DMAC_AXI_ID                     
#define DMAC_AXI0_COMMON_COMP_VER              REG_AP_DMAC_AXI0_BASE + DMAC_AXI_COMMON_REG + DMAC_AXI_COMP_VER               
#define DMAC_AXI0_COMMON_CFG                   REG_AP_DMAC_AXI0_BASE + DMAC_AXI_COMMON_REG + DMAC_AXI_CFG                    
#define DMAC_AXI0_COMMON_CH_EN                 REG_AP_DMAC_AXI0_BASE + DMAC_AXI_COMMON_REG + DMAC_AXI_CH_EN                  
#define DMAC_AXI0_COMMON_INTR_STATUS           REG_AP_DMAC_AXI0_BASE + DMAC_AXI_COMMON_REG + DMAC_AXI_INTR_STATUS            
#define DMAC_AXI0_COMMON_COMMON_INTR_CLEAR     REG_AP_DMAC_AXI0_BASE + DMAC_AXI_COMMON_REG + DMAC_AXI_COMMON_INTR_CLEAR      
#define DMAC_AXI0_COMMON_COMMON_STATUS_ENABLE  REG_AP_DMAC_AXI0_BASE + DMAC_AXI_COMMON_REG + DMAC_AXI_COMMON_STATUS_ENABLE   
#define DMAC_AXI0_COMMON_COMMON_SIGNAL_ENABLE  REG_AP_DMAC_AXI0_BASE + DMAC_AXI_COMMON_REG + DMAC_AXI_COMMON_SIGNAL_ENABLE   
#define DMAC_AXI0_COMMON_COMMON_INTR_STATUS    REG_AP_DMAC_AXI0_BASE + DMAC_AXI_COMMON_REG + DMAC_AXI_COMMON_INTR_STATUS     
#define DMAC_AXI0_COMMON_RST_REG               REG_AP_DMAC_AXI0_BASE + DMAC_AXI_COMMON_REG + DMAC_AXI_RST_REG                

#define DMAC_AXI0_CH1_SAR                      REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_SAR                 
#define DMAC_AXI0_CH1_DAR                      REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_DAR                 
#define DMAC_AXI0_CH1_BLOCK_TS                 REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_BLOCK_TS            
#define DMAC_AXI0_CH1_CTL                      REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_CTL                 
#define DMAC_AXI0_CH1_CFG                      REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_CFG                 
#define DMAC_AXI0_CH1_LLP                      REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_LLP                 
#define DMAC_AXI0_CH1_STATUS                   REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_STATUS              
#define DMAC_AXI0_CH1_SWHSSRC_REQ              REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_SWHSSRC_REQ         
#define DMAC_AXI0_CH1_SWHSDST_REQ              REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_SWHSDST_REQ         
#define DMAC_AXI0_CH1_BLK_TFR_RESUME_REQ       REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_BLK_TFR_RESUME_REQ  
#define DMAC_AXI0_CH1_AXI_ID                   REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_AXI_ID              
#define DMAC_AXI0_CH1_AXI_QOS                  REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_AXI_QOS             
#define DMAC_AXI0_CH1_SSTAT                    REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_SSTAT               
#define DMAC_AXI0_CH1_DSTAT                    REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_DSTAT               
#define DMAC_AXI0_CH1_STATAR                   REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_STATAR              
#define DMAC_AXI0_CH1_DSTATAR                  REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_DSTATAR             
#define DMAC_AXI0_CH1_INTR_STATUS_ENABLE       REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_INTR_STATUS_ENABLE  
#define DMAC_AXI0_CH1_INTR_STATUS              REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_INTR_STATUS         
#define DMAC_AXI0_CH1_INTR_SIGNAL_ENABLE       REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_INTR_SIGNAL_ENABLE  
#define DMAC_AXI0_CH1_INTR_CLEAR               REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH1_REG + DMAC_AXI_CH_INTR_CLEAR          

#define DMAC_AXI0_CH2_SAR                      REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_SAR                 
#define DMAC_AXI0_CH2_DAR                      REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_DAR                 
#define DMAC_AXI0_CH2_BLOCK_TS                 REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_BLOCK_TS            
#define DMAC_AXI0_CH2_CTL                      REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_CTL                 
#define DMAC_AXI0_CH2_CFG                      REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_CFG                 
#define DMAC_AXI0_CH2_LLP                      REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_LLP                 
#define DMAC_AXI0_CH2_STATUS                   REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_STATUS              
#define DMAC_AXI0_CH2_SWHSSRC_REQ              REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_SWHSSRC_REQ         
#define DMAC_AXI0_CH2_SWHSDST_REQ              REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_SWHSDST_REQ         
#define DMAC_AXI0_CH2_BLK_TFR_RESUME_REQ       REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_BLK_TFR_RESUME_REQ  
#define DMAC_AXI0_CH2_AXI_ID                   REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_AXI_ID              
#define DMAC_AXI0_CH2_AXI_QOS                  REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_AXI_QOS             
#define DMAC_AXI0_CH2_SSTAT                    REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_SSTAT               
#define DMAC_AXI0_CH2_DSTAT                    REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_DSTAT               
#define DMAC_AXI0_CH2_STATAR                   REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_STATAR              
#define DMAC_AXI0_CH2_DSTATAR                  REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_DSTATAR             
#define DMAC_AXI0_CH2_INTR_STATUS_ENABLE       REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_INTR_STATUS_ENABLE  
#define DMAC_AXI0_CH2_INTR_STATUS              REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_INTR_STATUS         
#define DMAC_AXI0_CH2_INTR_SIGNAL_ENABLE       REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_INTR_SIGNAL_ENABLE  
#define DMAC_AXI0_CH2_INTR_CLEAR               REG_AP_DMAC_AXI0_BASE + DMAC_AXI_CH2_REG + DMAC_AXI_CH_INTR_CLEAR          


/* DMAC_CFG */
#define DMAC_EN_POS         0
#define DMAC_EN_MASK        (0x1U)   

#define DMAC_CHAN_EN_SHIFT      0
#define DMAC_CHAN_EN_WE_SHIFT       8

#define CH_CTL_L_DST_MSIZE_POS      18
#define CH_CTL_L_SRC_MSIZE_POS      14

enum {
    DWAXIDMAC_BURST_TRANS_LEN_1 = 0,
    DWAXIDMAC_BURST_TRANS_LEN_4,
    DWAXIDMAC_BURST_TRANS_LEN_8,
    DWAXIDMAC_BURST_TRANS_LEN_16,
    DWAXIDMAC_BURST_TRANS_LEN_32,
    DWAXIDMAC_BURST_TRANS_LEN_64,
    DWAXIDMAC_BURST_TRANS_LEN_128,
    DWAXIDMAC_BURST_TRANS_LEN_256,
    DWAXIDMAC_BURST_TRANS_LEN_512,
    DWAXIDMAC_BURST_TRANS_LEN_1024
};

#define CH_CFG_H_TT_FC_POS      0
enum {
     DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC = 0,
     DWAXIDMAC_TT_FC_MEM_TO_PER_DMAC,
     DWAXIDMAC_TT_FC_PER_TO_MEM_DMAC,
     DWAXIDMAC_TT_FC_PER_TO_PER_DMAC,
     DWAXIDMAC_TT_FC_PER_TO_MEM_SRC,
     DWAXIDMAC_TT_FC_PER_TO_PER_SRC,
     DWAXIDMAC_TT_FC_MEM_TO_PER_DST,
     DWAXIDMAC_TT_FC_PER_TO_PER_DST
};

/* CH_CFG_L */
#define CH_CFG_L_DST_MULTBLK_TYPE_POS   2
#define CH_CFG_L_SRC_MULTBLK_TYPE_POS   0
enum {
    DWAXIDMAC_MBLK_TYPE_CONTIGUOUS  = 0,
    DWAXIDMAC_MBLK_TYPE_RELOAD,
    DWAXIDMAC_MBLK_TYPE_SHADOW_REG,
    DWAXIDMAC_MBLK_TYPE_LL
};


#define CH_CTL_L_DST_MAST       BIT(2)
#define CH_CTL_L_SRC_MAST       BIT(0)

/* CH_CFG_H */
#define CH_CFG_H_PRIORITY_POS       17
#define CH_CFG_H_HS_SEL_DST_POS     4
#define CH_CFG_H_HS_SEL_SRC_POS     3
enum {
    DWAXIDMAC_HS_SEL_HW     = 0,
    DWAXIDMAC_HS_SEL_SW
};

#define CH_CTL_L_DST_INC_POS        6
#define CH_CTL_L_SRC_INC_POS        4
enum {
    DWAXIDMAC_CH_CTL_L_INC      = 0,
    DWAXIDMAC_CH_CTL_L_NOINC
};

#define CH_CTL_L_DST_WIDTH_POS      11
#define CH_CTL_L_SRC_WIDTH_POS      8

enum {
    DWAXIDMAC_TRANS_WIDTH_8     = 0,
    DWAXIDMAC_TRANS_WIDTH_16,
    DWAXIDMAC_TRANS_WIDTH_32,
    DWAXIDMAC_TRANS_WIDTH_64,
    DWAXIDMAC_TRANS_WIDTH_128,
    DWAXIDMAC_TRANS_WIDTH_256,
    DWAXIDMAC_TRANS_WIDTH_512,
    DWAXIDMAC_TRANS_WIDTH_MAX   = DWAXIDMAC_TRANS_WIDTH_512
};

#define MEM_WRITE32(addr, value)  (*((volatile unsigned int*)(((unsigned long long)addr)))) = (value)
#define MEM_READ32(addr)  (*((volatile unsigned int*)(((unsigned long long)addr))))
#define REG_ADDR_TYPE (volatile unsigned int*)
#define REG_WRITE(addr, value)  (*((volatile unsigned int*)(((unsigned long long)addr)))) = (value)
#define REG_READ(addr)  (*((volatile unsigned int*)(((unsigned long long)addr))))
#define MEM_WRITE(addr, value)  (*((volatile unsigned long long*)(((unsigned long long)addr)))) = (value)
#define MEM_READ(addr)  (*((volatile unsigned long long*)(((unsigned long long)addr))))
#define BYTE_WRITE(addr, value)  (*((volatile unsigned char*)(((unsigned long long)addr)))) = (value)
#define BYTE_READ(addr)  (*((volatile unsigned char*)(((unsigned long long)addr))))


void dmac_test(void);

#endif

