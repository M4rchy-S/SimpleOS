global load_gdt
global reloadSegments


load_gdt:
    push eax

    or eax, eax

    mov ax, [esp + 8]
    lgdt [eax]

    pop eax

    ret

reloadSegments:
    jmp 0x08:.reload_CS

.reload_CS:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret