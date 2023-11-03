#ifndef _TERM_KEYBOARD_H
#define _TERM_KEYBOARD_H

#include "keyboard.h"
#include "types.h"
#include "lib.h"

#define TOP 0
#define TERMS 3
#define BOTTOM 95
#define ZERO 0x0B
#define DATA 0x60
#define BUF_SIZE 128
#define MAX_CHARS 127
#define FOUR_KB 0x1000
#define ROW_SIZE 80

volatile uint32_t pos_x, pos_y, curr_term, pid_cnt;
volatile char term_kb[TERMS][BUF_SIZE];

typedef struct terminal_t{
    uint32_t i;
    uint32_t save_x;
    uint32_t save_y;
    uint32_t curr_term_ebp;
    uint32_t curr_term_esp;
    uint32_t waiting_for_user;
}terminal_t; 

terminal_t term_buf[TERMS];

extern int32_t terminal_open(const uint8_t* filename);
extern int32_t terminal_close(int32_t fd);
extern int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes);
extern int32_t terminal_write(int32_t fd, const void* buf, int32_t nbytes);

#endif
