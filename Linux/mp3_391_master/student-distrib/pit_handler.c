#include "pit_handler.h"
#include "i8259.h"
#include "lib.h"
#include "scheduler.h"

int countdown;

/* pit_init
*   allows for clocked interrupts to occur on their own
*   output: none
*/
void pit_init(){
    countdown = 0;
    outb(CUR_MODE, MODE_REG);
    pit_set_freq(FREQ, 0); //only using channel 0
    enable_irq(IRQ_PIT);
}

/* pit_set_freq
*   sets the reload value for specified channel based on desired frequency
*   output: returns 0
*/
void pit_set_freq(int freq, int channel){ //channel 0, 1, or 2
    int reloadVal = 1193182 / freq;
    cli();
    if(channel == 0){
        outb(reloadVal & 0xFF, CHANNEL_0);
        outb((reloadVal & 0xFF00)<<8, CHANNEL_0);
    }
    if(channel == 1){
        outb(reloadVal & 0xFF, CHANNEL_1);
        outb((reloadVal & 0xFF00)<<8, CHANNEL_1);
    }
    if(channel == 2){
        outb(reloadVal & 0xFF, CHANNEL_2);
        outb((reloadVal & 0xFF00)<<8, CHANNEL_2);
    }
}

/* pit_handler
*   interrupts will occur at a specified rate
*   output: interrupts handler
*/
void pit_handler(){
    //task_switch();
    send_eoi(IRQ_PIT);
}
