	.file	"array_sum_asm.s"
		
	.section	.rodata
D1:
	.string	"%i"
D2:
	.string	"%d\n"

	.text
	.globl	array_sum
	.type	array_sum, @function
array_sum:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$0x1c, %esp
	movl	$0x00, -0x18(%ebp)	# i
	movl	$0x00, -0x1c(%ebp)	# sum
	jmp	L2
L1:
	movl	-0x18(%ebp), %ecx
	leal	-0x14(%ebp), %edx
	leal	(%edx, %ecx, 4), %edx
	pushl	%edx
	pushl	$D1
	#int	$3
	call	scanf
	addl	$0x08, %esp
	incl	-0x18(%ebp)
L2:
	movl	-0x18(%ebp), %ecx
	cmpl	$5, %ecx
	jl	L1
	#int	$3
	movl	$0x00, -0x18(%ebp)
	jmp	L4
L3:
	movl	-0x18(%ebp), %ecx
	leal	-0x14(%ebp), %edx
	leal	(%edx, %ecx, 4), %edx
	movl	(%edx), %eax
	addl	%eax, -0x1c(%ebp)
	incl	-0x18(%ebp)
L4:
	movl	-0x18(%ebp), %ecx
	cmpl	$5, %ecx
	jl	L3
	movl	-0x1c(%ebp), %eax
	pushl	%eax
	pushl	$D2
	call	printf
	add	$0x08, %esp
	movl	%ebp, %esp
	popl	%ebp
	ret

