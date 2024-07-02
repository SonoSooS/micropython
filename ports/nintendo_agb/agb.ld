
/* Specify the memory areas */
MEMORY
{
    ROM (rx)        : ORIGIN = 0x08000000, LENGTH = 32 * 1024k
    IWRAM (xrw)     : ORIGIN = 0x03000000, LENGTH = 32k - 512
    EWRAM (xrw)     : ORIGIN = 0x02000000, LENGTH = 256k
}

/* top end of the stack */
__StackTop = ORIGIN(IWRAM) + LENGTH(IWRAM);
__heap_ext_end = ORIGIN(EWRAM) + LENGTH(EWRAM);

/* define output sections */
SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        PROVIDE(__ImageBase = .);
        KEEP(*(.isr_vector))
        KEEP(*(.isr_vector.start))
        KEEP(*(.isr_vector.*))
        . = ALIGN(256);
    } >ROM

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        __text_end = .;
    } >ROM

    .data :
    {
        . = ALIGN(4);
        __data_start = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        __data_end = .;
    } >IWRAM AT>ROM
    __data_load = LOADADDR(.data);
    
    .romfs :
    {
        . = ALIGN(512);
        PROVIDE(__ROMFS = .);
        KEEP(*(.romfs));
        KEEP(*(.romfs*));
    } >ROM
    
    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
        . = ALIGN(16);
        PROVIDE(__StackBottom = .);
    } >IWRAM
    
    .heap_ext (NOLOAD) :
    {
        . = ALIGN(16);
        __heap_ext_start = .;
    } >EWRAM

    .ARM.attributes 0 : { *(.ARM.attributes) }
}
