/* i8259.c - Functions to interact with the 8259 interrupt controller
 * vim:ts=4 noexpandtab
 */
// #define ASM     1
#include "i8259.h"
#include "lib.h"

/* Interrupt masks to determine which interrupts are enabled and disabled */
uint8_t master_mask = 0xff; /* IRQs 0-7  */
uint8_t slave_mask = 0xff;  /* IRQs 8-15 */

/* Initialize the 8259 PIC */
void i8259_init(void) {
   
    outb(ICW1 | ICW4, MASTER_8259_PORT); //start initialization sequence for master
    outb(ICW1 | ICW4, SLAVE_8259_PORT); //start initialization sequence for slave

    outb(ICW2_MASTER, MASTER_8259_PORT + 1); //master PIC offset
    outb(ICW2_SLAVE, SLAVE_8259_PORT + 1); //slave PIC offset

    outb(ICW3_MASTER, MASTER_8259_PORT + 1); //tell master there is slave PIC at IRQ2
    outb(ICW3_SLAVE, SLAVE_8259_PORT + 1); //tell slave PIC its cascade identity

    outb(ICW4, MASTER_8259_PORT + 1); //set mode for master port PIC
    outb(ICW4, SLAVE_8259_PORT + 1); //set mode for slave port PIC

    outb(master_mask, MASTER_8259_PORT + 1);
    outb(slave_mask, SLAVE_8259_PORT + 1);

    enable_irq(2);
}
//not sure to leftshift or not for enable and disable irq_num values
/* Enable (unmask) the specified IRQ */
void enable_irq(uint32_t irq_num) {
    if (irq_num >= 8)
    {   
        slave_mask = slave_mask & ~(1 <<(irq_num - 8));
        outb(slave_mask, 0xA1);
    } else {
        master_mask = master_mask & ~(1 << irq_num);
        outb(master_mask, 0x21);  
    }
    // outb(MASTER_8259_PORT + 1, 0x21); //restore saved masks?
    // outb(SLAVE_8259_PORT + 1, 0xA1);
}

/* Disable (mask) the specified IRQ */
void disable_irq(uint32_t irq_num) {
    if (irq_num >= 8)
    {
        slave_mask = slave_mask | (1 << (irq_num - 8));
        outb(slave_mask, 0xA1);
    } else {
        master_mask = master_mask  | (1 << irq_num);
        outb(master_mask & ~(1 << irq_num), 0x21); 
    }
}

/* Send end-of-interrupt signal for the specified IRQ */
void send_eoi(uint32_t irq_num) {
    if(irq_num >= 8){ //eoi extends to the slave chip as well
        outb(EOI | (irq_num - 8), SLAVE_8259_PORT);
        outb((EOI + 2), MASTER_8259_PORT);

    } else {
        outb(EOI | irq_num, MASTER_8259_PORT);
    }
}
