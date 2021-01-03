;
;   boot.asm
;   The bootstrap assembly entrypoint to load the kernel
;

;
;   Boot code synopsis:

;	Set align, meminfo, flags, magic and checksum for multiboot
;	Declare multiboot header with .section, alignment 4, assign multiboot properties as long
;	Prepare the stack (section .bss), alignment 16, 16KiB stack_bottom, empty stack_top

;   _start
;       1.	Set global and function type with _start, .type @function [section .text]
;       2.	Initialize the stack
;       3.	Call the main kernel function
;       4.	If the system has returned, disable interrupts, halt with label 1:, and jump to the hlt instruction (1b)

;   Exit _start:
;       Set size of _start to current location (.) minus start, instruction and parameters seperated by comma

%include "src/interrupts.s"

; Define multiboot contants
; Magic must be 0x1BADB002 as opposed to 0x2BADB002: the bootloader magic value
MB_ALIGN equ        1<<0
MB_MEMINFO equ      1<<1
MB_FLAGS equ        MB_ALIGN | MB_MEMINFO
MB_MAGIC equ        0x1BADB002      
MB_CHECKSUM equ     -(MB_MAGIC + MB_FLAGS)

; Declare multiboot header
section .multiboot
align 4
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM

; Prepare the stack
section .bss                    ; Block Started by Symbol
align 16
    stack_bottom:
        resb 16384                 ; 16KiB space
    stack_top:


; Code to launch kernel
section .text
    global _start
    extern kernel_main
    _start:
        ; Initialize the stack
        ; esp = the 32-bit stack pointer. Format for mov in GNU assembler: $source, %destination_register
        mov [stack_top], esp

        ; Call the external main kernel function
        call kernel_main

        ; Loop the cpu into halt state upon return if the kernel has completed all tasks
        cli     ; Disable interrupts
        call halt

    halt:
        hlt
        jmp halt

    ; size _start, . - _start       ; . = our current location
