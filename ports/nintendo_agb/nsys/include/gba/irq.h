#include <gba/types.h>


#define REG_IE (*(vu16*)0x04000200)
#define REG_IF (*(vu16*)0x04000202)
#define REG_IME (*(vu16*)0x04000208)
#define BIOS_IF (*(vu16*)0x03FFFFF8)

#define IRQ_VBLANK (1 << 0)
#define IRQ_HBLANK (1 << 1)
#define IRQ_LYC (1 << 2)
#define IRQ_TIMER0 (1 << 3)
#define IRQ_TIMER1 (1 << 4)
#define IRQ_TIMER2 (1 << 5)
#define IRQ_TIMER3 (1 << 6)
#define IRQ_SIO (1 << 7)
#define IRQ_DMA0 (1 << 8)
#define IRQ_DMA1 (1 << 9)
#define IRQ_DMA2 (1 << 10)
#define IRQ_DMA3 (1 << 11)
#define IRQ_HID (1 << 12)
#define IRQ_DMAC (1 << 13)
