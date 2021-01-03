/*
*   kernel.cpp
*   Entrypoint to the kernel
*/

/*
*   Video/terminal code synopsis:

1.  Pointer for terminal video buffer at 0xB8000
2.  Place characters at y * vga //width// + x, where video mode is 80x25
    Note: remember - y * VGA_WIDTH + x !
3.  Character placement = vidptr[i] = char | (bitwise or) color << 8 (binary left shift)
3.  Store x and y coord of current character in variables

Definitions to set:
    enum vga_color              16-bit color, int for each
    func vga_entry_color        fg | bg << 4
    func vga_entry              Combine char and color to create entry in video buffer:
                                ch | color << 8
    func terminal_initialize:   Loop over all cols and rows replacing color
    func terminal_setcolor      Change variable
    func terminal_putentryat... Create vga entry in buffer as described above
    func terminal_putchar       Put entry and incriment rows/cols
    func terminal_write         For loop over length parameter, write string
    func terminal_writestring   terminal_write, calc size to pass

Data types:
    vga_color   uint8_t
    vga_entry   uint16_t        (color + char)
    vga_buffer  uint16_t*
    vga_col/row size_t

*/

/*
#ifdef __linux__
#error "You may not be using a cross-compiler and could encounter problems. Please compile for the ix86 architecture."
#endif

#ifndef __i386__
#error "You may not be using a cross-compiler for the i686 or newer x86 architecture and could encounter problems."
#endif
*/

#include "stddefex.hpp"
#include "idt.hpp"
#include "graphics.hpp"
#include "terminal.hpp"

Terminal tty0;

void tty_init(void) {
    uint8_t terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    size_t terminal_width = VGA_WIDTH_DEFAULT;
    size_t terminal_height = VGA_HEIGHT_DEFAULT;
    tty0 = Terminal(terminal_color, terminal_width, terminal_height);
}

extern "C" void kernel_main(void) {
    idt_init();
    tty_init();

    tty0.writestring("Hello, world!");

    return;
}
