#
#	MIPS program to output argc and all argv arguments
#	

	.data

argcStr:		.asciiz	"argc = "
newlineStr:		.asciiz	"\n"
argvStr:		.asciiz	"argv["
closeBracketStr:	.asciiz	"] = \""
quoteNewlineStr:	.asciiz	"\"\n"

	.text
	.globl	main

main:	or	$s0, $0, $a0	# $s0 <- argc
	or	$s1, $0, $a1	# $s1 <- argv

	li	$v0, 4		# $v0 <- system call code for print_string
	la	$a0, argcStr	# $a0 -> the argc string
	syscall			# output the argc string

	li	$v0, 1		# $v0 <- system call code for print_int
	or	$a0, $0, $s0	# $a0 <- argc passed to us
	syscall			# output argc passed to us

	li	$v0, 4		# $v0 <- system call code for print_string
	la	$a0, newlineStr	# $a0 -> the newline string
	syscall			# output the newline string

	ori	$s2, $0, 0	# initialize the printed arg count to 0

loop:	beq	$s0, $0, loopexit	# exit the loop if no more arguments
                nop

	addiu	$s0, $s0, -1	# decrement the loop argument count

	li	$v0, 4		# $v0 <- system call code for print_string
	la	$a0, argvStr	# $a0 -> the argv string
	syscall			# output the argv string

	li	$v0, 1		# $v0 <- system call code for print_int
	or	$a0, $0, $s2	# $a0 <- printed arg count
	syscall			# output argc passed to us

	li	$v0, 4		# $v0 <- system call code for print_string
	la	$a0, closeBracketStr	# $a0 -> the close bracket string
	syscall			# output the close bracket string

	li	$v0, 4		# $v0 <- system call code for print_string
	lw	$a0, 0($s1)	# $a0 -> the next argument
	syscall			# output the next argument

	addiu	$s1, $s1, 4	# $s1 -> the pointer to the next argument

	li	$v0, 4		# $v0 <- system call code for print_string
	la	$a0, quoteNewlineStr	# $a0 -> the quote/newline string
	syscall			# output the quote/newline string

	addiu	$s2, $s2, 1	# increment the printed arg count

	beq	$0, $0, loop	# loop to print next argument
                nop

loopexit:  li	$v0, 10		# $v0 <- system call code for exit
	syscall			# exit from the program
