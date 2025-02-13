#pragma once

#include <gba/types.h>



typedef struct
{
    vu16 CTR;
    vu16 CNT;
} gbaTimer;


#define REG_TIMER                       ((gbaTimer*)0x04000100)

#define REG_TIMER0                      (((gbaTimer*)0x04000100)[0])
#define REG_TIMER1                      (((gbaTimer*)0x04000100)[1])
#define REG_TIMER2                      (((gbaTimer*)0x04000100)[2])
#define REG_TIMER3                      (((gbaTimer*)0x04000100)[3])


#define TIMER_SCALE_SH                  0
#define TIMER_SCALE_NUM                 4
#define TIMER_SCALE_1                   BFAT(0, TIMER_SCALE_SH)
#define TIMER_SCALE_64                  BFAT(1, TIMER_SCALE_SH)
#define TIMER_SCALE_256                 BFAT(2, TIMER_SCALE_SH)
#define TIMER_SCALE_1024                BFAT(3, TIMER_SCALE_SH)

#define TIMER_CHAIN                     BBIT(2)
#define TIMER_IE                        BBIT(6)
#define TIMER_EN                        BBIT(7)
