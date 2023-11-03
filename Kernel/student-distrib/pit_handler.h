#ifndef PIT_HANDLER_H
#define PIT_HANDLER_H

#define IRQ_PIT 0
#define CHANNEL_0 0x40
#define CHANNEL_1 0x41
#define CHANNEL_2 0x43
#define MODE_REG 0x42
#define CUR_MODE 0x36  // 00 11 010 0   channel 0, lo/hi, rate gen, 16-bit binary
#define FREQ 30  // in milliseconds

void pit_init();
void pit_handler();
void pit_set_freq(int freq, int channel);

#endif
