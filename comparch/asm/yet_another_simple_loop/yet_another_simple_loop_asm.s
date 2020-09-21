	.file	"yet_another_simple_loop_asm.s"

	.section	.rodata
printf_str:
	.string	"Loop count: %#x\n"

	.text
	.globl	yet_another_simple_loop
	.type	yet_another_simple_loop, @function
yet_another_simple_loop:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	$0x00
	jmp	L2
L1:
	pushl	-0x04(%ebp)
	pushl	$printf_str
	call	printf
	addl	$0x08, %esp
	incl	-0x04(%ebp)
L2:
	cmpl	$0x10, -0x04(%ebp)
	jl	L1
	movl	%ebp, %esp
	popl	%ebp
