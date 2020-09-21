	.code32	
	.file	"simple_loop_asm.s"
	.text
	.globl	f
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$0x08, %esp
	movl	$0x00, -0x04(%ebp) # sum
	movl	$0xff, -0x08(%ebp) # i
L1:
	movl	-0x04(%ebp), %eax
	addl	-0x08(%ebp), %eax
	movl	%eax, -0x04(%ebp)
	movl	-0x08(%ebp), %eax
	dec	%eax
	movl	%eax, -0x08(%ebp)
	cmpl	$0x00, %eax
	jg	L1
	movl	-0x04(%ebp), %eax
	movl	%ebp, %esp
	popl	%ebp
	ret

