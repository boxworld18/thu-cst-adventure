# Simple routine to demo a loop
# Compute the sum of N integers: 1 + 2 + 3 + ... + N
# From: http://labs.cs.upt.ro/labs/so2/html/resources/nachos-doc/mipsf.html

.text

	.globl	main
main:
	addiu       $t0, $0, 100		# N = 100

	# Initialize registers
	li	$t1, 0		# initialize counter (i)
	li	$t2, 0		# initialize sum

	# Main loop body
loop:	addi	$t1, $t1, 1	# i = i + 1
	add	$t2, $t2, $t1	# sum = sum + i
	beq	$t0, $t1, exit	# if i = N, continue
                nop
	j	loop
                nop

	# Exit routine - print msg2
exit:	li	$v0, 4		# print_string syscall code = 4
	la	$a0, msg2
	syscall

	# Print sum
	li	$v0,1		# print_string syscall code = 4
	move	$a0, $t2
	syscall

	# Print newline
	li	$v0,4		# print_string syscall code = 4
	la	$a0, lf
	syscall
	li	$v0,10		# exit
	syscall

	# Start .data segment (data!)
.data
                msg2:	.asciiz	"Sum = "
                lf:     .asciiz	"\n"