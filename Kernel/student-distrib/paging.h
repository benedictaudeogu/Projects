#ifndef _PAGING_H
#define _PAGING_H

#include "types.h"

#define VID 33
#define START 0
#define SET_DIR 2
#define SET_BITS 3
#define PROGRAM 32
#define K 0x400000
#define D_SIZE 1024
#define SHIFT_TO_8 12
#define T_SIZE 1024
#define ALIGNMENT 4096
#define PADDR 0x800000
#define VADDR 0x8000000
#define KERNEL_OFFSET 12
#define PAGE_NUM_ELEMENTS D_SIZE
#define VIDEO_MEM_PAGE_LOCATION 0xB8000
#define TERM_PAGE_DIR 34
#define T1_VADDR 0xb9000
#define T2_VADDR 0xba000
#define T3_VADDR 0xbb000

extern void init_page();
extern void map_page(uint8_t pid);
extern void map_vidmap();
extern void unmap_vidmap();
extern void term_pages();


typedef struct __attribute__ ((packed)) page_dir_t {
    uint8_t p                 : 1;
    uint8_t r_w               : 1;
    uint8_t u_s               : 1;
    uint8_t pwt               : 1;
    uint8_t pcd               : 1;
    uint8_t acc               : 1;
    uint8_t avl_1             : 1;
    uint8_t ps                : 1;
    uint8_t avl_4             : 4;
    uint32_t addr             : 20;
}page_dir_t;

typedef struct __attribute__ ((packed)) page_table_t {
    uint8_t p                   : 1;
    uint8_t r_w                 : 1;
    uint8_t u_s                 : 1;
    uint8_t pwt                 : 1;
    uint8_t pcd                 : 1;
    uint8_t acc                 : 1;
    uint8_t dirty               : 1;
    uint8_t pat                 : 1;
    uint8_t global              : 1;
    uint8_t avl_3               : 3;
    uint32_t addr               : 20;
}page_table_t;

page_dir_t page_dir[D_SIZE] __attribute__((aligned(ALIGNMENT)));

page_table_t page_table[T_SIZE] __attribute__((aligned(ALIGNMENT)));
page_table_t page_table2[T_SIZE] __attribute__((aligned(ALIGNMENT)));

#endif
