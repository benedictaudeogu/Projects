#ifndef _RTC_H
#define _RTC_H

#include "types.h"

#define regA 0x8A
#define regB 0x8B
#define regC 0x8C
#define port1 0x70
#define port2 0x71
#define offset1 0x40
#define offset2 0x0F
#define offset3 0xF0
#define IRQ_RTC 8
#define fastest_rate 6
#define slowest_rate 15
#define rate_mask 0x00000001

extern void rtc_init();
extern void rtc_handler();
int32_t rtc_open(const uint8_t* filename);
int32_t rtc_close(int32_t fd);
int32_t rtc_read(int32_t fd, void* buf, int32_t nbytes);
int32_t rtc_write(int32_t fd, const void* buf, int32_t nbytes);

int interrupt_flag;

#endif
