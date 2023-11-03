#ifndef _NEW_FILE_H
#define _NEW_FILE_H

#include "types.h"

#define FILE_LEN 32
#define D_RESERVED 24
#define B_RESERVED 52
#define DENTRY_NUM 63
#define INODE_NUM 1023
#define BLOCK_SIZE 4096

volatile uint8_t* fd_array[8];

typedef struct dentry_t{
    uint8_t filename[FILE_LEN];
    uint32_t filetype;
    uint32_t inode_index;
    uint8_t reserved[D_RESERVED];
}dentry_t;

typedef struct boot_block_t{
    uint32_t dentry_count;
    uint32_t inode_count;
    uint32_t data_count;
    uint8_t reserved[B_RESERVED];
    dentry_t d_entries[DENTRY_NUM];
}boot_block_t;

typedef struct data_block_t{
    uint8_t data_b[BLOCK_SIZE];
}data_block_t;

typedef struct inode_t{
    uint32_t len;
    uint32_t data[INODE_NUM];
}inode_t;

extern uint32_t get_inode_len(uint32_t inode_idx);
extern int32_t f_close(int32_t fd);
extern int32_t d_close(int32_t fd);
extern void f_init(uint32_t* fs_start);
extern int32_t f_open(const uint8_t* filename);
extern int32_t d_open(const uint8_t* filename);
extern int32_t f_read(int32_t fd, void* buf, int32_t nbytes);
extern int32_t d_read(int32_t fd, void* buf, int32_t nbytes);
extern int32_t f_write(int32_t fd, const void* buf, int32_t nbytes);
extern int32_t d_write(int32_t fd, const void* buf, int32_t nbytes);

extern int32_t read_dentry_by_index(uint32_t index, dentry_t* dentry);
extern int32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry);
extern int32_t read_data(uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length);

#endif
