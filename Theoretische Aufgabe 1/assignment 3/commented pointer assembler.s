	.file	"pointer.c"
	.section	.rodata
.LC0:
	.string	"p\taddress\t%p\n"
.LC1:
	.string	"p\tcontent\t%d\n"
.LC2:
	.string	"a\taddress\t%p\n"
.LC3:
	.string	"a\tcontent\t%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp		# save base pointer to stack
	.cfi_def_cfa_offset 16	# .cfi_*: debug, exception handling
	.cfi_offset 6, -16
	movq	%rsp, %rbp	# use current stack top as stack base for now
	.cfi_def_cfa_register 6
	subq	$16, %rsp	# subtract 16 from top pointer to keep space for our variables free (increase frame size)
	movb	$5, -9(%rbp)	# save 5 (a) into our stack frame
	leaq	-9(%rbp), %rax	# save the address of the 5 (p:=&a) into rax
	movq	%rax, -8(%rbp)	# move the address to stack frame (p)
############################################################# ^char *p = &a ##########################################################
	movq	-8(%rbp), %rax	# copy a's address from p (in the stack frame) to rax
	movq	%rax, %rsi	# copy p(==a's address) to the second argument register
	movl	$.LC0, %edi	# copy a reference to the string to the first argument register
	movl	$0, %eax	# clean eax
	call	printf		# call printf
############################################################# ^printf p ##############################################################
	movq	-8(%rbp), %rax	# copy p to rax
	movzbl	(%rax), %eax	# resolve %rax (so like *%rax or like *p) and copy that value to %eax
	movsbl	%al, %eax	# move, padding with the src MSB, from byte to long.
	movl	%eax, %esi	# copy *p==a to the second argument register
	movl	$.LC1, %edi	# copy a reference to the string to the first argument register
	movl	$0, %eax	# clear eax
	call	printf		# call printf
############################################################# ^printf *p #############################################################
	movq	-8(%rbp), %rax	# copy p to rax
	movb	$22, (%rax)	# overwrite *rax with 22
	leaq	-9(%rbp), %rax	# copy effective address of a (==&a) to rax
	movq	%rax, %rsi	# copy &a==(old p) to the second argument register
	movl	$.LC2, %edi	# copy a reference to the string to the first argument register
	movl	$0, %eax	# clear eax
	call	printf		# call printf
############################################################# ^printf &a #############################################################
	movzbl	-9(%rbp), %eax	# move from a to eax, padding from byte to long with zeroes
	movsbl	%al, %eax	# copy from al to eax, this time padding with al's MSB (sign)
	movl	%eax, %esi	# copy a to the second argument register
	movl	$.LC3, %edi	# copy reference to the string to the first argument register
	movl	$0, %eax	# clear eax
	call	printf		# call printf
############################################################# ^printf a ##############################################################
	movl	$0, %eax	# clear eax
	leave			# leave the stack frame
	.cfi_def_cfa 7, 8
	ret			# return from function
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 5.3.0"
	.section	.note.GNU-stack,"",@progbits
