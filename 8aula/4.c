#include <detpic32.h>

int main(void)
{
    TRISE = TRISE & 0xFFF5;
    LATE = LATE & 0xFFF5;
    T1CONbits.TCKPS = 6;    // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR1 = 62499;            // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR1 = 0;               // Clear timer T3 count register
    T1CONbits.TON = 1;      // Enable timer T3 (must be the last command of the
                            // timer configuration sequence) 
    
    IPC1bits.T1IP = 2;      // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1;      // Enable timer T3 interrupts
    IFS0bits.T1IF = 0;      // Reset timer T3 interrupt flag 

    T3CONbits.TCKPS = 4;    // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 49999;            // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0;               // Clear timer T3 count register
    T3CONbits.TON = 1;      // Enable timer T3 (must be the last command of the
                            // timer configuration sequence) 
    
    IPC3bits.T3IP = 2;      // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1;      // Enable timer T3 interrupts
    IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag 

    EnableInterrupts();
    while(1);
    return 0;
}

void _int_(4) isr_T1(void)
{
    LATEbits.LATE1 = ~LATEbits.LATE1;
    putChar('1');
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void)
{
    LATEbits.LATE3 = ~LATEbits.LATE3; 
    putChar('3');
    IFS0bits.T3IF = 0;
}