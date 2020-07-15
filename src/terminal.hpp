/*
*   terminal.hpp
*/

#ifndef TERMINAL
#define TERMINAL

#include <stddef.h>
#include <stdint.h>
#include "graphics.hpp"
#include "string.hpp"

class Terminal {
    private:
        uint16_t* vga_buffer;
        uint8_t terminal_color;
        size_t terminal_width;
        size_t terminal_height;

        size_t terminal_column;
        size_t terminal_row;
    public:
        void configure(uint8_t color, size_t width, size_t height) {
            terminal_color = color;
            terminal_width = width;
            terminal_height = height;
        }
        
        void initialize() {
            vga_buffer = (uint16_t*) 0xB8000;
            terminal_column = 0;
            terminal_row = 0;
            uint16_t entry = vga_entry(' ', terminal_color);

            for (size_t y=0; y < terminal_height; y++) {
                for (size_t x=0; x < terminal_width; x++) {
                    const size_t index = y * terminal_width + x;
                    vga_buffer[index] = entry;
                }
            }
        }

        void setcolor(uint8_t color) {
            terminal_color = color;
        }

        void putentry(char ch, uint8_t color, size_t x, size_t y) {
            uint16_t entry = vga_entry(ch, color);
            const size_t index = y * terminal_width + x;
            vga_buffer[index] = entry;
        }

        void putchar(char ch) {
            putentry(ch, terminal_color, terminal_column, terminal_row);
            if (++terminal_column > terminal_width - 1) {
                terminal_column = 0;
                if (++terminal_row > terminal_height - 1) {
                    terminal_row = 0;
                    // Todo: clear screen
                }
            }
        }

        void write(const char* str, size_t len) {
            for (size_t i=0; i < len; i++)
                putchar(str[i]);
        }

        void writestring(const char* str) {
            write(str, strlen(str));
        }

        size_t getWidth() {
            return terminal_width;
        }

        size_t getHeight() {
            return terminal_height;
        }

        Terminal() {};
        Terminal(uint8_t color, size_t width, size_t height) {
            configure(color, width, height);
            initialize();
        }
};

#endif
