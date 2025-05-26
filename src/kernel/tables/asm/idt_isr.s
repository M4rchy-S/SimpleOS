
extern error_handler
global error_isr
error_isr:
    pusha 

    cli
    mov al, 'X'
    mov ah, 0x0F
    mov [0xB8000], ax


    call error_handler
    ; hlt

    sti
    popa

    iret

extern keyboard_handler
global keyboard_isr
keyboard_isr:
    pusha 

    cli

    call keyboard_handler

    ; hlt

    sti
    popa

    iret