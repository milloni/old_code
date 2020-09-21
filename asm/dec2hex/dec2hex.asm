section .rodata
	fmt: db "0x%x", 0x0a, 0x00
	fmt_len: equ $-fmt
	xlat_table: db "0123456789ABCDEF"

section .data
	;
	;


section .bss
buf_len: equ 11
buf:	resb buf_len


section .text
extern printf

; uint32_t __attribute__((cdecl)) my_strlen(char *s);
; Params:
;	s: pointer to a null-terminated string
; Return value:
;	Returns length of string s
global my_strlen
my_strlen:
	; create stack frame
	push ebp
	mov ebp, esp
	push ebx

	mov ebx, [ebp+0x08] ; s
	xor ecx, ecx
	mov dl, [ebx+ecx]  ; s[0]
	jmp .l2
.l1:
	inc ecx
	mov dl, [ebx+ecx] ; s[i]
.l2:
	test dl, dl
	jnz .l1

	mov eax, ecx ; return value
	
	; destroy stack frame
	lea esp, [ebp-0x04]
	pop ebx
	pop ebp
	ret

; void __attribute__((cdecl)) strrev(char *s);
; Params:
;	s:   pointer to a null-terminated string to reverse
global strrev
strrev:
	; create stack frame
	push ebp
	mov ebp, esp
	push ebx
	push esi

	mov ebx, [ebp+0x08] ; s

	; get length of the string
	push ebx
	call my_strlen
	add esp, 0x04
	mov esi, eax ; length of the string

	
	
	; destroy stack frame
	lea esp, [ebp-0x08]
	pop esi
	pop ebx
	pop ebp
	ret

; int __attribute__((cdecl)) dec2num(int8_t *digits, uint8_t len);
; Params:
; 	digits: pointer to an array of digits
; 	len:    number of digits in digits
; Return value:
;	Returns 32-bit number represented by digits
global dec2num
dec2num:
	; create stack frame
	push ebp
	mov ebp, esp
	push ebx
	push esi
	push edi

	mov ecx, [ebp+0x0c] ; index into the digits array. start with the
	dec ecx             ; least significant digit
	mov ebx, [ebp+0x08] ; pointer to the digits

	mov esi, 1   ; multiplier
	xor edi, edi ; result
.l1:
	mov al, [ebx+ecx] ;
	movsx eax, al
	sub eax, 0x30
	mul esi           ; multiply by scale factor
	add edi, eax      ; add to result
	mov edx, esi      ; multiple scale factor by 10
	sal edx, 1
	sal esi, 3
	add esi, edx
	dec ecx
	test ecx, ecx
	jge .l1

	mov eax, edi ; return value
	
	; destroy stack frame
	lea esp, [ebp-0x0c]
	pop edi
	pop esi
	pop ebx
	pop ebp
	ret

; void __attribute__((cdecl)) num2hex(int8_t *out, int in)
; Params:
;	out: buffer to store the result in (at least 11 bytes)
;	in:  number to convert to hex
global num2hex
num2hex:
	; create stack frame
	push ebp
	mov ebp, esp
	push ebx

	mov edx, [ebp+0x0c] ; in
	mov ebx, xlat_table
	xor ecx, ecx
.l1:
	mov eax, edx
	and eax, 0xF
	mov al, [ebx+eax]
	mov byte [buf+ecx], al
	sar edx, 0x04
	inc ecx
	cmp edx, 0x00
	jg .l1

	; null-terminate the string
	mov byte [buf+ecx+1], 0x00

	; destroy stack frame
	lea esp, [ebp-0x04]
	pop ebx
	pop ebp
	ret

global main
main:
	; create stack frame
	push ebp
	mov ebp, esp
	push ebx
	push esi

	; read decimal representation of a 32-bit integer from stdin.
	; max 10 digits == 10 bytes, but can be less.
	; read syscall
	mov eax, 0x03    ; syscall id
	mov ebx, 0x00    ; stdin
	mov ecx, buf     ; read to this buffer
	mov edx, buf_len ; read this much data
	int 0x80
	
	; get the 32-bit number represented by digits read from stdin
	lea ebx, [eax-0x01] ; get number of digits read (-1 cause we don't care about '\n')
	push ebx ; number of digits read
	push ecx ; addr of the digits
	call dec2num
	add esp, 0x08
	
	; cheating
	;push eax
	;push fmt
	;call printf
	;add esp, 0x08

	push eax
	push buf
	call num2hex
	add esp, 0x08
	;int3

	push buf
	call my_strlen
	add esp, 0x04
	int3
	
	; destroy stack frame
	lea esp, [ebp-0x08]
	pop esi
	pop ebx
	pop ebp
	ret
