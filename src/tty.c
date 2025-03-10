#include "../include/tty.h"

// Implementações
size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(enum vga_color font_color, enum vga_color background_color) {
    terminal_color = make_color(font_color, background_color);
    terminal_buffer = (uint16_t*)VGA_MEMORY;

    for(size_t y = 0; y < VGA_HEIGHT; y++) {
        for(size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = make_vgaentry(' ', terminal_color);
        }
    }
}

void terminal_scroll() {
    for(size_t y = 0; y < VGA_HEIGHT-1; y++) {
        for(size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y + 1) * VGA_WIDTH + x];
        }
    }
    terminal_row = VGA_HEIGHT - 1;
}

void terminal_putchar(char c) {
    if(c == '\n') {
        terminal_column = 0;
        if(++terminal_row == VGA_HEIGHT)
            terminal_scroll();
        return;
    }
    
    const size_t index = terminal_row * VGA_WIDTH + terminal_column;
    terminal_buffer[index] = make_vgaentry(c, terminal_color);
    
    if(++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if(++terminal_row == VGA_HEIGHT)
            terminal_scroll();
    }
}

void terminal_write(const char* data, size_t size) {
    for(size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

// Implementação básica do printk
void printk(const char* format, ...) {
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    
    terminal_write(buffer, strlen(buffer));
}