#include "sys_call_handler.h"
#include "term_keyboard.h"
#include "new_file.h"
#include "x86_desc.h"
#include "paging.h"
#include "types.h"
#include "lib.h"
#include "scheduler.h"

pcb_t* pcb;
int32_t next_available_pcb_idx = 0;
uint8_t available_indices[] = {0, 0, 0, 0, 0, 0};
uint8_t term_initialized[] = {0, 0, 0};
pcb_t* pcb_arr[] = {0, 0, 0};

t_funcs_t terminal_funcs = {terminal_open, terminal_close, terminal_read, terminal_write};
t_funcs_t rtc_funcs = {rtc_open, rtc_close, rtc_read, rtc_write};
t_funcs_t dir_funcs = {d_open, d_close, d_read, d_write};
t_funcs_t f_funcs = {f_open, f_close, f_read, f_write};

/**
 * It returns the first index in the array `available_indices` that is 0
 * 
 * @return The index of the next available index in the array.
 */
int32_t find_next_available_idx(){
    int i;  
    for(i = 0; i < 6; i++){
        if(available_indices[i] == 0){
            return i;
        }
    }
    return -1;
}

/** get_pcb
 * @param pid the pid of the process
 * @return The address of the PCB of the process with the given pid.
 */
pcb_t* get_pcb(int32_t pid){
    return (pcb_t*)(PADDR - K_OFFSET * (pid + 1)); //8MB - 8KB - 8KB*pid
}

/** get_cur_pcb
 * @return The address of the pcb struct
 */
pcb_t* get_cur_pcb(){
    return pcb;
}

/** get_kernel_stack
 * @param pid the process id of the process
 * @return The address of the kernel stack of the process with the given pid.
 */
int32_t get_kernel_stack(int32_t pid){
    return (int32_t)(PADDR - K_OFFSET * pid - MOVE_ESP); //8MB - 8KB*pid - 0x4
}

/** halt
 * halt a user program
 * @param status the status code to return to the parent process
 * @return The return value of the function that called halt.
 */
int32_t halt(uint8_t status){  
    uint32_t temp_ebp = pcb->saved_ebp;
    uint32_t temp_esp = pcb->saved_esp;

    available_indices[pcb->pid] = 0;
    if(pcb->parent_id == -1){
        pcb_arr[curr_term] = 0;
        // next_available_pcb_idx--;
        available_indices[pcb->pid] = 0;
        printf("Can't exit base shell\n");
        execute((uint8_t*)"shell");
    }
    else{
        pcb_arr[curr_term] = pcb;
    }

    int i;
    for(i = 0; i < 8; i++){
        pcb->file_array[i].flags = 0;
    }
    pcb->active = 0;

    tss.ss0 = KERNEL_DS;
    tss.esp0 = get_kernel_stack(pcb->parent_id);
    map_page(pcb->parent_id);
    pcb = get_pcb(pcb->parent_id);  // switch to parent pcb
    next_available_pcb_idx--;
    
    //restore esp, ebp to pre execute form to end current execute
    asm volatile ("                         \n\
        movl %0, %%esp                      \n\
        movl %1, %%ebp                      \n\
        movb %2, %%al                       \n\
        jmp exeret                          \n\
        "
        :
        : "r"(temp_esp), "r"(temp_ebp), "r"(status)
        : "memory"
    );

    return -1;  // shouldn't return
}

/** execute
 * executes a user program
 * @param command the command to execute
 * @return The return value of the user program.
 */
int32_t execute(const uint8_t* command){
    uint32_t eip_addr; 
    uint32_t esp_addr;
    uint8_t* p_img;
    uint8_t fname[PROGRAM];
    uint8_t buf[4];
    uint8_t args_buf[128];
    int32_t i;
    int32_t j;
    int32_t temp_pid;

    if(command == NULL) return -1;
    i = 0;
    while(command[i] == ' '){
        i++;
    }
    j = 0;
    while(command[i] != ' ' && command[i] != '\0'){
        fname[j] = command[i]; //program to run
        i++;
        j++;
    }
    fname[j] = '\0';
    j = 0;
    if(command[i] == '\0'){
        args_buf[j] = '\0';
    }
    else{
        i++;
        while(command[i] == ' '){
        i++;
        }
        while(command[i] != '\0'){
            args_buf[j] = command[i];
            j++;
            i++;
        }
        args_buf[j] = '\0';
    }
    
    dentry_t dentry;
    if(read_dentry_by_name(fname, &dentry) == -1) return -1; //check if file exists
    if(read_data(dentry.inode_index, 0, buf, 4) == -1) return -1;
    if(buf[0] != M0 || buf[1] != E1 || buf[2] != L2 || buf[3] != F3) return -1; //check if file is executable
    read_data(dentry.inode_index, START_BIT, buf, 4);
    eip_addr = *(uint32_t*)buf; //start of user program, virtual addr

    esp_addr = (uint32_t)(PROG + FOUR_MB - MOVE_ESP); // start of user program's stack, 128MB + 4MB, virtual

    if(find_next_available_idx() == -1) {
        printf("Can't open more than 6 processes\n");
        return -1; //cant have more than 6 processes
    }
    if(pcb != NULL){
        temp_pid = pcb->pid;
    }
    else{
        temp_pid = -1;
    }
    pcb = get_pcb(find_next_available_idx());
    pcb_arr[curr_term] = pcb;

    pcb->pid = find_next_available_idx();
    available_indices[find_next_available_idx()] = 1;

    pcb->parent_id = temp_pid;
    
    map_page(pcb->pid); 

    p_img = (uint8_t*)PAGE_IMG;
    read_data(dentry.inode_index, 0, p_img, get_inode_len(dentry.inode_index));
    
    register uint32_t save_esp asm("esp");
    register uint32_t save_ebp asm("ebp");

    //allocate pcb
    pcb->saved_ebp = save_ebp;
    pcb->saved_esp = save_esp;
    
    pcb->file_array[0].file_ops_table = &terminal_funcs;
    pcb->file_array[0].flags = 1;

    pcb->file_array[1].file_ops_table = &terminal_funcs;
    pcb->file_array[1].flags = 1;
    
    pcb->active = 1;

    tss.ss0 = KERNEL_DS;
    tss.esp0 = get_kernel_stack(pcb->pid);   
    strcpy((int8_t*)(pcb->args), (int8_t*)args_buf); 

    /* Assembly code that is executed when a user program is called. It sets up the stack
    and the registers for the user program. */
    asm volatile ("                                     \n\
        cli                                             \n\
        pushl %0                                        \n\
        pushl %1                                        \n\
        pushfl                                          \n\
        popl %%ebx                                      \n\
        orl %4, %%ebx                                   \n\
        pushl %%ebx                                     \n\
        pushl %2                                        \n\
        pushl %3                                        \n\
        sti                                             \n\
        iret                                            \n\
        exeret:                                         \n\
        leave                                           \n\
        ret"
        : 
        : "r"(USER_DS), "r"(esp_addr), "r"(USER_CS), "r"(eip_addr), "r"(FLAG_OFF)
        //: "r"(esp_addr), "r"(eip_addr), "r"(0x200)
        : "memory"
    );

    return -1; //should never reach
}

/** vidmap
 * This function maps the video memory to the virtual address space of the calling process
 * @param screen_start The address of the pointer to the virtual address of the video memory.
 * @return The virtual address of the video memory.
 */
int32_t vidmap(uint8_t** screen_start){
    if(screen_start == NULL || screen_start < (uint8_t**)PROG || screen_start >= (uint8_t**)(PROG + FOUR_MB)) return -1; //check if valid address
    map_vidmap(); //map page

    *screen_start = (uint8_t*)(PROG + FOUR_MB); //virtual addr 128 + 4
    
    return 0;
}

/** getargs
 * @param buf buffer to read input arguments to
 * @param nbytes bytes of args
 * @return 0 on success -1 on failure
 * */
int32_t getargs (uint8_t* buf, int32_t nbytes){
    if (buf == NULL || nbytes <= 0){
        return -1;
    }

    if (pcb->args == '\0' || strlen((int8_t*)(pcb->args)) > nbytes || strlen((int8_t*)(pcb->args)) == 0){
        return -1;
    }

    int i;
    for (i = 0; i < nbytes; i++){
        if (pcb->args[i] == '\0'){
            buf[i] = '\0';
            break;
        }
        buf[i] = pcb->args[i];
    }
    return 0;
}

/** open
 * opens a file and returns the file descriptor.
 * @param filename the name of the file to open
 * @return The index of the file in the file array.
 */
int32_t open(const uint8_t* filename){
    dentry_t temp;
    int i;
    if(read_dentry_by_name(filename, &temp) == -1) return -1;

    for(i = 0; i < MAX_FILE_NUM; i++){
        if(pcb->file_array[i].flags == 0){ //finds first available
            pcb->file_array[i].flags = 1;
            pcb->file_array[i].file_pos = 0;
            break;
        }
    }
    if(i == 8){
        return -1;
    }

    if(temp.filetype == 0){ //RTC
        pcb->file_array[i].inode = NULL;
        pcb->file_array[i].file_ops_table = &rtc_funcs;
    }

    else if(temp.filetype == 1){ //directory
        pcb->file_array[i].inode = NULL;
        pcb->file_array[i].file_ops_table = &dir_funcs;
    }

    else if(temp.filetype == 2){ //file
        pcb->file_array[i].inode = temp.inode_index;
        pcb->file_array[i].file_ops_table = &f_funcs;
    }
    
    return i;
}

/** close
 * closes the file descriptor.
 * @param fd the file descriptor of the file to be closed
 * @return The return value is the file descriptor of the file that was opened.
 */
int32_t close(int32_t fd){
    if(fd < MIN_FD_VAL || fd>= MAX_FILE_NUM) return -1;
    if(pcb->file_array[fd].flags == 0) return -1;
    // if(pcb->file_array[fd].file_ops_table->close_ref(fd) != 0) return -1;
    pcb->file_array[fd].flags = 0;

    return 0;
}   

/** read
 * reads nbytes of data from the file specified by fd into the buffer pointed to by buf
 * @param fd file descriptor
 * @param buf the buffer to read into
 * @param nbytes the number of bytes to read
 * @return The number of bytes read.
 */
int32_t read(int32_t fd, void* buf, int32_t nbytes){
    int num_bytes;

    if(fd < 0 || fd >= MAX_FILE_NUM) return -1;
    if(fd == 1) return -1; //stdout should not read
    if(buf == NULL || nbytes <= 0) return -1;
    if(pcb->file_array[fd].flags == 0) return -1;

    num_bytes = pcb->file_array[fd].file_ops_table->read_ref(fd, buf, nbytes);
    if(num_bytes == -1) return -1;

    //pcb->file_array[fd].file_pos += num_bytes; //update file position after every read
    return num_bytes;
}

/** write
 * call the write function in the file's file_ops_table
 * @param fd file descriptor
 * @param buf the buffer to write from
 * @param nbytes the number of bytes to write
 * @return The number of bytes written.
 */
int32_t write(int32_t fd, const void* buf, int32_t nbytes){
    if(fd < 0 || fd >= MAX_FILE_NUM) return -1;
    if(fd == 0) return -1; //stdin should not write
    
    if(buf == NULL || nbytes <= 0) return -1;
    if(pcb->file_array[fd].flags == 0) return -1;
    if(pcb->file_array[fd].file_ops_table->write_ref(fd, buf, nbytes) == -1) return -1;

    return nbytes;
}


/**
 * It initializes the terminal buffer, sets the current terminal to 0, and calls the term_pages
 * function
 */
void terminals_init(){
    term_buf[0] = (terminal_t){0, -1, -1, -1, -1, 1};
    term_buf[1] = (terminal_t){0, -1, -1, -1, -1, 1};
    term_buf[2] = (terminal_t){0, -1, -1, -1, -1, 1};
    curr_term = 0;
    term_pages();
}

/**
 * This function is called when the user presses the alt key and a number key. It saves the current
 * terminal's screen, then loads the new terminal's screen. It also saves the current terminal's esp
 * and ebp, then loads the new terminal's esp and ebp
 * 
 * @param term_num the terminal number that we want to switch to
 * 
 * @return The address of the terminal buffer
 */
void switch_terminals(uint32_t term_num){
    memcpy((void*)(T1_VADDR + (curr_term * FOUR_KB)), (void*)VIDEO_MEM_PAGE_LOCATION, FOUR_KB);

    //same terminal, maxed out processes
    if(curr_term == term_num || pid_cnt == 6) return; 
   
    //save current terminal
    register uint32_t save_esp asm("esp");
    register uint32_t save_ebp asm("ebp");

    term_buf[curr_term].curr_term_esp = save_esp;
    term_buf[curr_term].curr_term_ebp = save_ebp;

    term_buf[curr_term].save_x = get_screen_x();
    term_buf[curr_term].save_y = get_screen_y();

    curr_term = term_num;

    //save old terminal screen, display the new terminal screen
    memcpy((void*)VIDEO_MEM_PAGE_LOCATION, (void*)(T1_VADDR + (term_num * FOUR_KB)), FOUR_KB);

    if(pcb_arr[curr_term] == 0){
        clear();
        execute((uint8_t*)"shell"); 
    }
    set_pos(term_buf[curr_term].save_x, term_buf[curr_term].save_y);
    update_cursor(term_buf[curr_term].save_x, term_buf[curr_term].save_y);

    //context switch
    asm volatile ("                         \n\
        movl %0, %%esp                      \n\
        movl %1, %%ebp                      \n\
        jmp exeret                          \n\
        "
        :
        : "r"(term_buf[term_num].curr_term_esp), "r"(term_buf[term_num].curr_term_ebp)
        : "memory"
    );
}
