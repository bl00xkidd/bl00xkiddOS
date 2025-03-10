#ifndef _DEFINE_KBSTATP_0X64_KBD_CONTRO_H_
#define _DEFINE_KBSTATP_0X64_KBD_CONTRO_H_

#include <stdint.h>

#define KBSTATP 0x64
#define KBS_DIB 0x01
#define KBDATAP 0x60
#define BACKSPACE 0x0E
#define ENTER 0x1C
#define NO 0
#define SHIFT (1 << 0)
#define CTL (1 << 1)
#define ALT (1 << 2)
#define CAPSLOCK (1 << 3)
#define NUMLOCK (1 << 4)
#define SCROLLLOCK (1 << 5)
#define E0ESC (1 << 6)

// Special keycodes
#define KEY_HOME 0xE0
#define KEY_END 0xE1
#define KEY_UP 0xE2
#define KEY_DN 0xE3
#define KEY_LF 0xE4
#define KEY_RT 0xE5
#define KEY_PGUP 0xE6
#define KEY_PGDN 0xE7
#define KEY_INS 0xE8
#define KEY_DEL 0xE9

// C('A') == Control-A
#define C(x) (x - '@')

extern uint8_t shiftcode[256];
extern uint8_t togglecode[256];
extern uint8_t normalmap[256];
extern uint8_t capslockmap[256];
extern uint8_t shiftmap[256];
extern uint8_t ctlmap[256];

void kbd_init(void);
uint8_t kbd_getc(void);

#endif  // _DEFINE_KBSTATP_0X64_KBD_CONTRO_H_