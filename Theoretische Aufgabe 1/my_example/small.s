	.file	"small.c"		# lines beginning with . are assembler directives
	.text
	.globl	main			# global label main
	.type	main, @function
# suffixes on functions denote variable length: l for long (32bit), q for quad(64bit), b for byte (8bit)


# important stuff:
# r bp is stack base pointer, holds current stack frame
# r sp is stack top address pointer
# r:64, e:32, ax:16, al/ah 8bit high/low
# -cfi_* is information for debugging and exception handling about our offsets


main: 					# label main function
.LFB0:					# another label
.cfi_startproc			# 
	pushq	%rbp			# push rbp (our return address) to stack
.cfi_def_cfa_offset 16		# set canonical frame address offset to 16
.cfi_offset 6, -16		# save r6 at -16 offset from cfa
	movq	%rsp, %rbp		# write top pointer to base pointer
.cfi_def_cfa_register 6		# use r6 as cfa register
	movb	$5, -9(%rbp)		# load 5 into our variable space below the stack
	leaq	-9(%rbp), %rax		# load effective address of 'a' into rax, creating the pointer
	movq	%rax, -8(%rbp)		# save the address in our variable space
	movl	$0, %eax		# write 0 into the lower 32 bits of rax (empty it?)
	popq	%rbp			# pop rbp from stack
.cfi_def_cfa 7, 8		# compute cfa as "take address from r7, add offset 8"
	ret				# exit this function: overwrite the top pointer with the base pointer,
					# and overwrite the base pointer with the base pointer on the stack,
					# effectively moving down one stack frame
.cfi_endproc			# 
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 5.3.0"
	.section	.note.GNU-stack,"",@progbits