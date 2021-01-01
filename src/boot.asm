/*
*   boot.asm
*   The bootstrap assembly entrypoint to load the kernel
*/

/*
*   Boot code synopsis:

1.	Set align, meminfo, flags, magic and checksum for multiboot
2.	Declare multiboot header with .section, alignment 4, assign multiboot properties as long
3.	Prepare the stack (section .bss), alignment 16, 16KiB stack_bottom, empty stack_top

_start
1.	Set global and function type with _start, .type @function [section .text]
2.	Initialize the stack
3.	Call the main kernel function
4.	If the system has returned, disable interrupts, halt with label 1:, and jump to the hlt instruction (1b)

Exit _start:
	Set size of _start to current location (.) minus start, instruction and parameters seperated by comma

*/


/* Define multiboot contants */
/* Magic must be 0x1BADB002 as opposed to 0x2BADB002: the bootloader magic value */
.set ALIGN,     1<<0
.set MEMINFO,   1<<1
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1BADB002      
.set CHECKSUM,  -(MAGIC + FLAGS)


/* Declare multiboot header */
.section multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM


/* Prepare the stack */
.section bss                    /* Block Started by Symbol */
.align 16
stack_bottom:
    .skip 16384                 /* 16KiB space */
stack_top:


/* Code to launch kernel */
.section .text
.global _start
.type _start, @function
_start:
    /* Initialize the stack */
    /* esp = the 32-bit stack pointer. Format for mov in GNU assembler: $source, %destination_register */
    mov $stack_top, %esp

    /* Call the external main kernel function */
    call kernel_main

    /* Loop the cpu into halt state upon return if the kernel has completed all tasks */
    cli     /* Disable interrupts */
1:  hlt     /* Set start of loop */
    jmp 1b  /* Jump to halt instruction */

.size _start, . - _start       /* . = our current location */
