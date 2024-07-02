include ../../py/mkenv.mk

CROSS = 1
DEBUG = 0

QSTR_DEFS = qstrdefsport.h

MICROPY_ROM_TEXT_COMPRESSION ?= 0

FROZEN_MANIFEST ?= manifest.py

include $(TOP)/py/py.mk
include $(TOP)/extmod/extmod.mk

ifeq ($(CROSS), 1)
CROSS_COMPILE ?= arm-none-eabi-
endif

INC += -I.
INC += -I$(TOP)
INC += -I$(BUILD)
INC += -I./nsys/include


ifeq ($(CROSS), 1)
LD = $(CROSS_COMPILE)gcc
CFLAGS_ARM7TDMI = -mthumb -mthumb-interwork -mcpu=arm7tdmi -msoft-float -fsingle-precision-constant -Wdouble-promotion -Wfloat-conversion
CFLAGS += $(INC) -Wall -Werror -std=c99 $(CFLAGS_ARM7TDMI) $(COPT)
LDFLAGS += -T agb.ld -Wl,-Map=$@.map -Wl,--cref -Wl,--gc-sections
else
LD = $(CC)
CFLAGS += $(INC) -Wall -Werror -Wdouble-promotion -Wfloat-conversion -std=c99 $(COPT)
LDFLAGS += -Wl,-Map=$@.map,--cref -Wl,--gc-sections
endif

#CSUPEROPT = -Os # save some code space for performance-critical code
CSUPEROPT =

# Select debugging or optimisation build.
CFLAGS += -g  # always include debug info in the ELF
ifeq ($(DEBUG), 1)
CFLAGS += -Og
else
CFLAGS += -O2 -DNDEBUG
CFLAGS += -fdata-sections -ffunction-sections
endif

LIBS = -lm

SRC_C += \
	system.c \
	main.c \
	nsys/nsys_uart.c \
	mpdrv/modgba.c \
	mpdrv/gba/ROMFS.c \
	modmachine.c \
	fatfs_port.c \
	shared/timeutils/timeutils.c \
	shared/libc/printf.c \
	shared/readline/readline.c \
	shared/runtime/pyexec.c \
	shared/runtime/gchelper_generic.c \
	shared/runtime/stdout_helpers.c \
	lib/oofatfs/ff.c \
	lib/oofatfs/ffunicode.c \

#$(BUILD)/_frozen_mpy.c

ifeq ($(CROSS), 1)
SRC_C += \
	shared/libc/string0.c \
	extmod/machine_mem.c
endif

SRC_QSTR += \
	shared/readline/readline.c \
	shared/runtime/pyexec.c \
	modmachine.c \
	mpdrv/modgba.c \
	mpdrv/gba/ROMFS.c \

OBJ += $(PY_CORE_O) $(PY_O)
OBJ += $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_CXX:.cpp=.o))

ifneq ($(FROZEN_MANIFEST),)
CFLAGS += -DMICROPY_MODULE_FROZEN_MPY
CFLAGS += -DMICROPY_MODULE_FROZEN_STR
CFLAGS += -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool
endif

ifeq ($(CROSS), 1)
all: $(BUILD)/firmware.gba
else
all: $(BUILD)/firmware.elf
endif

$(BUILD)/_frozen_mpy.c: $(TOP)/tests/frozen/frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@

$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(Q)$(SIZE) $@

$(BUILD)/firmware.bin: $(BUILD)/firmware.elf
	$(ECHO) "Create $@"
	$(Q)$(OBJCOPY) -O binary -j .isr_vector -j .text -j .data -j .romfs $^ $@

$(BUILD)/firmware.gba: $(BUILD)/firmware.bin ./romfs.img
	$(ECHO) "Create $@"
	$(Q)cp $(BUILD)/firmware.bin $@
	$(Q)gbafix $@
	$(Q)cat ./romfs.img >>$@

deploy: $(BUILD)/firmware.dfu
	$(Q)$(PYTHON) $(PYDFU) -u $^

# Include remaining core make rules.
include $(TOP)/py/mkrules.mk
