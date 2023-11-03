#include "term_keyboard.h"
#include "keyboard.h"
#include "i8259.h"
#include "lib.h"
#include "sys_call_handler.h"

int shift_flag = 0;
int caps_flag = 0;
int ctrl_flag = 0;
int alt_flag = 0;
uint8_t keys[SIZE][TWO_D]
    = { //set empty values to 0, check when key is actually 0
        {'0','0'}, 
        {'0','0'}, //escape
        {'1','!'},         //(2)
        {'2','@'}, 
        {'3','#'}, 
        {'4','$'}, 
        {'5','%'}, 
        {'6','^'}, 
        {'7','&'}, 
        {'8','*'}, 
        {'9','('}, 
        {'0',')'},
        {'-','_'}, 
        {'=','+'}, 
        {'\b','\b'}, //backspace
        {'\t','\t'}, //tab (15)
        {'q','Q'}, 
        {'w','W'}, 
        {'e','E'}, 
        {'r','R'}, 
        {'t','T'}, 
        {'y','Y'}, 
        {'u','U'}, 
        {'i','I'}, 
        {'o','O'}, 
        {'p','P'},
        {'[','{'}, 
        {']','}'}, 
        {'\n','\n'}, //enter 
        {'0','0'},  //left control (29)
        {'a','A'}, 
        {'s','S'}, 
        {'d','D'}, 
        {'f','F'}, 
        {'g','G'}, 
        {'h','H'}, 
        {'j','J'}, 
        {'k','K'}, 
        {'l','L'},
        {';',':'}, 
        {'\'','"'}, 
        {'`','~'}, 
        {'0','0'}, //left shift (42)
        {'\\','|'},
        {'z','Z'}, 
        {'x','X'}, 
        {'c','C'}, 
        {'v','V'}, 
        {'b','B'}, 
        {'n','N'}, 
        {'m','M'},
        {',','<'},
        {'.','>'},
        {'/','?'},             //(53)
        {'0','0'}, //right shift
        {'0','0'}, //keypad *
        {'0','0'}, //left alt
        {' ',' '}, //space bar
        {'0','0'}, //caps lock   (58)
        {'0','0'}, //F1
        {'0','0'}, //F2
        {'0','0'}, //F3          (61)
    };

/* create_keyboard
*   keyboard interrupts allowed to happen
*   output: none
*/
void create_keyboard(){
    enable_irq(1);
    // waiting_for_user = 1;
    // i = 0;
    term_buf[curr_term].waiting_for_user = 1;
    term_buf[curr_term].i = 0;
}

/** keyboard_handler
 * * If the scan code is a valid key and it's not a release, then we check if it's a shift key. If it
 * is, then we check if the key is a letter. If it is, then we check if the caps flag is on. If it is,
 * then we change the letter to upper case. If it's not, then we change the letter to lower case. If
 * it's not a letter, then we just print the letter.
 * * If the scan code is a valid key and it's not a release, then we check if it's a caps key. If it
 * is, then we toggle the caps flag.
 * * If the scan code is a valid key and it's not a release, then we check if it's a ctrl key. If it
 * is, then we toggle the ctrl flag.
 * * If the scan code is a valid key and it's not a release, then we check if it's a
 * 
 * @return none
 */
void keyboard_handler(){
    int scan_code = inb(KEYBOARD_DATA);
    unsigned char c = keys[scan_code][0];
    switch(scan_code){ //pressed
        case ALT_PRESS:
            alt_flag = 1;
            send_eoi(1);
            return;
        case ALT_RELEASE:
            alt_flag = 0;
            send_eoi(1);
            return;
        case LPRESS: //l
            shift_flag = 1;
            send_eoi(1);
            return; 
        case LRELEASE:
            shift_flag = 0;
            send_eoi(1);
            return;
        case RPRESS: //r
            shift_flag = 1;
            send_eoi(1);
            return;
        case RRELEASE:
            shift_flag = 0;
            send_eoi(1);
            return;
        case CAPPRESS: //cap
            caps_flag = 1 - caps_flag;
            send_eoi(1);
            return;
        case CTRL_P: //ctrl
            ctrl_flag = 1;
            send_eoi(1);
            return;
        case CTRL_R:
            ctrl_flag = 0;
            send_eoi(1);
            return;
    }

    if(scan_code > 1 && scan_code <= (SIZE - 1) && !(scan_code & RELEASE)){ //valid and not released
        if (shift_flag && caps_flag && (c >= 'a' && c <= 'z')){
            c = keys[scan_code][0];
            if(term_buf[curr_term].i < KEYS_SIZE){
                term_kb[curr_term][term_buf[curr_term].i] = c;
                term_buf[curr_term].i++;
            }
        }
        else if(shift_flag){
            c = keys[scan_code][1];
            if(term_buf[curr_term].i < KEYS_SIZE){
                term_kb[curr_term][term_buf[curr_term].i] = c;
                term_buf[curr_term].i++;
            }
        }

        else if(caps_flag == 1 && (c >= 'a' && c <= 'z')){
            c = keys[scan_code][1];
            if(term_buf[curr_term].i < KEYS_SIZE){
                term_kb[curr_term][term_buf[curr_term].i] = c;
                term_buf[curr_term].i++;
            }
        } 

        if(c == '\n'){
            if(term_buf[curr_term].i < KEYS_SIZE){
                term_kb[curr_term][term_buf[curr_term].i] = c;
                term_buf[curr_term].i++;
            }
            putc(c);
            term_buf[curr_term].waiting_for_user = 0;
        }

        else if(c == '\b'){
            if(term_buf[curr_term].i > 0){
                term_buf[curr_term].i--;
                putc('\b');
            }
        }

        else if((ctrl_flag == 1 && c == 'l') || (ctrl_flag == 1 && c == 'L')){
            clear();
        } 

        else if(alt_flag == 1 && scan_code == A_F1){
            send_eoi(1);
            switch_terminals(0);
        }

        else if(alt_flag == 1 && scan_code == A_F2){
            send_eoi(1);
            switch_terminals(1);
        }

        else if(alt_flag == 1 && scan_code == A_F3){
            send_eoi(1);
            switch_terminals(2);
        }

        else{
            putc(c);
            if(term_buf[curr_term].i < KEYS_SIZE){
                term_kb[curr_term][term_buf[curr_term].i] = c;
                term_buf[curr_term].i++;
            }
        }
    }
    send_eoi(1);
}
