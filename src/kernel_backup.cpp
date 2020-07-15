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

/*
#if defined(__linux__)
#error "You are most likely not using a cross-compiler, problems may occur!"
#endif

#if !defined(__i386__)
#error "This is most likely not being compiled for an i386+ x86-elf target. Please compile for an ix86-elf platform."
#endif
*/

enum vga_color {
    /* Black, blue, green, cyan, red, magenta, brown, light grey, dark grey, light- blue back through brown, white */
    VGA_COLOR_BLACK     = 0,
    VGA_COLOR_BLUE      = 1,
    VGA_COLOR_GREEN     = 2,
    VGA_COLOR_CYAN      = 3,
    VGA_COLOR_RED       = 4,
    VGA_COLOR_MAGENTA   = 5,
    VGA_COLOR_BROWN     = 6,
    VGA_COLOR_LIGHT_GREY    = 7,
    VGA_COLOR_DARK_GREY     = 8,
    VGA_COLOR_LIGHT_BLUE    = 9,
    VGA_COLOR_LIGHT_GREEN   = 10,
    VGA_COLOR_LIGHT_CYAN    = 11,
    VGA_COLOR_LIGHT_RED     = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN   = 14,
    VGA_COLOR_WHITE     = 15
};

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

typedef pos vga_size;
typedef pos vga_pos;


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char ch, uint8_t color) {
    return (uint16_t)ch | (uint16_t)color << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

uint16_t* terminal_buffer;
uint8_t terminal_color;
vga_size terminal_size;
vga_pos terminal_pos;

void terminal_initialize(uint16_t* vga_buffer, uint8_t color, vga_size size, vga_pos pos) {
    vga_buffer = (uint16_t*)0xB8000;
    pos = vga_pos(0, 0);
    uint16_t entry = vga_entry(' ', color);

    for (size_t y=0; y < size.y; y++) {
        for (size_t x=0; x < size.x; x++) {
            const size_t index = y * size.y + x;
            vga_buffer[index] = entry;
        }
    }
}

void terminal_putentry(uint16_t* vga_buffer, uint16_t entry, vga_pos pos, vga_size vgasize) {
    const size_t index = pos.y * vgasize.y + pos.x;
    vga_buffer[index] = entry;
}

void terminal_putchar(uint16_t* vga_buffer, uint16_t entry, vga_pos pos, vga_size vgasize, uint8_t color) {
    terminal_putentry(vga_buffer, entry, pos, vgasize);
    if (++pos.x > vgasize.x - 1) {
        pos.x = 0;
        if (++pos.y > vgasize.y - 1) {
            pos.y = 0;
        }
    }
}

void terminal_write(uint16_t* vga_buffer, const char* str, size_t str_size, vga_pos pos, vga_size vgasize, uint8_t color) {
    for (size_t i=0; i < str_size; i++)
        terminal_putchar(vga_buffer, str[i], pos, vgasize, color);
}

size_t strlen(const char* str) {
    size_t length = 0;
    while (str[length])
        length++;
    return length;
}

void terminal_writestring(uint16_t* vga_buffer, const char* str, vga_pos pos, vga_size vgasize, uint8_t color) {
    terminal_write(vga_buffer, str, strlen(str), pos, vgasize, color);
}



/////////////////////////////////////////////////////////////////

void mainterminal_configure(uint8_t color, vga_size size) {
    terminal_color = color;
    terminal_size = size;
}

void mainterminal_initialize() {
    terminal_initialize(terminal_buffer, terminal_color, terminal_size, terminal_pos);
}

void mainterminal_write(const char* str, size_t str_size, vga_pos pos) {
    terminal_write(terminal_buffer, str, str_size, pos, terminal_size, terminal_color);
}

void mainterminal_writestring(const char* str) {
    terminal_writestring(terminal_buffer, str, terminal_pos, terminal_size, terminal_color);
}

void mainterminal_setcolor(uint8_t color) {
    terminal_color = color;
}

/////////////////////////////////////////////////////////////////


extern "C" void kernel_main(void) {
    uint8_t targetColor = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_size targetSize = vga_size(VGA_WIDTH, VGA_HEIGHT);

    mainterminal_configure(targetColor, targetSize);
    mainterminal_initialize();
    mainterminal_writestring("Hello, world!\n");

    return;
}