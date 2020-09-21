	.file	"fib_dw.c"
	.text
	.globl	fib_dw
	.type	fib_dw, @function
fib_dw:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)	# i
	movl	$0, -8(%ebp)	# val
	movl	$1, -12(%ebp)	# nval
.L2:
	movl	-8(%ebp), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, -16(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, -12(%ebp)
	addl	$1, -4(%ebp)
	movl	-4(%ebp), %eax
	cmpl	8(%ebp), %eax
	jl	.L2
	movl	-8(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	fib_dw, .-fib_dw
	.ident	"GCC: (GNU) 6.1.1 20160621 (Red Hat 6.1.1-3)"
	.section	.note.GNU-stack,"",@progbits
