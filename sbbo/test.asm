[bits 32]

section .text

global _start
_start:
    mov eax, 1
    mov ebx, 7
    int 0x80

