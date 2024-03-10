#include <detpic32.h>

int main(void)
{
    // Configure Timer T3 (2 Hz with interrupts disable)
    T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 39063; // Fout = 20MHz / (32 * (39063 + 1)) = 2 Hz
    TMR3 = 0; // Clear timer T3 count register
    T3CONbits.TON = 1; // Enable timer T3 (must be the last command of the
    // timer configuration sequence) T2 (must be the last command of the
    // timer configuration sequence)
    
    while(1)
    {
        // wait while T3IF = 0
        while(IFS0bits.T3IF !=1);
        IFS0bits.T3IF = 0;
        // Reset T3IF
        putchar('.');
    }
    return 0;
}