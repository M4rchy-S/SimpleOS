#ifndef ISR_H
#define ISR_H

#include <stdint.h>

#include "bytes_heads.h"
#include "PIC.h"
#include "../libc/print.h"


#define OPCODES_SIZE 0x3B
static char *OPCODES[OPCODES_SIZE] = {
    "[ESC]", 
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "-", "=", 
    "[BACKSPACE]", "[TAB]",
    "q", "w", "e", "r", "t", "y", "u", "i",
    "o", "p", 
    "[", "]", 
    "[ENTER]", "[L_CTRL]", 
    "a", "s",
    "d", "f", "g", "h", "j", "k", "l", ";", "'", "`",
    "[L_SHIFT]", "\\", 
    "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
    "[R_SHIFT]", "", "[L_ALT]", "[SPACE]", "[CapsLock]"

};


void keyboard_handler()
{
    uint8_t code = inb(0x60);

    // prints("[DEBUG] Keyboard interupt. Code: ");
    // printd(code);
    // prints("\n");

    if(code > OPCODES_SIZE)
    {
        outb(0x20, 0x20);
        return;
    }

    //  ESCAPE
    
    //  BACKSPACE
    if(code == 0x0E)
    {
        terminal_backspace();
        buffer_rem_char();
    }
    //  TAB
    else if(code == 0x0F)
    {
        prints("    ");
    }
    //  ENTER
    else if(code == 0x1C)
    {
        prints("\n");
        buffer_process();
    }
    //  SPACE
    else if(code == 0x39)
    {
        prints(" ");
    }
    //  Any Character
    else if(buffer_length <= MAX_BUFFER_LENGTH - 2)
    {
        prints( OPCODES[code-1] );
        buffer_add_char(OPCODES[code-1]);
    }
    
    
    outb(0x20, 0x20);

}

void error_handler()
{
    prints("[DEBUG] Exception interrupt\n");
}


#endif