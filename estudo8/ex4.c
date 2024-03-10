#include <detpic32.h>

int main(void)
{
    // configure Timers T1 and T3 with interrupts enabled
    T1CONbits.TCKPS = 6; // 1:642 prescaler (i.e. fout_presc = 625 KHz)
    PR1 = 62499; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR1 = 0; // Clear timer T2 count register
    T1CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)

    IPC1bits.T1IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1; // Enable timer T2 interrupts
    IFS0bits.T1IF = 0; // Reset timer T2 interrupt flag

    T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 39061; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0; // Clear timer T2 count register
    T3CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)

    IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; // Enable timer T2 interrupts
    IFS0bits.T3IF = 0; // Reset timer T2 interrupt flag

    EnableInterrupts(); // Global Interrupt Enable 

    while(1);
    return 0;
}
 void _int_(4) isr_T1(void)
 {
    LATEbits.LATE1=~LATEbits.LATE1;
    putchar('1');
    // Reset T1IF flag
    IFS0bits.T1IF=0;
 }
 void _int_(12) isr_T3(void)
 {
    LATEbits.LATE3=~LATEbits.LATE3;
    putchar('3');
    // Reset T3IF flag
    IFS0bits.T3IF=0;
 }