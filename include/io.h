#ifndef _IO_H
#define _IO_H

#include "../include/tty.h"

// Constantes para portas e comandos
#define KBRD_INTRFC 0x64
#define KBRD_IO 0x60
#define KBRD_RESET 0xFE
#define KBRD_BIT_KDATA 0x01
#define KBRD_BIT_UDATA 0x02
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
#define FB_LOW_BYTE_COMMAND 0x0F
#define FB_HIGH_BYTE_COMMAND 0x0E
#define VGA_WIDTH 80

// Funções básicas de I/O
void shutdown();
void reboot();
uint8_t input_bytes(uint16_t port);
void output_bytes(uint16_t port, uint8_t val);
uint8_t inw(uint16_t port);
void outw(uint16_t port, uint16_t data);
uint8_t scan(void);
void move_cursor(int row, int col);
void print_prompt(void);

#endif // _IO_H