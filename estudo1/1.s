.data
.equ BASE,0xBF88
.equ TRISE,0x6100
.equ LATE, 0x6120
.text
.globl main
main: 
    addiu $sp,$sp,-16
    sw $ra,0($sp)
    sw $s0,4($sp)
    sw $s1,8($sp)
    sw $s2,12($sp)

    lui $s0,BASE
    lw $s1,TRISE($s0)
    andi $s1,$s1,0xFFE0
    sw $s1,TRISE($s0)           # RE5 - 0 as outputs

    li $s2,0x0001
    lw $s1,LATE($s0)
    andi $s1,$s1,0xFFE0
    or $s1,$s1,$s2
    sw $s1,LATE($s0)
loop:
if: beq $s2,16,else
    sll $s2,$s2,1
    j endif
else:
    li $s2, 0x0001
endif:
    andi $s1,$s1,0xFFE0
    or $s1,$s1,$s2
    sw $s1,LATE($s0)

    li $a0,200
    jal delay

    j loop

    
    lw $ra,0($sp)
    lw $s0,4($sp)
    lw $s1,8($sp)
    lw $s2,12($sp)
    addiu $sp,$sp,16

    jr $ra

delay:
    li $v0,12
    syscall
    li $t0,20000
    mulou $t0,$t0,$a0
read:
    li $v0,11
    syscall
    bne $v0,$t0,end
    j read
end:
    jr $ra