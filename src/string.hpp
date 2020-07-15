/*
*   string.hpp
*/

#ifndef STRING
#define STRING

#include <stddef.h>
#include "defs.hpp"

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

void* memcpy(void* destination, const void* source, size_t size) {
    char* cast_destination = (char*)destination;
    const char* cast_source = (char*)source;

    for (size_t i=0; i<size; i++) {
        cast_destination[i] = cast_source[i];
    }
    return cast_destination;
}

char* reverse_str(char* str) {
    /*
    *   Function synopsis:
    1.  Loop incriment = 0
    2.  Length incriment = strlen -1 to subtract null character from result
    3.  Loop: tmp = str[length inc.], str[length] = str[loop], str[loop] = tmp,
    loop inc. +=1
    length inc. -=1 until the length is finished.

    */
    int loop = 0;
    int length = strlen(str)-1;
    char tmp = 0;
    char* ret = str;

    while (loop < length) {
        tmp = ret[length];
        ret[length] = ret[loop];
        ret[loop] = tmp;

        loop++;
        length--;
    }

    return ret;
}

char* itoa(int value, char* buffer, int base) {
    /*
    *   Function synopsis:
    1.  Check if value is 0 and return exclusive string with 0 null-terminated
    2.  Check if value is less than 0 and base 10 and store as negative
    3.  While the value is not equal to 0, incriment i and append to buffer: if remainder of value module base is more than 10, append value modulo base - 10 + 'a', otherwise append the remainder + '0' (*10)
    4.  Append neative operator to string if negative
    5.  Reverse string
    6.  Return
    */
    int i = 0;
    if (value == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }
    
    bool isNegative = false;
    int valueBuffer = value;
    int rem;
    if (value < 0 && base == 10) {
        isNegative = true;
        valueBuffer = -valueBuffer;
    }
    
    while (valueBuffer > 0) {
        rem = valueBuffer % base;
        buffer[i++] = (rem > 9)? ((rem-10) + 'a') : (rem + '0');
        valueBuffer /= base;
    }

    if (isNegative)
        buffer[i++] = '-';

    buffer[i] = '\0';
    char* reverse = reverse_str(buffer);
    memcpy(&buffer, &reverse, sizeof(buffer));
    return buffer;
}

void sprintf(char* str, const char* format, int value) {
    size_t i;
    int buffer_size = sizeof(str);
    char buffer[buffer_size];
    for (i=0; i<strlen(format); i++) {
        if (format[i] == '%') {
            switch (format[i+1]) {
                case 'd':
                    itoa(value, buffer, 10);
            }
            for (int n=0; n<buffer_size; n++) {
                str[i+n] = buffer[n];
            }
            i++;
        } else {
            str[i] = format[i];
        }
    }
}


/*  Todo: add malloc and memory management
char* sprintf_stdbuffer(const char* format, int value) {
    char* buffer = malloc(STD_BUFFERSIZE);
    sprintf(buffer, format, value);
    return buffer;
}
*/

#endif