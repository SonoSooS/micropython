#pragma once

#include <gba/types.h>



#define REG_IEIF                        (*(vu32*)0x04000200)
#define REG_IE                          (((vu16*)0x04000200)[0])
#define REG_IF                          (((vu16*)0x04000200)[1])
#define REG_IME                         (((vu32*)0x04000208)[2])
#define REG_HALTCNT                     (*(vu16*)0x04000300)
#define BIOS_IF                         (((vu16*)0x04000000)[-4])
#define BIOS_ISR_PTR                    (((void(**)(void))0x04000000)[-1])

#define IEIF_MERGE(val)                 ((val)|((val)>>16))

#define IRQ_VBLANK                      BBIT(0)
#define IRQ_HBLANK                      BBIT(1)
#define IRQ_LYC                         BBIT(2)
#define IRQ_TIMER0                      BBIT(3)
#define IRQ_TIMER1                      BBIT(4)
#define IRQ_TIMER2                      BBIT(5)
#define IRQ_TIMER3                      BBIT(6)
#define IRQ_SIO                         BBIT(7)
#define IRQ_DMA0                        BBIT(8)
#define IRQ_DMA1                        BBIT(9)
#define IRQ_DMA2                        BBIT(10)
#define IRQ_DMA3                        BBIT(11)
#define IRQ_HID                         BBIT(12)
#define IRQ_DMAC                        BBIT(13)

#define HALTCNT_HALT                    BFAT(0, 15)
#define HALTCNT_STOP                    BFAT(1, 15)
