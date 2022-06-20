#注意需要disable branch delay slot

.text
.globl main
main: 
     subu 	$sp,$sp,32 	# Stack frame is 32 bytes long
     sw 	$ra,20($sp) 	# Save return address
     sw 	$fp,16($sp) 	# Save old frame pointer
     addiu 	$fp,$sp,28 	# Set up frame pointer

     li	$a0,10 		# Put argument (10) in $a0
     jal 	fact 		# Call factorial function

     move 	$a0,$v0		#
     li	$v0,1 		# Print the result
     syscall			

     lw 	$ra,20($sp) 	# Restore return address
     lw 	$fp,16($sp) 	# Restore frame pointer
     addiu 	$sp,$sp,32 	# Pop stack frame

     li 	$v0, 10 		# terminate program run and
     syscall 		# return control to system


.text
fact:
     subu 	$sp,$sp,32 	# Stack frame is 32 bytes long
     sw 	$ra,20($sp)	# Save return address
     sw 	$fp,16($sp) 	# Save frame pointer
     addiu 	$fp,$sp,28 	# Set up frame pointer
     sw 	$a0,0($fp) 	# Save argument (n)

     lw 	$v0,0($fp) 	# Load n
     bgtz 	$v0,$L2 		# Branch if n > 0
     li 	$v0,1 		# Return 1
     jr 	$L1 		# Jump to code to return
$L2:
    lw 	$v1,0($fp) 	# Load n
    subu	$v0,$v1,1 	# Compute n - 1
    move 	$a0,$v0 		# Move value to $a0
    jal 	fact 		# Call factorial function
   lw 	$v1,0($fp) 	# Load n
   mul 	$v0,$v0,$v1 	# Compute fact(n-1) * n

$L1: 			# Result is in $v0
    lw 	$ra, 20($sp)	# Restore $ra
    lw 	$fp, 16($sp) 	# Restore $fp
    addiu 	$sp, $sp, 32 	# Pop stack
    jr 	$ra 		# Return to caller