
    .equ    RESET_CORE_TIMER, 12
    .equ    READ_CORE_TIMER, 11
    .equ putChar, 3
    .equ printInt, 6
    .data
    .text
    .globl main

main:                                   # int main(void) {
    addiu   $sp, $sp, -8            #       abrir espaco na pilha
    sw      $ra, 0($sp)             #       guardar o $ra
    sw      $s0, 4($sp)             #       guardar o $s0
    li      $s0, 0                  #       counter = 0;
while:                                  #       while(1) {
    li      $a0, 1000               #               $a0 = 1000;
    jal     delay                   #               delay(1000);
    addi $s0,$s0,1    
    move $a0,$s0                    #$a0 = ++counter;
    li $a1,0x0004000A
    li $v0,printInt                 #v0=6;
    syscall
    j while
    li $a0,'\r'
    li $v0,putChar
    syscall
    j while
    li $v0,0
    lw $ra,0($sp)
    lw $s0,4($sp)
    addiu $sp,$sp,8
    jr $ra

delay:
    move $t0,$a0    # $t0=ms;

for: ble $t0,0,endfor   
     li $v0,RESET_CORE_TIMER
     syscall
read:
    li $v0,READ_CORE_TIMER
    syscall
    bltu $v0,20000,read
    addi $t0,$t0,-1
    j for
endfor:
    jr $ra 
