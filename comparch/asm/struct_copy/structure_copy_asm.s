	.file	"structure_copy_asm.s"
	.set	sizeof_structure, 0x08	# in dwords.
	
	.text
	.globl	structure_copy
	.type	structure_copy, @function
structure_copy:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%edi
	movl	$sizeof_structure, %ecx
	movl	0x08(%ebp), %edi
	movl	0x0c(%ebp), %esi
	rep movsl	
	popl	%edi
	popl	%esi
	movl	%ebp, %esp
	popl	%ebp
	ret

