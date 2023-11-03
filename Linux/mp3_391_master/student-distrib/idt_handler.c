#include "idt_handler.h"
#include "lib.h"
#include "sys_call_handler.h"

/* only prints the desired message */
void divide_by_0(void) {
    printf("%s\n", "DIVIDE BY ZERO EXCEPTION");
    halt(1); 
}

void debug(void) {
    printf("%s\n", "DEBUG EXCEPTION");
    halt(1);
}

void nmi_interrupt(void) {
    printf("%s\n", "NMI INTERRUPT EXCEPTION");
    halt(1);
}

void breakpoint(void) {
    printf("%s\n", "BREAKPOINT EXCEPTION");
    halt(1);
}

void overflow(void) {
    printf("%s\n", "OVERFLOW EXCEPTION");
    halt(1);
}

void bound_range_exceeded(void) {
    printf("%s\n", "BOUND RANGE EXCEEDED EXCEPTION");
    halt(1);
}

void invalid_opcode(void) {
    printf("%s\n", "INVALID OPCODE EXCEPTION");
    halt(1);
}

void device_not_available(void) {
    printf("%s\n", "DEVICE NOT AVAILABLE EXCEPTION");
    halt(1);
}

void double_fault(void) {
    printf("%s\n", "DOUBLE FAULT EXCEPTION");
    halt(1);
}

void coprocessor_segment_overrun(void) {
    printf("%s\n", "COPROCESSOR SEGMENT OVERRUN EXCEPTION");
    halt(1);
}

void invalid_tss(void) {
    printf("%s\n", "INVALID TSS EXCEPTION");
    halt(1);
}

void segment_not_present(void) {
    printf("%s\n", "SEGMENT NOT PRESENT EXCEPTION");
    halt(1);
}

void stack_fault(void) {
    printf("%s\n", "STACK FAULT EXCEPTION");
    halt(1);
}

void general_protection(void) {
    printf("%s\n", "GENERAL PROTECTION EXCEPTION");
    halt(1);
}

/**
 * prints out the value of the cr2 register and the stack pointer, then halts the system
 */
void page_fault(void) {
    printf("%s\n", "PAGE FAULT EXCEPTION");
    uint32_t cr2_val, esp_val;
    asm volatile ("                                           \n\
        movl %%cr2, %0                                        \n\
        movl %%esp, %1"                                       
        : "=r"(cr2_val), "=r"(esp_val)
        : 
        : "memory"
    );
    printf("cr2: %x\nesp: %x\n", cr2_val, esp_val);
    halt(1);
}

/**
 * It prints a message and then halts the system
 */
void sys_call(void) {
    printf("%s\n", "SYSTEM CALL WAS CALLED");
    halt(1);
}
