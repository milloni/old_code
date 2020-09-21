	.file	"simple_loop_again.c"
	.section	.rodata
.LC0:
	.string	"Fear of the duck"
	.text
	.globl	simple_loop_again
	.type	simple_loop_again, @function
simple_loop_again:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	$.LC0, -12(%ebp)
	movl	$0, -8(%ebp)
	jmp	.L2
.L3:
	movl	-8(%ebp), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	addl	%eax, -4(%ebp)
	addl	$1, -8(%ebp)
.L2:
	movl	-8(%ebp), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L3
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	simple_loop_again, .-simple_loop_again
	.ident	"GCC: (GNU) 6.1.1 20160621 (Red Hat 6.1.1-3)"
	.section	.note.GNU-stack,"",@progbits
