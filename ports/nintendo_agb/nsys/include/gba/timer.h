#include <gba/types.h>


typedef struct
{
    vu16 CTR;
    vu16 CNT;
} gbaTimer;


#define REG_TIMERS ((gbaTimer*)0x04000100)

#define REG_TIMER0 (((gbaTimer*)0x04000100)[0])
#define REG_TIMER1 (((gbaTimer*)0x04000100)[1])
#define REG_TIMER2 (((gbaTimer*)0x04000100)[2])
#define REG_TIMER3 (((gbaTimer*)0x04000100)[3])


#define TIMER_SCALE_1 (0 << 0)
#define TIMER_SCALE_64 (1 << 0)
#define TIMER_SCALE_256 (2 << 0)
#define TIMER_SCALE_1024 (3 << 0)

#define TIMER_CHAIN (1 << 2)
#define TIMER_IRQEN (1 << 6)
#define TIMER_EN (1 << 7)
