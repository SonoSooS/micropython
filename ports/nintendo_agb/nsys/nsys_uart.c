
#include <stdint.h>
#include <string.h>

#include <gba/sio.h>
#include <gba/irq.h>

#include "py/stream.h"

static int mgba_dbg_en = 0;

volatile int uart_tx_placeholder = 0;

#define MGBA_DBGEN (*(volatile uint16_t*)0x04FFF780)
#define MGBA_FLAGS (*(volatile uint16_t*)0x04FFF700)
#define MGBA_BUF ((volatile char*)0x04FFF600)

#define MGBA_LOG_FATAL 0
#define MGBA_LOG_ERROR 1
#define MGBA_LOG_WARN 2
#define MGBA_LOG_INFO 3
#define MGBA_LOG_DEBUG 4

static void mgba_dbg(const char* str, size_t length)
{
    while(length)
    {
        size_t reallen = length;
        if(reallen > 80)
            reallen = 80;
        
        size_t i;
        for(i = 0; i < reallen; i++)
            MGBA_BUF[i] = *(str++);
        
        if(reallen != length)
            MGBA_BUF[i] = '=';
        
        MGBA_FLAGS = MGBA_LOG_INFO | 0x100;
        
        length -= reallen;
    }
}

void nsys_init_uart(void)
{
    MGBA_DBGEN = 0xC0DE;
    if(MGBA_DBGEN == 0x1DEA)
    {
        mgba_dbg_en = 1;
    }
    
    REG_RCNT = RCNT_MODE_SIO;
    
    REG_SIOCNT &= SIOCNT_MODE__M;
    REG_SIOCNT = SIOCNT_MODE_UART;
    REG_SIOCNT |= SIO_UART_BAUD_9600 /*| SIO_UART_SEND_ON_CLEAR*/ | SIO_UART_SIZE_8BIT;
    REG_SIOCNT |= SIO_UART_EN_TX | SIO_UART_EN_RX ;//| SIOCNT_IE;
}

__attribute__((noinline)) void sioSendSyncChar(char chr)
{
    while(REG_SIOCNT & SIO_UART_F_SEND_FULL)
        ;
    
    REG_SIODAT8 = chr;
}

__attribute__((noinline)) int sioRecvSyncChar(void)
{
    while(REG_SIOCNT & SIO_UART_F_RECV_EMPTY)
        ;
    
    return (int)REG_SIODAT8;
}

__attribute__((noinline)) int sioRecvAsyncChar(void)
{
    if(!(REG_SIOCNT & SIO_UART_F_RECV_EMPTY))
        return (int)REG_SIODAT8;
    
    return -1;
}

__attribute__((noinline)) void sioSendSyncStr(const char* str)
{
    for(;;)
    {
        char dat = *str;
        if(!dat)
            break;
        
        sioSendSyncChar(dat);
        
        ++str;
    }
}

uintptr_t mp_hal_stdio_poll(uintptr_t poll_flags)
{
    uintptr_t res = 0;
    
    if((poll_flags & MP_STREAM_POLL_RD) && !(REG_SIOCNT & SIO_UART_F_RECV_EMPTY))
        res |= MP_STREAM_POLL_RD;
    if((poll_flags & MP_STREAM_POLL_WR) && !(REG_SIOCNT & SIO_UART_F_SEND_FULL))
        res |= MP_STREAM_POLL_WR;
    if((poll_flags & MP_STREAM_POLL_ERR) && (REG_SIOCNT & SIO_UART_F_ERROR))
        res |= MP_STREAM_POLL_ERR;
    
    return res;
}

int mp_hal_stdin_rx_chr(void)
{
    int ret;
    
    if(uart_tx_placeholder > 0)
    {
        u32 irqdis = REG_IME;
        REG_IME = 0;
        ret = uart_tx_placeholder;
        uart_tx_placeholder = 0;
        REG_IME = irqdis;
        return ret;
    }
    
    ret = sioRecvAsyncChar();
    if(ret >= 0)
        return ret;
    
    return 0;
}

void mp_hal_stdout_tx_strn(const char *str, size_t len)
{
    (void)mgba_dbg;
    
    /*if(mgba_dbg_en && len && str[0])
        mgba_dbg(str, len);
    */
    
    while (len--)
    {
        if (*str == '\n')
            sioSendSyncChar('\r'); //HACK: don't do this, please
        
        sioSendSyncChar(*str++);
    }
}
