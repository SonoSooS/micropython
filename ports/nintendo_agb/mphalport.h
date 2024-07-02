
#include "py/obj.h"

extern char mp_interrupt_char;

static inline void mp_hal_set_interrupt_char(char c)
{
    mp_interrupt_char = c;
}

static inline mp_uint_t mp_hal_ticks_us(void)
{
    return 0;
}

static inline mp_uint_t mp_hal_ticks_ms(void)
{
    return 0;
}

static inline mp_uint_t mp_hal_ticks_cpu(void)
{
    return 0;
}

static inline mp_uint_t mp_hal_get_cpu_freq(void)
{
    return 1 << 24;
}
