/*
*   kernel.cpp
*   Entrypoint to the kernel.
*/

/*
*   Video code synopsis:

1.  Pointer for terminal video buffer at 0xB8000
2.  Place characters at y * vga width + x, where video mode is 80x25
3.  Character placement = vidptr[i] = char | (bitwise or) color << 8 (binary left shift)
3.  Store x and y coord of current character in variables

Definitions to create:
    enum vga_color              16-bit color, int for each
    func vga_entry_color        fg | bg << 4
    func vga_entry              Combine char and color to create entry in video buffer
    func terminal_initialize:   Loop over all cols and rows replacing color
    func terminal_setcolor      Change variable
    func terminal_putentryat... Create vga entry in buffer as described above
    func terminal_putchar       Put entry and incriment rows/cols
    func terminal_write         For loop over length parameter, write string
    func terminal_writestring   terminal_write, calc size to pass

Data types:
    vga_color   uint8_t
    vga_entry   uint16_t [color + char]
    vga_buffer  uint16_t*
    vga_col/row size_t

*/

#include <stddef.h>
#include <stdint.h>
#include "defs.hpp"
#include "string.hpp"
#include "graphics.hpp"
#include "terminal.hpp"

/*
#if defined(__linux__)
#error "You are most likely not using a cross-compiler, problems may occur!"
#endif

#if !defined(__i386__)
#error "This is most likely not being compiled for an i386+ x86-elf target. Please compile for an ix86-elf platform."
#endif
*/

Terminal tty0;

extern "C" void kernel_main(void) {
    uint8_t targetColor = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    
    tty0 = Terminal(targetColor, VGA_WIDTH, VGA_HEIGHT);
    tty0.writestring("Hello, world! ");        // Todo: add newline support

    char buffer[STD_BUFFERSIZE];
    sprintf(buffer, "%d Rows", tty0.getHeight());
    tty0.writestring(buffer);

    return;
}