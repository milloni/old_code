bits 32

section .data
	;
	;


section .rodata
EatMsg: db "Eat at Joe's", 0x0a
EatLen: equ $-EatMsg


section .bss
	;
	;


section .text

global _start
_start:
	; sys_write syscall
	; write string EatMsg to stdout 
	mov eax, 0x04
	mov ebx, 0x01
	mov ecx, EatMsg
	mov edx, EatLen
	int 0x80

	; sys_exit syscall
	; exit with code 0
	mov eax, 1
	mov ebx, 0
	int 0x80

