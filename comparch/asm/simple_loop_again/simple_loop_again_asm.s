	.code32	
	.file	"simple_loop_again_asm.s"
	
	.section .rodata
data_str:
	.string	"Fear of the duck"

	.text
	.globl	simple_loop_again
	.type	simple_loop_again, @function
simple_loop_again:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$0x0c, %esp
	movl	$0x00, -0x04(%ebp)	# int 	sum
	movl	$data_str, -0x08(%ebp)	# char *str
	movl	$0x00, -0x0c(%ebp)	# int	i
	jmp	L2
L1:
	movl	-0x08(%ebp), %eax
	addl	-0x0c(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	addl	%eax, -0x04(%ebp)
	incl	-0x0c(%ebp)
L2:
	movl	-0x08(%ebp), %eax
	addl	-0x0c(%ebp), %eax
	movb	(%eax), %al
	testb	%al, %al
	jnz	L1
	movl	-0x04(%ebp), %eax
	movl	%ebp, %esp
	popl	%ebp
	ret
