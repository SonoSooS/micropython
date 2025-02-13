#pragma once

#include <gba/types.h>



#define REG_KEYIN                       (((vu16*)0x04000130)[0])
#define REG_KEYCNT                      (((vu16*)0x04000130)[1])

#define KEYIN_A                         BBIT(0)
#define KEYIN_B                         BBIT(1)
#define KEYIN_SELECT                    BBIT(2)
#define KEYIN_START                     BBIT(3)
#define KEYIN_RIGHT                     BBIT(4)
#define KEYIN_LEFT                      BBIT(5)
#define KEYIN_UP                        BBIT(6)
#define KEYIN_DOWN                      BBIT(7)
#define KEYIN_R                         BBIT(8)
#define KEYIN_L                         BBIT(9)

#define KEYIN_ALL                       (BBIT(10)-1)

#define KEYCNT_IE                       BIT(14)
#define KEYCNT_MODE_ONE                 0
#define KEYCNT_MODE_ALL                 BIT(15)
