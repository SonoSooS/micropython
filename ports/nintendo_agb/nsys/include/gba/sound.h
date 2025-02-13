#pragma once

#include <gba/types.h>



#define REG_SND_CGB_VOL                 (((vu8*) 0x04000080)[0])
#define REG_SND_CGB_PAN                 (((vu8*) 0x04000080)[1])
#define REG_SND_MIX_VOL                 (((vu8*) 0x04000080)[2])
#define REG_SND_DMA_CNT                 (((vu8*) 0x04000080)[3])
#define REG_SND_MATER_EN                (((vu8*) 0x04000080)[4])
#define REG_SND_BIAS                    (((vu16*)0x04000080)[4])
#define REG_SND_DMA_FIFO_A              (((vu32*)0x040000A0)[0])
#define REG_SND_DMA_FIFO_B              (((vu32*)0x040000A0)[1])

#define SNDCNT_DMA_DEFAULT              (14)
#define SNDCNT_DMA_A_ENABLE_R           BFAT(1, 8)
#define SNDCNT_DMA_A_ENABLE_L           BFAT(2, 8)
#define SNDCNT_DMA_A_ENABLE_BOTH        BFAT(3, 8)
#define SNDCNT_DMA_A_FIFO_RESET         BBIT(11)
#define SNDCNT_DMA_B_FIFO_RESET         BBIT(15)



#define SND_FIFO_DEPTH_SAMPLES          16


#define SND_MASTER_EN                   BIT(7)


#define SND_BIAS_MODE_SH                14
// Dithered 8bit at 32kiHz with 64kiHz clock
#define SND_BIAS_MODE_9BIT              BFAT(0, SND_BIAS_MODE_SH)
// True 8bit at 64kiHz
#define SND_BIAS_MODE_8BIT              BFAT(1, SND_BIAS_MODE_SH)
// Technical details unknown, 7bit, 128kiHz
#define SND_BIAS_MODE_UNK               BFAT(2, SND_BIAS_MODE_SH)
// True 6bit at 256kiHz, used for CGB mode
#define SND_BIAS_MODE_6BIT              BFAT(3, SND_BIAS_MODE_SH)

#define SND_BIAS_VAL_SH                 1
#define SND_BIAS_VAL_NUM                512
#define SND_BIAS_VAL_ON                 256
#define SND_BIAS_VAL_OFF                0


#define SND_CGB_VOL_R_SH                0
#define SND_CGB_VOL_R_NUM               8
#define SND_CGB_VOL_L_SH                4
#define SND_CGB_VOL_L_NUM               8
#define SND_CGB_VOL_MAX                 0x77

#define SND_CGB_PAN_R_CH1               BBIT(0)
#define SND_CGB_PAN_R_CH2               BBIT(1)
#define SND_CGB_PAN_R_CH3               BBIT(2)
#define SND_CGB_PAN_R_CH4               BBIT(3)
#define SND_CGB_PAN_L_CH1               BBIT(4)
#define SND_CGB_PAN_L_CH2               BBIT(5)
#define SND_CGB_PAN_L_CH3               BBIT(6)
#define SND_CGB_PAN_L_CH4               BBIT(7)

#define SND_CGB_PAN_ALL_L               0x0F
#define SND_CGB_PAN_ALL_R               0xF0
#define SND_CGB_PAN_ALL                 0xFF

#define SND_MIX_VOL_CGB_SH              0
#define SND_MIX_VOL_CGB_NUM             3
#define SND_MIX_VOL_CGB_25              BFAT(0, SND_MIX_VOL_CGB_SH)
#define SND_MIX_VOL_CGB_50              BFAT(1, SND_MIX_VOL_CGB_SH)
#define SND_MIX_VOL_CGB_100             BFAT(2, SND_MIX_VOL_CGB_SH)

#define SND_MIX_VOL_DMA_A_50            0
#define SND_MIX_VOL_DMA_A_100           BBIT(2)
#define SND_MIX_VOL_DMA_B_50            0
#define SND_MIX_VOL_DMA_B_100           BBIT(3)

#define SND_DMA_CNT_R_SH                0
#define SND_DMA_CNT_L_SH                4
#define SND_DMA_PAN_R                   BBIT(0)
#define SND_DMA_PAN_L                   BBIT(1)
#define SND_DMA_TIMER_SEL_0             0
#define SND_DMA_TIMER_SEL_1             BBIT(2)
#define SND_DMA_FIFO_RESET              BBIT(3)

#define SND_DMA_PAN_AA_LR               0x03
#define SND_DMA_PAN_AB_LR               0x12
#define SND_DMA_TIMER1_BOTH             0x22
#define SND_DMA_TIMER0_BOTH             0x00
#define SND_DMA_FIFO_RESET_BOTH         0x44
