#int main(void)
#{
#char c;
#do {
#c = inkey();
#if( c != 0 )
#putChar( c );
#else
#putChar('.');
#} while( c != '\n' );
#return 0;
#}

.data
.equ getChar,2
.equ putChar,3
.equ inkey,1
.text
.globl main
main:
do:
  li $v0, getChar
    syscall
    move $t0, $v0     # $t0 = c
    move $a0, $v0
# addi $a0,$a0,1
if: beq $t0,0,while
  li $v0, putChar
    syscall
else:
  li $v0,'.'
while:
     bne $t0, '\n', do # se c != '\n' volta ao inicio
endwhile:
    li $v0,0  #return 0
  jr $ra