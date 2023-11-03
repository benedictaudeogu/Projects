#ifndef _keyboard_H
#define _keyboard_H

#include "types.h"

#define A_F1 59
#define A_F2 60
#define A_F3 61
#define TWO_D 2
#define SIZE 62
#define START_ 0
#define KEYS_SIZE 128
#define ALT_PRESS 0x38
#define ALT_RELEASE 0xb8
#define SCAN_ZERO 0x0B
#define KEYBOARD_PORT 0x21
#define KEYBOARD_DATA 0x60
#define LPRESS 0x2a
#define LRELEASE 0xaa
#define RPRESS 0x36
#define RRELEASE 0xb6
#define CAPPRESS 0x3a
#define CTRL_P 0x1d
#define CTRL_R 0x9d
#define RELEASE 0x80

volatile int t_flag;

extern void create_keyboard();
extern void keyboard_handler();

#endif
