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
    ;

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
    xor eax, eax
    ret

