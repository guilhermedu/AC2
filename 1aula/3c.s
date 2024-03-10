#int main(void)
#{
#int value;
#while(1)
#{
#printStr("\nIntroduza um inteiro (sinal e módulo): ");
#value = readInt10();
#printStr("\nValor em base 10 (signed): ");
#printInt10(value);
#printStr("\nValor em base 2: ");
#printInt(value, 2);
#printStr("\nValor em base 16: ");
#printInt(value, 16);
#printStr("\nValor em base 10 (unsigned): ");
#printInt(value, 10);
#printStr("\nValor em base 10 (unsigned), formatado: ");
#printInt(value, 10 | 5 << 16); // ver nota de rodapé 3
#}
#return 0;
#}


.data
.equ getChar,2
.equ putChar,3
.equ inkey,1
.equ printInt,6
.equ readInt10,5
.equ printStr,8
.equ printInt10,7
str1:   .asciiz "\nIntroduza um inteiro (sinal e módulo):"
str2:   .asciiz "\nValor em base 10(signed): "
str3:   .asciiz "\nValor em base 2:"
str4:   .asciiz "\nValor em base 10(unsigned): "
str5:   .asciiz "\nValor em base 10(unsigned),formatado:"  
.text
.globl main
main:
while:
    bne $t0,0,endwhile

    la $a0,str1
    li $v0,printStr
    syscall

    li $v0,readInt10
    syscall
    move $t1,$v0

    la $a0,str2
    li $v0,printStr
    syscall

    move $a0,$t1
    li $a1,2
    li $v0,printInt                              #printInt(value,2)
    syscall

    la $a0,str3
    li $v0,printStr
    syscall

    move $a0,$t1
    li $a1,16
    li $v0,printInt
    syscall


    la $a0,str4
    li $v0,printStr
    syscall

    move $a0,$t1
    li $a1,10
    li $v0,printInt
    syscall

    la $a0,str5
    li $v0,printStr
    syscall
    move $a0,$t1
    li $a1,0x0004000C        #$a1=10 | 5<<16???
# 2nd method 
#    lui $a1,5
#    ori $a1,$a1,10
# 3nd method 
#     ori $a1,$0,5
#     sll $a1,$a1,16
#     ori $a1,$a1,10

    li $v0,printInt10
    syscall
    j while
    

endwhile:
    li $v0,0
    jr $ra

    

    