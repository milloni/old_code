	.file	"mat_increment_asm.s"


	.text	
	.globl	mat_init
	.type	mat_init, @function
mat_init:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	0x08(%ebp), %edi
	movl	$0x0c, %ecx
	xorl	%eax, %eax
	#int	$0x03
	rep stosl
	#int	$0x03
	popl	%edi
	movl	%ebp, %esp	
	popl	%ebp
	ret


	.globl	mat_increment
	.type	mat_increment, @function
mat_increment:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$0x30, %esp
	leal	-0x30(%ebp), %eax
	pushl	%eax
	call	mat_init
	addl	$0x04, %esp
	leal	-0x30(%ebp),%edx
	movl	0x08(%ebp), %ecx
	sall	$4, %ecx
	addl	%ecx, %edx
	movl	0x0c(%ebp), %ecx
	#int	$0x03
	incl	(%edx, %ecx, 4)
	leal	-0x30(%ebp), %eax
	pushl	%eax
	call	mat_print
	addl	$0x04, %esp
	movl	%ebp, %esp
	popl	%ebp
	ret

