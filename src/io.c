#ifndef IO_H
#define IO_H

#include "../include/tty.h"
#include "../include/io.h"

// Implementações
void shutdown() {
    outw(0xB004, 0x2000);
    outw(0x604, 0x2000);
    outw(0x4004, 0x3400);
}

void reboot() {
    uint8_t temp;
    asm volatile("cli");
    
    do {
        temp = input_bytes(KBRD_INTRFC);
        if (check_flag(temp, KBRD_BIT_KDATA)) { // Agora reconhece a função
            input_bytes(KBRD_IO);
        }
    } while (check_flag(temp, KBRD_BIT_UDATA));

    output_bytes(KBRD_INTRFC, KBRD_RESET);
    
    while(1) asm volatile("hlt");
}

uint8_t input_bytes(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void output_bytes(uint16_t port, uint8_t val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inw(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__("in %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

void outw(uint16_t port, uint16_t data) {
    __asm__ __volatile__("out %0, %1" : : "a"(data), "d"(port));
}

uint8_t scan(void) {
    static uint8_t key = 0;
    uint8_t read_char = input_bytes(0x60) & 0x7F;
    return (read_char != key) ? (key = read_char) : 0;
}

void move_cursor(int row, int col) {
    unsigned short pos = row * VGA_WIDTH + col;
    output_bytes(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    output_bytes(FB_DATA_PORT, (pos & 0xFF));
    output_bytes(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    output_bytes(FB_DATA_PORT, ((pos >> 8) & 0xFF));
}

void print_prompt(void) {
    printk("\n$ > ");
    move_cursor(get_terminal_row(), get_terminal_col());
}

#endif // _IO_H