#include <detpic32.h>

volatile int duty=1;
void delay(int ms);
void set(unsigned int num);

int main()
{
    //configuração do porto RB de entrada
    TRISB=TRISB & 0x0009;

    //configuração do timer 2 
    T2CONbits.TCKPS = 2; // 1:4 prescaler (i.e. fout_presc = 625 KHz)     2,034505208
    PR2 = (5000000/150)-1; // Fout = 20MHz / (4 * (x + 1)) = 10 Hz
    TMR2 = 0; // Clear timer T2 count register
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)

    //configuração do OC2
    OC2CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC2CONbits.OCTSEL =0;// Use timer T2 as the time base for PWM generation
    OC2RS = ((PR2 +1)*duty)/100;
    OC2CONbits.ON = 1; // Enable OC1 module

    while(1)
    {
        if((PORTB & 0x0009)==0x0001)
        {
            set(25);
            printf("25");
        }
        if((PORTB & 0x0009)==0x0008)
        {
            set(70);
            printf("70");
        }
        delay(10);
    }
}
    void delay(int ms)
    {
        resetCoreTimer();
        while(readCoreTimer()<20000*ms);
    }
    void set(unsigned int num)
    {
        if(duty>=0 && duty <=100)
        {
            OC2RS = ((PR2 + 1)*num)/100;
        }
    }
