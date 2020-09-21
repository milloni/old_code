	.file	"yet_another_simple_loop.c"
	.section	.rodata
.LC0:
	.string	"Loop count: %#x\n"
	.text
	.globl	yet_another_simple_loop
	.type	yet_another_simple_loop, @function
yet_another_simple_loop:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$0, -12(%ebp)
	jmp	.L2
.L3:
	subl	$8, %esp
	pushl	-12(%ebp)
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	addl	$1, -12(%ebp)
.L2:
	cmpl	$15, -12(%ebp)
	jle	.L3
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	yet_another_simple_loop, .-yet_another_simple_loop
	.ident	"GCC: (GNU) 6.1.1 20160621 (Red Hat 6.1.1-3)"
	.section	.note.GNU-stack,"",@progbits
