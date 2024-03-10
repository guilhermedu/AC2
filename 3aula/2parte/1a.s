.equ SFR_BASE_HI, 0xBF88    # 16 MSbits of SFR area
.equ TRISE, 0x6100          #TRISE address is 0xBF886100
.equ PORTE, 0x6106          #PORTB address is 0xBF886110
.equ LATE, 0x6120           #LATE address is 0xBF886120
.equ TRISB, 0x6040        #TRISB address is 0xBF886040
.equ PORTB, 0x6050        #PORTB address is 0xBF886050

.data
.text
.globl main

main:
    lui $t0, SFR_BASE_HI #$t0=0xBF880000;

    lw $t1,TRISE($t0)
    andi $t1,$t1,0xFFE1   
    sw $t1,TRISE($t0)     #RE4-1 is output;
    li $t2,0            #counter=0;

loop:
    lw $t3,PORTB($t0)
    andi $t3,$t3,0xFFE1
    sll $t4,$t2,1   
    or $t3,$t4,$t3
    sw $t3,LATE($t0)      #RE0=RB0;

    li $v0,12
    syscall              #resetCoreTimer
delay:
    li $v0,11
    syscall             #readCoreTimer
    blt $v0,20000000,delay

    addi $t2,$t2,1 #counter++;
    #andi $t2,$t2,0x000F
    blt $t2,16,cont
    li $t2,0
cont:
    j loop
    jr $ra
