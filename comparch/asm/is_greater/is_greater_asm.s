	.code32	
	.file	"is_greater_asm.s"
	.text	
	.globl	is_greater
	.type	is_greater, @function
is_greater:
	pushl	%ebp
	movl	%esp, %ebp
	movl	0x08(%ebp), %edx
	cmpl	0x0c(%ebp), %edx
	jle	L1
	movl	$0x01, %eax
	jmp	L2
L1:
	movl	$0x00, %eax	
L2:
	leave
	ret

