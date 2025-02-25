
#include "py/mphal.h"
#include "py/runtime.h"

#include <gba/irq.h>

#if MICROPY_PY_MACHINE

#if MICROPY_PY_MACHINE_BARE_METAL_FUNCS
STATIC mp_obj_t mp_machine_get_freq(void)
{
    return MP_OBJ_NEW_SMALL_INT(mp_hal_get_cpu_freq());
}
#endif

STATIC void mp_machine_idle(void)
{
    uint32_t state = MICROPY_BEGIN_ATOMIC_SECTION();
    uint16_t IF = REG_IF;
    if(!IF)
    {
        uint32_t IME = REG_IME;
        REG_IME = 1;
        __asm__ volatile("SWI 0x02");
        REG_IME = IME;
    }
    MICROPY_END_ATOMIC_SECTION(state);
}

#endif // MICROPY_PY_MACHINE
