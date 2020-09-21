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
    usage_msg: db "Usage: hexdump filename", 0x0a, 0x00

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

    ; was the file given as argument?
    ; if not, exit
    mov eax, [ebp+0x08]
    cmp eax, 2
    je .l1
    call print_usage
    mov eax, 1
    jmp .exit
.l1:
    
    ; read the file into memory
    

.exit:
    ; destroy the stack frame
    mov esp, ebp
    pop ebp

    ; return value of eax
    ret

; void print_usage(void);
; Prints info on how to use the program
global print_usage
print_usage:
    push usage_msg
    call printf
    add esp, 0x04

; uint32_t file_len(char *file

