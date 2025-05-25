#ifndef TABLES_H
#define TABLES_H

#include "bytes_heads.h"
#include "GDT.h"
#include "IDT.h"
#include "PIC.h"

void setup_tables()
{
    asm("cli");

    gdt_table_setup();
    idt_init();
    PIC_remap(0x20, 0x28);

    asm("sti");

}

#endif