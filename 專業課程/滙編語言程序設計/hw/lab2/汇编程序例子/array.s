.data
     array: 
	.word -4, 5, 8, -1
     msg1: 
	.asciiz "\n The sum of the positive values = "
     msg2:
	.asciiz "\n The sum of the negative values = "

.globl main
.text
    main:
            li   $v0, 4		
            la  $a0, msg1 	# load address of msg1. into $a0
            syscall 		# print the string
            la $a0, array 	# Initialize address Parameter
            li   $a1, 4 		# Initialize length Parameter
            jal sum 		# Call sum
            nop		# delay slot
            move $a0, $v0 	# move value to be printed to $a0
            li   $v0, 1 		# system call code for print_int
            syscall 		# print sum of Pos:

            li   $v0, 4 			# system call code for print_str
            la   $a0, msg2 		# load address of msg2. into $a0
            syscall 			            # print the string
            li   $v0, 1			# system call code for print_int
            move $a0, $v1		# move value to be printed to $a0
            syscall 				# print sum of neg

            li   $v0, 10 			# terminate program run and
            syscall                      		# return control to system

sum:
            li   $v0, 0
            li   $v1, 0 			# Initialize v0 and v1 to zero
loop:
           blez $a1, retzz 		# If (a1 <= 0) Branch to Return
           nop
           addi $a1, $a1, -1 		# Decrement loop count
           lw   $t0, 0($a0) 		# Get a value from the array
           addi $a0, $a0, 4 		# Increment array pointer to next
           bltz $t0, negg 		# If value is negative Branch to negg
           nop
           add  $v0, $v0, $t0 	                # Add to the positive sum
           b    loop 			# Branch around the next two 				
           nop
negg:
           add  $v1, $v1, $t0 	# Add to the negative sum
           b    loop 			# Branch to loop
           nop
retzz:
           jr    $ra 			# Return
           nop