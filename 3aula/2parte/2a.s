#contador binario crescente de 4 bits atualizado a uma frequencia de 1Hz
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

    lui $s0,SFR_BASE_HI     #Base
    li $s3,0                #Contador=0;

    lw $s1,TRISE($s0)       #Leitura do TRISE
    andi $s1,$s1,0xFFF0    #Mascara para os 4 bits menos significativos
    sw $s1,TRISE($s0)       #Escrita do TRISE

loop:
    lw $s2,LATE($s0)        #Leitura do LATE
    andi $s2,$s2,0xFFF0    #Mascara para os 4 bits menos significativos RE=0
    or $s2,$s2,$s3          #OR para escrever o contador no LATE
    sw $s2,LATE($s0)        #RE = contador

    addi $s3,$s3,1          #contador ++;
    andi $s3,$s3,0x000F     #contador < 16;

    li $a0,1000              #1hz
    jal delay                #delay(1000);

    j loop

    lw $ra,0($sp)
    lw $s0,4($sp)
    lw $s1,8($sp)
    lw $s2,12($sp)
    lw $s3,16($sp)
    addiu $sp,$sp,20

    li $v0,0                #return 0;
    jr $ra                

    #####################
delay:
    li $v0,RESET_CORE_TIMER
    syscall

loop2:
    li $v0,READ_CORE_TIMER
    syscall

    li $t0,2000     #k
    mul $t0,$t0,$a0 #k*ms
    blt $v0,$t0,loop2
    jr $ra