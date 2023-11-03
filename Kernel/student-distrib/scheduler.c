// #include "scheduler.h"

// int curTaskIdx;
// int numOfTasks;
// int nextAvailableIdx;
// task_t* curTask;
// task_t* firstTask;
// task_t* lastTask;

// /**
//  * It initializes the scheduler by setting all the global variables to their initial values
//  */
// void scheduler_init(){
//     numOfTasks = 0;
//     curTaskIdx = 0;
//     nextAvailableIdx = 0;
//     lastTask = NULL;
//     firstTask = NULL;
//     curTask = NULL;
// }

// /**
//  * 
//  * 
//  * @param pcb the pcb of the task to be added
//  */
// void add_task(pcb_t* pcb){
//     numOfTasks += 1;
//     if(nextAvailableIdx == 0){
//         task_t task = {nextAvailableIdx, pcb, NULL, NULL}
//         firstTask = &task;
//         lastTask = &task;
//         curTask = &task;
//         task.next = &task;
//         task.prev = &task;
//     }
//     else{
//         task_t task = {nextAvailableIdx, pcb, lastTask, firstTask}
//         firstTask->prev = &task;
//         lastTask->next = &task;
//     }
    
//     nextAvailableIdx += 1;
// }

// /**
//  * 
//  * 
//  * @return Nothing.
//  */
// void task_switch(){  // called every 10-50ms
//     curTask = curTask->next;
//     tss.ss0 = KERNEL_DS;
//     tss.esp0 = get_kernel_stack(curTask->pcb->pid);  // must be set to new pcb
    
//     asm volatile ("                         \n\
//         movl %0, %%esp                      \n\
//         movl %1, %%ebp                      \n\
//         jmp exeret                          \n\
//         "
//         :
//         : "r"(next_esp), "r"(next_ebp)
//         : "memory"
//     );
//     return 0;
// }

