/*
*   graphics.hpp
*   Graphics/video code.
*/

#ifndef __GRAPHICS
#define __GRAPHICS

#include <stddef.h>

static const uint16_t* VGA_BUFFER_DEFAULT = (uint16_t*) 0xB8000;
static const size_t VGA_WIDTH_DEFAULT = 80;
static const size_t VGA_HEIGHT_DEFAULT = 25;

enum VGA_COLOR {
    /* Black, blue, green, cyan, red, magenta, brown */
    /* Light grey, dark grey, light blue, light green, light cyan, light red, light magenta, light brown */
    /* White */
    VGA_COLOR_BLACK         = 0,
    VGA_COLOR_BLUE          = 1,
    VGA_COLOR_GREEN         = 2,
    VGA_COLOR_CYAN          = 3,
    VGA_COLOR_RED           = 4,
    VGA_COLOR_MAGENTA       = 5,
    VGA_COLOR_BROWN         = 6,
    VGA_COLOR_LIGHT_GREY    = 7,
    VGA_COLOR_DARK_GREY     = 8,
    VGA_COLOR_LIGHT_BLUE    = 9,
    VGA_COLOR_LIGHT_GREEN   = 10,
    VGA_COLOR_LIGHT_CYAN    = 11,
    VGA_COLOR_LIGHT_RED     = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN   = 14,
    VGA_COLOR_WHITE         = 15
};

static inline uint16_t vga_entry(unsigned char ch, uint8_t color) {
    return (uint16_t) ch | (uint16_t) color << 8;
}

static inline uint8_t vga_entry_color(uint8_t fg, uint8_t bg) {
    return fg | bg << 4;
}

#endif
