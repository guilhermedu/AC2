#include <detpic32.h>

int main()
{
    T3CONbits.TCKPS = 7; 
    PR3 = 39061; 
    TMR3 = 0; 
    T3CONbits.TON = 1; 

    while(1)
    {
        //wait while T3IF
        while(IFS0bits.T3IF != 1);
        IFS0bits.T3IF=0;
        //Reset T3IF
        putchar(' .');
    }
    return 0;

}