
global test_isr
test_isr:
    pusha 

    cli
    mov al, 'X'
    mov ah, 0x0F
    mov [0xB8000], ax
    hlt

    popa

    iret