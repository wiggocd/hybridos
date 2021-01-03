/*
*   stdio.h
*/

#ifndef __STDIO
#define __STDIO

#include "string.hpp"
#include "terminal.hpp"
#include <stdarg.h>

#define MAX_BUFFER 1024

/* Currently nonfunctional */
int sprintf(char* buffer, const char* format, ...) {
    va_list args;
    va_start(args, format);

    const size_t len = strlen(format); 

    for (unsigned int i=0; i<len; i++) {
        if (i < len - 1) {
            if (format[i] == '%') {
                if (format[i+1] == 's') {
                    const char* str_arg = va_arg(args, char*);
                    for (unsigned int j=0; i<strlen(str_arg); i++) {
                        buffer[i] += str_arg[j];
                    }
                    i++;
                }
                if (format[i+1] == 'd') {
                    int n = va_arg(args, int);
                    buffer[i] += '0' + n;
                    i++;
                } else {
                    buffer[i] = format[i];
                }
            } else {
                buffer[i] = format[i];
            }
        } else {
            buffer[i] = format[i];
        }
    }

    return 0;
}

void printf(const char* str, ...) {
    va_list args;
    va_start(args, str);

    const size_t len = strlen(str);
    char buffer[len + MAX_BUFFER];

    sprintf(buffer, str, args);
    current_terminal.writestring(buffer);
}

#endif