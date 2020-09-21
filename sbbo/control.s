	.file	"control.c"
	.section	.rodata
	.align 4
.LC0:
	.string	"Hi! Welcome to the control centre. Please select your spell:"
	.align 4
.LC1:
	.string	"shutdown - shutdown the system"
.LC2:
	.string	"reboot - reboot the system"
.LC3:
	.string	"play - play a game"
	.text
	.globl	print_menu
	.type	print_menu, @function
print_menu:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$12, %esp
	pushl	$.LC0
	call	puts
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC1
	call	puts
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC2
	call	puts
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC3
	call	puts
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	print_menu, .-print_menu
	.globl	is_root
	.type	is_root, @function
is_root:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	call	getuid
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	is_root, .-is_root
	.globl	become_all_powerful
	.type	become_all_powerful, @function
become_all_powerful:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	become_all_powerful, .-become_all_powerful
	.section	.rodata
.LC4:
	.string	"%p %p\n"
.LC5:
	.string	"shutdown"
	.align 4
.LC6:
	.string	"Sorry! You have to be root to do this!"
.LC7:
	.string	"reboot"
.LC8:
	.string	"play"
.LC9:
	.string	"-p"
.LC10:
	.string	"/bin/bash"
.LC11:
	.string	"Unknown command!"
	.text
	.globl	run
	.type	run, @function
run:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$72, %esp
	movl	environ, %eax
	subl	$4, %esp
	pushl	%eax
	leal	-72(%ebp), %eax
	pushl	%eax
	pushl	$.LC4
	call	printf
	addl	$16, %esp
	subl	$12, %esp
	leal	-72(%ebp), %eax
	pushl	%eax
	call	gets
	addl	$16, %esp
	subl	$4, %esp
	pushl	$64
	pushl	$.LC5
	leal	-72(%ebp), %eax
	pushl	%eax
	call	strncmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L6
	call	is_root
	testl	%eax, %eax
	je	.L7
	subl	$12, %esp
	pushl	$1126301404
	call	reboot
	addl	$16, %esp
	jmp	.L8
.L7:
	subl	$12, %esp
	pushl	$.LC6
	call	puts
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L13
.L6:
	subl	$4, %esp
	pushl	$64
	pushl	$.LC7
	leal	-72(%ebp), %eax
	pushl	%eax
	call	strncmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L10
	call	is_root
	testl	%eax, %eax
	je	.L11
	subl	$12, %esp
	pushl	$19088743
	call	reboot
	addl	$16, %esp
	jmp	.L8
.L11:
	subl	$12, %esp
	pushl	$.LC6
	call	puts
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L13
.L10:
	subl	$4, %esp
	pushl	$64
	pushl	$.LC8
	leal	-72(%ebp), %eax
	pushl	%eax
	call	strncmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L12
	pushl	$0
	pushl	$.LC9
	pushl	$.LC10
	pushl	$.LC10
	call	execl
	addl	$16, %esp
	movl	$2, %eax
	jmp	.L13
.L12:
	subl	$12, %esp
	pushl	$.LC11
	call	puts
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L13
.L8:
	movl	$0, %eax
.L13:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	run, .-run
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$4, %esp
	call	become_all_powerful
	call	print_menu
	call	run
	addl	$4, %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
