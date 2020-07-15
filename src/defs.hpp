/*
*   defs.hpp
*/

#ifndef DEFS
#define DEFS

#include <stddef.h>
#include <stdint.h>

struct pos {
    size_t x;
    size_t y;
    public:
        pos() {};
        pos(size_t _x, size_t _y) {
            x = _x;
            y = _y;
        };
};

struct vga_pos {
    size_t column;
    size_t row;
    public:
        vga_pos() {};
        vga_pos(size_t _column, size_t _row) {
            column = _column;
            row = _row;
        };
};

struct size {
    size_t width;
    size_t height;
    public:
        size() {};
        size(size_t _width, size_t _height) {
            width = _width;
            height = _height;
        };
};

typedef uint16_t vgaentry;
typedef size vga_size;

static const size_t STD_BUFFERSIZE = 128;

#endif