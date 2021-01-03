/*
*   kernel.cpp
*   Entrypoint to the kernel
*/

#include "terminal.hpp"
#include "interrupts.hpp"
#include "stdio.h"

extern "C" void kernel_main(void) {
    tty_init();
    idt_init();

    printf("Hello, world!");

    return;
}
