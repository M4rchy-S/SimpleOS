#ifndef ISR_H
#define ISR_H

#include <stdint.h>
#include "bytes_heads.h"
#include "PIC.h"

static uint8_t code = 0x00;

void keyboard_handler()
{
    code = inb(0x60);


    outb(0x20, 0x20);

}


#endif