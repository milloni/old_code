	.file	"abs.c"
	.text
	.globl	abs
	.type	abs, @function
abs:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	cmpl	$0, 8(%ebp)
	jle	.L2
	movl	8(%ebp), %eax
	jmp	.L3
.L2:
	movl	8(%ebp), %eax
	negl	%eax
.L3:
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	abs, .-abs
	.ident	"GCC: (GNU) 6.1.1 20160621 (Red Hat 6.1.1-3)"
	.section	.note.GNU-stack,"",@progbits
