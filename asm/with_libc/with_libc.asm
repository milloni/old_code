section .rodata
	;
	;


section .data
	;
	;


section .bss
	;
	;


section .text
global main
main:
	push ebp
	mov ebp, esp
	mov eax, 0x08
	mov esp, ebp
	pop ebp
	ret
