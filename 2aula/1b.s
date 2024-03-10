#int main(void)
#{
#int counter = 0;
#while(1)
#{
#resetCoreTimer();
#while(readCoreTimer() < 200000);
#printInt(counter++, 10 | 4 << 16); // Ver nota1
#putChar('\r'); // cursor regressa ao inicio da linha
#}
#return 0;
#}

.data
.equ putChar,3
.equ printInt,6
.equ READ_CORE_TIMER,11
.equ RESET_CORE_TIMER,12
.text
.globl main

main: 
    li $t0,0 # counter=0
while: # while (1) {
    li $v0,RESET_CORE_TIMER #
    syscall # resetCoreTimer()

while2: 
    li $v0,READ_CORE_TIMER
    syscall
    blt $v0, 20000000,while2

    move $a0,$t0
    addi $t0,$t0,1

    li $t1,4
    sll $t1,$t1,16
    ori $t1,$t1,10

    li $v0,printInt
    syscall

    la $a0,'\r'
    li $v0,putChar
    syscall

    j while
    li $v0,0
    syscall
    jr $ra #f