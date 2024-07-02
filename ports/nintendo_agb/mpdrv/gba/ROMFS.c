
#include "../mpconfigport.h"

#include "py/obj.h"

#include <string.h>

#include "py/runtime.h"
#include "py/mphal.h"
#include "py/runtime.h"
#include "extmod/vfs.h"

#define BLOCK_SIZE_BYTES (512)

const mp_uint_t ROMFSHDR[BLOCK_SIZE_BYTES/sizeof(mp_uint_t)] __attribute__((section(".romfs"))) =
{
    0x55AAC0F1, 0x55AABABE, 0xC0FF1000, 0xCAFEBADD
};

extern const mp_obj_type_t gba_blkdev_type;

typedef struct _gba_blkdev_obj_t
{
    mp_obj_base_t base;
    const char* romfs_ptr;
    mp_off_t romfs_size;
} gba_blkdev_obj_t;

STATIC gba_blkdev_obj_t gba_blkdev_obj =
{
    .base = { &gba_blkdev_type },
    .romfs_ptr = 0,
    .romfs_size = 0,
};

void mpdrv_fs_init(void)
{
    gba_blkdev_obj.romfs_ptr = ((const char*)ROMFSHDR) + sizeof(ROMFSHDR);
    if((mp_off_t)gba_blkdev_obj.romfs_ptr < 0x08000000 || (mp_off_t)gba_blkdev_obj.romfs_ptr >= 0x0E000000)
    {
        gba_blkdev_obj.romfs_ptr = 0;
        gba_blkdev_obj.romfs_size = 0;
        return;
    }
    
    gba_blkdev_obj.romfs_size = (0x02000000 - (((mp_off_t)gba_blkdev_obj.romfs_ptr) & 0x01FFFFFF)) & ~(BLOCK_SIZE_BYTES - 1);
}


STATIC mp_obj_t gba_blkdev_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args)
{
    // Parse arguments
    enum { ARG_start, ARG_len };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_start, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = -1} },
        { MP_QSTR_len,   MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = -1} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
    
    mp_off_t rom_off = 0;
    mp_off_t rom_len = 0;
    
    if(args[ARG_start].u_int != -1)
        rom_off = args[ARG_start].u_int;
    
    if(args[ARG_len].u_int != -1)
        rom_len = args[ARG_len].u_int;
    
    gba_blkdev_obj_t *self = mp_obj_malloc(gba_blkdev_obj_t, &gba_blkdev_type);
    
    const char* romfs_ptr = gba_blkdev_obj.romfs_ptr;
    mp_off_t romfs_size = gba_blkdev_obj.romfs_size;
    
    romfs_ptr += rom_off;
    if(rom_len)
        romfs_size = rom_len;
    
    self->romfs_ptr = romfs_ptr;
    self->romfs_size = romfs_size;

    return MP_OBJ_FROM_PTR(self);
}

STATIC mp_obj_t gba_blkdev_readblocks(size_t n_args, const mp_obj_t *args)
{
    gba_blkdev_obj_t *self = MP_OBJ_TO_PTR(args[0]);
    uint32_t offset = mp_obj_get_int(args[1]) * BLOCK_SIZE_BYTES;
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[2], &bufinfo, MP_BUFFER_WRITE);
    if (n_args >= 4)
        offset += mp_obj_get_int(args[3]);
    
    memcpy(bufinfo.buf, (void *)(&self->romfs_ptr[offset]), bufinfo.len);
    
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gba_blkdev_readblocks_obj, 3, 4, gba_blkdev_readblocks);

STATIC mp_obj_t gba_blkdev_writeblocks(size_t n_args, const mp_obj_t *args)
{
    mp_raise_NotImplementedError(NULL);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gba_blkdev_writeblocks_obj, 3, 4, gba_blkdev_writeblocks);

STATIC mp_obj_t gba_blkdev_ioctl(mp_obj_t self_in, mp_obj_t cmd_in, mp_obj_t arg_in)
{
    gba_blkdev_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_int_t cmd = mp_obj_get_int(cmd_in);
    switch (cmd)
    {
        case MP_BLOCKDEV_IOCTL_INIT:
            return MP_OBJ_NEW_SMALL_INT(0);
        case MP_BLOCKDEV_IOCTL_DEINIT:
            return MP_OBJ_NEW_SMALL_INT(0);
        case MP_BLOCKDEV_IOCTL_SYNC:
            return MP_OBJ_NEW_SMALL_INT(0);
        case MP_BLOCKDEV_IOCTL_BLOCK_COUNT:
            return MP_OBJ_NEW_SMALL_INT(self->romfs_size / BLOCK_SIZE_BYTES);
        case MP_BLOCKDEV_IOCTL_BLOCK_SIZE:
            return MP_OBJ_NEW_SMALL_INT(BLOCK_SIZE_BYTES);
        case MP_BLOCKDEV_IOCTL_BLOCK_ERASE:
            mp_raise_NotImplementedError(NULL);
        default:
            return mp_const_none;
    }
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(gba_blkdev_ioctl_obj, gba_blkdev_ioctl);

STATIC const mp_rom_map_elem_t gba_blkdev_locals_dict_table[] =
{
    { MP_ROM_QSTR(MP_QSTR_readblocks), MP_ROM_PTR(&gba_blkdev_readblocks_obj) },
    { MP_ROM_QSTR(MP_QSTR_writeblocks), MP_ROM_PTR(&gba_blkdev_writeblocks_obj) },
    { MP_ROM_QSTR(MP_QSTR_ioctl), MP_ROM_PTR(&gba_blkdev_ioctl_obj) },
};
STATIC MP_DEFINE_CONST_DICT(gba_blkdev_locals_dict, gba_blkdev_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
    gba_blkdev_type,
    MP_QSTR_ROMFS,
    MP_TYPE_FLAG_NONE,
    make_new, gba_blkdev_make_new,
    locals_dict, &gba_blkdev_locals_dict
    );
