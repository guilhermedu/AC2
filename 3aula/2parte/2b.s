#contador binario decrescente de 4 bits atualizado a uma frequencia de 1Hz
.equ RESET_CORE_TIMER,12
.equ READ_CORE_TIMER,11
.equ SFR_BASE_HI,0xBF88
.equ TRISE,0x6100
.equ PORTE,0x6110
.equ LATE,0x6120
.data
.text
.globl main

main:
    addiu $sp,$sp,-20
    sw $ra,0($sp)
    sw $s0,4($sp)
    sw $s1,8($sp)
    sw $s2,12($sp)
    sw $s3,16($sp)
    

    lui $s0,SFR_BASE_HI     #base
    li $s3,0                #contador

    lw $s1,TRISE($s0)       #le o valor de TRISE
    andi $s1,$s1,0xFFF0     # Modifica RE0 a 3=out(0);
    sw $s1,TRISE($s0)       #escreve o valor de TRISE

loop:
    lw $s2,LATE($s0)        #le o valor de LATE
    andi $s2,$s2,0xFFF0     # RE=0;
    or $s2,$s2,$s3
    sw $s2,LATE($s0)        #escreve o valor de LATE

    subi	$s3, $s3, 1			# contador--
    andi    $s3,$s3,0x000F      # limita o contador a 4 bits

    li $a0,250         #4Hz
    jal delay

    j loop

    lw $ra,0($sp)
    lw $s0,4($sp)
    lw $s1,8($sp)
    lw $s2,12($sp)
    lw $s3,16($sp)
    addiu $sp,$sp,20

    li $v0,0  #return 0;
    jr $ra

    ################

delay:
    li $v0,RESET_CORE_TIMER
    syscall
loop2:
    li $v0,READ_CORE_TIMER
    syscall
    
    li $t0,2000    #k
    mul $t0,$t0,$a0  #k*ms
    blt $v0,$v0,loop2
    jr $ra
    
    