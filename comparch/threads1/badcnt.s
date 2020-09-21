	.file	"badcnt.c"
	.globl	cnt
	.bss
	.align 4
	.type	cnt, @object
	.size	cnt, 4
cnt:
	.zero	4
	.text
	.globl	_f
	.type	_f, @function
_f:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$12, %esp
	pushl	8(%ebp)
	call	perror
	addl	$16, %esp
	subl	$12, %esp
	pushl	$1
	call	exit
	.cfi_endproc
.LFE0:
	.size	_f, .-_f
	.section	.rodata
.LC0:
	.string	"pthread_create"
.LC1:
	.string	"pthread_joint"
.LC2:
	.string	"BOOM! cnt=%u\n"
.LC3:
	.string	"OK cnt=%u\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
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
	subl	$20, %esp
	pushl	$0
	pushl	$count
	pushl	$0
	leal	-12(%ebp), %eax
	pushl	%eax
	call	pthread_create
	addl	$16, %esp
	testl	%eax, %eax
	je	.L3
	subl	$12, %esp
	pushl	$.LC0
	call	_f
	addl	$16, %esp
.L3:
	pushl	$0
	pushl	$count
	pushl	$0
	leal	-16(%ebp), %eax
	pushl	%eax
	call	pthread_create
	addl	$16, %esp
	testl	%eax, %eax
	je	.L4
	subl	$12, %esp
	pushl	$.LC0
	call	_f
	addl	$16, %esp
.L4:
	movl	-12(%ebp), %eax
	subl	$8, %esp
	pushl	$0
	pushl	%eax
	call	pthread_join
	addl	$16, %esp
	testl	%eax, %eax
	je	.L5
	subl	$12, %esp
	pushl	$.LC1
	call	_f
	addl	$16, %esp
.L5:
	movl	-16(%ebp), %eax
	subl	$8, %esp
	pushl	$0
	pushl	%eax
	call	pthread_join
	addl	$16, %esp
	testl	%eax, %eax
	je	.L6
	subl	$12, %esp
	pushl	$.LC1
	call	_f
	addl	$16, %esp
.L6:
	movl	cnt, %eax
	cmpl	$2000, %eax
	je	.L7
	movl	cnt, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	jmp	.L8
.L7:
	movl	cnt, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC3
	call	printf
	addl	$16, %esp
.L8:
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.globl	count
	.type	count, @function
count:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	jmp	.L11
.L12:
	movl	cnt, %eax
	addl	$1, %eax
	movl	%eax, cnt
	addl	$1, -4(%ebp)
.L11:
	cmpl	$999, -4(%ebp)
	jle	.L12
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	count, .-count
	.ident	"GCC: (GNU) 6.3.1 20161221 (Red Hat 6.3.1-1)"
	.section	.note.GNU-stack,"",@progbits
