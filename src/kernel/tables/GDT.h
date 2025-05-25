#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct gdt_entry{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t fl_lim;
    uint8_t base_high;
}__attribute__((packed));

struct gdt_ptr{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));


#define GDT_LENGTH 5
struct gdt_ptr gdtp;
struct gdt_entry gdt[GDT_LENGTH];

void setGDTEntry(int n, uint32_t limit, uint32_t base, uint8_t access_byte, uint8_t flags)
{
    gdt[n].limit = limit & 0xFFFF;
    gdt[n].fl_lim = (limit >> 16) & 0x0F;

    gdt[n].base_low = base & 0xFFFF;
    gdt[n].base_mid = (base >> 16) & 0xFF;
    gdt[n].base_high = (base >> 24) & 0xFF;

    gdt[n].access = access_byte;
    
    gdt[n].fl_lim |= (flags << 4);

}

extern void load_gdt(uint32_t);
extern void reloadSegments();

void gdt_table_setup()
{
    gdtp.limit = (sizeof(struct gdt_entry) * GDT_LENGTH) - 1;
    gdtp.base = (uint32_t) &gdt;

    for (int i = 0; i < GDT_LENGTH; i++)
    {
        setGDTEntry(i, 0, 0, 0, 0);
    }
    

    setGDTEntry(0, 0, 0, 0, 0);
    setGDTEntry(1, 0xFFFFF, 0, 0x9A, 0xC);
    setGDTEntry(2, 0xFFFFF, 0, 0x92, 0xC);
    setGDTEntry(3, 0xFFFFF, 0, 0xFA, 0xC);
    setGDTEntry(4, 0xFFFFF, 0, 0xF2, 0xC);

    load_gdt( (uint32_t)&gdtp );
    reloadSegments();
}

#endif