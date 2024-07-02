/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2021 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

// Need to provide a declaration/definition of alloca()
#include <alloca.h>

// Options to control how MicroPython is built

// Use the minimal starting configuration (disables all optional features).
//#define MICROPY_CONFIG_ROM_LEVEL                (MICROPY_CONFIG_ROM_LEVEL_BASIC_FEATURES)
#define MICROPY_CONFIG_ROM_LEVEL                (MICROPY_CONFIG_ROM_LEVEL_EXTRA_FEATURES)
//#define MICROPY_CONFIG_ROM_LEVEL                (MICROPY_CONFIG_ROM_LEVEL_EVERYTHING)

// Compiler configuration
#define MICROPY_ENABLE_COMPILER                 (1)

// Python internal features
#define MICROPY_ERROR_REPORTING                 (MICROPY_ERROR_REPORTING_DETAILED)
//#define MICROPY_ERROR_REPORTING                 (MICROPY_ERROR_REPORTING_NONE)


#define MICROPY_QSTR_EXTRA_POOL           mp_qstr_frozen_const_pool
#define MICROPY_ENABLE_GC                 (1)
#define MICROPY_GC_SPLIT_HEAP (1)
#define MICROPY_HELPER_REPL               (1)
//#define MICROPY_MODULE_FROZEN_MPY         (0)
#define MICROPY_ENABLE_EXTERNAL_IMPORT    (1)
#define MICROPY_PERSISTENT_CODE_LOAD      (1)

#define MICROPY_ENABLE_FINALISER          (1)

#define MICROPY_LONGINT_IMPL (MICROPY_LONGINT_IMPL_MPZ)
#define MICROPY_FLOAT_IMPL (MICROPY_FLOAT_IMPL_FLOAT)

//#define MICROPY_OBJ_REPR (MICROPY_OBJ_REPR_C)
#define MICROPY_OBJ_REPR (MICROPY_OBJ_REPR_B)

#define MICROPY_OPT_COMPUTED_GOTO (1)

#define MICROPY_STACK_CHECK (0)
#define MICROPY_ENABLE_SCHEDULER (1)
#define MICROPY_SCHEDULER_STATIC_NODES (1)
#define MICROPY_SCHEDULER_DEPTH (8)

#define MICROPY_PY_GC_COLLECT_RETVAL (1)

#define MICROPY_PY_SYS_STDFILES (0)
#define MICROPY_PY_SYS_STDIO_BUFFER (0)
#define MICROPY_PY_UJSON (0)
#define MICROPY_PY_UOS (1)
#define MICROPY_PY_URANDOM (1)
#define MICROPY_PY_USELECT (0)
#define MICROPY_PY_UASYNCIO (0)
#define MICROPY_PY_BTREE (0)

#define MICROPY_PY_UCTYPES (1)
#define MICROPY_PY_UCTYPES_NATIVE_C_TYPES (1)
#define MICROPY_PY_FRAMEBUF (1)

#define MICROPY_READER_VFS (1)

#define MICROPY_ALLOC_PATH_MAX                      (240)
#define MICROPY_FATFS_ENABLE_LFN                    (2)
#define MICROPY_FATFS_MAX_LFN                       (MICROPY_ALLOC_PATH_MAX)
#define MICROPY_FATFS_LFN_CODE_PAGE                 437 // 1=SFN/ANSI 437=LFN/U.S.(OEM)
#define MICROPY_FATFS_RPATH                         (2)
#define MICROPY_FATFS_REENTRANT                     (0)

#define MICROPY_VFS (1)
#define MICROPY_VFS_FAT (1)
#define MICROPY_PY_IO (1)
#define MICROPY_PY_SYS (1)
#define MICROPY_PY_IOBASE (1)
#define MICROPY_PY_MACHINE (1)

#define MICROPY_EMIT_THUMB (0)
#define MICROPY_EMIT_THUMB_ARMV7M (0)
#define MICROPY_EMIT_INLINE_THUMB (0)
#define MICROPY_EMIT_INLINE_THUMB_FLOAT (0)
#define MICROPY_EMIT_ARM (0)

#define MICROPY_DYNAMIC_COMPILER (1)
//#define MICROPY_EMIT_X64 (MICROPY_DYNAMIC_COMPILER)
//#define MICROPY_EMIT_X86 (MICROPY_DYNAMIC_COMPILER)
//#define MICROPY_EMIT_XTENSA (MICROPY_DYNAMIC_COMPILER)
//#define MICROPY_EMIT_INLINE_XTENSA (MICROPY_DYNAMIC_COMPILER)
//#define MICROPY_EMIT_XTENSAWIN (MICROPY_DYNAMIC_COMPILER)

#define MICROPY_ALLOC_PARSE_CHUNK_INIT    (16)

#define MICROPY_HW_BOARD_NAME "Nintendo Game Boy Advance"
#define MICROPY_HW_MCU_NAME "CPU-AGB"

// No need to use ARM that much
#define MICROPY_MAKE_POINTER_CALLABLE(p)            ((void *)((mp_uint_t)(p) | 1))

#define MP_STATE_PORT MP_STATE_VM
//#define MP_SSIZE_MAX                                (0x7FFFFFFF)
#define MP_SSIZE_MAX                                (0xFFFFFF)

#define asm __asm__



#if MICROPY_PY_MACHINE
#define MACHINE_BUILTIN_MODULE_CONSTANTS \
    { MP_ROM_QSTR(MP_QSTR_umachine), MP_ROM_PTR(&mp_module_machine) }, \
    { MP_ROM_QSTR(MP_QSTR_machine), MP_ROM_PTR(&mp_module_machine) },
#else
#define MACHINE_BUILTIN_MODULE_CONSTANTS
#endif

#define MICROPY_PORT_CONSTANTS \
    MACHINE_BUILTIN_MODULE_CONSTANTS

// Type definitions for the specific machine

typedef int32_t mp_int_t; // must be pointer size
typedef uint32_t mp_uint_t; // must be pointer size
typedef ssize_t mp_off_t;

