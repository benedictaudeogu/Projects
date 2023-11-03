#include "RTC.h"
#include "i8259.h"
#include "lib.h"
#include "term_keyboard.h"

int32_t terminal_rates[] = {15, 15, 15}; // 11 is 32 hz


/* rtc_init
*   allows for clocked interrupts to occur on their own
*   output: none
*/
void rtc_init(){
    int rate = fastest_rate; //Kernel should limit to 1024Hz, or rate of 6. Slowest is 15 - interrupts of 2Hz (also the default rate)
    rate &= offset2;

    cli();
    outb(regB, port1); // regB = 0x8B,  0x80 disables NMI (1 bit), 0x0B selects register B (7 bits)
    char prev = inb(port2);
    outb(regB, port1);
    outb(prev | offset1, port2);  // turn on bit 6 of regB
    sti();

    // set rate
    cli();
    outb(regA, port1);
    prev = inb(port2);
    outb(regA, port1);
    outb((prev & offset3) | rate, port2);
    sti();

    interrupt_flag = 0;

    // install the IRQ handler before we enable RTC IRQ
    enable_irq(IRQ_RTC);
}

/* rtc_handler
*   interrupts will occur at a specified rate
*   output: interrupts handler
*/
void rtc_handler(){
    cli();
    // test_interrupts();
    //putc(65);
    outb(regC, port1);  
    inb(port2);  // read from status register C (must be read to ensure interrupt can happen again)
    send_eoi(IRQ_RTC);
    interrupt_flag = 0;
    sti();
}

/* rtc_open
*   description: initializes frequency to 2Hz
*   inputs: none
*   outputs: none
*/
int32_t rtc_open(const uint8_t* filename){
    // reset freq to 2Hz
    int rate = fastest_rate;
    rate &= offset2;
    cli();
    outb(regA, port1);
    char prev = inb(port2);
    outb(regA, port1);
    outb((prev & offset3) | rate, port2);
    sti();
    return 0;
}

/* rtc_close
*   description: Just returns 0, does nothing
*   inputs: none
*   outputs: none
*/
int32_t rtc_close(int32_t fd){
    return 0;
}

/* rtc_read
*   description: Waits for interrupt to happen
*   inputs: none
*   output: 0 once successful
*/
int32_t rtc_read(int32_t fd, void* buf, int32_t nbytes){
    interrupt_flag = 1;
    int cur_rate = terminal_rates[curr_term];
    int power = cur_rate - 6;
    int num_ints = 1;
    while(power > 0){
        num_ints *= 2;
        power--;
    }
    // 6 -> 1024 -> 1    
    // 7 -> 512 -> 2
    // 8 -> 256 -> 4
    int i;
    for(i = 0; i < num_ints; i++){
        interrupt_flag = 1;
        while(interrupt_flag == 1){
            // wait for handler to signal interrupt has happened
        }
    }
    return 0;
}

/* rtc_write
*   description: Sets a new frequency for the RTC
*   inputs: buf - int pointer to frequency
*           nbytes - should specify 4 bytes of buf
*   output: 0 if successful, otherwise -1
*/
int32_t rtc_write(int32_t fd, const void* buf, int32_t nbytes){
    if (nbytes != 4){
        return -1;
    }

    int32_t freq = *((int32_t*)buf); // 0x40000000
    int32_t bitmask = rate_mask;
    int numSetBits = 0;
    int rate;
    int i;
    // check if freq is power of 2
    for (i = 0; i < 32; i++){
        if ((freq & bitmask) != 0){
            rate = 16 - i;  // 1 -> 15, 2 -> 14, ...
            numSetBits++;
        }
        bitmask = bitmask << 1;
    }
        
    if (numSetBits != 1 || rate > slowest_rate || rate < fastest_rate){ // rate must be within 2 to 1024 Hz 
        return -1;
    } 
    terminal_rates[curr_term] = rate;

    // cli();
    // outb(regA, port1);  // Rate is set in register A
    // char prev = inb(port2);  
    // outb(regA, port1);
    // outb(rate | (prev & 0xF0), port2);  // Only modify 4 least sig bits in A
    // sti();
    return 0;
}
