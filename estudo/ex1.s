.data
.equ BASE,0xBF88
.equ TRISE,0x6100
.equ LATE,0x6120
.equ Reset_Core_Timer,12
.equ Read_Core_Timer,11
.equ PRINT_INT,6
.equ PUT_CHAR,3

.text
.globl main

main:
    addiu $sp,$sp,-8
    sw $ra,0($sp)
    sw $s0,4($sp)
  

    ##################

    lui $t1,BASE

    lw $t2,TRISE($t1)
    andi $t2,$t2,0xFFE1   # 1111 1111 1110 0001
    sw $t2,TRISE($t1)

    li $s0,0b1001

loop:
    sll $t0,$s0,1 
    lw $t2,LATE($t1)
    andi $t2,$t2,0xFFE1
    or $t2,$t2,$t0
    sw $t2,LATE($t1)

    li $v0,PUT_CHAR
    li $a0,'\n'
    syscall                              # putchar('\r)


    li $v0,PRINT_INT
    move $a0,$s0
    li $a1,2
    # li $a1,16
    # ori $a1,$a1,2
    syscall         # print Int (patern,2 | 4 <<16)

    not $s0,$s0               
    andi $s0,$s0,0x000F   

    li $a0,143
    jal delay

    j loop

    lw $ra,0($sp)
    lw $s0,4($sp)
    addiu $sp,$sp,8

    jr $ra


delay:  li $v0,Reset_Core_Timer
        syscall
        li $t0,20000
        mul $t0,$t0,$a0
while:  li $v0,Read_Core_Timer
        syscall 
        bge $v0,$t0,end
        j while
end:
        jr $ra
