#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include "../tables/bytes_heads.h"
#include "../libc/print.h"

#define RTC_COMMAND_PORT 0x70
#define RTC_DATA_PORT 0x71

static uint8_t read_rtc(uint8_t value)
{
    outb(RTC_COMMAND_PORT, value);
    return inb(RTC_DATA_PORT);
}

uint8_t BCD_to_DEC(uint8_t bcd)
{
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

void print_time()
{
    asm("cli");

    //  Waiting to rtc to be updated
    while(read_rtc(0x0A) & 0x80 == 0x80) {}

    uint8_t seconds = read_rtc(0x0);
    uint8_t minutes = read_rtc(0x2);
    uint8_t hour = read_rtc(0x4);
    
    uint8_t day  = read_rtc(0x7);
    uint8_t month  = read_rtc(0x8);
    uint8_t year = read_rtc(0x9);

    //  if BCD format
    if( !(read_rtc(0x0B) & 0x04) )
    {
        seconds = BCD_to_DEC(seconds);
        minutes = BCD_to_DEC(minutes);
        hour = BCD_to_DEC(hour);
        
        day  = BCD_to_DEC(day);
        month  = BCD_to_DEC(month);
        year = BCD_to_DEC(year);
    }

    // if( (read_rtc(0xB) & 0x02) )
    // {
    //     hour = hour % 12;
    // }

    prints("Current Time: ");
    printd(hour); prints(":"); printd(minutes);prints(":");printd(seconds);
    prints("\t");

    printd(day); prints("."); printd(month);prints(".");printd(year);

    prints("\n");

    asm("sti");
}


#endif