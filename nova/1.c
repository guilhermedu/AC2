#include <detpic32.h>

volatile int duty=1;

void delay(int ms);
void set(int num);

int main(void)
{
    //configurar portos
    TRISB=TRISB | 0x0009;

    //configurar T2 e OC2
    T2CONbits.TCKPS = 1; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR2 = (1000000/280)-1; // Fout = 20MHz / (2 * (x + 1)) = 280 Hz
    TMR2 = 0; // Reset timer T2 count register
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)
    OC2CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC2CONbits.OCTSEL =1;// Use timer T2 as the time base for PWM generation
    OC2RS = ((PR2+1)*duty)/100; // Ton constant
    OC2CONbits.ON = 1; // Enable OC1 module

    while(1)
    {
        if((PORTB & 0x0009)==0x0001)
        {
            set(25);
            putChar('2');
        }
        if((PORTB & 0x0009)==0x0008)
        {
            set(70);
            putchar('7');
        }
        delay(250);
    }

}

void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()<PBCLK/1000000*ms);
}

void set(int num)
{
    if(duty>=0 && 100<=duty)
    {
       OC2RS = ((PR2+1)*num)/100; 
    }

}
