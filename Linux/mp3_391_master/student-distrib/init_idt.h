#ifndef _INIT_IDT_H
#define _INIT_IDT_H

#include "x86_desc.h"

#define SYS_CALL 0x80
#define EXCEPTION_MAX 31
#define RTC_EXCEPTION 0x28
#define KEYBOARD_EXCEPTION 0x21
#define PIT_EXCEPTION 0x20

extern void idt_init(idt_desc_t* idt);

#endif
