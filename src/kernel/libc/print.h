#ifndef PRINT_H
#define PRINT_H

#include "../tty/tty.h"


void prints(char *string)
{
    terminal_writestring(string);
}

void printd(int value)
{
    if(value < 0)
    {
        terminal_write("-", 1);
        value = -value;
    }

    if(value > 10)
    {
        printd(value / 10);
    }

    char number = 48 + ( value % 10 );

    terminal_write(&number, 1);

}


#endif