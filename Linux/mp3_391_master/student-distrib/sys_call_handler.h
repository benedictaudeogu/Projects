#ifndef _SYS_CALL_HANDLER_H
#define _SYS_CALL_HANDLER_H

#include "types.h"
#include "term_keyboard.h"
#include "RTC.h"
#include "new_file.h"

#define M0 0x7f
#define E1 0x45
#define L2 0x4c
#define F3 0x46
#define MOVE_ESP 4
#define MAX_PID 6
#define MIN_FD_VAL 2
#define START_BIT 24
#define MAX_FILE_NUM 8
#define PROG 0x8000000
#define FLAG_OFF 0x200
#define K_OFFSET 0x2000
#define FOUR_MB 0x400000
#define PAGE_IMG 0x8048000
#define START_KERNEL 0x800000

typedef struct t_funcs_t{
    int32_t (*open_ref)(const uint8_t* filename);
    int32_t (*close_ref)(int32_t fd);
    int32_t (*read_ref)(int32_t fd, void* buf, int32_t nbytes);
    int32_t (*write_ref)(int32_t fd, const void* buf, int32_t nbytes);
}t_funcs_t;

typedef struct fd_t {
    t_funcs_t* file_ops_table;
    uint32_t inode;
    uint32_t file_pos;
    uint32_t flags;
} fd_t;

typedef struct pcb_t {
    fd_t file_array[MAX_FILE_NUM];
    uint8_t pid;
    int8_t parent_id;
    uint32_t saved_esp;
    uint32_t saved_ebp;
    uint32_t execute_ret;
    uint8_t active;
    uint8_t args[128];
} pcb_t;

extern void switch_terminals(uint32_t term_num);

extern pcb_t* get_pcb(int32_t pid);
extern pcb_t* get_cur_pcb();
extern void open_terminals(uint32_t f_key);
extern int32_t close(int32_t fd);
extern int32_t halt(uint8_t status);
extern int32_t open(const uint8_t* filename);
extern int32_t vidmap(uint8_t** screen_start);
extern int32_t execute (const uint8_t* command);
extern int32_t read(int32_t fd, void* buf, int32_t nbytes);
extern int32_t write(int32_t fd, const void* buf, int32_t nbytes);
extern void terminals_init();

#endif
