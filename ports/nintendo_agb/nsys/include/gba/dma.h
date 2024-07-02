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
    
    vu16 CTR;
    vu16 CNT;
} gbaDMA;


#define REG_DMAS ((gbaDMA*)0x040000B0)

#define REG_DMA0 (((gbaDMA*)0x040000B0)[0])
#define REG_DMA1 (((gbaDMA*)0x040000B0)[1])
#define REG_DMA2 (((gbaDMA*)0x040000B0)[2])
#define REG_DMA3 (((gbaDMA*)0x040000B0)[3])


#define DMA_DST_INC (0 << 5)
#define DMA_DST_DEC (1 << 5)
#define DMA_DST_FIX (2 << 5)
#define DMA_DST_RELOAD (3 << 5)

#define DMA_SRC_INC (0 << 7)
#define DMA_SRC_DEC (1 << 7)
#define DMA_SRC_FIX (2 << 7)

#define DMA_TRIGGER_ONESHOT (0 << 9)
#define DMA_TRIGGER_REPEAT (1 << 9)

#define DMA_SIZE_16 (0 << 10)
#define DMA_SIZE_32 (1 << 10)

#define DMA_TYPE_GENERAL (0 << 12)
#define DMA_TYPE_VBLANK (1 << 12)
#define DMA_TYPE_HDMA (2 << 12)
#define DMA_TYPE_HARDWARE (3 << 12)

#define DMA_IRQEN (1 << 14)
#define DMA_START (1 << 15)
