.equ SFR_BASE_HI, 0xBF88    # 16 MSbits of SFR area
.equ TRISE, 0x6100          #TRISE address is 0xBF886100
.equ PORTE, 0x6106          #PORTB address is 0xBF886110
.equ LATE, 0x6120           #LATE address is 0xBF886120
.equ TRISD, 0x60C0        #TRISB address is 0xBF886040
.equ PORTD, 0x60D0        #PORTB address is 0xBF886050

.data
.text
.globl main

main:
    lui $t0, SFR_BASE_HI #$t0=0xBF880000;
    lw $t1,TRISD($t0)    
    ori $t1,$t1,0x0080    #$t1=0x0000000001000000;
    sw $t1,TRISD($t0)     #RB0 is input;

    lw $t1,TRISE($t0)
    andi $t1,$t1,0xFFFE   
    sw $t1,TRISE($t0)     #RE0 is output;
loop:
    lw $t1,PORTD($t0)
    andi $t1,$t1,0x0100    #só fica o bit 8 #0x00000001000
    srl $t1,$t1,8       #bit 8 vai para bit 0


    lw $t2,LATE($t0)
    andi $t2,$t2,0xFFFE
    or $t2,$t2,$t1
    sw $t2,LATE($t0)      #RE0=RB0;
    j loop
    jr $ra
