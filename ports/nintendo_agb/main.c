#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "py/builtin.h"
#include "py/compile.h"
#include "py/runtime.h"
#include "py/repl.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "py/stackctrl.h"
#include "shared/runtime/pyexec.h"
#include "shared/runtime/gchelper.h"
#include "py/objexcept.h"

#if MICROPY_ENABLE_COMPILER
void do_str(const char *src, mp_parse_input_kind_t input_kind) {
    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
        mp_lexer_t *lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, src, strlen(src), 0);
        qstr source_name = lex->source_name;
        mp_parse_tree_t parse_tree = mp_parse(lex, input_kind);
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, true);
        mp_call_function_0(module_fun);
        nlr_pop();
    } else {
        // uncaught exception
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}
#endif

static char *stack_top;
#if MICROPY_ENABLE_GC
extern char __heap_ext_start;
extern char __heap_ext_end;
#endif

extern uint32_t __StackTop, __StackBottom;

int main(int argc, char **argv)
{
    int stack_dummy;
    stack_top = (char *)&stack_dummy;
    
    mp_stack_set_top(stack_top);
    mp_stack_set_limit((char*)&stack_dummy - (char*)&__StackBottom - 256);

    #if MICROPY_ENABLE_GC
    #if MICROPY_GC_SPLIT_HEAP
    mp_stack_set_limit(4096 - 256);
    gc_init((char*)((((size_t)&__StackBottom) + 15) & ~15), (char*)&stack_dummy - 4096);
    gc_add(&__heap_ext_start, &__heap_ext_end);
    #else
    gc_init(&__heap_ext_start, &__heap_ext_end);
    #endif
    #endif
    mp_init();
    pyexec_frozen_module("_boot.py");
    pyexec_file_if_exists("boot.py");
    #if MICROPY_ENABLE_COMPILER
    #if MICROPY_REPL_EVENT_DRIVEN
    pyexec_event_repl_init();
    for (;;) {
        int c = mp_hal_stdin_rx_chr();
        if (pyexec_event_repl_process_char(c)) {
            break;
        }
    }
    #else
    pyexec_friendly_repl();
    #endif
    // do_str("print('hello world!', list(x+1 for x in range(10)), end='eol\\n')", MP_PARSE_SINGLE_INPUT);
    // do_str("for i in range(10):\r\n  print(i)", MP_PARSE_FILE_INPUT);
    #else
    pyexec_frozen_module("frozentest.py");
    #endif
    mp_deinit();
    return 0;
}

#if MICROPY_ENABLE_GC
void gc_collect(void)
{
    // WARNING: This gc_collect implementation doesn't try to get root
    // pointers from CPU registers, and thus may function incorrectly.
    //void *dummy;
    gc_collect_start();
    gc_helper_collect_regs_and_stack();
    //gc_collect_root(&dummy, ((mp_uint_t)stack_top - (mp_uint_t)&dummy) / sizeof(mp_uint_t));
    gc_collect_end();
    gc_dump_info();
}
#endif

#if !MICROPY_READER_POSIX && !MICROPY_READER_VFS
mp_lexer_t *mp_lexer_new_from_file(const char *filename) {
    mp_raise_OSError(MP_ENOENT);
}
#endif

#if !MICROPY_VFS
mp_import_stat_t mp_import_stat(const char *path) {
    return MP_IMPORT_STAT_NO_EXIST;
}
#endif

void NORETURN __fatal_error(const char *msg)
{
    *(volatile unsigned short*)0x04000208 = 0;
    printf("Fatal error: %s\r\nHalted.\r\n\r\n", msg);
    for(;;);
}

void nlr_jump_fail(void *val)
{
    *(volatile unsigned short*)0x04000208 = 0;
    printf("nlr_jump_fail %08lX\n", (long unsigned int)val);
    const unsigned long* vars = (void*)val;
    printf("Values:\n- %08lX\n- %08lX\n- %08lX\n- %08lX\n"
           "- %08lX\n- %08lX\n- %08lX\n- %08lX\n",
        vars[0],
        vars[1],
        vars[2],
        vars[3],
        vars[4],
        vars[5],
        vars[6],
        vars[7]
        );
    //mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(val));
    mp_obj_exception_print(&mp_plat_print, val, PRINT_REPR);
    __fatal_error("nlr_jump_fail");
}

#ifndef NDEBUG
void MP_WEAK __assert_func(const char *file, int line, const char *func, const char *expr)
{
    printf("Assertion '%s' failed, at file %s:%d\n", expr, file, line);
    __fatal_error("Assertion failed");
}
#endif

