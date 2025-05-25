#ifndef TABLES_H
#define TABLES_H

#include "bytes_heads.h"
#include "GDT.h"
#include "IDT.h"

void setup_tables()
{
    // asm("cli");

    gdt_table_setup();
    idt_init();

    // asm("sti");

}

#endif