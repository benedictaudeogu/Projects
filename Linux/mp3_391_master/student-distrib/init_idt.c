#include "init_idt.h"
#include "idt_handler.h"
#include "idt_linkage.h"

/* idt_init
 * Initializes the IDT by setting the attributes of each entry in the IDT.
 * 
 * @param idt the pointer to the IDT
 */
void idt_init(idt_desc_t* idt) {//parameter needed?
    int i;

    /* set bit for all possible interrupts */
    for (i = 0; i < NUM_VEC; i++) {
        if (i == SYS_CALL) {
            idt[i].dpl = 3; //case of system call
        }
        else {
            idt[i].dpl = 0; //0 for interrupts and exceptions
        }
        idt[i].size = 1; //interrupt and trap gates both 32 bits
        idt[i].reserved0 = 0;
        idt[i].reserved1 = 1;
        idt[i].reserved2 = 1;
        if (i > EXCEPTION_MAX && i != SYS_CALL) {
            idt[i].reserved3 = 0; //0 for interrupt gate 1 for trap gate (just if > 31 and !0x80?)
        }
        else {
            idt[i].reserved3 = 1;
        }
        idt[i].reserved4 = 0;
        idt[i].present = 1;
        idt[i].seg_selector = KERNEL_CS;
    }
    /* SET_IDT_ENTRY for all interrupts */
    SET_IDT_ENTRY(idt[0], E0);
    SET_IDT_ENTRY(idt[1], E1);
    SET_IDT_ENTRY(idt[2], E2);
    SET_IDT_ENTRY(idt[3], E3);
    SET_IDT_ENTRY(idt[4], E4);
    SET_IDT_ENTRY(idt[5], E5);
    SET_IDT_ENTRY(idt[6], E6);
    SET_IDT_ENTRY(idt[7], E7);
    SET_IDT_ENTRY(idt[8], E8);
    SET_IDT_ENTRY(idt[9], E9);
    SET_IDT_ENTRY(idt[10], E10);
    SET_IDT_ENTRY(idt[11], E11);
    SET_IDT_ENTRY(idt[12], E12);
    SET_IDT_ENTRY(idt[13], E13);
    SET_IDT_ENTRY(idt[14], E14);

    SET_IDT_ENTRY(idt[RTC_EXCEPTION], rtc_link);
    SET_IDT_ENTRY(idt[KEYBOARD_EXCEPTION], keyboard_link);
    SET_IDT_ENTRY(idt[SYS_CALL], sys_link);
    SET_IDT_ENTRY(idt[PIT_EXCEPTION], pit_link);
}

