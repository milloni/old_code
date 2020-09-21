	.file	"array_sum.c"
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"%d\n"
	.text
	.globl	array_sum
	.type	array_sum, @function
array_sum:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$0, -12(%ebp)
	jmp	.L2
.L3:
	leal	-40(%ebp), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC0
	call	__isoc99_scanf
	addl	$16, %esp
	addl	$1, -12(%ebp)
.L2:
	cmpl	$4, -12(%ebp)
	jle	.L3
	movl	$0, -16(%ebp)
	movl	$0, -20(%ebp)
	jmp	.L4
.L5:
	movl	-20(%ebp), %eax
	movl	-40(%ebp,%eax,4), %eax
	addl	%eax, -16(%ebp)
	addl	$1, -20(%ebp)
.L4:
	cmpl	$4, -20(%ebp)
	jle	.L5
	subl	$8, %esp
	pushl	-16(%ebp)
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	array_sum, .-array_sum
	.ident	"GCC: (GNU) 6.1.1 20160621 (Red Hat 6.1.1-3)"
	.section	.note.GNU-stack,"",@progbits
