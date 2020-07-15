/*
*   boot.asm
*   The bootstrap assembly entrypoint to load the kernel.
*/

/*
*   Boot code synopsis:

1.	Set align, meminfo, flags, magic and checksum for multiboot.
2.	Declare multiboot header with .section, alignment 4, assign flags in multiboot standard as long
3.	Prepare the stack (section .bss), alignment 16, 16KiB stack_bottom, empty stack_top.


_start
1.	Set global and function type with _start, @type
2.	Setup the stack
3.	Call the main kernel function
4.	If the system has returned, disable interrupts, halt with label 1:, and jump to the hlt instruction (1b)

Exit _start,
	set size of _start to current location (.) minus start, instruction and parameters seperated by comma.

*/


/* Declare contants for the multiboot header */
.set ALIGN,     1<<0
.set MEMINFO,   1<<1
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

/* Define the multiboot header */
.section multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Prepare the stack, as C/C++ will require it and it's not set up in multiboot */
.section bss    /* Block Started by Symbol */
.align 16
stack_bottom:
    .skip 16384
stack_top:


.section .text
.global _start
.type _start, @function
_start:
    /* Create the stack by setting the value of eax to the address of stack_top */
    mov $stack_top, %esp

    call kernel_main

    /* If the system has finished all jobs and returns, create a loop to halt the cpu. */
    cli         /* Disable interrupts */
1:  hlt         /* Set start of loop */
    jmp 1b      /* Jump to halt instruction */


/* Set the size of the start function to our current location ('.'), subtracted by the location of _start. */
.size _start, . - _start
