#include <detpic32.h>

volatile int duty = 1; // global variable
void delay(int ms);
void set(unsigned int num);

int main(void)
{
    //port
    TRISB = TRISB | 0x0009; //0000 0000 0000 1001 -> RB0 e RB3 como entrada

    //Timer
    T2CONbits.TCKPS = 2; // 1:4 prescaler (i.e. fout_presc = 150 Hz)
    PR2 = 49999;         // Fout = 20MHz / (4 * ( 33332+ 1)) = 100 Hz
    TMR2 = 0;               // Reset timer T2 count register
    T2CONbits.TON = 1;      // Enable timer T2 (must be the last command of the
                            // timer configuration sequence)
    

    //OC2
    OC2CONbits.OCM = 6; //PWM mode on OCx; fault pin disabled
    OC2CONbits.OCTSEL = 0; // Use timer T2 as the time base for PWM generation
    OC2RS = ((PR2 + 1) * duty) / 100; 
    OC2CONbits.ON = 1; // Enable OC1 module

    while(1)
    {
        if((PORTB & 0x0009) == 0x0001)
            set(25);
        if((PORTB & 0x0009) == 0x0008)
            set(70);
        
        delay(5000);            // 250us 
    }
    
}

void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()< ms * 20000);
}
void set(unsigned int num)
{
    if(duty >=0 && duty <= 100)
        OC2RS = ((PR2 + 1) * num) / 100;
}