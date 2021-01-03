/*
*   io.hpp
*/

#ifndef __IO
#define __IO

inline unsigned char inb(unsigned int port) {
    unsigned char ret;
    asm volatile ("inb %dx, %al; outb %al, $0x80" : "=a" (ret) : "d" (port));
    return ret;
}

void outb(unsigned int port, unsigned char value) {
    asm volatile ("outb %%al, %%dx" :: "d" (port), "a" (value));
}

#endif