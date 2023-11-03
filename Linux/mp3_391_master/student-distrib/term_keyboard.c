#include "term_keyboard.h"
#include "sys_call_handler.h"
#include "paging.h"
#include "lib.h"

/**
 * Open a file for reading
 * 
 * @param filename The name of the file to open.
 * @return 0
 */
int32_t terminal_open(const uint8_t* filename){
    return 0;
}

/**
 * Close the file descriptor
 * 
 * @param fd The file descriptor of the terminal to close.
 * @return Nothing.
 */
int32_t terminal_close(int32_t fd){
    return 0;
}

// /* reads from keyboard buffer into buf */
// /**
//  * It reads from the keyboard buffer into buf
//  * @param fd The file descriptor of the terminal.
//  * @param buf the buffer to read into
//  * @param nbytes the number of bytes to read from the buffer
//  * @return The number of bytes read.
//  */
// int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes){ //reads from keyboard buffer into buf
//     if(buf == NULL) return 0;

//     term_buf[curr_term].i = 0; //why is this here?
//     int8_t* buf_new = (int8_t*)buf;
//     int size = strlen(buf_new);
//     memset(buf, 0, size); //clears buf
    
//     while(term_buf[curr_term].waiting_for_user){}; //waits for input
//     term_buf[curr_term].waiting_for_user = 1;

//     if(nbytes <= term_buf[curr_term].i){
//         memcpy(buf_new, (void*)term_kb[curr_term], nbytes); 
//         buf_new[nbytes] = '\0';
//         memset((void*)term_kb[curr_term], 0, BUF_SIZE);
//         pos_x = nbytes % ROW_SIZE;
//         pos_y = nbytes / ROW_SIZE;
//         return nbytes;
//     }

//     else{
//         memcpy(buf_new, (void*)term_kb[curr_term], term_buf[curr_term].i); 
//         buf_new[nbytes] = '\0';
//         memset((void*)term_kb[curr_term], 0, BUF_SIZE);
//         return term_buf[curr_term].i;
//     }

//     return 0;
// }

/**
 * writes to the screen from buf.
 * @param fd The file descriptor of the terminal.
 * @param buf the buffer to write to the screen
 * @param nbytes The number of bytes to write.
 * @return The number of bytes written to the terminal.
*/
int32_t terminal_write(int32_t fd, const void* buf, int32_t nbytes){
    int j;
    int8_t* buf_new = (int8_t*)buf;
    if(buf_new == NULL) return nbytes;

    if(nbytes > 0){
        j = 0;
        while(j != nbytes){
            if(buf_new[j] == '\n'){
                putc(buf_new[j]);
                j++;
                continue;
            }
            putc(buf_new[j]);
            j++;
        }
    }
    return j;
}

/**
 * It reads from the keyboard buffer into buf
 * @param fd The file descriptor of the terminal.
 * @param buf the buffer to read into
 * @param nbytes the number of bytes to read from the buffer
 * @return The number of bytes read.
 */
int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes){ //reads from keyboard buffer into buf
    if(buf == NULL) return 0;

    term_buf[curr_term].i = 0; //why is this here?
    int8_t* buf_new = (int8_t*)buf;
    int size = strlen(buf_new);
    memset(buf, 0, size); //clears buf
    
    // while(waiting_for_user){}; //waits for input
    // waiting_for_user = 1; 
    while(term_buf[curr_term].waiting_for_user){}; //waits for input
    term_buf[curr_term].waiting_for_user = 1;

    if(nbytes <= term_buf[curr_term].i){
        memcpy(buf_new, (void*)term_kb[curr_term], nbytes); 
        buf_new[nbytes] = '\0';
        memset((void*)term_kb[curr_term], 0, BUF_SIZE);
        pos_x = nbytes % ROW_SIZE;
        pos_y = nbytes / ROW_SIZE; // doesn't work past second row though
        return nbytes;
    }

    else{
        memcpy(buf_new, (void*)term_kb[curr_term], term_buf[curr_term].i); 
        buf_new[nbytes] = '\0';
        memset((void*)term_kb[curr_term], 0, BUF_SIZE);
        return term_buf[curr_term].i;
    }

    return 0;
}
