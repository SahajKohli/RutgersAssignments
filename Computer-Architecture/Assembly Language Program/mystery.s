	.file	"mystery.c"
	.text
.globl add
	.type	add, @function
add:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	leal	(%edx,%eax), %eax
	popl	%ebp
	ret
	.size	add, .-add
.globl compute_fib
	.type	compute_fib, @function
compute_fib:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	cmpl	$0, 8(%ebp)
	jg	.L4
	movl	$0, %eax
	jmp	.L5
.L4:
	cmpl	$1, 8(%ebp)
	jne	.L6
	movl	$1, %eax
	jmp	.L5
.L6:
	movl	8(%ebp), %eax
	subl	$2, %eax
	movl	%eax, (%esp)
	call	compute_fib
	movl	%eax, %ebx
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, (%esp)
	call	compute_fib
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	add
.L5:
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	compute_fib, .-compute_fib
	.section	.rodata
	.align 4
.LC0:
	.string	"ERROR. Too many arguments! Syntax: ./mystery <pos_int>\n"
	.align 4
.LC1:
	.string	"ERROR. No Argument Provided! Syntax: ./mystery <pos_int>\n"
	.align 4
.LC2:
	.string	"ERROR. Negative Integer! Syntax: ./mystery <pos_int>\n"
	.align 4
.LC3:
	.string	"ERROR. Integer too large! Syntax: ./mystery <pos_int>\n"
.LC4:
	.string	"%s"
.LC5:
	.string	"Value: "
.LC6:
	.string	"%d\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	cmpl	$2, 8(%ebp)
	jle	.L9
	movl	stderr, %eax
	movl	%eax, %edx
	movl	$.LC0, %eax
	movl	%edx, 12(%esp)
	movl	$55, 8(%esp)
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	fwrite
	movl	$1, (%esp)
	call	exit
.L9:
	cmpl	$1, 8(%ebp)
	jne	.L10
	movl	stderr, %eax
	movl	%eax, %edx
	movl	$.LC1, %eax
	movl	%edx, 12(%esp)
	movl	$57, 8(%esp)
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	fwrite
	movl	$1, (%esp)
	call	exit
.L10:
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	atoi
	movl	%eax, 28(%esp)
	cmpl	$0, 28(%esp)
	jns	.L11
	movl	stderr, %eax
	movl	%eax, %edx
	movl	$.LC2, %eax
	movl	%edx, 12(%esp)
	movl	$53, 8(%esp)
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	fwrite
	movl	$1, (%esp)
	call	exit
.L11:
	cmpl	$46, 28(%esp)
	jle	.L12
	movl	stderr, %eax
	movl	%eax, %edx
	movl	$.LC3, %eax
	movl	%edx, 12(%esp)
	movl	$54, 8(%esp)
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	fwrite
	movl	$1, (%esp)
	call	exit
.L12:
	movl	$.LC4, %eax
	movl	$.LC5, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	compute_fib
	movl	$.LC6, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	printf
	movl	$0, (%esp)
	call	exit
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-16)"
	.section	.note.GNU-stack,"",@progbits
