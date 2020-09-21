extern printf
extern scanf

; Write debug message to stdout
%macro _dbg 1
    push eax
    call %%l1
%%msg: db %1, 0x0a, 0x00
%%msg_len: equ $-%%msg
%%l1:
    call printf
    add esp, 0x04
    pop eax
%endmacro

; Write a number to stdout
; (same argument as push)
%macro _dbg_num 1
    push eax
    call %%l1
%%msg: db "%d", 0x0a, 0x00
%%msg_len: equ $-%%msg
%%l1:
    call printf
    add esp, 0x04
    pop eax
%endmacro

;;;; .rodata ;;
section .rodata
    msg_input: db "Enter a number to check for primality: ", 0x00
    msg_input_fmt: db "%d", 0x00
    msg_output_true: db "It is prime", 0x0a, 0x00
    msg_output_false: db "It is not prime", 0x0a, 0x00

;;;; .bss ;;;;;
section .bss
	;

;;;; .text ;;;;
section .text

; int32_t main(void);
; Return value:
;     Returns exit status of the program
global main
main:
    ; create the stack frame
    push ebp
    mov ebp, esp

    ; print the message
    push msg_input
    call printf
    add esp, 0x04

    ; enter the number
    ; store it on the stack
    sub esp, 0x04
    push esp
    push msg_input_fmt
    call scanf
    add esp, 0x08

    call is_prime
    add esp, 0x04
    ;_dbg_num eax

    ; print depending on the output
    cmp eax, 0
    jz .l1
    push msg_output_true
    jmp .l2
.l1:
    push msg_output_false
.l2:
    call printf
    add esp, 0x04

    ; destroy the stack frame
    mov esp, ebp
    pop ebp

    ; return 0
    xor eax, eax
    ret

; int32_t is_prime(int n)
; Checks if a number is a prime number
; Params:
;     n: number to be checked for primality
; Return value:
;     1 if prime, 0 otherwise
global is_prime
is_prime:
    ; create stack frame
    push ebp
    mov ebp, esp
    push ebx

    ; this loop checks whether n is prime
    xor edx, edx        ; prepare edx for idiv
    mov eax, [ebp+0x08] ; move argument to eax
    mov ecx, 2          ; initialize loop counter
.l4:
    cmp eax, ecx        ; if counter < n
    jle .l1
    idiv ecx            ; check if remainder of argument % counter == 0
    cmp edx, 0
    ;int3
    jnz .l2
    xor ebx, ebx        ; number is not prime
    jmp .l3
.l2:
    xor edx, edx        ; prepare edx for idiv
    mov eax, [ebp+0x08] ; move argument to eax
    inc ecx             ; increment the counter
    jmp .l4
.l1:
    ;int3
    mov ebx, 1

.l3: 
    ; destroy stack frame
    lea esp, [ebp-0x04]
    mov eax, ebx        ; return the result
    pop ebx
    pop ebp
    ret

