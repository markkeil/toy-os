/* GNU Linker */
/* Must match the function in kernel.c */
ENTRY(kernel_start)

/* Describes the arrangement of the final binary file */
SECTIONS {
    /* Start placing everything at 0x1000 which must map the final bootloader jump */
    . = 0x1000;

    /* Compiled C functions */
    .text : {
        *(.text)
    }

    /* Initialized global variables */
    .data : {
        *(.data)
    }

    /* Uninitialized global variables */
    .bss : {
        *(.bss)
    }
}