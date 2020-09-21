section .rodata
	;

section .bss
	buf: resb 1


section .text
global _start
_start:
	; read characters in loop until EOF	
	
	; get one character from stdin
	; sys_read syscall
	mov eax, 0x03 ; syscall number
	mov ebx, 0x00 ; file descriptor (stdin)
	mov ecx, buf  ; where to write
	mov edx, 0x01 ; number of bytes
	int 0x80
	test eax, eax ; test if sys_read returned 0 - EOF
	je .loop_end

.loop_start:
	; convert to uppercase if ch >= 'a' && ch <= 'z'
	mov al, [buf] ; copy char from buffer
	cmp al, 0x61 ; 'a'
	jl .gtfo
	cmp al, 0x7a ; 'z'
	jg .gtfo
	sub al, 0x20  ; convert to uppercase
	mov [buf], al ; copy back to buffer

.gtfo:
	; write one character to stdout
	; sys_write syscall
	mov eax, 0x04 ; syscall number
	mov ebx, 0x01 ; file descriptor (stdout)
	mov ecx, buf  ; from where to read
	mov edx, 0x01 ; number bytes
	int 0x80
	
	; get one character from stdin
	; sys_read syscall
	mov eax, 0x03 ; syscall number
	mov ebx, 0x00 ; file descriptor (stdin)
	mov ecx, buf  ; where to write
	mov edx, 0x01 ; number of bytes
	int 0x80	
	test eax, eax ; test if sys_read returned 0 - EOF
	jne .loop_start
	
.loop_end:
	; exit
	; sys_exit syscall
	mov eax, 0x01 ; syscall number
	mov ebx, 0x00 ; exit code
	int 0x80


