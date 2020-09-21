	.code32	
	.file	"cond_asm.s"
	.text	
	.globl	cond
	.type	cond, @function
cond:	
	pushl	%ebp
	movl	%esp, %ebp
	movl	0x0c(%ebp), %edx
	cmpl	$0x00, %edx
	je	L1
	movl	0x08(%ebp), %eax
	cmpl	$0x00, %eax
	jle	L1
	addl	%eax, (%edx)
L1:
	leave
	ret

