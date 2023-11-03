#include "paging.h"
#include "types.h"
#include "load_paging.h"


/** init_page
*  Assert that we only access memory we are allowed to access
*  return: none
*/
void init_page(){
/* old init_page */
    int i;
    for (i = 0; i < PAGE_NUM_ELEMENTS; i++){   
        page_dir[i].p = 0;
        page_dir[i].r_w = 1;
        page_dir[i].u_s = 0;
        page_dir[i].pwt = 0;
        page_dir[i].pcd = 0;
        page_dir[i].acc = 0; 
        page_dir[i].avl_1 = 0;
        page_dir[i].ps = 0;
        page_dir[i].avl_4 = 0;
        page_dir[i].addr = 0;
    }

    for (i = 0; i < PAGE_NUM_ELEMENTS; i++){
        page_table[i].p = 0; //is present 1 or 0 for video memory page table
        page_table[i].r_w = 1;
        page_table[i].u_s = 0;
        page_table[i].pwt = 0;
        page_table[i].pcd = 0;
        page_table[i].acc = 0; 
        page_table[i].dirty = 0; 
        page_table[i].pat = 0;
        page_table[i].global = 0;
        page_table[i].avl_3 = 0;
        page_table[i].addr = 0;  
    }

    //chop off first 12 bits so B8000 to B8
    page_table[VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8].p = 1;
    page_table[VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8].r_w = 1;
    page_table[VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8].addr = VIDEO_MEM_PAGE_LOCATION  >> SHIFT_TO_8;
    
    //first entry is table page
    page_dir[0].p = 1;
    page_dir[0].u_s = 0;
    page_dir[0].addr = (uint32_t)(page_table) >> SHIFT_TO_8;

    //second entry is kernel page
    page_dir[1].p = 1;
    page_dir[1].ps = 1; //set page size to 1 because kernel at 4 MB
    page_dir[1].addr = K >> KERNEL_OFFSET;
    
    loadPageDirectory(page_dir);
    enablePaging();
}

/**
 * map_page
 * @param pid process id
 * return: none
 */
void map_page(uint8_t pid){
    //map 128MB virtual to 8MB physical
    page_dir[PROGRAM].p = 1;
    page_dir[PROGRAM].u_s = 1;
    page_dir[PROGRAM].ps = 1; 
    page_dir[PROGRAM].addr = (PADDR + (pid * K)) >> KERNEL_OFFSET;

    flushTLB();
}

/**
 * map_vidmap
 * * maps the video memory to the virtual address space of the kernel. 
 * return: none
 */
void map_vidmap(){
    page_table2[0].p = 1;
    page_table2[0].r_w = 1;
    page_table2[0].u_s = 1;
    page_table2[0].addr = VIDEO_MEM_PAGE_LOCATION  >> SHIFT_TO_8; //equals location is phys mem

    page_dir[VID].p = 1;
    page_dir[VID].u_s = 1;
    page_dir[VID].ps = 0; //indicative of a 4kb page     
    page_dir[VID].addr = (uint32_t)(page_table2) >> SHIFT_TO_8;
    
    flushTLB();
}

/**
 * unmap_vidmap
 * unmaps page table and page directory entry for video memory
 */
void unmap_vidmap(){
    page_table2[(VADDR + K) >> SHIFT_TO_8].p = 0;
    page_dir[VID].p = 0;
}

/** term_pages
 *  creates 3 4kb pages for each terminals video memory
 *  creates 3 4mb pages for each terminal to run shell + 1 process
 * initializes pages based on current terminal being accessed
 *  @return: none
 */
void term_pages(){ /* map same 128mb virtual to 8mb, 12mb, 16mb for terminal pages, only one runs at a time */
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+1].p = 1;
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+1].r_w = 1;
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+1].u_s = 1;
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+1].addr = T1_VADDR >> SHIFT_TO_8;

    /* vdeo page for term 2 */
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+2].p = 1;
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+2].r_w = 1;
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+2].u_s = 1;
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+2].addr = T2_VADDR >> SHIFT_TO_8;
        
    /* vdeo page for term 3 */
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+3].p = 1;
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+3].r_w = 1;
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+3].u_s = 1;
    page_table[(VIDEO_MEM_PAGE_LOCATION >> SHIFT_TO_8)+3].addr = T3_VADDR >> SHIFT_TO_8;

    flushTLB();
}
