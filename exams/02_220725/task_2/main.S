	.file	"main.c"
	.text
	.section	.rodata
.LC0:
	.string	"Generating array"
.LC3:
	.string	"%lf "
	.align 8
.LC4:
	.string	"0 - ascending\n1 - descending\n2 - digit accumulator\n3 - absolute value\nChoose comparator: "
.LC5:
	.string	"%d"
.LC6:
	.string	"error: invalid parameter"
.LC7:
	.string	"Sorted array"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$160, %rsp
	movl	%edi, -148(%rbp)
	movq	%rsi, -160(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, -136(%rbp)
	jmp	.L2
.L3:
	movsd	.LC1(%rip), %xmm0
	movq	.LC2(%rip), %rax
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	rand_double
	movq	%xmm0, %rax
	movl	-136(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rax, -96(%rbp,%rdx,8)
	movl	-136(%rbp), %eax
	cltq
	movq	-96(%rbp,%rax,8), %rax
	movq	%rax, %xmm0
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	addl	$1, -136(%rbp)
.L2:
	cmpl	$9, -136(%rbp)
	jle	.L3
	movl	$10, %edi
	call	putchar@PLT
	movq	comp_asc@GOTPCREL(%rip), %rax
	movq	%rax, -128(%rbp)
	movq	comp_desc@GOTPCREL(%rip), %rax
	movq	%rax, -120(%rbp)
	movq	comp_whole_digit_acucmulator@GOTPCREL(%rip), %rax
	movq	%rax, -112(%rbp)
	movq	comp_abs@GOTPCREL(%rip), %rax
	movq	%rax, -104(%rbp)
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-140(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$1, %eax
	je	.L4
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$24, %edx
	movl	$1, %esi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$-1, %eax
	jmp	.L8
.L4:
	movl	-140(%rbp), %eax
	cltq
	movq	-128(%rbp,%rax,8), %rdx
	leaq	-96(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$10, %esi
	movq	%rax, %rdi
	call	qsort@PLT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, -132(%rbp)
	jmp	.L6
.L7:
	movl	-132(%rbp), %eax
	cltq
	movq	-96(%rbp,%rax,8), %rax
	movq	%rax, %xmm0
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	addl	$1, -132(%rbp)
.L6:
	cmpl	$9, -132(%rbp)
	jle	.L7
	movl	$10, %edi
	call	putchar@PLT
	movl	$0, %eax
.L8:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L9
	call	__stack_chk_fail@PLT
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.globl	rand_double
	.type	rand_double, @function
rand_double:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movsd	%xmm0, -8(%rbp)
	movsd	%xmm1, -16(%rbp)
	call	rand@PLT
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC8(%rip), %xmm2
	movapd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movsd	-16(%rbp), %xmm0
	subsd	-8(%rbp), %xmm0
	mulsd	%xmm1, %xmm0
	addsd	-8(%rbp), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	rand_double, .-rand_double
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1076101120
	.align 8
.LC2:
	.long	0
	.long	-1071382528
	.align 8
.LC8:
	.long	-4194304
	.long	1105199103
	.ident	"GCC: (GNU) 12.1.0"
	.section	.note.GNU-stack,"",@progbits
