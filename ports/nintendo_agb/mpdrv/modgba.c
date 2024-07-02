#include "py/runtime.h"
#include "py/mphal.h"
#include "drivers/dht/dht.h"
#include "shared/runtime/pyexec.h"


extern const mp_obj_type_t gba_blkdev_type;

// Define all properties of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
STATIC const mp_rom_map_elem_t example_module_globals_table[] =
{
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_gba) },
    { MP_ROM_QSTR(MP_QSTR_ROMFS), MP_ROM_PTR(&gba_blkdev_type) },
};
STATIC MP_DEFINE_CONST_DICT(example_module_globals, example_module_globals_table);

// Define module object.
const mp_obj_module_t gba_module =
{
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&example_module_globals,
};

// Register the module to make it available in Python.
MP_REGISTER_MODULE(MP_QSTR_gba, gba_module);
