#include "tests.h"
#include "x86_desc.h"
#include "term_keyboard.h"
#include "lib.h"
#include "RTC.h"
#include "new_file.h"
//#include "file.h"

#define PASS 1
#define FAIL 0

/* format these macros as you see fit */
#define TEST_HEADER 	\
	printf("[TEST %s] Running %s at %s:%d\n", __FUNCTION__, __FUNCTION__, __FILE__, __LINE__)
#define TEST_OUTPUT(name, result)	\
	printf("[TEST %s] Result = %s\n", name, (result) ? "PASS" : "FAIL");

static inline void assertion_failure(){
	/* Use exception #15 for assertions, otherwise
	   reserved by Intel */
	asm volatile("int $15");
}


/* Checkpoint 1 tests */

/* IDT Test - Example
 * 
 * Asserts that first 10 IDT entries are not NULL
 * Inputs: None
 * Outputs: PASS/FAIL
 * Side Effects: None
 * Coverage: Load IDT, IDT definition
 * Files: x86_desc.h/S
 */
int idt_test(){
	TEST_HEADER;

	int i;
	int result = PASS;
	for (i = 0; i < 10; ++i){
		if ((idt[i].offset_15_00 == NULL) && 
			(idt[i].offset_31_16 == NULL)){
			assertion_failure();
			result = FAIL;
		}
	}

	return result;
}

// add more tests here

/* divide_by_zero_test 
*	Asserts that divide by zero excption works properly
*	coverage: exception zero, idt
*/
int divide_by_zero_test() {
	TEST_HEADER;
	int i, j, k;
	int result = FAIL;
	i = 0;
	j = 4;
	k = j / i;

	return result;

}
/* dereference_null_ptr_test
*	Asserts that page fault exception occurs
*	coverage: page fault, idt
*/
// int dereference_null_ptr_test() {
// 	TEST_HEADER;
// 	int result = FAIL;
// 	int * temp;
// 	temp = NULL;
// 	int val = *temp;
// 	return result;
// }

/* sys_call_test
*	Asserts system calls are able to happen
*	coverage: system calls, idt
*/
int sys_call_test() {
	TEST_HEADER;
	int result = FAIL;
	asm volatile("int $0x80");
	return result;
}

/* Checkpoint 2 tests */
/**
 * Write a value to the RTC
 * 
 * @return PASS
 */
int rtc_write_test() {
	int result = PASS;
	//int32_t freq = SLOW_FREQ;
	int32_t freq = FAST_FREQ;
	int32_t* freq_ptr = &freq;
	// int temp;
	int b;
	for(b = 0; b < 10; b++){
		rtc_read(NULL, NULL, 0);
	}
	rtc_write(NULL, (void*)freq_ptr, N_BYTES_1);
	// while(1){
	// 	while (temp % 10 != 0){
	// 		temp = get_screen_x();
	// 	}
		
	// 	rtc_write(NULL, (void*)freq_ptr, N_BYTES_1);

	// 	while (temp % 10 != 0){
	// 		temp = get_screen_x();
	// 	}

	// 	freq = SLOW_FREQ;
	// 	rtc_write(NULL, (void*)freq_ptr, N_BYTES_1);
	// }
	
	return result;
}

int file_test() {
	TEST_HEADER;
	uint8_t buf[8000];
	int file, temp;
	file = f_open((uint8_t*)"verylargetextwithverylongname.txt");
	if(file == -1){
		return FAIL;
	}
	temp = f_read(file, buf, 1000);
	terminal_write(1, buf, temp);

	//file_close("fish");
	

	return PASS;
}

/**
 * Write a string to the terminal and read it back
 * 
 * @return PASS
 */
int terminal_test() {
	int result = PASS;
	char buf[TEST_SIZE] = "testing123";
	//char buf2[TEST_SIZE];
	
	while(1){
		terminal_write(1, buf, strlen(buf)); 
		terminal_read(0, buf, N_BYTES_2);
	}
	
	return result;
}
/* Checkpoint 3 tests */
/* Checkpoint 4 tests */
/* Checkpoint 5 tests */


/* Test suite entry point */
void launch_tests(){
	//TEST_OUTPUT("rtc_write_test", rtc_write_test());
	//TEST_OUTPUT("terminal_test", terminal_test());
	TEST_OUTPUT("file_test", file_test());
	//TEST_OUTPUT("dereferenece_null_ptr_test", dereference_null_ptr_test());
	TEST_OUTPUT("idt_test", idt_test());
	//TEST_OUTPUT("divide_by_zero_test", divide_by_zero_test());

	// TEST_OUTPUT("sys_call_test", sys_call_test());
	// launch your tests here
}
