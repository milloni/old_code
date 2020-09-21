int abs(int x) {
	if (x > 0) return x;
	else return -x;
}

// 	pushl	%ebp
// 	movl	%esp, %ebp
// 	movl	8(%ebp), %edx
// 	testl	%edx, %edx
// 	jle	L1
// 	movl	%edx, %eax
// 	jmp	L2
// .L1:
// 	negl	%edx
// 	movl	%edx, %eax
// .L2:
// 	movl	%ebp, %esp
// 	popl	%ebp
// 	ret


