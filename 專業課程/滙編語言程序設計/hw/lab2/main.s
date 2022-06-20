.globl	main
main: 
        lw $v0, 1($0)   # AdEL
        sw $v0, 1($0)   # AdES
        lui $7, 32767   # R7 = 7fff0000
        ori $7, 65535   # R7 = 7fffffff
        addi $7, 1      # Ov
        nop