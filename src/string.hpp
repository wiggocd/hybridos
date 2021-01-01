/*
*   string.hpp
*   String-related definitions and functions
*/

#ifndef __STRING_EX
#define __STRING_EX

#include <stddef.h>

size_t strlen(const char* str) {
    int len = 0;
    while (str[len])
        len++;
    return len;
}

#endif
