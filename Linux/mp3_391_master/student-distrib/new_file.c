#include "new_file.h"
#include "types.h"
#include "lib.h"
#include "sys_call_handler.h"

boot_block_t* boot; 
inode_t* i_node;
data_block_t* d_block; 
data_block_t* dblock; //point to current data block
dentry_t cur_dentry;
uint8_t* prev;


void f_init(uint32_t* fs_start){
    /*initialize file system pointers*/
    boot = (boot_block_t*)fs_start; //point to bootblock
    i_node = (inode_t*)(boot + 1);  //point to start of inode segment
    d_block = (data_block_t*)(i_node + boot->inode_count); //point to start of data block segments
}

uint32_t get_inode_len(uint32_t inode_idx){
    return (uint32_t)((i_node + inode_idx)->len);
}

/** f_open
 * @param filename The name of the file to open.
 */
int32_t f_open(const uint8_t* filename){
    if(read_dentry_by_name(filename, (dentry_t*)(&cur_dentry)) == -1) return -1; //check if file exists
    
    return (int32_t)(&cur_dentry);
}

/** f_close
 * @param fd The file descriptor of the file to close.
 */
int32_t f_close(int32_t fd){
    return 0;
}

/** d_open
 * @param filename The name of the file to open.
 */
int32_t d_open(const uint8_t* filename){
    return 0;
}

/** d_close
 * @param fd The file descriptor of the file to close.
 */
int32_t d_close(int32_t fd){
    return 0;
}

/** f_read
 * @param fd file descriptor
 * @param buf buffer to read into
 * @param nbytes the number of bytes to read
 */
int32_t f_read(int32_t fd, void* buf, int32_t nbytes){
    pcb_t* cur_pcb = get_cur_pcb();
    uint32_t inode_idx = cur_pcb->file_array[fd].inode;
    uint32_t offset = cur_pcb->file_array[fd].file_pos;
    int32_t num_bytes = read_data(inode_idx, offset, (uint8_t*)buf, nbytes);
    cur_pcb->file_array[fd].file_pos += nbytes;
    return num_bytes;
}

/** f_write
 * @param fd file descriptor
 * @param buf the buffer to write from
 * @param nbytes The number of bytes to write.
 */
int32_t f_write(int32_t fd, const void* buf, int32_t nbytes){
    return -1;
}

/** d_read
 * @param fd file descriptor
 * @param buf buffer to store the data
 * @param nbytes number of bytes to read
 * copies directory name into buf
 * @return The number of bytes read.
 */
int32_t d_read(int32_t fd, void* buf, int32_t nbytes){
    pcb_t* cur_pcb = get_cur_pcb();
    uint32_t idx = cur_pcb->file_array[fd].file_pos;
    int i = 0;

    if(prev == boot->d_entries[idx].filename){
        return -1;
    }
    else{
        prev = boot->d_entries[idx].filename;
    }

    while(boot->d_entries[idx].filename[i] != '\0' && i < 32){ //loop thru characters
        ((int8_t*)buf)[i] = boot->d_entries[idx].filename[i];
        i++;
    }
    ((int8_t*)buf)[i] = '\0';

    cur_pcb->file_array[fd].file_pos += 1;
    return i;
    // return -1;

}

/** d_write
 * @param fd file descriptor
 * @param buf the buffer to write from
 * @param nbytes The number of bytes to write.
 */
int32_t d_write(int32_t fd, const void* buf, int32_t nbytes){
    return -1;
}

/** read_dentry_by_name
 * This function takes in a file name and a dentry pointer and traverses the directory in the bootblock
 * to find the name of the file
 * 
 * @param fname the name of the file we want to find
 * @param dentry a pointer to a dentry_t struct
 */
int32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry){ //traverses dir in bootblock to find name of file
    int idx;

    if(fname == NULL || strlen((const int8_t*)fname) > FILE_LEN || strlen((const int8_t*)fname) == 0 || dentry == NULL) return -1;

    idx = 0;
    while(idx < DENTRY_NUM){
        if(strncmp((const int8_t*)fname, (const int8_t*)boot->d_entries[idx].filename, FILE_LEN) == 0){
            read_dentry_by_index(idx, dentry);
            return 0;
        }
        idx++;
    }
    
    return -1; //invalid file name
}

/** read_dentry_by_index
 * @param index the index of the dentry you want to read
 * @param dentry the dentry struct that we want to fill in
 * 
 * return if file not valid
 */
int32_t read_dentry_by_index(uint32_t index, dentry_t* dentry){
    if(index >= DENTRY_NUM || dentry == NULL) return -1;

    strncpy((int8_t*)dentry->filename, (const int8_t*)boot->d_entries[index].filename, FILE_LEN); //copy file name
    dentry->filetype = boot->d_entries[index].filetype; //copy file type
    dentry->inode_index = boot->d_entries[index].inode_index; //copy inode #

    return 0;
}

/** read_data
 * @param inode the inode number of the file to read from
 * @param offset the offset in bytes from the beginning of the first data block
 * @param buf the buffer to write the data to
 * @param length the number of bytes to read
 * 
 * @return The number of bytes read.
 */
int32_t read_data(uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length){
    int i, start;
    inode_t* inode_num = i_node + inode; //points to current inode
    uint32_t file_size = inode_num->len; //get size of file
    uint32_t block_num = offset / BLOCK_SIZE; //get block number to start reading from
    dblock = d_block + inode_num->data[block_num]; //first data block to read from
    uint32_t start_idx = offset % BLOCK_SIZE; //get offset into block
    start = start_idx; //keep track of how many bytes we have read

    if(inode < 0  || inode > boot->inode_count || buf == NULL || file_size/BLOCK_SIZE > boot->data_count){ //param checks
        return -1;
    }

    if(offset >= file_size){
        return 0;
    }

    if(length > file_size){ //check if length is greater than file size
        length = file_size - offset;
    }
    uint32_t end_idx = start_idx + length; //get end of read

    i = 0;
    while(start != end_idx){
        if(start_idx == BLOCK_SIZE){ //for cases where acessing more than one block
            block_num++; //want to go to the next block num
            start_idx = 0; //reset start index
            dblock = d_block + inode_num->data[block_num];
        }

        buf[i] = dblock->data_b[start_idx]; //copy data from block
        start_idx++;
        start++;
        i++;
    }

    return length; //modified so can always return this
}

