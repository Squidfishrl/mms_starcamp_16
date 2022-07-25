	.file	"comparators.c"
	.text
	.globl	comp_asc
	.type	comp_asc, @function
comp_asc:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-32(%rbp), %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-16(%rbp), %xmm0
	subsd	-8(%rbp), %xmm0
	movq	.LC0(%rip), %xmm1
	andpd	%xmm0, %xmm1
	movsd	.LC1(%rip), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L6
	movl	$0, %eax
	jmp	.L4
.L6:
	movsd	-16(%rbp), %xmm0
	subsd	-8(%rbp), %xmm0
	cvttsd2sil	%xmm0, %eax
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	comp_asc, .-comp_asc
	.globl	comp_desc
	.type	comp_desc, @function
comp_desc:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-32(%rbp), %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	subsd	-16(%rbp), %xmm0
	movq	.LC0(%rip), %xmm1
	andpd	%xmm0, %xmm1
	movsd	.LC1(%rip), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L12
	movl	$0, %eax
	jmp	.L10
.L12:
	movsd	-8(%rbp), %xmm0
	subsd	-16(%rbp), %xmm0
	cvttsd2sil	%xmm0, %eax
.L10:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	comp_desc, .-comp_desc
	.globl	digit_sum
	.type	digit_sum, @function
digit_sum:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$0, -4(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	movl	%eax, -20(%rbp)
	jmp	.L14
.L15:
	movl	-20(%rbp), %ecx
	movslq	%ecx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %edx
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
	addl	%edx, -4(%rbp)
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$1717986919, %rdx, %rdx
	shrq	$32, %rdx
	movl	%edx, %ecx
	sarl	$2, %ecx
	cltd
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, -20(%rbp)
.L14:
	cmpl	$0, -20(%rbp)
	jne	.L15
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	digit_sum, .-digit_sum
	.globl	comp_whole_digit_acucmulator
	.type	comp_whole_digit_acucmulator, @function
comp_whole_digit_acucmulator:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	-16(%rbp), %rax
	movsd	(%rax), %xmm0
	cvttsd2sil	%xmm0, %eax
	movl	%eax, %edi
	call	digit_sum
	movl	%eax, %ebx
	movq	-24(%rbp), %rax
	movsd	(%rax), %xmm0
	cvttsd2sil	%xmm0, %eax
	movl	%eax, %edi
	call	digit_sum
	movl	%ebx, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	comp_whole_digit_acucmulator, .-comp_whole_digit_acucmulator
	.globl	comp_abs
	.type	comp_abs, @function
comp_abs:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-40(%rbp), %rax
	movsd	(%rax), %xmm0
	movq	.LC0(%rip), %xmm1
	andpd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	movq	-40(%rbp), %rax
	movsd	(%rax), %xmm0
	movq	.LC0(%rip), %xmm1
	andpd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	leaq	-16(%rbp), %rdx
	leaq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	comp_asc
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L21
	call	__stack_chk_fail@PLT
.L21:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	comp_abs, .-comp_abs
	.section	.rodata
	.align 16
.LC0:
	.long	-1
	.long	2147483647
	.long	0
	.long	0
	.align 8
.LC1:
	.long	-1998362383
	.long	1055193269
	.ident	"GCC: (GNU) 12.1.0"
	.section	.note.GNU-stack,"",@progbits
