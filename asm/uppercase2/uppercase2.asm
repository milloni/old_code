section .rodata
	;


section .bss
buff_len: equ 0x400
buff: resb buff_len


section .text
global _start
_start:
	; read buff_len bytes from stdin to buff
	; sys_read syscall
	mov eax, 0x03     ; syscall id
	mov ebx, 0x00     ; file descriptor
	mov ecx, buff     ; buffer to write
	mov edx, buff_len ; buffer size
	int 0x80
	mov esi, eax
	test eax, eax     ; test if sys_read encountered EOF
	jz .exit

	mov ecx, esi
.loop_start:
	; convert lowercase characters in the buffer to uppercase
	; one character at a time
	mov edx, esi 
	sub edx, ecx
	mov ebx, buff     ; get addr of the buffer
	mov al, [ebx+edx] ; read char from buffer
	cmp al, 0x61      ; 'a'
	jl .skip
	cmp al, 0x7a      ; 'z'
	jg .skip
	sub al, 0x20      ; convert to uppercase
	mov [ebx+edx], al ; copy char back to buffer
.skip:
	loop .loop_start

	; write buff_len to stdout
	; sys_write syscall
	mov eax, 0x04 ; syscall id
	mov ebx, 0x01 ; file descriptor (stdout)
	mov ecx, buff ; buffer to read
	mov edx, esi
	int 0x80

	; read buff_len bytes from stdin to buff
	; sys_read syscall
	mov eax, 0x03     ; syscall id
	mov ebx, 0x00     ; file descriptor
	mov ecx, buff     ; buffer to write
	mov edx, buff_len ; buffer size
	int 0x80
	mov esi, eax
	mov ecx, esi
	test eax, eax     ; test if sys_read encountered EOF
	jnz .loop_start
	
.exit:
	; terminate the process
	; sys_exit syscall
	mov eax, 0x01 ; syscall id
	mov ebx, 0x00 ; exit code
	int 0x80

