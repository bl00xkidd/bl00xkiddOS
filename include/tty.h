#ifndef _TTY_H
#define _TTY_H

#include "../include/string.h"
#include "../include/io.h"
#include "../include/bool.h"
#include "../include/kbd.h"

enum vga_color {
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_LIGHT_BLUE
};

// Variáveis globais
extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;

#include <stddef.h>

// Endereço VGA como macro
#define VGA_MEMORY ((uint16_t*)0xB8000)

// Declarações consistentes
extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;

// Protótipos simplificados
void terminal_init(enum vga_color fg, enum vga_color bg);
void terminal_putchar(char c);
void printk(const char* fmt, ...);

// Funções auxiliares
static inline uint8_t make_color(enum vga_color fg, enum vga_color bg) {
    return fg | (bg << 4);
}

static inline uint16_t make_vgaentry(char c, uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}

#endif // _TTY_H