	.file	"printf.c"
	.text
	.globl	int_to_string
	.type	int_to_string, @function
int_to_string:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	cmpl	$0, -28(%rbp)
	jne	.L2
	movq	-24(%rbp), %rax
	movb	$48, (%rax)
	jmp	.L1
.L2:
	cmpl	$0, -28(%rbp)
	jns	.L5
	negl	-28(%rbp)
	movl	$1, -12(%rbp)
	jmp	.L5
.L6:
	movl	-28(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movl	%edx, %eax
	leal	48(%rax), %ecx
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -4(%rbp)
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movl	-28(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -28(%rbp)
.L5:
	cmpl	$0, -28(%rbp)
	jg	.L6
	cmpl	$0, -12(%rbp)
	je	.L7
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -4(%rbp)
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$45, (%rax)
.L7:
	movl	$0, -8(%rbp)
	jmp	.L8
.L9:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, -16(%rbp)
	movl	-4(%rbp), %eax
	subl	-8(%rbp), %eax
	cltq
	leaq	-1(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rcx
	movq	-24(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	movl	-4(%rbp), %eax
	subl	-8(%rbp), %eax
	cltq
	leaq	-1(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	-16(%rbp), %edx
	movb	%dl, (%rax)
	addl	$1, -8(%rbp)
.L8:
	movl	-4(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	cmpl	%eax, -8(%rbp)
	jl	.L9
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
.L1:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	int_to_string, .-int_to_string
	.globl	millonis_printf
	.type	millonis_printf, @function
millonis_printf:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$272, %rsp
	movq	%rdi, -264(%rbp)
	movq	%rsi, -168(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L27
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L27:
	movq	-264(%rbp), %rax
	movq	%rax, -184(%rbp)
	movl	$0, -196(%rbp)
	movq	$0, -256(%rbp)
	movq	$0, -248(%rbp)
	movl	%esi, -212(%rbp)
	movl	%edx, -216(%rbp)
	movl	%ecx, -220(%rbp)
	movq	%r8, %rax
	movl	%eax, -224(%rbp)
	movq	%r9, %rax
	movl	%eax, -228(%rbp)
	movq	%rbp, %rax
	movq	%rax, -208(%rbp)
	addq	$8, -208(%rbp)
	addq	$8, -208(%rbp)
	movq	-184(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -185(%rbp)
	jmp	.L12
.L26:
	cmpb	$37, -185(%rbp)
	jne	.L13
	addq	$1, -184(%rbp)
	movq	-184(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -185(%rbp)
	cmpb	$0, -185(%rbp)
	je	.L28
	cmpb	$100, -185(%rbp)
	jne	.L25
	cmpl	$4, -196(%rbp)
	ja	.L17
	movl	-196(%rbp), %eax
	movq	.L19(,%rax,8), %rax
	jmp	*%rax
	.section	.rodata
	.align 8
	.align 4
.L19:
	.quad	.L23
	.quad	.L22
	.quad	.L21
	.quad	.L20
	.quad	.L18
	.text
.L23:
	movl	-212(%rbp), %eax
	movl	%eax, -192(%rbp)
	addl	$1, -196(%rbp)
	jmp	.L24
.L22:
	movl	-216(%rbp), %eax
	movl	%eax, -192(%rbp)
	addl	$1, -196(%rbp)
	jmp	.L24
.L21:
	movl	-220(%rbp), %eax
	movl	%eax, -192(%rbp)
	addl	$1, -196(%rbp)
	jmp	.L24
.L20:
	movl	-224(%rbp), %eax
	movl	%eax, -192(%rbp)
	addl	$1, -196(%rbp)
	jmp	.L24
.L18:
	movl	-228(%rbp), %eax
	movl	%eax, -192(%rbp)
	addl	$1, -196(%rbp)
	jmp	.L24
.L17:
	movq	-208(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -192(%rbp)
	addq	$8, -208(%rbp)
	nop
.L24:
	movl	-192(%rbp), %edx
	leaq	-256(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	int_to_string
	movq	stdout(%rip), %rdx
	leaq	-256(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fputs
	jmp	.L25
.L13:
	movsbl	-185(%rbp), %eax
	movl	%eax, %edi
	call	putchar
.L25:
	addq	$1, -184(%rbp)
	movq	-184(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -185(%rbp)
.L12:
	cmpb	$0, -185(%rbp)
	jne	.L26
	jmp	.L15
.L28:
	nop
.L15:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	millonis_printf, .-millonis_printf
	.globl	millonis_printf2
	.type	millonis_printf2, @function
millonis_printf2:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$256, %rsp
	movq	%rdi, -248(%rbp)
	movq	%rsi, -168(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L40
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L40:
	movq	-248(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	$0, -240(%rbp)
	movq	$0, -232(%rbp)
	movl	$8, -216(%rbp)
	movl	$48, -212(%rbp)
	leaq	16(%rbp), %rax
	movq	%rax, -208(%rbp)
	leaq	-176(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-184(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -185(%rbp)
	jmp	.L31
.L39:
	cmpb	$37, -185(%rbp)
	jne	.L32
	addq	$1, -184(%rbp)
	movq	-184(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -185(%rbp)
	cmpb	$0, -185(%rbp)
	je	.L41
	cmpb	$100, -185(%rbp)
	jne	.L38
	movl	-216(%rbp), %eax
	cmpl	$47, %eax
	ja	.L36
	movq	-200(%rbp), %rax
	movl	-216(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-216(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -216(%rbp)
	jmp	.L37
.L36:
	movq	-208(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -208(%rbp)
.L37:
	movl	(%rax), %eax
	movl	%eax, -192(%rbp)
	movl	-192(%rbp), %edx
	leaq	-240(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	int_to_string
	movq	stdout(%rip), %rdx
	leaq	-240(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fputs
	jmp	.L38
.L32:
	movsbl	-185(%rbp), %eax
	movl	%eax, %edi
	call	putchar
.L38:
	addq	$1, -184(%rbp)
	movq	-184(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -185(%rbp)
.L31:
	cmpb	$0, -185(%rbp)
	jne	.L39
	jmp	.L34
.L41:
	nop
.L34:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	millonis_printf2, .-millonis_printf2
	.section	.rodata
	.align 8
.LC0:
	.string	"asdf%dx yz%dqwerty %d %d %d %d %d %d %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	$9
	pushq	$8
	pushq	$7
	pushq	$6
	movl	$5, %r9d
	movl	$4, %r8d
	movl	$34153, %ecx
	movl	$2431, %edx
	movl	$1, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	millonis_printf
	addq	$32, %rsp
	pushq	$9
	pushq	$8
	pushq	$7
	pushq	$6
	movl	$5, %r9d
	movl	$4, %r8d
	movl	$34153, %ecx
	movl	$2431, %edx
	movl	$1, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	millonis_printf
	addq	$32, %rsp
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.3.1 20190223 (Red Hat 8.3.1-2)"
	.section	.note.GNU-stack,"",@progbits
