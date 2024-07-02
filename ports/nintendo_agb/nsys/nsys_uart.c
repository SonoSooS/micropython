
#include <stdint.h>
#include <string.h>

#include <gba/sio.h>

static int mgba_dbg_en = 0;

int uart_tx_placeholder;

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
    
    REG_SIOPORTCNT = 0;
    REG_SIOCNT = 3 << 12;
    REG_SIOCNT |= (0 << 0) /*| (1 << 2)*/ | (1 << 7) | (0 << 8);
    REG_SIOCNT |= (1 << 10) | (1 << 11);
}

__attribute__((noinline)) void sioSendSyncChar(char chr)
{
    while(REG_SIOCNT & (1 << 4))
        ;
    
    REG_SIODAT8 = chr;
}

__attribute__((noinline)) int sioRecvSyncChar(void)
{
    while(REG_SIOCNT & (1 << 5))
        ;
    
    return (int)REG_SIODAT8;
}

__attribute__((noinline)) int sioRecvAsyncChar(void)
{
    if(!(REG_SIOCNT & (1 << 5)))
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

int mp_hal_stdin_rx_chr(void)
{
    int ret;
    
    if(uart_tx_placeholder >= 0)
    {
        ret = uart_tx_placeholder;
        uart_tx_placeholder = -1;
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
            sioSendSyncChar('\r');
        
        sioSendSyncChar(*str++);
    }
}
