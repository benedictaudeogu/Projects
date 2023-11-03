#ifndef _IDT_LINKAGE_H
#define _IDT_LINKAGE_H

// // #include "init_idt.h"
// #define RTC_EXCEPTION 0x28
// #define KEYBOARD_EXCEPTION 0x21

extern void E0();
extern void E1();
extern void E2();
extern void E3();
extern void E4();
extern void E5();
extern void E6();
extern void E7();
extern void E8();
extern void E9();
extern void E10();
extern void E11();
extern void E12();
extern void E13();
extern void E14();
extern void sys_link();

extern void keyboard_link();
extern void rtc_link();
extern void pit_link();

#endif
