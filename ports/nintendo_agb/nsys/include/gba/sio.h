#pragma once

#include <gba/types.h>



#define REG_RCNT                        (*(vu16*)0x04000134)
#define REG_GPIO_CNT                    (*(vu8*) 0x04000134)
#define REG_PORT_CNT                    (*(vu8*) 0x04000135)

#define REG_SIOCNT                      (*(vu16*)0x04000128)
#define REG_SIOCNT_L                    (*(vu8*) 0x04000128)
#define REG_SIODAT8                     (*(vu8*) 0x0400012A)
#define REG_SIODAT16                    (*(vu16*)0x0400012A)
#define REG_SIODAT32                    (*(vu32*)0x04000120)


#define GPIO_VAL_M                      0x0F
#define GPIO_VAL_SC                     BBIT(0)
#define GPIO_VAL_SD                     BBIT(1)
#define GPIO_VAL_SI                     BBIT(2)
#define GPIO_VAL_SO                     BBIT(3)
#define GPIO_DIR_M                      0xF0
#define GPIO_DIR_ALL_IN                 0x00
#define GPIO_DIR_ALL_OUT                0xF0
#define GPIO_DIR_SC                     BBIT(4)
#define GPIO_DIR_SD                     BBIT(5)
#define GPIO_DIR_SI                     BBIT(6)
#define GPIO_DIR_SO                     BBIT(7)

// Enables SI *falling edge* interrupt in GPIO mode
#define PORT_IE                         BBIT(0)

#define PORT_MODE_SH                    6
#define PORT_MODE_NUM                   4
#define PORT_MODE_SIO                   0
#define PORT_MODE_SIO1                  1
#define PORT_MODE_GPIO                  2
#define PORT_MODE_JOYBUS                3

#define RCNT_PORT_IE                    (PORT_IE            << (PORT_MODE_SH + 8))
#define RCNT_MODE_SIO                   (PORT_MODE_SIO      << (PORT_MODE_SH + 8))
#define RCNT_MODE_SIO1                  (PORT_MODE_SIO1     << (PORT_MODE_SH + 8))
#define RCNT_MODE_GPIO                  (PORT_MODE_GPIO     << (PORT_MODE_SH + 8))
#define RCNT_MODE_JOYBUS                (PORT_MODE_JOYBUS   << (PORT_MODE_SH + 8))


#define SIO_SPI_SC_DIR_IN               0
#define SIO_SPI_SC_DIR_OUT              BBIT(0)
// 256kiHz
#define SIO_SPI_SC_SPEED_SLOW           0
// 2MiHz
#define SIO_SPI_SC_SPEED_FAST           BBIT(1)
#define SIO_SPI_SO_IN                   BBIT(2)
#define SIO_SPI_SO_OUT                  BBIT(3)

#define SIO_SPI_START                   BBIT(7)


#define SIO_UART_BAUD_SH                0
#define SIO_UART_BAUD_NUM               4
#define SIO_UART_BAUD_M                 BFAT(SIO_UART_BAUD_NUM-1, SIO_UART_BAUD_SH)
#define SIO_UART_F_M                    0x70

#define SIO_UART_BAUD_9600              BFAT(0, SIO_UART_BAUD_SH)
#define SIO_UART_BAUD_38400             BFAT(1, SIO_UART_BAUD_SH)
#define SIO_UART_BAUD_57600             BFAT(2, SIO_UART_BAUD_SH)
#define SIO_UART_BAUD_115200            BFAT(3, SIO_UART_BAUD_SH)
#define SIO_UART_SEND_ALWAYS            0
#define SIO_UART_SEND_ON_CLEAR          BBIT(2)
#define SIO_UART_PARITY_EVEN            0
#define SIO_UART_PARITY_ODD             BBIT(3)
#define SIO_UART_F_SEND_NONFULL         0
#define SIO_UART_F_SEND_FULL            BBIT(4)
#define SIO_UART_F_RECV_NONEMPTY        0
#define SIO_UART_F_RECV_EMPTY           BBIT(5)
#define SIO_UART_F_ERROR                BBIT(6)
#define SIO_UART_SIZE_7BIT              0
#define SIO_UART_SIZE_8BIT              BBIT(7)
#define SIO_UART_FIFOEN                 BBIT(8)
#define SIO_UART_PARITY_EN              BBIT(9)
#define SIO_UART_EN_TX                  BBIT(10)
#define SIO_UART_EN_RX                  BBIT(11)

#define SIO_UART_FLAG_CLEAR(val,flags)  (((val)&(~SIO_UART_F_M))|(flags))

#define SIOCNT_MODE_SPI_8               BFAT(0, 12)
#define SIOCNT_MODE_SPI_32              BFAT(1, 12)
#define SIOCNT_MODE_MULTI               BFAT(2, 12)
#define SIOCNT_MODE_UART                BFAT(3, 12)
#define SIOCNT_MODE__M                  BFAT(3, 12)

#define SIOCNT_IE                       BIT(14)

#define SIOCNT_SPI_SIZE_8               0
#define SIOCNT_SPI_SIZE_32              BBIT(12)
#define SIOCNT_TYPE_SPI                 0
#define SIOCNT_TYPE_UART                BBIT(13)
