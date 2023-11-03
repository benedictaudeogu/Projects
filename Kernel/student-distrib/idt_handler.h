#ifndef _IDT_HANDLER_H
#define _IDT_HANDLER_H

#include "x86_desc.h"

extern void divide_by_0(void);
extern void debug(void);
extern void nmi_interrupt(void);
extern void breakpoint(void);
extern void overflow(void);
extern void bound_range_exceeded(void);
extern void invalid_opcode(void);
extern void device_not_available(void);
extern void double_fault(void);
extern void coprocessor_segment_overrun(void);
extern void invalid_tss(void);
extern void segment_not_present(void);
extern void stack_fault(void);
extern void general_protection(void);
extern void page_fault(void);
extern void sys_call(void);

#endif
