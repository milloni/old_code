	.file	"callingconv.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"%d %d %d %d %d %d %d %d %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	999
	push	888
	push	777
	push	666
	mov	r9d, 555
	mov	r8d, 444
	mov	ecx, 333
	mov	edx, 222
	mov	esi, 111
	mov	edi, OFFSET FLAT:.LC0
	mov	eax, 0
	call	printf
	add	rsp, 32
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.3.1 20190223 (Red Hat 8.3.1-2)"
	.section	.note.GNU-stack,"",@progbits
