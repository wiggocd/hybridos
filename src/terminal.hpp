/*
*   terminal.hpp
*   Functions and definitions for the command line.
*/

#ifndef __TERMINAL
#define __TERMINAL

#include "graphics.hpp"
#include "string.hpp"
#include "stddef.h"

class Terminal {
    private:
        uint16_t* vga_buffer;
        uint8_t color;
        size_t width;
        size_t height;
        unsigned int column;
        unsigned int row;
    public:
        void setcolor(uint8_t _color) {
            color = _color;
        }

        void configure(uint8_t _color, size_t _width, size_t _height) {
            color = _color;
            width = _width;
            height = _height;
        }

        void initialize() {
            vga_buffer = (uint16_t*) VGA_BUFFER_DEFAULT;
            column = 0;
            row = 0;
            uint16_t entry = vga_entry(' ', color);

            for (size_t y = 0; y < height; y++) {
                for (size_t x = 0; x < width; x++) {
                    vga_buffer[y * width + x] = entry;
                }
            }
        }

        void putentry(uint16_t entry, unsigned int x, unsigned int y) {
            uint16_t index = y * width + x;
            vga_buffer[index] = entry;
        }

        void putchar(unsigned char ch) {
            uint16_t entry = vga_entry(ch, color);
            putentry(entry, column, row);
            if (++column > width - 1) {
                column = 0;
                row++;
                if (++row > height - 1) {
                    /* TODO: Impliment scroll later on down the line */
                    initialize();
                }
            }
        }

        void write(const char* str, size_t len) {
            for (size_t i = 0; i < len; i++) {
                putchar(str[i]);
            }
        }

        void writestring(const char* str) {
            write(str, strlen(str));
        }

        Terminal() {};
        Terminal(uint8_t _color, size_t _width, size_t _height) {
            configure(_color, _width, _height);
            initialize();
        }
};

#endif
