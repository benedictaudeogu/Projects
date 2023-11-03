/* tuxctl-ioctl.c
 *
 * Driver (skeleton) for the mp2 tuxcontrollers for ECE391 at UIUC.
 *
 * Mark Murphy 2006
 * Andrew Ofisher 2007
 * Steve Lumetta 12-13 Sep 2009
 * Puskar Naha 2013
 */

#include <asm/current.h>
#include <asm/uaccess.h>

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/file.h>
#include <linux/miscdevice.h>
#include <linux/kdev_t.h>  
#include <linux/tty.h>
#include <linux/spinlock.h>

#include "tuxctl-ld.h"
#include "tuxctl-ioctl.h"
#include "mtcp.h"


int tux_init(struct tty_struct* tty);
int tux_set_led(struct tty_struct* tty, int arg);
int tux_buttons(unsigned long arg_);

#define debug(str, ...) \
	printk(KERN_DEBUG "%s: " str, __FUNCTION__, ## __VA_ARGS__)

/* 7 segment representation of 0-15 */
const char hex_values[16] = {0xE7, 0x06, 0xCB, 0x8F, 0x2E, 0xAD, 0xED, 0x86, 0xEF, 0xAF, 0xEE, 0x6D, 0xE1, 0x4F, 0xE9, 0xE8};

/* MACROS */
#define BUSY 1
#define MASK 4
#define L_SIZE 6
#define I_SIZE 7
#define P_SIZE 8
#define OFFSET 3
#define MASK_L 0x0F
#define MASK_H 0xF0
#define SHIFT_1 1
#define NOT_BUSY 0
#define NEXT_BIT 4
#define GET_L 0x20
#define GET_D 0x40
#define CLEAR 0xE7
#define INIT_SIZE 2
#define SHIFT_24 24
#define SHIFT_16 16
#define DP_MASK 0x10
#define CLEAR_OLD 0x9F
#define EIGHT_BIT 0xFF
#define LOW_HIGH 0x0f000000
#define LOW_THIRD 0x000f0000


/* SHARED GLOBAL VARIABLES */
int button;
static int busy_flag;
int i, l, d, dp, led_cnt;
unsigned char led[NEXT_BIT];
unsigned char tux_buf[P_SIZE];

/************************ Protocol Implementation *************************/

/* tuxctl_handle_packet()
 * IMPORTANT : Read the header for tuxctl_ldisc_data_callback() in 
 * tuxctl-ld.c. It calls this function, so all warnings there apply 
 * here as well.
 */
void tuxctl_handle_packet (struct tty_struct* tty, unsigned char* packet)
{
    unsigned a, b, c;

    a = packet[0]; 
    b = packet[1]; /* values when printing them. */
    c = packet[2];

	switch(a){
	case MTCP_ACK:
		busy_flag = NOT_BUSY;
		break;

	case MTCP_BIOC_EVENT:
		button = ((b & MASK_L) | (c<<MASK & MASK_H));
		l = (button & GET_L) << SHIFT_1; //get left
		d = (button & GET_D) >> SHIFT_1; //get right
		button &= CLEAR_OLD;
		button |= l;
		button |= d;
		button = ~button;
		button &= EIGHT_BIT;
		break;
		
	case MTCP_RESET:
		busy_flag = BUSY;
		tux_buf[0] = MTCP_BIOC_ON;
		tux_buf[1] = MTCP_LED_USR;
		tux_buf[2] = MTCP_LED_SET;
		tux_buf[3] = MASK_L;
		for(i = MASK; i < P_SIZE; i++){
			tux_buf[i] = led[i-MASK];
		}
		tuxctl_ldisc_put(tty, tux_buf, P_SIZE);
		break;
	}

	/* Avoid printk() sign extending the 8-bit */
    /*printk("packet : %x %x %x\n", a, b, c); */
}

/******** IMPORTANT NOTE: READ THIS BEFORE IMPLEMENTING THE IOCTLS ************
 *                                                                            *
 * The ioctls should not spend any time waiting for responses to the commands *
 * they send to the controller. The data is sent over the serial line at      *
 * 9600 BAUD. At this rate, a byte takes approximately 1 millisecond to       *
 * transmit; this means that there will be about 9 milliseconds between       *
 * the time you request that the low-level serial driver send the             *
 * 6-byte SET_LEDS packet and the time the 3-byte ACK packet finishes         *
 * arriving. This is far too long a time for a system call to take. The       *
 * ioctls should return immediately with success if their parameters are      *
 * valid.                                                                     *
 *                                                                            *
 ******************************************************************************/
int 
tuxctl_ioctl (struct tty_struct* tty, struct file* file, 
	      unsigned cmd, unsigned long arg)
{
    switch (cmd) {
	case TUX_INIT:
		tux_init(tty);
		break;

	case TUX_BUTTONS:
		tux_buttons(arg);
		break;

	case TUX_SET_LED:
		if(busy_flag){
			return 0; //shouldn't do anything if already busy
		}
		tux_set_led(tty, arg);
		break;

	case TUX_LED_ACK:
		return -EINVAL;
	case TUX_LED_REQUEST:
		return -EINVAL;
	case TUX_READ_LED:
		return -EINVAL;
	default:
	    return -EINVAL;
    }
	return 0;
}

/*
* tux_init
* inputs: tty pointer
* side effects: initializes all the leds to zero
*/
int tux_init(struct tty_struct* tty){
	tux_buf[0] = MTCP_BIOC_ON; 
	tux_buf[1] = MTCP_LED_USR;
	tux_buf[2] = MTCP_LED_SET; 
	
	busy_flag = BUSY;
	i = OFFSET; //args 3 - 6 -> get led val one at a time
	while(i < I_SIZE){ 
		led[i-OFFSET] = CLEAR; 
		tux_buf[i] = led[i-OFFSET];
		i++;
	}

	tuxctl_ldisc_put(tty, tux_buf, I_SIZE);
	return 0;
}

/*
* tux_set_led
* inputs: tty pointer, arg as a 32 bit integer
* 		  ->arg contains led vals, which ones 
*		  -> should be on, and which decimal 
*		  -> should be on as well
* side effects: initializes all the leds to zero
*/
int tux_set_led(struct tty_struct* tty, int arg){
	tux_buf[0] = MTCP_LED_SET; 
	tux_buf[1] = MASK_L;
	busy_flag = BUSY;

	i = INIT_SIZE;
	dp = (arg & LOW_HIGH) >> SHIFT_24;
	led_cnt = (arg & LOW_THIRD) >> SHIFT_16;
	while(i < L_SIZE){ 
		if(led_cnt & SHIFT_1){
			led[i-INIT_SIZE] = hex_values[arg & MASK_L];
			tux_buf[i] = hex_values[arg & MASK_L]; 
		}
		else{
			tux_buf[i] = 0; //led off
			led[i-INIT_SIZE] = 0; //led off
		}
		if(dp & SHIFT_1){
			tux_buf[i] |= DP_MASK;
			led[i-INIT_SIZE] |= DP_MASK;
		}
		i++;
		dp >>= SHIFT_1;
		led_cnt >>= SHIFT_1;
		arg >>= NEXT_BIT;
	}

	tuxctl_ldisc_put(tty, tux_buf, L_SIZE); 
	return 0;
}

/*
*	tux_buttons
*	inputs: arg which is a pointer
*			used in copy to user to
*			get button from kernel to
*			user mode
*/
int tux_buttons(unsigned long arg_){
	if(arg_ == 0){// null check
		return -EINVAL;
	}

	//need to use copy to user to copy kernel button press to user space
	copy_to_user((void *)arg_, &button, NEXT_BIT); //arg = *to , button = *from, n = 4 (1) byte to copy
	return 0;
}

