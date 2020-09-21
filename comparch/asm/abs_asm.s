	.code32
	.file 	"abs_asm.c"
	.text	
	.globl	abs
	.type	abs, @function
abs:
	pushl   %ebp
	movl    %esp, %ebp
	movl    8(%ebp), %edx
	testl   %edx, %edx
	jle     L1
	movl    %edx, %eax
	jmp     L2
L1:
	negl    %edx
	movl    %edx, %eax
L2:
	movl    %ebp, %esp
	popl    %ebp
	ret

