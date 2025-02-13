#pragma once

#include <gba/types.h>



typedef struct
{
    volatile union
    {
        const void* ptr;
        u32 val;
    } SRC;
    volatile union
    {
        const void* ptr;
        u32 val;
    } DST;
    
    volatile union
    {
        struct
        {
            vu16 CTR;
            vu16 CNT;
        };
        vu32 ALL;
    };
} gbaDMA;


#define REG_DMA                         ((gbaDMA*)0x040000B0)

#define REG_DMA0                        (((gbaDMA*)0x040000B0)[0])
#define REG_DMA1                        (((gbaDMA*)0x040000B0)[1])
#define REG_DMA2                        (((gbaDMA*)0x040000B0)[2])
#define REG_DMA3                        (((gbaDMA*)0x040000B0)[3])

#define DMA_ALL_CTR_SH                  0
#define DMA_ALL_CNT_SH                  16

#define DMA_DST_INC                     BFAT(0, 5)
#define DMA_DST_DEC                     BFAT(1, 5)
#define DMA_DST_FIX                     BFAT(2, 5)
#define DMA_DST_RELOAD                  BFAT(3, 5)

#define DMA_SRC_INC                     BFAT(0, 7)
#define DMA_SRC_DEC                     BFAT(1, 7)
#define DMA_SRC_FIX                     BFAT(2, 7)

#define DMA_TRIGGER_ONESHOT             0
#define DMA_TRIGGER_REPEAT              BBIT(9)

#define DMA_SIZE_16                     0
#define DMA_SIZE_32                     BBIT(10)

#define DMA_TYPE_GENERAL                BFAT(0, 12)
#define DMA_TYPE_VBLANK                 BFAT(1, 12)
#define DMA_TYPE_HDMA                   BFAT(2, 12)
#define DMA_TYPE_HARDWARE               BFAT(3, 12)

#define DMA_IE                          BBIT(14)
#define DMA_START                       BBIT(15)
