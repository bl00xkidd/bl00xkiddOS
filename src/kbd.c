#include "kbd.h"
#include <stdint.h>

// Global variable declarations
uint8_t shift_state;
uint8_t toggle_state;

uint8_t shiftcode[256] = {
    [0x1D] = CTL,
    [0x2A] = SHIFT,
    [0x36] = SHIFT,
    [0x38] = ALT,
    [0x9D] = CTL,
    [0xB8] = ALT
};

uint8_t togglecode[256] = {
    [0x3A] = CAPSLOCK,
    [0x45] = NUMLOCK,
    [0x46] = SCROLLLOCK
};

uint8_t normalmap[256] = {
    NO, 0x1B, '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', '\n', NO, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', NO, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', NO, '*'
};

uint8_t capslockmap[256] = {
    NO, 0x1B, '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '{', '}', '\n', NO, 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
    '\'', '`', NO, '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', NO, '*'
};

uint8_t shiftmap[256] = {
    NO, 033, '!', '@', '#', '$', '%', '^',
    '&', '*', '(', ')', '_', '+', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '{', '}', '\n', NO, 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
    '"', '~', NO, '|', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', '<', '>', '?', NO, '*'
};

uint8_t ctlmap[256] = {
    NO, NO, NO, NO, NO, NO, NO, NO,
    NO, NO, NO, NO, NO, NO, NO, NO,
    C('Q'), C('W'), C('E'), C('R'), C('T'), C('Y'), C('U'), C('I'),
    C('O'), C('P'), NO, NO, '\r', NO, C('A'), C('S'),
    C('D'), C('F'), C('G'), C('H'), C('J'), C('K'), C('L'), NO,
    NO, NO, NO, C('\\'), C('Z'), C('X'), C('C'), C('V'),
    C('B'), C('N'), C('M'), NO, NO, C('/'), NO, NO
};

// Function to read a byte from a port
uint8_t inb(uint16_t port) {
    uint8_t data;
    asm volatile ("inb %1, %0" : "=a"(data) : "dN"(port));
    return data;
}

// Initialize keyboard state
void kbd_init() {
    shift_state = 0;
    toggle_state = 0;
}

// Get a character from the keyboard
uint8_t kbd_getc() {
    while (!(inb(KBSTATP) & KBS_DIB)); // Wait until the buffer has data

    uint8_t scancode = inb(KBDATAP);
    if (scancode & 0x80) { // Key release
        scancode &= 0x7F;
        if (shiftcode[scancode]) {
            shift_state &= ~shiftcode[scancode];
        }
    } else { // Key press
        if (shiftcode[scancode]) {
            shift_state |= shiftcode[scancode];
            return NO;
        }

        if (togglecode[scancode]) {
            toggle_state ^= togglecode[scancode];
            return NO;
        }

        uint8_t c;
        if (shift_state & SHIFT) {
            c = shiftmap[scancode];
        } else if (shift_state & CTL) {
            c = ctlmap[scancode];
        } else if (toggle_state & CAPSLOCK) {
            c = capslockmap[scancode];
        } else {
            c = normalmap[scancode];
        }

        return c;
    }
    return NO;
}