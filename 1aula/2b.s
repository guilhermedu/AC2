# int main(void)
# { 
# char c;
# do
# {
# c = getChar();
# putChar( c );
# } while( c != '\n' );
# return 0;
# }

#Mapa de Registos
#$t0=c
.data
.equ getChar,2
.equ putChar,3
.text
.globl main
main:
do:
  li $v0, getChar
    syscall
    move $t0, $v0     # $t0 = c
    move $a0, $v0
# addi $a0,$a0,1
  li $v0, putChar
    syscall
  bne $t0, '\n', do # se c != '\n' volta ao inicio
  li $v0, 0
  jr $ra                    # jump to $ra