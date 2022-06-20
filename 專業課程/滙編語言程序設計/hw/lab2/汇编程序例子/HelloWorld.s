# helloworld.s
#
# Print out "Hello World"
#

        .data
msg:  
        .asciiz "Hello World"

        .text
        .globl main
main: 
        #lw $v0, 1($0)   # ADEL
        #sw $v0, 1($0)   # ADES
        lui $7, 32767
        lui $8, 32767
        add $9, $7, $8
        j kira
        sw $v0, 1($0)   # ADES
        lui $10, 65535
kira:
        li $v0, 4       # syscall 4 (print_str)
        la $a0, msg     # argument: string
        
        syscall         # print the string
        
        jr $ra          # retrun to caller
        nop
