# #include "idt_linkage.h"
#define ASM 1

jump_table:
	.long halt, execute, read, write, open, close, getargs, vidmap

/* IDT_LINK(name, func)
*	global function macro made to excute all possible excutions and interrupts except sys calls
*	output: handlers of called interrupts executed
*/
#define IDT_LINK(name, func)  \
 	.globl name				 ;\
 	name:					 ;\
 		pushal				 ;\
 		pushfl				 ;\
 		call func			 ;\
 		popfl				 ;\
 		popal				 ;\
 		iret	

/* IDT_LINK_SYS(name, func)
*	global function macro to execute system calls
*   inputs: EAX - syscall number
*			EBX - 1st arg
*			ECX - 2nd arg
*			EDX - 3rd arg
*	output: may return respective sys call output in EAX
*/

#define IDT_LINK_SYS(name)  	\
 	.globl name					;\
 	name:						;\
 		pushfl					;\
		pushl %ebp				;\
		movl %esp, %ebp			;\
		pushl %esi				;\
		pushl %edi				;\
		cmpl $1, %eax		 	;\
		jl invalid_sys_call	 	;\
		cmpl $10, %eax		 	;\
		jg invalid_sys_call	 	;\
	valid_sys_call:				;\
		pushl %edx				;\
		pushl %ecx				;\
		pushl %ebx				;\
		decl %eax				;\
		call *jump_table(,%eax,4);\
		addl $12, %esp			;\
		jmp sys_return			;\
	invalid_sys_call:			;\
		movl $-1, %eax			;\
		jmp sys_return			;\
	sys_return:					;\
		popl %edi				;\
		popl %esi				;\
		leave					;\
		popfl					;\
		iret

		
IDT_LINK(E0, divide_by_0);
IDT_LINK(E1, debug);
IDT_LINK(E2, nmi_interrupt);
IDT_LINK(E3, breakpoint);
IDT_LINK(E4, overflow);
IDT_LINK(E5, bound_range_exceeded);
IDT_LINK(E6, invalid_opcode);
IDT_LINK(E7, device_not_available);
IDT_LINK(E8, double_fault);
IDT_LINK(E9, coprocessor_segment_overrun);
IDT_LINK(E10, invalid_tss);
IDT_LINK(E11, segment_not_present);
IDT_LINK(E12, stack_fault);
IDT_LINK(E13, general_protection);
IDT_LINK(E14, page_fault);
IDT_LINK(keyboard_link, keyboard_handler);
IDT_LINK(rtc_link, rtc_handler);
IDT_LINK(pit_link, pit_handler);

IDT_LINK_SYS(sys_link);
