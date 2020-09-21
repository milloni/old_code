bits 32


section .rodata
load_data: db 0xaa, 0xbb, 0xcc, 0xdd


section .bss
	;


section .text
global _start
_start:
	nop
	mov eax, [load_data]
	;int3
	mov eax, 0x01
	mov ebx, 0x00
	int 0x80

