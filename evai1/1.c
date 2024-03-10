#include <detpic32.h>

volatile int duty = 1 ;


int main()
{
    TRISB=TRISB | 0x0009;

    T2CONbits.TCKPS = 2; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR2 = 49999; // Fout = 20MHz / (4 * (x + 1)) = 100 Hz
    TMR2 = 0; // Clear timer T2 count register
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)

    OC2CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC2CONbits.OCTSEL =0;// Use timer T2 as the time base for PWM generation
    OC2RS = ((PR2 + 1) * duty)/100; // Ton constant
    OC2CONbits.ON = 1; // Enable OC1 module

    while(1)
    {
        if((PORTB & 0x0009)==0x0001)
        {
            set(25);        
        }
        if((PORTB & 0x0009)==0x0008)
        {
            set(70);
        }
        delay(4000);
    }
}

void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()<20000*ms);
}

void set(int num)
{
    if(duty>=0 && duty <=100)
    {
        OC2RS=((PR2 +1)*num)/100;
    }
}